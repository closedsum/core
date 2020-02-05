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

void FCsManagerLoad_Task_LoadObjects::Update(const FCsDeltaTime& DeltaTime)
{
	// If Queue Empty, EXIT
	if (Paths.Num() == CS_EMPTY)
		return;

	if (Order == ECsLoadAsyncOrder::Bulk)
		OnLoadProgressUpdated_Event.ExecuteIfBound(Handle->GetProgress());

	// If Still Loading, EXIT
	if (Count < Paths.Num())
		return;

	const float CurrentTime = World ? World->GetTimeSeconds() : UCsLibrary_Common::GetCurrentDateTimeSeconds();
	const float LoadTime    = CurrentTime - StartTime;

	// All AssetReferences are LOADED
	if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
	{
		// FirstToLast
		if (Order == ECsLoadAsyncOrder::FirstToLast)
		{
			UE_LOG(LogCs, Log, TEXT("FCsManagerLoad_Task_LoadObjects::OnUpdate: Finished Loading %d Assets. %f mb (%f kb, %d bytes) in %f seconds."), Count, SizeLoaded.Megabytes, SizeLoaded.Kilobytes, SizeLoaded.Bytes, LoadTime);
		}
		// None | Bulk
		else
		{
			UE_LOG(LogCs, Log, TEXT("FCsManagerLoad_Task_LoadObjects::OnUpdate: Finished Loading %d Assets in %f seconds."), Count, LoadTime);
		}
	}

	TArray<UObject*> LoadedObjects = Manager_Load->GetLoadedObjects(Index);

	OnFinishLoadObjectPaths_Event.ExecuteIfBound(LoadedObjects, LoadTime);

	// Assume the Callback holds onto the references for LoadedAssets
	LoadedObjects.Reset(LoadedObjects.Max());

	Reset();
}

void FCsManagerLoad_Task_LoadObjects::LoadObjectPaths(UWorld* InWorld, const TArray<FSoftObjectPath>& ObjectPaths, const ECsLoadAsyncOrder& AsyncOrder, FCsManagerLoad_OnFinishLoadObjectPaths Delegate)
{
	Order = AsyncOrder;

	const int32 Size = ObjectPaths.Num();
	const int32 Max  = FMath::Max(Paths.Max(), Size);

	Paths.Reserve(Max);
	Paths.Append(ObjectPaths);

	// Add Callback
	OnFinishLoadObjectPaths_Event = Delegate;

	World = InWorld;

	// Start Loading - Load All References
	OnStartLoadObjectPaths_Event.ExecuteIfBound(Size);
	OnStartLoadProgress_Event.ExecuteIfBound(Size);

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
		OnStartLoadObjectPath_Event.ExecuteIfBound(ObjectPaths[CS_FIRST]);
		Manager_Load->StreamableManager.RequestAsyncLoad(ObjectPaths[CS_FIRST], OnFinishLoadObjectPathDelegate);
	}
	// Bulk
	else
	{
		Handle = Manager_Load->StreamableManager.RequestAsyncLoad(ObjectPaths, OnFinishLoadObjectPathsDelegate);
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

	FSoftObjectPath& NextPath = Paths[Count];

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
	Info.Path			 = Path;
	Info.Count			 = LastCount;
	Info.Size.Bytes		 = Bytes;
	Info.Size.Kilobytes  = Kilobytes;
	Info.Size.Megabytes  = Megabytes;
	Info.Time			 = LoadingTime;

	OnFinishLoadObjectPath_Event.ExecuteIfBound(Info, Object);

	// FirstToLast, Queue the NEXT Asset for Async Load
	if (Count < Paths.Num())
	{
		if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Log, TEXT("UCsManager_Load::OnFinishedLoadingAssetReference: Requesting Load of %s."), *(NextPath.ToString()));
		}
		OnStartLoadObjectPath_Event.ExecuteIfBound(NextPath);
		Manager_Load->StreamableManager.RequestAsyncLoad(NextPath, OnFinishLoadObjectPathDelegate);
	}
	StartTime = CurrentTime;
}

void FCsManagerLoad_Task_LoadObjects::OnFinishLoadObjectPaths()
{
	TArray<UObject*> LoadedObjects = Manager_Load->GetLoadedObjects(Index);

	for (FSoftObjectPath& Path : Paths)
	{
		UObject* Object = Path.ResolveObject();
		check(Object);

		LoadedObjects.Add(Object);
	}
	Count = Paths.Num();
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

/*static*/ void UCsManager_Load::Shutdown(UObject* InRoot /*=nullptr*/)
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
	TCsDoubleLinkedList<FCsResourceContainer_ManagerLoad_Task_LoadObjects*>* Current = Manager_Tasks.GetAllocatedHead();
	TCsDoubleLinkedList<FCsResourceContainer_ManagerLoad_Task_LoadObjects*>* Next    = Current;

	while (Next)
	{
		Current														 = Next;
		FCsResourceContainer_ManagerLoad_Task_LoadObjects* Container = **Current;
		Next														 = Current->GetNextLink();

		FCsManagerLoad_Task_LoadObjects* Task = Container->Get();

		//Task->OnUpdate()
	}

	return true;
}

void UCsManager_Load::Initialize()
{
	// Register delegate for ticker callback
	TickDelegate	   = FTickerDelegate::CreateUObject(this, &UCsManager_Load::Tick);
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);

	// Init Tasks
	{
		const TArray<FCsResourceContainer_ManagerLoad_Task_LoadObjects*>& Pool = Manager_Tasks.GetPool();

		for (FCsResourceContainer_ManagerLoad_Task_LoadObjects* Container : Pool)
		{
			LoadedObjects.AddDefaulted();
			LoadedObjects.Last().Reset();

			FCsManagerLoad_Task_LoadObjects* Task = Container->Get();

			Task->Index		   = Container->GetIndex();
			Task->Manager_Load = this;
			Task->Init();
		}
	}
}

void UCsManager_Load::CleanUp()
{
	// Unregister ticker delegate
	FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);

	Manager_Tasks.Shutdown();
}

// Root
#pragma region

void UCsManager_Load::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

TArray<UObject*>& UCsManager_Load::GetLoadedObjects(const int32& Index)
{
	return LoadedObjects[Index];
}

FCsManagerLoad_Task_LoadObjects& UCsManager_Load::LoadObjectPaths(UWorld* CurrentWorld, TArray<FStringAssetReference>& AssetReferences, const ECsLoadAsyncOrder& AsyncOrder, FCsManagerLoad_OnFinishLoadObjectPaths Delegate)
{
	FCsResourceContainer_ManagerLoad_Task_LoadObjects* Resource = Manager_Tasks.Allocate();
	FCsManagerLoad_Task_LoadObjects* Task						= Resource->Get();

	Task->LoadObjectPaths(CurrentWorld, AssetReferences, AsyncOrder, Delegate);

	return *Task;
}