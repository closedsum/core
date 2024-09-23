// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Spawner
#include "Modifier/CsSpawnerModifier.h"
#include "Modifier/CsAllocated_SpawnerModifier.h"
// Log
#include "Utility/CsSpawnerLog.h"

namespace NCsSpawner
{
	namespace NModifier
	{
		/**
		* Library for interface: ModifierType (NCsSpawner::NModifier::IModifier)
		*/
		struct CSSPAWNER_API FLibrary final : public NCsInterfaceMap::TLibrary<CsSpawnerModifierType>
		{
		#define LogLevel void(*Log)(const FString&) = &NCsSpawner::FLog::Warning

		public:

			static bool IsValidChecked(const FString& Context, const CsSpawnerModifierType* Modifier);

			static bool IsValid(const FString& Context, const CsSpawnerModifierType* Modifier, LogLevel);

		#define AllocatedModifierType NCsSpawner::NModifier::FAllocated

			static void AddChecked(const FString& Context, UObject* WorldContext, const TArray<CsSpawnerModifierType*>& Modifiers, TArray<AllocatedModifierType>& AllocatedModifiers);

			static int32 ModifyIntChecked(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsSpawnerModifier& Type, const int32& Value);

			static float ModifyFloatChecked(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsSpawnerModifier& Type, const float& Value);

		#undef AllocatedModifierType

		#undef LogLevel
		};
	}
}

using CsSpawnerModifierLibrary = NCsSpawner::NModifier::FLibrary;