// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/GameInstance.h"
#include "../Core/Public/Containers/Ticker.h"
#include "CsTypes.h"
#include "CsGameInstance.generated.h"

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

// Data Mapping
#pragma region

	FString DataMappingAssetPath;

	UPROPERTY(BlueprintReadOnly, Category = "Game Instance")
	class ACsDataMapping* DataMapping;

	bool ForcePopulateAssetReferences;

	virtual void LoadDataMapping();
	static char LoadDataMapping_Internal(struct FCsRoutine* r);

	void OnFinishedLoadingDataAssets(const TArray<UObject*> &LoadedAssets, const float& LoadingTime);

	bool HasLoadedDataAssets;

	UPROPERTY()
	TArray<UObject*> LoadedDataAssets;

	UPROPERTY(BlueprintReadOnly, Category = "Game Instance")
	bool HasLoadedDataMapping;

#pragma endregion Data Mapping

	bool IsVR;

	UPROPERTY(BlueprintReadOnly, Category = "Game Instance")
	TEnumAsByte<ECsLevelState::Type> LevelState;
};