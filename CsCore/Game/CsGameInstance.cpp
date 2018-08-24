// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/CsGameInstance.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"

#include "Coroutine/CsCoroutineScheduler.h"

// Managers
#include "Managers/CsManager_Loading.h"
#include "Managers/Runnable/CsManager_Runnable.h"
// Data
#include "Data/CsDataMapping.h"
#include "Data/CsData_Payload.h"
#include "Data/CsData.h"
#include "Data/CsData_UI_Common.h"
// UI
#include "UI/CsUserWidget.h"
#include "UI/CsWidget_Fullscreen.h"

#include "Async/AsyncWork.h"

#if WITH_EDITOR
#include "Editor.h"
#endif // #if WITH_EDITOR

// Enums
#pragma region

namespace ECsGameInstanceRoutine
{
	namespace Str
	{
		const TCsString OnBoard_Internal = TCsString(TEXT("OnBoard_Internal"), TEXT("onboard_internal"));
		const TCsString LoadDataMapping_Internal = TCsString(TEXT("LoadDataMapping_Internal"), TEXT("loaddatamapping_internal"));
		const TCsString PerformLevelTransition_Internal = TCsString(TEXT("PerformLevelTransition_Internal"), TEXT("performleveltransition_internal"));
		const TCsString CreateFullscreenWidget_Internal = TCsString(TEXT("CreateFullscreenWidget_Internal"), TEXT("createfullscreenwidget_internal"));
		const TCsString HideMouseCursor_Internal = TCsString(TEXT("HideMouseCursor_Internal"), TEXT("hidemousecursor_internal"));
	}

	namespace Ref
	{
		const TCsGameInstanceRoutine OnBoard_Internal = Type::OnBoard_Internal;
		const TCsGameInstanceRoutine LoadDataMapping_Internal = Type::LoadDataMapping_Internal;
		const TCsGameInstanceRoutine PerformLevelTransition_Internal = Type::PerformLevelTransition_Internal;
		const TCsGameInstanceRoutine CreateFullscreenWidget_Internal = Type::CreateFullscreenWidget_Internal;
		const TCsGameInstanceRoutine HideMouseCursor_Internal = Type::HideMouseCursor_Internal;
		const TCsGameInstanceRoutine ECsGameInstanceRoutine_MAX = Type::ECsGameInstanceRoutine_MAX;
	}
}

namespace ECsGameInstanceOnBoardState
{
	namespace Str
	{
		const TCsString LoadDataMapping = TCsString(TEXT("LoadDataMapping"), TEXT("loaddatamapping"));
		const TCsString FinishedLoadingDataAssets = TCsString(TEXT("FinishedLoadingDataAssets"), TEXT("finishedloadingdataassets"));
		const TCsString FinishedPopulatingAssetReferences = TCsString(TEXT("FinishedPopulatingAssetReferences"), TEXT("finishedpopulatingassetreferences"));
		const TCsString LoadStartUpData = TCsString(TEXT("LoadStartUpData"), TEXT("loadstartupdata"));
		const TCsString LoadScreen = TCsString(TEXT("LoadScreen"), TEXT("loadscreen"));
		const TCsString Completed = TCsString(TEXT("Completed"), TEXT("completed"));
	}

	namespace Ref
	{
		const Type LoadDataMapping = Type::LoadDataMapping;
		const Type FinishedLoadingDataAssets = Type::FinishedLoadingDataAssets;
		const Type FinishedPopulatingAssetReferences = Type::FinishedPopulatingAssetReferences;
		const Type LoadStartUpData = Type::LoadStartUpData;
		const Type LoadScreen = Type::LoadScreen;
		const Type Completed = Type::Completed;
		const Type ECsGameInstanceOnBoardState_MAX = Type::ECsGameInstanceOnBoardState_MAX;
	}
}

#pragma endregion

// Cache
#pragma region

