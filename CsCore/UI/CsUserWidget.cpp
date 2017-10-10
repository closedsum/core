// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/CsUserWidget.h"
#include "CsCore.h"

UCsUserWidget::UCsUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsUserWidget::Init()
{
	HasInitFinished = true;
}

void UCsUserWidget::OnPostProcessInput(const float &DeltaTime) {}
void UCsUserWidget::OnLastTick(const float &DeltaSeconds){}

void UCsUserWidget::SetFocus(const ECsWidgetFocus &InFocus)
{
	CS_SET_BLUEPRINT_BITFLAG(Focus, InFocus);
}

void UCsUserWidget::SetFocus(const int32 &InFocus)
{
	Focus = InFocus;
}

void UCsUserWidget::Show()
{
	SetIsEnabled(true);
	SetVisibility(ESlateVisibility::Visible);
	SetFocus(ECS_WIDGET_FOCUS_ALL);
}

void UCsUserWidget::Hide()
{
	SetFocus(ECS_WIDGET_FOCUS_NONE);
	SetVisibility(ESlateVisibility::Hidden);
	SetIsEnabled(false);
}

UCsUserWidget* UCsUserWidget::GetChildWidget(const TCsWidgetType &WidgetType)
{
	TArray<UCsUserWidget*>* Widgets = ChildWidgetsMap.Find(WidgetType);

	return (*Widgets)[CS_FIRST];
}

UCsUserWidget* UCsUserWidget::GetActiveChildWidget(const TCsWidgetType &WidgetType)
{
	TArray<UCsUserWidget*>* Widgets = ActiveChildWidgetsMap.Find(WidgetType);

	if (!Widgets)
		return nullptr;
	if (Widgets->Num() == CS_EMPTY)
		return nullptr;
	return (*Widgets)[CS_FIRST];
}

void UCsUserWidget::SetChildFocus(const TCsWidgetType &WidgetType, const int32 &InFocus)
{
	if (UCsUserWidget* Widget = GetActiveChildWidget(WidgetType))
	{
		Widget->SetFocus(Focus);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsUserWidget::SetChildFocus(%s): Widget: %s is NOT Active."), *GetName(), *((*WidgetTypeToString)(WidgetType)));
	}
}

void UCsUserWidget::OpenChild(const TCsWidgetType &WidgetType)
{
	if (UCsUserWidget* Widget = GetActiveChildWidget(WidgetType))
	{
		UE_LOG(LogCs, Warning, TEXT("UCsUserWidget::OpenChild: Attempting to open widget: %s but it is already open."), *((*WidgetTypeToString)(WidgetType)));
		return;
	}

	UCsUserWidget* Widget = GetChildWidget(WidgetType);

	ActiveChildWidgets.Add(Widget);

	if (TArray<UCsUserWidget*>* Widgets = ActiveChildWidgetsMap.Find(WidgetType))
	{
		Widgets->Add(Widget);
	}
	else
	{
		TArray<UCsUserWidget*> Array;
		Array.Add(Widget);
		ActiveChildWidgetsMap.Add(WidgetType, Array);
	}

	Widget->Show();
#if WITH_EDITOR
	OnOpenChild_ScriptEvent.Broadcast((uint8)WidgetType);
#endif // #if WITH_EDITOR
	OnOpenChild_Event.Broadcast(WidgetType);
}

bool UCsUserWidget::IsChildOpened(const TCsWidgetType &WidgetType) { return GetActiveChildWidget(WidgetType) != nullptr;  }

void UCsUserWidget::CloseChild(const TCsWidgetType &WidgetType)
{
	UCsUserWidget* Widget = GetActiveChildWidget(WidgetType);

	if (!Widget)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsUserWidget::CloseChild: Attempting to close menu: %s but it is NOT open."), *((*WidgetTypeToString)(WidgetType)));
		return;
	}

	const int32 Count = ActiveChildWidgets.Num();

	for (int32 I = Count - 1; I >= 0; I--)
	{
		if (ActiveChildWidgets[I] == Widget)
		{
			ActiveChildWidgets.RemoveAt(I);
			break;
		}
	}

	if (TArray<UCsUserWidget*>* Widgets = ActiveChildWidgetsMap.Find(WidgetType))
	{
		const int32 WidgetCount = Widgets->Num();

		for (int32 I = WidgetCount - 1; I >= 0; I--)
		{
			if ((*Widgets)[I] == Widget)
			{
				Widgets->RemoveAt(I);
				break;
			}
		}
	}

	Widget->Hide();
#if WITH_EDITOR
	OnCloseChild_ScriptEvent.Broadcast((uint8)WidgetType);
#endif // #if WITH_EDITOR
	OnCloseChild_Event.Broadcast(WidgetType);
}

void UCsUserWidget::CloseAllChildrenExcept(const TCsWidgetType &WidgetType)
{
	const int32 Count = ActiveChildWidgets.Num();

	for (int32 I = Count - 1; I >= 0; I--)
	{
		UCsUserWidget* Widget		   = ActiveChildWidgets[I];
		const TCsWidgetType ActiveType = Widget->Type;

		if (WidgetType == ActiveType)
			continue;

		Widget->Hide();

#if WITH_EDITOR
		OnCloseChild_ScriptEvent.Broadcast((uint8)ActiveType);
#endif // #if WITH_EDITOR
		OnCloseChild_Event.Broadcast(ActiveType);

		ActiveChildWidgets.RemoveAt(I);
	}

	const int32 TypeCount = ChildWidgetTypes.Num();

	for (int32 I = 0; I < TypeCount; I++)
	{
		const TCsWidgetType ActiveType = ChildWidgetTypes[I];

		if (WidgetType == ActiveType)
			continue;

		if (TArray<UCsUserWidget*>* Widgets = ActiveChildWidgetsMap.Find(ActiveType))
			Widgets->Reset();
	}
}

bool UCsUserWidget::IsChildClosed(const TCsWidgetType &WidgetType) { return GetActiveChildWidget(WidgetType) == nullptr; }

// Routines
#pragma region

/*static*/ void UCsUserWidget::AddRoutine(UObject* InWidget, struct FCsRoutine* Routine, const uint8 &InType)
{
	Cast<UCsUserWidget>(InWidget)->AddRoutine_Internal(Routine, InType);
}

bool UCsUserWidget::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType)
{
	return false;
}

/*static*/ void UCsUserWidget::RemoveRoutine(UObject* InWidget, struct FCsRoutine* Routine, const uint8 &InType)
{
	Cast<UCsUserWidget>(InWidget)->RemoveRoutine_Internal(Routine, InType);
}

bool UCsUserWidget::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType)
{
	return false;
}

#pragma endregion Routines

bool UCsUserWidget::ProcessGameEvent(const TCsGameEvent &GameEvent) { return false; }