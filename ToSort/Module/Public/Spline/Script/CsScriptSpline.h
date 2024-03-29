// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "Spline/CsSpline.h"
#include "CsScriptSpline.generated.h"

UINTERFACE(BlueprintType, MinimalApi)
class UCsScriptSpline : public UCsSpline
{
	GENERATED_UINTERFACE_BODY()
};


class CSCORE_API ICsScriptSpline : public ICsSpline
{
	GENERATED_IINTERFACE_BODY()

// ICsSpline
#pragma region
public:

	USplineComponent* GetSplineComponent();

#pragma endregion ICsSpline

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptSpline", meta = (DisplayName = "GetSplineComponent"))
	USplineComponent* Script_GetSplineComponent();
};