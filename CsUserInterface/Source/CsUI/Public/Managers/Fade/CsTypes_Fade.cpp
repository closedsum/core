// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Fade/CsTypes_Fade.h"

// Library
#include "Library/CsLibrary_Valid.h"

bool FCsFadeParams::IsValidChecked(const FString& Context) const
{
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Time, 0.0f)
	return true;
}

bool FCsFadeParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Time, 0.0f)
	return true;
}

namespace NCsFade
{
	bool FParams::IsValidChecked(const FString& Context) const
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Time, 0.0f)
		return true;
	}

	bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Time, 0.0f)
		return true;
	}
}