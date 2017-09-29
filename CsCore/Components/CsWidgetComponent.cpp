// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Components/CsWidgetComponent.h"
#include "CsCore.h"
#include "Types/CsTypes.h"
#include "UI/CsUserWidget.h"

UCsWidgetComponent::UCsWidgetComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UCsUserWidget* UCsWidgetComponent::GetWidget()
{
	return Cast<UCsUserWidget>(Widget);
}

void UCsWidgetComponent::SetInfo(const FCsWidgetActorInfo &Info)
{
	SetDrawSize(Info.DrawSize);
	SetRelativeTransform(Info.Transform);
}

void UCsWidgetComponent::Show()
{
	Widget->SetIsEnabled(true);
	Widget->SetVisibility(ESlateVisibility::Visible);
	Activate();
	SetComponentTickEnabled(true);
	SetHiddenInGame(false);
	SetVisibility(true);
}

void UCsWidgetComponent::Hide()
{
	Widget->SetIsEnabled(false);
	Widget->SetVisibility(ESlateVisibility::Hidden);
	SetVisibility(false);
	SetHiddenInGame(true);
	SetComponentTickEnabled(false);
	Deactivate();
}