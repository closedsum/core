// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "CsTypes_Map.generated.h"
#pragma once

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