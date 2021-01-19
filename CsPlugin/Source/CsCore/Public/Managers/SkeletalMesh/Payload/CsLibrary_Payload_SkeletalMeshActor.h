// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/Payload/CsPayload_SkeletalMeshActor.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

// NCsSkeletalMeshActor::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSkeletalMeshActor, NPayload, FImpl)
// NCsSkeletalMeshActor::NAnim::NSequence::FOneShot
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSkeletalMeshActor, NAnim, NSequence, FOneShot)

namespace NCsSkeletalMeshActor
{
	namespace NPayload
	{
	#define PayloadType NCsSkeletalMeshActor::NPayload::IPayload

		struct CSCORE_API FLibrary : public TCsLibrary_InterfaceMap<PayloadType>
		{
		public:

		#define PayloadImplType NCsSkeletalMeshActor::NPayload::FImpl
		#define ShotType NCsSkeletalMeshActor::NAnim::NSequence::FOneShot
			
			/**
			*/
			static bool IsValidChecked(const FString& Context, PayloadType* Payload);

			/**
			* 
			* 
			* @param Context	The calling context.
			* @param Payload
			* @parma Shot
			*/
			static void SetPayload(const FString& Context, PayloadImplType* Payload, const ShotType& Shot);

		#undef PayloadImplType
		#undef ShotType
		};

	#undef PayloadType
	}
}