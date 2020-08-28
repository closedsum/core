// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Projectile/CsManager_Projectile.h"
#include "CsPrj.h"

// CVars
#include "Managers/Projectile/CsCVars_Manager_Projectile.h"
// Types
#include "Types/CsTypes_Collision.h"
// Library
#include "Library/CsLibrary_Property.h"
#include "Library/Load/CsLibrary_Load.h" // TEMP
#include "Data/CsLibrary_Data_Projectile.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
#include "Settings/CsProjectileSettings.h"
// Managers
#include "Managers/Data/CsManager_Data.h"
// Data
#include "Data/CsPrjGetDataRootSet.h"
#include "Data/CsData_Projectile.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Projectile
#include "Payload/CsPayload_ProjectileInterfaceMap.h"
#include "Payload/CsPayload_ProjectileImplSlice.h"
#include "Payload/Damage/CsPayload_ProjectileModifierDamageImplSlice.h"
#include "Data/CsData_ProjectileImpl.h"
// Game
#include "Engine/GameInstance.h"
#include "GameFramework/GameStateBase.h"

#include "Classes/Engine/World.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Projectile/CsGetManagerProjectile.h"

#include "Library/CsLibrary_Common.h"

#include "Classes/Engine/Engine.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerProjectile
{
	namespace Str
	{
		const FString InitInternalFromSettings = TEXT("UCsManager_Projectile::InitInternalFromSettings");
		const FString PopulateClassMapFromSettings = TEXT("UCsManager_Projectile::PopulateClassMapFromSettings");
		const FString PopulateDataMapFromSettings = TEXT("UCsManager_Projectile::PopulateDataMapFromSettings");
		const FString CreateEmulatedDataFromDataTable = TEXT("UCsManager_Projectile::CreateEmulatedDataFromDataTable");
		const FString DeconstructEmulatedData = TEXT("UCsManager_Projectile::DeconstructEmulatedData");
		const FString PopulateDataMapFromDataTable = TEXT("UCsManager_Projectile::PopulateDataMapFromDataTable");
	}

	namespace Name
	{
		const FName Class = FName("Class");
		const FName Data = FName("Data");

		const FName LifeTime = FName("LifeTime");
		const FName InitialSpeed = FName("InitialSpeed");
		const FName MaxSpeed = FName("MaxSpeed");
		const FName GravityScale = FName("GravityScale");
	}
}

#pragma endregion Cached

// Internal
#pragma region

FCsManager_Projectile_Internal::FCsManager_Projectile_Internal() 
	: Super()
{
}

#pragma endregion Internal

// static initializations
UCsManager_Projectile* UCsManager_Projectile::s_Instance;
bool UCsManager_Projectile::s_bShutdown = false;

