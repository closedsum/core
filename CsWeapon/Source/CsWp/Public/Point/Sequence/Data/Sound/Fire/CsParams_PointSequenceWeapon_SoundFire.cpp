// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Sequence/Data/Sound/Fire/CsParams_PointSequenceWeapon_SoundFire.h"

// Library
#include "Library/CsLibrary_Valid.h"

// FCsPointSequenceWeapon_SoundFire_Params
#pragma region

#define ParamsType NCsWeapon::NPoint::NSequence::NFire::NSound::FParams

void FCsPointSequenceWeapon_SoundFire_Params::CopyToParams(ParamsType* Params)
{
	Params->SetSound(&Sound);

	typedef NCsWeapon::NPoint::NSequence::NFire::NSound::EAttach AttachType;

	Params->SetAttach((AttachType*)(&Attach));
}

void FCsPointSequenceWeapon_SoundFire_Params::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetSound(Sound);

	typedef NCsWeapon::NPoint::NSequence::NFire::NSound::EAttach AttachType;

	Params->SetAttach((AttachType)(Attach));
}

#undef ParamsType

bool FCsPointSequenceWeapon_SoundFire_Params::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Sound);
	return true;
}

bool FCsPointSequenceWeapon_SoundFire_Params::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_VALID(Sound)
	return true;
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
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
}

#pragma endregion FCsPointSequenceWeapon_SoundFire_Params