// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Data/Sound/Fire/CsParams_PointWeapon_SoundFire.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsParams_PointWeapon_SoundFire)

// FCsPointWeapon_SoundFire_Params
#pragma region

#define ParamsType NCsWeapon::NPoint::NFire::NSound::FParams

void FCsPointWeapon_SoundFire_Params::CopyToParams(ParamsType* Params)
{
	Params->SetSound(&Sound);

	typedef NCsWeapon::NPoint::NFire::NSound::EAttach AttachType;

	Params->SetAttach((AttachType*)(&Attach));
}

void FCsPointWeapon_SoundFire_Params::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetSound(Sound);

	typedef NCsWeapon::NPoint::NFire::NSound::EAttach AttachType;

	Params->SetAttach((AttachType)(Attach));
}

#undef ParamsType

bool FCsPointWeapon_SoundFire_Params::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Sound);
	return true;
}

bool FCsPointWeapon_SoundFire_Params::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_VALID(Sound)
	return true;
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NFire
		{
			namespace NSound
			{
				bool FParams::IsValidChecked(const FString& Context) const
				{
					CS_IS_VALID_CHECKED(GetSound());
					return true;
				}

				bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
				{
					CS_IS_VALID(GetSound())
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsPointWeapon_SoundFire_Params