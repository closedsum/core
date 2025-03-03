// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Cached.h"
#include "CsMacro_Log.h"
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// StaticMesh
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActor.h"
// Log
#include "Utility/CsStaticMeshLog.h"

// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// PayloadImplType (NCsStaticMeshActor::NPayload::NImpl::FImpl)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsStaticMeshActor, NPayload, NImpl, FImpl)

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_3(NCsStaticMeshActor, NPayload, NLibrary, Library)

namespace NCsStaticMeshActor
{
	namespace NPayload
	{
		namespace NLibrary
		{
			using PayloadType = NCsStaticMeshActor::NPayload::IPayload;

			struct CSSTATICMESH_API FLibrary final : public NCsInterfaceMap::TLibrary<PayloadType>
			{
			private:

				using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
				using PayloadImplType = NCsStaticMeshActor::NPayload::NImpl::FImpl;
				
				CS_USING_CACHED_FUNCTION_NAME_NESTED_3(NCsStaticMeshActor, NPayload, NLibrary, Library);

				CS_DECLARE_STATIC_LOG_LEVEL

			public:

				/**
				*/
				static bool IsValidChecked(const FString& Context, PayloadType* Payload);

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
				static bool SetSafe(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

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
				static bool SetSafe(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const FCsStaticMeshActorPooledInfo& Info, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

				/**
				* Safely set the contents of Payload with PooledPayload.
				*
				* @param Payload
				* @param PooledPayload
				* @param Info
				* return
				*/
				static bool SetSafe(PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const FCsStaticMeshActorPooledInfo& Info);
			};
		}
	}
}

using CsStaticMeshActorPayloadLibrary = NCsStaticMeshActor::NPayload::NLibrary::FLibrary;
using CsSMAPayloadLibrary = NCsStaticMeshActor::NPayload::NLibrary::FLibrary;