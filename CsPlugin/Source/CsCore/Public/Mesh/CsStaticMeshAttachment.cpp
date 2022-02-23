// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Mesh/CsStaticMeshAttachment.h"

// Library
#include "Managers/StaticMesh/CsLibrary_Manager_StaticMeshActor.h"
#include "Managers/StaticMesh/Payload/CsLibrary_Payload_StaticMeshActor.h"
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_SkeletalMesh.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// StaticMesh
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActorImpl.h"
// Components
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

#define AttachmentType NCsStaticMesh::NAttachment::FAttachment

void FCsStaticMeshAttachment::CopyToAttachment(AttachmentType* Attachment)
{
	Attachment->SetMesh(Mesh.GetPtr());
	Attachment->SetMaterials(Materials.GetPtr());
	Attachment->SetAttachmentTransformRules(&AttachmentTransformRules);
	Attachment->SetBone(&Bone);
	Attachment->SetTransformRules(&TransformRules);
	Attachment->SetTransform(&Transform);
}

void FCsStaticMeshAttachment::CopyToAttachmentAsValue(AttachmentType* Attachment) const
{
	Attachment->SetMesh(Mesh.Get());
	
	const TArray<UMaterialInterface*>& Mats = Materials.Get();

	const int32 Count = Mats.Num();

	TArray<UMaterialInterface*>* MatsPtr = Attachment->GetMaterialsPtr();

	MatsPtr->Reset(Count);
	MatsPtr->Append(Mats);

	Attachment->SetAttachmentTransformRules(AttachmentTransformRules);
	Attachment->SetBone(Bone);
	Attachment->SetTransformRules(TransformRules);
	Attachment->SetTransform(Transform);
}

#undef AttachmentType

bool FCsStaticMeshAttachment::IsValidChecked(const FString& Context) const
{
	// Check Mesh is Valid
	CS_IS_VALID_CHECKED(Mesh);
	// Check Materials is Valid
	CS_IS_VALID_CHECKED(Materials);
	// Check AttachmentTransformRules is Valid
	CS_IS_ENUM_VALID_CHECKED(EMCsAttachmentTransformRules, AttachmentTransformRules);
	// Check Transform is Valid
	if (!Transform.Equals(FTransform::Identity))
	{
		checkf(TransformRules != 0, TEXT("%s: No TransformRules set for Transform: %s."), *Context, *(Transform.ToString()));
	}
	// Transform.Scale is Valid
	CS_IS_VECTOR_ZERO_CHECKED(Transform.GetScale3D())

	typedef NCsMaterial::FLibrary MaterialLibrary;

	check(MaterialLibrary::IsValidChecked(Context, Mesh.GetChecked(Context), Materials.GetChecked(Context)))
	return true;
}

bool FCsStaticMeshAttachment::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check Mesh is Valid
	CS_IS_VALID(Mesh)
	// Check Materials is Valid
	CS_IS_VALID(Materials)
	// Check AttachmentTransformRules is Valid
	CS_IS_ENUM_VALID(EMCsAttachmentTransformRules, ECsAttachmentTransformRules, AttachmentTransformRules)
	// Check Transform is Valid
	if (!Transform.Equals(FTransform::Identity))
	{
		if (TransformRules == 0)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No TransformRules set for Transform: %s."), *Context, *(Transform.ToString())));
			return true;
		}
	}
	// Transform.Scale is Valid
	CS_IS_VECTOR_ZERO(Transform.GetScale3D())

	typedef NCsMaterial::FLibrary MaterialLibrary;

	if (!MaterialLibrary::IsValid(Context, Mesh.GetChecked(Context), Materials.GetChecked(Context), Log))
		return false;
	return true;
}

void FCsStaticMeshAttachment::AttachChecked(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child) const
{
	CS_IS_PTR_NULL_CHECKED(Parent)

	CS_IS_PTR_NULL_CHECKED(Child)

	check(IsValidChecked(Context));

	typedef NCsSkeletalMesh::FLibrary SkeletalMeshLibrary;

	check(SkeletalMeshLibrary::ConditionalIsBoneOrSocketValidChecked(Context, Parent, Bone));

	Child->AttachToComponent(Parent, NCsAttachmentTransformRules::ToRule(AttachmentTransformRules), Bone);
	NCsTransformRules::SetRelativeTransform(Child, Transform, TransformRules);
	Child->SetStaticMesh(Mesh.GetChecked(Context));

	typedef NCsMaterial::FLibrary MaterialLibrary;

	MaterialLibrary::SetChecked(Context, Child, Materials.GetChecked(Context));
}

