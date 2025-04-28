// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Sound/CsManager_Sound.h"
#include "CsSound.h"

// CVars
#include "Managers/Sound/CsCVars_Manager_Sound.h"
// Library
#include "Managers/Sound/Payload/CsLibrary_Payload_Sound.h"
#include "Managers/Time/CsLibrary_Manager_Time.h"
	// Common
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Managers/Sound/CsSettings_Manager_Sound.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// Data
#include "Managers/Sound/Data/CsData_Sound.h"
#include "Managers/Sound/Data/CsData_SoundImpl.h"
// FX
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"
// World
#include "Engine/World.h"
// Package
#include "UObject/Package.h"

#if WITH_EDITOR
// Library
#include "Managers/Sound/CsLibrary_Manager_Sound.h"
// Singleton
#include "Singleton/CsGetManagerSingleton.h"
#include "Singleton/CsManager_Singleton.h"
#include "Managers/Sound/CsGetManagerSound.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsManager_Sound)

// Cached
#pragma region

namespace NCsManagerSound
{
	namespace NCached
	{
		namespace Str
		{
			// Singleton
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Sound, Init);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Sound, SetupInternal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Sound, Spawn);

			const FString None = TEXT("None");
		}

		namespace Name
		{
		}
	}
}

#pragma endregion Cached

// Internal
#pragma region

namespace NCsSound
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
UCsManager_Sound* UCsManager_Sound::s_Instance;
bool UCsManager_Sound::s_bShutdown = false;

UCsManager_Sound::UCsManager_Sound(const FObjectInitializer& ObjectInitializer)
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
	Script_OnConstructObject_Impl(),
	// Data
	DataMap(),
	ClassMap(),
	DataTables()
{
}

using ManagerParamsType = NCsSound::NManager::NInternal::FManager::FParams;
using PoolParamsType = NCsPooledObject::NManager::FPoolParams;
using ConstructParamsType = NCsPooledObject::NManager::FConstructParams;
using PayloadLibrary = NCsSound::NPayload::NLibrary::FLibrary;
using PayloadType = NCsSound::NPayload::IPayload;
using PayloadImplType = NCsSound::NPayload::NImpl::FImpl;


// Singleton
#pragma region

#if WITH_EDITOR
/*static*/ UCsManager_Sound* UCsManager_Sound::Get(UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerSound(InRoot)->GetManager_Sound();
}

/*static*/ UCsManager_Sound* UCsManager_Sound::GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerSound* GetManagerSound = GetSafe_GetManagerSound(Context, InRoot, Log))
		return GetManagerSound->GetManager_Sound();
	return nullptr;
}

/*static*/ bool UCsManager_Sound::IsValid(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerSound(InRoot)->GetManager_Sound() != nullptr;
}
#endif // #if WITH_EDITOR

