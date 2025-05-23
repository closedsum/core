// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/WidgetActor/CsManager_WidgetActor.h"
#include "CsUI.h"

// CVars
#include "Managers/WidgetActor/CsCVars_Manager_WidgetActor.h"
// Library
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsUILibrary_DataRootSet.h"
#include "Library/CsLibrary_Valid.h"
// Utility
#include "Utility/CsUILog.h"
// Settings
#include "Settings/CsUserInterfaceSettings.h"
// WidgetActor
#include "Managers/WidgetActor/Handler/CsManager_WidgetActor_ClassHandler.h"
#include "Managers/WidgetActor/Handler/CsManager_WidgetActor_DataHandler.h"
#include "Managers/WidgetActor/Payload/CsPayload_WidgetActorImpl.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"

#if WITH_EDITOR
#include "Singleton/CsGetManagerSingleton.h"
#include "Singleton/CsManager_Singleton.h"
#include "Managers/WidgetActor/CsGetManagerWidgetActor.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsManager_WidgetActor)

// Cached
#pragma region

namespace NCsManagerWidgetActor
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_WidgetActor, SetupInternal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_WidgetActor, InitInternalFromSettings);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_WidgetActor, PopulateClassMapFromSettings);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_WidgetActor, PopulateDataMapFromSettings);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_WidgetActor, GetWidgetActor);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_WidgetActor, GetData);

			const FString None = TEXT("None");
		}
	}
}

#pragma endregion Cached

// Internal
#pragma region

namespace NCsWidgetActor
{
	namespace NManager
	{
		namespace NInternal
		{
			FManager::FManager()
				: Super()
			{
			}
		}
	}
}

#pragma endregion Internal

// static initializations
UCsManager_WidgetActor* UCsManager_WidgetActor::s_Instance;
bool UCsManager_WidgetActor::s_bShutdown = false;

UCsManager_WidgetActor::UCsManager_WidgetActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

using ManagerParamsType = NCsWidgetActor::NManager::NInternal::FManager::FParams;
using ConstructParamsType = NCsPooledObject::NManager::FConstructParams;
using PayloadType = NCsWidgetActor::NPayload::IPayload;
using PayloadImplType = NCsWidgetActor::NPayload::NImpl::FImpl;
using DataType = NCsWidgetActor::NData::IData;

// Singleton
#pragma region

#if WITH_EDITOR

/*static*/ UCsManager_WidgetActor* UCsManager_WidgetActor::Get(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerWidgetActor(InRoot)->GetManager_WidgetActor();
}

/*static*/ UCsManager_WidgetActor* UCsManager_WidgetActor::GetSafe(const FString& Context, UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerWidgetActor* GetManagerWidgetActor = GetSafe_GetManagerWidgetActor(Context, InRoot, Log))
		return GetManagerWidgetActor->GetManager_WidgetActor();
	return nullptr;
}

/*static*/ bool UCsManager_WidgetActor::IsValid(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerWidgetActor(InRoot)->GetManager_WidgetActor() != nullptr;
}

#endif // #if WITH_EDITOR

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

/*static*/ void UCsManager_WidgetActor::Shutdown(const UObject* InRoot /*=nullptr*/)
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

#if WITH_EDITOR
/*static*/ bool UCsManager_WidgetActor::HasShutdown(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerWidgetActor(InRoot)->GetManager_WidgetActor() == nullptr;
}
#endif // #if WITH_EDITOR

#if WITH_EDITOR

/*static*/ ICsGetManagerWidgetActor* UCsManager_WidgetActor::Get_GetManagerWidgetActor(const UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_WidgetActor::Get_GetManagerWidgetActor: InRoot is NULL."));

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_WidgetActor::Get_GetManagerWidgetActor: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_WidgetActor::Get_GetManagerWidgetActor: Manager_Singleton is NULL."));

	ICsGetManagerWidgetActor* GetManagerWidgetActor = Cast<ICsGetManagerWidgetActor>(Manager_Singleton);

	checkf(GetManagerWidgetActor, TEXT("UCsManager_WidgetActor::Get_GetManagerWidgetActor: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerWidgetActor."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerWidgetActor;
}

/*static*/ ICsGetManagerWidgetActor* UCsManager_WidgetActor::GetSafe_GetManagerWidgetActor(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
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
	return Cast<ICsGetManagerWidgetActor>(Manager_Singleton);
}

/*static*/ UCsManager_WidgetActor* UCsManager_WidgetActor::GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerWidgetActor* GetManagerWidgetActor = GetSafe_GetManagerWidgetActor(Context, InRoot, Log))
		return GetManagerWidgetActor->GetManager_WidgetActor();
	return nullptr;
}

#endif // #if WITH_EDITOR

void UCsManager_WidgetActor::Initialize()
{
	SetupInternal();

	bInitialized = true;
}

