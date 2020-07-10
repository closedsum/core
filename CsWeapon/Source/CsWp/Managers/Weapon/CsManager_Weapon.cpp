// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Weapon/CsManager_Weapon.h"
#include "CsWp.h"

// CVars
//#include "Managers/Projectile/CsCVars_Manager_Projectile.h"
// Types
#include "Projectile/CsTypes_ProjectileWeapon.h"
// Library
#include "Library/CsLibrary_Property.h"
#include "Library/Load/CsLibrary_Load.h"
// Settings
#include "Settings/CsWeaponSettings.h"
// Data
#include "Data/CsData_WeaponInterfaceMap.h"
#include "Data/CsData_WeaponImpl.h"
#include "Projectile/Data/CsData_ProjectileWeaponImpl.h"
#include "Projectile/Data/CsData_ProjectileWeaponSoundImpl.h"
// Weapon
#include "Payload/CsWeaponPooledPayloadImpl.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Weapon/CsGetManagerWeapon.h"

#include "Library/CsLibrary_Common.h"

#include "Classes/Engine/World.h"
#include "Classes/Engine/Engine.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerWeapon
{
	namespace Str
	{
		const FString PopulateDataMapFromSettings = TEXT("UCsManager_Weapon::PopulateDataMapFromSettings");
		const FString CreateEmulatedDataFromDataTable = TEXT("UCsManager_Weapon::CreateEmulatedDataFromDataTable");
		const FString DeconstructEmulatedData = TEXT("UCsManager_Weapon::DeconstructEmulatedData");
	}

	namespace Name
	{
		const FName Weapon = FName("Weapon");
		const FName Data = FName("Data");

		// ICsData_ProjectileWeapon
		const FName bDoFireOnRelease = FName("bDoFireOnRelease");
		const FName bFullAuto = FName("bFullAuto");
		const FName MaxAmmo = FName("MaxAmmo");
		const FName ProjectilesPerShot = FName("ProjectilesPerShot");
		const FName TimeBetweenShots = FName("TimeBetweenShots");
		const FName TimeBetweenAutoShots = FName("TimeBetweenAutoShots");
		const FName TimeBetweenProjectilesPerShot = FName("TimeBetweenProjectilesPerShot");
		// ICsData_ProjectileWeaponSound
		const FName FireSound = FName("FireSound");
	}
}

#pragma endregion Cached

// Internal
#pragma region

FCsManager_Weapon_Internal::FCsManager_Weapon_Internal()
	: Super()
{
}

#pragma endregion Internal

// static initializations
UCsManager_Weapon* UCsManager_Weapon::s_Instance;
bool UCsManager_Weapon::s_bShutdown = false;

