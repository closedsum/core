// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/GameInstance.h"
#include "../Core/Public/Containers/Ticker.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_Coroutine.h"
#include "CsGameInstance.generated.h"

// OnTick
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsGameInstance_OnTick, const float&, DeltaSeconds);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsGameInstance_OnTick, const float&);
// OnServerTravel
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableDynEvent_CsGameInstance_OnServerTravel);
DECLARE_MULTICAST_DELEGATE(FBindableEvent_CsGameInstance_OnServerTravel);

// Enums
#pragma region

namespace ECsGameInstanceRoutine
{
	enum Type
	{
		OnBoard_Internal				UMETA(DisplayName = "OnBoard_Internal"),
		LoadDataMapping_Internal		UMETA(DisplayName = "LoadDataMapping_Internal"),
		PerformLevelTransition_Internal	UMETA(DisplayName = "PerformLevelTransition_Internal"),
		CreateFullscreenWidget_Internal UMETA(DisplayName = "CreateFullscreenWidget_Internal"),
		HideMouseCursor_Internal		UMETA(DisplayName = "HideMouseCursor_Internal"),
		ECsGameInstanceRoutine_MAX		UMETA(Hidden),
	};
}

#define ECS_GAME_INSTANCE_ROUTINE_MAX (uint8)ECsGameInstanceRoutine::ECsGameInstanceRoutine_MAX
typedef ECsGameInstanceRoutine::Type TCsGameInstanceRoutine;

namespace ECsGameInstanceRoutine
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		extern const TCsString OnBoard_Internal;
		extern const TCsString LoadDataMapping_Internal;
		extern const TCsString PerformLevelTransition_Internal;
		extern const TCsString CreateFullscreenWidget_Internal;
		extern const TCsString HideMouseCursor_Internal;
	}

	namespace Ref
	{
		extern const TCsGameInstanceRoutine OnBoard_Internal;
		extern const TCsGameInstanceRoutine LoadDataMapping_Internal;
		extern const TCsGameInstanceRoutine PerformLevelTransition_Internal;
		extern const TCsGameInstanceRoutine CreateFullscreenWidget_Internal;
		extern const TCsGameInstanceRoutine HideMouseCursor_Internal;
		extern const TCsGameInstanceRoutine ECsGameInstanceRoutine_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::OnBoard_Internal) { return Str::OnBoard_Internal.Value; }
		if (EType == Type::LoadDataMapping_Internal) { return Str::LoadDataMapping_Internal.Value; }
		if (EType == Type::PerformLevelTransition_Internal) { return Str::PerformLevelTransition_Internal.Value; }
		if (EType == Type::CreateFullscreenWidget_Internal) { return Str::CreateFullscreenWidget_Internal.Value; }
		if (EType == Type::HideMouseCursor_Internal) { return Str::HideMouseCursor_Internal.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &String)
	{
		if (String == Str::OnBoard_Internal) { return Ref::OnBoard_Internal; }
		if (String == Str::LoadDataMapping_Internal) { return Ref::LoadDataMapping_Internal; }
		if (String == Str::PerformLevelTransition_Internal) { return Ref::PerformLevelTransition_Internal; }
		if (String == Str::CreateFullscreenWidget_Internal) { return Ref::CreateFullscreenWidget_Internal; }
		if (String == Str::HideMouseCursor_Internal) { return Ref::HideMouseCursor_Internal; }
		return Ref::ECsGameInstanceRoutine_MAX;
	}
}

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
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

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

	FBindableEvent_CsGameInstance_OnTick OnTick_Event;

	UPROPERTY(BlueprintAssignable, Category = "Tick")
	FBindableDynEvent_CsGameInstance_OnTick OnTick_ScriptEvent;

	uint64 CurrentGameFrame;

// Routines
#pragma region
public:

	static void AddRoutine(UObject* InGameInstance, struct FCsRoutine* Routine, const uint8 &Type);
	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type);

	static void RemoveRoutine(UObject* InGameInstance, struct FCsRoutine* Routine, const uint8 &Type);
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type);

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

	UPROPERTY(BlueprintReadOnly, Category = "Game Instance")
	class ACsDataMapping* DataMapping;

	bool ForcePopulateAssetReferences;

	CS_COROUTINE_DECLARE(LoadDataMapping)

	virtual void OnFinishedLoadingDataAssets(const TArray<UObject*> &LoadedAssets, const float& LoadingTime);

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
	virtual void OnFinishedLoadingStartUpDataAssets(const TArray<UObject*> &LoadedAssets, const float& LoadingTime);

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
	TEnumAsByte<ECsLevelState::Type> LevelState;

	FDelegateHandle OnPreWorldInitializationHandle;
	void OnPreWorldInitialization(UWorld* InWorld, const UWorld::InitializationValues);
	FDelegateHandle OnPostWorldInitializationHandle;
	void OnPostWorldInitialization(UWorld* InWorld, const UWorld::InitializationValues);
	FDelegateHandle OnLevelAddedToWorldHandle;
	void OnLevelAddedToWorld(ULevel* InLevel, UWorld* InWorld);
	FDelegateHandle OnLevelRemovedFromWorldHandle;
	void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld);

	virtual void PerformLevelTransition(const FString &Level, const FString &GameMode);
	static char PerformLevelTransition_Internal(struct FCsRoutine* r);
	struct FCsRoutine* PerformLevelTransition_Internal_Routine;

	FBindableEvent_CsGameInstance_OnServerTravel OnServerTravel_Event;

	UPROPERTY(BlueprintAssignable, Category = "Level")
	FBindableDynEvent_CsGameInstance_OnServerTravel OnServerTravel_ScriptEvent;

#pragma endregion Level

	virtual void ExitGame();

// Object
#pragma region
public:

	UPROPERTY()
	uint64 UniqueObjectIdIndex;

	uint64 GetUniqueObjectId();

#pragma endregion Object
};