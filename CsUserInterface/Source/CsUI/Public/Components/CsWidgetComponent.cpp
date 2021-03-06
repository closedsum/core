// Copyright 2017 Respawn Entertainment, Inc. All rights reserved.

#include "Components/CsWidgetComponent.h"
#include "CsUI.h"

UCsWidgetComponent::UCsWidgetComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCsWidgetComponent::Show()
{
	Activate();
	SetHiddenInGame(false);
	SetVisibility(true);

	if (GetWidget())
	{
		GetWidget()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		GetWidget()->SetIsEnabled(true);
	}
}

void UCsWidgetComponent::Hide()
{
	if (GetWidget())
	{
		GetWidget()->SetIsEnabled(false);
		GetWidget()->SetVisibility(ESlateVisibility::Collapsed);
	}
	SetVisibility(false);
	SetHiddenInGame(true);
	Deactivate();
}


void UCsWidgetComponent::Enable()
{
	if (GetWidget())
		GetWidget()->SetIsEnabled(true);
}

void UCsWidgetComponent::Disable()
{
	if (GetWidget())
		GetWidget()->SetIsEnabled(false);
}