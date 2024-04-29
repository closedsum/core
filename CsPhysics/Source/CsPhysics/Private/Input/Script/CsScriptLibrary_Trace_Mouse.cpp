// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Input/Script/CsScriptLibrary_Trace_Mouse.h"
#include "CsPhysics.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Input/CsLibrary_Trace_Input.h"
#include "Managers/Trace/CsLibrary_Manager_Trace.h"

namespace NCsScriptLibraryTraceMouse
{
	namespace NCached
	{
		namespace Str
		{
			// Trace
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Trace_Mouse, Trace);
		}
	}
}

UCsScriptLibrary_Trace_Mouse::UCsScriptLibrary_Trace_Mouse(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define LogError &FCsLog::Error
#define MouseLibrary NCsInput::NMouse::NPhysics::FLibrary

// Trace
#pragma region

bool UCsScriptLibrary_Trace_Mouse::Trace(const FString& Context, const UObject* WorldContextObject, const FCsTraceRequest& Request, const float& Distance, FCsTraceResponse& OutResponse)
{
	using namespace NCsScriptLibraryTraceMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Trace : Context;

	FCsTraceRequest* Req = const_cast<FCsTraceRequest*>(&Request);

	if (Req->Shape.IsLine() &&
		Req->Start == Req->End)
	{
		Req->End += FVector3f(0.0f, 0.0f, 1.0f);
	}

	if (!Request.IsValid(Ctxt))
		return false;

	typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;
	typedef NCsTrace::NRequest::FRequest RequestType;

	RequestType* RequestPtr = TraceManagerLibrary::SafeAllocateRequest(Ctxt, WorldContextObject);

	if (!RequestPtr)
		return false;

	Request.CopyToRequestAsValue(RequestPtr);

	typedef NCsTrace::NResponse::FResponse ResponseType;

	ResponseType* ResponsePtr = MouseLibrary::SafeTrace(Ctxt, WorldContextObject, RequestPtr, Distance);

	if (ResponsePtr)
	{
		OutResponse.CopyFromResponse(ResponsePtr);
		return ResponsePtr->bResult;
	}

	TraceManagerLibrary::SafeDeallocateRequest(Ctxt, WorldContextObject, RequestPtr);
	return false;
}

#pragma endregion Trace

#undef LogError
#undef MouseLibrary