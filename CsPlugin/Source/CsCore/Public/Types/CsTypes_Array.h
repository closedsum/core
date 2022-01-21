// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.

#include "CsTypes_Array.generated.h"
#pragma once

// FCsArray_int32
#pragma region

USTRUCT(BlueprintType)
struct FCsArray_int32
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> Array;

	FCsArray_int32() :
		Array()
	{
	}
};

#pragma endregion FCsArray_int32