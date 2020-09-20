// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Sound/CsManager_Sound.h"
#include "CsCore.h"

// CVars
#include "Managers/Sound/CsCVars_Manager_Sound.h"
// Library
#include "Library/CsLibrary_Property.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Data
#include "Managers/Sound/Data/CsData_Sound.h"
#include "Managers/Sound/Data/CsData_SoundImpl.h"
// FX
#include "Managers/Sound/Payload/CsSoundPooledPayloadImpl.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Sound/CsGetManagerSound.h"

#include "Library/CsLibrary_Common.h"

#include "Engine/World.h"
#include "Engine/Engine.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerSound
{
	namespace Str
	{
		CS_DEFINE_CACHED_STRING(PopulateDataMapFromSettings, "UCsManager_Sound::PopulateDataMapFromSettings");
	}

	namespace Name
	{
	}
}

#pragma endregion Cached

// Internal
#pragma region

FCsManager_Sound_Internal::FCsManager_Sound_Internal() 
	: Super()
{
}

#pragma endregion Internal

// static initializations
UCsManager_Sound* UCsManager_Sound::s_Instance;
bool UCsManager_Sound::s_bShutdown = false;

UCsManager_Sound::UCsManager_Sound(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsManager_Sound* UCsManager_Sound::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerSound(InRoot)->GetManager_Sound();
#else
	if (s_bShutdown)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Sound::Get: Manager has already shutdown."));
		return nullptr;
	}
	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Sound::IsValid(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerSound(InRoot)->GetManager_Sound() != nullptr;
#else
	return s_Instance != nullptr;
#endif // #if WITH_EDITOR
}

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
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Sound::Init: Init has already been called."));
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
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Sound::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
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
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Sound::Shutdown: Manager has already been shutdown."));
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

