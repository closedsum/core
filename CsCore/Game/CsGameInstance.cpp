// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/CsGameInstance.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Managers/CsManager_Loading.h"
#include "Coroutine/CsCoroutineScheduler.h"
// Data
#include "Data/CsDataMapping.h"
#include "Data/CsData.h"
#include "Data/CsData_UI_Common.h"
// UI
#include "UI/CsUserWidget.h"

UCsGameInstance::UCsGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DataMappingAssetPath = TEXT("/Game/AlwaysCook/bp_data_mapping.bp_data_mapping_C");
	DataMapping			 = nullptr;

	LevelState = ECsLevelState::None;

	ResetCVars();
}

void UCsGameInstance::ResetCVars()
{
	// Loading
	//CsCVarLogManagerLoading->Set(CS_CVAR_HIDE_LOG, ECVF_SetByConsole);
}

void UCsGameInstance::Init()
{
	Super::Init();

	// Register delegate for ticker callback
	TickDelegate	   = FTickerDelegate::CreateUObject(this, &UCsGameInstance::Tick);
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);

	UCsManager_Loading::Init();
	UCsCoroutineScheduler::Init();
	LoadDataMapping();

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
	return false;
}

#pragma endregion Routines

// OnBoard
#pragma region

void UCsGameInstance::OnBoard()
{
	CsCoroutine Function		  = &UCsGameInstance::OnBoard_Internal;
	CsCoroutineStopCondition Stop = &UCsCommon::CoroutineStopCondition_CheckActor;
	CsAddRoutine Add			  = &UCsGameInstance::AddRoutine;
	CsRemoveRoutine Remove		  = &UCsGameInstance::RemoveRoutine;
	const uint8 Type			  = (uint8)ECsGameInstanceRoutine::OnBoard_Internal;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsRoutine* R					 = Scheduler->Allocate(Function, Stop, this, Add, Remove, Type, true, false);

	Scheduler->StartRoutine(R);
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
		DataMapping->LoadFromJson();
		DataMapping->PopulateDataAssetReferences();
#endif // #if WITH_EDITOR
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsGameInstance::Init: Failed to Load DataMapping asset."));
		return;
	}

	CsCoroutine Function		  = &UCsGameInstance::LoadDataMapping_Internal;
	CsCoroutineStopCondition Stop = &UCsCommon::CoroutineStopCondition_CheckObject;
	CsAddRoutine Add			  = &UCsGameInstance::AddRoutine;
	CsRemoveRoutine Remove		  = &UCsGameInstance::RemoveRoutine;
	const uint8 Type			  = (uint8)ECsGameInstanceRoutine::LoadDataMapping_Internal;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsRoutine* R					 = Scheduler->Allocate(Function, Stop, this, Add, Remove, Type, true, false);

	Scheduler->StartRoutine(R);
}

PT_THREAD(UCsGameInstance::LoadDataMapping_Internal(struct FCsRoutine* r))
{
	UCsGameInstance* gi			= Cast<UCsGameInstance>(r->GetRObject());
	UCsCoroutineScheduler* s	= r->scheduler;
	ACsDataMapping* dataMapping = gi->DataMapping;

	CS_COROUTINE_BEGIN(r);

	if (!gi->ForcePopulateAssetReferences || !dataMapping->ForcePopulateAssetReferences)
	{
		UCsManager_Loading::Get()->LoadAssetReferences(gi->GetWorld(), dataMapping->DataAssetReferences, ECsLoadAsyncOrder::Bulk, gi, &UCsGameInstance::OnFinishedLoadingDataAssets);

		// Wait until Data Assets are LOADED
		CS_COROUTINE_WAIT_UNTIL(r, gi->HasLoadedDataAssets);

		// TODO: Maybe time slice this for built game 
		{
			const int32 Count = gi->LoadedDataAssets.Num();

			for (int32 I = 0; I < Count; I++)
			{
				ACsData* Data = Cast<UBlueprintGeneratedClass>(gi->LoadedDataAssets[I])->GetDefaultObject<ACsData>();
				Data->LoadFromJson();
				Data->PopulateAssetReferences(false);
			}
		}
		dataMapping->PopulateAssetReferences();
		gi->LoadedDataAssets.Reset();
	}
	gi->HasLoadedDataMapping = true;
	gi->OnBoardState = ECsGameInstanceOnBoardState::LoadStartUpData;

	CS_COROUTINE_END(r);
}

void UCsGameInstance::OnFinishedLoadingDataAssets(const TArray<UObject*> &LoadedAssets, const float& LoadingTime)
{
	const int32 Count = LoadedAssets.Num();

	for (int32 I = 0; I < Count; I++)
	{
		LoadedDataAssets.Add(LoadedAssets[I]);
	}
	HasLoadedDataAssets = true;
}

#pragma endregion Data Mapping

	// Load StartUp Data
#pragma region

void UCsGameInstance::LoadStartUpData()
{
	/*
	const TCsLoadAsyncOrder AsyncOrder = UCsCommon::GetLoadAsyncOrder();

	DataMapping->AsyncLoadAssets<ACsGameState>(ECsLoadAssetsType::StartUp, AsyncOrder, this, &ACsGameState::OnFinishedLoadCommonData);
	*/
}

void UCsGameInstance::OnFinishedLoadingStartUpDataAssets(const TArray<UObject*> &LoadedAssets, const float& LoadingTime)
{
	//DataMapping->OnFinishedAsyncLoadingAssetsSetReferences(ECsLoadAssetsType::StartUp, LoadedAssets);

	OnBoardState = ECsGameInstanceOnBoardState::Completed;
}

#pragma endregion Load StartUp Data

	// Fullscreen Widget
#pragma region

void UCsGameInstance::SetupFullscreenWidget()
{
	if (!FullscreenWidget)
	{
		ACsData_UI_Common* bp_ui_common = Cast<ACsData_UI_Common>(DataMapping->LoadData(FName("bp_ui_common")));
		FullscreenWidget			    = CreateWidget<UCsUserWidget>(this, bp_ui_common->FullscreenWidget.Get());
	}
	FullscreenWidget->Show();
}

#pragma endregion Fullscreen Widget

#pragma endregion OnBoard