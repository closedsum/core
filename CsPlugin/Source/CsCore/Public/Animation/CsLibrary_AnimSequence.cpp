// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/CsLibrary_AnimSequence.h"
#include "CsCore.h"

// Library
#include "Object/CsLibrary_Object.h"
// Blueprint
#include "Animation/AnimSequence.h"

namespace NCsAnimSequence
{
	// Load
	#pragma region

	UAnimSequence* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<UAnimSequence>(Context, Path, Log);
	}

	UAnimSequence* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<UAnimSequence>(Context, Path, Log);
	}

	#pragma endregion Load
}