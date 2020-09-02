// Copyright 2017 Respawn Entertainment, Inc. All rights reserved.

#include "Components/CsWidgetComponent.h"
#include "CsUI.h"

UCsWidgetComponent::UCsWidgetComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UUserWidget* UCsWidgetComponent::GetWidget()
{
	return Widget;
}

void UCsWidgetComponent::Show()
{
	Activate();
	SetHiddenInGame(false);
	SetVisibility(true);

	if (Widget)
	{
		Widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Widget->SetIsEnabled(true);
	}
}

void UCsWidgetComponent::Hide()
{
	if (Widget)
	{
		Widget->SetIsEnabled(false);
		Widget->SetVisibility(ESlateVisibility::Collapsed);
	}
	SetVisibility(false);
	SetHiddenInGame(true);
	Deactivate();
}


void UCsWidgetComponent::Enable()
{
	if (Widget)
		Widget->SetIsEnabled(true);
}

void UCsWidgetComponent::Disable()
{
	if (Widget)
		Widget->SetIsEnabled(false);
}