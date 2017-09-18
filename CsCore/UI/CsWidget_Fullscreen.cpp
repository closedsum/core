// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/CsWidget_Fullscreen.h"
#include "CsCore.h"
#include "CsCommon.h"
#include "Coroutine/CsCoroutineScheduler.h"

UCsWidget_Fullscreen::UCsWidget_Fullscreen(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsWidget_Fullscreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!HasInitFinished)
		Init();

	Fullscreen.OnNativeTick(InDeltaTime);

#if WITH_EDITOR
	OnNativeTick_ScriptEvent.Broadcast(MyGeometry, InDeltaTime);
#endif // #if WITH_EDITOR
}

void UCsWidget_Fullscreen::Init()
{
	Fullscreen.Set(Fullscreen_Image);

	HasInitFinished = true;
}

// Routines
#pragma region

bool UCsWidget_Fullscreen::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType)
{
	if (Super::AddRoutine_Internal(Routine, InType))
		return true;

	const TCsWidgetFullscreenRoutine RoutineType = (TCsWidgetFullscreenRoutine)InType;

	// FadeOut_Internal
	if (RoutineType == ECsWidgetFullscreenRoutine::FadeOut_Internal)
	{
		FadeOut_Internal_Routine = Routine;
		return true;
	}
	// FadeIn_Internal
	if (RoutineType == ECsWidgetFullscreenRoutine::FadeIn_Internal)
	{
		FadeIn_Internal_Routine = Routine;
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

	// FadeOut_Internal
	if (RoutineType == ECsWidgetFullscreenRoutine::FadeOut_Internal)
	{
		check(FadeOut_Internal_Routine == Routine);
		FadeOut_Internal_Routine = nullptr;
		return true;
	}
	// FadeIn_Internal
	if (RoutineType == ECsWidgetFullscreenRoutine::FadeIn_Internal)
	{
		check(FadeIn_Internal_Routine == Routine);
		FadeIn_Internal_Routine = nullptr;
		return true;
	}
	checkf(0, TEXT("UCsWidget_Fullscreen::RemoveRoutine_Internal: Adding a Routine of unknown Type"));
	return false;
}

#pragma endregion Routines

void UCsWidget_Fullscreen::FadeOut(const TEnumAsByte<ECsEasingType::Type> &EasingType, const float &Start, const float &End, const float &Time, const FLinearColor &Color)
{
	CsCoroutine Function		  = &UCsWidget_Fullscreen::Fade_Internal;
	CsCoroutineStopCondition Stop = &UCsCommon::CoroutineStopCondition_CheckObject;
	CsAddRoutine Add			  = &UCsUserWidget::AddRoutine;
	CsRemoveRoutine Remove		  = &UCsUserWidget::RemoveRoutine;
	const uint8 RoutineType		  = (uint8)ECsWidgetFullscreenRoutine::FadeOut_Internal;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsRoutine* R					 = Scheduler->Allocate(Function, Stop, this, Add, Remove, RoutineType, true, false);

	R->ints[0] = (int32)EasingType;
	R->floats[0] = Start;
	R->floats[1] = End;
	R->floats[2] = Time;
	R->colors[0] = Color;

	Scheduler->StartRoutine(R);
}

void UCsWidget_Fullscreen::FadeIn(const TEnumAsByte<ECsEasingType::Type> &EasingType, const float &Start, const float &End, const float &Time, const FLinearColor &Color)
{
	CsCoroutine Function		  = &UCsWidget_Fullscreen::Fade_Internal;
	CsCoroutineStopCondition Stop = &UCsCommon::CoroutineStopCondition_CheckObject;
	CsAddRoutine Add			  = &UCsUserWidget::AddRoutine;
	CsRemoveRoutine Remove		  = &UCsUserWidget::RemoveRoutine;
	const uint8 RoutineType		  = (uint8)ECsWidgetFullscreenRoutine::FadeIn_Internal;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsRoutine* R					 = Scheduler->Allocate(Function, Stop, this, Add, Remove, RoutineType, true, false);

	R->ints[0] = (int32)EasingType;
	R->floats[0] = Start;
	R->floats[1] = End;
	R->floats[2] = Time;
	R->colors[0] = Color;

	Scheduler->StartRoutine(R);
}

CS_COROUTINE(UCsWidget_Fullscreen, Fade_Internal)
{
	UCsWidget_Fullscreen* wd = Cast<UCsWidget_Fullscreen>(r->GetRObject());
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w				 = wd->GetWorld();

	const float CurrentTime = w->TimeSeconds;
	const float StartTime   = r->startTime;
	const float MaxTime     = r->floats[2];

	const TEnumAsByte<ECsEasingType::Type> EasingType = (TEnumAsByte<ECsEasingType::Type>)r->ints[0];

	const float Start	 = r->floats[0];
	const float End		 = r->floats[1];
	const bool IsFadeOut = Start > End;
	const float Max		 = FMath::Max(Start, End);
	const float Min		 = FMath::Min(Start, End);
	const float Delta	 = Max - Min;

	const FLinearColor Color = r->colors[0];

	CS_COROUTINE_BEGIN(r);

	wd->Fullscreen.SetColorAndOpacity(Color);

	if (r->delay > 0)
		CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - StartTime > r->delay);

	do
	{
		{
			const float Percent = FMath::Clamp((CurrentTime - StartTime) / MaxTime, 0.0f, 1.0f);
			const float Time    = UCsCommon::Ease(EasingType, Percent, 0.0f, 1.0f, 1.0f);
			const float Alpha   = IsFadeOut ? 1.0f - (Min + Percent * Delta) : Min + Percent * Delta;

			wd->Fullscreen.SetOpacity(Alpha);
		}
		CS_COROUTINE_YIELD(r);
	} while (CurrentTime - StartTime <= MaxTime);

	wd->Fullscreen.SetOpacity(End);

	CS_COROUTINE_END(r);
}