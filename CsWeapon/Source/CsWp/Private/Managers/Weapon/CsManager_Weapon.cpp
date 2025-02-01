// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Weapon/CsManager_Weapon.h"
#include "CsWp.h"

// CVars
#include "Managers/Weapon/CsCVars_Manager_Weapon.h"
// Library
#include "Modifier/CsLibrary_WeaponModifier.h"
	// Data
#include "Data/CsLibrary_Data_Weapon.h"
#include "Level/CsLibrary_LevelData.h"
	// Common
#include "Game/CsLibrary_GameInstance.h"
#include "Actor/CsLibrary_Actor.h"
#include "Library/CsLibrary_Valid.h"
// Utility
#include "Utility/CsWpLog.h"
// Settings
#include "Managers/Weapon/CsGetSettingsManagerWeapon.h"
// Interface
#include "ICsStartPlay.h"
// Data
#include "Data/CsWpGetDataRootSet.h"
#include "Data/CsData_WeaponInterfaceMap.h"
#include "Data/ICsData.h"
#include "Data/CsData_WeaponImplSlice.h"
#include "Projectile/Data/CsData_ProjectileWeaponImplSlice.h"
#include "Projectile/Data/Sound/Fire/CsData_ProjectileWeapon_SoundFireImplSlice.h"
// Weapon
#include "Managers/Weapon/Handler/CsManager_Weapon_ClassHandler.h"
#include "Managers/Weapon/Handler/CsManager_Weapon_DataHandler.h"
	// Payload
#include "Payload/CsPayload_WeaponImpl.h"
	// Modifier
#include "Modifier/Types/CsGetWeaponModifierType.h"
#include "Modifier/Copy/CsWeaponModifier_Copy.h"
	// Event
#include "Event/CsWeapon_Event.h"
#include "Point/Event/CsPointWeapon_Event.h"
#include "Point/Sequence/Event/CsPointSequenceWeapon_Event.h"
// Modifier
#include "Modifier/CsWeaponModifierImpl.h"
// Package
#include "UObject/Package.h"

#if WITH_EDITOR
// Library
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
	// Common
#include "Library/CsLibrary_World.h"
// Singleton
#include "Singleton/CsGetManagerSingleton.h"
#include "Singleton/CsManager_Singleton.h"
#include "Managers/Weapon/CsGetManagerWeapon.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsManager_Weapon)

// Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME(CsManager_Weapon)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsManager_Weapon, StartPlay)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsManager_Weapon, AddPoolParams)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsManager_Weapon, SetupInternal)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsManager_Weapon, InitInternalFromSettings)

	CS_DEFINE_CACHED_FUNCTION_NAME(UCsManager_Weapon, GetWeapon)

	CS_DEFINE_CACHED_FUNCTION_NAME(UCsManager_Weapon, GetData)
CS_END_CACHED_FUNCTION_NAME

namespace NCsManagerWeapon
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_STRING(Class, "Class");
		}
	}
}

#pragma endregion Cached

// Internal
#pragma region

namespace NCsWeapon
{
	namespace NInternal
	{
		FManager::FManager()
		: Super()
	{
	}
	}
}

#pragma endregion Internal

// static initializations
UCsManager_Weapon* UCsManager_Weapon::s_Instance;
bool UCsManager_Weapon::s_bShutdown = false;

UCsManager_Weapon::UCsManager_Weapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	// Modifier
	Manager_Modifiers(),
	ImplTypeByModifier()
{
}

using ManagerParamsType = NCsWeapon::NInternal::FManager::FParams;
using ConstructParamsType = NCsPooledObject::NManager::FConstructParams;
using PoolParamsType = NCsPooledObject::NManager::FPoolParams;
using DataLibrary = NCsWeapon::NData::NLibrary::FLibrary;
using DataType = NCsWeapon::NData::IData;
using PayloadType = NCsWeapon::NPayload::IPayload;
using PayloadImplType = NCsWeapon::NPayload::FImpl;
using ModifierManagerType = NCsWeapon::NModifier::NResource::FManager;
using ModifierResourceType = NCsWeapon::NModifier::NResource::FResource;
using ModifierType = NCsWeapon::NModifier::IModifier;
using ModifierImplType = NCsWeapon::NModifier::EImpl;
using CopyType = NCsWeapon::NModifier::NCopy::ICopy;

// Singleton
#pragma region

#if WITH_EDITOR

/*static*/ UCsManager_Weapon* UCsManager_Weapon::Get(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerWeapon(InRoot)->GetManager_Weapon();
}

/*static*/ UCsManager_Weapon* UCsManager_Weapon::GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerWeapon* GetManagerWeapon = GetSafe_GetManagerWeapon(Context, InRoot, Log))
		return GetManagerWeapon->GetManager_Weapon();
	return nullptr;
}

