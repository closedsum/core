// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/GameInstance.h"
#include "../Core/Public/Containers/Ticker.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_Coroutine.h"
#include "CsGameInstance.generated.h"

// OnTick
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsGameInstance_OnTick, const float&, DeltaSeconds);
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

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsGameInstanceRoutine& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsGameInstanceRoutine : public TCsEnumStructMap<FECsGameInstanceRoutine, uint8>
{
	CS_DECLARE_ENUM_STRUCT_MAP_BODY(EMCsGameInstanceRoutine)
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

namespace ECsGameInstanceOnBoardState
{
	enum Type
	{
		LoadDataMapping,
		FinishedLoadingDataAssets,
		FinishedPopulatingAssetReferences,
		LoadStartUpData,
		LoadScreen,
		Completed,
		ECsGameInstanceOnBoardState_MAX,
	};
}

namespace ECsGameInstanceOnBoardState
{
	typedef TCsProperty_Multi_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		extern const TCsString LoadDataMapping;
		extern const TCsString FinishedLoadingDataAssets;
		extern const TCsString FinishedPopulatingAssetReferences;
		extern const TCsString LoadStartUpData;
		extern const TCsString LoadScreen;
		extern const TCsString Completed;
	}

	namespace Ref
	{
		extern const Type LoadDataMapping;
		extern const Type FinishedLoadingDataAssets;
		extern const Type FinishedPopulatingAssetReferences;
		extern const Type LoadStartUpData;
		extern const Type LoadScreen;
		extern const Type Completed;
		extern const Type ECsGameInstanceOnBoardState_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::LoadDataMapping) { return Str::LoadDataMapping.Value; }
		if (EType == Type::FinishedLoadingDataAssets) { return Str::FinishedLoadingDataAssets.Value; }
		if (EType == Type::FinishedPopulatingAssetReferences) { return Str::FinishedPopulatingAssetReferences.Value; }
		if (EType == Type::LoadStartUpData) { return Str::LoadStartUpData.Value; }
		if (EType == Type::LoadScreen) { return Str::LoadScreen.Value; }
		if (EType == Type::Completed) { return Str::Completed.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &String)
	{
		if (String == Str::LoadDataMapping) { return Ref::LoadDataMapping; }
		if (String == Str::FinishedLoadingDataAssets) { return Ref::FinishedLoadingDataAssets; }
		if (String == Str::FinishedPopulatingAssetReferences) { return Ref::FinishedPopulatingAssetReferences; }
		if (String == Str::LoadStartUpData) { return Ref::LoadStartUpData; }
		if (String == Str::LoadScreen) { return Ref::LoadScreen; }
		if (String == Str::Completed) { return Ref::Completed; }
		return Ref::ECsGameInstanceOnBoardState_MAX;
	}
}

#define ECS_GAME_INSTANCE_ONBOARD_STATE_MAX (uint8)ECsGameInstanceOnBoardState::ECsGameInstanceOnBoardState_MAX
typedef ECsGameInstanceOnBoardState::Type TCsGameInstanceOnBoardState;

#pragma endregion Enums

#define CS_INVALID_UNIQUE_OBJECT_ID ECsCached::Ref::Long_MAX

class ACsDataMapping;

UCLASS(config = Game)
class CSCORE_API UCsGameInstance : public UGameInstance
{
	GENERATED_UCLASS_BODY()

	virtual void InitCVars();

	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void StartGameInstance() override;

#if WITH_EDITOR
	virtual FGameInstancePIEResult StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params) override;
#endif // #if WITH_EDITOR

	/** Delegate for callbacks to Tick */
	FTickerDelegate	TickDelegate;

	/** Handle to various registered delegates */
	FDelegateHandle	TickDelegateHandle;

	virtual bool Tick(float DeltaSeconds);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnTick, const float&);

	FOnTick OnTick_Event;

	UPROPERTY(BlueprintAssignable, Category = "Tick")
	FBindableDynEvent_CsGameInstance_OnTick OnTick_ScriptEvent;

	uint64 CurrentGameFrame;

// Routines
#pragma region
public:

	static void AddRoutine(UObject* InGameInstance, struct FCsRoutine* Routine, const uint8& Type);
	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8& Type);

	static void RemoveRoutine(UObject* InGameInstance, struct FCsRoutine* Routine, const uint8& Type);
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8& Type);

#pragma endregion Routines

// OnBoard
#pragma region
public:

	TCsGameInstanceOnBoardState OnBoardState;

	CS_COROUTINE_DECLARE(OnBoard)

	// Data Mapping
#pragma region
public:

	FString DataMappingAssetPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance")
	TSoftClassPtr<ACsDataMapping> DataMappingClass;

	UPROPERTY(BlueprintReadOnly, Category = "Game Instance")
	ACsDataMapping* DataMapping;

	bool ForcePopulateAssetReferences;

	CS_COROUTINE_DECLARE(LoadDataMapping)

	virtual void OnFinishedLoadingDataAssets(const TArray<UObject*>& LoadedAssets, const float& LoadingTime);

	bool HasLoadedDataAssets;

	void PopulateAssetReferences();
	void AsyncPopulateAssetReferences();

	UPROPERTY()
	TArray<UObject*> LoadedDataAssets;

	UPROPERTY(BlueprintReadOnly, Category = "Game Instance")
	bool HasLoadedDataMapping;

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

	bool IsVR;

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

	UPROPERTY(BlueprintReadOnly, Category = "Game Instance")
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

	UPROPERTY(BlueprintAssignable, Category = "Level")
	FBindableDynEvent_CsGameInstance_OnServerTravel OnServerTravel_ScriptEvent;

#pragma endregion Level

public:

	virtual void ExitGame();

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
};