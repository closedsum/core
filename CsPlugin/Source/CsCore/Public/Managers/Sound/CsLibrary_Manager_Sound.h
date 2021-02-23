// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Sound/CsTypes_Sound.h"

class UObject;
struct FCsSoundPooled;

// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

namespace NCsSound
{
	namespace NManager
	{
		struct CSCORE_API FLibrary final
		{
		public:

			/**
			* Get the Context (Root) for UCsManager_Sound from an Actor.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_Sound
			*/
			static UObject* GetContextRootChecked(const FString& Context, UObject* WorldContext);

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Sound
			* return
			*/
			static const FCsSoundPooled* SpawnChecked(const FString& Context, UObject* WorldContext, const FCsSound& Sound);
		
		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Sound
			* return
			*/
			static const FCsSoundPooled* SpawnChecked(const FString& Context, UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsSound& Sound);

		#undef PooledPayloadType
		};
	}
}