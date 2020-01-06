// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/CsUserWidget.h"
#include "CsUiWidget_Loading.generated.h"

// Loading
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUiWidgetLoading_OnStartLoadingAssets, const int32&, AssetCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUiWidgetLoading_OnStartLoadingAsset, const FStringAssetReference&, Reference);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUiWidgetLoading_OnFinishedLoadingAsset, const FCsObjectPathLoadedInfo&, Info);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsUiWidgetLoading_OnFinishedLoadingAssets, const TArray<UObject*>&, LoadedAssets, const float&, LoadingTime);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUiWidgetLoading_OnStartLoadProgress, const int32&, AssetCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUiWidgetLoading_OnLoadProgressUpdated, const float&, Percent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsUiWidgetLoading_Bulk_OnFinishedLoadingAssetReferences, const TArray<UObject*>&, LoadedAssets, const float&, LoadingTime);

UCLASS()
class CSCORE_API UCsUiWidget_Loading : public UCsUserWidget
{
	GENERATED_UCLASS_BODY()

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void Init() override;

	// Loading
#pragma region

	FCsWidget_Loading Loading;

	void OnNativeTick_HandleLoading(const float &InDeltaTime);

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Loading_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Loading_Processing_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Loading_Finished_Text;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* Loading_Bar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Loading_Total_Text;

	// FirstToLast
#pragma region

	virtual void OnStartLoadingAssets(const int32& AssetCount);

	UPROPERTY(BlueprintAssignable, Category = "Loading")
	FBindableDynEvent_CsUiWidgetLoading_OnStartLoadingAssets OnStartLoadingAssets_ScriptEvent;

	virtual void OnStartLoadingAsset(const FStringAssetReference& Reference);

	UPROPERTY(BlueprintAssignable, Category = "Loading")
	FBindableDynEvent_CsUiWidgetLoading_OnStartLoadingAsset OnStartLoadingAsset_ScriptEvent;

	virtual void OnFinishedLoadingAsset(const FCsObjectPathLoadedInfo& Info);

	UPROPERTY(BlueprintAssignable, Category = "Loading")
	FBindableDynEvent_CsUiWidgetLoading_OnFinishedLoadingAsset OnFinishedLoadingAsset_ScriptEvent;

	virtual void OnFinishedLoadingAssets(const TArray<UObject*>& LoadedAssets, const float& LoadingTime);

	UPROPERTY(BlueprintAssignable, Category = "Loading")
	FBindableDynEvent_CsUiWidgetLoading_OnFinishedLoadingAssets OnFinishedLoadingAssets_ScriptEvent;

#pragma endregion FirstToLast

	// Bulk
#pragma region

	virtual void OnStartLoadProgress(const int32 &AssetCount);

	UPROPERTY(BlueprintAssignable, Category = "Loading")
	FBindableDynEvent_CsUiWidgetLoading_OnStartLoadProgress OnStartLoadProgress_ScriptEvent;

	virtual void OnLoadProgressUpdated(const float &Percent);

	UPROPERTY(BlueprintAssignable, Category = "Loading")
	FBindableDynEvent_CsUiWidgetLoading_OnLoadProgressUpdated OnLoadProgressUpdated_ScriptEvent;

	virtual void Bulk_OnFinishedLoadingAssets(const TArray<UObject*> &LoadedAssets, const float &LoadingTime);

	UPROPERTY(BlueprintAssignable, Category = "Loading")
	FBindableDynEvent_CsUiWidgetLoading_Bulk_OnFinishedLoadingAssetReferences Bulk_OnFinishedLoadingAssets_ScriptEvent;

#pragma endregion Bulk

#pragma endregion Loading
};