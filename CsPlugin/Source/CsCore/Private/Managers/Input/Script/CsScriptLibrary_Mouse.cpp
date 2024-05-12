// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/Script/CsScriptLibrary_Mouse.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Input/CsLibrary_Input.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Mouse)

namespace NCsScriptLibraryMouse
{
	namespace NCached
	{
		namespace Str
		{
			// Show / Hide
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, IsShowingCursor);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, IsShowingCursorChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, ShowCursor);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, ShowCursorChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, HideCursor);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, HideCursorChecked);
			// Get / Set
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, GetPosition);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, SetPosition);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, SetCenterOfViewport);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, RefreshPosition);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, RefreshPositionChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, GetWorldIntersection);
		}
	}
}

UCsScriptLibrary_Mouse::UCsScriptLibrary_Mouse(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define LogError &FCsLog::Error
#define MouseLibrary NCsInput::NMouse::FLibrary

// Show / Hide
#pragma region

bool UCsScriptLibrary_Mouse::IsShowingCursor(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsShowingCursor : Context;

	return MouseLibrary::SafeIsShowingCursor(Ctxt, WorldContextObject);
}

bool UCsScriptLibrary_Mouse::IsShowingCursorChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsShowingCursorChecked : Context;

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(MouseLibrary::IsShowingCursorChecked(Ctxt, WorldContextObject), MouseLibrary::SafeIsShowingCursor(Ctxt, WorldContextObject, OutSuccess, LogError));
}

bool UCsScriptLibrary_Mouse::ShowCursor(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ShowCursor : Context;

	return MouseLibrary::SafeShowCursor(Ctxt, WorldContextObject);
}

void UCsScriptLibrary_Mouse::ShowCursorChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ShowCursor : Context;

	OutSuccess = true;
	CS_SCRIPT_CHECKED(MouseLibrary::ShowCursorChecked(Ctxt, WorldContextObject), MouseLibrary::SafeShowCursor(Ctxt, WorldContextObject, OutSuccess, LogError));
}

bool UCsScriptLibrary_Mouse::HideCursor(const FString& Context, const UObject* WorldContextObject) 
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::HideCursor : Context;

	return MouseLibrary::SafeHideCursor(Ctxt, WorldContextObject);
}

void UCsScriptLibrary_Mouse::HideCursorChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess) 
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::HideCursorChecked : Context;

	OutSuccess = true;
	CS_SCRIPT_CHECKED(MouseLibrary::HideCursorChecked(Ctxt, WorldContextObject), MouseLibrary::SafeHideCursor(Ctxt, WorldContextObject, OutSuccess, LogError));
}

#pragma endregion Show / Hide

// Get / Set
#pragma region

bool UCsScriptLibrary_Mouse::GetPosition(const FString& Context, const UObject* WorldContextObject, FIntPoint& OutPosition)
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetPosition : Context;

	return MouseLibrary::GetSafePosition(Ctxt, WorldContextObject, OutPosition);
}

bool UCsScriptLibrary_Mouse::SetPosition(const FString& Context, const UObject* WorldContextObject, const int32& X, const int32& Y)
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetPosition : Context;

	return MouseLibrary::SetSafePosition(Ctxt, WorldContextObject, X, Y);
}

bool UCsScriptLibrary_Mouse::SetCenterOfViewport(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetCenterOfViewport : Context;

	return MouseLibrary::SetSafeCenterOfViewport(Ctxt, WorldContextObject);
}

bool UCsScriptLibrary_Mouse::RefreshPosition(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::RefreshPosition : Context;

	return MouseLibrary::SafeRefreshPosition(Ctxt, WorldContextObject);
}

void UCsScriptLibrary_Mouse::RefreshPositionChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::RefreshPositionChecked : Context;

	OutSuccess = true;
	CS_SCRIPT_CHECKED(MouseLibrary::RefreshPositionChecked(Ctxt, WorldContextObject), MouseLibrary::SafeRefreshPosition(Ctxt, WorldContextObject, OutSuccess, LogError));
}

#pragma endregion Get / Set

// Trace
#pragma region

bool UCsScriptLibrary_Mouse::GetWorldIntersection(const FString& Context, const UObject* WorldContextObject, const FPlane4f& Plane, FVector3f& OutIntersection)
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetWorldIntersection : Context;

	return MouseLibrary::GetSafeWorldIntersection(Ctxt, WorldContextObject, Plane, OutIntersection);
}

#pragma endregion Trace

#undef LogError
#undef MouseLibrary