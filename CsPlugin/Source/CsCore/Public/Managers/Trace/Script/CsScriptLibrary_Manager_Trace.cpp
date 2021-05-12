// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Trace/Script/CsScriptLibrary_Manager_Trace.h"
#include "CsCore.h"

// Library
#include "Managers/Trace/CsLibrary_Manager_Trace.h"
// Managers
#include "Managers/Trace/CsManager_Trace.h"
// Actor
#include "GameFramework/Actor.h"

// Cached
#pragma region

namespace NCsScriptLibraryManagerTrace
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Trace, Trace);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Trace, LineTraceSingleByChannel);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_Trace::UCsScriptLibrary_Manager_Trace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsScriptLibrary_Manager_Trace::Trace(const FString& Context, const UObject* WorldContextObject, const FCsTraceRequest& Request, FCsTraceResponse& OutResponse)
{
	using namespace NCsScriptLibraryManagerTrace::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Trace : Context;

	if (!Request.IsValid(Ctxt))
		return;

	typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;

	if (UCsManager_Trace* Manager = TraceManagerLibrary::GetSafe(Ctxt, WorldContextObject))
	{
		typedef NCsTrace::NRequest::FRequest RequestType;
		typedef NCsTrace::NResponse::FResponse ResponseType;

		RequestType* RequestPtr = Manager->AllocateRequest();

		Request.CopyToRequestAsValue(RequestPtr);

		ResponseType* ResponsePtr = TraceManagerLibrary::SafeTrace(Ctxt, WorldContextObject, RequestPtr);

		if (ResponsePtr)
		{
			OutResponse.CopyFromResponse(ResponsePtr);
		}
	}
}

// Line
#pragma region

bool UCsScriptLibrary_Manager_Trace::LineTraceSingleByChannel(const FString& Context, UObject* WorldContextObject, const FVector& Start, const FVector& End, const TEnumAsByte<ECollisionChannel>& Channel, bool bTraceComplex, bool bIgnoreSelf, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit)
{
	using namespace NCsScriptLibraryManagerTrace::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LineTraceSingleByChannel : Context;

	typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;

	if (UCsManager_Trace* Manager = TraceManagerLibrary::GetSafe(Ctxt, WorldContextObject))
	{
		// Fill out Request
		typedef NCsTrace::NRequest::FRequest RequestType;

		RequestType* Request		  = Manager->AllocateRequest();
		Request->Start				  = Start;
		Request->End				  = End;
		Request->Channel			  = Channel;
		Request->Params.bTraceComplex = bTraceComplex;

		if (bIgnoreSelf)
		{
			if (AActor* Actor = Cast<AActor>(WorldContextObject))
				Request->Params.AddIgnoredActor(Actor);
		}

		Request->Params.AddIgnoredActors(ActorsToIgnore);

		// Check Response
		typedef NCsTrace::NResponse::FResponse ResponseType;

		if (ResponseType* Response = Manager->Trace(Request))
		{
			if (Response->bResult)
			{
				OutHit = Response->OutHits[CS_FIRST];
			}
			return Response->bResult;
		}
		return false;
	}
	return false;
}

#pragma endregion Line