UCsManager_Projectile::UCsManager_Projectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsManager_Projectile* UCsManager_Projectile::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerProjectile(InRoot)->GetManager_Projectile();
#else
	if (s_bShutdown)
	{
		UE_LOG(LogCsPrj, Warning, TEXT("UCsManager_Projectile::Get: Manager has already shutdown."));
		return nullptr;
	}
	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Projectile::IsValid(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerProjectile(InRoot)->GetManager_Projectile() != nullptr;
#else
	return s_Instance != nullptr;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Projectile::Init(UObject* InRoot, TSubclassOf<UCsManager_Projectile> ManagerProjectileClass, UObject* InOuter /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerProjectile* GetManagerProjectile = Get_GetManagerProjectile(InRoot);

	UCsManager_Projectile* Manager_Projectile = GetManagerProjectile->GetManager_Projectile();

	if (!Manager_Projectile)
	{
		Manager_Projectile = NewObject<UCsManager_Projectile>(InOuter ? InOuter : InRoot, ManagerProjectileClass, TEXT("Manager_Projectile_Singleton"), RF_Transient | RF_Public);

		GetManagerProjectile->SetManager_Projectile(Manager_Projectile);

		Manager_Projectile->SetMyRoot(InRoot);
		Manager_Projectile->Initialize();
	}
	else
	{
		UE_LOG(LogCsPrj, Warning, TEXT("UCsManager_Projectile::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Projectile>(GetTransientPackage(), ManagerProjectileClass, TEXT("Manager_Projectile_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCsPrj, Warning, TEXT("UCsManager_Projectile::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Projectile::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerProjectile* GetManagerProjectile = Get_GetManagerProjectile(InRoot);
	UCsManager_Projectile* Manager_Projectile	  = GetManagerProjectile->GetManager_Projectile();
	Manager_Projectile->CleanUp();

	GetManagerProjectile->SetManager_Projectile(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCsPrj, Warning, TEXT("UCsManager_Projectile::Shutdown: Manager has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Projectile::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerProjectile(InRoot)->GetManager_Projectile() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerProjectile* UCsManager_Projectile::Get_GetManagerProjectile(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Projectile::Get_GetManagerProjectile: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Projectile::Get_GetManagerProjectile: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Projectile::Get_GetManagerProjectile: Manager_Singleton is NULL."));

	ICsGetManagerProjectile* GetManagerProjectile = Cast<ICsGetManagerProjectile>(Manager_Singleton);

	checkf(GetManagerProjectile, TEXT("UCsManager_Projectile::Get_GetManagerProjectile: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerProjectile."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerProjectile;
}

/*static*/ ICsGetManagerProjectile* UCsManager_Projectile::GetSafe_GetManagerProjectile(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCsPrj, Warning, TEXT("UCsManager_Projectile::GetSafe_GetManagerProjectile: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCsPrj, Warning, TEXT("UCsManager_Projectile::GetSafe_GetManagerProjectile: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCsPrj, Warning, TEXT("UCsManager_Projectile::GetSafe_GetManagerProjectile: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetManagerProjectile>(Manager_Singleton);
}

/*static*/ UCsManager_Projectile* UCsManager_Projectile::GetSafe(UObject* Object)
{
	if (ICsGetManagerProjectile* GetManagerProjectile = GetSafe_GetManagerProjectile(Object))
		return GetManagerProjectile->GetManager_Projectile();
	return nullptr;
}

/*static*/ UCsManager_Projectile* UCsManager_Projectile::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game State
		if (UCsManager_Projectile* Manager = GetSafe(World->GetGameState()))
			return Manager;

		UE_LOG(LogCsPrj, Warning, TEXT("UCsManager_Projectile::GetFromWorldContextObject: Failed to Manager Item of type UCsManager_Projectile from GameState."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_Projectile::Initialize()
{
	SetupInternal();

	bInitialized = true;
}

/*static*/ bool UCsManager_Projectile::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_Projectile::CleanUp()
{
	Internal.Shutdown();
	
	for (TPair<FName, TArray<void*>>& Pair : PayloadInterfaceImplMap)
	{
		const FName& InterfaceImplName = Pair.Key;
		TArray<void*> Impls			   = Pair.Value;

		for (void* Impl: Impls)
		{
			DeconstructPayloadSlice(InterfaceImplName, Impl);
		}
		Impls.Reset();
	}
	PayloadInterfaceImplMap.Reset();

	for (FCsPayload_ProjectileInterfaceMap* Map : PayloadInterfaceMaps)
	{
		delete Map;
	}
	PayloadInterfaceMaps.Reset();
	
	Pool.Reset();

	// Class
	ResetClassContainers();
	// Data
	ResetDataContainers();

	bInitialized = false;
}

	// Root
#pragma region

void UCsManager_Projectile::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// Internal
#pragma region

void UCsManager_Projectile::SetupInternal()
{
	// Delegates
	{
		// Log
		Internal.LogTransaction_Impl.BindUObject(this, &UCsManager_Projectile::LogTransaction);
		// Container
		Internal.ConstructContainer_Impl.BindUObject(this, &UCsManager_Projectile::ConstructContainer);
		// Payload
		Internal.ConstructPayload_Impl.BindUObject(this, &UCsManager_Projectile::ConstructPayload);
		// Pool
		Internal.OnAddToPool_Event.AddUObject(this, &UCsManager_Projectile::OnAddToPool);
		// Update
		Internal.OnPreUpdate_Pool_Impl.BindUObject(this, &UCsManager_Projectile::OnPreUpdate_Pool);
		Internal.OnUpdate_Object_Event.AddUObject(this, &UCsManager_Projectile::OnUpdate_Object);
		Internal.OnPostUpdate_Pool_Impl.BindUObject(this, &UCsManager_Projectile::OnPostUpdate_Pool);

		// Bind delegates for a script interface.
		Internal.Script_GetCache_Impl = Script_GetCache_Impl;
		Internal.Script_Allocate_Impl = Script_Allocate_Impl;
		Internal.Script_Deallocate_Impl = Script_Deallocate_Impl;
		Internal.Script_Update_Impl = Script_Update_Impl;
	}

#if !UE_BUILD_SHIPPING
	//if (FCsCVarToggleMap::Get().IsEnabled(NCsCVarToggle::EnableManagerProjectileUnitTest))
	//{
		// Do Nothing
	//}
	//else
#endif // #if !UE_BUILD_SHIPPING
		// If any settings have been set for Manager_WidgetActor, apply them
	{
		UCsProjectileSettings* ModuleSettings = GetMutableDefault<UCsProjectileSettings>();

		checkf(ModuleSettings, TEXT("UCsManager_Projectile::SetupInternal: Failed to get settings of type: UCsProjectileSettings."));

		Settings = ModuleSettings->Manager_Projectile;

		// Populate TypeMapArray
		{
			const int32& Count = EMCsProjectile::Get().Num();

			TypeMapArray.Reserve(Count);

			for (const FECsProjectile& Type : EMCsProjectile::Get())
			{
				TypeMapArray.Add(Type);
			}

			for (const TPair<FECsProjectile, FECsProjectile>& Pair : Settings.TypeMap)
			{
				TypeMapArray[Pair.Key.GetValue()] = Pair.Value;
			}
		}

		InitInternalFromSettings();
	}
}

void UCsManager_Projectile::InitInternalFromSettings()
{
	using namespace NCsManagerProjectile;

	const FString& Context = Str::InitInternalFromSettings;

	PopulateClassMapFromSettings();
	PopulateDataMapFromSettings();

	if (Settings.PoolParams.Num() > CS_EMPTY)
	{
		FCsManager_Projectile_Internal::FCsManagerPooledObjectMapParams Params;

		Params.Name  = TEXT("UCsManager_Projectile::FCsManager_Projectile_Internal");
		Params.World = MyRoot->GetWorld();

		for (const TPair<FECsProjectile, FCsSettings_Manager_Projectile_PoolParams>& Pair : Settings.PoolParams)
		{
			const FECsProjectile& Type									= Pair.Key;
			const FCsSettings_Manager_Projectile_PoolParams& PoolParams = Pair.Value;

			FCsManagerPooledObjectParams& ObjectParams = Params.ObjectParams.Add(Type);

			// Get Class
			const FECsProjectileClass& ClassType = PoolParams.Class;

			checkf(EMCsProjectileClass::Get().IsValidEnum(ClassType), TEXT("%s: Class for NOT Valid."), *Context, ClassType.ToChar());

			FCsProjectile* Projectile = GetProjectileChecked(Context, ClassType);
			UClass* Class			  = Projectile->GetClass();

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

void UCsManager_Projectile::InitInternal(const FCsManager_Projectile_Internal::FCsManagerPooledObjectMapParams& Params)
{
	// Add CVars
	{
		FCsManager_Projectile_Internal::FCsManagerPooledObjectMapParams& P = const_cast<FCsManager_Projectile_Internal::FCsManagerPooledObjectMapParams&>(Params);

		for (TPair<FECsProjectile, FCsManagerPooledObjectParams>& Pair : P.ObjectParams)
		{
			FCsManagerPooledObjectParams& ObjectParams = Pair.Value;

			// Scoped Timer CVars
			ObjectParams.ScopedGroup = NCsScopedGroup::ManagerProjectile;

			ObjectParams.CreatePoolScopedTimerCVar		= NCsCVarLog::LogManagerProjectileScopedTimerCreatePool;
			ObjectParams.UpdateScopedTimerCVar			= NCsCVarLog::LogManagerProjectileScopedTimerUpdate;
			ObjectParams.UpdateObjectScopedTimerCVar	= NCsCVarLog::LogManagerProjectileScopedTimerUpdateObject;
			ObjectParams.AllocateScopedTimerCVar		= NCsCVarLog::LogManagerProjectileScopedTimerAllocate;
			ObjectParams.AllocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerProjectileScopedTimerAllocateObject;
			ObjectParams.DeallocateScopedTimerCVar		= NCsCVarLog::LogManagerProjectileScopedTimerDeallocate;
			ObjectParams.DeallocateObjectScopedTimerCVar = NCsCVarLog::LogManagerProjectileScopedTimerDeallocateObject;
			ObjectParams.SpawnScopedTimerCVar			= NCsCVarLog::LogManagerProjectileScopedTimerSpawn;
			ObjectParams.DestroyScopedTimerCVar			= NCsCVarLog::LogManagerProjectileScopedTimerDestroy;
		}
	}
	Internal.Init(Params);
}

void UCsManager_Projectile::Clear()
{
	Internal.Clear();
}

	// Pool
#pragma region

void UCsManager_Projectile::CreatePool(const FECsProjectile& Type, const int32& Size)
{
	const int32& PoolSize = Internal.GetPoolSize(Type);

	if (PoolSize > CS_EMPTY)
	{
		UE_LOG(LogCsPrj, Warning, TEXT("UCsManager_Projectile::CreatePool: Pool for Creep: %s has already been created with Size: %d."), Type.ToChar(), PoolSize);
	}

	Internal.CreatePool(Type, Size);
}

TBaseDelegate<FCsProjectilePooled*, const FECsProjectile&>& UCsManager_Projectile::GetConstructContainer_Impl()
{
	return Internal.ConstructContainer_Impl;
}

FCsProjectilePooled* UCsManager_Projectile::ConstructContainer(const FECsProjectile& Type)
{
	return new FCsProjectilePooled();
}

TMulticastDelegate<void, const FCsProjectilePooled*, const FCsManagerPooledObjectConstructParams&>& UCsManager_Projectile::GetOnConstructObject_Event(const FECsProjectile& Type)
{
	return Internal.GetOnConstructObject_Event(Type);
}

		// Add
#pragma region

			// Pool
#pragma region

const FCsProjectilePooled* UCsManager_Projectile::AddToPool(const FECsProjectile& Type, ICsProjectile* Object)
{
	return Internal.AddToPool(GetTypeFromTypeMap(Type), Object);
}

const FCsProjectilePooled* UCsManager_Projectile::AddToPool(const FECsProjectile& Type, const FCsProjectilePooled* Object)
{
	return Internal.AddToPool(GetTypeFromTypeMap(Type), Object->GetObject());
}

const FCsProjectilePooled* UCsManager_Projectile::AddToPool(const FECsProjectile& Type, UObject* Object)
{
	return Internal.AddToPool(GetTypeFromTypeMap(Type), Object);
}

void UCsManager_Projectile::OnAddToPool(const FECsProjectile& Type, const FCsProjectilePooled* Object)
{
	Pool.Add(Object->GetObject());

	// Apply delegates for a script interface
	FCsProjectilePooled* O = const_cast<FCsProjectilePooled*>(Object);

	O->Script_GetInstigator_Impl = Script_GetInstigator_Impl;
	O->Script_GetOwner_Impl = Script_GetOwner_Impl;
}

#pragma endregion Pool

			// Allocated Objects
#pragma region

const FCsProjectilePooled* UCsManager_Projectile::AddToAllocatedObjects(const FECsProjectile& Type, ICsProjectile* Projectile, UObject* Object)
{
	return Internal.AddToAllocatedObjects(GetTypeFromTypeMap(Type), Projectile, Object);
}

const FCsProjectilePooled* UCsManager_Projectile::AddToAllocatedObjects(const FECsProjectile& Type, ICsProjectile* Object)
{
	return Internal.AddToAllocatedObjects(GetTypeFromTypeMap(Type), Object);
}

const FCsProjectilePooled* UCsManager_Projectile::AddToAllocatedObjects(const FECsProjectile& Type, UObject* Object)
{
	return Internal.AddToAllocatedObjects(GetTypeFromTypeMap(Type), Object);
}

#pragma endregion Allocated Objects

#pragma endregion Add

const TArray<FCsProjectilePooled*>& UCsManager_Projectile::GetPool(const FECsProjectile& Type)
{
	return Internal.GetPool(GetTypeFromTypeMap(Type));
}

const TArray<FCsProjectilePooled*>& UCsManager_Projectile::GetAllocatedObjects(const FECsProjectile& Type)
{
	return Internal.GetAllocatedObjects(GetTypeFromTypeMap(Type));
}

const int32& UCsManager_Projectile::GetPoolSize(const FECsProjectile& Type)
{
	return Internal.GetPoolSize(GetTypeFromTypeMap(Type));
}

int32 UCsManager_Projectile::GetAllocatedObjectsSize(const FECsProjectile& Type)
{
	return Internal.GetAllocatedObjectsSize(GetTypeFromTypeMap(Type));
}

bool UCsManager_Projectile::IsExhausted(const FECsProjectile& Type)
{
	return Internal.IsExhausted(GetTypeFromTypeMap(Type));
}

	// Find
#pragma region

const FCsProjectilePooled* UCsManager_Projectile::FindObject(const FECsProjectile& Type, const int32& Index)
{
	return Internal.FindObject(GetTypeFromTypeMap(Type), Index);
}

const FCsProjectilePooled* UCsManager_Projectile::FindObject(const FECsProjectile& Type, ICsProjectile* Object)
{
	return Internal.FindObject(GetTypeFromTypeMap(Type), Object);
}

const FCsProjectilePooled* UCsManager_Projectile::FindObject(const FECsProjectile& Type, UObject* Object)
{
	return Internal.FindObject(GetTypeFromTypeMap(Type), Object);
}

const FCsProjectilePooled* UCsManager_Projectile::FindSafeObject(const FECsProjectile& Type, const int32& Index)
{
	return Internal.FindSafeObject(GetTypeFromTypeMap(Type), Index);
}

const FCsProjectilePooled* UCsManager_Projectile::FindSafeObject(const FECsProjectile& Type, ICsProjectile* Object)
{
	return Internal.FindSafeObject(GetTypeFromTypeMap(Type), Object);
}

const FCsProjectilePooled* UCsManager_Projectile::FindSafeObject(const FECsProjectile& Type, UObject* Object)
{
	return Internal.FindSafeObject(GetTypeFromTypeMap(Type), Object);
}

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region

void UCsManager_Projectile::Update(const FCsDeltaTime& DeltaTime)
{
	Internal.Update(DeltaTime);
}

void UCsManager_Projectile::OnPreUpdate_Pool(const FECsProjectile& Type)
{
	CurrentUpdatePoolType		 = Type;
	CurrentUpdatePoolObjectIndex = 0;
}

void UCsManager_Projectile::OnUpdate_Object(const FECsProjectile& Type, const FCsProjectilePooled* Object)
{
	++CurrentUpdatePoolObjectIndex;
}

void UCsManager_Projectile::OnPostUpdate_Pool(const FECsProjectile& Type)
{
}

#pragma endregion Update

	// Payload
#pragma region

void UCsManager_Projectile::ConstructPayloads(const FECsProjectile& Type, const int32& Size)
{
	Internal.ConstructPayloads(GetTypeFromTypeMap(Type), Size);
}

ICsPayload_Projectile* UCsManager_Projectile::ConstructPayload(const FECsProjectile& Type)
{
	// TODO: Perform a new in place for all structs.
	//		 Need to call dtor manually

	FCsPayload_ProjectileInterfaceMap* PayloadInterfaceMap = new FCsPayload_ProjectileInterfaceMap();

	PayloadInterfaceMaps.Add(PayloadInterfaceMap);

	FCsInterfaceMap* InterfaceMap = PayloadInterfaceMap->GetInterfaceMap();

	// FCsPayload_PooledObjectImplSlice
	FCsPayload_PooledObjectImplSlice* BaseSlice = new FCsPayload_PooledObjectImplSlice();

	{
		BaseSlice->SetInterfaceMap(InterfaceMap);
		// Add to map
		TArray<void*>& ImplMap = PayloadInterfaceImplMap.FindOrAdd(FCsPayload_PooledObjectImplSlice::Name);
		ImplMap.Add(BaseSlice);
	}

	// FCsPayload_ProjectileImplSlice
	{
		FCsPayload_ProjectileImplSlice* Slice = new FCsPayload_ProjectileImplSlice();

		Slice->SetInterfaceMap(InterfaceMap);
		// Add slice as ICsReset to BaseSlice so this slice gets reset call.
		BaseSlice->AddReset(static_cast<ICsReset*>(Slice));
		// NOTE: Do NOT add to map. Internal will take care of deconstruction.
	}

	UCsProjectileSettings* ModuleSettings = GetMutableDefault<UCsProjectileSettings>();
	
	const TSet<FECsProjectilePayload> PayloadTypes = ModuleSettings->Manager_Projectile.PayloadTypes;

	// FCsPayload_ProjectileModifierDamageImplSlice
	if (PayloadTypes.Contains(NCsProjectilePayload::ProjectileDamageModifier))
	{
		FCsPayload_ProjectileModifierDamageImplSlice* Slice = new FCsPayload_ProjectileModifierDamageImplSlice();

		Slice->SetInterfaceMap(InterfaceMap);
		// Add slice as ICsReset to BaseSlice so this slice gets reset call.
		BaseSlice->AddReset(static_cast<ICsReset*>(Slice));
		// Add to map
		TArray<void*>& ImplMap = PayloadInterfaceImplMap.FindOrAdd(FCsPayload_ProjectileModifierDamageImplSlice::Name);
		ImplMap.Add(Slice);
	}

	return InterfaceMap->Get<ICsPayload_Projectile>();
}

void UCsManager_Projectile::DeconstructPayloadSlice(const FName& InterfaceImplName, void* Data)
{
	// FCsPayload_PooledObjectImplSlice
	if (InterfaceImplName == FCsPayload_PooledObjectImplSlice::Name)
	{
		delete static_cast<FCsPayload_PooledObjectImplSlice*>(Data);
	}
	// FCsPayload_ProjectileImplSlice
	if (InterfaceImplName == FCsPayload_ProjectileImplSlice::Name)
	{
		checkf(0, TEXT("UCsManager_Projectile::DeconstructPayloadSlice: Deleting Data of type: FCsPayload_ProjectileImplSlice is handled by Intenral."));
	}
	// FCsPayload_ProjectileModifierDamageImplSlice
	if (InterfaceImplName == FCsPayload_ProjectileModifierDamageImplSlice::Name)
	{
		delete static_cast<FCsPayload_ProjectileModifierDamageImplSlice*>(Data);
	}
}

ICsPayload_Projectile* UCsManager_Projectile::AllocatePayload(const FECsProjectile& Type)
{
	return Internal.AllocatePayload(GetTypeFromTypeMap(Type));
}

ICsPayload_Projectile* UCsManager_Projectile::ScriptAllocatePayload(const FECsProjectile& Type, const FCsScriptProjectilePayload& ScriptPayload)
{
	ICsPayload_Projectile* IP = Internal.AllocatePayload(GetTypeFromTypeMap(Type));
	/*
	
	// FCsPayload_PooledObjectImplSlice
	if (FCsPayload_PooledObjectImplSlice* Slice = FCsLibrary_Payload_Projectile::SafeStaticCastChecked<FCsPayload_PooledObjectImplSlice>())
	{
		Slice->Instigator = ScriptPayload.Instigator;
		Slice->Owner	  = ScriptPayload.Owner;
		Slice->Parent	  = ScriptPayload.Parent;
	}
	// FCsPayload_ProjectileImplSlice
	if (FCsPayload_ProjectileImplSlice* Slice = FCsLibrary_Payload_Projectile::SafeStaticCastChecked<FCsPayload_ProjectileImplSlice>())
	{
		Slice->Direction = ScriptPayload.Direction;
		Slice->Location	 = ScriptPayload.Location;
	}
	*/
	return IP;
}

#pragma endregion Payload

	// Spawn
#pragma region

const FCsProjectilePooled* UCsManager_Projectile::Spawn(const FECsProjectile& Type, ICsPayload_Projectile* Payload)
{
	return Internal.Spawn(GetTypeFromTypeMap(Type), Payload);
}

const FCsProjectilePooled* UCsManager_Projectile::ScriptSpawn(const FECsProjectile& Type, const FCsScriptProjectilePayload& ScriptPayload)
{
	ICsPayload_Projectile* Payload = ScriptAllocatePayload(GetTypeFromTypeMap(Type), ScriptPayload);

	return Spawn(Type, Payload);
}

#pragma endregion Spawn

	// Destroy
#pragma region

bool UCsManager_Projectile::Destroy(const FECsProjectile& Type, ICsProjectile* Projectile)
{
	return Internal.Destroy(GetTypeFromTypeMap(Type), Projectile);
}

bool UCsManager_Projectile::Destroy(ICsProjectile* Projectile)
{
	return Internal.Destroy(Projectile);
}


#pragma endregion Destroy

	// Log
#pragma region

void UCsManager_Projectile::Log(const FString& Str)
{
	UE_LOG(LogCsPrj, Warning, TEXT("%s"), *Str);
}

void UCsManager_Projectile::LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsProjectilePooled* Object)
{
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerProjectileTransactions))
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
			UE_LOG(LogCsPrj, Warning, TEXT("%s: %s %s of Type: %s for %s attached to %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *OwnerName, *ParentName, CurrentTime);
		}
		else 
		if (ObjectOwner)
		{
			UE_LOG(LogCsPrj, Warning, TEXT("%s: %s %s of Type: %s for %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *OwnerName, CurrentTime);
		}
		else
		if (Parent)
		{
			UE_LOG(LogCsPrj, Warning, TEXT("%s: %s %s of Type: %s attached to %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *ParentName, CurrentTime);
		}
		else
		{
			UE_LOG(LogCsPrj, Warning, TEXT("%s: %s %s of Type: %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, CurrentTime);
		}
	}
}

#pragma endregion Log 

#pragma endregion Internal

// Class
#pragma region

void UCsManager_Projectile::GetProjectileClassesDataTableChecked(const FString& Context, UDataTable*& OutDataTable, TSoftObjectPtr<UDataTable>& OutDataTableSoftObject)
{
	// Get DataRootSetImpl
	UWorld* World				  = MyRoot->GetWorld();
	UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());
	UObject* DataRootSetImpl	  = Manager_Data->DataRootSet.GetObject();

	checkf(DataRootSetImpl, TEXT("%s: Failed to find DataRootSet."), *Context);

	// Get DataRootSet for this Module
	ICsPrjGetDataRootSet* GetDataRootSet = Cast<ICsPrjGetDataRootSet>(DataRootSetImpl);

	checkf(GetDataRootSet, TEXT("%s: DataRootSet: %s with Class: %s does NOT implement interface: ICsPrjGetDataRootSet."), *Context, *(DataRootSetImpl->GetName()), *(DataRootSetImpl->GetClass()->GetName()));

	const FCsPrjDataRootSet& DataRootSet = GetDataRootSet->GetCsPrjDataRootSet();

	OutDataTableSoftObject = DataRootSet.ProjectileClasses;

	checkf(OutDataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetCsPrjDataRootSet().ProjectileClasses is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

	OutDataTable = Manager_Data->GetDataTable(OutDataTableSoftObject);

	checkf(OutDataTable, TEXT("%s: Failed to get DataTable @ %s."), *Context, *(OutDataTableSoftObject.ToSoftObjectPath().ToString()));
}

void UCsManager_Projectile::PopulateClassMapFromSettings()
{
	using namespace NCsManagerProjectile;

	const FString& Context = Str::PopulateClassMapFromSettings;

	// Reset appropriate containers
	ResetClassContainers();

	// Get DataRootSetImpl
	UWorld* World				  = MyRoot->GetWorld();
	UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

	UDataTable* DataTable = nullptr;
	TSoftObjectPtr<UDataTable> DT_SoftObject(nullptr);

	GetProjectileClassesDataTableChecked(Context, DataTable, DT_SoftObject);

	// Get Classes from DataTable

	const UScriptStruct* RowStruct = DataTable->GetRowStruct();

	// Get the Property named "Class" if it exists.
	UStructProperty* ClassProperty = FCsLibrary_Property::FindStructPropertyByName<FCsProjectilePtr>(RowStruct, Name::Class);

	if (!ClassProperty)
	{
		UE_LOG(LogCsPrj, Warning, TEXT("%s: Failed to find StructProperty: Class in DataTable: %s with Struct: %s"), *Context, *(DataTable->GetName()), *(RowStruct->GetName()));
		return;
	}

	// Cache any class related information that is loaded.
	const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

	for (const TPair<FName, uint8*>& Pair : RowMap)
	{
		const FName& Name = Pair.Key;
		uint8* RowPtr	  = Manager_Data->GetDataTableRow(DT_SoftObject, Name);

		if (!RowPtr)
			continue;

		// If Property named "Class" exists, cache the class.
		if (ClassProperty)
		{
			FCsProjectilePtr* ProjectilePtr = ClassProperty->ContainerPtrToValuePtr<FCsProjectilePtr>(RowPtr);

			checkf(ProjectilePtr, TEXT("%s: ProjectilePtr is NULL."), *Context);

			UObject* O = ProjectilePtr->Get();

			checkf(O, TEXT("%s: Failed to get projectile from DataTable: %s: Row: %s."), *Context, *(DataTable->GetName()), *(Name.ToString()));

			FCsProjectile& Projectile = ProjectileClassByClassTypeMap.Add(Name);

			Projectile.SetObject(O);
		}
	}
}

FCsProjectile* UCsManager_Projectile::GetProjectile(const FECsProjectile& Type)
{
	checkf(EMCsProjectile::Get().IsValidEnum(Type), TEXT("UCsManager_Projectile::GetProjectile: Type: %s is NOT Valid."), Type.ToChar());

	return ProjectileClassByTypeMap.Find(Type.GetFName());
}

FCsProjectile* UCsManager_Projectile::GetProjectile(const FECsProjectileClass& Type)
{
	checkf(EMCsProjectileClass::Get().IsValidEnum(Type), TEXT("UCsManager_Projectile::GetProjectile: Type: %s is NOT Valid."), Type.ToChar());

	return ProjectileClassByClassTypeMap.Find(Type.GetFName());
}

FCsProjectile* UCsManager_Projectile::GetProjectileChecked(const FString& Context, const FECsProjectileClass& Type)
{
	FCsProjectile* Ptr = GetProjectile(Type);

	checkf(Ptr, TEXT("%s: Failed to find a projectile associated with Type: %s."), *Context, Type.ToChar());

	return Ptr;
}

void UCsManager_Projectile::ResetClassContainers()
{
	ProjectileClassByTypeMap.Reset();
	ProjectileClassByClassTypeMap.Reset();
}

#pragma endregion Class

// Data
#pragma region

void UCsManager_Projectile::PopulateDataMapFromSettings()
{
	using namespace NCsManagerProjectile;

	const FString& Context = Str::PopulateDataMapFromSettings;

	// Reset appropriate containers
	ResetDataContainers();

	// Get DataRootSetImpl
	UWorld* World = MyRoot->GetWorld();

	UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());
	UObject* DataRootSetImpl	  = Manager_Data->DataRootSet.GetObject();

	checkf(DataRootSetImpl, TEXT("%s: Failed to find DataRootSet."), *Context);

	// Get DataRootSet for this Module
	ICsPrjGetDataRootSet* GetDataRootSet = Cast<ICsPrjGetDataRootSet>(DataRootSetImpl);

	checkf(GetDataRootSet, TEXT("%s: DataRootSet: %s with Class: %s does NOT implement interface: ICsPrjGetDataRootSet."), *Context, *(DataRootSetImpl->GetName()), *(DataRootSetImpl->GetClass()->GetName()));

	const FCsPrjDataRootSet& DataRootSet = GetDataRootSet->GetCsPrjDataRootSet();

	// Find which DataTables have been loaded
	for (const FCsProjectileSettings_DataTable_Projectiles& Projectiles : DataRootSet.Projectiles)
	{
		// Check DataTable of Weapons
		TSoftObjectPtr<UDataTable> DT_SoftObject = Projectiles.Projectiles;

		if (UDataTable* DT = Manager_Data->GetDataTable(DT_SoftObject))
		{
			DataTables.Add(DT);

			// Emulated
			const TSet<FECsProjectileData>& EmulatedDataInterfaces = Projectiles.EmulatedDataInterfaces;

			if (EmulatedDataInterfaces.Num() > CS_EMPTY)
			{
				CreateEmulatedDataFromDataTable(DT, DT_SoftObject, EmulatedDataInterfaces);
			}
			// "Normal" / Non-Emulated
			else
			{
				PopulateDataMapFromDataTable(DT, DT_SoftObject);
			}
		}
	}
}

void UCsManager_Projectile::CreateEmulatedDataFromDataTable(UDataTable* DataTable, const TSoftObjectPtr<UDataTable>& DataTableSoftObject, const TSet<FECsProjectileData>& EmulatedDataInterfaces)
{
	using namespace NCsManagerProjectile;

	const FString& Context = Str::CreateEmulatedDataFromDataTable;

	const UScriptStruct* RowStruct = DataTable->GetRowStruct();

	checkf(EmulatedDataInterfaces.Find(NCsProjectileData::Projectile), TEXT("%s: Emulated Data Interfaces must include ICsData_Projecitle."), *Context);

	// ICsData_Projectile
	bool Emulates_ICsDataProjectile = true;
		// LifeTime
	UFloatProperty* LifeTimeProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<UFloatProperty>(Context, RowStruct, Name::LifeTime, NCsProjectileData::Projectile.GetDisplayName());
		// InitialSpeed
	UFloatProperty* InitialSpeedProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<UFloatProperty>(Context, RowStruct, Name::InitialSpeed, NCsProjectileData::Projectile.GetDisplayName());
		// MaxSpeed
	UFloatProperty* MaxSpeedProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<UFloatProperty>(Context, RowStruct, Name::MaxSpeed, NCsProjectileData::Projectile.GetDisplayName());
		// GravityScale
	UFloatProperty* GravityScaleProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<UFloatProperty>(Context, RowStruct, Name::GravityScale, NCsProjectileData::Projectile.GetDisplayName());

	// ICsData_ProjectileCollision
	bool Emulates_ICsData_ProjectileCollision = false;

	// ICsData_ProjectileStaticMeshVisual
	bool Emulates_ICsData_ProjectileStaticMeshVisual = false;
		// StaticMesh
	//FCsPrjStaticMesh* StaticMesh;

	if (EmulatedDataInterfaces.Find(NCsProjectileData::ProjectileStaticMeshVisual))
	{
	}

	if (EmulatedDataInterfaces.Find(NCsProjectileData::ProjectileTrailVisual))
	{
	}

		// CollisionPreset
	UStructProperty* CollisionPresetProperty = nullptr;

	if (EmulatedDataInterfaces.Find(NCsProjectileData::ProjectileCollision))
	{
		CollisionPresetProperty = FCsLibrary_Property::FindStructPropertyByNameForInterfaceChecked<FCsCollisionPreset>(Context, RowStruct, Name::GravityScale, NCsProjectileData::ProjectileCollision.GetDisplayName());
	}

	// Class
	UStructProperty* ClassProperty = FCsLibrary_Property::FindStructPropertyByName<FCsProjectilePtr>(RowStruct, Name::Class);

	if (!ClassProperty)
	{
		UE_LOG(LogCsPrj, Warning, TEXT("%s: Failed to find StructProperty: Class in DataTable: %s with Struct: %s"), *Context, *(DataTable->GetName()), *(RowStruct->GetName()));
	}

	// Get Manager_Data
	UWorld* World				  = MyRoot->GetWorld();
	UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

	// Check which rows from the DataTable have been loaded
	const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

	for (const TPair<FName, uint8*>& Pair : RowMap)
	{
		const FName& Name = Pair.Key;
		uint8* RowPtr	  = Manager_Data->GetDataTableRow(DataTableSoftObject, Name);

		if (!RowPtr)
			continue;

		// ICsData_Projectile
		if (Emulates_ICsDataProjectile)
		{
			FCsData_ProjectileImpl* Data = new FCsData_ProjectileImpl();

			checkf(EmulatedDataMap.Find(Name) == nullptr, TEXT("%s: Data has already been created for Row: %s."), *Context, *(Name.ToString()));

			EmulatedDataMap.Add(Name, Data);

			FCsData_ProjectileInterfaceMap* EmulatedInterfaceMap = new FCsData_ProjectileInterfaceMap();

			checkf(EmulatedDataInterfaceMap.Find(Name) == nullptr, TEXT("%s: Emulated Interface Map has already been created for Row: %s."), *Context, *(Name.ToString()));

			EmulatedDataInterfaceMap.Add(Name, EmulatedInterfaceMap);

			FCsInterfaceMap* InterfaceMap = EmulatedInterfaceMap->GetInterfaceMap();

			InterfaceMap->Add<ICsData_Projectile>(FCsData_ProjectileImpl::Name, static_cast<ICsData_Projectile*>(Data));

			Data->SetInterfaceMap(InterfaceMap);

			TMap<FName, void*>& InterfaceImplMap = EmulatedDataInterfaceImplMap.FindOrAdd(Name);
			InterfaceImplMap.Add(FCsData_ProjectileImpl::Name, Data);

			DataMap.Add(Name, Data);

			// LifeTime
			{
				float* Value = FCsLibrary_Property::ContainerPtrToValuePtrChecked<float>(Context, LifeTimeProperty, RowPtr);

				Data->SetLifeTime(Value);
			}
			// InitialSpeed
			{
				float* Value = FCsLibrary_Property::ContainerPtrToValuePtrChecked<float>(Context, InitialSpeedProperty, RowPtr);

				Data->SetInitialSpeed(Value);
			}
			// MaxSpeed
			{
				float* Value = FCsLibrary_Property::ContainerPtrToValuePtrChecked<float>(Context, MaxSpeedProperty, RowPtr);

				Data->SetMaxSpeed(Value);
			}
			// GravityScale
			{
				float* Value = FCsLibrary_Property::ContainerPtrToValuePtrChecked<float>(Context, GravityScaleProperty, RowPtr);

				Data->SetGravityScale(Value);
			}
		}
		// ICsData_ProjectileCollision
		if (Emulates_ICsData_ProjectileCollision)
		{

		}
		// ICsData_ProjectileStaticMeshVisual
		if (Emulates_ICsData_ProjectileStaticMeshVisual)
		{

		}

		// Class
		if (ClassProperty)
		{
			FCsProjectilePtr* ProjectilePtr = ClassProperty->ContainerPtrToValuePtr<FCsProjectilePtr>(RowPtr);

			checkf(ProjectilePtr, TEXT("%s: WeaponPtr is NULL."), *Context);

			UObject* O = ProjectilePtr->Get();

			checkf(O, TEXT("%s: Failed to get projectile from DataTable: %s: Row: %s."), *Context, *(DataTable->GetName()), *(Name.ToString()));

			FCsProjectile& Projectile = ProjectileClassByTypeMap.Add(Name);

			Projectile.SetObject(O);
		}
	}
}

void UCsManager_Projectile::DeconstructEmulatedData(const FName& InterfaceImplName, void* Data)
{
	// FCsData_ProjectileImpl
	if (InterfaceImplName == FCsData_ProjectileImpl::Name)
	{
		delete static_cast<FCsData_ProjectileImpl*>(Data);
	}
	// FCsData_ProjecitleVisualImpl
	// FCsData_ProjectileCollisionImpl
	else
	{
		checkf(0, TEXT("UCsManager_Projectile::DeconstructEmulatedData: Failed to delete InterfaceMap."));
	}
}

void UCsManager_Projectile::PopulateDataMapFromDataTable(UDataTable* DataTable, const TSoftObjectPtr<UDataTable>& DataTableSoftObject)
{
	using namespace NCsManagerProjectile;

	const FString& Context = Str::PopulateDataMapFromDataTable;

	// Get Manager_Data
	UWorld* World				  = MyRoot->GetWorld();
	UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

	const UScriptStruct* RowStruct = DataTable->GetRowStruct();

	// Class
	UStructProperty* ClassProperty = FCsLibrary_Property::FindStructPropertyByName<FCsProjectilePtr>(RowStruct, Name::Class);

	if (!ClassProperty)
	{
		UE_LOG(LogCsPrj, Warning, TEXT("%s: Failed to find StructProperty: Class in DataTable: %s with Struct: %s"), *Context, *(DataTable->GetName()), *(RowStruct->GetName()));
	}

	// Data
	UStructProperty* DataProperty = FCsLibrary_Property::FindStructPropertyByName<FCsData_ProjectilePtr>(RowStruct, Name::Data);

	if (!DataProperty)
	{
		UE_LOG(LogCsPrj, Warning, TEXT("%s: Failed to find StructProperty: Data in DataTable: %s with Struct: %s"), *Context, *(DataTable->GetName()), *(RowStruct->GetName()));
	}

	// Check which rows from the DataTable have been loaded
	const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

	for (const TPair<FName, uint8*>& Pair : RowMap)
	{
		const FName& Name = Pair.Key;
		uint8* RowPtr     = Manager_Data->GetDataTableRow(DataTableSoftObject, Name);

		if (!RowPtr)
			continue;

		TMap<FName, uint8*>& Map = DataTableRowByPathMap.FindOrAdd(DataTableSoftObject.ToSoftObjectPath());
		Map.Add(Name, RowPtr);

		// Class
		if (ClassProperty)
		{
			FCsProjectilePtr* ProjectilePtr = ClassProperty->ContainerPtrToValuePtr<FCsProjectilePtr>(RowPtr);

			checkf(ProjectilePtr, TEXT("%s: ProjectilePtr is NULL."), *Context);

			UObject* O = ProjectilePtr->Get();

			checkf(O, TEXT("%s: Failed to get weapon from DataTable: %s: Row: %s."), *Context, *(DataTable->GetName()), *(Name.ToString()));

			FCsProjectile& Projectile = ProjectileClassByTypeMap.Add(Name);

			Projectile.SetObject(O);
		}

		// Data
		if (DataProperty)
		{
			FCsData_ProjectilePtr* DataPtr = DataProperty->ContainerPtrToValuePtr<FCsData_ProjectilePtr>(RowPtr);

			UObject* Data = DataPtr->Get();

			checkf(Data, TEXT("%s: Failed to get data from DataTable: %s Row: %s."), *Context, *(DataTable->GetName()), *(Name.ToString()));

			ICsData_Projectile* IData = Cast<ICsData_Projectile>(Data);

			checkf(IData, TEXT("%s: Data: %s with Class: %s does NOT implement interface: ICsData_Weapon."), *Context, *(Data->GetName()), *(Data->GetClass()->GetName()));

			DataMap.Add(Name, IData);
		}
	}
}

ICsData_Projectile* UCsManager_Projectile::GetData(const FName& Name)
{
	checkf(Name != NAME_None, TEXT("UCsManager_Projectile::GetData: Name: None is NOT Valid."));

	// Check emulated data
	if (ICsData_Projectile** EmuDataPtr = EmulatedDataMap.Find(Name))
		return *EmuDataPtr;

	// Check data
	if (ICsData_Projectile** DataPtr = DataMap.Find(Name))
		return *DataPtr;

	return nullptr;
}

ICsData_Projectile* UCsManager_Projectile::GetData(const FECsProjectile& Type)
{
	checkf(EMCsProjectile::Get().IsValidEnum(Type), TEXT("UCsManager_Projectile::GetData: Type: %s is NOT Valid."), Type.ToChar());

	return GetData(Type.GetFName());
}

ICsData_Projectile* UCsManager_Projectile::GetDataChecked(const FString& Context, const FName& Name)
{
	ICsData_Projectile* Ptr = GetData(Name);

	checkf(Ptr, TEXT("%s: Failed to find a Data associated with Name: %s."), *(Name.ToString()));

	return Ptr;
}

ICsData_Projectile* UCsManager_Projectile::GetDataChecked(const FString& Context, const FECsProjectile& Type)
{
	ICsData_Projectile* Ptr = GetData(Type);

	checkf(Ptr, TEXT("%s: Failed to find a Data associated with Type: %s."), Type.ToChar());

	return Ptr;
}

void UCsManager_Projectile::ResetDataContainers()
{
	for (TPair<FName, TMap<FName, void*>>& DataPair : EmulatedDataInterfaceImplMap)
	{
		TMap<FName, void*> InterfaceImplMap = DataPair.Value;

		for (TPair<FName, void*>& ImplPair : InterfaceImplMap)
		{
			DeconstructEmulatedData(ImplPair.Key, ImplPair.Value);

			ImplPair.Value = nullptr;
		}
	}
	EmulatedDataMap.Reset();
	EmulatedDataInterfaceImplMap.Reset();

	for (TPair<FName, FCsData_ProjectileInterfaceMap*>& Pair : EmulatedDataInterfaceMap)
	{
		FCsData_ProjectileInterfaceMap* Ptr = Pair.Value;
		delete Ptr;
		Pair.Value = nullptr;
	}
	EmulatedDataInterfaceMap.Reset();

	DataMap.Reset();
	DataTables.Reset(DataTables.Max());
	DataTableRowByPathMap.Reset();
}

void UCsManager_Projectile::OnPayloadUnloaded(const FName& Payload)
{
}

#pragma endregion Data