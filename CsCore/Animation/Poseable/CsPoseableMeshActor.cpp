// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/Poseable/CsPoseableMeshActor.h"
#include "Components/CsPoseableMeshComponent.h"
#include "CsCore.h"
#include "CsCommon.h"

#if WITH_EDITOR
#include "../AnimationCore/Public/TwoBoneIK.h"
#endif // #if WITH_EDITOR

#include "Animation/Poseable/CsAnim_Bone.h"
#include "Animation/Poseable/Controls/CsAnim_Control.h"
#include "Animation/Poseable/Controls/CsAnim_ControlAnchor.h"
#include "Animation/Poseable/Controls/CsAnim_Control_TwoBoneIK.h"
#include "Animation/Poseable/Controls/Helpers/CsAnim_ControlHelper_EndEffector.h"
#include "Animation/Poseable/Controls/Helpers/CsAnim_ControlHelper_JointTarget.h"


ACsPoseableMeshActor::ACsPoseableMeshActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;

	PoseableMeshComponent = ObjectInitializer.CreateDefaultSubobject<UCsPoseableMeshComponent>(this, TEXT("PoseableMeshComponent"));
	SetRootComponent(PoseableMeshComponent);
}

void ACsPoseableMeshActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Make a Copy of Controls_TwoBoneIK
	Controls_TwoBoneIK_Copy.Reset();

	const int32 Count = Controls_TwoBoneIK.Num();

	for (int32 I = 0; I < Count; I++)
	{
		Controls_TwoBoneIK_Copy.AddDefaulted();
		Controls_TwoBoneIK_Copy[I] = Controls_TwoBoneIK[I];
	}
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

#if WITH_EDITOR

void ACsPoseableMeshActor::OnTick_Editor(const float &DeltaSeconds)
{
	if (!HasTickedInEditor)
	{
		HasTickedInEditor = true;
	}
	
	//if (IsSelected())
	//	return;

	// Controls

		// TwoBoneIK
	{
		const int32 ControlCount = Controls_TwoBoneIK.Num();

		for (int32 I = 0; I < ControlCount; I++)
		{
			FCsAnimControlInfo_TwoBoneIK& TwoBoneIK = Controls_TwoBoneIK[I];
			ACsAnim_Control_TwoBoneIK* Control		= TwoBoneIK.Actor;

			if (!Control)
			{
				DestroyOrphanedControlAnchors();
				DestroyOrphanedControlHelpers();
				Create_Control_TwoBoneIK(I);
			}

			if (!Control->Anchor ||
				!Control->EndEffector || 
				!Control->JointTarget)
			{
				Create_Control_TwoBoneIK(I);
			}

			if (IsSelected())
			{
				Control->ForceUpdateTransform = true;
				Control->EndEffector->ForceUpdateTransform = true;
				Control->JointTarget->ForceUpdateTransform = true;
				continue;
			}

			if (!Control->StartBone || !Control->MiddleBone || !Control->EndBone)
				continue;

			const bool UpdateIK = Control->EndEffector->Location.HasChanged() || Control->JointTarget->Location.HasChanged();

			if (UpdateIK)
			{
				PerformTwoBoneIK(I);
			}
		}
	}

	// Bones
	const int32 BoneCount = Bones.Num();

	for (int32 I = 0; I < BoneCount; I++)
	{
		if (!Bones[I].Actor)
		{
			RecreateBone(I);
		}

		Bones[I].Actor->ForceUpdateTransform |= IsSelected();

		// Location
		if (Bones[I].Actor->Location.HasChanged() ||
			Bones[I].Actor->ForceUpdateTransform)
		{
			PoseableMeshComponent->SetBoneLocationByIndex(Bones[I].BoneIndex, Bones[I].Actor->Location.Get(), EBoneSpaces::WorldSpace);
			Bones[I].Actor->Location.Clear();
		}
		// Rotation
		if (Bones[I].Actor->Rotation.HasChanged() ||
			Bones[I].Actor->ForceUpdateTransform)
		{
			PoseableMeshComponent->SetBoneRotationByIndex(Bones[I].BoneIndex, Bones[I].Actor->Rotation.Get(), EBoneSpaces::WorldSpace);
			Bones[I].Actor->Rotation.Clear();
		}
		// Scale
		if (Bones[I].Actor->Scale.HasChanged() ||
			Bones[I].Actor->ForceUpdateTransform)
		{
			PoseableMeshComponent->SetBoneScaleByIndex(Bones[I].BoneIndex, Bones[I].Actor->Scale.Get(), EBoneSpaces::WorldSpace);
			Bones[I].Actor->Scale.Clear();
		}
	}
}

