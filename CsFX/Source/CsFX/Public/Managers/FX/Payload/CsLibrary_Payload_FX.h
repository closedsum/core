// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/FX/Payload/CsPayload_FX.h"
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Log
#include "Utility/CsFXLog.h"

// NCsFX::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NPayload, FImpl)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

namespace NCsFX
{
	namespace NPayload
	{
		struct CSFX_API FLibrary final : public NCsInterfaceMap::TLibrary<CsFXPayloadType>
		{
		#define LogLevel void(*Log)(const FString&) = &NCsFX::FLog::Warning

		public:

			/**
			* Check if the Payload is Valid with checks.
			* 
			* @param Context	The calling context.
			* @param Payload
			* return
			*/
			static bool IsValidChecked(const FString& Context, CsFXPayloadType* Payload);

			/**
			* Check if the Payload is Valid.
			*
			* @param Context	The calling context.
			* @param Payload
			* @param Log
			* return
			*/
			static bool IsValid(const FString& Context, CsFXPayloadType* Payload, LogLevel);

		#define PayloadImplType NCsFX::NPayload::FImpl
		#define CsPooledObjectPayloadType NCsPooledObject::NPayload::IPayload

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
			static void SetSafe(const FString& Conext, PayloadImplType* Payload, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity, LogLevel);

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
			static void SetChecked(const FString& Context, CsFXPayloadType* Payload, const FTransform3f& Transform);

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
			static void SetChecked(const FString& Context, PayloadImplType* Payload, CsPooledObjectPayloadType* PooledPayload, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity);

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
			static void SetSafe(const FString& Context, PayloadImplType* Payload, CsPooledObjectPayloadType* PooledPayload, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity, LogLevel);

			/**
			* Safely set the contents of Payload with PooledPayload and FX.
			*
			* @param Payload
			* @param PooledPayload
			* @param FX
			* @param Transform		(optional) Transform to apply the fx after allocation and before playing.
			*						FX.Transform is applied as an "offset".
			*/
			static void SetSafe(PayloadImplType* Payload, CsPooledObjectPayloadType* PooledPayload, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity);

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
			static void SetChecked(const FString& Context, CsFXPayloadType* Payload, CsPooledObjectPayloadType* PooledPayload, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity);

			/**
			* Set the contents of Payload with PooledPayload.
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			*/
			static void SetChecked(const FString& Context, PayloadImplType* Payload, CsPooledObjectPayloadType* PooledPayload);

			/**
			* Set the contents of Payload with PooledPayload.
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			*/
			static void SetChecked(const FString& Context, CsFXPayloadType* Payload, CsPooledObjectPayloadType* PooledPayload);

			/**
			* Apply Transform as an offset to the existing Payload->GetTransform().
			*
			* @param Context	The calling context.
			* @param Payload
			* @param Transform	Transform to apply the sound after allocation and before playing.
			*					Sound.Transform is applied as an "offset".
			*/
			static void ApplyAsOffsetChecked(const FString& Context, CsFXPayloadType* Payload, const FTransform3f& Transform);

		#undef CsPooledObjectPayloadType
		#undef PayloadImplType

		#undef LogLevel
		};
	}
}