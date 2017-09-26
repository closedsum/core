// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Components/CsPoseableMeshComponent.h"
#include "CsCore.h"
#include "CsTypes.h"
#include "CsCommon.h"

UCsPoseableMeshComponent::UCsPoseableMeshComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCsPoseableMeshComponent::SetBoneTransformByIndex(const int32 &BoneIndex, const FTransform& InTransform, const EBoneSpaces::Type &BoneSpace)
{
	if (!SkeletalMesh || !RequiredBones.IsValid())
	{
		return;
	}

	check(!MasterPoseComponent.IsValid()); //Shouldn't call set bone functions when we are using MasterPoseComponent

	if (BoneIndex >= 0 && BoneIndex < BoneSpaceTransforms.Num())
	{
		BoneSpaceTransforms[BoneIndex] = InTransform;

		// If we haven't requested local space we need to transform the position passed in
		//if(BoneSpace != EBoneSpaces::LocalSpace)
		{
			if (BoneSpace == EBoneSpaces::WorldSpace)
			{
				BoneSpaceTransforms[BoneIndex].SetToRelativeTransform(GetComponentToWorld());
			}

			int32 ParentIndex = RequiredBones.GetParentBoneIndex(BoneIndex);
			if (ParentIndex >= 0)
			{
				FA2CSPose CSPose;
				CSPose.AllocateLocalPoses(RequiredBones, BoneSpaceTransforms);

				BoneSpaceTransforms[BoneIndex].SetToRelativeTransform(CSPose.GetComponentSpaceTransform(ParentIndex));
			}

			// Need to send new state to render thread
			RefreshBoneTransforms();
		}
	}
}

void UCsPoseableMeshComponent::SetBoneLocationByIndex(const int32 &BoneIndex, const FVector &InLocation, const EBoneSpaces::Type &BoneSpace)
{
	FTransform CurrentTransform = GetBoneTransformByIndex(BoneIndex, BoneSpace);
	CurrentTransform.SetLocation(InLocation);
	SetBoneTransformByIndex(BoneIndex, CurrentTransform, BoneSpace);
}

void UCsPoseableMeshComponent::SetBoneRotationByIndex(const int32 &BoneIndex, const FRotator &InRotation, const EBoneSpaces::Type &BoneSpace)
{
	FTransform CurrentTransform = GetBoneTransformByIndex(BoneIndex, BoneSpace);
	CurrentTransform.SetRotation(FQuat(InRotation));
	SetBoneTransformByIndex(BoneIndex, CurrentTransform, BoneSpace);
}

void UCsPoseableMeshComponent::SetBoneScaleByIndex(const int32 &BoneIndex, const FVector &InScale3D, const EBoneSpaces::Type &BoneSpace)
{
	FTransform CurrentTransform = GetBoneTransformByIndex(BoneIndex, BoneSpace);
	CurrentTransform.SetScale3D(InScale3D);
	SetBoneTransformByIndex(BoneIndex, CurrentTransform, BoneSpace);
}

template<class CompType>
FTransform GetBoneTransformByIndexHelper(const int32 &BoneIndex, const EBoneSpaces::Type &BoneSpace, FBoneContainer& RequiredBones, CompType* Component)
{
	if (BoneIndex == INDEX_NONE)
	{
		FString Message = FString::Printf(TEXT("Invalid Bone Index"));
		FFrame::KismetExecutionMessage(*Message, ELogVerbosity::Warning);
		return FTransform();
	}

	//if(BoneSpace == EBoneSpaces::LocalSpace)
	//{
	//return Component->BoneSpaceTransforms[i];
	//}

	FA2CSPose CSPose;
	CSPose.AllocateLocalPoses(RequiredBones, Component->BoneSpaceTransforms);

	if (BoneSpace == EBoneSpaces::ComponentSpace)
	{
		return CSPose.GetComponentSpaceTransform(BoneIndex);
	}
	else
	{
		return CSPose.GetComponentSpaceTransform(BoneIndex) * Component->ComponentToWorld;
	}
}

FTransform UCsPoseableMeshComponent::GetBoneTransformByIndex(const int32 &BoneIndex, const EBoneSpaces::Type &BoneSpace)
{
	if (!SkeletalMesh || !RequiredBones.IsValid())
	{
		return FTransform();
	}

	USkinnedMeshComponent* MPCPtr = MasterPoseComponent.Get();
	if (MPCPtr)
	{
		if (USkeletalMeshComponent* SMC = Cast<USkeletalMeshComponent>(MPCPtr))
		{
			if (UAnimInstance* AnimInstance = SMC->GetAnimInstance())
			{
				return GetBoneTransformByIndexHelper(BoneIndex, BoneSpace, AnimInstance->GetRequiredBones(), SMC);
			}
			FString Message = FString::Printf(TEXT("Cannot return valid bone transform. Master Pose Component has no anim instance"));
			FFrame::KismetExecutionMessage(*Message, ELogVerbosity::Warning);
			return FTransform();
		}
		FString Message = FString::Printf(TEXT("Cannot return valid bone transform. Master Pose Component is not of type USkeletalMeshComponent"));
		FFrame::KismetExecutionMessage(*Message, ELogVerbosity::Warning);
		return FTransform();
	}
	return GetBoneTransformByIndexHelper(BoneIndex, BoneSpace, RequiredBones, this);
}