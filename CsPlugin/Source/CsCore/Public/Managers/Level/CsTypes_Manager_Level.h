// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "CsTypes_Manager_Level.generated.h"

USTRUCT(BlueprintType)
struct FCsManagerLevelChangeMapParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Map;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TransitionMap;

	FCsManagerLevelChangeMapParams()
	{
	}
};