// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsTypes_FX_Impact.h"

// Library
#include "Library/CsLibrary_Valid.h"

// FCsFXImpact
#pragma region

bool FCsFXImpact::IsValidChecked(const FString& Context) const
{
	checkf(Surface != EPhysicalSurface::SurfaceType_Max, TEXT("%s: Surface == EPhysicalSurface::SurfaceType_Max is NOT Valid."), *Context);
	CS_IS_VALID_CHECKED(FX);
	return true;
}

bool FCsFXImpact::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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