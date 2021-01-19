// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/SkeletalMesh/CsManager_SkeletalMeshActor.h"
#include "CsCore.h"

// CVars
#include "Managers/SkeletalMesh/CsCVars_Manager_SkeletalMeshActor.h"
// Library
#include "Library/CsLibrary_Property.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Managers
#include "Managers/Data/CsManager_Data.h"
// Data
#include "Managers/SkeletalMesh/Data/CsData_SkeletalMeshActorImpl.h"
// SkeletalMeshActor
#include "Managers/SkeletalMesh/Payload/CsPayload_SkeletalMeshActorImpl.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/SkeletalMesh/CsGetManagerSkeletalMeshActor.h"

#include "Library/CsLibrary_Common.h"

#include "Engine/World.h"
#include "Engine/Engine.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerSkeletalMeshActor
{
	namespace Str
	{
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_SkeletalMeshActor, InitInternalFromSettings);
	}

	namespace Name
	{
	}
}

#pragma endregion Cached

// Internal
#pragma region

namespace NCsSkeletalMeshActor
{
	FManager::FManager()
		: Super()
	{
	}
}

#pragma endregion Internal

// static initializations
UCsManager_SkeletalMeshActor* UCsManager_SkeletalMeshActor::s_Instance;
bool UCsManager_SkeletalMeshActor::s_bShutdown = false;

