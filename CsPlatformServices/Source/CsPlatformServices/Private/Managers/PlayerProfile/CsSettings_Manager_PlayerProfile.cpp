// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/PlayerProfile/CsSettings_Manager_PlayerProfile.h"

// Library
	// Common
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/PlayerProfile/CsManager_PlayerProfile.h"
// Settings
#include "Settings/CsPlatformServicesSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSettings_Manager_PlayerProfile)

// FCsSettings_Manager_PlayerProfile
#pragma region

FCsSettings_Manager_PlayerProfile::FCsSettings_Manager_PlayerProfile() :
	Class(UCsManager_PlayerProfile::StaticClass())
{
}

/*static*/ const FCsSettings_Manager_PlayerProfile& FCsSettings_Manager_PlayerProfile::Get()
{
	return GetMutableDefault<UCsPlatformServicesSettings>()->Manager_PlayerProfile;
}

bool FCsSettings_Manager_PlayerProfile::IsValidChecked(const FString& Context) const
{
	const FSoftObjectPath& SoftPath = Class.ToSoftObjectPath();

	checkf(SoftPath.IsValid(), TEXT("%s: Class is NULL or does NOT point to a Valid Path."), *Context);

	return true;
}

UClass* FCsSettings_Manager_PlayerProfile::LoadClassChecked(const FString& Context) const
{
	check(IsValidChecked(Context));

	UClass* C = Class.LoadSynchronous();

	checkf(C, TEXT("%s: Failed to load Class at Path: %s."), *Context, *(Class.ToString()));

	return C;
}

#pragma endregion FCsSettings_Manager_PlayerProfile