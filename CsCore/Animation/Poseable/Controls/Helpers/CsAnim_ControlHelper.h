// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/StaticMeshActor.h"
#include "CsTypes.h"
#include "CsAnim_ControlHelper.generated.h"

UCLASS()
class CSCORE_API ACsAnim_ControlHelper : public AStaticMeshActor
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;
	virtual void OnTick_Editor(const float &DeltaSeconds);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Helper")
	int32 ControlIndex;

	bool HasTickedInEditor;

	FCsPrimitiveType<FVector> Location;
	FCsPrimitiveType<FRotator> Rotation;
	FCsPrimitiveType<FVector> Scale;

	bool HasTransformChanged();
	void ResolveTransform();
	void UpdateRelativeTransform(const FTransform &Transform, const bool &Resolve);
};