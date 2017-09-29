// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/CsManager_Loading.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"

// static initializations
UCsManager_Loading* UCsManager_Loading::s_managerLoadingSingleton;
bool UCsManager_Loading::s_bManagerHasShutdown = false;

UCsManager_Loading::UCsManager_Loading(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

/*static*/ UCsManager_Loading* UCsManager_Loading::Get()
{
	if (s_bManagerHasShutdown)
		return nullptr;

	if (!s_managerLoadingSingleton)
	{
		s_managerLoadingSingleton = NewObject<UCsManager_Loading>(GetTransientPackage(), UCsManager_Loading::StaticClass(), TEXT("Manager_Loading_Singleton"), RF_Transient | RF_Public);
		s_managerLoadingSingleton->AddToRoot();
		s_managerLoadingSingleton->Initialize();
	}

	return s_managerLoadingSingleton;
}

/*static*/ void UCsManager_Loading::Init()
{
	s_bManagerHasShutdown = false;
	UCsManager_Loading::Get();
}

/*static*/ void UCsManager_Loading::Shutdown()
{
	if (!s_managerLoadingSingleton)
		return;

	// Unregister ticker delegate
	FTicker::GetCoreTicker().RemoveTicker(s_managerLoadingSingleton->TickDelegateHandle);

	s_managerLoadingSingleton->CleanUp();
	s_managerLoadingSingleton->RemoveFromRoot();
	s_managerLoadingSingleton = nullptr;
	s_bManagerHasShutdown = true;
}

bool UCsManager_Loading::Tick(float DeltaSeconds)
{
	// If Queue Empty, EXIT
	if (AssetReferencesQueue.Num() == CS_EMPTY)
		return true;

	TArray<FStringAssetReference>& AssetReferences = AssetReferencesQueue[CS_FIRST];

	if (AsyncOrders[CS_FIRST] == ECsLoadAsyncOrder::Bulk)
		OnLoadProgressUpdated_Event.Broadcast(LoadHandle->GetProgress());

	// If Still Loading, EXIT
	if (AssetReferencesLoadedCount < AssetReferences.Num())
		return true;
	
	const float CurrentTime = CurrentWorlds[CS_FIRST] ? CurrentWorlds[CS_FIRST]->GetTimeSeconds() : UCsCommon::GetCurrentDateTimeSeconds();
	const float LoadingTime = CurrentTime - LoadingTotalStartTime;

	// All AssetReferences are LOADED
	if (CsCVarLogManagerLoading->GetInt() == CS_CVAR_SHOW_LOG)
	{
		// FirstToLast
		if (AsyncOrders[CS_FIRST] == ECsLoadAsyncOrder::FirstToLast)
		{
			UE_LOG(LogCs, Log, TEXT("UCsManager_Loading::Tick: Finished Loading %d Assets. %f mb (%f kb, %d bytes) in %f seconds"), AssetReferencesLoadedCount, ResourceSizeLoaded.Megabytes, ResourceSizeLoaded.Kilobytes, ResourceSizeLoaded.Bytes, LoadingTime);
		}
		// None | Bulk
		else
		{
			UE_LOG(LogCs, Log, TEXT("UCsManager_Loading::Tick: Finished Loading %d Assets in %f seconds"), AssetReferencesLoadedCount, LoadingTime);
		}
	}

	AsyncOrders.RemoveAt(CS_FIRST);
	AssetReferencesQueue.RemoveAt(CS_FIRST);
	CurrentWorlds.RemoveAt(CS_FIRST);

	OnFinishedLoadingAssetReferences_Events[CS_FIRST].Broadcast(LoadedAssets, LoadingTime);
	OnFinishedLoadingAssetReferences_Events.RemoveAt(CS_FIRST);

	OnFinishedLoadingAssetReferences_Event.Broadcast(LoadedAssets, LoadingTime);
	Bulk_OnFinishedLoadingAssetReferences_Event.Broadcast(LoadedAssets, LoadingTime);

	LoadHandle = nullptr;

	// Assume the Callback holds onto the references for LoadedAssets
	LoadedAssets.Reset();

	// If Queue is NOT Empty, Load the next batch of AssetReferences 
	if (AssetReferencesQueue.Num() != CS_EMPTY)
	{
		LoadAssetReferences_Internal(AssetReferencesQueue[CS_FIRST], AsyncOrders[CS_FIRST]);
	}
	return true;
}

void UCsManager_Loading::Initialize()
{
	// Register delegate for ticker callback
	TickDelegate	   = FTickerDelegate::CreateUObject(this, &UCsManager_Loading::Tick);
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);

	// FirstToLast
	AssetReferenceLoadedDelegate  = FStreamableDelegate::CreateUObject(this, &UCsManager_Loading::OnFinishedLoadingAssetReference);
	// None | Bulk
	AssetReferencesLoadedDelegate = FStreamableDelegate::CreateUObject(this, &UCsManager_Loading::OnFinishedLoadingAssetReferences);
}

void UCsManager_Loading::CleanUp()
{
}

