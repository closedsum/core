// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsTypes_Library_FX.h"
#include "CsCore.h"

namespace NCsFX
{
	namespace NSpawn
	{
		namespace NParams
		{
			bool FParams::IsValidChecked(const FString& Context) const
			{
				// Check FX is Valid.
				check(FX.IsValidChecked(Context));
				// Check Frequency Params are Valid.
				check(FrequencyParams.IsValidChecked(Context));
				// Check Group is Valid.
				check(EMCsUpdateGroup::Get().IsValidEnumChecked(Context, Group));
				return true;
			}

			bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				// Check FX is Valid.
				if (!FX.IsValid(Context, Log))
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

			AActor* FParams::GetActor() const { return Actor.IsValid() ? Actor.Get() : nullptr; }

			void FParams::Update()
			{
				FX.UpdateInternalPtrs();
				FrequencyParams.Update();
			}

			void FParams::Reset()
			{
				FX.Reset();
				FrequencyParams.Reset();
				Actor = nullptr;
				Group = EMCsUpdateGroup::Get().GetMAX();
			}
		}
	}
}

#define ParamsType NCsFX::NSpawn::NParams::FParams
void FCsFX_Spawn_Params::CopyToParamsAsValue(ParamsType* Params) const
{
#undef ParamsType

	Params->FX = FX;
	Params->FX.UpdateInternalPtrs();
	Params->Actor = Actor;
	FrequencyParams.CopyToParamsAsValue(Params->GetFrequencyParamsPtr());
	Params->Group = Group;
}

bool FCsFX_Spawn_Params::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check FX is Valid
	if (!FX.IsValid(Context, Log))
		return false;
	// Check FrequencyParams is Valid
	if (!FrequencyParams.IsValid(Context))
		return false;
	// Check Group is Valid
	if (!EMCsUpdateGroup::Get().IsValidEnum(Group))
		return false;
	return true;
}

void FCsFX_Spawn_Params::Update()
{
	FrequencyParams.Update();
}