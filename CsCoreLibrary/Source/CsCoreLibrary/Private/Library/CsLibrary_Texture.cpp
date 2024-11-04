// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_Texture.h"

// Library
#include "Object/CsLibrary_Object.h"
// Mesh
#include "Engine/Texture.h"

namespace NCsTexture
{
	using LogClassType = NCsCore::NLibrary::FLog;

	CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

	// Load
	#pragma region

	UTexture* FLibrary::LoadChecked(const FString& Context, const FSoftObjectPath& Path)
	{
		return CsObjectLibrary::LoadChecked<UTexture>(Context, Path);
	}

	UTexture* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		return CsObjectLibrary::SafeLoad<UTexture>(Context, Path, Log);
	}

	UTexture* FLibrary::LoadChecked(const FString& Context, const FString& Path)
	{
		return CsObjectLibrary::LoadChecked<UTexture>(Context, Path);
	}

	UTexture* FLibrary::SafeLoad(const FString& Context, const FString& Path, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		return CsObjectLibrary::SafeLoad<UTexture>(Context, Path, Log);
	}

	#pragma endregion Load
}