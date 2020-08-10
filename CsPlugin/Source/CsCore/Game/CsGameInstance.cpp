// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/CsGameInstance.h"
#include "CsCore.h"

// CoroutineScheduler
#include "Coroutine/CsCoroutineScheduler.h"
// Managers
#include "Managers/ScopedTimer//CsManager_ScopedTimer.h"
#include "Managers/UnitTest/CsManager_UnitTest.h"
#include "Managers/Load/CsManager_Load.h"
#include "Managers/Runnable/CsManager_Runnable.h"
#include "Managers/Time/CsManager_Time.h"
#include "Async/AsyncWork.h"
// Types
#include "Managers/Time/CsTypes_Update.h"
#include "Managers/Input/CsTypes_Input.h"
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
		const FString Init = TEXT("UCsGameInstance::Init");
		const FString Check_FinishedLoadingPersistentLevel_Internal = TEXT("UCsGameInstance::Check_FinishedLoadingPersistentLevel_Internal");
	}

	namespace Name
	{
		const FName Check_FinishedLoadingPersistentLevel_Internal = FName("UCsGameInstance::Check_FinishedLoadingPersistentLevel_Internal");
	}
}

#pragma endregion Cached

UCsGameInstance::UCsGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

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

	UCsManager_UnitTest::Init(this);
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

	UCsManager_UnitTest::Shutdown(this);
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

	FCsManager_ScopedTimer::Get().Update(DeltaTime);
	UCsCoroutineScheduler::Get(this)->Update(Group, DeltaTime);
	UCsManager_Load::Get(this)->Update(DeltaTime);
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

// Persistent Level
#pragma region

void UCsGameInstance::Check_FinishedLoadingPersistentLevel()
{
	using namespace NCsGameInstanceCached;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(this);
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload(UpdateGroup);

	Payload->CoroutineImpl.BindUObject(this, &UCsGameInstance::Check_FinishedLoadingPersistentLevel_Internal);
	Payload->StartTime = UCsManager_Time::Get(this)->GetTime(UpdateGroup);
	Payload->Owner.SetOwner(this);
	Payload->SetName(Str::Check_FinishedLoadingPersistentLevel_Internal);
	Payload->SetFName(Name::Check_FinishedLoadingPersistentLevel_Internal);

	bFinishedLoadingPersistentlLevel = false;

	Scheduler->Start(Payload);
}

void UCsGameInstance::Check_FinishedLoadingPersistentLevel(const FString& MapPackageName)
{
	using namespace NCsGameInstanceCached;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(this);
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload(UpdateGroup);

	Payload->CoroutineImpl.BindUObject(this, &UCsGameInstance::Check_FinishedLoadingPersistentLevel_Internal);
	Payload->StartTime = UCsManager_Time::Get(this)->GetTime(UpdateGroup);
	Payload->Owner.SetOwner(this);
	Payload->SetName(Str::Check_FinishedLoadingPersistentLevel_Internal);
	Payload->SetFName(Name::Check_FinishedLoadingPersistentLevel_Internal);

	bFinishedLoadingPersistentlLevel = false;

	Payload->SetValue_Flag(CS_FIRST, true);
	Payload->SetValue_String(CS_FIRST, MapPackageName);

	Scheduler->Start(Payload);
}

char UCsGameInstance::Check_FinishedLoadingPersistentLevel_Internal(FCsRoutine* R)
{
	const bool& CheckMapName	  = R->GetValue_Flag(CS_FIRST);
	const FString& MapPackageName = R->GetValue_String(CS_FIRST);

	if (GetWorld())
	{
		const TArray<ULevel*>& Levels = GetWorld()->GetLevels();

		for (ULevel* Level : Levels)
		{
			if (Level->IsPersistentLevel() &&
				Level->bIsVisible)
			{
				if (CheckMapName)
				{
					const FString PersistentLevelPackageName = UWorld::StripPIEPrefixFromPackageName(GetWorld()->GetOutermost()->GetName(), GetWorld()->StreamingLevelsPrefix);

					if (PersistentLevelPackageName == MapPackageName)
					{
						bFinishedLoadingPersistentlLevel = true;
						break;
					}
				}
				else
				{
					bFinishedLoadingPersistentlLevel = true;
					break;
				}
			}
		}
	}

	CS_COROUTINE_BEGIN(R);

	// Wait until Persistent level is loaded
	CS_COROUTINE_WAIT_UNTIL(R, bFinishedLoadingPersistentlLevel);

	CS_COROUTINE_END(R);
}

ULevel* UCsGameInstance::GetPersistentLevel()
{
	if (GetWorld())
	{
		const TArray<ULevel*>& Levels = GetWorld()->GetLevels();

		for (ULevel* Level : Levels)
		{
			if (Level->IsPersistentLevel())
			{
				return Level;
			}
		}
	}
	return nullptr;
}

FString UCsGameInstance::GetPersistentLevelName()
{
	if (GetWorld())
	{
		return UWorld::StripPIEPrefixFromPackageName(GetWorld()->GetOutermost()->GetName(), GetWorld()->StreamingLevelsPrefix);
	}
	return FString();
}

FName UCsGameInstance::GetPersistentLevelFName()
{
	if (GetWorld())
	{
		const FString Name = UWorld::StripPIEPrefixFromPackageName(GetWorld()->GetOutermost()->GetName(), GetWorld()->StreamingLevelsPrefix);

		return FName(*Name);
	}
	return NAME_None;
}

ACsLevelScriptActor* UCsGameInstance::GetPersistentLevelScriptActor()
{
	return Cast<ACsLevelScriptActor>(GetPersistentLevel()->LevelScriptActor);
}

#pragma endregion Persistent Level