#endif // #if WITH_EDITOR

#if WITH_EDITOR

void ACsPoseableMeshActor::OnControlNameChanged_TwoBoneIK(const int32 &Index)
{
	FCsAnimControlInfo_TwoBoneIK& TwoBoneIK = Controls_TwoBoneIK[Index];
	ACsAnim_Control_TwoBoneIK* Control		= TwoBoneIK.Actor;

	TwoBoneIK.Control = Control->GetActorLabel();
}

void ACsPoseableMeshActor::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	if (!UCsCommon::IsPlayInEditor(GetWorld()))
	{
		Super::PostEditChangeProperty(e);
		return;
	}

	// SkeletalMesh
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
	Super::PostEditChangeProperty(e);
}

void ACsPoseableMeshActor::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& e)
{
	if (!UCsCommon::IsPlayInEditor(GetWorld()))
	{
		Super::PostEditChangeChainProperty(e);
		return;
	}

	const int32 Controls_TwoBoneIK_Index = e.GetArrayIndex(TEXT("Controls_TwoBoneIK"));

	// Controls_TwoBoneIK
	if (Controls_TwoBoneIK_Index != INDEX_NONE)
	{
		const int32 Index						= Controls_TwoBoneIK_Index;
		FCsAnimControlInfo_TwoBoneIK& TwoBoneIK = Controls_TwoBoneIK[Index];

		// SkeletalMesh is NULL
		if (!PoseableMeshComponent->SkeletalMesh)
		{
			UCsCommon::DisplayNotificationInfo(TEXT("SkeletalMesh is NULL."), TEXT("PoseableMesh"), TEXT("PostEditChangeChainProperty"), 5.0f);

			UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::PostEditChangeChainProperty(%s): SkeletalMesh is NULL. Can NOT update Controls."), *GetName());
			Super::PostEditChangeChainProperty(e);
			return;
		}

		FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

		const int32 ControlCount = Controls_TwoBoneIK.Num();
		const int32 CopyCount    = Controls_TwoBoneIK_Copy.Num();

		// Check if NEW elements were ADDED
		if (ControlCount > CopyCount)
		{
			const int32 Delta = ControlCount - CopyCount;

			for (int32 I = 0; I < Delta; I++)
			{
				const int32 CopyIndex = CopyCount + I;

				Create_Control_TwoBoneIK(CopyIndex);
				
				Controls_TwoBoneIK_Copy.AddDefaulted();
				Controls_TwoBoneIK_Copy[CopyIndex] = Controls_TwoBoneIK[CopyIndex];
			}
		}
		// Check if elements were REMOVED
		if (ControlCount < CopyCount)
		{
			const int32 Delta = CopyCount - ControlCount;

			for (int32 I = CopyCount - 1; I >= CopyCount - Delta; I--)
			{
				ACsAnim_Control_TwoBoneIK* Control = Controls_TwoBoneIK_Copy[I].Actor;

				if (Control && !Control->IsPendingKill())
				{
					if (Control->EndEffector && !Control->EndEffector->IsPendingKill())
						Control->EndEffector->Destroy();
					if (Control->JointTarget && !Control->JointTarget->IsPendingKill())
						Control->JointTarget->Destroy();
					Control->Destroy();
				}
				Controls_TwoBoneIK_Copy.RemoveAt(I);
			}
		}
		// Controls_TwoBoneIK[Index].Control
		if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsAnimControlInfo_TwoBoneIK, Control))
		{
			if (ACsAnim_Control_TwoBoneIK* Control = TwoBoneIK.Actor)
			{
				Control->SetControlName(TwoBoneIK.Control);
			}
		}
		// Controls_TwoBoneIK[Index].IK.IKBone
		if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsAnimControlInfo_TwoBoneIK_IK, IKBone))
		{
			const FName BoneName  = TwoBoneIK.IK.IKBone;
			const int32 BoneIndex = PoseableMeshComponent->GetBoneIndex(BoneName);
			
			TwoBoneIK.IK.IKBoneIndex = BoneIndex;

			TwoBoneIK.EndEffector.EffectorSpaceBoneName  = BoneName;
			TwoBoneIK.EndEffector.EffectorSpaceBoneIndex = BoneIndex;

			if (BoneName == NAME_None || BoneIndex == INDEX_NONE)
			{
				TwoBoneIK.IK.IKBone = NAME_None;
				TwoBoneIK.IK.IKBoneIndex = INDEX_NONE;
				TwoBoneIK.IK.IKBoneArrayIndex = INDEX_NONE;
				TwoBoneIK.IK.Last_IKBone = BoneName;
				TwoBoneIK.IK.ParentBone = NAME_None;
				TwoBoneIK.IK.ParentBoneIndex = INDEX_NONE;
				TwoBoneIK.IK.ParentBoneIndex = INDEX_NONE;

				TwoBoneIK.EndEffector.EffectorSpaceBoneName = NAME_None;
				TwoBoneIK.EndEffector.EffectorSpaceBoneIndex = INDEX_NONE;
				TwoBoneIK.EndEffector.EffectorSpaceBoneArrayIndex = NAME_None;

				TwoBoneIK.JointTarget.JointTargetSpaceBoneName = NAME_None;
				TwoBoneIK.JointTarget.JointTargetSpaceBoneIndex = INDEX_NONE;
				TwoBoneIK.JointTarget.JointTargetSpaceBoneArrayIndex = INDEX_NONE;
				
				if (ACsAnim_Control_TwoBoneIK* Control = TwoBoneIK.Actor)
				{
					Control->StartBone = nullptr;
					Control->MiddleBone = nullptr;
					Control->EndBone = nullptr;
				}

				Controls_TwoBoneIK_Copy[Index] = TwoBoneIK;

				Super::PostEditChangeChainProperty(e);
				return;
			}

			if (BoneName == TwoBoneIK.IK.Last_IKBone)
			{
				Super::PostEditChangeChainProperty(e);
				return;
			}

			TwoBoneIK.IK.Last_IKBone = BoneName;

			ACsAnim_Control_TwoBoneIK* Control = TwoBoneIK.Actor;

			if (!Control)
			{
				DestroyOrphanedControlAnchors();
				DestroyOrphanedControlHelpers();
			}

			Create_Control_TwoBoneIK(Index);
			Controls_TwoBoneIK_Copy[Index] = Controls_TwoBoneIK[Index];
		}
	}
	Super::PostEditChangeChainProperty(e);
}

