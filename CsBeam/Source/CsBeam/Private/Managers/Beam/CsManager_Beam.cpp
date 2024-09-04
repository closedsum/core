// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Beam/CsManager_Beam.h"
#include "CsBeam.h"

// CVars
#include "Managers/Beam/CsCVars_Manager_Beam.h"
// Types
#include "Collision/CsTypes_Collision.h"
// Library
#include "Library/CsLibrary_Property.h"
#include "Data/CsLibrary_Data_Beam.h"
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsBeamLibrary_DataRootSet.h"
#include "Game/CsLibrary_GameInstance.h"
#include "Level/CsLibrary_Level.h"
// Utility
#include "Utility/CsBeamLog.h"
// Settings
#include "Settings/CsBeamSettings.h"
// Managers
#include "Managers/Data/CsManager_Data.h"
#include "Managers/Time/CsManager_Time.h"
// Data
#include "Data/CsBeamGetDataRootSet.h"
#include "Data/CsData_Beam.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
#include "Settings/CsGetSettingsManagerBeamPoolParams.h"
// Beam
#include "Managers/Beam/Handler/CsManager_Beam_ClassHandler.h"
#include "Managers/Beam/Handler/CsManager_Beam_DataHandler.h"
#include "Payload/CsPayload_BeamInterfaceMap.h"
#include "Payload/CsPayload_BeamImplSlice.h"
#include "Payload/Damage/CsPayload_BeamModifierDamageImplSlice.h"
// Level
#include "Engine/LevelScriptActor.h"

#if WITH_EDITOR
// Library
#include "Managers/Beam/CsLibrary_Manager_Beam.h"
// Singleton
#include "Singleton/CsGetManagerSingleton.h"
#include "Singleton/CsManager_Singleton.h"
#include "Managers/Beam/CsGetManagerBeam.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsManager_Beam)

// Cached
#pragma region

namespace NCsManagerBeam
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Beam, GetFromWorldContextObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Beam, SetupInternal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Beam, InitInternalFromSettings);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Beam, PopulateClassMapFromSettings);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Beam, PopulateDataMapFromSettings);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Beam, CreateEmulatedDataFromDataTable);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Beam, PopulateDataMapFromDataTable);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Beam, GetBeam);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Beam, GetData);
		}

		namespace Name
		{
		}
	}
}

#pragma endregion Cached

// Internal
#pragma region

namespace NCsBeam
{
	FManager::FManager()
		: Super()
	{
	}
}

#pragma endregion Internal

// static initializations
UCsManager_Beam* UCsManager_Beam::s_Instance;
bool UCsManager_Beam::s_bShutdown = false;

UCsManager_Beam::UCsManager_Beam(const FObjectInitializer& ObjectInitializer)
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
	Script_Update_Impl()
{
}

// Singleton
#pragma region

#if WITH_EDITOR

/*static*/ UCsManager_Beam* UCsManager_Beam::Get(UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerBeam(InRoot)->GetManager_Beam();
}

/*static*/ bool UCsManager_Beam::IsValid(UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerBeam(InRoot)->GetManager_Beam() != nullptr;
}

#endif // #if WITH_EDITOR

