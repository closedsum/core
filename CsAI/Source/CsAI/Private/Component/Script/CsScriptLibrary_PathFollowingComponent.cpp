// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Component/Script/CsScriptLibrary_PathFollowingComponent.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Log
#include "Utility/CsAILog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_PathFollowingComponent)

// Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME(CsScriptLibrary_PathFollowingComponent)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_PathFollowingComponent, AbortMove)
CS_END_CACHED_FUNCTION_NAME

#pragma endregion Cached

UCsScriptLibrary_PathFollowingComponent::UCsScriptLibrary_PathFollowingComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_PathFollowingComponent::AbortMove(const FString& Context, UPathFollowingComponent* Component, UObject* Instigator, const int32& AbortFlags, const FAIRequestID& RequestID, const ECsPathFollowingVelocityMode& VelocityMode /*=ECsPathFollowingVelocityMode::Reset*/)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(AbortMove);

	void(*Log)(const FString&) = &NCsAI::FLog::Warning;

	CS_IS_PENDING_KILL2(Component)
	CS_IS_PENDING_KILL2(Instigator)

	Component->AbortMove(*Instigator, AbortFlags, RequestID, (EPathFollowingVelocityMode)VelocityMode);
	return true;
}