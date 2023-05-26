// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Params/Shot/Point/CsParams_PointWeapon_Shot_Point.h"

// Library
#include "Library/CsLibrary_Valid.h"

// FCsPointWeapon_Shot_PointParams
#pragma region

#define ParamsType NCsWeapon::NPoint::NShot::NPoint::FParams

void FCsPointWeapon_Shot_PointParams::CopyToParams(ParamsType* Params)
{
	Params->SetCount(&Count);
	Params->SetInterval(&Interval);
}

void FCsPointWeapon_Shot_PointParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetCount(Count);
	Params->SetInterval(Interval);
}

#undef ParamsType

bool FCsPointWeapon_Shot_PointParams::IsValidChecked(const FString& Context) const
{
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Count, 1)
	CS_IS_FLOAT_GREATER_THAN_CHECKED(Interval, 0.0f)
	return true;
}

bool FCsPointWeapon_Shot_PointParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_INT_GREATER_THAN_OR_EQUAL(Count, 1)
	CS_IS_FLOAT_GREATER_THAN(Interval, 0.0f)
	return true;
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NShot
		{
			namespace NPoint
			{
				bool FParams::IsValidChecked(const FString& Context) const
				{
					CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(GetCount(), 1)
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetInterval(), 0.0f)
					return true;
				}

				bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
				{
					CS_IS_INT_GREATER_THAN_OR_EQUAL(GetCount(), 1)
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetInterval(), 0.0f)
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsPointWeapon_Shot_PointParams