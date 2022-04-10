// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/FX/CsTypes_FX.h"
// Log
#include "Utility/CsLog.h"

class UObject;
class UCsManager_FX_Actor;
struct FCsFXActorPooled;

// NCsFX::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NPayload, IPayload)
// NCsFX::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NPayload, FImpl)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

namespace NCsFX
{
	namespace NManager
	{
		/**
		*/
		struct CSCORE_API FLibrary final
		{
		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_FX from a WorldContext.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_FX.
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_FX from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				Context for UCsManager_FX.
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_FX from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_FX.
			*/
			static UObject* GetSafeContextRoot(const UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const UObject* WorldContext)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region
		public:

			/**
			* Get the reference to UCsManager_FX_Actor from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_FX_Actor.
			*/
			static UCsManager_FX_Actor* GetChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get the reference to UCsManager_FX_Actor from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				UCsManager_FX_Actor.
			*/
			static UCsManager_FX_Actor* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely get the reference to UCsManager_FX_Actor from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_FX_Actor.
			*/
			static UCsManager_FX_Actor* GetSafe(const UObject* WorldContext);

		#pragma endregion Get

		// Pool
		#pragma region
		public:

			/**
			* 
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				
			*/
			static bool IsNoneAllocatedChecked(const FString& Context, const UObject* WorldContext);

		#pragma endregion Pool

		// Allocate / Deallocate
		#pragma region
		public:

		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

		#define PayloadType NCsFX::NPayload::IPayload
		
			/**
			* Allocate a Payload given the FX information
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param FX
			* @param Transform		(optional)
			* return				Payload
			*/
			static PayloadType* AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform& Transform = FTransform::Identity);

			/**
			* Allocate a Payload given the FX information
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param FX
			* @param Location		
			* return				Payload
			*/
			static PayloadType* AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FVector& Location);

			/**
			* Allocate a Payload given the FX information
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param FX
			* @param Transform		(optional)
			* return				Payload
			*/
			static PayloadType* AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, const FCsFX& FX, const FTransform& Transform = FTransform::Identity);

		#undef PayloadType

		#define PayloadImplType NCsFX::NPayload::FImpl

			/**
			* Allocate a Payload given the FX information
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param FX
			* @param Transform		(optional)
			* return				Payload
			*/
			static PayloadImplType* AllocatePayloadImplChecked(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform& Transform = FTransform::Identity);

			/**
			* Allocate a Payload given the FX information
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param FX
			* @param Location		
			* return				Payload
			*/
			static PayloadImplType* AllocatePayloadImplChecked(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FVector& Location);

			/**
			* Allocate a Payload given the FX information
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param FX
			* @param Transform		(optional)
			* return				Payload
			*/
			static PayloadImplType* AllocatePayloadImplChecked(const FString& Context, const UObject* WorldContext, const FCsFX& FX, const FTransform& Transform = FTransform::Identity);

		#undef PayloadImplType

		#undef PooledPayloadType

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return
			*/
			static void QueueDeallocateAllChecked(const FString& Context, const UObject* WorldContext);

		#pragma endregion Allocate / Deallocate

		// Spawn
		#pragma region
		public:

		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

			/**
			* Spawn an FX with the given payload.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param FX
			* @param Transform		(optional) Transform to apply the fx after allocation and before playing.
			*						FX.Transform is applied as an "offset".
			* return				Spawned FX
			*/
			static const FCsFXActorPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform& Transform = FTransform::Identity);

			/**
			* Safely spawn an FX with the given payload.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param FX
			* @param Transform		(optional) Transform to apply the fx after allocation and before playing.
			*						FX.Transform is applied as an "offset".
			* @param Log			(optional)
			* return				Spawned FX
			*/
			static const FCsFXActorPooled* SafeSpawn(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform& Transform = FTransform::Identity, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely spawn an FX with the given payload.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param FX
			* @param Transform		(optional) Transform to apply the fx after allocation and before playing.
			*						FX.Transform is applied as an "offset".
			* return				Spawned FX
			*/
			static const FCsFXActorPooled* SafeSpawn(const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform& Transform = FTransform::Identity);

			/**
			* Spawn an FX with the given payload.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param FX
			* @param Location		Location to apply the fx after allocation and before playing.
			*						FX.Transform is applied as an "offset".
			* return				Spawned FX
			*/
			static const FCsFXActorPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FVector& Location);

		#undef PooledPayloadType

			/**
			* Spawn an FX with the given payload.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param FX
			* @param Transform		(optional) Transform to apply the fx after allocation and before playing.
			*						FX.Transform is applied as an "offset".
			* return				Spawned FX
			*/
			static const FCsFXActorPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, const FCsFX& FX, const FTransform& Transform = FTransform::Identity);

			/**
			* Safely spawn an FX with the given payload.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param FX
			* @param Transform		(optional) Transform to apply the fx after allocation and before playing.
			*						FX.Transform is applied as an "offset".
			* @param Log			(optional)
			* return				Spawned FX
			*/
			static const FCsFXActorPooled* SafeSpawn(const FString& Context, const UObject* WorldContext, const FCsFX& FX, const FTransform& Transform = FTransform::Identity, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely spawn an FX with the given payload.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param FX
			* @param Transform		(optional) Transform to apply the fx after allocation and before playing.
			*						FX.Transform is applied as an "offset".
			* return				Spawned FX
			*/
			static const FCsFXActorPooled* SafeSpawn(const UObject* WorldContext, const FCsFX& FX, const FTransform& Transform = FTransform::Identity);

		#pragma endregion Spawn
		};
	}
}