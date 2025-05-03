// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Enhanced/CsTypes_EnhancedInput_WithGameplayTag.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "CsLibrary_Valid_GameplayTags.h"
#include "Library/CsLibrary_Valid.h"
// Input
#include "InputMappingContext.h"
#include "InputAction.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_EnhancedInput_WithGameplayTag)

// FCsEnhancedInput_WithGameplayTag_ActionInfo
#pragma region

bool FCsEnhancedInput_WithGameplayTag_ActionInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_PENDING_KILL_CHECKED(Action)
	CS_IS_GAMEPLAY_TAG_VALID_CHECKED(Tag)
	checkf(!Events.IsEmpty(), TEXT("%s: Events is EMPTY. No Events set."), *Context);
	// TODO: Check Events is NOT Empty
	// TODO: Add CS_IS_ENUM_STRUCT_SET_UNIQUE_CHECKED(EMCsInputEvent, ECsInputEvent, Events)
	return true;
}

bool FCsEnhancedInput_WithGameplayTag_ActionInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsInput::NWithGameplayTag::FLog::Warning*/) const
{
	CS_IS_PENDING_KILL(Action)
	CS_IS_GAMEPLAY_TAG_VALID(Tag)

	if (Events.IsEmpty())
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Events is EMPTY. No Events set."), *Context))
		return false;
	}
	return true;
}

void FCsEnhancedInput_WithGameplayTag_ActionInfo::OnPostEditChange(const TSet<FString>& PropertyNames)
{
	TitleProperty.Empty();

	if (::IsValid(Action))
		TitleProperty += Action->GetName();

	TitleProperty += TitleProperty.IsEmpty() ? TEXT("None (") + Tag.ToString() + TEXT(")") : TEXT(" (") + Tag.ToString() + TEXT(")");
}

#pragma endregion FCsEnhancedInput_WithGameplayTag_ActionInfo

// FCsEnhancedInput_WithGameplayTag_MappingInfo
#pragma region

bool FCsEnhancedInput_WithGameplayTag_MappingInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_PENDING_KILL_CHECKED(MappingContext)
	CS_IS_GAMEPLAY_TAG_VALID_CHECKED(Tag)

	for (const FCsEnhancedInput_WithGameplayTag_ActionInfo& Info : ActionInfos)
	{
		CS_IS_VALID_CHECKED(Info);
	}
	return true;
}

bool FCsEnhancedInput_WithGameplayTag_MappingInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsInput::NWithGameplayTag::FLog::Warning*/) const
{
	CS_IS_PENDING_KILL(MappingContext)
	CS_IS_GAMEPLAY_TAG_VALID(Tag)

	for (const FCsEnhancedInput_WithGameplayTag_ActionInfo& Info : ActionInfos)
	{
		CS_IS_VALID(Info)
	}
	return true;
}

void FCsEnhancedInput_WithGameplayTag_MappingInfo::OnPostEditChange(const TSet<FString>& PropertyNames)
{
	TitleProperty.Empty();

	if (::IsValid(MappingContext))
		TitleProperty += MappingContext->GetName();

	TitleProperty += TitleProperty.IsEmpty() ? TEXT("None (") + Tag.ToString() + TEXT(")") : TEXT(" (") + Tag.ToString() + TEXT(")");

	if (PropertyNames.Contains(TEXT("ActionInfos")))
	{
		for (FCsEnhancedInput_WithGameplayTag_ActionInfo& Info : ActionInfos)
		{
			Info.OnPostEditChange(PropertyNames);
		}
	}
}

#pragma endregion FCsEnhancedInput_WithGameplayTag_MappingInfo