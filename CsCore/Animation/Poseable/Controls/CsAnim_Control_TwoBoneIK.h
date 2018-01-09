// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Animation/Poseable/Controls/CsAnim_Control.h"
#include "CsAnim_Control_TwoBoneIK.generated.h"

UCLASS()
class CSCORE_API ACsAnim_Control_TwoBoneIK : public ACsAnim_Control
{
	GENERATED_UCLASS_BODY()

#if WITH_EDITOR

	virtual void OnTick_Editor(const float &DeltaSeconds) override;	
	virtual void OnControlNameChanged() override;

#endif // #if WITH_EDITOR

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "00 Control")
	class ACsAnim_ControlHelper_EndEffector* EndEffector;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "00 Control")
	class ACsAnim_ControlHelper_JointTarget* JointTarget;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "00 Control")
	class ACsAnim_Bone* StartBone;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "00 Control")
	class ACsAnim_Bone* MiddleBone;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "00 Control")
	class ACsAnim_Bone* EndBone;
};