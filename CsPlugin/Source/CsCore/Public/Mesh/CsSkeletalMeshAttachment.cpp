// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Mesh/CsSkeletalMeshAttachment.h"

// Library
#include "Managers/SkeletalMesh/CsLibrary_Manager_SkeletalMeshActor.h"
#include "Managers/SkeletalMesh/Payload/CsLibrary_Payload_SkeletalMeshActor.h"
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_SkeletalMesh.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// SkeletalMesh
#include "Managers/SkeletalMesh/Payload/CsPayload_SkeletalMeshActorImpl.h"
// Components
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

#define AttachmentType NCsSkeletalMesh::NAttachment::FAttachment

void FCsSkeletalMeshAttachment::CopyToAttachment(AttachmentType* Attachment)
{
	Attachment->SetMesh(Mesh.GetPtr());
	Attachment->SetMaterials(Materials.GetPtr());
	Attachment->SetbGenerateMIDs(&bGenerateMIDs);
	Attachment->SetAttachmentTransformRules(&AttachmentTransformRules);
	Attachment->SetBone(&Bone);
	Attachment->SetTransformRules(&TransformRules);
	Attachment->SetTransform(&Transform);
	Attachment->SetbCastShadow(&bCastShadow);
	Attachment->SetbReceivesDecals(&bReceivesDecals);
	Attachment->SetbUseAsOccluder(&bUseAsOccluder);
	Attachment->SetbRenderCustomDepth(&bRenderCustomDepth);
	Attachment->SetCustomDepthStencilValue(&CustomDepthStencilValue);
	Attachment->SetTags(&Tags);
	Attachment->SetbSlavePoseComponent(&bSlavePoseComponent);
}

void FCsSkeletalMeshAttachment::CopyToAttachmentAsValue(AttachmentType* Attachment) const
{
	Attachment->SetMesh(Mesh.Get());
	
	const TArray<UMaterialInterface*>& Mats = Materials.Get();

	const int32 Count = Mats.Num();

	TArray<UMaterialInterface*>* MatsPtr = Attachment->GetMaterialsPtr();

	MatsPtr->Reset(Count);
	MatsPtr->Append(Mats);

	Attachment->SetbGenerateMIDs(bGenerateMIDs);
	Attachment->SetAttachmentTransformRules(AttachmentTransformRules);
	Attachment->SetBone(Bone);
	Attachment->SetTransformRules(TransformRules);
	Attachment->SetTransform(Transform);
	Attachment->SetbCastShadow(bCastShadow);
	Attachment->SetbReceivesDecals(bReceivesDecals);
	Attachment->SetbUseAsOccluder(bUseAsOccluder);
	Attachment->SetbRenderCustomDepth(bRenderCustomDepth);
	Attachment->SetCustomDepthStencilValue(CustomDepthStencilValue);
	Attachment->SetTags(Tags);
	Attachment->SetbSlavePoseComponent(bSlavePoseComponent);
}

#undef AttachmentType

bool FCsSkeletalMeshAttachment::IsValidChecked(const FString& Context) const
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
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(CustomDepthStencilValue, 0)
	CS_IS_INT_LESS_THAN_OR_EQUAL_CHECKED(CustomDepthStencilValue, 255)
	// Check Tags is Valid
	CS_IS_TARRAY_ANY_NONE_CHECKED(Tags)
	return true;
}

bool FCsSkeletalMeshAttachment::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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

	CS_IS_INT_GREATER_THAN_OR_EQUAL(CustomDepthStencilValue, 0)
	CS_IS_INT_LESS_THAN_OR_EQUAL(CustomDepthStencilValue, 255)
	// Check Tags is Valid
	CS_IS_TARRAY_ANY_NONE(Tags)
	return true;
}

void FCsSkeletalMeshAttachment::AttachChecked(const FString& Context, USceneComponent* Parent, USkeletalMeshComponent* Child) const
{
	CS_IS_PTR_NULL_CHECKED(Parent)

	CS_IS_PTR_NULL_CHECKED(Child)

	check(IsValidChecked(Context));

	if (bSlavePoseComponent)
	{
		Child->SetSkeletalMesh(Mesh.GetChecked(Context));

		USkeletalMeshComponent* Component = Cast<USkeletalMeshComponent>(Parent);

		checkf(Component, TEXT("%s: if bSlavePoseComponent == true, then Parent: %s with Class: %s MUST be a USkeletalMeshComponent."), *Context, *(Parent->GetName()), *(Parent->GetClass()->GetName()));

		Child->SetMasterPoseComponent(Component);
	}
	else
	{
		typedef NCsSkeletalMesh::FLibrary SkeletalMeshLibrary;

		check(SkeletalMeshLibrary::ConditionalIsBoneOrSocketValidChecked(Context, Parent, Bone));

		Child->AttachToComponent(Parent, NCsAttachmentTransformRules::ToRule(AttachmentTransformRules), Bone);
		NCsTransformRules::SetRelativeTransform(Child, Transform, TransformRules);
		Child->SetSkeletalMesh(Mesh.GetChecked(Context));
	}
	
	Child->SetCastShadow(bCastShadow);
	Child->SetReceivesDecals(bReceivesDecals);
	Child->bUseAsOccluder = bUseAsOccluder;
	Child->SetRenderCustomDepth(bRenderCustomDepth);
	Child->SetCustomDepthStencilValue(CustomDepthStencilValue);

	typedef NCsMaterial::FLibrary MaterialLibrary;

	MaterialLibrary::SetChecked(Context, Child, Materials.GetChecked(Context));
}

