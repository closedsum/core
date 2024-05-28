// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "System/CsLibrary_AbilitySystemComponent.h"

// Library
	// Common
#include "Ability/CsLibrary_GameplayAbility.h"
#include "CsLibrary_Valid_GameplayTags.h"
#include "CsLibrary_Valid_GameplayAbilities.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Interface
#include "AbilitySystemInterface.h"
#include "System/CsAbilitySystem_Execution.h"
// Ability
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
// Actor
#include "GameFramework/Actor.h"

namespace NCsAbility
{
	namespace NSystem
	{
		#define LogLevel void(*Log)(const FString&) /*=&NCsGameplayAbilities::FLog::Warning*/

		// ICsAbilitySystem_Execution
		#pragma region

		ICsAbilitySystem_Execution* FLibrary::GetChecked_ICsAbilitySystem_Execution(const FString& Context, UAbilitySystemComponent* Component)
		{
			return CS_INTERFACE_CAST_CHECKED(Component, UAbilitySystemComponent, ICsAbilitySystem_Execution);
		}

		ICsAbilitySystem_Execution* FLibrary::GetSafe_ICsAbilitySystem_Execution(const FString& Context, UAbilitySystemComponent* Component, LogLevel)
		{
			return CS_INTERFACE_CAST(Component, UAbilitySystemComponent, ICsAbilitySystem_Execution);
		}

		#pragma endregion ICsAbilitySystem_Execution

		#undef LogLevel

		namespace NComponent
		{
			#define LogLevel void(*Log)(const FString&) /*=&NCsGameplayAbilities::FLog::Warning*/
			#define ObjectLibrary NCsObject::FLibrary
			#define AbilitySystemLibrary NCsAbility::NSystem::FLibrary
			#define GameplayAbilityLibrary NCsGameplayAbility::FLibrary

			FString FLibrary::PrintOwnerWithClass(const UAbilitySystemComponent* Component)
			{
				return FString::Printf(TEXT("Owner: %s with Component's Class: %s"), *(Component->GetOwnerActor()->GetName()), *(Component->GetClass()->GetName()));
			}

			// Get
			#pragma region
			
			UAbilitySystemComponent* FLibrary::GetChecked(const FString& Context, const UObject* Object)
			{
			#if !UE_BUILD_SHIPPING
				UAbilitySystemComponent* ASC = CS_CONST_INTERFACE_CAST_CHECKED(Object, UObject, IAbilitySystemInterface)->GetAbilitySystemComponent();

				CS_IS_PENDING_KILL_CHECKED(ASC)
				return ASC;
			#else
				return Cast<IAbilitySystemInterface>(Object)->GetAbilitySystemComponent();
			#endif // #if !UE_BUILD_SHIPPING
			}

			UAbilitySystemComponent* FLibrary::GetSafe(const FString& Context, const UObject* Object, LogLevel)
			{
				if (const IAbilitySystemInterface* Interface = CS_CONST_INTERFACE_CAST(Object, UObject, IAbilitySystemInterface))
				{
					UAbilitySystemComponent* ASC = Interface->GetAbilitySystemComponent();

					CS_IS_PENDING_KILL_RET_NULL(ASC)
					return ASC;
				}
				return nullptr;
			}

			#pragma endregion Get

			// Tag
			#pragma region

			void FLibrary::RemoveLooseGameplayTags(const FString& Context, UAbilitySystemComponent* Component, const TArray<FGameplayTag>& Tags)
			{
				CS_IS_PENDING_KILL_CHECKED(Component)
				CS_IS_TARRAY_EMPTY_CHECKED(Tags, FGameplayTag)
				CS_IS_GAMEPLAY_TAGS_VALID_CHECKED(Tags)

				for (const FGameplayTag& Tag : Tags)
				{
					Component->RemoveLooseGameplayTag(Tag);
				}
			}

			#pragma endregion Tag

			// Ability
			#pragma region
	
