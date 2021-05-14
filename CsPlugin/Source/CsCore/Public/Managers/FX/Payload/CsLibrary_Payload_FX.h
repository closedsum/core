// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Payload/CsPayload_FX.h"
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Log
#include "Utility/CsLog.h"
#pragma once

// NCsFX::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NPayload, FImpl)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

namespace NCsFX
{
	namespace NPayload
	{
		#define PayloadType NCsFX::NPayload::IPayload

		struct CSCORE_API FLibrary : public TCsLibrary_InterfaceMap<PayloadType>
		{
		

			/**
			* Check if the Payload is Valid with checks.
			* 
			* @param Context	The calling context.
			* @param Payload
			* return
			*/
			static bool IsValidChecked(const FString& Context, PayloadType* Payload);

			/**
			* Check if the Payload is Valid.
			*
			* @param Context	The calling context.
			* @param Payload
			* @param Log
			* return
			*/
			static bool IsValid(const FString& Context, PayloadType* Payload, void(*Log)(const FString&) = &FCsLog::Warning);

		#define PayloadImplType NCsFX::NPayload::FImpl
		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

			/**
			* Set the contents of Payload with FX.
			* 
			* @param Context	The calling context.
			* @param Payload
			* @param FX
			* @param Transform	(optional) Transform to apply the sound after allocation and before playing.
			*					Sound.Transform is applied as an "offset".
			*/
			static void SetChecked(const FString& Context, PayloadImplType* Payload, const FCsFX& FX, const FTransform& Transform = FTransform::Identity);

			/**
			* Safely set the contents of Payload with FX.
			*
			* @param Context	The calling context.
			* @param Payload
			* @param FX
			* @param Transform	(optional) Transform to apply the sound after allocation and before playing.
			*					Sound.Transform is applied as an "offset".
			* @param Log		(optional)
			*/
			static void SetSafe(const FString& Conext, PayloadImplType* Payload, const FCsFX& FX, const FTransform& Transform = FTransform::Identity, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely set the contents of Payload with FX.
			*
			* @param Payload
			* @param FX
			* @param Transform	(optional) Transform to apply the sound after allocation and before playing.
			*					Sound.Transform is applied as an "offset".
			*/
			static void SetSafe(PayloadImplType* Payload, const FCsFX& FX, const FTransform& Transform = FTransform::Identity);

			/**
			* Set the contents of Payload with PooledPayload and FX.
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			* @param FX
			* @param Transform		(optional) Transform to apply the sound after allocation and before playing.
			*						Sound.Transform is applied as an "offset".
			*/
			static void SetChecked(const FString& Context, PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform& Transform = FTransform::Identity);

			/**
			* Safely set the contents of Payload with PooledPayload and FX.
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			* @param FX
			* @param Transform		(optional) Transform to apply the sound after allocation and before playing.
			*						Sound.Transform is applied as an "offset".
			* @param Log			(optional)
			*/
			static void SetSafe(const FString& Context, PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform& Transform = FTransform::Identity, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely set the contents of Payload with PooledPayload and FX.
			*
			* @param Payload
			* @param PooledPayload
			* @param FX
			* @param Transform		(optional) Transform to apply the sound after allocation and before playing.
			*						Sound.Transform is applied as an "offset".
			*/
			static void SetSafe(PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform& Transform = FTransform::Identity);

		#undef PooledPayloadType
		#undef PayloadImplType
		};

		#undef PayloadType
	}
}