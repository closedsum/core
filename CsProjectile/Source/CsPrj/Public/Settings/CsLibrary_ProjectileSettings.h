// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Settings/CsTypes_Settings_Enum.h"

class UCsProjectileSettings;

namespace NCsProjectile
{
	namespace NSettings
	{
		/**
		*/
		class CSPRJ_API FLibrary
		{
		public:
			
			static UCsProjectileSettings* Get();
		
		// Enum
		#pragma region
		public:

			static const ECsPopulateEnumMapMethod& Get_ECsProjectile_PopulateEnumMapMethod();
			static const TArray<FCsSettings_Enum>& GetSettingsEnum_Projectile();
			static const FString& GetSettingsEnumPath_Projectile();

			static const ECsPopulateEnumMapMethod& Get_ECsProjectileClass_PopulateEnumMapMethod();
			static const TArray<FCsSettings_Enum>& GetSettingsEnum_ProjectileClass();
			static const FString& GetSettingsEnumPath_ProjectileClass();

		#pragma endregion Enum
		};
	}
}