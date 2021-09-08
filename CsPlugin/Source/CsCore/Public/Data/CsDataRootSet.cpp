// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsDataRootSet.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Load.h"
// Library
#include "Level/CsLibrary_Level.h"
#include "Library/CsLibrary_Valid.h"

// Cached
#pragma region

namespace NCsDataRootSetCached
{
	namespace Str
	{
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsDataRootSet, AddDataTable);
	}
}

#pragma endregion Cached

#if WITH_EDITOR

void FCsDataRootSet::AddDataTable(const FName& EntryName, const TSoftObjectPtr<UDataTable>& DataTable, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
{
	using namespace NCsDataRootSetCached;

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
	using namespace NCsDataRootSetCached;

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