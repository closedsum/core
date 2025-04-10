// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Cached.h"
#include "CsMacro_Log.h"
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"
// Log
#include "Utility/CsStaticMeshLog.h"

class UObject;
class UCsManager_StaticMeshActor;
struct FCsStaticMeshActorPooled;

// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// PayloadType (NCsStaticMeshActor::NPayload::IPayload)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStaticMeshActor, NPayload, IPayload)
// PayloadImplType (NCsStaticMeshActor::NPayload::NImpl::FImpl)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsStaticMeshActor, NPayload, NImpl, FImpl)

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_2(NCsStaticMeshActor, NManager, Library)

namespace NCsStaticMeshActor
{
	namespace NManager
	{
		struct CSSTATICMESH_API FLibrary final
		{
		private:

			using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
			using PayloadType = NCsStaticMeshActor::NPayload::IPayload;
			using PayloadImplType = NCsStaticMeshActor::NPayload::NImpl::FImpl;

			CS_USING_CACHED_FUNCTION_NAME_NESTED_2(NCsStaticMeshActor, NManager, Library);

			CS_DECLARE_STATIC_LOG_LEVEL

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
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL) { return nullptr; }
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
			static UCsManager_StaticMeshActor* GetSafe(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			/**
			* Safely get the reference to UCsManager_StaticMeshActor from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_StaticMeshActor.
			*/
			static UCsManager_StaticMeshActor* GetSafe(const UObject* WorldContext);

		#pragma endregion Get

		// Payload
		#pragma region
		public:

			/*
			* Allocate a Payload (used to Spawn a StaticMeshActor from Manager_StaticMeshActor).
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* return				Payload
			*/
			static PayloadType* AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, const FECsStaticMeshActor& Type);

			/**
			* Allocate a Payload associated with Type
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* return				Payload
			*/
			static PayloadImplType* AllocatePayloadImplChecked(const FString& Context, const UObject* WorldContext, const FECsStaticMeshActor& Type);

			/**
			* Allocate a Payload associated with Default Type
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Payload
			*/
			FORCEINLINE static PayloadImplType* AllocatePayloadImplChecked(const FString& Context, const UObject* WorldContext)
			{
				return AllocatePayloadImplChecked(Context, WorldContext, NCsStaticMeshActor::GetDefault());
			}

		#pragma endregion Payload

		// Spawn
		#pragma region
		public:

			/**
			* Spawn an StaticMeshActor with the given Payload.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			
			* @param Payload
			* return				Spawned StaticMeshActor
			*/
			static const FCsStaticMeshActorPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, const FECsStaticMeshActor& Type, PayloadType* Payload);

			/**
			* Spawn an StaticMeshActor with the given Pooled Payload, Info and Transform.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param Info
			* @param Transform		(optional)
			* return				Spawned StaticMeshActor
			*/
			static const FCsStaticMeshActorPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, const PooledPayloadType* PooledPayload, const FCsStaticMeshActorPooledInfo& Info, const FTransform& Transform = FTransform::Identity);

			/**
			* Safely spawn an StaticMeshActor with the given Pooled Payload, Info and Transform.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param Info
			* @param Transform		(optional)
			* @param Log			(optional)
			* return				Spawned StaticMeshActor
			*/
			static const FCsStaticMeshActorPooled* SafeSpawn(const FString& Context, const UObject* WorldContext, const PooledPayloadType* PooledPayload, const FCsStaticMeshActorPooledInfo& Info, const FTransform& Transform = FTransform::Identity, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			/**
			* Spawn an StaticMeshActor of Default Type with the given Payload.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* @param Payload
			* return				Spawned StaticMeshActor
			*/
			FORCEINLINE static const FCsStaticMeshActorPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, PayloadType* Payload)
			{
				return SpawnChecked(Context, WorldContext, NCsStaticMeshActor::GetDefault(), Payload);
			}

		#pragma endregion Spawn
		};
	}
}

using CsStaticMeshManagerLibrary = NCsStaticMeshActor::NManager::FLibrary;