namespace ECsGameInstanceCached
{
	namespace Name
	{
		// Functions
		const FName OnBoard_Internal = FName("UCsGameInstance::OnBoard_Internal");
		const FName LoadDataMapping_Internal = FName("UCsGameInstance::LoadDataMapping_Internal");
		const FName PerformLevelTransition_Internal = FName("UCsGameInstance::PerformLevelTransition_Internal");
		const FName CreateFullscreenWidget_Internal = FName("UCsGameInstance::CreateFullscreenWidget_Internal");
		const FName HideMouseCursor_Internal = FName("UCsGameInstance::HideMouseCursor_Internal");
	};

	namespace Str
	{
		// Functions
		const FString OnBoard_Internal = TEXT("UCsGameInstance::OnBoard_Internal");
		const FString LoadDataMapping_Internal = TEXT("UCsGameInstance::LoadDataMapping_Internal");
		const FString PerformLevelTransition_Internal = TEXT("UCsGameInstance::PerformLevelTransition_Internal");
		const FString CreateFullscreenWidget_Internal = TEXT("UCsGameInstance::CreateFullscreenWidget_Internal");
		const FString HideMouseCursor_Internal = TEXT("UCsGameInstance::HideMouseCursor_Internal");
	};
}

#pragma endregion Cache

UCsGameInstance::UCsGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentGameFrame = 0;

#if WITH_EDITOR
	ForcePopulateAssetReferences = true;
#endif // #if WITH_EDITOR

	DataMappingAssetPath = TEXT("/Game/AlwaysCook/bp_data_mapping.bp_data_mapping_C");
	DataMapping			 = nullptr;

	OnBoardState = ECsGameInstanceOnBoardState::LoadDataMapping;
	LevelState   = ECsLevelState::None;
}

void UCsGameInstance::InitCVars(){}

void UCsGameInstance::Init()
{
	Super::Init();

	// Register delegate for ticker callback
	TickDelegate	   = FTickerDelegate::CreateUObject(this, &UCsGameInstance::Tick);
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);

	OnPreWorldInitializationHandle	= FWorldDelegates::OnPreWorldInitialization.AddUObject(this, &UCsGameInstance::OnPreWorldInitialization);
	OnPostWorldInitializationHandle = FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UCsGameInstance::OnPostWorldInitialization);
	OnLevelAddedToWorldHandle		= FWorldDelegates::LevelAddedToWorld.AddUObject(this, &UCsGameInstance::OnLevelAddedToWorld);
	OnLevelRemovedFromWorldHandle	= FWorldDelegates::LevelRemovedFromWorld.AddUObject(this, &UCsGameInstance::OnLevelRemovedFromWorld);

	UCsManager_Loading::Init();
	UCsManager_Runnable::Init();
	UCsCoroutineScheduler::Init();

	OnTick_Event.AddUObject(UCsCoroutineScheduler::Get(), &UCsCoroutineScheduler::OnTick_Update);
	
	HideMouseCursor();
	OnBoard();

	IsVR = GEngine->StereoRenderingDevice.IsValid() && GEngine->IsStereoscopic3D();
}

void UCsGameInstance::Shutdown()
{
	Super::Shutdown();

	// Unregister ticker delegate
	FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);

	if (FullscreenWidget && !FullscreenWidget->IsPendingKill())
		FullscreenWidget->MarkPendingKill();

	FWorldDelegates::OnPreWorldInitialization.Remove(OnPreWorldInitializationHandle);
	FWorldDelegates::OnPostWorldInitialization.Remove(OnPostWorldInitializationHandle);
	FWorldDelegates::LevelAddedToWorld.Remove(OnLevelAddedToWorldHandle);
	FWorldDelegates::LevelRemovedFromWorld.Remove(OnLevelRemovedFromWorldHandle);

	UCsManager_Loading::Shutdown();
	UCsManager_Runnable::Shutdown();
	UCsCoroutineScheduler::Shutdown();
}

void UCsGameInstance::StartGameInstance()
{
	Super::StartGameInstance();
}

#if WITH_EDITOR

FGameInstancePIEResult UCsGameInstance::StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params)
{
	return Super::StartPlayInEditorGameInstance(LocalPlayer, Params);
}

#endif // #if WITH_EDITOR

