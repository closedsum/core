// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/StaticMesh/CsManager_StaticMeshActor.h"
#include "CsCore.h"

// CVars
#include "Managers/StaticMesh/CsCVars_Manager_StaticMeshActor.h"
// Library
#include "Library/CsLibrary_Property.h"
#include "Managers/StaticMesh/Payload/CsLibrary_Payload_StaticMeshActor.h"
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Data
#include "Managers/StaticMesh/Data/CsData_StaticMeshActorImpl.h"
// StaticMeshActor
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActorImpl.h"

#if WITH_EDITOR
// Library
#include "Managers/StaticMesh/CsLibrary_Manager_StaticMeshActor.h"
// Singleton
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/StaticMesh/CsGetManagerStaticMeshActor.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerStaticMeshActor
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_StaticMeshActor, SetupInternal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_StaticMeshActor, InitInternalFromSettings);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_StaticMeshActor, Spawn);
		}

		namespace Name
		{
		}
	}
}

#pragma endregion Cached

// Internal
#pragma region

namespace NCsStaticMeshActor
{
	FManager::FManager()
		: Super()
	{
	}
}

#pragma endregion Internal

// static initializations
UCsManager_StaticMeshActor* UCsManager_StaticMeshActor::s_Instance;
bool UCsManager_StaticMeshActor::s_bShutdown = false;

UCsManager_StaticMeshActor::UCsManager_StaticMeshActor(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	// Singleton
	bInitialized(false),
	MyRoot(nullptr),
	// Settings
	Settings(),
	// Internal
	Internal(),
		// Update
	CurrentUpdatePoolType(),
	CurrentUpdatePoolObjectIndex(0),
		// Spawn
	OnSpawn_Event(),
	OnSpawn_ScriptEvent(),
		// Destroy
	OnDestroy_Event(),
	// Pool
	Pool(),
	// Script
		// ICsPooledObject
	Script_GetCache_Impl(),
	Script_Allocate_Impl(),
	Script_Deallocate_Impl(),
		// ICsUpdate
	Script_Update_Impl(),
		// ICsOnConstructObject
	Script_OnConstructObject_Impl(),
	// Class
	ClassMap()
{
}

// Singleton
#pragma region

#if WITH_EDITOR

/*static*/ UCsManager_StaticMeshActor* UCsManager_StaticMeshActor::Get(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerStaticMeshActor(InRoot)->GetManager_StaticMeshActor();
}

/*static*/ UCsManager_StaticMeshActor* UCsManager_StaticMeshActor::GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerStaticMeshActor* GetManagerStaticMeshActor = GetSafe_GetManagerStaticMeshActor(Context, InRoot, Log))
		return GetManagerStaticMeshActor->GetManager_StaticMeshActor();
	return nullptr;
}

/*static*/ bool UCsManager_StaticMeshActor::IsValid(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerStaticMeshActor(InRoot)->GetManager_StaticMeshActor() != nullptr;
}

#endif // #if WITH_EDITOR

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

#if WITH_EDITOR

/*static*/ bool UCsManager_StaticMeshActor::HasShutdown(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerStaticMeshActor(InRoot)->GetManager_StaticMeshActor() == nullptr;
}

