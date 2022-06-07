// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Weapon
#include "Modifier/Projectile/CsProjectileWeaponModifier.h"
// Log
#include "Utility/CsWpLog.h"

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NModifier
		{
		#define ModifierType NCsWeapon::NProjectile::NModifier::IModifier

		/**
		* Library for interface: ModifierType (NCsWeapon::NProjectile::NModifier::IModifier)
		*/
		struct CSWP_API FLibrary final : public NCsInterfaceMap::TLibrary<ModifierType>
		{
		public:

			static bool IsValidChecked(const FString& Context, const ModifierType* Modifier);

			static bool IsValid(const FString& Context, const ModifierType* Modifier, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);
		};

		#undef ModifierType
		}
	}
}