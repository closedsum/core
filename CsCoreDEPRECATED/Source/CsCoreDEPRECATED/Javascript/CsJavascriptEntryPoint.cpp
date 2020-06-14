// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Javascript/CsJavascriptEntryPoint.h"
#include "CsCoreDEPRECATED.h"

// Library
#include "Library/CsLibrary_Common_DEPRECATED.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Game
#include "Game/CsGameInstance_DEPRECATED.h"
#include "Game/CsGameState_DEPRECATED.h"
// UI
#include "UI/CsUI.h"
// Player
#include "Player/CsPlayerController.h"
#include "Player/CsPlayerState.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
#include "Managers/Input/CsManager_Input.h"
// Data
#include "Data/CsDataMapping.h"

#include "GameFramework/Character.h"

// Enums
#pragma region

	// JavascriptEntryPointRoutine
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsJavascriptEntryPointRoutine)

namespace ECsJavascriptEntryPointRoutine
{
	CSCOREDEPRECATED_API const FECsJavascriptEntryPointRoutine Setup_Internal = EMCsJavascriptEntryPointRoutine::Get().Create(TEXT("Setup_Internal"));
}

#pragma endregion Enums

// Cache
#pragma region

namespace NCsJavascriptEntryPointCached
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
	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameState;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(GetGameInstance());
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload(UpdateGroup);

	Payload->Coroutine.BindStatic(&ACsJavascriptEntryPoint::Setup_Internal);
	Payload->StartTime = UCsManager_Time::Get(GetGameInstance())->GetTime(UpdateGroup);
	Payload->Owner.SetObject(this);

	Payload->SetName(NCsJavascriptEntryPointCached::Str::Setup_Internal);
	Payload->SetFName(NCsJavascriptEntryPointCached::Name::Setup_Internal);

	Scheduler->Start(Payload);
}

PT_THREAD(ACsJavascriptEntryPoint::Setup_Internal(FCsRoutine* r))
{
	ACsJavascriptEntryPoint* js = r->GetOwnerAsObject<ACsJavascriptEntryPoint>();
	UWorld* w					= js->GetWorld();
	UCsGameInstance_DEPRECATED* gi			= Cast<UCsGameInstance_DEPRECATED>(w->GetGameInstance());
	ACsGameState_DEPRECATED* gs			= w->GetGameState<ACsGameState_DEPRECATED>();
	UCsCoroutineScheduler* s	= UCsCoroutineScheduler::Get(gi);
	ACsPlayerController* pc		= UCsLibrary_Common::GetLocalPlayerController<ACsPlayerController>(w);
	ACsUI* hud					= pc ? Cast<ACsUI>(pc->MyHUD) : nullptr;
	ACsPlayerState* ps			= UCsLibrary_Common::GetLocalPlayerState<ACsPlayerState>(w);

	CS_COROUTINE_BEGIN(r);

	// Create Javascript hooks
	UCsLibrary_Common_DEPRECATED::SetupJavascript(js, w, js->Isolate, js->Context);

	// Root
	UCsLibrary_Common_DEPRECATED::Javascript_ExposeObject(js->Context, TEXT("Root"), js);

	// GameInstance
	UCsLibrary_Common_DEPRECATED::Javascript_ExposeObject(js->Context, TEXT("GameInstance"), gi);

	// DataMapping
	UCsLibrary_Common_DEPRECATED::Javascript_ExposeObject(js->Context, TEXT("DataMapping"), gi->DataMapping);

	// World
	UCsLibrary_Common_DEPRECATED::Javascript_ExposeObject(js->Context, TEXT("MyWorld"), w);

	// Game State
	UCsLibrary_Common_DEPRECATED::Javascript_ExposeObject(js->Context, TEXT("MyGameState"), gs);

	// Local Player Controller
	CS_COROUTINE_WAIT_UNTIL(r, pc);

	UCsLibrary_Common_DEPRECATED::Javascript_ExposeObject(js->Context, TEXT("MyPC"), pc);

	// HUD
	CS_COROUTINE_WAIT_UNTIL(r, hud);

	UCsLibrary_Common_DEPRECATED::Javascript_ExposeObject(js->Context, TEXT("MyHUD"), hud);

	// Local Player State
	CS_COROUTINE_WAIT_UNTIL(r, ps);

	UCsLibrary_Common_DEPRECATED::Javascript_ExposeObject(js->Context, TEXT("MyPS"), ps);

	// Local Character
	CS_COROUTINE_WAIT_UNTIL(r, pc->GetPawn());

	UCsLibrary_Common_DEPRECATED::Javascript_ExposeObject(js->Context, TEXT("MyPawn"), pc->GetPawn());

	// Manager Input
	CS_COROUTINE_WAIT_UNTIL(r, pc->Manager_Input);

	UCsLibrary_Common_DEPRECATED::Javascript_ExposeObject(js->Context, TEXT("Manager_Input"), pc->Manager_Input);

	// Additional Setup
	CS_COROUTINE_WAIT_UNTIL(r, js->HasCompletedAdditionalSetup());

	// Run Javascript
	UCsLibrary_Common_DEPRECATED::Javascript_RunFile(js->Context, js->EditorFile);

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

	UCsLibrary_Common_DEPRECATED::Javascript_RunFile(Context, EditorFile);
#endif // #if WITH_EDITOR
}