// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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

	/**
	* NOTE: For scripts (i.e. Python) that don't handle const ref properly
	*/
	UFUNCTION(BlueprintCallable, Category = "CsGameplayAbilities|Library", meta = (AutoCreateRefTerm = "Context"))
	static TArray<UGameplayAbility*> GetActivatableAbilities_PrimaryInstance2(const FString& Context, const UAbilitySystemComponent* Component);

	UFUNCTION(BlueprintCallable, Category = "CsGameplayAbilities|Library", meta = (AutoCreateRefTerm = "Context,Tag"))
	static bool TryActivateByExecutionTag(const FString& Context, UAbilitySystemComponent* Component, const FGameplayTag& Tag);

#pragma endregion Ability
};