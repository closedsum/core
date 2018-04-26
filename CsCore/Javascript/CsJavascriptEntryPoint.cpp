// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Javascript/CsJavascriptEntryPoint.h"
#include "CsCore.h"
#include "Common/CsCommon.h"
#include "Game/CsGameInstance.h"
#include "Data/CsDataMapping.h"
#include "Coroutine/CsCoroutineScheduler.h"
#include "Game/CsGameState.h"
#include "Player/CsPlayerController.h"
#include "UI/CsUI.h"
#include "Player/CsPlayerState.h"

// Managers
#include "Managers/Input/CsManager_Input.h"

#if WITH_EDITOR
#include "../Plugins/UnrealJS/Source/V8/Public/JavascriptIsolate.h"
#include "../Plugins/UnrealJS/Source/V8/Public/JavascriptContext.h"
#endif // #if WITH_EDITOR

#include "GameFramework/Character.h"

ACsJavascriptEntryPoint::ACsJavascriptEntryPoint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;

	EditorFile = TEXT("Cs/EntryPoint_Game.js");
}

// Javascript
#pragma region

#if WITH_EDITOR

void ACsJavascriptEntryPoint::Setup()
{
	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	CsCoroutine Function		  = &ACsJavascriptEntryPoint::Setup_Internal;
	CsCoroutineStopCondition Stop = &UCsCommon::CoroutineStopCondition_CheckActor;
	CsAddRoutine Add			  = &ACsJavascriptEntryPoint::AddRoutine;
	CsRemoveRoutine Remove		  = &ACsJavascriptEntryPoint::RemoveRoutine;
	const uint8 Type			  = (uint8)ECsRoutineJavascriptEntryPoint::Setup_Internal;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsRoutine* R					 = Scheduler->Allocate(Schedule, Function, Stop, this, Add, Remove, Type, true, false);
	Setup_Internal_Routine			 = R;

	Scheduler->StartRoutine(Schedule, R);
}

PT_THREAD(ACsJavascriptEntryPoint::Setup_Internal(FCsRoutine* r))
{
	ACsJavascriptEntryPoint* js = Cast<ACsJavascriptEntryPoint>(r->GetActor());
	UWorld* w					= js->GetWorld();
	UCsGameInstance* gi			= Cast<UCsGameInstance>(w->GetGameInstance());
	ACsGameState* gs			= w->GetGameState<ACsGameState>();
	UCsCoroutineScheduler* s	= UCsCoroutineScheduler::Get();
	ACsPlayerController* pc		= UCsCommon::GetLocalPlayerController<ACsPlayerController>(w);
	ACsUI* hud					= pc ? Cast<ACsUI>(pc->MyHUD) : nullptr;
	ACsPlayerState* ps			= UCsCommon::GetLocalPlayerState<ACsPlayerState>(w);

	CS_COROUTINE_BEGIN(r);

	// Create Javascript hooks
	UCsCommon::SetupJavascript(js, w, js->Isolate, js->Context);

	// Root
	UCsCommon::Javascript_ExposeObject(js->Context, TEXT("Root"), js);

	// GameInstance
	UCsCommon::Javascript_ExposeObject(js->Context, TEXT("GameInstance"), gi);

	// DataMapping
	UCsCommon::Javascript_ExposeObject(js->Context, TEXT("DataMapping"), gi->DataMapping);

	// World
	UCsCommon::Javascript_ExposeObject(js->Context, TEXT("MyWorld"), w);

	// Game State
	UCsCommon::Javascript_ExposeObject(js->Context, TEXT("MyGameState"), gs);

	// Local Player Controller
	CS_COROUTINE_WAIT_UNTIL(r, pc);

	UCsCommon::Javascript_ExposeObject(js->Context, TEXT("MyPC"), pc);

	// HUD
	CS_COROUTINE_WAIT_UNTIL(r, hud);

	UCsCommon::Javascript_ExposeObject(js->Context, TEXT("MyHUD"), hud);

	// Local Player State
	CS_COROUTINE_WAIT_UNTIL(r, ps);

	UCsCommon::Javascript_ExposeObject(js->Context, TEXT("MyPS"), ps);

	// Local Character
	CS_COROUTINE_WAIT_UNTIL(r, pc->GetPawn());

	UCsCommon::Javascript_ExposeObject(js->Context, TEXT("MyPawn"), pc->GetPawn());

	// Manager Input
	CS_COROUTINE_WAIT_UNTIL(r, pc->Manager_Input);

	UCsCommon::Javascript_ExposeObject(js->Context, TEXT("Manager_Input"), pc->Manager_Input);

	// Additional Setup
	CS_COROUTINE_WAIT_UNTIL(r, js->HasCompletedAdditionalSetup());

	// Run Javascript
	UCsCommon::Javascript_RunFile(js->Context, js->EditorFile);

	js->HasCompletedSetup = true;

	CS_COROUTINE_END(r);
}

bool ACsJavascriptEntryPoint::HasCompletedAdditionalSetup()
{
	return true;
}

#endif // #if WITH_EDITOR

float ACsJavascriptEntryPoint::GetTimeSeconds()
{
	return GetWorld()->GetTimeSeconds();
}

#pragma endregion Javascript

// Routines
#pragma region

/*static*/ void ACsJavascriptEntryPoint::AddRoutine(UObject* InJavascriptEntryPoint, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<ACsJavascriptEntryPoint>(InJavascriptEntryPoint)->AddRoutine_Internal(Routine, (TCsRoutineJavascriptEntryPoint)Type);
}

void ACsJavascriptEntryPoint::AddRoutine_Internal(struct FCsRoutine* Routine, const TCsRoutineJavascriptEntryPoint &Type)
{
#if WITH_EDITOR
	// Setup_Internal
	if (Type == ECsRoutineJavascriptEntryPoint::Setup_Internal)
	{
		Setup_Internal_Routine = Routine;
		return;
	}
#endif // #if WITH_EDITOR
	checkf(0, TEXT("ACsJavascriptEntryPoint::AddRoutine_Internal: Adding a Routine of unknown Type"));
}

/*static*/ void ACsJavascriptEntryPoint::RemoveRoutine(UObject* InJavascriptEntryPoint, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<ACsJavascriptEntryPoint>(InJavascriptEntryPoint)->RemoveRoutine_Internal(Routine, (TCsRoutineJavascriptEntryPoint)Type);
}

void ACsJavascriptEntryPoint::RemoveRoutine_Internal(struct FCsRoutine* Routine, const TCsRoutineJavascriptEntryPoint &Type)
{
#if WITH_EDITOR
	// Setup_Internal
	if (Type == ECsRoutineJavascriptEntryPoint::Setup_Internal)
	{
		check(Setup_Internal_Routine == Routine);
		Setup_Internal_Routine = nullptr;
		return;
	}
#endif // #if WITH_EDITOR
	checkf(0, TEXT("ACsJavascriptEntryPoint::AddRoutine_Internal: Removing a Routine of unknown Type"));
}

#pragma endregion Routines

void ACsJavascriptEntryPoint::Run()
{
#if WITH_EDITOR
	if (EditorFile == TEXT(""))
		return;

	DoPerformCleanUpOnEditorFile = true;

	UCsCommon::Javascript_RunFile(Context, EditorFile);
#endif // #if WITH_EDITOR
}