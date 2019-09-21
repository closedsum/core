// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes.h"
#include "UI/CsTypes_UI.h"
#include "CsData_UI_Common.generated.h"

/* Current Order of Categories

*/

UCLASS(Abstract, hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_UI_Common : public ACsData
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Common")
	FCsBlueprint FullscreenWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Common")
	FCsBlueprint LoadingWidget;

// Widgets
#pragma region

	virtual class UBlueprintGeneratedClass* GetWidget(const FECsWidgetType& WidgetType);

#pragma endregion Widgets
};