// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/Script/CsScriptLibrary_BlendSpace.h"

// Types
#include "CsMacro_Misc.h"
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

#define USING_NS_CACHED using namespace NCsScriptLibraryBlendSpace::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryBlendSpace::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define BlendSpaceLibrary NCsBlendSpace::FLibrary
#define BlendSpace1DLibrary NCsBlendSpace::N1D::FLibrary

// Load
#pragma region

UBlendSpace* UCsScriptLibrary_BlendSpace::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	CONDITIONAL_SET_CTXT(LoadBySoftObjectPath);

	return BlendSpaceLibrary::SafeLoad(Context, Path);
}

UBlendSpace* UCsScriptLibrary_BlendSpace::LoadByStringPath(const FString& Context, const FString& Path)
{
	CONDITIONAL_SET_CTXT(LoadByStringPath);

	return BlendSpaceLibrary::SafeLoad(Ctxt, Path);
}

UBlendSpace1D* UCsScriptLibrary_BlendSpace::Load1DBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	CONDITIONAL_SET_CTXT(Load1DBySoftObjectPath);

	return BlendSpace1DLibrary::SafeLoad(Context, Path);
}

UBlendSpace1D* UCsScriptLibrary_BlendSpace::Load1DByStringPath(const FString& Context, const FString& Path)
{
	CONDITIONAL_SET_CTXT(Load1DByStringPath);

	return BlendSpace1DLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load


// Get
#pragma region

UBlendSpace* UCsScriptLibrary_BlendSpace::GetByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetByPath);

	return BlendSpaceLibrary::GetSafe(Context, Object, Path, OutSuccess);
}

UBlendSpace1D* UCsScriptLibrary_BlendSpace::Get1DByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(Get1DByPath);

	return BlendSpace1DLibrary::GetSafe(Context, Object, Path, OutSuccess);
}

#pragma endregion Get

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef BlendSpaceLibrary
#undef BlendSpace1DLibrary