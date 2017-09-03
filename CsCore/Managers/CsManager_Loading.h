// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsTypes.h"
#include "CsManager_Loading.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsManagerLoading_OnStartLoadingAssetReferences, const int32&);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsManagerLoading_OnStartLoadingAssetReference, const FStringAssetReference&);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsManagerLoading_OnFinishedLoadingAssetReference, const FCsAssetReferenceLoadedCache&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsManagerLoading_OnFinishedLoadingAssetReferences, const TArray<UObject*>&, const float&);

UCLASS(transient)
class CSCORE_API UCsManager_Loading : public UObject
{
	GENERATED_UCLASS_BODY()
public:

	static UCsManager_Loading* Get();
	static void Init();
	static void Shutdown();

	/** Delegate for callbacks to Tick */
	FTickerDelegate	TickDelegate;

	/** Handle to various registered delegates */
	FDelegateHandle	TickDelegateHandle;

	bool Tick(float DeltaSeconds);

protected:

	void Initialize();
	void CleanUp();

public:

	TArray<TCsLoadAsyncOrder> AsyncOrders;
	TArray<TArray<FStringAssetReference>> AssetReferencesQueue;
	TArray<FBindableEvent_CsManagerLoading_OnFinishedLoadingAssetReferences> OnFinishedLoadingAssetReferences_Events;
	TArray<UWorld*> CurrentWorlds;

	FBindableEvent_CsManagerLoading_OnStartLoadingAssetReferences OnStartLoadingAssetReferences_Event;
	FBindableEvent_CsManagerLoading_OnStartLoadingAssetReference OnStartLoadingAssetReference_Event;
	FBindableEvent_CsManagerLoading_OnFinishedLoadingAssetReference OnFinishedLoadingAssetReference_Event;
	FBindableEvent_CsManagerLoading_OnFinishedLoadingAssetReferences OnFinishedLoadingAssetReferences_Event;

protected:

	FStreamableManager		StreamableManager;
	FStreamableDelegate		AssetReferenceLoadedDelegate;
	FStreamableDelegate		AssetReferencesLoadedDelegate;

	int32 AssetReferencesLoadedCount;

	FCsResourceSize ResourceSizeLoaded;

	FCsAssetReferenceLoadedCache AssetReferenceLoadedCache;

	void OnFinishedLoadingAssetReference();
	void OnFinishedLoadingAssetReferences();

	float LoadingStartTime;
	float LoadingTotalStartTime;

	UPROPERTY()
	TArray<UObject*> LoadedAssets;

public:

	template<typename T>
	void LoadAssetReferences(UWorld* CurrentWorld, TArray<FStringAssetReference> &AssetReferences, const TCsLoadAsyncOrder &AsyncOrder, T* CallbackCaller , void (T::*Callback)(const TArray<UObject*>&, const float&))
	{
		// Add Callback
		OnFinishedLoadingAssetReferences_Events.AddDefaulted();

		const int32 Count = OnFinishedLoadingAssetReferences_Events.Num();

		OnFinishedLoadingAssetReferences_Events[Count - 1].AddUObject(CallbackCaller, Callback);

		AsyncOrders.Add(AsyncOrder);
		AssetReferencesQueue.Add(AssetReferences);
		CurrentWorlds.Add(CurrentWorld);

		// If the FIRST batch of AssetReferences, queue loading immediately
		if (AssetReferencesQueue.Num() == 1)
			LoadAssetReferences_Internal(AssetReferences, AsyncOrder);
	}

	void LoadAssetReferences_Internal(TArray<FStringAssetReference> &AssetReferences, const TCsLoadAsyncOrder &AsyncOrder);

private:
	// Singleton data
	static UCsManager_Loading* s_managerLoadingSingleton;
	static bool s_bManagerHasShutdown;
};