/*static*/ bool UCsManager_WidgetActor::HasInitialized(const UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_WidgetActor::CleanUp()
{
	Internal.Shutdown();
	Pool.Reset();

	delete ClassHandler;
	delete DataHandler;

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
	using namespace NCsManagerWidgetActor::NCached;

	const FString& Context = Str::SetupInternal;

	// Populate EnumMaps
	UWorld* World				= MyRoot->GetWorld();
	UGameInstance* GameInstance = World ? World->GetGameInstance() : nullptr;

	NCsWidgetActor::PopulateEnumMapFromSettings(Context, GameInstance);
	NCsWidgetActorClass::PopulateEnumMapFromSettings(Context, GameInstance);

	// Class Handler
	ConstructClassHandler();

	checkf(ClassHandler, TEXT("%s: Failed to construct ClassHandler."), *Context);

	// Data Handler
	ConstructDataHandler();

	checkf(DataHandler, TEXT("%s: Failed to construct DataHandler."), *Context);

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

		checkf(ModuleSettings, TEXT("%s: Failed to get settings of type: UCsUserInterfaceSettings."), *Context);

		Settings = ModuleSettings->Manager_WidgetActor;

		// Populate TypeMapArray
		{
			const int32& Count = EMCsWidgetActor::Get().Num();

			TypeMapArray.Reset(Count);

			for (const FECsWidgetActor& Type : EMCsWidgetActor::Get())
			{
				TypeMapArray.Add(Type);
			}
			/*
			for (const TPair<FECsWidgetActor, FECsWidgetActor>& Pair : Settings.TypeMap)
			{
				TypeMapArray[Pair.Key.GetValue()] = Pair.Value;
			}
			*/
		}

		checkf(EMCsWidgetActor::Get().IsValidEnum(Settings.DefaultType), TEXT("%s: UCsUserInterfaceSettings->Manager_WidgetActor.DefaultType: %s is NOT Valid."), *Context, Settings.DefaultType.ToChar());

		InitInternalFromSettings();
	}
}

