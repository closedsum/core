// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/CsGameInstance.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"
#include "Managers/CsManager_Loading.h"
#include "Coroutine/CsCoroutineScheduler.h"
// Data
#include "Data/CsDataMapping.h"
#include "Data/CsData_Payload.h"
#include "Data/CsData.h"
#include "Data/CsData_UI_Common.h"
// UI
#include "UI/CsUserWidget.h"
#include "UI/CsWidget_Fullscreen.h"

#include "Async/AsyncWork.h"

UCsGameInstance::UCsGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
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

	UCsManager_Loading::Init();
	UCsCoroutineScheduler::Init();
	OnBoard();

	IsVR = GEngine->HMDDevice.IsValid() && GEngine->IsStereoscopic3D();
}

void UCsGameInstance::Shutdown()
{
	Super::Shutdown();

	// Unregister ticker delegate
	FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);

	UCsManager_Loading::Shutdown();
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
	return false;
}

#pragma endregion Routines

// OnBoard
#pragma region

void UCsGameInstance::OnBoard()
{
	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

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
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w				 = gi->GetWorld();

	CS_COROUTINE_BEGIN(r);

	gi->LoadDataMapping();

	CS_COROUTINE_WAIT_UNTIL(r, gi->OnBoardState == ECsGameInstanceOnBoardState::LoadStartUpData);

	gi->LoadStartUpData();

	// Wait till the World is VALID
	CS_COROUTINE_WAIT_UNTIL(r, w);

	gi->SetupFullscreenWidget();

	FWorldDelegates::LevelAddedToWorld.AddUObject(gi, &UCsGameInstance::OnLevelAddedToWorld);
	FWorldDelegates::LevelRemovedFromWorld.AddUObject(gi, &UCsGameInstance::OnLevelRemovedFromWorld);

	CS_COROUTINE_WAIT_UNTIL(r, gi->OnBoardState == ECsGameInstanceOnBoardState::Completed);

	CS_COROUTINE_END(r);
}

	// Data Mapping
#pragma region

void UCsGameInstance::LoadDataMapping()
{
	const FStringAssetReference AssetRef			 = FStringAssetReference(DataMappingAssetPath);
	TAssetSubclassOf<ACsDataMapping> AssetSubclassOf = TAssetSubclassOf<ACsDataMapping>(AssetRef);

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

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

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
	UCsCoroutineScheduler* s	= r->scheduler;
	ACsDataMapping* dataMapping = gi->DataMapping;

	CS_COROUTINE_BEGIN(r);

	if (gi->ForcePopulateAssetReferences || dataMapping->ForcePopulateAssetReferences)
	{
		UCsManager_Loading::Get()->LoadAssetReferences(gi->GetWorld(), dataMapping->DataAssetReferences, ECsLoadAsyncOrder::Bulk, gi, &UCsGameInstance::OnFinishedLoadingDataAssets);

		// Wait until Data Assets are LOADED
		CS_COROUTINE_WAIT_UNTIL(r, gi->OnBoardState == ECsGameInstanceOnBoardState::FinishedLoadingDataAssets);

#if WITH_EDITOR
		CS_COROUTINE_WAIT_UNTIL(r, !dataMapping->AsyncTaskMutex);
#endif // #if WITH_EDITOR

		if (UCsCommon::CanAsyncTask())
		{
#if WITH_EDITOR
			dataMapping->AsyncTaskMutex = true;
#endif // #if WITH_EDITOR

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
	dataMapping->AsyncTaskMutex = false;
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

#pragma endregion Data Mapping

	// Load StartUp Data
#pragma region

void UCsGameInstance::LoadStartUpData(){}
void UCsGameInstance::OnFinishedLoadingStartUpDataAssets(const TArray<UObject*> &LoadedAssets, const float& LoadingTime){}

#pragma endregion Load StartUp Data

	// Fullscreen Widget
#pragma region

void UCsGameInstance::SetupFullscreenWidget()
{
	if (!FullscreenWidget)
	{
		ACsData_UI_Common* bp_ui_common = Cast<ACsData_UI_Common>(DataMapping->LoadData(FName("bp_ui_common")));

		if (!bp_ui_common)
		{
			UE_LOG(LogCs, Warning, TEXT("UCsGameInstance::SetupFullscreenWidget: Failed to Load bp_ui_common (ACsData_UI_Common)."));
			return;
		}
		FullscreenWidget = CreateWidget<UCsUserWidget>(this, bp_ui_common->FullscreenWidget.Get());
		FullscreenWidget->AddToViewport();
	}
	FullscreenWidget->Show();

	OnBoardState = ECsGameInstanceOnBoardState::Completed;
}

#pragma endregion Fullscreen Widget

#pragma endregion OnBoard

// Level
#pragma region

void UCsGameInstance::OnLevelAddedToWorld(ULevel* InLevel, UWorld* InWorld)
{
	// Make sure FullscreenWidget is attached to Viewport
	if (FullscreenWidget &&
		!FullscreenWidget->GetParent() &&
		!FullscreenWidget->IsInViewport())
	{
		FullscreenWidget->AddToViewport();
	}
}

void UCsGameInstance::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	// Make sure FullscreenWidget is attached to Viewport
	if (FullscreenWidget &&
		!FullscreenWidget->GetParent() &&
		!FullscreenWidget->IsInViewport())
	{
		FullscreenWidget->AddToViewport();
	}
}

void UCsGameInstance::PerformLevelTransition(const FString &Level, const FString &GameMode)
{
	LevelState = ECsLevelState::BeginTransition;

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

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
	UCsGameInstance* gi		 = Cast<UCsGameInstance>(r->GetRObject());
	UCsCoroutineScheduler* s = r->scheduler;
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

		w->ServerTravel(Level + TEXT("?game=") + GameMode);
	}

	CS_COROUTINE_END(r);
}

#pragma endregion Level