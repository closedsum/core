// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/CsWidgetActor_Damage.h"
#include "CsCore.h"

// UI
#include "UI/Simple/CsWidget_Int32.h"

ACsWidgetActor_Damage::ACsWidgetActor_Damage(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void ACsWidgetActor_Damage::Allocate_Internal(FCsWidgetActorPayload* Payload)
{
	Super::Allocate_Internal(Payload);

	UCsWidget_Int32* CurrentWidget = Cast<UCsWidget_Int32>(MyWidget);
	CurrentWidget->SetValue(Payload->Int32);
}