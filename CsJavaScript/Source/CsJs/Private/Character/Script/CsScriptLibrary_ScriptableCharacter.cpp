// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Character/Script/CsScriptLibrary_ScriptableCharacter.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Character/CsLibrary_ScriptableCharacter.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_ScriptableCharacter)

// Cached
#pragma region

namespace NCsScriptLibraryScriptableCharacter
{
	namespace NCached
	{
		namespace Str
		{
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_ScriptableCharacter, GetAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_ScriptableCharacter, GetByTag);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_ScriptableCharacter, GetAnyByTags);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_ScriptableCharacter, GetByName);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_ScriptableCharacter, GetByLabel);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_ScriptableCharacter::UCsScriptLibrary_ScriptableCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryScriptableCharacter::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryScriptableCharacter::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

// Get
#pragma region

bool UCsScriptLibrary_ScriptableCharacter::GetAll(const FString& Context, const UObject* WorldContextObject, TArray<ACharacter*>& OutCharacters)
{
	CONDITIONAL_SET_CTXT(GetAll);

	return CsScriptableCharacterLibrary::GetSafe(Ctxt, WorldContextObject, OutCharacters);
}

ACharacter* UCsScriptLibrary_ScriptableCharacter::GetByTag(const FString& Context, UObject* WorldContextObject, const FName& Tag)
{
	CONDITIONAL_SET_CTXT(GetByTag);

	return CsScriptableCharacterLibrary::GetSafeByTag(Ctxt, WorldContextObject, Tag);
}

bool UCsScriptLibrary_ScriptableCharacter::GetAnyByTags(const FString& Context, UObject* WorldContextObject, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters)
{
	CONDITIONAL_SET_CTXT(GetAnyByTags);

	return CsScriptableCharacterLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags, OutCharacters);
}

ACharacter* UCsScriptLibrary_ScriptableCharacter::GetByName(const FString& Context, UObject* WorldContextObject, const FName& Name)
{
	CONDITIONAL_SET_CTXT(GetByName);

	return CsScriptableCharacterLibrary::GetSafeByName(Ctxt, WorldContextObject, Name);
}

ACharacter* UCsScriptLibrary_ScriptableCharacter::GetByLabel(const FString& Context, UObject* WorldContextObject, const FString& Label)
{
	CONDITIONAL_SET_CTXT(GetByLabel);

	return CsScriptableCharacterLibrary::GetSafeByLabel(Ctxt, WorldContextObject, Label);
}

#pragma endregion Get

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT