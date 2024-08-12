// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_Class.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"

namespace NCsClass
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				const FString _C = TEXT("_C");
			}
		}
	}

	#define LogLevel void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/

	// Load
	#pragma region

	UClass* FLibrary::LoadChecked(const FString& Context, const FSoftObjectPath& Path)
	{
		// Check Path is Valid
		CS_IS_SOFT_OBJECT_PATH_VALID_CHECKED(Path)

		UClass* Class = Cast<UClass>(Path.TryLoad());

		checkf(Class, TEXT("%s: Failed to load Class at Path: %s."), *Context, *(Path.ToString()));
		return Class;
	}

	UClass* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogLevel)
	{
		// Check Path is Valid
		CS_IS_SOFT_OBJECT_PATH_VALID_RET_NULL(Path)

		UClass* Class = Cast<UClass>(Path.TryLoad());

		if (!Class)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to load Class at Path: %s."), *Context, *(Path.ToString())));
			return nullptr;
		}
		return Class;
	}

	UClass* FLibrary::LoadChecked(const FString& Context, const FString& Path)
	{
		// Check Path is Valid
		CS_IS_STRING_EMPTY_CHECKED(Path)

		FSoftObjectPath SoftPath(Path);

		return LoadChecked(Context, SoftPath);
	}

	UClass* FLibrary::SafeLoad(const FString& Context, const FString& Path, LogLevel)
	{
		// Check Path is Valid
		CS_IS_STRING_EMPTY_RET_NULL(Path)

		FSoftObjectPath SoftPath(Path);

		return SafeLoad(Context, SoftPath, Log);
	}

	UObject* FLibrary::SafeLoadDefaultObject(const FString& Context, const FSoftObjectPath& Path, bool& OutSuccess, LogLevel)
	{
		OutSuccess = false;

		UClass* Class = SafeLoad(Context, Path, Log);

		if (!Class)
			return nullptr;	

		UObject* DOb = Class->GetDefaultObject();

		if (!DOb)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Default Object from Class: %s."), *Context, *(Class->GetName())))
			return nullptr;
		}
		OutSuccess = true;
		return DOb;
	}

	UObject* FLibrary::SafeLoadDefaultObject(const FString& Context, const FString& Path, bool& OutSuccess, LogLevel)
	{
		OutSuccess = false;

		FString ClassPath = Path;

		if (!ClassPath.EndsWith(NCsClass::NLibrary::NCached::Str::_C))
			ClassPath.Append(NCsClass::NLibrary::NCached::Str::_C);

		UClass* Class = SafeLoad(Context, Path, Log);

		if (!Class)
			return nullptr;	

		UObject* DOb = Class->GetDefaultObject();

		if (!DOb)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Default Object from Class: %s."), *Context, *(Class->GetName())))
			return nullptr;
		}
		OutSuccess = true;
		return DOb;
	}

	#pragma endregion Load

	#undef LogLevel
}