// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/CsGameState.h"
#include "CsCore.h"
#include "Coroutine/CsCoroutineScheduler.h"
#include "CsLastTickActor.h"
// Managers
#include "Managers/CsManager_Loading.h"
#include "Managers/CsManager_Input.h"

#include "Game/CsGameInstance.h"
#include "Javascript/CsJavascriptEntryPoint.h"

ACsGameState::ACsGameState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	JavascriptEntryPointClass = ACsJavascriptEntryPoint::StaticClass();

	MyAddRoutine = nullptr;
	MyRemoveRoutine = nullptr;

	CsSetupLastTickActor_Internal			= nullptr;
	SetupLastTickActor_Internal_RoutineType = CS_ROUTINE_MAX_TYPE;
}

void ACsGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACsGameState::PostActorCreated()
{
	Super::PostActorCreated();

	if (GetWorld()->WorldType == EWorldType::Editor ||
		GetWorld()->WorldType == EWorldType::EditorPreview)
		return;

	// Coroutine Scheduler
	UCsCoroutineScheduler::Get()->MyOwner = this;
	OnTick_Event.AddUObject(UCsCoroutineScheduler::Get(), &UCsCoroutineScheduler::OnTick_Update);

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags |= RF_Transient;

	// LastTickActor
	LastTickActor = GetWorld()->SpawnActor<ACsLastTickActor>(ACsLastTickActor::StaticClass(), FTransform::Identity, SpawnInfo);
	LastTickActor->Role = ROLE_None;
	GetWorld()->RemoveNetworkActor(LastTickActor);
	SetupLastTickActor();

#if WITH_EDITOR
	// Javascript
	SetupJavascriptEntryPoint();
#endif // #if WITH_EDITOR
}

void ACsGameState::SeamlessTravelTransitionCheckpoint(bool bToTransitionMap)
{
	Super::SeamlessTravelTransitionCheckpoint(bToTransitionMap);

	//UCsCoroutineScheduler::Get()->EndAll();
	//UCsCoroutineScheduler::Get()->CalcCamera_EndAll();
	UCsCoroutineScheduler::Get()->MyOwner = nullptr;

	if (LastTickActor && !LastTickActor->IsPendingKill())
	{
		LastTickActor->Destroy(true);
		LastTickActor = nullptr;
	}

#if WITH_EDITOR
	if (JavascriptEntryPoint && !JavascriptEntryPoint->IsPendingKill())
	{
		JavascriptEntryPoint->Destroy(true);
		JavascriptEntryPoint = nullptr;
	}
#endif // #if WITH_EDITOR
}

// Javascript
#pragma region

#if WITH_EDITOR

void ACsGameState::SetupJavascriptEntryPoint()
{
	CsCoroutine Function		  = &ACsGameState::SetupJavascriptEntryPoint_Internal;
	CsCoroutineStopCondition Stop = &UCsCommon::CoroutineStopCondition_CheckActor;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsRoutine* R					 = Scheduler->Allocate(Function, Stop, this, true, false);

	Scheduler->StartRoutine(R);
}

PT_THREAD(ACsGameState::SetupJavascriptEntryPoint_Internal(FCsRoutine* r))
{
	ACsGameState* gs		 = Cast<ACsGameState>(r->GetActor());
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w				 = gs->GetWorld();

	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_WAIT_UNTIL(r, gs == w->GetGameState<ACsGameState>());

	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.ObjectFlags					|= RF_Transient;

		gs->JavascriptEntryPoint = w->SpawnActor<ACsJavascriptEntryPoint>(gs->JavascriptEntryPointClass, SpawnInfo);
		gs->JavascriptEntryPoint->Setup();
	}

	CS_COROUTINE_END(r);
}

#endif // #if WITH_EDITOR

#pragma endregion Javascript

// LastTickActor
#pragma region

void ACsGameState::SetupLastTickActor()
{
	if (!CsSetupLastTickActor_Internal)
	{
		checkf(0, TEXT("ACsGameState::SetupLastTickActor: No Function set for CsSetupLastTickActor_Internal."));
	}
	
	CsCoroutine Function		  = CsSetupLastTickActor_Internal;
	CsCoroutineStopCondition Stop = &UCsCommon::CoroutineStopCondition_CheckActor;
	const uint8 Type			  = SetupLastTickActor_Internal_RoutineType;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsRoutine* R					 = Scheduler->Allocate(Function, Stop, this, MyAddRoutine, MyRemoveRoutine, Type, true, false);

	Scheduler->StartRoutine(R);
}

#pragma endregion LastTickActor