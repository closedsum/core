// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "CsSettings_Manager_Load.generated.h"
#pragma once

// FCsSettings_Manager_Load
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Load
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "4", UIMin = "4"))
	int32 PoolSize;
	 
	FCsSettings_Manager_Load() :
		PoolSize(64)
	{
	}
};

#pragma endregion FCsSettings_Manager_Load

// FCsSettings_Manager_Load_UnitTest
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Load_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	FCsSettings_Manager_Load_UnitTest()
	{
	}
};

#pragma endregion FCsSettings_Manager_Load_UnitTest