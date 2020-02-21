// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Data/CsDataRootSet.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Load.h"
// DataTable
#include "Engine/DataTable.h"

// Cached
#pragma region

namespace NCsDataRootSetCached
{
	namespace Str
	{
		const FString AddDataTable = TEXT("UCsDataRootSet::AddDataTable");
	}
}

#pragma endregion Cached


UCsDataRootSet::UCsDataRootSet(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#if WITH_EDITOR

void UCsDataRootSet::AddDataTable(const TSoftObjectPtr<UDataTable>& InDataTable)
{
	// Check DataTables exists
	if (!DataTables)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsDataRootSet::AddDataTable: DataTables is NULL."));
		return;
	}

	// Check Path is valid
	const FSoftObjectPath& Path = InDataTable.ToSoftObjectPath();

	if (!Path.IsValid())
	{
		UE_LOG(LogCs, Warning, TEXT("UCsDataRootSet::AddDataTable: InDataTable is NOT Valid."));
		return;
	}

	// Find or Add the DataTable
	const FName& DataTableName = FName(*Path.GetAssetName());

	const FString& Context = NCsDataRootSetCached::Str::AddDataTable;

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

void UCsDataRootSet::AddDataTable(const TSoftObjectPtr<UDataTable>& InDataTable, const TSet<FName>& RowNames)
{
	// Check DataTables exists
	if (!DataTables)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsDataRootSet::AddDataTable: DataTables is NULL."));
		return;
	}

	// Check Path is valid
	const FSoftObjectPath& Path = InDataTable.ToSoftObjectPath();

	if (!Path.IsValid())
	{
		UE_LOG(LogCs, Warning, TEXT("UCsDataRootSet::AddDataTable: InDataTable is NOT Valid."));
		return;
	}

	// Find or Add the DataTable
	const FName& DataTableName = FName(*Path.GetAssetName());

	const FString& Context = NCsDataRootSetCached::Str::AddDataTable;

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

void UCsDataRootSet::AddDataTables(const TSet<TSoftObjectPtr<UDataTable>>& InDataTables)
{
	// Check DataTables exists
	if (!DataTables)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsDataRootSet::AddDataTables: DataTables is NULL."));
		return;
	}

	for (const TSoftObjectPtr<UDataTable>& DT : InDataTables)
	{
		// Check Path is valid
		const FSoftObjectPath& Path = DT.ToSoftObjectPath();

		if (!Path.IsValid())
		{
			UE_LOG(LogCs, Warning, TEXT("UCsDataRootSet::AddDataTables: DT is NOT Valid."));
			continue;
		}

		AddDataTable(DT);
	}
}

void UCsDataRootSet::AddDataTables(const TMap<TSoftObjectPtr<UDataTable>, TSet<FName>>& RowNamesByDataTableMap)
{
	// Check DataTables exists
	if (!DataTables)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsDataRootSet::AddDataTables: DataTables is NULL."));
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

void UCsDataRootSet::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	const FName PropertyName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	// DataTables
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UCsDataRootSet, DataTables))
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