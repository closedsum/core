// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_Character.h"
#include "CsCore.h"

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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Character, GetAnyByTags);
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

ACharacter* UCsScriptLibrary_Character::Spawn(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryCharacter::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Spawn : Context;

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

#define CharacterLibrary NCsCharacter::FLibrary

// Get
#pragma region

ACharacter* UCsScriptLibrary_Character::GetByTag(const FString& Context, UObject* WorldContextObject, const FName& Tag)
{
	using namespace NCsScriptLibraryCharacter::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetByTag : Context;

	return CharacterLibrary::GetSafeByTag(Ctxt, WorldContextObject, Tag);
}

ACharacter* UCsScriptLibrary_Character::GetByTags(const FString& Context, UObject* WorldContextObject, const TArray<FName>& Tags)
{
	using namespace NCsScriptLibraryCharacter::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetByTags : Context;

	return CharacterLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags);
}

bool UCsScriptLibrary_Character::GetAnyByTags(const FString& Context, UObject* WorldContextObject, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters)
{
	using namespace NCsScriptLibraryCharacter::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetAnyByTags : Context;

	return CharacterLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags, OutCharacters);
}

ACharacter* UCsScriptLibrary_Character::GetByName(const FString& Context, UObject* WorldContextObject, const FName& Name)
{
	using namespace NCsScriptLibraryCharacter::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetByName : Context;

	return CharacterLibrary::GetSafeByName(Ctxt, WorldContextObject, Name);
}

ACharacter* UCsScriptLibrary_Character::GetByLabel(const FString& Context, UObject* WorldContextObject, const FString& Label)
{
	using namespace NCsScriptLibraryCharacter::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetByLabel : Context;

	return CharacterLibrary::GetSafeByLabel(Ctxt, WorldContextObject, Label);
}

#pragma endregion Get

#undef CharacterLibrary