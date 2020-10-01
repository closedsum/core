// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Launch/CsTypes_Params_ProjectileWeapon_LaunchTrace.h"

// ProjectileWeaponLaunchTraceStart
#pragma region

namespace NCsProjectileWeaponLaunchTraceStart
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponLaunchTraceStart EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(LaunchLocation);
		CSWP_API CS_ADD_TO_ENUM_MAP(Camera);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponLaunchTraceStart_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsProjectileWeaponLaunchTraceStart_MAX;
}

#pragma endregion ProjectileWeaponLaunchTraceStart