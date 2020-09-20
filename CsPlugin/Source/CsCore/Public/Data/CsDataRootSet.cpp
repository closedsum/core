// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsDataRootSet.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Load.h"

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

void FCsDataRootSet::AddDataTable(const FName& EntryName, const TSoftObjectPtr<UDataTable>& DataTable)
{
	using namespace NCsDataRootSetCached;

	const FString& Context = Str::AddDataTable;

	// Check DataTables exists
	if (!DataTables)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: DataTables is NULL."), *Context);
		return;
	}

	// Check Path is valid
	const FSoftObjectPath& Path = DataTable.ToSoftObjectPath();

	if (!Path.IsValid())
	{
		UE_LOG(LogCs, Warning, TEXT("%s: DataTable is NOT Valid."), *Context);
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

void FCsDataRootSet::AddDataTable(const FName& EntryName, const TSoftObjectPtr<UDataTable>& DataTable, const TSet<FName>& RowNames)
{
	using namespace NCsDataRootSetCached;

	const FString& Context = Str::AddDataTable;

	// Check Core_DataRootSet.DataTables exists
	if (!DataTables)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: DataTables is NULL."), *Context);
		return;
	}

	// Check Path is valid
	const FSoftObjectPath& Path = DataTable.ToSoftObjectPath();

	if (!Path.IsValid())
	{
		UE_LOG(LogCs, Warning, TEXT("%s: DataTable is NOT Valid."), *Context);
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