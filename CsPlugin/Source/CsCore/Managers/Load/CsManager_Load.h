// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Engine/StreamableManager.h"
#include "Types/CsTypes_Load.h"
#include "CsManager_Load.generated.h"

DECLARE_DELEGATE_TwoParams(FCsManagerLoad_OnFinishedLoadingObjects, const TArray<UObject*>&, const float&);

// Structs
#pragma region

class UWorld;

struct CSCORE_API FCsManagerLoad_Task_LoadObjects
{
public:

	ECsLoadAsyncOrder Order;

	TArray<FSoftObjectPath> Paths;

	FCsManagerLoad_OnFinishedLoadingObjects OnFinishedLoadingObjects_Event;

	UWorld* CurrentWorld;

	int32 LoadedCount;

	FCsResourceSize ResourceSizeLoaded;

	FCsManagerLoad_Task_LoadObjects()
	{

	}

	void Reset()
	{
		Order = ECsLoadAsyncOrder::Bulk;
		Paths.Reset(Paths.Max());
		OnFinishedLoadingObjects_Event.Unbind();
		CurrentWorld = nullptr;
		LoadedCount = 0;
		ResourceSizeLoaded.Reset();
	}
};

#pragma endregion Structs

class UWorld;

UCLASS(transient)
class CSCORE_API UCsManager_Load : public UObject
{
	GENERATED_UCLASS_BODY()
public:

// Singleton
#pragma region
public:

	static UCsManager_Load* Get();
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

private:
	// Singleton data
	static UCsManager_Load* s_Instance;
	static bool s_bShutdown;                                      

#pragma endregion Singleton

public:

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnStartLoadingAssetReferences, const int32&);

	FOnStartLoadingAssetReferences OnStartLoadingAssetReferences_Event;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnStartLoadingAssetReference, const FStringAssetReference&);

	FOnStartLoadingAssetReference OnStartLoadingAssetReference_Event;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnFinishedLoadingAssetReference, const FCsObjectPathLoadedCache&);

	FOnFinishedLoadingAssetReference OnFinishedLoadingAssetReference_Event;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFinishedLoadingAssetReferences, const TArray<UObject*>&, const float&);

	FOnFinishedLoadingAssetReferences OnFinishedLoadingAssetReferences_Event;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnStartLoadProgress, const int32&);

	FOnStartLoadProgress OnStartLoadProgress_Event;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoadProgressUpdated, const float&);

	FOnLoadProgressUpdated OnLoadProgressUpdated_Event;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFinishedLoadingAssetReferences, const TArray<UObject*>&, const float&);

	FOnFinishedLoadingAssetReferences Bulk_OnFinishedLoadingAssetReferences_Event;

	TArray<ECsLoadAsyncOrder> AsyncOrders;
	TArray<TArray<FStringAssetReference>> AssetReferencesQueue;
	TArray<FOnFinishedLoadingAssetReferences> OnFinishedLoadingAssetReferences_Events;
	TArray<UWorld*> CurrentWorlds;

protected:

	FStreamableManager		StreamableManager;
	FStreamableDelegate		AssetReferenceLoadedDelegate;
	FStreamableDelegate		AssetReferencesLoadedDelegate;

	TSharedPtr<FStreamableHandle> LoadHandle;

	TArray<FCsManagerLoad_Task_LoadObjects> Tasks;

public:

protected:

	int32 AssetReferencesLoadedCount;

	FCsResourceSize ResourceSizeLoaded;

	FCsObjectPathLoadedCache ObjectPathLoadedCache;

	void OnFinishedLoadingAssetReference();
	void OnFinishedLoadingAssetReferences();

	float LoadingStartTime;
	float LoadingTotalStartTime;

	UPROPERTY()
	TArray<UObject*> LoadedAssets;

public:

	template<typename T>
	void LoadAssetReferences(UWorld* CurrentWorld, TArray<FStringAssetReference>& AssetReferences, const ECsLoadAsyncOrder& AsyncOrder, T* CallbackCaller, void (T::*Callback)(const TArray<UObject*>&, const float&))
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

	void LoadAssetReferences_Internal(TArray<FStringAssetReference> &AssetReferences, const ECsLoadAsyncOrder& AsyncOrder);
};