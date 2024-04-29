// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_Component.h"
#include "CsCoreLibrary.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Components
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Cached
#pragma region

namespace NCsScriptLibraryComponent
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Component, CreateAndRegister_CameraComponent);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Component, CreateAndRegister_SpringArmComponent);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Component::UCsScriptLibrary_Component(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryComponent::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryComponent::NCached; \
	const FString& Ctxt = Str::__FunctionName

bool UCsScriptLibrary_Component::CreateAndRegister_IsValid(const FString& Context, const UObject* Outer, const FName& Name, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
{
	CS_IS_PENDING_KILL(Outer)
	CS_IS_NAME_NONE(Name)
	return true;
}

UCameraComponent* UCsScriptLibrary_Component::CreateAndRegister_CameraComponent(const FString& Context, UObject* Outer, const FName& Name)
{
	CONDITIONAL_SET_CTXT(CreateAndRegister_CameraComponent);

	if (!CreateAndRegister_IsValid(Ctxt, Outer, Name))
		return nullptr;

	UCameraComponent* Component = NewObject<UCameraComponent>(Outer, Name);

	if (!Component)
	{
		UE_LOG(LogCsCoreLibrary, Warning, TEXT("%s: Failed to create Component of type: UCameraComponent with Name: for Outer: %s."), *Ctxt, *(Outer->GetName()), *(Name.ToString()));
		return nullptr;
	}
	Component->RegisterComponent();

	return Component;
}

USpringArmComponent* UCsScriptLibrary_Component::CreateAndRegister_SpringArmComponent(const FString& Context, UObject* Outer, const FName& Name)
{
	CONDITIONAL_SET_CTXT(CreateAndRegister_SpringArmComponent);

	if (!CreateAndRegister_IsValid(Ctxt, Outer, Name))
		return nullptr;

	USpringArmComponent* Component = NewObject<USpringArmComponent>(Outer, Name);

	if (!Component)
	{
		UE_LOG(LogCsCoreLibrary, Warning, TEXT("%s: Failed to create Component of type: USpringArmComponent with Name: for Outer: %s."), *Ctxt, *(Outer->GetName()), *(Name.ToString()));
		return nullptr;
	}
	Component->RegisterComponent();

	return Component;
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT