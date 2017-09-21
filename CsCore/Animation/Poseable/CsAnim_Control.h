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

	FCsPrimitiveType<FVector> Location;
	FCsPrimitiveType<FRotator> Rotation;
	FCsPrimitiveType<FVector> Scale;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "00 Control")
	FName Control;
};