// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_Character.h"
#include "CsCore.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Character.h"
#include "Library/CsLibrary_World.h"
// Character
#include "GameFramework/Character.h"
// World
#include "Engine/World.h"

// Cached
#pragma region

namespace NCsScriptLibraryCharacter
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Character, Spawn);
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Character, GetByTag);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Character, GetByTags);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Character, GetByTagsChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Character, GetAnyByTags);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Character, GetAllByTags);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Character, GetAllByTagsChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Character, GetByName);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Character, GetByLabel);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Character::UCsScriptLibrary_Character(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryCharacter::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryCharacter::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::##__FunctionName : Context
#define LogError &FCsLog::Error
#define CharacterLibrary NCsCharacter::FLibrary

ACharacter* UCsScriptLibrary_Character::Spawn(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(Spawn);

	typedef NCsWorld::FLibrary WorldLibrary;

	UWorld* World = WorldLibrary::GetSafe(Ctxt, WorldContextObject);

	if (!World)
		return nullptr;

	ACharacter* Character = World->SpawnActor<ACharacter>(ACharacter::StaticClass());

	if (!Character)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Failed to Spawn object of type: ACharacter."), *Ctxt);
		return nullptr;
	}
	return Character;
}

// Get
#pragma region

ACharacter* UCsScriptLibrary_Character::GetByTag(const FString& Context, const UObject* WorldContextObject, const FName& Tag)
{
	CONDITIONAL_SET_CTXT(GetByTag);

	return CharacterLibrary::GetSafeByTag(Ctxt, WorldContextObject, Tag);
}

ACharacter* UCsScriptLibrary_Character::GetByTags(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags)
{
	CONDITIONAL_SET_CTXT(GetByTags);

	return CharacterLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags);
}

ACharacter* UCsScriptLibrary_Character::GetByTagsChecked(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetByTagsChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(CharacterLibrary::GetByTagsChecked(Ctxt, WorldContextObject, Tags), CharacterLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags, OutSuccess, LogError));
}

bool UCsScriptLibrary_Character::GetAnyByTags(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters)
{
	CONDITIONAL_SET_CTXT(GetAnyByTags);

	return CharacterLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags, OutCharacters);
}

bool UCsScriptLibrary_Character::GetAllByTags(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters)
{
	CONDITIONAL_SET_CTXT(GetAllByTags);

	return CharacterLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags, OutCharacters);
}

void UCsScriptLibrary_Character::GetAllByTagsChecked(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetAllByTagsChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(CharacterLibrary::GetByTagsChecked(Ctxt, WorldContextObject, Tags, OutCharacters), CharacterLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags, OutCharacters, OutSuccess, LogError));
}

ACharacter* UCsScriptLibrary_Character::GetByName(const FString& Context, const UObject* WorldContextObject, const FName& Name)
{
	CONDITIONAL_SET_CTXT(GetByName);

	return CharacterLibrary::GetSafeByName(Ctxt, WorldContextObject, Name);
}

ACharacter* UCsScriptLibrary_Character::GetByLabel(const FString& Context, const UObject* WorldContextObject, const FString& Label)
{
	CONDITIONAL_SET_CTXT(GetByLabel);

	return CharacterLibrary::GetSafeByLabel(Ctxt, WorldContextObject, Label);
}

#pragma endregion Get

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError
#undef CharacterLibrary