/*static*/ void UCsManager_Sound::Init(UObject* InRoot, TSubclassOf<UCsManager_Sound> ManagerSoundClass, UObject* InOuter /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerSound* GetManagerSound = Get_GetManagerSound(InRoot);

	UCsManager_Sound* Manager_Sound = GetManagerSound->GetManager_Sound();

	if (!Manager_Sound)
	{
		Manager_Sound = NewObject<UCsManager_Sound>(InOuter ? InOuter : InRoot, ManagerSoundClass, TEXT("Manager_Sound_Singleton"), RF_Transient | RF_Public);

		GetManagerSound->SetManager_Sound(Manager_Sound);

		Manager_Sound->SetMyRoot(InRoot);
		Manager_Sound->Initialize();
	}
	else
	{
		UE_LOG(LogCsSound, Warning, TEXT("UCsManager_Sound::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Sound>(GetTransientPackage(), ManagerSoundClass, TEXT("Manager_Sound_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCsSound, Warning, TEXT("UCsManager_Sound::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Sound::Init(UObject* InRoot, UObject* InOuter /*=nullptr*/)
{
	using namespace NCsManagerSound::NCached;

	const FString& Context = Str::Init;

	const FCsSettings_Manager_Sound& Settings = FCsSettings_Manager_Sound::Get();

	Init(InRoot, Settings.LoadClassChecked(Context), InOuter);
}

/*static*/ void UCsManager_Sound::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerSound* GetManagerSound = Get_GetManagerSound(InRoot);
	UCsManager_Sound* Manager_Sound		= GetManagerSound->GetManager_Sound();
	Manager_Sound->CleanUp();

	GetManagerSound->SetManager_Sound(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCsSound, Warning, TEXT("UCsManager_Sound::Shutdown: Manager has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Sound::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerSound(InRoot)->GetManager_Sound() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerSound* UCsManager_Sound::Get_GetManagerSound(const UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Sound::Get_GetManagerSound: InRoot is NULL."));

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Sound::Get_GetManagerSound: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Sound::Get_GetManagerSound: Manager_Singleton is NULL."));

	ICsGetManagerSound* GetManagerSound = Cast<ICsGetManagerSound>(Manager_Singleton);

	checkf(GetManagerSound, TEXT("UCsManager_Sound::Get_GetManagerSound: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerSound."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerSound;
}

/*static*/ ICsGetManagerSound* UCsManager_Sound::GetSafe_GetManagerSound(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
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
	return Cast<ICsGetManagerSound>(Manager_Singleton);
}

#endif // #if WITH_EDITOR

void UCsManager_Sound::Initialize()
{
	SetupInternal();

	bInitialized = true;
}

/*static*/ bool UCsManager_Sound::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_Sound::CleanUp()
{
#if WITH_EDITOR
	UObject* ContextRoot = CsTimeManagerLibrary::GetSafeContextRoot(this);

	if (ContextRoot)
#else
	UObject* ContextRoot = nullptr;
#endif // #if WITH_EDITOR
	{
		for (const TPair<FECsUpdateGroup, FDelegateHandle>& Pair : OnPauseHandleByGroupMap)
		{
			const FECsUpdateGroup& Group  = Pair.Key;
			const FDelegateHandle& Handle = Pair.Value;

			if (UCsManager_Time* Manager_Time = UCsManager_Time::Get(ContextRoot))
			{
				Manager_Time->RemoveOnPause(Group, Handle);
			}
		}
	}
	OnPauseHandleByGroupMap.Reset();

	Internal.Shutdown();

	// Editor Preview - Make sure to mark pending kill or destroy objects
#if WITH_EDITOR
	if (UWorld* World = MyRoot->GetWorld())
	{
		if (World->WorldType == EWorldType::EditorPreview)
		{
			for (UObject* O : Pool)
			{
				if (IsValid(O))
				{
					if (AActor* A = Cast<AActor>(O))
						A->Destroy();
					else
						O->MarkAsGarbage();
				}
			}
		}
	}
#endif // #if WITH_EDITOR
	Pool.Reset();

	for (TPair<FName, ICsData_Sound*>& Pair : DataMap)
	{
		ICsData_Sound* Data = Pair.Value;
		DeconstructData(Data);
		Pair.Value = nullptr;
	}
	DataMap.Reset();

	bInitialized = false;
}

	// Root
#pragma region

void UCsManager_Sound::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// Internal
#pragma region

void UCsManager_Sound::SetupInternal()
{
	using namespace NCsManagerSound::NCached;

	const FString& Context = Str::SetupInternal;

	// Populate EnumMaps
	UObject* ContextObject = CsGameInstanceLibrary::GetSafeAsObject(Context, MyRoot, nullptr);

	NCsSound::PopulateEnumMapFromSettings(Context, ContextObject);

	// Delegates
	{
		// Log
		Internal.Log_Impl.BindUObject(this, &UCsManager_Sound::Log);
		Internal.LogTransaction_Impl.BindUObject(this, &UCsManager_Sound::LogTransaction);
		// Container
		Internal.ConstructContainer_Impl.BindUObject(this, &UCsManager_Sound::ConstructContainer);
		// Payload
		Internal.ConstructPayload_Impl.BindUObject(this, &UCsManager_Sound::ConstructPayload);
		// Pool
		Internal.OnAddToPool_Event.AddUObject(this, &UCsManager_Sound::OnAddToPool);
		// Update
		Internal.OnPreUpdate_Pool_Impl.BindUObject(this, &UCsManager_Sound::OnPreUpdate_Pool);
		Internal.OnUpdate_Object_Event.AddUObject(this, &UCsManager_Sound::OnUpdate_Object);
		Internal.OnPostUpdate_Pool_Impl.BindUObject(this, &UCsManager_Sound::OnPostUpdate_Pool);

		// Bind delegates for a script interface.
		Internal.Script_GetCache_Impl = Script_GetCache_Impl;
		Internal.Script_Allocate_Impl = Script_Allocate_Impl;
		Internal.Script_Deallocate_Impl = Script_Deallocate_Impl;
		Internal.Script_Update_Impl = Script_Update_Impl;
		Internal.Script_OnConstructObject_Impl = Script_OnConstructObject_Impl;
	}
#if !UE_BUILD_SHIPPING
	//if (FCsCVarToggleMap::Get().IsEnabled(NCsCVarToggle::EnableManagerSoundUnitTest))
	//{
		// Do Nothing
	//}
	//else
#endif // #if !UE_BUILD_SHIPPING
		// If any settings have been set for Manager_Sound, apply them
	{
		Settings = FCsSettings_Manager_Sound::Get();

		// Populate TypesByUpdateGroup
		{
			TypesByUpdateGroup.Reset(EMCsUpdateGroup::Get().Num());
			TypesByUpdateGroup.AddDefaulted(EMCsUpdateGroup::Get().Num());

			for (const TPair<FECsUpdateGroup, FCsSettings_Manager_Sound_TypeArray>& Pair : Settings.TypesByUpdateGroupMap)
			{
				const FECsUpdateGroup& Group					 = Pair.Key;
				const FCsSettings_Manager_Sound_TypeArray& Array = Pair.Value;

				checkf(Array.Types.Num() > CS_EMPTY, TEXT("%s: No Types added for UCsDeveloperSettings.Manager_Sound.TypesByUpdateGroupMap[%s]."), *Context, Group.ToChar());

				TypesByUpdateGroup[Group.GetValue()].Append(Array.Types);

				bTypesByUpdateGroup = true;
			}
		}
		InitInternalFromSettings();
	}

	typedef NCsSound::NPayload::NChange::FCounter ChangeCounter;

	ChangeCounter::Get().Reset();
}

void UCsManager_Sound::InitInternalFromSettings()
{
	PopulateDataMapFromSettings();

	if (Settings.PoolParams.Num() > CS_EMPTY)
	{
		ManagerParamsType ManagerParams;

		ManagerParams.Name  = TEXT("UCsManager_Sound::NCsSound::FManager");
		ManagerParams.World = MyRoot->GetWorld();

		for (const TPair<FECsSound, FCsSettings_Manager_Sound_PoolParams>& Pair : Settings.PoolParams)
		{
			const FECsSound& Type							   = Pair.Key;
			const FCsSettings_Manager_Sound_PoolParams& Params = Pair.Value;

			PoolParamsType& PoolParams = ManagerParams.ObjectParams.Add(Type);

			checkf(Params.Class.ToSoftObjectPath().IsValid(), TEXT("UCsManager_Sound::InitInternalFromSettings: Class for Type: %s is NOT a Valid Path."), Type.ToChar());

#if !UE_BUILD_SHIPPING
			if (!Params.Class.Get())
			{
				UE_LOG(LogCsSound, Warning, TEXT("UCsManager_Sound::InitInternalFromSettings: Class @ for Type: %s is NOT already loaded in memory."), *(Params.Class.ToString()), Type.ToChar());
			}
#endif // #if !UE_BUILD_SHIPPING

			UClass* Class = Params.Class.LoadSynchronous();

			checkf(Class, TEXT("UCsManager_Sound::InitInternalFromSettings: Failed to load Class @ for Type: %s."), *(Params.Class.ToString()), Type.ToChar());

			ClassMap.Add(Type, Class);

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

void UCsManager_Sound::InitInternal(const ManagerParamsType& Params)
{
	// Add CVars
	{
		ManagerParamsType& P = const_cast<ManagerParamsType&>(Params);

		for (TPair<FECsSound, PoolParamsType>& Pair : P.ObjectParams)
		{
			PoolParamsType& PoolParams = Pair.Value;

			// Scoped Timer CVars
			PoolParams.ScopedGroup = NCsScopedGroup::ManagerSound;

			PoolParams.CreatePoolScopedTimerCVar		= NCsCVarLog::LogManagerSoundScopedTimerCreatePool;
			PoolParams.UpdateScopedTimerCVar			= NCsCVarLog::LogManagerSoundScopedTimerUpdate;
			PoolParams.UpdateObjectScopedTimerCVar		= NCsCVarLog::LogManagerSoundScopedTimerUpdateObject;
			PoolParams.AllocateScopedTimerCVar			= NCsCVarLog::LogManagerSoundScopedTimerAllocate;
			PoolParams.AllocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerSoundScopedTimerAllocateObject;
			PoolParams.DeallocateScopedTimerCVar		= NCsCVarLog::LogManagerSoundScopedTimerDeallocate;
			PoolParams.DeallocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerSoundScopedTimerDeallocateObject;
			PoolParams.SpawnScopedTimerCVar				= NCsCVarLog::LogManagerSoundScopedTimerSpawn;
			PoolParams.DestroyScopedTimerCVar			= NCsCVarLog::LogManagerSoundScopedTimerDestroy;
		}
	}
	Internal.Init(Params);
}

void UCsManager_Sound::Clear()
{
	Internal.Clear();
}

	// Pool
#pragma region

void UCsManager_Sound::CreatePool(const FECsSound& Type, const int32& Size)
{
	const int32& PoolSize = Internal.GetPoolSize(Type);

	if (PoolSize > CS_EMPTY)
	{
		UE_LOG(LogCsSound, Warning, TEXT("UCsManager_Sound::CreatePool: Pool for Sound: %s has already been created with Size: %d."), Type.ToChar(), PoolSize);
	}

	Internal.CreatePool(Type, Size);
}

TDelegate<FCsSoundPooled*(const FECsSound&)>& UCsManager_Sound::GetConstructContainer_Impl()
{
	return Internal.ConstructContainer_Impl;
}

FCsSoundPooled* UCsManager_Sound::ConstructContainer(const FECsSound& Type)
{
	return new FCsSoundPooled();
}

TMulticastDelegate<void(const FCsSoundPooled*, const ConstructParamsType&)>& UCsManager_Sound::GetOnConstructObject_Event(const FECsSound& Type)
{
	return Internal.GetOnConstructObject_Event(Type);
}

		// Add
#pragma region

			// Pool
#pragma region

const FCsSoundPooled* UCsManager_Sound::AddToPool(const FECsSound& Type, ICsSoundPooled* Object)
{
	return Internal.AddToPool(Type, Object);
}

const FCsSoundPooled* UCsManager_Sound::AddToPool(const FECsSound& Type, const FCsSoundPooled* Object)
{
	return Internal.AddToPool(Type, Object->GetObject());
}

const FCsSoundPooled* UCsManager_Sound::AddToPool(const FECsSound& Type, UObject* Object)
{
	return Internal.AddToPool(Type, Object);
}

void UCsManager_Sound::OnAddToPool(const FECsSound& Type, const FCsSoundPooled* Object)
{
	Pool.Add(Object->GetObject());
}

#pragma endregion Pool

			// Allocated Objects
#pragma region

const FCsSoundPooled* UCsManager_Sound::AddToAllocatedObjects(const FECsSound& Type, ICsSoundPooled* Sound, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, Sound, Object);
}

const FCsSoundPooled* UCsManager_Sound::AddToAllocatedObjects(const FECsSound& Type, ICsSoundPooled* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

const FCsSoundPooled* UCsManager_Sound::AddToAllocatedObjects(const FECsSound& Type, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

#pragma endregion Allocated Objects

#pragma endregion Add

const TArray<FCsSoundPooled*>& UCsManager_Sound::GetPool(const FECsSound& Type)
{
	return Internal.GetPool(Type);
}

const TArray<FCsSoundPooled*>& UCsManager_Sound::GetAllocatedObjects(const FECsSound& Type)
{
	return Internal.GetAllocatedObjects(Type);
}

const int32& UCsManager_Sound::GetPoolSize(const FECsSound& Type)
{
	return Internal.GetPoolSize(Type);
}

int32 UCsManager_Sound::GetAllocatedObjectsSize(const FECsSound& Type)
{
	return Internal.GetAllocatedObjectsSize(Type);
}

bool UCsManager_Sound::IsExhausted(const FECsSound& Type)
{
	return Internal.IsExhausted(Type);
}

		// Find
#pragma region

const FCsSoundPooled* UCsManager_Sound::FindObject(const FECsSound& Type, const int32& Index)
{
	return Internal.FindObject(Type, Index);
}

const FCsSoundPooled* UCsManager_Sound::FindObject(const FECsSound& Type, ICsSoundPooled* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsSoundPooled* UCsManager_Sound::FindObject(const FECsSound& Type, UObject* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsSoundPooled* UCsManager_Sound::FindSafeObject(const FECsSound& Type, const int32& Index)
{
	return Internal.FindSafeObject(Type, Index);
}

const FCsSoundPooled* UCsManager_Sound::FindSafeObject(const FECsSound& Type, ICsSoundPooled* Object)
{
	return Internal.FindSafeObject(Type, Object);
}

const FCsSoundPooled* UCsManager_Sound::FindSafeObject(const FECsSound& Type, UObject* Object)
{
	return Internal.FindSafeObject(Type, Object);
}

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region

void UCsManager_Sound::Update(const FCsDeltaTime& DeltaTime)
{
	Internal.Update(DeltaTime);
}

void UCsManager_Sound::Update(const FECsUpdateGroup& Group, const FCsDeltaTime& DeltaTime)
{
	checkf(TypesByUpdateGroup[Group.GetValue()].Num() > CS_EMPTY, TEXT("UCsManager_Sound::Update: No Types associated with Group: %s."), Group.ToChar());

	for (const FECsSound& Type : TypesByUpdateGroup[Group.GetValue()])
	{
		Internal.Update(Type, DeltaTime);
	}
}

void UCsManager_Sound::Update(const FECsSound& Type, const FCsDeltaTime& DeltaTime)
{
	Internal.Update(Type, DeltaTime);
}

void UCsManager_Sound::OnPreUpdate_Pool(const FECsSound& Type)
{
	CurrentUpdatePoolType		 = Type;
	CurrentUpdatePoolObjectIndex = 0;
}

void UCsManager_Sound::OnUpdate_Object(const FECsSound& Type, const FCsSoundPooled* Object)
{
	++CurrentUpdatePoolObjectIndex;
}

void UCsManager_Sound::OnPostUpdate_Pool(const FECsSound& Type)
{
}

#pragma endregion Update

	// Pause
#pragma region

void UCsManager_Sound::Pause(const FECsUpdateGroup& Group, bool bPaused)
{
	if (bTypesByUpdateGroup)
	{
		checkf(TypesByUpdateGroup[Group.GetValue()].Num() > CS_EMPTY, TEXT("UCsManager_Sound::Update: No Types associated with Group: %s."), Group.ToChar());

		for (const FECsSound& Type : TypesByUpdateGroup[Group.GetValue()])
		{
			Internal.Pause(Type, bPaused);
		}
	}
	else
	{
		Internal.Pause(bPaused);
	}
}

void UCsManager_Sound::Pause(const FECsSound& Type, bool bPaused)
{
	Internal.Pause(Type, bPaused);
}

void UCsManager_Sound::BindToOnPause(const FECsUpdateGroup& Group)
{
	FDelegateHandle Handle = UCsManager_Time::Get(GetOuter())->GetOnPause_Event(Group).AddUObject(this, &UCsManager_Sound::Pause);

	OnPauseHandleByGroupMap.Add(Group, Handle);
}

#pragma endregion Pause

	// Payload
#pragma region

void UCsManager_Sound::ConstructPayloads(const FECsSound& Type, const int32& Size)
{
	Internal.ConstructPayloads(Type, Size);
}

PayloadType* UCsManager_Sound::ConstructPayload(const FECsSound& Type)
{
	return new PayloadImplType();
}
PayloadType* UCsManager_Sound::AllocatePayload(const FECsSound& Type)
{
	return Internal.AllocatePayload(Type);
}

#pragma endregion Payload

	// Spawn
#pragma region

const FCsSoundPooled* UCsManager_Sound::Spawn(const FECsSound& Type, PayloadType* Payload)
{
	using namespace NCsManagerSound::NCached;

	const FString& Context = Str::Spawn;

	if (Internal.IsExhausted(Type))
	{
		const FCsSoundPooled* AllocatedHead = Internal.GetAllocatedHeadObject(Type);

#if !UE_BUILD_SHIPPING
		if (UObject* Object = AllocatedHead->GetObject())
		{
			UE_LOG(LogCsSound, Warning, TEXT("UCsManager_Sound::Spawn: Deallocating object: %s as pool for Type: %s is exhausted."), *(Object->GetName()), Type.ToChar());
		}
#endif // #if !UE_BUILD_SHIPPING

		Internal.Destroy(Type, AllocatedHead);
	}

	check(PayloadLibrary::IsValidChecked(Context, Payload));

	return Internal.Spawn(Type, Payload);
}

#pragma endregion Spawn

	// Destroy
#pragma region

bool UCsManager_Sound::Destroy(const FECsSound& Type, ICsSoundPooled* Object)
{
	return Internal.Destroy(Type, Object);
}

bool UCsManager_Sound::Destroy(ICsSoundPooled* Object)
{
	return Internal.Destroy(Object);
}

#pragma endregion Destroy

	// Log
#pragma region

void UCsManager_Sound::Log(const FString& Str)
{
	UE_LOG(LogCsSound, Warning, TEXT("%s"), *Str);
}

void UCsManager_Sound::LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsSoundPooled* Object)
{
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerSoundTransactions))
	{
		const FString& TransactionAsString = EMCsPoolTransaction::Get().ToString(Transaction);

		ICsPooledObject* Interface  = Object->GetInterface();
		const FString ClassName		= Object->GetObject()->GetClass()->GetName();
		const FString ObjectName	= Object->GetObject()->GetName();
		const UObject* ObjectOwner	= Interface->GetCache()->GetOwner();
		const FString OwnerName		= ObjectOwner ? ObjectOwner->GetName() : NCsManagerSound::NCached::Str::None;
		const UObject* Parent		= Interface->GetCache()->GetParent();
		const FString ParentName	= Parent ? Parent->GetName() : NCsManagerSound::NCached::Str::None;
		const float CurrentTime		= MyRoot->GetWorld()->GetTimeSeconds();

		if (ObjectOwner && Parent)
		{
			UE_LOG(LogCsSound, Warning, TEXT("%s: %s %s of Type: %s for %s attached to %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *OwnerName, *ParentName, CurrentTime);
		}
		else 
		if (ObjectOwner)
		{
			UE_LOG(LogCsSound, Warning, TEXT("%s: %s %s of Type: %s for %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *OwnerName, CurrentTime);
		}
		else
		if (Parent)
		{
			UE_LOG(LogCsSound, Warning, TEXT("%s: %s %s of Type: %s attached to %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *ParentName, CurrentTime);
		}
		else
		{
			UE_LOG(LogCsSound, Warning, TEXT("%s: %s %s of Type: %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, CurrentTime);
		}
	}
}

#pragma endregion Log

#pragma endregion Internal

// Data
#pragma region

void UCsManager_Sound::PopulateDataMapFromSettings()
{
	using namespace NCsManagerSound;

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

				// ICsData_Projectile
				typedef NCsProperty::FLibrary PropertyLibrary;

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

void UCsManager_Sound::DeconstructData(ICsData_Sound* Data)
{
	FCsInterfaceMap* InterfaceMap = Data->GetInterfaceMap();

	checkf(InterfaceMap, TEXT("UCsManager_Sound::DeconstructData: Data failed to propertly implement method: GetInterfaceMap for interface: ICsGetInterfaceMap."));
	
	// FCsData_SoundImpl
	if (InterfaceMap->GetRootName() == FCsData_SoundImpl::Name)
	{
		delete static_cast<FCsData_SoundImpl*>(Data);
	}
	else
	{
		checkf(0, TEXT("UCsManager_Sound::DeconstructData: Failed to delete Data."));
	}
}

ICsData_Sound* UCsManager_Sound::GetData(const FName& Name)
{
	checkf(Name != NAME_None, TEXT("UCsManager_Sound::GetData: Name = None is NOT Valid."));

	ICsData_Sound** DataPtr = DataMap.Find(Name);

	checkf(DataPtr, TEXT("UCsManager_Sound::GetData: Failed to find Data for Name: %s."), *(Name.ToString()));

	return *DataPtr;
}

#pragma endregion Data