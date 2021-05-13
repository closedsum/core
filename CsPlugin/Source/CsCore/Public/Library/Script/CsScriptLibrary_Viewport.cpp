// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/Script/CsScriptLibrary_Viewport.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Viewport.h"

// Cached
#pragma region

namespace NCsScriptLibraryViewport
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Viewport, DeprojectScreenToWorld);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Viewport, GetSize);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Viewport, GetScreenWorldIntersection);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Viewport::UCsScriptLibrary_Viewport(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_Viewport::DeprojectScreenToWorld(const FString& Context, const UObject* WorldContextObject, const FVector2D& ScreenPosition, FVector& OutWorldPosition, FVector& OutWorldDirection)
{
	using namespace NCsScriptLibraryViewport::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::DeprojectScreenToWorld : Context;

	typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

	return ViewportLibrary::SafeDeprojectScreenToWorld(Context, WorldContextObject, ScreenPosition, OutWorldPosition, OutWorldDirection);
}

FIntPoint UCsScriptLibrary_Viewport::GetSize(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryViewport::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetSize : Context;

	typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

	return ViewportLibrary::GetSafeSize(Context, WorldContextObject);
}

bool UCsScriptLibrary_Viewport::GetScreenWorldIntersection(const FString& Context, const UObject* WorldContextObject, const FVector2D& ScreenPosition, const FPlane& Plane, FVector& OutIntersection)
{
	using namespace NCsScriptLibraryViewport::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetScreenWorldIntersection : Context;

	typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

	return ViewportLibrary::GetSafeScreenWorldIntersection(Context, WorldContextObject, ScreenPosition, Plane, OutIntersection);
}