// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsSettings_Manager_Trace.generated.h"
#pragma once

// FCsSettings_Manager_Trace
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Trace
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "4", UIMin = "4"))
	int32 MaxRequestsProcessedPerTick;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "4", UIMin = "4"))
	int32 PoolSize;

	FCsSettings_Manager_Trace() :
		MaxRequestsProcessedPerTick(64),
		PoolSize(256)
	{
	}
};

#pragma endregion FCsSettings_Manager_Trace

// FCsSettings_Manager_Trace_UnitTest
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Trace_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	FCsSettings_Manager_Trace_UnitTest()
	{
	}
};

#pragma endregion FCsSettings_Manager_Trace_UnitTest