// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/CsUiWidget_Loading.h"
#include "CsCore.h"

UCsUiWidget_Loading::UCsUiWidget_Loading(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsUiWidget_Loading::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!HasInitFinished)
		Init();

	OnNativeTick_HandleLoading(InDeltaTime);

#if WITH_EDITOR
	OnNativeTick_ScriptEvent.Broadcast(MyGeometry, InDeltaTime);
#endif // #if WITH_EDITOR
}

void UCsUiWidget_Loading::Init()
{
	// Loading
	Loading.Loading.Set(Loading_Text);
	Loading.Processing.Set(Loading_Processing_Text);
	Loading.Finished.Set(Loading_Finished_Text);
	Loading.Bar.Set(Loading_Bar);
	Loading.Total.Set(Loading_Total_Text);

	HasInitFinished = true;
}

void UCsUiWidget_Loading::OnNativeTick_HandleLoading(const float &InDeltaTime)
{
	if (Loading.IsShuttingDown)
	{
		Loading.OnNativeTick(InDeltaTime);

		Loading.IsActive = false;
		Hide();
	}

	if (!Loading.IsActive)
		return;

	Loading.OnNativeTick(InDeltaTime);
}

void UCsUiWidget_Loading::OnStartLoadingAssets(const int32 &AssetCount)
{
	Show();
	Loading.Activate();
	Loading.SetTotalCount(AssetCount);

#if WITH_EDITOR
	OnStartLoadingAssets_ScriptEvent.Broadcast(AssetCount);
#endif // #if WITH_EDITOR
}

void UCsUiWidget_Loading::OnStartLoadingAsset(const FStringAssetReference &Reference)
{
	Loading.SetProcessing(Reference.ToString());

#if WITH_EDITOR
	OnStartLoadingAsset_ScriptEvent.Broadcast(Reference);
#endif // #if WITH_EDITOR
}

void UCsUiWidget_Loading::OnFinishedLoadingAsset(const FCsAssetReferenceLoadedCache &Cache)
{
	Loading.SetFinished(Cache.Reference.ToString(), Cache.Count + 1, Cache.Size.Megabytes, Cache.Size.Kilobytes, Cache.Size.Bytes, Cache.Time);

#if WITH_EDITOR
	OnFinishedLoadingAsset_ScriptEvent.Broadcast(Cache);
#endif // #if WITH_EDITOR
}

void UCsUiWidget_Loading::OnFinishedLoadingAssets(const TArray<UObject*> &LoadedAssets, const float &LoadingTime)
{
	Loading.SetCompleted();

#if WITH_EDITOR
	OnFinishedLoadingAssets_ScriptEvent.Broadcast(LoadedAssets, LoadingTime);
#endif // #if WITH_EDITOR
}