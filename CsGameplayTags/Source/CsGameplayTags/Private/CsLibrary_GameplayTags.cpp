// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsLibrary_GameplayTags.h"

// Library
#include "CsLibrary_Valid_GameplayTags.h"
#include "Library/CsLibrary_Valid.h"
// GameplayTag
#include "GameplayTagsManager.h"

namespace NCsGameplayTags
{
	#define LogLevel void(*Log)(const FString&) /*=&NCsGameplayTags::FLog::Warning*/

	FGameplayTag FLibrary::GetChecked(const FString& Context, const FName& Name)
	{
		CS_IS_NAME_NONE_CHECKED(Name)
		
		const FGameplayTag Tag = UGameplayTagsManager::Get().RequestGameplayTag(Name, false);

		CS_IS_GAMEPLAY_TAG_VALID_CHECKED(Tag)
		return Tag;
	}

	FGameplayTag FLibrary::GetChecked(const FString& Context, const FString& Name)
	{
		CS_IS_STRING_EMPTY_CHECKED(Name)
		return GetChecked(Context, FName(*Name));
	}

	FGameplayTag FLibrary::GetSafe(const FString& Context, const FName& Name, bool& OutSuccess, LogLevel)
	{
		OutSuccess = false;

		CS_IS_NAME_NONE_RET_VALUE(Name, FGameplayTag::EmptyTag)

		const FGameplayTag Tag = UGameplayTagsManager::Get().RequestGameplayTag(Name, false);

		CS_IS_GAMEPLAY_TAG_VALID_RET_VALUE(Tag, FGameplayTag::EmptyTag)
		return Tag;
	}

	FGameplayTag FLibrary::GetSafe(const FString& Context, const FString& Name, bool& OutSuccess, LogLevel)
	{
		OutSuccess = false;

		CS_IS_STRING_EMPTY_RET_VALUE(Name, FGameplayTag::EmptyTag)
		return GetSafe(Context, FName(*Name), OutSuccess, Log);
	}

	#undef LogLevel
}