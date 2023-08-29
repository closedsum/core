// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsSettings_Manager_Data.generated.h"

// FCsSettings_Manager_Data
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Data
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Data", meta = (ClampMin = "4", UIMin = "4"))
	int32 PayloadPoolSize;
	 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Data", meta = (ClampMin = "4", UIMin = "4"))
	int32 DataEntryDataPoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Data", meta = (ClampMin = "4", UIMin = "4"))
	int32 DataEntryDataTablePoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Data")
	bool bLoadbyDependencyGroup;

	FCsSettings_Manager_Data() :
		PayloadPoolSize(64),
		DataEntryDataPoolSize(256),
		DataEntryDataTablePoolSize(256),
		bLoadbyDependencyGroup(false)
	{
	}
};

#pragma endregion FCsSettings_Manager_Data

// FCsSettings_Manager_Data_UnitTest
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Data_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	FCsSettings_Manager_Data_UnitTest()
	{
	}
};

#pragma endregion FCsSettings_Manager_Data_UnitTest