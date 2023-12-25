// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Settings
#include "Settings/CsSettings_EnumStruct.h"

#include "CsSettings_Data.generated.h"

// FCsSettings_Data_EnumStruct
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Data_EnumStruct
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Data")
	FCsSettings_EnumStruct_PopulateByDataTable ECsDataEntryData;
	
	FCsSettings_Data_EnumStruct() :
		ECsDataEntryData()
	{
		ECsDataEntryData.bRemoveFromStart_BP_Data = false;
	}

	static const FCsSettings_Data_EnumStruct& Get();
};

#pragma endregion FCsSettings_Data_EnumStruct

// FCsSettings_Data
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Data
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Data")
	FCsSettings_Data_EnumStruct EnumStructSettings;
	
	FCsSettings_Data() :
		EnumStructSettings()
	{
	}

	static const FCsSettings_Data& Get();
};

#pragma endregion FCsSettings_Data