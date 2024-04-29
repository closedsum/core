// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Proxy.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsParams_PointWeapon_Shot_Point.generated.h"

// FCsProjectileWeapon_Shot_PointParams
#pragma region

// NCsWeapon::NPoint::NShot::NPoint::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NPoint, NShot, NPoint, FParams)

/**
* Describes any information related to Points per Shot for a Point Weapon.
*  Point Weapon is an object that implements the interface: ICsPointWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsPointWeapon_Shot_PointParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** The number of Points to Launch for a Shot. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (UIMin = "1", ClampMin = "1"))
	int32 Count;

	/** The time between the Points per Shot. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Interval;

	FCsPointWeapon_Shot_PointParams() :
		Count(1),
		Interval(0.0f)
	{
	}

#define ParamsType NCsWeapon::NPoint::NShot::NPoint::FParams
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
		namespace NShot
		{
			namespace NPoint
			{
				/**
				* Describes any information related to Points per Shot for a Point Weapon.
				*  Point Weapon is an object that implements the interface: ICsPointWeapon.
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

#pragma endregion FCsPointWeapon_Shot_PointParams