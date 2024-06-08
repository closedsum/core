// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_SceneComponent.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_SceneComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_SceneComponent)

// Cached
#pragma region

namespace NCsScriptLibrarySceneComponent
{
	namespace NCached
	{
		namespace Str
		{
				// Attach
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_SceneComponent, AttachToComponent_KeepRelativeTransform);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_SceneComponent, AttachToComponent_KeepWorldTransform);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_SceneComponent, AttachToComponent_SnapToTargetNotIncludingScale);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_SceneComponent, AttachToComponent_SnapToTargetIncludingScale);
				// Detach
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_SceneComponent, DetachFromComponent_KeepRelativeTransform);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_SceneComponent, DetachFromComponent_KeepWorldTransform);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_SceneComponent::UCsScriptLibrary_SceneComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibrarySceneComponent::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibrarySceneComponent::NCached; \
	const FString& Ctxt = Str::__FunctionName
#define SceneComponentLibrary NCsSceneComponent::FLibrary

// Attach / Detach
#pragma region

	// Attach
#pragma region

bool UCsScriptLibrary_SceneComponent::AttachToComponent_KeepRelativeTransform(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket /*=NAME_None*/)
{
	CONDITIONAL_SET_CTXT(AttachToComponent_KeepRelativeTransform);

	return SceneComponentLibrary::SafeAttach_KeepRelativeTransform(Ctxt, Child, Parent, Socket);
}

bool UCsScriptLibrary_SceneComponent::AttachToComponent_KeepWorldTransform(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket /*=NAME_None*/)
{
	CONDITIONAL_SET_CTXT(AttachToComponent_KeepWorldTransform);

	return SceneComponentLibrary::SafeAttach_KeepWorldTransform(Ctxt, Child, Parent, Socket);
}

bool UCsScriptLibrary_SceneComponent::AttachToComponent_SnapToTargetNotIncludingScale(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket /*=NAME_None*/)
{
	CONDITIONAL_SET_CTXT(AttachToComponent_SnapToTargetNotIncludingScale);

	return SceneComponentLibrary::SafeAttach_SnapToTargetNotIncludingScale(Ctxt, Child, Parent, Socket);
}

bool UCsScriptLibrary_SceneComponent::AttachToComponent_SnapToTargetIncludingScale(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket /*=NAME_None*/)
{
	CONDITIONAL_SET_CTXT(AttachToComponent_SnapToTargetIncludingScale);

	return SceneComponentLibrary::SafeAttach_SnapToTargetIncludingScale(Ctxt, Child, Parent, Socket);
}

#pragma endregion Attach

	// Detach
#pragma region

bool UCsScriptLibrary_SceneComponent::DetachFromComponent_KeepRelativeTransform(const FString& Context, USceneComponent* Component)
{
	CONDITIONAL_SET_CTXT(DetachFromComponent_KeepRelativeTransform);

	return SceneComponentLibrary::SafeDetach_KeepRelativeTransform(Ctxt, Component);
}

bool UCsScriptLibrary_SceneComponent::DetachFromComponent_KeepWorldTransform(const FString& Context, USceneComponent* Component)
{
	CONDITIONAL_SET_CTXT(DetachFromComponent_KeepWorldTransform);

	return SceneComponentLibrary::SafeDetach_KeepWorldTransform(Ctxt, Component);
}

#pragma endregion Detach

#pragma endregion Attach / Detach

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef SceneComponentLibrary