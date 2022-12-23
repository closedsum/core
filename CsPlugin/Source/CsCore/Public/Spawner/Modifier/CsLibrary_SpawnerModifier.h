// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Spawner
#include "Spawner/Modifier/CsSpawnerModifier.h"
#include "Spawner/Modifier/CsAllocated_SpawnerModifier.h"
// Log
#include "Utility/CsLog.h"

namespace NCsSpawner
{
	namespace NModifier
	{
	#define ModifierType NCsSpawner::NModifier::IModifier

		/**
		* Library for interface: ModifierType (NCsSpawner::NModifier::IModifier)
		*/
		struct CSCORE_API FLibrary final : public NCsInterfaceMap::TLibrary<ModifierType>
		{
		public:

			static bool IsValidChecked(const FString& Context, const ModifierType* Modifier);

			static bool IsValid(const FString& Context, const ModifierType* Modifier, void(*Log)(const FString&) = &FCsLog::Warning);

		#define AllocatedModifierType NCsSpawner::NModifier::FAllocated

			static void AddChecked(const FString& Context, UObject* WorldContext, const TArray<ModifierType*>& Modifiers, TArray<AllocatedModifierType>& AllocatedModifiers);

			static int32 ModifyIntChecked(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsSpawnerModifier& Type, const int32& Value);

			static float ModifyFloatChecked(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsSpawnerModifier& Type, const float& Value);

		#undef AllocatedModifierType
		};

	#undef ModifierType
	}
}