/*static*/ bool UCsManager_Weapon::IsValid(const UObject* InRoot /*=nullptr*/)
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

/*static*/ void UCsManager_Weapon::Shutdown(const UObject* InRoot /*=nullptr*/)
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

/*static*/ bool UCsManager_Weapon::HasShutdown(const UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerWeapon(InRoot)->GetManager_Weapon() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerWeapon* UCsManager_Weapon::Get_GetManagerWeapon(const UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Weapon::Get_GetManagerWeapon: InRoot is NULL."));

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Weapon::Get_GetManagerWeapon: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Weapon::Get_GetManagerWeapon: Manager_Singleton is NULL."));

	ICsGetManagerWeapon* GetManagerWeapon = Cast<ICsGetManagerWeapon>(Manager_Singleton);

	checkf(GetManagerWeapon, TEXT("UCsManager_Weapon::Get_GetManagerWeapon: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerWeapon."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerWeapon;
}

/*static*/ ICsGetManagerWeapon* UCsManager_Weapon::GetSafe_GetManagerWeapon(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
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
	return Cast<ICsGetManagerWeapon>(Manager_Singleton);
}

#endif // #if WITH_EDITOR

void UCsManager_Weapon::Initialize()
{
	SetupInternal();
	SetupModifiers();
	SetupSpreadVariables();
	
	bInitialized = true;
}

/*static*/ bool UCsManager_Weapon::HasInitialized(const UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_Weapon::CleanUp()
{
	Internal.Shutdown();
	Pool.Reset();

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

void UCsManager_Weapon::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// StartPlay
#pragma region

void UCsManager_Weapon::StartPlay()
{
	CS_SET_CONTEXT_AS_FUNCTION_NAME(StartPlay);

	checkf(!bStartedPlay, TEXT("%s: StartPlay has ALREADY been called."), *Context);

	for (AActor* Actor : WeaponsQueuedForStartPlay)
	{
		CS_IS_PENDING_KILL_CHECKED(Actor)

		ICsStartPlay* Interface = CS_INTERFACE_CAST_CHECKED(Actor, AActor, ICsStartPlay);

		checkf(!Interface->HasStartedPlay(), TEXT("%s: Actor: %s with Class: %s has ALREADY called StartPlay."), *Context, *(Actor->GetName()), *(Actor->GetClass()->GetName()));

		Interface->StartPlay();
	}

	ReceiveStartPlay();

	bStartedPlay = true;
}

#pragma endregion StartPlay

// Settings
#pragma region

void UCsManager_Weapon::SetAndAddTypeMapKeyValue(const FECsWeapon& Key, const FECsWeapon& Value)
{
	check(EMCsWeapon::Get().IsValidEnum(Key));
	check(EMCsWeapon::Get().IsValidEnum(Value));

	for (int32 I = TypeMapArray.Num() - 1; I < Key.GetValue(); ++I)
	{
		TypeMapArray.AddDefaulted_GetRef() = EMCsWeapon::Get().GetEnumAt(I + 1);

		TypeMapToArray.AddDefaulted();
	}
	TypeMapArray[Key.GetValue()] = Value;
	
	TypeMapToArray[Value.GetValue()].Add(Key);
	TypeToSet.Add(Value);
}

void UCsManager_Weapon::AddPoolParams(const FECsWeapon& Type, const FCsSettings_Manager_Weapon_PoolParams& InPoolParams)
{
	CS_SET_CONTEXT_AS_FUNCTION_NAME(AddPoolParams);

	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeapon, Type)

	if (Settings.PoolParams.Find(Type))
	{
		UE_LOG(LogCsWp, Warning, TEXT("%s: PoolParams ALREADY exist for %s."), *Context, Type.ToChar());
		return;
	}

	CS_IS_VALID_CHECKED(InPoolParams);

	PoolParamsType PoolParams;

	// Get Class
	const FECsWeaponClass& ClassType = InPoolParams.Class;
	FCsWeaponClass* Weapon			 = GetWeaponChecked(Context, ClassType);
	UClass* Class					 = Weapon->GetClass();

	checkf(Class, TEXT("%s: Failed to get class for Type: %s ClassType: %s."), *Context, Type.ToChar(), ClassType.ToChar());

	PoolParams.Name								= TEXT("UCManager_Weapon::NCsWeapon::NInternal::FManager_") + Type.GetName();
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
	PoolParams.ScopedGroup = NCsScopedGroup::ManagerWeapon;

	PoolParams.CreatePoolScopedTimerCVar = NCsCVarLog::LogManagerWeaponScopedTimerCreatePool;
	PoolParams.UpdateScopedTimerCVar = NCsCVarLog::LogManagerWeaponScopedTimerUpdate;
	PoolParams.UpdateObjectScopedTimerCVar = NCsCVarLog::LogManagerWeaponScopedTimerUpdateObject;
	PoolParams.AllocateScopedTimerCVar = NCsCVarLog::LogManagerWeaponScopedTimerAllocate;
	PoolParams.AllocateObjectScopedTimerCVar = NCsCVarLog::LogManagerWeaponScopedTimerAllocateObject;
	PoolParams.DeallocateScopedTimerCVar = NCsCVarLog::LogManagerWeaponScopedTimerDeallocate;
	PoolParams.DeallocateObjectScopedTimerCVar = NCsCVarLog::LogManagerWeaponScopedTimerDeallocateObject;
	PoolParams.SpawnScopedTimerCVar = NCsCVarLog::LogManagerWeaponScopedTimerSpawn;
	PoolParams.DestroyScopedTimerCVar = NCsCVarLog::LogManagerWeaponScopedTimerDestroy;

	Internal.Init(Type, PoolParams);

	// Bind to delegates
	//  This is mostly done to have a single place to bind to delegates for a Weapon related events (i.e. OnAllocate ... etc).
	const TArray<FCsWeaponPooled*>& PoolOfType = Internal.GetPool(Type);

	for (FCsWeaponPooled* WeaponPooled : PoolOfType)
	{
		UObject* O = WeaponPooled->GetObject();

		if (ICsWeapon_Event* Event = Cast<ICsWeapon_Event>(O))
		{
			Event->GetOnAllocate_Event().AddUObject(this, &UCsManager_Weapon::Weapon_OnAllocate);
			Event->GetOnDeallocate_Start_Event().AddUObject(this, &UCsManager_Weapon::Weapon_OnDeallocate_Start);
		}
		// Point
		if (ICsPointWeapon_Event* Event = Cast<ICsPointWeapon_Event>(O))
		{
			Event->GetOnHit_Event().AddUObject(this, &UCsManager_Weapon::PointWeapon_OnHit);
		}
		// Point Sequence
		if (ICsPointSequenceWeapon_Event* Event = Cast<ICsPointSequenceWeapon_Event>(O))
		{
			Event->GetOnHit_Event().AddUObject(this, &UCsManager_Weapon::PointSequenceWeapon_OnHit);
		}
	}
}

#pragma endregion Settings

// Internal
#pragma region

void UCsManager_Weapon::SetupInternal()
{
	CS_SET_CONTEXT_AS_FUNCTION_NAME(SetupInternal);

	// Populate EnumMaps
	UObject* ContextRoot = nullptr;

#if WITH_EDITOR
	if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(MyRoot))
	{
		// Do Nothing
	}
	else
#endif // #if WITH_EDITOR
	{
		ContextRoot = CsGameInstanceLibrary::GetSafeAsObject(Context, MyRoot);
	}

	NCsWeapon::PopulateEnumMapFromSettings(Context, ContextRoot);
	NCsWeaponClass::PopulateEnumMapFromSettings(Context, ContextRoot);
	NCsWeaponState::PopulateEnumMapFromSettings(Context, ContextRoot);

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


#if WITH_EDITOR
	if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(MyRoot))
	{
		Settings = FCsSettings_Manager_Weapon::GetEd();

		// Populate TypeMapArray
		{
			const int32& Count = EMCsWeapon::Get().Num();

			TypeMapArray.Reset(Count);
			TypeMapToArray.Reset(Count);

			for (const FECsWeapon& Type : EMCsWeapon::Get())
			{
				TypeMapArray.Add(Type);
				TypeMapToArray.AddDefaulted();
			}

			for (const TPair<FECsWeapon, FECsWeapon>& Pair : Settings.TypeMap)
			{
				const FECsWeapon& From = Pair.Key;
				const FECsWeapon& To = Pair.Value;

				TypeMapArray[From.GetValue()] = To;

				TypeMapToArray[To.GetValue()].Add(From);
			}
		}

		// Get any Weapon placed in the Level
		//  TODO:
		//TArray<AActor*> WeaponsPlacedInLevel;
		//CsActorLibrary::GetSafeAllByInterface(Context, MyRoot, UCsWeapon::StaticClass(), WeaponsPlacedInLevel, nullptr);

		InitInternalFromSettings();

		/*
		ClassHandler->PopulateClassMapFromSettings(Context);
		DataHandler->PopulateDataMapFromSettings(Context);

		DataHandler->RemapDataMap(Context);
		*/
		
		// Add the Weapons to the Pool
		//  TODO: NOTE: FUTURE: Placed Actors should be replaced by the pooled version?
		/*
		for (AActor* A : WeaponsPlacedInLevel)
		{
			// Only add Weapons that implement are "Pooled" (i.e. implement the interface: ICsPooledObject)
			if (!Cast<ICsPooledObject>(A))
				continue;

			ICsWeapon* Interface = CS_INTERFACE_CAST_CHECKED(A, AActor, ICsWeapon);

			AddToAllocatedObjects(Interface->GetCharacterType(), Interface, A);
			
			WeaponsQueuedForStartPlay.Add(A);
		}
		*/

		// Editor or Editor Preview Instance should handle any additional setup.
	}
	else
#endif // #if WITH_EDITOR
	// If any settings have been set for Manager_Weapon, apply them
	{
		// Get Settings for the Level Setup Data  (via Level Script Actor / Level Blueprint implementing the interface: ICsGetLevelSetupData)
		//  NOTE: For now, do NOT Log
		if (ICsGetSettingsManagerWeapon* GetSettingsManagerWeapon = CsLevelDataLibrary::GetSafeSetupData<ICsGetSettingsManagerWeapon>(Context, MyRoot, nullptr))
		{
			Settings = GetSettingsManagerWeapon->GetSettingsManagerWeapon();

			CS_IS_VALID_CHECKED(Settings);

			// Populate TypeMapArray
			{
				const int32& Count = EMCsWeapon::Get().Num();

				TypeMapArray.Reset(Count);
				TypeMapToArray.Reset(Count);

				for (const FECsWeapon& Type : EMCsWeapon::Get())
				{
					TypeMapArray.Add(Type);
					TypeMapToArray.AddDefaulted();
				}

				for (const TPair<FECsWeapon, FECsWeapon>& Pair : Settings.TypeMap)
				{
					const FECsWeapon& From = Pair.Key;
					const FECsWeapon& To   = Pair.Value;

					TypeMapArray[From.GetValue()] = To;

					TypeMapToArray[To.GetValue()].Add(From);
				}
			}
		}
		// TODO: Get Settings for UCsWeaponSettings
		else
		{

		}

		InitInternalFromSettings();
	}
}

void UCsManager_Weapon::InitInternalFromSettings()
{
	CS_SET_CONTEXT_AS_FUNCTION_NAME(InitInternalFromSettings);

	ClassHandler->PopulateClassMapFromSettings(Context);
	DataHandler->PopulateDataMapFromSettings(Context);

	// Setup Pool
	if (Settings.PoolParams.Num() > CS_EMPTY)
	{
		ManagerParamsType ManagerParams;

		ManagerParams.Name  = TEXT("UCsManager_Weapon::NCsWeapon::NInternal::FManager");
		ManagerParams.World = MyRoot->GetWorld();

		//  Pool params for each specified Weapon Type
		for (const TPair<FECsWeapon, FCsSettings_Manager_Weapon_PoolParams>& Pair : Settings.PoolParams)
		{
			const FECsWeapon& Type								= Pair.Key;
			const FCsSettings_Manager_Weapon_PoolParams& Params = Pair.Value;

			PoolParamsType& PoolParams = ManagerParams.ObjectParams.Add(Type);

			// Get Class
			const FECsWeaponClass& ClassType = Params.Class;

			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponClass, ClassType);

			FCsWeaponClass* Weapon = GetWeaponChecked(Context, ClassType);
			UClass* Class		   = Weapon->GetClass();

			checkf(Class, TEXT("%s: Failed to get class for Type: %s ClassType: %s."), *Context, Type.ToChar(), ClassType.ToChar());

			PoolParams.Name								= ManagerParams.Name + TEXT("_") + Type.ToChar();
			PoolParams.World							= ManagerParams.World;
			//PoolParams.LogType
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

void UCsManager_Weapon::InitInternal(const ManagerParamsType& Params)
{
	// Add CVars
	{
		ManagerParamsType& P = const_cast<ManagerParamsType&>(Params);

		for (TPair<FECsWeapon, PoolParamsType>& Pair : P.ObjectParams)
		{
			PoolParamsType& PoolParams = Pair.Value;

			// Scoped Timer CVars
			PoolParams.ScopedGroup = NCsScopedGroup::ManagerWeapon;

			PoolParams.CreatePoolScopedTimerCVar		= NCsCVarLog::LogManagerWeaponScopedTimerCreatePool;
			PoolParams.UpdateScopedTimerCVar			= NCsCVarLog::LogManagerWeaponScopedTimerUpdate;
			PoolParams.UpdateObjectScopedTimerCVar		= NCsCVarLog::LogManagerWeaponScopedTimerUpdateObject;
			PoolParams.AllocateScopedTimerCVar			= NCsCVarLog::LogManagerWeaponScopedTimerAllocate;
			PoolParams.AllocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerWeaponScopedTimerAllocateObject;
			PoolParams.DeallocateScopedTimerCVar		= NCsCVarLog::LogManagerWeaponScopedTimerDeallocate;
			PoolParams.DeallocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerWeaponScopedTimerDeallocateObject;
			PoolParams.SpawnScopedTimerCVar				= NCsCVarLog::LogManagerWeaponScopedTimerSpawn;
			PoolParams.DestroyScopedTimerCVar			= NCsCVarLog::LogManagerWeaponScopedTimerDestroy;
		}
	}
	Internal.Init(Params);

	// Bind to delegates
	//  This is mostly done to have a single place to bind to delegates for a Weapon related events (i.e. OnAllocate ... etc).
	TArray<FECsWeapon> Types;
	Internal.GetPoolTypes(Types);

	for (const FECsWeapon& Type : Types)
	{
		const TArray<FCsWeaponPooled*>& PoolOfType = Internal.GetPool(Type);

		for (FCsWeaponPooled* WeaponPooled : PoolOfType)
		{
			UObject* O = WeaponPooled->GetObject();
			
			if (ICsWeapon_Event* Event = Cast<ICsWeapon_Event>(O))
			{
				Event->GetOnAllocate_Event().AddUObject(this, &UCsManager_Weapon::Weapon_OnAllocate);
				Event->GetOnDeallocate_Start_Event().AddUObject(this, &UCsManager_Weapon::Weapon_OnDeallocate_Start);
			}
			// Point
			if (ICsPointWeapon_Event* Event = Cast<ICsPointWeapon_Event>(O))
			{
				Event->GetOnHit_Event().AddUObject(this, &UCsManager_Weapon::PointWeapon_OnHit);
			}
			// Point Sequence
			if (ICsPointSequenceWeapon_Event* Event = Cast<ICsPointSequenceWeapon_Event>(O))
			{
				Event->GetOnHit_Event().AddUObject(this, &UCsManager_Weapon::PointSequenceWeapon_OnHit);
			}
		}
	}
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

TMulticastDelegate<void(const FCsWeaponPooled*, const ConstructParamsType&)>& UCsManager_Weapon::GetOnConstructObject_Event(const FECsWeapon& Type)
{
	return Internal.GetOnConstructObject_Event(Type);
}

		// Add
#pragma region

			// Pool
#pragma region

const FCsWeaponPooled* UCsManager_Weapon::AddToPool(const FECsWeapon& Type, ICsWeapon* Object)
{
	return Internal.AddToPool(GetTypeFromTypeMap(Type), Object);
}

const FCsWeaponPooled* UCsManager_Weapon::AddToPool(const FECsWeapon& Type, const FCsWeaponPooled* Object)
{
	return Internal.AddToPool(GetTypeFromTypeMap(Type), Object->GetObject());
}

const FCsWeaponPooled* UCsManager_Weapon::AddToPool(const FECsWeapon& Type, UObject* Object)
{
	return Internal.AddToPool(GetTypeFromTypeMap(Type), Object);
}

#pragma endregion Pool

			// Allocated Objects
#pragma region

const FCsWeaponPooled* UCsManager_Weapon::AddToAllocatedObjects(const FECsWeapon& Type, ICsWeapon* Projectile, UObject* Object)
{
	return Internal.AddToAllocatedObjects(GetTypeFromTypeMap(Type), Projectile, Object);
}

const FCsWeaponPooled* UCsManager_Weapon::AddToAllocatedObjects(const FECsWeapon& Type, ICsWeapon* Object)
{
	return Internal.AddToAllocatedObjects(GetTypeFromTypeMap(Type), Object);
}

const FCsWeaponPooled* UCsManager_Weapon::AddToAllocatedObjects(const FECsWeapon& Type, UObject* Object)
{
	return Internal.AddToAllocatedObjects(GetTypeFromTypeMap(Type), Object);
}

#pragma endregion Allocated Objects

#pragma endregion Add

const TArray<FCsWeaponPooled*>& UCsManager_Weapon::GetPool(const FECsWeapon& Type)
{
	return Internal.GetPool(GetTypeFromTypeMap(Type));
}

const TArray<FCsWeaponPooled*>& UCsManager_Weapon::GetAllocatedObjects(const FECsWeapon& Type)
{
	return Internal.GetAllocatedObjects(GetTypeFromTypeMap(Type));
}

const int32& UCsManager_Weapon::GetPoolSize(const FECsWeapon& Type)
{
	return Internal.GetPoolSize(GetTypeFromTypeMap(Type));
}

int32 UCsManager_Weapon::GetAllocatedObjectsSize(const FECsWeapon& Type)
{
	return Internal.GetAllocatedObjectsSize(GetTypeFromTypeMap(Type));
}

bool UCsManager_Weapon::IsExhausted(const FECsWeapon& Type)
{
	return Internal.IsExhausted(GetTypeFromTypeMap(Type));
}

	// Find
#pragma region

const FCsWeaponPooled* UCsManager_Weapon::FindObject(const FECsWeapon& Type, const int32& Index)
{
	return Internal.FindObject(GetTypeFromTypeMap(Type), Index);
}

const FCsWeaponPooled* UCsManager_Weapon::FindObject(const FECsWeapon& Type, ICsWeapon* Object)
{
	return Internal.FindObject(GetTypeFromTypeMap(Type), Object);
}

const FCsWeaponPooled* UCsManager_Weapon::FindObject(const FECsWeapon& Type, UObject* Object)
{
	return Internal.FindObject(GetTypeFromTypeMap(Type), Object);
}

const FCsWeaponPooled* UCsManager_Weapon::FindSafeObject(const FECsWeapon& Type, const int32& Index)
{
	return Internal.FindSafeObject(GetTypeFromTypeMap(Type), Index);
}

const FCsWeaponPooled* UCsManager_Weapon::FindSafeObject(const FECsWeapon& Type, ICsWeapon* Object)
{
	return Internal.FindSafeObject(GetTypeFromTypeMap(Type), Object);
}

const FCsWeaponPooled* UCsManager_Weapon::FindSafeObject(const FECsWeapon& Type, UObject* Object)
{
	return Internal.FindSafeObject(GetTypeFromTypeMap(Type), Object);
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
	Internal.ConstructPayloads(GetTypeFromTypeMap(Type), Size);
}

PayloadType* UCsManager_Weapon::ConstructPayload(const FECsWeapon& Type)
{
	return new PayloadImplType();
}

PayloadType* UCsManager_Weapon::AllocatePayload(const FECsWeapon& Type)
{
	return Internal.AllocatePayload(GetTypeFromTypeMap(Type));
}

#pragma endregion Payload

	// Spawn
#pragma region

const FCsWeaponPooled* UCsManager_Weapon::Spawn(const FECsWeapon& Type, PayloadType* Payload)
{
	return Internal.Spawn(GetTypeFromTypeMap(Type), Payload);
}

#pragma endregion Spawn

	// Destroy
#pragma region

bool UCsManager_Weapon::Destroy(const FECsWeapon& Type, ICsWeapon* Weapon)
{
	return Internal.Destroy(GetTypeFromTypeMap(Type), Weapon);
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
	using ClassHandlerImplType = NCsWeapon::NManager::NHandler::NClass::FClass;

	ClassHandler = new ClassHandlerImplType();
	ClassHandler->Outer = this;
	ClassHandler->MyRoot = MyRoot;
}

FCsWeaponClass* UCsManager_Weapon::GetWeapon(const FECsWeapon& Type)
{
	CS_SET_CONTEXT_AS_FUNCTION_NAME(GetWeapon);

	return ClassHandler->GetClassByType<EMCsWeapon, FECsWeapon>(Context, Type);
}

FCsWeaponClass* UCsManager_Weapon::GetWeaponChecked(const FString& Context, const FECsWeapon& Type)
{
	return ClassHandler->GetClassByTypeChecked<EMCsWeapon>(Context, Type);
}

FCsWeaponClass* UCsManager_Weapon::GetSafeWeapon(const FString& Context, const FECsWeapon& Type)
{
	return ClassHandler->GetSafeClassByType<EMCsWeapon>(Context, Type);
}

FCsWeaponClass* UCsManager_Weapon::GetWeapon(const FECsWeaponClass& Type)
{
	CS_SET_CONTEXT_AS_FUNCTION_NAME(GetWeapon);

	return ClassHandler->GetClassByClassType<EMCsWeaponClass>(Context, Type);
}

FCsWeaponClass* UCsManager_Weapon::GetWeaponChecked(const FString& Context, const FECsWeaponClass& Type)
{
	return ClassHandler->GetClassByClassTypeChecked<EMCsWeaponClass>(Context, Type);
}

FCsWeaponClass* UCsManager_Weapon::GetSafeWeapon(const FString& Context, const FECsWeaponClass& Type)
{
	return ClassHandler->GetSafeClassByClassType<EMCsWeaponClass>(Context, Type);
}

bool UCsManager_Weapon::SafeAddClass(const FString& Context, const FECsWeapon& Type, UObject* Class)
{
	return ClassHandler->SafeAddClassByType<EMCsWeapon, FECsWeapon>(Context, Type, Class);
}

bool UCsManager_Weapon::SafeAddClass(const FString& Context, const FECsWeaponClass& Type, UObject* Class)
{
	return ClassHandler->SafeAddClassByClassType<EMCsWeaponClass>(Context, Type, Class);
}

#pragma endregion Class

// Data
#pragma region

void UCsManager_Weapon::ConstructDataHandler()
{
	using DataHandlerImplType = NCsWeapon::NManager::NHandler::NData::FData;

	DataHandler = new DataHandlerImplType();
	DataHandler->Outer = this;
	DataHandler->MyRoot = MyRoot;
}

DataType* UCsManager_Weapon::GetData(const FName& Name)
{
	CS_SET_CONTEXT_AS_FUNCTION_NAME(GetData);

#if WITH_EDITOR
	DataType* Data = DataHandler->GetData(Context, Name);

	IsValid(Context, Data);
	return Data;
#else
	return DataHandler->GetData(Context, Name);
#endif // #if WITH_EDITOR
}

DataType* UCsManager_Weapon::GetDataChecked(const FString& Context, const FName& Name)
{
#if WITH_EDITOR
	DataType* Data = DataHandler->GetDataChecked(Context, Name);

	check(IsValidChecked(Context, Data));
	return Data;
#else
	return DataHandler->GetDataChecked(Context, Name);
#endif // #if WITH_EDITOR
}

DataType* UCsManager_Weapon::GetSafeData(const FString& Context, const FName& Name)
{
#if WITH_EDITOR
	DataType* Data = DataHandler->GetSafeData(Context, Name);

	if (IsValid(Context, Data, nullptr))
		return Data;
	return nullptr;
#else
	return DataHandler->GetSafeData(Context, Name);
#endif // #if WITH_EDITOR
}

DataType* UCsManager_Weapon::GetData(const FECsWeapon& Type)
{
	CS_SET_CONTEXT_AS_FUNCTION_NAME(GetData);

#if WITH_EDITOR
	DataType* Data = DataHandler->GetData<EMCsWeapon, FECsWeapon>(Context, Type);

	IsValid(Context, Data);
	return Data;
#else
	return DataHandler->GetData<EMCsWeapon, FECsWeapon>(Context, Type);
#endif // #if WITH_EDITOR
}

DataType* UCsManager_Weapon::GetDataChecked(const FString& Context, const FECsWeapon& Type)
{
#if WITH_EDITOR
	DataType* Data = DataHandler->GetDataChecked<EMCsWeapon, FECsWeapon>(Context, Type);

	check(IsValidChecked(Context, Data));
	return Data;
#else
	return DataHandler->GetDataChecked<EMCsWeapon, FECsWeapon>(Context, Type);
#endif // #if WITH_EDITOR
}

DataType* UCsManager_Weapon::GetSafeData(const FString& Context, const FECsWeapon& Type)
{
#if WITH_EDITOR
	DataType* Data = DataHandler->GetSafeData<EMCsWeapon, FECsWeapon>(Context, Type);

	if (IsValid(Context, Data, nullptr))
		return Data;
	return nullptr;
#else
	return DataHandler->GetSafeData<EMCsWeapon, FECsWeapon>(Context, Type);
#endif // #if WITH_EDITOR
}

void UCsManager_Weapon::OnPayloadUnloaded(const FName& Payload)
{
}

#pragma endregion Data

// Valid
#pragma region

bool UCsManager_Weapon::IsValidChecked(const FString& Context, const DataType* Data) const
{
	check(DataLibrary::IsValidChecked(Context, Data));	
	return true;
}

bool UCsManager_Weapon::IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
{
	if (!DataLibrary::IsValid(Context, Data, Log))
		return false;
	return true;
}

#pragma endregion Valid

// Modifier
#pragma region

void UCsManager_Weapon::SetupModifiers()
{
	Manager_Modifiers.Reset((uint8)ModifierImplType::EImpl_MAX);
	Manager_Modifiers.AddDefaulted((uint8)ModifierImplType::EImpl_MAX);

	const FCsSettings_Manager_Weapon_Modifiers& ModifierSettings = FCsSettings_Manager_Weapon_Modifiers::Get();

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

	ImplTypeByModifier.Reset(EMCsWeaponModifier::Get().Num());
	ImplTypeByModifier.AddDefaulted(EMCsWeaponModifier::Get().Num());

	// Projectile Weapon
	ImplTypeByModifier[NCsWeaponModifier::PrjWp_TimeBetweenShots.GetValue()]			  = ModifierImplType::Float;
		// ProjectilesPerShot
	ImplTypeByModifier[NCsWeaponModifier::PrjWp_ProjectilesPerShot_Count.GetValue()]	= ModifierImplType::Int;
	ImplTypeByModifier[NCsWeaponModifier::PrjWp_ProjectilesPerShot_Interval.GetValue()]	= ModifierImplType::Float;
		// Spread
	ImplTypeByModifier[NCsWeaponModifier::PrjWp_UseSpreadParams.GetValue()]	= ModifierImplType::Toggle;
	// Point Weapon
	ImplTypeByModifier[NCsWeaponModifier::PointWp_TimeBetweenShots.GetValue()] = ModifierImplType::Float;
		// PointsPerShot
	ImplTypeByModifier[NCsWeaponModifier::PointWp_PointsPerShot_Count.GetValue()] = ModifierImplType::Int;
	ImplTypeByModifier[NCsWeaponModifier::PointWp_PointsPerShot_Interval.GetValue()] = ModifierImplType::Float;
	// Point Sequence Weapon
	ImplTypeByModifier[NCsWeaponModifier::PointSeqWp_TimeBetweenShots.GetValue()] = ModifierImplType::Float;
		// Sequence
	ImplTypeByModifier[NCsWeaponModifier::PointSeqWp_Sequence_Count.GetValue()] = ModifierImplType::Int;
	ImplTypeByModifier[NCsWeaponModifier::PointSeqWp_Sequence_Interval.GetValue()] = ModifierImplType::Float;
		// SequencesPerShot
	ImplTypeByModifier[NCsWeaponModifier::PointSeqWp_SequencesPerShot_Count.GetValue()] = ModifierImplType::Int;
	ImplTypeByModifier[NCsWeaponModifier::PointSeqWp_SequencesPerShot_Interval.GetValue()] = ModifierImplType::Float;
}

ModifierType* UCsManager_Weapon::ConstructModifier(const ModifierImplType& ImplType)
{
	// Int
	if (ImplType == ModifierImplType::Int)
		return new NCsWeapon::NModifier::FInt();
	// Float
	if (ImplType == ModifierImplType::Float)
		return new NCsWeapon::NModifier::FFloat();
	// Toggle
	if (ImplType == ModifierImplType::Toggle)
		return new NCsWeapon::NModifier::FToggle();
	check(0);
	return nullptr;
}

ModifierResourceType* UCsManager_Weapon::AllocateModifier(const FECsWeaponModifier& Type)
{
	checkf(EMCsWeaponModifier::Get().IsValidEnum(Type), TEXT("UCsManager_Weapon::AllocateModifier: Type: %s is NOT Valid."), Type.ToChar());

	return Manager_Modifiers[Type.GetValue()].Allocate();
}

void UCsManager_Weapon::DeallocateModifier(const FString& Context, const FECsWeaponModifier& Type, ModifierResourceType* Modifier)
{
	checkf(EMCsWeaponModifier::Get().IsValidEnum(Type), TEXT("UCsManager_Weapon::DeallocateModifier: Type: %s is NOT Valid."), Type.ToChar());

	CS_IS_PTR_NULL_CHECKED(Modifier)

	// Reset
	if (ICsReset* IReset = CsWeaponModifierLibrary::GetSafeInterfaceChecked<ICsReset>(Context, Modifier->Get()))
		IReset->Reset();

	Manager_Modifiers[Type.GetValue()].Deallocate(Modifier);
}

const FECsWeaponModifier& UCsManager_Weapon::GetModifierType(const FString& Context, const ModifierType* Modifier)
{
	const ICsGetWeaponModifierType* GetWeaponModifierType = CsWeaponModifierLibrary::GetInterfaceChecked<ICsGetWeaponModifierType>(Context, Modifier);
	const FECsWeaponModifier& Type						  = GetWeaponModifierType->GetWeaponModifierType();

	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type);

	return Type;
}

ModifierResourceType* UCsManager_Weapon::CreateCopyOfModifier(const FString& Context, const ModifierType* Modifier)
{
	const FECsWeaponModifier& Type	= GetModifierType(Context, Modifier);
	ModifierResourceType* Container	= AllocateModifier(Type);
	ModifierType* Copy				= Container->Get();

	CopyType* ICopy = CsWeaponModifierLibrary::GetInterfaceChecked<CopyType>(Context, Copy);

	ICopy->Copy(Modifier);

	return Container;
}

ModifierResourceType* UCsManager_Weapon::CreateCopyOfModifier(const FString& Context, const ModifierResourceType* Modifier)
{
	return CreateCopyOfModifier(Context, Modifier->Get());
}

#pragma endregion Modifier

// Spread
#pragma region

void UCsManager_Weapon::SetupSpreadVariables()
{
	SpreadVariablesManager.CreatePool(Settings.Spread.PoolSize);
}

#pragma endregion Spread