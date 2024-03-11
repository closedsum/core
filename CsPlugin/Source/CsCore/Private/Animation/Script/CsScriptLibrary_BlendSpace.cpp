// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/Script/CsScriptLibrary_BlendSpace.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Animation/CsLibrary_BlendSpace.h"

// Cached
#pragma region

namespace NCsScriptLibraryBlendSpace
{
	namespace NCached
	{
		namespace Str
		{
			// Load
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_BlendSpace, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_BlendSpace, LoadByStringPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_BlendSpace, Load1DBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_BlendSpace, Load1DByStringPath);
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_BlendSpace, GetByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_BlendSpace, Get1DByPath);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_BlendSpace::UCsScriptLibrary_BlendSpace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define BlendSpaceLibrary NCsBlendSpace::FLibrary
#define BlendSpace1DLibrary NCsBlendSpace::N1D::FLibrary

// Load
#pragma region

UBlendSpace* UCsScriptLibrary_BlendSpace::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibraryBlendSpace::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadBySoftObjectPath : Context;

	return BlendSpaceLibrary::SafeLoad(Context, Path);
}

UBlendSpace* UCsScriptLibrary_BlendSpace::LoadByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryBlendSpace::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadByStringPath : Context;

	return BlendSpaceLibrary::SafeLoad(Ctxt, Path);
}

UBlendSpace1D* UCsScriptLibrary_BlendSpace::Load1DBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibraryBlendSpace::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Load1DBySoftObjectPath : Context;

	return BlendSpace1DLibrary::SafeLoad(Context, Path);
}

UBlendSpace1D* UCsScriptLibrary_BlendSpace::Load1DByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryBlendSpace::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Load1DByStringPath : Context;

	return BlendSpace1DLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load


// Get
#pragma region

UBlendSpace* UCsScriptLibrary_BlendSpace::GetByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	using namespace NCsScriptLibraryBlendSpace::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetByPath : Context;

	return BlendSpaceLibrary::GetSafe(Context, Object, Path, OutSuccess);
}

UBlendSpace1D* UCsScriptLibrary_BlendSpace::Get1DByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	using namespace NCsScriptLibraryBlendSpace::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Get1DByPath : Context;

	return BlendSpace1DLibrary::GetSafe(Context, Object, Path, OutSuccess);
}

#pragma endregion Get

#undef BlendSpaceLibrary
#undef BlendSpace1DLibrary