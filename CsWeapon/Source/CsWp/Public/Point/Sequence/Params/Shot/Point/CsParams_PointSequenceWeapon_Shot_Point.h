// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsParams_PointSequenceWeapon_Shot_Point.generated.h"

// FCsPointSequenceWeapon_Shot_PointParams
#pragma region

// NCsWeapon::NPoint::NSequence::NShot::NPoint::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NPoint, NSequence, NShot, NPoint, FParams)

/**
* Describes any information related to Points per Shot for a Point Sequence Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsPointSequenceWeapon_Shot_PointParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** The number of Points to Launch for a Shot. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (UIMin = "1", ClampMin = "1"))
	int32 Count;

	/** The time between the Points per Shot. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Interval;

	FCsPointSequenceWeapon_Shot_PointParams() :
		Count(1),
		Interval(0.0f)
	{
	}

#define ParamsType NCsWeapon::NPoint::NSequence::NShot::NPoint::FParams
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
			namespace NShot
		{
			namespace NPoint
			{
				/**
				* Describes any information related to Points per Shot for a Point Sequence Weapon.
				*  Weapon is an object that implements the interface: ICsWeapon.
				*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
				*/
				struct CSWP_API FParams
				{
				private:

					/** The number of Points to Launch for a Shot. */
					CS_DECLARE_MEMBER_WITH_PROXY(Count, int32)
					/** The time between the Points per Shot. */
					CS_DECLARE_MEMBER_WITH_PROXY(Interval, float)

				public:

					FParams() :
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Count, 1),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Interval, 0.0f)
					{
						CS_CTOR_SET_MEMBER_PROXY(Count);
						CS_CTOR_SET_MEMBER_PROXY(Interval);
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Count, int32)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Interval, float)

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
				};
			}
		}
		}
	}
}

#pragma endregion FCsPointSequenceWeapon_Shot_PointParams