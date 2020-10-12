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
#include "Data/CsLibrary_Data.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
#include "Settings/CsWeaponSettings.h"
// Managers
#include "Managers/Data/CsManager_Data.h"
// Data
#include "Data/CsWpGetDataRootSet.h"
#include "Data/CsData_WeaponInterfaceMap.h"
#include "Data/CsData.h"
#include "Data/CsData_WeaponEmuSlice.h"
#include "Projectile/Data/CsData_ProjectileWeaponEmuSlice.h"
#include "Projectile/Data/Sound/CsData_ProjectileWeapon_SoundFireImpl.h"
// Weapon
#include "Payload/CsPayload_WeaponPooledImpl.h"
// Game
#include "Engine/GameInstance.h"
#include "GameFramework/GameStateBase.h"

#include "Engine/World.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Weapon/CsGetManagerWeapon.h"

#include "Library/CsLibrary_Common.h"

#include "Engine/Engine.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerWeapon
{
	namespace Str
	{
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Weapon, SetupInternal);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Weapon, InitInternalFromSettings);
		CS_DEFINE_CACHED_STRING(Class, "Class");

		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Weapon, PopulateClassMapFromSettings);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Weapon, GetWeapon);
		CS_DEFINE_CACHED_STRING(Type, "Type");

		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Weapon, GetData);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Weapon, PopulateDataMapFromSettings);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Weapon, CreateEmulatedDataFromDataTable);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Weapon, DeconstructEmulatedData);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Weapon, PopulateDataMapFromDataTable);
	}

	namespace Name
	{
		const FName Weapon = FName("Weapon");
		const FName Class = FName("Class");
		const FName Data = FName("Data");

		// ICsData_ProjectileWeapon
		const FName bDoFireOnRelease = FName("bDoFireOnRelease");
		const FName bFullAuto = FName("bFullAuto");
		const FName bInfiniteAmmo = FName("bInfiniteAmmo");
		const FName MaxAmmo = FName("MaxAmmo");
		const FName ProjectilesPerShot = FName("ProjectilesPerShot");
		const FName TimeBetweenShots = FName("TimeBetweenShots");
		const FName TimeBetweenAutoShots = FName("TimeBetweenAutoShots");
		const FName TimeBetweenProjectilesPerShot = FName("TimeBetweenProjectilesPerShot");
		// ICsData_ProjectileWeapon_SoundFire
		const FName FireSound = FName("FireSound");
	}
}

#pragma endregion Cached

// Internal
#pragma region

namespace NCsWeapon
{
	FManager::FManager()
		: Super()
	{
	}
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
	
	bInitialized = true;
}

/*static*/ bool UCsManager_Weapon::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_Weapon::CleanUp()
{
	Internal.Shutdown();
	Pool.Reset();

	// Class
	ResetClassContainers();
	// Data
	ResetDataContainers();

	bInitialized = false;
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
	using namespace NCsManagerWeapon;

	const FString& Context = Str::SetupInternal;

	// Populate EnumMaps
	UWorld* World				= MyRoot->GetWorld();
	UGameInstance* GameInstance = World ? World->GetGameInstance() : nullptr;

	NCsWeapon::PopulateEnumMapFromSettings(Context, GameInstance);
	NCsWeaponClass::PopulateEnumMapFromSettings(Context, GameInstance);
	NCsWeaponState::PopulateEnumMapFromSettings(Context, GameInstance);

	// Delegates
	{
		// Log
		Internal.Log_Impl.BindUObject(this, &UCsManager_Weapon::Log);
		Internal.LogTransaction_Impl.BindUObject(this, &UCsManager_Weapon::LogTransaction);
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

		// Populate TypeMapArray
		{
			const int32& Count = EMCsWeapon::Get().Num();

			TypeMapArray.Reset(Count);

			for (const FECsWeapon& Type : EMCsWeapon::Get())
			{
				TypeMapArray.Add(Type);
			}

			for (const TPair<FECsWeapon, FECsWeapon>& Pair : Settings.TypeMap)
			{
				TypeMapArray[Pair.Key.GetValue()] = Pair.Value;
			}
		}

		InitInternalFromSettings();
	}
}

