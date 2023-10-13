// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/CsLibrary_BlendSpace.h"
#include "CsCore.h"

// Library
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Property.h"
// Blueprint
#include "Animation/BlendSpace1D.h"

namespace NCsBlendSpace
{
	// Load
	#pragma region

	#define ObjectLibrary NCsObject::FLibrary

	UBlendSpace* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		return ObjectLibrary::SafeLoad<UBlendSpace>(Context, Path, Log);
	}

	UBlendSpace* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		return ObjectLibrary::SafeLoad<UBlendSpace>(Context, Path, Log);
	}

	#undef ObjectLibrary

	#pragma endregion Load

	// Get
	#pragma region
	
	UBlendSpace* FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsProperty::FLibrary PropertyLibrary;

		return PropertyLibrary::GetObjectPropertyValueByPath<UBlendSpace>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
	}

	#pragma endregion Get

	namespace N1D
	{
		// Load
		#pragma region

		#define ObjectLibrary NCsObject::FLibrary

		UBlendSpace1D* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			return ObjectLibrary::SafeLoad<UBlendSpace1D>(Context, Path, Log);
		}

		UBlendSpace1D* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			return ObjectLibrary::SafeLoad<UBlendSpace1D>(Context, Path, Log);
		}

		#undef ObjectLibrary

		#pragma endregion Load

		// Get
		#pragma region
	
		UBlendSpace1D* FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsProperty::FLibrary PropertyLibrary;

			return PropertyLibrary::GetObjectPropertyValueByPath<UBlendSpace1D>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
		}

		#pragma endregion Get
	}
}