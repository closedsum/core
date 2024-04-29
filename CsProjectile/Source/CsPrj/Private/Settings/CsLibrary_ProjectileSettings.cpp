// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsLibrary_ProjectileSettings.h"
#include "CsPrj.h"

// Settings
#include "Settings/CsProjectileSettings.h"

namespace NCsProjectile
{
	namespace NSettings
	{
		UCsProjectileSettings* FLibrary::Get() { return GetMutableDefault<UCsProjectileSettings>(); }
		
		// Enum
		#pragma region

		const ECsPopulateEnumMapMethod& FLibrary::Get_ECsProjectile_PopulateEnumMapMethod() { return Get()->ECsProjectile_PopulateEnumMapMethod; }
		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_Projectile()				{ return Get()->GetSettingsEnum<FECsProjectile>(); }
		const FString& FLibrary::GetSettingsEnumPath_Projectile()							{ return NCsProjectileSettings::NCached::Str::Projectile; }

		const ECsPopulateEnumMapMethod& FLibrary::Get_ECsProjectileClass_PopulateEnumMapMethod() { return Get()->ECsProjectileClass_PopulateEnumMapMethod; }
		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_ProjectileClass()				 { return Get()->GetSettingsEnum<FECsProjectileClass>(); }
		const FString& FLibrary::GetSettingsEnumPath_ProjectileClass()							 { return NCsProjectileSettings::NCached::Str::ProjectileClass; }

		#pragma endregion Enum
	}
}