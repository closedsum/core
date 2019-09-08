#pragma once

#include "Components/PoseableMeshComponent.h"
#include "CsPoseableMeshComponent.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class CSCORE_API UCsPoseableMeshComponent : public UPoseableMeshComponent
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "Components|PoseableMesh")
	void SetBoneTransformByIndex(const int32 &BoneIndex, const FTransform& InTransform, const EBoneSpaces::Type &BoneSpace);

	UFUNCTION(BlueprintCallable, Category = "Components|PoseableMesh")
	void SetBoneLocationByIndex(const int32 &BoneIndex, const FVector &InLocation, const EBoneSpaces::Type &BoneSpace);

	UFUNCTION(BlueprintCallable, Category = "Components|PoseableMesh")
	void SetBoneRotationByIndex(const int32 &BoneIndex, const FRotator &InRotation, const EBoneSpaces::Type &BoneSpace);

	UFUNCTION(BlueprintCallable, Category = "Components|PoseableMesh")
	void SetBoneScaleByIndex(const int32 &BoneIndex, const FVector &InScale3D, const EBoneSpaces::Type &BoneSpace);

	UFUNCTION(BlueprintCallable, Category = "Components|PoseableMesh")
	FTransform GetBoneTransformByIndex(const int32 &BoneIndex, const EBoneSpaces::Type &BoneSpace);
};