// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Settings/CsTypes_Settings_Enum.h"

class UCsWeaponSettings;

namespace NCsWeapon
{
	namespace NSettings
	{
		/**
		*/
		class CSWP_API FLibrary
		{
		public:
			
			static UCsWeaponSettings* Get();
		
		// Enum
		#pragma region
		public:

			static const ECsPopulateEnumMapMethod& Get_ECsWeapon_PopulateEnumMapMethod();
			static const TArray<FCsSettings_Enum>& GetSettingsEnum_Weapon();
			static const FString& GetSettingsEnumPath_Weapon();

			static const ECsPopulateEnumMapMethod& Get_ECsWeaponClass_PopulateEnumMapMethod();
			static const TArray<FCsSettings_Enum>& GetSettingsEnum_WeaponClass();
			static const FString& GetSettingsEnumPath_WeaponClass();

			static const TArray<FCsSettings_Enum>& GetSettingsEnum_WeaponState();
			static const FString& GetSettingsEnumPath_WeaponState();

		#pragma endregion Enum
		};
	}
}