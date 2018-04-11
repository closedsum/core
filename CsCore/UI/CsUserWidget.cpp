// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/CsUserWidget.h"
#include "CsCore.h"

// Managers
#include "Managers/Inventory/CsManager_Inventory.h"
// UI
#include "UI/CsUI.h"
// Player
#include "Player/CsPlayerController.h"
#include "Player/CsPlayerStateBase.h"

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

void UCsUserWidget::Init(){}

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

ACsPlayerController* UCsUserWidget::GetMyController()
{
	ACsUI* HUD = GetMyOwner<ACsUI>();
	return HUD ? HUD->GetMyOwner<ACsPlayerController>() : nullptr;
}

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

	// Open
#pragma region

bool UCsUserWidget::OpenChild(const TCsWidgetType &WidgetType)
{
	if (UCsUserWidget* Widget = GetActiveChildWidget(WidgetType))
	{
		UE_LOG(LogCs, Warning, TEXT("UCsUserWidget::OpenChild: Attempting to open widget: %s but it is already open."), *((*WidgetTypeToString)(WidgetType)));
		return false;
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

	// Apply Rules 
	if (ACsPlayerController* Controller = GetMyController())
	{
		// InputActionMapRules
		{
			if (FCsInputActionMapRule* Rule = OpenChildActionMapRules.Find(WidgetType))
			{
				Controller->ClearCurrentInputActionMap(Rule->Clear);
				Controller->SetCurrentInputActionMap(Rule->Set);
			}
		}
		// ShowMouseCursorRules
		{
			if (bool* Rule = OpenChildShowMouseCursorRules.Find(WidgetType))
			{
				Controller->bShowMouseCursor = *Rule;
			}
		}
	}

	Widget->Show();
#if WITH_EDITOR
	OnOpenChild_ScriptEvent.Broadcast((uint8)WidgetType);
#endif // #if WITH_EDITOR
	OnOpenChild_Event.Broadcast(WidgetType);
	return true;
}

bool UCsUserWidget::OpenChild_Script(const uint8 &WidgetType) { return OpenChild((TCsWidgetType)WidgetType); }

#pragma endregion Open

	// Close
#pragma region

bool UCsUserWidget::IsChildOpened(const TCsWidgetType &WidgetType) { return GetActiveChildWidget(WidgetType) != nullptr; }
bool UCsUserWidget::IsChildOpened_Script(const uint8 &WidgetType) { return IsChildOpened((TCsWidgetType)WidgetType); }

bool UCsUserWidget::CloseChild(const TCsWidgetType &WidgetType)
{
	UCsUserWidget* Widget = GetActiveChildWidget(WidgetType);

	if (!Widget)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsUserWidget::CloseChild: Attempting to close menu: %s but it is NOT open."), *((*WidgetTypeToString)(WidgetType)));
		return false;
	}

	const int32 Count = ActiveChildWidgets.Num();

	for (int32 I = Count - 1; I >= 0; --I)
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

		for (int32 I = WidgetCount - 1; I >= 0; --I)
		{
			if ((*Widgets)[I] == Widget)
			{
				Widgets->RemoveAt(I);
				break;
			}
		}
	}

	if (ActiveChildWidgets.Num() == CS_EMPTY)
	{
		if (ACsPlayerController* MyController = GetMyController())
			SetUserFocus(MyController);
	}

	// Apply Rules 
	if (ACsPlayerController* Controller = GetMyController())
	{
		// InputActionMapRules
		{
			// First Apply Close
			if (FCsInputActionMapRule* Rule = CloseChildActionMapRules.Find(WidgetType))
			{
				Controller->ClearCurrentInputActionMap(Rule->Clear);
				Controller->SetCurrentInputActionMap(Rule->Set);
			}
			// ReApply Open for any Widgets that are still open
			TArray<TCsWidgetType> Keys;
			ActiveChildWidgetsMap.GetKeys(Keys);

			const int32 KeyCount = Keys.Num();

			for (int32 I = 0; I < KeyCount; ++I)
			{
				const TCsWidgetType& Key = Keys[I];

				if (Key == WidgetType)
					continue;

				if (TArray<UCsUserWidget*>* Widgets = ActiveChildWidgetsMap.Find(Key))
				{
					if (Widgets->Num() == CS_EMPTY)
						continue;

					if (FCsInputActionMapRule* Rule = OpenChildActionMapRules.Find(Key))
					{
						Controller->ClearCurrentInputActionMap(Rule->Clear);
						Controller->SetCurrentInputActionMap(Rule->Set);
					}
				}
			}
		}
		// ShowMouseCursorRules
		{
			// First Apply Close
			if (bool* Rule = CloseChildShowMouseCursorRules.Find(WidgetType))
			{
				Controller->bShowMouseCursor = *Rule;
			}
			// ReApply Open for any Widgets that are still open
			TArray<TCsWidgetType> Keys;
			ActiveChildWidgetsMap.GetKeys(Keys);

			const int32 KeyCount = Keys.Num();

			for (int32 I = 0; I < KeyCount; ++I)
			{
				const TCsWidgetType& Key = Keys[I];

				if (Key == WidgetType)
					continue;

				if (TArray<UCsUserWidget*>* Widgets = ActiveChildWidgetsMap.Find(Key))
				{
					if (Widgets->Num() == CS_EMPTY)
						continue;

					if (bool* Rule = OpenChildShowMouseCursorRules.Find(Key))
					{
						Controller->bShowMouseCursor = *Rule;
					}
				}
			}
		}
	}

	Widget->Hide();
