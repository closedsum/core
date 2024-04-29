// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_Interpolation_Easing.h"

// Library
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"

namespace NCsEasing
{
	bool FFloat::IsValidChecked(const FString& Context) const
	{
		CS_IS_ENUM_VALID_CHECKED(EMCsEasingType, GetType());
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetMax(), GetMin())
		return true;
	}

	bool FFloat::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
	{
		CS_IS_ENUM_VALID(EMCsEasingType, ECsEasingType, GetType())
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetMax(), GetMin())
		return true;
	}

	float FFloat::Ease(const float& Alpha) const
	{
		typedef NCsMath::FLibrary MathLibrary;

		return MathLibrary::Ease(GetType(), Alpha, GetMin(), GetMax(), 1.0f);
	}
}