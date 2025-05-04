// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Component/Script/CsScriptLibrary_PathFollowingComponent.h"
#include "CsAI.h"

// Types
#include "CsMacro_Misc.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_PathFollowingComponent)

// Cached
#pragma region

namespace NCsScriptLibraryPathFollowComponent
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PathFollowingComponent, AbortMove);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_PathFollowingComponent::UCsScriptLibrary_PathFollowingComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_PathFollowingComponent::AbortMove(const FString& Context, UPathFollowingComponent* Component, UObject* Instigator, const int32& AbortFlags, const FAIRequestID& RequestID, const ECsPathFollowingVelocityMode& VelocityMode /*=ECsPathFollowingVelocityMode::Reset*/)
{
	using namespace NCsScriptLibraryPathFollowComponent::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AbortMove : Context;

	if (!Component)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Component is NULL."), *Ctxt);
		return false;
	}

	if (!Instigator)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Instigator is NULL."), *Ctxt);
		return false;
	}

	Component->AbortMove(*Instigator, AbortFlags, RequestID, (EPathFollowingVelocityMode)VelocityMode);
	return true;
}