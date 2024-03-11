// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Achievement/CsSettings_Manager_Achievement.h"

// Library
	// Common
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Achievement/CsManager_Achievement.h"
// Settings
#include "Settings/CsPlatformServicesSettings.h"

// FCsSettings_Manager_Achievement
#pragma region

FCsSettings_Manager_Achievement::FCsSettings_Manager_Achievement() :
	Class(UCsManager_Achievement::StaticClass())
{
}

/*static*/ const FCsSettings_Manager_Achievement& FCsSettings_Manager_Achievement::Get()
{
	return GetMutableDefault<UCsPlatformServicesSettings>()->Manager_Achievement;
}

bool FCsSettings_Manager_Achievement::IsValidChecked(const FString& Context) const
{
	const FSoftObjectPath& SoftPath = Class.ToSoftObjectPath();

	checkf(SoftPath.IsValid(), TEXT("%s: Class is NULL or does NOT point to a Valid Path."), *Context);

	return true;
}

UClass* FCsSettings_Manager_Achievement::LoadClassChecked(const FString& Context) const
{
	check(IsValidChecked(Context));

	UClass* C = Class.LoadSynchronous();

	checkf(C, TEXT("%s: Failed to load Class at Path: %s."), *Context, *(Class.ToString()));

	return C;
}

#pragma endregion FCsSettings_Manager_Achievement