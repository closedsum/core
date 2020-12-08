// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/CsGameInstance.h"
#include "CsCore.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "Managers/Time/CsTypes_Update.h"
#include "Managers/Input/CsTypes_Input.h"
// Managers
#include "Managers/ScopedTimer//CsManager_ScopedTimer.h"
#include "Managers/UnitTest/CsManager_UnitTest.h"
#include "Managers/Load/CsManager_Load.h"
#include "Managers/Runnable/CsManager_Runnable.h"
#include "Managers/Time/CsManager_Time.h"
// Coordinators
#include "Coordinators/ConsoleCommand/CsCoordinator_ConsoleCommand.h"
#include "Coordinators/GameEvent/CsCoordinator_GameEvent.h"
// Level
#include "Level/CsLevelScriptActor.h"

#if WITH_EDITOR
#include "Editor.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsGameInstanceCached
{
	namespace Str
	{
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsGameInstance, Init);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsGameInstance, Check_FinishedLoadingPersistentLevel_Internal);
	}

	namespace Name
	{
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsGameInstance, Check_FinishedLoadingPersistentLevel_Internal);
	}
}

#pragma endregion Cached

UCsGameInstance::UCsGameInstance(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer)
{
}

// UGameInstance Interface
#pragma region

void UCsGameInstance::Init()
{
	Super::Init();

	using namespace NCsGameInstanceCached;

	const FString& Context = Str::Init;

	// Register delegate for ticker callback
	TickDelegate	   = FTickerDelegate::CreateUObject(this, &UCsGameInstance::Tick);
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);

	// Populate Enum Maps
	
		// Input
	NCsInputAction::PopulateEnumMapFromSettings(Context, this);
	NCsInputActionMap::PopulateEnumMapFromSettings(Context, this);
	NCsGameEvent::PopulateEnumMapFromSettings(Context, this);
	
	ConstructManagerSingleton();

	UCsCoordinator_ConsoleCommand::Init(this);
	UCsManager_UnitTest::Init(this);
	UCsManager_Time::Init(this);
	UCsCoroutineScheduler::Init(this);
	UCsManager_Load::Init(this);
	UCsManager_Runnable::Init(this);
	UCsCoordinator_GameEvent::Init(this);
}

void UCsGameInstance::Shutdown()
{
	Super::Shutdown();

	// Unregister ticker delegate
	FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);

	UCsCoordinator_GameEvent::Shutdown(this);
	UCsManager_Load::Shutdown(this);
	UCsManager_Runnable::Shutdown(this);
	UCsCoroutineScheduler::Shutdown(this);
	UCsManager_Time::Shutdown(this);
	UCsManager_UnitTest::Shutdown(this);
	UCsCoordinator_ConsoleCommand::Shutdown(this);
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

#pragma endregion UGameInstance Interface

// FExec Interface
#pragma region

bool UCsGameInstance::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Out /*=*GLog*/)
{
	if (Super::Exec(InWorld, Cmd, Out))
		return true;
	if (UCsCoordinator_ConsoleCommand::Get(this)->Exec(InWorld, Cmd, Out))
		return true;
	return false;
}

#pragma endregion FExec Interface

// Tick
#pragma region

bool UCsGameInstance::Tick(float DeltaSeconds)
{
	const FECsUpdateGroup& Group = NCsUpdateGroup::GameInstance;

	UCsManager_Time::Get(this)->Update(Group, DeltaSeconds);

	const FCsDeltaTime& DeltaTime = UCsManager_Time::Get(this)->GetScaledDeltaTime(Group);

	FCsManager_ScopedTimer::Get().Update(DeltaTime);
	UCsCoroutineScheduler::Get(this)->Update(Group, DeltaTime);
	UCsManager_Load::Get(this)->Update(DeltaTime);
	UCsManager_Runnable::Get(this)->Update(DeltaTime);
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