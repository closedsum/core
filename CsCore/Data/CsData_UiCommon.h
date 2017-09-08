// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "CsData_UiCommon.generated.h"

/* Current Order of Categories

*/

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_UiCommon : public ACsData
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Common")
	FCsBlueprint FullscreenWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Common")
	FCsBlueprint LoadingWidget;
};