// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Params/Start/CsParams_PointWeapon_Start.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsParams_PointWeapon_Start)

// FCsPointWeapon_StartParams
#pragma region

#define ParamsType NCsWeapon::NPoint::NStart::FParams

void FCsPointWeapon_StartParams::CopyToParams(ParamsType* Params)
{
	typedef NCsWeapon::NPoint::EStart StartType;

	Params->SetType((StartType*)(&Type));
	Params->SetOffset(&Offset);
	Params->SetbSpreadParams(&bSpreadParams);
	SpreadParams.CopyToParams(Params->GetSpreadParamsPtr());
}

void FCsPointWeapon_StartParams::CopyToParamsAsValue(ParamsType* Params) const
{
	typedef NCsWeapon::NPoint::EStart StartType;

	Params->SetType((StartType)Type);
	Params->SetOffset(Offset);
	Params->SetbSpreadParams(bSpreadParams);
	SpreadParams.CopyToParamsAsValue(Params->GetSpreadParamsPtr());
}

#undef ParamsType

bool FCsPointWeapon_StartParams::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsPointWeaponStart, Type)

	if (bSpreadParams)
	{
		CS_IS_VALID_CHECKED(SpreadParams);
	}
	return true;
}

bool FCsPointWeapon_StartParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsPointWeaponStart, ECsPointWeaponStart, Type)

	if (bSpreadParams)
	{
		CS_IS_VALID(SpreadParams)
	}
	return true;
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NStart
		{
			bool FParams::IsValidChecked(const FString& Context) const
			{
				typedef NCsWeapon::NPoint::EMStart StartMapType;

				CS_IS_ENUM_VALID_CHECKED(StartMapType, Type)

				if (GetbSpreadParams())
				{
					CS_IS_VALID_CHECKED(GetSpreadParams());
				}
				return true;
			}

			bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
			{
				typedef NCsWeapon::NPoint::EMStart StartMapType;
				typedef NCsWeapon::NPoint::EStart StartType;

				CS_IS_ENUM_VALID(StartMapType, StartType, Type)

				if (GetbSpreadParams())
				{
					CS_IS_VALID(GetSpreadParams())
				}
				return true;
			}
		}
	}
}

#pragma endregion FCsPointWeapon_StartParams