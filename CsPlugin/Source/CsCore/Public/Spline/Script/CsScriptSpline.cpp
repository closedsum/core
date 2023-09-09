// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Spline/Script/CsScriptSpline.h"
#include "CsCore.h"

UCsScriptSpline::UCsScriptSpline(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// ICsScriptSpline
#pragma region

	// ICsSpline
#pragma region

USplineComponent* ICsScriptSpline::GetSplineComponent()
{
	return ICsScriptSpline::Execute_Script_GetSplineComponent(_getUObject());
}

#pragma endregion ICsSpline

#pragma endregion ICsScriptSpline