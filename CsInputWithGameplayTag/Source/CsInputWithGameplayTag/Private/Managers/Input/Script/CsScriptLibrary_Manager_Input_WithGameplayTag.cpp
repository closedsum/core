// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/Script/CsScriptLibrary_Manager_Input_WithGameplayTag.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Input/CsLibrary_Manager_Input_WithGameplayTag.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Manager_Input_WithGameplayTag)

// Cached
#pragma region

namespace NCsScriptLibraryManagerInputWithGameplayTag
{
	namespace NCached
	{
		namespace Str
		{
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input_WithGameplayTag, GetAsObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input_WithGameplayTag, GetAsObjectChecked);
			// Tag

				// HasMapping
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input_WithGameplayTag, HasMapping);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input_WithGameplayTag, HasMappingByName);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input_WithGameplayTag, HasMappingByString);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input_WithGameplayTag, HasMappingChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input_WithGameplayTag, HasMappingByNameChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input_WithGameplayTag, HasMappingByStringChecked);
				// SetMappingActive
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input_WithGameplayTag, SetMappingActive);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input_WithGameplayTag, SetMappingActiveByName);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input_WithGameplayTag, SetMappingActiveByString);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input_WithGameplayTag, SetMappingActiveChecked);
				// SetMappingInactive
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input_WithGameplayTag, SetMappingInctive);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input_WithGameplayTag, SetMappingInctiveChecked);
				// BlockMapping
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input_WithGameplayTag, BlockMapping);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input_WithGameplayTag, BlockMappingChecked);
		}
	}
}

#pragma endregion Cached

void(*UCsScriptLibrary_Manager_Input_WithGameplayTag::LogError)(const FString&) = &NCsInput::NWithGameplayTag::FLog::Error;

UCsScriptLibrary_Manager_Input_WithGameplayTag::UCsScriptLibrary_Manager_Input_WithGameplayTag(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryManagerInputWithGameplayTag::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryManagerInputWithGameplayTag::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

// Get
#pragma region

UObject* UCsScriptLibrary_Manager_Input_WithGameplayTag::GetAsObject(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId)
{
	CONDITIONAL_SET_CTXT(GetAsObject);

	return CsInputWithTagManagerLibrary::GetSafeAsObject(Ctxt, WorldContextObject, ControllerId);
}

UObject* UCsScriptLibrary_Manager_Input_WithGameplayTag::GetAsObjectChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetAsObjectChecked);

	OutSuccess = true;
	return CS_SCRIPT_LIBRARY_GET_CUSTOM_CHECKED_5(GetAsObjectChecked, GetSafeAsObject, WorldContextObject, ControllerId);
}

#pragma endregion Get

// Tag
#pragma region

	// HasMapping

bool UCsScriptLibrary_Manager_Input_WithGameplayTag::HasMapping(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FGameplayTag& Tag)
{
	CONDITIONAL_SET_CTXT(HasMapping);

	return CsInputWithTagManagerLibrary::SafeHasMapping(Ctxt, WorldContextObject, ControllerId, Tag);
}

bool UCsScriptLibrary_Manager_Input_WithGameplayTag::HasMappingByName(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FName& Tag)
{
	CONDITIONAL_SET_CTXT(HasMappingByName);

	return CsInputWithTagManagerLibrary::SafeHasMapping(Ctxt, WorldContextObject, ControllerId, Tag);
}

bool UCsScriptLibrary_Manager_Input_WithGameplayTag::HasMappingByString(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FString& Tag)
{
	CONDITIONAL_SET_CTXT(HasMappingByString);

	return CsInputWithTagManagerLibrary::SafeHasMapping(Ctxt, WorldContextObject, ControllerId, Tag);
}

bool UCsScriptLibrary_Manager_Input_WithGameplayTag::HasMappingChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FGameplayTag& Tag, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(HasMappingChecked);

	OutSuccess = true;
	return CS_SCRIPT_LIBRARY_GET_CHECKED_6(HasMapping, WorldContextObject, ControllerId, Tag);
}

bool UCsScriptLibrary_Manager_Input_WithGameplayTag::HasMappingByNameChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FName& Tag, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(HasMappingByNameChecked);

	OutSuccess = true;
	return CS_SCRIPT_LIBRARY_GET_CHECKED_6(HasMapping, WorldContextObject, ControllerId, Tag);
}

bool UCsScriptLibrary_Manager_Input_WithGameplayTag::HasMappingByStringChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FString& Tag, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(HasMappingByStringChecked);

	OutSuccess = true;
	return CS_SCRIPT_LIBRARY_GET_CHECKED_6(HasMapping, WorldContextObject, ControllerId, Tag);
}

	// SetMappingActive

bool UCsScriptLibrary_Manager_Input_WithGameplayTag::SetMappingActive(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FGameplayTag& Tag)
{
	CONDITIONAL_SET_CTXT(SetMappingActive);

	return CsInputWithTagManagerLibrary::SafeSetMappingActive(Ctxt, WorldContextObject, ControllerId, Tag);
}

bool UCsScriptLibrary_Manager_Input_WithGameplayTag::SetMappingActiveByName(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FName& Tag)
{
	CONDITIONAL_SET_CTXT(SetMappingActiveByName);

	return CsInputWithTagManagerLibrary::SafeSetMappingActive(Ctxt, WorldContextObject, ControllerId, Tag);
}

bool UCsScriptLibrary_Manager_Input_WithGameplayTag::SetMappingActiveByString(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FString& Tag)
{
	CONDITIONAL_SET_CTXT(SetMappingActiveByString);

	return CsInputWithTagManagerLibrary::SafeSetMappingActive(Ctxt, WorldContextObject, ControllerId, Tag);
}

void UCsScriptLibrary_Manager_Input_WithGameplayTag::SetMappingActiveChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FGameplayTag& Tag, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(SetMappingActiveChecked);

	CS_SCRIPT_LIBRARY_CHECKED_6(SetMappingActive, WorldContextObject, ControllerId, Tag)
}

bool UCsScriptLibrary_Manager_Input_WithGameplayTag::SetMappingInctive(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FGameplayTag& Tag)
{
	CONDITIONAL_SET_CTXT(SetMappingInctive);

	return CsInputWithTagManagerLibrary::SafeSetMappingActive(Ctxt, WorldContextObject, ControllerId, Tag);
}

void UCsScriptLibrary_Manager_Input_WithGameplayTag::SetMappingInctiveChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FGameplayTag& Tag, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(SetMappingInctiveChecked);

	CS_SCRIPT_LIBRARY_CHECKED_6(SetMappingInactive, WorldContextObject, ControllerId, Tag)
}

bool UCsScriptLibrary_Manager_Input_WithGameplayTag::BlockMapping(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FGameplayTag& Tag)
{
	CONDITIONAL_SET_CTXT(BlockMapping);

	return CsInputWithTagManagerLibrary::SafeBlockMapping(Ctxt, WorldContextObject, ControllerId, Tag);
}

void UCsScriptLibrary_Manager_Input_WithGameplayTag::BlockMappingChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FGameplayTag& Tag, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(BlockMappingChecked);

	CS_SCRIPT_LIBRARY_CHECKED_6(BlockMapping, WorldContextObject, ControllerId, Tag)
}

#pragma endregion Tag

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT