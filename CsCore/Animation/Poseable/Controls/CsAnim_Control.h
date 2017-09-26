// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/StaticMeshActor.h"
#include "CsTypes.h"
#include "CsAnim_Control.generated.h"

UCLASS()
class CSCORE_API ACsAnim_Control : public AStaticMeshActor
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;
	virtual void OnTick_Editor(const float &DeltaSeconds);

	bool HasTickedInEditor;
	/* Control Name */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Control")
	FName Control;
	/* Reference to PoseableMeshActor */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Control")
	AActor* Root;

	bool ForceUpdateTransform;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Control")
	bool LockTransform;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Control")
	bool LockLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Control")
	bool LockRotation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Control")
	bool LockScale;

	bool RecordTransform;
	bool RecordLocation;
	bool RecordRotation;
	bool RecordScale;

	FCsPrimitiveType<FVector> Location;
	FCsPrimitiveType<FRotator> Rotation;
	FCsPrimitiveType<FVector> Scale;
};