// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Script/CsScriptLibrary_GameplayTag.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "CsLibrary_GameplayTags.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_GameplayTag)

// Cached
#pragma region

namespace NCsScriptLibraryGameplayTag
{
	namespace NCached
	{
		namespace Str
		{
			// Tag
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameplayTag, Get);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameplayTag, GetChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameplayTag, GetByString);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameplayTag, GetByStringChecked);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_GameplayTag::UCsScriptLibrary_GameplayTag(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryGameplayTag::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryGameplayTag::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define LogError &NCsGameplayTags::FLog::Error

// Tag
#pragma region

FGameplayTag UCsScriptLibrary_GameplayTag::Get(const FString& Context, const FName& TagName)
{
	CONDITIONAL_SET_CTXT(Get);

	return CsGameplayTagsLibrary::GetSafe(Ctxt, TagName);
}

FGameplayTag UCsScriptLibrary_GameplayTag::GetChecked(const FString& Context, const FName& TagName, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(CsGameplayTagsLibrary::GetChecked(Ctxt, TagName), CsGameplayTagsLibrary::GetSafe(Ctxt, TagName, OutSuccess, LogError));
}

FGameplayTag UCsScriptLibrary_GameplayTag::GetByString(const FString& Context, const FString& TagName)
{
	CONDITIONAL_SET_CTXT(GetByString);

	return CsGameplayTagsLibrary::GetSafe(Ctxt, TagName);
}

FGameplayTag UCsScriptLibrary_GameplayTag::GetByStringChecked(const FString& Context, const FString& TagName, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetByStringChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(CsGameplayTagsLibrary::GetChecked(Ctxt, TagName), CsGameplayTagsLibrary::GetSafe(Ctxt, TagName, OutSuccess, LogError));
}

#pragma endregion Tag

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError