// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/FX/Actor/CsManager_FX_Actor.h"
#include "CsCore.h"

// CVars
#include "Managers/FX/Actor/CsCVars_Manager_FX_Actor.h"
// Library
#include "Managers/FX/Payload/CsLibrary_Payload_FX.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// Data
#include "Managers/FX/Data/CsData_FX.h"
#include "Managers/FX/Data/CsData_FXImpl.h"
// FX
#include "Managers/FX/Payload/CsPayload_FXImpl.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_Common.h"
#include "Managers/Time/CsLibrary_Manager_Time.h"
// Managers
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/FX/Actor/CsGetManagerFXActor.h"
// World
#include "Engine/World.h"
// Engine
#include "Engine/Engine.h"
// Game
#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerFXActor
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_FX_Actor, SetupInternal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_FX_Actor, PopulateDataMapFromSettings);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_FX_Actor, Spawn);
		}

		namespace Name
		{
		}
	}
}

#pragma endregion Cached

// Internal
#pragma region

namespace NCsFX
{
	FManager::FManager()
		: Super()
	{
	}
}

#pragma endregion Internal

// static initializations
UCsManager_FX_Actor* UCsManager_FX_Actor::s_Instance;
bool UCsManager_FX_Actor::s_bShutdown = false;

UCsManager_FX_Actor::UCsManager_FX_Actor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	// Singleton
	bInitialized(false),
	MyRoot(nullptr),
	// Settings
	Settings(),
	// Internal
	Internal(),
		// Pool
	CurrentUpdatePoolType(),
	CurrentUpdatePoolObjectIndex(0),
		// Pause
	OnPauseHandleByGroupMap(),
		// Spawn
	OnSpawn_Event(),
	OnSpawn_ScriptEvent(),
		// Destroy
	OnDestroy_Event(),
	// Pool
	Pool(),
	// Script
	Script_GetCache_Impl(),
	Script_Allocate_Impl(),
	Script_Deallocate_Impl(),
	Script_Update_Impl(),
	Script_OnConstructObject_Impl(),
	// Data
	DataMap(),
	ClassMap(),
	DataTables(),
	// Params
	Manager_ParameterInt(),
	Manager_ParameterFloat(),
	Manager_ParameterVector()
{
}

// Singleton
#pragma region

