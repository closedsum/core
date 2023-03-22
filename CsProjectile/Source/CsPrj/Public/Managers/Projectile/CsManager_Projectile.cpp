// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Projectile/CsManager_Projectile.h"
#include "CsPrj.h"

// CVars
#include "Managers/Projectile/CsCVars_Manager_Projectile.h"
// Types
#include "Collision/CsTypes_Collision.h"
// Library
	// Data
#include "Data/CsLibrary_Data_Projectile.h"
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsPrjLibrary_DataRootSet.h"
	// Modifier
#include "Modifier/CsLibrary_ProjectileModifier.h"
	// Common
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Property.h"
#include "Level/CsLibrary_Level.h"
#include "Library/CsLibrary_Valid.h"
// Utility
#include "Utility/CsPrjLog.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
#include "Settings/CsProjectileSettings.h"
// Managers
#include "Managers/Data/CsManager_Data.h"
#include "Managers/Time/CsManager_Time.h"
// Data
#include "Data/CsPrjGetDataRootSet.h"
#include "Data/CsData_Projectile.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
#include "Settings/CsGetSettingsManagerProjectile.h"
// Projectile
#include "Managers/Projectile/Handler/CsManager_Projectile_ClassHandler.h"
#include "Managers/Projectile/Handler/CsManager_Projectile_DataHandler.h"
	// Payload
#include "Payload/CsPayload_ProjectileInterfaceMap.h"
#include "Payload/CsPayload_ProjectileImplSlice.h"
#include "Payload/Collision/CsPayload_Projectile_CollisionImplSlice.h"
#include "Payload/Modifier/CsPayload_Projectile_ModifierImplSlice.h"
#include "Payload/Modifier/Damage/CsPayload_Projectile_ModifierDamageImplSlice.h"
#include "Payload/Target/CsPayload_Projectile_TargetImplSlice.h"
#include "Payload/Damage/CsPayload_Projectile_DamageImplSlice.h"
	// Modifier
#include "Modifier/Types/CsGetProjectileModifierType.h"
#include "Modifier/Copy/CsProjectileModifier_Copy.h"
	// Event
#include "Event/CsProjectile_Event.h"
// Modifier
#include "Modifier/CsProjectileModifierImpl.h"

#if WITH_EDITOR
// Library
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"
	// Common
#include "Library/CsLibrary_World.h"
// Singleton
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Projectile/CsGetManagerProjectile.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerProjectile
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Projectile, SetupInternal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Projectile, InitInternalFromSettings);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Projectile, InitInternal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Projectile, AddPoolParams);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Projectile, GetProjectile);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Projectile, GetData);
		}

		namespace Name
		{
		}
	}
}

#pragma endregion Cached

// Internal
#pragma region

namespace NCsProjectile
{
	FManager::FManager()
		: Super()
	{
	}
}

#pragma endregion Internal

// static initializations
UCsManager_Projectile* UCsManager_Projectile::s_Instance;
bool UCsManager_Projectile::s_bShutdown = false;

UCsManager_Projectile::UCsManager_Projectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	// Singleton
	bInitialized(false),
	MyRoot(nullptr),
	// Settings
	Settings(),
	// Internal
	Internal(),
	// Update
	bTypesByUpdateGroup(false),
	TypesByUpdateGroup(),
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
	// Class
	ClassHandler(nullptr),
	// Data
	DataHandler(nullptr),
	// Modifier
	Manager_Modifiers(),
	ImplTypeByModifier()
{
}

// Singleton
#pragma region

#if WITH_EDITOR

/*static*/ UCsManager_Projectile* UCsManager_Projectile::Get(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerProjectile(InRoot)->GetManager_Projectile();
}

/*static*/ bool UCsManager_Projectile::IsValid(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerProjectile(InRoot)->GetManager_Projectile() != nullptr;
}

#endif // #if WITH_EDITOR

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

/*static*/ void UCsManager_Projectile::Shutdown(const UObject* InRoot /*=nullptr*/)
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

