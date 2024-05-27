// Copyright Studio Sai, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "GameplayTagContainer.h"

#include "CsScriptLibrary_AbilitySystemComponent.generated.h"

class UAbilitySystemComponent;

UCLASS()
class CSGAMEPLAYABILITIES_API UCsScriptLibrary_AbilitySystemComponent : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Ability
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "CsGameplayAbilities|Library", meta = (AutoCreateRefTerm = "Tag"))
	static bool TryActivateByExecutionTag(const FString& Context, UAbilitySystemComponent* Component, const FGameplayTag& Tag);

#pragma endregion Ability
};