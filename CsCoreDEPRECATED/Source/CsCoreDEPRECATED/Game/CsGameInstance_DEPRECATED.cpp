// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/CsGameInstance_DEPRECATED.h"
#include "CsCoreDEPRECATED.h"
#include "CsCVars.h"

// Types
#include "Types/Enum/CsEnumStructUserDefinedEnumMap.h"
#include "Types/CsTypes_Load.h"
#include "Managers/Input/CsTypes_Input.h"
// Library
#include "Library/CsLibrary_Common.h"
// CoroutineScheduler
#include "Coroutine/CsCoroutineScheduler.h"
// Managers
#include "Managers/Load/CsManager_Load.h"
#include "Managers/Runnable/CsManager_Runnable.h"
#include "Managers/Time/CsManager_Time.h"
// Data
#include "Data/CsDataMapping.h"
#include "Data/CsData_Payload.h"
#include "Data/CsData.h"
#include "Data/CsData_UI_Common.h"
// Input
#include "Managers/Input/CsInputSetting.h"
// UI
#include "UI/CsUserWidget.h"
#include "UI/CsWidget_Fullscreen.h"

#include "Async/AsyncWork.h"

#if WITH_EDITOR
#include "Editor.h"
#endif // #if WITH_EDITOR

// Enums
#pragma region

	// GameInstanceRoutine
namespace ECsGameInstanceRoutine
{
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsGameInstanceRoutine, OnBoard_Internal);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsGameInstanceRoutine, LoadDataMapping_Internal);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsGameInstanceRoutine, PerformLevelTransition_Internal);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsGameInstanceRoutine, CreateFullscreenWidget_Internal);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsGameInstanceRoutine, HideMouseCursor_Internal);
}

	// GameInstanceOnBoardState
namespace NCsGameInstanceOnBoardState
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsGameInstanceOnBoardState, LoadDataMapping);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsGameInstanceOnBoardState, FinishedLoadingDataAssets);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsGameInstanceOnBoardState, FinishedPopulatingAssetReferences);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsGameInstanceOnBoardState, LoadStartUpData);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsGameInstanceOnBoardState, LoadScreen);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsGameInstanceOnBoardState, Completed);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsGameInstanceOnBoardState, ECsGameInstanceOnBoardState_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsGameInstanceOnBoardState_MAX;
}

#pragma endregion

// Cache
#pragma region

namespace NCsGameInstanceCached
{
	namespace Name
	{
		// Functions
		const FName OnBoard_Internal = FName("UCsGameInstance_DEPRECATED::OnBoard_Internal");
		const FName LoadDataMapping_Internal = FName("UCsGameInstance_DEPRECATED::LoadDataMapping_Internal");
		const FName PerformLevelTransition_Internal = FName("UCsGameInstance_DEPRECATED::PerformLevelTransition_Internal");
		const FName CreateFullscreenWidget_Internal = FName("UCsGameInstance_DEPRECATED::CreateFullscreenWidget_Internal");
		const FName HideMouseCursor_Internal = FName("UCsGameInstance_DEPRECATED::HideMouseCursor_Internal");
	};

	namespace Str
	{
		// Functions
		const FString OnBoard_Internal = TEXT("UCsGameInstance_DEPRECATED::OnBoard_Internal");
		const FString LoadDataMapping_Internal = TEXT("UCsGameInstance_DEPRECATED::LoadDataMapping_Internal");
		const FString PerformLevelTransition_Internal = TEXT("UCsGameInstance_DEPRECATED::PerformLevelTransition_Internal");
		const FString CreateFullscreenWidget_Internal = TEXT("UCsGameInstance_DEPRECATED::CreateFullscreenWidget_Internal");
		const FString HideMouseCursor_Internal = TEXT("UCsGameInstance_DEPRECATED::HideMouseCursor_Internal");
	};
}

#pragma endregion Cache

