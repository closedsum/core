// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Fade/CsTypes_Fade.h"

// Library
#include "Library/CsLibrary_Valid.h"

// FCsFade_ClearToBlackParams
#pragma region

#define ParamsType NCsFade::NClearToBlack::FParams

void FCsFade_ClearToBlackParams::CopyToParams(ParamsType* Params)
{
	CS_COPY_TO_PROXY(Params, InterpolationMethod);
	CS_COPY_TO_PROXY(Params, Easing);
	Params->SetCurve(Curve.GetPtr());
	CS_COPY_TO_PROXY(Params, Time);
}

void FCsFade_ClearToBlackParams::CopyToParamsAsValue(ParamsType* Params) const
{
	CS_COPY_TO_PROXY_AS_VALUE(Params, InterpolationMethod);
	CS_COPY_TO_PROXY_AS_VALUE(Params, Easing);
	Params->SetCurve(Curve.Get());
	CS_COPY_TO_PROXY_AS_VALUE(Params, Time);
}

#undef ParamsType

bool FCsFade_ClearToBlackParams::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsInterpolatingMethod, InterpolationMethod)

	// Easing
	if (InterpolationMethod == ECsInterpolatingMethod::Easing)
	{
		CS_IS_ENUM_VALID_CHECKED(EMCsEasingType, Easing)
	}
	// Curve
	else
	if (InterpolationMethod == ECsInterpolatingMethod::Curve)
	{
		CS_IS_VALID_CHECKED(Curve);
	}
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Time, 0.0f)
	return true;
}

bool FCsFade_ClearToBlackParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsInterpolatingMethod, ECsInterpolatingMethod, InterpolationMethod)

	// Easing
	if (InterpolationMethod == ECsInterpolatingMethod::Easing)
	{
		CS_IS_ENUM_VALID(EMCsEasingType, ECsEasingType, Easing)
	}
	// Curve
	else
	if (InterpolationMethod == ECsInterpolatingMethod::Curve)
	{
		CS_IS_VALID(Curve)
	}
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Time, 0.0f)
	return true;
}

bool FCsFade_ClearToBlackParams::IsTopValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsInterpolatingMethod, InterpolationMethod)

	// Easing
	if (InterpolationMethod == ECsInterpolatingMethod::Easing)
	{
		CS_IS_ENUM_VALID_CHECKED(EMCsEasingType, Easing)
	}
	// Curve
	else
	if (InterpolationMethod == ECsInterpolatingMethod::Curve)
	{
		CS_IS_TOP_VALID_CHECKED(Curve);
	}
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Time, 0.0f)
	return true;
}

bool FCsFade_ClearToBlackParams::IsTopValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsInterpolatingMethod, ECsInterpolatingMethod, InterpolationMethod)

	// Easing
	if (InterpolationMethod == ECsInterpolatingMethod::Easing)
	{
		CS_IS_ENUM_VALID(EMCsEasingType, ECsEasingType, Easing)
	}
	// Curve
	else
	if (InterpolationMethod == ECsInterpolatingMethod::Curve)
	{
		CS_IS_TOP_VALID(Curve)
	}
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Time, 0.0f)
	return true;
}

namespace NCsFade
{
	namespace NClearToBlack
	{
		bool FParams::IsValidChecked(const FString& Context) const
		{
			CS_IS_ENUM_VALID_CHECKED(EMCsInterpolatingMethod, GetInterpolationMethod())

			// Easing
			if (GetInterpolationMethod() == ECsInterpolatingMethod::Easing)
			{
				CS_IS_ENUM_VALID_CHECKED(EMCsEasingType, GetEasing())
			}
			// Curve
			else
			if (GetInterpolationMethod() == ECsInterpolatingMethod::Curve)
			{
				CS_IS_PENDING_KILL_CHECKED(GetCurve())
			}
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetTime(), 0.0f)
			return true;
		}

		bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
		{
			CS_IS_ENUM_VALID(EMCsInterpolatingMethod, ECsInterpolatingMethod, GetInterpolationMethod())

			// Easing
			if (GetInterpolationMethod() == ECsInterpolatingMethod::Easing)
			{
				CS_IS_ENUM_VALID(EMCsEasingType, ECsEasingType, GetEasing())
			}
			// Curve
			else
			if (GetInterpolationMethod() == ECsInterpolatingMethod::Curve)
			{
				CS_IS_PENDING_KILL(GetCurve())
			}
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetTime(), 0.0f)
			return true;
		}

		bool FParams::IsTopValidChecked(const FString& Context) const
		{
			CS_IS_ENUM_VALID_CHECKED(EMCsInterpolatingMethod, GetInterpolationMethod())

			// Easing
			if (GetInterpolationMethod() == ECsInterpolatingMethod::Easing)
			{
				CS_IS_ENUM_VALID_CHECKED(EMCsEasingType, GetEasing())
			}
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetTime(), 0.0f)
			return true;
		}

		bool FParams::IsTopValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
		{
			CS_IS_ENUM_VALID(EMCsInterpolatingMethod, ECsInterpolatingMethod, GetInterpolationMethod())

			// Easing
			if (GetInterpolationMethod() == ECsInterpolatingMethod::Easing)
			{
				CS_IS_ENUM_VALID(EMCsEasingType, ECsEasingType, GetEasing())
			}
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetTime(), 0.0f)
			return true;
		}
	}
}

#pragma endregion FCsFade_ClearToBlackParams

// FCsFade_BlackToClearParams
#pragma region

#define ParamsType NCsFade::NBlackToClear::FParams

void FCsFade_BlackToClearParams::CopyToParams(ParamsType* Params)
{
	CS_COPY_TO_PROXY(Params, InterpolationMethod);
	CS_COPY_TO_PROXY(Params, Easing);
	Params->SetCurve(Curve.GetPtr());
	CS_COPY_TO_PROXY(Params, Time);
}

void FCsFade_BlackToClearParams::CopyToParamsAsValue(ParamsType* Params) const
{
	CS_COPY_TO_PROXY_AS_VALUE(Params, InterpolationMethod);
	CS_COPY_TO_PROXY_AS_VALUE(Params, Easing);
	Params->SetCurve(Curve.Get());
	CS_COPY_TO_PROXY_AS_VALUE(Params, Time);
}

#undef ParamsType

bool FCsFade_BlackToClearParams::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsInterpolatingMethod, InterpolationMethod)

	// Easing
	if (InterpolationMethod == ECsInterpolatingMethod::Easing)
	{
		CS_IS_ENUM_VALID_CHECKED(EMCsEasingType, Easing)
	}
	// Curve
	else
	if (InterpolationMethod == ECsInterpolatingMethod::Curve)
	{
		CS_IS_VALID_CHECKED(Curve);
	}
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Time, 0.0f)
	return true;
}

bool FCsFade_BlackToClearParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsInterpolatingMethod, ECsInterpolatingMethod, InterpolationMethod)

	// Easing
	if (InterpolationMethod == ECsInterpolatingMethod::Easing)
	{
		CS_IS_ENUM_VALID(EMCsEasingType, ECsEasingType, Easing)
	}
	// Curve
	else
	if (InterpolationMethod == ECsInterpolatingMethod::Curve)
	{
		CS_IS_VALID(Curve)
	}
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Time, 0.0f)
	return true;
}

bool FCsFade_BlackToClearParams::IsTopValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsInterpolatingMethod, InterpolationMethod)

	// Easing
	if (InterpolationMethod == ECsInterpolatingMethod::Easing)
	{
		CS_IS_ENUM_VALID_CHECKED(EMCsEasingType, Easing)
	}
	// Curve
	else
	if (InterpolationMethod == ECsInterpolatingMethod::Curve)
	{
		CS_IS_TOP_VALID_CHECKED(Curve);
	}
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Time, 0.0f)
	return true;
}

