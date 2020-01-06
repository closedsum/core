// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Load/CsManager_Load.h"
#include "CsCore.h"
#include "CsCVars.h"

// Library
#include "Library/CsLibrary_Common.h"
#include "Library/CsLibrary_Math.h"

#include "Classes/Engine/World.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Load/CsGetManagerLoad.h"

#include "Classes/Engine/Engine.h"
#endif // #if WITH_EDITOR

// Structs
#pragma region

	// FCsManagerLoad_Task_LoadObjects
#pragma region

void FCsManagerLoad_Task_LoadObjects::Init()
{
	// FirstToLast
	OnFinishLoadObjectPathDelegate = FStreamableDelegate::CreateRaw(this, &FCsManagerLoad_Task_LoadObjects::OnFinishLoadObjectPath);
	// None | Bulk
	OnFinishLoadObjectPathsDelegate = FStreamableDelegate::CreateRaw(this, &FCsManagerLoad_Task_LoadObjects::OnFinishLoadObjectPaths);
}

void FCsManagerLoad_Task_LoadObjects::OnUpdate(const FCsDeltaTime& DeltaTime)
{

}

void FCsManagerLoad_Task_LoadObjects::LoadObjectPaths(UWorld* InWorld, const TArray<FSoftObjectPath>& ObjectPaths, const ECsLoadAsyncOrder& AsyncOrder, FCsManagerLoad_OnFinishLoadObjects Delegate)
{
	Order = AsyncOrder;

	const int32 Size = ObjectPaths.Num();
	const int32 Max  = FMath::Max(Paths.Max(), Size);

	Paths.Reserve(Max);
	Paths.Append(ObjectPaths);

	// Add Callback
	OnFinishLoadObjects_Event = Delegate;

	World = InWorld;

	// Start Loading - Load All References
	//OnStartLoadingAssetReferences_Event.Broadcast(Size);
	//OnStartLoadProgress_Event.Broadcast(Size);

	if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("FCsManagerLoad_Task_LoadObjects::LoadObjectPaths: Requesting Load of %d Assets."), Size);
		// None | Bulk
		if (AsyncOrder == ECsLoadAsyncOrder::None ||
			AsyncOrder == ECsLoadAsyncOrder::Bulk)
		{
			for (const FSoftObjectPath& Path : ObjectPaths)
			{
				UE_LOG(LogCs, Log, TEXT("FCsManagerLoad_Task_LoadObjects::LoadObjectPaths: Requesting Load of %s."), *(Path.ToString()));
			}
		}
	}
	// Start the Async Load

		// FirstToLast
	if (AsyncOrder == ECsLoadAsyncOrder::FirstToLast)
	{
		if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Log, TEXT("UCsManager_Load::LoadObjectPaths_Internal: Requesting Load of %s."), *(ObjectPaths[CS_FIRST].ToString()));
		}
		//OnStartLoadingAssetReference_Event.Broadcast(ObjectPaths[CS_FIRST]);
		StreamableManager.RequestAsyncLoad(ObjectPaths[CS_FIRST], OnFinishLoadObjectPathDelegate);
	}
	// Bulk
	else
	{
		LoadHandle = StreamableManager.RequestAsyncLoad(ObjectPaths, OnFinishLoadObjectPathsDelegate);
	}

	StartTime = World ? World->GetTimeSeconds() : UCsLibrary_Common::GetCurrentDateTimeSeconds();
}

