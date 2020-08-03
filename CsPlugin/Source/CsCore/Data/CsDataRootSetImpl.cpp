// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsDataRootSetImpl.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Load.h"
// DataTable
#include "Engine/DataTable.h"

// Cached
#pragma region

namespace NCsDataRootSetImplCached
{
	namespace Str
	{
		const FString AddDataTable = TEXT("UCsDataRootSetImpl::AddDataTable");
	}
}

#pragma endregion Cached


UCsDataRootSetImpl::UCsDataRootSetImpl(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#if WITH_EDITOR

void UCsDataRootSetImpl::AddDataTable(const FName& EntryName, const TSoftObjectPtr<UDataTable>& DataTable)
{
	using namespace NCsDataRootSetImplCached;

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

	RowPtr->Name	  = EntryName;
	RowPtr->DataTable = DataTable;
	RowPtr->bAllRows  = true;
	RowPtr->Populate();

	DataTables->MarkPackageDirty();
}

void UCsDataRootSetImpl::AddDataTable(const FName& EntryName, const TSoftObjectPtr<UDataTable>& DataTable, const TSet<FName>& RowNames)
{
	using namespace NCsDataRootSetImplCached;

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

	RowPtr->Name	  = EntryName;
	RowPtr->DataTable = DataTable;
	RowPtr->bAllRows  = AllRowsAlreadySet || RowNames.Num() == CS_EMPTY;

	if (!AllRowsAlreadySet)
		RowPtr->Rows.Append(RowNames);

	RowPtr->Populate();

	DataTables->MarkPackageDirty();
}

#endif // #if WITH_EDITOR

// Editor
#pragma region
#if WITH_EDITOR

void UCsDataRootSetImpl::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	const FName PropertyName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	// DataTables
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UCsDataRootSetImpl, DataTables))
	{
		if (DataTables)
		{
			if (FCsDataEntry_DataTable::StaticStruct() != DataTables->GetRowStruct())
			{
				DataTables = nullptr;
			}
		}
	}
	// Payloads

	Super::PostEditChangeProperty(e);
}

#endif // #if WITH_EDITOR
#pragma endregion Editor