			FGameplayAbilitySpecHandle FLibrary::GiveChecked(const FString& Context, UAbilitySystemComponent* Component, const FCsGameplayAbilityInfo& Info)
			{
				CS_IS_PENDING_KILL_CHECKED(Component)
				CS_IS_VALID_CHECKED(Info);

				FGameplayAbilitySpec Spec;
				GameplayAbilityLibrary::BuildChecked(Context, Info, Spec);

				FGameplayAbilitySpecHandle Handle = Component->GiveAbility(Spec);

				CS_IS_GA_SPEC_HANDLE_VALID_CHECKED(Handle)

				if (Info.ExecutionRequiredTags.IsValid())
				{
					ICsAbilitySystem_Execution* Interface = AbilitySystemLibrary::GetChecked_ICsAbilitySystem_Execution(Context, Component);
					
					Interface->AddExecutionRequiredTags(Handle, Info.ExecutionRequiredTags);
				}
				return Handle;
			}

			void FLibrary::GiveChecked(const FString& Context, UAbilitySystemComponent* Component, const TArray<FCsGameplayAbilityInfo>& Infos, TArray<FGameplayAbilitySpecHandle>& OutHandles)
			{
				CS_IS_TARRAY_EMPTY_CHECKED(Infos, FCsGameplayAbilityInfo)

				OutHandles.Reset(FMath::Max(OutHandles.Max(), Infos.Num()));

				for (const FCsGameplayAbilityInfo& Info : Infos)
				{
					FGameplayAbilitySpecHandle Handle = GiveChecked(Context, Component, Info);

					OutHandles.Add(Handle);
				}
			}

			void FLibrary::GiveChecked(const FString& Context, UAbilitySystemComponent* Component, const TArray<FCsGameplayAbilityInfo>& Infos)
			{
				CS_IS_TARRAY_EMPTY_CHECKED(Infos, FCsGameplayAbilityInfo)

				for (const FCsGameplayAbilityInfo& Info : Infos)
				{
					GiveChecked(Context, Component, Info);
				}
			}

			const FGameplayAbilitySpec* FLibrary::GetChecked(const FString& Context, const UAbilitySystemComponent* Component, const FGameplayAbilitySpecHandle& Handle)
			{
				CS_IS_PENDING_KILL_CHECKED(Component)
				CS_IS_GA_SPEC_HANDLE_VALID_CHECKED(Handle)

				const TArray<FGameplayAbilitySpec>& Specs = Component->GetActivatableAbilities();

				for (const FGameplayAbilitySpec& Spec : Specs)
				{
					if (Spec.Handle == Handle)
						return &Spec;
				}
				checkf(0, TEXT("%s: %s: Failed to find Gameplay Ability Spec associated with Handle."), *Context, *PrintOwnerWithClass(Component));
				return nullptr;
			}

			FGameplayAbilitySpec* FLibrary::GetChecked(const FString& Context, UAbilitySystemComponent* Component, const FGameplayAbilitySpecHandle& Handle)
			{
				CS_IS_PENDING_KILL_CHECKED(Component)
				CS_IS_GA_SPEC_HANDLE_VALID_CHECKED(Handle)

				TArray<FGameplayAbilitySpec>& Specs = Component->GetActivatableAbilities();

				for (FGameplayAbilitySpec& Spec : Specs)
				{
					if (Spec.Handle == Handle)
						return &Spec;
				}
				checkf(0, TEXT("%s: %s: Failed to find Gameplay Ability Spec associated with Handle."), *Context, *PrintOwnerWithClass(Component));
				return nullptr;
			}

			bool FLibrary::HasChecked(const FString& Context, const UAbilitySystemComponent* Component, const FGameplayAbilitySpec* Spec)
			{
				CS_IS_PENDING_KILL_CHECKED(Component)
				check(GameplayAbilityLibrary::IsValidSpecChecked(Context, Spec));

				for (const FGameplayAbilitySpec& S : Component->GetActivatableAbilities())
				{
					if (S.Handle == Spec->Handle)
						return true;
				}
				checkf(0, TEXT("%s: %s does NOT have Spec."), *Context);
				return false;
			}

