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
			ACsAnim_Control_TwoBoneIK* Control = Controls_TwoBoneIK[I].Actor;

			if (!Control)
				continue;
			if (!Control->EndEffector || !Control->JointTarget)
				continue;
			if (!Control->StartBone || !Control->MiddleBone || !Control->EndBone)
				continue;

			const bool UpdateIK = Control->EndEffector->Location.HasChanged() || Control->JointTarget->Location.HasChanged();

			if (UpdateIK)
			{
				TArray<FTransform> Transforms;

				PerformTwoBoneIK(I, Transforms);

				const FName StartBone  = Controls_TwoBoneIK[I].EndEffector.EffectorSpaceBoneName;
				const FName MiddleBone = Controls_TwoBoneIK[I].IK.ParentBone;
				const FName EndBone    = Controls_TwoBoneIK[I].IK.IKBone;

				const int32 START = 0; const int32 MIDDLE = 1; const int32 END = 2;

				// TODO: Create SetBoneTransformByIndex. This should be faster
				
				//PoseableMeshComponent->SetBoneTransformByName(StartBone, Transforms[START], EBoneSpaces::ComponentSpace);
				//PoseableMeshComponent->SetBoneTransformByName(MiddleBone, Transforms[MIDDLE], EBoneSpaces::ComponentSpace);
				//PoseableMeshComponent->SetBoneTransformByName(EndBone, Transforms[END], EBoneSpaces::ComponentSpace);
				
				/*
				const FTransform ComponentTransform = PoseableMeshComponent->GetComponentTransform();
				const FTransform StartTransform = Transforms[START] * ComponentTransform;
				const FTransform MiddleTransform = Transforms[MIDDLE] * ComponentTransform;
				const FTransform EndTransform = Transforms[END] * ComponentTransform;
				*/

				//Transforms[START].SetTranslation(Control->StartBone->GetActorLocation());
				const FTransform ComponentTransform = PoseableMeshComponent->GetComponentTransform();
				Control->StartBone->UpdateTransform(Transforms[START] * ComponentTransform);
				Control->MiddleBone->UpdateTransform(Transforms[MIDDLE] * ComponentTransform);
				Control->EndBone->UpdateTransform(Transforms[END] * ComponentTransform);

				//Control->EndBone->UpdateRelativeTransform(PoseableMeshComponent->BoneSpaceTransforms[Control->EndBone->BoneIndex], true);
				//Control->MiddleBone->UpdateRelativeTransform(PoseableMeshComponent->BoneSpaceTransforms[Control->MiddleBone->BoneIndex], true);
				//Control->StartBone->UpdateRelativeTransform(PoseableMeshComponent->BoneSpaceTransforms[Control->StartBone->BoneIndex], true);

				Control->EndEffector->Location.Clear();

				Control->JointTarget->Location.Clear();
			}
		}
	}

	// Bones
	const int32 BoneCount = Bones.Num();

	for (int32 I = 0; I < BoneCount; I++)
	{
		// Location
		if (Bones[I].Actor->Location.HasChanged() ||
			Bones[I].Actor->ForceUpdateTransform)
		{
			PoseableMeshComponent->SetBoneLocationByName(Bones[I].Bone, Bones[I].Actor->Location.Get(), EBoneSpaces::WorldSpace);
			Bones[I].Actor->Location.Clear();
		}
		// Rotation
		if (Bones[I].Actor->Rotation.HasChanged() ||
			Bones[I].Actor->ForceUpdateTransform)
		{
			PoseableMeshComponent->SetBoneRotationByName(Bones[I].Bone, Bones[I].Actor->Rotation.Get(), EBoneSpaces::WorldSpace);
			Bones[I].Actor->Rotation.Clear();
		}
		// Scale
		if (Bones[I].Actor->Scale.HasChanged() ||
			Bones[I].Actor->ForceUpdateTransform)
		{
			PoseableMeshComponent->SetBoneScaleByName(Bones[I].Bone, Bones[I].Actor->Scale.Get(), EBoneSpaces::WorldSpace);
			Bones[I].Actor->Scale.Clear();
		}
		Bones[I].Actor->ForceUpdateTransform = false;
	}
}

#endif // #if WITH_EDITOR

#if WITH_EDITOR

