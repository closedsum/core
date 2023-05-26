// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"
// Log
#include "Utility/CsLog.h"

class UObject;
class UCsManager_StaticMeshActor;
struct FCsStaticMeshActorPooled;

// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// NCsStaticMeshActor::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStaticMeshActor, NPayload, IPayload)
// NCsStaticMeshActor::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStaticMeshActor, NPayload, FImpl)

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

		// Payload
		#pragma region
		public:

		#define PayloadType NCsStaticMeshActor::NPayload::IPayload

			/*
			* Allocate a Payload (used to Spawn a StaticMeshActor from Manager_StaticMeshActor).
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* return				Payload
			*/
			static PayloadType* AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, const FECsStaticMeshActor& Type);

		#define PayloadImplType NCsStaticMeshActor::NPayload::FImpl

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

		#undef PayloadImplType

		#undef PayloadType 

		#pragma endregion Payload

		// Spawn
		#pragma region
		public:

		#define PayloadType NCsStaticMeshActor::NPayload::IPayload

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

		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

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
			static const FCsStaticMeshActorPooled* SafeSpawn(const FString& Context, const UObject* WorldContext, const PooledPayloadType* PooledPayload, const FCsStaticMeshActorPooledInfo& Info, const FTransform& Transform = FTransform::Identity, void(*Log)(const FString&) = &FCsLog::Warning);

		#undef PooledPayloadType

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

		#undef PayloadType

		#pragma endregion Spawn
		};
	}
}