// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Launch/CsTypes_Params_ProjectileWeapon_LaunchTrace.h"

#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_LaunchTraceEmu.h"

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

#define EmuType NCsWeapon::NProjectile::NParams::NLaunch::FTraceEmu
void FCsProjectileWeaponLaunchTraceParams::CopyParams(EmuType* Emu)
{
#undef EmuType

	Emu->SetLocationType(&Location);
	Emu->SetDirectionType(&Direction);
	Emu->SetDirectionRules(&DirectionRules);
	Emu->SetTraceType(&TraceType);
	Emu->SetTraceMethod(&TraceMethod);
	Emu->SetTraceStartType(&TraceStart);
	Emu->SetTraceDirectionType(&TraceDirection);
	Emu->SetTraceDistance(&TraceDistance);
}

#pragma endregion FCsProjectileWeaponLaunchTraceParams