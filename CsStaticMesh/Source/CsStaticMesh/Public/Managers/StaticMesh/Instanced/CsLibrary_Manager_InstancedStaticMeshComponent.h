// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsStaticMeshLog.h"

class UObject;
class ACsManager_InstancedStaticMeshComponent;

// NCsStaticMesh::NInstanced::NComponent::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsStaticMesh, NInstanced, NComponent, FResource)

namespace NCsStaticMesh
{
	namespace NInstanced
	{
		namespace NComponent
		{
			namespace NManager
			{
				struct CSSTATICMESH_API FLibrary final
				{
				#define LogLevel void(*Log)(const FString&) = &NCsStaticMesh::FLog::Warning

				// ContextRoot
				#pragma region
				public:

					/**
					* Get the Context (Root) for ACsManager_InstancedStaticMeshComponent from a WorldContext.
					*
					* @param Context		The calling context.
					* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
					* return				Context for ACsManager_InstancedStaticMeshComponent
					*/
					static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext);

					/**
					* Get the Context (Root) for ACsManager_InstancedStaticMeshComponent from a WorldContext.
					*
					* @param Context		The calling context.
					* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
					* @param Log
					* return				Context for ACsManager_InstancedStaticMeshComponent
					*/
					static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, LogLevel);

					/**
					* Get the Context (Root) for ACsManager_InstancedStaticMeshComponent from a WorldContext.
					*
					* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
					* return				Context for ACsManager_InstancedStaticMeshComponent
					*/
					static UObject* GetSafeContextRoot(const UObject* WorldContext);

				#pragma endregion ContextRoot

				// Get
				#pragma region
				public:

					/**
					* Get the reference to ACsManager_InstancedStaticMeshComponent from a WorldContext.
					*
					* @param Context		The calling context.
					* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
					* return				ACsManager_InstancedStaticMeshComponent.
					*/
					static ACsManager_InstancedStaticMeshComponent* GetChecked(const FString& Context, const UObject* WorldContext);

					/**
					* Safely get the reference to ACsManager_InstancedStaticMeshComponent from a WorldContext.
					*
					* @param Context		The calling context.
					* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
					* @param Log
					* return				ACsManager_InstancedStaticMeshComponent.
					*/
					static ACsManager_InstancedStaticMeshComponent* GetSafe(const FString& Context, const UObject* WorldContext, LogLevel);

					/**
					* Safely get the reference to ACsManager_InstancedStaticMeshComponent from a WorldContext.
					*
					* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
					* return				ACsManager_InstancedStaticMeshComponent.
					*/
					static ACsManager_InstancedStaticMeshComponent* GetSafe(const UObject* WorldContext);

				#pragma endregion Get

				public:

				#define ResourceType NCsStaticMesh::NInstanced::NComponent::FResource
					static const ResourceType* AllocateChecked(const FString& Context, const UObject* WorldContext);
				#undef ResourceType

				#undef LogLevel
				};
			}
		}
	}
}