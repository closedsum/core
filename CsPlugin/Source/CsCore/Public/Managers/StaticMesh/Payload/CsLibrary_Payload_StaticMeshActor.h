// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActor.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

// NCsStaticMeshActor::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStaticMeshActor, NPayload, FImpl)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

namespace NCsStaticMeshActor
{
	namespace NPayload
	{
	#define PayloadType NCsStaticMeshActor::NPayload::IPayload

		struct CSCORE_API FLibrary final : public TCsLibrary_InterfaceMap<PayloadType>
		{
		public:

			/**
			*/
			static bool IsValidChecked(const FString& Context, PayloadType* Payload);

		#define PayloadImplType NCsStaticMeshActor::NPayload::FImpl
		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

			/**
			* Set the contents of the Payload with PooledPayload.
			*
			* @param Context	The calling context.
			* @param Payload
			* @param Shot
			*/
			static void SetChecked(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload);

			/**
			* Safely set the contents of Payload with PooledPayload.
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			* @param Log
			*/
			static void SetSafe(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely set the contents of Payload with PooledPayload.
			*
			* @param Payload
			* @param PooledPayload
			*/
			static void SetSafe(PayloadImplType* Payload, const PooledPayloadType* PooledPayload);

		#undef PayloadImplType
		#undef PooledPayloadType
		};

	#undef PayloadType
	}
}