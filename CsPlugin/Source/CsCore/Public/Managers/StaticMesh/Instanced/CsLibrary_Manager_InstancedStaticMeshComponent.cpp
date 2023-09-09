// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/StaticMesh/Instanced/CsLibrary_Manager_InstancedStaticMeshComponent.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
	// Common
#include "Library/CsLibrary_World.h"
#include "Game/CsLibrary_GameState.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/StaticMesh/Instanced/CsManager_InstancedStaticMeshComponent.h"

namespace NCsStaticMesh
{
	namespace NInstanced
	{
		namespace NComponent
		{
			namespace NManager
			{
				namespace NLibrary
				{
					namespace NCached
					{
						namespace Str
						{
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStaticMesh::NInstanced::NComponent::NManager::FLibrary, GetSafeContextRoot);
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStaticMesh::NInstanced::NComponent::NManager::FLibrary, SafeSpawn);
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStaticMesh::NInstanced::NComponent::NManager::FLibrary, GetSafe);
						}
					}
				}

				// ContextRoot
				#pragma region

				UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* WorldContext)
				{
					typedef NCsWorld::FLibrary WorldLibrary;

					if (WorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
					{
						const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST_CHECKED(WorldContext, UObject, ICsGetManagerSingleton);

						return GetManagerSingleton->_getUObject();
					}

					typedef NCsGameState::FLibrary GameStateLibrary;

					return GameStateLibrary::GetAsObjectChecked(Context, WorldContext);
				}

				UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
				{
					typedef NCsWorld::FLibrary WorldLibrary;

					if (WorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
					{
						if (const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST(WorldContext, UObject, ICsGetManagerSingleton))
						{
							return GetManagerSingleton->_getUObject();
						}
						return nullptr;
					}

					typedef NCsGameState::FLibrary GameStateLibrary;

					return GameStateLibrary::GetSafeAsObject(Context, WorldContext, Log);
				}

				UObject* FLibrary::GetSafeContextRoot(const UObject* WorldContext)
				{
					using namespace NCsStaticMesh::NInstanced::NComponent::NManager::NLibrary::NCached;

					const FString& Context = Str::GetSafeContextRoot;

					return GetSafeContextRoot(Context, WorldContext, nullptr);
				}

				#pragma endregion ContextRoot

				// Get
				#pragma region

				ACsManager_InstancedStaticMeshComponent* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
				{
					UObject* ContextRoot								  = GetContextRootChecked(Context, WorldContext);
					ACsManager_InstancedStaticMeshComponent* Manager_ISMC = ACsManager_InstancedStaticMeshComponent::Get(ContextRoot);

					CS_IS_PTR_NULL_CHECKED(Manager_ISMC)
					return Manager_ISMC;
				}

				ACsManager_InstancedStaticMeshComponent* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
				{
					UObject* ContextRoot = GetSafeContextRoot(Context, WorldContext, Log);

					if (!ContextRoot)
						return nullptr;

					ACsManager_InstancedStaticMeshComponent* Manager_ISMC = ACsManager_InstancedStaticMeshComponent::GetSafe(Context, ContextRoot, Log);

					if (!Manager_ISMC)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_InstancedStaticMeshComponent."), *Context));
					}
					return Manager_ISMC;
				}

				ACsManager_InstancedStaticMeshComponent* FLibrary::GetSafe(const UObject* WorldContext)
				{
					using namespace NCsStaticMesh::NInstanced::NComponent::NManager::NLibrary::NCached;

					const FString& Context = Str::GetSafe;

					return GetSafe(Context, WorldContext, nullptr);
				}

				#pragma endregion Get

				#define ResourceType NCsStaticMesh::NInstanced::NComponent::FResource
				const ResourceType* FLibrary::AllocateChecked(const FString& Context, const UObject* WorldContext)
				{
					return GetChecked(Context, WorldContext)->Allocate();
				}
				#undef ResourceType
			}
		}
	}
}