void ACsPoseableMeshActor::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	if (UCsCommon::IsPlayInEditor(GetWorld()))
	{
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
	}
	Super::PostEditChangeProperty(e);
}

void ACsPoseableMeshActor::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& e)
{
	const int32 Controls_TwoBoneIK_Index = e.GetArrayIndex(TEXT("Controls_TwoBoneIK"));

	// Controls_TwoBoneIK
	if (Controls_TwoBoneIK_Index != INDEX_NONE)
	{
		const int32 Index = Controls_TwoBoneIK_Index;

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
			if (Controls_TwoBoneIK[Index].Actor)
			{
				Controls_TwoBoneIK[Index].Actor->SetActorLabel(Controls_TwoBoneIK[Index].Control);
			}
		}
		// Controls[Index].IK.IKBone
		if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsAnimControlInfo_TwoBoneIK_IK, IKBone))
		{
			const FName BoneName	  = Controls_TwoBoneIK[Index].IK.IKBone;
			const int32 BoneIndex	  = PoseableMeshComponent->GetBoneIndex(BoneName);
			
			Controls_TwoBoneIK[Index].IK.IKBoneIndex = BoneIndex;

			Controls_TwoBoneIK[Index].EndEffector.EffectorSpaceBoneName = BoneName;
			Controls_TwoBoneIK[Index].EndEffector.EffectorSpaceBoneIndex = BoneIndex;

			if (BoneName == NAME_None || BoneIndex == INDEX_NONE)
			{
				Controls_TwoBoneIK[Index].IK.IKBone = NAME_None;
				Controls_TwoBoneIK[Index].IK.IKBoneIndex = INDEX_NONE;
				Controls_TwoBoneIK[Index].IK.IKBoneArrayIndex = INDEX_NONE;
				Controls_TwoBoneIK[Index].IK.Last_IKBone = BoneName;
				Controls_TwoBoneIK[Index].IK.ParentBone = NAME_None;
				Controls_TwoBoneIK[Index].IK.ParentBoneIndex = INDEX_NONE;
				Controls_TwoBoneIK[Index].IK.ParentBoneIndex = INDEX_NONE;

				Controls_TwoBoneIK[Index].EndEffector.EffectorSpaceBoneName = NAME_None;
				Controls_TwoBoneIK[Index].EndEffector.EffectorSpaceBoneIndex = INDEX_NONE;
				Controls_TwoBoneIK[Index].EndEffector.EffectorSpaceBoneArrayIndex = NAME_None;

				Controls_TwoBoneIK[Index].JointTarget.JointTargetSpaceBoneName = NAME_None;
				Controls_TwoBoneIK[Index].JointTarget.JointTargetSpaceBoneIndex = INDEX_NONE;
				Controls_TwoBoneIK[Index].JointTarget.JointTargetSpaceBoneArrayIndex = INDEX_NONE;

				Controls_TwoBoneIK_Copy[Index] = Controls_TwoBoneIK[Index];

				Super::PostEditChangeChainProperty(e);
				return;
			}

			if (BoneName == Controls_TwoBoneIK[Index].IK.Last_IKBone)
			{
				Super::PostEditChangeChainProperty(e);
				return;
			}

			Controls_TwoBoneIK[Index].IK.Last_IKBone = BoneName;

			ACsAnim_Control_TwoBoneIK* Control = Controls_TwoBoneIK[Index].Actor;

			if (!Control)
			{
				// Check control Children who do NOT have a parent, Delete them
				TArray<AActor*> Helpers;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACsAnim_ControlHelper::StaticClass(), Helpers);

				const int32 Count = Helpers.Num();

				for (int32 I = 0; I < Count; I++)
				{
					ACsAnim_ControlHelper* Helper = Cast<ACsAnim_ControlHelper>(Helpers[I]);

					if (Helper->ControlIndex == INDEX_NONE)
						Helper->Destroy();
				}
				// Recreate the Control
				Create_Control_TwoBoneIK(Index);
				Controls_TwoBoneIK_Copy[Index] = Controls_TwoBoneIK[Index];

				Super::PostEditChangeChainProperty(e);
				return;
			}

			// Cache ArrayIndex
			Controls_TwoBoneIK[Index].IK.IKBoneArrayIndex = INDEX_NONE;

			{
				const int32 Count = Bones.Num();

				for (int32 I = 0; I < Count; I++)
				{
					if (Bones[I].Bone == BoneName)
					{
						Controls_TwoBoneIK[Index].IK.IKBoneArrayIndex = I;
						Controls_TwoBoneIK[Index].EndEffector.EffectorSpaceBoneArrayIndex = I;
						break;
					}
				}
			}

			// Middle Bone
			const FName MiddleBoneName  = PoseableMeshComponent->GetParentBone(BoneName);
			const int32 MiddleBoneIndex = PoseableMeshComponent->GetBoneIndex(MiddleBoneName);

			Controls_TwoBoneIK[Index].IK.ParentBone      = MiddleBoneName;
			Controls_TwoBoneIK[Index].IK.ParentBoneIndex = MiddleBoneIndex;
			Controls_TwoBoneIK[Index].IK.ParentBoneArrayIndex = INDEX_NONE;

			// Start Bone
			const FName StartBoneName = PoseableMeshComponent->GetParentBone(MiddleBoneName);
			const int32 StartBoneIndex = PoseableMeshComponent->GetBoneIndex(StartBoneName);

			Controls_TwoBoneIK[Index].JointTarget.JointTargetSpaceBoneName = StartBoneName;
			Controls_TwoBoneIK[Index].JointTarget.JointTargetSpaceBoneIndex = StartBoneIndex;
			Controls_TwoBoneIK[Index].JointTarget.JointTargetSpaceBoneArrayIndex = INDEX_NONE;

			// Change JointTarget (Start Bone)
			{
				// Reset PREVIOUS Start Bone
				if (Control->StartBone)
				{
					Control->StartBone->ResetRelativeTransform();
					PoseableMeshComponent->SetBoneTransformByName(Control->StartBone->Bone, Control->StartBone->GetActorTransform(), EBoneSpaces::ComponentSpace);
				}

				ACsAnim_ControlHelper_JointTarget* JointTarget = Control->JointTarget;

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
							//JointTarget->Location.Clear();
							
							//JointTarget->UpdateRelativeTransform(Control->StartBone->DefaultRelativeTransform, true);

							Controls_TwoBoneIK[Index].JointTarget.JointTargetSpaceBoneArrayIndex = I;
							break;
						}
					}
				}
				else
				{
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

							Controls_TwoBoneIK[Index].IK.ParentBoneArrayIndex = I;
						}
					}
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::Create_Control_TwoBoneIK(%s): IKBone's Parent Bone (Middle Bone): %s is NOT found in SkeletalMesh: %s"), *GetName(), *(MiddleBoneName.ToString()), *(PoseableMeshComponent->SkeletalMesh->GetName()));
				}
			}
			// Change EndEffector (End Bone)
			{
				ACsAnim_ControlHelper_EndEffector* EndEffector = Control->EndEffector;

				// Reset PREVIOUS End Bone. TODO: Need to check if any other Control is referencing this bone
				if (Control->EndBone)
				{
					Control->EndBone->ResetRelativeTransform();
					PoseableMeshComponent->SetBoneTransformByName(Control->EndBone->Bone, Control->EndBone->GetActorTransform(), EBoneSpaces::ComponentSpace);
				}

				const int32 Count = Bones.Num();

				for (int32 I = 0; I < Count; I++)
				{
					if (Bones[I].Bone == BoneName)
					{
						// Reset NEW / CURRENT End Bone
						Control->EndBone = Bones[I].Actor;
						Control->EndBone->ResetRelativeTransform();
						PoseableMeshComponent->SetBoneTransformByName(Control->EndBone->Bone, Control->EndBone->GetActorTransform(), EBoneSpaces::ComponentSpace);

						EndEffector->SetActorLocation(Control->EndBone->GetActorLocation());
						EndEffector->Location = Control->EndBone->GetActorLocation();
						//EndEffector->Location.Clear();

						//EndEffector->UpdateRelativeTransform(Control->EndBone->DefaultRelativeTransform, true);
						break;
					}
				}
			}

			Controls_TwoBoneIK_Copy[Index] = Controls_TwoBoneIK[Index];
		}
	}
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
		ACsAnim_Bone* Bone = GetWorld()->SpawnActor<ACsAnim_Bone>();

		const FName BoneName = BoneNames[I];
		Bone->SetActorLabel(BoneName.ToString());
		Bone->Bone = BoneName;
		Bone->Root = this;

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
		
		const int32 BoneIndex = PoseableMeshComponent->GetBoneIndex(BoneName);
		Bone->BoneIndex		  = BoneIndex;
		FTransform Transform  = PoseableMeshComponent->BoneSpaceTransforms[BoneIndex];

		Bone->UpdateRelativeTransform(Transform, true);

		Bone->DefaultRelativeTransform = Transform;
		Bone->ArrayIndex = I;

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

