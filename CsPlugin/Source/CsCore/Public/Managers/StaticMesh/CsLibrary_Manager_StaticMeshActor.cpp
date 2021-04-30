// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/CsLibrary_Manager_StaticMeshActor.h"

// Managers
#include "Managers/StaticMesh/CsManager_StaticMeshActor.h"
// Library
//#include "Managers/StaticMesh/Payload/CsLibrary_Payload_StaticMeshActor.h"
#include "Library/CsLibrary_Valid.h"
// StaticsMesh
//#include "Managers/StaticsMesh/Payload/CsPayload_StaticMeshActorImpl.h"
//#include "Managers/StaticsMesh/Params/CsParams_StaticMeshActor.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameState.h"
#endif // #if WITH_EDITOR

namespace NCsStaticMeshActor
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStaticMeshActor::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStaticMeshActor::NManager::FLibrary, SafeSpawn);
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

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetSafeAsObject(Context, WorldContext, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* WorldContext)
		{
			using namespace NCsStaticMeshActor::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_StaticMeshActor* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* ContextRoot								= GetContextRootChecked(Context, ContextObject);
			UCsManager_StaticMeshActor* Manager_StaticMeshActor = UCsManager_StaticMeshActor::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_StaticMeshActor)
			return Manager_StaticMeshActor;
		}

		UCsManager_StaticMeshActor* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_StaticMeshActor* Manager_StaticMeshActor = UCsManager_StaticMeshActor::Get(ContextRoot);

			if (!Manager_StaticMeshActor)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_StaticMeshActor."), *Context));
			}
			return Manager_StaticMeshActor;
		}

		#pragma endregion Get
	}
}