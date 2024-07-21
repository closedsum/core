// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/CsSettings_Manager_Input_WithGameplayTag.h"

// Managers
#include "Managers/Input/Enhanced/CsManager_EnhancedInput_WithGameplayTag.h"
// Settings
#include "Settings/CsInputWithGameplayTagSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSettings_Manager_Input_WithGameplayTag)

// FCsSettings_Manager_Input
#pragma region

FCsSettings_Manager_Input_WithGameplayTag::FCsSettings_Manager_Input_WithGameplayTag() :
	Class(UCsManager_EnhancedInput_WithGameplayTag::StaticClass())
{
}

const FCsSettings_Manager_Input_WithGameplayTag& FCsSettings_Manager_Input_WithGameplayTag::Get()
{
	return GetMutableDefault<UCsInputWithGameplayTagSettings>()->Manager_Input;
}

bool FCsSettings_Manager_Input_WithGameplayTag::IsValidChecked(const FString& Context) const
{
	const FSoftObjectPath& SoftPath = Class.ToSoftObjectPath();

	checkf(SoftPath.IsValid(), TEXT("%s: Class is NULL or does NOT point to a Valid Path."), *Context);
	return true;
}

UClass* FCsSettings_Manager_Input_WithGameplayTag::LoadClassChecked(const FString& Context) const
{
	check(IsValidChecked(Context));

	UClass* C = Class.LoadSynchronous();

	checkf(C, TEXT("%s: Failed to load Class at Path: %s."), *Context, *(Class.ToString()));
	return C;
}

#pragma endregion FCsSettings_Manager_Input_WithGameplayTag