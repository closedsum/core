// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData_Impl.h"
#include "Types/CsTypes.h"
#include "UI/CsTypes_UI.h"
#include "CsData_UI_Common.generated.h"

/* Current Order of Categories

*/

UCLASS(Abstract)
class CSCORE_API UCsData_UI_Common : public UCsData_Impl
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