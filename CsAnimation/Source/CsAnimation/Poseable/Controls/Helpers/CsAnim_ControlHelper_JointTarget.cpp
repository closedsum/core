// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Poseable/Controls/Helpers/CsAnim_ControlHelper_JointTarget.h"
#include "CsAnimation.h"

ACsAnim_ControlHelper_JointTarget::ACsAnim_ControlHelper_JointTarget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	LockRotation = true;
	LockScale = true;

	RecordRotation = !LockRotation;
	RecordScale = !LockScale;
}