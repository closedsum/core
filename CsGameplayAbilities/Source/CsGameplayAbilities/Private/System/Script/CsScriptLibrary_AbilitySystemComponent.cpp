// Copyright Studio Sai, LLC. All Rights Reserved.
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
			// Ability
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
#define ASCLibrary NCsAbility::NSystem::NComponent::FLibrary

// Ability
#pragma region

bool UCsScriptLibrary_AbilitySystemComponent::TryActivateByExecutionTag(const FString& Context, UAbilitySystemComponent* Component, const FGameplayTag& Tag)
{
	CONDITIONAL_SET_CTXT(TryActivateByExecutionTag);

	return ASCLibrary::TrySafeActivateByExecutionTag(Ctxt, Component, Tag);
}

#pragma endregion Ability

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef ASCLibrary