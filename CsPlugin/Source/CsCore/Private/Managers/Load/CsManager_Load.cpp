// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Load/CsManager_Load.h"

// Types
#include "CsMacro_Misc.h"
// Settings
#include "Managers/Load/CsSettings_Manager_Load.h"
// Library
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Load/CsGetManagerLoad.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsManager_Load)

// static initializations
UCsManager_Load* UCsManager_Load::s_Instance;
bool UCsManager_Load::s_bShutdown = false;

namespace NCsManagerLoad
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Load, CleanUp);
		}
	}
}

UCsManager_Load::UCsManager_Load(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UpdateGroup = NCsUpdateGroup::GameInstance;
}

// Singleton
#pragma region

#if WITH_EDITOR

/*static*/ UCsManager_Load* UCsManager_Load::Get(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerLoad(InRoot)->GetManager_Load();
}

/*static*/ UCsManager_Load* UCsManager_Load::GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerLoad* GetManagerLoad = GetSafe_GetManagerLoad(Context, InRoot, Log))
		return GetManagerLoad->GetManager_Load();
	return nullptr;
}

#endif // #if WITH_EDITOR

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

/*static*/ void UCsManager_Load::Shutdown(const UObject* InRoot /*=nullptr*/)
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

/*static*/ bool UCsManager_Load::HasShutdown(const UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerLoad(InRoot)->GetManager_Load() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerLoad* UCsManager_Load::Get_GetManagerLoad(const UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Load::Get_GetManagerLoad: InRoot is NULL."));

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Load::Get_GetManagerLoad: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Load::Get_GetManagerLoad: Manager_Singleton is NULL."));

	ICsGetManagerLoad* GetManagerLoad = Cast<ICsGetManagerLoad>(Manager_Singleton);

	checkf(GetManagerLoad, TEXT("UCsManager_Load::Get_GetManagerLoad: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerLoad."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerLoad;
}

/*static*/ ICsGetManagerLoad* UCsManager_Load::GetSafe_GetManagerLoad(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	CS_IS_PTR_NULL_RET_NULL(InRoot)

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	if (!GetManagerSingleton)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *Context, *(InRoot->GetName()), *(InRoot->GetClass()->GetName())));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Singleton from InRoot: %s with Class: %s."), *Context, *(InRoot->GetName()), *(InRoot->GetClass()->GetName())));
		return nullptr;
	}
	return Cast<ICsGetManagerLoad>(Manager_Singleton);
}

#endif // #if WITH_EDITOR

void UCsManager_Load::Initialize()
{
	const FCsSettings_Manager_Load& Manager_Load = FCsSettings_Manager_Load::Get();

	checkf(Manager_Load.PoolSize >= 4, TEXT("UCsManager_Load::Initialize: UCsDeveloperSettings.Manager_Load.PoolSize is NOT >= 4."));

	Manager_Tasks.CreatePool(Manager_Load.PoolSize);
	// Init Tasks
	{
		typedef NCsLoad::NManager::NTask::NLoadObjects::FResource ResourceType;

		const TArray<ResourceType*>& Pool = Manager_Tasks.GetPool();

		for (ResourceType* Container : Pool)
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

/*static*/ bool UCsManager_Load::HasInitialized(const UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_Load::CleanUp()
{
	using namespace NCsManagerLoad::NCached;

	const FString& Context = Str::CleanUp;

	typedef NCsObject::FLibrary ObjectLibrary;

	for (UObject* O : Tasks)
	{
		ObjectLibrary::SafeMarkAsGarbage(O);
	}

	Tasks.Reset();

	typedef NCsLoad::NManager::NTask::NLoadObjects::FResource ResourceType;
	typedef UCsManagerLoad_Task_LoadObjects TaskType;

	const TArray<ResourceType*>& Pool = Manager_Tasks.GetPool();

	for (ResourceType* Container : Pool)
	{
		TaskType* Task = Container->Get();

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
	typedef NCsLoad::NManager::NTask::NLoadObjects::FResource ResourceType;
	typedef UCsManagerLoad_Task_LoadObjects TaskType;

	TCsDoubleLinkedList<ResourceType*>* Current = Manager_Tasks.GetAllocatedHead();
	TCsDoubleLinkedList<ResourceType*>* Next	= Current;

	while (Next)
	{
		Current					= Next;
		ResourceType* Container = **Current;
		Next					= Current->GetNextLink();

		TaskType* Task = Container->Get();

		Task->Update(DeltaTime);

		if (Task->IsComplete())
		{
			Manager_Tasks.Deallocate(Container);
		}
	}
}

#define PayloadType NCsLoad::NManager::NLoadObjectPaths::FPayload
FCsLoadHandle UCsManager_Load::LoadObjectPaths(const PayloadType& Payload)
{
#undef PayloadType

	typedef NCsLoad::NManager::NTask::NLoadObjects::FResource ResourceType;
	typedef UCsManagerLoad_Task_LoadObjects TaskType;

	ResourceType* Resource = Manager_Tasks.Allocate();
	TaskType* Task		   = Resource->Get();

	FCsLoadHandle Handle = Task->LoadObjectPaths(Payload);

	return Handle;
}