/*static*/ bool UCsManager_Projectile::HasShutdown(const UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerProjectile(InRoot)->GetManager_Projectile() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerProjectile* UCsManager_Projectile::Get_GetManagerProjectile(const UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Projectile::Get_GetManagerProjectile: InRoot is NULL."));

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Projectile::Get_GetManagerProjectile: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Projectile::Get_GetManagerProjectile: Manager_Singleton is NULL."));

	ICsGetManagerProjectile* GetManagerProjectile = Cast<ICsGetManagerProjectile>(Manager_Singleton);

	checkf(GetManagerProjectile, TEXT("UCsManager_Projectile::Get_GetManagerProjectile: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerProjectile."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerProjectile;
}

/*static*/ ICsGetManagerProjectile* UCsManager_Projectile::GetSafe_GetManagerProjectile(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
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
	return Cast<ICsGetManagerProjectile>(Manager_Singleton);
}

/*static*/ UCsManager_Projectile* UCsManager_Projectile::GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerProjectile* GetManagerProjectile = GetSafe_GetManagerProjectile(Context, InRoot, Log))
		return GetManagerProjectile->GetManager_Projectile();
	return nullptr;
}

#endif // #if WITH_EDITOR

void UCsManager_Projectile::Initialize()
{
	SetupInternal();
	SetupVariablesManager();
	SetupModifiers();
	SetupOnHit();

	bInitialized = true;
}

/*static*/ bool UCsManager_Projectile::HasInitialized(const UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_Projectile::CleanUp()
{
	Projectile_OnAllocate_Event.Clear();
	Projectile_OnDeallocate_Start_Event.Clear();
	Projectile_OnHit_Event.Clear();
	OnSpawn_Event.Clear();
	OnSpawn_ScriptEvent.Clear();
	OnDestroy_Event.Clear();

	Internal.Shutdown();

	for (NCsProjectile::NPayload::FInterfaceMap* Map : PayloadInterfaceMaps)
	{
		delete Map;
	}
	PayloadInterfaceMaps.Reset();

	Pool.Reset();

	typedef NCsProjectile::NModifier::FManager ModifierManagerType;
	typedef NCsProjectile::NModifier::FResource ModifierResourceType;
	typedef NCsProjectile::NModifier::IModifier ModifierType;

	for (ModifierManagerType& ModifierManager : Manager_Modifiers)
	{
		const TArray<ModifierResourceType*>& Containers = ModifierManager.GetPool();

		for (ModifierResourceType* Container : Containers)
		{
			ModifierType* M = Container->Get();
			delete M;
			Container->Set(nullptr);
		}
	}
	Manager_Modifiers.Reset();

	delete ClassHandler;
	ClassHandler = nullptr;

	delete DataHandler;
	DataHandler = nullptr;

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

// Settings
#pragma region

void UCsManager_Projectile::SetAndAddTypeMapKeyValue(const FECsProjectile& Key, const FECsProjectile& Value)
{
	check(EMCsProjectile::Get().IsValidEnum(Key));

	check(EMCsProjectile::Get().IsValidEnum(Value));

	for (int32 I = TypeMapArray.Num() - 1; I < Key.GetValue(); ++I)
	{
		TypeMapArray.AddDefaulted_GetRef() = EMCsProjectile::Get().GetEnumAt(I + 1);

		TypeMapToArray.AddDefaulted();
	}
	TypeMapArray[Key.GetValue()] = Value;

	TypeMapToArray[Value.GetValue()].Add(Key);
}

void UCsManager_Projectile::AddPoolParams(const FECsProjectile& Type, const FCsSettings_Manager_Projectile_PoolParams& InPoolParams)
{
	using namespace NCsManagerProjectile::NCached;

	const FString& Context = Str::AddPoolParams;

	check(EMCsProjectile::Get().IsValidEnumChecked(Context, Type));

	if (Settings.PoolParams.Find(Type))
	{
		UE_LOG(LogCsPrj, Warning, TEXT("%s: PoolParams ALREADY exist for %s."), *Context, Type.ToChar());
		return;
	}

	check(InPoolParams.IsValidChecked(Context));

	typedef NCsPooledObject::NManager::FPoolParams PoolParamsType;

	PoolParamsType PoolParams;

	// Get Class
	const FECsProjectileClass& ClassType	= InPoolParams.Class;
	FCsProjectilePooled* Projectile			= GetProjectileChecked(Context, ClassType);
	UClass* Class							= Projectile->GetClass();

	checkf(Class, TEXT("%s: Failed to get class for Type: %s ClassType: %s."), *Context, Type.ToChar(), ClassType.ToChar());

	PoolParams.Name								= TEXT("UCsManager_Projectile::NCsProjectile::FManager_") + Type.GetName();
	PoolParams.World							= MyRoot->GetWorld();
	PoolParams.ConstructParams.Outer			= this;
	PoolParams.ConstructParams.Class			= Class;
	PoolParams.ConstructParams.ConstructionType = NCsPooledObject::EConstruction::Actor;
	PoolParams.bConstructPayloads				= true;
	PoolParams.PayloadSize						= InPoolParams.PayloadSize;
	PoolParams.bCreatePool						= true;
	PoolParams.PoolSize							= InPoolParams.PoolSize;

	// Add CVars

	// Scoped Timer CVars
	PoolParams.ScopedGroup = NCsScopedGroup::ManagerProjectile;

	PoolParams.CreatePoolScopedTimerCVar = NCsCVarLog::LogManagerProjectileScopedTimerCreatePool;
	PoolParams.UpdateScopedTimerCVar = NCsCVarLog::LogManagerProjectileScopedTimerUpdate;
	PoolParams.UpdateObjectScopedTimerCVar = NCsCVarLog::LogManagerProjectileScopedTimerUpdateObject;
	PoolParams.AllocateScopedTimerCVar = NCsCVarLog::LogManagerProjectileScopedTimerAllocate;
	PoolParams.AllocateObjectScopedTimerCVar = NCsCVarLog::LogManagerProjectileScopedTimerAllocateObject;
	PoolParams.DeallocateScopedTimerCVar = NCsCVarLog::LogManagerProjectileScopedTimerDeallocate;
	PoolParams.DeallocateObjectScopedTimerCVar = NCsCVarLog::LogManagerProjectileScopedTimerDeallocateObject;
	PoolParams.SpawnScopedTimerCVar = NCsCVarLog::LogManagerProjectileScopedTimerSpawn;
	PoolParams.DestroyScopedTimerCVar = NCsCVarLog::LogManagerProjectileScopedTimerDestroy;

	Internal.Init(Type, PoolParams);

	// Bind to delegates
	//  This is mostly done to have a single place to bind to delegates for a Projectile related events (i.e. OnAllocate ... etc).
	const TArray<FCsProjectilePooled*>& PoolOfType = Internal.GetPool(Type);

	for (FCsProjectilePooled* ProjectilePooled : PoolOfType)
	{
		UObject* O				   = ProjectilePooled->GetObject();
		ICsProjectile_Event* Event = CS_INTERFACE_CAST_CHECKED(O, UObject, ICsProjectile_Event);

		Event->GetOnAllocate_Event().AddUObject(this, &UCsManager_Projectile::Projectile_OnAllocate);
		Event->GetOnDeallocate_Start_Event().AddUObject(this, &UCsManager_Projectile::Projectile_OnDeallocate_Start);
		Event->GetOnHit_Event().AddUObject(this, &UCsManager_Projectile::Projectile_OnHit);
	}
}

#pragma endregion Settings

// Internal
#pragma region

void UCsManager_Projectile::SetupInternal()
{
	using namespace NCsManagerProjectile::NCached;

	const FString& Context = Str::SetupInternal;

	// Populate EnumMaps
	UObject* ContextRoot = nullptr;

#if WITH_EDITOR
	typedef NCsWorld::FLibrary WorldLibrary;

	if (WorldLibrary::IsPlayInEditorOrEditorPreview(MyRoot))
	{
		// Do Nothing
	}
	else
#endif // #if WITH_EDITOR
	{
		typedef NCsGameInstance::FLibrary GameInstanceLibrary;

		ContextRoot = GameInstanceLibrary::GetSafeAsObject(Context, MyRoot);
	}

	NCsProjectile::PopulateEnumMapFromSettings(Context, ContextRoot);
	NCsProjectileClass::PopulateEnumMapFromSettings(Context, ContextRoot);

	// Class Handler
	ConstructClassHandler();

	checkf(ClassHandler, TEXT("%s: Failed to construct ClassHandler."), *Context);

	// Data Handler
	ConstructDataHandler();

	checkf(DataHandler, TEXT("%s: Failed to construct DataHandler."), *Context);

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

#if WITH_EDITOR
	typedef NCsWorld::FLibrary WorldLibrary;

	if (WorldLibrary::IsPlayInEditorOrEditorPreview(MyRoot))
	{
		Settings = FCsSettings_Manager_Projectile::GetEd();

		// Populate TypeMapArray
		{
			const int32& Count = EMCsProjectile::Get().Num();

			TypeMapArray.Reset(Count);
			TypeMapToArray.Reset(Count);

			for (const FECsProjectile& Type : EMCsProjectile::Get())
			{
				TypeMapArray.Add(Type);
				TypeMapToArray.AddDefaulted();
			}

			for (const TPair<FECsProjectile, FECsProjectile>& Pair : Settings.TypeMap)
			{
				const FECsProjectile& From = Pair.Key;
				const FECsProjectile& To = Pair.Value;

				TypeMapArray[From.GetValue()] = To;

				TypeMapToArray[To.GetValue()].Add(From);
				TypeToSet.Add(To);
			}
		}

		InitInternalFromSettings();

		/*
		ClassHandler->PopulateClassMapFromSettings(Context);
		DataHandler->PopulateDataMapFromSettings(Context);

		DataHandler->RemapDataMap(Context);
		*/

		// Editor or Editor Preview Instance should handle any additional setup.
	}
	else
#endif // #if WITH_EDITOR
	// If any settings have been set for Manager_Projectile, apply them
	{

		typedef NCsLevel::NPersistent::FLibrary LevelLibrary;

		ICsGetSettingsManagerProjectile* GetPoolParams = LevelLibrary::GetSetupDataChecked<ICsGetSettingsManagerProjectile>(Context, MyRoot);

		Settings = GetPoolParams->GetSettingsManagerProjectile();

		CS_IS_VALID_CHECKED(Settings);

		// Populate TypeMapArray
		{
			const int32& Count = EMCsProjectile::Get().Num();

			TypeMapArray.Reset(Count);
			TypeMapToArray.Reset(Count);

			for (const FECsProjectile& Type : EMCsProjectile::Get())
			{
				TypeMapArray.Add(Type);
				TypeMapToArray.AddDefaulted();
			}

			for (const TPair<FECsProjectile, FECsProjectile>& Pair : Settings.TypeMap)
			{
				const FECsProjectile& From = Pair.Key;
				const FECsProjectile& To   = Pair.Value;

				TypeMapArray[From.GetValue()] = To;

				TypeMapToArray[To.GetValue()].Add(From);
				TypeToSet.Add(To);
			}
		}

		// Populate TypesByUpdateGroup
		{
			TypesByUpdateGroup.Reset(EMCsUpdateGroup::Get().Num());
			TypesByUpdateGroup.AddDefaulted(EMCsUpdateGroup::Get().Num());

			for (TPair<FECsUpdateGroup, FCsSettings_Manager_Projectile_TypeArray>& Pair : Settings.TypesByUpdateGroupMap)
			{
				const FECsUpdateGroup& Group						  = Pair.Key;
				const FCsSettings_Manager_Projectile_TypeArray& Array = Pair.Value;

				checkf(Array.Types.Num() > CS_EMPTY, TEXT("%s: No Types added for UCsDeveloperSettings.Manager_Projectile.TypesByUpdateGroupMap[%s]."), *Context, Group.ToChar());

				TypesByUpdateGroup[Group.GetValue()].Append(Array.Types);

				bTypesByUpdateGroup = true;
			}
		}
		InitInternalFromSettings();
	}
}

void UCsManager_Projectile::InitInternalFromSettings()
{
	using namespace NCsManagerProjectile::NCached;

	const FString& Context = Str::InitInternalFromSettings;

	ClassHandler->PopulateClassMapFromSettings(Context);
	DataHandler->PopulateDataMapFromSettings(Context);

	if (Settings.PoolParams.Num() > CS_EMPTY)
	{
		typedef NCsProjectile::FManager::FParams ManagerParamsType;

		ManagerParamsType ManagerParams;

		ManagerParams.Name  = TEXT("UCsManager_Projectile::NCsProjectile::FManager");
		ManagerParams.World = MyRoot->GetWorld();

		for (const TPair<FECsProjectile, FCsSettings_Manager_Projectile_PoolParams>& Pair : Settings.PoolParams)
		{
			const FECsProjectile& Type								= Pair.Key;
			const FCsSettings_Manager_Projectile_PoolParams& Params = Pair.Value;

			typedef NCsPooledObject::NManager::FPoolParams PoolParamsType;

			PoolParamsType& PoolParams = ManagerParams.ObjectParams.Add(Type);

			// Get Class
			const FECsProjectileClass& ClassType = Params.Class;

			checkf(EMCsProjectileClass::Get().IsValidEnum(ClassType), TEXT("%s: Class for NOT Valid."), *Context, ClassType.ToChar());

			FCsProjectilePooled* Projectile = GetProjectileChecked(Context, ClassType);
			UClass* Class					= Projectile->GetClass();

			checkf(Class, TEXT("%s: Failed to get class for Type: %s ClassType: %s."), *Context, Type.ToChar(), ClassType.ToChar());

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

#define ManagerParamsType NCsProjectile::FManager::FParams
void UCsManager_Projectile::InitInternal(const ManagerParamsType& Params)
{
	using namespace NCsManagerProjectile::NCached;

	const FString& Context = Str::InitInternal;

	// Add CVars
	{
		ManagerParamsType& P = const_cast<ManagerParamsType&>(Params);

		typedef NCsPooledObject::NManager::FPoolParams PoolParamsType;

		for (TPair<FECsProjectile, PoolParamsType>& Pair : P.ObjectParams)
		{
			PoolParamsType& PoolParams = Pair.Value;

			// Scoped Timer CVars
			PoolParams.ScopedGroup = NCsScopedGroup::ManagerProjectile;

			PoolParams.CreatePoolScopedTimerCVar		= NCsCVarLog::LogManagerProjectileScopedTimerCreatePool;
			PoolParams.UpdateScopedTimerCVar			= NCsCVarLog::LogManagerProjectileScopedTimerUpdate;
			PoolParams.UpdateObjectScopedTimerCVar		= NCsCVarLog::LogManagerProjectileScopedTimerUpdateObject;
			PoolParams.AllocateScopedTimerCVar			= NCsCVarLog::LogManagerProjectileScopedTimerAllocate;
			PoolParams.AllocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerProjectileScopedTimerAllocateObject;
			PoolParams.DeallocateScopedTimerCVar		= NCsCVarLog::LogManagerProjectileScopedTimerDeallocate;
			PoolParams.DeallocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerProjectileScopedTimerDeallocateObject;
			PoolParams.SpawnScopedTimerCVar				= NCsCVarLog::LogManagerProjectileScopedTimerSpawn;
			PoolParams.DestroyScopedTimerCVar			= NCsCVarLog::LogManagerProjectileScopedTimerDestroy;
		}
	}
	Internal.Init(Params);

	// Bind to delegates
	//  This is mostly done to have a single place to bind to delegates for a Projectile related events (i.e. OnAllocate ... etc).
	TArray<FECsProjectile> Types;
	Internal.GetPoolTypes(Types);

	for (const FECsProjectile& Type : Types)
	{
		const TArray<FCsProjectilePooled*>& PoolOfType = Internal.GetPool(Type);

		for (FCsProjectilePooled* ProjectilePooled : PoolOfType)
		{
			UObject* O				   = ProjectilePooled->GetObject();
			ICsProjectile_Event* Event = CS_INTERFACE_CAST_CHECKED(O, UObject, ICsProjectile_Event);

			Event->GetOnAllocate_Event().AddUObject(this, &UCsManager_Projectile::Projectile_OnAllocate);
			Event->GetOnDeallocate_Start_Event().AddUObject(this, &UCsManager_Projectile::Projectile_OnDeallocate_Start);
			Event->GetOnHit_Event().AddUObject(this, &UCsManager_Projectile::Projectile_OnHit);
		}
	}
}
#undef ManagerParamsType

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

TDelegate<FCsProjectilePooled*(const FECsProjectile&)>& UCsManager_Projectile::GetConstructContainer_Impl()
{
	return Internal.ConstructContainer_Impl;
}

FCsProjectilePooled* UCsManager_Projectile::ConstructContainer(const FECsProjectile& Type)
{
	return new FCsProjectilePooled();
}

#define ConstructParamsType NCsPooledObject::NManager::FConstructParams
TMulticastDelegate<void(const FCsProjectilePooled*, const ConstructParamsType&)>& UCsManager_Projectile::GetOnConstructObject_Event(const FECsProjectile& Type)
{
#undef ConstructParamsType
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

bool UCsManager_Projectile::HasPool(const FECsProjectile& Type) const
{
	return Internal.HasPool(GetTypeFromTypeMap(Type));
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

	UpdateVariablesManager(DeltaTime);
}

void UCsManager_Projectile::Update(const FECsUpdateGroup& Group, const FCsDeltaTime& DeltaTime)
{
	checkf(TypesByUpdateGroup[Group.GetValue()].Num() > CS_EMPTY, TEXT("UCsManager_Projectile::Update: No Types associated with Group: %s."), Group.ToChar());

	for (const FECsProjectile& Type : TypesByUpdateGroup[Group.GetValue()])
	{
		Internal.Update(Type, DeltaTime);
	}
}

void UCsManager_Projectile::Update(const FECsProjectile& Type, const FCsDeltaTime& DeltaTime)
{
	Internal.Update(Type, DeltaTime);
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

	// Pause
#pragma region

void UCsManager_Projectile::Pause(const FECsUpdateGroup& Group, bool bPaused)
{
	if (bTypesByUpdateGroup)
	{
		checkf(TypesByUpdateGroup[Group.GetValue()].Num() > CS_EMPTY, TEXT("UCsManager_Projectile::Update: No Types associated with Group: %s."), Group.ToChar());

		for (const FECsProjectile& Type : TypesByUpdateGroup[Group.GetValue()])
		{
			Internal.Pause(Type, bPaused);
		}
	}
	else
	{
		Internal.Pause(bPaused);
	}
}

void UCsManager_Projectile::Pause(const FECsProjectile& Type, bool bPaused)
{
	Internal.Pause(Type, bPaused);
}

void UCsManager_Projectile::BindToOnPause(const FECsUpdateGroup& Group)
{
	FDelegateHandle Handle = UCsManager_Time::Get(GetOuter())->GetOnPause_Event(Group).AddUObject(this, &UCsManager_Projectile::Pause);

	OnPauseHandleByGroupMap.Add(Group, Handle);
}

#pragma endregion Pause

	// Allocate / Deallocate
#pragma region

void UCsManager_Projectile::QueueDeallocateAll()
{
	Internal.QueueDeallocateAll();
}

#pragma endregion Allocate / Deallocate

	// Payload
#pragma region

void UCsManager_Projectile::ConstructPayloads(const FECsProjectile& Type, const int32& Size)
{
	Internal.ConstructPayloads(GetTypeFromTypeMap(Type), Size);
}

#define PayloadType NCsProjectile::NPayload::IPayload

PayloadType* UCsManager_Projectile::ConstructPayload(const FECsProjectile& Type)
{
	// TODO: Perform a new in place for all structs.
	//		 Need to call dtor manually

	NCsProjectile::NPayload::FInterfaceMap* PayloadInterfaceMap = new NCsProjectile::NPayload::FInterfaceMap();

	PayloadInterfaceMaps.Add(PayloadInterfaceMap);

	FCsInterfaceMap* InterfaceMap = PayloadInterfaceMap->GetInterfaceMap();

	// Pooled (Base)
	typedef NCsPooledObject::NPayload::FImplSlice BaseSliceType;

	BaseSliceType* BaseSlice = new BaseSliceType();

	{
		BaseSlice->SetInterfaceMap(InterfaceMap);
		// Add to map
		PayloadInterfaceMap->AddDeconstruct(BaseSliceType::Name, &BaseSliceType::Deconstruct);
	}

	// Projectile (NCsProjectile::NPayload::FImplSice)
	{
		typedef NCsProjectile::NPayload::FImplSlice SliceType;

		SliceType* Slice = new SliceType();

		Slice->SetInterfaceMap(InterfaceMap);
		// Add slice as ICsReset to BaseSlice so this slice gets reset call.
		BaseSlice->AddReset(static_cast<ICsReset*>(Slice));
		// NOTE: Do NOT add to map. Internal will take care of deconstruction.
	}

	const FCsSettings_Manager_Projectile& ManagerSettings = FCsSettings_Manager_Projectile::Get();
	const TSet<FECsProjectilePayload> PayloadTypes		  = ManagerSettings.PayloadTypes;

	// Collision (NCsProjectile::NPayload::NCollision::FImplSlice)
	if (PayloadTypes.Contains(NCsProjectilePayload::ProjectileCollision))
	{
		typedef NCsProjectile::NPayload::NCollision::FImplSlice SliceType;

		SliceType* Slice = new SliceType();

		Slice->SetInterfaceMap(InterfaceMap);
		// Add slice as ICsReset to BaseSlice so this slice gets reset call.
		BaseSlice->AddReset(static_cast<ICsReset*>(Slice));
		// Add to map
		PayloadInterfaceMap->AddDeconstruct(SliceType::Name, &SliceType::Deconstruct);
	}
	// Modifier (NCsProjectile::NPayload::NModifier::FImplSlice)
	if (PayloadTypes.Contains(NCsProjectilePayload::ProjectileModifier))
	{
		typedef NCsProjectile::NPayload::NModifier::FImplSlice SliceType;

		SliceType* Slice = new SliceType();

		Slice->SetInterfaceMap(InterfaceMap);
		// Add slice as ICsReset to BaseSlice so this slice gets reset call.
		BaseSlice->AddReset(static_cast<ICsReset*>(Slice));
		// Add to map
		PayloadInterfaceMap->AddDeconstruct(SliceType::Name, &SliceType::Deconstruct);
	}
	// Damage Modifier (NCsProjectile::NPayload::NModifier::NDamage::FImplSlice)
	if (PayloadTypes.Contains(NCsProjectilePayload::ProjectileModifierDamage))
	{
		typedef NCsProjectile::NPayload::NModifier::NDamage::FImplSlice SliceType;

		SliceType* Slice = new SliceType();

		Slice->SetInterfaceMap(InterfaceMap);
		// Add slice as ICsReset to BaseSlice so this slice gets reset call.
		BaseSlice->AddReset(static_cast<ICsReset*>(Slice));
		// Add to map
		PayloadInterfaceMap->AddDeconstruct(SliceType::Name, &SliceType::Deconstruct);
	}
	// Target (NCsProjectile::NPayload::NTarget::FImplSlice)
	if (PayloadTypes.Contains(NCsProjectilePayload::ProjectileTarget))
	{
		typedef NCsProjectile::NPayload::NTarget::FImplSlice SliceType;

		SliceType* Slice = new SliceType();

		Slice->SetInterfaceMap(InterfaceMap);
		// Add slice as ICsReset to BaseSlice so this slice gets reset call.
		BaseSlice->AddReset(static_cast<ICsReset*>(Slice));
		// Add to map
		PayloadInterfaceMap->AddDeconstruct(SliceType::Name, &SliceType::Deconstruct);
	}
	// Damage (NCsProjectile::NPayload::NDamage::FImplSlice)
	if (PayloadTypes.Contains(NCsProjectilePayload::ProjectileDamage))
	{
		typedef NCsProjectile::NPayload::NDamage::FImplSlice SliceType;

		SliceType* Slice = new SliceType();

		Slice->SetInterfaceMap(InterfaceMap);
		// Add slice as ICsReset to BaseSlice so this slice gets reset call.
		BaseSlice->AddReset(static_cast<ICsReset*>(Slice));
		// Add to map
		PayloadInterfaceMap->AddDeconstruct(SliceType::Name, &SliceType::Deconstruct);
	}
	return InterfaceMap->Get<PayloadType>();
}

PayloadType* UCsManager_Projectile::AllocatePayload(const FECsProjectile& Type)
{
	return Internal.AllocatePayload(GetTypeFromTypeMap(Type));
}

#undef PayloadType

#pragma endregion Payload

	// Spawn
#pragma region

#define PayloadType NCsProjectile::NPayload::IPayload
const FCsProjectilePooled* UCsManager_Projectile::Spawn(const FECsProjectile& Type, PayloadType* Payload)
{
#undef PayloadType
	return Internal.Spawn(GetTypeFromTypeMap(Type), Payload);
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
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerProjectileTransactions))
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

void UCsManager_Projectile::ConstructClassHandler()
{
	typedef NCsProjectile::NManager::NHandler::FClass ClassHandlerType;

	ClassHandler = new ClassHandlerType();
	ClassHandler->Outer = this;
	ClassHandler->MyRoot = MyRoot;
}

FCsProjectilePooled* UCsManager_Projectile::GetProjectile(const FECsProjectile& Type)
{
	using namespace NCsManagerProjectile::NCached;

	const FString& Context = Str::GetProjectile;

	return ClassHandler->GetClassByType<EMCsProjectile, FECsProjectile>(Context, Type);
}

FCsProjectilePooled* UCsManager_Projectile::GetSafeProjectile(const FString& Context, const FECsProjectile& Type)
{
	return ClassHandler->GetSafeClassByType<EMCsProjectile, FECsProjectile>(Context, Type);
}

FCsProjectilePooled* UCsManager_Projectile::GetProjectile(const FECsProjectileClass& Type)
{
	using namespace NCsManagerProjectile::NCached;

	const FString& Context = Str::GetProjectile;

	return ClassHandler->GetClassByClassType<EMCsProjectileClass>(Context, Type);
}

FCsProjectilePooled* UCsManager_Projectile::GetProjectileChecked(const FString& Context, const FECsProjectileClass& Type)
{
	return ClassHandler->GetClassByClassTypeChecked<EMCsProjectileClass>(Context, Type);
}

FCsProjectilePooled* UCsManager_Projectile::GetSafeProjectile(const FString& Context, const FECsProjectileClass& Type)
{
	return ClassHandler->GetSafeClassByClassType<EMCsProjectileClass>(Context, Type);
}

#pragma endregion Class

// Data
#pragma region

void UCsManager_Projectile::ConstructDataHandler()
{
	typedef NCsProjectile::NManager::NHandler::FData DataHandlerType;

	DataHandler = new DataHandlerType();
	DataHandler->Outer = this;
	DataHandler->MyRoot = MyRoot;
}

#define DataType NCsProjectile::NData::IData

DataType* UCsManager_Projectile::GetData(const FName& Name)
{
	using namespace NCsManagerProjectile::NCached;

	const FString& Context = Str::GetData;

#if WITH_EDITOR
	DataType* Data = DataHandler->GetData(Context, Name);

	IsValid(Context, Data);
	return Data;
#else
	return DataHandler->GetData(Context, Name);
#endif // #if WITH_EDITOR
}

DataType* UCsManager_Projectile::GetDataChecked(const FString& Context, const FName& Name)
{
#if WITH_EDITOR
	DataType* Data = DataHandler->GetDataChecked(Context, Name);

	check(IsValidChecked(Context, Data));
	return Data;
#else
	return DataHandler->GetDataChecked(Context, Name);
#endif // #if WITH_EDITOR
}

DataType* UCsManager_Projectile::GetSafeData(const FString& Context, const FName& Name)
{
	DataType* Data = DataHandler->GetSafeData(Context, Name);

	if (!IsValid(Context, Data, nullptr))
		return nullptr;
	return Data;
}

DataType* UCsManager_Projectile::GetData(const FECsProjectile& Type)
{
	using namespace NCsManagerProjectile::NCached;

	const FString& Context = Str::GetData;

#if WITH_EDITOR
	DataType* Data = DataHandler->GetData<EMCsProjectile, FECsProjectile>(Context, Type);

	IsValid(Context, Data);
	return Data;
#else
	return DataHandler->GetData<EMCsProjectile, FECsProjectile>(Context, Type);
#endif // #if WITH_EDITOR
}

DataType* UCsManager_Projectile::GetDataChecked(const FString& Context, const FECsProjectile& Type)
{
#if WITH_EDITOR
	DataType* Data = DataHandler->GetDataChecked<EMCsProjectile, FECsProjectile>(Context, Type);

	check(IsValidChecked(Context, Data));
	return Data;
#else
	return DataHandler->GetDataChecked<EMCsProjectile, FECsProjectile>(Context, Type);
#endif // WITH_EDITOR
}

DataType* UCsManager_Projectile::GetSafeData(const FString& Context, const FECsProjectile& Type)
{
	DataType* Data = DataHandler->GetSafeData<EMCsProjectile, FECsProjectile>(Context, Type);

	if (!IsValid(Context, Data, nullptr))
		return nullptr;
	return Data;
}

#undef DataType

void UCsManager_Projectile::OnPayloadUnloaded(const FName& Payload)
{
}

#pragma endregion Data

// Valid
#pragma region

#define DataType NCsProjectile::NData::IData

bool UCsManager_Projectile::IsValidChecked(const FString& Context, const DataType* Data) const
{
	typedef NCsProjectile::NData::FLibrary DataLibrary;

	check(DataLibrary::IsValidChecked(Context, Data));	
	return true;
}

bool UCsManager_Projectile::IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
{
	typedef NCsProjectile::NData::FLibrary DataLibrary;

	if (!DataLibrary::IsValid(Context, Data, Log))
		return false;
	return true;
}

#undef DataType

#pragma endregion Valid

// Modifier
#pragma region

#define ModifierResourceType NCsProjectile::NModifier::FResource
#define ModifierType NCsProjectile::NModifier::IModifier

void UCsManager_Projectile::SetupModifiers()
{
	typedef NCsProjectile::NModifier::EImpl ModifierImplType;

	Manager_Modifiers.Reset((uint8)ModifierImplType::EImpl_MAX);
	Manager_Modifiers.AddDefaulted((uint8)ModifierImplType::EImpl_MAX);

	typedef NCsProjectile::NModifier::FManager ModifierManagerType;

	const FCsSettings_Manager_Projectile_Modifiers& ModifierSettings = FCsSettings_Manager_Projectile_Modifiers::Get();

	const int32& PoolSize = ModifierSettings.PoolSize;

	// Int
	{
		ModifierManagerType& ModifierManager = Manager_Modifiers[(uint8)ModifierImplType::Int];

		ModifierManager.CreatePool(PoolSize);

		for (int32 I = 0; I < PoolSize; ++I)
		{
			ModifierManager.Add(ConstructModifier(ModifierImplType::Int));
		}
	}
	// Float
	{
		ModifierManagerType& ModifierManager = Manager_Modifiers[(uint8)ModifierImplType::Float];

		ModifierManager.CreatePool(PoolSize);

		for (int32 I = 0; I < PoolSize; ++I)
		{
			ModifierManager.Add(ConstructModifier(ModifierImplType::Float));
		}
	}
	// Toggle
	{
		ModifierManagerType& ModifierManager = Manager_Modifiers[(uint8)ModifierImplType::Toggle];

		ModifierManager.CreatePool(PoolSize);

		for (int32 I = 0; I < PoolSize; ++I)
		{
			ModifierManager.Add(ConstructModifier(ModifierImplType::Toggle));
		}
	}

	ImplTypeByModifier.Reset(EMCsProjectileModifier::Get().Num());
	ImplTypeByModifier.AddDefaulted(EMCsProjectileModifier::Get().Num());

	ImplTypeByModifier[NCsProjectileModifier::LifeTime.GetValue()]		= ModifierImplType::Float;
	ImplTypeByModifier[NCsProjectileModifier::InitialSpeed.GetValue()]	= ModifierImplType::Float;
	ImplTypeByModifier[NCsProjectileModifier::MaxSpeed.GetValue()]		= ModifierImplType::Float;
	// Collision
	ImplTypeByModifier[NCsProjectileModifier::CollisionRadius.GetValue()]	= ModifierImplType::Float;
	ImplTypeByModifier[NCsProjectileModifier::HitCount.GetValue()]			= ModifierImplType::Int;
}

#define ModifierImplType NCsProjectile::NModifier::EImpl
ModifierType* UCsManager_Projectile::ConstructModifier(const ModifierImplType& ImplType)
{
	// Int
	if (ImplType == ModifierImplType::Int)
		return new NCsProjectile::NModifier::FInt();
	// Float
	if (ImplType == ModifierImplType::Float)
		return new NCsProjectile::NModifier::FFloat();
	// Toggle
	if (ImplType == ModifierImplType::Toggle)
		return new NCsProjectile::NModifier::FToggle();
	check(0);
	return nullptr;
}
#undef ModifierImplType

ModifierResourceType* UCsManager_Projectile::AllocateModifier(const FECsProjectileModifier& Type)
{
	checkf(EMCsProjectileModifier::Get().IsValidEnum(Type), TEXT("UCsManager_Projectile::AllocateModifier: Type: %s is NOT Valid."), Type.ToChar());

	return GetManagerModifier(Type).Allocate();
}

void UCsManager_Projectile::DeallocateModifier(const FString& Context, const FECsProjectileModifier& Type, ModifierResourceType* Modifier)
{
	checkf(EMCsProjectileModifier::Get().IsValidEnum(Type), TEXT("UCsManager_Projectile::DeallocateModifier: Type: %s is NOT Valid."), Type.ToChar());

	CS_IS_PTR_NULL_CHECKED(Modifier)

	typedef NCsProjectile::NModifier::FLibrary ModifierLibrary;

	// Reset
	ICsReset* IReset = ModifierLibrary::GetInterfaceChecked<ICsReset>(Context, Modifier->Get());
	
	IReset->Reset();

	GetManagerModifier(Type).Deallocate(Modifier);
}

const FECsProjectileModifier& UCsManager_Projectile::GetModifierType(const FString& Context, const ModifierType* Modifier)
{
	typedef NCsProjectile::NModifier::FLibrary ModifierLibrary;

	const ICsGetProjectileModifierType* GetProjectileModifierType = ModifierLibrary::GetInterfaceChecked<ICsGetProjectileModifierType>(Context, Modifier);
	const FECsProjectileModifier& PrjModifierType				  = GetProjectileModifierType->GetProjectileModifierType();

	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectileModifier, PrjModifierType);

	return PrjModifierType;
}

#undef ModifierResourceType
#undef ModifierType

#pragma endregion Modifier

// Variables
#pragma region

void UCsManager_Projectile::SetupVariablesManager()
{
	Manager_Variables.SetOuter(this);
	Manager_Variables.SetSize(Settings.Variables.PoolSize);
	Manager_Variables.LooseCoarseGrid.Create(5000.0f, 5000.0f, 1000.0f, 1000.0f, 0.0f, 0.0f, 100000.0f, 100000.0f);
}

void UCsManager_Projectile::UpdateVariablesManager(const FCsDeltaTime& DeltaTime)
{
	Manager_Variables.Update(DeltaTime);
}

#define VariablesType NCsProjectile::NVariables::FVariables
#define VariablesPayloadType NCsProjectile::NVariables::NAllocate::FPayload
VariablesType* UCsManager_Projectile::AllocateVariablesChecked(const FString& Context, const VariablesPayloadType& Payload)
{
#undef VariablesPayloadType
	return Manager_Variables.AllocateChecked(Context, Payload);
}

void UCsManager_Projectile::DeallocateVariablesChecked(const FString& Context, VariablesType* Variables)
{
	Manager_Variables.DeallocateChecked(Context, Variables);
}

#undef VariablesType

#pragma endregion Variables

// OnHit
#pragma region

void UCsManager_Projectile::FOnHit::FSpawn::FProjectile::FSpread::Setup()
{
	// TODO: Get from Settings
	VariablesManager.CreatePool(1024);
}

void UCsManager_Projectile::FOnHit::FSpawn::FProjectile::Setup()
{
	Spread.Setup();

	// TODO: Get from Settings
	VariablesManager.CreatePool(1024);
}

void UCsManager_Projectile::FOnHit::Setup()
{
	Spawn.Projectile.Setup();
}

void UCsManager_Projectile::SetupOnHit()
{
	OnHit.Outer = this;
	OnHit.Setup();
}

#pragma endregion OnHit