UCsGameInstance_DEPRECATED::UCsGameInstance_DEPRECATED(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentGameFrame = 0;

#if WITH_EDITOR
	bForcePopulateAssetReferences = true;
#endif // #if WITH_EDITOR

	DataMappingAssetPath = TEXT("/Game/AlwaysCook/bp_data_mapping.bp_data_mapping_C");
	DataMapping			 = nullptr;

	OnBoardState = ECsGameInstanceOnBoardState::LoadDataMapping;
	LevelState   = ECsLevelState::None;
}

void UCsGameInstance_DEPRECATED::Init()
{
	Super::Init();

	// Register delegate for ticker callback
	TickDelegate	   = FTickerDelegate::CreateUObject(this, &UCsGameInstance_DEPRECATED::Tick);
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);

	OnPreWorldInitializationHandle	= FWorldDelegates::OnPreWorldInitialization.AddUObject(this, &UCsGameInstance_DEPRECATED::OnPreWorldInitialization);
	OnPostWorldInitializationHandle = FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UCsGameInstance_DEPRECATED::OnPostWorldInitialization);
	OnLevelAddedToWorldHandle		= FWorldDelegates::LevelAddedToWorld.AddUObject(this, &UCsGameInstance_DEPRECATED::OnLevelAddedToWorld);
	OnLevelRemovedFromWorldHandle	= FWorldDelegates::LevelRemovedFromWorld.AddUObject(this, &UCsGameInstance_DEPRECATED::OnLevelRemovedFromWorld);
	
	ConstructManagerSingleton();

	//InitSettings();
	//PopulateEnumMapsFromUserDefinedEnums();

	UCsManager_Time::Init(this);
	UCsCoroutineScheduler::Init(this);
	UCsManager_Load::Init(this);
	UCsManager_Runnable::Init();

#if WITH_EDITOR
	Manager_Time = UCsManager_Time::Get(this);
	CoroutineScheduler = UCsCoroutineScheduler::Get(this);
#endif // #if WITH_EDITOR
	
	//OnTick_Event.AddUObject(UCsCoroutineScheduler::Get(), &UCsCoroutineScheduler::OnTick_Update);
	
	//HideMouseCursor();
	//OnBoard();
}

void UCsGameInstance_DEPRECATED::Shutdown()
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


	UCsManager_Time::Shutdown(this);
	UCsCoroutineScheduler::Shutdown(this);
	UCsManager_Load::Shutdown(this);
	UCsManager_Runnable::Shutdown();

#if WITH_EDITOR
	Manager_Time->MarkPendingKill();
	Manager_Time = nullptr;

	CoroutineScheduler->MarkPendingKill();
	CoroutineScheduler = nullptr;
#endif // #if WITH_EDITOR
}

void UCsGameInstance_DEPRECATED::StartGameInstance()
{
	Super::StartGameInstance();
}

#if WITH_EDITOR

FGameInstancePIEResult UCsGameInstance_DEPRECATED::StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params)
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

bool UCsGameInstance_DEPRECATED::Tick(float DeltaSeconds)
{
	++CurrentGameFrame;

	const FECsUpdateGroup& Group = NCsUpdateGroup::GameInstance;

	UCsManager_Time::Get(this)->Update(Group, DeltaSeconds);

	const FCsDeltaTime& DeltaTime = UCsManager_Time::Get(this)->GetScaledDeltaTime(Group);

	UCsCoroutineScheduler::Get(this)->Update(Group, DeltaTime);

	OnTick_Event.Broadcast(DeltaSeconds);
#if WITH_EDITOR
	OnTick_ScriptEvent.Broadcast(DeltaSeconds);
#endif // #if WITH_EDITOR
	return true;
}

#pragma endregion Tick

bool UCsGameInstance_DEPRECATED::IsSimulateInEditor()
{
#if WITH_EDITOR
	return GameInstancePIEParametersCache.bSimulateInEditor;
#else
	return false;
#endif // #if WITH_EDITOR
}

