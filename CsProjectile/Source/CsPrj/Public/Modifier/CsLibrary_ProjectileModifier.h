// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Types
#include "Modifier/CsTypes_ProjectileModifier.h"
// Projectile
#include "Modifier/CsProjectileModifier.h"
#include "Modifier/CsAllocated_ProjectileModifier.h"
// Log
#include "Utility/CsPrjLog.h"

// NCsDamage::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, IModifier)

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

		static bool IsValidChecked(const FString& Context, const ModifierType* Modifier);

		static bool IsValid(const FString& Context, const ModifierType* Modifier, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

		/**
		* Get the Type (FECsProjectileModifier) associated with Modifier.
		* 
		* @param Context	The calling context.
		* @param Modifier
		* return			Type (FECsProjectileModifier) associated with Modifier.
		*/
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

	// Damage
	#pragma region
	public:

	#define AllocatedModifierType NCsProjectile::NModifier::FAllocated
	#define DmgModifierType NCsDamage::NModifier::IModifier

		static void GetDamageModifiersChecked(const FString& Context, const TArray<AllocatedModifierType>& Modifiers, TArray<DmgModifierType*>& OutModifiers);

	#undef AllocatedModifierType
	#undef DmgModifierType

	#pragma endregion Damage
	};

	#undef ModifierType
	}
}