void FCsManagerLoad_Task_LoadObjects::OnFinishLoadObjectPath()
{
	FSoftObjectPath& Path = Paths[Count];

	UObject* Object = Path.ResolveObject();
	check(Object);

	TArray<UObject*> LoadedObjects = Manager_Load->GetLoadedObjects(Index);

	LoadedObjects.Add(Object);

	const int32 LastCount = Count;

	++Count;

	// Get Memory loaded and the time it took
	const int32 Bytes	  = Object->GetResourceSizeBytes(EResourceSizeMode::Exclusive);
	const float Kilobytes = UCsLibrary_Math::BytesToKilobytes(Bytes);
	const float Megabytes = UCsLibrary_Math::BytesToMegabytes(Bytes);

	SizeLoaded.Bytes	 += Bytes;
	SizeLoaded.Kilobytes += Kilobytes;
	SizeLoaded.Megabytes += Megabytes;

	const float CurrentTime = World ? World->GetTimeSeconds() : UCsLibrary_Common::GetCurrentDateTimeSeconds();
	const float LoadingTime	= CurrentTime - StartTime;

	if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("FCsManagerLoad_Task_LoadObjects::OnFinishLoadObjectPath: Finished Loading %s. %f mb (%f kb, %d bytes) in %f seconds."), *Path.ToString(), Megabytes, Kilobytes, Bytes, LoadingTime);
	}

	// Broadcast the event to anyone listening
	Cache.Path			 = Path;
	Cache.Count			 = LastCount;
	Cache.Size.Bytes	 = Bytes;
	Cache.Size.Kilobytes = Kilobytes;
	Cache.Size.Megabytes = Megabytes;
	Cache.Time			 = LoadingTime;

	OnFinishLoadObjectPath_Event.Broadcast(Cache);

	// FirstToLast, Queue the NEXT Asset for Async Load
	if (Count < Paths.Num())
	{
		if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Log, TEXT("UCsManager_Load::OnFinishedLoadingAssetReference: Requesting Load of %s."), *(Paths[Count].ToString()));
		}
		OnStartLoadingAssetReference_Event.Broadcast(AssetReferences[AssetReferencesLoadedCount]);
		StreamableManager.RequestAsyncLoad(AssetReferences[AssetReferencesLoadedCount], AssetReferenceLoadedDelegate);
	}
	LoadingStartTime = CurrentTime;
}

void FCsManagerLoad_Task_LoadObjects::OnFinishLoadObjectPaths()
{

}

#pragma endregion FCsManagerLoad_Task_LoadObjects

#pragma endregion Structs

// static initializations
UCsManager_Load* UCsManager_Load::s_Instance;
bool UCsManager_Load::s_bShutdown = false;

