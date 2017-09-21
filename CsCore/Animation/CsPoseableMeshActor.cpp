// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/CsPoseableMeshActor.h"
#include "Components/CsPoseableMeshComponent.h"
#include "CsCore.h"
#include "CsCommon.h"
#include "Animation/CsBoneActor.h"

ACsPoseableMeshActor::ACsPoseableMeshActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;

	PoseableMeshComponent = ObjectInitializer.CreateDefaultSubobject<UCsPoseableMeshComponent>(this, TEXT("PoseableMeshComponent"));
}

void ACsPoseableMeshActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

#if WITH_EDITOR
	// Handle Waypoints placed in Editor
	if (UCsCommon::IsPlayInEditor(GetWorld()))
	{
		OnTick_Editor(DeltaSeconds);
		return;
	}
#endif // #if WITH_EDITOR
}

bool ACsPoseableMeshActor::ShouldTickIfViewportsOnly() const
{
#if WITH_EDITOR
	if (UCsCommon::IsPlayInEditor(GetWorld()))
		return true;
#endif // #if WITH_EDITOR
	return Super::ShouldTickIfViewportsOnly();
}

void ACsPoseableMeshActor::OnTick_Editor(const float &DeltaSeconds)
{
	if (!HasTickedInEditor)
	{
		HasTickedInEditor = true;
	}
}

#if WITH_EDITOR

void ACsPoseableMeshActor::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	if (UCsCommon::IsPlayInEditor(GetWorld()))
	{
		if (PropertyName == GET_MEMBER_NAME_CHECKED(ACsPoseableMeshActor, PoseableMeshComponent))
		{
			if (PoseableMeshComponent->SkeletalMesh != Last_SkeletalMesh)
			{
				if (PoseableMeshComponent->SkeletalMesh)
					GenerateBones();
				else
					ClearBones();
			}
			Last_SkeletalMesh = PoseableMeshComponent->SkeletalMesh;
		}
	}
	Super::PostEditChangeProperty(e);
}

void ACsPoseableMeshActor::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& e)
{
	Super::PostEditChangeChainProperty(e);
}

void ACsPoseableMeshActor::GenerateBones()
{
	ClearBones();

	TArray<FName> BoneNames;
	PoseableMeshComponent->GetBoneNames(BoneNames);

	const int32 Count = BoneNames.Num();

	for (int32 I = 0; I < Count; I++)
	{
		ACsBoneActor* Bone = GetWorld()->SpawnActor<ACsBoneActor>();

		const FName BoneName = BoneNames[I];
		Bone->SetActorLabel(BoneName.ToString());
		Bone->Bone = BoneName;

		Bone->SetActorRelativeTransform(FTransform::Identity);

		const FName ParentBoneName = PoseableMeshComponent->GetParentBone(BoneName);

		if (ParentBoneName == NAME_None)
		{
			Bone->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		}
		else
		{
			const int32 InfoCount = Bones.Num();

			for (int32 J = 0; J < InfoCount; J++)
			{
				if (Bones[J].Bone == ParentBoneName)
				{
					Bone->AttachToActor(Bones[J].Actor, FAttachmentTransformRules::KeepRelativeTransform);
					break;
				}
			}
		}
		Bone->SetActorRelativeLocation(PoseableMeshComponent->GetBoneLocation(BoneName, EBoneSpaces::ComponentSpace));
		Bone->SetActorRelativeRotation(PoseableMeshComponent->GetBoneRotationByName(BoneName, EBoneSpaces::ComponentSpace));

		Bones.AddDefaulted();
		const int32 Index = Bones.Num() - 1;
		Bones[Index].Bone = BoneName;
		Bones[Index].Actor = Bone;
	}
}

void ACsPoseableMeshActor::ClearBones()
{
	const int32 Count = Bones.Num();

	for (int32 I = 0; I < Count; I++)
	{
		if (Bones[I].Actor && !Bones[I].Actor->IsPendingKill())
			Bones[I].Actor->Destroy();
	}
	Bones.Reset();
}

#endif // #if WITH_EDITOR