bool FCsSkeletalMeshAttachment::AttachSafe(const FString& Context, USceneComponent* Parent, USkeletalMeshComponent* Child, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_PTR_NULL(Parent)

	CS_IS_PTR_NULL(Child)

	if (!IsValid(Context, Log))
		return false;

	if (bSlavePoseComponent)
	{
		Child->SetSkeletalMesh(Mesh.GetChecked(Context));

		USkeletalMeshComponent* Component = Cast<USkeletalMeshComponent>(Parent);

		if (!Component)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: if bSlavePoseComponent == true, then Parent: %s with Class: %s MUST be a USkeletalMeshComponent."), *Context, *(Parent->GetName()), *(Parent->GetClass()->GetName())));
			return false;
		}
		Child->SetMasterPoseComponent(Component);
	}
	else
	{
		typedef NCsSkeletalMesh::FLibrary SkeletalMeshLibrary;

		if (!SkeletalMeshLibrary::ConditionalSafeIsBoneOrSocketValid(Context, Parent, Bone, Log))
			return false;

		Child->AttachToComponent(Parent, NCsAttachmentTransformRules::ToRule(AttachmentTransformRules), Bone);
		NCsTransformRules::SetRelativeTransform(Child, Transform, TransformRules);
		Child->SetSkeletalMesh(Mesh.GetChecked(Context));
	}

	Child->SetCastShadow(bCastShadow);
	Child->SetReceivesDecals(bReceivesDecals);
	Child->bUseAsOccluder = bUseAsOccluder;
	Child->SetRenderCustomDepth(bRenderCustomDepth);
	Child->SetCustomDepthStencilValue(CustomDepthStencilValue);

	typedef NCsMaterial::FLibrary MaterialLibrary;

	MaterialLibrary::SetChecked(Context, Child, Materials.GetChecked(Context));
	return true;
}

FCsSkeletalMeshActorPooled* FCsSkeletalMeshAttachment::AttachChecked(const FString& Context, const UObject* WorldContext, USceneComponent* Parent) const
{
	CS_IS_PTR_NULL_CHECKED(Parent)

	check(IsValidChecked(Context));

	typedef NCsSkeletalMeshActor::NManager::FLibrary SkeletalMeshManagerLibrary;
	typedef NCsSkeletalMeshActor::NPayload::FLibrary PayloadLibrary;
	typedef NCsSkeletalMeshActor::NPayload::IPayload PayloadType;
	typedef NCsSkeletalMeshActor::NPayload::FImpl PayloadImplType;

	const FECsSkeletalMeshActor& DefaultType = NCsSkeletalMeshActor::GetDefault();

	PayloadType* Payload		 = SkeletalMeshManagerLibrary::AllocatePayloadChecked(Context, WorldContext, DefaultType);
	PayloadImplType* PayloadImpl = PayloadLibrary::PureStaticCastChecked<PayloadImplType>(Context, Payload);

	PayloadImpl->Parent = Parent;
	PayloadImpl->Mesh   = Mesh.GetChecked(Context);
	PayloadImpl->SetMaterials(Materials.GetChecked(Context));
	PayloadImpl->bGenerateMIDs  = bGenerateMIDs;
	PayloadImpl->Bone			= Bone;
	PayloadImpl->TransformRules = TransformRules;
	PayloadImpl->Transform		= Transform;
	PayloadImpl->bCastShadow	= bCastShadow;
	PayloadImpl->bReceivesDecals = bReceivesDecals;
	PayloadImpl->bUseAsOccluder = bUseAsOccluder;
	PayloadImpl->bRenderCustomDepth = bRenderCustomDepth;
	PayloadImpl->CustomDepthStencilValue = CustomDepthStencilValue;
	PayloadImpl->Tags.Reset(FMath::Max(PayloadImpl->Tags.Max(), Tags.Num()));
	PayloadImpl->Tags.Append(Tags);
	PayloadImpl->bSlavePoseComponent = bSlavePoseComponent;

	const FCsSkeletalMeshActorPooled* Object = SkeletalMeshManagerLibrary::SpawnChecked(Context, WorldContext, DefaultType, Payload);

	return const_cast<FCsSkeletalMeshActorPooled*>(Object);
}

