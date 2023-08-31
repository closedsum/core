// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsProjectileSettings.h"
#include "CsPrj.h"

#include "CsProjectile.h"

// Cached
#pragma region

namespace NCsProjectileSettings
{
	namespace NCached
	{
		namespace Str
		{
			CSPRJ_API CS_DEFINE_CACHED_STRING(Projectile, "UCsProjectileSettings.ECsProjectile");
			CSPRJ_API CS_DEFINE_CACHED_STRING(ProjectileClass, "UCsProjectileSettings.ECsProjectileClass");
		}
	}
}

#pragma endregion Cached

UCsProjectileSettings::UCsProjectileSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}