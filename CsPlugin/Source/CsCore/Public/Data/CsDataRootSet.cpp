// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/CsDataRootSet.h"
#include "CsCore.h"

// Types
#include "Data/CsTypes_DataEntry.h"
// Library
#include "Data/CsLibrary_DataRootSet.h"
#include "Level/CsLibrary_Level.h"
#include "Library/CsLibrary_Valid.h"

#if WITH_EDITOR
// Library
	// Common
#include "Library/CsLibrary_World.h"
#include "Library/Load/CsLibrary_Load.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsDataRootSet
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsDataRootSet, AddDataTable);

			CS_DEFINE_CACHED_STRING(GetCsDataRootSet, "GetCsDataRootSet()");

			CS_DEFINE_CACHED_STRING(Datas, "Datas");
			CS_DEFINE_CACHED_STRING(DataTables, "DataTables");
			CS_DEFINE_CACHED_STRING(Payloads, "Payloads");
		}

		namespace Name
		{
			CS_DEFINE_CACHED_NAME(Datas, "Datas");
			CS_DEFINE_CACHED_NAME(DataTables, "DataTables");
			CS_DEFINE_CACHED_NAME(Payloads, "Payloads");
		}
	}
}

#pragma endregion Cached

#define MemberType FCsDataRootSet::EMember
MemberType FCsDataRootSet::GetMember(const FName& MemberName)
{
	using namespace NCsDataRootSet::NCached;

	if (MemberName == Name::Datas)
		return MemberType::Datas;
	if (MemberName == Name::DataTables)
		return MemberType::DataTables;
	if (MemberName == Name::Payloads)
		return MemberType::Payloads;
	return MemberType::Datas;
}
#undef MemberType

#if WITH_EDITOR

void FCsDataRootSet::AddDataTable(const FName& EntryName, const TSoftObjectPtr<UDataTable>& DataTable, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
{
	using namespace NCsDataRootSet::NCached;

	const FString& Context = Str::AddDataTable;

	// Check DataTables exists
	CS_IS_PTR_NULL_EXIT(DataTables)

	// Check Path is valid
	const FSoftObjectPath& Path = DataTable.ToSoftObjectPath();

	if (!Path.IsValid())
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: DataTable is NOT Valid."), *Context));
		return;
	}

	FCsDataEntry_DataTable* RowPtr = DataTables->FindRow<FCsDataEntry_DataTable>(EntryName, Context, false);

	// Add the DataTable if has NOT already been added
	if (!RowPtr)
	{
		FCsDataEntry_DataTable Row;
		DataTables->AddRow(EntryName, Row);

		RowPtr = DataTables->FindRow<FCsDataEntry_DataTable>(EntryName, Context);
	}

	RowPtr->DataTable = DataTable;
	RowPtr->bAllRows  = true;
	RowPtr->Populate();

	DataTables->MarkPackageDirty();
}

void FCsDataRootSet::AddDataTable(const FName& EntryName, const TSoftObjectPtr<UDataTable>& DataTable, const TSet<FName>& RowNames, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
{
	using namespace NCsDataRootSet::NCached;

	const FString& Context = Str::AddDataTable;

	// Check Core_DataRootSet.DataTables exists
	CS_IS_PTR_NULL_EXIT(DataTables)

	// Check Path is valid
	const FSoftObjectPath& Path = DataTable.ToSoftObjectPath();

	if (!Path.IsValid())
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: DataTable is NOT Valid."), *Context));
		return;
	}

	// Find or Add the DataTable
	FCsDataEntry_DataTable* RowPtr = DataTables->FindRow<FCsDataEntry_DataTable>(EntryName, Context);

	bool AllRowsAlreadySet = false;

	// Add the DataTable if has NOT already been added
	if (!RowPtr)
	{
		FCsDataEntry_DataTable Row;
		DataTables->AddRow(EntryName, Row);

		RowPtr = DataTables->FindRow<FCsDataEntry_DataTable>(EntryName, Context);

		AllRowsAlreadySet = RowPtr->bAllRows;
	}
	else
	{
		// DataTable changed, Update
		if (RowPtr->DataTable.ToSoftObjectPath() != DataTable.ToSoftObjectPath())
		{
			RowPtr->Rows.Reset();
		}
	}

	RowPtr->DataTable = DataTable;
	RowPtr->bAllRows  = AllRowsAlreadySet || RowNames.Num() == CS_EMPTY;

	if (!AllRowsAlreadySet)
		RowPtr->Rows.Append(RowNames);

	RowPtr->Populate();

	DataTables->MarkPackageDirty();
}

#endif // #if WITH_EDITOR

#define MapType FCsDataRootSet::EMap
bool FCsDataRootSet::IsPersistentLevel(UObject* WorldContext, const MapType& Type) const
{
	FString MapName;

	// Entry
	if (Type == MapType::Entry)
		MapName = EntryMap.GetLongPackageName();
	// Main
	else
	if (Type == MapType::Main)
		MapName = MainMap.GetLongPackageName();
		
	typedef NCsLevel::NPersistent::FLibrary LevelLibrary;

	return LevelLibrary::SafeIsName(WorldContext, MapName);
}
#undef MapType

