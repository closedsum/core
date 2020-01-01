// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/GameInstance.h"
#include "../Core/Public/Containers/Ticker.h"
#include "Types/CsTypes.h"
#include "Coroutine/CsTypes_Coroutine.h"
#include "CsGameInstance.generated.h"

// OnTick
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsGameInstance_OnTick, const float&, DeltaSeconds);
// OnServerTravel
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableDynEvent_CsGameInstance_OnServerTravel);
DECLARE_MULTICAST_DELEGATE(FBindableEvent_CsGameInstance_OnServerTravel);

// Enums
#pragma region

	// GameInstanceRoutine
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsGameInstanceRoutine : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsGameInstanceRoutine)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsGameInstanceRoutine)

struct CSCORE_API EMCsGameInstanceRoutine : public TCsEnumStructMap<FECsGameInstanceRoutine, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsGameInstanceRoutine, FECsGameInstanceRoutine, uint8)
};

namespace ECsGameInstanceRoutine
{
	typedef FECsGameInstanceRoutine Type;

	extern CSCORE_API const Type OnBoard_Internal;
	extern CSCORE_API const Type LoadDataMapping_Internal;
	extern CSCORE_API const Type PerformLevelTransition_Internal;
	extern CSCORE_API const Type CreateFullscreenWidget_Internal;
	extern CSCORE_API const Type HideMouseCursor_Internal;
}

#pragma endregion GameInstanceRoutine

	// GameInstanceOnBoardState
#pragma region

enum class ECsGameInstanceOnBoardState : uint8
{
	LoadDataMapping,
	FinishedLoadingDataAssets,
	FinishedPopulatingAssetReferences,
	LoadStartUpData,
	LoadScreen,
	Completed,
	ECsGameInstanceOnBoardState_MAX,
};

struct CSCORE_API EMCsGameInstanceOnBoardState : public TCsEnumMap<ECsGameInstanceOnBoardState>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsGameInstanceOnBoardState, ECsGameInstanceOnBoardState)
};

namespace NCsGameInstanceOnBoardState
{
	typedef ECsGameInstanceOnBoardState Type;

	namespace Ref
	{
		extern CSCORE_API const Type LoadDataMapping;
		extern CSCORE_API const Type FinishedLoadingDataAssets;
		extern CSCORE_API const Type FinishedPopulatingAssetReferences;
		extern CSCORE_API const Type LoadStartUpData;
		extern CSCORE_API const Type LoadScreen;
		extern CSCORE_API const Type Completed;
		extern CSCORE_API const Type ECsGameInstanceOnBoardState_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#define ECS_GAME_INSTANCE_ONBOARD_STATE_MAX NCsGameInstanceOnBoardState::MAX

#pragma endregion GameInstanceOnBoardState

#pragma endregion Enums

#define CS_INVALID_UNIQUE_OBJECT_ID NCsCached::Ref::Long_MAX

class UCsDataMapping;
class UCsEnumStructUserDefinedEnumMap;
class UCsInputSetting;
class UCsManager_Singleton;
class UCsManager_Time;
class UCsCoroutineScheduler;

UCLASS(config = Game)
class CSCORE_API UCsGameInstance : public UGameInstance
{
	GENERATED_UCLASS_BODY()

public:

	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void StartGameInstance() override;

#if WITH_EDITOR
	virtual FGameInstancePIEResult StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params) override;
#endif // #if WITH_EDITOR

#if WITH_EDITOR
	FGameInstancePIEParameters GameInstancePIEParametersCache;
#endif // #if WITH_EDITOR

// Tick
#pragma region
protected:

	/** Delegate for callbacks to Tick */
	FTickerDelegate	TickDelegate;

	/** Handle to various registered delegates */
	FDelegateHandle	TickDelegateHandle;

	virtual bool Tick(float DeltaSeconds);

public:

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnTick, const float&);

	FOnTick OnTick_Event;

	UPROPERTY(BlueprintAssignable, Category = "Tick")
	FCsGameInstance_OnTick OnTick_ScriptEvent;

#pragma endregion Tick

	uint64 CurrentGameFrame;

	bool IsSimulateInEditor();

// Routines
#pragma region
public:

	static void AddRoutine(UObject* InGameInstance, struct FCsRoutine* Routine, const uint8& Type);
	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8& Type);

	static void RemoveRoutine(UObject* InGameInstance, struct FCsRoutine* Routine, const uint8& Type);
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8& Type);

#pragma endregion Routines

// Enums
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance|Enums")
	TSoftClassPtr<UCsEnumStructUserDefinedEnumMap> EnumStructUserDefinedEnumMapClass;

	UPROPERTY(BlueprintReadOnly, Category = "Game Instance|Enums")
	UCsEnumStructUserDefinedEnumMap* EnumStructUserDefinedEnumMap;

	virtual void PopulateEnumMapsFromUserDefinedEnums();

	template<typename EnumMap>
	void PopulateEnumMapFromUserDefinedEnum(const FECsUserDefinedEnum& EnumType)
	{
		TArray<FString> Names;
		GetUserDefinedEnumNames(EnumMap::Get().GetEnumName(), EnumType, Names);
#if WITH_EDITOR
		EnumMap::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR
		AddEnumsByNameToEnumMap<EnumMap>(Names);
	}

	void GetUserDefinedEnumNames(const FString& EnumName, const FECsUserDefinedEnum& EnumType, TArray<FString>& OutNames);

	template<typename EnumMap>
	void AddEnumsByNameToEnumMap(const TArray<FString>& Names)
	{
		for (const FString& Name : Names)
		{
#if WITH_EDITOR
			EnumMap::Get().CreateSafe(Name, true);
#else
			EnumMap::Get().Create(Name, true);
#endif // #if WITH_EDITOR
		}
	}

