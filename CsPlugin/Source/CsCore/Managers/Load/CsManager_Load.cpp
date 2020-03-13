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

// static initializations
UCsManager_Load* UCsManager_Load::s_Instance;
bool UCsManager_Load::s_bShutdown = false;

UCsManager_Load::UCsManager_Load(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UpdateGroup = NCsUpdateGroup::GameInstance;
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

	UCsManager_Load* Manager_Load = NewObject<UCsManager_Load>(InRoot, UCsManager_Load::StaticClass(), TEXT("Manager_Load_Singleton"), RF_Transient | RF_Public);

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

void UCsManager_Load::Initialize()
{
	// TODO: Add a config variable to change the pool size
	static const int32 DEFAULT_POOL_SIZE = 64;
	Manager_Tasks.CreatePool(DEFAULT_POOL_SIZE);
	// Init Tasks
	{
		const TArray<FCsResource_ManagerLoad_Task_LoadObjects*>& Pool = Manager_Tasks.GetPool();

		for (FCsResource_ManagerLoad_Task_LoadObjects* Container : Pool)
		{
			UCsManagerLoad_Task_LoadObjects* Task = NewObject<UCsManagerLoad_Task_LoadObjects>(this, UCsManagerLoad_Task_LoadObjects::StaticClass());
			
			Tasks.Add(Task);

			Container->Set(Task);

			Task->Index	= Container->GetIndex();
			Task->Init();
			Task->UpdateGroup = UpdateGroup;
			Task->SetStreamableManager(&StreamableManager);
		}
	}
}

void UCsManager_Load::CleanUp()
{
	for (UObject* O : Tasks)
	{
		if (O &&
			!O->IsPendingKill())
		{
			O->MarkPendingKill();
		}
	}

	Tasks.Reset();

	const TArray<FCsResource_ManagerLoad_Task_LoadObjects*>& Pool = Manager_Tasks.GetPool();

	for (FCsResource_ManagerLoad_Task_LoadObjects* Container : Pool)
	{
		UCsManagerLoad_Task_LoadObjects* Task = Container->Get();

		Container->Set(nullptr);
	}

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

void UCsManager_Load::Update(const FCsDeltaTime& DeltaTime)
{
	TCsDoubleLinkedList<FCsResource_ManagerLoad_Task_LoadObjects*>* Current = Manager_Tasks.GetAllocatedHead();
	TCsDoubleLinkedList<FCsResource_ManagerLoad_Task_LoadObjects*>* Next	= Current;

	while (Next)
	{
		Current												= Next;
		FCsResource_ManagerLoad_Task_LoadObjects* Container = **Current;
		Next												= Current->Next();

		UCsManagerLoad_Task_LoadObjects* Task = Container->Get();

		Task->Update(DeltaTime);
	}
}

FCsLoadHandle UCsManager_Load::LoadObjectPaths(UWorld* CurrentWorld, TArray<FSoftObjectPath>& ObjectPaths, const ECsLoadAsyncOrder& AsyncOrder, UCsManagerLoad_Task_LoadObjects::FOnFinishLoadObjectPaths Delegate)
{
	FCsResource_ManagerLoad_Task_LoadObjects* Resource = Manager_Tasks.Allocate();
	UCsManagerLoad_Task_LoadObjects* Task			   = Resource->Get();

	FCsLoadHandle Handle = Task->LoadObjectPaths(CurrentWorld, ObjectPaths, AsyncOrder, Delegate);

	return Handle;
}