// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Data/CsManager_Data.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Load.h"

// Cached
#pragma region

namespace NCsManagerDataCached
{
	namespace Str
	{
		const FString GenerateMaps = TEXT("UCsManager_Data::GenerateMaps");
	}
}

#pragma endregion

UCsManager_Data::UCsManager_Data(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCsManager_Data::GenerateMaps()
{
	// Datas
	if (Datas)
	{
		const UScriptStruct* ScriptStruct = Datas->GetRowStruct();

		checkf(ScriptStruct == FCsDataEntry_Data::StaticStruct(), TEXT("UCsManager_Data::GenerateMaps: The Row Struct for Data: %s is of incorrect type: %s. It should be FCsDataEntry_Data"), *(Datas->GetName()), *(ScriptStruct->GetName()));

		DataEntryMap.Reset();

		TArray<FName> RowNames = Datas->GetRowNames();

		for (const FName& RowName : RowNames)
		{
			FCsDataEntry_Data* RowPtr = Datas->FindRow<FCsDataEntry_Data>(RowName, NCsManagerDataCached::Str::GenerateMaps);

			DataEntryMap.Add(RowName, RowPtr);
		}
	}
	// DataTables
	if (DataTables)
	{
		const UScriptStruct* ScriptStruct = DataTables->GetRowStruct();

		checkf(ScriptStruct == FCsDataEntry_DataTable::StaticStruct(), TEXT("UCsManager_Data::GenerateMaps: The Row Struct for Data: %s is of incorrect type: %s. It should be FCsDataEntry_DataTable"), *(DataTables->GetName()), *(ScriptStruct->GetName()));

		DataTableEntryMap.Reset();

		TArray<FName> RowNames = DataTables->GetRowNames();

		for (const FName& RowName : RowNames)
		{
			FCsDataEntry_DataTable* RowPtr = DataTables->FindRow<FCsDataEntry_DataTable>(RowName, NCsManagerDataCached::Str::GenerateMaps);

			DataTableEntryMap.Add(RowName, RowPtr);
		}
	}
	// Payloads
	if (Payloads)
	{
		const UScriptStruct* ScriptStruct = Payloads->GetRowStruct();

		checkf(ScriptStruct == FCsPayload::StaticStruct(), TEXT("UCsManager_Data::GenerateMaps: The Row Struct for Data: %s is of incorrect type: %s. It should be FCsPayload"), *(DataTables->GetName()), *(ScriptStruct->GetName()));

		PayloadMap.Reset();

		TArray<FName> RowNames = Payloads->GetRowNames();

		for (const FName& RowName : RowNames)
		{
			FCsPayload* RowPtr = Payloads->FindRow<FCsPayload>(RowName, NCsManagerDataCached::Str::GenerateMaps);

			PayloadMap.Add(RowName, RowPtr);
		}
	}
}

// Load
#pragma region

void UCsManager_Data::LoadPayload(const FName& PayloadName)
{
	if (FCsPayload** PayloadPtr = PayloadMap.Find(PayloadName))
	{
		FCsPayload* Payload = *PayloadPtr;

		// Datas
		for (FCsPayload_Data& Payload_Data : Payload->Datas)
		{

		}

		// DataTables
		for (FCsPayload_DataTable& Payload_DataTable : Payload->DataTables)
		{
			const FName& TableName = Payload_DataTable.ShortCode;

			UDataTable* DT = LoadDataTable(TableName);

			const UScriptStruct* ScriptStruct = DT->GetRowStruct();
			UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
			UStruct* const Struct			  = Temp;

			TArray<FName> RowNames;

			// All Rows
			if (Payload_DataTable.bAllRows)
			{
				RowNames = DT->GetRowNames();
			}
			// Specified Rows
			else
			{
				RowNames = Payload_DataTable.Rows;
			}

			for (const FName& RowName : RowNames)
			{
				if (IsLoadedDataTableRow(TableName, RowName))
					continue;

				uint8* RowPtr = DT->FindRowUnchecked(RowName);

				UCsLibrary_Load::LoadStruct(RowPtr, Struct);
			}
		}

		PayloadMap_Loaded.Add(PayloadName, Payload);
	}
}

	// DataTable
#pragma region

UDataTable* UCsManager_Data::LoadDataTable(const FName& TableName)
{
	if (UDataTable* Table = GetDataTable(TableName))
		return Table;

	if (FCsDataEntry_DataTable** EntryPtr = DataTableEntryMap.Find(TableName))
	{
		FCsDataEntry_DataTable* Entry = *EntryPtr;

		UCsLibrary_Load::LoadStruct(Entry, FCsDataEntry_DataTable::StaticStruct());

		return Entry->Get();
	}
	// LOG
	return nullptr;
}

uint8* UCsManager_Data::LoadDataTableRow(const FName& TableName, const FName& RowName)
{
	// Check if DataTable and Row are already loaded
	if (uint8* RowPtr = GetDataTableRow(TableName, RowName))
		return RowPtr;

	if (FCsDataEntry_DataTable** EntryPtr = DataTableEntryMap.Find(TableName))
	{
		FCsDataEntry_DataTable* Entry = *EntryPtr;

		// If DataTable is NOT loaded, load it
		if (!Entry->Get())
			UCsLibrary_Load::LoadStruct(Entry, FCsDataEntry_DataTable::StaticStruct());

		UDataTable* DT = Entry->Get();

		const UScriptStruct* ScriptStruct = DT->GetRowStruct();
		UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
		UStruct* const Struct			  = Temp;

		if (uint8* RowPtr = DT->FindRowUnchecked(RowName))
		{
			UCsLibrary_Load::LoadStruct(RowPtr, Struct);

			return RowPtr;
		}
	}
	// LOG
	return nullptr;
}

bool UCsManager_Data::IsLoadedDataTableRow(const FName& TableName, const FName& RowName)
{
	if (uint8* RowPtr = GetDataTableRow(TableName, RowName))
		return true;
	return false;
}

#pragma endregion DataTable

#pragma endregion Load

// Get
#pragma region

UDataTable* UCsManager_Data::GetDataTable(const FName& TableName)
{
	if (UDataTable** TablePtr = DataTableMap_Loaded.Find(TableName))
		return *TablePtr;
	return nullptr;
}

uint8* UCsManager_Data::GetDataTableRow(const FName& TableName, const FName& RowName)
{
	if (TMap<FName, uint8*>* TablePtr = DataTableRowMap_Loaded.Find(TableName))
	{
		if (uint8** RowPtr = TablePtr->Find(RowName))
		{
			return *RowPtr;
		}
	}
	return nullptr;
}

#pragma endregion Get

// Editor
#pragma region
#if WITH_EDITOR

void UCsManager_Data::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	const FName PropertyName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	// Datas
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UCsManager_Data, Datas))
	{
		if (Datas)
		{
			const UScriptStruct* ScriptStruct = Datas->GetRowStruct();

			if (ScriptStruct != FCsDataEntry_DataTable::StaticStruct())
			{
				// LOG
				Datas = nullptr;
			}
		}
	}
	// DataTables
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UCsManager_Data, DataTables))
	{
		if (DataTables)
		{
			const UScriptStruct* ScriptStruct = DataTables->GetRowStruct();

			if (ScriptStruct != FCsDataEntry_DataTable::StaticStruct())
			{
				// LOG
				DataTables = nullptr;
			}
		}
	}
	// Payloads
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UCsManager_Data, Payloads))
	{
		if (Payloads)
		{
			const UScriptStruct* ScriptStruct = Payloads->GetRowStruct();

			if (ScriptStruct != FCsDataEntry_DataTable::StaticStruct())
			{
				// LOG
				Payloads = nullptr;
			}
		}
	}

	// Payload
	{
		// Payload.DataTable
		/*
		if (PropertyName == GET_MEMBER_NAME_CHECKED(ACsLevelScriptActor, Payload) &&
			MemberPropertyName == GET_MEMBER_NAME_CHECKED(FCsPayload, DataTable))
		{

		}
		*/
	}

	Super::PostEditChangeProperty(e);
}

void UCsManager_Data::PostEditChangeChainProperty(FPropertyChangedChainEvent& e)
{
	const FName PropertyName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	Super::PostEditChangeChainProperty(e);
}

#endif // #if WITH_EDITOR
#pragma endregion Editor