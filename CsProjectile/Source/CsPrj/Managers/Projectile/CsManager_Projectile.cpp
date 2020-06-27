// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Projectile/CsManager_Projectile.h"
#include "CsPrj.h"

// CVars
#include "Managers/Projectile/CsCVars_Manager_Projectile.h"
// Library
#include "Library/CsLibrary_Property.h"
// Settings
#include "Settings/CsProjectileSettings.h"
// Data
#include "Data/CsData_Projectile.h"
// Projectile
#include "Payload/CsProjectilePooledPayloadImpl.h"
#include "Data/CsData_ProjectileImpl.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Projectile/CsGetManagerProjectile.h"

#include "Library/CsLibrary_Common.h"

#include "Classes/Engine/World.h"
#include "Classes/Engine/Engine.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerProjectile
{
	namespace Str
	{
		const FString PopulateDataMapFromSettings = TEXT("UCsManager_Projectile::PopulateDataMapFromSettings");
	}

	namespace Name
	{
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

	checkf(GetManagerProjectile, TEXT("UCsManager_Projectile::Get_GetManagerProjectile: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerItem."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

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
}

void UCsManager_Projectile::CleanUp()
{
	Internal.Shutdown();
	Pool.Reset();

	for (TPair<FName, ICsData_Projectile*>& Pair : DataMap)
	{
		ICsData_Projectile* Data = Pair.Value;
		DeconstructData(Data);
		Pair.Value = nullptr;
	}
	DataMap.Reset();
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
		// If any settings have been set for Manager_Creep, apply them
	{
		UCsProjectileSettings* ModuleSettings = GetMutableDefault<UCsProjectileSettings>();

		checkf(ModuleSettings, TEXT("UCsManager_Projectile::SetupInternal: Failed to get settings of type: UCsTdSettings."));

		Settings = ModuleSettings->ManagerProjectile;

		InitInternalFromSettings();
	}
}

void UCsManager_Projectile::InitInternalFromSettings()
{
#if WITH_EDITOR
	if (Settings.Payload == NAME_None)
	{
		UE_LOG(LogCsPrj, Warning, TEXT("UCsManager_Projectile::InitInternalFromSettings: No Payload specified in settings. Storing hard references on manager."));
	}
#else
	checkf(Settings.Payload != NAME_None, TEXT("UCsManager_Projectile::InitInternalFromSettings: No Payload specified in settings."));
#endif // #if WITH_EDITOR

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

			checkf(PoolParams.Class.ToSoftObjectPath().IsValid(), TEXT("UCsManager_Projectile::InitInternalFromSettings: Class for Type: %s is NOT a Valid Path."), *(Type.Name));

#if !UE_BUILD_SHIPPING
			if (!PoolParams.Class.Get())
			{
				UE_LOG(LogCsPrj, Warning, TEXT("UCsManager_Projectile::InitInternalFromSettings: Class @ for Type: %s is NOT already loaded in memory."), *(PoolParams.Class.ToString()), *(Type.Name));
			}
#endif // #if !UE_BUILD_SHIPPING

			UClass* Class = PoolParams.Class.LoadSynchronous();

			checkf(Class, TEXT("UCsManager_Projectile::InitInternalFromSettings: Failed to load Class @ for Type: %s."), *(PoolParams.Class.ToString()), *(Type.Name));

			ClassMap.Add(Type, Class);

			ObjectParams.Name  = Params.Name + TEXT("_") + Type.Name;
			ObjectParams.World = Params.World;
			//ObjectParams.LogType
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
		UE_LOG(LogCsPrj, Warning, TEXT("UCsManager_Projectile::CreatePool: Pool for Creep: %s has already been created with Size: %d."), *(Type.Name), PoolSize);
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

TMulticastDelegate<void, const FCsProjectilePooled*>& UCsManager_Projectile::GetOnConstructObject_Event(const FECsProjectile& Type)
{
	return Internal.GetOnConstructObject_Event(Type);
}

		// Add
#pragma region

			// Pool
#pragma region

const FCsProjectilePooled* UCsManager_Projectile::AddToPool(const FECsProjectile& Type, ICsProjectile* Object)
{
	return Internal.AddToPool(Type, Object);
}

const FCsProjectilePooled* UCsManager_Projectile::AddToPool(const FECsProjectile& Type, const FCsProjectilePooled* Object)
{
	return Internal.AddToPool(Type, Object->GetObject());
}

const FCsProjectilePooled* UCsManager_Projectile::AddToPool(const FECsProjectile& Type, UObject* Object)
{
	return Internal.AddToPool(Type, Object);
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
	return Internal.AddToAllocatedObjects(Type, Projectile, Object);
}

const FCsProjectilePooled* UCsManager_Projectile::AddToAllocatedObjects(const FECsProjectile& Type, ICsProjectile* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

const FCsProjectilePooled* UCsManager_Projectile::AddToAllocatedObjects(const FECsProjectile& Type, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

#pragma endregion Allocated Objects

#pragma endregion Add

const TArray<FCsProjectilePooled*>& UCsManager_Projectile::GetPool(const FECsProjectile& Type)
{
	return Internal.GetPool(Type);
}

const TArray<FCsProjectilePooled*>& UCsManager_Projectile::GetAllocatedObjects(const FECsProjectile& Type)
{
	return Internal.GetAllocatedObjects(Type);
}

const int32& UCsManager_Projectile::GetPoolSize(const FECsProjectile& Type)
{
	return Internal.GetPoolSize(Type);
}

int32 UCsManager_Projectile::GetAllocatedObjectsSize(const FECsProjectile& Type)
{
	return Internal.GetAllocatedObjectsSize(Type);
}

bool UCsManager_Projectile::IsExhausted(const FECsProjectile& Type)
{
	return Internal.IsExhausted(Type);
}

	// Find
#pragma region

const FCsProjectilePooled* UCsManager_Projectile::FindObject(const FECsProjectile& Type, const int32& Index)
{
	return Internal.FindObject(Type, Index);
}

const FCsProjectilePooled* UCsManager_Projectile::FindObject(const FECsProjectile& Type, ICsProjectile* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsProjectilePooled* UCsManager_Projectile::FindObject(const FECsProjectile& Type, UObject* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsProjectilePooled* UCsManager_Projectile::FindSafeObject(const FECsProjectile& Type, const int32& Index)
{
	return Internal.FindSafeObject(Type, Index);
}

const FCsProjectilePooled* UCsManager_Projectile::FindSafeObject(const FECsProjectile& Type, ICsProjectile* Object)
{
	return Internal.FindSafeObject(Type, Object);
}

const FCsProjectilePooled* UCsManager_Projectile::FindSafeObject(const FECsProjectile& Type, UObject* Object)
{
	return Internal.FindSafeObject(Type, Object);
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
	Internal.ConstructPayloads(Type, Size);
}

ICsProjectilePayload* UCsManager_Projectile::ConstructPayload(const FECsProjectile& Type)
{
	return new FCsProjectilePooledPayloadImpl();
}

ICsProjectilePayload* UCsManager_Projectile::AllocatePayload(const FECsProjectile& Type)
{
	return Internal.AllocatePayload(Type);
}

ICsProjectilePayload* UCsManager_Projectile::ScriptAllocatePayload(const FECsProjectile& Type, const FCsScriptProjectilePayload& ScriptPayload)
{
	ICsProjectilePayload* IP				= Internal.AllocatePayload(Type);
	FCsProjectilePooledPayloadImpl* Payload = static_cast<FCsProjectilePooledPayloadImpl*>(IP);

	Payload->Instigator = ScriptPayload.Instigator;
	Payload->Owner		= ScriptPayload.Owner;
	Payload->Parent		= ScriptPayload.Parent;
	Payload->Direction	= ScriptPayload.Direction;
	Payload->Location	= ScriptPayload.Location;

	return IP;
}

#pragma endregion Payload

	// Spawn
#pragma region

const FCsProjectilePooled* UCsManager_Projectile::Spawn(const FECsProjectile& Type, ICsProjectilePayload* Payload)
{
	return Internal.Spawn(Type, Payload);
}

const FCsProjectilePooled* UCsManager_Projectile::ScriptSpawn(const FECsProjectile& Type, const FCsScriptProjectilePayload& ScriptPayload)
{
	ICsProjectilePayload* Payload = ScriptAllocatePayload(Type, ScriptPayload);

	return Spawn(Type, Payload);
}

#pragma endregion Spawn

	// Destroy
#pragma region

bool UCsManager_Projectile::Destroy(const FECsProjectile& Type, ICsProjectile* Projectile)
{
	return Internal.Destroy(Type, Projectile);
}

bool UCsManager_Projectile::Destroy(ICsProjectile* Projectile)
{
	return Internal.Destroy(Projectile);
}


#pragma endregion Destroy

#pragma endregion Internal

// Data
#pragma region

void UCsManager_Projectile::PopulateDataMapFromSettings()
{
	using namespace NCsManagerProjectile;

	if (UCsProjectileSettings* ModuleSettings = GetMutableDefault<UCsProjectileSettings>())
	{
		for (FCsProjectileSettings_DataTable_Projectiles& Projectiles : ModuleSettings->Projectiles)
		{
			// TODO: Get DataTable from Manager_Data

			// TODO: Add check for ModuleSettings->ManagerProjectile.Payload

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

				// ICsData_Projectile

				// LifeTime
				UFloatProperty* LifeTimeProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<UFloatProperty>(Str::PopulateDataMapFromSettings, RowStruct, Name::LifeTime, NCsProjectileData::Projectile.GetDisplayName());
				// InitialSpeed
				UFloatProperty* InitialSpeedProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<UFloatProperty>(Str::PopulateDataMapFromSettings, RowStruct, Name::InitialSpeed, NCsProjectileData::Projectile.GetDisplayName());
				// MaxSpeed
				UFloatProperty* MaxSpeedProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<UFloatProperty>(Str::PopulateDataMapFromSettings, RowStruct, Name::MaxSpeed, NCsProjectileData::Projectile.GetDisplayName());
				// GravityScale
				UFloatProperty* GravityScaleProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<UFloatProperty>(Str::PopulateDataMapFromSettings, RowStruct, Name::GravityScale, NCsProjectileData::Projectile.GetDisplayName());

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
	}
}

void UCsManager_Projectile::DeconstructData(ICsData_Projectile* Data)
{
	FCsInterfaceMap* InterfaceMap = Data->GetInterfaceMap();

	checkf(InterfaceMap, TEXT("UCsManager_Projectile::DeconstructData: Data failed to propertly implement method: GetInterfaceMap for interface: ICsGetInterfaceMap."));
	
	// FCsData_ProjectileImpl
	if (InterfaceMap->GetRootName() == FCsData_ProjectileImpl::Name)
	{
		delete static_cast<FCsData_ProjectileImpl*>(Data);
	}
	else
	{
		checkf(0, TEXT("UCsManager_Projectile::DeconstructData: Failed to delete Data."));
	}
}

ICsData_Projectile* UCsManager_Projectile::GetData(const FName& Name)
{
	checkf(Name != NAME_None, TEXT("UCsManager_Projectile::GetData: Name = None is NOT Valid."));

	ICsData_Projectile** DataPtr = DataMap.Find(Name);

	checkf(DataPtr, TEXT("UCsManager_Projectile::GetData: Failed to find Data for Name: %s."), *(Name.ToString()));

	return *DataPtr;
}

#pragma endregion Data