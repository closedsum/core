// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsSettings_Manager_Load.generated.h"

// FCsSettings_Manager_Load
#pragma region

USTRUCT(BlueprintType)
struct CSLOAD_API FCsSettings_Manager_Load
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Load", meta = (ClampMin = "4", UIMin = "4"))
	int32 PoolSize;
	 
	FCsSettings_Manager_Load() :
		PoolSize(64)
	{
	}

	static const FCsSettings_Manager_Load& Get();
};

#pragma endregion FCsSettings_Manager_Load

// FCsSettings_Manager_Load_UnitTest
#pragma region

USTRUCT(BlueprintType)
struct CSLOAD_API FCsSettings_Manager_Load_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	FCsSettings_Manager_Load_UnitTest()
	{
	}
};

#pragma endregion FCsSettings_Manager_Load_UnitTest