UCsManager_Load::UCsManager_Load(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsManager_Load* UCsManager_Load::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerLoad(InRoot)->GetManager_Load();
#else
	if (s_bShutdown)
		return nullptr;

	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Load::Init(UObject* InRoot)
{
#if WITH_EDITOR
	ICsGetManagerLoad* GetManagerLoad = Get_GetManagerLoad(InRoot);

	UCsManager_Load* Manager_Load = NewObject<UCsManager_Load>(GetTransientPackage(), UCsManager_Load::StaticClass(), TEXT("Manager_Load_Singleton"), RF_Transient | RF_Public);

	GetManagerLoad->SetManager_Load(Manager_Load);

	Manager_Load->SetMyRoot(InRoot);
	Manager_Load->Initialize();
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Load>(GetTransientPackage(), UCsManager_Load::StaticClass(), TEXT("Manager_Load_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}

#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Load::Shutdown(UObject* InRoot = nullptr)
{
#if WITH_EDITOR
	ICsGetManagerLoad* GetManagerLoad = Get_GetManagerLoad(InRoot);
	UCsManager_Load* Manager_Load	  = GetManagerLoad->GetManager_Load();
	Manager_Load->CleanUp();

	GetManagerLoad->SetManager_Load(nullptr);
#else
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerLoad* UCsManager_Load::Get_GetManagerLoad(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Load::Get_GetManagerLoad: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Load::Get_GetManagerLoad: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Load::Get_GetManagerLoad: Manager_Singleton is NULL."));

	ICsGetManagerLoad* GetManagerLoad = Cast<ICsGetManagerLoad>(Manager_Singleton);

	checkf(GetManagerLoad, TEXT("UCsManager_Load::Get_GetManagerLoad: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerLoad."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerLoad;
}

/*static*/ ICsGetManagerLoad* UCsManager_Load::GetSafe_GetManagerLoad(UObject* InRoot)
{
	if (!InRoot)
		return nullptr;

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	if (!GetManagerSingleton)
		return nullptr;

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
		return nullptr;

	return Cast<ICsGetManagerLoad>(Manager_Singleton);
}

/*static*/ UCsManager_Load* UCsManager_Load::GetSafe(UObject* InRoot)
{
	if (ICsGetManagerLoad* GetManagerLoad = GetSafe_GetManagerLoad(InRoot))
		return GetManagerLoad->GetManager_Load();
	return nullptr;
}

/*static*/ UCsManager_Load* UCsManager_Load::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game Instance
		if (UCsManager_Load* Manager = GetSafe(World->GetGameInstance()))
			return Manager;

		UE_LOG(LogCs, Warning, TEXT("UCsManager_Load::GetFromWorldContextObject: Failed to Manager Player Profile of type UCsManager_Load from GameInstance."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

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
		LoadObjectPaths_Internal(AssetReferencesQueue[CS_FIRST], AsyncOrders[CS_FIRST]);
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

	// Init Tasks
	{
		const TArray<FCsMemoryResource_ManagerLoad_Task_LoadObjects*>& Pool = Manager_Tasks.GetPool();

		for (FCsMemoryResource_ManagerLoad_Task_LoadObjects* Resource : Pool)
		{
			LoadedObjects.AddDefaulted();
			LoadedObjects.Last().Reset();

			FCsManagerLoad_Task_LoadObjects* Task = Resource->Get();

			Task->Index		   = Resource->GetIndex();
			Task->Manager_Load = this;
			Task->Init();
		}
	}
}

void UCsManager_Load::CleanUp()
{
	// Unregister ticker delegate
	FTicker::GetCoreTicker().RemoveTicker(s_Instance->TickDelegateHandle);

}

// Root
#pragma region

void UCsManager_Load::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

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
	ObjectPathLoadedCache.Path			 = AssetReference;
	ObjectPathLoadedCache.Count			 = LastCount;
	ObjectPathLoadedCache.Size.Bytes	 = Bytes;
	ObjectPathLoadedCache.Size.Kilobytes = Kilobytes;
	ObjectPathLoadedCache.Size.Megabytes = Megabytes;
	ObjectPathLoadedCache.Time			 = LoadingTime;

	OnFinishedLoadingAssetReference_Event.Broadcast(ObjectPathLoadedCache);
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

TArray<UObject*>& UCsManager_Load::GetLoadedObjects(const int32& Index)
{
	return LoadedObjects[Index];
}

FCsManagerLoad_Task_LoadObjects& UCsManager_Load::LoadObjectPaths(UWorld* CurrentWorld, TArray<FStringAssetReference>& AssetReferences, const ECsLoadAsyncOrder& AsyncOrder, FCsManagerLoad_OnFinishLoadObjects Delegate)
{
	FCsMemoryResource_ManagerLoad_Task_LoadObjects* Resource = Manager_Tasks.Allocate();
	FCsManagerLoad_Task_LoadObjects* Task					 = Resource->Get();

	Task->LoadObjectPaths(CurrentWorld, AssetReferences, AsyncOrder, Delegate);

	return *Task;
}

void UCsManager_Load::LoadObjectPaths_Internal(TArray<FSoftObjectPath>& ObjectPaths, const ECsLoadAsyncOrder& AsyncOrder)
{
	AssetReferencesLoadedCount = 0;

	ResourceSizeLoaded.Reset();

	// Start Loading - Load All References

	const int32 Size = ObjectPaths.Num();

	OnStartLoadingAssetReferences_Event.Broadcast(Size);
	OnStartLoadProgress_Event.Broadcast(Size);

	if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("UCsManager_Load::LoadObjectPaths_Internal: Requesting Load of %d Assets."), Size);
		// None | Bulk
		if (AsyncOrder == ECsLoadAsyncOrder::None ||
			AsyncOrder == ECsLoadAsyncOrder::Bulk)
		{
			for (int32 I = 0; I < Size; ++I)
			{
				UE_LOG(LogCs, Log, TEXT("UCsManager_Load::LoadObjectPaths_Internal: Requesting Load of %s."), *(ObjectPaths[I].ToString()));
			}
		}
	}
	// Start the Async Load

		// FirstToLast
	if (AsyncOrder == ECsLoadAsyncOrder::FirstToLast)
	{
		if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Log, TEXT("UCsManager_Load::LoadObjectPaths_Internal: Requesting Load of %s."), *(ObjectPaths[CS_FIRST].ToString()));
		}
		OnStartLoadingAssetReference_Event.Broadcast(ObjectPaths[CS_FIRST]);
		StreamableManager.RequestAsyncLoad(ObjectPaths[CS_FIRST], AssetReferenceLoadedDelegate);
	}
		// Bulk
	else
	{
		LoadHandle = StreamableManager.RequestAsyncLoad(ObjectPaths, AssetReferencesLoadedDelegate);
	}

	LoadingStartTime	  = CurrentWorlds[CS_FIRST] ? CurrentWorlds[CS_FIRST]->GetTimeSeconds() : UCsLibrary_Common::GetCurrentDateTimeSeconds();
	LoadingTotalStartTime = LoadingStartTime;
}