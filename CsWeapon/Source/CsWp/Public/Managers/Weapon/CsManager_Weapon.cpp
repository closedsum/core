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
// Utility
#include "Utility/CsWpLog.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
#include "Settings/CsWeaponSettings.h"
// Managers
#include "Managers/Data/CsManager_Data.h"
// Data
#include "Data/CsWpGetDataRootSet.h"
#include "Data/CsData_WeaponInterfaceMap.h"
#include "Data/CsData.h"
#include "Data/CsData_WeaponImplSlice.h"
#include "Projectile/Data/CsData_ProjectileWeaponImplSlice.h"
#include "Projectile/Data/Sound/CsData_ProjectileWeapon_SoundFireImpl.h"
// Weapon
#include "Managers/Weapon/Handler/CsManager_Weapon_ClassHandler.h"
#include "Managers/Weapon/Handler/CsManager_Weapon_DataHandler.h"
#include "Payload/CsPayload_WeaponPooledImpl.h"

#if WITH_EDITOR
// Library
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
// Singleton
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Weapon/CsGetManagerWeapon.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerWeapon
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Weapon, GetFromWorldContextObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Weapon, SetupInternal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Weapon, InitInternalFromSettings);
			CS_DEFINE_CACHED_STRING(Class, "Class");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Weapon, PopulateClassMapFromSettings);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Weapon, GetWeapon);

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Weapon, GetData);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Weapon, PopulateDataMapFromSettings);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Weapon, CreateEmulatedDataFromDataTable);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Weapon, DeconstructEmulatedData);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Weapon, PopulateDataMapFromDataTable);
		}
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

#if WITH_EDITOR

/*static*/ UCsManager_Weapon* UCsManager_Weapon::Get(UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerWeapon(InRoot)->GetManager_Weapon();
}

/*static*/ bool UCsManager_Weapon::IsValid(UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerWeapon(InRoot)->GetManager_Weapon() != nullptr;
}

#endif // #if WITH_EDITOR

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
	using namespace NCsManagerWeapon::NCached;

	const FString& Context = Str::GetFromWorldContextObject;

	typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;

	if (UObject* ContextRoot = WeaponManagerLibrary::GetSafe(Context, WorldContextObject))
	{
		if (UCsManager_Weapon* Manager = GetSafe(ContextRoot))
			return Manager;

		UE_LOG(LogCsWp, Warning, TEXT("%s: Failed to Manager Weapon of type UCsManager_Weapon from ContextRoot: %s."), *Context, *(ContextRoot->GetName()));
	}
	return nullptr;
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

	delete ClassHandler;
	ClassHandler = nullptr;

	delete DataHandler;
	DataHandler = nullptr;

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
	using namespace NCsManagerWeapon::NCached;

	const FString& Context = Str::SetupInternal;

	// Populate EnumMaps
	UWorld* World				= MyRoot->GetWorld();
	UGameInstance* GameInstance = World ? World->GetGameInstance() : nullptr;

	NCsWeapon::PopulateEnumMapFromSettings(Context, GameInstance);
	NCsWeaponClass::PopulateEnumMapFromSettings(Context, GameInstance);
	NCsWeaponState::PopulateEnumMapFromSettings(Context, GameInstance);

	// Class Handler
	ConstructClassHandler();

	checkf(ClassHandler, TEXT("%s: Failed to construct ClassHandler."), *Context);

	// Data Handler
	ConstructDataHandler();

	checkf(DataHandler, TEXT("%s: Failed to construct DataHandler."), *Context);

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
	using namespace NCsManagerWeapon::NCached;

	const FString& Context = Str::InitInternalFromSettings;

	ClassHandler->PopulateClassMapFromSettings(Context);
	DataHandler->PopulateDataMapFromSettings(Context);

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

TDelegate<FCsWeaponPooled*(const FECsWeapon&)>& UCsManager_Weapon::GetConstructContainer_Impl()
{
	return Internal.ConstructContainer_Impl;
}

FCsWeaponPooled* UCsManager_Weapon::ConstructContainer(const FECsWeapon& Type)
{
	return new FCsWeaponPooled();
}