// Routines
#pragma region

/*static*/ void UCsGameInstance_DEPRECATED::AddRoutine(UObject* InGameInstance, struct FCsRoutine* Routine, const uint8& Type)
{
	Cast<UCsGameInstance_DEPRECATED>(InGameInstance)->AddRoutine_Internal(Routine, Type);
}

bool UCsGameInstance_DEPRECATED::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8& Type)
{
	const FECsGameInstanceRoutine RoutineType = EMCsGameInstanceRoutine::Get()[Type];

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

/*static*/ void UCsGameInstance_DEPRECATED::RemoveRoutine(UObject* InGameInstance, struct FCsRoutine* Routine, const uint8& Type)
{
	Cast<UCsGameInstance_DEPRECATED>(InGameInstance)->RemoveRoutine_Internal(Routine, Type);
}

bool UCsGameInstance_DEPRECATED::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8& Type)
{
	const FECsGameInstanceRoutine RoutineType = EMCsGameInstanceRoutine::Get()[Type];

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

// Enums
#pragma region

void UCsGameInstance_DEPRECATED::PopulateEnumMapsFromUserDefinedEnums()
{ 
	// Check AssetReference Path set for EnumStructUserDefinedEnumMapClass
	FString Path = EnumStructUserDefinedEnumMapClass.ToString();

	checkf(Path != NCsCached::Str::Empty, TEXT("UCsGameInstance_DEPRECATED::GetUserDefinedEnumNames: No valid Asset Path set for EnumStructUserDefinedEnumMapClass."));

	// Check EnumStructUserDefinedEnumMapClass points to a valid cooked object
	UClass* Class = EnumStructUserDefinedEnumMapClass.LoadSynchronous();

	checkf(Class, TEXT("UCsGameInstance_DEPRECATED::GetUserDefinedEnumNames: Failed to load EnumStructUserDefinedEnumMapClass at Path: %s."), *Path);

	// Check there is a Default Object for EnumStructUserDefinedEnumMapClass
	EnumStructUserDefinedEnumMap = Class->GetDefaultObject<UCsEnumStructUserDefinedEnumMap>();

	checkf(EnumStructUserDefinedEnumMap, TEXT("UCsGameInstance_DEPRECATED::GetUserDefinedEnumNames: Failed to get the Default Object for Class: %s at Path: %s."), *(Class->GetName()), *Path);

	// DataType
	PopulateEnumMapFromUserDefinedEnum<EMCsDataType>(NCsUserDefinedEnum::FECsDataType);
	// DataCollection
	PopulateEnumMapFromUserDefinedEnum<EMCsDataCollectionType>(NCsUserDefinedEnum::FECsDataCollectionType);
	// Input
	{
		// InputAction
		PopulateEnumMapFromUserDefinedEnum<EMCsInputAction>(NCsUserDefinedEnum::FECsInputAction);
		// InputActionMap
		PopulateEnumMapFromUserDefinedEnum<EMCsInputActionMap>(NCsUserDefinedEnum::FECsInputActionMap);
		// GameEvent
		PopulateEnumMapFromUserDefinedEnum<EMCsGameEvent>(NCsUserDefinedEnum::FECsGameEvent);
	}
}

void UCsGameInstance_DEPRECATED::GetUserDefinedEnumNames(const FString& EnumName, const FECsUserDefinedEnum& EnumType, TArray<FString>& OutNames)
{
	if (UUserDefinedEnum* Enum = EnumStructUserDefinedEnumMap->GetUserDefinedEnum(EnumType))
	{
		const int32 Count = Enum->NumEnums() - 1;

		for (int32 I = 0; I < Count; ++I)
		{
			OutNames.Add(Enum->GetDisplayNameTextByIndex(I).ToString());
		}
	}
	else
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsGameInstance_DEPRECATED::GetUserDefinedEnumNames: Failed to find UserDefinedEnum: %s for EnumStruct: %s."), *(EnumType.Name), *EnumName);
	}
}