namespace NCsSkeletalMesh
{
	namespace NAttachment
	{
		bool FAttachment::IsValidChecked(const FString& Context) const
		{
			// Check GetMesh() is Valid
			CS_IS_PTR_NULL_CHECKED(GetMesh())
			// Check GetMaterials() is Valid
			CS_IS_TARRAY_EMPTY_CHECKED(GetMaterials(), UMaterialInterface*)
			CS_IS_TARRAY_ANY_NULL_CHECKED(GetMaterials(), UMaterialInterface)
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
			CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(GetCustomDepthStencilValue(), 0)
			CS_IS_INT_LESS_THAN_OR_EQUAL_CHECKED(GetCustomDepthStencilValue(), 255)
			// Check GetTags() is Valid
			CS_IS_TARRAY_ANY_NONE_CHECKED(GetTags())
			return true;
		}

		bool FAttachment::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			// Check Mesh is Valid
			CS_IS_PTR_NULL(GetMesh())
			// Check Materials is Valid
			CS_IS_TARRAY_EMPTY(GetMaterials(), UMaterialInterface*)
			CS_IS_TARRAY_ANY_NULL(GetMaterials(), UMaterialInterface)
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

			CS_IS_INT_GREATER_THAN_OR_EQUAL(GetCustomDepthStencilValue(), 0)
			CS_IS_INT_LESS_THAN_OR_EQUAL(GetCustomDepthStencilValue(), 255)
			// Check GetTags() is Valid
			CS_IS_TARRAY_ANY_NONE(GetTags())
			return true;
		}

		void FAttachment::AttachChecked(const FString& Context, USceneComponent* Parent, USkeletalMeshComponent* Child) const
		{
			CS_IS_PTR_NULL_CHECKED(Parent)

			CS_IS_PTR_NULL_CHECKED(Child);

			check(IsValidChecked(Context));

			if (GetbSlavePoseComponent())
			{
				Child->SetSkeletalMesh(GetMesh());

				USkeletalMeshComponent* Component = Cast<USkeletalMeshComponent>(Parent);

				checkf(Component, TEXT("%s: if GetbSlavePoseComponent() == true, then Parent: %s with Class: %s MUST be a USkeletalMeshComponent."), *Context, *(Parent->GetName()), *(Parent->GetClass()->GetName()));

				Child->SetMasterPoseComponent(Component);
			}
			else
			{
				typedef NCsSkeletalMesh::FLibrary SkeletalMeshLibrary;

				check(SkeletalMeshLibrary::ConditionalIsBoneOrSocketValidChecked(Context, Parent, Bone));

				Child->AttachToComponent(Parent, NCsAttachmentTransformRules::ToRule(GetAttachmentTransformRules()), GetBone());
				NCsTransformRules::SetRelativeTransform(Child, GetTransform(), GetTransformRules());
				Child->SetSkeletalMesh(GetMesh());
			}

			Child->SetCastShadow(GetbCastShadow());
			Child->SetReceivesDecals(GetbReceivesDecals());
			Child->bUseAsOccluder = GetbUseAsOccluder();
			Child->bRenderCustomDepth = GetbRenderCustomDepth();
			Child->CustomDepthStencilValue = GetCustomDepthStencilValue();

			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::SetChecked(Context, Child, GetMaterials());
		}

		bool FAttachment::AttachSafe(const FString& Context, USceneComponent* Parent, USkeletalMeshComponent* Child, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			CS_IS_PTR_NULL(Parent)

			CS_IS_PTR_NULL(Child);

			if (!IsValid(Context, Log))
				return false;

			if (GetbSlavePoseComponent())
			{
				Child->SetSkeletalMesh(GetMesh());

				USkeletalMeshComponent* Component = Cast<USkeletalMeshComponent>(Parent);

				if (!Component)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: if GetbSlavePoseComponent() == true, then Parent: %s with Class: %s MUST be a USkeletalMeshComponent."), *Context, *(Parent->GetName()), *(Parent->GetClass()->GetName())));
					return false;
				}
				Child->SetMasterPoseComponent(Component);
			}
			else
			{
				typedef NCsSkeletalMesh::FLibrary SkeletalMeshLibrary;

				if (!SkeletalMeshLibrary::ConditionalSafeIsBoneOrSocketValid(Context, Parent, GetBone(), Log))
					return false;

				Child->AttachToComponent(Parent, NCsAttachmentTransformRules::ToRule(GetAttachmentTransformRules()), GetBone());
				NCsTransformRules::SetRelativeTransform(Child, GetTransform(), GetTransformRules());
				Child->SetSkeletalMesh(GetMesh());
			}

