// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/Projectile/CsLibrary_ProjectileWeaponModifier.h"
#include "CsWp.h"

// Library
#include "Library/CsLibrary_Valid.h"

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NModifier
		{
			#define ModifierType NCsWeapon::NProjectile::NModifier::IModifier

			bool FLibrary::IsValidChecked(const FString& Context, const ModifierType* Modifier)
			{
				CS_IS_PTR_NULL_CHECKED(Modifier)

				return true;
			}

			bool FLibrary::IsValid(const FString& Context, const ModifierType* Modifier, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
			{
				CS_IS_PTR_NULL(Modifier)

				return true;
			}

			#undef ModifierType
		}
	}
}