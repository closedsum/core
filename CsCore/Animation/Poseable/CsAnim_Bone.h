// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
#include "CsTypes.h"
#include "CsAnim_Bone.generated.h"

UCLASS()
class CSCORE_API ACsAnim_Bone : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;
	void OnTick_Editor(const float &DeltaSeconds);

	bool HasTickedInEditor;

	class USceneComponent* DefaultRootComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "00 Bone")
	class UCsStaticMeshComponent* StaticMeshComponent;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "00 Bone", meta = (ClampMin = "0.01", UIMin = "0.01"))
	float HandleSize;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Bone")
	FVector HandleSize_Internal;

	FCsPrimitiveType<FVector> HandleScale;

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

	FCsPrimitiveType<FVector> Location;
	FCsPrimitiveType<FRotator> Rotation;
	FCsPrimitiveType<FVector> Scale;

	bool HasTransformChanged();
	void ResolveTransform();

	UFUNCTION(BlueprintCallable, Category = "Bone")
	void UpdateTransform(const FTransform &Transform);
	UFUNCTION(BlueprintCallable, Category = "Bone")
	void UpdateLocation(const FVector &InLocation);
	UFUNCTION(BlueprintCallable, Category = "Bone")
	void UpdateRotation(const FRotator &InRotation);
	UFUNCTION(BlueprintCallable, Category = "Bone")
	void UpdateScale(const FVector &InScale);
	UFUNCTION(BlueprintCallable, Category = "Bone")
	void UpdateRelativeTransform(const FTransform &Transform, const bool &Resolve);
};