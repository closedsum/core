// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Types
#include "Modifier/Types/CsTypes_ProjectileModifier.h"
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
		namespace NLibrary
		{
			using ModifierType = NCsProjectile::NModifier::IModifier;

			/**
			* Library for interface: ModifierType (NCsProjectile::NModifier::IModifier)
			*/
			struct CSPRJ_API FLibrary final : public NCsInterfaceMap::TLibrary<ModifierType>
			{
			private:

				using AllocatedModifierType = NCsProjectile::NModifier::FAllocated;
				using DmgModifierType = NCsDamage::NModifier::IModifier;

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

				static void AddChecked(const FString& Context, UObject* WorldContext, const TArray<ModifierType*>& Modifiers, TArray<AllocatedModifierType>& AllocatedModifiers);

			// Int
			#pragma region
			public:

				static int32 ModifyIntChecked(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsProjectileModifier& Type, const int32& Value);

			#pragma endregion Int

			// Float
			#pragma region
			public:

				static float ModifyFloatChecked(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsProjectileModifier& Type, const float& Value);

				static float ModifyFloatChecked_Size64(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsProjectileModifier& Type, const float& Value);

				static float ModifyFloatChecked(const FString& Context, const ModifierType* Modifier, const float& Value);

			#pragma endregion Float

			// Damage
			#pragma region
			public:	

				static void GetDamageModifiersChecked(const FString& Context, const TArray<AllocatedModifierType>& Modifiers, TArray<DmgModifierType*>& OutModifiers);

			#pragma endregion Damage
			};
		}
	}
}

using CsProjectileModifierLibrary = NCsProjectile::NModifier::NLibrary::FLibrary;