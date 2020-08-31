// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Settings/CsProjectileSettings.h"
#include "CsPrj.h"

#include "Managers/Projectile/CsProjectile.h"

// Cached
#pragma region

namespace NCsProjectileSettings
{
	namespace Str
	{
		CSPRJ_API const FString Projectile = TEXT("UCsProjectileSettings.ECsProjectile");
		CSPRJ_API const FString ProjectileClass = TEXT("UCsProjectileSettings.ECsProjectileClass");
	}
}

#pragma endregion Cached

UCsProjectileSettings::UCsProjectileSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}