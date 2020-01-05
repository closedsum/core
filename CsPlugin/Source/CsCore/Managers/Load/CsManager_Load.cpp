// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Load/CsManager_Load.h"
#include "CsCore.h"
#include "CsCVars.h"

// Library
#include "Library/CsLibrary_Common.h"
#include "Library/CsLibrary_Math.h"

#include "Classes/Engine/World.h"

// static initializations
UCsManager_Load* UCsManager_Load::s_Instance;
bool UCsManager_Load::s_bShutdown = false;

UCsManager_Load::UCsManager_Load(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsManager_Load* UCsManager_Load::Get()
{
	if (s_bShutdown)
		return nullptr;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Load>(GetTransientPackage(), UCsManager_Load::StaticClass(), TEXT("Manager_Load_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->Initialize();
	}

	return s_Instance;
}

/*static*/ void UCsManager_Load::Init()
{
	s_bShutdown = false;
	UCsManager_Load::Get();
}

/*static*/ void UCsManager_Load::Shutdown()
{
	if (!s_Instance)
		return;

	// Unregister ticker delegate
	FTicker::GetCoreTicker().RemoveTicker(s_Instance->TickDelegateHandle);

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
}

bool UCsManager_Load::Tick(float DeltaSeconds)
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
	
	const float CurrentTime = CurrentWorlds[CS_FIRST] ? CurrentWorlds[CS_FIRST]->GetTimeSeconds() : UCsLibrary_Common::GetCurrentDateTimeSeconds();
	const float LoadingTime = CurrentTime - LoadingTotalStartTime;

	// All AssetReferences are LOADED
	if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
	{
		// FirstToLast
		if (AsyncOrders[CS_FIRST] == ECsLoadAsyncOrder::FirstToLast)
		{
			UE_LOG(LogCs, Log, TEXT("UCsManager_Load::Tick: Finished Loading %d Assets. %f mb (%f kb, %d bytes) in %f seconds."), AssetReferencesLoadedCount, ResourceSizeLoaded.Megabytes, ResourceSizeLoaded.Kilobytes, ResourceSizeLoaded.Bytes, LoadingTime);
		}
		// None | Bulk
		else
		{
			UE_LOG(LogCs, Log, TEXT("UCsManager_Load::Tick: Finished Loading %d Assets in %f seconds."), AssetReferencesLoadedCount, LoadingTime);
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

void UCsManager_Load::Initialize()
{
	// Register delegate for ticker callback
	TickDelegate	   = FTickerDelegate::CreateUObject(this, &UCsManager_Load::Tick);
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);

	// FirstToLast
	AssetReferenceLoadedDelegate  = FStreamableDelegate::CreateUObject(this, &UCsManager_Load::OnFinishedLoadingAssetReference);
	// None | Bulk
	AssetReferencesLoadedDelegate = FStreamableDelegate::CreateUObject(this, &UCsManager_Load::OnFinishedLoadingAssetReferences);
}

void UCsManager_Load::CleanUp()
{
}

#pragma endregion Singleton

void UCsManager_Load::OnFinishedLoadingAssetReference()
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
	const float Kilobytes = UCsLibrary_Math::BytesToKilobytes(Bytes);
	const float Megabytes = UCsLibrary_Math::BytesToMegabytes(Bytes);

	ResourceSizeLoaded.Bytes	 += Bytes;
	ResourceSizeLoaded.Kilobytes += Kilobytes;
	ResourceSizeLoaded.Megabytes += Megabytes;

	const float CurrentTime = CurrentWorlds[CS_FIRST] ? CurrentWorlds[CS_FIRST]->GetTimeSeconds() : UCsLibrary_Common::GetCurrentDateTimeSeconds();
	const float LoadingTime	= CurrentTime - LoadingStartTime;

	if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("UCsManager_Load::OnFinishedLoadingAssetReference: Finished Loading %s. %f mb (%f kb, %d bytes) in %f seconds."), *AssetReference.ToString(), Megabytes, Kilobytes, Bytes, LoadingTime);
	}

	// Broadcast the event to anyone listening
	AssetReferenceLoadedCache.Reference		 = AssetReference;
	AssetReferenceLoadedCache.Count			 = LastCount;
	AssetReferenceLoadedCache.Size.Bytes	 = Bytes;
	AssetReferenceLoadedCache.Size.Kilobytes = Kilobytes;
	AssetReferenceLoadedCache.Size.Megabytes = Megabytes;
	AssetReferenceLoadedCache.Time			 = LoadingTime;

	OnFinishedLoadingAssetReference_Event.Broadcast(AssetReferenceLoadedCache);
	// FirstToLast, Queue the NEXT Asset for Async Load
	if (AssetReferencesLoadedCount < AssetReferences.Num())
	{
		if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Log, TEXT("UCsManager_Load::OnFinishedLoadingAssetReference: Requesting Load of %s."), *(AssetReferences[AssetReferencesLoadedCount].ToString()));
		}
		OnStartLoadingAssetReference_Event.Broadcast(AssetReferences[AssetReferencesLoadedCount]);
		StreamableManager.RequestAsyncLoad(AssetReferences[AssetReferencesLoadedCount], AssetReferenceLoadedDelegate);
	}
	LoadingStartTime = CurrentTime;
}

