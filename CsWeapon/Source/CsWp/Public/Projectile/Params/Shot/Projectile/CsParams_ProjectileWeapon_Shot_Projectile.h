// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Proxy.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsParams_ProjectileWeapon_Shot_Projectile.generated.h"

// FCsProjectileWeapon_Shot_ProjectileParams
#pragma region

// NCsWeapon::NProjectile::NShot::NProjectile::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NProjectile, NShot, NProjectile, FParams)

/**
* Describes any information related to Projectiles per Shot for a Projectile Weapon.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeapon_Shot_ProjectileParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** The number of Projectiles to Launch for a Shot. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (UIMin = "1", ClampMin = "1"))
	int32 Count;

	/** The time between the Projectiles per Shot. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Interval;

	/** Whether to determine the current Launch Location or used a cached Launch Location (determined at Fire, start of a Shot). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	bool bCurrentLaunchLocation;

	/** Whether to determine the current Launch Direction or used a cached Launch Direction (determined at Fire, start of a Shot). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	bool bCurrentLaunchDirection;

	FCsProjectileWeapon_Shot_ProjectileParams() :
		Count(1),
		Interval(0.0f),
		bCurrentLaunchLocation(true),
		bCurrentLaunchDirection(true)
	{
	}

#define ParamsType NCsWeapon::NProjectile::NShot::NProjectile::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NShot
		{
			namespace NProjectile
			{
				/**
				* Describes any information related to Projectiles per Shot for a Projectile Weapon.
				*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
				*/
				struct CSWP_API FParams
				{
				private:

					/** The number of Projectiles to Launch for a Shot. */
					CS_DECLARE_MEMBER_WITH_PROXY(Count, int32)
					/** The time between the Projectiles per Shot. */
					CS_DECLARE_MEMBER_WITH_PROXY(Interval, float)
					/** Whether to determine the current Launch Location or used a cached Launch Location (determined at Fire, start of a Shot). */
					CS_DECLARE_MEMBER_WITH_PROXY(bCurrentLaunchLocation, bool)
					/** Whether to determine the current Launch Direction or used a cached Launch Direction (determined at Fire, start of a Shot). */
					CS_DECLARE_MEMBER_WITH_PROXY(bCurrentLaunchDirection, bool)

				public:

					FParams() :
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Count, 1),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Interval, 0.0f),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(bCurrentLaunchLocation, true),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(bCurrentLaunchDirection, true)
					{
						CS_CTOR_SET_MEMBER_PROXY(Count);
						CS_CTOR_SET_MEMBER_PROXY(Interval);
						CS_CTOR_SET_MEMBER_PROXY(bCurrentLaunchLocation);
						CS_CTOR_SET_MEMBER_PROXY(bCurrentLaunchDirection);
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Count, int32)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Interval, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bCurrentLaunchLocation, bool)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bCurrentLaunchDirection, bool)

					FORCEINLINE bool CanCacheLocationOrDirection() const 
					{
						return GetCount() > 1 && GetInterval() > 0.0f && (GetbCurrentLaunchLocation() || GetbCurrentLaunchDirection());
					}

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
				};
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Shot_ProjectileParams