bool FCsStaticMeshAttachment::AttachSafe(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_PTR_NULL(Parent)

	CS_IS_PTR_NULL(Child)

	if (!IsValid(Context, Log))
		return false;

	typedef NCsSkeletalMesh::FLibrary SkeletalMeshLibrary;

	if (!SkeletalMeshLibrary::ConditionalSafeIsBoneOrSocketValid(Context, Parent, Bone, Log))
		return false;

	Child->AttachToComponent(Parent, NCsAttachmentTransformRules::ToRule(AttachmentTransformRules), Bone);
	NCsTransformRules::SetRelativeTransform(Child, Transform, TransformRules);
	Child->SetStaticMesh(Mesh.GetChecked(Context));

	typedef NCsMaterial::FLibrary MaterialLibrary;

	MaterialLibrary::SetChecked(Context, Child, Materials.GetChecked(Context));
	return true;
}

FCsStaticMeshActorPooled* FCsStaticMeshAttachment::AttachChecked(const FString& Context, const UObject* WorldContext, USceneComponent* Parent) const
{
	CS_IS_PTR_NULL_CHECKED(Parent)

	check(IsValidChecked(Context));

	typedef NCsStaticMeshActor::NManager::FLibrary StaticMeshManagerLibrary;
	typedef NCsStaticMeshActor::NPayload::FLibrary PayloadLibrary;
	typedef NCsStaticMeshActor::NPayload::IPayload PayloadType;
	typedef NCsStaticMeshActor::NPayload::FImpl PayloadImplType;

	const FECsStaticMeshActor& DefaultType = NCsStaticMeshActor::GetDefault();

	PayloadType* Payload		 = StaticMeshManagerLibrary::AllocatePayloadChecked(Context, WorldContext, DefaultType);
	PayloadImplType* PayloadImpl = PayloadLibrary::PureStaticCastChecked<PayloadImplType>(Context, Payload);

	PayloadImpl->Parent = Parent;
	PayloadImpl->Mesh   = Mesh.GetChecked(Context);
	PayloadImpl->SetMaterials(Materials.GetChecked(Context));
	PayloadImpl->Bone			= Bone;
	PayloadImpl->TransformRules = TransformRules;
	PayloadImpl->Transform		= Transform;

	const FCsStaticMeshActorPooled* Object = StaticMeshManagerLibrary::SpawnChecked(Context, WorldContext, DefaultType, Payload);

	return const_cast<FCsStaticMeshActorPooled*>(Object);
}

namespace NCsStaticMesh
{
	namespace NAttachment
	{
		bool FAttachment::IsValidChecked(const FString& Context) const
		{
			// Check GetMesh() is Valid
			CS_IS_PTR_NULL_CHECKED(GetMesh())
			// Check GetMaterials() is Valid
			CS_IS_ARRAY_EMPTY_CHECKED(GetMaterials(), UMaterialInterface*)
			CS_IS_ARRAY_ANY_NULL_CHECKED(GetMaterials(), UMaterialInterface)
			// Check GetAttachmentTransformRules() is Valid
			CS_IS_ENUM_VALID_CHECKED(EMCsAttachmentTransformRules, GetAttachmentTransformRules());
			// Check GetTransform() is Valid
			if (!GetTransform().Equals(FTransform::Identity))
			{
				checkf(GetTransformRules() != 0, TEXT("%s: No GetTransformRules() set for GetTransform(): %s."), *Context, *(GetTransform().ToString()));
			}
			// GetTransform().GetScale() is Valid
			CS_IS_VECTOR_ZERO_CHECKED(GetTransform().GetScale3D())

			typedef NCsMaterial::FLibrary MaterialLibrary;

			check(MaterialLibrary::IsValidChecked(Context, GetMesh(), GetMaterials()))
			return true;
		}

