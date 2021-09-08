// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "CsSettings_Manager_Runnable.generated.h"
#pragma once

// FCsSettings_Manager_Runnable
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Runnable
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1", UIMin = "1"))
	int32 RunnablePoolSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1", UIMin = "1"))
	int32 RunnablePayloadSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "4", UIMin = "4"))
	int32 TaskPoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "4", UIMin = "4"))
	int32 TaskPayloadSize;

	FCsSettings_Manager_Runnable() :
		RunnablePoolSize(2),
		RunnablePayloadSize(2),
		TaskPoolSize(32),
		TaskPayloadSize(4)
	{
	}
};

#pragma endregion FCsSettings_Manager_Runnable

// FCsSettings_Manager_Runnable_UnitTest
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Runnable_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	FCsSettings_Manager_Runnable_UnitTest()
	{
	}
};

#pragma endregion FCsSettings_Manager_Runnable_UnitTest