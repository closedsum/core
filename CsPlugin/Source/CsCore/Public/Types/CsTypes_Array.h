// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsTypes_Array.generated.h"

// FCsArray_int32
#pragma region

USTRUCT(BlueprintType)
struct FCsArray_int32
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Array")
	TArray<int32> Array;

	FCsArray_int32() :
		Array()
	{
	}
};

#pragma endregion FCsArray_int32