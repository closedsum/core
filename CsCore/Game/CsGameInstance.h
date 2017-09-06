// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/GameInstance.h"
#include "../Core/Public/Containers/Ticker.h"
#include "CsTypes.h"
#include "CsGameInstance.generated.h"

// Enums
#pragma region

namespace ECsGameInstanceRoutine
{
	enum Type
	{
		OnBoard_Internal			UMETA(DisplayName = "OnBoard_Internal"),
		LoadDataMapping_Internal	UMETA(DisplayName = "LoadDataMapping_Internal"),
		ECsGameInstanceRoutine_MAX	UMETA(Hidden),
	};
}

namespace ECsGameInstanceRoutine
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString OnBoard_Internal = TCsString(TEXT("OnBoard_Internal"), TEXT("onboard_internal"), TEXT("onboard internal"));
		const TCsString LoadDataMapping_Internal = TCsString(TEXT("LoadDataMapping_Internal"), TEXT("loaddatamapping_internal"), TEXT("load data mapping internal"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::OnBoard_Internal) { return Str::OnBoard_Internal.Value; }
		if (EType == Type::LoadDataMapping_Internal) { return Str::LoadDataMapping_Internal.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::OnBoard_Internal) { return Type::OnBoard_Internal; }
		if (String == Str::LoadDataMapping_Internal) { return Type::LoadDataMapping_Internal; }
		return Type::ECsGameInstanceRoutine_MAX;
	}
}

#define ECS_GAME_INSTANCE_ROUTINE_MAX (uint8)ECsGameInstanceRoutine::ECsGameInstanceRoutine_MAX
typedef ECsGameInstanceRoutine::Type TCsGameInstanceRoutine;

namespace ECsGameInstanceOnBoardState
{
	enum Type
	{
		LoadDataMapping,
		LoadStartUpData,
		LoadScreen,
		Completed,
		ECsGameInstanceOnBoardState_MAX,
	};
}

namespace ECsGameInstanceOnBoardState
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString LoadDataMapping = TCsString(TEXT("LoadDataMapping"), TEXT("loaddatamapping"), TEXT("load data mapping"));
		const TCsString LoadStartUpData = TCsString(TEXT("LoadStartUpData"), TEXT("loadstartupdata"), TEXT("load start up data"));
		const TCsString LoadScreen = TCsString(TEXT("LoadScreen"), TEXT("loadscreen"), TEXT("load screen"));
		const TCsString Completed = TCsString(TEXT("Completed"), TEXT("completed"), TEXT("completed"));
	}

	FORCEINLINE FString ToString(const Type &EType)
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

	virtual void ResetCVars();

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

	UPROPERTY()
	TArray<UObject*> LoadedDataAssets;

	UPROPERTY(BlueprintReadOnly, Category = "Game Instance")
	bool HasLoadedDataMapping;

#pragma endregion Data Mapping

	// Load StartUp Data
#pragma region

	virtual void LoadStartUpData();
	virtual void OnFinishedLoadingStartUpDataAssets(const TArray<UObject*> &LoadedAssets, const float& LoadingTime);

#pragma endregion Load StartUp Data

	// Fullscreen Widget
#pragma region

	UPROPERTY(BlueprintReadOnly, Category = "Game Instance")
	class UCsUserWidget* FullscreenWidget;

	virtual void SetupFullscreenWidget();

#pragma endregion Fullscreen Widget

#pragma region OnBoard

	bool IsVR;

	UPROPERTY(BlueprintReadOnly, Category = "Game Instance")
	TEnumAsByte<ECsLevelState::Type> LevelState;

// UI
#pragma region
public:

	UPROPERTY(BlueprintReadOnly, Category = "Game Instance")
	class UCsUserWidget* SplashScreenWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Game Instance")
	class UCsUserWidget* TransitionWidget;

#pragma endregion UI
};