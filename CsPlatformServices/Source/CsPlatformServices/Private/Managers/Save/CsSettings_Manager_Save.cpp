// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Save/CsSettings_Manager_Save.h"

// Library
	// Common
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Save/CsManager_Save.h"
// Settings
#include "Settings/CsPlatformServicesSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSettings_Manager_Save)

// FCsSettings_Manager_Save
#pragma region

FCsSettings_Manager_Save::FCsSettings_Manager_Save() :
	Class(UCsManager_Save::StaticClass())
{
}

/*static*/ const FCsSettings_Manager_Save& FCsSettings_Manager_Save::Get()
{
	return GetMutableDefault<UCsPlatformServicesSettings>()->Manager_Save;
}

bool FCsSettings_Manager_Save::IsValidChecked(const FString& Context) const
{
	const FSoftObjectPath& SoftPath = Class.ToSoftObjectPath();

	checkf(SoftPath.IsValid(), TEXT("%s: Class is NULL or does NOT point to a Valid Path."), *Context);

	return true;
}

UClass* FCsSettings_Manager_Save::LoadClassChecked(const FString& Context) const
{
	check(IsValidChecked(Context));

	UClass* C = Class.LoadSynchronous();

	checkf(C, TEXT("%s: Failed to load Class at Path: %s."), *Context, *(Class.ToString()));

	return C;
}

#pragma endregion FCsSettings_Manager_Save