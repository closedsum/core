// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coordinators/GameplayTag/CsTypes_Coordinator_GameplayTag.h"

// Library
#include "CsLibrary_Valid_GameplayTags.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Coordinator_GameplayTag)

// GameplayTagCoordinatorGroup
#pragma region

namespace NCsGameplayTagCoordinatorGroup
{
	CSGAMEPLAYTAGS_API CS_CREATE_ENUM_STRUCT(None);
	CSGAMEPLAYTAGS_API CS_CREATE_ENUM_STRUCT(GameInstance);
	CSGAMEPLAYTAGS_API CS_CREATE_ENUM_STRUCT(GameState);
	CSGAMEPLAYTAGS_API CS_CREATE_ENUM_STRUCT(ManagerInput0);
	CSGAMEPLAYTAGS_API CS_CREATE_ENUM_STRUCT(ManagerInput1);
}

#pragma endregion GameplayTagCoordinatorGroup

bool FCsGameplayTagEvent::IsValidChecked(const FString& Context) const 
{
	CS_IS_GAMEPLAY_TAG_VALID_CHECKED(Tag)
	return true;
}

bool FCsGameplayTagEvent::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsGameplayTags::FLog::Warning*/) const
{
	CS_IS_GAMEPLAY_TAG_VALID(Tag)
	return true;
}