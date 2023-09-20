// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Character/Script/CsScriptLibrary_ScriptableCharacter.h"
#include "CsJs.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Character/CsLibrary_ScriptableCharacter.h"

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

#define CharacterLibrary NCsCharacter::NScriptable::FLibrary

UCsScriptLibrary_ScriptableCharacter::UCsScriptLibrary_ScriptableCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Get
#pragma region

bool UCsScriptLibrary_ScriptableCharacter::GetAll(const FString& Context, const UObject* WorldContextObject, TArray<ACharacter*>& OutCharacters)
{
	using namespace NCsScriptLibraryScriptableCharacter::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetAll : Context;

	return CharacterLibrary::GetSafe(Ctxt, WorldContextObject, OutCharacters);
}

ACharacter* UCsScriptLibrary_ScriptableCharacter::GetByTag(const FString& Context, UObject* WorldContextObject, const FName& Tag)
{
	using namespace NCsScriptLibraryScriptableCharacter::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetByTag : Context;

	return CharacterLibrary::GetSafeByTag(Ctxt, WorldContextObject, Tag);
}

bool UCsScriptLibrary_ScriptableCharacter::GetAnyByTags(const FString& Context, UObject* WorldContextObject, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters)
{
	using namespace NCsScriptLibraryScriptableCharacter::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetAnyByTags : Context;

	return CharacterLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags, OutCharacters);
}

ACharacter* UCsScriptLibrary_ScriptableCharacter::GetByName(const FString& Context, UObject* WorldContextObject, const FName& Name)
{
	using namespace NCsScriptLibraryScriptableCharacter::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetByName : Context;

	return CharacterLibrary::GetSafeByName(Ctxt, WorldContextObject, Name);
}

ACharacter* UCsScriptLibrary_ScriptableCharacter::GetByLabel(const FString& Context, UObject* WorldContextObject, const FString& Label)
{
	using namespace NCsScriptLibraryScriptableCharacter::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetByLabel : Context;

	return CharacterLibrary::GetSafeByLabel(Ctxt, WorldContextObject, Label);
}

#pragma endregion Get

#undef CharacterLibrary