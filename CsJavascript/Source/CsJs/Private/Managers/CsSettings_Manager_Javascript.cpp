// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/CsSettings_Manager_Javascript.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsJsSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSettings_Manager_Javascript)

// FCsSettings_Manager_Javascript
#pragma region

/*static*/ const FCsSettings_Manager_Javascript& FCsSettings_Manager_Javascript::Get()
{
	return GetMutableDefault<UCsJsSettings>()->Manager_Javascript;
}

bool FCsSettings_Manager_Javascript::IsValidChecked(const FString& Context) const
{
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(PoolSize, 1)
	CS_IS_STRING_EMPTY_CHECKED(EmptyPath)
	return true;
}

#pragma endregion FCsSettings_Manager_Javascript