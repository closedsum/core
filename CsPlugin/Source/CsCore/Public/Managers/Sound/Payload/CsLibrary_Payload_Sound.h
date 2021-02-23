// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/Payload/CsPayload_Sound.h"
#include "Containers/CsLibrary_InterfaceMap.h"
// Types
#include "Managers/Sound/CsTypes_Sound.h"
#pragma once

// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// NCsSound::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSound, NPayload, FImpl)

class USoundBase;

namespace NCsSound
{
	namespace NPayload
	{
	#define PayloadType NCsSound::NPayload::IPayload

		struct CSCORE_API FLibrary : public TCsLibrary_InterfaceMap<NCsSound::NPayload::IPayload>
		{
		#define PooledPayloadType NCsPooledObject::NPayload::IPayload
		#define PayloadImplType NCsSound::NPayload::FImpl

			/**
			* 
			* 
			* @param Context	The calling context.
			* @param Payload
			*/
			static bool IsValidChecked(const FString& Context, NCsSound::NPayload::IPayload* Payload);

			/**
			*
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			* @param Sound
			*/
			static void Set(const FString& Context, PayloadType* Payload, PooledPayloadType* PooledPayload, const FCsSound& Sound);

			/**
			*
			*
			* @param Context	The calling context.
			* @param Payload
			* @param Sound
			*/
			static void Set(const FString& Context, NCsSound::NPayload::IPayload* Payload, const FCsSound& Sound);

			/**
			*
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			* @param Sound
			*/
			static void Set(const FString& Context, PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsSound& Sound);

			/**
			* 
			* 
			* @param Context	The calling context.
			* @param Payload
			* @param Sound
			*/
			static void Set(const FString& Context, NCsSound::NPayload::FImpl* Payload, const FCsSound& Sound);

			/**
			*
			*
			* @param Context	The calling context.
			* @param Payload
			* @param Sound
			*/
			static void Set(const FString& Context, NCsSound::NPayload::FImpl* Payload, USoundBase* Sound);

		#undef PooledPayloadType
		#undef PayloadImplType
		};

	#undef PayloadType
	}
}