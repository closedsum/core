// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "LevelSequence/Script/CsScriptLibrary_LevelSequencePlayer.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "LevelSequence/CsLibrary_LevelSequence.h"

// Cached
#pragma region

namespace NCsScriptLibraryLevelSequencePlayer
{
	namespace NCached
	{
		namespace Str
		{
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_LevelSequencePlayer, GetByTag);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_LevelSequencePlayer, GetByTags);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_LevelSequencePlayer, GetByName);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_LevelSequencePlayer, GetByLabel);
			// Play
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_LevelSequencePlayer, PlayFromStart);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_LevelSequencePlayer::UCsScriptLibrary_LevelSequencePlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define LevelSequencePlayerLibrary NCsLevelSequence::NPlayer::FLibrary

// Get
#pragma region

ULevelSequencePlayer* UCsScriptLibrary_LevelSequencePlayer::GetByTag(const FString& Context, UObject* WorldContextObject, const FName& Tag)
{
	using namespace NCsScriptLibraryLevelSequencePlayer::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetByTag : Context;

	return LevelSequencePlayerLibrary::GetSafeByTag(Ctxt, WorldContextObject, Tag);
}

ULevelSequencePlayer* UCsScriptLibrary_LevelSequencePlayer::GetByTags(const FString& Context, UObject* WorldContextObject, const TArray<FName>& Tags)
{
	using namespace NCsScriptLibraryLevelSequencePlayer::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetByTags : Context;

	return LevelSequencePlayerLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags);
}

ULevelSequencePlayer* UCsScriptLibrary_LevelSequencePlayer::GetByName(const FString& Context, UObject* WorldContextObject, const FName& Name)
{
	using namespace NCsScriptLibraryLevelSequencePlayer::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetByName : Context;

	return LevelSequencePlayerLibrary::GetSafeByName(Ctxt, WorldContextObject, Name);
}

ULevelSequencePlayer* UCsScriptLibrary_LevelSequencePlayer::GetByLabel(const FString& Context, UObject* WorldContextObject, const FString& Label)
{
	using namespace NCsScriptLibraryLevelSequencePlayer::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetByLabel : Context;

	return LevelSequencePlayerLibrary::GetSafeByLabel(Ctxt, WorldContextObject, Label);
}

#pragma endregion Get

// Play
#pragma region

bool UCsScriptLibrary_LevelSequencePlayer::PlayFromStart(const FString& Context, ULevelSequencePlayer* Player)
{
	using namespace NCsScriptLibraryLevelSequencePlayer::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::PlayFromStart : Context;

	return LevelSequencePlayerLibrary::SafePlayFromStart(Ctxt, Player);
}

#pragma endregion Play

#undef LevelSequencePlayerLibrary