			bool FLibrary::HasAbilityChecked(const FString& Context, const UAbilitySystemComponent* Component, const FGameplayTag& Tag)
			{
				CS_IS_PENDING_KILL_CHECKED(Component)
				CS_IS_GAMEPLAY_TAG_VALID_CHECKED(Tag)

				int32 Count = 0;

				for (const FGameplayAbilitySpec& Spec : Component->GetActivatableAbilities())
				{
					CS_IS_OBJECT_PTR_NULL_CHECKED(Spec.Ability, UGameplayAbility)
					
					int32 LocalCount = Spec.Ability->AbilityTags.HasTagExact(Tag) ? 1 : 0;

					// Non Replicated
					for (const TObjectPtr<UGameplayAbility>& Instance : Spec.NonReplicatedInstances)
					{
						CS_IS_OBJECT_PTR_NULL_CHECKED(Instance, UGameplayAbility)

						LocalCount += Instance->AbilityTags.HasTagExact(Tag) ? 1 : 0;
					}
					// Replicated
					for (const TObjectPtr<UGameplayAbility>& Instance : Spec.ReplicatedInstances)
					{
						CS_IS_OBJECT_PTR_NULL_CHECKED(Instance, UGameplayAbility)

						LocalCount += Instance->AbilityTags.HasTagExact(Tag) ? 1 : 0;
					}

					Count += LocalCount > 0 ? 1 : 0;
				}
				checkf(Count == 1, TEXT("%s: More than ONE Ability found with Tag: %s."), *(Tag.ToString()));
				return Count > 0;
			}

			void FLibrary::GetMatchingTags(const FString& Context, const UAbilitySystemComponent* Component, const FGameplayTagContainer& Tags, TArray<FGameplayAbilitySpec*>& OutSpecs)
			{
				CS_IS_PENDING_KILL_CHECKED(Component)
				CS_IS_GAMEPLAY_TAG_CONTAINER_VALID_CHECKED(Tags)

				for (const FGameplayAbilitySpec& Spec : Component->GetActivatableAbilities())
				{
					if (GameplayAbilityLibrary::HasAll(Context, Spec, Tags))
						OutSpecs.Add(const_cast<FGameplayAbilitySpec*>(&Spec));
				}
			}

			void FLibrary::GetMatchingExecutionTags(const FString& Context, const UAbilitySystemComponent* Component, const FGameplayTagContainer& Tags, TArray<FGameplayAbilitySpec*>& OutSpecs)
			{
				CS_IS_PENDING_KILL_CHECKED(Component)
				CS_IS_GAMEPLAY_TAG_CONTAINER_VALID_CHECKED(Tags)

				const ICsAbilitySystem_Execution* Interface =  CS_CONST_INTERFACE_CAST_CHECKED(Component, UAbilitySystemComponent, ICsAbilitySystem_Execution);

				const TMap<FGameplayAbilitySpecHandle, FGameplayTagContainer>& ExecutionRequiredTagsByAbilitySpecHandleMap = Interface->GetExecutionRequiredTagsByAbilitySpecHandleMap();

				for (const FGameplayAbilitySpec& Spec : Component->GetActivatableAbilities())
				{
					if (const FGameplayTagContainer* TagsPtr = ExecutionRequiredTagsByAbilitySpecHandleMap.Find(Spec.Handle))
					{
						if (TagsPtr->HasAll(Tags))
							OutSpecs.Add(const_cast<FGameplayAbilitySpec*>(&Spec));
					}
				}
			}

			bool FLibrary::GetSafeActivatableAbilities_PrimaryInstance(const FString& Context, const UAbilitySystemComponent* Component, TArray<UGameplayAbility*>& OutAbilities, LogLevel)
			{
				CS_IS_PENDING_KILL(Component)

				const TArray<FGameplayAbilitySpec>& ActivatableAbilities = Component->GetActivatableAbilities();

				CS_IS_TARRAY_EMPTY(ActivatableAbilities, FGameplayAbilitySpec)

				OutAbilities.Reset(FMath::Max(OutAbilities.Max(), ActivatableAbilities.Num()));

				for (const FGameplayAbilitySpec& Spec : ActivatableAbilities)
				{
					if (!GameplayAbilityLibrary::IsValidSpec(Context, &Spec, Log))
						return false;

					// TODO: Make a Checked and Safe call for GetPrimaryInstance
					OutAbilities.Add(Spec.GetPrimaryInstance());
				}
				return true;
			}

