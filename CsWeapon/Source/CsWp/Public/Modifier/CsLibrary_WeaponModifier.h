// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Weapon
#include "Modifier/CsWeaponModifier.h"
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
	struct CSWP_API FLibrary final : public NCsInterfaceMap::TLibrary<ModifierType>
	{
	public:

		static bool IsValidChecked(const FString& Context, const ModifierType* Modifier);

		static bool IsValid(const FString& Context, const ModifierType* Modifier, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);
	};

	#undef ModifierType
	}
}