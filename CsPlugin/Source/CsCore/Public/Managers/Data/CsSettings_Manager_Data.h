// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsSettings_Manager_Data.generated.h"
#pragma once

// FCsSettings_Manager_Data
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Data
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "4", UIMin = "4"))
	int32 PayloadPoolSize;
	 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "4", UIMin = "4"))
	int32 DataEntryDataPoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "4", UIMin = "4"))
	int32 DataEntryDataTablePoolSize;

	FCsSettings_Manager_Data() :
		PayloadPoolSize(64),
		DataEntryDataPoolSize(256),
		DataEntryDataTablePoolSize(256)
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