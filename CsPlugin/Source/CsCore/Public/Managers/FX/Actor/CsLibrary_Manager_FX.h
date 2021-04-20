// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/FX/CsTypes_FX.h"
// Log
#include "Utility/CsLog.h"

class UObject;
struct FCsFXActorPooled;

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
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_FX from a WorldContext.
			* 
			* @parma Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_FX.
			*/
			static UObject* GetContextRootChecked(const FString& Context, UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, UObject* WorldContext)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_FX from a WorldContext.
			*
			* @parma Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				Context for UCsManager_FX.
			*/
			static UObject* GetSafeContextRoot(const FString& Context, UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning)
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
			static UObject* GetSafeContextRoot(UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(UObject* WorldContext)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

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
			* return				Spawned FX
			*/
			static const FCsFXActorPooled* SpawnChecked(const FString& Context, UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX);

			/**
			* Safely spawn an FX with the given payload.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param FX
			* @param Log
			* return				Spawned FX
			*/
			static const FCsFXActorPooled* SafeSpawn(const FString& Context, UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely spawn an FX with the given payload.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param FX
			* return				Spawned FX
			*/
			static const FCsFXActorPooled* SafeSpawn(UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX);

		#undef PooledPayloadType

		#pragma endregion Spawn
		};
	}
}