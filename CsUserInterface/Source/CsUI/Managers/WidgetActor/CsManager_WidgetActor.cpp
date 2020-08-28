// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/WidgetActor/CsManager_WidgetActor.h"
#include "CsUI.h"

// CVars
#include "Managers/WidgetActor/CsCVars_Manager_WidgetActor.h"
// Library
#include "Library/CsLibrary_Property.h"
// Settings
#include "Settings/CsUserInterfaceSettings.h"
// FX
#include "Managers/WidgetActor/Payload/CsPayload_WidgetActorImpl.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/WidgetActor/CsGetManagerWidgetActor.h"

#include "Library/CsLibrary_Common.h"

#include "Classes/Engine/World.h"
#include "Classes/Engine/Engine.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerWidgetActor
{
	namespace Str
	{
		const FString InitInternalFromSettings = TEXT("UCsManager_WidgetActor::InitInternalFromSettings");
		const FString PopulateDataMapFromSettings = TEXT("UCsManager_WidgetActor::PopulateDataMapFromSettings");
	}

	namespace Name
	{
	}
}

#pragma endregion Cached

// Internal
#pragma region

FCsManager_WidgetActor_Internal::FCsManager_WidgetActor_Internal()
	: Super()
{
}

#pragma endregion Internal

// static initializations
UCsManager_WidgetActor* UCsManager_WidgetActor::s_Instance;
bool UCsManager_WidgetActor::s_bShutdown = false;

