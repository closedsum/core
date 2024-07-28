// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/CsLibrary_AnimSequence.h"

// Library
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Property.h"
// Blueprint
#include "Animation/AnimSequence.h"

namespace NCsAnimSequence
{
	#define LogLevel void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/

	// Load
	#pragma region

	UAnimSequence* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogLevel)
	{
		return CsObjectLibrary::SafeLoad<UAnimSequence>(Context, Path, Log);
	}

	UAnimSequence* FLibrary::SafeLoad(const FString& Context, const FString& Path, LogLevel)
	{
		return CsObjectLibrary::SafeLoad<UAnimSequence>(Context, Path, Log);
	}

	#pragma endregion Load

	// Get
	#pragma region
	
	UAnimSequence* FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, void(*Log)(const FString&) /*= &FCsLog::Warning*/)
	{
		return CsPropertyLibrary::GetObjectPropertyValueByPath<UAnimSequence>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
	}

	#pragma endregion Get

	#undef LogLevel
}