#pragma endregion Enums

// Settings
#pragma region

void UCsGameInstance_DEPRECATED::InitSettings()
{
	InitInputSetting();
}

void UCsGameInstance_DEPRECATED::InitInputSetting()
{
	// Check AssetReference Path set for InputSettingClass
	FString Path = InputSettingClass.ToString();

	checkf(Path != NCsCached::Str::Empty, TEXT("UCsGameInstance_DEPRECATED::InitInputSetting: No valid Asset Path set for InputSettingClass."));

	// Check InputSettingClass points to a valid cooked object
	UClass* Class = InputSettingClass.LoadSynchronous();

	checkf(Class, TEXT("UCsGameInstance_DEPRECATED::InitInputSetting: Failed to load InputSettingClass at Path: %s."), *Path);

	// Check there is a Default Object for InputSettingClass
	InputSetting = Class->GetDefaultObject<UCsInputSetting>();

	checkf(InputSetting, TEXT("UCsGameInstance_DEPRECATED::InitInputSetting: Failed to get the Default Object for Class: %s at Path: %s."), *(Class->GetName()), *Path);

}

#pragma endregion Settings

// OnBoard
#pragma region

void UCsGameInstance_DEPRECATED::OnBoard()
{
	const FECsUpdateGroup& Group = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(this);
	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&UCsGameInstance_DEPRECATED::OnBoard_Internal);
	Payload->StartTime = UCsManager_Time::Get(this)->GetTime(Group);
	Payload->Owner.SetObject(this);

	Scheduler->Start(Payload);
}

CS_COROUTINE(UCsGameInstance_DEPRECATED, OnBoard_Internal)
{
	UCsGameInstance_DEPRECATED* gi = r->GetOwnerAsObject<UCsGameInstance_DEPRECATED>();

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

void UCsGameInstance_DEPRECATED::LoadDataMapping()
{
	const FStringAssetReference AssetRef		  = FStringAssetReference(DataMappingAssetPath);
	TSoftClassPtr<UCsDataMapping> AssetSubclassOf = TSoftClassPtr<UCsDataMapping>(AssetRef);

	if (UClass* DataClass = AssetSubclassOf.LoadSynchronous())
	{
		DataMapping = DataClass->GetDefaultObject<UCsDataMapping>();
#if WITH_EDITOR

		checkf(DataMapping->IsValid(), TEXT("UCsGameInstance_DEPRECATED::LoadDataMapping: DataMapping is NOT Valid."));

		DataMapping->LoadFromJson();
		DataMapping->ClearLoaded();
		DataMapping->PopulateDataAssetReferences();
#endif // #if WITH_EDITOR
	}
	else
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsGameInstance_DEPRECATED::Init: Failed to Load DataMapping asset."));
		return;
	}

	const FECsUpdateGroup& Group = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(this);
	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&UCsGameInstance_DEPRECATED::LoadDataMapping_Internal);
	Payload->StartTime = UCsManager_Time::Get(this)->GetTime(Group);
	Payload->Owner.SetObject(this);

	Scheduler->Start(Payload);
}

