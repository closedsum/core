// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_Texture.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
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

// Load
#pragma region

UTexture* UCsScriptLibrary_Texture::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibraryTexture::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadBySoftObjectPath : Context;

	typedef NCsTexture::FLibrary TextureLibrary;

	return TextureLibrary::SafeLoad(Ctxt, Path);
}

UTexture* UCsScriptLibrary_Texture::LoadByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryTexture::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadByStringPath : Context;

	typedef NCsTexture::FLibrary TextureLibrary;

	return TextureLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load