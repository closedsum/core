// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/CsLibrary_AnimSequence.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Object.h"
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