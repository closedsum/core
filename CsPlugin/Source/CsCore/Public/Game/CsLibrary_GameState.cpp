// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/CsLibrary_GameState.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"
// World
#include "Engine/World.h"
#include "GameFrameWork/GameStateBase.h"

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

	AGameStateBase* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
	{
		CS_IS_PTR_NULL_CHECKED(WorldContext)

		UWorld* World = WorldContext->GetWorld();

		checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

		AGameStateBase* GameState = World->GetGameState();

		checkf(GameState, TEXT("%s: Failed to get GameState from World: %s."), *Context, *(World->GetName()));
		return GameState;
	}

	AGameStateBase* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL_RET_NULL(WorldContext)

		UWorld* World = WorldContext->GetWorld();

		if (!World)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName())));
			return nullptr;
		}

		AGameStateBase* GameState = World->GetGameState();

		if (!GameState)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get GameState from World: %s."), *Context, *(World->GetName())));
		}

		return GameState;
	}

	AGameStateBase* FLibrary::GetSafe(const UObject* WorldContext)
	{
		using namespace NCsGameState::NLibrary::NCached;

		const FString& Context = Str::GetSafe;

		return GetSafe(Context, WorldContext, nullptr);
	}

	UObject* FLibrary::GetAsObjectChecked(const FString& Context, const UObject* WorldContext)
	{
		return GetChecked(Context, WorldContext);
	}

	UObject* FLibrary::GetSafeAsObject(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		return GetSafe(Context, WorldContext, Log);
	}

	UObject* FLibrary::GetSafeAsObject(const UObject* WorldContext)
	{
		using namespace NCsGameState::NLibrary::NCached;

		const FString& Context = Str::GetSafeAsObject;

		return GetSafeAsObject(Context, WorldContext, nullptr);
	}
}