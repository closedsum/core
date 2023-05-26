// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsTypes_Library_Sound.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"

namespace NCsSound
{
	namespace NSpawn
	{
		namespace NParams
		{
			bool FParams::IsValidChecked(const FString& Context) const
			{
				// Check Sound is Valid.
				CS_IS_VALID_CHECKED(Sound);
				CS_IS_FLOAT_GREATER_THAN_CHECKED(VolumeMultiplier, 0.0f)
				CS_IS_FLOAT_GREATER_THAN_CHECKED(PitchMultiplier, 0.0f)
				// Check Frequency Params are Valid.
				CS_IS_VALID_CHECKED(FrequencyParams);
				// Check Group is Valid.
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, Group)
				return true;
			}

			bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				// Check Sound is Valid.
				CS_IS_VALID(Sound)
				CS_IS_FLOAT_GREATER_THAN(VolumeMultiplier, 0.0f)
				CS_IS_FLOAT_GREATER_THAN(PitchMultiplier, 0.0f)
				// Check Frequency Params are Valid.
				CS_IS_VALID(FrequencyParams)
				// Check Group is Valid.
				CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, Group)
				return true;
			}

			UObject* FParams::GetObject() const { return Object.IsValid() ? Object.Get() : nullptr; }

			void FParams::Update()
			{
				FrequencyParams.Update();
			}

			void FParams::Reset()
			{
				Sound.Reset();
				FrequencyParams.Reset();
				Object = nullptr;
				Group = EMCsUpdateGroup::Get().GetMAX();
			}
		}
	}
}

#define ParamsType NCsSound::NSpawn::NParams::FParams
void FCsSound_Spawn_Params::CopyToParams(ParamsType* Params) const
{
#undef ParamsType

	Params->Sound = Sound;
	Params->VolumeMultiplier = VolumeMultiplier;
	Params->PitchMultiplier = PitchMultiplier;
	Params->Object = Object;
	FrequencyParams.CopyToParamsAsValue(Params->GetFrequencyParamsPtr());
	Params->Group = Group;
}

bool FCsSound_Spawn_Params::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check Sound is Valid
	CS_IS_VALID(Sound)
	CS_IS_FLOAT_GREATER_THAN(VolumeMultiplier, 0.0f)
	CS_IS_FLOAT_GREATER_THAN(PitchMultiplier, 0.0f)
	// Check FrequencyParams is Valid
	CS_IS_VALID(FrequencyParams)
	// Check Group is Valid
	CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, Group)
	return true;
}

void FCsSound_Spawn_Params::Update()
{
	FrequencyParams.Update();
}