// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/WidgetActor/CsWidgetActor.h"
#include "CsWidgetActor_Damage.generated.h"

UCLASS()
class CSCORE_API ACsWidgetActor_Damage : public ACsWidgetActor
{
	GENERATED_UCLASS_BODY()

	virtual void Allocate_Internal(FCsWidgetActorPayload* Payload) override;
};	