// Copyright Studio Sai, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "GameplayTagContainer.h"
#include "Engine/HitResult.h" // TEMP

#include "CsScriptLibrary_AbilitySystemComponent.generated.h"

class UAbilitySystemComponent;
class AActor; // TEMP

UCLASS()
class CSGAMEPLAYABILITIES_API UCsScriptLibrary_AbilitySystemComponent : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Get
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsGameplayAbilities|Library", meta = (AutoCreateRefTerm = "Context"))
	static UAbilitySystemComponent* Get(const FString& Context, const UObject* Object);

#pragma endregion Get

// Ability
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "CsGameplayAbilities|Library", meta = (AutoCreateRefTerm = "Context"))
	static bool GetActivatableAbilities_PrimaryInstance(const FString& Context, const UAbilitySystemComponent* Component, TArray<UGameplayAbility*>& OutAbilities);

	UFUNCTION(BlueprintCallable, Category = "CsGameplayAbilities|Library", meta = (AutoCreateRefTerm = "Context,Tag"))
	static bool TryActivateByExecutionTag(const FString& Context, UAbilitySystemComponent* Component, const FGameplayTag& Tag);

#pragma endregion Ability

// TEMP

	UFUNCTION(BlueprintPure, Category = "CsGameplayAbilities|Library")
	static AActor* GetActor(const FHitResult& Hit);
};