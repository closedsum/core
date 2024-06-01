// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Time/CsSettings_Manager_Time.h"

// Library
	// Common
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Time/CsManager_time.h"
// Settings
#include "Settings/CsTimeSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSettings_Manager_Time)

// FCsSettings_Manager_Time
#pragma region

FCsSettings_Manager_Time::FCsSettings_Manager_Time() :
	Class(UCsManager_Time::StaticClass()),
	TogglePauseGroupByKeysMap(),
	CustomUpdateMap()
{
}

/*static*/ const FCsSettings_Manager_Time& FCsSettings_Manager_Time::Get()
{
	return GetMutableDefault<UCsTimeSettings>()->Manager_Time;
}

bool FCsSettings_Manager_Time::IsValidChecked(const FString& Context) const
{
	const FSoftObjectPath& SoftPath = Class.ToSoftObjectPath();

	checkf(SoftPath.IsValid(), TEXT("%s: Class is NULL or does NOT point to a Valid Path."), *Context);
	return true;
}

UClass* FCsSettings_Manager_Time::LoadClassChecked(const FString& Context) const
{
	check(IsValidChecked(Context));

	UClass* C = Class.LoadSynchronous();

	checkf(C, TEXT("%s: Failed to load Class at Path: %s."), *Context, *(Class.ToString()));
	return C;
}

#pragma endregion FCsSettings_Manager_Time