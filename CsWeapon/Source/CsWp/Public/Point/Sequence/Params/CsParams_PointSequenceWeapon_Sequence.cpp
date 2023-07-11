// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Sequence/Params/CsParams_PointSequenceWeapon_Sequence.h"

// Library
#include "Library/CsLibrary_Valid.h"

// FCsPointSequenceWeapon_Sequence_SearchParams
#pragma region

#define ParamsType NCsWeapon::NPoint::NSequence::NSequence::NSearch::FParams

void FCsPointSequenceWeapon_Sequence_SearchParams::CopyToParams(ParamsType* Params)
{
	Params->SetMinDistance(&MinDistance);
}

void FCsPointSequenceWeapon_Sequence_SearchParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetMinDistance(MinDistance);
}

#undef ParamsType

bool FCsPointSequenceWeapon_Sequence_SearchParams::IsValidChecked(const FString& Context) const
{
	CS_IS_FLOAT_GREATER_THAN_CHECKED(MinDistance, 0.0f)
	return true;
}

bool FCsPointSequenceWeapon_Sequence_SearchParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_FLOAT_GREATER_THAN(MinDistance, 0.0f)
	return true;
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NSequence
			{
				namespace NSearch
				{
					bool FParams::IsValidChecked(const FString& Context) const
					{
						CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetMinDistance(), 0.0f)
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetMinDistance(), 0.0f)
						return true;
					}
				}
			}
		}
	}
}

#pragma endregion FCsPointSequenceWeapon_SequenceParams

// FCsPointSequenceWeapon_SequenceParams
#pragma region

#define ParamsType NCsWeapon::NPoint::NSequence::NSequence::FParams

void FCsPointSequenceWeapon_SequenceParams::CopyToParams(ParamsType* Params)
{
	Params->SetCount(&Count);
	Params->SetInterval(&Interval);
	SearchParams.CopyToParams(Params->GetSearchParamsPtr());
}

void FCsPointSequenceWeapon_SequenceParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetCount(Count);
	Params->SetInterval(Interval);
	SearchParams.CopyToParamsAsValue(Params->GetSearchParamsPtr());
}

#undef ParamsType

bool FCsPointSequenceWeapon_SequenceParams::IsValidChecked(const FString& Context) const
{
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Count, 2)
	CS_IS_FLOAT_GREATER_THAN_CHECKED(Interval, 0.0f)
	CS_IS_VALID_CHECKED(SearchParams);
	return true;
}

bool FCsPointSequenceWeapon_SequenceParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_INT_GREATER_THAN_OR_EQUAL(Count, 2)
	CS_IS_FLOAT_GREATER_THAN(Interval, 0.0f)
	CS_IS_VALID(SearchParams)
	return true;
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NSequence
			{
				bool FParams::IsValidChecked(const FString& Context) const
				{
					CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(GetCount(), 2)
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetInterval(), 0.0f)
					CS_IS_VALID_CHECKED(GetSearchParams());
					return true;
				}

				bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
				{
					CS_IS_INT_GREATER_THAN_OR_EQUAL(GetCount(), 2)
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetInterval(), 0.0f)
					CS_IS_VALID(GetSearchParams())
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsPointSequenceWeapon_SequenceParams