bool UCsGameInstance::Tick(float DeltaSeconds)
{
	++CurrentGameFrame;

	OnTick_Event.Broadcast(DeltaSeconds);
#if WITH_EDITOR
	OnTick_ScriptEvent.Broadcast(DeltaSeconds);
#endif // #if WITH_EDITOR
	return true;
}

// Routines
#pragma region

/*static*/ void UCsGameInstance::AddRoutine(UObject* InGameInstance, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<UCsGameInstance>(InGameInstance)->AddRoutine_Internal(Routine, Type);
}

bool UCsGameInstance::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	const TCsGameInstanceRoutine RoutineType = (TCsGameInstanceRoutine)Type;

	// OnBoard_Internal
	if (RoutineType == ECsGameInstanceRoutine::OnBoard_Internal)
	{
		OnBoard_Internal_Routine = Routine;
		return true;
	}
	// PerformLevelTransition_Internal
	if (RoutineType == ECsGameInstanceRoutine::PerformLevelTransition_Internal)
	{
		PerformLevelTransition_Internal_Routine = Routine;
		return true;
	}
	// CreateFullscreenWidget_Internal
	if (RoutineType == ECsGameInstanceRoutine::CreateFullscreenWidget_Internal)
	{
		CreateFullscreenWidget_Internal_Routine = Routine;
		return true;
	}
	// HideMouseCursor_Internal
	if (RoutineType == ECsGameInstanceRoutine::HideMouseCursor_Internal)
	{
		HideMouseCursor_Internal_Routine = Routine;
		return true;
	}
	return false;
}

/*static*/ void UCsGameInstance::RemoveRoutine(UObject* InGameInstance, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<UCsGameInstance>(InGameInstance)->RemoveRoutine_Internal(Routine, Type);
}

bool UCsGameInstance::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	const TCsGameInstanceRoutine RoutineType = (TCsGameInstanceRoutine)Type;

	// OnBoard_Internal
	if (RoutineType == ECsGameInstanceRoutine::OnBoard_Internal)
	{
		check(OnBoard_Internal_Routine == Routine);
		OnBoard_Internal_Routine = nullptr;
		return true;
	}
	// PerformLevelTransition_Internal
	if (RoutineType == ECsGameInstanceRoutine::PerformLevelTransition_Internal)
	{
		check(PerformLevelTransition_Internal_Routine == Routine);
		PerformLevelTransition_Internal_Routine = nullptr;
		return true;
	}
	// CreateFullscreenWidget_Internal
	if (RoutineType == ECsGameInstanceRoutine::CreateFullscreenWidget_Internal)
	{
		check(CreateFullscreenWidget_Internal_Routine == Routine);
		CreateFullscreenWidget_Internal_Routine = nullptr;
		return true;
	}
	// HideMouseCursor_Internal
	if (RoutineType == ECsGameInstanceRoutine::HideMouseCursor_Internal)
	{
		check(HideMouseCursor_Internal_Routine == Routine);
		HideMouseCursor_Internal_Routine = nullptr;
		return true;
	}
	return false;
}

#pragma endregion Routines

// OnBoard
#pragma region

