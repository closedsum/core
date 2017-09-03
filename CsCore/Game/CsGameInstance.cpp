// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/CsGameInstance.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Managers/CsManager_Loading.h"
#include "Coroutine/CsCoroutineScheduler.h"
#include "Data/CsDataMapping.h"
#include "Data/CsData.h"

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
	CsCVarLogManagerLoading->Set(CS_CVAR_HIDE_LOG, ECVF_SetByConsole);
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

// Data Mapping
#pragma region

void UCsGameInstance::LoadDataMapping()
{
	const FStringAssetReference AssetRef			 = FStringAssetReference(DataMappingAssetPath);
	TAssetSubclassOf<ACsDataMapping> AssetSubclassOf = TAssetSubclassOf<ACsDataMapping>(AssetRef);

	if (UClass* DataClass = AssetSubclassOf.LoadSynchronous())
	{
		DataMapping = DataClass->GetDefaultObject<ACsDataMapping>();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsGameInstance::Init: Failed to Load DataMapping asset."));
		return;
	}

	CsCoroutine Function		 = &UCsGameInstance::LoadDataMapping_Internal;
	CsCoroutineStopCondition Stop = &UCsCommon::CoroutineStopCondition_CheckObject;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsRoutine* R					 = Scheduler->Allocate(Function, Stop, this, true, false);

	Scheduler->StartRoutine(R);
}

PT_THREAD(UCsGameInstance::LoadDataMapping_Internal(struct FCsRoutine* r))
{
	UCsGameInstance* gi			= Cast<UCsGameInstance>(r->GetRObject());
	UCsCoroutineScheduler* s	= r->scheduler;
	ACsDataMapping* dataMapping = gi->DataMapping;

	CS_COROUTINE_BEGIN(r);

	// Wait until the World is VALID
	CS_COROUTINE_WAIT_UNTIL(r, gi->GetWorld());

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