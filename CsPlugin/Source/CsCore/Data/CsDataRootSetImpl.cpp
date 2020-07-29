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

void UCsDataRootSetImpl::AddDataTable(const TSoftObjectPtr<UDataTable>& InDataTable)
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
	const FSoftObjectPath& Path = InDataTable.ToSoftObjectPath();

	if (!Path.IsValid())
	{
		UE_LOG(LogCs, Warning, TEXT("%s: InDataTable is NOT Valid."), *Context);
		return;
	}

	// Find or Add the DataTable
	const FName& DataTableName = FName(*Path.GetAssetName());

	FCsDataEntry_DataTable* RowPtr = DataTables->FindRow<FCsDataEntry_DataTable>(DataTableName, Context);

	// Add the DataTable if has NOT already been added
	if (!RowPtr)
	{
		FCsDataEntry_DataTable Row;
		DataTables->AddRow(DataTableName, Row);

		RowPtr = DataTables->FindRow<FCsDataEntry_DataTable>(DataTableName, Context);
	}

	RowPtr->Name	  = DataTableName;
	RowPtr->DataTable = InDataTable;
	RowPtr->bAllRows  = true;
	RowPtr->Populate();

	DataTables->MarkPackageDirty();
}

void UCsDataRootSetImpl::AddDataTable(const TSoftObjectPtr<UDataTable>& InDataTable, const TSet<FName>& RowNames)
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
	const FSoftObjectPath& Path = InDataTable.ToSoftObjectPath();

	if (!Path.IsValid())
	{
		UE_LOG(LogCs, Warning, TEXT("%s: InDataTable is NOT Valid."), *Context);
		return;
	}

	// Find or Add the DataTable
	const FName& DataTableName = FName(*Path.GetAssetName());

	FCsDataEntry_DataTable* RowPtr = DataTables->FindRow<FCsDataEntry_DataTable>(DataTableName, Context);

	bool AllRowsAlreadySet = false;

	// Add the DataTable if has NOT already been added
	if (!RowPtr)
	{
		FCsDataEntry_DataTable Row;
		DataTables->AddRow(DataTableName, Row);

		RowPtr = DataTables->FindRow<FCsDataEntry_DataTable>(DataTableName, Context);

		AllRowsAlreadySet = RowPtr->bAllRows;
	}

	RowPtr->Name	  = DataTableName;
	RowPtr->DataTable = InDataTable;
	RowPtr->bAllRows  = AllRowsAlreadySet || RowNames.Num() == CS_EMPTY;

	if (!AllRowsAlreadySet)
		RowPtr->Rows = RowNames;

	RowPtr->Populate();

	DataTables->MarkPackageDirty();
}

void UCsDataRootSetImpl::AddDataTables(const TSet<TSoftObjectPtr<UDataTable>>& InDataTables)
{
	// Check DataTables exists
	if (!DataTables)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsDataRootSetImpl::AddDataTables: DataTables is NULL."));
		return;
	}

	for (const TSoftObjectPtr<UDataTable>& DT : InDataTables)
	{
		// Check Path is valid
		const FSoftObjectPath& Path = DT.ToSoftObjectPath();

		if (!Path.IsValid())
		{
			UE_LOG(LogCs, Warning, TEXT("UCsDataRootSetImpl::AddDataTables: DT is NOT Valid."));
			continue;
		}

		AddDataTable(DT);
	}
}

void UCsDataRootSetImpl::AddDataTables(const TMap<TSoftObjectPtr<UDataTable>, TSet<FName>>& RowNamesByDataTableMap)
{
	// Check DataTables exists
	if (!DataTables)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsDataRootSetImpl::AddDataTables: DataTables is NULL."));
		return;
	}

	for (const TPair<TSoftObjectPtr<UDataTable>, TSet<FName>>& Pair : RowNamesByDataTableMap)
	{
		const TSoftObjectPtr<UDataTable>& DT = Pair.Key;
		const TSet<FName>& RowNames			 = Pair.Value;

		if (RowNames.Num() == CS_EMPTY)
			AddDataTable(DT);
		else
			AddDataTable(DT, RowNames);
	}
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