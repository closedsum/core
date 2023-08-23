// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_BlendSpace, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_BlendSpace, LoadByStringPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_BlendSpace, Load1DBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_BlendSpace, Load1DByStringPath);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_BlendSpace::UCsScriptLibrary_BlendSpace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Load
#pragma region

UBlendSpace* UCsScriptLibrary_BlendSpace::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibraryBlendSpace::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadBySoftObjectPath : Context;

	typedef NCsBlendSpace::FLibrary BlendSpaceLibrary;

	return BlendSpaceLibrary::SafeLoad(Context, Path);
}

UBlendSpace* UCsScriptLibrary_BlendSpace::LoadByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryBlendSpace::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadByStringPath : Context;

	typedef NCsBlendSpace::FLibrary BlendSpaceLibrary;

	return BlendSpaceLibrary::SafeLoad(Ctxt, Path);
}

UBlendSpace1D* UCsScriptLibrary_BlendSpace::Load1DBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibraryBlendSpace::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Load1DBySoftObjectPath : Context;

	typedef NCsBlendSpace::N1D::FLibrary BlendSpaceLibrary;

	return BlendSpaceLibrary::SafeLoad(Context, Path);
}

UBlendSpace1D* UCsScriptLibrary_BlendSpace::Load1DByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryBlendSpace::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Load1DByStringPath : Context;

	typedef NCsBlendSpace::N1D::FLibrary BlendSpaceLibrary;

	return BlendSpaceLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load