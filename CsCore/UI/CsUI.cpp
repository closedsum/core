// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
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

	for (int32 I = Count - 1; I >= 0; --I)
	{
		UCsUserWidget* Widget = Widgets[I];

		if (Widget)
		{
			Widget->RemoveFromViewport();
			Widget->MarkPendingKill();
		}
		Widgets.RemoveAt(I);
	}

	WidgetsMap.Reset();
	ActiveWidgets.Reset();
	ActiveWidgetsMap.Reset();
	WidgetActors.Reset();
	ActiveWidgetActors.Reset();
}

void ACsUI::OnUpdate(const float &DeltaSeconds){}
void ACsUI::OnPostProcessInput(const float &DeltaTime){}
void ACsUI::OnLastTick(const float &DeltaSeconds){}

AActor* ACsUI::GetMyOwner() { return MyOwner.IsValid() ? MyOwner.Get() : nullptr; }

void ACsUI::AddWidget(const TCsWidgetType &WidgetType) {}
void ACsUI::AddWidget_Script(const uint8 &WidgetType) { AddWidget((TCsWidgetType)WidgetType); }

// Get
#pragma region

UCsUserWidget* ACsUI::GetWidget(const TCsWidgetType &WidgetType)
{ 
	TArray<UCsUserWidget*>* Array = WidgetsMap.Find(WidgetType);

	return (*Array)[CS_FIRST];
}

UCsUserWidget* ACsUI::GetWidget_Script(const uint8 &WidgetType) { return GetWidget((TCsWidgetType)WidgetType); }

UCsUserWidget* ACsUI::GetActiveWidget(const TCsWidgetType &WidgetType) 
{ 
	TArray<UCsUserWidget*>* Array = ActiveWidgetsMap.Find(WidgetType);

	if (!Array)
		return nullptr;
	if (Array->Num() == CS_EMPTY)
		return nullptr;
	return (*Array)[CS_FIRST];
}

UCsUserWidget* ACsUI::GetActiveWidget_Script(const uint8 &WidgetType) { return GetActiveWidget((TCsWidgetType)WidgetType); }

#pragma endregion Get

bool ACsUI::HasWidgetInitialized(const TCsWidgetType &WidgetType) { return true; }

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

void ACsUI::SetFocusAll(const TCsWidgetType &WidgetType) { SetFocus(WidgetType, ECS_WIDGET_FOCUS_ALL); }
void ACsUI::SetFocusAll_Script(const uint8 &WidgetType) { SetFocusAll((TCsWidgetType)WidgetType); }

// Open / Close
#pragma region

void ACsUI::Open(const TCsWidgetType &WidgetType)
{
	if (UCsUserWidget* Widget = GetActiveWidget(WidgetType))
	{
		UE_LOG(LogCs, Warning, TEXT("ACsUI::Open: Attempting to open menu: %s but it is already open."), *((*WidgetTypeToString)(WidgetType)));
		return;
	}

	UCsUserWidget* Widget = GetWidget(WidgetType);

	ActiveWidgets.Add(Widget);

	if (TArray<UCsUserWidget*>* WidgetArray = ActiveWidgetsMap.Find(WidgetType))
	{
		WidgetArray->Add(Widget);
	}
	else
	{
		TArray<UCsUserWidget*> Array;
		Array.Add(Widget);
		ActiveWidgetsMap.Add(WidgetType, Array);
	}

	Widget->Show();
#if WITH_EDITOR
	OnOpen_ScriptEvent.Broadcast((uint8)WidgetType);
#endif // #if WITH_EDITOR
	OnOpen_Event.Broadcast(WidgetType);
}

bool ACsUI::IsOpened(const TCsWidgetType &WidgetType) { return GetActiveWidget(WidgetType) != nullptr; }
bool ACsUI::IsOpened_Script(const uint8 &WidgetType) { return IsOpened((TCsWidgetType)WidgetType); }

bool ACsUI::IsOpenedAndFocused(const TCsWidgetType &WidgetType)
{
	if (UCsUserWidget* Widget = GetActiveWidget(WidgetType))
		return Widget->Focus > ECS_WIDGET_FOCUS_NONE;
	return false;
}

bool ACsUI::IsOpenedAndFocused_Script(const uint8 &WidgetType) { return IsOpenedAndFocused((TCsWidgetType)WidgetType); }

void ACsUI::Close(const TCsWidgetType &WidgetType)
{
	// Close All
	if (WidgetType == WidgetType_MAX)
	{
		int32 Count = ActiveWidgets.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			UCsUserWidget* Widget = ActiveWidgets[I];

			Widget->Hide();
#if WITH_EDITOR
			OnClose_ScriptEvent.Broadcast((uint8)Widget->Type);
#endif // #if WITH_EDITOR
			OnClose_Event.Broadcast(Widget->Type);
		}
		ActiveWidgets.Reset();

		Count = WidgetTypes.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (TArray<UCsUserWidget*>* WidgetArray = ActiveWidgetsMap.Find(WidgetTypes[I]))
			{
				WidgetArray->Reset();
			}
		}
		return;
	}

	UCsUserWidget* Widget = GetActiveWidget(WidgetType);

	if (!Widget)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsUI::Close: Attempting to close menu: %s but it is NOT open."), *((*WidgetTypeToString)(WidgetType)));
		return;
	}

	const int32 Count = ActiveWidgets.Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
		if (ActiveWidgets[I] == Widget)
		{
			ActiveWidgets.RemoveAt(I);
			break;
		}
	}

	if (TArray<UCsUserWidget*>* WidgetArray = ActiveWidgetsMap.Find(WidgetType))
	{
		const int32 WidgetCount = WidgetArray->Num();

		for (int32 I = WidgetCount - 1; I >= 0; --I)
		{
			if ((*WidgetArray)[I] == Widget)
			{
				WidgetArray->RemoveAt(I);
				break;
			}
		}
	}

	Widget->Hide();
#if WITH_EDITOR
	OnClose_ScriptEvent.Broadcast((uint8)WidgetType);
#endif // #if WITH_EDITOR
	OnClose_Event.Broadcast(WidgetType);
}

void ACsUI::Close_Script(const uint8 &WidgetType) { Close((TCsWidgetType)WidgetType); }
void ACsUI::CloseAll() { Close(WidgetType_MAX); }

bool ACsUI::IsClosed(const TCsWidgetType &WidgetType) { return GetActiveWidget(WidgetType) == nullptr; }
bool ACsUI::IsClosed_Script(const uint8 &WidgetType) { return IsClosed((TCsWidgetType)WidgetType); }

#pragma endregion Open / Close

// Raw Inputs
#pragma region

bool ACsUI::ProcessInputFrame(FCsInputFrame &InputFrame) { return false; }

#pragma endregion Raw Inputs

// Game Event
#pragma region

bool ACsUI::ProcessGameEvent(const TCsGameEvent &GameEvent) { return false; }

#pragma endregion Game Event