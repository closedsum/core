// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Controller/Script/CsScriptLibrary_AI_Controller.h"
#include "CsAI.h"

// Types
#include "Types/CsTypes_Macro.h"
// AI
#include "AIController.h"

// Cached
#pragma region

namespace NCsScriptLibraryAIController
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, MoveTo);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, GetDefaultNavigationFilterClass);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_AI_Controller::UCsScriptLibrary_AI_Controller(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FCsPathFollowingRequestResult UCsScriptLibrary_AI_Controller::MoveTo(const FString& Context, AAIController* Controller, const FCsAIMoveRequest& MoveRequest)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::MoveTo : Context;

	if (!Controller)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Controller is NULL."), *Ctxt);
		return FCsPathFollowingRequestResult();
	}

	// TODO: Check Is Valid
	FAIMoveRequest Request;
	MoveRequest.CopyTo(Request);

	FPathFollowingRequestResult Result = Controller->MoveTo(Request);

	FCsPathFollowingRequestResult RequestResult;
	RequestResult.MoveId = Result.MoveId;
	RequestResult.Code   = Result.Code;

	return RequestResult;
}

TSubclassOf<UNavigationQueryFilter> UCsScriptLibrary_AI_Controller::GetDefaultNavigationFilterClass(const FString& Context, AAIController* Controller)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetDefaultNavigationFilterClass : Context;

	if (!Controller)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Controller is NULL."), *Ctxt);
		return nullptr;
	}
	return Controller->GetDefaultNavigationFilterClass();
}