void UCsGameInstance::OnBoard()
{
	const ECsCoroutineSchedule& Schedule = NCsCoroutineSchedule::Ref::Tick;

	CsCoroutine Function		  = &UCsGameInstance::OnBoard_Internal;
	CsCoroutineStopCondition Stop = &UCsCommon::CoroutineStopCondition_CheckObject;
	CsAddRoutine Add			  = &UCsGameInstance::AddRoutine;
	CsRemoveRoutine Remove		  = &UCsGameInstance::RemoveRoutine;
	const uint8 Type			  = (uint8)ECsGameInstanceRoutine::OnBoard_Internal;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsRoutine* R					 = Scheduler->Allocate(Schedule, Function, Stop, this, Add, Remove, Type, true, false);

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(UCsGameInstance, OnBoard_Internal)
{
	UCsGameInstance* gi		 = Cast<UCsGameInstance>(r->GetRObject());
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();

	CS_COROUTINE_BEGIN(r);

	gi->LoadDataMapping();

	CS_COROUTINE_WAIT_UNTIL(r, gi->OnBoardState == ECsGameInstanceOnBoardState::LoadStartUpData);

	gi->LoadStartUpData();

	CS_COROUTINE_WAIT_UNTIL(r, gi->OnBoardState == ECsGameInstanceOnBoardState::LoadScreen);

	gi->CreateFullscreenWidget();

	CS_COROUTINE_WAIT_UNTIL(r, gi->FullscreenWidget);

	gi->OnBoardState = ECsGameInstanceOnBoardState::Completed;

	CS_COROUTINE_WAIT_UNTIL(r, gi->OnBoardState == ECsGameInstanceOnBoardState::Completed);

	gi->OnBoardCompleted_Event.Broadcast();

	CS_COROUTINE_END(r);
}

	// Data Mapping
#pragma region

void UCsGameInstance::LoadDataMapping()
{
	const FStringAssetReference AssetRef			 = FStringAssetReference(DataMappingAssetPath);
	TSoftClassPtr<ACsDataMapping> AssetSubclassOf = TSoftClassPtr<ACsDataMapping>(AssetRef);

	if (UClass* DataClass = AssetSubclassOf.LoadSynchronous())
	{
		DataMapping = DataClass->GetDefaultObject<ACsDataMapping>();
#if WITH_EDITOR

		checkf(DataMapping->IsValid(), TEXT("UCsGameInstance::LoadDataMapping: DataMapping is NOT Valid."));

		DataMapping->LoadFromJson();
		DataMapping->ClearLoaded();
		DataMapping->PopulateDataAssetReferences();
#endif // #if WITH_EDITOR
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsGameInstance::Init: Failed to Load DataMapping asset."));
		return;
	}

	const ECsCoroutineSchedule& Schedule = NCsCoroutineSchedule::Ref::Tick;

	CsCoroutine Function		  = &UCsGameInstance::LoadDataMapping_Internal;
	CsCoroutineStopCondition Stop = &UCsCommon::CoroutineStopCondition_CheckObject;
	CsAddRoutine Add			  = &UCsGameInstance::AddRoutine;
	CsRemoveRoutine Remove		  = &UCsGameInstance::RemoveRoutine;
	const uint8 Type			  = (uint8)ECsGameInstanceRoutine::LoadDataMapping_Internal;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsRoutine* R					 = Scheduler->Allocate(Schedule, Function, Stop, this, Add, Remove, Type, true, false);

	Scheduler->StartRoutine(Schedule, R);
}

PT_THREAD(UCsGameInstance::LoadDataMapping_Internal(struct FCsRoutine* r))
{
	UCsGameInstance* gi			= Cast<UCsGameInstance>(r->GetRObject());
	UCsCoroutineScheduler* s	= UCsCoroutineScheduler::Get();
	ACsDataMapping* dataMapping = gi->DataMapping;

	CS_COROUTINE_BEGIN(r);

	if (gi->ForcePopulateAssetReferences || dataMapping->ForcePopulateAssetReferences)
	{
		UCsManager_Loading::Get()->LoadAssetReferences(gi->GetWorld(), dataMapping->DataAssetReferences, ECsLoadAsyncOrder::Bulk, gi, &UCsGameInstance::OnFinishedLoadingDataAssets);

		// Wait until Data Assets are LOADED
		CS_COROUTINE_WAIT_UNTIL(r, gi->OnBoardState == ECsGameInstanceOnBoardState::FinishedLoadingDataAssets);

#if WITH_EDITOR
		CS_COROUTINE_WAIT_UNTIL(r, !dataMapping->AsyncTaskMutex.IsLocked());
#endif // #if WITH_EDITOR

		if (UCsCommon::CanAsyncTask())
		{
			gi->AsyncPopulateAssetReferences();
		}
		else
		{
			gi->PopulateAssetReferences();
		}
		// Wait until ALL Asset References
		CS_COROUTINE_WAIT_UNTIL(r, gi->OnBoardState == ECsGameInstanceOnBoardState::FinishedPopulatingAssetReferences);
	}

#if WITH_EDITOR
	{
		ACsData_Payload* Payload = dataMapping->GetPayload();

		checkf(Payload->Editor_IsValid(dataMapping), TEXT("UCsGameInstance::LoadDataMapping_Internal: Payload is NOT Valid."));
	}
#endif // #if WITH_EDITOR

	dataMapping->GenerateMaps();

#if WITH_EDITOR
	dataMapping->AsyncTaskMutex.Unlock();
#endif // #if WITH_EDITOR

	gi->HasLoadedDataMapping = true;
	gi->OnBoardState = ECsGameInstanceOnBoardState::LoadStartUpData;

	CS_COROUTINE_END(r);
}

void UCsGameInstance::OnFinishedLoadingDataAssets(const TArray<UObject*> &LoadedAssets, const float& LoadingTime)
{
	const int32 Count = LoadedAssets.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		LoadedDataAssets.Add(LoadedAssets[I]);
	}
	OnBoardState = ECsGameInstanceOnBoardState::FinishedLoadingDataAssets;
}

