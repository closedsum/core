// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/CsWidget_Fullscreen.h"
#include "CsCore.h"
#include "Common/CsCommon.h"
#include "Coroutine/CsCoroutineScheduler.h"

UCsWidget_Fullscreen::UCsWidget_Fullscreen(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Type = EMCsWidgetType::Get().GetSafeEnumAt(0);
}

void UCsWidget_Fullscreen::OnNativeTick(const FGeometry& MyGeometry, const float& InDeltaTime)
{
	Super::OnNativeTick(MyGeometry, InDeltaTime);

	Fullscreen.OnNativeTick(InDeltaTime);
}

void UCsWidget_Fullscreen::Init()
{
	Fullscreen.Set(Fullscreen_Image);
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

void UCsWidget_Fullscreen::FadeOut(const ECsEasingType &EasingType, const float &Start, const float &End, const float &Time, const FLinearColor &Color)
{
	const ECsCoroutineSchedule& Schedule = NCsCoroutineSchedule::Ref::Tick;

	CsCoroutine Function		  = &UCsWidget_Fullscreen::Fade_Internal;
	CsCoroutineStopCondition Stop = &UCsCommon::CoroutineStopCondition_CheckObject;
	CsAddRoutine Add			  = &UCsUserWidget::AddRoutine;
	CsRemoveRoutine Remove		  = &UCsUserWidget::RemoveRoutine;
	const uint8 RoutineType		  = (uint8)ECsWidgetFullscreenRoutine::FadeOut_Internal;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsRoutine* R					 = Scheduler->Allocate(Schedule, Function, Stop, this, Add, Remove, RoutineType, true, false);

	R->ints[0] = (int32)EasingType;
	R->floats[0] = Start;
	R->floats[1] = End;
	R->floats[2] = Time;
	R->colors[0] = Color;

	Scheduler->StartRoutine(Schedule, R);
}

void UCsWidget_Fullscreen::FadeIn(const ECsEasingType &EasingType, const float &Start, const float &End, const float &Time, const FLinearColor &Color)
{
	const ECsCoroutineSchedule& Schedule = NCsCoroutineSchedule::Ref::Tick;

	CsCoroutine Function		  = &UCsWidget_Fullscreen::Fade_Internal;
	CsCoroutineStopCondition Stop = &UCsCommon::CoroutineStopCondition_CheckObject;
	CsAddRoutine Add			  = &UCsUserWidget::AddRoutine;
	CsRemoveRoutine Remove		  = &UCsUserWidget::RemoveRoutine;
	const uint8 RoutineType		  = (uint8)ECsWidgetFullscreenRoutine::FadeIn_Internal;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsRoutine* R					 = Scheduler->Allocate(Schedule, Function, Stop, this, Add, Remove, RoutineType, true, false);

	R->ints[0] = (int32)EasingType;
	R->floats[0] = Start;
	R->floats[1] = End;
	R->floats[2] = Time;
	R->colors[0] = Color;

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(UCsWidget_Fullscreen, Fade_Internal)
{
	UCsWidget_Fullscreen* wd = Cast<UCsWidget_Fullscreen>(r->GetRObject());
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();
	UWorld* w				 = wd->GetWorld();

	const float CurrentTime = w->GetTimeSeconds();
	const float StartTime   = r->startTime;
	const float MaxTime     = r->floats[2];

	const ECsEasingType& EasingType = EMCsEasingType::Get().GetEnumAt(r->ints[0]);

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