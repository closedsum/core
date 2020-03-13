// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
#include "CsAnim_ControlAnchor.generated.h"

class ACsAnim_Control;

UCLASS()
class CSANIMATION_API ACsAnim_ControlAnchor : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;
	virtual void OnTick_Editor(const float &DeltaSeconds);

	bool HasTickedInEditor;

	class USceneComponent* DefaultRootComponent;

	/* Reference to Control */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Control")
	ACsAnim_Control* Control;
};