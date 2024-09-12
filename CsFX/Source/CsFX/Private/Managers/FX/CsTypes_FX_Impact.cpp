// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/FX/CsTypes_FX_Impact.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_FX_Impact)

// FCsFXImpact
#pragma region

bool FCsFXImpact::IsValidChecked(const FString& Context) const
{
	checkf(Surface != EPhysicalSurface::SurfaceType_Max, TEXT("%s: Surface == EPhysicalSurface::SurfaceType_Max is NOT Valid."), *Context);
	CS_IS_VALID_CHECKED(FX);
	return true;
}

bool FCsFXImpact::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/) const
{
	if (Surface == EPhysicalSurface::SurfaceType_Max)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Surface == EPhysicalSurface::SurfaceType_Max is NOT Valid."), *Context));
		return false;
	}
	CS_IS_VALID(FX)
	return true;
}

#pragma endregion FCsFXImpact