/*static*/ ICsGetManagerSound* UCsManager_Sound::Get_GetManagerSound(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Sound::Get_GetManagerSound: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Sound::Get_GetManagerSound: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Sound::Get_GetManagerSound: Manager_Singleton is NULL."));

	ICsGetManagerSound* GetManagerSound = Cast<ICsGetManagerSound>(Manager_Singleton);

	checkf(GetManagerSound, TEXT("UCsManager_Sound::Get_GetManagerSound: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerSound."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerSound;
}

/*static*/ ICsGetManagerSound* UCsManager_Sound::GetSafe_GetManagerSound(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Sound::GetSafe_GetManagerSound: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Sound::GetSafe_GetManagerSound: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Sound::GetSafe_GetManagerSound: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetManagerSound>(Manager_Singleton);
}

/*static*/ UCsManager_Sound* UCsManager_Sound::GetSafe(UObject* Object)
{
	if (ICsGetManagerSound* GetManagerSound = GetSafe_GetManagerSound(Object))
		return GetManagerSound->GetManager_Sound();
	return nullptr;
}

/*static*/ UCsManager_Sound* UCsManager_Sound::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game State
		if (UCsManager_Sound* Manager = GetSafe(World->GetGameState()))
			return Manager;

		UE_LOG(LogCs, Warning, TEXT("UCsManager_Sound::GetFromWorldContextObject: Failed to Manager FX Actor of type UCsManager_Sound from GameState."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
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
	Internal.Shutdown();
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
		// If any settings have been set for Manager_Creep, apply them
	{
		UCsDeveloperSettings* ModuleSettings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(ModuleSettings, TEXT("UCsManager_Sound::SetupInternal: Failed to get settings of type: UCsDeveloperSettings."));

		Settings = ModuleSettings->Manager_Sound;

		InitInternalFromSettings();
	}
}

void UCsManager_Sound::InitInternalFromSettings()
{
	PopulateDataMapFromSettings();

	if (Settings.PoolParams.Num() > CS_EMPTY)
	{
		FCsManager_Sound_Internal::FCsManagerPooledObjectMapParams Params;

		Params.Name  = TEXT("UCsManager_Sound::FCsManager_Sound_Internal");
		Params.World = MyRoot->GetWorld();

		for (const TPair<FECsSound, FCsSettings_Manager_Sound_PoolParams>& Pair : Settings.PoolParams)
		{
			const FECsSound& Type								   = Pair.Key;
			const FCsSettings_Manager_Sound_PoolParams& PoolParams = Pair.Value;

			FCsManagerPooledObjectParams& ObjectParams = Params.ObjectParams.Add(Type);

			checkf(PoolParams.Class.ToSoftObjectPath().IsValid(), TEXT("UCsManager_Sound::InitInternalFromSettings: Class for Type: %s is NOT a Valid Path."), Type.ToChar());

#if !UE_BUILD_SHIPPING
			if (!PoolParams.Class.Get())
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Sound::InitInternalFromSettings: Class @ for Type: %s is NOT already loaded in memory."), *(PoolParams.Class.ToString()), Type.ToChar());
			}
#endif // #if !UE_BUILD_SHIPPING

			UClass* Class = PoolParams.Class.LoadSynchronous();

			checkf(Class, TEXT("UCsManager_Sound::InitInternalFromSettings: Failed to load Class @ for Type: %s."), *(PoolParams.Class.ToString()), Type.ToChar());

			ClassMap.Add(Type, Class);

			ObjectParams.Name							  = Params.Name + TEXT("_") + Type.ToChar();
			ObjectParams.World							  = Params.World;
			ObjectParams.ConstructParams.Outer			  = this;
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

void UCsManager_Sound::InitInternal(const FCsManager_Sound_Internal::FCsManagerPooledObjectMapParams& Params)
{
	// Add CVars
	{
		FCsManager_Sound_Internal::FCsManagerPooledObjectMapParams& P = const_cast<FCsManager_Sound_Internal::FCsManagerPooledObjectMapParams&>(Params);

		for (TPair<FECsSound, FCsManagerPooledObjectParams>& Pair : P.ObjectParams)
		{
			FCsManagerPooledObjectParams& ObjectParams = Pair.Value;

			// Scoped Timer CVars
			ObjectParams.ScopedGroup = NCsScopedGroup::ManagerSound;

			ObjectParams.CreatePoolScopedTimerCVar		= NCsCVarLog::LogManagerSoundScopedTimerCreatePool;
			ObjectParams.UpdateScopedTimerCVar			= NCsCVarLog::LogManagerSoundScopedTimerUpdate;
			ObjectParams.UpdateObjectScopedTimerCVar	= NCsCVarLog::LogManagerSoundScopedTimerUpdateObject;
			ObjectParams.AllocateScopedTimerCVar		= NCsCVarLog::LogManagerSoundScopedTimerAllocate;
			ObjectParams.AllocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerSoundScopedTimerAllocateObject;
			ObjectParams.DeallocateScopedTimerCVar		= NCsCVarLog::LogManagerSoundScopedTimerDeallocate;
			ObjectParams.DeallocateObjectScopedTimerCVar = NCsCVarLog::LogManagerSoundScopedTimerDeallocateObject;
			ObjectParams.SpawnScopedTimerCVar			= NCsCVarLog::LogManagerSoundScopedTimerSpawn;
			ObjectParams.DestroyScopedTimerCVar			= NCsCVarLog::LogManagerSoundScopedTimerDestroy;
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
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Sound::CreatePool: Pool for Sound: %s has already been created with Size: %d."), Type.ToChar(), PoolSize);
	}

	Internal.CreatePool(Type, Size);
}

TBaseDelegate<FCsSoundPooled*, const FECsSound&>& UCsManager_Sound::GetConstructContainer_Impl()
{
	return Internal.ConstructContainer_Impl;
}

FCsSoundPooled* UCsManager_Sound::ConstructContainer(const FECsSound& Type)
{
	return new FCsSoundPooled();
}

TMulticastDelegate<void, const FCsSoundPooled*, const FCsManagerPooledObjectConstructParams&>& UCsManager_Sound::GetOnConstructObject_Event(const FECsSound& Type)
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

	// Payload
#pragma region

void UCsManager_Sound::ConstructPayloads(const FECsSound& Type, const int32& Size)
{
	Internal.ConstructPayloads(Type, Size);
}

ICsSoundPooledPayload* UCsManager_Sound::ConstructPayload(const FECsSound& Type)
{
	return new FCsSoundPooledPayloadImpl();
}

ICsSoundPooledPayload* UCsManager_Sound::AllocatePayload(const FECsSound& Type)
{
	return Internal.AllocatePayload(Type);
}

/*
ICsFXPooledPayload* UCsManager_FX_Actor::ScriptAllocatePayload(const FECsSound& Type, const FCsScriptProjectilePayload& ScriptPayload)
{
	ICsPayload_Projectile* IP				= Internal.AllocatePayload(Type);
	FCsPayload_ProjectilePooledImpl* Payload = static_cast<FCsPayload_ProjectilePooledImpl*>(IP);

	Payload->Instigator = ScriptPayload.Instigator;
	Payload->Owner		= ScriptPayload.Owner;
	Payload->Parent		= ScriptPayload.Parent;
	Payload->Direction	= ScriptPayload.Direction;
	Payload->Location	= ScriptPayload.Location;

	return IP;
}
*/

#pragma endregion Payload

	// Spawn
#pragma region

const FCsSoundPooled* UCsManager_Sound::Spawn(const FECsSound& Type, ICsSoundPooledPayload* Payload)
{
	if (Internal.IsExhausted(Type))
	{
		const FCsSoundPooled* AllocatedHead = Internal.GetAllocatedHeadObject(Type);

#if !UE_BUILD_SHIPPING
		if (UObject* Object = AllocatedHead->GetObject())
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Sound::Spawn: Deallocating object: %s as pool for Type: %s is exhausted."), *(Object->GetName()), Type.ToChar());
		}
#endif // #if !UE_BUILD_SHIPPING

		Internal.Destroy(Type, AllocatedHead);
	}
	return Internal.Spawn(Type, Payload);
}

/*
const FCsFXActorPooled* UCsManager_FX_Actor::ScriptSpawn(const FECsProjectile& Type, const FCsScriptProjectilePayload& ScriptPayload)
{
	ICsPayload_Projectile* Payload = ScriptAllocatePayload(Type, ScriptPayload);

	return Spawn(Type, Payload);
}
*/

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
	UE_LOG(LogCs, Warning, TEXT("%s"), *Str);
}

void UCsManager_Sound::LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsSoundPooled* Object)
{
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSoundTransactions))
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

void UCsManager_Sound::PopulateDataMapFromSettings()
{
	using namespace NCsManagerSound;

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