		bool FAttachment::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			// Check Mesh is Valid
			CS_IS_PTR_NULL(GetMesh())
			// Check Materials is Valid
			CS_IS_ARRAY_EMPTY(GetMaterials(), UMaterialInterface*)
			CS_IS_ARRAY_ANY_NULL(GetMaterials(), UMaterialInterface)
			// Check GetAttachmentTransformRules is Valid
			CS_IS_ENUM_VALID(EMCsAttachmentTransformRules, ECsAttachmentTransformRules, GetAttachmentTransformRules())
			// Check GetTransform() is Valid
			if (!GetTransform().Equals(FTransform::Identity))
			{
				if (GetTransformRules() == 0)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No GetTransformRules() set for GetTransform(): %s."), *Context, *(GetTransform().ToString())));
					return true;
				}
			}
			// GetTransform().GetScale() is Valid
			CS_IS_VECTOR_ZERO(GetTransform().GetScale3D())

			typedef NCsMaterial::FLibrary MaterialLibrary;

			if (!MaterialLibrary::IsValid(Context, GetMesh(), GetMaterials(), Log))
				return false;
			return true;
		}

		void FAttachment::AttachChecked(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child) const
		{
			CS_IS_PTR_NULL_CHECKED(Parent)

			CS_IS_PTR_NULL_CHECKED(Child);

			check(IsValidChecked(Context));

			typedef NCsSkeletalMesh::FLibrary SkeletalMeshLibrary;

			check(SkeletalMeshLibrary::ConditionalIsBoneOrSocketValidChecked(Context, Parent, GetBone()));

			Child->AttachToComponent(Parent, NCsAttachmentTransformRules::ToRule(GetAttachmentTransformRules()), GetBone());
			NCsTransformRules::SetRelativeTransform(Child, GetTransform(), GetTransformRules());
			Child->SetStaticMesh(GetMesh());

			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::SetChecked(Context, Child, GetMaterials());
		}

		bool FAttachment::AttachSafe(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			CS_IS_PTR_NULL(Parent)

			CS_IS_PTR_NULL(Child);

			if (!IsValid(Context, Log))
				return false;

			typedef NCsSkeletalMesh::FLibrary SkeletalMeshLibrary;

			if (!SkeletalMeshLibrary::ConditionalSafeIsBoneOrSocketValid(Context, Parent, GetBone(), Log))
				return false;

			Child->AttachToComponent(Parent, NCsAttachmentTransformRules::ToRule(GetAttachmentTransformRules()), GetBone());
			NCsTransformRules::SetRelativeTransform(Child, GetTransform(), GetTransformRules());
			Child->SetStaticMesh(GetMesh());

			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::SetSafe(Context, Child, GetMaterials(), Log);
			return true;
		}

		FCsStaticMeshActorPooled* FAttachment::AttachChecked(const FString& Context, const UObject* WorldContext, USceneComponent* Parent) const
		{
			CS_IS_PTR_NULL_CHECKED(Parent)

			check(IsValidChecked(Context));

			typedef NCsStaticMeshActor::NManager::FLibrary StaticMeshManagerLibrary;
			typedef NCsStaticMeshActor::NPayload::FLibrary PayloadLibrary;
			typedef NCsStaticMeshActor::NPayload::IPayload PayloadType;
			typedef NCsStaticMeshActor::NPayload::FImpl PayloadImplType;

			const FECsStaticMeshActor& DefaultType = NCsStaticMeshActor::GetDefault();

			PayloadType* Payload		 = StaticMeshManagerLibrary::AllocatePayloadChecked(Context, WorldContext, DefaultType);
			PayloadImplType* PayloadImpl = PayloadLibrary::PureStaticCastChecked<PayloadImplType>(Context, Payload);

			PayloadImpl->Parent = Parent;
			PayloadImpl->Mesh   = GetMesh();
			PayloadImpl->SetMaterials(GetMaterials());
			PayloadImpl->Bone			= GetBone();
			PayloadImpl->TransformRules = GetTransformRules();
			PayloadImpl->Transform		= GetTransform();

			const FCsStaticMeshActorPooled* Object = StaticMeshManagerLibrary::SpawnChecked(Context, WorldContext, DefaultType, Payload);

			return const_cast<FCsStaticMeshActorPooled*>(Object);
		}
	}
}