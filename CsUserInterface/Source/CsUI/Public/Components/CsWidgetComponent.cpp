// Copyright 2017-2023 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Components/CsWidgetComponent.h"
#include "CsUI.h"

// Library
#include "Library/CsLibrary_Valid.h"

UCsWidgetComponent::UCsWidgetComponent(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer)
{
	bWindowFocusable = false;
}

void UCsWidgetComponent::Show()
{
	Activate();
	SetComponentTickEnabled(true);
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
	SetComponentTickEnabled(false);
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

void UCsWidgetComponent::ConditionalSetWidgetChecked(const FString& Context, UClass* InWidgetClass)
{
	CS_IS_PTR_NULL_CHECKED(InWidgetClass)

	UUserWidget* W = GetWidget();

	// Setting a Widget with the SAME, Exit
	if (W &&
		W->GetClass() == InWidgetClass)
	{
		return;
	}

	UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), InWidgetClass);

	CS_IS_PTR_NULL_CHECKED(NewWidget)

	SetWidget(NewWidget);

	if (W)
	{
		W->MarkAsGarbage();
	}
}