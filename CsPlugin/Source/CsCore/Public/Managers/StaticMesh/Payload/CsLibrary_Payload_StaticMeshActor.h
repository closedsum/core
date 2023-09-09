// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// StaticMesh
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActor.h"

// NCsStaticMeshActor::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStaticMeshActor, NPayload, FImpl)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

namespace NCsStaticMeshActor
{
	namespace NPayload
	{
	#define PayloadType NCsStaticMeshActor::NPayload::IPayload

		struct CSCORE_API FLibrary final : public NCsInterfaceMap::TLibrary<PayloadType>
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
			* @param PooledPayload
			*/
			static void SetChecked(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload);

			/**
			* Safely set the contents of Payload with PooledPayload.
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			* @param Log
			* return
			*/
			static bool SetSafe(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely set the contents of Payload with PooledPayload.
			*
			* @param Payload
			* @param PooledPayload
			* return
			*/
			static bool SetSafe(PayloadImplType* Payload, const PooledPayloadType* PooledPayload);

			/**
			* Set the contents of the Payload with PooledPayload.
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			* @param Info
			*/
			static void SetChecked(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const FCsStaticMeshActorPooledInfo& Info);

			/**
			* Safely set the contents of Payload with PooledPayload.
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			* @param Info
			* @param Log
			* return
			*/
			static bool SetSafe(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const FCsStaticMeshActorPooledInfo& Info, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely set the contents of Payload with PooledPayload.
			*
			* @param Payload
			* @param PooledPayload
			* @param Info
			* return
			*/
			static bool SetSafe(PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const FCsStaticMeshActorPooledInfo& Info);

		#undef PayloadImplType
		#undef PooledPayloadType
		};

	#undef PayloadType
	}
}