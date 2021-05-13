// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/Script/CsScriptLibrary_Mouse.h"
#include "CsCore.h"

// Library
#include "Managers/Input/CsLibrary_Input.h"

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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Mouse, GetWorldIntersection);
		}
	}
}

UCsScriptLibrary_Mouse::UCsScriptLibrary_Mouse(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

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

void UCsScriptLibrary_Mouse::GetPosition(const FString& Context, const UObject* WorldContextObject, FIntPoint& OutPosition)
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetPosition : Context;

	typedef NCsInput::NMouse::FLibrary MouseLibrary;

	MouseLibrary::GetSafePosition(Context, WorldContextObject, OutPosition);
}

void UCsScriptLibrary_Mouse::SetPosition(const FString& Context, const UObject* WorldContextObject, const int32& X, const int32& Y)
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetPosition : Context;

	typedef NCsInput::NMouse::FLibrary MouseLibrary;

	MouseLibrary::SetSafePosition(Context, WorldContextObject, X, Y);
}

bool UCsScriptLibrary_Mouse::GetWorldIntersection(const FString& Context, const UObject* WorldContextObject, const FPlane& Plane, FVector& OutIntersection)
{
	using namespace NCsScriptLibraryMouse::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetWorldIntersection : Context;

	typedef NCsInput::NMouse::FLibrary MouseLibrary;

	return MouseLibrary::GetSafeWorldIntersection(Context, WorldContextObject, Plane, OutIntersection);
}