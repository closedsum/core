// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Level/CsSettings_Manager_Level.h"

// Library
	// Common
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Level/CsManager_Level.h"
// Settings
#include "Settings/CsDeveloperSettings.h"

// FCsSettings_Manager_Level
#pragma region

FCsSettings_Manager_Level::FCsSettings_Manager_Level() :
	Class(UCsManager_Level::StaticClass())
{
}

/*static*/ const FCsSettings_Manager_Level& FCsSettings_Manager_Level::Get()
{
	return GetMutableDefault<UCsDeveloperSettings>()->Manager_Level;
}

bool FCsSettings_Manager_Level::IsValidChecked(const FString& Context) const
{
	const FSoftObjectPath& SoftPath = Class.ToSoftObjectPath();

	checkf(SoftPath.IsValid(), TEXT("%s: Class is NULL or does NOT point to a Valid Path."), *Context);

	return true;
}

UClass* FCsSettings_Manager_Level::LoadClassChecked(const FString& Context) const
{
	check(IsValidChecked(Context));

	UClass* C = Class.LoadSynchronous();

	checkf(C, TEXT("%s: Failed to load Class at Path: %s."), *Context, *(Class.ToString()));

	return C;
}

#pragma endregion FCsSettings_Manager_Level