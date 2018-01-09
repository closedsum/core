// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/Poseable/Controls/CsAnim_Control_FK.h"
#include "CsCore.h"
#include "Common/CsCommon.h"

ACsAnim_Control_FK::ACsAnim_Control_FK(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void ACsAnim_Control_FK::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

#if WITH_EDITOR
	// Handle Waypoints placed in Editor
	if (UCsCommon::IsPlayInEditor(GetWorld()))
	{
		OnTick_Editor(DeltaSeconds);
		return;
	}
#endif // #if WITH_EDITOR
}

bool ACsAnim_Control_FK::ShouldTickIfViewportsOnly() const
{
#if WITH_EDITOR
	if (UCsCommon::IsPlayInEditor(GetWorld()))
		return true;
#endif // #if WITH_EDITOR
	return Super::ShouldTickIfViewportsOnly();
}

#if WITH_EDITOR

void ACsAnim_Control_FK::OnTick_Editor(const float &DeltaSeconds)
{
	Super::OnTick_Editor(DeltaSeconds);
}

#endif // #if WITH_EDITOR