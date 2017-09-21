// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/StaticMeshActor.h"
#include "CsTypes.h"
#include "CsBoneActor.generated.h"

UCLASS()
class CSCORE_API ACsBoneActor : public AStaticMeshActor
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;
	void OnTick_Editor(const float &DeltaSeconds);

	bool HasTickedInEditor;

	FCsPrimitiveType<FVector> Location;
	FCsPrimitiveType<FRotator> Rotation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Bone")
	FName Bone;
};