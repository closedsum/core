// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Sound/CsTypes_SoundPooled.h"
// Log
#include "Utility/CsSoundLog.h"

class UObject;
class UCsManager_Sound;
struct FCsSoundPooled;

// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

// NCsSound::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSound, NPayload, IPayload)
// NCsSound::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSound, NPayload, FImpl)

namespace NCsSound
{
	namespace NManager
	{
		struct CSSOUND_API FLibrary final
		{
		// Print
		#pragma region
		public:

			static FString PrintObjectWithClass(const UCsManager_Sound* Manager);

		#pragma endregion Print

		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Sound from an Actor.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_Sound
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
			* Safely get the Context (Root) for UCsManager_Sound from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				Context for UCsManager_Sound.
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsSound::FLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsSound::FLog::Warning)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_Sound from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_Sound.
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
			* Get the reference to UCsManager_Sound from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_Sound.
			*/
			static UCsManager_Sound* GetChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Get the reference to UCsManager_Sound from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_Sound.
			*/
			template<typename T>
			static T* GetChecked(const FString& Context, const UObject* ContextObject)
			{
				UCsManager_Sound* O = GetChecked(Context, ContextObject);
				T* Other			= Cast<T>(O);

				checkf(Other, TEXT("%s: %s is NOT of type: %s."), *Context, *PrintObjectWithClass(O), *(T::StaticClass()->GetName()));
				return Other;
			}

			/**
			* Safely get the reference to UCsManager_Sound from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				UCsManager_Sound.
			*/
			static UCsManager_Sound* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsSound::FLog::Warning);

			/**
			* Safely get the reference to UCsManager_Sound from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				UCsManager_Sound.
			*/
			template<typename T>
			static T* GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &NCsSound::FLog::Warning)
			{
				UCsManager_Sound* O = GetSafe(Context, ContextObject, Log);

				if (!O)
					return nullptr;

				T* Other = Cast<T>(O);

				if (!Other)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NOT of type: %s."), *Context, *PrintObjectWithClass(O), *(T::StaticClass()->GetName())));
				}
				return Other;
			}

			/**
			* Safely get the reference to UCsManager_Sound from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_Sound.
			*/
			static UCsManager_Sound* GetSafe(const UObject* WorldContext);

		#pragma endregion Get

		// Pool
		#pragma region
		public:

			// Find
		#pragma region
		public:

			static const FCsSoundPooled* FindSafeObject(const FString& Context, const UObject* WorldContext, const FECsSound& Type, const int32& Index, void(*Log)(const FString&) = &NCsSound::FLog::Warning);

		#pragma endregion Find

		#pragma endregion Pool

		// Payload
		#pragma region
		public:

		#define PayloadType NCsSound::NPayload::IPayload
		#define PayloadImplType NCsSound::NPayload::FImpl

			/*
			* Allocate a Payload (used to Spawn a Sound from Manager_Sound).
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* return				Payload
			*/
			static PayloadType* AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, const FECsSound& Type);

			/*
			* Safely allocate a Payload (used to Spawn a Sound from Manager_Sound).
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* @param Log			(optional)
			* return				Payload
			*/
			static PayloadType* SafeAllocatePayload(const FString& Context, const UObject* WorldContext, const FECsSound& Type, void(*Log)(const FString&) = &NCsSound::FLog::Warning);

			/*
			* Allocate a Payload (used to Spawn a Sound from Manager_Sound).
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* return				Payload
			*/
			static PayloadImplType* AllocatePayloadImplChecked(const FString& Context, const UObject* WorldContext, const FECsSound& Type);

		#undef PayloadType
		#undef PayloadImplType

		#pragma endregion Payload

		// Spawn
		#pragma region
		public:

			/**
			* Spawn a sound for UCsManager_Sound from Sound.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Sound
			* return				Spawned Sound in a pooled container.
			*/
			static const FCsSoundPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, const FCsSound& Sound);
		
		#define PayloadType NCsSound::NPayload::IPayload

			/**
			* Spawn a sound for UCsManager_Sound from Sound.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Payload
			* return				Spawned Sound in a pooled container.
			*/
			static const FCsSoundPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, const FECsSound& Type, PayloadType* Payload);

		#undef PayloadType

		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

			/**
			* Spawn a sound for UCsManager_Sound from PooledPayload and Sound.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Sound
			* @param Transform		(optional) Transform to apply the sound after allocation and before playing.
			*						Sound.Transform is applied as an "offset".
			* return				Spawned Sound in a pooled container.
			*/
			static const FCsSoundPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsSound& Sound, const FTransform3f& Transform = FTransform3f::Identity);

		#undef PooledPayloadType

			/**
			* Safely spawn a sound for UCsManager_Sound from Sound.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Sound
			* @param Log			(optional)
			* return				Spawned Sound in a pooled container.
			*/
			static const FCsSoundPooled* SafeSpawn(const FString& Context, const UObject* WorldContext, const FCsSound& Sound, void(*Log)(const FString&) = &NCsSound::FLog::Warning);

		#pragma endregion Spawn
		};
	}
}

using CsSoundManagerLibrary = NCsSound::NManager::FLibrary;