PT_THREAD(UCsGameInstance_DEPRECATED::LoadDataMapping_Internal(FCsRoutine* R))
{
	UCsGameInstance_DEPRECATED* gi			= R->GetOwnerAsObject<UCsGameInstance_DEPRECATED>();
	UCsDataMapping* dataMapping = gi->DataMapping;

	CS_COROUTINE_BEGIN(R);

	if (gi->bForcePopulateAssetReferences || dataMapping->bForcePopulateAssetReferences)
	{
		//UCsManager_Load::Get()->LoadObjectPaths(gi->GetWorld(), dataMapping->DataAssetReferences, ECsLoadAsyncOrder::Bulk, FCsManagerLoad_OnFinishLoadObjectPaths::CreateUObject(gi, &UCsGameInstance_DEPRECATED::OnFinishedLoadingDataObjects));

		// Wait until Data Assets are LOADED
		CS_COROUTINE_WAIT_UNTIL(R, gi->OnBoardState == ECsGameInstanceOnBoardState::FinishedLoadingDataAssets);

#if WITH_EDITOR
		CS_COROUTINE_WAIT_UNTIL(R, !dataMapping->AsyncTaskMutex.IsLocked());
#endif // #if WITH_EDITOR

		if (UCsLibrary_Common::CanAsyncTask())
		{
			gi->AsyncPopulateAssetReferences();
		}
		else
		{
			gi->PopulateAssetReferences();
		}
		// Wait until ALL Asset References
		CS_COROUTINE_WAIT_UNTIL(R, gi->OnBoardState == ECsGameInstanceOnBoardState::FinishedPopulatingAssetReferences);
	}

#if WITH_EDITOR
	{
		UCsData_Payload* Payload = dataMapping->GetPayload();

		checkf(Payload->Editor_IsValid(dataMapping), TEXT("UCsGameInstance_DEPRECATED::LoadDataMapping_Internal: Payload is NOT Valid."));
	}
#endif // #if WITH_EDITOR

	dataMapping->GenerateMaps();

#if WITH_EDITOR
	dataMapping->AsyncTaskMutex.Unlock();
#endif // #if WITH_EDITOR

	gi->bHasLoadedDataMapping = true;
	gi->OnBoardState = ECsGameInstanceOnBoardState::LoadStartUpData;

	CS_COROUTINE_END(R);
}

void UCsGameInstance_DEPRECATED::OnFinishedLoadingDataObjects(const TArray<UObject*>& LoadedObjects, const float& LoadingTime)
{
	for (UObject* Object : LoadedObjects)
	{
		LoadedDataObjects.Add(Object);
	}
	OnBoardState = ECsGameInstanceOnBoardState::FinishedLoadingDataAssets;
}

void UCsGameInstance_DEPRECATED::PopulateAssetReferences()
{
	// TODO: Maybe time slice this for built game 
	const int32 Count = LoadedDataObjects.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		UObject* DataAsObject = Cast<UBlueprintGeneratedClass>(LoadedDataObjects[I])->GetDefaultObject();
		ICsData* Data		  = Cast<ICsData>(DataAsObject);

		//Data->LoadFromJson();
		//Data->PopulateAssetReferences(false);
	}
	DataMapping->PopulateAssetReferences();
	LoadedDataObjects.Reset(LoadedDataObjects.Max());

	OnBoardState = ECsGameInstanceOnBoardState::FinishedPopulatingAssetReferences;
}

void UCsGameInstance_DEPRECATED::AsyncPopulateAssetReferences()
{
#if WITH_EDITOR
	DataMapping->AsyncTaskMutex.Lock();
#endif // #if WITH_EDITOR

	UCsManager_Runnable* Manager_Runnable = UCsManager_Runnable::Get();

	FCsRunnablePayload* Payload = Manager_Runnable->AllocatePayload();
	Payload->Owner				= this;
	Payload->ThreadPriority		= EThreadPriority::TPri_Normal;

	FCsRunnable_Delegate* Runnable = Manager_Runnable->Prep(Payload);
	Runnable->Delegate.AddUObject(this, &UCsGameInstance_DEPRECATED::PopulateAssetReferences);
	Runnable->Start();
}

