// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_Texture.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Texture.h"

// Cached
#pragma region

namespace NCsScriptLibraryTexture
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Texture, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Texture, LoadByStringPath);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Texture::UCsScriptLibrary_Texture(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryTexture::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryTexture::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define TextureLibrary NCsTexture::FLibrary

// Load
#pragma region

UTexture* UCsScriptLibrary_Texture::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	CONDITIONAL_SET_CTXT(LoadBySoftObjectPath);

	return TextureLibrary::SafeLoad(Ctxt, Path);
}

UTexture* UCsScriptLibrary_Texture::LoadByStringPath(const FString& Context, const FString& Path)
{
	CONDITIONAL_SET_CTXT(LoadByStringPath);

	return TextureLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef TextureLibrary