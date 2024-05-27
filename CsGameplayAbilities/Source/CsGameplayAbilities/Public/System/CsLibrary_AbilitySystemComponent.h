// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "GameplayAbilitySpecHandle.h"
#include "ActiveGameplayEffectHandle.h"
// Ability
#include "Ability/CsTypes_GameplayAbility.h"
// Log
#include "Utility/CsGameplayAbilitiesLog.h"

class UAbilitySystemComponent;
class ICsAbilitySystem_Execution;
struct FGameplayAbilitySpec;
class UGameplayEffect;

namespace NCsAbility
{
	namespace NSystem
	{
		struct CSGAMEPLAYABILITIES_API FLibrary final
		{
		#define LogLevel void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning

		// ICsAbilitySystem_Execution
		#pragma region
		public:

			static ICsAbilitySystem_Execution* GetChecked_ICsAbilitySystem_Execution(const FString& Context, UAbilitySystemComponent* Component);

			static ICsAbilitySystem_Execution* GetSafe_ICsAbilitySystem_Execution(const FString& Context, UAbilitySystemComponent* Component, LogLevel);

		#pragma endregion ICsAbilitySystem_Execution

		#undef LogLevel
		};

		namespace NComponent
		{
			struct CSGAMEPLAYABILITIES_API FLibrary final
			{
			#define LogLevel void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning

			public:

				static FString PrintOwnerWithClass(const UAbilitySystemComponent* Component);

			// Get
			#pragma region
			public:

				static UAbilitySystemComponent* GetChecked(const FString& Context, UObject* Object);

				static UAbilitySystemComponent* GetSafe(const FString& Context, UObject* Object, LogLevel);

			#pragma endregion Get

			// Tag
			#pragma region
			public:

				static void RemoveLooseGameplayTags(const FString& Context, UAbilitySystemComponent* Component, const TArray<FGameplayTag>& Tags);

			#pragma endregion Tag

			// Ability
			#pragma region
			public:

				static FGameplayAbilitySpecHandle GiveChecked(const FString& Context, UAbilitySystemComponent* Component, const FCsGameplayAbilityInfo& Info);

				static void GiveChecked(const FString& Context, UAbilitySystemComponent* Component, const TArray<FCsGameplayAbilityInfo>& Infos, TArray<FGameplayAbilitySpecHandle>& OutHandles);

				static void GiveChecked(const FString& Context, UAbilitySystemComponent* Component, const TArray<FCsGameplayAbilityInfo>& Infos);

				static const FGameplayAbilitySpec* GetChecked(const FString& Context, const UAbilitySystemComponent* Component, const FGameplayAbilitySpecHandle& Handle);
				static FGameplayAbilitySpec* GetChecked(const FString& Context, UAbilitySystemComponent* Component, const FGameplayAbilitySpecHandle& Handle);

				static bool HasChecked(const FString& Context, const UAbilitySystemComponent* Component, const FGameplayAbilitySpec* Spec);

				static bool HasAbilityChecked(const FString& Context, const UAbilitySystemComponent* Component, const FGameplayTag& Tag);

				static void GetMatchingTags(const FString& Context, const UAbilitySystemComponent* Component, const FGameplayTagContainer& Tags, TArray<FGameplayAbilitySpec*>& OutSpecs);

				static void GetMatchingExecutionTags(const FString& Context, const UAbilitySystemComponent* Component, const FGameplayTagContainer& Tags, TArray<FGameplayAbilitySpec*>& OutSpecs);

				// Activate
			#pragma region
			public:

				/**
				* Tries to Activate any Abilities on Component with matching Execution Tags.
				*  Component MUST implement the interface: ICsAbilitySystem_Execution
				* 
				* @param Context	The calling context.
				* @param Component
				* @param Tags
				* return			Whether any Abilities had been activated
				*/
				static bool TryActivateByExecutionTagsChecked(const FString& Context, UAbilitySystemComponent* Component, const FGameplayTagContainer& Tags);

				/**
				* Safely tries to Activate any Abilities on Component with matching Execution Tags.
				*  Component MUST implement the interface: ICsAbilitySystem_Execution
				* 
				* @param Context	The calling context.
				* @param Component
				* @param Tags
				* @param Log		(optional)
				* return			Whether any Abilities had been activated
				*/
				static bool TrySafeActivateByExecutionTags(const FString& Context, UAbilitySystemComponent* Component, const FGameplayTagContainer& Tags, LogLevel);

				/**
				* Safely tries to Activate any Abilities on Component with matching Execution Tags.
				*  Component MUST implement the interface: ICsAbilitySystem_Execution
				* 
				* @param Context	The calling context.
				* @param Component
				* @param Tag
				* @param Log		(optional)
				* return			Whether any Abilities had been activated
				*/
				static bool TrySafeActivateByExecutionTag(const FString& Context, UAbilitySystemComponent* Component, const FGameplayTag& Tag, LogLevel);

			#pragma endregion Activate

				// Cancel
			#pragma region
			public:

				

			#pragma endregion Cancel

			#pragma endregion Ability
		
			// Effect
			#pragma region
			public:

				static void ApplyChecked(const FString& Context, UAbilitySystemComponent* From, UAbilitySystemComponent* To, const TArray<TSubclassOf<UGameplayEffect>>& Effects, TArray<FActiveGameplayEffectHandle>& OutHandles);
				FORCEINLINE static void ApplyChecked(const FString& Context, UAbilitySystemComponent* From, UAbilitySystemComponent* To, const TArray<TSubclassOf<UGameplayEffect>>& Effects)
				{
					static TArray<FActiveGameplayEffectHandle> Handles;
					Handles.Reset(FMath::Max(Handles.Max(), Effects.Num()));

					ApplyChecked(Context, From, To, Effects, Handles);
				}

				static void ApplyChecked(const FString& Context, UAbilitySystemComponent* From, UAbilitySystemComponent* To, const TArray<UGameplayEffect*>& Effects, TArray<FActiveGameplayEffectHandle>& OutHandles);
				FORCEINLINE static void ApplyChecked(const FString& Context, UAbilitySystemComponent* From, UAbilitySystemComponent* To, const TArray<UGameplayEffect*>& Effects)
				{
					static TArray<FActiveGameplayEffectHandle> Handles;
					Handles.Reset(FMath::Max(Handles.Max(), Effects.Num()));

					ApplyChecked(Context, From, To, Effects, Handles);
				}

			#pragma endregion Effect

			#undef LogLevel
			};
		}
	}
}