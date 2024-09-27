// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Ability/CsTypes_GameplayAbility.h"
#include "GameplayTagContainer.h"
// Ability
#include "GameplayAbilitySpec.h"
// Log
#include "Utility/CsGameplayAbilitiesLog.h"

class UGameplayAbility;

namespace NCsGameplayAbility
{
	struct CSGAMEPLAYABILITIES_API FLibrary final
	{
	#define LogLevel void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning

	// Spec
	#pragma region
	public:

		FORCEINLINE static void Reset(FGameplayAbilitySpec& Spec)
		{
			//Spec.Handle;
			Spec.Ability = nullptr;
			Spec.Level = 0;
			Spec.InputID = -1;
			Spec.SourceObject.Reset();
			Spec.ActiveCount = 0;
			Spec.InputPressed = false;
			Spec.RemoveAfterActivation = false;
			Spec.PendingRemove = false;
			Spec.bActivateOnce = false;
			Spec.GameplayEventData.Reset();
			Spec.ActivationInfo.ActivationMode = EGameplayAbilityActivationMode::Authority;
			Spec.ActivationInfo.bCanBeEndedByOtherInstance = false;
			Spec.DynamicAbilityTags.Reset(Spec.DynamicAbilityTags.Num());
			Spec.NonReplicatedInstances.Reset(Spec.NonReplicatedInstances.Num());
			Spec.ReplicatedInstances.Reset(Spec.ReplicatedInstances.Num());
			Spec.GameplayEffectHandle.Invalidate();
			Spec.SetByCallerTagMagnitudes.Reset();
		}

		static bool IsValidSpecChecked(const FString& Context, const FGameplayAbilitySpec& Spec);

		static bool IsValidSpec(const FString& Context, const FGameplayAbilitySpec& Spec, LogLevel);

		static bool IsValidSpecChecked(const FString& Context, const FGameplayAbilitySpec* Spec);

		static bool IsValidSpec(const FString& Context, const FGameplayAbilitySpec* Spec, LogLevel);

		static void BuildChecked(const FString& Context, UGameplayAbility* AbilityClass, const int32& Level, const int32& InputID, FGameplayAbilitySpec& OutSpec);

		static void BuildChecked(const FString& Context, const FCsGameplayAbilityInfo& Info, FGameplayAbilitySpec& OutSpec);

		static bool HasAll(const FString& Context, const FGameplayAbilitySpec& Spec, const FGameplayTagContainer& Tags);

	#pragma endregion Spec

	#undef LogLevel
	};
}

using CsGameplayAbilityLibrary = NCsGameplayAbility::FLibrary;