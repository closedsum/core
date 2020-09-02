// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsTypes_Payload_Projectile.h"
#include "CsPrj.h"

// NCsProjectilePayload
#pragma region

namespace NCsProjectilePayload
{
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsProjectilePayload, Projectile, "ICsPayload_Projectile");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsProjectilePayload, ProjectileDamageModifier, "ICsPayload_ProjectileDamageModifier");
}

#pragma endregion NCsProjectilePayload