UCsManager_Weapon::UCsManager_Weapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsManager_Weapon* UCsManager_Weapon::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerWeapon(InRoot)->GetManager_Weapon();
#else
	if (s_bShutdown)
	{
		UE_LOG(LogCsWp, Warning, TEXT("UCsManager_Weapon::Get: Manager has already shutdown."));
		return nullptr;
	}
	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Weapon::IsValid(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerWeapon(InRoot)->GetManager_Weapon() != nullptr;
#else
	return s_Instance != nullptr;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Weapon::Init(UObject* InRoot, TSubclassOf<UCsManager_Weapon> ManagerWeaponClass, UObject* InOuter /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerWeapon* GetManagerWeapon = Get_GetManagerWeapon(InRoot);

	UCsManager_Weapon* Manager_Weapon = GetManagerWeapon->GetManager_Weapon();

	if (!Manager_Weapon)
	{
		Manager_Weapon = NewObject<UCsManager_Weapon>(InOuter ? InOuter : InRoot, ManagerWeaponClass, TEXT("Manager_Weapon_Singleton"), RF_Transient | RF_Public);

		GetManagerWeapon->SetManager_Weapon(Manager_Weapon);

		Manager_Weapon->SetMyRoot(InRoot);
		Manager_Weapon->Initialize();
	}
	else
	{
		UE_LOG(LogCsWp, Warning, TEXT("UCsManager_Weapon::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Weapon>(GetTransientPackage(), ManagerWeaponClass, TEXT("Manager_Weapon_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCsWp, Warning, TEXT("UCsManager_Weapon::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Weapon::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerWeapon* GetManagerWeapon = Get_GetManagerWeapon(InRoot);
	UCsManager_Weapon* Manager_Weapon	  = GetManagerWeapon->GetManager_Weapon();
	Manager_Weapon->CleanUp();

	GetManagerWeapon->SetManager_Weapon(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCsWp, Warning, TEXT("UCsManager_Weapon::Shutdown: Manager has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Weapon::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerWeapon(InRoot)->GetManager_Weapon() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerWeapon* UCsManager_Weapon::Get_GetManagerWeapon(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Weapon::Get_GetManagerWeapon: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Weapon::Get_GetManagerWeapon: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Weapon::Get_GetManagerWeapon: Manager_Singleton is NULL."));

	ICsGetManagerWeapon* GetManagerWeapon = Cast<ICsGetManagerWeapon>(Manager_Singleton);

	checkf(GetManagerWeapon, TEXT("UCsManager_Weapon::Get_GetManagerWeapon: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerWeapon."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerWeapon;
}

/*static*/ ICsGetManagerWeapon* UCsManager_Weapon::GetSafe_GetManagerWeapon(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCsWp, Warning, TEXT("UCsManager_Weapon::GetSafe_GetManagerWeapon: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCsWp, Warning, TEXT("UCsManager_Weapon::GetSafe_GetManagerWeapon: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCsWp, Warning, TEXT("UCsManager_Weapon::GetSafe_GetManagerWeapon: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetManagerWeapon>(Manager_Singleton);
}

/*static*/ UCsManager_Weapon* UCsManager_Weapon::GetSafe(UObject* Object)
{
	if (ICsGetManagerWeapon* GetManagerWeapon = GetSafe_GetManagerWeapon(Object))
		return GetManagerWeapon->GetManager_Weapon();
	return nullptr;
}

/*static*/ UCsManager_Weapon* UCsManager_Weapon::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game State
		if (UCsManager_Weapon* Manager = GetSafe(World->GetGameState()))
			return Manager;

		UE_LOG(LogCsWp, Warning, TEXT("UCsManager_Weapon::GetFromWorldContextObject: Failed to Manager Item of type UCsManager_Weapon from GameState."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_Weapon::Initialize()
{
	SetupInternal();
}

void UCsManager_Weapon::CleanUp()
{
	Internal.Shutdown();
	Pool.Reset();

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

	for (TPair<FName, FCsData_WeaponInterfaceMap*>& Pair : EmulatedDataInterfaceMap)
	{
		FCsData_WeaponInterfaceMap* Ptr = Pair.Value;
		delete Ptr;
		Pair.Value = nullptr;
	}
	EmulatedDataInterfaceMap.Reset();

	DataMap.Reset();
	ClassMap.Reset();
	DataTables.Reset();
	WeaponMap.Reset();
}

	// Root
#pragma region

void UCsManager_Weapon::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// Internal
#pragma region

void UCsManager_Weapon::SetupInternal()
{
	// Delegates
	{
		// Container
		Internal.ConstructContainer_Impl.BindUObject(this, &UCsManager_Weapon::ConstructContainer);
		// Payload
		Internal.ConstructPayload_Impl.BindUObject(this, &UCsManager_Weapon::ConstructPayload);
		// Update
		Internal.OnPreUpdate_Pool_Impl.BindUObject(this, &UCsManager_Weapon::OnPreUpdate_Pool);
		Internal.OnUpdate_Object_Event.AddUObject(this, &UCsManager_Weapon::OnUpdate_Object);
		Internal.OnPostUpdate_Pool_Impl.BindUObject(this, &UCsManager_Weapon::OnPostUpdate_Pool);

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
		// If any settings have been set for Manager_Weapon, apply them
	{
		UCsWeaponSettings* ModuleSettings = GetMutableDefault<UCsWeaponSettings>();

		checkf(ModuleSettings, TEXT("UCsManager_Weapon::SetupInternal: Failed to get settings of type: UCsWeaponSettings."));

		Settings = ModuleSettings->ManagerWeapon;

		InitInternalFromSettings();
	}
}

void UCsManager_Weapon::InitInternalFromSettings()
{
#if WITH_EDITOR
	if (Settings.Payload == NAME_None)
	{
		UE_LOG(LogCsWp, Warning, TEXT("UCsManager_Weapon::InitInternalFromSettings: No Payload specified in settings. Storing hard references on manager."));
	}
#else
	checkf(Settings.Payload != NAME_None, TEXT("UCsManager_Weapon::InitInternalFromSettings: No Payload specified in settings."));
#endif // #if WITH_EDITOR

	PopulateDataMapFromSettings();

	if (Settings.PoolParams.Num() > CS_EMPTY)
	{
		FCsManager_Weapon_Internal::FCsManagerPooledObjectMapParams Params;

		Params.Name  = TEXT("UCsManager_Weapon::FCsManager_Weapon_Internal");
		Params.World = MyRoot->GetWorld();

		for (const TPair<FECsWeapon, FCsSettings_Manager_Weapon_PoolParams>& Pair : Settings.PoolParams)
		{
			const FECsWeapon& Type									= Pair.Key;
			const FCsSettings_Manager_Weapon_PoolParams& PoolParams = Pair.Value;

			FCsManagerPooledObjectParams& ObjectParams = Params.ObjectParams.Add(Type);

			checkf(PoolParams.Class.ToSoftObjectPath().IsValid(), TEXT("UCsManager_Weapon::InitInternalFromSettings: Class for Type: %s is NOT a Valid Path."), *(Type.Name));

#if !UE_BUILD_SHIPPING
			if (!PoolParams.Class.Get())
			{
				UE_LOG(LogCsWp, Warning, TEXT("UCsManager_Weapon::InitInternalFromSettings: Class @ for Type: %s is NOT already loaded in memory."), *(PoolParams.Class.ToString()), *(Type.Name));
			}
#endif // #if !UE_BUILD_SHIPPING

			// TODO: Get DataTable from Manager_Data

			// TODO: Add check for ModuleSettings->ManagerWeapon.Payload

			UClass* Class = PoolParams.Class.LoadSynchronous();

			checkf(Class, TEXT("UCsManager_Weapon::InitInternalFromSettings: Failed to load Class @ for Type: %s."), *(PoolParams.Class.ToString()), *(Type.Name));

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

void UCsManager_Weapon::InitInternal(const FCsManager_Weapon_Internal::FCsManagerPooledObjectMapParams& Params)
{
	Internal.Init(Params);
}

void UCsManager_Weapon::Clear()
{
	Internal.Clear();
}

	// Pool
#pragma region

void UCsManager_Weapon::CreatePool(const FECsWeapon& Type, const int32& Size)
{
	const int32& PoolSize = Internal.GetPoolSize(Type);

	if (PoolSize > CS_EMPTY)
	{
		UE_LOG(LogCsWp, Warning, TEXT("UCsManager_Weapon::CreatePool: Pool for Creep: %s has already been created with Size: %d."), *(Type.Name), PoolSize);
	}

	Internal.CreatePool(Type, Size);
}

TBaseDelegate<FCsWeaponPooled*, const FECsWeapon&>& UCsManager_Weapon::GetConstructContainer_Impl()
{
	return Internal.ConstructContainer_Impl;
}

FCsWeaponPooled* UCsManager_Weapon::ConstructContainer(const FECsWeapon& Type)
{
	return new FCsWeaponPooled();
}

TMulticastDelegate<void, const FCsWeaponPooled*>& UCsManager_Weapon::GetOnConstructObject_Event(const FECsWeapon& Type)
{
	return Internal.GetOnConstructObject_Event(Type);
}

		// Add
#pragma region

			// Pool
#pragma region

const FCsWeaponPooled* UCsManager_Weapon::AddToPool(const FECsWeapon& Type, ICsWeapon* Object)
{
	return Internal.AddToPool(Type, Object);
}

const FCsWeaponPooled* UCsManager_Weapon::AddToPool(const FECsWeapon& Type, const FCsWeaponPooled* Object)
{
	return Internal.AddToPool(Type, Object->GetObject());
}

const FCsWeaponPooled* UCsManager_Weapon::AddToPool(const FECsWeapon& Type, UObject* Object)
{
	return Internal.AddToPool(Type, Object);
}

#pragma endregion Pool

			// Allocated Objects
#pragma region

const FCsWeaponPooled* UCsManager_Weapon::AddToAllocatedObjects(const FECsWeapon& Type, ICsWeapon* Projectile, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, Projectile, Object);
}

const FCsWeaponPooled* UCsManager_Weapon::AddToAllocatedObjects(const FECsWeapon& Type, ICsWeapon* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

const FCsWeaponPooled* UCsManager_Weapon::AddToAllocatedObjects(const FECsWeapon& Type, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

#pragma endregion Allocated Objects

#pragma endregion Add

const TArray<FCsWeaponPooled*>& UCsManager_Weapon::GetPool(const FECsWeapon& Type)
{
	return Internal.GetPool(Type);
}

const TArray<FCsWeaponPooled*>& UCsManager_Weapon::GetAllocatedObjects(const FECsWeapon& Type)
{
	return Internal.GetAllocatedObjects(Type);
}

const int32& UCsManager_Weapon::GetPoolSize(const FECsWeapon& Type)
{
	return Internal.GetPoolSize(Type);
}

int32 UCsManager_Weapon::GetAllocatedObjectsSize(const FECsWeapon& Type)
{
	return Internal.GetAllocatedObjectsSize(Type);
}

bool UCsManager_Weapon::IsExhausted(const FECsWeapon& Type)
{
	return Internal.IsExhausted(Type);
}

	// Find
#pragma region

const FCsWeaponPooled* UCsManager_Weapon::FindObject(const FECsWeapon& Type, const int32& Index)
{
	return Internal.FindObject(Type, Index);
}

const FCsWeaponPooled* UCsManager_Weapon::FindObject(const FECsWeapon& Type, ICsWeapon* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsWeaponPooled* UCsManager_Weapon::FindObject(const FECsWeapon& Type, UObject* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsWeaponPooled* UCsManager_Weapon::FindSafeObject(const FECsWeapon& Type, const int32& Index)
{
	return Internal.FindSafeObject(Type, Index);
}

const FCsWeaponPooled* UCsManager_Weapon::FindSafeObject(const FECsWeapon& Type, ICsWeapon* Object)
{
	return Internal.FindSafeObject(Type, Object);
}

const FCsWeaponPooled* UCsManager_Weapon::FindSafeObject(const FECsWeapon& Type, UObject* Object)
{
	return Internal.FindSafeObject(Type, Object);
}

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region

void UCsManager_Weapon::Update(const FCsDeltaTime& DeltaTime)
{
	Internal.Update(DeltaTime);
}

void UCsManager_Weapon::OnPreUpdate_Pool(const FECsWeapon& Type)
{
	CurrentUpdatePoolType		 = Type;
	CurrentUpdatePoolObjectIndex = 0;
}

void UCsManager_Weapon::OnUpdate_Object(const FECsWeapon& Type, const FCsWeaponPooled* Object)
{
	++CurrentUpdatePoolObjectIndex;
}

void UCsManager_Weapon::OnPostUpdate_Pool(const FECsWeapon& Type)
{
}

#pragma endregion Update

	// Payload
#pragma region

void UCsManager_Weapon::ConstructPayloads(const FECsWeapon& Type, const int32& Size)
{
	Internal.ConstructPayloads(Type, Size);
}

ICsWeaponPayload* UCsManager_Weapon::ConstructPayload(const FECsWeapon& Type)
{
	return new FCsWeaponPooledPayloadImpl();
}

ICsWeaponPayload* UCsManager_Weapon::AllocatePayload(const FECsWeapon& Type)
{
	return Internal.AllocatePayload(Type);
}

#pragma endregion Payload

	// Spawn
#pragma region

const FCsWeaponPooled* UCsManager_Weapon::Spawn(const FECsWeapon& Type, ICsWeaponPayload* Payload)
{
	return Internal.Spawn(Type, Payload);
}

#pragma endregion Spawn

	// Destroy
#pragma region

bool UCsManager_Weapon::Destroy(const FECsWeapon& Type, ICsWeapon* Weapon)
{
	return Internal.Destroy(Type, Weapon);
}

bool UCsManager_Weapon::Destroy(ICsWeapon* Weapon)
{
	return Internal.Destroy(Weapon);
}

#pragma endregion Destroy

#pragma endregion Internal

// Data
#pragma region

void UCsManager_Weapon::PopulateDataMapFromSettings()
{
	using namespace NCsManagerWeapon;

	if (UCsWeaponSettings* ModuleSettings = GetMutableDefault<UCsWeaponSettings>())
	{
		for (FCsWeaponSettings_DataTable_Weapons& Weapons : ModuleSettings->Weapons)
		{
			// TODO: Get DataTable from Manager_Data

			// TODO: Add check for ModuleSettings->Manager_Weapon.Payload

			bool LoadedFromManagerData = false;

			if (!LoadedFromManagerData)
			{
				// LOG Warning
			}

			// Check DataTable of Weapons
			TSoftObjectPtr<UDataTable> DT_SoftObject = Weapons.Weapons;

			if (UDataTable* DT = DT_SoftObject.LoadSynchronous())
			{
				UCsLibrary_Load::LoadDataTable(DT, NCsLoadFlags::All, NCsLoadCodes::All);

				if (!LoadedFromManagerData)
				{
					DataTables.Add(DT);
				}

				const TSet<FECsWeaponData>& EmulatedDataInterfaces = Weapons.EmulatedDataInterfaces;

				if (EmulatedDataInterfaces.Num() > CS_EMPTY)
				{
					CreateEmulatedDataFromDataTable(DT, EmulatedDataInterfaces);
				}
				else
				{
					PopulateDataMapFromDataTable(DT);
				}
			}
		}
	}
}

void UCsManager_Weapon::CreateEmulatedDataFromDataTable(UDataTable* DataTable, const TSet<FECsWeaponData>& EmulatedDataInterfaces)
{
	using namespace NCsManagerWeapon;

	const FString& Context = Str::CreateEmulatedDataFromDataTable;

	const UScriptStruct* RowStruct = DataTable->GetRowStruct();

	checkf(EmulatedDataInterfaces.Find(NCsWeaponData::Weapon), TEXT("%s: Emulated Data Interfaces must include ICsData_Weapon."), *Context);

	// ICsData_Weapon
	bool Emulates_ICsDataWeapon = true;

	// ICsData_ProjectileWeapon
	bool Emulates_ICsData_ProjectileWeapon = false;

		// bDoFireOnRelease
	UBoolProperty* bDoFireOnReleaseProperty = nullptr;
		// bFullAuto
	UBoolProperty* bFullAutoProperty = nullptr;
		// MaxAmmo
	UIntProperty* MaxAmmoProperty = nullptr;
		// ProjectilesPerShot
	UIntProperty* ProjectilesPerShotProperty = nullptr;
		// TimeBetweenShots
	UFloatProperty* TimeBetweenShotsProperty = nullptr;
		// TimeBetweenAutoShots
	UFloatProperty* TimeBetweenAutoShotsProperty = nullptr;
		// TimeBetweenProjectilesPerShot
	UFloatProperty* TimeBetweenProjectilesPerShotProperty = nullptr;

	if (EmulatedDataInterfaces.Find(NCsWeaponData::ProjectileWeapon))
	{
		// bDoFireOnRelease
		bDoFireOnReleaseProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<UBoolProperty>(Context, RowStruct, Name::bDoFireOnRelease, NCsWeaponData::ProjectileWeapon.GetDisplayName());
		// bFullAuto
		bFullAutoProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<UBoolProperty>(Context, RowStruct, Name::bFullAuto, NCsWeaponData::ProjectileWeapon.GetDisplayName());
		// MaxAmmo
		MaxAmmoProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<UIntProperty>(Context, RowStruct, Name::MaxAmmo, NCsWeaponData::ProjectileWeapon.GetDisplayName());
		// ProjectilesPerShot
		ProjectilesPerShotProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<UIntProperty>(Context, RowStruct, Name::ProjectilesPerShot, NCsWeaponData::ProjectileWeapon.GetDisplayName());
		// TimeBetweenShots
		TimeBetweenShotsProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<UFloatProperty>(Context, RowStruct, Name::TimeBetweenShots, NCsWeaponData::ProjectileWeapon.GetDisplayName());
		// TimeBetweenAutoShots
		TimeBetweenAutoShotsProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<UFloatProperty>(Context, RowStruct, Name::TimeBetweenAutoShots, NCsWeaponData::ProjectileWeapon.GetDisplayName());
		// TimeBetweenProjectilesPerShot
		TimeBetweenProjectilesPerShotProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<UFloatProperty>(Context, RowStruct, Name::TimeBetweenProjectilesPerShot, NCsWeaponData::ProjectileWeapon.GetDisplayName());

		Emulates_ICsData_ProjectileWeapon = true;
	}

	// ICsData_ProjectileWeaponSound
	bool Emulates_ICsData_ProjectileWeaponSound = false;

		// FireSound
	UStructProperty* FireSoundProperty = nullptr;

	if (EmulatedDataInterfaces.Find(NCsWeaponData::ProjectileWeaponSound))
	{
		// FireSound
		FireSoundProperty = FCsLibrary_Property::FindStructPropertyByNameForInterfaceChecked<FCsSound>(Context, RowStruct, Name::FireSound, NCsWeaponData::ProjectileWeaponSound.GetDisplayName());

		Emulates_ICsData_ProjectileWeaponSound = true;
	}

	// Weapon
	UStructProperty* WeaponProperty = FCsLibrary_Property::FindPropertyByName<UStructProperty>(RowStruct, Name::Weapon);

	if (!WeaponProperty)
	{
		UE_LOG(LogCsWp, Warning, TEXT("UCsManager_Weapon::CreateEmulatedDataFromDataTable: Failed to find StructProperty: Weapon in Struct: %s"), *(RowStruct->GetName()));
	}

	const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

	for (const TPair<FName, uint8*>& Pair : RowMap)
	{
		const FName& Name = Pair.Key;
		uint8* RowPtr	  = const_cast<uint8*>(Pair.Value);

		// ICsData_Weapon
		if (Emulates_ICsDataWeapon)
		{
			// Setup and Add Emulated Interface
			FCsData_WeaponImpl* Data = new FCsData_WeaponImpl();

			checkf(EmulatedDataMap.Find(Name) == nullptr, TEXT("%s: Data has already been created for Row: %s."), *Context, *(Name.ToString()));

			EmulatedDataMap.Add(Name, Data);

			FCsData_WeaponInterfaceMap* EmulatedInterfaceMap = new FCsData_WeaponInterfaceMap();

			checkf(EmulatedDataInterfaceMap.Find(Name) == nullptr, TEXT("%s: Emulated Interface Map has already been created for Row: %s."), *Context, *(Name.ToString()));

			EmulatedDataInterfaceMap.Add(Name, EmulatedInterfaceMap);

			FCsInterfaceMap* InterfaceMap = EmulatedInterfaceMap->GetInterfaceMap();

			InterfaceMap->Add<ICsData_Weapon>(FCsData_WeaponImpl::Name, static_cast<ICsData_Weapon*>(Data));

			Data->SetInterfaceMap(InterfaceMap);

			TMap<FName, void*>& InterfaceImplMap = EmulatedDataInterfaceImplMap.FindOrAdd(Name);
			InterfaceImplMap.Add(FCsData_WeaponImpl::Name, Data);

			DataMap.Add(Name, Data);
		}
		// ICsData_ProjectileWeapon
		if (Emulates_ICsData_ProjectileWeapon)
		{
			// Setup and Add Emulated Interface
			FCsData_ProjectileWeaponImpl* Data = new FCsData_ProjectileWeaponImpl();

			FCsData_WeaponInterfaceMap* EmulatedInterfaceMap = EmulatedDataInterfaceMap[Name];
			FCsInterfaceMap* InterfaceMap					 = EmulatedInterfaceMap->GetInterfaceMap();

			InterfaceMap->Add<ICsData_ProjectileWeapon>(FCsData_ProjectileWeaponImpl::Name, static_cast<ICsData_ProjectileWeapon*>(Data));

			Data->SetInterfaceMap(InterfaceMap);

			TMap<FName, void*>& InterfaceImplMap = EmulatedDataInterfaceImplMap.FindOrAdd(Name);
			InterfaceImplMap.Add(FCsData_ProjectileWeaponImpl::Name, Data);

			// bDoFireOnRelease
			{
				bool* Value = FCsLibrary_Property::ContainerPtrToValuePtrChecked<bool>(Context, bDoFireOnReleaseProperty, RowPtr);

				Data->SetDoFireOnRelease(Value);
			}
			// bFullAuto
			{
				bool* Value = FCsLibrary_Property::ContainerPtrToValuePtrChecked<bool>(Context, bFullAutoProperty, RowPtr);

				Data->SetFullAuto(Value);
			}
			// MaxAmmo
			{
				int32* Value = FCsLibrary_Property::ContainerPtrToValuePtrChecked<int32>(Context, MaxAmmoProperty, RowPtr);

				Data->SetMaxAmmo(Value);
			}
			// ProjectilesPerShot
			{
				int32* Value = FCsLibrary_Property::ContainerPtrToValuePtrChecked<int32>(Context, ProjectilesPerShotProperty, RowPtr);

				Data->SetProjectilesPerShot(Value);
			}
			// TimeBetweenShots
			{
				float* Value = FCsLibrary_Property::ContainerPtrToValuePtrChecked<float>(Context, TimeBetweenShotsProperty, RowPtr);

				Data->SetTimeBetweenShots(Value);
			}
			// TimeBetweenAutoShots
			{
				float* Value = FCsLibrary_Property::ContainerPtrToValuePtrChecked<float>(Context, TimeBetweenAutoShotsProperty, RowPtr);

				Data->SetTimeBetweenAutoShots(Value);
			}
			// TimeBetweenProjectilesPerShot
			{
				float* Value = FCsLibrary_Property::ContainerPtrToValuePtrChecked<float>(Context, TimeBetweenProjectilesPerShotProperty, RowPtr);

				Data->SetTimeBetweenProjectilesPerShot(Value);
			}
		}
		// ICsData_ProjectileWeaponSound
		if (Emulates_ICsData_ProjectileWeaponSound)
		{
			// Setup and Add Emulated Interface
			FCsData_ProjectileWeaponSoundImpl* Data = new FCsData_ProjectileWeaponSoundImpl();

			FCsData_WeaponInterfaceMap* EmulatedInterfaceMap = EmulatedDataInterfaceMap[Name];
			FCsInterfaceMap* InterfaceMap					 = EmulatedInterfaceMap->GetInterfaceMap();

			InterfaceMap->Add<ICsData_ProjectileWeaponSound>(FCsData_ProjectileWeaponSoundImpl::Name, static_cast<ICsData_ProjectileWeaponSound*>(Data));

			Data->SetInterfaceMap(InterfaceMap);

			TMap<FName, void*>& InterfaceImplMap = EmulatedDataInterfaceImplMap.FindOrAdd(Name);
			InterfaceImplMap.Add(FCsData_ProjectileWeaponSoundImpl::Name, Data);

			// FireSound
			{
				FCsSound* Value = FCsLibrary_Property::ContainerPtrToValuePtrChecked<FCsSound>(Context, FireSoundProperty, RowPtr);

				Data->SetFireSound(Value);
			}
		}

		// Weapon
		if (WeaponProperty)
		{
			FCsWeaponPtr* WeaponPtr = WeaponProperty->ContainerPtrToValuePtr<FCsWeaponPtr>(RowPtr);

			checkf(WeaponPtr, TEXT("UCsManager_Weapon::CreateEmulatedDataFromDataTable: WeaponPtr is NULL."));

			WeaponMap.Add(Name, WeaponPtr);
		}
	}
}

void UCsManager_Weapon::DeconstructEmulatedData(const FName& InterfaceImplName, void* Data)
{
	// FCsData_WeaponImpl
	if (InterfaceImplName == FCsData_WeaponImpl::Name)
	{
		delete static_cast<FCsData_WeaponImpl*>(Data);
	}
	// FCsData_ProjectileWeaponImpl
	else
	if (InterfaceImplName == FCsData_ProjectileWeaponImpl::Name)
	{
		delete static_cast<FCsData_ProjectileWeaponImpl*>(Data);
	}
	// FCsData_ProjectileWeaponSoundImpl
	else
	if (InterfaceImplName == FCsData_ProjectileWeaponSoundImpl::Name)
	{
		delete static_cast<FCsData_ProjectileWeaponSoundImpl*>(Data);
	}
	else
	{
		checkf(0, TEXT("UCsManager_Weapon::DeconstructEmulatedData: Failed to delete InterfaceMap."));
	}
}

void UCsManager_Weapon::PopulateDataMapFromDataTable(UDataTable* DataTable)
{
	using namespace NCsManagerWeapon;

	const UScriptStruct* RowStruct = DataTable->GetRowStruct();

	// Data
	UStructProperty* DataProperty = FCsLibrary_Property::FindPropertyByName<UStructProperty>(RowStruct, Name::Data);

	if (DataProperty &&
		DataProperty->Struct == FCsDataWeapon::StaticStruct())
	{
		const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

		for (const TPair<FName, uint8*>& Pair : RowMap)
		{
			const FName& Name = Pair.Key;
			uint8* RowPtr     = const_cast<uint8*>(Pair.Value);

			FCsDataWeapon* DataPtr = DataProperty->ContainerPtrToValuePtr<FCsDataWeapon>(RowPtr);

			if (ICsData_Weapon* Data = DataPtr->Get<ICsData_Weapon>())
			{
				DataMap.Add(Name, Data);
			}
		}
	}
}

ICsData_Weapon* UCsManager_Weapon::GetData(const FName& Name)
{
	checkf(Name != NAME_None, TEXT("UCsManager_Weapon::GetData: Name: None is NOT Valid."));

	// TODO: Get the Data from Manager_Data or have a callback whenever Payload is unloaded

	ICsData_Weapon** DataPtr = DataMap.Find(Name);

	checkf(DataPtr, TEXT("UCsManager_Weapon::GetData: Failed to find Data for Name: %s."), *(Name.ToString()));

	return *DataPtr;
}

ICsData_Weapon* UCsManager_Weapon::GetData(const FECsWeapon& Type)
{
	checkf(EMCsWeapon::Get().IsValidEnum(Type), TEXT("UCsManager_Weapon::GetData: Type: %s is NOT Valid."), Type.ToChar());

	return GetData(Type.GetFName());
}

void UCsManager_Weapon::OnPayloadUnloaded(const FName& Payload)
{
}

FCsWeaponPtr* UCsManager_Weapon::GetWeaponPtr(const FName& Name)
{
	checkf(Name != NAME_None, TEXT("UCsManager_Weapon::GetWeaponPtr: Name: None is NOT Valid."));

	FCsWeaponPtr** Ptr = WeaponMap.Find(Name);

	return Ptr ? *Ptr : nullptr;
}

FCsWeaponPtr* UCsManager_Weapon::GetWeaponPtr(const FECsWeapon& Type)
{
	checkf(EMCsWeapon::Get().IsValidEnum(Type), TEXT("UCsManager_Weapon::GetWeaponPtr: Type: %s is NOT Valid."), Type.ToChar());

	return GetWeaponPtr(Type.GetFName());
}
#pragma endregion Data