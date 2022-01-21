// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"
// Log
#include "Utility/CsLog.h"

#pragma once

class UObject;
class UCsManager_StaticMeshActor;
struct FCsStaticMeshActorPooled;

// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

namespace NCsStaticMeshActor
{
	namespace NManager
	{
		struct CSCORE_API FLibrary final
		{
		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_StaticMeshActor from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_StaticMeshActor
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_StaticMeshActor from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				Context for UCsManager_StaticMeshActor
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_StaticMeshActor from a WorldContext.
			*
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_StaticMeshActor
			*/
			static UObject* GetSafeContextRoot(const UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region
		public:

			/**
			* Get the reference to UCsManager_StaticMeshActor from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_StaticMeshActor.
			*/
			static UCsManager_StaticMeshActor* GetChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get the reference to UCsManager_StaticMeshActor from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				UCsManager_StaticMeshActor.
			*/
			static UCsManager_StaticMeshActor* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely get the reference to UCsManager_StaticMeshActor from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_StaticMeshActor.
			*/
			static UCsManager_StaticMeshActor* GetSafe(const UObject* WorldContext);

		#pragma endregion Get

		// Spawn
		#pragma region
		public:

		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

			/**
			* Spawn an StaticMeshActor with the given payload.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param Shot
			* @param Transform		(optional)
			* return				Spawned StaticMeshActor
			*/
			static const FCsStaticMeshActorPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, const PooledPayloadType* PooledPayload, const FCsStaticMeshActorPooledInfo& Info, const FTransform& Transform = FTransform::Identity);

			/**
			* Safely spawn an StaticMeshActor with the given payload.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param Shot
			* @param Transform		(optional)
			* @param Log			(optional)
			* return				Spawned StaticMeshActor
			*/
			static const FCsStaticMeshActorPooled* SafeSpawn(const FString& Context, const UObject* WorldContext, const PooledPayloadType* PooledPayload, const FCsStaticMeshActorPooledInfo& Info, const FTransform& Transform = FTransform::Identity, void(*Log)(const FString&) = &FCsLog::Warning);

		#undef PooledPayloadType

		#pragma endregion Spawn
		};
	}
}