/*static*/ UCsManager_FX_Actor* UCsManager_FX_Actor::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerFXActor(InRoot)->GetManager_FX_Actor();
#else
	if (s_bShutdown)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::Get: Manager has already shutdown."));
		return nullptr;
	}
	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_FX_Actor::IsValid(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerFXActor(InRoot)->GetManager_FX_Actor() != nullptr;
#else
	return s_Instance != nullptr;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_FX_Actor::Init(UObject* InRoot, TSubclassOf<UCsManager_FX_Actor> ManagerFXActorClass, UObject* InOuter /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerFXActor* GetManagerFXActor = Get_GetManagerFXActor(InRoot);

	UCsManager_FX_Actor* Manager_FX_Actor = GetManagerFXActor->GetManager_FX_Actor();

	if (!Manager_FX_Actor)
	{
		Manager_FX_Actor = NewObject<UCsManager_FX_Actor>(InOuter ? InOuter : InRoot, ManagerFXActorClass, TEXT("Manager_FX_Actor_Singleton"), RF_Transient | RF_Public);

		GetManagerFXActor->SetManager_FX_Actor(Manager_FX_Actor);

		Manager_FX_Actor->SetMyRoot(InRoot);
		Manager_FX_Actor->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_FX_Actor>(GetTransientPackage(), ManagerFXActorClass, TEXT("Manager_FX_Actor_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_FX_Actor::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerFXActor* GetManagerFXActor = Get_GetManagerFXActor(InRoot);
	UCsManager_FX_Actor* Manager_FX_Actor	= GetManagerFXActor->GetManager_FX_Actor();
	Manager_FX_Actor->CleanUp();

	GetManagerFXActor->SetManager_FX_Actor(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::Shutdown: Manager has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_FX_Actor::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerFXActor(InRoot)->GetManager_FX_Actor() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerFXActor* UCsManager_FX_Actor::Get_GetManagerFXActor(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_FX_Actor::Get_GetManagerProjectile: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_FX_Actor::Get_GetManagerFXActor: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_FX_Actor::Get_GetManagerFXActor: Manager_Singleton is NULL."));

	ICsGetManagerFXActor* GetManagerFXActor = Cast<ICsGetManagerFXActor>(Manager_Singleton);

	checkf(GetManagerFXActor, TEXT("UCsManager_FX_Actor::Get_GetManagerFXActor: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerFXActor."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerFXActor;
}

/*static*/ ICsGetManagerFXActor* UCsManager_FX_Actor::GetSafe_GetManagerFXActor(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::GetSafe_GetManagerFXActor: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::GetSafe_GetManagerFXActor: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::GetSafe_GetManagerFXActor: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetManagerFXActor>(Manager_Singleton);
}

/*static*/ UCsManager_FX_Actor* UCsManager_FX_Actor::GetSafe(UObject* Object)
{
	if (ICsGetManagerFXActor* GetManagerFXActor = GetSafe_GetManagerFXActor(Object))
		return GetManagerFXActor->GetManager_FX_Actor();
	return nullptr;
}

/*static*/ UCsManager_FX_Actor* UCsManager_FX_Actor::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game State
		if (UCsManager_FX_Actor* Manager = GetSafe(World->GetGameState()))
			return Manager;

		UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::GetFromWorldContextObject: Failed to Manager FX Actor of type UCsManager_FX_Actor from GameState."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_FX_Actor::Initialize()
{
	SetupInternal();

	bInitialized = true;
}

/*static*/ bool UCsManager_FX_Actor::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_FX_Actor::CleanUp()
{
	// Unbind delegates for Time related events
	{
#if WITH_EDITOR
		typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

		UObject* ContextRoot = TimeManagerLibrary::GetSafeContextRoot(this);

		if (ContextRoot)
#else
		UObject* ContextRoot = nullptr;
#endif // #if WITH_EDITOR
		{
			if (UCsManager_Time* Manager_Time = UCsManager_Time::Get(ContextRoot))
			{
				for (const TPair<FECsUpdateGroup, FDelegateHandle>& Pair : OnPauseHandleByGroupMap)
				{
					const FECsUpdateGroup& Group = Pair.Key;
					const FDelegateHandle& Handle = Pair.Value;

					Manager_Time->RemoveOnPause(Group, Handle);
				}
			}
		}
		OnPauseHandleByGroupMap.Reset();
	}

	Internal.Shutdown();
	
	// Editor Preview - Make sure to mark pending kill or destroy objects
#if WITH_EDITOR
	if (UWorld* World = MyRoot->GetWorld())
	{
		if (World->WorldType == EWorldType::EditorPreview)
		{
			for (UObject* O : Pool)
			{
				if (O && !O->IsPendingKill())
				{
					if (AActor* A = Cast<AActor>(O))
						A->Destroy();
					else
						O->MarkPendingKill();
				}
			}
		}
	}
#endif // #if WITH_EDITOR
	Pool.Reset();

	for (TPair<FName, ICsData_FX*>& Pair : DataMap)
	{
		ICsData_FX* Data = Pair.Value;
		DeconstructData(Data);
		Pair.Value = nullptr;
	}
	DataMap.Reset();
	// Params
	Manager_ParameterInt.Shutdown();
	Manager_ParameterFloat.Shutdown();
	Manager_ParameterVector.Shutdown();

	bInitialized = false;
}

	// Root
#pragma region

void UCsManager_FX_Actor::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// Internal
#pragma region

void UCsManager_FX_Actor::SetupInternal()
{
	using namespace NCsManagerFXActor::NCached;

	const FString& Context = Str::SetupInternal;

	// Populate EnumMaps
	UWorld* World				= MyRoot->GetWorld();
	UGameInstance* GameInstance = World ? World->GetGameInstance() : nullptr;

	NCsFX::PopulateEnumMapFromSettings(Context, GameInstance);

	// Delegates
	{
		// Log
		Internal.Log_Impl.BindStatic(&FCsLog::Warning);
		Internal.LogTransaction_Impl.BindUObject(this, &UCsManager_FX_Actor::LogTransaction);
		// Container
		Internal.ConstructContainer_Impl.BindUObject(this, &UCsManager_FX_Actor::ConstructContainer);
		// Payload
		Internal.ConstructPayload_Impl.BindUObject(this, &UCsManager_FX_Actor::ConstructPayload);
		// Pool
		Internal.OnAddToPool_Event.AddUObject(this, &UCsManager_FX_Actor::OnAddToPool);
		// Update
		Internal.OnPreUpdate_Pool_Impl.BindUObject(this, &UCsManager_FX_Actor::OnPreUpdate_Pool);
		Internal.OnUpdate_Object_Event.AddUObject(this, &UCsManager_FX_Actor::OnUpdate_Object);
		Internal.OnPostUpdate_Pool_Impl.BindUObject(this, &UCsManager_FX_Actor::OnPostUpdate_Pool);

		// Bind delegates for a script interface.
		Internal.Script_GetCache_Impl = Script_GetCache_Impl;
		Internal.Script_Allocate_Impl = Script_Allocate_Impl;
		Internal.Script_Deallocate_Impl = Script_Deallocate_Impl;
		Internal.Script_Update_Impl = Script_Update_Impl;
		Internal.Script_OnConstructObject_Impl = Script_OnConstructObject_Impl;
	}
#if !UE_BUILD_SHIPPING
	//if (FCsCVarToggleMap::Get().IsEnabled(NCsCVarToggle::EnableManagerFXActorUnitTest))
	//{
		// Do Nothing
	//}
	//else
#endif // #if !UE_BUILD_SHIPPING
		// If any settings have been set for Manager_Creep, apply them
	{
		UCsDeveloperSettings* ModuleSettings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to get settings of type: UCsDeveloperSettings."), *Context);

		Settings = ModuleSettings->Manager_FX;

		InitInternalFromSettings();
	}
	// Params
	{
		UCsDeveloperSettings* ModuleSettings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to get settings of type: UCsDeveloperSettings."), *Context);

		const int32 (&PoolSizes)[(uint8)ECsFXParameterValue::ECsFXParameterValue_MAX] = ModuleSettings->Manager_FX.Parameters.PoolSizes;
		
		// Int
		{
			const int32& Size = PoolSizes[(uint8)ECsFXParameterValue::Int];

			checkf(Size > 0, TEXT("%s: UCsDeveloperSettings->Manager_FX.Parameters.PoolSizes[Int] is NOT > 0."), *Context);

			Manager_ParameterInt.CreatePool(Size);

			typedef NCsFX::NParameter::NInt::FResource ResourceContainerType;
			typedef NCsFX::NParameter::NInt::FIntType ResourceType;

			const TArray<ResourceContainerType*>& ParamPool = Manager_ParameterInt.GetPool();

			const int32 Count = ParamPool.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				ResourceType* R = ParamPool[I]->Get();
				R->SetIndex(I);
			}
		}
		// Float
		{
			const int32& Size = PoolSizes[(uint8)ECsFXParameterValue::Float];

			checkf(Size > 0, TEXT("%s: UCsDeveloperSettings->Manager_FX.Parameters.PoolSizes[Float] is NOT > 0."), *Context);

			Manager_ParameterFloat.CreatePool(Size);

			typedef NCsFX::NParameter::NFloat::FResource ResourceContainerType;
			typedef NCsFX::NParameter::NFloat::FFloatType ResourceType;

			const TArray<ResourceContainerType*>& ParamPool = Manager_ParameterFloat.GetPool();
	
			const int32 Count = ParamPool.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				ResourceType* R = ParamPool[I]->Get();
				R->SetIndex(I);
			}
		}
		// Vector
		{
			const int32& Size = PoolSizes[(uint8)ECsFXParameterValue::Float];

			checkf(Size > 0, TEXT("%s: UCsDeveloperSettings->Manager_FX.Parameters.PoolSizes[Vector] is NOT > 0."), *Context);

			Manager_ParameterVector.CreatePool(Size);

			typedef NCsFX::NParameter::NVector::FResource ResourceContainerType;
			typedef NCsFX::NParameter::NVector::FVectorType ResourceType;

			const TArray<ResourceContainerType*>& ParamPool = Manager_ParameterVector.GetPool();

			const int32 Count = ParamPool.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				ResourceType* R = ParamPool[I]->Get();
				R->SetIndex(I);
			}
		}
	}

	typedef NCsFX::NPayload::NChange::FCounter ChangeCounter;

	ChangeCounter::Get().Reset();
}

void UCsManager_FX_Actor::InitInternalFromSettings()
{
	PopulateDataMapFromSettings();

	if (Settings.PoolParams.Num() > CS_EMPTY)
	{
		typedef NCsFX::FManager::FParams ManagerParamsType;

		ManagerParamsType ManagerParams;

		ManagerParams.Name  = TEXT("UCsManager_FX_Actor::NCsFX::FManager");
		ManagerParams.World = MyRoot->GetWorld();

		for (const TPair<FECsFX, FCsSettings_Manager_FX_PoolParams>& Pair : Settings.PoolParams)
		{
			const FECsFX& Type								= Pair.Key;
			const FCsSettings_Manager_FX_PoolParams& Params = Pair.Value;

			typedef NCsPooledObject::NManager::FPoolParams PoolParamsType;

			PoolParamsType& PoolParams = ManagerParams.ObjectParams.Add(Type);

			checkf(Params.Class.ToSoftObjectPath().IsValid(), TEXT("UCsManager_FX_Actor::InitInternalFromSettings: Class for Type: %s is NOT a Valid Path."), Type.ToChar());

#if !UE_BUILD_SHIPPING
			if (!Params.Class.Get())
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::InitInternalFromSettings: Class @ for Type: %s is NOT already loaded in memory."), *(Params.Class.ToString()), Type.ToChar());
			}
#endif // #if !UE_BUILD_SHIPPING

			UClass* Class = Params.Class.LoadSynchronous();

			checkf(Class, TEXT("UCsManager_FX_Actor::InitInternalFromSettings: Failed to load Class @ for Type: %s."), *(Params.Class.ToString()), Type.ToChar());

			ClassMap.Add(Type, Class);

			PoolParams.Name							  = ManagerParams.Name + TEXT("_") + Type.GetName();
			PoolParams.World						  = ManagerParams.World;
			PoolParams.ConstructParams.Outer		  = this;
			PoolParams.ConstructParams.Class		  = Class;
			PoolParams.ConstructParams.ConstructionType = ECsPooledObjectConstruction::Object;
			PoolParams.bConstructPayloads			  = true;
			PoolParams.PayloadSize					  = Params.PayloadSize;
			PoolParams.bCreatePool					  = true;
			PoolParams.PoolSize						  = Params.PoolSize;
		}

		InitInternal(ManagerParams);
	}
}

#define ManagerParamsType NCsFX::FManager::FParams
void UCsManager_FX_Actor::InitInternal(const ManagerParamsType& Params)
{
	// Add CVars
	{
		ManagerParamsType& P = const_cast<ManagerParamsType&>(Params);

		typedef NCsPooledObject::NManager::FPoolParams PoolParamsType;

		for (TPair<FECsFX, PoolParamsType>& Pair : P.ObjectParams)
		{
			PoolParamsType& PoolParams = Pair.Value;

			// Scoped Timer CVars
			PoolParams.ScopedGroup = NCsScopedGroup::ManagerFXActor;

			PoolParams.CreatePoolScopedTimerCVar		= NCsCVarLog::LogManagerFXActorScopedTimerCreatePool;
			PoolParams.UpdateScopedTimerCVar			= NCsCVarLog::LogManagerFXActorScopedTimerUpdate;
			PoolParams.UpdateObjectScopedTimerCVar		= NCsCVarLog::LogManagerFXActorScopedTimerUpdateObject;
			PoolParams.AllocateScopedTimerCVar			= NCsCVarLog::LogManagerFXActorScopedTimerAllocate;
			PoolParams.AllocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerFXActorScopedTimerAllocateObject;
			PoolParams.DeallocateScopedTimerCVar		= NCsCVarLog::LogManagerFXActorScopedTimerDeallocate;
			PoolParams.DeallocateObjectScopedTimerCVar = NCsCVarLog::LogManagerFXActorScopedTimerDeallocateObject;
			PoolParams.SpawnScopedTimerCVar				= NCsCVarLog::LogManagerFXActorScopedTimerSpawn;
			PoolParams.DestroyScopedTimerCVar			= NCsCVarLog::LogManagerFXActorScopedTimerDestroy;
		}
	}
	Internal.Init(Params);
}
#undef ManagerParamsType

void UCsManager_FX_Actor::Clear()
{
	Internal.Clear();
}

	// Pool
#pragma region

void UCsManager_FX_Actor::CreatePool(const FECsFX& Type, const int32& Size)
{
	const int32& PoolSize = Internal.GetPoolSize(Type);

	if (PoolSize > CS_EMPTY)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::CreatePool: Pool for Creep: %s has already been created with Size: %d."), Type.ToChar(), PoolSize);
	}

	Internal.CreatePool(Type, Size);
}

TDelegate<FCsFXActorPooled*(const FECsFX&)>& UCsManager_FX_Actor::GetConstructContainer_Impl()
{
	return Internal.ConstructContainer_Impl;
}

FCsFXActorPooled* UCsManager_FX_Actor::ConstructContainer(const FECsFX& Type)
{
	return new FCsFXActorPooled();
}

#define ConstructParamsType NCsPooledObject::NManager::FConstructParams
TMulticastDelegate<void(const FCsFXActorPooled*, const ConstructParamsType&)>& UCsManager_FX_Actor::GetOnConstructObject_Event(const FECsFX& Type)
{
#undef ConstructParamsType
	return Internal.GetOnConstructObject_Event(Type);
}

		// Add
#pragma region

			// Pool
#pragma region

const FCsFXActorPooled* UCsManager_FX_Actor::AddToPool(const FECsFX& Type, ICsFXActorPooled* Object)
{
	return Internal.AddToPool(Type, Object);
}

const FCsFXActorPooled* UCsManager_FX_Actor::AddToPool(const FECsFX& Type, const FCsFXActorPooled* Object)
{
	return Internal.AddToPool(Type, Object->GetObject());
}

const FCsFXActorPooled* UCsManager_FX_Actor::AddToPool(const FECsFX& Type, UObject* Object)
{
	return Internal.AddToPool(Type, Object);
}

void UCsManager_FX_Actor::OnAddToPool(const FECsFX& Type, const FCsFXActorPooled* Object)
{
	Pool.Add(Object->GetObject());
}

#pragma endregion Pool

			// Allocated Objects
#pragma region

const FCsFXActorPooled* UCsManager_FX_Actor::AddToAllocatedObjects(const FECsFX& Type, ICsFXActorPooled* Projectile, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, Projectile, Object);
}

const FCsFXActorPooled* UCsManager_FX_Actor::AddToAllocatedObjects(const FECsFX& Type, ICsFXActorPooled* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

const FCsFXActorPooled* UCsManager_FX_Actor::AddToAllocatedObjects(const FECsFX& Type, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

#pragma endregion Allocated Objects

#pragma endregion Add

const TArray<FCsFXActorPooled*>& UCsManager_FX_Actor::GetPool(const FECsFX& Type)
{
	return Internal.GetPool(Type);
}

const TArray<FCsFXActorPooled*>& UCsManager_FX_Actor::GetAllocatedObjects(const FECsFX& Type)
{
	return Internal.GetAllocatedObjects(Type);
}

const int32& UCsManager_FX_Actor::GetPoolSize(const FECsFX& Type)
{
	return Internal.GetPoolSize(Type);
}

int32 UCsManager_FX_Actor::GetAllocatedObjectsSize(const FECsFX& Type)
{
	return Internal.GetAllocatedObjectsSize(Type);
}

bool UCsManager_FX_Actor::IsExhausted(const FECsFX& Type)
{
	return Internal.IsExhausted(Type);
}

	// Find
#pragma region

const FCsFXActorPooled* UCsManager_FX_Actor::FindObject(const FECsFX& Type, const int32& Index)
{
	return Internal.FindObject(Type, Index);
}

const FCsFXActorPooled* UCsManager_FX_Actor::FindObject(const FECsFX& Type, ICsFXActorPooled* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsFXActorPooled* UCsManager_FX_Actor::FindObject(const FECsFX& Type, UObject* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsFXActorPooled* UCsManager_FX_Actor::FindSafeObject(const FECsFX& Type, const int32& Index)
{
	return Internal.FindSafeObject(Type, Index);
}

const FCsFXActorPooled* UCsManager_FX_Actor::FindSafeObject(const FECsFX& Type, ICsFXActorPooled* Object)
{
	return Internal.FindSafeObject(Type, Object);
}

const FCsFXActorPooled* UCsManager_FX_Actor::FindSafeObject(const FECsFX& Type, UObject* Object)
{
	return Internal.FindSafeObject(Type, Object);
}

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region

void UCsManager_FX_Actor::Update(const FCsDeltaTime& DeltaTime)
{
	Internal.Update(DeltaTime);
}

void UCsManager_FX_Actor::OnPreUpdate_Pool(const FECsFX& Type)
{
	CurrentUpdatePoolType		 = Type;
	CurrentUpdatePoolObjectIndex = 0;
}

void UCsManager_FX_Actor::OnUpdate_Object(const FECsFX& Type, const FCsFXActorPooled* Object)
{
	++CurrentUpdatePoolObjectIndex;
}

void UCsManager_FX_Actor::OnPostUpdate_Pool(const FECsFX& Type)
{
}

#pragma endregion Update

	// Pause
#pragma region

void UCsManager_FX_Actor::Pause(const FECsUpdateGroup& Group, bool bPaused)
{
	Internal.Pause(bPaused);
}

void UCsManager_FX_Actor::Pause(const FECsFX& Type, bool bPaused)
{
	Internal.Pause(Type, bPaused);
}

void UCsManager_FX_Actor::BindToOnPause(const FECsUpdateGroup& Group)
{
	FDelegateHandle Handle = UCsManager_Time::Get(GetOuter())->GetOnPause_Event(Group).AddUObject(this, &UCsManager_FX_Actor::Pause);

	OnPauseHandleByGroupMap.Add(Group, Handle);
}

#pragma endregion Pause

	// Payload
#pragma region

void UCsManager_FX_Actor::ConstructPayloads(const FECsFX& Type, const int32& Size)
{
	Internal.ConstructPayloads(Type, Size);
}

#define PayloadType NCsFX::NPayload::IPayload
PayloadType* UCsManager_FX_Actor::ConstructPayload(const FECsFX& Type)
{
#undef PayloadType

	typedef NCsFX::NPayload::FImpl PayloadImplType;

	PayloadImplType* Payload = new PayloadImplType();

	Payload->SetRoot(MyRoot);

	return Payload;
}

#define PayloadType NCsFX::NPayload::IPayload
PayloadType* UCsManager_FX_Actor::AllocatePayload(const FECsFX& Type)
{
#undef PayloadType
	return Internal.AllocatePayload(Type);
}

#pragma endregion Payload

	// Spawn
#pragma region

#define PayloadType NCsFX::NPayload::IPayload
const FCsFXActorPooled* UCsManager_FX_Actor::Spawn(const FECsFX& Type, PayloadType* Payload)
{
#undef PayloadType

	using namespace NCsManagerFXActor::NCached;

	const FString& Context = Str::Spawn;

	typedef NCsFX::NPayload::FLibrary FXPayloadLibrary;

	check(FXPayloadLibrary::IsValidChecked(Context, Payload));

	return Internal.Spawn(Type, Payload);
}

#pragma endregion Spawn

	// Destroy
#pragma region

bool UCsManager_FX_Actor::Destroy(const FECsFX& Type, ICsFXActorPooled* Object)
{
	return Internal.Destroy(Type, Object);
}

bool UCsManager_FX_Actor::Destroy(ICsFXActorPooled* Object)
{
	return Internal.Destroy(Object);
}

#pragma endregion Destroy

	// Log
#pragma region

void UCsManager_FX_Actor::Log(const FString& Str)
{
	UE_LOG(LogCs, Warning, TEXT("%s"), *Str);
}

void UCsManager_FX_Actor::LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsFXActorPooled* Object)
{
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerFXActorTransactions))
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

// Data
#pragma region

void UCsManager_FX_Actor::PopulateDataMapFromSettings()
{
	using namespace NCsManagerFXActor::NCached;

	if (UCsDeveloperSettings* ModuleSettings = GetMutableDefault<UCsDeveloperSettings>())
	{
		/*
		for (FCsProjectileSettings_DataTable_Projectiles& Projectiles : ModuleSettings->Projectiles)
		{
			// TODO: Get DataTable from Manager_Data

			// TODO: Add check for ModuleSettings->Manager_Projectile.Payload

			bool LoadedFromManagerData = false;

			if (!LoadedFromManagerData)
			{
				// LOG Warning
			}

			// Check DataTable of Projectiles
			TSoftObjectPtr<UDataTable> DT_SoftObject = Projectiles.Projectiles;

			if (UDataTable* DT = DT_SoftObject.LoadSynchronous())
			{
				if (!LoadedFromManagerData)
				{
					DataTables.Add(DT);
				}

				const UScriptStruct* RowStruct    = DT->GetRowStruct();
				const TMap<FName, uint8*>& RowMap = DT->GetRowMap();

				typedef NCsProperty::FLibrary PropertyLibrary;

				// ICsData_Projectile

				// LifeTime
				UFloatProperty* LifeTimeProperty = PropertyLibrary::FindPropertyByNameForInterfaceChecked<UFloatProperty>(Str::PopulateDataMapFromSettings, RowStruct, Name::LifeTime, NCsProjectileData::Projectile.GetDisplayName());
				// InitialSpeed
				UFloatProperty* InitialSpeedProperty = PropertyLibrary::FindPropertyByNameForInterfaceChecked<UFloatProperty>(Str::PopulateDataMapFromSettings, RowStruct, Name::InitialSpeed, NCsProjectileData::Projectile.GetDisplayName());
				// MaxSpeed
				UFloatProperty* MaxSpeedProperty = PropertyLibrary::FindPropertyByNameForInterfaceChecked<UFloatProperty>(Str::PopulateDataMapFromSettings, RowStruct, Name::MaxSpeed, NCsProjectileData::Projectile.GetDisplayName());
				// GravityScale
				UFloatProperty* GravityScaleProperty = PropertyLibrary::FindPropertyByNameForInterfaceChecked<UFloatProperty>(Str::PopulateDataMapFromSettings, RowStruct, Name::GravityScale, NCsProjectileData::Projectile.GetDisplayName());

				for (const TPair<FName, uint8*>& Pair : RowMap)
				{
					const FName& Name = Pair.Key;
					uint8* RowPtr	  = const_cast<uint8*>(Pair.Value);

					FCsData_ProjectileImpl* Data = new FCsData_ProjectileImpl();
					
					DataMap.Add(Name, Data);

					// ICsData_Projectile
					{
						// LifeTime
						{
							float* Value = LifeTimeProperty->ContainerPtrToValuePtr<float>(RowPtr);

							checkf(Value, TEXT("UCsManager_Projectile::PopulateDataMapFromSettings: Failed to float ptr from FloatProperty: LifeTime."));

							Data->SetLifeTime(Value);
						}
						// InitialSpeed
						{
							float* Value = InitialSpeedProperty->ContainerPtrToValuePtr<float>(RowPtr);

							checkf(Value, TEXT("UCsManager_Projectile::PopulateDataMapFromSettings: Failed to float ptr from FloatProperty: InitialSpeed."));

							Data->SetInitialSpeed(Value);
						}
						// MaxSpeed
						{
							float* Value = MaxSpeedProperty->ContainerPtrToValuePtr<float>(RowPtr);

							checkf(Value, TEXT("UCsManager_Projectile::PopulateDataMapFromSettings: Failed to float ptr from FloatProperty: MaxSpeed."));

							Data->SetMaxSpeed(Value);
						}
						// GravityScale
						{
							float* Value = GravityScaleProperty->ContainerPtrToValuePtr<float>(RowPtr);

							checkf(Value, TEXT("UCsManager_Projectile::PopulateDataMapFromSettings: Failed to float ptr from FloatProperty: GravityScale."));

							Data->SetGravityScale(Value);
						}
					}
				}
			}
		}
		*/
	}
}

void UCsManager_FX_Actor::DeconstructData(ICsData_FX* Data)
{
	FCsInterfaceMap* InterfaceMap = Data->GetInterfaceMap();

	checkf(InterfaceMap, TEXT("UCsManager_FX_Actor::DeconstructData: Data failed to propertly implement method: GetInterfaceMap for interface: ICsGetInterfaceMap."));
	
	// FCsData_FXImpl
	if (InterfaceMap->GetRootName() == FCsData_FXImpl::Name)
	{
		delete static_cast<FCsData_FXImpl*>(Data);
	}
	else
	{
		checkf(0, TEXT("UCsManager_FX_Actor::DeconstructData: Failed to delete Data."));
	}
}

ICsData_FX* UCsManager_FX_Actor::GetData(const FName& Name)
{
	checkf(Name != NAME_None, TEXT("UCsManager_FX_Actor::GetData: Name = None is NOT Valid."));

	ICsData_FX** DataPtr = DataMap.Find(Name);

	checkf(DataPtr, TEXT("UCsManager_FX_Actor::GetData: Failed to find Data for Name: %s."), *(Name.ToString()));

	return *DataPtr;
}

#pragma endregion Data

// Params
#pragma region

#define ParameterType NCsFX::NParameter::IParameter
void UCsManager_FX_Actor::DeallocateValue(ParameterType* Value)
{
#undef ParameterType
	checkf(Value, TEXT("UCsManager_FX_Actor::DeallocateValue: Value is NULL."));

	typedef NCsFX::NParameter::EValue ParameterValueType;

	const ParameterValueType& ValueType = Value->GetValueType();

	// Int
	if (ValueType == ParameterValueType::Int)
		DeallocateValue((NCsFX::NParameter::NInt::FIntType*)Value);
	// Float
	if (ValueType == ParameterValueType::Float)
		DeallocateValue((NCsFX::NParameter::NFloat::FFloatType*)Value);
	// Vector
	else
	if (ValueType == ParameterValueType::Vector)
		DeallocateValue((NCsFX::NParameter::NVector::FVectorType*)Value);
}

#pragma endregion Params