#if WITH_EDITOR
	OnCloseChild_ScriptEvent.Broadcast((uint8)WidgetType);
#endif // #if WITH_EDITOR
	OnCloseChild_Event.Broadcast(WidgetType);
	return true;
}

bool UCsUserWidget::CloseChild_Script(const uint8 &WidgetType) { return CloseChild((TCsWidgetType)WidgetType); }

void UCsUserWidget::CloseAllChildrenExcept(const TCsWidgetType &WidgetType)
{
	const int32 Count = ActiveChildWidgets.Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
		UCsUserWidget* Widget		    = ActiveChildWidgets[I];
		const TCsWidgetType& ActiveType = Widget->Type;

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
		const TCsWidgetType& ActiveType = ChildWidgetTypes[I];

		if (WidgetType == ActiveType)
			continue;

		if (TArray<UCsUserWidget*>* Widgets = ActiveChildWidgetsMap.Find(ActiveType))
			Widgets->Reset();
	}
}

void UCsUserWidget::CloseAllChildrenExcept_Script(const uint8 &WidgetType) { CloseAllChildrenExcept((TCsWidgetType)WidgetType); }

bool UCsUserWidget::IsChildClosed(const TCsWidgetType &WidgetType) { return GetActiveChildWidget(WidgetType) == nullptr; }
bool UCsUserWidget::IsChildClosed_Script(const uint8 &WidgetType) { return IsChildClosed((TCsWidgetType)WidgetType); }

#pragma endregion Close

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

// Raw Inputs
#pragma region

bool UCsUserWidget::ProcessInputFrame(FCsInputFrame &InputFrame) { return false;  }

bool UCsUserWidget::ChildWidgets_ProcessInputFrame(FCsInputFrame &InputFrame)
{
	const int32 Count = ChildWidgetTypes.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (IsChildOpened(ChildWidgetTypes[I]))
		{
			UCsUserWidget* Widget = GetActiveChildWidget(ChildWidgetTypes[I]);

			if (Widget->ProcessInputFrame(InputFrame))
				return true;
		}
	}
	return false;
}

#pragma endregion Raw Inputs

// Game Event
#pragma region

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

#pragma endregion Game Event

// Inventory
#pragma region

ACsManager_Inventory* UCsUserWidget::GetMyManager_Inventory()
{
	if (ACsPlayerController* Controller = GetMyController())
	{
		ACsPlayerStateBase* PlayerStateBase = Cast<ACsPlayerStateBase>(Controller->PlayerState);
		return PlayerStateBase->Manager_Inventory;
	}
	return nullptr;
}

#pragma endregion Inventory