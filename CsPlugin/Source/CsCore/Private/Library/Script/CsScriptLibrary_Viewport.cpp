// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_Viewport.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
	// Common
#include "Library/CsLibrary_Viewport.h"
#include "Library/CsLibrary_Math.h"

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

bool UCsScriptLibrary_Viewport::DeprojectScreenToWorld(const FString& Context, const UObject* WorldContextObject, const FVector2f& ScreenPosition, FVector3f& OutWorldPosition, FVector3f& OutWorldDirection)
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

bool UCsScriptLibrary_Viewport::GetScreenWorldIntersection(const FString& Context, const UObject* WorldContextObject, const FVector2f& ScreenPosition, const FPlane4f& Plane, FVector3f& OutIntersection)
{
	using namespace NCsScriptLibraryViewport::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetScreenWorldIntersection : Context;

	typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

	return ViewportLibrary::GetSafeScreenWorldIntersection(Context, WorldContextObject, ScreenPosition, Plane, OutIntersection);
}