void ACsPoseableMeshActor::Create_Control_TwoBoneIK(const int32 Index)
{
	ACsAnim_Control_TwoBoneIK* Control = GetWorld()->SpawnActor<ACsAnim_Control_TwoBoneIK>();

	Control->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

	Control->SetActorLabel(Controls_TwoBoneIK[Index].Control);
	Controls_TwoBoneIK[Index].Actor = Control;
	
	const FName BoneName = Controls_TwoBoneIK[Index].IK.IKBone;
	const int32 BoneIndex = PoseableMeshComponent->GetBoneIndex(BoneName);

	Controls_TwoBoneIK[Index].IK.IKBoneIndex = BoneIndex;

	Controls_TwoBoneIK[Index].EndEffector.EffectorSpaceBoneName = BoneName;
	Controls_TwoBoneIK[Index].EndEffector.EffectorSpaceBoneIndex = BoneIndex;

	// Cache ArrayIndex
	Controls_TwoBoneIK[Index].IK.IKBoneArrayIndex = INDEX_NONE;

	{
		const int32 Count = Bones.Num();

		for (int32 I = 0; I < Count; I++)
		{
			if (Bones[I].Bone == BoneName)
			{
				Controls_TwoBoneIK[Index].IK.IKBoneArrayIndex = I;
				Controls_TwoBoneIK[Index].EndEffector.EffectorSpaceBoneArrayIndex = I;
				break;
			}
		}
	}

	// Middle Bone
	const FName MiddleBoneName = PoseableMeshComponent->GetParentBone(BoneName);
	const int32 MiddleBoneIndex = PoseableMeshComponent->GetBoneIndex(MiddleBoneName);

	Controls_TwoBoneIK[Index].IK.ParentBone = MiddleBoneName;
	Controls_TwoBoneIK[Index].IK.ParentBoneIndex = MiddleBoneIndex;
	Controls_TwoBoneIK[Index].IK.ParentBoneArrayIndex = INDEX_NONE;

	// Start Bone
	const FName StartBoneName = PoseableMeshComponent->GetParentBone(MiddleBoneName);
	const int32 StartBoneIndex = PoseableMeshComponent->GetBoneIndex(StartBoneName);

	Controls_TwoBoneIK[Index].JointTarget.JointTargetSpaceBoneName = StartBoneName;
	Controls_TwoBoneIK[Index].JointTarget.JointTargetSpaceBoneIndex = StartBoneIndex;
	Controls_TwoBoneIK[Index].JointTarget.JointTargetSpaceBoneArrayIndex = INDEX_NONE;

	// Change JointTarget (Start Bone)
	ACsAnim_ControlHelper_JointTarget* JointTarget = GetWorld()->SpawnActor<ACsAnim_ControlHelper_JointTarget>();
	JointTarget->ControlIndex					   = Index;
	Control->JointTarget						   = JointTarget;
	JointTarget->AttachToActor(Control, FAttachmentTransformRules::KeepRelativeTransform);
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
					//JointTarget->Location.Clear();

					//JointTarget->UpdateRelativeTransform(Control->StartBone->DefaultRelativeTransform, true);

					Controls_TwoBoneIK[Index].JointTarget.JointTargetSpaceBoneArrayIndex = I;
					break;
				}
			}
		}
		else
		{
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

					Controls_TwoBoneIK[Index].IK.ParentBoneArrayIndex = I;
				}
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::Create_Control_TwoBoneIK(%s): IKBone's Parent Bone (Middle Bone): %s is NOT found in SkeletalMesh: %s"), *GetName(), *(MiddleBoneName.ToString()), *(PoseableMeshComponent->SkeletalMesh->GetName()));
		}
	}
	// Change EndEffector (End Bone)
	ACsAnim_ControlHelper_EndEffector* EndEffector = GetWorld()->SpawnActor<ACsAnim_ControlHelper_EndEffector>();
	EndEffector->ControlIndex					   = Index;
	Control->EndEffector						   = EndEffector;
	EndEffector->AttachToActor(Control, FAttachmentTransformRules::KeepRelativeTransform);

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
					//EndEffector->Location.Clear();
					
					//EndEffector->UpdateRelativeTransform(Control->EndBone->DefaultRelativeTransform, true);
					break;
				}
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::Create_Control_TwoBoneIK(%s): IKBone (End Bone): %s is NOT found in SkeletalMesh: %s"), *GetName(), *(BoneName.ToString()), *(PoseableMeshComponent->SkeletalMesh->GetName()));
		}
	}
}

