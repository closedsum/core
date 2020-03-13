// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Poseable/Controls/Helpers/CsAnim_ControlHelper_EndEffector.h"
#include "CsAnimation.h"

ACsAnim_ControlHelper_EndEffector::ACsAnim_ControlHelper_EndEffector(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	LockRotation = true;
	LockScale = true;

	RecordRotation = !LockRotation;
	RecordScale = !LockScale;
}