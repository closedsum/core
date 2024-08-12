// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_Character.h"
#include "CsCoreLibrary.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Character.h"
#include "Library/CsLibrary_World.h"
// Character
#include "GameFramework/Character.h"
// World
#include "Engine/World.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Character)

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
			// Anim
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Character, Montage_Play);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Character, Montage_PlayByPath);
		}
	}
}

#pragma endregion Cached

void(*UCsScriptLibrary_Character::LogError)(const FString&) = &NCsCore::NLibrary::FLog::Error;

UCsScriptLibrary_Character::UCsScriptLibrary_Character(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryCharacter::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryCharacter::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

ACharacter* UCsScriptLibrary_Character::Spawn(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(Spawn);

	UWorld* World = CsWorldLibrary::GetSafe(Ctxt, WorldContextObject);

	if (!World)
		return nullptr;

	ACharacter* Character = World->SpawnActor<ACharacter>(ACharacter::StaticClass());

	if (!Character)
	{
		UE_LOG(LogCsCoreLibrary, Warning, TEXT("%s: Failed to Spawn object of type: ACharacter."), *Ctxt);
		return nullptr;
	}
	return Character;
}

// Get
#pragma region

ACharacter* UCsScriptLibrary_Character::GetByTag(const FString& Context, const UObject* WorldContextObject, const FName& Tag)
{
	CONDITIONAL_SET_CTXT(GetByTag);

	return CsCharacterLibrary::GetSafeByTag(Ctxt, WorldContextObject, Tag);
}

ACharacter* UCsScriptLibrary_Character::GetByTags(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags)
{
	CONDITIONAL_SET_CTXT(GetByTags);

	return CsCharacterLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags);
}

ACharacter* UCsScriptLibrary_Character::GetByTagsChecked(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetByTagsChecked);

	OutSuccess = true;
	return CS_SCRIPT_LIBRARY_GET_CUSTOM_CHECKED_5(GetByTagsChecked, GetSafeByTags, WorldContextObject, Tags);
}

bool UCsScriptLibrary_Character::GetAnyByTags(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters)
{
	CONDITIONAL_SET_CTXT(GetAnyByTags);

	return CsCharacterLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags, OutCharacters);
}

bool UCsScriptLibrary_Character::GetAllByTags(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters)
{
	CONDITIONAL_SET_CTXT(GetAllByTags);

	return CsCharacterLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags, OutCharacters);
}

void UCsScriptLibrary_Character::GetAllByTagsChecked(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetAllByTagsChecked);

	OutSuccess = true;
	CS_SCRIPT_LIBRARY_CUSTOM_CHECKED_6(GetByTagsChecked, GetSafeByTags, WorldContextObject, Tags, OutCharacters)
}

ACharacter* UCsScriptLibrary_Character::GetByName(const FString& Context, const UObject* WorldContextObject, const FName& Name)
{
	CONDITIONAL_SET_CTXT(GetByName);

	return CsCharacterLibrary::GetSafeByName(Ctxt, WorldContextObject, Name);
}

ACharacter* UCsScriptLibrary_Character::GetByLabel(const FString& Context, const UObject* WorldContextObject, const FString& Label)
{
	CONDITIONAL_SET_CTXT(GetByLabel);

	return CsCharacterLibrary::GetSafeByLabel(Ctxt, WorldContextObject, Label);
}

#pragma endregion Get

// Anim
#pragma region

float UCsScriptLibrary_Character::Montage_Play(const FString& Context, const ACharacter* Character, const FCsAnimMontage_PlayParams& Params)
{
	CONDITIONAL_SET_CTXT(Montage_Play);

	return CsCharacterLibrary::SafePlay(Context, Character, Params);
}

float UCsScriptLibrary_Character::Montage_PlayByPath(const FString& Context, const ACharacter* Character, const FCsAnimMontage_PlayByPathParams& Params)
{
	CONDITIONAL_SET_CTXT(Montage_PlayByPath);

	return CsCharacterLibrary::SafePlay(Context, Character, Params);
}

#pragma endregion Anim

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT