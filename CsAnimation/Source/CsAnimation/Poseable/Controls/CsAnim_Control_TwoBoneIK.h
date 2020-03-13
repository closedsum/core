// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Poseable/Controls/CsAnim_Control.h"
#include "CsAnim_Control_TwoBoneIK.generated.h"

class ACsAnim_ControlHelper_EndEffector;
class ACsAnim_ControlHelper_JointTarget;
class ACsAnim_Bone;

UCLASS()
class CSANIMATION_API ACsAnim_Control_TwoBoneIK : public ACsAnim_Control
{
	GENERATED_UCLASS_BODY()

#if WITH_EDITOR

	virtual void OnTick_Editor(const float &DeltaSeconds) override;	
	virtual void OnControlNameChanged() override;

#endif // #if WITH_EDITOR

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "00 Control")
	ACsAnim_ControlHelper_EndEffector* EndEffector;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "00 Control")
	ACsAnim_ControlHelper_JointTarget* JointTarget;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "00 Control")
	ACsAnim_Bone* StartBone;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "00 Control")
	ACsAnim_Bone* MiddleBone;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "00 Control")
	ACsAnim_Bone* EndBone;
};