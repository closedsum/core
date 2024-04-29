// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsTypes_Map.generated.h"

// FCsMap_ObjectByName
#pragma region

USTRUCT(BlueprintType)
struct CSTYPES_API FCsMap_ObjectByName
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Map")
	TMap<FName, UObject*> Map;

	FCsMap_ObjectByName() :
		Map()
	{
	}
};

#pragma endregion FCsMap_ObjectByName