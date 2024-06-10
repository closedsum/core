// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coroutine/CsSettings_CoroutineScheduler.h"

// Library
	// Common
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsCoroutineSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSettings_CoroutineScheduler)

// FCsSettings_CoroutineScheduler_Custom
#pragma region

/*static*/ const FCsSettings_CoroutineScheduler_Custom& FCsSettings_CoroutineScheduler_Custom::Get()
{
	return FCsSettings_CoroutineScheduler::Get().Custom;
}

bool FCsSettings_CoroutineScheduler_Custom::IsValidChecked(const FString& Context) const
{
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(MaxGroups, 1)
	CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(MaxGroups, 4)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(MaxOwners, 1)
	CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(MaxOwners, 2048)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(MaxRoutinesPerOwner, 1)
	CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(MaxRoutinesPerOwner, 2048)
	return true;
}

#pragma endregion FCsSettings_CoroutineScheduler_Custom

// FCsSettings_CoroutineScheduler
#pragma region

/*static*/ const FCsSettings_CoroutineScheduler& FCsSettings_CoroutineScheduler::Get()
{
	return GetMutableDefault<UCsCoroutineSettings>()->CoroutineScheduler;
}

bool FCsSettings_CoroutineScheduler::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Custom);
	return true;
}

#pragma endregion FCsSettings_CoroutineScheduler