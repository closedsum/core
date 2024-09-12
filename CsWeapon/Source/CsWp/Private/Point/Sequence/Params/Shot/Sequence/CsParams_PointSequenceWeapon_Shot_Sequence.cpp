// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Sequence/Params/Shot/Sequence/CsParams_PointSequenceWeapon_Shot_Sequence.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsParams_PointSequenceWeapon_Shot_Sequence)

// FCsPointSequenceWeapon_Shot_SequenceParams
#pragma region

#define ParamsType NCsWeapon::NPoint::NSequence::NShot::NSequence::FParams

void FCsPointSequenceWeapon_Shot_SequenceParams::CopyToParams(ParamsType* Params)
{
	Params->SetCount(&Count);
	Params->SetInterval(&Interval);
}

void FCsPointSequenceWeapon_Shot_SequenceParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetCount(Count);
	Params->SetInterval(Interval);
}

#undef ParamsType

bool FCsPointSequenceWeapon_Shot_SequenceParams::IsValidChecked(const FString& Context) const
{
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Count, 1)
	CS_IS_FLOAT_GREATER_THAN_CHECKED(Interval, 0.0f)
	return true;
}

bool FCsPointSequenceWeapon_Shot_SequenceParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_INT_GREATER_THAN_OR_EQUAL(Count, 1)
	CS_IS_FLOAT_GREATER_THAN(Interval, 0.0f)
	return true;
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NShot
			{
				namespace NSequence
				{
					bool FParams::IsValidChecked(const FString& Context) const
					{
						CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(GetCount(), 1)
						CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetInterval(), 0.0f)
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						CS_IS_INT_GREATER_THAN_OR_EQUAL(GetCount(), 1)
						CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetInterval(), 0.0f)
						return true;
					}
				}
			}
		}
	}
}

#pragma endregion FCsPointSequenceWeapon_Shot_SequenceParams