// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/StaticMesh/Instanced/CsLibrary_Manager_InstancedStaticMeshComponent.h"

// Types
#include "CsMacro_Misc.h"
// Library
	// Common
#include "Library/CsLibrary_World.h"
#include "Game/CsLibrary_GameState.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Singleton/CsGetManagerSingleton.h"
#include "Managers/StaticMesh/Instanced/CsManager_InstancedStaticMeshComponent.h"

CS_START_CACHED_FUNCTION_NAME_NESTED_4(NCsStaticMesh, NInstanced, NComponent, NManager, Library)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsStaticMesh::NInstanced::NComponent::NManager::FLibrary, GetSafeContextRoot)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsStaticMesh::NInstanced::NComponent::NManager::FLibrary, SafeSpawn)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsStaticMesh::NInstanced::NComponent::NManager::FLibrary, GetSafe)
CS_END_CACHED_FUNCTION_NAME_NESTED_4

namespace NCsStaticMesh
{
	namespace NInstanced
	{
		namespace NComponent
		{
			namespace NManager
			{
				using LogLevelType = NCsStaticMesh::FLog;

				CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogLevelType::Warning);
			
				using ResourceType = NCsStaticMesh::NInstanced::NComponent::FResource;

				// ContextRoot
				#pragma region

				UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* WorldContext)
				{
					if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
					{
						const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST_CHECKED(WorldContext, UObject, ICsGetManagerSingleton);

						return GetManagerSingleton->_getUObject();
					}
					return CsGameStateLibrary::GetAsObjectChecked(Context, WorldContext);
				}

				UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
				{
					if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
					{
						if (const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST(WorldContext, UObject, ICsGetManagerSingleton))
						{
							return GetManagerSingleton->_getUObject();
						}
						return nullptr;
					}
					return CsGameStateLibrary::GetSafeAsObject(Context, WorldContext, Log);
				}

				UObject* FLibrary::GetSafeContextRoot(const UObject* WorldContext)
				{
					CS_SET_CONTEXT_AS_FUNCTION_NAME(GetSafeContextRoot);

					return GetSafeContextRoot(Context, WorldContext, nullptr);
				}

				#pragma endregion ContextRoot

				// Get
				#pragma region

				ACsManager_InstancedStaticMeshComponent* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
				{
				#if UE_BUILD_SHIPPING
					return ACsManager_InstancedStaticMeshComponent::Get(nullptr);
				#else
					UObject* ContextRoot								  = GetContextRootChecked(Context, WorldContext);
					ACsManager_InstancedStaticMeshComponent* Manager_ISMC = ACsManager_InstancedStaticMeshComponent::Get(ContextRoot);

					CS_IS_PTR_NULL_CHECKED(Manager_ISMC)
					return Manager_ISMC;
				#endif // #if UE_BUILD_SHIPPING
				}

				ACsManager_InstancedStaticMeshComponent* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
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
					CS_SET_CONTEXT_AS_FUNCTION_NAME(GetSafe);

					return GetSafe(Context, WorldContext, nullptr);
				}

				#pragma endregion Get

				const ResourceType* FLibrary::AllocateChecked(const FString& Context, const UObject* WorldContext)
				{
					return GetChecked(Context, WorldContext)->Allocate();
				}
			}
		}
	}
}