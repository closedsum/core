// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/Payload/CsLibrary_Payload_SkeletalMeshActor.h"

// StaticMesh
#include "Managers/SkeletalMesh/Payload/CsPayload_SkeletalMeshActorImpl.h"
#include "Managers/SkeletalMesh/Params/CsParams_SkeletalMeshActor.h"

namespace NCsSkeletalMeshActor
{
	namespace NPayload
	{
		#define PayloadType NCsSkeletalMeshActor::NPayload::IPayload
		bool FLibrary::IsValidChecked(const FString& Context, PayloadType* Payload)
		{
		#undef PayloadType

			// Check SkeletalMesh is Valid
			checkf(Payload->GetSkeletalMesh(), TEXT("%s: SkeletalMesh is NULL."), *Context);
			// Params
			typedef NCsSkeletalMeshActor::NParams::IParams ParamsType;

			if (ParamsType* Params = Payload->GetParams())
			{
				// OneShot
				{
					typedef NCsSkeletalMeshActor::NParams::NAnim::NSequence::FOneShot ShotType;

					if (ShotType* Shot = NCsInterfaceMap::SafePureStaticCastChecked<ShotType, ParamsType>(Context, Params))
					{
						check(Shot->IsValidChecked(Context));
					}
				}
			}
			return true;
		}

		#define PayloadImplType NCsSkeletalMeshActor::NPayload::FImpl
		#define ShotType NCsSkeletalMeshActor::NAnim::NSequence::FOneShot
		void FLibrary::SetPayload(const FString& Context, PayloadImplType* Payload, const ShotType& Shot)
		{
		#undef ShotType
		#undef PayloadImplType

			checkf(Payload, TEXT("%s: Payload is NULL."), *Context);

			check(Shot.IsValidChecked(Context));

			Payload->Mesh					  = Shot.GetMesh();
			Payload->DeallocateMethod		  = Shot.GetDeallocateMethod();
			Payload->LifeTime				  = Shot.GetLifeTime();
			Payload->AttachmentTransformRules = Shot.GetAttachmentTransformRules();
			Payload->Bone					  = Shot.GetBone();
			Payload->TransformRules			  = Shot.GetTransformRules();
			Payload->Transform				  = Shot.GetTransform();

			typedef NCsSkeletalMeshActor::NParams::NAnim::NSequence::FOneShot ParamsType;

			Payload->Params	= const_cast<ParamsType*>(Shot.GetParamsPtr());
		}
	}
}