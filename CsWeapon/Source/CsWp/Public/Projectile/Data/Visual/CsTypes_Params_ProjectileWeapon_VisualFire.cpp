// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/Visual/CsTypes_Params_ProjectileWeapon_VisualFire.h"

#include "Projectile/Data/Visual/CsParams_ProjectileWeapon_VisualFire.h"

// ProjectileWeaponVisualFireAttach
#pragma region

namespace NCsProjectileWeaponVisualFireAttach
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponVisualFireAttach EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(None);
		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponVisualFireAttach_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsProjectileWeaponVisualFireAttach_MAX;
}

#pragma endregion ProjectileWeaponVisualFireAttach

// FCsProjectileWeaponLaunchTraceParams
#pragma region

#define ParamsType NCsWeapon::NProjectile::NData::NVisual::NFire::FParams
void FCsProjectileWeaponVisualFireParams::CopyParams(ParamsType* Params)
{
#undef ParamsType

	Params->SetFX(&FX);
	Params->SetAttachType(&Attach);
}

#pragma endregion FCsProjectileWeaponLaunchTraceParams