void ACsPoseableMeshActor::GenerateBones()
{
	ClearBones();
	
	const FTransform ComponentTransform = PoseableMeshComponent->GetComponentTransform();

	TArray<FName> BoneNames;
	PoseableMeshComponent->GetBoneNames(BoneNames);

	const int32 Count = BoneNames.Num();

	for (int32 I = 0; I < Count; I++)
	{
		ACsAnim_Bone* Bone = GetWorld()->SpawnActor<ACsAnim_Bone>();

		const FName BoneName = BoneNames[I];
		Bone->SetActorLabel(BoneName.ToString());
		Bone->Bone = BoneName;
		Bone->Root = this;

		Bone->SetActorRelativeTransform(FTransform::Identity);
	
		const FName ParentBoneName = PoseableMeshComponent->GetParentBone(BoneName);
		int32 ParentBoneIndex	   = INDEX_NONE;

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
					ParentBoneIndex = Bones[J].BoneIndex;
					Bone->AttachToActor(Bones[J].Actor, FAttachmentTransformRules::KeepRelativeTransform);
					break;
				}
			}
		}
		
		const int32 BoneIndex = PoseableMeshComponent->GetBoneIndex(BoneName);
		Bone->BoneIndex		  = BoneIndex;
		Bone->ParentBone	  = ParentBoneName;
		Bone->ParentBoneIndex = ParentBoneIndex;
		// Store Local / Relative Transform
		Bone->DefaultRelativeTransform = PoseableMeshComponent->BoneSpaceTransforms[BoneIndex];
		Bone->UpdateRelativeTransform(Bone->DefaultRelativeTransform, true);
		// Store Component Transform - WorldSpace -> ComponentSpace
		Bone->DefaultComponentTransform = PoseableMeshComponent->GetBoneTransform(BoneIndex);
		Bone->DefaultComponentTransform.SetToRelativeTransform(ComponentTransform);

		Bone->ArrayIndex = I;

		Bones.AddDefaulted();
		const int32 Index = Bones.Num() - 1;
		Bones[Index].Bone = BoneName;
		Bones[Index].BoneIndex = BoneIndex;
		Bones[Index].ParentBone = ParentBoneName;
		Bones[Index].ParentBoneIndex = ParentBoneIndex;
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

