// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Delay, 0.0f)
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
				CS_IS_FLOAT_GREATER_THAN_CHECKED(Delay, 0.0f)
				// Check Frequency Params are Valid.
				CS_IS_VALID(FrequencyParams)
				// Check Group is Valid.
				CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, Group)
				return true;
			}

			AActor* FParams::GetActor() const { return Actor.IsValid() ? Actor.Get() : nullptr; }

			void FParams::Update()
			{
				FrequencyParams.Update();
			}

			void FParams::Reset()
			{
				FX.Reset();
				Actor = nullptr;
				Delay = 0.0f;
				FrequencyParams.Reset();		
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
	Params->Delay = Delay;
	Params->Actor = Actor;
	FrequencyParams.CopyToParamsAsValue(Params->GetFrequencyParamsPtr());
	Params->Group = Group;
}

bool FCsFX_Spawn_Params::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check FX is Valid.
	CS_IS_VALID(FX)
	CS_IS_FLOAT_GREATER_THAN_CHECKED(Delay, 0.0f)
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

namespace NCsFX
{
	namespace NLibrary
	{
		namespace NSetArrayFloatChecked
		{
			bool FPayload::IsValidChecked(const FString& Context) const
			{
				CS_IS_INT_GREATER_THAN_CHECKED(Count, 0)
				CS_IS_TARRAY_EMPTY_CHECKED(Indices, int32)
				CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Indices.Num(), Count)
				CS_IS_INT_GREATER_THAN_CHECKED(Stride, 0)
				CS_IS_TARRAY_EMPTY_CHECKED(Values, float)

				const int32 MinValuesSize = Stride * Count;

				CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Values.Num(), MinValuesSize)
				return true;
			}
		}
	}
}