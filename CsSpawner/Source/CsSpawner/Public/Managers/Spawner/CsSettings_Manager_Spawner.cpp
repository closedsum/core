// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Spawner/CsSettings_Manager_Spawner.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSettings_Manager_Spawner)

// FCsSettings_Manager_Spawner_Modifier
#pragma region

bool FCsSettings_Manager_Spawner_Modifier::IsValidChecked(const FString& Context) const
{
	// Check PoolSize is >= 256
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(PoolSize, 256)
	return true;
}

bool FCsSettings_Manager_Spawner_Modifier::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsSpawner::FLog::Warning*/) const
{
	// Check PoolSize is >= 256
	CS_IS_INT_GREATER_THAN_OR_EQUAL(PoolSize, 256)
	return true;
}

#pragma endregion FCSettings_Manager_Character_Modifier

// FCsSettings_Manager_Spawner
#pragma region

bool FCsSettings_Manager_Spawner::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Modifier);
	return true;
}

bool FCsSettings_Manager_Spawner::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsSpawner::FLog::Warning*/) const
{
	CS_IS_VALID(Modifier)
	return true;
}

#pragma endregion FCsSettings_Manager_Spawner