UCsManager_WidgetActor::UCsManager_WidgetActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsManager_WidgetActor* UCsManager_WidgetActor::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerWidgetActor(InRoot)->GetManager_WidgetActor();
#else
	if (s_bShutdown)
	{
		UE_LOG(LogCsUI, Warning, TEXT("UCsManager_WidgetActor::Get: Manager has already shutdown."));
		return nullptr;
	}
	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_WidgetActor::IsValid(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerWidgetActor(InRoot)->GetManager_WidgetActor() != nullptr;
#else
	return s_Instance != nullptr;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_WidgetActor::Init(UObject* InRoot, TSubclassOf<UCsManager_WidgetActor> ManagerWidgetActorClass, UObject* InOuter /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerWidgetActor* GetManagerWidgetActor = Get_GetManagerWidgetActor(InRoot);

	UCsManager_WidgetActor* Manager_WidgetActor = GetManagerWidgetActor->GetManager_WidgetActor();

	if (!Manager_WidgetActor)
	{
		Manager_WidgetActor = NewObject<UCsManager_WidgetActor>(InOuter ? InOuter : InRoot, ManagerWidgetActorClass, TEXT("Manager_WidgetActor_Singleton"), RF_Transient | RF_Public);

		GetManagerWidgetActor->SetManager_WidgetActor(Manager_WidgetActor);

		Manager_WidgetActor->SetMyRoot(InRoot);
		Manager_WidgetActor->Initialize();
	}
	else
	{
		UE_LOG(LogCsUI, Warning, TEXT("UCsManager_WidgetActor::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_WidgetActor>(GetTransientPackage(), ManagerWidgetActorClass, TEXT("Manager_WidgetActor_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCsUI, Warning, TEXT("UCsManager_WidgetActor::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_WidgetActor::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerWidgetActor* GetManagerWidgetActor = Get_GetManagerWidgetActor(InRoot);
	UCsManager_WidgetActor* Manager_WidgetActor	= GetManagerWidgetActor->GetManager_WidgetActor();
	Manager_WidgetActor->CleanUp();

	GetManagerWidgetActor->SetManager_WidgetActor(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCsUI, Warning, TEXT("UCsManager_WidgetActor::Shutdown: Manager has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_WidgetActor::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerWidgetActor(InRoot)->GetManager_WidgetActor() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerWidgetActor* UCsManager_WidgetActor::Get_GetManagerWidgetActor(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_WidgetActor::Get_GetManagerWidgetActor: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_WidgetActor::Get_GetManagerWidgetActor: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_WidgetActor::Get_GetManagerWidgetActor: Manager_Singleton is NULL."));

	ICsGetManagerWidgetActor* GetManagerWidgetActor = Cast<ICsGetManagerWidgetActor>(Manager_Singleton);

	checkf(GetManagerWidgetActor, TEXT("UCsManager_WidgetActor::Get_GetManagerWidgetActor: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerWidgetActor."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerWidgetActor;
}

/*static*/ ICsGetManagerWidgetActor* UCsManager_WidgetActor::GetSafe_GetManagerWidgetActor(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCsUI, Warning, TEXT("UCsManager_WidgetActor::GetSafe_GetManagerWidgetActor: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCsUI, Warning, TEXT("UCsManager_WidgetActor::GetSafe_GetManagerWidgetActor: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCsUI, Warning, TEXT("UCsManager_WidgetActor::GetSafe_GetManagerWidgetActor: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetManagerWidgetActor>(Manager_Singleton);
}

/*static*/ UCsManager_WidgetActor* UCsManager_WidgetActor::GetSafe(UObject* Object)
{
	if (ICsGetManagerWidgetActor* GetManagerWidgetActor = GetSafe_GetManagerWidgetActor(Object))
		return GetManagerWidgetActor->GetManager_WidgetActor();
	return nullptr;
}

/*static*/ UCsManager_WidgetActor* UCsManager_WidgetActor::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game State
		if (UCsManager_WidgetActor* Manager = GetSafe(World->GetGameState()))
			return Manager;

		UE_LOG(LogCsUI, Warning, TEXT("UCsManager_WidgetActor::GetFromWorldContextObject: Failed to Manager FX Actor of type UCsManager_WidgetActor from GameState."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_WidgetActor::Initialize()
{
	SetupInternal();

	bInitialized = true;
}

/*static*/ bool UCsManager_WidgetActor::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_WidgetActor::CleanUp()
{
	Internal.Shutdown();
	Pool.Reset();

	bInitialized = false;
}

	// Root
#pragma region

void UCsManager_WidgetActor::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// Internal
#pragma region

void UCsManager_WidgetActor::SetupInternal()
{
	// Delegates
	{
		// Log
		Internal.LogTransaction_Impl.BindUObject(this, &UCsManager_WidgetActor::LogTransaction);
		// Container
		Internal.ConstructContainer_Impl.BindUObject(this, &UCsManager_WidgetActor::ConstructContainer);
		// Payload
		Internal.ConstructPayload_Impl.BindUObject(this, &UCsManager_WidgetActor::ConstructPayload);
		// Pool
		Internal.OnAddToPool_Event.AddUObject(this, &UCsManager_WidgetActor::OnAddToPool);
		// Update
		Internal.OnPreUpdate_Pool_Impl.BindUObject(this, &UCsManager_WidgetActor::OnPreUpdate_Pool);
		Internal.OnUpdate_Object_Event.AddUObject(this, &UCsManager_WidgetActor::OnUpdate_Object);
		Internal.OnPostUpdate_Pool_Impl.BindUObject(this, &UCsManager_WidgetActor::OnPostUpdate_Pool);

		// Bind delegates for a script interface.
		Internal.Script_GetCache_Impl = Script_GetCache_Impl;
		Internal.Script_Allocate_Impl = Script_Allocate_Impl;
		Internal.Script_Deallocate_Impl = Script_Deallocate_Impl;
		Internal.Script_Update_Impl = Script_Update_Impl;
	}

#if !UE_BUILD_SHIPPING
	//if (FCsCVarToggleMap::Get().IsEnabled(NCsCVarToggle::EnableManagerWidgetActorUnitTest))
	//{
		// Do Nothing
	//}
	//else
#endif // #if !UE_BUILD_SHIPPING
		// If any settings have been set for Manager_WidgetActor, apply them
	{
		UCsUserInterfaceSettings* ModuleSettings = GetMutableDefault<UCsUserInterfaceSettings>();

		checkf(ModuleSettings, TEXT("UCsManager_WidgetActor::SetupInternal: Failed to get settings of type: UCsUserInterfaceSettings."));

		Settings = ModuleSettings->Manager_WidgetActor;

		// Populate TypeMapArray
		{
			const int32& Count = EMCsWidgetActor::Get().Num();

			TypeMapArray.Reserve(Count);

			for (const FECsWidgetActor& Type : EMCsWidgetActor::Get())
			{
				TypeMapArray.Add(Type);
			}
			/*
			for (const TPair<FECsProjectile, FECsProjectile>& Pair : Settings.TypeMap)
			{
				TypeMapArray[Pair.Key.GetValue()] = Pair.Value;
			}
			*/
		}

		InitInternalFromSettings();
	}
}

void UCsManager_WidgetActor::InitInternalFromSettings()
{
	using namespace NCsManagerWidgetActor;

	const FString& Context = Str::InitInternalFromSettings;

	//PopulateClassMapFromSettings();
	//PopulateDataMapFromSettings();

	if (Settings.PoolParams.Num() > CS_EMPTY)
	{
		FCsManager_WidgetActor_Internal::FCsManagerPooledObjectMapParams Params;

		Params.Name  = TEXT("UCsManager_WidgetActor::FCsManager_WidgetActor_Internal");
		Params.World = MyRoot->GetWorld();

		for (const TPair<FECsWidgetActor, FCsSettings_Manager_WidgetActor_PoolParams>& Pair : Settings.PoolParams)
		{
			const FECsWidgetActor& Type									= Pair.Key;
			const FCsSettings_Manager_WidgetActor_PoolParams& PoolParams = Pair.Value;

			FCsManagerPooledObjectParams& ObjectParams = Params.ObjectParams.Add(Type);

			// Get Class
			const FECsWidgetActorClass& ClassType = PoolParams.Class;

			checkf(EMCsWidgetActorClass::Get().IsValidEnum(ClassType), TEXT("%s: Class for NOT Valid."), *Context, ClassType.ToChar());

			FCsWidgetActorPooled* WidgetActor = nullptr;//GetWidgetActorChecked(Context, ClassType);
			UClass* Class					  = WidgetActor->GetClass();

			checkf(Class, TEXT("%s: Failed to get class for Type: %s ClassType: %s."), *Context, Type.ToChar(), ClassType.ToChar());

			ObjectParams.Name							  = Params.Name + TEXT("_") + Type.ToChar();
			ObjectParams.World							  = Params.World;
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

void UCsManager_WidgetActor::InitInternal(const FCsManager_WidgetActor_Internal::FCsManagerPooledObjectMapParams& Params)
{
	// Add CVars
	{
		FCsManager_WidgetActor_Internal::FCsManagerPooledObjectMapParams& P = const_cast<FCsManager_WidgetActor_Internal::FCsManagerPooledObjectMapParams&>(Params);

		for (TPair<FECsWidgetActor, FCsManagerPooledObjectParams>& Pair : P.ObjectParams)
		{
			FCsManagerPooledObjectParams& ObjectParams = Pair.Value;

			// Scoped Timer CVars
			ObjectParams.ScopedGroup = NCsScopedGroup::ManagerWidgetActor;

			ObjectParams.CreatePoolScopedTimerCVar		= NCsCVarLog::LogManagerWidgetActorScopedTimerCreatePool;
			ObjectParams.UpdateScopedTimerCVar			= NCsCVarLog::LogManagerWidgetActorScopedTimerUpdate;
			ObjectParams.UpdateObjectScopedTimerCVar	= NCsCVarLog::LogManagerWidgetActorScopedTimerUpdateObject;
			ObjectParams.AllocateScopedTimerCVar		= NCsCVarLog::LogManagerWidgetActorScopedTimerAllocate;
			ObjectParams.AllocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerWidgetActorScopedTimerAllocateObject;
			ObjectParams.DeallocateScopedTimerCVar		= NCsCVarLog::LogManagerWidgetActorScopedTimerDeallocate;
			ObjectParams.DeallocateObjectScopedTimerCVar = NCsCVarLog::LogManagerWidgetActorScopedTimerDeallocateObject;
			ObjectParams.SpawnScopedTimerCVar			= NCsCVarLog::LogManagerWidgetActorScopedTimerSpawn;
			ObjectParams.DestroyScopedTimerCVar			= NCsCVarLog::LogManagerWidgetActorScopedTimerDestroy;
		}
	}
	Internal.Init(Params);
}

void UCsManager_WidgetActor::Clear()
{
	Internal.Clear();
}

	// Pool
#pragma region

void UCsManager_WidgetActor::CreatePool(const FECsWidgetActor& Type, const int32& Size)
{
	const int32& PoolSize = Internal.GetPoolSize(Type);

	if (PoolSize > CS_EMPTY)
	{
		UE_LOG(LogCsUI, Warning, TEXT("UCsManager_WidgetActor::CreatePool: Pool for Creep: %s has already been created with Size: %d."), Type.ToChar(), PoolSize);
	}

	Internal.CreatePool(Type, Size);
}

TBaseDelegate<FCsWidgetActorPooled*, const FECsWidgetActor&>& UCsManager_WidgetActor::GetConstructContainer_Impl()
{
	return Internal.ConstructContainer_Impl;
}

FCsWidgetActorPooled* UCsManager_WidgetActor::ConstructContainer(const FECsWidgetActor& Type)
{
	return new FCsWidgetActorPooled();
}

TMulticastDelegate<void, const FCsWidgetActorPooled*>& UCsManager_WidgetActor::GetOnConstructObject_Event(const FECsWidgetActor& Type)
{
	return Internal.GetOnConstructObject_Event(Type);
}

		// Add
#pragma region

			// Pool
#pragma region

const FCsWidgetActorPooled* UCsManager_WidgetActor::AddToPool(const FECsWidgetActor& Type, ICsWidgetActor* Object)
{
	return Internal.AddToPool(Type, Object);
}

const FCsWidgetActorPooled* UCsManager_WidgetActor::AddToPool(const FECsWidgetActor& Type, const FCsWidgetActorPooled* Object)
{
	return Internal.AddToPool(Type, Object->GetObject());
}

const FCsWidgetActorPooled* UCsManager_WidgetActor::AddToPool(const FECsWidgetActor& Type, UObject* Object)
{
	return Internal.AddToPool(Type, Object);
}

void UCsManager_WidgetActor::OnAddToPool(const FECsWidgetActor& Type, const FCsWidgetActorPooled* Object)
{
	Pool.Add(Object->GetObject());
}

#pragma endregion Pool

			// Allocated Objects
#pragma region

const FCsWidgetActorPooled* UCsManager_WidgetActor::AddToAllocatedObjects(const FECsWidgetActor& Type, ICsWidgetActor* WidgetActor, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, WidgetActor, Object);
}

const FCsWidgetActorPooled* UCsManager_WidgetActor::AddToAllocatedObjects(const FECsWidgetActor& Type, ICsWidgetActor* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

const FCsWidgetActorPooled* UCsManager_WidgetActor::AddToAllocatedObjects(const FECsWidgetActor& Type, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

#pragma endregion Allocated Objects

#pragma endregion Add

const TArray<FCsWidgetActorPooled*>& UCsManager_WidgetActor::GetPool(const FECsWidgetActor& Type)
{
	return Internal.GetPool(Type);
}

const TArray<FCsWidgetActorPooled*>& UCsManager_WidgetActor::GetAllocatedObjects(const FECsWidgetActor& Type)
{
	return Internal.GetAllocatedObjects(Type);
}

const int32& UCsManager_WidgetActor::GetPoolSize(const FECsWidgetActor& Type)
{
	return Internal.GetPoolSize(Type);
}

int32 UCsManager_WidgetActor::GetAllocatedObjectsSize(const FECsWidgetActor& Type)
{
	return Internal.GetAllocatedObjectsSize(Type);
}

bool UCsManager_WidgetActor::IsExhausted(const FECsWidgetActor& Type)
{
	return Internal.IsExhausted(Type);
}

	// Find
#pragma region

const FCsWidgetActorPooled* UCsManager_WidgetActor::FindObject(const FECsWidgetActor& Type, const int32& Index)
{
	return Internal.FindObject(Type, Index);
}

const FCsWidgetActorPooled* UCsManager_WidgetActor::FindObject(const FECsWidgetActor& Type, ICsWidgetActor* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsWidgetActorPooled* UCsManager_WidgetActor::FindObject(const FECsWidgetActor& Type, UObject* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsWidgetActorPooled* UCsManager_WidgetActor::FindSafeObject(const FECsWidgetActor& Type, const int32& Index)
{
	return Internal.FindSafeObject(Type, Index);
}

const FCsWidgetActorPooled* UCsManager_WidgetActor::FindSafeObject(const FECsWidgetActor& Type, ICsWidgetActor* Object)
{
	return Internal.FindSafeObject(Type, Object);
}

const FCsWidgetActorPooled* UCsManager_WidgetActor::FindSafeObject(const FECsWidgetActor& Type, UObject* Object)
{
	return Internal.FindSafeObject(Type, Object);
}

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region

void UCsManager_WidgetActor::Update(const FCsDeltaTime& DeltaTime)
{
	Internal.Update(DeltaTime);
}

void UCsManager_WidgetActor::OnPreUpdate_Pool(const FECsWidgetActor& Type)
{
	CurrentUpdatePoolType		 = Type;
	CurrentUpdatePoolObjectIndex = 0;
}

void UCsManager_WidgetActor::OnUpdate_Object(const FECsWidgetActor& Type, const FCsWidgetActorPooled* Object)
{
	++CurrentUpdatePoolObjectIndex;
}

void UCsManager_WidgetActor::OnPostUpdate_Pool(const FECsWidgetActor& Type)
{
}

#pragma endregion Update

	// Payload
#pragma region

void UCsManager_WidgetActor::ConstructPayloads(const FECsWidgetActor& Type, const int32& Size)
{
	Internal.ConstructPayloads(Type, Size);
}

ICsPayload_WidgetActor* UCsManager_WidgetActor::ConstructPayload(const FECsWidgetActor& Type)
{
	return new FCsPayload_WidgetActorImpl();
}

ICsPayload_WidgetActor* UCsManager_WidgetActor::AllocatePayload(const FECsWidgetActor& Type)
{
	return Internal.AllocatePayload(Type);
}

#pragma endregion Payload

	// Spawn
#pragma region

const FCsWidgetActorPooled* UCsManager_WidgetActor::Spawn(const FECsWidgetActor& Type, ICsPayload_WidgetActor* Payload)
{
	return Internal.Spawn(Type, Payload);
}

#pragma endregion Spawn

	// Destroy
#pragma region

bool UCsManager_WidgetActor::Destroy(const FECsWidgetActor& Type, ICsWidgetActor* Object)
{
	return Internal.Destroy(Type, Object);
}

bool UCsManager_WidgetActor::Destroy(ICsWidgetActor* Object)
{
	return Internal.Destroy(Object);
}

#pragma endregion Destroy

	// Log
#pragma region

void UCsManager_WidgetActor::Log(const FString& Str)
{
	UE_LOG(LogCsUI, Warning, TEXT("%s"), *Str);
}

void UCsManager_WidgetActor::LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsWidgetActorPooled* Object)
{
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerWidgetActorTransactions))
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
			UE_LOG(LogCsUI, Warning, TEXT("%s: %s %s of Type: %s for %s attached to %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *OwnerName, *ParentName, CurrentTime);
		}
		else 
		if (ObjectOwner)
		{
			UE_LOG(LogCsUI, Warning, TEXT("%s: %s %s of Type: %s for %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *OwnerName, CurrentTime);
		}
		else
		if (Parent)
		{
			UE_LOG(LogCsUI, Warning, TEXT("%s: %s %s of Type: %s attached to %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *ParentName, CurrentTime);
		}
		else
		{
			UE_LOG(LogCsUI, Warning, TEXT("%s: %s %s of Type: %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, CurrentTime);
		}
	}
}

#pragma endregion Log

#pragma endregion Internal