// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/Poseable/CsPoseableMeshActor.h"
#include "Components/CsPoseableMeshComponent.h"
#include "CsCore.h"
#include "CsCommon.h"
#include "Animation/Poseable/CsAnim_Bone.h"
#include "Animation/Poseable/CsAnim_Control.h"
#include "Animation/Poseable/CsAnim_Control_TwoBoneIK.h"
#include "Animation/Poseable/CsAnim_Control_EndEffector.h"
#include "Animation/Poseable/CsAnim_Control_JointTarget.h"

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
	
	// Controls
	const int32 ControlCount = Controls.Num();


	// Bones
	const int32 BoneCount = Bones.Num();

	for (int32 I = 0; I < BoneCount; I++)
	{
		// Location
		if (Bones[I].Actor->Location.HasChanged())
		{
			PoseableMeshComponent->SetBoneLocationByName(Bones[I].Bone, Bones[I].Actor->Location.Get(), EBoneSpaces::WorldSpace);
			Bones[I].Actor->Location.Clear();
		}
		// Rotation
		if (Bones[I].Actor->Rotation.HasChanged())
		{
			PoseableMeshComponent->SetBoneRotationByName(Bones[I].Bone, Bones[I].Actor->Rotation.Get(), EBoneSpaces::WorldSpace);
			Bones[I].Actor->Rotation.Clear();
		}
		// Scale
		if (Bones[I].Actor->Scale.HasChanged())
		{
			PoseableMeshComponent->SetBoneScaleByName(Bones[I].Bone, Bones[I].Actor->Scale.Get(), EBoneSpaces::WorldSpace);
			Bones[I].Actor->Scale.Clear();
		}
	}
}

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
	// Controls
	const int32 Index = e.GetArrayIndex(TEXT("Controls"));

	if (Index == INDEX_NONE)
	{
		Super::PostEditChangeChainProperty(e);
		return;
	}

	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	// Controls[Index].Type
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsAnimControlInfo, Type))
	{
		if (Controls[Index].Type == Controls[Index].Last_Type)
		{
			Super::PostEditChangeChainProperty(e);
			return;
		}

		const TCsAnimControl ControlType = Controls[Index].Type;

		// None
		if (ControlType == ECsAnimControl::None)
		{
			// TwoBoneIK
			if (ACsAnim_Control_TwoBoneIK* Control = Cast<ACsAnim_Control_TwoBoneIK>(Controls[Index].Actor))
			{
				Control->EndEffector->Destroy();
				Control->JointTarget->Destroy();
				Control->Destroy();
			}
		}
		// TwoBoneIK
		if (ControlType == ECsAnimControl::TwoBoneIK)
		{
			ACsAnim_Control_TwoBoneIK* Control = GetWorld()->SpawnActor<ACsAnim_Control_TwoBoneIK>();

			Control->SetActorTransform(GetActorTransform());
			Control->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

			Control->SetActorLabel(Controls[Index].Control);
			Controls[Index].Actor = Control;
			// End Effector
			ACsAnim_Control_EndEffector* EndEffector = GetWorld()->SpawnActor<ACsAnim_Control_EndEffector>();
			Control->EndEffector = EndEffector;
			EndEffector->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

			const int32 Count = Bones.Num();

			for (int32 I = 0; I < Count; I++)
			{
				if (Bones[I].Bone == Controls[Index].EndEffector.EffectorSpaceBoneName)
				{
					EndEffector->SetActorTransform(Bones[I].Actor->GetActorTransform());
					break;
				}
			}
			// JointTarget
			ACsAnim_Control_JointTarget* JointTarget = GetWorld()->SpawnActor<ACsAnim_Control_JointTarget>();
			Control->JointTarget = JointTarget;
			JointTarget->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

			const FName JointBoneName = PoseableMeshComponent->GetParentBone(Controls[Index].IK.IKBone);

			if (JointBoneName != NAME_None)
			{
				for (int32 I = 0; I < Count; I++)
				{
					if (Bones[I].Bone == JointBoneName)
					{
						JointTarget->SetActorTransform(Bones[I].Actor->GetActorTransform());
						break;
					}
				}
			}
			Controls[Index].Last_Type = Controls[Index].Type;
		}
	}
	// Controls[Index].Control
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsAnimControlInfo, Control))
	{
		if (Controls[Index].Actor)
		{
			Controls[Index].Actor->SetActorLabel(Controls[Index].Control);
		}
	}
	// Controls[Index].IK.IKBone
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsAnimControlInfo_IK, IKBone))
	{
		const FName BoneName = Controls[Index].IK.IKBone;

		if (BoneName == NAME_None)
		{
			Controls[Index].IK.Last_IKBone = BoneName;

			Super::PostEditChangeChainProperty(e);
			return;
		}

		if (BoneName == Controls[Index].IK.Last_IKBone)
		{
			Super::PostEditChangeChainProperty(e);
			return;
		}

		ACsAnim_Control_TwoBoneIK* Control = Cast<ACsAnim_Control_TwoBoneIK>(Controls[Index].Actor);

		if (!Control)
		{
			Super::PostEditChangeChainProperty(e);
			return;
		}

		// Change JointTarget
		ACsAnim_Control_JointTarget* JointTarget = Control->JointTarget;
		const FName JointBoneName				 = PoseableMeshComponent->GetParentBone(BoneName);

		if (JointBoneName != NAME_None)
		{
			const int32 Count = Bones.Num();

			for (int32 I = 0; I < Count; I++)
			{
				if (Bones[I].Bone == JointBoneName)
				{
					JointTarget->SetActorTransform(Bones[I].Actor->GetActorTransform());
					break;
				}
			}
		}
		Controls[Index].IK.Last_IKBone = BoneName;
	}
	// Controls[Index].EndEffector.EffectorSpaceBoneName
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsAnimControlInfo_EndEffector, EffectorSpaceBoneName))
	{
		const FName BoneName = Controls[Index].EndEffector.EffectorSpaceBoneName;

		if (BoneName == NAME_None)
		{
			Controls[Index].EndEffector.Last_EffectorSpaceBoneName = BoneName;

			Super::PostEditChangeChainProperty(e);
			return;
		}

		if (Controls[Index].EndEffector.EffectorSpaceBoneName == Controls[Index].EndEffector.Last_EffectorSpaceBoneName)
		{
			Super::PostEditChangeChainProperty(e);
			return;
		}

		ACsAnim_Control_TwoBoneIK* Control = Cast<ACsAnim_Control_TwoBoneIK>(Controls[Index].Actor);

		// Change End Effector
		ACsAnim_Control_EndEffector* EndEffector = Control->EndEffector;
		EndEffector->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

		const int32 Count = Bones.Num();

		for (int32 I = 0; I < Count; I++)
		{
			if (Bones[I].Bone == BoneName)
			{
				EndEffector->SetActorTransform(Bones[I].Actor->GetActorTransform());
				break;
			}
		}
		Controls[Index].EndEffector.Last_EffectorSpaceBoneName = BoneName;
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
		FTransform Transform  = PoseableMeshComponent->BoneSpaceTransforms[BoneIndex];

		Bone->SetActorRelativeTransform(Transform);

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

/*
void FAnimNode_TwoBoneIK::EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms)
{
SCOPE_CYCLE_COUNTER(STAT_TwoBoneIK_Eval);

check(OutBoneTransforms.Num() == 0);

const FBoneContainer& BoneContainer = Output.Pose.GetPose().GetBoneContainer();

// Get indices of the lower and upper limb bones and check validity.
bool bInvalidLimb = false;

FCompactPoseBoneIndex IKBoneCompactPoseIndex = IKBone.GetCompactPoseIndex(BoneContainer);

FCompactPoseBoneIndex UpperLimbIndex(INDEX_NONE);
const FCompactPoseBoneIndex LowerLimbIndex = BoneContainer.GetParentBoneIndex(IKBoneCompactPoseIndex);
if (LowerLimbIndex == INDEX_NONE)
{
bInvalidLimb = true;
}
else
{
UpperLimbIndex = BoneContainer.GetParentBoneIndex(LowerLimbIndex);
if (UpperLimbIndex == INDEX_NONE)
{
bInvalidLimb = true;
}
}

const bool bInBoneSpace = (EffectorLocationSpace == BCS_ParentBoneSpace) || (EffectorLocationSpace == BCS_BoneSpace);
const int32 EffectorBoneIndex = bInBoneSpace ? BoneContainer.GetPoseBoneIndexForBoneName(EffectorSpaceBoneName) : INDEX_NONE;
const FCompactPoseBoneIndex EffectorSpaceBoneIndex = BoneContainer.MakeCompactPoseIndex(FMeshPoseBoneIndex(EffectorBoneIndex));

if (bInBoneSpace && (EffectorSpaceBoneIndex == INDEX_NONE))
{
bInvalidLimb = true;
}

// If we walked past the root, this controlled is invalid, so return no affected bones.
if( bInvalidLimb )
{
return;
}

// Get Local Space transforms for our bones. We do this first in case they already are local.
// As right after we get them in component space. (And that does the auto conversion).
// We might save one transform by doing local first...
const FTransform EndBoneLocalTransform = Output.Pose.GetLocalSpaceTransform(IKBoneCompactPoseIndex);

// Now get those in component space...
FTransform LowerLimbCSTransform = Output.Pose.GetComponentSpaceTransform(LowerLimbIndex);
FTransform UpperLimbCSTransform = Output.Pose.GetComponentSpaceTransform(UpperLimbIndex);
FTransform EndBoneCSTransform = Output.Pose.GetComponentSpaceTransform(IKBoneCompactPoseIndex);

// Get current position of root of limb.
// All position are in Component space.
const FVector RootPos = UpperLimbCSTransform.GetTranslation();
const FVector InitialJointPos = LowerLimbCSTransform.GetTranslation();
const FVector InitialEndPos = EndBoneCSTransform.GetTranslation();

// Transform EffectorLocation from EffectorLocationSpace to ComponentSpace.
FTransform EffectorTransform(EffectorLocation);
FAnimationRuntime::ConvertBoneSpaceTransformToCS(Output.AnimInstanceProxy->GetComponentTransform(), Output.Pose, EffectorTransform, EffectorSpaceBoneIndex, EffectorLocationSpace);

// Get joint target (used for defining plane that joint should be in).
FTransform JointTargetTransform(JointTargetLocation);
FCompactPoseBoneIndex JointTargetSpaceBoneIndex(INDEX_NONE);

if (JointTargetLocationSpace == BCS_ParentBoneSpace || JointTargetLocationSpace == BCS_BoneSpace)
{
int32 Index = BoneContainer.GetPoseBoneIndexForBoneName(JointTargetSpaceBoneName);
JointTargetSpaceBoneIndex = BoneContainer.MakeCompactPoseIndex(FMeshPoseBoneIndex(Index));
}

FAnimationRuntime::ConvertBoneSpaceTransformToCS(Output.AnimInstanceProxy->GetComponentTransform(), Output.Pose, JointTargetTransform, JointTargetSpaceBoneIndex, JointTargetLocationSpace);

FVector	JointTargetPos = JointTargetTransform.GetTranslation();

// This is our reach goal.
FVector DesiredPos = EffectorTransform.GetTranslation();

// IK solver
UpperLimbCSTransform.SetLocation(RootPos);
LowerLimbCSTransform.SetLocation(InitialJointPos);
EndBoneCSTransform.SetLocation(InitialEndPos);

AnimationCore::SolveTwoBoneIK(UpperLimbCSTransform, LowerLimbCSTransform, EndBoneCSTransform, JointTargetPos, DesiredPos, bAllowStretching, StartStretchRatio, MaxStretchScale);

// Update transform for upper bone.
{
// Order important. First bone is upper limb.
OutBoneTransforms.Add( FBoneTransform(UpperLimbIndex, UpperLimbCSTransform) );
}

// Update transform for lower bone.
{
// Order important. Second bone is lower limb.
OutBoneTransforms.Add( FBoneTransform(LowerLimbIndex, LowerLimbCSTransform) );
}

// Update transform for end bone.
{
// only allow bTakeRotationFromEffectorSpace during bone space
if (bInBoneSpace && bTakeRotationFromEffectorSpace)
{
EndBoneCSTransform.SetRotation(EffectorTransform.GetRotation());
}
else if (bMaintainEffectorRelRot)
{
EndBoneCSTransform = EndBoneLocalTransform * LowerLimbCSTransform;
}
// Order important. Third bone is End Bone.
OutBoneTransforms.Add(FBoneTransform(IKBoneCompactPoseIndex, EndBoneCSTransform));
}

// Make sure we have correct number of bones
check(OutBoneTransforms.Num() == 3);
}
*/
#endif // #if WITH_EDITOR