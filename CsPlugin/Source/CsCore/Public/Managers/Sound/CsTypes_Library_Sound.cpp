// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsTypes_Library_Sound.h"
#include "CsCore.h"

namespace NCsSound
{
	namespace NSpawn
	{
		namespace NParams
		{
			bool FParams::IsValidChecked(const FString& Context) const
			{
				// Check Sound is Valid.
				check(Sound.IsValidChecked(Context));
				// Check Frequency Params are Valid.
				check(FrequencyParams.IsValidChecked(Context));
				// Check Group is Valid.
				check(EMCsUpdateGroup::Get().IsValidEnumChecked(Context, Group));
				return true;
			}

			bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				// Check Sound is Valid.
				if (!Sound.IsValid(Context, Log))
					return false;
				// Check Frequency Params are Valid.
				if (!FrequencyParams.IsValid(Context))
					return false;
				// Check Group is Valid.
				if (!EMCsUpdateGroup::Get().IsValidEnum(Group))
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Group: %s is NOT Valid."), *Context, Group.ToChar()));
					return false;
				}
				return true;
			}

			UObject* FParams::GetObject() const { return Object.IsValid() ? Object.Get() : nullptr; }

			void FParams::Update()
			{
				Sound.UpdateInternalPtrs();
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
	Params->Sound.UpdateInternalPtrs();
	Params->Object = Object;
	Params->FrequencyParams = FrequencyParams;
	Params->Group = Group;
}

bool FCsSound_Spawn_Params::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check Sound is Valid
	if (!Sound.IsValid(Context, Log))
		return false;
	// Check FrequencyParams is Valid
	if (!FrequencyParams.IsValid(Context))
		return false;
	// Check Group is Valid
	if (!EMCsUpdateGroup::Get().IsValidEnum(Group))
		return false;
	return true;
}

void FCsSound_Spawn_Params::Update()
{
	FrequencyParams.Update();
}