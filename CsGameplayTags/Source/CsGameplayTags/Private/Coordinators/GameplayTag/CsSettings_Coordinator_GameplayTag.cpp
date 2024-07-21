// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coordinators/GameplayTag/CsSettings_Coordinator_GameplayTag.h"

// Library
	// Common
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Coordinators/GameplayTag/CsCoordinator_GameplayTag.h"
// Settings
#include "Settings/CsGameplayTagsSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSettings_Coordinator_GameplayTag)

// FCsSettings_Coordinator_GameplayTag
#pragma region

FCsSettings_Coordinator_GameplayTag::FCsSettings_Coordinator_GameplayTag() :
	Class(UCsCoordinator_GameplayTag::StaticClass())
{
}

/*static*/ const FCsSettings_Coordinator_GameplayTag& FCsSettings_Coordinator_GameplayTag::Get()
{
	return GetMutableDefault<UCsGameplayTagsSettings>()->Coordinator_GameplayTag;
}

bool FCsSettings_Coordinator_GameplayTag::IsValidChecked(const FString& Context) const
{
	const FSoftObjectPath& SoftPath = Class.ToSoftObjectPath();

	checkf(SoftPath.IsValid(), TEXT("%s: Class is NULL or does NOT point to a Valid Path."), *Context);
	return true;
}

UClass* FCsSettings_Coordinator_GameplayTag::LoadClassChecked(const FString& Context) const
{
	check(IsValidChecked(Context));

	UClass* C = Class.LoadSynchronous();

	checkf(C, TEXT("%s: Failed to load Class at Path: %s."), *Context, *(Class.ToString()));
	return C;
}

#pragma endregion FCsSettings_Coordinator_GameplayTag