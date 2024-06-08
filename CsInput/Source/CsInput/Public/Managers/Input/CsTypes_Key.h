// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "InputCoreTypes.h"

#include "CsTypes_Key.generated.h"

// FCsSet_Key
#pragma region

USTRUCT(BlueprintType)
struct CSINPUT_API FCsSet_Key
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsInput|Input")
	TSet<FKey> Set;

	FCsSet_Key() :
		Set()
	{
	}
};

#pragma endregion FCsSet_Key