// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsManager_Data.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Load.h"

UCsManager_Data::UCsManager_Data(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
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
	if (uint8* RowPtr = GetDataTableRow(TableName, RowName))
		return RowPtr;

	if (FCsDataEntry_DataTable** EntryPtr = DataTableEntryMap.Find(TableName))
	{
		FCsDataEntry_DataTable* Entry = *EntryPtr;

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