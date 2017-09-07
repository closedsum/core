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

void ACsUI::AddWidget(const TCsWidgetType &WidgetType) {}

UCsUserWidget* ACsUI::GetWidget(const TCsWidgetType &WidgetType) { return nullptr; }

UCsUserWidget* ACsUI::GetActiveWidget(const TCsWidgetType &WidgetType) 
{ 
	const int32 Count = ActiveWidgets.Num();

	for (int32 I = 0; I < Count; I++)
	{
		if (ActiveWidgets[I]->Type == WidgetType)
			return ActiveWidgets[I];
	}
	return nullptr;
}

bool ACsUI::HasWidgetInitialized(const TCsWidgetType &WidgetType) { return true; }

void ACsUI::Open(const TCsWidgetType &WidgetType){}
void ACsUI::Close(const TCsWidgetType &WidgetType){}