void ACsPoseableMeshActor::DestroyOrphanedControlAnchors()
{
	TArray<AActor*> Anchors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACsAnim_ControlAnchor::StaticClass(), Anchors);

	const int32 Count = Anchors.Num();

	for (int32 I = 0; I < Count; I++)
	{
		ACsAnim_ControlAnchor* Anchor = Cast<ACsAnim_ControlAnchor>(Anchors[I]);

		if (!Anchor->Control)
			Anchor->Destroy();
	}
}

void ACsPoseableMeshActor::DestroyOrphanedControlHelpers()
{
	// Check Control Children who do NOT have a parent, Delete them
	TArray<AActor*> Helpers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACsAnim_ControlHelper::StaticClass(), Helpers);

	const int32 Count = Helpers.Num();

	for (int32 I = 0; I < Count; I++)
	{
		ACsAnim_ControlHelper* Helper = Cast<ACsAnim_ControlHelper>(Helpers[I]);

		if (Helper->ControlIndex == INDEX_NONE)
			Helper->Destroy();
	}
}

void ACsPoseableMeshActor::RecreateBone(const int32 &Index)
{
	ACsAnim_Bone* Bone = GetWorld()->SpawnActor<ACsAnim_Bone>();

	Bones[Index].Actor = Bone;
	const FName BoneName = Bones[Index].Bone;
	Bone->SetActorLabel(BoneName.ToString());
	Bone->Bone = BoneName;
	Bone->Root = this;

	Bone->SetActorRelativeTransform(FTransform::Identity);

	const FName ParentBoneName = Bones[Index].ParentBone;
	int32 ParentBoneIndex	   = Bones[Index].ParentBoneIndex;

	if (ParentBoneName == NAME_None)
	{
		Bone->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}

	const int32 InfoCount = Bones.Num();

	for (int32 J = 0; J < InfoCount; J++)
	{
		if (Bones[J].Bone == ParentBoneName)
		{
			Bone->AttachToActor(Bones[J].Actor, FAttachmentTransformRules::KeepRelativeTransform);
		}

		if (Bones[J].ParentBone == BoneName)
		{
			Bones[J].Actor->AttachToActor(Bone, FAttachmentTransformRules::KeepRelativeTransform);
			Bones[J].Actor->ResetRelativeTransform();
		}
	}

	const int32 BoneIndex = PoseableMeshComponent->GetBoneIndex(BoneName);
	Bone->BoneIndex		  = BoneIndex;
	Bone->ParentBone	  = ParentBoneName;
	Bone->ParentBoneIndex = ParentBoneIndex;
	// Store Local / Relative Transform
	Bone->DefaultRelativeTransform = PoseableMeshComponent->BoneSpaceTransforms[BoneIndex];
	Bone->UpdateRelativeTransform(Bone->DefaultRelativeTransform, true);
	// Store Component Transform - WorldSpace -> ComponentSpace
	const FTransform ComponentTransform = PoseableMeshComponent->GetComponentTransform();
	Bone->DefaultComponentTransform = PoseableMeshComponent->GetBoneTransform(BoneIndex);
	Bone->DefaultComponentTransform.SetToRelativeTransform(ComponentTransform);

	Bone->ArrayIndex = Index;
}

