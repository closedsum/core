// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/SkeletalMesh/Payload/CsPayload_SkeletalMeshActor.h"
#include "Containers/CsLibrary_InterfaceMap.h"
// Log
#include "Utility/CsSkeletalMeshLog.h"

// NCsSkeletalMeshActor::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSkeletalMeshActor, NPayload, FImpl)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// NCsSkeletalMeshActor::NAnim::NSequence::FOneShot
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSkeletalMeshActor, NAnim, NSequence, FOneShot)
// NCsSkeletalMeshActor::NAnim::NMontage::FOneShot
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSkeletalMeshActor, NAnim, NMontage, FOneShot)

namespace NCsSkeletalMeshActor
{
	namespace NPayload
	{
	#define PayloadType NCsSkeletalMeshActor::NPayload::IPayload

		struct CSSKELETALMESH_API FLibrary final : public NCsInterfaceMap::TLibrary<PayloadType>
		{
		#define LogLevel void(*Log)(const FString&) = &NCsSkeletalMesh::FLog::Warning

		public:

			/**
			*/
			static bool IsValidChecked(const FString& Context, PayloadType* Payload);

		#define PayloadImplType NCsSkeletalMeshActor::NPayload::FImpl
		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

		#define ShotType NCsSkeletalMeshActor::NAnim::NSequence::FOneShot

			/**
			* Set the contents of the Payload with Shot.
			* 
			* @param Context	The calling context.
			* @param Payload
			* @param Shot
			*/
			static void SetChecked(const FString& Context, PayloadImplType* Payload, const ShotType& Shot);

			/**
			* Set the contents of the Payload with Shot.
			*
			* @param Context	The calling context.
			* @param Payload
			* @param Shot
			*/
			static void SetChecked(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const ShotType& Shot);

			/**
			* Safely set the contents of Payload with Shot.
			*
			* @param Context	The calling context.
			* @param Payload
			* @param FX
			* @param Log
			*/
			static void SetSafe(const FString& Conext, PayloadImplType* Payload, const ShotType& Shot, LogLevel);

			/**
			* Safely set the contents of Payload with Shot.
			*
			* @param Payload
			* @param Shot
			*/
			static void SetSafe(PayloadImplType* Payload, const ShotType& Shot);

			/**
			* Safely set the contents of Payload with PooledPayload and Shot.
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			* @param Shot
			* @param Log
			*/
			static void SetSafe(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const ShotType& Shot, LogLevel);

			/**
			* Safely set the contents of Payload with PooledPayload and Shot.
			*
			* @param Payload
			* @param PooledPayload
			* @param Shot
			*/
			static void SetSafe(PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const ShotType& Shot);

		#undef ShotType

		#define ShotType NCsSkeletalMeshActor::NAnim::NMontage::FOneShot

			/**
			* Set the contents of the Payload with Shot.
			* 
			* @param Context	The calling context.
			* @param Payload
			* @param Shot
			*/
			static void SetChecked(const FString& Context, PayloadImplType* Payload, const ShotType& Shot);

			/**
			* Set the contents of the Payload with Shot.
			*
			* @param Context	The calling context.
			* @param Payload
			* @param Shot
			*/
			static void SetChecked(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const ShotType& Shot);

			/**
			* Safely set the contents of Payload with Shot.
			*
			* @param Context	The calling context.
			* @param Payload
			* @param FX
			* @param Log
			*/
			static void SetSafe(const FString& Conext, PayloadImplType* Payload, const ShotType& Shot, LogLevel);

			/**
			* Safely set the contents of Payload with Shot.
			*
			* @param Payload
			* @param Shot
			*/
			static void SetSafe(PayloadImplType* Payload, const ShotType& Shot);

			/**
			* Safely set the contents of Payload with PooledPayload and Shot.
			*
			* @param Context		The calling context.
			* @param Payload
			* @param PooledPayload
			* @param Shot
			* @param Log
			*/
			static void SetSafe(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const ShotType& Shot, LogLevel);

			/**
			* Safely set the contents of Payload with PooledPayload and Shot.
			*
			* @param Payload
			* @param PooledPayload
			* @param Shot
			*/
			static void SetSafe(PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const ShotType& Shot);

		#undef ShotType

		#undef PayloadImplType
		#undef PooledPayloadType

		#undef LogLevel
		};

	#undef PayloadType
	}
}