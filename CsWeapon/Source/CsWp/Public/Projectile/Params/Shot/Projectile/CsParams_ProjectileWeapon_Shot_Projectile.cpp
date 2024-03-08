// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Shot/Projectile/CsParams_ProjectileWeapon_Shot_Projectile.h"

// Library
#include "Library/CsLibrary_Valid.h"

// FCsProjectileWeapon_Shot_ProjectileParams
#pragma region

#define ParamsType NCsWeapon::NProjectile::NShot::NProjectile::FParams

void FCsProjectileWeapon_Shot_ProjectileParams::CopyToParams(ParamsType* Params)
{
	Params->SetCount(&Count);
	Params->SetInterval(&Interval);
	Params->SetbCurrentLaunchLocation(&bCurrentLaunchLocation);
	Params->SetbCurrentLaunchDirection(&bCurrentLaunchDirection);
}

void FCsProjectileWeapon_Shot_ProjectileParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetCount(Count);
	Params->SetInterval(Interval);
	Params->SetbCurrentLaunchLocation(bCurrentLaunchLocation);
	Params->SetbCurrentLaunchDirection(bCurrentLaunchDirection);
}

#undef ParamsType

bool FCsProjectileWeapon_Shot_ProjectileParams::IsValidChecked(const FString& Context) const
{
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Count, 1)
	CS_IS_FLOAT_GREATER_THAN_CHECKED(Interval, 0.0f)
	return true;
}

bool FCsProjectileWeapon_Shot_ProjectileParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_INT_GREATER_THAN_OR_EQUAL(Count, 1)
	CS_IS_FLOAT_GREATER_THAN(Interval, 0.0f)
	return true;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NShot
		{
			namespace NProjectile
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

#pragma endregion FCsProjectileWeapon_Shot_ProjectileParams