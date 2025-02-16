// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/Projectile/CsLibrary_ProjectileWeaponModifier.h"

// Library
#include "Library/CsLibrary_Valid.h"

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NModifier
		{
			namespace NLibrary
			{
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
			}
		}
	}
}