void ACsPoseableMeshActor::Create_Control_TwoBoneIK(const int32 &Index)
{
	FCsAnimControlInfo_TwoBoneIK& TwoBoneIK = Controls_TwoBoneIK[Index];
	ACsAnim_Control_TwoBoneIK* Control	    = TwoBoneIK.Actor;

	if (!Control)
	{
		ACsAnim_ControlAnchor* Anchor = GetWorld()->SpawnActor<ACsAnim_ControlAnchor>();

		Anchor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		Control		         = GetWorld()->SpawnActor<ACsAnim_Control_TwoBoneIK>();
		Control->Control     = TwoBoneIK.Control;
		Control->ControlName = TwoBoneIK.Control;
		Control->ControlName.Clear();
		Control->SetActorLabel(TwoBoneIK.Control);
		Control->ControlIndex = Index;
		Control->Root = this;
		Control->Anchor = Anchor;

		Control->AttachToActor(Anchor, FAttachmentTransformRules::KeepRelativeTransform);

		TwoBoneIK.Actor = Control;

		Control->OnControlNameChanged_Event.BindUObject(this, &ACsPoseableMeshActor::OnControlNameChanged_TwoBoneIK);

		Anchor->Control = Control;
		Anchor->SetActorLabel(TEXT("anchor_") + Control->GetActorLabel());
	}

	if (!Control->Anchor)
	{
		ACsAnim_ControlAnchor* Anchor = GetWorld()->SpawnActor<ACsAnim_ControlAnchor>();

		Anchor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		const FTransform WorldTransform = Control->GetActorTransform();
		Control->SetActorRelativeTransform(FTransform::Identity);
		Control->AttachToActor(Anchor, FAttachmentTransformRules::KeepRelativeTransform);
		Control->SetActorTransform(WorldTransform);

		Anchor->Control = Control;
		Anchor->SetActorLabel(TEXT("anchor_") + Control->GetActorLabel());
	}

	const FName BoneName = TwoBoneIK.IK.IKBone;
	const int32 BoneIndex = PoseableMeshComponent->GetBoneIndex(BoneName);

	TwoBoneIK.IK.IKBoneIndex = BoneIndex;

	TwoBoneIK.EndEffector.EffectorSpaceBoneName = BoneName;
	TwoBoneIK.EndEffector.EffectorSpaceBoneIndex = BoneIndex;

	// Cache ArrayIndex
	TwoBoneIK.IK.IKBoneArrayIndex = INDEX_NONE;

	{
		const int32 Count = Bones.Num();

		for (int32 I = 0; I < Count; I++)
		{
			if (Bones[I].Bone == BoneName)
			{
				TwoBoneIK.IK.IKBoneArrayIndex = I;
				TwoBoneIK.EndEffector.EffectorSpaceBoneArrayIndex = I;
				break;
			}
		}
	}

	// Middle Bone
	const FName MiddleBoneName = PoseableMeshComponent->GetParentBone(BoneName);
	const int32 MiddleBoneIndex = PoseableMeshComponent->GetBoneIndex(MiddleBoneName);

	TwoBoneIK.IK.ParentBone = MiddleBoneName;
	TwoBoneIK.IK.ParentBoneIndex = MiddleBoneIndex;
	TwoBoneIK.IK.ParentBoneArrayIndex = INDEX_NONE;

	// Start Bone
	const FName StartBoneName = PoseableMeshComponent->GetParentBone(MiddleBoneName);
	const int32 StartBoneIndex = PoseableMeshComponent->GetBoneIndex(StartBoneName);

	TwoBoneIK.JointTarget.JointTargetSpaceBoneName = StartBoneName;
	TwoBoneIK.JointTarget.JointTargetSpaceBoneIndex = StartBoneIndex;
	TwoBoneIK.JointTarget.JointTargetSpaceBoneArrayIndex = INDEX_NONE;

	// Change JointTarget (Start Bone)
	ACsAnim_ControlHelper_JointTarget* JointTarget = Control->JointTarget; 
	
	if (!JointTarget)
	{
		JointTarget				  = GetWorld()->SpawnActor<ACsAnim_ControlHelper_JointTarget>();
		JointTarget->ControlIndex = Index;
		JointTarget->Root		  = this;
		JointTarget->SetActorLabel(TwoBoneIK.Control + TEXT("_PoleVector"));
		Control->JointTarget = JointTarget;
		JointTarget->AttachToActor(Control, FAttachmentTransformRules::KeepRelativeTransform);
	}

	{
		// Reset PREVIOUS Start Bone
		if (Control->StartBone)
		{
			Control->StartBone->ResetRelativeTransform();
			PoseableMeshComponent->SetBoneTransformByName(Control->StartBone->Bone, Control->StartBone->GetActorTransform(), EBoneSpaces::ComponentSpace);
		}

		if (StartBoneName != NAME_None)
		{
			const int32 Count = Bones.Num();

			for (int32 I = 0; I < Count; I++)
			{
				if (Bones[I].Bone == StartBoneName)
				{
					// Reset NEW / CURRENT Start Bone
					Control->StartBone = Bones[I].Actor;
					Control->StartBone->ResetRelativeTransform();
					PoseableMeshComponent->SetBoneTransformByName(Control->StartBone->Bone, Control->StartBone->GetActorTransform(), EBoneSpaces::ComponentSpace);

					JointTarget->SetActorLocation(Control->StartBone->GetActorLocation());
					JointTarget->Location = Control->StartBone->GetActorLocation();

					TwoBoneIK.JointTarget.JointTargetSpaceBoneArrayIndex = I;
					break;
				}
			}
		}
		else
		{
			Control->StartBone = nullptr;

			UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::Create_Control_TwoBoneIK(%s): JointTargetBoneName (Start Bone): %s is NOT found in SkeletalMesh: %s"), *GetName(), *(StartBoneName.ToString()), *(PoseableMeshComponent->SkeletalMesh->GetName()));
		}
	}
	// Change Middle Bone
	{
		// Reset PREVIOUS Middle Bone
		if (Control->MiddleBone)
		{
			Control->MiddleBone->ResetRelativeTransform();
			PoseableMeshComponent->SetBoneTransformByName(Control->MiddleBone->Bone, Control->MiddleBone->GetActorTransform(), EBoneSpaces::ComponentSpace);
		}
		// Reset NEW / CURRENT Middle Bone
		if (MiddleBoneName != NAME_None)
		{
			const int32 Count = Bones.Num();

			for (int32 I = 0; I < Count; I++)
			{
				if (Bones[I].Bone == MiddleBoneName)
				{
					Control->MiddleBone = Bones[I].Actor;
					Control->MiddleBone->ResetRelativeTransform();
					PoseableMeshComponent->SetBoneTransformByName(Control->MiddleBone->Bone, Control->MiddleBone->GetActorTransform(), EBoneSpaces::ComponentSpace);

					TwoBoneIK.IK.ParentBoneArrayIndex = I;
				}
			}
		}
		else
		{
			Control->MiddleBone = nullptr;

			UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::Create_Control_TwoBoneIK(%s): IKBone's Parent Bone (Middle Bone): %s is NOT found in SkeletalMesh: %s"), *GetName(), *(MiddleBoneName.ToString()), *(PoseableMeshComponent->SkeletalMesh->GetName()));
		}
	}
	// Change EndEffector (End Bone)
	ACsAnim_ControlHelper_EndEffector* EndEffector = Control->EndEffector;
	
	if (!EndEffector)
	{
		EndEffector				  = GetWorld()->SpawnActor<ACsAnim_ControlHelper_EndEffector>();
		EndEffector->ControlIndex = Index;
		EndEffector->Root		  = this;
		EndEffector->SetActorLabel(TwoBoneIK.Control + TEXT("_EndEffector"));
		Control->EndEffector = EndEffector;
		EndEffector->AttachToActor(Control, FAttachmentTransformRules::KeepRelativeTransform);
	}

	{
		// Reset PREVIOUS End Bone. TODO: Need to check if any other Control is referencing this bone
		if (Control->EndBone)
		{
			Control->EndBone->ResetRelativeTransform();
			PoseableMeshComponent->SetBoneTransformByName(Control->EndBone->Bone, Control->EndBone->GetActorTransform(), EBoneSpaces::ComponentSpace);
		}
		if (BoneName != NAME_None)
		{
			const int32 Count = Bones.Num();

			for (int32 I = 0; I < Count; I++)
			{
				if (Bones[I].Bone == BoneName)
				{
					// Reset NEW / CURRENT End Bone
					Control->EndBone = Bones[I].Actor;
					Control->MiddleBone->ResetRelativeTransform();
					PoseableMeshComponent->SetBoneTransformByName(Control->EndBone->Bone, Control->EndBone->GetActorTransform(), EBoneSpaces::ComponentSpace);

					EndEffector->SetActorLocation(Control->EndBone->GetActorLocation());
					EndEffector->Location = Control->EndBone->GetActorLocation();
					break;
				}
			}
		}
		else
		{
			Control->EndBone = nullptr;

			UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::Create_Control_TwoBoneIK(%s): IKBone (End Bone): %s is NOT found in SkeletalMesh: %s"), *GetName(), *(BoneName.ToString()), *(PoseableMeshComponent->SkeletalMesh->GetName()));
		}
	}

	if (Control->StartBone && Control->MiddleBone && Control->EndBone)
		PerformTwoBoneIK(Index);
}

