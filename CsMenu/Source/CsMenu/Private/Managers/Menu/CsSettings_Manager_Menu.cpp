// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Menu/CsSettings_Manager_Menu.h"

// Library
	// Common
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Menu/CsManager_Menu.h"
// Settings
#include "Settings/CsMenuSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSettings_Manager_Menu)

// FCsSettings_Manager_Menu
#pragma region

FCsSettings_Manager_Menu::FCsSettings_Manager_Menu() :
	Class(UCsManager_Menu::StaticClass())
{
}

/*static*/ const FCsSettings_Manager_Menu& FCsSettings_Manager_Menu::Get()
{
	return GetMutableDefault<UCsMenuSettings>()->Manager_Menu;
}

bool FCsSettings_Manager_Menu::IsValidChecked(const FString& Context) const
{
	const FSoftObjectPath& SoftPath = Class.ToSoftObjectPath();

	checkf(SoftPath.IsValid(), TEXT("%s: Class is NULL or does NOT point to a Valid Path."), *Context);

	return true;
}

UClass* FCsSettings_Manager_Menu::LoadClassChecked(const FString& Context) const
{
	check(IsValidChecked(Context));

	UClass* C = Class.LoadSynchronous();

	checkf(C, TEXT("%s: Failed to load Class at Path: %s."), *Context, *(Class.ToString()));

	return C;
}

#pragma endregion FCsSettings_Manager_Menu