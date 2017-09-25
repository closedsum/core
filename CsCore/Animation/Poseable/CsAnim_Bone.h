// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/StaticMeshActor.h"
#include "CsTypes.h"
#include "CsAnim_Bone.generated.h"

UCLASS()
class CSCORE_API ACsAnim_Bone : public AStaticMeshActor
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;
	void OnTick_Editor(const float &DeltaSeconds);

	bool HasTickedInEditor;
	/* Bone Name */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Bone")
	FName Bone;
	/* Index in Bone Array in SkeletalMesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Bone")
	int32 BoneIndex;
	/* Index in Bone Array in PoseableMeshActor */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Bone")
	int32 ArrayIndex;
	/* Reference to PoseableMeshActor */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Bone")
	AActor* Root;

	bool ForceUpdateTransform;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Control")
	bool RecordTransform;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Control")
	bool RecordLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Control")
	bool RecordRotation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Control")
	bool RecordScale;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Control")
	FTransform DefaultRelativeTransform;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Control")
	FTransform DefaultComponentTransform;

	void ResetRelativeTransform();

	FCsPrimitiveType<FVector> Location;
	FCsPrimitiveType<FRotator> Rotation;
	FCsPrimitiveType<FVector> Scale;

	bool HasTransformChanged();
	void ResolveTransform();
	void UpdateTransform(const FTransform &Transform);
	void UpdateRelativeTransform(const FTransform &Transform, const bool &Resolve);
};