// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Sequence/Params/CsParams_PointSequenceWeapon_Sequence.h"

// Library
#include "Library/CsLibrary_Valid.h"

// PointSequenceWeaponSearchDimension
#pragma region

namespace NCsPointSequenceWeaponSearchDimension
{
	namespace Ref
	{
		typedef EMCsPointSequenceWeaponSearchDimension EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(XY, "2D: X,Y");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(XYZ, "3D: X,Y,Z");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPointSequenceWeaponSearchDimension_MAX, "MAX");
	}
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NSearch
			{
				namespace NDimension
				{
					namespace Ref
					{
						typedef EMDimension EnumMapType;

						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(XY, "2D: X,Y");
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(XYZ, "3D: X,Y,Z");
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDimension_MAX, "MAX");
					}
				}
			}
		}
	}
}

#pragma endregion PointSequenceWeaponSearchDimension

// FCsPointSequenceWeapon_Sequence_SearchParams
#pragma region

#define ParamsType NCsWeapon::NPoint::NSequence::NSequence::NSearch::FParams

void FCsPointSequenceWeapon_Sequence_SearchParams::CopyToParams(ParamsType* Params)
{
	typedef NCsWeapon::NPoint::NSequence::NSearch::EDimension DimensionType;

	Params->SetDimension((DimensionType*)(&Dimension));
	Params->SetMinDistance(&MinDistance);
	Params->SetMaxDistance(&MaxDistance);
	Params->SetbMinDot(&bMinDot);
	Params->SetMinDot(&MinDot);
	Params->SetMinAngle(&MinAngle);
}

void FCsPointSequenceWeapon_Sequence_SearchParams::CopyToParamsAsValue(ParamsType* Params) const
{
	typedef NCsWeapon::NPoint::NSequence::NSearch::EDimension DimensionType;

	Params->SetDimension((DimensionType)Dimension);
	Params->SetMinDistance(MinDistance);
	Params->SetMaxDistance(MaxDistance);
	Params->SetbMinDot(bMinDot);
	Params->SetMinDot(MinDot);
	Params->SetMinAngle(MinAngle);
}

#undef ParamsType

bool FCsPointSequenceWeapon_Sequence_SearchParams::IsValidChecked(const FString& Context) const
{
	typedef EMCsPointSequenceWeaponSearchDimension DimensionMapType;

	CS_IS_ENUM_VALID_CHECKED(DimensionMapType, Dimension)
	CS_IS_FLOAT_GREATER_THAN_CHECKED(MinDistance, 0.0f)
	CS_IS_FLOAT_GREATER_THAN_CHECKED(MaxDistance, MinDistance)

	if (bMinDot)
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(MinDot, -1.0f)
		CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(MinDot, 1.0f)
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(MinAngle, -90.0f)
		CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(MinAngle, 90.0f)
	}
	return true;
}

bool FCsPointSequenceWeapon_Sequence_SearchParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	typedef EMCsPointSequenceWeaponSearchDimension DimensionMapType;
	typedef ECsPointSequenceWeaponSearchDimension DimensionType;

	CS_IS_ENUM_VALID(DimensionMapType, DimensionType, Dimension)
	CS_IS_FLOAT_GREATER_THAN(MinDistance, 0.0f)
	CS_IS_FLOAT_GREATER_THAN(MaxDistance, MinDistance)

	if (bMinDot)
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(MinDot, -1.0f)
		CS_IS_FLOAT_LESS_THAN_OR_EQUAL(MinDot, 1.0f)
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(MinAngle, -90.0f)
		CS_IS_FLOAT_LESS_THAN_OR_EQUAL(MinAngle, 90.0f)
	}
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
						typedef NCsWeapon::NPoint::NSequence::NSearch::EMDimension DimensionMapType;

						CS_IS_ENUM_VALID_CHECKED(DimensionMapType, GetDimension())
						CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetMinDistance(), 0.0f)
						CS_IS_FLOAT_GREATER_THAN_CHECKED(GetMaxDistance(), GetMinDistance())

						if (GetbMinDot())
						{
							CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetMinDot(), -1.0f)
							CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(GetMinDot(), 1.0f)
							CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetMinAngle(), -90.0f)
							CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(GetMinAngle(), 90.0f)
						}
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						typedef NCsWeapon::NPoint::NSequence::NSearch::EMDimension DimensionMapType;
						typedef NCsWeapon::NPoint::NSequence::NSearch::EDimension DimensionType;

						CS_IS_ENUM_VALID(DimensionMapType, DimensionType, GetDimension())
						CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetMinDistance(), 0.0f)
						CS_IS_FLOAT_GREATER_THAN(GetMaxDistance(), GetMinDistance())

						if (GetbMinDot())
						{
							CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetMinDot(), -1.0f)
							CS_IS_FLOAT_LESS_THAN_OR_EQUAL(GetMinDot(), 1.0f)
							CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetMinAngle(), -90.0f)
							CS_IS_FLOAT_LESS_THAN_OR_EQUAL(GetMinAngle(), 90.0f)
						}
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