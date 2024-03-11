// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_Component.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
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

bool UCsScriptLibrary_Component::CreateAndRegister_IsValid(const FString& Context, const UObject* Outer, const FName& Name, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
{
	CS_IS_PENDING_KILL(Outer)
	CS_IS_NAME_NONE(Name)
	return true;
}

UCameraComponent* UCsScriptLibrary_Component::CreateAndRegister_CameraComponent(const FString& Context, UObject* Outer, const FName& Name)
{
	using namespace NCsScriptLibraryComponent::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::CreateAndRegister_CameraComponent : Context;

	if (!CreateAndRegister_IsValid(Ctxt, Outer, Name))
		return nullptr;

	UCameraComponent* Component = NewObject<UCameraComponent>(Outer, Name);

	if (!Component)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Failed to create Component of type: UCameraComponent with Name: for Outer: %s."), *Ctxt, *(Outer->GetName()), *(Name.ToString()));
		return nullptr;
	}
	Component->RegisterComponent();

	return Component;
}

USpringArmComponent* UCsScriptLibrary_Component::CreateAndRegister_SpringArmComponent(const FString& Context, UObject* Outer, const FName& Name)
{
	using namespace NCsScriptLibraryComponent::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::CreateAndRegister_SpringArmComponent : Context;

	if (!CreateAndRegister_IsValid(Ctxt, Outer, Name))
		return nullptr;

	USpringArmComponent* Component = NewObject<USpringArmComponent>(Outer, Name);

	if (!Component)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Failed to create Component of type: USpringArmComponent with Name: for Outer: %s."), *Ctxt, *(Outer->GetName()), *(Name.ToString()));
		return nullptr;
	}
	Component->RegisterComponent();

	return Component;
}