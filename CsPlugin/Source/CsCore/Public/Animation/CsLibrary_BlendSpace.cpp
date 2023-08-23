// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/CsLibrary_BlendSpace.h"
#include "CsCore.h"

// Library
#include "Object/CsLibrary_Object.h"
// Blueprint
#include "Animation/BlendSpace1D.h"

namespace NCsBlendSpace
{
	// Load
	#pragma region

	UBlendSpace* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<UBlendSpace>(Context, Path, Log);
	}

	UBlendSpace* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<UBlendSpace>(Context, Path, Log);
	}

	#pragma endregion Load

	namespace N1D
	{
		// Load
		#pragma region

		UBlendSpace1D* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsObject::FLibrary ObjectLibrary;

			return ObjectLibrary::SafeLoad<UBlendSpace1D>(Context, Path, Log);
		}

		UBlendSpace1D* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsObject::FLibrary ObjectLibrary;

			return ObjectLibrary::SafeLoad<UBlendSpace1D>(Context, Path, Log);
		}

		#pragma endregion Load
	}
}