// Copied from Engine\Source\Runtime\AnimGraphRuntime\Private\BoneControllers\AnimNode_TowBoneIK.cpp

void ACsPoseableMeshActor::PerformTwoBoneIK(const int32 &Index)
{
	FCsAnimControlInfo_TwoBoneIK& TwoBoneIK = Controls_TwoBoneIK[Index];
	ACsAnim_Control_TwoBoneIK* Control      = TwoBoneIK.Actor;

	ACsAnim_Bone* StartBone = Control->StartBone;
	ACsAnim_Bone* MiddleBone = Control->MiddleBone;
	ACsAnim_Bone* EndBone = Control->EndBone;

	// Now get those in component space...
	FTransform StartTransform = StartBone->DefaultComponentTransform;
	FTransform MiddleTransform = MiddleBone->DefaultComponentTransform;
	FTransform EndTransform = EndBone->DefaultComponentTransform;

	// Get current position of root of limb.
	// All position are in Component space.
	const FVector StartPos		   = StartTransform.GetTranslation();
	const FVector InitialMiddlePos = MiddleTransform.GetTranslation();
	const FVector InitialEndPos    = EndTransform.GetTranslation();

	const FTransform ComponentTransform = PoseableMeshComponent->GetComponentTransform();

	// Get JointTarget Transform in ComponentSpace
	
	const FVector JointTargetLocation = Control->JointTarget->GetActorLocation();
	FTransform JointTargetTransform(JointTargetLocation);
		// Convert JointTargetTransform WorldSpace -> ComponentSpace
	JointTargetTransform.SetToRelativeTransform(ComponentTransform);
	
	FVector	JointTargetPos = JointTargetTransform.GetTranslation();

	// Get EndEffector Transform in ComponentSpace

	const FVector EndEffectorLocation = Control->EndEffector->GetActorLocation();
	FTransform EndEffectorTransform(EndEffectorLocation);
		// Convert EndEffectorTransfrom WorldSpace -> ComponentSpace
	EndEffectorTransform.SetToRelativeTransform(ComponentTransform);

	FVector DesiredPos = EndEffectorTransform.GetTranslation();

	// IK solver
	
	StartTransform.SetLocation(StartPos);
	MiddleTransform.SetLocation(InitialMiddlePos);
	EndTransform.SetLocation(InitialEndPos);

	const bool bAllowStretching   = TwoBoneIK.IK.bAllowStretching;
	const float StartStretchRatio = TwoBoneIK.IK.StartStretchRatio;
	const float MaxStretchRatio   = TwoBoneIK.IK.MaxStretchRatio;

	AnimationCore::SolveTwoBoneIK(StartTransform, MiddleTransform, EndTransform, JointTargetPos, DesiredPos, bAllowStretching, StartStretchRatio, MaxStretchRatio);

	// Update transform for end bone.

	// only allow bTakeRotationFromEffectorSpace during bone space
	if (TwoBoneIK.EndEffector.bTakeRotationFromEffectorSpace)
	{
		EndTransform.SetRotation(EndEffectorTransform.GetRotation());
	}
	else 
	if (TwoBoneIK.EndEffector.bMaintainEffectorRelRot)
	{
		// Get Local Space transforms for our bones. We do this first in case they already are local.
		// As right after we get them in component space. (And that does the auto conversion).
		// We might save one transform by doing local first...
		const FTransform EndLocalTransform = PoseableMeshComponent->BoneSpaceTransforms[EndBone->BoneIndex];
		EndTransform					   = EndLocalTransform * MiddleTransform;
	}

	// Set World Transform. ComponentSpace -> WorldSpace

	// Start
	const FTransform StartWorldTransform = StartTransform * ComponentTransform;
	Control->StartBone->UpdateRotation(StartWorldTransform.Rotator());
	// Middle
	Control->MiddleBone->UpdateTransform(MiddleTransform * ComponentTransform);
	// End
	const FTransform EndWorldTransform = EndTransform * ComponentTransform;
	Control->EndBone->UpdateLocation(EndWorldTransform.GetTranslation());

	Control->EndEffector->Location.Clear();
	Control->JointTarget->Location.Clear();
}

#endif // #if WITH_EDITOR