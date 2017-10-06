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