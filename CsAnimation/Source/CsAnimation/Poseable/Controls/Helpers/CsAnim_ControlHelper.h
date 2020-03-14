// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/StaticMeshActor.h"
// Types
#include "Types/CsTypes_Primitive.h"
#include "Types/Property/Value/CsProperty_Vector.h"
#include "Types/Property/Value/CsProperty_Rotator.h"
#include "CsAnim_ControlHelper.generated.h"

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSANIMATION_API ACsAnim_ControlHelper : public AStaticMeshActor
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;
	virtual void OnTick_Editor(const float &DeltaSeconds);

	/* Index for Control in Control Array in PoseableMeshActor */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Helper")
	int32 ControlIndex;
	/* Reference to PoseableMeshActor */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Helper")
	AActor* Root;

	bool HasTickedInEditor;

	bool ForceUpdateTransform;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Helper")
	bool LockTransform;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Helper")
	bool LockLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Helper")
	bool LockRotation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Helper")
	bool LockScale;

	bool RecordTransform;
	bool RecordLocation;
	bool RecordRotation;
	bool RecordScale;

	TCsFVector Location;
	TCsFRotator Rotation;
	TCsFVector Scale;

	bool HasTransformChanged();
	void ResolveTransform();
	void UpdateRelativeTransform(const FTransform &Transform, const bool &Resolve);
};