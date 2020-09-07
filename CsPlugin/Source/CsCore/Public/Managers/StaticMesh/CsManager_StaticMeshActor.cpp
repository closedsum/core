// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/StaticMesh/CsManager_StaticMeshActor.h"
#include "CsCore.h"

// CVars
#include "Managers/StaticMesh/CsCVars_Manager_StaticMeshActor.h"
// Library
#include "Library/CsLibrary_Property.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Managers
#include "Managers/Data/CsManager_Data.h"
// Data
#include "Managers/StaticMesh/Data/CsData_StaticMeshActorImpl.h"
// StaticMeshActor
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActorImpl.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/StaticMesh/CsGetManagerStaticMeshActor.h"

#include "Library/CsLibrary_Common.h"

#include "Engine/World.h"
#include "Engine/Engine.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerStaticMeshActor
{
	namespace Str
	{
		const FString InitInternalFromSettings = TEXT("UCsManager_StaticMeshActor::InitInternalFromSettings");
	}

	namespace Name
	{
	}
}

#pragma endregion Cached

// Internal
#pragma region

FCsManager_StaticMeshActor_Internal::FCsManager_StaticMeshActor_Internal() 
	: Super()
{
}

#pragma endregion Internal

// static initializations
UCsManager_StaticMeshActor* UCsManager_StaticMeshActor::s_Instance;
bool UCsManager_StaticMeshActor::s_bShutdown = false;

