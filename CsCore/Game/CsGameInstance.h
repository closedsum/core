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
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString OnBoard_Internal = TCsString(TEXT("OnBoard_Internal"), TEXT("onboard_internal"), TEXT("onboard internal"));
		const TCsString LoadDataMapping_Internal = TCsString(TEXT("LoadDataMapping_Internal"), TEXT("loaddatamapping_internal"), TEXT("load data mapping internal"));
		const TCsString PerformLevelTransition_Internal = TCsString(TEXT("PerformLevelTransition_Internal"), TEXT("performleveltransition_internal"), TEXT("perform level transition internal"));
		const TCsString CreateFullscreenWidget_Internal = TCsString(TEXT("CreateFullscreenWidget_Internal"), TEXT("createfullscreenwidget_internal"), TEXT("create fullscreen widget internal"));
		const TCsString HideMouseCursor_Internal = TCsString(TEXT("HideMouseCursor_Internal"), TEXT("hidemousecursor_internal"), TEXT("hide mouse cursor internal"));
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
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString LoadDataMapping = TCsString(TEXT("LoadDataMapping"), TEXT("loaddatamapping"), TEXT("load data mapping"));
		const TCsString LoadStartUpData = TCsString(TEXT("LoadStartUpData"), TEXT("loadstartupdata"), TEXT("load start up data"));
		const TCsString LoadScreen = TCsString(TEXT("LoadScreen"), TEXT("loadscreen"), TEXT("load screen"));
		const TCsString Completed = TCsString(TEXT("Completed"), TEXT("completed"), TEXT("completed"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::LoadDataMapping) { return Str::LoadDataMapping.Value; }
		if (EType == Type::LoadStartUpData) { return Str::LoadStartUpData.Value; }
		if (EType == Type::LoadScreen) { return Str::LoadScreen.Value; }
		if (EType == Type::Completed) { return Str::Completed.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::LoadDataMapping) { return Type::LoadDataMapping; }
		if (String == Str::LoadStartUpData) { return Type::LoadStartUpData; }
		if (String == Str::LoadScreen) { return Type::LoadScreen; }
		if (String == Str::Completed) { return Type::Completed; }
		return Type::ECsGameInstanceOnBoardState_MAX;
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