UCsManager_SkeletalMeshActor::UCsManager_SkeletalMeshActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsManager_SkeletalMeshActor* UCsManager_SkeletalMeshActor::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerSkeletalMeshActor(InRoot)->GetManager_SkeletalMeshActor();
#else
	if (s_bShutdown)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_SkeletalMeshActor::Get: Manager has already shutdown."));
		return nullptr;
	}
	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_SkeletalMeshActor::IsValid(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerSkeletalMeshActor(InRoot)->GetManager_SkeletalMeshActor() != nullptr;
#else
	return s_Instance != nullptr;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_SkeletalMeshActor::Init(UObject* InRoot, TSubclassOf<UCsManager_SkeletalMeshActor> ManagerSkeletalMeshActorClass, UObject* InOuter /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerSkeletalMeshActor* GetManagerSkeletalMeshActor = Get_GetManagerSkeletalMeshActor(InRoot);

	UCsManager_SkeletalMeshActor* Manager_SkeletalMeshActor = GetManagerSkeletalMeshActor->GetManager_SkeletalMeshActor();

	if (!Manager_SkeletalMeshActor)
	{
		Manager_SkeletalMeshActor = NewObject<UCsManager_SkeletalMeshActor>(InOuter ? InOuter : InRoot, ManagerSkeletalMeshActorClass, TEXT("Manager_SkeletalMeshActor_Singleton"), RF_Transient | RF_Public);

		GetManagerSkeletalMeshActor->SetManager_SkeletalMeshActor(Manager_SkeletalMeshActor);

		Manager_SkeletalMeshActor->SetMyRoot(InRoot);
		Manager_SkeletalMeshActor->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_SkeletalMeshActor::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_SkeletalMeshActor>(GetTransientPackage(), ManagerSkeletalMeshActorClass, TEXT("Manager_SkeletalMeshActor_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_SkeletalMeshActor::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_SkeletalMeshActor::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerSkeletalMeshActor* GetManagerSkeletalMeshActor = Get_GetManagerSkeletalMeshActor(InRoot);
	UCsManager_SkeletalMeshActor* Manager_SkeletalMeshActor		= GetManagerSkeletalMeshActor->GetManager_SkeletalMeshActor();
	Manager_SkeletalMeshActor->CleanUp();

	GetManagerSkeletalMeshActor->SetManager_SkeletalMeshActor(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_SkeletalMeshActor::Shutdown: Manager has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_SkeletalMeshActor::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerSkeletalMeshActor(InRoot)->GetManager_SkeletalMeshActor() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerSkeletalMeshActor* UCsManager_SkeletalMeshActor::Get_GetManagerSkeletalMeshActor(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_SkeletalMeshActor::Get_GetManagerSkeletalMeshActor: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_SkeletalMeshActor::Get_GetManagerSkeletalMeshActor: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_SkeletalMeshActor::Get_GetManagerSkeletalMeshActor: Manager_Singleton is NULL."));

	ICsGetManagerSkeletalMeshActor* GetManagerSkeletalMeshActor = Cast<ICsGetManagerSkeletalMeshActor>(Manager_Singleton);

	checkf(GetManagerSkeletalMeshActor, TEXT("UCsManager_SkeletalMeshActor::Get_GetManagerSkeletalMeshActor: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerSkeletalMeshActor."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerSkeletalMeshActor;
}

/*static*/ ICsGetManagerSkeletalMeshActor* UCsManager_SkeletalMeshActor::GetSafe_GetManagerSkeletalMeshActor(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_SkeletalMeshActor::GetSafe_GetManagerSkeletalMeshActor: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_SkeletalMeshActor::GetSafe_GetManagerSkeletalMeshActor: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_SkeletalMeshActor::GetSafe_GetManagerSkeletalMeshActor: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetManagerSkeletalMeshActor>(Manager_Singleton);
}

/*static*/ UCsManager_SkeletalMeshActor* UCsManager_SkeletalMeshActor::GetSafe(UObject* Object)
{
	if (ICsGetManagerSkeletalMeshActor* GetManagerSkeletalMeshActor = GetSafe_GetManagerSkeletalMeshActor(Object))
		return GetManagerSkeletalMeshActor->GetManager_SkeletalMeshActor();
	return nullptr;
}

/*static*/ UCsManager_SkeletalMeshActor* UCsManager_SkeletalMeshActor::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game State
		if (UCsManager_SkeletalMeshActor* Manager = GetSafe(World->GetGameState()))
			return Manager;

		UE_LOG(LogCs, Warning, TEXT("UCsManager_SkeletalMeshActor::GetFromWorldContextObject: Failed to Manager FX Actor of type UCsManager_SkeletalMeshActor from GameState."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_SkeletalMeshActor::Initialize()
{
	SetupInternal();

	bInitialized = true;
}

/*static*/ bool UCsManager_SkeletalMeshActor::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_SkeletalMeshActor::CleanUp()
{
	Internal.Shutdown();
	Pool.Reset();

	bInitialized = false;
}

	// Root
#pragma region

void UCsManager_SkeletalMeshActor::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// Internal
#pragma region

void UCsManager_SkeletalMeshActor::SetupInternal()
{
	// Delegates
	{
		// Log
		Internal.Log_Impl.BindUObject(this, &UCsManager_SkeletalMeshActor::Log);
		Internal.LogTransaction_Impl.BindUObject(this, &UCsManager_SkeletalMeshActor::LogTransaction);
		// Container
		Internal.ConstructContainer_Impl.BindUObject(this, &UCsManager_SkeletalMeshActor::ConstructContainer);
		// Payload
		Internal.ConstructPayload_Impl.BindUObject(this, &UCsManager_SkeletalMeshActor::ConstructPayload);
		// Pool
		Internal.OnAddToPool_Event.AddUObject(this, &UCsManager_SkeletalMeshActor::OnAddToPool);
		// Update
		Internal.OnPreUpdate_Pool_Impl.BindUObject(this, &UCsManager_SkeletalMeshActor::OnPreUpdate_Pool);
		Internal.OnUpdate_Object_Event.AddUObject(this, &UCsManager_SkeletalMeshActor::OnUpdate_Object);
		Internal.OnPostUpdate_Pool_Impl.BindUObject(this, &UCsManager_SkeletalMeshActor::OnPostUpdate_Pool);

		// Bind delegates for a script interface.
		Internal.Script_GetCache_Impl = Script_GetCache_Impl;
		Internal.Script_Allocate_Impl = Script_Allocate_Impl;
		Internal.Script_Deallocate_Impl = Script_Deallocate_Impl;
		Internal.Script_Update_Impl = Script_Update_Impl;
		Internal.Script_OnConstructObject_Impl = Script_OnConstructObject_Impl;
	}
#if !UE_BUILD_SHIPPING
	//if (FCsCVarToggleMap::Get().IsEnabled(NCsCVarToggle::EnableManagerSkeletalMeshActorUnitTest))
	//{
		// Do Nothing
	//}
	//else
#endif // #if !UE_BUILD_SHIPPING
		// If any settings have been set for Manager_Creep, apply them
	{
		UCsDeveloperSettings* ModuleSettings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(ModuleSettings, TEXT("UCsManager_SkeletalMeshActor::SetupInternal: Failed to get settings of type: UCsDeveloperSettings."));

		Settings = ModuleSettings->Manager_SkeletalMeshActor;

		InitInternalFromSettings();
	}
}

void UCsManager_SkeletalMeshActor::InitInternalFromSettings()
{
	using namespace NCsManagerSkeletalMeshActor;

	const FString& Context = Str::InitInternalFromSettings;

	if (Settings.PoolParams.Num() > CS_EMPTY)
	{
		typedef NCsSkeletalMeshActor::FManager::FParams ManagerParamsType;

		ManagerParamsType ManagerParams;

		ManagerParams.Name  = TEXT("UCsManager_SkeletalMeshActor::NCsSkeletalMeshActor::FManager");
		ManagerParams.World = MyRoot->GetWorld();

		for (const TPair<FECsSkeletalMeshActor, FCsSettings_Manager_SkeletalMeshActor_PoolParams>& Pair : Settings.PoolParams)
		{
			const FECsSkeletalMeshActor& Type							   = Pair.Key;
			const FCsSettings_Manager_SkeletalMeshActor_PoolParams& Params = Pair.Value;

			typedef NCsPooledObject::NManager::FPoolParams PoolParamsType;

			PoolParamsType& PoolParams = ManagerParams.ObjectParams.Add(Type);

			checkf(Params.Class.ToSoftObjectPath().IsValid(), TEXT("%s: Class for Type: %s is NOT a Valid Path."), *Context, Type.ToChar());

#if !UE_BUILD_SHIPPING
			if (!Params.Class.Get())
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Class @ for Type: %s is NOT already loaded in memory."), *Context, *(Params.Class.ToString()), Type.ToChar());
			}
#endif // #if !UE_BUILD_SHIPPING

			UClass* Class = Params.Class.LoadSynchronous();

			checkf(Class, TEXT("%s: Failed to load Class @ for Type: %s."), *Context, *(Params.Class.ToString()), Type.ToChar());

			ClassMap.Add(Type, Class);

			// FUTURE: If needed implement getting class via Enum
			/*
			// Get Class
			const FECsSkeletalMeshActorClass& ClassType = Params.Class;

			checkf(EMCsSkeletalMeshActorClass::Get().IsValidEnum(ClassType), TEXT("%s: Class for NOT Valid."), *Context, ClassType.ToChar());

			//FCsSkeletalMeshActorPooled* SkeletalMeshActor = GetSkeletalMeshActorChecked(Context, ClassType);
			UClass* Class									= SkeletalMeshActor->GetClass();

			checkf(Class, TEXT("%s: Failed to get class for Type: %s ClassType: %s."), *Context, Type.ToChar(), ClassType.ToChar());
			*/

			PoolParams.Name								= ManagerParams.Name + TEXT("_") + Type.ToChar();
			PoolParams.World							= ManagerParams.World;
			PoolParams.ConstructParams.Outer			= this;
			PoolParams.ConstructParams.Class			= Class;
			PoolParams.ConstructParams.ConstructionType = ECsPooledObjectConstruction::Actor;
			PoolParams.bConstructPayloads				= true;
			PoolParams.PayloadSize						= Params.PayloadSize;
			PoolParams.bCreatePool						= true;
			PoolParams.PoolSize							= Params.PoolSize;
		}

		InitInternal(ManagerParams);
	}
}

#define ManagerParamsType NCsSkeletalMeshActor::FManager::FParams
void UCsManager_SkeletalMeshActor::InitInternal(const ManagerParamsType& Params)
{
	// Add CVars
	{
		ManagerParamsType& P = const_cast<ManagerParamsType&>(Params);

		typedef NCsPooledObject::NManager::FPoolParams PoolParamsType;

		for (TPair<FECsSkeletalMeshActor, PoolParamsType>& Pair : P.ObjectParams)
		{
			PoolParamsType& PoolParams = Pair.Value;

			// Scoped Timer CVars
			PoolParams.ScopedGroup = NCsScopedGroup::ManagerSkeletalMeshActor;

			PoolParams.CreatePoolScopedTimerCVar		= NCsCVarLog::LogManagerSkeletalMeshActorScopedTimerCreatePool;
			PoolParams.UpdateScopedTimerCVar			= NCsCVarLog::LogManagerSkeletalMeshActorScopedTimerUpdate;
			PoolParams.UpdateObjectScopedTimerCVar		= NCsCVarLog::LogManagerSkeletalMeshActorScopedTimerUpdateObject;
			PoolParams.AllocateScopedTimerCVar			= NCsCVarLog::LogManagerSkeletalMeshActorScopedTimerAllocate;
			PoolParams.AllocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerSkeletalMeshActorScopedTimerAllocateObject;
			PoolParams.DeallocateScopedTimerCVar		= NCsCVarLog::LogManagerSkeletalMeshActorScopedTimerDeallocate;
			PoolParams.DeallocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerSkeletalMeshActorScopedTimerDeallocateObject;
			PoolParams.SpawnScopedTimerCVar				= NCsCVarLog::LogManagerSkeletalMeshActorScopedTimerSpawn;
			PoolParams.DestroyScopedTimerCVar			= NCsCVarLog::LogManagerSkeletalMeshActorScopedTimerDestroy;
		}
	}
	Internal.Init(Params);
}
#undef ManagerParamsType

void UCsManager_SkeletalMeshActor::Clear()
{
	Internal.Clear();
}

	// Pool
#pragma region

void UCsManager_SkeletalMeshActor::CreatePool(const FECsSkeletalMeshActor& Type, const int32& Size)
{
	const int32& PoolSize = Internal.GetPoolSize(Type);

	if (PoolSize > CS_EMPTY)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_SkeletalMeshActor::CreatePool: Pool for Sound: %s has already been created with Size: %d."), Type.ToChar(), PoolSize);
	}

	Internal.CreatePool(Type, Size);
}

TBaseDelegate<FCsSkeletalMeshActorPooled*, const FECsSkeletalMeshActor&>& UCsManager_SkeletalMeshActor::GetConstructContainer_Impl()
{
	return Internal.ConstructContainer_Impl;
}

FCsSkeletalMeshActorPooled* UCsManager_SkeletalMeshActor::ConstructContainer(const FECsSkeletalMeshActor& Type)
{
	return new FCsSkeletalMeshActorPooled();
}

#define ConstructParamsType NCsPooledObject::NManager::FConstructParams
TMulticastDelegate<void, const FCsSkeletalMeshActorPooled*, const ConstructParamsType&>& UCsManager_SkeletalMeshActor::GetOnConstructObject_Event(const FECsSkeletalMeshActor& Type)
{
#undef ConstructParamsType
	return Internal.GetOnConstructObject_Event(Type);
}

		// Add
#pragma region

			// Pool
#pragma region

const FCsSkeletalMeshActorPooled* UCsManager_SkeletalMeshActor::AddToPool(const FECsSkeletalMeshActor& Type, ICsSkeletalMeshActor* Object)
{
	return Internal.AddToPool(Type, Object);
}

const FCsSkeletalMeshActorPooled* UCsManager_SkeletalMeshActor::AddToPool(const FECsSkeletalMeshActor& Type, const FCsSkeletalMeshActorPooled* Object)
{
	return Internal.AddToPool(Type, Object->GetObject());
}

const FCsSkeletalMeshActorPooled* UCsManager_SkeletalMeshActor::AddToPool(const FECsSkeletalMeshActor& Type, UObject* Object)
{
	return Internal.AddToPool(Type, Object);
}

void UCsManager_SkeletalMeshActor::OnAddToPool(const FECsSkeletalMeshActor& Type, const FCsSkeletalMeshActorPooled* Object)
{
	Pool.Add(Object->GetObject());
}

#pragma endregion Pool

			// Allocated Objects
#pragma region

const FCsSkeletalMeshActorPooled* UCsManager_SkeletalMeshActor::AddToAllocatedObjects(const FECsSkeletalMeshActor& Type, ICsSkeletalMeshActor* Sound, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, Sound, Object);
}

const FCsSkeletalMeshActorPooled* UCsManager_SkeletalMeshActor::AddToAllocatedObjects(const FECsSkeletalMeshActor& Type, ICsSkeletalMeshActor* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

const FCsSkeletalMeshActorPooled* UCsManager_SkeletalMeshActor::AddToAllocatedObjects(const FECsSkeletalMeshActor& Type, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

#pragma endregion Allocated Objects

#pragma endregion Add

const TArray<FCsSkeletalMeshActorPooled*>& UCsManager_SkeletalMeshActor::GetPool(const FECsSkeletalMeshActor& Type)
{
	return Internal.GetPool(Type);
}

const TArray<FCsSkeletalMeshActorPooled*>& UCsManager_SkeletalMeshActor::GetAllocatedObjects(const FECsSkeletalMeshActor& Type)
{
	return Internal.GetAllocatedObjects(Type);
}

const int32& UCsManager_SkeletalMeshActor::GetPoolSize(const FECsSkeletalMeshActor& Type)
{
	return Internal.GetPoolSize(Type);
}

int32 UCsManager_SkeletalMeshActor::GetAllocatedObjectsSize(const FECsSkeletalMeshActor& Type)
{
	return Internal.GetAllocatedObjectsSize(Type);
}

bool UCsManager_SkeletalMeshActor::IsExhausted(const FECsSkeletalMeshActor& Type)
{
	return Internal.IsExhausted(Type);
}

	// Find
#pragma region

const FCsSkeletalMeshActorPooled* UCsManager_SkeletalMeshActor::FindObject(const FECsSkeletalMeshActor& Type, const int32& Index)
{
	return Internal.FindObject(Type, Index);
}

const FCsSkeletalMeshActorPooled* UCsManager_SkeletalMeshActor::FindObject(const FECsSkeletalMeshActor& Type, ICsSkeletalMeshActor* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsSkeletalMeshActorPooled* UCsManager_SkeletalMeshActor::FindObject(const FECsSkeletalMeshActor& Type, UObject* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsSkeletalMeshActorPooled* UCsManager_SkeletalMeshActor::FindSafeObject(const FECsSkeletalMeshActor& Type, const int32& Index)
{
	return Internal.FindSafeObject(Type, Index);
}

const FCsSkeletalMeshActorPooled* UCsManager_SkeletalMeshActor::FindSafeObject(const FECsSkeletalMeshActor& Type, ICsSkeletalMeshActor* Object)
{
	return Internal.FindSafeObject(Type, Object);
}

const FCsSkeletalMeshActorPooled* UCsManager_SkeletalMeshActor::FindSafeObject(const FECsSkeletalMeshActor& Type, UObject* Object)
{
	return Internal.FindSafeObject(Type, Object);
}

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region

void UCsManager_SkeletalMeshActor::Update(const FCsDeltaTime& DeltaTime)
{
	Internal.Update(DeltaTime);
}

void UCsManager_SkeletalMeshActor::OnPreUpdate_Pool(const FECsSkeletalMeshActor& Type)
{
	CurrentUpdatePoolType		 = Type;
	CurrentUpdatePoolObjectIndex = 0;
}

void UCsManager_SkeletalMeshActor::OnUpdate_Object(const FECsSkeletalMeshActor& Type, const FCsSkeletalMeshActorPooled* Object)
{
	++CurrentUpdatePoolObjectIndex;
}

void UCsManager_SkeletalMeshActor::OnPostUpdate_Pool(const FECsSkeletalMeshActor& Type)
{
}

#pragma endregion Update

	// Payload
#pragma region

void UCsManager_SkeletalMeshActor::ConstructPayloads(const FECsSkeletalMeshActor& Type, const int32& Size)
{
	Internal.ConstructPayloads(Type, Size);
}

#define PayloadType NCsSkeletalMeshActor::NPayload::IPayload
PayloadType* UCsManager_SkeletalMeshActor::ConstructPayload(const FECsSkeletalMeshActor& Type)
{
#undef PayloadType

	typedef NCsSkeletalMeshActor::NPayload::FImpl PayloadImplType;

	return new PayloadImplType();
}

#define PayloadType NCsSkeletalMeshActor::NPayload::IPayload
PayloadType* UCsManager_SkeletalMeshActor::AllocatePayload(const FECsSkeletalMeshActor& Type)
{
#undef PayloadType
	return Internal.AllocatePayload(Type);
}

#pragma endregion Payload

	// Spawn
#pragma region

#define PayloadType NCsSkeletalMeshActor::NPayload::IPayload
const FCsSkeletalMeshActorPooled* UCsManager_SkeletalMeshActor::Spawn(const FECsSkeletalMeshActor& Type, PayloadType* Payload)
{
#undef PayloadType
	if (Internal.IsExhausted(Type))
	{
		const FCsSkeletalMeshActorPooled* AllocatedHead = Internal.GetAllocatedHeadObject(Type);

#if !UE_BUILD_SHIPPING
		if (UObject* Object = AllocatedHead->GetObject())
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_SkeletalMeshActor::Spawn: Deallocating object: %s as pool for Type: %s is exhausted."), *(Object->GetName()), Type.ToChar());
		}
#endif // #if !UE_BUILD_SHIPPING

		Internal.Destroy(Type, AllocatedHead);
	}
	return Internal.Spawn(Type, Payload);
}

#pragma endregion Spawn

	// Destroy
#pragma region

bool UCsManager_SkeletalMeshActor::Destroy(const FECsSkeletalMeshActor& Type, ICsSkeletalMeshActor* Object)
{
	return Internal.Destroy(Type, Object);
}

bool UCsManager_SkeletalMeshActor::Destroy(ICsSkeletalMeshActor* Object)
{
	return Internal.Destroy(Object);
}

#pragma endregion Destroy

	// Log
#pragma region

void UCsManager_SkeletalMeshActor::Log(const FString& Str)
{
	UE_LOG(LogCs, Warning, TEXT("%s"), *Str);
}

void UCsManager_SkeletalMeshActor::LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsSkeletalMeshActorPooled* Object)
{
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSkeletalMeshActorTransactions))
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