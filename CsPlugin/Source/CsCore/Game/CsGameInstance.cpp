// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/CsGameInstance.h"
#include "CsCore.h"

// CoroutineScheduler
#include "Coroutine/CsCoroutineScheduler.h"
// Managers
#include "Managers/Load/CsManager_Load.h"
#include "Managers/Runnable/CsManager_Runnable.h"
#include "Managers/Time/CsManager_Time.h"
#include "Async/AsyncWork.h"

#if WITH_EDITOR
#include "Editor.h"
#endif // #if WITH_EDITOR

UCsGameInstance::UCsGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsGameInstance::Init()
{
	Super::Init();

	// Register delegate for ticker callback
	TickDelegate	   = FTickerDelegate::CreateUObject(this, &UCsGameInstance::Tick);
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);

	ConstructManagerSingleton();

	UCsManager_Time::Init(this);
	UCsCoroutineScheduler::Init(this);
	UCsManager_Load::Init(this);
	UCsManager_Runnable::Init();
}

void UCsGameInstance::Shutdown()
{
	Super::Shutdown();

	// Unregister ticker delegate
	FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);

	UCsManager_Time::Shutdown(this);
	UCsCoroutineScheduler::Shutdown(this);
	UCsManager_Load::Shutdown(this);
	UCsManager_Runnable::Shutdown();
}

#if WITH_EDITOR

FGameInstancePIEResult UCsGameInstance::StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params)
{
	// Cache Params
	GameInstancePIEParametersCache.bSimulateInEditor = Params.bSimulateInEditor;
	GameInstancePIEParametersCache.bAnyBlueprintErrors = Params.bAnyBlueprintErrors;
	GameInstancePIEParametersCache.bStartInSpectatorMode = Params.bStartInSpectatorMode;
	GameInstancePIEParametersCache.bRunAsDedicated = Params.bRunAsDedicated;
	GameInstancePIEParametersCache.WorldFeatureLevel = Params.WorldFeatureLevel;
	
	return Super::StartPlayInEditorGameInstance(LocalPlayer, Params);
}

#endif // #if WITH_EDITOR

// Tick
#pragma region

bool UCsGameInstance::Tick(float DeltaSeconds)
{
	const FECsUpdateGroup& Group = NCsUpdateGroup::GameInstance;

	UCsManager_Time::Get(this)->Update(Group, DeltaSeconds);

	const FCsDeltaTime& DeltaTime = UCsManager_Time::Get(this)->GetScaledDeltaTime(Group);

	UCsCoroutineScheduler::Get(this)->Update(Group, DeltaTime);
	return true;
}

#pragma endregion Tick

bool UCsGameInstance::IsSimulateInEditor()
{
#if WITH_EDITOR
	return GameInstancePIEParametersCache.bSimulateInEditor;
#else
	return false;
#endif // #if WITH_EDITOR
}

void UCsGameInstance::ExitGame()
{
#if WITH_EDITOR
	GEditor->RequestEndPlayMap();
#else
	FGenericPlatformMisc::RequestExit(false);
#endif // #if WITH_EDITOR
}

// Managers
#pragma region

void UCsGameInstance::ConstructManagerSingleton()
{
	checkf(0, TEXT("UCsGameInstance::ConstructManagerSingleton: This function must be implemented in a derived class."));
}

#pragma endregion Managers