bool FCsDataRootSet::IsValidChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
	using namespace NCsDataRootSet::NCached;

	#define CS_TEMP_CHECK(Member) if (MemberType == EMember::Member) \
	{ \
		checkf(Member.ToSoftObjectPath().IsValid(), TEXT("%s: %s.%s.%s is NOT Valid."), *Context, *(WorldContext->GetName(), *Str::GetCsDataRootSet, *Str::Member)); \
	}

	#undef CS_TEMP_CHECK

	return true;
}

const TSoftObjectPtr<UDataTable>& FCsDataRootSet::GetDataTableSoftObjectChecked(const FString& Context, const EMember& MemberType) const
{
	#define CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(Member) if (MemberType == EMember::Member) \
		return Member;

	#undef CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED

	checkf(0, TEXT("%s: Failed to get DataTable SoftObject for MemberType."), *Context);
	static const TSoftObjectPtr<UDataTable> DT;
	return DT;
}

UDataTable* FCsDataRootSet::GetSafeDataTable(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
	#define CS_TEMP_GET_SAFE_DATA_TABLE(Member) if (MemberType == EMember::Member) \
		return Member;

	CS_TEMP_GET_SAFE_DATA_TABLE(Datas)
	CS_TEMP_GET_SAFE_DATA_TABLE(DataTables)
	CS_TEMP_GET_SAFE_DATA_TABLE(Payloads)

	#undef CS_TEMP_GET_SAFE_DATA_TABLE

	UE_LOG(LogCs, Warning, TEXT("%s: Failed to get DataTable for MemberType."), *Context);
	return nullptr;
}

UDataTable* FCsDataRootSet::GetDataTableChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
	return GetDataTableChecked(Context, MemberType);
}

UDataTable* FCsDataRootSet::GetDataTableChecked(const FString& Context, const EMember& MemberType) const
{
	UDataTable* DT = nullptr;

	#define CS_TEMP_GET_DATA_TABLE(Member) if (MemberType == EMember::Member) \
		DT = Member;

	CS_TEMP_GET_DATA_TABLE(Datas)
	CS_TEMP_GET_DATA_TABLE(DataTables)
	CS_TEMP_GET_DATA_TABLE(Payloads)

	#undef CS_TEMP_GET_DATA_TABLE

	CS_IS_PTR_NULL_CHECKED(DT)
	return DT;
} 

uint8* FCsDataRootSet::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const FName& RowName) const
{
	return GetDataTableRowChecked(Context, MemberType, RowName);
}

uint8* FCsDataRootSet::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const UScriptStruct* RowStruct, const FName& RowName) const
{
	return GetDataTableRowChecked(Context, MemberType, RowStruct, RowName);
}

uint8* FCsDataRootSet::GetDataTableRowChecked(const FString& Context, const EMember& MemberType, const FName& RowName) const
{
	UDataTable* DT = GetDataTableChecked(Context, MemberType);

#if WITH_EDITOR
	UCsLibrary_Load::LoadDataTableRowChecked(Context, DT, RowName, NCsLoadFlags::All, NCsLoadCodes::All);
#endif // #if WITH_EDITOR

	const TMap<FName, uint8*>& RowMap = DT->GetRowMap();

	for (const TPair<FName, uint8*>& Pair : RowMap)
	{
		const FName& Name = Pair.Key;
		uint8* RowPtr	  = Pair.Value;

		if (Name == RowName)
			return RowPtr;
	}
	checkf(0, TEXT("Failed to find Row with Name: %s from DataTable: %s."), *Context, *(RowName.ToString()), *(DT->GetName()));
	return nullptr;
}

uint8* FCsDataRootSet::GetDataTableRowChecked(const FString& Context, const EMember& MemberType, const UScriptStruct* RowStruct, const FName& RowName) const
{
	UDataTable* DT = GetDataTableChecked(Context, MemberType);

#if WITH_EDITOR
	UCsLibrary_Load::LoadDataTableRowChecked(Context, DT, RowName, NCsLoadFlags::All, NCsLoadCodes::All);
#endif // #if WITH_EDITOR

	CS_IS_PTR_NULL_CHECKED(RowStruct)

	checkf(DT->GetRowStruct() == RowStruct, TEXT("%s: DataTable: %s RowStruct: %s != %s."), *Context, *(DT->GetName()), *(DT->GetRowStruct()->GetName()), *(RowStruct->GetName()));

	const TMap<FName, uint8*>& RowMap = DT->GetRowMap();

	for (const TPair<FName, uint8*>& Pair : RowMap)
	{
		const FName& Name = Pair.Key;
		uint8* RowPtr = Pair.Value;

		if (Name == RowName)
			return RowPtr;
	}
	checkf(0, TEXT("Failed to find Row with Name: %s from DataTable: %s."), *Context, *(RowName.ToString()), *(DT->GetName()));
	return nullptr;
}