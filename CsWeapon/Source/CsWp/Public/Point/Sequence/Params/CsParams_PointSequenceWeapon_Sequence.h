// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/Enum/CsEnumMap.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsParams_PointSequenceWeapon_Sequence.generated.h"

// PointSequenceWeaponSearchDimension
#pragma region

/**
* Describes dimensions (XY, XYZ, ... etc) to search.
*/
UENUM(BlueprintType)
enum class ECsPointSequenceWeaponSearchDimension : uint8
{
	/** 2D: X,Y */
	XY											UMETA(DisplayName = "2D: X,Y"),
	/** 3D: X,Y,Z */
	XYZ											UMETA(DisplayName = "3D: X,Y,Z"),
	ECsPointSequenceWeaponSearchDimension_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsPointSequenceWeaponSearchDimension : public TCsEnumMap<ECsPointSequenceWeaponSearchDimension>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsPointSequenceWeaponSearchDimension, ECsPointSequenceWeaponSearchDimension)
};

namespace NCsPointSequenceWeaponSearchDimension
{
	typedef ECsPointSequenceWeaponSearchDimension Type;

	namespace Ref
	{
		extern CSWP_API const Type XY;
		extern CSWP_API const Type XYZ;
		extern CSWP_API const Type ECsPointSequenceWeaponSearchDimension_MAX;
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
				/**
				* Describes dimensions (XY, XYZ, ... etc) to search.
				*/
				enum class EDimension : uint8 
				{
					/** 2D: X,Y */
					XY,
					/** 3D: X,Y,Z */
					XYZ,
					EDimension_MAX
				};

				struct CSWP_API EMDimension : public TCsEnumMap<EDimension>
				{
					CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMDimension, EDimension)
				};

				namespace NDimension
				{
					typedef EDimension Type;

					namespace Ref
					{
						extern CSWP_API const Type XY;
						extern CSWP_API const Type XYZ;
						extern CSWP_API const Type EDimension_MAX;
					}
				}
			}
		}
	}
}

#pragma endregion PointSequenceWeaponSearchDimension

// FCsPointSequenceWeapon_Sequence_SearchParams
#pragma region

// NCsWeapon::NPoint::NSequence::NSequence::NSearch::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NPoint, NSequence, NSequence, NSearch, FParams)

