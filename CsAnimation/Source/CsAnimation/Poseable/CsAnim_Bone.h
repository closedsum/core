// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
// Types
#include "Types/CsTypes_Macro.h"
#include "Types/Property/Value/CsProperty_Vector.h"
#include "Types/Property/Value/CsProperty_Rotator.h"
#include "CsAnim_Bone.generated.h"

class USceneComponent;
class UCsStaticMeshComponent;

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSANIMATION_API ACsAnim_Bone : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;
	void OnTick_Editor(const float &DeltaSeconds);

	bool HasTickedInEditor;

	USceneComponent* DefaultRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Bone")
	UCsStaticMeshComponent* StaticMeshComponent;

	/* Bone Name */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Bone")
	FName Bone;
	/* Index in Bone Array in SkeletalMesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Bone")
	int32 BoneIndex;
	/* Index in Bone Array in PoseableMeshActor */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Bone")
	int32 ArrayIndex;
	/* Parent Bone Name */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Bone")
	FName ParentBone;
	/* Index in Parent Bone Array in SkeletalMesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Bone")
	int32 ParentBoneIndex;
	/* Reference to PoseableMeshActor */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Bone")
	AActor* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "00 Bone", meta = (ClampMin = "0.01", UIMin = "0.01"))
	float HandleSize;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Bone")
	FVector HandleSize_Internal;

	TCsFVector HandleScale;

	bool ForceUpdateTransform;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Bone")
	bool LockTransform;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Bone")
	bool LockLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Bone")
	bool LockRotation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Bone")
	bool LockScale;

	bool RecordTransform;
	bool RecordLocation;
	bool RecordRotation;
	bool RecordScale;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Bone")
	FTransform DefaultRelativeTransform;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Bone")
	FTransform DefaultComponentTransform;

	void ResetRelativeTransform();

	TCsFVector RelativeLocation;
	TCsFRotator RelativeRotation;
	TCsFVector RelativeScale;

	TCsFVector Location;
	TCsFRotator Rotation;
	TCsFVector Scale;

	bool HasTransformChanged();
	void ResolveTransform();


	UFUNCTION(BlueprintCallable, Category = "Bone")
	void UpdateRelativeTransform(const FTransform &Transform, const bool &Resolve);

	UFUNCTION(BlueprintCallable, Category = "Bone")
	void UpdateTransform(const FTransform &Transform);
	UFUNCTION(BlueprintCallable, Category = "Bone")
	void UpdateLocation(const FVector &InLocation, const int32 &Axes = 7 /*ECS_AXES_3D_ALL*/);
	UFUNCTION(BlueprintCallable, Category = "Bone")
	void UpdateRotation(const FRotator &InRotation, const int32 &Axes = 7 /*ECS_AXES_3D_ALL*/);
	UFUNCTION(BlueprintCallable, Category = "Bone")
	void UpdateScale(const FVector &InScale, const int32 &Axes = 7 /*ECS_AXES_3D_ALL*/);

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

#endif // #if WITH_EDITOR
};