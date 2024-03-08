// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsSettings_EnumStruct.generated.h"

class UObject;
class UDataTable;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_EnumStruct_PopulateByDataTable
{
	GENERATED_USTRUCT_BODY()

	/** Whether to populate the RowName, Name, and DisplayName from the Data. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Settings")
	bool bPopulateNamesByData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Settings", meta = (DisplayName = "Remove From Start: Defualt__"))
	bool bRemoveFromStart_Default;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Settings", meta = (DisplayName = "Remove From Start: BP_Data_"))
	bool bRemoveFromStart_BP_Data;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Settings", meta = (DisplayName = "Remove From Start: BP_ScriptData_"))
	bool bRemoveFromStart_BP_ScriptData;

	/** The prefixes to remove from the Start of the Data's name.
		NOTE: This is only used if the Data's name is used to Populate the RowName, Name, and DisplayName. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Settings")
	TArray<FString> PrefixesToRemoveFromStart;

	/** The suffixes to remove from the Start of the Data's name.
		NOTE: This is only used if the Data's name is used to Populate the RowName, Name, and DisplayName. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Settings")
	TArray<FString> SuffixesToRemoveFromStart;

	FCsSettings_EnumStruct_PopulateByDataTable() :
		bPopulateNamesByData(true),
		bRemoveFromStart_Default(true),
		bRemoveFromStart_BP_Data(true),
		bRemoveFromStart_BP_ScriptData(true),
		PrefixesToRemoveFromStart(),
		SuffixesToRemoveFromStart()
	{
	}

	void OnDataTableChanged(const UDataTable* InDataTable, const FName& InRowName, FString& OutName, FString& OutDisplayName, const FString& AssetName) const;
	void OnDataTableChanged(const UDataTable* InDataTable, const FName& InRowName, FName& OutName, const FString& AssetName) const;
};