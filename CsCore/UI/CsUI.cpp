// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/CsUI.h"
#include "CsCore.h"
#include "UI/CsUserWidget.h"

ACsUI::ACsUI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	WidgetTypeToString = nullptr;
	StringToWidgetType = nullptr;
	WidgetActorTypeToString = nullptr;
	StringToWidgetActorType = nullptr;
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

void ACsUI::OnUpdate(const float &DeltaSeconds){}
void ACsUI::OnPostProcessInput(const float &DeltaTime){}
void ACsUI::OnLastTick(const float &DeltaSeconds){}

void ACsUI::AddWidget(const TCsWidgetType &WidgetType) {}

UCsUserWidget* ACsUI::GetWidget(const TCsWidgetType &WidgetType)
{ 
	const int32 Count = Widgets.Num();

	for (int32 I = 0; I < Count; I++)
	{
		if (Widgets[I]->Type == WidgetType)
			return Widgets[I];
	}
	return nullptr;
}

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
bool ACsUI::IsOpened(const TCsWidgetType &WidgetType) { return GetActiveWidget(WidgetType) != nullptr; }
bool ACsUI::IsOpenedAndFocused(const TCsWidgetType &WidgetType)
{
	if (UCsUserWidget* Widget = GetActiveWidget(WidgetType))
		return Widget->Focus > ECS_WIDGET_FOCUS_NONE;
	return false;
}

void ACsUI::SetFocus(const TCsWidgetType &WidgetType, const int32& Focus)
{
	if (UCsUserWidget* Widget = GetActiveWidget(WidgetType))
	{
		Widget->Focus = Focus;
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsUI::SetFocus(%s): Widget: %s is NOT Active."), *GetName(), *((*WidgetTypeToString)(WidgetType)));
	}
}

void ACsUI::SetFocus(const TCsWidgetType &WidgetType, const ECsWidgetFocus& Focus)
{
	if (UCsUserWidget* Widget = GetActiveWidget(WidgetType))
	{
		CS_SET_BLUEPRINT_BITFLAG(Widget->Focus, Focus);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsUI::SetFocus(%s): Widget: %s is NOT Active."), *GetName(), *((*WidgetTypeToString)(WidgetType)));
	}
}

void ACsUI::Close(const TCsWidgetType &WidgetType){}
bool ACsUI::IsClosed(const TCsWidgetType &WidgetType) { return GetActiveWidget(WidgetType) == nullptr; }

bool ACsUI::ProcessGameEvent(const TCsGameEvent &GameEvent) { return false; }