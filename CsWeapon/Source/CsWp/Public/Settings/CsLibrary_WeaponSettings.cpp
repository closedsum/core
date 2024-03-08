// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsLibrary_WeaponSettings.h"
#include "CsWp.h"

// Settings
#include "Settings/CsWeaponSettings.h"

namespace NCsWeapon
{
	namespace NSettings
	{
		UCsWeaponSettings* FLibrary::Get() { return GetMutableDefault<UCsWeaponSettings>(); }
		
		// Enum
		#pragma region

		const ECsPopulateEnumMapMethod& FLibrary::Get_ECsWeapon_PopulateEnumMapMethod() { return Get()->ECsWeapon_PopulateEnumMapMethod; }
		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_Weapon()				{ return Get()->GetSettingsEnum<FECsWeapon>(); }
		const FString& FLibrary::GetSettingsEnumPath_Weapon()							{ return NCsWeaponSettings::NCached::Str::Weapon; }

		const ECsPopulateEnumMapMethod& FLibrary::Get_ECsWeaponClass_PopulateEnumMapMethod(){ return Get()->ECsWeaponClass_PopulateEnumMapMethod; }
		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_WeaponClass()				{ return Get()->GetSettingsEnum<FECsWeaponClass>(); }
		const FString& FLibrary::GetSettingsEnumPath_WeaponClass()							{ return NCsWeaponSettings::NCached::Str::WeaponClass; }

		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_WeaponState()				{ return Get()->GetSettingsEnum<FECsWeaponState>(); }
		const FString& FLibrary::GetSettingsEnumPath_WeaponState()							{ return NCsWeaponSettings::NCached::Str::WeaponState; }

		#pragma endregion Enum
	}
}