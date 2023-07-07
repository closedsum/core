// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Sequence/Params/Start/CsParams_PointSequenceWeapon_Start.h"

// Library
#include "Library/CsLibrary_Valid.h"

// FCsPointSequenceWeapon_StartParams
#pragma region

#define ParamsType NCsWeapon::NPoint::NSequence::NStart::FParams

void FCsPointSequenceWeapon_StartParams::CopyToParams(ParamsType* Params)
{
	typedef NCsWeapon::NPoint::NSequence::EStart StartType;

	Params->SetType((StartType*)(&Type));
	Params->SetOffset(&Offset);
}

void FCsPointSequenceWeapon_StartParams::CopyToParamsAsValue(ParamsType* Params) const
{
	typedef NCsWeapon::NPoint::NSequence::EStart StartType;

	Params->SetType((StartType)Type);
	Params->SetOffset(Offset);
}

#undef ParamsType

bool FCsPointSequenceWeapon_StartParams::IsValidChecked(const FString& Context) const
{
	typedef EMCsPointSequenceWeaponStart StartMapType;

	CS_IS_ENUM_VALID_CHECKED(StartMapType, Type)
	return true;
}

bool FCsPointSequenceWeapon_StartParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	typedef EMCsPointSequenceWeaponStart StartMapType;
	typedef ECsPointSequenceWeaponStart StartType;

	CS_IS_ENUM_VALID(StartMapType, StartType, Type)
	return true;
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NStart
			{
				bool FParams::IsValidChecked(const FString& Context) const
				{
					typedef NCsWeapon::NPoint::NSequence::EMStart StartMapType;

					CS_IS_ENUM_VALID_CHECKED(StartMapType, Type)
					return true;
				}

				bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
				{
					typedef NCsWeapon::NPoint::NSequence::EMStart StartMapType;
					typedef NCsWeapon::NPoint::NSequence::EStart StartType;

					CS_IS_ENUM_VALID(StartMapType, StartType, Type)
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsPointSequenceWeapon_StartParams