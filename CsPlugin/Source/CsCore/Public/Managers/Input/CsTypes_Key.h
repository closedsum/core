// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "CsTypes_Key.generated.h"

// FCsSet_Key
#pragma region

USTRUCT(BlueprintType)
struct FCsSet_Key
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<FKey> Set;

	FCsSet_Key() :
		Set()
	{
	}
};

#pragma endregion FCsSet_Key