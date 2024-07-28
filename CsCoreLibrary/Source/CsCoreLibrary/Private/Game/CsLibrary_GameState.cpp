// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/CsLibrary_GameState.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Valid.h"
// World
#include "Engine/World.h"
#include "GameFramework/GameStateBase.h"

namespace NCsGameState
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameState::FLibrary, GetSafe);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameState::FLibrary, GetSafeAsObject);
			}
		}
	}

	#define USING_NS_CACHED using namespace NCsGameState::NLibrary::NCached;
	#define SET_CONTEXT(__FunctionName) using namespace NCsGameState::NLibrary::NCached; \
		const FString& Context = Str::__FunctionName
	#define LogLevel void(*Log)(const FString&) /*=&FCsLog::Warning*/

	FString FLibrary::PrintGameStateAndClass(AGameStateBase* GameState)
	{
		return FString::Printf(TEXT("GameState: %s with Class: %s"), *(GameState->GetName()), *(GameState->GetClass()->GetName()));
	}

	AGameStateBase* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
	{
		UWorld* World			  = CsWorldLibrary::GetChecked(Context, WorldContext);
		AGameStateBase* GameState = World->GetGameState();

		checkf(GameState, TEXT("%s: Failed to get GameState from World: %s."), *Context, *(World->GetName()));
		return GameState;
	}

	AGameStateBase* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, LogLevel)
	{
		UWorld* World = CsWorldLibrary::GetSafe(Context, WorldContext, Log);

		if (!World)
			return nullptr;

		AGameStateBase* GameState = World->GetGameState();

		if (!GameState)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get GameState from World: %s."), *Context, *(World->GetName())));
			return nullptr;
		}
		return GameState;
	}

	AGameStateBase* FLibrary::GetSafe(const UObject* WorldContext)
	{
		SET_CONTEXT(GetSafe);

		return GetSafe(Context, WorldContext, nullptr);
	}

	UObject* FLibrary::GetAsObjectChecked(const FString& Context, const UObject* WorldContext)
	{
		return GetChecked(Context, WorldContext);
	}

	UObject* FLibrary::GetSafeAsObject(const FString& Context, const UObject* WorldContext, LogLevel)
	{
		return GetSafe(Context, WorldContext, Log);
	}

	UObject* FLibrary::GetSafeAsObject(const UObject* WorldContext)
	{
		using namespace NCsGameState::NLibrary::NCached;

		const FString& Context = Str::GetSafeAsObject;

		return GetSafeAsObject(Context, WorldContext, nullptr);
	}

	#undef USING_NS_CACHED
	#undef LogLevel
	#undef SET_CONTEXT
}