void UCsGameInstance::PopulateAssetReferences()
{
	// TODO: Maybe time slice this for built game 
	const int32 Count = LoadedDataAssets.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		ACsData* Data = Cast<UBlueprintGeneratedClass>(LoadedDataAssets[I])->GetDefaultObject<ACsData>();
		Data->LoadFromJson();
		Data->PopulateAssetReferences(false);
	}
	DataMapping->PopulateAssetReferences();
	LoadedDataAssets.Reset();

	OnBoardState = ECsGameInstanceOnBoardState::FinishedPopulatingAssetReferences;
}

void UCsGameInstance::AsyncPopulateAssetReferences()
{
#if WITH_EDITOR
	DataMapping->AsyncTaskMutex.Lock();
#endif // #if WITH_EDITOR

	UCsManager_Runnable* Manager_Runnable = UCsManager_Runnable::Get();

	FCsRunnablePayload* Payload = Manager_Runnable->AllocatePayload();
	Payload->Owner				= this;
	Payload->ThreadPriority		= EThreadPriority::TPri_Normal;

	FCsRunnable_Delegate* Runnable = Manager_Runnable->Prep(Payload);
	Runnable->Delegate.AddUObject(this, &UCsGameInstance::PopulateAssetReferences);
	Runnable->Start();
}

/*
void UCsGameInstance::AsyncPopulateAssetReferences()
{
	class FAsyncPopulateAssetReferencesWorker : public FNonAbandonableTask
	{
	public:

		friend class FAutoDeleteAsyncTask<FAsyncPopulateAssetReferencesWorker>;

		UCsGameInstance* GameInstance;

		FAsyncPopulateAssetReferencesWorker(UCsGameInstance* InGameInstance)
		{
			GameInstance = InGameInstance;
		}

		void DoWork()
		{
			GameInstance->PopulateAssetReferences();
		}

		FORCEINLINE TStatId GetStatId() const
		{
			RETURN_QUICK_DECLARE_CYCLE_STAT(FAsyncPopulateAssetReferencesWorker, STATGROUP_ThreadPoolAsyncTasks);
		}
	};
	(new FAutoDeleteAsyncTask<FAsyncPopulateAssetReferencesWorker>(this))->StartBackgroundTask();
}
*/

#pragma endregion Data Mapping

	// Load StartUp Data
#pragma region

void UCsGameInstance::LoadStartUpData(){ OnBoardState = ECsGameInstanceOnBoardState::LoadScreen; }
void UCsGameInstance::OnFinishedLoadingStartUpDataAssets(const TArray<UObject*> &LoadedAssets, const float& LoadingTime){}

#pragma endregion Load StartUp Data

	// Fullscreen Widget
#pragma region

