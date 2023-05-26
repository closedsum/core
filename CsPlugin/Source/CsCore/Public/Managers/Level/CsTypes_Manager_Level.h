// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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