bool FCsFade_BlackToClearParams::IsTopValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsInterpolatingMethod, ECsInterpolatingMethod, InterpolationMethod)

	// Easing
	if (InterpolationMethod == ECsInterpolatingMethod::Easing)
	{
		CS_IS_ENUM_VALID(EMCsEasingType, ECsEasingType, Easing)
	}
	// Curve
	else
	if (InterpolationMethod == ECsInterpolatingMethod::Curve)
	{
		CS_IS_TOP_VALID(Curve)
	}
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Time, 0.0f)
	return true;
}

namespace NCsFade
{
	namespace NBlackToClear
	{
		bool FParams::IsValidChecked(const FString& Context) const
		{
			CS_IS_ENUM_VALID_CHECKED(EMCsInterpolatingMethod, GetInterpolationMethod())

			// Easing
			if (GetInterpolationMethod() == ECsInterpolatingMethod::Easing)
			{
				CS_IS_ENUM_VALID_CHECKED(EMCsEasingType, GetEasing())
			}
			// Curve
			else
			if (GetInterpolationMethod() == ECsInterpolatingMethod::Curve)
			{
				CS_IS_PENDING_KILL_CHECKED(GetCurve())
			}
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetTime(), 0.0f)
			return true;
		}

		bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
		{
			CS_IS_ENUM_VALID(EMCsInterpolatingMethod, ECsInterpolatingMethod, GetInterpolationMethod())

			// Easing
			if (GetInterpolationMethod() == ECsInterpolatingMethod::Easing)
			{
				CS_IS_ENUM_VALID(EMCsEasingType, ECsEasingType, GetEasing())
			}
			// Curve
			else
			if (GetInterpolationMethod() == ECsInterpolatingMethod::Curve)
			{
				CS_IS_PENDING_KILL(GetCurve())
			}
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetTime(), 0.0f)
			return true;
		}

		bool FParams::IsTopValidChecked(const FString& Context) const
		{
			CS_IS_ENUM_VALID_CHECKED(EMCsInterpolatingMethod, GetInterpolationMethod())

			// Easing
			if (GetInterpolationMethod() == ECsInterpolatingMethod::Easing)
			{
				CS_IS_ENUM_VALID_CHECKED(EMCsEasingType, GetEasing())
			}
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetTime(), 0.0f)
			return true;
		}

		bool FParams::IsTopValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
		{
			CS_IS_ENUM_VALID(EMCsInterpolatingMethod, ECsInterpolatingMethod, GetInterpolationMethod())

			// Easing
			if (GetInterpolationMethod() == ECsInterpolatingMethod::Easing)
			{
				CS_IS_ENUM_VALID(EMCsEasingType, ECsEasingType, GetEasing())
			}
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetTime(), 0.0f)
			return true;
		}
	}
}

#pragma endregion FCsFade_BlackToClearParams

// FCsFadeParams
#pragma region

#define ParamsType NCsFade::FParams

void FCsFadeParams::CopyToParams(ParamsType* Params)
{
	CS_COPY_TO_PROXY(Params, From);
	CS_COPY_TO_PROXY(Params, To);
	CS_COPY_TO_PROXY(Params, InterpolationMethod);
	CS_COPY_TO_PROXY(Params, Easing);
	Params->SetCurve(Curve.GetPtr());
	CS_COPY_TO_PROXY(Params, Time);
}

void FCsFadeParams::CopyToParamsAsValue(ParamsType* Params) const
{
	CS_COPY_TO_PROXY_AS_VALUE(Params, From);
	CS_COPY_TO_PROXY_AS_VALUE(Params, To);
	CS_COPY_TO_PROXY_AS_VALUE(Params, InterpolationMethod);
	CS_COPY_TO_PROXY_AS_VALUE(Params, Easing);
	Params->SetCurve(Curve.Get());
	CS_COPY_TO_PROXY_AS_VALUE(Params, Time);
}

#undef ParamsType

bool FCsFadeParams::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsInterpolatingMethod, InterpolationMethod)

	// Easing
	if (InterpolationMethod == ECsInterpolatingMethod::Easing)
	{
		CS_IS_ENUM_VALID_CHECKED(EMCsEasingType, Easing)
	}
	// Curve
	else
	if (InterpolationMethod == ECsInterpolatingMethod::Curve)
	{
		CS_IS_VALID_CHECKED(Curve);
	}
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Time, 0.0f)
	return true;
}