#pragma endregion Enums

// Settings
#pragma region
public:

	void InitSettings();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Instance|Settings|Input")
	TSoftClassPtr<UCsInputSetting> InputSettingClass;

	UPROPERTY(BlueprintReadOnly, Category = "Game Instance|Settings|Input")
	UCsInputSetting* InputSetting;

	void InitInputSetting();

#pragma endregion Settings

// OnBoard
#pragma region
public:

	ECsGameInstanceOnBoardState OnBoardState;

	CS_COROUTINE_DECLARE(OnBoard)

	// Data Mapping
#pragma region
public:

	FString DataMappingAssetPath;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Instance|Data Mapping")
	TSoftClassPtr<UCsDataMapping> DataMappingClass;

	UPROPERTY(BlueprintReadOnly, Category = "Game Instance|Data Mapping")
	UCsDataMapping* DataMapping;

	bool bForcePopulateAssetReferences;

	CS_COROUTINE_DECLARE(LoadDataMapping)

	virtual void OnFinishedLoadingDataAssets(const TArray<UObject*>& LoadedAssets, const float& LoadingTime);

	void PopulateAssetReferences();
	void AsyncPopulateAssetReferences();

	UPROPERTY()
	TArray<UObject*> LoadedDataAssets;

	UPROPERTY(BlueprintReadOnly, Category = "Game Instance|Data Mapping")
	bool bHasLoadedDataMapping;

#pragma endregion Data Mapping

	// Load StartUp Data
#pragma region
public:

	virtual void LoadStartUpData();
	virtual void OnFinishedLoadingStartUpDataAssets(const TArray<UObject*>& LoadedAssets, const float& LoadingTime);

#pragma endregion Load StartUp Data

	// Fullscreen Widget
#pragma region
public:

	UPROPERTY(BlueprintReadOnly, Category = "Game Instance")
	class UCsUserWidget* FullscreenWidget;

	CS_COROUTINE_DECLARE(CreateFullscreenWidget);

	void CheckFullscreenWidget();

#pragma endregion Fullscreen Widget

	// Mouse Cursor
#pragma region
public:

	CS_COROUTINE_DECLARE(HideMouseCursor);

#pragma endregion Mouse Cursor

public:

	DECLARE_MULTICAST_DELEGATE(FOnBoardCompleted);

	FOnBoardCompleted OnBoardCompleted_Event;

#pragma endregion OnBoard

// UI
#pragma region
public:

	UPROPERTY(BlueprintReadOnly, Category = "Game Instance")
	class UCsUserWidget* SplashScreenWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Game Instance")
	class UCsUserWidget* TransitionWidget;

#pragma endregion UI

// Level
#pragma region
public:

	UPROPERTY(BlueprintReadOnly, Category = "Game Instance|Level")
	ECsLevelState LevelState;

	FDelegateHandle OnPreWorldInitializationHandle;
	void OnPreWorldInitialization(UWorld* InWorld, const UWorld::InitializationValues);
	FDelegateHandle OnPostWorldInitializationHandle;
	void OnPostWorldInitialization(UWorld* InWorld, const UWorld::InitializationValues);
	FDelegateHandle OnLevelAddedToWorldHandle;
	void OnLevelAddedToWorld(ULevel* InLevel, UWorld* InWorld);
	FDelegateHandle OnLevelRemovedFromWorldHandle;
	void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld);

	virtual void PerformLevelTransition(const FString& Level, const FString& GameMode);
	static char PerformLevelTransition_Internal(struct FCsRoutine* r);
	struct FCsRoutine* PerformLevelTransition_Internal_Routine;

	FBindableEvent_CsGameInstance_OnServerTravel OnServerTravel_Event;

	UPROPERTY(BlueprintAssignable, Category = "Game Instance|Level")
	FBindableDynEvent_CsGameInstance_OnServerTravel OnServerTravel_ScriptEvent;

#pragma endregion Level

// Exit
#pragma region
public:

	virtual void ExitGame();

#pragma endregion Exit

// Object
#pragma region
public:

	UPROPERTY()
	uint64 UniqueObjectIdIndex;

	uint64 GetUniqueObjectId();

	TMap<uint64, TWeakObjectPtr<UObject>> ObjectMap;
	TMap<uint64, TWeakObjectPtr<AActor>> ActorMap;

	uint64 RegisterUniqueObject(UObject* InObject);
	void UnregisterUniqueObject(const uint64& Id);

	UObject* GetUniqueObjectById(const uint64& Id);
	template<typename T>
	T* GetUniqueObjectById(const uint64& Id)
	{
		return Cast<T>(GetUniqueObjectById(Id));
	}

	UObject* GetSafeUniqueObjectById(const uint64& Id);
	template<typename T>
	T* GetSafeUniqueObjectById(const uint64& Id)
	{
		return Cast<T>(GetSafeUniqueObjectById(Id));
	}

	AActor* GetUniqueActorById(const uint64& Id);
	template<typename T>
	T* GetUniqueActorById(const uint64& Id)
	{
		return Cast<T>(GetUniqueActorById(Id));
	}

	AActor* GetSafeUniqueActorById(const uint64& Id);
	template<typename T>
	T* GetSafeUniqueActorById(const uint64& Id)
	{
		return Cast<T>(GetSafeUniqueActorById(Id));
	}

#pragma endregion Object

protected:

	UPROPERTY()
	UCsCoroutineScheduler* CoroutineScheduler;

// Managers
#pragma region
protected:

	UPROPERTY()
	UCsManager_Singleton* Manager_Singleton;

	UPROPERTY()
	UCsManager_Time* Manager_Time;

#pragma endregion Managers
};