void UCsManager_Load::OnFinishedLoadingAssetReferences()
{
	TArray<FStringAssetReference>& AssetReferences = AssetReferencesQueue[CS_FIRST];

	for (FStringAssetReference& AssetReference : AssetReferences)
	{
		UObject* Asset = AssetReference.ResolveObject();
		check(Asset);

		LoadedAssets.Add(Asset);
	}
	AssetReferencesLoadedCount = AssetReferences.Num();
}

void UCsManager_Load::LoadAssetReferences_Internal(TArray<FStringAssetReference>& AssetReferences, const ECsLoadAsyncOrder& AsyncOrder)
{
	AssetReferencesLoadedCount = 0;

	ResourceSizeLoaded.Reset();

	// Start Loading - Load All References

	const int32 Size = AssetReferences.Num();

	OnStartLoadingAssetReferences_Event.Broadcast(Size);
	OnStartLoadProgress_Event.Broadcast(Size);

	if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("UCsManager_Load::LoadAssetReferences_Internal: Requesting Load of %d Assets."), Size);
		// None | Bulk
		if (AsyncOrder == ECsLoadAsyncOrder::None ||
			AsyncOrder == ECsLoadAsyncOrder::Bulk)
		{
			for (int32 I = 0; I < Size; ++I)
			{
				UE_LOG(LogCs, Log, TEXT("UCsManager_Load::LoadAssetReferences_Internal: Requesting Load of %s."), *(AssetReferences[I].ToString()));
			}
		}
	}
	// Start the Async Load

		// FirstToLast
	if (AsyncOrder == ECsLoadAsyncOrder::FirstToLast)
	{
		if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Log, TEXT("UCsManager_Load::LoadAssetReferences_Internal: Requesting Load of %s."), *(AssetReferences[CS_FIRST].ToString()));
		}
		OnStartLoadingAssetReference_Event.Broadcast(AssetReferences[CS_FIRST]);
		StreamableManager.RequestAsyncLoad(AssetReferences[CS_FIRST], AssetReferenceLoadedDelegate);
	}
		// Bulk
	else
	{
		LoadHandle = StreamableManager.RequestAsyncLoad(AssetReferences, AssetReferencesLoadedDelegate);
	}

	LoadingStartTime	  = CurrentWorlds[CS_FIRST] ? CurrentWorlds[CS_FIRST]->GetTimeSeconds() : UCsLibrary_Common::GetCurrentDateTimeSeconds();
	LoadingTotalStartTime = LoadingStartTime;
}