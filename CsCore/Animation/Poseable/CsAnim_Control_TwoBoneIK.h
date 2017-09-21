// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Animation/Poseable/CsAnim_Control.h"
#include "CsTypes.h"
#include "CsAnim_Control_TwoBoneIK.generated.h"

UCLASS()
class CSCORE_API ACsAnim_Control_TwoBoneIK : public ACsAnim_Control
{
	GENERATED_UCLASS_BODY()

	virtual void OnTick_Editor(const float &DeltaSeconds) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "00 Control")
	class ACsAnim_Control_EndEffector* EndEffector;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "00 Control")
	class ACsAnim_Control_JointTarget* JointTarget;
};