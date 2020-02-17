// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/CsWidget_Fullscreen.h"
#include "CsCore.h"

#include "Library/CsLibrary_Common.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Managers
#include "Managers/Time/CsManager_Time.h"

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
	const FECsUpdateGroup& Group = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(GetGameInstance());
	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&UCsWidget_Fullscreen::Fade_Internal);
	Payload->StartTime = UCsManager_Time::Get(GetGameInstance())->GetTime(Group);
	Payload->Owner.SetObject(this);

	Payload->SetValue_Int(CS_FIRST, (int32)EasingType);

	static const int32 START_INDEX = 0;
	Payload->SetValue_Float(START_INDEX, Start);

	static const int32 END_INDEX = 1;
	Payload->SetValue_Float(END_INDEX, End);

	static const int32 TIME_INDEX = 2;
	Payload->SetValue_Float(TIME_INDEX, Time);

	Payload->SetValue_Color(CS_FIRST, Color);

	Scheduler->Start(Payload);
}

void UCsWidget_Fullscreen::FadeIn(const ECsEasingType &EasingType, const float &Start, const float &End, const float &Time, const FLinearColor &Color)
{
	const FECsUpdateGroup& Group = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(GetGameInstance());
	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&UCsWidget_Fullscreen::Fade_Internal);
	Payload->StartTime = UCsManager_Time::Get(GetGameInstance())->GetTime(Group);
	Payload->Owner.SetObject(this);

	Payload->SetValue_Int(CS_FIRST, (int32)EasingType);

	static const int32 START_INDEX = 0;
	Payload->SetValue_Float(START_INDEX, Start);

	static const int32 END_INDEX = 1;
	Payload->SetValue_Float(END_INDEX, End);

	static const int32 TIME_INDEX = 2;
	Payload->SetValue_Float(TIME_INDEX, Time);

	Payload->SetValue_Color(CS_FIRST, Color);

	Scheduler->Start(Payload);
}

CS_COROUTINE(UCsWidget_Fullscreen, Fade_Internal)
{
	UCsWidget_Fullscreen* wd = r->GetOwnerAsObject<UCsWidget_Fullscreen>();
	UWorld* w				 = wd->GetWorld();

	const FCsTime& CurrentTime = UCsManager_Time::Get(wd->GetGameInstance())->GetTime(r->Group);
	const FCsTime& StartTime   = r->StartTime;

	static const int32 MAX_TIME_INDEX = 2;
	const float& MaxTime = r->GetValue_Float(MAX_TIME_INDEX);

	const ECsEasingType& EasingType = EMCsEasingType::Get().GetEnumAt(r->GetValue_Int(CS_FIRST));

	static const int32 START_INDEX = 0;
	const float& Start = r->GetValue_Float(START_INDEX);

	static const int32 END_INDEX = 1;
	const float& End = r->GetValue_Float(END_INDEX);

	const bool IsFadeOut = Start > End;
	const float Max		 = FMath::Max(Start, End);
	const float Min		 = FMath::Min(Start, End);
	const float Delta	 = Max - Min;

	const FLinearColor& Color = r->GetValue_Color(CS_FIRST);

	CS_COROUTINE_BEGIN(r);

	wd->Fullscreen.SetColorAndOpacity(Color);

	if (r->Delay > 0)
		CS_COROUTINE_WAIT_UNTIL(r, CurrentTime.Time - StartTime.Time > r->Delay);

	do
	{
		{
			const float Percent = FMath::Clamp((CurrentTime.Time - StartTime.Time) / MaxTime, 0.0f, 1.0f);
			const float Time    = UCsLibrary_Common::Ease(EasingType, Percent, 0.0f, 1.0f, 1.0f);
			const float Alpha   = IsFadeOut ? 1.0f - (Min + Percent * Delta) : Min + Percent * Delta;

			wd->Fullscreen.SetOpacity(Alpha);
		}
		CS_COROUTINE_YIELD(r);
	} while (CurrentTime.Time - StartTime.Time <= MaxTime);

	wd->Fullscreen.SetOpacity(End);

	CS_COROUTINE_END(r);
}