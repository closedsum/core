// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/Payload/CsLibrary_Payload_SkeletalMeshActor.h"

// Library
#include "Library/CsLibrary_SkeletalMesh.h"
#include "Library/CsLibrary_Valid.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// StaticMesh
#include "Managers/SkeletalMesh/Payload/CsPayload_SkeletalMeshActorImpl.h"
#include "Managers/SkeletalMesh/Params/CsParams_SkeletalMeshActor.h"

namespace NCsSkeletalMeshActor
{
	namespace NPayload
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSkeletalMeshActor::NPayload::FLibrary, SetSafe);
				}
			}
		}

		#define PayloadType NCsSkeletalMeshActor::NPayload::IPayload
		bool FLibrary::IsValidChecked(const FString& Context, PayloadType* Payload)
		{
		#undef PayloadType

			// Check SkeletalMesh is Valid
			checkf(Payload->GetSkeletalMesh(), TEXT("%s: SkeletalMesh is NULL."), *Context);

			// Check Bone is Valid
			// TODO: Need to have support for Socket
			typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;

			PooledPayloadType* PooledPayload = GetInterfaceChecked<PooledPayloadType>(Context, Payload);

			if (USkeletalMeshComponent* Component = Cast<USkeletalMeshComponent>(PooledPayload->GetParent()))
			{
				if (USkeletalMesh* Mesh = Component->SkeletalMesh)
				{
					typedef NCsSkeletalMesh::FLibrary SkeletalMeshLibrary;

					SkeletalMeshLibrary::IsBoneValidChecked(Context, Component, Payload->GetBone());
				}
			}

			// Params
			typedef NCsSkeletalMeshActor::NParams::IParams ParamsType;

			if (ParamsType* Params = Payload->GetParams())
			{
				// OneShot - Anim Sequence
				{
					typedef NCsSkeletalMeshActor::NParams::NAnim::NSequence::FOneShot ShotType;

					if (ShotType* Shot = NCsInterfaceMap::SafePureStaticCastChecked<ShotType, ParamsType>(Context, Params))
					{
						check(Shot->IsValidChecked(Context));
					}
				}
				// OneShot - Anim Montage
				{
					typedef NCsSkeletalMeshActor::NParams::NAnim::NMontage::FOneShot ShotType;

					if (ShotType* Shot = NCsInterfaceMap::SafePureStaticCastChecked<ShotType, ParamsType>(Context, Params))
					{
						check(Shot->IsValidChecked(Context));
					}
				}
			}
			return true;
		}

		#define PayloadImplType NCsSkeletalMeshActor::NPayload::FImpl
		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

		#define ShotType NCsSkeletalMeshActor::NAnim::NSequence::FOneShot

		void FLibrary::SetChecked(const FString& Context, PayloadImplType* Payload, const ShotType& Shot)
		{
			CS_IS_PTR_NULL_CHECKED(Payload)

			check(Shot.IsValidChecked(Context));

			Payload->Mesh = Shot.GetMesh();

			Payload->SetMaterials(Shot.GetMaterials());

			Payload->DeallocateMethod		  = Shot.GetDeallocateMethod();
			Payload->LifeTime				  = Shot.GetLifeTime();
			Payload->AttachmentTransformRules = Shot.GetAttachmentTransformRules();
			Payload->Bone					  = Shot.GetBone();
			Payload->TransformRules			  = Shot.GetTransformRules();

			Payload->Transform.SetTranslation(Payload->Transform.GetTranslation() + Shot.GetTransform().GetTranslation());
			const FRotator Rotation = Payload->Transform.GetRotation().Rotator() + Shot.GetTransform().GetRotation().Rotator();
			Payload->Transform.SetRotation(Rotation.Quaternion());
			Payload->Transform.SetScale3D(Payload->Transform.GetScale3D() * Shot.GetTransform().GetScale3D());

			typedef NCsSkeletalMeshActor::NParams::NAnim::NSequence::FOneShot ParamsType;

			Payload->Params	= const_cast<ParamsType*>(Shot.GetParamsPtr());
		}

		void FLibrary::SetChecked(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const ShotType& Shot)
		{
			SetChecked(Context, Payload, Shot);

			Payload->Instigator						= PooledPayload->GetInstigator();
			Payload->Owner							= PooledPayload->GetOwner();
			Payload->Parent							= PooledPayload->GetParent();
			Payload->Time							= PooledPayload->GetTime();
			Payload->PreserveChangesFromDefaultMask = PooledPayload->GetPreserveChangesFromDefaultMask();
		}

		void FLibrary::SetSafe(const FString& Context, PayloadImplType* Payload, const ShotType& Shot, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL_EXIT(Payload)

			if (!Shot.IsValid(Context, Log))
				return;

			SetChecked(Context, Payload, Shot);
		}

		void FLibrary::SetSafe(PayloadImplType* Payload, const ShotType& Shot)
		{
			using namespace NCsSkeletalMeshActor::NPayload::NLibrary::NCached;

			const FString& Context = Str::SetSafe;

			SetSafe(Context, Payload, Shot, nullptr);
		}

		void FLibrary::SetSafe(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const ShotType& Shot, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL_CHECKED(Payload)

			CS_IS_PTR_NULL_CHECKED(PooledPayload)

			if (!Shot.IsValid(Context, Log))
				return;

			SetChecked(Context, Payload, PooledPayload, Shot);
		}

		void FLibrary::SetSafe(PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const ShotType& Shot)
		{
			using namespace NCsSkeletalMeshActor::NPayload::NLibrary::NCached;

			const FString& Context = Str::SetSafe;

			SetSafe(Context, Payload, PooledPayload, Shot, nullptr);
		}

		#undef ShotType

		#define ShotType NCsSkeletalMeshActor::NAnim::NMontage::FOneShot

		void FLibrary::SetChecked(const FString& Context, PayloadImplType* Payload, const ShotType& Shot)
		{
			CS_IS_PTR_NULL_CHECKED(Payload)

			check(Shot.IsValidChecked(Context));

			Payload->Mesh = Shot.GetMesh();

			Payload->SetMaterials(Shot.GetMaterials());

			Payload->DeallocateMethod		  = Shot.GetDeallocateMethod();
			Payload->LifeTime				  = Shot.GetLifeTime();
			Payload->AttachmentTransformRules = Shot.GetAttachmentTransformRules();
			Payload->Bone					  = Shot.GetBone();
			Payload->TransformRules			  = Shot.GetTransformRules();

			Payload->Transform.SetTranslation(Payload->Transform.GetTranslation() + Shot.GetTransform().GetTranslation());
			const FRotator Rotation = Payload->Transform.GetRotation().Rotator() + Shot.GetTransform().GetRotation().Rotator();
			Payload->Transform.SetRotation(Rotation.Quaternion());
			Payload->Transform.SetScale3D(Payload->Transform.GetScale3D() * Shot.GetTransform().GetScale3D());

			typedef NCsSkeletalMeshActor::NParams::NAnim::NMontage::FOneShot ParamsType;

			Payload->Params	= const_cast<ParamsType*>(Shot.GetParamsPtr());
		}

		void FLibrary::SetChecked(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const ShotType& Shot)
		{
			SetChecked(Context, Payload, Shot);

			Payload->Instigator						= PooledPayload->GetInstigator();
			Payload->Owner							= PooledPayload->GetOwner();
			Payload->Parent							= PooledPayload->GetParent();
			Payload->Time							= PooledPayload->GetTime();
			Payload->PreserveChangesFromDefaultMask = PooledPayload->GetPreserveChangesFromDefaultMask();
		}

		void FLibrary::SetSafe(const FString& Context, PayloadImplType* Payload, const ShotType& Shot, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL_EXIT(Payload)

			if (!Shot.IsValid(Context, Log))
				return;

			SetChecked(Context, Payload, Shot);
		}

		void FLibrary::SetSafe(PayloadImplType* Payload, const ShotType& Shot)
		{
			using namespace NCsSkeletalMeshActor::NPayload::NLibrary::NCached;

			const FString& Context = Str::SetSafe;

			SetSafe(Context, Payload, Shot, nullptr);
		}

		void FLibrary::SetSafe(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const ShotType& Shot, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL_EXIT(Payload)

			CS_IS_PTR_NULL_EXIT(PooledPayload)

			if (!Shot.IsValid(Context, Log))
				return;

			SetChecked(Context, Payload, PooledPayload, Shot);
		}

		void FLibrary::SetSafe(PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const ShotType& Shot)
		{
			using namespace NCsSkeletalMeshActor::NPayload::NLibrary::NCached;

			const FString& Context = Str::SetSafe;

			SetSafe(Context, Payload, PooledPayload, Shot, nullptr);
		}

		#undef ShotType

		#undef PayloadImplType
		#undef PooledPayloadType
	}
}