void UCsManager_Loading::OnFinishedLoadingAssetReference()
{
	TArray<FStringAssetReference>& AssetReferences = AssetReferencesQueue[CS_FIRST];
	FStringAssetReference& AssetReference		   = AssetReferences[AssetReferencesLoadedCount];

	UObject* Asset = AssetReference.ResolveObject();
	check(Asset);

	LoadedAssets.Add(Asset);

	const int32 LastCount = AssetReferencesLoadedCount;

	AssetReferencesLoadedCount++;

	// Get Memory loaded and the time it took
	const int32 Bytes	  = Asset->GetResourceSizeBytes(EResourceSizeMode::Exclusive);
	const float Kilobytes = UCsCommon::BytesToKilobytes(Bytes);
	const float Megabytes = UCsCommon::BytesToMegabytes(Bytes);

	ResourceSizeLoaded.Bytes	 += Bytes;
	ResourceSizeLoaded.Kilobytes += Kilobytes;
	ResourceSizeLoaded.Megabytes += Megabytes;

	const float CurrentTime = CurrentWorlds[CS_FIRST] ? CurrentWorlds[CS_FIRST]->GetTimeSeconds() : UCsCommon::GetCurrentDateTimeSeconds();
	const float LoadingTime	= CurrentTime - LoadingStartTime;

	if (CsCVarLogManagerLoading->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("UCsManager_Loading::OnFinishedLoadingAssetReference: Finished Loading %s. %f mb (%f kb, %d bytes) in %f seconds."), *AssetReference.ToString(), Megabytes, Kilobytes, Bytes, LoadingTime);
	}

	// Broadcast the event to anyone listening
	AssetReferenceLoadedCache.Reference = AssetReference;
	AssetReferenceLoadedCache.Count = LastCount;
	AssetReferenceLoadedCache.Size.Bytes = Bytes;
	AssetReferenceLoadedCache.Size.Kilobytes = Kilobytes;
	AssetReferenceLoadedCache.Size.Megabytes = Megabytes;
	AssetReferenceLoadedCache.Time = LoadingTime;

	OnFinishedLoadingAssetReference_Event.Broadcast(AssetReferenceLoadedCache);
	// FirstToLast, Queue the NEXT Asset for Async Load
	if (AssetReferencesLoadedCount < AssetReferences.Num())
	{
		if (CsCVarLogManagerLoading->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Log, TEXT("UCsManager_Loading::OnFinishedLoadingAssetReference: Requesting Load of %s"), *(AssetReferences[AssetReferencesLoadedCount].ToString()));
		}
		OnStartLoadingAssetReference_Event.Broadcast(AssetReferences[AssetReferencesLoadedCount]);
		StreamableManager.RequestAsyncLoad(AssetReferences[AssetReferencesLoadedCount], AssetReferenceLoadedDelegate);
	}
	LoadingStartTime = CurrentTime;
}

void UCsManager_Loading::OnFinishedLoadingAssetReferences()
{
	TArray<FStringAssetReference>& AssetReferences = AssetReferencesQueue[CS_FIRST];

	const int32 Count = AssetReferences.Num();

	for (int32 I = 0; I < Count; I++)
	{
		FStringAssetReference& AssetReference = AssetReferences[I];

		UObject* Asset = AssetReference.ResolveObject();
		check(Asset);

		LoadedAssets.Add(Asset);
	}
	AssetReferencesLoadedCount = Count;
}

void UCsManager_Loading::LoadAssetReferences_Internal(TArray<FStringAssetReference> &AssetReferences, const TCsLoadAsyncOrder &AsyncOrder)
{
	AssetReferencesLoadedCount = 0;

	ResourceSizeLoaded.Reset();

	// Start Loading - Load All References

	const int32 Size = AssetReferences.Num();

	OnStartLoadingAssetReferences_Event.Broadcast(Size);
	OnStartLoadProgress_Event.Broadcast(Size);

	if (CsCVarLogManagerLoading->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("UCsManager_Loading::LoadAssetReferences_Internal: Requesting Load of %d Assets"), Size);
		// None | Bulk
		if (AsyncOrder == ECsLoadAsyncOrder::None ||
			AsyncOrder == ECsLoadAsyncOrder::Bulk)
		{
			for (int32 I = 0; I < Size; I++)
			{
				UE_LOG(LogCs, Log, TEXT("UCsManager_Loading::LoadAssetReferences_Internal: Requesting Load of %s"), *(AssetReferences[I].ToString()));
			}
		}
	}
	// Start the Async Load

		// FirstToLast
	if (AsyncOrder == ECsLoadAsyncOrder::FirstToLast)
	{
		if (CsCVarLogManagerLoading->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Log, TEXT("UCsManager_Loading::LoadAssetReferences_Internal: Requesting Load of %s"), *(AssetReferences[CS_FIRST].ToString()));
		}
		OnStartLoadingAssetReference_Event.Broadcast(AssetReferences[CS_FIRST]);
		StreamableManager.RequestAsyncLoad(AssetReferences[CS_FIRST], AssetReferenceLoadedDelegate);
	}
		// Bulk
	else
	{
		LoadHandle = StreamableManager.RequestAsyncLoad(AssetReferences, AssetReferencesLoadedDelegate);
	}

	LoadingStartTime	  = CurrentWorlds[CS_FIRST] ? CurrentWorlds[CS_FIRST]->GetTimeSeconds() : UCsCommon::GetCurrentDateTimeSeconds();
	LoadingTotalStartTime = LoadingStartTime;
}