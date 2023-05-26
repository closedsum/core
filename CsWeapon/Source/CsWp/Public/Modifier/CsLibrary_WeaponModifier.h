// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
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
		struct CSWP_API FLibrary final : public NCsInterfaceMap::TLibrary<ModifierType>
		{
		public:

		#define AllocatedModifierType NCsWeapon::NModifier::FAllocated

			static bool IsValidChecked(const FString& Context, const ModifierType* Modifier);

			static bool IsValid(const FString& Context, const ModifierType* Modifier, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

			static void AddChecked(const FString& Context, UObject* WorldContext, const TArray<ModifierType*>& Modifiers, TArray<AllocatedModifierType>& AllocatedModifiers);

		// Int
		#pragma region
		public:

			static int32 ModifyIntChecked(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsWeaponModifier& Type, const int32& Value);

			static int32 ModifyIntChecked(const FString& Context, const TArray<ModifierType*>& Modifiers, const FECsWeaponModifier& Type, const int32& Value);

			static int32 ModifyIntAndEmptyChecked(const FString& Context, TArray<ModifierType*>& Modifiers, const FECsWeaponModifier& Type, const int32& Value);

		#pragma endregion Int

		// Float
		#pragma region
		public:

			static float ModifyFloatChecked(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsWeaponModifier& Type, const float& Value);

			static float ModifyFloatChecked_Size64(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsWeaponModifier& Type, const float& Value);

			static float ModifyFloatChecked(const FString& Context, const TArray<ModifierType*>& Modifiers, const FECsWeaponModifier& Type, const float& Value);

			static float ModifyFloatChecked_Size64(const FString& Context, const TArray<ModifierType*>& Modifiers, const FECsWeaponModifier& Type, const float& Value);

			static float ModifyFloatAndEmptyChecked(const FString& Context, TArray<ModifierType*>& Modifiers, const FECsWeaponModifier& Type, const float& Value);

			static float ModifyFloatAndEmptyChecked_Size64(const FString& Context, TArray<ModifierType*>& Modifiers, const FECsWeaponModifier& Type, const float& Value);

		#pragma endregion Float

		public:

			static bool ToggleChecked(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsWeaponModifier& Type);

			static bool ToggleChecked(const FString& Context, const TArray<ModifierType*>& Modifiers, const FECsWeaponModifier& Type);

		#undef AllocatedModifierType
		};

	#undef ModifierType
	}
}