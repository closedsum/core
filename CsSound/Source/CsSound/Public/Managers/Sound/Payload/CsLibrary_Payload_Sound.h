// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/Sound/Payload/CsPayload_Sound.h"
#include "Containers/CsLibrary_InterfaceMap.h"
// Types
#include "Managers/Sound/CsTypes_SoundPooled.h"
// Log
#include "Utility/CsSoundLog.h"

// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// PayloadImplType (NCsSound::NPayload::NImpl::FImpl)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSound, NPayload, NImpl, FImpl)

class USoundBase;

namespace NCsSound
{
	namespace NPayload
	{
		namespace NLibrary
		{
			using PayloadType = NCsSound::NPayload::IPayload;

			struct CSSOUND_API FLibrary : public NCsInterfaceMap::TLibrary<PayloadType>
			{
			private:

				using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
				using PayloadImplType = NCsSound::NPayload::NImpl::FImpl;

			public:

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
				* return
				*/
				static bool SetSafe(const FString& Context, PayloadType* Payload, PooledPayloadType* PooledPayload, const FCsSound& Sound, const FTransform& Transform = FTransform::Identity, void(*Log)(const FString&) = &NCsSound::FLog::Warning);

				/**
				* Safely set the contents of Payload with PoolePayload and Sound
				*
				* @param Payload
				* @param PooledPayload
				* @param Sound
				* @param Transform		(optional) Transform to apply the sound after allocation and before playing.
				*						Sound.Transform is applied as an "offset".
				* return
				*/
				static bool SetSafe(PayloadType* Payload, PooledPayloadType* PooledPayload, const FCsSound& Sound, const FTransform& Transform = FTransform::Identity);

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
				* @param Log		(optional)
				* return
				*/
				static bool SetSafe(const FString& Context, PayloadType* Payload, const FCsSound& Sound, void(*Log)(const FString&) = &NCsSound::FLog::Warning);

				/**
				* Safely set the contents of Payload with Sound
				*
				* @param Context	The calling context.
				* @param Payload
				* @param Sound
				*/
				static bool SetSafe(PayloadType* Payload, const FCsSound& Sound);

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
				* return
				*/
				static bool SetSafe(const FString& Context, PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsSound& Sound, const FTransform& Transform = FTransform::Identity, void(*Log)(const FString&) = &NCsSound::FLog::Warning);

				/**
				* Safely set the contents of Payload with PoolePayload and Sound
				*
				* @param Payload
				* @param PooledPayload
				* @param Sound
				* @param Transform		(optional)
				* return
				*/
				static bool SetSafe(PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsSound& Sound, const FTransform& Transform = FTransform::Identity);

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
				* @param Log		(optional)
				* return
				*/
				static bool SetSafe(const FString& Context, PayloadImplType* Payload, const FCsSound& Sound, void(*Log)(const FString&) = &NCsSound::FLog::Warning);

				/**
				* Set the contents of Payload with Sound
				*
				* @param Payload
				* @param Sound
				* return
				*/
				static bool SetSafe(PayloadImplType* Payload, const FCsSound&);

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
				* @param Log		(optional)
				*/
				static bool SetSafe(const FString& Context, PayloadImplType* Payload, USoundBase* Sound, void(*Log)(const FString&) = &NCsSound::FLog::Warning);

				/**
				* Set the contents of Payload with Sound
				*
				* @param Payload
				* @param Sound
				* return
				*/
				static bool SetSafe(PayloadImplType* Payload, USoundBase* Sound);
			};
		}
	}
}

using CsSoundPayloadLibrary = NCsSound::NPayload::NLibrary::FLibrary;