// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsLog.h"

#pragma once

class UObject;
class UCsManager_SkeletalMeshActor;
struct FCsSkeletalMeshActorPooled;

// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// NCsSkeletalMeshActor::NAnim::NSequence::FOneShot
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSkeletalMeshActor, NAnim, NSequence, FOneShot)
// NCsSkeletalMeshActor::NAnim::NMontage::FOneShot
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSkeletalMeshActor, NAnim, NMontage, FOneShot)

namespace NCsSkeletalMeshActor
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
			* Get the Context (Root) for UCsManager_SkeletalMeshActor from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_SkeletalMeshActor
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_SkeletalMeshActor from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				Context for UCsManager_SkeletalMeshActor
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_SkeletalMeshActor from a WorldContext.
			*
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_SkeletalMeshActor
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
			* Get the reference to UCsManager_SkeletalMeshActor from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_SkeletalMeshActor.
			*/
			static UCsManager_SkeletalMeshActor* GetChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get the reference to UCsManager_SkeletalMeshActor from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				UCsManager_SkeletalMeshActor.
			*/
			static UCsManager_SkeletalMeshActor* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely get the reference to UCsManager_SkeletalMeshActor from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				UCsManager_SkeletalMeshActor.
			*/
			static UCsManager_SkeletalMeshActor* GetSafe(const UObject* WorldContext);

		#pragma endregion Get

		// Spawn
		#pragma region
		public:

		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

		#define ShotType NCsSkeletalMeshActor::NAnim::NSequence::FOneShot

			/**
			* Spawn an SkeletalMeshActor with the given payload.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param Shot
			* @param Transform		(optional)
			* return				Spawned SkeletalMeshActor
			*/
			static const FCsSkeletalMeshActorPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, const PooledPayloadType* PooledPayload, const ShotType& Shot, const FTransform& Transform = FTransform::Identity);

			/**
			* Safely spawn an SkeletalMeshActor with the given payload.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param Shot
			* @param Transform		(optional)
			* @param Log			(optional)
			* return				Spawned SkeletalMeshActor
			*/
			static const FCsSkeletalMeshActorPooled* SafeSpawn(const FString& Context, const UObject* WorldContext, const PooledPayloadType* PooledPayload, const ShotType& Shot, const FTransform& Transform = FTransform::Identity, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely spawn an SkeletalMeshActor with the given payload.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param Shot
			* return				Spawned SkeletalMeshActor
			*/
			static const FCsSkeletalMeshActorPooled* SafeSpawn(const UObject* WorldContext, const PooledPayloadType* PooledPayload, const ShotType& Shot);

		#undef ShotType

		#define ShotType NCsSkeletalMeshActor::NAnim::NMontage::FOneShot

			/**
			* Spawn an SkeletalMeshActor with the given payload.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param Shot
			* @param Transform		(optional)
			* return				Spawned SkeletalMeshActor
			*/
			static const FCsSkeletalMeshActorPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, const PooledPayloadType* PooledPayload, const ShotType& Shot, const FTransform& Transform = FTransform::Identity);

			/**
			* Safely spawn an SkeletalMeshActor with the given payload.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param Shot
			* @param Transform		(optional)
			* @param Log			(optional)
			* return				Spawned SkeletalMeshActor
			*/
			static const FCsSkeletalMeshActorPooled* SafeSpawn(const FString& Context, const UObject* WorldContext, const PooledPayloadType* PooledPayload, const ShotType& Shot, const FTransform& Transform = FTransform::Identity, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely spawn an SkeletalMeshActor with the given payload.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param Shot
			* return				Spawned SkeletalMeshActor
			*/
			static const FCsSkeletalMeshActorPooled* SafeSpawn(const UObject* WorldContext, const PooledPayloadType* PooledPayload, const ShotType& Shot);

		#undef ShotType

		#undef PooledPayloadType

		#pragma endregion Spawn
		};
	}
}