/*
void UCsGameInstance_DEPRECATED::AsyncPopulateAssetReferences()
{
	class FAsyncPopulateAssetReferencesWorker : public FNonAbandonableTask
	{
	public:

		friend class FAutoDeleteAsyncTask<FAsyncPopulateAssetReferencesWorker>;

		UCsGameInstance_DEPRECATED* GameInstance;

		FAsyncPopulateAssetReferencesWorker(UCsGameInstance_DEPRECATED* InGameInstance)
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

void UCsGameInstance_DEPRECATED::LoadStartUpData(){ OnBoardState = ECsGameInstanceOnBoardState::LoadScreen; }
void UCsGameInstance_DEPRECATED::OnFinishedLoadingStartUpDataAssets(const TArray<UObject*>& LoadedAssets, const float& LoadingTime){}

#pragma endregion Load StartUp Data

	// Fullscreen Widget
#pragma region

void UCsGameInstance_DEPRECATED::CreateFullscreenWidget()
{
	const FECsUpdateGroup& Group = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(this);
	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&UCsGameInstance_DEPRECATED::CreateFullscreenWidget_Internal);
	Payload->StartTime = UCsManager_Time::Get(this)->GetTime(Group);
	Payload->Owner.SetObject(this);

	Payload->SetName(NCsGameInstanceCached::Name::CreateFullscreenWidget_Internal);
	Payload->SetNameAsString(NCsGameInstanceCached::Str::CreateFullscreenWidget_Internal);

	Scheduler->Start(Payload);
}

CS_COROUTINE(UCsGameInstance_DEPRECATED, CreateFullscreenWidget_Internal)
{
	UCsGameInstance_DEPRECATED* gi = r->GetOwnerAsObject<UCsGameInstance_DEPRECATED>();
	UWorld* w			= gi->GetWorld();

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

		const FCsData& Data = gi->DataMapping->LoadData(FName("bp_ui_common"));

		if (UCsData_UI_Common* bp_ui_common = Data.GetObject<UCsData_UI_Common>())
		{
			gi->FullscreenWidget = CreateWidget<UCsUserWidget>(gi, bp_ui_common->FullscreenWidget.Get());
			gi->FullscreenWidget->AddToViewport();
		}
		else
		{
			UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsGameInstance_DEPRECATED::CreateFullscreenWidget_Internal: Failed to Load bp_ui_common (UCsData_UI_Common)."));
		}
	}

	CS_COROUTINE_END(r);
}

void UCsGameInstance_DEPRECATED::CheckFullscreenWidget()
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

void UCsGameInstance_DEPRECATED::HideMouseCursor()
{
	const FECsUpdateGroup& Group = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(this);
	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&UCsGameInstance_DEPRECATED::HideMouseCursor_Internal);
	Payload->StartTime = UCsManager_Time::Get(this)->GetTime(Group);
	Payload->Owner.SetObject(this);

	Payload->SetName(NCsGameInstanceCached::Name::HideMouseCursor_Internal);
	Payload->SetNameAsString(NCsGameInstanceCached::Str::HideMouseCursor_Internal);

	Scheduler->Start(Payload);
}

CS_COROUTINE(UCsGameInstance_DEPRECATED, HideMouseCursor_Internal)
{
	UCsGameInstance_DEPRECATED* gi = r->GetOwnerAsObject<UCsGameInstance_DEPRECATED>();

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

void UCsGameInstance_DEPRECATED::OnPreWorldInitialization(UWorld* InWorld, const UWorld::InitializationValues)
{
	CreateFullscreenWidget();
}

void UCsGameInstance_DEPRECATED::OnPostWorldInitialization(UWorld* InWorld, const UWorld::InitializationValues)
{
	//CreateFullscreenWidget();
}

void UCsGameInstance_DEPRECATED::OnLevelAddedToWorld(ULevel* InLevel, UWorld* InWorld)
{
	CheckFullscreenWidget();
}

void UCsGameInstance_DEPRECATED::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	CheckFullscreenWidget();
}

void UCsGameInstance_DEPRECATED::PerformLevelTransition(const FString& Level, const FString& GameMode)
{
	LevelState = ECsLevelState::BeginTransition;

	const FECsUpdateGroup& Group = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(this);
	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&UCsGameInstance_DEPRECATED::PerformLevelTransition_Internal);
	Payload->StartTime = UCsManager_Time::Get(this)->GetTime(Group);
	Payload->Owner.SetObject(this);

	static const int32 LEVEL_INDEX = 0;
	Payload->SetValue_String(LEVEL_INDEX, Level);

	static const int32 GAME_MODE_INDEX = 1;
	Payload->SetValue_String(GAME_MODE_INDEX, GameMode);
	//R->floats[0] = Time;

	Scheduler->Start(Payload);
}

CS_COROUTINE(UCsGameInstance_DEPRECATED, PerformLevelTransition_Internal)
{
	UCsGameInstance_DEPRECATED* gi = r->GetOwnerAsObject<UCsGameInstance_DEPRECATED>();
	UWorld* w			= gi->GetWorld();

	UCsWidget_Fullscreen* Widget = Cast<UCsWidget_Fullscreen>(gi->FullscreenWidget);

	const FCsTime& CurrentTime = UCsManager_Time::Get(gi)->GetTime(r->Group);
	const FCsTime& StartTime   = r->StartTime;

	const float Delay = 1.0f;

	CS_COROUTINE_BEGIN(r);

	// Set Screen to Black
	Widget->Fullscreen.SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 1.0f));
	// Slight delay before transitioning
	CS_COROUTINE_WAIT_UNTIL(r, CurrentTime.Time - StartTime.Time > Delay);

	gi->LevelState = ECsLevelState::InTransition;

	{
		static const int32 LEVEL_INDEX = 0;
		const FString& Level = r->GetValue_String(LEVEL_INDEX);

		static const int32 GAME_MODE_INDEX = 1;
		const FString& GameMode = r->GetValue_String(GAME_MODE_INDEX);

		gi->OnServerTravel_Event.Broadcast();
#if WITH_EDITOR
		gi->OnServerTravel_ScriptEvent.Broadcast();
#endif // #if WITH_EDITOR
		w->ServerTravel(Level + TEXT("?game=") + GameMode);
	}

	CS_COROUTINE_END(r);
}

#pragma endregion Level

void UCsGameInstance_DEPRECATED::ExitGame()
{
#if WITH_EDITOR
	GEditor->RequestEndPlayMap();
#else
	FGenericPlatformMisc::RequestExit(false);
#endif // #if WITH_EDITOR
}

// Object
#pragma region

uint64 UCsGameInstance_DEPRECATED::GetUniqueObjectId()
{
	++UniqueObjectIdIndex;
	return UniqueObjectIdIndex;
}

uint64 UCsGameInstance_DEPRECATED::RegisterUniqueObject(UObject* InObject)
{
	const uint64 Id = GetUniqueObjectId();

	ObjectMap.Add(Id, InObject);

	if (AActor* Actor = Cast<AActor>(InObject))
		ActorMap.Add(Id, Actor);
	return Id;
}

void UCsGameInstance_DEPRECATED::UnregisterUniqueObject(const uint64& Id)
{
	ObjectMap.Remove(Id);
	ActorMap.Remove(Id);
}

UObject* UCsGameInstance_DEPRECATED::GetUniqueObjectById(const uint64& Id)
{
	return ObjectMap[Id].IsValid() ? ObjectMap[Id].Get() : nullptr;
}

UObject* UCsGameInstance_DEPRECATED::GetSafeUniqueObjectById(const uint64& Id)
{
	if (!ObjectMap.Find(Id))
		return nullptr;
	return GetUniqueObjectById(Id);
}

AActor* UCsGameInstance_DEPRECATED::GetUniqueActorById(const uint64& Id)
{
	return ActorMap[Id].IsValid() ? ActorMap[Id].Get() : nullptr;
}

AActor* UCsGameInstance_DEPRECATED::GetSafeUniqueActorById(const uint64& Id)
{
	if (!ActorMap.Find(Id))
		return nullptr;
	return GetUniqueActorById(Id);
}

#pragma endregion Object

// Managers
#pragma region

void UCsGameInstance_DEPRECATED::ConstructManagerSingleton(){}

#pragma endregion Managers
