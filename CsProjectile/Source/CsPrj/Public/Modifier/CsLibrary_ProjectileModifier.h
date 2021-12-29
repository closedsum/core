// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Types
#include "Modifier/CsTypes_ProjectileModifier.h"
// Projectile
#include "Modifier/CsProjectileModifier.h"

namespace NCsProjectile
{
	namespace NModifier
	{
	#define ModifierType NCsProjectile::NModifier::IModifier

	/**
	* Library for interface: ModifierType (NCsProjectile::NModifier::IModifier)
	*/
	struct CSPRJ_API FLibrary final : public TCsLibrary_InterfaceMap<ModifierType>
	{
	public:

		static const FECsProjectileModifier& GetTypeChecked(const FString& Context, const ModifierType* Modifier);

		/**
		* Copy the values from From to To with checks.
		* Currently supports To types of:
		*  
		*
		* @param Context	The calling context.
		* @param From		What to copy.
		* @param To			What to copy to.
		* return			Whether the copy was performed successfully.
		*/
		static bool CopyChecked(const FString& Context, const ModifierType* From, ModifierType* To);
	};

	#undef ModifierType
	}
}