// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/CsUserWidget.h"
#include "CsCore.h"

UCsUserWidget::UCsUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (HasNativeContructed)
		return;

	OnNativeConstruct();

	HasNativeContructed = true;
}

void UCsUserWidget::OnNativeConstruct(){}

void UCsUserWidget::Init()
{
	HasInitFinished = true;
}

void UCsUserWidget::OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime) {}

void UCsUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!HasInitFinished)
	{
		Init();

		HasInitFinished = true;
	}

	OnNativeTick(MyGeometry, InDeltaTime);

#if WITH_EDITOR
	OnNativeTick_ScriptEvent.Broadcast(MyGeometry, InDeltaTime);
#endif // #if WITH_EDITOR
}

void UCsUserWidget::OnPostProcessInput(const float &DeltaTime){}
void UCsUserWidget::OnUpdate(const float &DeltaSeconds){}
void UCsUserWidget::OnLastTick(const float &DeltaSeconds){}

void UCsUserWidget::SetMyOwner(AActor* InOwner) 
{ 
	MyOwner = InOwner; 
}

AActor* UCsUserWidget::GetMyOwner() { return MyOwner.IsValid() ? MyOwner.Get() : nullptr; }

void UCsUserWidget::SetFocus(const ECsWidgetFocus &InFocus)
{
	CS_SET_BLUEPRINT_BITFLAG(Focus, InFocus);
}

void UCsUserWidget::SetFocus(const int32 &InFocus)
{
	Focus = InFocus;
}

void UCsUserWidget::ClearFocus()
{
	Focus = ECS_WIDGET_FOCUS_NONE;
}

void UCsUserWidget::SetFocusAll()
{
	Focus = ECS_WIDGET_FOCUS_ALL;
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

// Get
#pragma region

UCsUserWidget* UCsUserWidget::GetChildWidget(const TCsWidgetType &WidgetType)
{
	TArray<UCsUserWidget*>* Widgets = ChildWidgetsMap.Find(WidgetType);

	return (*Widgets)[CS_FIRST];
}

UCsUserWidget* UCsUserWidget::GetChildWidget_Script(const uint8 &WidgetType){ return GetChildWidget((TCsWidgetType)WidgetType); }

UCsUserWidget* UCsUserWidget::GetActiveChildWidget(const TCsWidgetType &WidgetType)
{
	TArray<UCsUserWidget*>* Widgets = ActiveChildWidgetsMap.Find(WidgetType);

	if (!Widgets)
		return nullptr;
	if (Widgets->Num() == CS_EMPTY)
		return nullptr;
	return (*Widgets)[CS_FIRST];
}

UCsUserWidget* UCsUserWidget::GetActiveChildWidget_Script(const uint8 &WidgetType) { return GetActiveChildWidget((TCsWidgetType)WidgetType); }

#pragma endregion Get

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

// Open / Close Child
#pragma region

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

void UCsUserWidget::OpenChild_Script(const uint8 &WidgetType) { OpenChild((TCsWidgetType)WidgetType); }

bool UCsUserWidget::IsChildOpened(const TCsWidgetType &WidgetType) { return GetActiveChildWidget(WidgetType) != nullptr; }
bool UCsUserWidget::IsChildOpened_Script(const uint8 &WidgetType) { return IsChildOpened((TCsWidgetType)WidgetType); }

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

void UCsUserWidget::CloseChild_Script(const uint8 &WidgetType) { CloseChild((TCsWidgetType)WidgetType); }

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

	for (int32 I = 0; I < TypeCount; ++I)
	{
		const TCsWidgetType ActiveType = ChildWidgetTypes[I];

		if (WidgetType == ActiveType)
			continue;

		if (TArray<UCsUserWidget*>* Widgets = ActiveChildWidgetsMap.Find(ActiveType))
			Widgets->Reset();
	}
}

void UCsUserWidget::CloseAllChildrenExcept_Script(const uint8 &WidgetType) { CloseAllChildrenExcept((TCsWidgetType)WidgetType); }

bool UCsUserWidget::IsChildClosed(const TCsWidgetType &WidgetType) { return GetActiveChildWidget(WidgetType) == nullptr; }
bool UCsUserWidget::IsChildClosed_Script(const uint8 &WidgetType) { return IsChildClosed((TCsWidgetType)WidgetType); }

#pragma endregion Open / Close Child

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
bool UCsUserWidget::ProcessGameEvent_Script(const uint8 &GameEvent) { return ProcessGameEvent((TCsGameEvent)GameEvent); }

bool UCsUserWidget::ChildWidgets_ProcessGameEvent(const TCsGameEvent &GameEvent)
{
	const int32 Count = ChildWidgetTypes.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (IsChildOpened(ChildWidgetTypes[I]))
		{
			UCsUserWidget* Widget = GetActiveChildWidget(ChildWidgetTypes[I]);

			if (Widget->ProcessGameEvent(GameEvent))
				return true;
		}
	}
	return false;
}

bool UCsUserWidget::ChildWidgets_ProcessGameEvent_Script(const uint8 &GameEvent) { return ChildWidgets_ProcessGameEvent((TCsGameEvent)GameEvent); }