// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsProjectileSettings.h"

// Types
#include "CsMacro_Misc.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsProjectileSettings)

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