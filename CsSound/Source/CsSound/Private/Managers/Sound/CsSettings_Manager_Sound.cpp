// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Sound/CsSettings_Manager_Sound.h"

// Library
	// Common
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Sound/CsManager_Sound.h"
// Settings
#include "Settings/CsSoundSettings.h"

// FCsSettings_Manager_Sound
#pragma region

FCsSettings_Manager_Sound::FCsSettings_Manager_Sound() :
	Class(UCsManager_Sound::StaticClass()),
	TypesByUpdateGroupMap(),
	PoolParams()
{
}

/*static*/ const FCsSettings_Manager_Sound& FCsSettings_Manager_Sound::Get()
{
	return GetMutableDefault<UCsSoundSettings>()->Manager_Sound;
}

bool FCsSettings_Manager_Sound::IsValidChecked(const FString& Context) const
{
	const FSoftObjectPath& SoftPath = Class.ToSoftObjectPath();

	checkf(SoftPath.IsValid(), TEXT("%s: Class is NULL or does NOT point to a Valid Path."), *Context);

	return true;
}

UClass* FCsSettings_Manager_Sound::LoadClassChecked(const FString& Context) const
{
	check(IsValidChecked(Context));

	UClass* C = Class.LoadSynchronous();

	checkf(C, TEXT("%s: Failed to load Class at Path: %s."), *Context, *(Class.ToString()));

	return C;
}

#pragma endregion FCsSettings_Manager_Sound