void UCsGameInstance::CreateFullscreenWidget()
{
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload = Scheduler->AllocatePayload();

	const ECsCoroutineSchedule& Schedule = NCsCoroutineSchedule::Ref::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &UCsGameInstance::CreateFullscreenWidget_Internal;
	Payload->Object			= this;
	Payload->Stop.Add(&UCsCommon::CoroutineStopCondition_CheckObject);
	Payload->Add			= &UCsGameInstance::AddRoutine;
	Payload->Remove			= &UCsGameInstance::RemoveRoutine;
	Payload->Type			= (uint8)ECsGameInstanceRoutine::CreateFullscreenWidget_Internal;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsGameInstanceCached::Name::CreateFullscreenWidget_Internal;
	Payload->NameAsString	= ECsGameInstanceCached::Str::CreateFullscreenWidget_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(UCsGameInstance, CreateFullscreenWidget_Internal)
{
	UCsGameInstance* gi		 = r->GetRObject<UCsGameInstance>();
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();
	UWorld* w				 = gi->GetWorld();

	CS_COROUTINE_BEGIN(r);

	// Wait till the World is VALID
	CS_COROUTINE_WAIT_UNTIL(r, w);

	{
		if (gi->FullscreenWidget)
		{
			if (!gi->FullscreenWidget->IsPendingKill())
			{
				gi->FullscreenWidget->RemoveFromViewport();
				gi->FullscreenWidget->ConditionalBeginDestroy();
			}
		}

		if (ACsData_UI_Common* bp_ui_common = Cast<ACsData_UI_Common>(gi->DataMapping->LoadData(FName("bp_ui_common"))))
		{
			gi->FullscreenWidget = CreateWidget<UCsUserWidget>(gi, bp_ui_common->FullscreenWidget.Get());
			gi->FullscreenWidget->AddToViewport();
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsGameInstance::CreateFullscreenWidget_Internal: Failed to Load bp_ui_common (ACsData_UI_Common)."));
		}
	}

	CS_COROUTINE_END(r);
}

void UCsGameInstance::CheckFullscreenWidget()
{
	// Make sure FullscreenWidget is attached to Viewport
	if (FullscreenWidget)
	{
		if (!FullscreenWidget->GetParent() &&
			!FullscreenWidget->IsInViewport())
		{
			CreateFullscreenWidget();
		}
	}
}

#pragma endregion Fullscreen Widget

void UCsGameInstance::HideMouseCursor()
{
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const ECsCoroutineSchedule& Schedule = NCsCoroutineSchedule::Ref::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &UCsGameInstance::HideMouseCursor_Internal;
	Payload->Object			= this;
	Payload->Stop.Add(&UCsCommon::CoroutineStopCondition_CheckObject);
	Payload->Add			= &UCsGameInstance::AddRoutine;
	Payload->Remove			= &UCsGameInstance::RemoveRoutine;
	Payload->Type			= (uint8)ECsGameInstanceRoutine::HideMouseCursor_Internal;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsGameInstanceCached::Name::HideMouseCursor_Internal;
	Payload->NameAsString	= ECsGameInstanceCached::Str::HideMouseCursor_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(UCsGameInstance, HideMouseCursor_Internal)
{
	UCsGameInstance* gi		 = r->GetRObject<UCsGameInstance>();
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();

	CS_COROUTINE_BEGIN(r);

	// Wait till GEngine is VALID
	CS_COROUTINE_WAIT_UNTIL(r, GEngine);
	// Wait till GEngine->GameViewport is VALID
	CS_COROUTINE_WAIT_UNTIL(r, GEngine->GameViewport);
	// Wait till GEngine->GameViewport->Viewport is VALID
	CS_COROUTINE_WAIT_UNTIL(r, GEngine->GameViewport->Viewport);

	GEngine->GameViewport->Viewport->ShowCursor(false);

	CS_COROUTINE_END(r);
}

#pragma endregion OnBoard

// Level
#pragma region

void UCsGameInstance::OnPreWorldInitialization(UWorld* InWorld, const UWorld::InitializationValues)
{
	CreateFullscreenWidget();
}

void UCsGameInstance::OnPostWorldInitialization(UWorld* InWorld, const UWorld::InitializationValues)
{
	//CreateFullscreenWidget();
}

void UCsGameInstance::OnLevelAddedToWorld(ULevel* InLevel, UWorld* InWorld)
{
	CheckFullscreenWidget();
}

void UCsGameInstance::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	CheckFullscreenWidget();
}

void UCsGameInstance::PerformLevelTransition(const FString &Level, const FString &GameMode)
{
	LevelState = ECsLevelState::BeginTransition;

	const ECsCoroutineSchedule& Schedule = NCsCoroutineSchedule::Ref::Tick;

	CsCoroutine Function		  = &UCsGameInstance::PerformLevelTransition_Internal;
	CsCoroutineStopCondition Stop = &UCsCommon::CoroutineStopCondition_CheckObject;
	CsAddRoutine Add			  = &UCsGameInstance::AddRoutine;
	CsRemoveRoutine Remove		  = &UCsGameInstance::RemoveRoutine;
	const uint8 Type			  = (uint8)ECsGameInstanceRoutine::PerformLevelTransition_Internal;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsRoutine* R					 = Scheduler->Allocate(Schedule, Function, Stop, this, Add, Remove, Type, true, false);

	R->strings[0] = Level;
	R->strings[1] = GameMode;
	//R->floats[0] = Time;

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(UCsGameInstance, PerformLevelTransition_Internal)
{
	UCsGameInstance* gi		 = r->GetRObject<UCsGameInstance>();
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();
	UWorld* w				 = gi->GetWorld();

	UCsWidget_Fullscreen* Widget = Cast<UCsWidget_Fullscreen>(gi->FullscreenWidget);

	const float CurrentTime = w->GetTimeSeconds();
	const float StartTime	= r->startTime;

	const float Delay = 1.0f;

	CS_COROUTINE_BEGIN(r);

	// Set Screen to Black
	Widget->Fullscreen.SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 1.0f));
	// Slight delay before transitioning
	CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - StartTime > Delay);

	gi->LevelState = ECsLevelState::InTransition;

	{
		const FString Level	   = r->strings[0];
		const FString GameMode = r->strings[1];

		gi->OnServerTravel_Event.Broadcast();
#if WITH_EDITOR
		gi->OnServerTravel_ScriptEvent.Broadcast();
#endif // #if WITH_EDITOR
		w->ServerTravel(Level + TEXT("?game=") + GameMode);
	}

	CS_COROUTINE_END(r);
}