/**
* Describes any information related to searching for Points for a Sequence Sequence Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsPointSequenceWeapon_Sequence_SearchParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes dimensions (XY, XYZ, ... etc) to search. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (UIMin = "0.0", ClampMin = "0.0"))
	ECsPointSequenceWeaponSearchDimension Dimension;

	/** The Minimum Distance to prioritize searching for Points.
		NOTE: Usually if no valid Points are found in Minimum Distance, the Distance is increased / expanded before
			  searching for Points LESS THAN Minimum Distance. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float MinDistance;

	/** The Maximum Distance to prioritize searching for Points. 
		NOTE: Usually if no valid Points are found and no valid points are found LESS THAN Minimum Distance, then
			  the Distance is increased / expanded GREATER THAN Maximum Distance. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float MaxDistance;

	/** Whether to consider using the Dot Product when determine if a Point is Valid. 
		NOTE: Usually the Dot Product is taken using Direction of the previous Segment (Point to Point). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (ScriptName = "m_bMinDot", InlineEditConditionToggle))
	bool bMinDot;

	/** Represents Cosine of the minimum Angle between the Direction of the previous Segment (Previous Point and Current Point) 
		and next Segment (Current Point and the Point to consider). */
	UPROPERTY(VisibleDefaultsOnly, Category = "CsWp|Weapon|Point", meta = (ScriptName = "m_MinDot", EditCondition = "bMinDot", UIMin = "-1.0", ClampMin = "-1.0", UIMax = "1.0", Clampmax = "1.0"))
	float MinDot;

	/** Minimum Angle in degrees between the Direction of the previous Segment (Previous Point and Current Point)
		and next Segment (Current Point and the Point to consider). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (EditCondition = "bMinDot", UIMin = "-89.0", ClampMin = "-89.0", UIMax = "89.0", Clampmax = "89.0"))
	float MinAngle;

	FCsPointSequenceWeapon_Sequence_SearchParams() :
		Dimension(ECsPointSequenceWeaponSearchDimension::XY),
		MinDistance(1000.0f),
		MaxDistance(4000.0f),
		bMinDot(false),
		MinDot(0.0f),
		MinAngle(0.0f)
	{
	}

#define ParamsType NCsWeapon::NPoint::NSequence::NSequence::NSearch::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

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
					/**
					* Describes any information related to searching for Points for a Sequence Sequence Weapon.
					*  Weapon is an object that implements the interface: ICsWeapon.
					*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
					*/
					struct CSWP_API FParams
					{
					#define DimensionType NCsWeapon::NPoint::NSequence::NSearch::EDimension 

					private:

						/** Describes dimensions (XY, XYZ, ... etc) to search. */
						CS_DECLARE_MEMBER_WITH_PROXY(Dimension, DimensionType)
						/** The Minimum Distance to prioritize searching for Points.
							NOTE: Usually if no valid Points are found in Minimum Distance, the Distance is increased / expanded before
								  searching for Points LESS THAN Minimum Distance. */
						CS_DECLARE_MEMBER_WITH_PROXY(MinDistance, float)
						/** The Maximum Distance to prioritize searching for Points. 
							NOTE: Usually if no valid Points are found and no valid points are found LESS THAN Minimum Distance, then
								  the Distance is increased / expanded GREATER THAN Maximum Distance. */
						CS_DECLARE_MEMBER_WITH_PROXY(MaxDistance, float)
						/** Whether to consider using the Dot Product when determine if a Point is Valid. 
							NOTE: Usually the Dot Product is taken using Direction of the previous Segment (Point to Point). */
						CS_DECLARE_MEMBER_WITH_PROXY(bMinDot, bool)
						/** Represents Cosine of the minimum Angle between the Direction of the previous Segment (Previous Point and Current Point) 
							and next Segment (Current Point and the Point to consider). */
						CS_DECLARE_MEMBER_WITH_PROXY(MinDot, float)
						/** Minimum Angle in degrees between the Direction of the previous Segment (Previous Point and Current Point)
							and next Segment (Current Point and the Point to consider). */
						CS_DECLARE_MEMBER_WITH_PROXY(MinAngle, float)

					public:

						FParams() :
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Dimension, DimensionType::XY),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(MinDistance, 1000.0f),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(MaxDistance, 1000.0f),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(bMinDot, false),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(MinDot, 0.0f),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(MinAngle, 0.0f)
						{
							CS_CTOR_SET_MEMBER_PROXY(Dimension);
							CS_CTOR_SET_MEMBER_PROXY(MinDistance);
							CS_CTOR_SET_MEMBER_PROXY(MaxDistance);
							CS_CTOR_SET_MEMBER_PROXY(bMinDot);
							CS_CTOR_SET_MEMBER_PROXY(MinDot);
							CS_CTOR_SET_MEMBER_PROXY(MinAngle);
						}

						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Dimension, DimensionType)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MinDistance, float)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MaxDistance, float)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bMinDot, bool)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MinDot, float)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MinAngle, float)

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

					#undef DimensionType
					};
				}
			}
		}
	}
}

#pragma endregion FCsPointSequenceWeapon_Sequence_SearchParams

// FCsPointSequenceWeapon_SequenceParams
#pragma region

// NCsWeapon::NPoint::NSequence::NSequence::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NPoint, NSequence, NSequence, FParams)

/**
* Describes any information related to Sequences for a Point Sequence Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsPointSequenceWeapon_SequenceParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** The number of Points that are a part of a Sequence per Shot. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (UIMin = "2", ClampMin = "2"))
	int32 Count;

	/** The time between the Points per Shot. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Interval;

	/** Describes any information related to searching for Points. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (UIMin = "0.0", ClampMin = "0.0"))
	FCsPointSequenceWeapon_Sequence_SearchParams SearchParams;

	FCsPointSequenceWeapon_SequenceParams() :
		Count(2),
		Interval(0.0f),
		SearchParams()
	{
	}

#define ParamsType NCsWeapon::NPoint::NSequence::NSequence::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NSequence
			{
				/**
				* Describes any information related to Sequences for a Point Sequence Weapon.
				*  Weapon is an object that implements the interface: ICsWeapon.
				*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
				*/
				struct CSWP_API FParams
				{
				#define SearchParamsType NCsWeapon::NPoint::NSequence::NSequence::NSearch::FParams

				private:

					/** The number of Points that are a part of a Sequence per Shot. */
					CS_DECLARE_MEMBER_WITH_PROXY(Count, int32)
						/** The time between the Points per Shot. */
					CS_DECLARE_MEMBER_WITH_PROXY(Interval, float)
					/** Describes any information related to searching for Points. */
					SearchParamsType SearchParams;

				public:

					FParams() :
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Count, 2),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Interval, 0.0f),
						SearchParams()
					{
						CS_CTOR_SET_MEMBER_PROXY(Count);
						CS_CTOR_SET_MEMBER_PROXY(Interval);
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Count, int32)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Interval, float)
					FORCEINLINE const SearchParamsType& GetSearchParams() const { return SearchParams; }
					FORCEINLINE SearchParamsType* GetSearchParamsPtr() { return &SearchParams; }

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

				#undef SearchParamsType
				};
			}
		}
	}
}

#pragma endregion FCsPointSequenceWeapon_SequenceParams