			bool FLibrary::TryActivateByExecutionTagsChecked(const FString& Context, UAbilitySystemComponent* Component, const FGameplayTagContainer& Tags)
			{
				CS_IS_PENDING_KILL_CHECKED(Component)
				CS_IS_GAMEPLAY_TAG_CONTAINER_VALID_CHECKED(Tags)

				// TODO: Check FGameplayAbilitySpecContainer is Valid
				static TArray<FGameplayAbilitySpec*> AbilitiesToActivate;
				AbilitiesToActivate.Reset(AbilitiesToActivate.Max());

				GetMatchingExecutionTags(Context, Component, Tags, AbilitiesToActivate);

				bool Success = false;

				for (FGameplayAbilitySpec* Spec : AbilitiesToActivate)
				{
					Success |= Component->TryActivateAbility(Spec->Handle, true);
				}
				AbilitiesToActivate.Reset(AbilitiesToActivate.Max());
				return Success;
			}

			bool FLibrary::TrySafeActivateByExecutionTags(const FString& Context, UAbilitySystemComponent* Component, const FGameplayTagContainer& Tags, LogLevel)
			{
				CS_IS_PENDING_KILL(Component)
				CS_IS_GAMEPLAY_TAG_CONTAINER_VALID(Tags)

				// TODO: Check FGameplayAbilitySpecContainer is Valid
				static TArray<FGameplayAbilitySpec*> AbilitiesToActivate;
				AbilitiesToActivate.Reset(AbilitiesToActivate.Max());

				GetMatchingExecutionTags(Context, Component, Tags, AbilitiesToActivate);

				bool Success = false;

				for (FGameplayAbilitySpec* Spec : AbilitiesToActivate)
				{
					Success |= Component->TryActivateAbility(Spec->Handle, true);
				}
				AbilitiesToActivate.Reset(AbilitiesToActivate.Max());
				return Success;
			}

			bool FLibrary::TrySafeActivateByExecutionTag(const FString& Context, UAbilitySystemComponent* Component, const FGameplayTag& Tag, LogLevel)
			{
				CS_IS_GAMEPLAY_TAG_VALID(Tag)

				static FGameplayTagContainer Tags;
				Tags.Reset(Tags.Num());
				Tags.AddTag(Tag);

				return TrySafeActivateByExecutionTags(Context, Component, Tags, Log);
			}

			#pragma endregion Ability

			// Effect
			#pragma region
			
			void FLibrary::ApplyChecked(const FString& Context, UAbilitySystemComponent* From, UAbilitySystemComponent* To, const TArray<TSubclassOf<UGameplayEffect>>& Effects, TArray<FActiveGameplayEffectHandle>& OutHandles)
			{
				CS_IS_PENDING_KILL_CHECKED(From)
				CS_IS_PENDING_KILL_CHECKED(To)
				CS_IS_TARRAY_EMPTY_CHECKED(Effects, TSubclassOf<UGameplayEffect>)
				CS_IS_TARRAY_ANY_NULL_CHECKED(Effects, UGameplayEffect)

				for (const TSubclassOf<UGameplayEffect>& Effect : Effects)
				{
					UGameplayEffect* DOb = CS_SUBCLASS_OF_GET_DEFAULT_OBJ_CHECKED(Effect, UGameplayEffect);

					FActiveGameplayEffectHandle Handle = From->ApplyGameplayEffectToTarget(DOb, To);

					OutHandles.Add(Handle);
				}
			}

			void FLibrary::ApplyChecked(const FString& Context, UAbilitySystemComponent* From, UAbilitySystemComponent* To, const TArray<UGameplayEffect*>& Effects, TArray<FActiveGameplayEffectHandle>& OutHandles)
			{
				CS_IS_PENDING_KILL_CHECKED(From)
				CS_IS_PENDING_KILL_CHECKED(To)
				CS_IS_TARRAY_EMPTY_CHECKED(Effects, UGameplayEffect*)
				CS_IS_TARRAY_ANY_PENDING_KILL_CHECKED(Effects, UGameplayEffect)

				for (UGameplayEffect* Effect : Effects)
				{
					check(ObjectLibrary::IsDefaultObjectChecked(Context, Effect));

					FActiveGameplayEffectHandle Handle = From->ApplyGameplayEffectToTarget(Effect, To);

					OutHandles.Add(Handle);
				}
			}

			#pragma endregion Effect

			#undef LogLevel
			#undef ObjectLibrary
			#undef AbilitySystemLibrary
			#undef GameplayAbilityLibrary
		}
	}
}