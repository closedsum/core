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
	#define LogWarning void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/

	// Load
	#pragma region

	UTexture* FLibrary::LoadChecked(const FString& Context, const FSoftObjectPath& Path)
	{
		return CsObjectLibrary::LoadChecked<UTexture>(Context, Path);
	}

	UTexture* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogWarning)
	{
		return CsObjectLibrary::SafeLoad<UTexture>(Context, Path, Log);
	}

	UTexture* FLibrary::LoadChecked(const FString& Context, const FString& Path)
	{
		return CsObjectLibrary::LoadChecked<UTexture>(Context, Path);
	}

	UTexture* FLibrary::SafeLoad(const FString& Context, const FString& Path, LogWarning)
	{
		return CsObjectLibrary::SafeLoad<UTexture>(Context, Path, Log);
	}

	#pragma endregion Load

	#undef LogWarning
}