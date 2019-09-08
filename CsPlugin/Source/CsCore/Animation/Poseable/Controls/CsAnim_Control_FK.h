// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Animation/Poseable/Controls/CsAnim_Control.h"
#include "CsAnim_Control_FK.generated.h"

UCLASS()
class CSCORE_API ACsAnim_Control_FK : public ACsAnim_Control
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;

#if WITH_EDITOR

	virtual void OnTick_Editor(const float &DeltaSeconds);

#endif // #if WITH_EDITOR
};