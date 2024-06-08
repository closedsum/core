// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/CsSettings_Manager_Input.h"

// Managers
#include "Managers/Input/Default/CsManager_Input_Default.h"
// Settings
#include "Settings/CsInputSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSettings_Manager_Input)

// FCsSettings_Manager_Input
#pragma region

FCsSettings_Manager_Input::FCsSettings_Manager_Input() :
	Class(UCsManager_Input_Default::StaticClass()),
	InputPoolSize(2048),
	RemappedGamepadControllerIds()
{
}

const FCsSettings_Manager_Input& FCsSettings_Manager_Input::Get()
{
	return GetMutableDefault<UCsInputSettings>()->Manager_Input;
}

bool FCsSettings_Manager_Input::IsValidChecked(const FString& Context) const
{
	const FSoftObjectPath& SoftPath = Class.ToSoftObjectPath();

	checkf(SoftPath.IsValid(), TEXT("%s: Class is NULL or does NOT point to a Valid Path."), *Context);
	return true;
}

UClass* FCsSettings_Manager_Input::LoadClassChecked(const FString& Context) const
{
	check(IsValidChecked(Context));

	UClass* C = Class.LoadSynchronous();

	checkf(C, TEXT("%s: Failed to load Class at Path: %s."), *Context, *(Class.ToString()));
	return C;
}

#pragma endregion FCsSettings_Manager_Input