#pragma endregion Level

void UCsGameInstance::ExitGame()
{
#if WITH_EDITOR
	GEditor->RequestEndPlayMap();
#else
	FGenericPlatformMisc::RequestExit(false);
#endif // #if WITH_EDITOR
}

// Object
#pragma region

uint64 UCsGameInstance::GetUniqueObjectId()
{
	++UniqueObjectIdIndex;
	return UniqueObjectIdIndex;
}

uint64 UCsGameInstance::RegisterUniqueObject(UObject* InObject)
{
	const uint64 Id = GetUniqueObjectId();

	ObjectMap.Add(Id, InObject);

	if (AActor* Actor = Cast<AActor>(InObject))
		ActorMap.Add(Id, Actor);
	return Id;
}

void UCsGameInstance::UnregisterUniqueObject(const uint64 &Id)
{
	ObjectMap.Remove(Id);
	ActorMap.Remove(Id);
}

UObject* UCsGameInstance::GetUniqueObjectById(const uint64 &Id)
{
	return ObjectMap[Id].IsValid() ? ObjectMap[Id].Get() : nullptr;
}

UObject* UCsGameInstance::GetSafeUniqueObjectById(const uint64 &Id)
{
	if (!ObjectMap.Find(Id))
		return nullptr;
	return GetUniqueObjectById(Id);
}

AActor* UCsGameInstance::GetUniqueActorById(const uint64 &Id)
{
	return ActorMap[Id].IsValid() ? ActorMap[Id].Get() : nullptr;
}

AActor* UCsGameInstance::GetSafeUniqueActorById(const uint64 &Id)
{
	if (!ActorMap.Find(Id))
		return nullptr;
	return GetUniqueActorById(Id);
}

#pragma endregion Object