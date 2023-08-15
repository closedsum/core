// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/FX/Payload/CsPayload_FX.h"
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Log
#include "Utility/CsLog.h"

// NCsFX::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NPayload, FImpl)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

namespace NCsFX
{
	namespace NPayload
	{
		#define PayloadType NCsFX::NPayload::IPayload

		struct CSCORE_API FLibrary final : public NCsInterfaceMap::TLibrary<PayloadType>
		{
		public:

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
			* @param Transform	(optional) Transform to apply the fx after allocation and before playing.
			*					FX.Transform is applied as an "offset".
			*/
			static void SetChecked(const FString& Context, PayloadImplType* Payload, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity);

			/**
			* Safely set the contents of Payload with FX.
			*
			* @param Context	The calling context.
			* @param Payload
			* @param FX
			* @param Transform	(optional) Transform to apply the fx after allocation and before playing.
			*					FX.Transform is applied as an "offset".
			* @param Log		(optional)
			*/
			static void SetSafe(const FString& Conext, PayloadImplType* Payload, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely set the contents of Payload with FX.
			*
			* @param Payload
			* @param FX
			* @param Transform	(optional) Transform to apply the fx after allocation and before playing.
			*					FX.Transform is applied as an "offset".
			*/
			static void SetSafe(PayloadImplType* Payload, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity);

			/**
			* Set the contents of Payload with Transform.
			*
			* @param Context	The calling context.
			* @param Payload
			* @param Transform
			*/
			static void SetChecked(const FString& Context, PayloadType* Payload, const FTransform3f& Transform);

			/**
			* Set the contents of Payload with PooledPayload and FX.
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			* @param FX
			* @param Transform		(optional) Transform to apply the fx after allocation and before playing.
			*						FX.Transform is applied as an "offset".
			*/
			static void SetChecked(const FString& Context, PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity);

			/**
			* Safely set the contents of Payload with PooledPayload and FX.
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			* @param FX
			* @param Transform		(optional) Transform to apply the fx after allocation and before playing.
			*						FX.Transform is applied as an "offset".
			* @param Log			(optional)
			*/
			static void SetSafe(const FString& Context, PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely set the contents of Payload with PooledPayload and FX.
			*
			* @param Payload
			* @param PooledPayload
			* @param FX
			* @param Transform		(optional) Transform to apply the fx after allocation and before playing.
			*						FX.Transform is applied as an "offset".
			*/
			static void SetSafe(PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity);

			/**
			* Set the contents of Payload with PooledPayload and FX.
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			* @param FX
			* @param Transform		(optional) Transform to apply the fx after allocation and before playing.
			*						FX.Transform is applied as an "offset".
			*/
			static void SetChecked(const FString& Context, PayloadType* Payload, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity);

			/**
			* Set the contents of Payload with PooledPayload.
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			*/
			static void SetChecked(const FString& Context, PayloadImplType* Payload, PooledPayloadType* PooledPayload);

			/**
			* Set the contents of Payload with PooledPayload.
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			*/
			static void SetChecked(const FString& Context, PayloadType* Payload, PooledPayloadType* PooledPayload);

			/**
			* Apply Transform as an offset to the existing Payload->GetTransform().
			*
			* @param Context	The calling context.
			* @param Payload
			* @param Transform	Transform to apply the sound after allocation and before playing.
			*					Sound.Transform is applied as an "offset".
			*/
			static void ApplyAsOffsetChecked(const FString& Context, PayloadType* Payload, const FTransform3f& Transform);

		#undef PooledPayloadType
		#undef PayloadImplType
		};

		#undef PayloadType
	}
}