			Child->SetCastShadow(GetbCastShadow());
			Child->SetReceivesDecals(GetbReceivesDecals());
			Child->bUseAsOccluder = GetbUseAsOccluder();
			Child->bRenderCustomDepth = GetbRenderCustomDepth();
			Child->CustomDepthStencilValue = GetCustomDepthStencilValue();

			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::SetSafe(Context, Child, GetMaterials(), Log);
			return true;
		}

		void FAttachment::AttachAndActivateChecked(const FString& Context, USceneComponent* Parent, USkeletalMeshComponent* Child, TArray<UMaterialInstanceDynamic*>& OutMIDs) const
		{
			CS_IS_PTR_NULL_CHECKED(Parent)

			CS_IS_PTR_NULL_CHECKED(Child);

			check(IsValidChecked(Context));

			if (GetbSlavePoseComponent())
			{
				Child->SetSkeletalMesh(GetMesh());

				USkeletalMeshComponent* Component = Cast<USkeletalMeshComponent>(Parent);

				checkf(Component, TEXT("%s: if GetbSlavePoseComponent() == true, then Parent: %s with Class: %s MUST be a USkeletalMeshComponent."), *Context, *(Parent->GetName()), *(Parent->GetClass()->GetName()));

				Child->SetMasterPoseComponent(Component);
			}
			else
			{
				typedef NCsSkeletalMesh::FLibrary SkeletalMeshLibrary;

				check(SkeletalMeshLibrary::ConditionalIsBoneOrSocketValidChecked(Context, Parent, Bone));

				Child->AttachToComponent(Parent, NCsAttachmentTransformRules::ToRule(GetAttachmentTransformRules()), GetBone());
				NCsTransformRules::SetRelativeTransform(Child, GetTransform(), GetTransformRules());
				Child->SetSkeletalMesh(GetMesh());
			}

			Child->SetCastShadow(GetbCastShadow());
			Child->SetReceivesDecals(GetbReceivesDecals());
			Child->bUseAsOccluder = GetbUseAsOccluder();
			Child->bRenderCustomDepth = GetbRenderCustomDepth();
			Child->CustomDepthStencilValue = GetCustomDepthStencilValue();

			typedef NCsMaterial::NMID::FLibrary MIDLibrary;

			MIDLibrary::SetChecked(Context, Child, GetMaterials(), OutMIDs);

			Child->SetComponentTickEnabled(true);
			Child->SetHiddenInGame(false);
		}

		FCsSkeletalMeshActorPooled* FAttachment::AttachChecked(const FString& Context, const UObject* WorldContext, USceneComponent* Parent) const
		{
			CS_IS_PTR_NULL_CHECKED(Parent)

			check(IsValidChecked(Context));

			typedef NCsSkeletalMeshActor::NManager::FLibrary SkeletalMeshManagerLibrary;
			typedef NCsSkeletalMeshActor::NPayload::FLibrary PayloadLibrary;
			typedef NCsSkeletalMeshActor::NPayload::IPayload PayloadType;
			typedef NCsSkeletalMeshActor::NPayload::FImpl PayloadImplType;

			const FECsSkeletalMeshActor& DefaultType = NCsSkeletalMeshActor::GetDefault();

			PayloadType* Payload		 = SkeletalMeshManagerLibrary::AllocatePayloadChecked(Context, WorldContext, DefaultType);
			PayloadImplType* PayloadImpl = PayloadLibrary::PureStaticCastChecked<PayloadImplType>(Context, Payload);

			PayloadImpl->Parent = Parent;
			PayloadImpl->Mesh   = GetMesh();
			PayloadImpl->SetMaterials(GetMaterials());
			PayloadImpl->bGenerateMIDs  = GetbGenerateMIDs();
			PayloadImpl->Bone			= GetBone();
			PayloadImpl->TransformRules = GetTransformRules();
			PayloadImpl->Transform		= GetTransform();
			PayloadImpl->bCastShadow	= GetbCastShadow();
			PayloadImpl->bReceivesDecals = GetbReceivesDecals();
			PayloadImpl->bUseAsOccluder = GetbUseAsOccluder();
			PayloadImpl->bRenderCustomDepth = GetbRenderCustomDepth();
			PayloadImpl->CustomDepthStencilValue = GetCustomDepthStencilValue();
			PayloadImpl->Tags.Reset(FMath::Max(PayloadImpl->Tags.Max(), GetTags().Num()));
			PayloadImpl->Tags.Append(GetTags());
			PayloadImpl->bSlavePoseComponent = GetbSlavePoseComponent();

			const FCsSkeletalMeshActorPooled* Object = SkeletalMeshManagerLibrary::SpawnChecked(Context, WorldContext, DefaultType, Payload);

			return const_cast<FCsSkeletalMeshActorPooled*>(Object);
		}
	}
}