bool FCsFadeParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsInterpolatingMethod, ECsInterpolatingMethod, InterpolationMethod)

	// Easing
	if (InterpolationMethod == ECsInterpolatingMethod::Easing)
	{
		CS_IS_ENUM_VALID(EMCsEasingType, ECsEasingType, Easing)
	}
	// Curve
	else
	if (InterpolationMethod == ECsInterpolatingMethod::Curve)
	{
		CS_IS_VALID(Curve)
	}
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Time, 0.0f)
	return true;
}

bool FCsFadeParams::IsTopValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsInterpolatingMethod, InterpolationMethod)

	// Easing
	if (InterpolationMethod == ECsInterpolatingMethod::Easing)
	{
		CS_IS_ENUM_VALID_CHECKED(EMCsEasingType, Easing)
	}
	// Curve
	else
	if (InterpolationMethod == ECsInterpolatingMethod::Curve)
	{
		CS_IS_TOP_VALID_CHECKED(Curve);
	}
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Time, 0.0f)
	return true;
}

bool FCsFadeParams::IsTopValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsInterpolatingMethod, ECsInterpolatingMethod, InterpolationMethod)

	// Easing
	if (InterpolationMethod == ECsInterpolatingMethod::Easing)
	{
		CS_IS_ENUM_VALID(EMCsEasingType, ECsEasingType, Easing)
	}
	// Curve
	else
	if (InterpolationMethod == ECsInterpolatingMethod::Curve)
	{
		CS_IS_TOP_VALID(Curve)
	}
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Time, 0.0f)
	return true;
}

namespace NCsFade
{
	bool FParams::IsValidChecked(const FString& Context) const
	{
		CS_IS_ENUM_VALID_CHECKED(EMCsInterpolatingMethod, GetInterpolationMethod())

		// Easing
		if (GetInterpolationMethod() == ECsInterpolatingMethod::Easing)
		{
			CS_IS_ENUM_VALID_CHECKED(EMCsEasingType, GetEasing())
		}
		// Curve
		else
		if (GetInterpolationMethod() == ECsInterpolatingMethod::Curve)
		{
			CS_IS_PENDING_KILL_CHECKED(GetCurve())
		}
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Time, 0.0f)
		return true;
	}

	bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
	{
		CS_IS_ENUM_VALID(EMCsInterpolatingMethod, ECsInterpolatingMethod, GetInterpolationMethod())

		// Easing
		if (GetInterpolationMethod() == ECsInterpolatingMethod::Easing)
		{
			CS_IS_ENUM_VALID(EMCsEasingType, ECsEasingType, GetEasing())
		}
		// Curve
		else
		if (GetInterpolationMethod() == ECsInterpolatingMethod::Curve)
		{
			CS_IS_PENDING_KILL(GetCurve())
		}
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Time, 0.0f)
		return true;
	}

	bool FParams::IsTopValidChecked(const FString& Context) const
	{
		CS_IS_ENUM_VALID_CHECKED(EMCsInterpolatingMethod, GetInterpolationMethod())

		// Easing
		if (GetInterpolationMethod() == ECsInterpolatingMethod::Easing)
		{
			CS_IS_ENUM_VALID_CHECKED(EMCsEasingType, GetEasing())
		}
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetTime(), 0.0f)
		return true;
	}

	bool FParams::IsTopValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
	{
		CS_IS_ENUM_VALID(EMCsInterpolatingMethod, ECsInterpolatingMethod, GetInterpolationMethod())

		// Easing
		if (GetInterpolationMethod() == ECsInterpolatingMethod::Easing)
		{
			CS_IS_ENUM_VALID(EMCsEasingType, ECsEasingType, GetEasing())
		}
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetTime(), 0.0f)
		return true;
	}
}

#pragma endregion FCsFadeParams