// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "CsTypes_Map.generated.h"

// FCsMap_ObjectByName
#pragma region

USTRUCT(BlueprintType)
struct FCsMap_ObjectByName
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, UObject*> Map;

	FCsMap_ObjectByName() :
		Map()
	{
	}
};

#pragma endregion FCsMap_ObjectByName