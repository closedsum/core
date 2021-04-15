// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsLog.h"

#pragma once

class UObject;
struct FCsSkeletalMeshActorPooled;

// NCsPooledObject::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, FImpl)
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
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_SkeletalMeshActor from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_SkeletalMeshActor
			*/
			static UObject* GetContextRootChecked(const FString& Context, UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_SkeletalMeshActor from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				Context for UCsManager_SkeletalMeshActor
			*/
			static UObject* GetSafeContextRoot(const FString& Context, UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_SkeletalMeshActor from a WorldContext.
			*
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_SkeletalMeshActor
			*/
			static UObject* GetSafeContextRoot(UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR

		// Spawn
		#pragma region
		public:

		#define PooledPooledType NCsPooledObject::NPayload::IPayload

		#define ShotType NCsSkeletalMeshActor::NAnim::NSequence::FOneShot

			/**
			* Spawn an SkeletalMeshActor with the given payload.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param Shot
			* return				Spawned SkeletalMeshActor
			*/
			static const FCsSkeletalMeshActorPooled* SpawnChecked(const FString& Context, UObject* WorldContext, const PooledPooledType* PooledPayload, const ShotType& Shot);

			/**
			* Safely spawn an SkeletalMeshActor with the given payload.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param Shot
			* @param Log
			* return				Spawned SkeletalMeshActor
			*/
			static const FCsSkeletalMeshActorPooled* SafeSpawn(const FString& Context, UObject* WorldContext, const PooledPooledType* PooledPayload, const ShotType& Shot, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely spawn an SkeletalMeshActor with the given payload.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param Shot
			* return				Spawned SkeletalMeshActor
			*/
			static const FCsSkeletalMeshActorPooled* SafeSpawn(UObject* WorldContext, const PooledPooledType* PooledPayload, const ShotType& Shot);

		#undef ShotType

		#define ShotType NCsSkeletalMeshActor::NAnim::NMontage::FOneShot

			/**
			* Spawn an SkeletalMeshActor with the given payload.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param Shot
			* return				Spawned SkeletalMeshActor
			*/
			static const FCsSkeletalMeshActorPooled* SpawnChecked(const FString& Context, UObject* WorldContext, const PooledPooledType* PooledPayload, const ShotType& Shot);

			/**
			* Safely spawn an SkeletalMeshActor with the given payload.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param Shot
			* @param Log
			* return				Spawned SkeletalMeshActor
			*/
			static const FCsSkeletalMeshActorPooled* SafeSpawn(const FString& Context, UObject* WorldContext, const PooledPooledType* PooledPayload, const ShotType& Shot, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely spawn an SkeletalMeshActor with the given payload.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param Shot
			* return				Spawned SkeletalMeshActor
			*/
			static const FCsSkeletalMeshActorPooled* SafeSpawn(UObject* WorldContext, const PooledPooledType* PooledPayload, const ShotType& Shot);

		#undef ShotType

		#undef PooledPooledType

		#pragma endregion Spawn
		};
	}
}