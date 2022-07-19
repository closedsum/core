// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsTypes_Payload_Projectile.h"
#include "CsPrj.h"

// NCsProjectilePayload
#pragma region

namespace NCsProjectilePayload
{
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(Projectile, "NCsProjectile::NPayload::IPayload");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(ProjectileCollision, "NCsProjectile::NPayload::NCollision::ICollision");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(ProjectileModifier, "NCsProjectile::NPayload::NModifier::IModifier");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(ProjectileTarget, "NCsProjectile::NPayload::NTarget::ITarget");
}

#pragma endregion NCsProjectilePayload