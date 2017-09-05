// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/CsUI.h"
#include "CsCore.h"
#include "UI/CsUserWidget.h"

ACsUI::ACsUI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ACsUI::Destroyed()
{
	Super::Destroyed();

	const int32 Count = Widgets.Num();

	for (int32 I = Count - 1; I >= 0; I--)
	{
		UCsUserWidget* Widget = Widgets[I];

		if (Widget)
		{
			Widget->RemoveFromViewport();
			Widget->MarkPendingKill();
		}
		Widgets.RemoveAt(I);
	}

	WidgetActors.Reset();
}

void ACsUI::OnUpdate(const float &DeltaSeconds)
{
}

void ACsUI::AddWidget(const TCsWidgetType &WidgetType, const bool &Enabled, const ESlateVisibility &Visiblity) {}
UCsUserWidget* ACsUI::GetWidget(const TCsWidgetType &WidgetType) { return nullptr; }
UCsUserWidget* ACsUI::GetActiveWidget(const TCsWidgetType &WidgetType) { return nullptr; }