#define ConstructParamsType NCsPooledObject::NManager::FConstructParams
TMulticastDelegate<void(const FCsWeaponPooled*, const ConstructParamsType&)>& UCsManager_Weapon::GetOnConstructObject_Event(const FECsWeapon& Type)
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

void UCsManager_Weapon::ConstructClassHandler()
{
	typedef NCsWeapon::NManager::NHandler::FClass ClassHandlerType;

	ClassHandler = new ClassHandlerType();
	ClassHandler->Outer = this;
	ClassHandler->MyRoot = MyRoot;
	ClassHandler->Log = &NCsWeapon::FLog::Warning;
}


FCsWeapon* UCsManager_Weapon::GetWeapon(const FECsWeapon& Type)
{
	using namespace NCsManagerWeapon::NCached;

	const FString& Context = Str::GetWeapon;

	return ClassHandler->GetClassByType<EMCsWeapon, FECsWeapon>(Context, Type);
}

FCsWeapon* UCsManager_Weapon::GetWeaponChecked(const FString& Context, const FECsWeapon& Type)
{
	return ClassHandler->GetClassByTypeChecked<EMCsWeapon>(Context, Type);
}

FCsWeapon* UCsManager_Weapon::GetSafeWeapon(const FString& Context, const FECsWeapon& Type)
{
	return ClassHandler->GetSafeClassByType<EMCsWeapon>(Context, Type);
}

FCsWeapon* UCsManager_Weapon::GetWeapon(const FECsWeaponClass& Type)
{
	using namespace NCsManagerWeapon::NCached;

	const FString& Context = Str::GetWeapon;

	return ClassHandler->GetClassByClassType<EMCsWeaponClass>(Context, Type);
}

FCsWeapon* UCsManager_Weapon::GetWeaponChecked(const FString& Context, const FECsWeaponClass& Type)
{
	return ClassHandler->GetClassByClassTypeChecked<EMCsWeaponClass>(Context, Type);
}

FCsWeapon* UCsManager_Weapon::GetSafeWeapon(const FString& Context, const FECsWeaponClass& Type)
{
	return ClassHandler->GetSafeClassByClassType<EMCsWeaponClass>(Context, Type);
}

#pragma endregion Class

// Data
#pragma region

void UCsManager_Weapon::ConstructDataHandler()
{
	typedef NCsWeapon::NManager::NHandler::FData DataHandlerType;

	DataHandler = new DataHandlerType();
	DataHandler->Outer = this;
	DataHandler->MyRoot = MyRoot;
	DataHandler->Log = &NCsWeapon::FLog::Warning;
}

#define DataType NCsWeapon::NData::IData

DataType* UCsManager_Weapon::GetData(const FName& Name)
{
	using namespace NCsManagerWeapon::NCached;

	const FString& Context = Str::GetData;

	return DataHandler->GetData(Context, Name);
}

DataType* UCsManager_Weapon::GetDataChecked(const FString& Context, const FName& Name)
{
	return DataHandler->GetDataChecked(Context, Name);
}

DataType* UCsManager_Weapon::GetSafeData(const FString& Context, const FName& Name)
{
	return DataHandler->GetSafeData(Context, Name);
}

DataType* UCsManager_Weapon::GetData(const FECsWeapon& Type)
{
	using namespace NCsManagerWeapon::NCached;

	const FString& Context = Str::GetData;

	return DataHandler->GetData<EMCsWeapon, FECsWeapon>(Context, Type);
}

DataType* UCsManager_Weapon::GetDataChecked(const FString& Context, const FECsWeapon& Type)
{
	return DataHandler->GetDataChecked<EMCsWeapon, FECsWeapon>(Context, Type);
}

DataType* UCsManager_Weapon::GetSafeData(const FString& Context, const FECsWeapon& Type)
{
	return DataHandler->GetSafeData<EMCsWeapon, FECsWeapon>(Context, Type);
}

#undef DataType

void UCsManager_Weapon::OnPayloadUnloaded(const FName& Payload)
{
}

#pragma endregion Data