UCsManager_StaticMeshActor::UCsManager_StaticMeshActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsManager_StaticMeshActor* UCsManager_StaticMeshActor::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerStaticMeshActor(InRoot)->GetManager_StaticMeshActor();
#else
	if (s_bShutdown)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_StaticMeshActor::Get: Manager has already shutdown."));
		return nullptr;
	}
	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_StaticMeshActor::IsValid(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerStaticMeshActor(InRoot)->GetManager_StaticMeshActor() != nullptr;
#else
	return s_Instance != nullptr;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_StaticMeshActor::Init(UObject* InRoot, TSubclassOf<UCsManager_StaticMeshActor> ManagerStaticMeshActorClass, UObject* InOuter /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerStaticMeshActor* GetManagerStaticMeshActor = Get_GetManagerStaticMeshActor(InRoot);

	UCsManager_StaticMeshActor* Manager_StaticMeshActor = GetManagerStaticMeshActor->GetManager_StaticMeshActor();

	if (!Manager_StaticMeshActor)
	{
		Manager_StaticMeshActor = NewObject<UCsManager_StaticMeshActor>(InOuter ? InOuter : InRoot, ManagerStaticMeshActorClass, TEXT("Manager_StaticMeshActor_Singleton"), RF_Transient | RF_Public);

		GetManagerStaticMeshActor->SetManager_StaticMeshActor(Manager_StaticMeshActor);

		Manager_StaticMeshActor->SetMyRoot(InRoot);
		Manager_StaticMeshActor->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_StaticMeshActor::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_StaticMeshActor>(GetTransientPackage(), ManagerStaticMeshActorClass, TEXT("Manager_StaticMeshActor_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_StaticMeshActor::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_StaticMeshActor::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerStaticMeshActor* GetManagerStaticMeshActor = Get_GetManagerStaticMeshActor(InRoot);
	UCsManager_StaticMeshActor* Manager_StaticMeshActor		= GetManagerStaticMeshActor->GetManager_StaticMeshActor();
	Manager_StaticMeshActor->CleanUp();

	GetManagerStaticMeshActor->SetManager_StaticMeshActor(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_StaticMeshActor::Shutdown: Manager has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_StaticMeshActor::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerStaticMeshActor(InRoot)->GetManager_StaticMeshActor() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerStaticMeshActor* UCsManager_StaticMeshActor::Get_GetManagerStaticMeshActor(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_StaticMeshActor::Get_GetManagerStaticMeshActor: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_StaticMeshActor::Get_GetManagerStaticMeshActor: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_StaticMeshActor::Get_GetManagerStaticMeshActor: Manager_Singleton is NULL."));

	ICsGetManagerStaticMeshActor* GetManagerStaticMeshActor = Cast<ICsGetManagerStaticMeshActor>(Manager_Singleton);

	checkf(GetManagerStaticMeshActor, TEXT("UCsManager_StaticMeshActor::Get_GetManagerStaticMeshActor: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerStaticMeshActor."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerStaticMeshActor;
}

/*static*/ ICsGetManagerStaticMeshActor* UCsManager_StaticMeshActor::GetSafe_GetManagerStaticMeshActor(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_StaticMeshActor::GetSafe_GetManagerStaticMeshActor: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_StaticMeshActor::GetSafe_GetManagerStaticMeshActor: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_StaticMeshActor::GetSafe_GetManagerStaticMeshActor: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetManagerStaticMeshActor>(Manager_Singleton);
}

/*static*/ UCsManager_StaticMeshActor* UCsManager_StaticMeshActor::GetSafe(UObject* Object)
{
	if (ICsGetManagerStaticMeshActor* GetManagerStaticMeshActor = GetSafe_GetManagerStaticMeshActor(Object))
		return GetManagerStaticMeshActor->GetManager_StaticMeshActor();
	return nullptr;
}

/*static*/ UCsManager_StaticMeshActor* UCsManager_StaticMeshActor::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game State
		if (UCsManager_StaticMeshActor* Manager = GetSafe(World->GetGameState()))
			return Manager;

		UE_LOG(LogCs, Warning, TEXT("UCsManager_StaticMeshActor::GetFromWorldContextObject: Failed to Manager FX Actor of type UCsManager_StaticMeshActor from GameState."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_StaticMeshActor::Initialize()
{
	SetupInternal();

	bInitialized = true;
}

/*static*/ bool UCsManager_StaticMeshActor::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_StaticMeshActor::CleanUp()
{
	Internal.Shutdown();
	Pool.Reset();

	bInitialized = false;
}

	// Root
#pragma region

void UCsManager_StaticMeshActor::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// Internal
#pragma region

void UCsManager_StaticMeshActor::SetupInternal()
{
	// Delegates
	{
		// Log
		Internal.Log_Impl.BindUObject(this, &UCsManager_StaticMeshActor::Log);
		Internal.LogTransaction_Impl.BindUObject(this, &UCsManager_StaticMeshActor::LogTransaction);
		// Container
		Internal.ConstructContainer_Impl.BindUObject(this, &UCsManager_StaticMeshActor::ConstructContainer);
		// Payload
		Internal.ConstructPayload_Impl.BindUObject(this, &UCsManager_StaticMeshActor::ConstructPayload);
		// Pool
		Internal.OnAddToPool_Event.AddUObject(this, &UCsManager_StaticMeshActor::OnAddToPool);
		// Update
		Internal.OnPreUpdate_Pool_Impl.BindUObject(this, &UCsManager_StaticMeshActor::OnPreUpdate_Pool);
		Internal.OnUpdate_Object_Event.AddUObject(this, &UCsManager_StaticMeshActor::OnUpdate_Object);
		Internal.OnPostUpdate_Pool_Impl.BindUObject(this, &UCsManager_StaticMeshActor::OnPostUpdate_Pool);

		// Bind delegates for a script interface.
		Internal.Script_GetCache_Impl = Script_GetCache_Impl;
		Internal.Script_Allocate_Impl = Script_Allocate_Impl;
		Internal.Script_Deallocate_Impl = Script_Deallocate_Impl;
		Internal.Script_Update_Impl = Script_Update_Impl;
		Internal.Script_OnConstructObject_Impl = Script_OnConstructObject_Impl;
	}
#if !UE_BUILD_SHIPPING
	//if (FCsCVarToggleMap::Get().IsEnabled(NCsCVarToggle::EnableManagerStaticMeshActorUnitTest))
	//{
		// Do Nothing
	//}
	//else
#endif // #if !UE_BUILD_SHIPPING
		// If any settings have been set for Manager_Creep, apply them
	{
		UCsDeveloperSettings* ModuleSettings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(ModuleSettings, TEXT("UCsManager_StaticMeshActor::SetupInternal: Failed to get settings of type: UCsDeveloperSettings."));

		//Settings = ModuleSettings->Manager_StaticMeshActor;

		InitInternalFromSettings();
	}
}

void UCsManager_StaticMeshActor::InitInternalFromSettings()
{
	using namespace NCsManagerStaticMeshActor;

	const FString& Context = Str::InitInternalFromSettings;

	if (Settings.PoolParams.Num() > CS_EMPTY)
	{
		FCsManager_StaticMeshActor_Internal::FCsManagerPooledObjectMapParams Params;

		Params.Name  = TEXT("UCsManager_StaticMeshActor::FCsManager_StaticMeshActor_Internal");
		Params.World = MyRoot->GetWorld();

		for (const TPair<FECsStaticMeshActor, FCsSettings_Manager_StaticMeshActor_PoolParams>& Pair : Settings.PoolParams)
		{
			const FECsStaticMeshActor& Type								   = Pair.Key;
			const FCsSettings_Manager_StaticMeshActor_PoolParams& PoolParams = Pair.Value;

			FCsManagerPooledObjectParams& ObjectParams = Params.ObjectParams.Add(Type);

			// Get Class
			const FECsStaticMeshActorClass& ClassType = PoolParams.Class;

			checkf(EMCsStaticMeshActorClass::Get().IsValidEnum(ClassType), TEXT("%s: Class for NOT Valid."), *Context, ClassType.ToChar());

			//FCsStaticMeshActorPooled* StaticMeshActor = GetStaticMeshActorChecked(Context, ClassType);
			UClass* Class							  = nullptr;//StaticMeshActor->GetClass();

			checkf(Class, TEXT("%s: Failed to get class for Type: %s ClassType: %s."), *Context, Type.ToChar(), ClassType.ToChar());

			ObjectParams.Name							  = Params.Name + TEXT("_") + Type.ToChar();
			ObjectParams.World							  = Params.World;
			ObjectParams.ConstructParams.Outer			  = this;
			ObjectParams.ConstructParams.Class			  = Class;
			ObjectParams.ConstructParams.ConstructionType = ECsPooledObjectConstruction::Actor;
			ObjectParams.bConstructPayloads				  = true;
			ObjectParams.PayloadSize					  = PoolParams.PayloadSize;
			ObjectParams.bCreatePool					  = true;
			ObjectParams.PoolSize						  = PoolParams.PoolSize;
		}

		InitInternal(Params);
	}
}

void UCsManager_StaticMeshActor::InitInternal(const FCsManager_StaticMeshActor_Internal::FCsManagerPooledObjectMapParams& Params)
{
	// Add CVars
	{
		FCsManager_StaticMeshActor_Internal::FCsManagerPooledObjectMapParams& P = const_cast<FCsManager_StaticMeshActor_Internal::FCsManagerPooledObjectMapParams&>(Params);

		for (TPair<FECsStaticMeshActor, FCsManagerPooledObjectParams>& Pair : P.ObjectParams)
		{
			FCsManagerPooledObjectParams& ObjectParams = Pair.Value;

			// Scoped Timer CVars
			ObjectParams.ScopedGroup = NCsScopedGroup::ManagerStaticMeshActor;

			ObjectParams.CreatePoolScopedTimerCVar		= NCsCVarLog::LogManagerStaticMeshActorScopedTimerCreatePool;
			ObjectParams.UpdateScopedTimerCVar			= NCsCVarLog::LogManagerStaticMeshActorScopedTimerUpdate;
			ObjectParams.UpdateObjectScopedTimerCVar	= NCsCVarLog::LogManagerStaticMeshActorScopedTimerUpdateObject;
			ObjectParams.AllocateScopedTimerCVar		= NCsCVarLog::LogManagerStaticMeshActorScopedTimerAllocate;
			ObjectParams.AllocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerStaticMeshActorScopedTimerAllocateObject;
			ObjectParams.DeallocateScopedTimerCVar		= NCsCVarLog::LogManagerStaticMeshActorScopedTimerDeallocate;
			ObjectParams.DeallocateObjectScopedTimerCVar = NCsCVarLog::LogManagerStaticMeshActorScopedTimerDeallocateObject;
			ObjectParams.SpawnScopedTimerCVar			= NCsCVarLog::LogManagerStaticMeshActorScopedTimerSpawn;
			ObjectParams.DestroyScopedTimerCVar			= NCsCVarLog::LogManagerStaticMeshActorScopedTimerDestroy;
		}
	}
	Internal.Init(Params);
}

void UCsManager_StaticMeshActor::Clear()
{
	Internal.Clear();
}

	// Pool
#pragma region

void UCsManager_StaticMeshActor::CreatePool(const FECsStaticMeshActor& Type, const int32& Size)
{
	const int32& PoolSize = Internal.GetPoolSize(Type);

	if (PoolSize > CS_EMPTY)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_StaticMeshActor::CreatePool: Pool for Sound: %s has already been created with Size: %d."), Type.ToChar(), PoolSize);
	}

	Internal.CreatePool(Type, Size);
}

TBaseDelegate<FCsStaticMeshActorPooled*, const FECsStaticMeshActor&>& UCsManager_StaticMeshActor::GetConstructContainer_Impl()
{
	return Internal.ConstructContainer_Impl;
}

FCsStaticMeshActorPooled* UCsManager_StaticMeshActor::ConstructContainer(const FECsStaticMeshActor& Type)
{
	return new FCsStaticMeshActorPooled();
}

TMulticastDelegate<void, const FCsStaticMeshActorPooled*, const FCsManagerPooledObjectConstructParams&>& UCsManager_StaticMeshActor::GetOnConstructObject_Event(const FECsStaticMeshActor& Type)
{
	return Internal.GetOnConstructObject_Event(Type);
}

		// Add
#pragma region

			// Pool
#pragma region

const FCsStaticMeshActorPooled* UCsManager_StaticMeshActor::AddToPool(const FECsStaticMeshActor& Type, ICsStaticMeshActor* Object)
{
	return Internal.AddToPool(Type, Object);
}

const FCsStaticMeshActorPooled* UCsManager_StaticMeshActor::AddToPool(const FECsStaticMeshActor& Type, const FCsStaticMeshActorPooled* Object)
{
	return Internal.AddToPool(Type, Object->GetObject());
}

const FCsStaticMeshActorPooled* UCsManager_StaticMeshActor::AddToPool(const FECsStaticMeshActor& Type, UObject* Object)
{
	return Internal.AddToPool(Type, Object);
}

void UCsManager_StaticMeshActor::OnAddToPool(const FECsStaticMeshActor& Type, const FCsStaticMeshActorPooled* Object)
{
	Pool.Add(Object->GetObject());
}

#pragma endregion Pool

			// Allocated Objects
#pragma region

const FCsStaticMeshActorPooled* UCsManager_StaticMeshActor::AddToAllocatedObjects(const FECsStaticMeshActor& Type, ICsStaticMeshActor* Sound, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, Sound, Object);
}

const FCsStaticMeshActorPooled* UCsManager_StaticMeshActor::AddToAllocatedObjects(const FECsStaticMeshActor& Type, ICsStaticMeshActor* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

const FCsStaticMeshActorPooled* UCsManager_StaticMeshActor::AddToAllocatedObjects(const FECsStaticMeshActor& Type, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

#pragma endregion Allocated Objects

#pragma endregion Add

const TArray<FCsStaticMeshActorPooled*>& UCsManager_StaticMeshActor::GetPool(const FECsStaticMeshActor& Type)
{
	return Internal.GetPool(Type);
}

const TArray<FCsStaticMeshActorPooled*>& UCsManager_StaticMeshActor::GetAllocatedObjects(const FECsStaticMeshActor& Type)
{
	return Internal.GetAllocatedObjects(Type);
}

const int32& UCsManager_StaticMeshActor::GetPoolSize(const FECsStaticMeshActor& Type)
{
	return Internal.GetPoolSize(Type);
}

int32 UCsManager_StaticMeshActor::GetAllocatedObjectsSize(const FECsStaticMeshActor& Type)
{
	return Internal.GetAllocatedObjectsSize(Type);
}

bool UCsManager_StaticMeshActor::IsExhausted(const FECsStaticMeshActor& Type)
{
	return Internal.IsExhausted(Type);
}

	// Find
#pragma region

const FCsStaticMeshActorPooled* UCsManager_StaticMeshActor::FindObject(const FECsStaticMeshActor& Type, const int32& Index)
{
	return Internal.FindObject(Type, Index);
}

const FCsStaticMeshActorPooled* UCsManager_StaticMeshActor::FindObject(const FECsStaticMeshActor& Type, ICsStaticMeshActor* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsStaticMeshActorPooled* UCsManager_StaticMeshActor::FindObject(const FECsStaticMeshActor& Type, UObject* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsStaticMeshActorPooled* UCsManager_StaticMeshActor::FindSafeObject(const FECsStaticMeshActor& Type, const int32& Index)
{
	return Internal.FindSafeObject(Type, Index);
}

const FCsStaticMeshActorPooled* UCsManager_StaticMeshActor::FindSafeObject(const FECsStaticMeshActor& Type, ICsStaticMeshActor* Object)
{
	return Internal.FindSafeObject(Type, Object);
}

const FCsStaticMeshActorPooled* UCsManager_StaticMeshActor::FindSafeObject(const FECsStaticMeshActor& Type, UObject* Object)
{
	return Internal.FindSafeObject(Type, Object);
}

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region

void UCsManager_StaticMeshActor::Update(const FCsDeltaTime& DeltaTime)
{
	Internal.Update(DeltaTime);
}

void UCsManager_StaticMeshActor::OnPreUpdate_Pool(const FECsStaticMeshActor& Type)
{
	CurrentUpdatePoolType		 = Type;
	CurrentUpdatePoolObjectIndex = 0;
}

void UCsManager_StaticMeshActor::OnUpdate_Object(const FECsStaticMeshActor& Type, const FCsStaticMeshActorPooled* Object)
{
	++CurrentUpdatePoolObjectIndex;
}

void UCsManager_StaticMeshActor::OnPostUpdate_Pool(const FECsStaticMeshActor& Type)
{
}

#pragma endregion Update

	// Payload
#pragma region

void UCsManager_StaticMeshActor::ConstructPayloads(const FECsStaticMeshActor& Type, const int32& Size)
{
	Internal.ConstructPayloads(Type, Size);
}

ICsPayload_StaticMeshActor* UCsManager_StaticMeshActor::ConstructPayload(const FECsStaticMeshActor& Type)
{
	return new FCsPayload_StaticMeshActorImpl();
}

ICsPayload_StaticMeshActor* UCsManager_StaticMeshActor::AllocatePayload(const FECsStaticMeshActor& Type)
{
	return Internal.AllocatePayload(Type);
}

#pragma endregion Payload

	// Spawn
#pragma region

const FCsStaticMeshActorPooled* UCsManager_StaticMeshActor::Spawn(const FECsStaticMeshActor& Type, ICsPayload_StaticMeshActor* Payload)
{
	if (Internal.IsExhausted(Type))
	{
		const FCsStaticMeshActorPooled* AllocatedHead = Internal.GetAllocatedHeadObject(Type);

#if !UE_BUILD_SHIPPING
		if (UObject* Object = AllocatedHead->GetObject())
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_StaticMeshActor::Spawn: Deallocating object: %s as pool for Type: %s is exhausted."), *(Object->GetName()), Type.ToChar());
		}
#endif // #if !UE_BUILD_SHIPPING

		Internal.Destroy(Type, AllocatedHead);
	}
	return Internal.Spawn(Type, Payload);
}

#pragma endregion Spawn

	// Destroy
#pragma region

bool UCsManager_StaticMeshActor::Destroy(const FECsStaticMeshActor& Type, ICsStaticMeshActor* Object)
{
	return Internal.Destroy(Type, Object);
}

bool UCsManager_StaticMeshActor::Destroy(ICsStaticMeshActor* Object)
{
	return Internal.Destroy(Object);
}

#pragma endregion Destroy

	// Log
#pragma region

void UCsManager_StaticMeshActor::Log(const FString& Str)
{
	UE_LOG(LogCs, Warning, TEXT("%s"), *Str);
}

void UCsManager_StaticMeshActor::LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsStaticMeshActorPooled* Object)
{
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerStaticMeshActorTransactions))
	{
		const FString& TransactionAsString = EMCsPoolTransaction::Get().ToString(Transaction);

		ICsPooledObject* Interface  = Object->GetInterface();
		const FString ClassName		= Object->GetObject()->GetClass()->GetName();
		const FString ObjectName	= Object->GetObject()->GetName();
		const UObject* ObjectOwner	= Interface->GetCache()->GetOwner();
		const FString OwnerName		= ObjectOwner ? ObjectOwner->GetName() : NCsCached::Str::None;
		const UObject* Parent		= Interface->GetCache()->GetParent();
		const FString ParentName	= Parent ? Parent->GetName() : NCsCached::Str::None;
		const float CurrentTime		= GetWorld()->GetTimeSeconds();

		if (ObjectOwner && Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s %s of Type: %s for %s attached to %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *OwnerName, *ParentName, CurrentTime);
		}
		else 
		if (ObjectOwner)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s %s of Type: %s for %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *OwnerName, CurrentTime);
		}
		else
		if (Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s %s of Type: %s attached to %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *ParentName, CurrentTime);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s %s of Type: %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, CurrentTime);
		}
	}
}

#pragma endregion Log

#pragma endregion Internal