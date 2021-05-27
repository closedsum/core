// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Launch/CsTypes_Params_ProjectileWeapon_LaunchTrace.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Params
#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_LaunchTraceImpl.h"

// ProjectileWeaponLaunchTraceStart
#pragma region

namespace NCsProjectileWeaponLaunchTraceStart
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponLaunchTraceStart EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(LaunchLocation, "Launch Location");
		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Camera);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponLaunchTraceStart_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsProjectileWeaponLaunchTraceStart_MAX;
}

#pragma endregion ProjectileWeaponLaunchTraceStart

// ProjectileWeaponLaunchTraceDirection
#pragma region

namespace NCsProjectileWeaponLaunchTraceDirection
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponLaunchTraceDirection EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Camera);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponLaunchTraceDirection_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsProjectileWeaponLaunchTraceDirection_MAX;
}

#pragma endregion ProjectileWeaponLaunchTraceDirection

// FCsProjectileWeaponLaunchTraceParams
#pragma region

#define ParamsType NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FImpl

void FCsProjectileWeaponLaunchTraceParams::CopyToParams(ParamsType* Params)
{
	Params->SetLocationType(&Location);
	Params->SetDirectionType(&Direction);
	Params->SetDirectionRules(&DirectionRules);
	Params->SetTraceType(&TraceType);
	Params->SetTraceMethod(&TraceMethod);
	Params->SetTraceStartType(&TraceStart);
	Params->SetTraceDirectionType(&TraceDirection);
	Params->SetTraceDistance(&TraceDistance);
}

#undef ParamsType

bool FCsProjectileWeaponLaunchTraceParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_FLOAT_GREATER_THAN(TraceDistance, 0.0f)
	return true;
}

#pragma endregion FCsProjectileWeaponLaunchTraceParams