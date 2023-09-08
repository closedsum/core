// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsTypes_Manager_Level.generated.h"

USTRUCT(BlueprintType)
struct FCsManagerLevelChangeMapParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Managers|Level")
	FString Map;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Managers|Level")
	FString TransitionMap;

	FCsManagerLevelChangeMapParams()
	{
	}
};