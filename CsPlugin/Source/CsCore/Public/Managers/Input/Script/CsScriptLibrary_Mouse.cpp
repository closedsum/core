// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/Script/CsScriptLibrary_Mouse.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Managers/Input/CsLibrary_Input.h"
#include "Managers/Trace/CsLibrary_Manager_Trace.h"

namespace NCsScriptLibraryMouse
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, IsShowingCursor);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, ShowCursor);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, HideCursor);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, GetPosition);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, SetPosition);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, SetCenterOfViewport);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, GetWorldIntersection);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, Trace);
		}
	}
}

UCsScriptLibrary_Mouse::UCsScriptLibrary_Mouse(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Show / Hide
#pragma region

bool UCsScriptLibrary_Mouse::IsShowingCursor(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsShowingCursor : Context;

	typedef NCsInput::NMouse::FLibrary MouseLibrary;

	return MouseLibrary::SafeIsShowingCursor(Ctxt, WorldContextObject);
}

void UCsScriptLibrary_Mouse::ShowCursor(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ShowCursor : Context;

	typedef NCsInput::NMouse::FLibrary MouseLibrary;

	MouseLibrary::SafeShowCursor(Context, WorldContextObject);
}

void UCsScriptLibrary_Mouse::HideCursor(const FString& Context, const UObject* WorldContextObject) 
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::HideCursor : Context;

	typedef NCsInput::NMouse::FLibrary MouseLibrary;

	MouseLibrary::SafeHideCursor(Context, WorldContextObject);
}

#pragma endregion Show / Hide

// Get / Set
#pragma region

bool UCsScriptLibrary_Mouse::GetPosition(const FString& Context, const UObject* WorldContextObject, FIntPoint& OutPosition)
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetPosition : Context;

	typedef NCsInput::NMouse::FLibrary MouseLibrary;

	return MouseLibrary::GetSafePosition(Context, WorldContextObject, OutPosition);
}

bool UCsScriptLibrary_Mouse::SetPosition(const FString& Context, const UObject* WorldContextObject, const int32& X, const int32& Y)
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetPosition : Context;

	typedef NCsInput::NMouse::FLibrary MouseLibrary;

	return MouseLibrary::SetSafePosition(Context, WorldContextObject, X, Y);
}

bool UCsScriptLibrary_Mouse::SetCenterOfViewport(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetCenterOfViewport : Context;

	typedef NCsInput::NMouse::FLibrary MouseLibrary;

	return MouseLibrary::SetSafeCenterOfViewport(Context, WorldContextObject);
}

#pragma endregion Get / Set

// Trace
#pragma region

bool UCsScriptLibrary_Mouse::GetWorldIntersection(const FString& Context, const UObject* WorldContextObject, const FPlane& Plane, FVector& OutIntersection)
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetWorldIntersection : Context;

	typedef NCsInput::NMouse::FLibrary MouseLibrary;

	return MouseLibrary::GetSafeWorldIntersection(Context, WorldContextObject, Plane, OutIntersection);
}

bool UCsScriptLibrary_Mouse::Trace(const FString& Context, const UObject* WorldContextObject, const FCsTraceRequest& Request, const float& Distance, FCsTraceResponse& OutResponse)
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Trace : Context;

	FCsTraceRequest* Req = const_cast<FCsTraceRequest*>(&Request);

	if (Req->Shape.IsLine() &&
		Req->Start == Req->End)
	{
		Req->End += FVector(0.0f, 0.0f, 1.0f);
	}

	if (!Request.IsValid(Ctxt))
		return false;

	typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;
	typedef NCsTrace::NRequest::FRequest RequestType;

	RequestType* RequestPtr = TraceManagerLibrary::SafeAllocateRequest(Ctxt, WorldContextObject);

	if (!RequestPtr)
		return false;

	Request.CopyToRequestAsValue(RequestPtr);

	typedef NCsInput::NMouse::FLibrary MouseLibrary;
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