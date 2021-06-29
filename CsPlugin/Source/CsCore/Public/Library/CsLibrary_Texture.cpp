// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Texture.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Object.h"
// Mesh
#include "Engine/Texture.h"

namespace NCsTexture
{
	// Load
	#pragma region

	UTexture* FLibrary::LoadChecked(const FString& Context, const FSoftObjectPath& Path)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::LoadChecked<UTexture>(Context, Path);
	}

	UTexture* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<UTexture>(Context, Path, Log);
	}

	UTexture* FLibrary::LoadChecked(const FString& Context, const FString& Path)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::LoadChecked<UTexture>(Context, Path);
	}

	UTexture* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<UTexture>(Context, Path, Log);
	}

	#pragma endregion Load
}