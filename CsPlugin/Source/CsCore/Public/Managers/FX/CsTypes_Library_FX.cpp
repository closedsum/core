// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsTypes_Library_FX.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"

namespace NCsFX
{
	namespace NSpawn
	{
		namespace NParams
		{
			bool FParams::IsValidChecked(const FString& Context) const
			{
				// Check FX is Valid.
				CS_IS_VALID_CHECKED(FX);
				// Check Frequency Params are Valid.
				CS_IS_VALID_CHECKED(FrequencyParams);
				// Check Group is Valid.
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, Group)
				return true;
			}

			bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				// Check FX is Valid.
				CS_IS_VALID(FX)
				// Check Frequency Params are Valid.
				CS_IS_VALID(FrequencyParams)
				// Check Group is Valid.
				CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, Group)
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
	// Check FX is Valid.
	CS_IS_VALID(FX)
	// Check Frequency Params are Valid.
	CS_IS_VALID(FrequencyParams)
	// Check Group is Valid.
	CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, Group)
	return true;
}

void FCsFX_Spawn_Params::Update()
{
	FrequencyParams.Update();
}