/*static*/ void UCsManager_Beam::Init(UObject* InRoot, TSubclassOf<UCsManager_Beam> ManagerBeamClass, UObject* InOuter /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerBeam* GetManagerBeam = Get_GetManagerBeam(InRoot);

	UCsManager_Beam* Manager_Beam = GetManagerBeam->GetManager_Beam();

	if (!Manager_Beam)
	{
		Manager_Beam = NewObject<UCsManager_Beam>(InOuter ? InOuter : InRoot, ManagerBeamClass, TEXT("Manager_Beam_Singleton"), RF_Transient | RF_Public);

		GetManagerBeam->SetManager_Beam(Manager_Beam);

		Manager_Beam->SetMyRoot(InRoot);
		Manager_Beam->Initialize();
	}
	else
	{
		UE_LOG(LogCsBeam, Warning, TEXT("UCsManager_Beam::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Beam>(GetTransientPackage(), ManagerBeamClass, TEXT("Manager_Beam_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCsBeam, Warning, TEXT("UCsManager_Beam::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Beam::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerBeam* GetManagerBeam = Get_GetManagerBeam(InRoot);
	UCsManager_Beam* Manager_Beam	  = GetManagerBeam->GetManager_Beam();
	Manager_Beam->CleanUp();

	GetManagerBeam->SetManager_Beam(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCsBeam, Warning, TEXT("UCsManager_Beam::Shutdown: Manager has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Beam::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerBeam(InRoot)->GetManager_Beam() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerBeam* UCsManager_Beam::Get_GetManagerBeam(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Beam::Get_GetManagerBeam: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Beam::Get_GetManagerBeam: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Beam::Get_GetManagerBeam: Manager_Singleton is NULL."));

	ICsGetManagerBeam* GetManagerBeam = Cast<ICsGetManagerBeam>(Manager_Singleton);

	checkf(GetManagerBeam, TEXT("UCsManager_Beam::Get_GetManagerBeam: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerBeam."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerBeam;
}

/*static*/ ICsGetManagerBeam* UCsManager_Beam::GetSafe_GetManagerBeam(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCsBeam, Warning, TEXT("UCsManager_Beam::GetSafe_GetManagerBeam: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCsBeam, Warning, TEXT("UCsManager_Beam::GetSafe_GetManagerBeam: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCsBeam, Warning, TEXT("UCsManager_Beam::GetSafe_GetManagerBeam: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetManagerBeam>(Manager_Singleton);
}

/*static*/ UCsManager_Beam* UCsManager_Beam::GetSafe(UObject* Object)
{
	if (ICsGetManagerBeam* GetManagerBeam = GetSafe_GetManagerBeam(Object))
		return GetManagerBeam->GetManager_Beam();
	return nullptr;
}

/*static*/ UCsManager_Beam* UCsManager_Beam::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	using namespace NCsManagerBeam::NCached;

	const FString& Context = Str::GetFromWorldContextObject;

	typedef NCsBeam::NManager::FLibrary BeamManagerLibrary;

	if (UObject* ContextRoot = BeamManagerLibrary::GetSafe(Context, WorldContextObject))
	{
		if (UCsManager_Beam* Manager = GetSafe(ContextRoot))
			return Manager;

		UE_LOG(LogCsBeam, Warning, TEXT("%s: Failed to Manager Beam of type UCsManager_Beam from ContextRoot: %s."), *Context, *(ContextRoot->GetName()));
	}
	return nullptr;
}

#endif // #if WITH_EDITOR

void UCsManager_Beam::Initialize()
{
	SetupInternal();

	bInitialized = true;
}

/*static*/ bool UCsManager_Beam::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_Beam::CleanUp()
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

	for (NCsBeam::NPayload::FInterfaceMap* Map : PayloadInterfaceMaps)
	{
		delete Map;
	}
	PayloadInterfaceMaps.Reset();
	
	Pool.Reset();

	delete ClassHandler;
	ClassHandler = nullptr;

	delete DataHandler;
	DataHandler = nullptr;

	bInitialized = false;
}

	// Root
#pragma region

void UCsManager_Beam::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// Settings
#pragma region

void UCsManager_Beam::SetAndAddTypeMapKeyValue(const FECsBeam& Key, const FECsBeam& Value)
{
	check(EMCsBeam::Get().IsValidEnum(Key));

	check(EMCsBeam::Get().IsValidEnum(Value));

	for (int32 I = TypeMapArray.Num() - 1; I < Key.GetValue(); ++I)
	{
		TypeMapArray.AddDefaulted_GetRef() = EMCsBeam::Get().GetEnumAt(I + 1);
	}
	TypeMapArray[Key.GetValue()] = Value;
}

#pragma endregion Settings

// Internal
#pragma region

void UCsManager_Beam::SetupInternal()
{
	using namespace NCsManagerBeam::NCached;

	const FString& Context = Str::SetupInternal;

	// Populate EnumMaps
	typedef NCsGameInstance::FLibrary GameInstanceLibrary;

	UObject* ContextRoot = GameInstanceLibrary::GetSafeAsObject(Context, MyRoot, nullptr);

	NCsBeam::PopulateEnumMapFromSettings(Context, ContextRoot);
	NCsBeamClass::PopulateEnumMapFromSettings(Context, ContextRoot);

	// Class Handler
	ConstructClassHandler();

	checkf(ClassHandler, TEXT("%s: Failed to construct ClassHandler."), *Context);

	// Data Handler
	ConstructDataHandler();

	checkf(DataHandler, TEXT("%s: Failed to construct DataHandler."), *Context);

	// Delegates
	{
		// Log
		Internal.LogTransaction_Impl.BindUObject(this, &UCsManager_Beam::LogTransaction);
		// Container
		Internal.ConstructContainer_Impl.BindUObject(this, &UCsManager_Beam::ConstructContainer);
		// Payload
		Internal.ConstructPayload_Impl.BindUObject(this, &UCsManager_Beam::ConstructPayload);
		// Pool
		Internal.OnAddToPool_Event.AddUObject(this, &UCsManager_Beam::OnAddToPool);
		// Update
		Internal.OnPreUpdate_Pool_Impl.BindUObject(this, &UCsManager_Beam::OnPreUpdate_Pool);
		Internal.OnUpdate_Object_Event.AddUObject(this, &UCsManager_Beam::OnUpdate_Object);
		Internal.OnPostUpdate_Pool_Impl.BindUObject(this, &UCsManager_Beam::OnPostUpdate_Pool);

		// Bind delegates for a script interface.
		Internal.Script_GetCache_Impl = Script_GetCache_Impl;
		Internal.Script_Allocate_Impl = Script_Allocate_Impl;
		Internal.Script_Deallocate_Impl = Script_Deallocate_Impl;
		Internal.Script_Update_Impl = Script_Update_Impl;
	}

#if !UE_BUILD_SHIPPING
	//if (FCsCVarToggleMap::Get().IsEnabled(NCsCVarToggle::EnableManagerBeamUnitTest))
	//{
		// Do Nothing
	//}
	//else
#endif // #if !UE_BUILD_SHIPPING
		// If any settings have been set for Manager_Beam, apply them
	{
		UCsBeamSettings* ModuleSettings = GetMutableDefault<UCsBeamSettings>();

		checkf(ModuleSettings, TEXT("UCsManager_Beam::SetupInternal: Failed to get settings of type: UCsBeamSettings."));

		Settings = ModuleSettings->Manager_Beam;

		// Populate TypeMapArray
		{
			const int32& Count = EMCsBeam::Get().Num();

			TypeMapArray.Reset(Count);

			for (const FECsBeam& Type : EMCsBeam::Get())
			{
				TypeMapArray.Add(Type);
			}

			for (const TPair<FECsBeam, FECsBeam>& Pair : Settings.TypeMap)
			{
				TypeMapArray[Pair.Key.GetValue()] = Pair.Value;
			}
		}

		// Populate TypesByUpdateGroup
		{
			TypesByUpdateGroup.Reset(EMCsUpdateGroup::Get().Num());
			TypesByUpdateGroup.AddDefaulted(EMCsUpdateGroup::Get().Num());

			for (TPair<FECsUpdateGroup, FCsSettings_Manager_Beam_TypeArray>& Pair : Settings.TypesByUpdateGroupMap)
			{
				const FECsUpdateGroup& Group						  = Pair.Key;
				const FCsSettings_Manager_Beam_TypeArray& Array = Pair.Value;

				checkf(Array.Types.Num() > CS_EMPTY, TEXT("%s: No Types added for UCsDeveloperSettings.Manager_Sound.TypesByUpdateGroupMap[%s]."), *Context, Group.ToChar());

				TypesByUpdateGroup[Group.GetValue()].Append(Array.Types);

				bTypesByUpdateGroup = true;
			}
		}

		// Check if there any pool params from the LevelScriptActor
		typedef NCsLevel::NPersistent::FLibrary LevelLibrary;

		if (ICsGetSettingsManagerBeamPoolParams* GetPoolParams = LevelLibrary::GetSafeScriptActor<ICsGetSettingsManagerBeamPoolParams>(MyRoot))
		{
			Settings.PoolParams = GetPoolParams->GetSettingsManagerBeamPoolParams();
		}

		InitInternalFromSettings();
	}
}

void UCsManager_Beam::InitInternalFromSettings()
{
	using namespace NCsManagerBeam::NCached;

	const FString& Context = Str::InitInternalFromSettings;

	ClassHandler->PopulateClassMapFromSettings(Context);
	DataHandler->PopulateDataMapFromSettings(Context);

	if (Settings.PoolParams.Num() > CS_EMPTY)
	{
		typedef NCsBeam::FManager::FParams ManagerParamsType;

		ManagerParamsType ManagerParams;

		ManagerParams.Name  = TEXT("UCsManager_Beam::NCsBeam::FManager");
		ManagerParams.World = MyRoot->GetWorld();

		for (const TPair<FECsBeam, FCsSettings_Manager_Beam_PoolParams>& Pair : Settings.PoolParams)
		{
			const FECsBeam& Type								= Pair.Key;
			const FCsSettings_Manager_Beam_PoolParams& Params = Pair.Value;

			typedef NCsPooledObject::NManager::FPoolParams PoolParamsType;

			PoolParamsType& PoolParams = ManagerParams.ObjectParams.Add(Type);

			// Get Class
			const FECsBeamClass& ClassType = Params.Class;

			checkf(EMCsBeamClass::Get().IsValidEnum(ClassType), TEXT("%s: Class for NOT Valid."), *Context, ClassType.ToChar());

			FCsBeamPooled* Beam = GetBeamChecked(Context, ClassType);
			UClass* Class					= Beam->GetClass();

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

#define ManagerParamsType NCsBeam::FManager::FParams
void UCsManager_Beam::InitInternal(const ManagerParamsType& Params)
{
	// Add CVars
	{
		ManagerParamsType& P = const_cast<ManagerParamsType&>(Params);

		typedef NCsPooledObject::NManager::FPoolParams PoolParamsType;

		for (TPair<FECsBeam, PoolParamsType>& Pair : P.ObjectParams)
		{
			PoolParamsType& PoolParams = Pair.Value;

			// Scoped Timer CVars
			PoolParams.ScopedGroup = NCsScopedGroup::ManagerBeam;

			PoolParams.CreatePoolScopedTimerCVar		= NCsCVarLog::LogManagerBeamScopedTimerCreatePool;
			PoolParams.UpdateScopedTimerCVar			= NCsCVarLog::LogManagerBeamScopedTimerUpdate;
			PoolParams.UpdateObjectScopedTimerCVar		= NCsCVarLog::LogManagerBeamScopedTimerUpdateObject;
			PoolParams.AllocateScopedTimerCVar			= NCsCVarLog::LogManagerBeamScopedTimerAllocate;
			PoolParams.AllocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerBeamScopedTimerAllocateObject;
			PoolParams.DeallocateScopedTimerCVar		= NCsCVarLog::LogManagerBeamScopedTimerDeallocate;
			PoolParams.DeallocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerBeamScopedTimerDeallocateObject;
			PoolParams.SpawnScopedTimerCVar				= NCsCVarLog::LogManagerBeamScopedTimerSpawn;
			PoolParams.DestroyScopedTimerCVar			= NCsCVarLog::LogManagerBeamScopedTimerDestroy;
		}
	}
	Internal.Init(Params);
}
#undef ManagerParamsType

void UCsManager_Beam::Clear()
{
	Internal.Clear();
}

	// Pool
#pragma region

void UCsManager_Beam::CreatePool(const FECsBeam& Type, const int32& Size)
{
	const int32& PoolSize = Internal.GetPoolSize(Type);

	if (PoolSize > CS_EMPTY)
	{
		UE_LOG(LogCsBeam, Warning, TEXT("UCsManager_Beam::CreatePool: Pool for Creep: %s has already been created with Size: %d."), Type.ToChar(), PoolSize);
	}

	Internal.CreatePool(Type, Size);
}

TDelegate<FCsBeamPooled*(const FECsBeam&)>& UCsManager_Beam::GetConstructContainer_Impl()
{
	return Internal.ConstructContainer_Impl;
}

FCsBeamPooled* UCsManager_Beam::ConstructContainer(const FECsBeam& Type)
{
	return new FCsBeamPooled();
}

#define ConstructParamsType NCsPooledObject::NManager::FConstructParams
TMulticastDelegate<void(const FCsBeamPooled*, const ConstructParamsType&)>& UCsManager_Beam::GetOnConstructObject_Event(const FECsBeam& Type)
{
#undef ConstructParamsType
	return Internal.GetOnConstructObject_Event(Type);
}

		// Add
#pragma region

			// Pool
#pragma region

const FCsBeamPooled* UCsManager_Beam::AddToPool(const FECsBeam& Type, ICsBeam* Object)
{
	return Internal.AddToPool(GetTypeFromTypeMap(Type), Object);
}

const FCsBeamPooled* UCsManager_Beam::AddToPool(const FECsBeam& Type, const FCsBeamPooled* Object)
{
	return Internal.AddToPool(GetTypeFromTypeMap(Type), Object->GetObject());
}

const FCsBeamPooled* UCsManager_Beam::AddToPool(const FECsBeam& Type, UObject* Object)
{
	return Internal.AddToPool(GetTypeFromTypeMap(Type), Object);
}

void UCsManager_Beam::OnAddToPool(const FECsBeam& Type, const FCsBeamPooled* Object)
{
	Pool.Add(Object->GetObject());

	// Apply delegates for a script interface
	FCsBeamPooled* O = const_cast<FCsBeamPooled*>(Object);

	O->Script_GetInstigator_Impl = Script_GetInstigator_Impl;
	O->Script_GetOwner_Impl = Script_GetOwner_Impl;
}

#pragma endregion Pool

			// Allocated Objects
#pragma region

const FCsBeamPooled* UCsManager_Beam::AddToAllocatedObjects(const FECsBeam& Type, ICsBeam* Beam, UObject* Object)
{
	return Internal.AddToAllocatedObjects(GetTypeFromTypeMap(Type), Beam, Object);
}

const FCsBeamPooled* UCsManager_Beam::AddToAllocatedObjects(const FECsBeam& Type, ICsBeam* Object)
{
	return Internal.AddToAllocatedObjects(GetTypeFromTypeMap(Type), Object);
}

const FCsBeamPooled* UCsManager_Beam::AddToAllocatedObjects(const FECsBeam& Type, UObject* Object)
{
	return Internal.AddToAllocatedObjects(GetTypeFromTypeMap(Type), Object);
}

#pragma endregion Allocated Objects

#pragma endregion Add

const TArray<FCsBeamPooled*>& UCsManager_Beam::GetPool(const FECsBeam& Type)
{
	return Internal.GetPool(GetTypeFromTypeMap(Type));
}

const TArray<FCsBeamPooled*>& UCsManager_Beam::GetAllocatedObjects(const FECsBeam& Type)
{
	return Internal.GetAllocatedObjects(GetTypeFromTypeMap(Type));
}

const int32& UCsManager_Beam::GetPoolSize(const FECsBeam& Type)
{
	return Internal.GetPoolSize(GetTypeFromTypeMap(Type));
}

int32 UCsManager_Beam::GetAllocatedObjectsSize(const FECsBeam& Type)
{
	return Internal.GetAllocatedObjectsSize(GetTypeFromTypeMap(Type));
}

bool UCsManager_Beam::IsExhausted(const FECsBeam& Type)
{
	return Internal.IsExhausted(GetTypeFromTypeMap(Type));
}

	// Find
#pragma region

const FCsBeamPooled* UCsManager_Beam::FindObject(const FECsBeam& Type, const int32& Index)
{
	return Internal.FindObject(GetTypeFromTypeMap(Type), Index);
}

const FCsBeamPooled* UCsManager_Beam::FindObject(const FECsBeam& Type, ICsBeam* Object)
{
	return Internal.FindObject(GetTypeFromTypeMap(Type), Object);
}

const FCsBeamPooled* UCsManager_Beam::FindObject(const FECsBeam& Type, UObject* Object)
{
	return Internal.FindObject(GetTypeFromTypeMap(Type), Object);
}

const FCsBeamPooled* UCsManager_Beam::FindSafeObject(const FECsBeam& Type, const int32& Index)
{
	return Internal.FindSafeObject(GetTypeFromTypeMap(Type), Index);
}

const FCsBeamPooled* UCsManager_Beam::FindSafeObject(const FECsBeam& Type, ICsBeam* Object)
{
	return Internal.FindSafeObject(GetTypeFromTypeMap(Type), Object);
}

const FCsBeamPooled* UCsManager_Beam::FindSafeObject(const FECsBeam& Type, UObject* Object)
{
	return Internal.FindSafeObject(GetTypeFromTypeMap(Type), Object);
}

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region

void UCsManager_Beam::Update(const FCsDeltaTime& DeltaTime)
{
	Internal.Update(DeltaTime);
}

void UCsManager_Beam::Update(const FECsUpdateGroup& Group, const FCsDeltaTime& DeltaTime)
{
	checkf(TypesByUpdateGroup[Group.GetValue()].Num() > CS_EMPTY, TEXT("UCsManager_Beam::Update: No Types associated with Group: %s."), Group.ToChar());

	for (const FECsBeam& Type : TypesByUpdateGroup[Group.GetValue()])
	{
		Internal.Update(Type, DeltaTime);
	}
}

void UCsManager_Beam::Update(const FECsBeam& Type, const FCsDeltaTime& DeltaTime)
{
	Internal.Update(Type, DeltaTime);
}

void UCsManager_Beam::OnPreUpdate_Pool(const FECsBeam& Type)
{
	CurrentUpdatePoolType		 = Type;
	CurrentUpdatePoolObjectIndex = 0;
}

void UCsManager_Beam::OnUpdate_Object(const FECsBeam& Type, const FCsBeamPooled* Object)
{
	++CurrentUpdatePoolObjectIndex;
}

void UCsManager_Beam::OnPostUpdate_Pool(const FECsBeam& Type)
{
}

#pragma endregion Update

	// Pause
#pragma region

void UCsManager_Beam::Pause(const FECsUpdateGroup& Group, bool bPaused)
{
	if (bTypesByUpdateGroup)
	{
		checkf(TypesByUpdateGroup[Group.GetValue()].Num() > CS_EMPTY, TEXT("UCsManager_Beam::Update: No Types associated with Group: %s."), Group.ToChar());

		for (const FECsBeam& Type : TypesByUpdateGroup[Group.GetValue()])
		{
			Internal.Pause(Type, bPaused);
		}
	}
	else
	{
		Internal.Pause(bPaused);
	}
}

void UCsManager_Beam::Pause(const FECsBeam& Type, bool bPaused)
{
	Internal.Pause(Type, bPaused);
}

void UCsManager_Beam::BindToOnPause(const FECsUpdateGroup& Group)
{
	FDelegateHandle Handle = UCsManager_Time::Get(GetOuter())->GetOnPause_Event(Group).AddUObject(this, &UCsManager_Beam::Pause);

	OnPauseHandleByGroupMap.Add(Group, Handle);
}

#pragma endregion Pause

	// Payload
#pragma region

void UCsManager_Beam::ConstructPayloads(const FECsBeam& Type, const int32& Size)
{
	Internal.ConstructPayloads(GetTypeFromTypeMap(Type), Size);
}

#define PayloadType NCsBeam::NPayload::IPayload
PayloadType* UCsManager_Beam::ConstructPayload(const FECsBeam& Type)
{
	// TODO: Perform a new in place for all structs.
	//		 Need to call dtor manually

	NCsBeam::NPayload::FInterfaceMap* PayloadInterfaceMap = new NCsBeam::NPayload::FInterfaceMap();

	PayloadInterfaceMaps.Add(PayloadInterfaceMap);

	FCsInterfaceMap* InterfaceMap = PayloadInterfaceMap->GetInterfaceMap();

	// FCsPayload_PooledObjectImplSlice
	typedef NCsPooledObject::NPayload::FImplSlice BaseSliceType;

	BaseSliceType* BaseSlice = new BaseSliceType();

	{
		BaseSlice->SetInterfaceMap(InterfaceMap);
		// Add to map
		TArray<void*>& ImplMap = PayloadInterfaceImplMap.FindOrAdd(BaseSliceType::Name);
		ImplMap.Add(BaseSlice);
	}

	// NCsBeam::NPayload::FImplSice
	{
		typedef NCsBeam::NPayload::FImplSlice SliceType;

		SliceType* Slice = new SliceType();

		Slice->SetInterfaceMap(InterfaceMap);
		// Add slice as ICsReset to BaseSlice so this slice gets reset call.
		BaseSlice->AddReset(static_cast<ICsReset*>(Slice));
		// NOTE: Do NOT add to map. Internal will take care of deconstruction.
	}

	UCsBeamSettings* ModuleSettings = GetMutableDefault<UCsBeamSettings>();
	
	const TSet<FECsBeamPayload> PayloadTypes = ModuleSettings->Manager_Beam.PayloadTypes;

	// NCsBeam::NPayload::NModifier::NDamage::FImplSlice
	if (PayloadTypes.Contains(NCsBeamPayload::BeamDamageModifier))
	{
		typedef NCsBeam::NPayload::NModifier::NDamage::FImplSlice SliceType;

		SliceType* Slice = new SliceType();

		Slice->SetInterfaceMap(InterfaceMap);
		// Add slice as ICsReset to BaseSlice so this slice gets reset call.
		BaseSlice->AddReset(static_cast<ICsReset*>(Slice));
		// Add to map
		TArray<void*>& ImplMap = PayloadInterfaceImplMap.FindOrAdd(SliceType::Name);
		ImplMap.Add(Slice);
	}

	return InterfaceMap->Get<PayloadType>();
}
#undef PayloadType

void UCsManager_Beam::DeconstructPayloadSlice(const FName& InterfaceImplName, void* Data)
{
	// FCsPayload_PooledObjectImplSlice
	if (InterfaceImplName == NCsPooledObject::NPayload::FImplSlice::Name)
	{
		delete static_cast<NCsPooledObject::NPayload::FImplSlice*>(Data);
	}
	// FCsPayload_BeamImplSlice
	if (InterfaceImplName == NCsBeam::NPayload::FImplSlice::Name)
	{
		checkf(0, TEXT("UCsManager_Beam::DeconstructPayloadSlice: Deleting Data of type: NCsBeam::NPayload::FImplSlice is handled by Intenral."));
	}
	// FCsPayload_BeamModifierDamageImplSlice
	if (InterfaceImplName == NCsBeam::NPayload::NModifier::NDamage::FImplSlice::Name)
	{
		typedef NCsBeam::NPayload::NModifier::NDamage::FImplSlice SliceType;

		delete static_cast<SliceType*>(Data);
	}
}

#define PayloadType NCsBeam::NPayload::IPayload

PayloadType* UCsManager_Beam::AllocatePayload(const FECsBeam& Type)
{
	return Internal.AllocatePayload(GetTypeFromTypeMap(Type));
}

#undef PayloadType

#pragma endregion Payload

	// Spawn
#pragma region

#define PayloadType NCsBeam::NPayload::IPayload
const FCsBeamPooled* UCsManager_Beam::Spawn(const FECsBeam& Type, PayloadType* Payload)
{
#undef PayloadType
	return Internal.Spawn(GetTypeFromTypeMap(Type), Payload);
}

#pragma endregion Spawn

	// Destroy
#pragma region

bool UCsManager_Beam::Destroy(const FECsBeam& Type, ICsBeam* Beam)
{
	return Internal.Destroy(GetTypeFromTypeMap(Type), Beam);
}

bool UCsManager_Beam::Destroy(ICsBeam* Beam)
{
	return Internal.Destroy(Beam);
}


#pragma endregion Destroy

	// Log
#pragma region

void UCsManager_Beam::Log(const FString& Str)
{
	UE_LOG(LogCsBeam, Warning, TEXT("%s"), *Str);
}

void UCsManager_Beam::LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsBeamPooled* Object)
{
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerBeamTransactions))
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
			UE_LOG(LogCsBeam, Warning, TEXT("%s: %s %s of Type: %s for %s attached to %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *OwnerName, *ParentName, CurrentTime);
		}
		else 
		if (ObjectOwner)
		{
			UE_LOG(LogCsBeam, Warning, TEXT("%s: %s %s of Type: %s for %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *OwnerName, CurrentTime);
		}
		else
		if (Parent)
		{
			UE_LOG(LogCsBeam, Warning, TEXT("%s: %s %s of Type: %s attached to %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *ParentName, CurrentTime);
		}
		else
		{
			UE_LOG(LogCsBeam, Warning, TEXT("%s: %s %s of Type: %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, CurrentTime);
		}
	}
}

#pragma endregion Log 

#pragma endregion Internal

// Class
#pragma region

void UCsManager_Beam::ConstructClassHandler()
{
	typedef NCsBeam::NManager::NHandler::FClass ClassHandlerType;

	ClassHandler = new ClassHandlerType();
	ClassHandler->Outer = this;
	ClassHandler->MyRoot = MyRoot;
}

FCsBeamPooled* UCsManager_Beam::GetBeam(const FECsBeam& Type)
{
	using namespace NCsManagerBeam::NCached;

	const FString& Context = Str::GetBeam;

	return ClassHandler->GetClassByType<EMCsBeam, FECsBeam>(Context, Type);
}

FCsBeamPooled* UCsManager_Beam::GetBeam(const FECsBeamClass& Type)
{
	using namespace NCsManagerBeam::NCached;

	const FString& Context = Str::GetBeam;

	return ClassHandler->GetClassByClassType<EMCsBeamClass>(Context, Type);
}

FCsBeamPooled* UCsManager_Beam::GetBeamChecked(const FString& Context, const FECsBeamClass& Type)
{
	return ClassHandler->GetClassByClassTypeChecked<EMCsBeamClass>(Context, Type);
}

#pragma endregion Class

// Data
#pragma region

void UCsManager_Beam::ConstructDataHandler()
{
	typedef NCsBeam::NManager::NHandler::FData DataHandlerType;

	DataHandler = new DataHandlerType();
	DataHandler->Outer = this;
	DataHandler->MyRoot = MyRoot;
}

#define DataType NCsBeam::NData::IData

DataType* UCsManager_Beam::GetData(const FName& Name)
{
	using namespace NCsManagerBeam::NCached;

	const FString& Context = Str::GetData;

	return DataHandler->GetData(Context, Name);
}

DataType* UCsManager_Beam::GetDataChecked(const FString& Context, const FName& Name)
{
	return DataHandler->GetDataChecked(Context, Name);
}

DataType* UCsManager_Beam::GetSafeData(const FString& Context, const FName& Name)
{
	return DataHandler->GetSafeData(Context, Name);
}

DataType* UCsManager_Beam::GetData(const FECsBeam& Type)
{
	using namespace NCsManagerBeam::NCached;

	const FString& Context = Str::GetData;

	return DataHandler->GetData<EMCsBeam, FECsBeam>(Context, Type);
}

DataType* UCsManager_Beam::GetDataChecked(const FString& Context, const FECsBeam& Type)
{
	return DataHandler->GetDataChecked<EMCsBeam, FECsBeam>(Context, Type);
}

DataType* UCsManager_Beam::GetSafeData(const FString& Context, const FECsBeam& Type)
{
	return DataHandler->GetSafeData<EMCsBeam, FECsBeam>(Context, Type);
}

#undef DataType

void UCsManager_Beam::OnPayloadUnloaded(const FName& Payload)
{
}

#pragma endregion Data