// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_Viewport.h"

// Types
#include "CsMacro_Misc.h"
	// Common
#include "Library/CsLibrary_Viewport.h"
#include "Library/CsLibrary_Math.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Viewport)

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

#define USING_NS_CACHED using namespace NCsScriptLibraryViewport::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryViewport::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define ViewportLibrary NCsViewport::NLocal::NPlayer::FLibrary

bool UCsScriptLibrary_Viewport::DeprojectScreenToWorld(const FString& Context, const UObject* WorldContextObject, const FVector2f& ScreenPosition, FVector3f& OutWorldPosition, FVector3f& OutWorldDirection)
{
	CONDITIONAL_SET_CTXT(DeprojectScreenToWorld);

	return ViewportLibrary::SafeDeprojectScreenToWorld(Context, WorldContextObject, ScreenPosition, OutWorldPosition, OutWorldDirection);
}

FIntPoint UCsScriptLibrary_Viewport::GetSize(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(GetSize);

	return ViewportLibrary::GetSafeSize(Context, WorldContextObject);
}

bool UCsScriptLibrary_Viewport::GetScreenWorldIntersection(const FString& Context, const UObject* WorldContextObject, const FVector2f& ScreenPosition, const FPlane4f& Plane, FVector3f& OutIntersection)
{
	CONDITIONAL_SET_CTXT(GetScreenWorldIntersection);

	return ViewportLibrary::GetSafeScreenWorldIntersection(Context, WorldContextObject, ScreenPosition, Plane, OutIntersection);
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef ViewportLibrary