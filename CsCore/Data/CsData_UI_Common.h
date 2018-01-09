// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes.h"
#include "CsData_UI_Common.generated.h"

/* Current Order of Categories

*/

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_UI_Common : public ACsData
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Common")
	FCsBlueprint FullscreenWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Common")
	FCsBlueprint LoadingWidget;
};