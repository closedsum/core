// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/CsLibrary_BlendSpace.h"

// Library
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Property.h"
// Blueprint
#include "Animation/BlendSpace1D.h"

namespace NCsBlendSpace
{
	#define LogLevel void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/
	#define ObjectLibrary NCsObject::FLibrary

	// Load
	#pragma region

	UBlendSpace* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogLevel)
	{
		return ObjectLibrary::SafeLoad<UBlendSpace>(Context, Path, Log);
	}

	UBlendSpace* FLibrary::SafeLoad(const FString& Context, const FString& Path, LogLevel)
	{
		return ObjectLibrary::SafeLoad<UBlendSpace>(Context, Path, Log);
	}

	#pragma endregion Load

	// Get
	#pragma region
	
	UBlendSpace* FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, LogLevel)
	{
		typedef NCsProperty::FLibrary PropertyLibrary;

		return PropertyLibrary::GetObjectPropertyValueByPath<UBlendSpace>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
	}

	#pragma endregion Get

	#undef LogLevel
	#undef ObjectLibrary

	namespace N1D
	{
		#define LogLevel void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/
		#define ObjectLibrary NCsObject::FLibrary

		// Load
		#pragma region

		UBlendSpace1D* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogLevel)
		{
			return ObjectLibrary::SafeLoad<UBlendSpace1D>(Context, Path, Log);
		}

		UBlendSpace1D* FLibrary::SafeLoad(const FString& Context, const FString& Path, LogLevel)
		{
			return ObjectLibrary::SafeLoad<UBlendSpace1D>(Context, Path, Log);
		}

		#pragma endregion Load

		// Get
		#pragma region
	
		UBlendSpace1D* FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, LogLevel)
		{
			typedef NCsProperty::FLibrary PropertyLibrary;

			return PropertyLibrary::GetObjectPropertyValueByPath<UBlendSpace1D>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
		}

		#pragma endregion Get

		#undef LogLevel
		#undef ObjectLibrary
	}
}