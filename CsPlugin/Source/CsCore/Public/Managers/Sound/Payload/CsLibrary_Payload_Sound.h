// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/Payload/CsPayload_Sound.h"
#include "Containers/CsLibrary_InterfaceMap.h"
// Types
#include "Managers/Sound/CsTypes_Sound.h"
// Log
#include "Utility/CsLog.h"
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

		struct CSCORE_API FLibrary : public NCsInterfaceMap::TLibrary<PayloadType>
		{
		#define PooledPayloadType NCsPooledObject::NPayload::IPayload
		#define PayloadImplType NCsSound::NPayload::FImpl

			/**
			* Check if the Payload is Valid with checks.
			* 
			* @param Context	The calling context.
			* @param Payload
			*/
			static bool IsValidChecked(const FString& Context, PayloadType* Payload);

			/**
			* Set the contents of Payload with PoolePayload and Sound
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			* @param Sound
			* @param Transform		(optional) Transform to apply the sound after allocation and before playing.
			*						Sound.Transform is applied as an "offset".
			*/
			static void SetChecked(const FString& Context, PayloadType* Payload, PooledPayloadType* PooledPayload, const FCsSound& Sound, const FTransform& Transform = FTransform::Identity);

			/**
			* Safely set the contents of Payload with PoolePayload and Sound
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			* @param Sound
			* @param Transform		(optional) Transform to apply the sound after allocation and before playing.
			*						Sound.Transform is applied as an "offset".
			* @param Log			(optional)
			*/
			static void SetSafe(const FString& Context, PayloadType* Payload, PooledPayloadType* PooledPayload, const FCsSound& Sound, const FTransform& Transform = FTransform::Identity, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely set the contents of Payload with PoolePayload and Sound
			*
			* @param Payload
			* @param PooledPayload
			* @param Sound
			* @param Transform		(optional) Transform to apply the sound after allocation and before playing.
			*						Sound.Transform is applied as an "offset".
			*/
			static void SetSafe(PayloadType* Payload, PooledPayloadType* PooledPayload, const FCsSound& Sound, const FTransform& Transform = FTransform::Identity);

			/**
			* Set the contents of Payload with Sound
			*
			* @param Context	The calling context.
			* @param Payload
			* @param Sound
			*/
			static void SetChecked(const FString& Context, PayloadType* Payload, const FCsSound& Sound);

			/**
			* Safely set the contents of Payload with Sound
			*
			* @param Context	The calling context.
			* @param Payload
			* @param Sound
			* @param Log
			*/
			static void SetSafe(const FString& Context, PayloadType* Payload, const FCsSound& Sound, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely set the contents of Payload with Sound
			*
			* @param Context	The calling context.
			* @param Payload
			* @param Sound
			* @param Log
			*/
			static void SetSafe(PayloadType* Payload, const FCsSound& Sound);

			/**
			* Set the contents of Payload with PoolePayload and Sound
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			* @param Sound
			* @param Transform		(optional) Transform to apply the sound after allocation and before playing.
			*						Sound.Transform is applied as an "offset".
			*/
			static void SetChecked(const FString& Context, PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsSound& Sound, const FTransform& Transform = FTransform::Identity);

			/**
			* Safely set the contents of Payload with PoolePayload and Sound
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			* @param Sound
			* @param Transform		(optional) Transform to apply the sound after allocation and before playing.
			*						Sound.Transform is applied as an "offset".
			* @param Log			(optional)
			*/
			static void SetSafe(const FString& Context, PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsSound& Sound, const FTransform& Transform = FTransform::Identity, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely set the contents of Payload with PoolePayload and Sound
			*
			* @param Payload
			* @param PooledPayload
			* @param Sound
			*/
			static void SetSafe(PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsSound& Sound, const FTransform& Transform = FTransform::Identity);

			/**
			* Set the contents of Payload with Sound
			*
			* @param Context	The calling context.
			* @param Payload
			* @param Sound
			*/
			static void SetChecked(const FString& Context, PayloadImplType* Payload, const FCsSound& Sound);

			/**
			* Set the contents of Payload with Sound
			*
			* @param Context	The calling context.
			* @param Payload
			* @param Sound
			*/
			static void SetSafe(const FString& Context, PayloadImplType* Payload, const FCsSound& Sound, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Set the contents of Payload with Sound
			*
			* @param Payload
			* @param Sound
			*/
			static void SetSafe(PayloadImplType* Payload, const FCsSound&);

			/**
			* Set the contents of Payload with Sound
			*
			* @param Context	The calling context.
			* @param Payload
			* @param Sound
			*/
			static void SetChecked(const FString& Context, PayloadImplType* Payload, USoundBase* Sound);

			/**
			* Set the contents of Payload with Sound
			*
			* @param Context	The calling context.
			* @param Payload
			* @param Sound
			*/
			static void SetSafe(const FString& Context, PayloadImplType* Payload, USoundBase* Sound, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Set the contents of Payload with Sound
			*
			* @param Payload
			* @param Sound
			*/
			static void SetSafe(PayloadImplType* Payload, USoundBase* Sound);

		#undef PooledPayloadType
		#undef PayloadImplType
		};

	#undef PayloadType
	}
}