// Copied from Engine\Source\Runtime\AnimGraphRuntime\Private\BoneControllers\AnimNode_TowBoneIK.cpp

void ACsPoseableMeshActor::PerformTwoBoneIK(const int32 ControlIndex, TArray<FTransform>& OutTransforms)
{
	const int32 StartIndex  = Controls_TwoBoneIK[ControlIndex].JointTarget.JointTargetSpaceBoneIndex;
	const int32 MiddleIndex = Controls_TwoBoneIK[ControlIndex].IK.ParentBoneIndex;
	const int32 EndIndex    = Controls_TwoBoneIK[ControlIndex].IK.IKBoneIndex;

	if (StartIndex == INDEX_NONE || MiddleIndex == INDEX_NONE || EndIndex == INDEX_NONE)
		return;

	// Get Local Space transforms for our bones. We do this first in case they already are local.
	// As right after we get them in component space. (And that does the auto conversion).
	// We might save one transform by doing local first...
	const FTransform EndLocalTransform = PoseableMeshComponent->BoneSpaceTransforms[EndIndex];

	const FTransform ComponentTransform = PoseableMeshComponent->GetComponentTransform();

	// Now get those in component space...
	FTransform StartTransform = PoseableMeshComponent->GetBoneTransform(StartIndex);
	FTransform MiddleTransform = PoseableMeshComponent->GetBoneTransform(MiddleIndex);
	FTransform EndTransform = PoseableMeshComponent->GetBoneTransform(EndIndex);

	StartTransform.SetToRelativeTransform(ComponentTransform);
	MiddleTransform.SetToRelativeTransform(ComponentTransform);
	EndTransform.SetToRelativeTransform(ComponentTransform);

	// Get current position of root of limb.
	// All position are in Component space.
	const FVector StartPos		   = StartTransform.GetTranslation();
	const FVector InitialMiddlePos = MiddleTransform.GetTranslation();
	const FVector InitialEndPos    = EndTransform.GetTranslation();

	ACsAnim_Control_TwoBoneIK* Control  = Controls_TwoBoneIK[ControlIndex].Actor;
	//const FTransform ComponentTransform = PoseableMeshComponent->GetComponentTransform();

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

	const bool bAllowStretching   = Controls_TwoBoneIK[ControlIndex].IK.bAllowStretching;
	const float StartStretchRatio = Controls_TwoBoneIK[ControlIndex].IK.StartStretchRatio;
	const float MaxStretchRatio   = Controls_TwoBoneIK[ControlIndex].IK.MaxStretchRatio;

	AnimationCore::SolveTwoBoneIK(StartTransform, MiddleTransform, EndTransform, JointTargetPos, DesiredPos, bAllowStretching, StartStretchRatio, MaxStretchRatio);

	// Update transform for end bone.

	// only allow bTakeRotationFromEffectorSpace during bone space
	if (Controls_TwoBoneIK[ControlIndex].EndEffector.bTakeRotationFromEffectorSpace)
	{
		EndTransform.SetRotation(EndEffectorTransform.GetRotation());
	}
	else 
	if (Controls_TwoBoneIK[ControlIndex].EndEffector.bMaintainEffectorRelRot)
	{
		EndTransform = EndLocalTransform * MiddleTransform;
	}
	OutTransforms.Add(StartTransform);
	OutTransforms.Add(MiddleTransform);
	OutTransforms.Add(EndTransform);
}

#endif // #if WITH_EDITOR