// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Settings/CsProjectileSettings.h"
#include "CsPrj.h"

#include "CsProjectile.h"

// Cached
#pragma region

namespace NCsProjectileSettings
{
	namespace Str
	{
		CSPRJ_API CS_DEFINE_CACHED_STRING(Projectile, "UCsProjectileSettings.ECsProjectile");
		CSPRJ_API CS_DEFINE_CACHED_STRING(ProjectileClass, "UCsProjectileSettings.ECsProjectileClass");
	}
}

#pragma endregion Cached

UCsProjectileSettings::UCsProjectileSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}