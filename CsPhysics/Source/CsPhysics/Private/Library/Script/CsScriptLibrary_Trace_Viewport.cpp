// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_Trace_Viewport.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Trace/CsLibrary_Manager_Trace.h"
	// Common
#include "Library/CsLibrary_Trace_Viewport.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Trace_Viewport)

// Cached
#pragma region

namespace NCsScriptLibraryTraceViewport
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Trace_Viewport, Trace);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Trace_Viewport::UCsScriptLibrary_Trace_Viewport(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

using ViewportLibrary = NCsViewport::NLocal::NPlayer::NPhysics::FLibrary;
using RequestType = NCsTrace::NRequest::FRequest;
using ResponseType = NCsTrace::NResponse::FResponse;

bool UCsScriptLibrary_Trace_Viewport::Trace(const FString& Context, const UObject* WorldContextObject, const FVector2f& ScreenPosition, const FCsTraceRequest& Request, const float& Distance, FCsTraceResponse& OutResponse)
{
	using namespace NCsScriptLibraryTraceViewport::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Trace : Context;

	FCsTraceRequest* Req = const_cast<FCsTraceRequest*>(&Request);

	if (Req->Shape.IsLine() &&
		Req->Start == Req->End)
	{
		Req->End += FVector3f(0.0f, 0.0f, 1.0f);
	}

	if (!Request.IsValid(Ctxt))
		return false;

	RequestType* RequestPtr = CsTraceManagerLibrary::SafeAllocateRequest(Ctxt, WorldContextObject);

	if (!RequestPtr)
		return false;

	Request.CopyToRequestAsValue(RequestPtr);

	ResponseType* ResponsePtr = ViewportLibrary::SafeTrace(Ctxt, WorldContextObject, ScreenPosition, RequestPtr, Distance);

	if (ResponsePtr)
	{
		OutResponse.CopyFromResponse(ResponsePtr);
		return ResponsePtr->bResult;
	}

	CsTraceManagerLibrary::SafeDeallocateRequest(Ctxt, WorldContextObject, RequestPtr);
	return false;
}