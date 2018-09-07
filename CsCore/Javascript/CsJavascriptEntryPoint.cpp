// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Javascript/CsJavascriptEntryPoint.h"
#include "CsCore.h"
#include "Common/CsCommon.h"

#include "Coroutine/CsCoroutineScheduler.h"

// Game
#include "Game/CsGameInstance.h"
#include "Game/CsGameState.h"
// UI
#include "UI/CsUI.h"
// Player
#include "Player/CsPlayerController.h"
#include "Player/CsPlayerState.h"
// Managers
#include "Managers/Input/CsManager_Input.h"
// Data
#include "Data/CsDataMapping.h"

#include "GameFramework/Character.h"

// Enums
#pragma region

// JavascriptEntryPointRoutine
EMCsJavascriptEntryPointRoutine* EMCsJavascriptEntryPointRoutine::Instance;

EMCsJavascriptEntryPointRoutine& EMCsJavascriptEntryPointRoutine::Get()
{
	if (!Instance)
		Instance = new EMCsJavascriptEntryPointRoutine();
	return *Instance;
}

namespace ECsJavascriptEntryPointRoutine
{
	CSCORE_API const FECsJavascriptEntryPointRoutine Setup_Internal = EMCsJavascriptEntryPointRoutine::Get().Create(TEXT("Setup_Internal"));
}

#pragma endregion Enums

// Cache
#pragma region

namespace ECsJavascriptEntryPointCached
{
	namespace Name
	{
		// Functions
		const FName Setup_Internal = FName("ACsJavascriptEntryPoint::Setup_Internal");
	};

	namespace Str
	{
		// Functions
		const FString Setup_Internal = TEXT("ACsJavascriptEntryPoint::Setup_Internal");
	};
}

#pragma endregion Cache

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
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const ECsCoroutineSchedule& Schedule = NCsCoroutineSchedule::Ref::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &ACsJavascriptEntryPoint::Setup_Internal;
	Payload->Actor			= this;
	Payload->Stop.Add(&UCsCommon::CoroutineStopCondition_CheckActor);
	Payload->Add			= &ACsJavascriptEntryPoint::AddRoutine;
	Payload->Remove			= &ACsJavascriptEntryPoint::RemoveRoutine;
	Payload->Type			= ECsJavascriptEntryPointRoutine::Setup_Internal.Value;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsJavascriptEntryPointCached::Name::Setup_Internal;
	Payload->NameAsString	= ECsJavascriptEntryPointCached::Str::Setup_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

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
	Cast<ACsJavascriptEntryPoint>(InJavascriptEntryPoint)->AddRoutine_Internal(Routine, Type);
}

void ACsJavascriptEntryPoint::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	const FECsJavascriptEntryPointRoutine& RoutineType = EMCsJavascriptEntryPointRoutine::Get()[Type];

#if WITH_EDITOR
	// Setup_Internal
	if (RoutineType == ECsJavascriptEntryPointRoutine::Setup_Internal)
	{
		Setup_Internal_Routine = Routine;
		return;
	}
#endif // #if WITH_EDITOR
	checkf(0, TEXT("ACsJavascriptEntryPoint::AddRoutine_Internal: Adding a Routine of unknown Type"));
}

/*static*/ void ACsJavascriptEntryPoint::RemoveRoutine(UObject* InJavascriptEntryPoint, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<ACsJavascriptEntryPoint>(InJavascriptEntryPoint)->RemoveRoutine_Internal(Routine, Type);
}

void ACsJavascriptEntryPoint::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	const FECsJavascriptEntryPointRoutine& RoutineType = EMCsJavascriptEntryPointRoutine::Get()[Type];

#if WITH_EDITOR
	// Setup_Internal
	if (Type == ECsJavascriptEntryPointRoutine::Setup_Internal)
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