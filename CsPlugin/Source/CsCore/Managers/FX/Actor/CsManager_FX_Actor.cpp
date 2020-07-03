// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/FX/Actor/CsManager_FX_Actor.h"
#include "CsCore.h"

// CVars
#include "Managers/FX/Actor/CsCVars_Manager_FX_Actor.h"
// Library
#include "Library/CsLibrary_Property.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Data
#include "Managers/FX/Data/CsData_FX.h"
#include "Managers/FX/Data/CsData_FXImpl.h"
// FX
#include "Managers/FX/Payload/CsFXPooledPayloadImpl.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/FX/Actor/CsGetManagerFXActor.h"

#include "Library/CsLibrary_Common.h"

#include "Classes/Engine/World.h"
#include "Classes/Engine/Engine.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerFXActor
{
	namespace Str
	{
		const FString PopulateDataMapFromSettings = TEXT("UCsManager_FX_Actor::PopulateDataMapFromSettings");
	}

	namespace Name
	{
	}
}

#pragma endregion Cached

// Internal
#pragma region

FCsManager_FX_Actor_Internal::FCsManager_FX_Actor_Internal() 
	: Super()
{
}

#pragma endregion Internal

// static initializations
UCsManager_FX_Actor* UCsManager_FX_Actor::s_Instance;
bool UCsManager_FX_Actor::s_bShutdown = false;

