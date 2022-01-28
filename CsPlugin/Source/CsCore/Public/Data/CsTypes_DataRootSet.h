// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsTypes_DataRootSet.generated.h"

class UObject;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_DataRootSet
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Data")
	bool bApply;

	/** Populate all the soft references from
		DataRootSet->Datas and DataRootSet->DataTables. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Data")
	bool bPopulateAll;

	/** Populate all the soft references for rows listed
		under DataRowsToPopulate and DataTableRowsToPopulate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Data")
	bool bPopulateSubset;

	/** Row names from DataRootSet->Datas to populate soft references
		for when bPopulateSubset is toggled. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Data")
	TSet<FName> DataRowsToPopulate;

	/** Row names from DataRootSet->DataTables to populate soft references
		for when bPopulateSubset is toggled. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Data")
	TSet<FName> DataTableRowsToPopulate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Data")
	TSoftClassPtr<UObject> DataRootSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Data", meta = (LongPackageName))
	FDirectoryPath DirectoryToAlwaysCook;

	FCsSettings_DataRootSet() :
		bApply(false),
		bPopulateAll(false),
		bPopulateSubset(false),
		DataRowsToPopulate(),
		DataTableRowsToPopulate(),
		DataRootSet(),
		DirectoryToAlwaysCook()
	{
	}
};