void UCsManager_WidgetActor::InitInternalFromSettings()
{
	using namespace NCsManagerWidgetActor::NCached;

	const FString& Context = Str::InitInternalFromSettings;

	ClassHandler->PopulateClassMapFromSettings(Context);

	const FCsUIDataRootSet& DataRootSet = NCsUI::NDataRootSet::FLibrary::GetChecked(Context, MyRoot);

	if (DataRootSet.bWidgetActorsHasData)
		DataHandler->PopulateDataMapFromSettings(Context);

	if (Settings.PoolParams.Num() > CS_EMPTY)
	{
		ManagerParamsType ManagerParams;

		ManagerParams.Name  = TEXT("UCsManager_WidgetActor::NCsWidgetActor::FManager");
		ManagerParams.World = MyRoot->GetWorld();

		for (const TPair<FECsWidgetActor, FCsSettings_Manager_WidgetActor_PoolParams>& Pair : Settings.PoolParams)
		{
			const FECsWidgetActor& Type								 = Pair.Key;
			const FCsSettings_Manager_WidgetActor_PoolParams& Params = Pair.Value;

			typedef NCsPooledObject::NManager::FPoolParams PoolParamsType;

			PoolParamsType& PoolParams = ManagerParams.ObjectParams.Add(Type);

			// Get Class
			const FECsWidgetActorClass& ClassType = Params.Class;

			checkf(EMCsWidgetActorClass::Get().IsValidEnum(ClassType), TEXT("%s: Class for NOT Valid."), *Context, ClassType.ToChar());

			FCsWidgetActorPooled* WidgetActor = GetWidgetActorChecked(Context, ClassType);
			UClass* Class					  = WidgetActor->GetClass();

			checkf(Class, TEXT("%s: Failed to get class for Type: %s ClassType: %s."), *Context, Type.ToChar(), ClassType.ToChar());

			PoolParams.Name								= ManagerParams.Name + TEXT("_") + Type.ToChar();
			PoolParams.World							= ManagerParams.World;
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

void UCsManager_WidgetActor::InitInternal(const ManagerParamsType& Params)
{
	// Add CVars
	{
		ManagerParamsType& P = const_cast<ManagerParamsType&>(Params);

		typedef NCsPooledObject::NManager::FPoolParams PoolParamsType;

		for (TPair<FECsWidgetActor, PoolParamsType>& Pair : P.ObjectParams)
		{
			PoolParamsType& PoolParams = Pair.Value;

			// Scoped Timer CVars
			PoolParams.ScopedGroup = NCsScopedGroup::ManagerWidgetActor;

			PoolParams.CreatePoolScopedTimerCVar		= NCsCVarLog::LogManagerWidgetActorScopedTimerCreatePool;
			PoolParams.UpdateScopedTimerCVar			= NCsCVarLog::LogManagerWidgetActorScopedTimerUpdate;
			PoolParams.UpdateObjectScopedTimerCVar		= NCsCVarLog::LogManagerWidgetActorScopedTimerUpdateObject;
			PoolParams.AllocateScopedTimerCVar			= NCsCVarLog::LogManagerWidgetActorScopedTimerAllocate;
			PoolParams.AllocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerWidgetActorScopedTimerAllocateObject;
			PoolParams.DeallocateScopedTimerCVar		= NCsCVarLog::LogManagerWidgetActorScopedTimerDeallocate;
			PoolParams.DeallocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerWidgetActorScopedTimerDeallocateObject;
			PoolParams.SpawnScopedTimerCVar				= NCsCVarLog::LogManagerWidgetActorScopedTimerSpawn;
			PoolParams.DestroyScopedTimerCVar			= NCsCVarLog::LogManagerWidgetActorScopedTimerDestroy;
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

TDelegate<FCsWidgetActorPooled*(const FECsWidgetActor&)>& UCsManager_WidgetActor::GetConstructContainer_Impl()
{
	return Internal.ConstructContainer_Impl;
}

FCsWidgetActorPooled* UCsManager_WidgetActor::ConstructContainer(const FECsWidgetActor& Type)
{
	return new FCsWidgetActorPooled();
}

TMulticastDelegate<void(const FCsWidgetActorPooled*, const ConstructParamsType&)>& UCsManager_WidgetActor::GetOnConstructObject_Event(const FECsWidgetActor& Type)
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

PayloadType* UCsManager_WidgetActor::ConstructPayload(const FECsWidgetActor& Type)
{
	return new PayloadImplType();
}

PayloadType* UCsManager_WidgetActor::AllocatePayload(const FECsWidgetActor& Type)
{
	return Internal.AllocatePayload(Type);
}

#pragma endregion Payload

	// Spawn
#pragma region

const FCsWidgetActorPooled* UCsManager_WidgetActor::Spawn(const FECsWidgetActor& Type, PayloadType* Payload)
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
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerWidgetActorTransactions))
	{
		const FString& TransactionAsString = EMCsPoolTransaction::Get().ToString(Transaction);

		ICsPooledObject* Interface  = Object->GetInterface();
		const FString ClassName		= Object->GetObject()->GetClass()->GetName();
		const FString ObjectName	= Object->GetObject()->GetName();
		const UObject* ObjectOwner	= Interface->GetCache()->GetOwner();
		const FString OwnerName		= ObjectOwner ? ObjectOwner->GetName() : NCsManagerWidgetActor::NCached::Str::None;
		const UObject* Parent		= Interface->GetCache()->GetParent();
		const FString ParentName	= Parent ? Parent->GetName() : NCsManagerWidgetActor::NCached::Str::None;
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

#pragma endregion Logwwd

#pragma endregion Internal

// Class
#pragma region

void UCsManager_WidgetActor::ConstructClassHandler()
{
	using _ClassHandlerType = NCsWidgetActor::NManager::NHandler::NClass::FClass;

	ClassHandler = new _ClassHandlerType();
	ClassHandler->Outer = this;
	ClassHandler->MyRoot = MyRoot;
}

FCsWidgetActorPooled* UCsManager_WidgetActor::GetWidgetActor(const FECsWidgetActor& Type)
{
	const FString& Context = NCsManagerWidgetActor::NCached::Str::GetWidgetActor;

	return ClassHandler->GetClassByType<EMCsWidgetActor, FECsWidgetActor>(Context, Type);
}

FCsWidgetActorPooled* UCsManager_WidgetActor::GetWidgetActor(const FECsWidgetActorClass& Type)
{
	const FString& Context = NCsManagerWidgetActor::NCached::Str::GetWidgetActor;

	return ClassHandler->GetClassByClassType<EMCsWidgetActorClass>(Context, Type);
}

FCsWidgetActorPooled* UCsManager_WidgetActor::GetWidgetActorChecked(const FString& Context, const FECsWidgetActorClass& Type)
{
	return ClassHandler->GetClassByClassTypeChecked<EMCsWidgetActorClass>(Context, Type);
}

#pragma endregion Class

// Data
#pragma region

void UCsManager_WidgetActor::ConstructDataHandler()
{
	using _DataHandlerType = NCsWidgetActor::NManager::NHandler::NData::FData;

	DataHandler = new DataHandlerType();
	DataHandler->Outer = this;
	DataHandler->MyRoot = MyRoot;
}

DataType* UCsManager_WidgetActor::GetData(const FName& Name)
{
	using namespace NCsManagerWidgetActor::NCached;

	const FString& Context = Str::GetData;

	return DataHandler->GetData(Context, Name);
}

DataType* UCsManager_WidgetActor::GetData(const FECsWidgetActor& Type)
{
	return GetData(Type.GetFName());
}

DataType* UCsManager_WidgetActor::GetDataChecked(const FString& Context, const FName& Name)
{
	return DataHandler->GetData(Context, Name);
}

DataType* UCsManager_WidgetActor::GetDataChecked(const FString& Context, const FECsWidgetActor& Type)
{
	return GetDataChecked(Context, Type.GetFName());
}

#pragma endregion Data