// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Fade/CsSettings_Manager_Fade.h"

// Library
	// Common
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Fade/CsManager_Fade.h"
// Settings
#include "Settings/CsFadeSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSettings_Manager_Fade)

// FCsSettings_Manager_Fade
#pragma region

FCsSettings_Manager_Fade::FCsSettings_Manager_Fade() :
	Class(UCsManager_Fade::StaticClass())
{
}

/*static*/ const FCsSettings_Manager_Fade& FCsSettings_Manager_Fade::Get()
{
	return GetMutableDefault<UCsFadeSettings>()->Manager_Fade;
}

bool FCsSettings_Manager_Fade::IsValidChecked(const FString& Context) const
{
	const FSoftObjectPath& SoftPath = Class.ToSoftObjectPath();

	checkf(SoftPath.IsValid(), TEXT("%s: Class is NULL or does NOT point to a Valid Path."), *Context);

	return true;
}

UClass* FCsSettings_Manager_Fade::LoadClassChecked(const FString& Context) const
{
	check(IsValidChecked(Context));

	UClass* C = Class.LoadSynchronous();

	checkf(C, TEXT("%s: Failed to load Class at Path: %s."), *Context, *(Class.ToString()));

	return C;
}

#pragma endregion FCsSettings_Manager_Fade