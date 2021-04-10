// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsTypes_Library_FX.h"
#include "CsCore.h"

namespace NCsFX
{
	namespace NSpawn
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

		bool FParams::IsValid(const FString& Context) const
		{
			// Check FX is Valid.
			if (!FX.IsValid(Context))
				return false;
			// Check Frequency Params are Valid.
			if (!FrequencyParams.IsValid(Context))
				return false;
			// Check Group is Valid.
			if (!EMCsUpdateGroup::Get().IsValidEnum(Group))
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Group: %s is NOT Valid."), *Context, Group.ToChar());
				return false;
			}
			return true;
		}

		AActor* FParams::GetActor() const { return Actor.IsValid() ? Actor.Get() : nullptr; }

		void FParams::Reset()
		{
			FX.Reset();
			FrequencyParams.Reset();
			Actor = nullptr;
			Group = EMCsUpdateGroup::Get().GetMAX();
		}
	}
}