void UCsManager_Weapon::InitInternalFromSettings()
{
	using namespace NCsManagerWeapon;

	const FString& Context = Str::InitInternalFromSettings;

	PopulateClassMapFromSettings();
	PopulateDataMapFromSettings();

	// Setup Pool
	if (Settings.PoolParams.Num() > CS_EMPTY)
	{
		typedef NCsWeapon::FManager::FParams ManagerParamsType;

		ManagerParamsType ManagerParams;

		ManagerParams.Name  = TEXT("UCsManager_Weapon::NCsWeapon::FManager");
		ManagerParams.World = MyRoot->GetWorld();

		//  Pool params for each specified Weapon Type
		for (const TPair<FECsWeapon, FCsSettings_Manager_Weapon_PoolParams>& Pair : Settings.PoolParams)
		{
			const FECsWeapon& Type									= Pair.Key;
			const FCsSettings_Manager_Weapon_PoolParams& Params = Pair.Value;

			typedef NCsPooledObject::NManager::FPoolParams PoolParamsType;

			PoolParamsType& PoolParams = ManagerParams.ObjectParams.Add(Type);

			// Get Class
			const FECsWeaponClass& ClassType = Params.Class;

			check(EMCsWeaponClass::Get().IsValidEnumChecked(Context, Str::Class, ClassType));

			FCsWeapon* Weapon = GetWeaponChecked(Context, ClassType);
			UClass* Class	  = Weapon->GetClass();

			checkf(Class, TEXT("%s: Failed to get class for Type: %s ClassType: %s."), *Context, Type.ToChar(), ClassType.ToChar());

			PoolParams.Name								= ManagerParams.Name + TEXT("_") + Type.ToChar();
			PoolParams.World							= ManagerParams.World;
			//PoolParams.LogType
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

#define ManagerParamsType NCsWeapon::FManager::FParams
void UCsManager_Weapon::InitInternal(const ManagerParamsType& Params)
{
#undef ManagerParamsType
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
		UE_LOG(LogCsWp, Warning, TEXT("UCsManager_Weapon::CreatePool: Pool for Creep: %s has already been created with Size: %d."), Type.ToChar(), PoolSize);
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

#define ConstructParamsType NCsPooledObject::NManager::FConstructParams
TMulticastDelegate<void, const FCsWeaponPooled*, const ConstructParamsType&>& UCsManager_Weapon::GetOnConstructObject_Event(const FECsWeapon& Type)
{
#undef ConstructParamsType
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

#define PayloadType NCsWeapon::NPayload::IPayload
PayloadType* UCsManager_Weapon::ConstructPayload(const FECsWeapon& Type)
{
#undef PayloadType
	
	typedef NCsWeapon::NPayload::FImplPooled PayloadImplType;

	return new PayloadImplType();
}

#define PayloadType NCsWeapon::NPayload::IPayload
PayloadType* UCsManager_Weapon::AllocatePayload(const FECsWeapon& Type)
{
#undef PayloadType
	return Internal.AllocatePayload(Type);
}

#pragma endregion Payload

	// Spawn
#pragma region

#define PayloadType NCsWeapon::NPayload::IPayload
const FCsWeaponPooled* UCsManager_Weapon::Spawn(const FECsWeapon& Type, PayloadType* Payload)
{
#undef PayloadType
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

	// Log
#pragma region

void UCsManager_Weapon::Log(const FString& Str)
{
	UE_LOG(LogCsWp, Warning, TEXT("%s"), *Str);
}

void UCsManager_Weapon::LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsWeaponPooled* Object)
{

}

#pragma endregion Log

#pragma endregion Internal

// Class
#pragma region

void UCsManager_Weapon::GetWeaponClassesDataTableChecked(const FString& Context, UDataTable*& OutDataTable, TSoftObjectPtr<UDataTable>& OutDataTableSoftObject)
{
	// Get DataRootSetImpl
	UWorld* World				  = MyRoot->GetWorld();
	UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());
	UObject* DataRootSetImpl	  = Manager_Data->DataRootSet.GetObject();

	checkf(DataRootSetImpl, TEXT("%s: Failed to find DataRootSet."), *Context);

	// Get DataRootSet for this Module
	ICsWpGetDataRootSet* GetDataRootSet = Cast<ICsWpGetDataRootSet>(DataRootSetImpl);

	checkf(GetDataRootSet, TEXT("%s: DataRootSet: %s with Class: %s does NOT implement interface: ICsWpGetDataRootSet."), *Context, *(DataRootSetImpl->GetName()), *(DataRootSetImpl->GetClass()->GetName()));

	const FCsWpDataRootSet& DataRootSet = GetDataRootSet->GetCsWpDataRootSet();

	OutDataTableSoftObject = DataRootSet.WeaponClasses;

	checkf(OutDataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetCsWpDataRootSet().WeaponClasses is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

	OutDataTable = Manager_Data->GetDataTable(OutDataTableSoftObject);

	checkf(OutDataTable, TEXT("%s: Failed to get DataTable @ %s."), *Context, *(OutDataTableSoftObject.ToSoftObjectPath().ToString()));
}

void UCsManager_Weapon::PopulateClassMapFromSettings()
{
	using namespace NCsManagerWeapon;

	const FString& Context = Str::PopulateClassMapFromSettings;

	// Reset appropriate containers
	ResetClassContainers();

	// Get DataRootSetImpl
	UWorld* World				  = MyRoot->GetWorld();
	UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

	UDataTable* DataTable = nullptr;
	TSoftObjectPtr<UDataTable> DT_SoftObject(nullptr);

	GetWeaponClassesDataTableChecked(Context, DataTable, DT_SoftObject);

	// Get Classes from DataTable

	const UScriptStruct* RowStruct = DataTable->GetRowStruct();

	// Get the Property named "Class" if it exists.
	FStructProperty* ClassProperty = FCsLibrary_Property::FindStructPropertyByName<FCsWeaponPtr>(RowStruct, Name::Class);

	if (!ClassProperty)
	{
		UE_LOG(LogCsWp, Warning, TEXT("%s: Failed to find StructProperty: Class in DataTable: %s with Struct: %s"), *Context, *(DataTable->GetName()), *(RowStruct->GetName()));
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
			FCsWeaponPtr* WeaponPtr = ClassProperty->ContainerPtrToValuePtr<FCsWeaponPtr>(RowPtr);

			checkf(WeaponPtr, TEXT("%s: WeaponPtr is NULL."), *Context);

			UObject* O = WeaponPtr->Get();

			checkf(O, TEXT("%s: Failed to get weapon from DataTable: %s: Row: %s."), *Context, *(DataTable->GetName()), *(Name.ToString()));

			FCsWeapon& Weapon = WeaponClassByClassTypeMap.Add(Name);

			Weapon.SetObject(O);
		}
	}
}

FCsWeapon* UCsManager_Weapon::GetWeapon(const FECsWeapon& Type)
{
	using namespace NCsManagerWeapon;

	const FString& Context = Str::GetWeapon;

	check(EMCsWeapon::Get().IsValidEnumChecked(Context, Str::Type, Type));

	return WeaponClassByTypeMap.Find(Type.GetFName());
}

FCsWeapon* UCsManager_Weapon::GetWeaponChecked(const FString& Context, const FECsWeapon& Type)
{
	FCsWeapon* Ptr = GetWeapon(Type);

	checkf(Ptr, TEXT("%s: Failed to find a Weapon associated with Type: %s."), *Context, Type.ToChar());

	return Ptr;
}

FCsWeapon* UCsManager_Weapon::GetWeapon(const FECsWeaponClass& Type)
{
	using namespace NCsManagerWeapon;

	const FString& Context = Str::GetWeapon;

	check(EMCsWeaponClass::Get().IsValidEnumChecked(Context, Str::Type, Type));

	return WeaponClassByClassTypeMap.Find(Type.GetFName());
}

FCsWeapon* UCsManager_Weapon::GetWeaponChecked(const FString& Context, const FECsWeaponClass& Type)
{
	FCsWeapon* Ptr = GetWeapon(Type);

	checkf(Ptr, TEXT("%s: Failed to find a Weapon associated with Type: %s."), *Context, Type.ToChar());

	return Ptr;
}

void UCsManager_Weapon::ResetClassContainers()
{
	WeaponClassByTypeMap.Reset();
	WeaponClassByClassTypeMap.Reset();
}

#pragma endregion Class

// Data
#pragma region

void UCsManager_Weapon::PopulateDataMapFromSettings()
{
	using namespace NCsManagerWeapon;

	const FString& Context = Str::PopulateDataMapFromSettings;

	// Reset appropriate containers
	ResetDataContainers();

	// Get DataRootSetImpl
	UWorld* World = MyRoot->GetWorld();

	UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());
	UObject* DataRootSetImpl	  = Manager_Data->DataRootSet.GetObject();

	checkf(DataRootSetImpl, TEXT("%s: Failed to find DataRootSet."), *Context);

	// Get DataRootSet for this Module
	ICsWpGetDataRootSet* GetDataRootSet = Cast<ICsWpGetDataRootSet>(DataRootSetImpl);

	checkf(GetDataRootSet, TEXT("%s: DataRootSet: %s with Class: %s does NOT implement interface: ICsWpGetDataRootSet."), *Context, *(DataRootSetImpl->GetName()), *(DataRootSetImpl->GetClass()->GetName()));

	const FCsWpDataRootSet& DataRootSet = GetDataRootSet->GetCsWpDataRootSet();

	// Find which DataTables have been loaded
	for (const FCsWeaponSettings_DataTable_Weapons& Weapons : DataRootSet.Weapons)
	{
		// Check DataTable of Weapons
		TSoftObjectPtr<UDataTable> DT_SoftObject = Weapons.Weapons;

		if (UDataTable* DT = Manager_Data->GetDataTable(DT_SoftObject))
		{
			DataTables.Add(DT);

			// Emulated
			const TSet<FECsWeaponData>& EmulatedDataInterfaces = Weapons.EmulatedDataInterfaces;

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

void UCsManager_Weapon::CreateEmulatedDataFromDataTable(UDataTable* DataTable, const TSoftObjectPtr<UDataTable>& DataTableSoftObject, const TSet<FECsWeaponData>& EmulatedDataInterfaces)
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
	FBoolProperty* bDoFireOnReleaseProperty = nullptr;
		// bFullAuto
	FBoolProperty* bFullAutoProperty = nullptr;
		// bInfiniteAmmo
	FBoolProperty* bInfiniteAmmoProperty = nullptr;
		// MaxAmmo
	FIntProperty* MaxAmmoProperty = nullptr;
		// ProjectilesPerShot
	FIntProperty* ProjectilesPerShotProperty = nullptr;
		// TimeBetweenShots
	FFloatProperty* TimeBetweenShotsProperty = nullptr;
		// TimeBetweenAutoShots
	FFloatProperty* TimeBetweenAutoShotsProperty = nullptr;
		// TimeBetweenProjectilesPerShot
	FFloatProperty* TimeBetweenProjectilesPerShotProperty = nullptr;

	if (EmulatedDataInterfaces.Find(NCsWeaponData::ProjectileWeapon))
	{
		// bDoFireOnRelease
		bDoFireOnReleaseProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<FBoolProperty>(Context, RowStruct, Name::bDoFireOnRelease, NCsWeaponData::ProjectileWeapon.GetDisplayName());
		// bFullAuto
		bFullAutoProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<FBoolProperty>(Context, RowStruct, Name::bFullAuto, NCsWeaponData::ProjectileWeapon.GetDisplayName());
		// bInfiniteAmmo
		bInfiniteAmmoProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<FBoolProperty>(Context, RowStruct, Name::bInfiniteAmmo, NCsWeaponData::ProjectileWeapon.GetDisplayName());
		// MaxAmmo
		MaxAmmoProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<FIntProperty>(Context, RowStruct, Name::MaxAmmo, NCsWeaponData::ProjectileWeapon.GetDisplayName());
		// ProjectilesPerShot
		ProjectilesPerShotProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<FIntProperty>(Context, RowStruct, Name::ProjectilesPerShot, NCsWeaponData::ProjectileWeapon.GetDisplayName());
		// TimeBetweenShots
		TimeBetweenShotsProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<FFloatProperty>(Context, RowStruct, Name::TimeBetweenShots, NCsWeaponData::ProjectileWeapon.GetDisplayName());
		// TimeBetweenAutoShots
		TimeBetweenAutoShotsProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<FFloatProperty>(Context, RowStruct, Name::TimeBetweenAutoShots, NCsWeaponData::ProjectileWeapon.GetDisplayName());
		// TimeBetweenProjectilesPerShot
		TimeBetweenProjectilesPerShotProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<FFloatProperty>(Context, RowStruct, Name::TimeBetweenProjectilesPerShot, NCsWeaponData::ProjectileWeapon.GetDisplayName());

		Emulates_ICsData_ProjectileWeapon = true;
	}

	// ICsData_ProjectileWeapon_SoundFire
	bool Emulates_ICsData_ProjectileWeapon_SoundFire = false;

		// FireSound
	FStructProperty* FireSoundProperty = nullptr;

	if (EmulatedDataInterfaces.Find(NCsWeaponData::ProjectileWeaponSound))
	{
		// FireSound
		FireSoundProperty = FCsLibrary_Property::FindStructPropertyByNameForInterfaceChecked<FCsSound>(Context, RowStruct, Name::FireSound, NCsWeaponData::ProjectileWeaponSound.GetDisplayName());

		Emulates_ICsData_ProjectileWeapon_SoundFire = true;
	}

	// Class
	FStructProperty* ClassProperty = FCsLibrary_Property::FindStructPropertyByName<FCsWeaponPtr>(RowStruct, Name::Class);

	if (!ClassProperty)
	{
		UE_LOG(LogCsWp, Warning, TEXT("%s: Failed to find StructProperty: Class in DataTable: %s with Struct: %s"), *Context, *(DataTable->GetName()), *(RowStruct->GetName()));
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

		TMap<FName, uint8*>& Map = DataTableRowByPathMap.FindOrAdd(DataTableSoftObject.ToSoftObjectPath());
		Map.Add(Name, RowPtr);

		// ICsData_Weapon
		if (Emulates_ICsDataWeapon)
		{
			// Setup and Add Emulated Interface
			typedef NCsWeapon::NData::IData DataType;
			typedef NCsWeapon::NData::FEmuSlice DataEmuSliceType;

			DataEmuSliceType* Data = new DataEmuSliceType();

			checkf(EmulatedDataMap.Find(Name) == nullptr, TEXT("%s: Data has already been created for Row: %s."), *Context, *(Name.ToString()));

			EmulatedDataMap.Add(Name, Data);

			FCsData_WeaponInterfaceMap* EmulatedInterfaceMap = new FCsData_WeaponInterfaceMap();

			checkf(EmulatedDataInterfaceMap.Find(Name) == nullptr, TEXT("%s: Emulated Interface Map has already been created for Row: %s."), *Context, *(Name.ToString()));

			EmulatedDataInterfaceMap.Add(Name, EmulatedInterfaceMap);

			FCsInterfaceMap* InterfaceMap = EmulatedInterfaceMap->GetInterfaceMap();

			InterfaceMap->Add<DataType>(DataEmuSliceType::Name, static_cast<DataType*>(Data));

			Data->SetInterfaceMap(InterfaceMap);

			TMap<FName, void*>& InterfaceImplMap = EmulatedDataInterfaceImplMap.FindOrAdd(Name);
			InterfaceImplMap.Add(DataEmuSliceType::Name, Data);

			DataMap.Add(Name, Data);
		}
		// ICsData_ProjectileWeapon
		if (Emulates_ICsData_ProjectileWeapon)
		{
			// Setup and Add Emulated Interface
			typedef NCsWeapon::NProjectile::NData::IData DataType;
			typedef NCsWeapon::NProjectile::NData::FEmuSlice DataEmuSliceType;

			DataEmuSliceType* Data = new DataEmuSliceType();

			FCsData_WeaponInterfaceMap* EmulatedInterfaceMap = EmulatedDataInterfaceMap[Name];
			FCsInterfaceMap* InterfaceMap					 = EmulatedInterfaceMap->GetInterfaceMap();

			InterfaceMap->Add<DataType>(DataEmuSliceType::Name, static_cast<DataType*>(Data));

			Data->SetInterfaceMap(InterfaceMap);

			TMap<FName, void*>& InterfaceImplMap = EmulatedDataInterfaceImplMap.FindOrAdd(Name);
			InterfaceImplMap.Add(DataEmuSliceType::Name, Data);

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
			// bInfiniteAmmo
			{
				bool* Value = FCsLibrary_Property::ContainerPtrToValuePtrChecked<bool>(Context, bInfiniteAmmoProperty, RowPtr);

				Data->SetInfiniteAmmo(Value);
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
		// ICsData_ProjectileWeapon_SoundFire
		if (Emulates_ICsData_ProjectileWeapon_SoundFire)
		{
			// Setup and Add Emulated Interface

			// TODO: Change FImpl to FEmu functionality
			/*
			typedef ICsData_ProjectileWeapon_SoundFire SoundDataType;
			typedef NCsWeapon::NProjectile::NData::NSound::NFire::FImpl SoundDataImplType;

			SoundDataImplType* Data = new SoundDataImplType();

			FCsData_WeaponInterfaceMap* EmulatedInterfaceMap = EmulatedDataInterfaceMap[Name];
			FCsInterfaceMap* InterfaceMap					 = EmulatedInterfaceMap->GetInterfaceMap();

			InterfaceMap->Add<SoundDataType>(SoundDataImplType::Name, static_cast<SoundDataType*>(Data));

			Data->SetInterfaceMap(InterfaceMap);

			TMap<FName, void*>& InterfaceImplMap = EmulatedDataInterfaceImplMap.FindOrAdd(Name);
			InterfaceImplMap.Add(SoundDataImplType::Name, Data);

			// FireSound
			{
				FCsSound* Value = FCsLibrary_Property::ContainerPtrToValuePtrChecked<FCsSound>(Context, FireSoundProperty, RowPtr);

				Data->SetFireSound(Value);
			}
			*/
		}

		// Class
		if (ClassProperty)
		{
			FCsWeaponPtr* WeaponPtr = ClassProperty->ContainerPtrToValuePtr<FCsWeaponPtr>(RowPtr);

			checkf(WeaponPtr, TEXT("%s: WeaponPtr is NULL."), *Context);

			UObject* O = WeaponPtr->Get();

			checkf(O, TEXT("%s: Failed to get weapon from DataTable: %s: Row: %s."), *Context, *(DataTable->GetName()), *(Name.ToString()));

			FCsWeapon& Weapon = WeaponClassByTypeMap.Add(Name);

			Weapon.SetObject(O);
		}
	}
}

void UCsManager_Weapon::DeconstructEmulatedData(const FName& InterfaceImplName, void* Data)
{
	// NCsWeapon::NData::FEmuSlice
	if (InterfaceImplName == NCsWeapon::NData::FEmuSlice::Name)
	{
		delete static_cast<NCsWeapon::NData::FEmuSlice*>(Data);
	}
	// NCsWeapon::NProjectile::NData::FEmuSlice
	else
	if (InterfaceImplName == NCsWeapon::NProjectile::NData::FEmuSlice::Name)
	{
		delete static_cast<NCsWeapon::NProjectile::NData::FEmuSlice*>(Data);
	}
	// NCsWeapon::NProjectile::NData::NSound::NFire::FImpl
	else
	if (InterfaceImplName == NCsWeapon::NProjectile::NData::NSound::NFire::FImpl::Name)
	{
		delete static_cast<NCsWeapon::NProjectile::NData::NSound::NFire::FImpl*>(Data);
	}
	else
	{
		checkf(0, TEXT("UCsManager_Weapon::DeconstructEmulatedData: Failed to delete InterfaceMap."));
	}
}

void UCsManager_Weapon::PopulateDataMapFromDataTable(UDataTable* DataTable, const TSoftObjectPtr<UDataTable>& DataTableSoftObject)
{
	using namespace NCsManagerWeapon;

	const FString& Context = Str::PopulateDataMapFromDataTable;

	// Get Manager_Data
	UWorld* World				  = MyRoot->GetWorld();
	UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

	const UScriptStruct* RowStruct = DataTable->GetRowStruct();

	// Class
	FStructProperty* ClassProperty = FCsLibrary_Property::FindStructPropertyByName<FCsWeaponPtr>(RowStruct, Name::Class);

	if (!ClassProperty)
	{
		UE_LOG(LogCsWp, Warning, TEXT("%s: Failed to find StructProperty: Class in DataTable: %s with Struct: %s"), *Context, *(DataTable->GetName()), *(RowStruct->GetName()));
	}

	// Data
	FStructProperty* DataProperty = FCsLibrary_Property::FindStructPropertyByName<FCsData_WeaponPtr>(RowStruct, Name::Data);

	if (!DataProperty)
	{
		UE_LOG(LogCsWp, Warning, TEXT("%s: Failed to find StructProperty: Data in DataTable: %s with Struct: %s"), *Context, *(DataTable->GetName()), *(RowStruct->GetName()));
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
			FCsWeaponPtr* WeaponPtr = ClassProperty->ContainerPtrToValuePtr<FCsWeaponPtr>(RowPtr);

			checkf(WeaponPtr, TEXT("%s: WeaponPtr is NULL."), *Context);

			UObject* O = WeaponPtr->Get();

			checkf(O, TEXT("%s: Failed to get weapon from DataTable: %s: Row: %s."), *Context, *(DataTable->GetName()), *(Name.ToString()));

			FCsWeapon& Weapon = WeaponClassByTypeMap.Add(Name);

			Weapon.SetObject(O);
		}

		// Data
		if (DataProperty)
		{
			FCsData_WeaponPtr* DataPtr = DataProperty->ContainerPtrToValuePtr<FCsData_WeaponPtr>(RowPtr);

			UObject* O = DataPtr->Get();

			checkf(O, TEXT("%s: Failed to get data from DataTable: %s Row: %s."), *Context, *(DataTable->GetName()), *(Name.ToString()));

			ICsData* Data = Cast<ICsData>(O);

			checkf(Data, TEXT("%s: Data: %s with Class: %s does NOT implement interface: ICsData."), *Context, *(O->GetName()), *(O->GetClass()->GetName()));

			typedef NCsData::IData DataType;

			DataType* IData = Data->_getIData();

			checkf(IData, TEXT("%s: Failed to get IData (Data emulating ICsData) from Data: %s with Class: %s."));

			typedef NCsWeapon::NData::IData WeaponDataType;

			WeaponDataType* WeaponData = NCsData::FLibrary::GetInterfaceChecked<WeaponDataType>(Context, IData);

			DataMap.Add(Name, WeaponData);
		}
	}
}

#define DataType NCsWeapon::NData::IData
DataType* UCsManager_Weapon::GetData(const FName& Name)
{
	checkf(Name != NAME_None, TEXT("UCsManager_Weapon::GetData: Name: None is NOT Valid."));

	// Check emulated data
	if (DataType** EmuDataPtr = EmulatedDataMap.Find(Name))
		return *EmuDataPtr;

	// Check data
	if (DataType** DataPtr = DataMap.Find(Name))
		return *DataPtr;

	return nullptr;
}
#undef DataType

#define DataType NCsWeapon::NData::IData
DataType* UCsManager_Weapon::GetData(const FECsWeapon& Type)
{
#undef DataType

	using namespace NCsManagerWeapon;

	const FString& Context = Str::GetData;

	check(EMCsWeapon::Get().IsValidEnumChecked(Context, Str::Type, Type));

	return GetData(Type.GetFName());
}

#define DataType NCsWeapon::NData::IData
DataType* UCsManager_Weapon::GetDataChecked(const FString& Context, const FName& Name)
{
	DataType* Ptr = GetData(Name);

	checkf(Ptr, TEXT("%s: Failed to find a Data associated with Name: %s."), *(Name.ToString()));

	return Ptr;
}
#undef DataType

#define DataType NCsWeapon::NData::IData
DataType* UCsManager_Weapon::GetDataChecked(const FString& Context, const FECsWeapon& Type)
{
	DataType* Ptr = GetData(Type);

	checkf(Ptr, TEXT("%s: Failed to find a Data associated with Type: %s."), Type.ToChar());

	return Ptr;
}
#undef DataType

void UCsManager_Weapon::ResetDataContainers()
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

	for (TPair<FName, FCsData_WeaponInterfaceMap*>& Pair : EmulatedDataInterfaceMap)
	{
		FCsData_WeaponInterfaceMap* Ptr = Pair.Value;
		delete Ptr;
		Pair.Value = nullptr;
	}
	EmulatedDataInterfaceMap.Reset();

	DataMap.Reset();
	DataTables.Reset(DataTables.Max());
	DataTableRowByPathMap.Reset();
}

void UCsManager_Weapon::OnPayloadUnloaded(const FName& Payload)
{
}

#pragma endregion Data