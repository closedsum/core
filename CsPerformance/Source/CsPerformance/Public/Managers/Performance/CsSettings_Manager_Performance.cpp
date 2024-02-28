// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Performance/CsSettings_Manager_Performance.h"

// Library
	// Common
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Performance/CsManager_Performance.h"
// Settings
#include "Settings/CsPerformanceSettings.h"

// FCsSettings_Manager_Performance
#pragma region

FCsSettings_Manager_Performance::FCsSettings_Manager_Performance() :
	Class(UCsManager_Performance::StaticClass())
{
}

/*static*/ const FCsSettings_Manager_Performance& FCsSettings_Manager_Performance::Get()
{
	return GetMutableDefault<UCsPerformanceSettings>()->Manager_Performance;
}

bool FCsSettings_Manager_Performance::IsValidChecked(const FString& Context) const
{
	CS_IS_SOFT_CLASS_PTR_VALID_CHECKED(Class, UCsManager_Performance)
	return true;
}

UClass* FCsSettings_Manager_Performance::LoadClassChecked(const FString& Context) const
{
	check(IsValidChecked(Context));

	UClass* C = Class.LoadSynchronous();

	checkf(C, TEXT("%s: Failed to load Class at Path: %s."), *Context, *(Class.ToString()));

	return C;
}

#pragma endregion FCsSettings_Manager_Performance