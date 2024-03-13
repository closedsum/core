// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Debug/CsTypes_Debug.h"

#include "CsSettings_Manager_Trace.generated.h"

// FCsSettings_Manager_Trace_Debug
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSPHYSICS_API FCsSettings_Manager_Trace_Debug
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Trace")
	FCsDebugDrawTraceShape DrawRequest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Trace")
	FCsDebugDrawTraceShape DrawResponse;

	FCsSettings_Manager_Trace_Debug() :
		DrawRequest(),
		DrawResponse()
	{
	}
};

#pragma endregion FCsSettings_Manager_Trace_Debug

// FCsSettings_Manager_Trace
#pragma region

USTRUCT(BlueprintType)
struct CSPHYSICS_API FCsSettings_Manager_Trace
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Trace", meta = (ClampMin = "4", UIMin = "4"))
	int32 MaxRequestsProcessedPerTick;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Trace", meta = (ClampMin = "4", UIMin = "4"))
	int32 PoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Trace")
	FCsSettings_Manager_Trace_Debug Debug;

	FCsSettings_Manager_Trace() :
		MaxRequestsProcessedPerTick(64),
		PoolSize(256),
		Debug()
	{
	}
};

#pragma endregion FCsSettings_Manager_Trace

// FCsSettings_Manager_Trace_UnitTest
#pragma region

USTRUCT(BlueprintType)
struct CSPHYSICS_API FCsSettings_Manager_Trace_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	FCsSettings_Manager_Trace_UnitTest()
	{
	}
};

#pragma endregion FCsSettings_Manager_Trace_UnitTest