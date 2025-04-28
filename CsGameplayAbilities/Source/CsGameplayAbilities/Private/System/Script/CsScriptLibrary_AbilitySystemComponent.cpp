// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "System/Script/CsScriptLibrary_AbilitySystemComponent.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "System/CsLibrary_AbilitySystemComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_AbilitySystemComponent)

// Cached
#pragma region

namespace NCScriptLibraryAbilitySystemComponent
{
	namespace NCached
	{
		namespace Str
		{
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AbilitySystemComponent, Get);
			// Ability
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AbilitySystemComponent, GetActivatableAbilities_PrimaryInstance);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AbilitySystemComponent, GetActivatableAbilities_PrimaryInstance2);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AbilitySystemComponent, TryActivateByExecutionTag);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_AbilitySystemComponent::UCsScriptLibrary_AbilitySystemComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCScriptLibraryAbilitySystemComponent::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCScriptLibraryAbilitySystemComponent::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

// Get
#pragma region

UAbilitySystemComponent* UCsScriptLibrary_AbilitySystemComponent::Get(const FString& Context, const UObject* Object)
{
	CONDITIONAL_SET_CTXT(Get);

	return CsASCLibrary::GetSafe(Ctxt, Object);
}

#pragma endregion Get

// Ability
#pragma region

bool UCsScriptLibrary_AbilitySystemComponent::GetActivatableAbilities_PrimaryInstance(const FString& Context, const UAbilitySystemComponent* Component, TArray<UGameplayAbility*>& OutAbilities)
{
	CONDITIONAL_SET_CTXT(GetActivatableAbilities_PrimaryInstance);

	return CsASCLibrary::GetSafeActivatableAbilities_PrimaryInstance(Ctxt, Component, OutAbilities);
}

TArray<UGameplayAbility*> UCsScriptLibrary_AbilitySystemComponent::GetActivatableAbilities_PrimaryInstance2(const FString& Context, const UAbilitySystemComponent* Component)
{
	CONDITIONAL_SET_CTXT(GetActivatableAbilities_PrimaryInstance2);

	static TArray<UGameplayAbility*> Abilities;
	Abilities.Reset(Abilities.Max());

	CsASCLibrary::GetSafeActivatableAbilities_PrimaryInstance(Ctxt, Component, Abilities);
	return Abilities;
}

bool UCsScriptLibrary_AbilitySystemComponent::TryActivateByExecutionTag(const FString& Context, UAbilitySystemComponent* Component, const FGameplayTag& Tag)
{
	CONDITIONAL_SET_CTXT(TryActivateByExecutionTag);

	return CsASCLibrary::TrySafeActivateByExecutionTag(Ctxt, Component, Tag);
}

#pragma endregion Ability

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT