// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Types
#include "Modifier/Types/CsTypes_WeaponModifier.h"
// Weapon
#include "Modifier/CsWeaponModifier.h"
#include "Modifier/CsAllocated_WeaponModifier.h"
// Log
#include "Utility/CsWpLog.h"

namespace NCsWeapon
{
	namespace NModifier
	{
	#define ModifierType NCsWeapon::NModifier::IModifier

	/**
	* Library for interface: ModifierType (NCsWeapon::NModifier::IModifier)
	*/
	struct CSWP_API FLibrary final : public TCsLibrary_InterfaceMap<ModifierType>
	{
	public:

		static bool IsValidChecked(const FString& Context, const ModifierType* Modifier);

		static bool IsValid(const FString& Context, const ModifierType* Modifier, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

		/**
		* Get the Type (FECsWeaponModifier) associated with Modifier.
		* 
		* @param Context	The calling context.
		* @param Modifier
		* return			Type (FECsWeaponModifier) associated with Modifier.
		*/
		static const FECsWeaponModifier& GetTypeChecked(const FString& Context, const ModifierType* Modifier);

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