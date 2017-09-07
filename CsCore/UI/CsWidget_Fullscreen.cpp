// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/CsWidget_Fullscreen.h"
#include "CsCore.h"

UCsWidget_Fullscreen::UCsWidget_Fullscreen(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsWidget_Fullscreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!HasInitFinished)
		Init();

#if WITH_EDITOR
	OnNativeTick_ScriptEvent.Broadcast(MyGeometry, InDeltaTime);
#endif // #if WITH_EDITOR
}

void UCsWidget_Fullscreen::Init()
{
	HasInitFinished = true;
}

// Routines
#pragma region

bool UCsWidget_Fullscreen::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType)
{
	if (Super::AddRoutine_Internal(Routine, InType))
		return true;

	const TCsWidgetFullscreenRoutine RoutineType = (TCsWidgetFullscreenRoutine)InType;

	// OnBoard_Internal
	if (RoutineType == ECsWidgetFullscreenRoutine::FadeOut_Internal)
	{
		FadeOut_Internal_Routine = Routine;
		return true;
	}
	checkf(0, TEXT("UCsWidget_Fullscreen::AddRoutine_Internal: Adding a Routine of unknown Type"));
	return false;
}


bool UCsWidget_Fullscreen::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType)
{
	if (Super::RemoveRoutine_Internal(Routine, InType))
		return true;

	const TCsWidgetFullscreenRoutine RoutineType = (TCsWidgetFullscreenRoutine)InType;

	// OnBoard_Internal
	if (RoutineType == ECsWidgetFullscreenRoutine::FadeOut_Internal)
	{
		check(FadeOut_Internal_Routine == Routine);
		FadeOut_Internal_Routine = nullptr;
		return true;
	}
	checkf(0, TEXT("UCsWidget_Fullscreen::RemoveRoutine_Internal: Adding a Routine of unknown Type"));
	return false;
}

#pragma endregion Routines
/*
void UCsWidget_Fullscreen::FadeOut(const TEnumAsByte<ECsEasingType::Type> &EasingType, const float &Start, const float &End, const float &Time, const FLinearColor &Color)
{
	CsCoroutine Function		  = &UCsWidget_Fullscreen::FadeOut_Internal;
	CsCoroutineStopCondition Stop = &UCsCommon::CoroutineStopCondition_CheckActor;
	CsAddRoutine Add			  = &UCsUserWidget::AddRoutine;
	CsRemoveRoutine Remove		  = &UCsUserWidget::RemoveRoutine;
	const uint8 Type			  = (uint8)ECsWidgetFullscreenRoutine::FadeOut_Internal;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsRoutine* R					 = Scheduler->Allocate(Function, Stop, this, Add, Remove, Type, true, false);

	R->ints[0] = (int32)EasingType;
	R->floats[0] = Start;
	R->floats[1] = End;
	R->floats[2] = Time;
	R->colors[0] = Color;

	Scheduler->StartRoutine(R);
}
*/
CS_COROUTINE(UCsWidget_Fullscreen, FadeOut_Internal)
{
	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_END(r);
}