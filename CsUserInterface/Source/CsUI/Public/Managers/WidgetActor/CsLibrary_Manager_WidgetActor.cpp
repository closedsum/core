// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/WidgetActor/CsLibrary_Manager_WidgetActor.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/WidgetActor/CsManager_WidgetActor.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameState.h"
#endif // #if WITH_EDITOR

namespace NCsWidgetActor
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidgetActor::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidgetActor::NManager::FLibrary, GetSafe);
				}
			}
		}

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* WorldContext)
		{
			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetAsObjectChecked(Context, WorldContext);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
		{
			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetSafeAsObject(Context, WorldContext, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* WorldContext)
		{
			using namespace NCsWidgetActor::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_WidgetActor* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* ContextRoot					    = GetContextRootChecked(Context, ContextObject);
			UCsManager_WidgetActor* Manager_WidgetActor = UCsManager_WidgetActor::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_WidgetActor)
			return Manager_WidgetActor;
		}

		UCsManager_WidgetActor* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*= &NCsUI::FLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_WidgetActor* Manager_WidgetActor = UCsManager_WidgetActor::GetSafe(Context, ContextRoot, Log);

			if (!Manager_WidgetActor)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_WidgetActor."), *Context));
			}
			return Manager_WidgetActor;
		}

		UCsManager_WidgetActor* FLibrary::GetSafe(const UObject* ContextObject)
		{
			using namespace NCsWidgetActor::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get

		// Payload
		#pragma region

		#define PayloadType NCsWidgetActor::NPayload::IPayload
		PayloadType* FLibrary::AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, const FECsWidgetActor& Type)
		{
		#undef PayloadType
			return GetChecked(Context, WorldContext)->AllocatePayload(Type);
		}

		#pragma endregion Payload

		// Spawn
		#pragma region

		#define PayloadType NCsWidgetActor::NPayload::IPayload
		const FCsWidgetActorPooled* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, const FECsWidgetActor& Type, PayloadType* Payload)
		{
		#undef PayloadType
			return GetChecked(Context, WorldContext)->Spawn(Type, Payload);
		}

		#pragma endregion Spawn
	}
}