UCsManager_FX_Actor::UCsManager_FX_Actor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsManager_FX_Actor* UCsManager_FX_Actor::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerFXActor(InRoot)->GetManager_FX_Actor();
#else
	if (s_bShutdown)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::Get: Manager has already shutdown."));
		return nullptr;
	}
	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_FX_Actor::IsValid(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerFXActor(InRoot)->GetManager_FX_Actor() != nullptr;
#else
	return s_Instance != nullptr;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_FX_Actor::Init(UObject* InRoot, TSubclassOf<UCsManager_FX_Actor> ManagerFXActorClass, UObject* InOuter /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerFXActor* GetManagerFXActor = Get_GetManagerFXActor(InRoot);

	UCsManager_FX_Actor* Manager_FX_Actor = GetManagerFXActor->GetManager_FX_Actor();

	if (!Manager_FX_Actor)
	{
		Manager_FX_Actor = NewObject<UCsManager_FX_Actor>(InOuter ? InOuter : InRoot, ManagerFXActorClass, TEXT("Manager_FX_Actor_Singleton"), RF_Transient | RF_Public);

		GetManagerFXActor->SetManager_FX_Actor(Manager_FX_Actor);

		Manager_FX_Actor->SetMyRoot(InRoot);
		Manager_FX_Actor->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_FX_Actor>(GetTransientPackage(), ManagerFXActorClass, TEXT("Manager_FX_Actor_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_FX_Actor::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerFXActor* GetManagerFXActor = Get_GetManagerFXActor(InRoot);
	UCsManager_FX_Actor* Manager_FX_Actor	= GetManagerFXActor->GetManager_FX_Actor();
	Manager_FX_Actor->CleanUp();

	GetManagerFXActor->SetManager_FX_Actor(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::Shutdown: Manager has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_FX_Actor::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerFXActor(InRoot)->GetManager_FX_Actor() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerFXActor* UCsManager_FX_Actor::Get_GetManagerFXActor(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_FX_Actor::Get_GetManagerProjectile: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_FX_Actor::Get_GetManagerFXActor: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_FX_Actor::Get_GetManagerFXActor: Manager_Singleton is NULL."));

	ICsGetManagerFXActor* GetManagerFXActor = Cast<ICsGetManagerFXActor>(Manager_Singleton);

	checkf(GetManagerFXActor, TEXT("UCsManager_FX_Actor::Get_GetManagerFXActor: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerFXActor."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerFXActor;
}

/*static*/ ICsGetManagerFXActor* UCsManager_FX_Actor::GetSafe_GetManagerFXActor(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::GetSafe_GetManagerFXActor: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::GetSafe_GetManagerFXActor: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::GetSafe_GetManagerFXActor: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetManagerFXActor>(Manager_Singleton);
}

/*static*/ UCsManager_FX_Actor* UCsManager_FX_Actor::GetSafe(UObject* Object)
{
	if (ICsGetManagerFXActor* GetManagerFXActor = GetSafe_GetManagerFXActor(Object))
		return GetManagerFXActor->GetManager_FX_Actor();
	return nullptr;
}

/*static*/ UCsManager_FX_Actor* UCsManager_FX_Actor::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game State
		if (UCsManager_FX_Actor* Manager = GetSafe(World->GetGameState()))
			return Manager;

		UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::GetFromWorldContextObject: Failed to Manager FX Actor of type UCsManager_FX_Actor from GameState."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_FX_Actor::Initialize()
{
	SetupInternal();
}

void UCsManager_FX_Actor::CleanUp()
{
	Internal.Shutdown();
	Pool.Reset();

	for (TPair<FName, ICsData_FX*>& Pair : DataMap)
	{
		ICsData_FX* Data = Pair.Value;
		DeconstructData(Data);
		Pair.Value = nullptr;
	}
	DataMap.Reset();
}

	// Root
#pragma region

void UCsManager_FX_Actor::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// Internal
#pragma region

void UCsManager_FX_Actor::SetupInternal()
{
	// Delegates
	{
		// Log
		Internal.LogTransaction_Impl.BindUObject(this, &UCsManager_FX_Actor::LogTransaction);
		// Container
		Internal.ConstructContainer_Impl.BindUObject(this, &UCsManager_FX_Actor::ConstructContainer);
		// Payload
		Internal.ConstructPayload_Impl.BindUObject(this, &UCsManager_FX_Actor::ConstructPayload);
		// Pool
		Internal.OnAddToPool_Event.AddUObject(this, &UCsManager_FX_Actor::OnAddToPool);
		// Update
		Internal.OnPreUpdate_Pool_Impl.BindUObject(this, &UCsManager_FX_Actor::OnPreUpdate_Pool);
		Internal.OnUpdate_Object_Event.AddUObject(this, &UCsManager_FX_Actor::OnUpdate_Object);
		Internal.OnPostUpdate_Pool_Impl.BindUObject(this, &UCsManager_FX_Actor::OnPostUpdate_Pool);

		// Bind delegates for a script interface.
		Internal.Script_GetCache_Impl = Script_GetCache_Impl;
		Internal.Script_Allocate_Impl = Script_Allocate_Impl;
		Internal.Script_Deallocate_Impl = Script_Deallocate_Impl;
		Internal.Script_Update_Impl = Script_Update_Impl;
		Internal.Script_OnConstructObject_Impl = Script_OnConstructObject_Impl;
	}
#if !UE_BUILD_SHIPPING
	//if (FCsCVarToggleMap::Get().IsEnabled(NCsCVarToggle::EnableManagerFXActorUnitTest))
	//{
		// Do Nothing
	//}
	//else
#endif // #if !UE_BUILD_SHIPPING
		// If any settings have been set for Manager_Creep, apply them
	{
		UCsDeveloperSettings* ModuleSettings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(ModuleSettings, TEXT("UCsManager_FX_Actor::SetupInternal: Failed to get settings of type: UCsDeveloperSettings."));

		Settings = ModuleSettings->Manager_FX_Actor;

		InitInternalFromSettings();
	}
}

void UCsManager_FX_Actor::InitInternalFromSettings()
{
#if WITH_EDITOR
	if (Settings.Payload == NAME_None)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::InitInternalFromSettings: No Payload specified in settings. Storing hard references on manager."));
	}
#else
	checkf(Settings.Payload != NAME_None, TEXT("UCsManager_FX_Actor::InitInternalFromSettings: No Payload specified in settings."));
#endif // #if WITH_EDITOR

	PopulateDataMapFromSettings();

	if (Settings.PoolParams.Num() > CS_EMPTY)
	{
		FCsManager_FX_Actor_Internal::FCsManagerPooledObjectMapParams Params;

		Params.Name  = TEXT("UCsManager_FX_Actor::FCsManager_FX_Actor_Internal");
		Params.World = MyRoot->GetWorld();

		for (const TPair<FECsFX, FCsSettings_Manager_FX_Actor_PoolParams>& Pair : Settings.PoolParams)
		{
			const FECsFX& Type										  = Pair.Key;
			const FCsSettings_Manager_FX_Actor_PoolParams& PoolParams = Pair.Value;

			FCsManagerPooledObjectParams& ObjectParams = Params.ObjectParams.Add(Type);

			checkf(PoolParams.Class.ToSoftObjectPath().IsValid(), TEXT("UCsManager_FX_Actor::InitInternalFromSettings: Class for Type: %s is NOT a Valid Path."), *(Type.Name));

#if !UE_BUILD_SHIPPING
			if (!PoolParams.Class.Get())
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::InitInternalFromSettings: Class @ for Type: %s is NOT already loaded in memory."), *(PoolParams.Class.ToString()), *(Type.Name));
			}
#endif // #if !UE_BUILD_SHIPPING

			UClass* Class = PoolParams.Class.LoadSynchronous();

			checkf(Class, TEXT("UCsManager_FX_Actor::InitInternalFromSettings: Failed to load Class @ for Type: %s."), *(PoolParams.Class.ToString()), *(Type.Name));

			ClassMap.Add(Type, Class);

			ObjectParams.Name  = Params.Name + TEXT("_") + Type.Name;
			ObjectParams.World = Params.World;
			//ObjectParams.LogType
			ObjectParams.ConstructParams.Outer			  = this;
			ObjectParams.ConstructParams.Class			  = Class;
			ObjectParams.ConstructParams.ConstructionType = ECsPooledObjectConstruction::Object;
			ObjectParams.bConstructPayloads				  = true;
			ObjectParams.PayloadSize					  = PoolParams.PayloadSize;
			ObjectParams.bCreatePool					  = true;
			ObjectParams.PoolSize						  = PoolParams.PoolSize;
		}

		InitInternal(Params);
	}
}

void UCsManager_FX_Actor::InitInternal(const FCsManager_FX_Actor_Internal::FCsManagerPooledObjectMapParams& Params)
{
	Internal.Init(Params);
}

void UCsManager_FX_Actor::Clear()
{
	Internal.Clear();
}

	// Pool
#pragma region

void UCsManager_FX_Actor::CreatePool(const FECsFX& Type, const int32& Size)
{
	const int32& PoolSize = Internal.GetPoolSize(Type);

	if (PoolSize > CS_EMPTY)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_FX_Actor::CreatePool: Pool for Creep: %s has already been created with Size: %d."), *(Type.Name), PoolSize);
	}

	Internal.CreatePool(Type, Size);
}

TBaseDelegate<FCsFXActorPooled*, const FECsFX&>& UCsManager_FX_Actor::GetConstructContainer_Impl()
{
	return Internal.ConstructContainer_Impl;
}

FCsFXActorPooled* UCsManager_FX_Actor::ConstructContainer(const FECsFX& Type)
{
	return new FCsFXActorPooled();
}

TMulticastDelegate<void, const FCsFXActorPooled*>& UCsManager_FX_Actor::GetOnConstructObject_Event(const FECsFX& Type)
{
	return Internal.GetOnConstructObject_Event(Type);
}

		// Add
#pragma region

			// Pool
#pragma region

const FCsFXActorPooled* UCsManager_FX_Actor::AddToPool(const FECsFX& Type, ICsFXActorPooled* Object)
{
	return Internal.AddToPool(Type, Object);
}

const FCsFXActorPooled* UCsManager_FX_Actor::AddToPool(const FECsFX& Type, const FCsFXActorPooled* Object)
{
	return Internal.AddToPool(Type, Object->GetObject());
}

const FCsFXActorPooled* UCsManager_FX_Actor::AddToPool(const FECsFX& Type, UObject* Object)
{
	return Internal.AddToPool(Type, Object);
}

void UCsManager_FX_Actor::OnAddToPool(const FECsFX& Type, const FCsFXActorPooled* Object)
{
	Pool.Add(Object->GetObject());
}

#pragma endregion Pool

			// Allocated Objects
#pragma region

const FCsFXActorPooled* UCsManager_FX_Actor::AddToAllocatedObjects(const FECsFX& Type, ICsFXActorPooled* Projectile, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, Projectile, Object);
}

const FCsFXActorPooled* UCsManager_FX_Actor::AddToAllocatedObjects(const FECsFX& Type, ICsFXActorPooled* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

const FCsFXActorPooled* UCsManager_FX_Actor::AddToAllocatedObjects(const FECsFX& Type, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

#pragma endregion Allocated Objects

#pragma endregion Add

const TArray<FCsFXActorPooled*>& UCsManager_FX_Actor::GetPool(const FECsFX& Type)
{
	return Internal.GetPool(Type);
}

const TArray<FCsFXActorPooled*>& UCsManager_FX_Actor::GetAllocatedObjects(const FECsFX& Type)
{
	return Internal.GetAllocatedObjects(Type);
}

const int32& UCsManager_FX_Actor::GetPoolSize(const FECsFX& Type)
{
	return Internal.GetPoolSize(Type);
}

int32 UCsManager_FX_Actor::GetAllocatedObjectsSize(const FECsFX& Type)
{
	return Internal.GetAllocatedObjectsSize(Type);
}

bool UCsManager_FX_Actor::IsExhausted(const FECsFX& Type)
{
	return Internal.IsExhausted(Type);
}

	// Find
#pragma region

const FCsFXActorPooled* UCsManager_FX_Actor::FindObject(const FECsFX& Type, const int32& Index)
{
	return Internal.FindObject(Type, Index);
}

const FCsFXActorPooled* UCsManager_FX_Actor::FindObject(const FECsFX& Type, ICsFXActorPooled* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsFXActorPooled* UCsManager_FX_Actor::FindObject(const FECsFX& Type, UObject* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsFXActorPooled* UCsManager_FX_Actor::FindSafeObject(const FECsFX& Type, const int32& Index)
{
	return Internal.FindSafeObject(Type, Index);
}

const FCsFXActorPooled* UCsManager_FX_Actor::FindSafeObject(const FECsFX& Type, ICsFXActorPooled* Object)
{
	return Internal.FindSafeObject(Type, Object);
}

const FCsFXActorPooled* UCsManager_FX_Actor::FindSafeObject(const FECsFX& Type, UObject* Object)
{
	return Internal.FindSafeObject(Type, Object);
}

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region

void UCsManager_FX_Actor::Update(const FCsDeltaTime& DeltaTime)
{
	Internal.Update(DeltaTime);
}

void UCsManager_FX_Actor::OnPreUpdate_Pool(const FECsFX& Type)
{
	CurrentUpdatePoolType		 = Type;
	CurrentUpdatePoolObjectIndex = 0;
}

void UCsManager_FX_Actor::OnUpdate_Object(const FECsFX& Type, const FCsFXActorPooled* Object)
{
	++CurrentUpdatePoolObjectIndex;
}

void UCsManager_FX_Actor::OnPostUpdate_Pool(const FECsFX& Type)
{
}

#pragma endregion Update

	// Payload
#pragma region

void UCsManager_FX_Actor::ConstructPayloads(const FECsFX& Type, const int32& Size)
{
	Internal.ConstructPayloads(Type, Size);
}

ICsFXPooledPayload* UCsManager_FX_Actor::ConstructPayload(const FECsFX& Type)
{
	return new FCsFXPooledPayloadImpl();
}

ICsFXPooledPayload* UCsManager_FX_Actor::AllocatePayload(const FECsFX& Type)
{
	return Internal.AllocatePayload(Type);
}

/*
ICsFXPooledPayload* UCsManager_FX_Actor::ScriptAllocatePayload(const FECsFX& Type, const FCsScriptProjectilePayload& ScriptPayload)
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
*/

#pragma endregion Payload

	// Spawn
#pragma region

const FCsFXActorPooled* UCsManager_FX_Actor::Spawn(const FECsFX& Type, ICsFXPooledPayload* Payload)
{
	return Internal.Spawn(Type, Payload);
}

/*
const FCsFXActorPooled* UCsManager_FX_Actor::ScriptSpawn(const FECsProjectile& Type, const FCsScriptProjectilePayload& ScriptPayload)
{
	ICsProjectilePayload* Payload = ScriptAllocatePayload(Type, ScriptPayload);

	return Spawn(Type, Payload);
}
*/

#pragma endregion Spawn

	// Destroy
#pragma region

bool UCsManager_FX_Actor::Destroy(const FECsFX& Type, ICsFXActorPooled* Object)
{
	return Internal.Destroy(Type, Object);
}

bool UCsManager_FX_Actor::Destroy(ICsFXActorPooled* Object)
{
	return Internal.Destroy(Object);
}

#pragma endregion Destroy

	// Log
#pragma region

void UCsManager_FX_Actor::LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsFXActorPooled* Object)
{
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerFXActorTransactions))
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

void UCsManager_FX_Actor::PopulateDataMapFromSettings()
{
	using namespace NCsManagerFXActor;

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

void UCsManager_FX_Actor::DeconstructData(ICsData_FX* Data)
{
	FCsInterfaceMap* InterfaceMap = Data->GetInterfaceMap();

	checkf(InterfaceMap, TEXT("UCsManager_FX_Actor::DeconstructData: Data failed to propertly implement method: GetInterfaceMap for interface: ICsGetInterfaceMap."));
	
	// FCsData_FXImpl
	if (InterfaceMap->GetRootName() == FCsData_FXImpl::Name)
	{
		delete static_cast<FCsData_FXImpl*>(Data);
	}
	else
	{
		checkf(0, TEXT("UCsManager_FX_Actor::DeconstructData: Failed to delete Data."));
	}
}

ICsData_FX* UCsManager_FX_Actor::GetData(const FName& Name)
{
	checkf(Name != NAME_None, TEXT("UCsManager_FX_Actor::GetData: Name = None is NOT Valid."));

	ICsData_FX** DataPtr = DataMap.Find(Name);

	checkf(DataPtr, TEXT("UCsManager_FX_Actor::GetData: Failed to find Data for Name: %s."), *(Name.ToString()));

	return *DataPtr;
}

#pragma endregion Data