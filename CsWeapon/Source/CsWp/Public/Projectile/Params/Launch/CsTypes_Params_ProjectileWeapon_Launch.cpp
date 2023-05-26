// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Launch/CsTypes_Params_ProjectileWeapon_Launch.h"

// ProjectileWeaponLaunchLocation
#pragma region

namespace NCsProjectileWeaponLaunchLocation
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponLaunchLocation EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponLaunchLocation_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsProjectileWeaponLaunchLocation_MAX;
}

#pragma endregion ProjectileWeaponLaunchLocation

// ProjectileWeaponLaunchDirection
#pragma region

namespace NCsProjectileWeaponLaunchDirection
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponLaunchDirection EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Camera);
		CSWP_API CS_ADD_TO_ENUM_MAP(Trace);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponLaunchDirection_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsProjectileWeaponLaunchDirection_MAX;
}

#pragma endregion ProjectileWeaponLaunchDirection