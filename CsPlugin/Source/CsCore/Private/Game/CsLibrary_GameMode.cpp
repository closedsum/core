// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/CsLibrary_GameMode.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Valid.h"
// Game
#include "Game/Event/CsGameMode_Event.h"
// World
#include "Engine/World.h"
#include "GameFramework/GameModeBase.h"

namespace NCsGameMode
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameMode::FLibrary, GetSafe);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameMode::FLibrary, GetSafeAsObject);
			}
		}
	}

	#define USING_NS_CACHED using namespace NCsGameMode::NLibrary::NCached;
	#define SET_CONTEXT(__FunctionName) using namespace NCsGameMode::NLibrary::NCached; \
		const FString& Context = Str::__FunctionName
	#define WorldLibrary NCsWorld::FLibrary

	FString FLibrary::PrintGameModeAndClass(AGameModeBase* GameMode)
	{
		return FString::Printf(TEXT("GameMode: %s with Class: %s"), *(GameMode->GetName()), *(GameMode->GetClass()->GetName()));
	}

	AGameModeBase* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
	{
		UWorld* World			 = WorldLibrary::GetChecked(Context, WorldContext);
		AGameModeBase* GameMode = World->GetAuthGameMode();

		checkf(GameMode, TEXT("%s: Failed to get GameMode from World: %s."), *Context, *(World->GetName()));
		return GameMode;
	}

	AGameModeBase* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

		if (!World)
			return nullptr;

		AGameModeBase* GameMode = World->GetAuthGameMode();

		if (!GameMode)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get GameMode from World: %s."), *Context, *(World->GetName())));
			return nullptr;
		}
		return GameMode;
	}

	AGameModeBase* FLibrary::GetSafe(const UObject* WorldContext)
	{
		SET_CONTEXT(GetSafe);

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
		using namespace NCsGameMode::NLibrary::NCached;

		const FString& Context = Str::GetSafeAsObject;

		return GetSafeAsObject(Context, WorldContext, nullptr);
	}

	// ICsGameMode_Event
	#pragma region

	#define OnPostSeamlessTravelCompleteEventType NCsGameMode::NSeamlessTravel::NPost::FOnComplete

	OnPostSeamlessTravelCompleteEventType& FLibrary::GetPostSeamlessTravel_OnComplete_EventChecked(const FString& Context, const UObject* WorldContext)
	{
		AGameModeBase* GameMode		 = GetChecked(Context, WorldContext);
		ICsGameMode_Event* Interface = CS_INTERFACE_CAST_CHECKED(GameMode, AGameModeBase, ICsGameMode_Event);

		return Interface->GetPostSeamlessTravel_OnComplete_Event();
	}

	#undef OnPostSeamlessTravelCompleteEventType

	#pragma endregion ICsGameMode_Event

	#undef USING_NS_CACHED
	#undef SET_CONTEXT
	#undef WorldLibrary
}