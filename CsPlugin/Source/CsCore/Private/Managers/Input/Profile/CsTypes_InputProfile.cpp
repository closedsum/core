// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/Profile/CsTypes_InputProfile.h"

// Library
#include "Managers/Input/CsLibrary_Input.h"
#include "Library/CsLibrary_Valid.h"
// Utility
#include "Utility/CsLog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_InputProfile)

// FCsInputActionMapping
#pragma region

bool FCsInputActionMapping::IsValidChecked(const FString& Context) const
{
	check(EMCsInputAction::Get().IsValidEnumChecked(Context, Action));

	checkf(Key.IsValid(), TEXT("%s: Key: %s is NOT Valid."), *Context, *(Key.GetDisplayName().ToString()));
	return true;
}

bool FCsInputActionMapping::IsValid(const FString& Context, void(*Log)(const FString&) /*=nullptr*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsInputAction, FECsInputAction, Action)

	if (!Key.IsValid())
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Key: %s is NOT Valid."), *Context, *(Key.GetDisplayName().ToString())));
		return false;
	}
	return true;
}

#pragma endregion FCsInputActionMapping

// FCsInputActionMappings
#pragma region

bool FCsInputActionMappings::IsValidChecked(const FString& Context) const
{
	for (const FCsInputActionMapping& Mapping : Mappings)
	{
		check(Mapping.IsValidChecked(Context));
	}
	return true;
}

bool FCsInputActionMappings::IsValid(const FString& Context, void(*Log)(const FString&) /*=nullptr*/) const
{
	for (const FCsInputActionMapping& Mapping : Mappings)
	{
		if (!Mapping.IsValid(Context, Log))
			return false;
	}
	return true;
}

void FCsInputActionMappings::ReplaceActionsChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const ECsInputDevice& Device) const
{
	check(IsValidChecked(Context));

	typedef NCsInput::NMapping::FLibrary InputMappingLibrary;

	for (const FCsInputActionMapping& Mapping : Mappings)
	{
		InputMappingLibrary::ReplaceActionChecked(Context, WorldContext, ControllerId, Device, Mapping.Action, Mapping.Key, Mapping.Scale);
	}
}

#pragma endregion FCsInputActionMappings