/*static*/ ICsGetManagerStaticMeshActor* UCsManager_StaticMeshActor::Get_GetManagerStaticMeshActor(const UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_StaticMeshActor::Get_GetManagerStaticMeshActor: InRoot is NULL."));

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_StaticMeshActor::Get_GetManagerStaticMeshActor: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_StaticMeshActor::Get_GetManagerStaticMeshActor: Manager_Singleton is NULL."));

	ICsGetManagerStaticMeshActor* GetManagerStaticMeshActor = Cast<ICsGetManagerStaticMeshActor>(Manager_Singleton);

	checkf(GetManagerStaticMeshActor, TEXT("UCsManager_StaticMeshActor::Get_GetManagerStaticMeshActor: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerStaticMeshActor."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerStaticMeshActor;
}

/*static*/ ICsGetManagerStaticMeshActor* UCsManager_StaticMeshActor::GetSafe_GetManagerStaticMeshActor(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
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
	return Cast<ICsGetManagerStaticMeshActor>(Manager_Singleton);
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
	using namespace NCsManagerStaticMeshActor::NCached;

	const FString& Context = Str::SetupInternal;

	typedef NCsGameInstance::FLibrary GameInstanceLibrary;

	// Populate EnumMaps
	UObject* ContextRoot = GameInstanceLibrary::GetSafeAsObject(MyRoot);

	NCsStaticMeshActor::PopulateEnumMapFromSettings(Context, ContextRoot);

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

		Settings = ModuleSettings->Manager_StaticMeshActor;

		InitInternalFromSettings();
	}
}

void UCsManager_StaticMeshActor::InitInternalFromSettings()
{
	using namespace NCsManagerStaticMeshActor::NCached;

	const FString& Context = Str::InitInternalFromSettings;

	if (Settings.PoolParams.Num() > CS_EMPTY)
	{
		typedef NCsStaticMeshActor::FManager::FParams ManagerParamsType;

		ManagerParamsType ManagerParams;

		ManagerParams.Name  = TEXT("UCsManager_StaticMeshActor::NCsStaticMeshActor::FManager");
		ManagerParams.World = MyRoot->GetWorld();

		for (const TPair<FECsStaticMeshActor, FCsSettings_Manager_StaticMeshActor_PoolParams>& Pair : Settings.PoolParams)
		{
			const FECsStaticMeshActor& Type								   = Pair.Key;
			const FCsSettings_Manager_StaticMeshActor_PoolParams& Params = Pair.Value;

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
			const FECsStaticMeshActorClass& ClassType = Params.Class;

			checkf(EMCsStaticMeshActorClass::Get().IsValidEnum(ClassType), TEXT("%s: Class for NOT Valid."), *Context, ClassType.ToChar());

			FCsStaticMeshActorPooled* StaticMeshActor = GetStaticMeshActorChecked(Context, ClassType);
			UClass* Class							  = StaticMeshActor->GetClass();

			checkf(Class, TEXT("%s: Failed to get class for Type: %s ClassType: %s."), *Context, Type.ToChar(), ClassType.ToChar());
			*/

			PoolParams.Name								= ManagerParams.Name + TEXT("_") + Type.ToChar();
			PoolParams.World							= ManagerParams.World;
			PoolParams.ConstructParams.Outer			= this;
			PoolParams.ConstructParams.Class			= Class;
			PoolParams.ConstructParams.ConstructionType = NCsPooledObject::EConstruction::Actor;
			PoolParams.bConstructPayloads				= true;
			PoolParams.PayloadSize						= Params.PayloadSize;
			PoolParams.bCreatePool						= true;
			PoolParams.PoolSize							= Params.PoolSize;
		}

		InitInternal(ManagerParams);
	}
}

#define ManagerParamsType NCsStaticMeshActor::FManager::FParams
void UCsManager_StaticMeshActor::InitInternal(const ManagerParamsType& Params)
{
	// Add CVars
	{
		ManagerParamsType& P = const_cast<ManagerParamsType&>(Params);

		typedef NCsPooledObject::NManager::FPoolParams PoolParamsType;

		for (TPair<FECsStaticMeshActor, PoolParamsType>& Pair : P.ObjectParams)
		{
			PoolParamsType& PoolParams = Pair.Value;

			// Scoped Timer CVars
			PoolParams.ScopedGroup = NCsScopedGroup::ManagerStaticMeshActor;

			PoolParams.CreatePoolScopedTimerCVar		= NCsCVarLog::LogManagerStaticMeshActorScopedTimerCreatePool;
			PoolParams.UpdateScopedTimerCVar			= NCsCVarLog::LogManagerStaticMeshActorScopedTimerUpdate;
			PoolParams.UpdateObjectScopedTimerCVar		= NCsCVarLog::LogManagerStaticMeshActorScopedTimerUpdateObject;
			PoolParams.AllocateScopedTimerCVar			= NCsCVarLog::LogManagerStaticMeshActorScopedTimerAllocate;
			PoolParams.AllocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerStaticMeshActorScopedTimerAllocateObject;
			PoolParams.DeallocateScopedTimerCVar		= NCsCVarLog::LogManagerStaticMeshActorScopedTimerDeallocate;
			PoolParams.DeallocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerStaticMeshActorScopedTimerDeallocateObject;
			PoolParams.SpawnScopedTimerCVar				= NCsCVarLog::LogManagerStaticMeshActorScopedTimerSpawn;
			PoolParams.DestroyScopedTimerCVar			= NCsCVarLog::LogManagerStaticMeshActorScopedTimerDestroy;
		}
	}
	Internal.Init(Params);
}
#undef ManagerParamsType

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

TDelegate<FCsStaticMeshActorPooled*(const FECsStaticMeshActor&)>& UCsManager_StaticMeshActor::GetConstructContainer_Impl()
{
	return Internal.ConstructContainer_Impl;
}

FCsStaticMeshActorPooled* UCsManager_StaticMeshActor::ConstructContainer(const FECsStaticMeshActor& Type)
{
	return new FCsStaticMeshActorPooled();
}

#define ConstructParamsType NCsPooledObject::NManager::FConstructParams
TMulticastDelegate<void(const FCsStaticMeshActorPooled*, const ConstructParamsType&)>& UCsManager_StaticMeshActor::GetOnConstructObject_Event(const FECsStaticMeshActor& Type)
{
#undef ConstructParamsType
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

#define PayloadType NCsStaticMeshActor::NPayload::IPayload
PayloadType* UCsManager_StaticMeshActor::ConstructPayload(const FECsStaticMeshActor& Type)
{
#undef PayloadType

	typedef NCsStaticMeshActor::NPayload::FImpl PayloadImplType;

	return new PayloadImplType();
}

#define PayloadType NCsStaticMeshActor::NPayload::IPayload
PayloadType* UCsManager_StaticMeshActor::AllocatePayload(const FECsStaticMeshActor& Type)
{
#undef PayloadType
	return Internal.AllocatePayload(Type);
}

#pragma endregion Payload

	// Spawn
#pragma region

#define PayloadType NCsStaticMeshActor::NPayload::IPayload
const FCsStaticMeshActorPooled* UCsManager_StaticMeshActor::Spawn(const FECsStaticMeshActor& Type, PayloadType* Payload)
{
#undef PayloadType

	using namespace NCsManagerStaticMeshActor::NCached;

	const FString& Context = Str::Spawn;

	typedef NCsStaticMeshActor::NPayload::FLibrary PayloadLibrary;

	check(PayloadLibrary::IsValidChecked(Context, Payload));

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
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerStaticMeshActorTransactions))
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