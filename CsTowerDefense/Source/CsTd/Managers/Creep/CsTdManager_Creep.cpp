// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Creep/CsTdManager_Creep.h"
#include "CsTd.h"
#include "CsCVars.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Creep/CsTdGetManagerCreep.h"

#include "Library/CsLibrary_Common.h"

#include "Classes/Engine/World.h"
#include "Classes/Engine/Engine.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// Internal
#pragma region

FCsTdManager_Creep_Internal::FCsTdManager_Creep_Internal()
	: Super()
{
}

#pragma endregion Internal

// static initializations
UCsTdManager_Creep* UCsTdManager_Creep::s_Instance;
bool UCsTdManager_Creep::s_bShutdown = false;

UCsTdManager_Creep::UCsTdManager_Creep(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// UObject Interface
#pragma region

void UCsTdManager_Creep::BeginDestroy()
{
	Super::BeginDestroy();

	UCsTdManager_Creep::Shutdown(this);
}

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region

void UCsTdManager_Creep::OnRegister()
{
	Super::OnRegister();

	Init(this);
}

#pragma endregion UActorComponent Interface

// Singleton
#pragma region

/*static*/ UCsTdManager_Creep* UCsTdManager_Creep::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerCreep(InRoot)->GetManager_Creep();
#else
	if (s_bShutdown)
		return nullptr;

	if (!s_Instance)
	{
		UE_LOG(LogCsTd, Warning, TEXT("UCsTdManager_Creep::Get: Manager must be attached and registered on a game object in order to call Get()."));
		return nullptr;
	}

	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsTdManager_Creep::Init(UCsTdManager_Creep* Manager)
{
	s_bShutdown = false;

	if (s_Instance)
	{
		UE_LOG(LogCsTd, Warning, TEXT("UCsTdManager_Creep::Init: This is being called before the previous instance of the manager has been Shutdown."));
	}
	s_Instance = Manager;

	s_Instance->Initialize();
}

/*static*/ void UCsTdManager_Creep::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsTdGetManagerCreep* GetManagerCreep = Get_GetManagerCreep(InRoot);
	UCsTdManager_Creep* Manager_Creep	  = GetManagerCreep->GetManager_Creep();
	Manager_Creep->CleanUp();

	GetManagerCreep->SetManager_Creep(nullptr);
#else
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsTdGetManagerCreep* UCsTdManager_Creep::Get_GetManagerCreep(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsTdManager_Creep::Get_GetManagerCreep: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsTdManager_Creep::Get_GetManagerCreep: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsTdManager_Creep::Get_GetManagerCreep: Manager_Singleton is NULL."));

	ICsTdGetManagerCreep* GetManagerCreep = Cast<ICsTdGetManagerCreep>(Manager_Singleton);

	checkf(GetManagerCreep, TEXT("UCsTdManager_Creep::Get_GetManagerCreep: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsTdGetManagerCreep."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerCreep;
}

/*static*/ ICsTdGetManagerCreep* UCsTdManager_Creep::GetSafe_GetManagerCreep(UObject* Object)
{
	if (!Object)
		return nullptr;

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
		return nullptr;

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
		return nullptr;

	return Cast<ICsTdGetManagerCreep>(Manager_Singleton);
}

/*static*/ UCsTdManager_Creep* UCsTdManager_Creep::GetSafe(UObject* Object)
{
	if (ICsTdGetManagerCreep* GetManagerCreep = GetSafe_GetManagerCreep(Object))
		return GetManagerCreep->GetManager_Creep();
	return nullptr;
}

/*static*/ UCsTdManager_Creep* UCsTdManager_Creep::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game Instance
		if (UCsTdManager_Creep* Manager = GetSafe(World->GetGameInstance()))
			return Manager;
		// Game State
		if (UCsTdManager_Creep* Manager = GetSafe(World->GetGameState()))
			return Manager;

		// Player Controller
		TArray<APlayerController*> Controllers;

		//UCsLibrary_Common::GetAllLocalPlayerControllers(World, Controllers);

		if (Controllers.Num() == CS_EMPTY)
			return nullptr;

		for (APlayerController* Controller : Controllers)
		{
			if (UCsTdManager_Creep* Manager = GetSafe(Controller))
				return Manager;
		}

		UE_LOG(LogCsTd, Warning, TEXT("UCsTdManager_Creep::GetFromWorldContextObject: Failed to Manager Item of type UCsTdManager_Creep from GameInstance, GameState, or PlayerController."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsTdManager_Creep::Initialize()
{
	SetupInternal();
}

void UCsTdManager_Creep::CleanUp()
{
	Internal.Shutdown();
	Pool.Reset();
}

#pragma endregion Singleton

// Internal
#pragma region

void UCsTdManager_Creep::SetupInternal()
{
	// Delegates
	{
		// Payload
		Internal.ConstructPayload_Impl.BindUObject(this, &UCsTdManager_Creep::ConstructPayload);
		// Update
		Internal.OnPreUpdate_Pool_Impl.BindUObject(this, &UCsTdManager_Creep::OnPreUpdate_Pool);
		Internal.OnUpdate_Object_Event.AddUObject(this, &UCsTdManager_Creep::OnUpdate_Object);
		Internal.OnPostUpdate_Pool_Impl.BindUObject(this, &UCsTdManager_Creep::OnPostUpdate_Pool);

		// Bind delegates for a script interface.
		Internal.Script_GetCache_Impl = Script_GetCache_Impl;
		Internal.Script_Allocate_Impl = Script_Allocate_Impl;
		Internal.Script_Deallocate_Impl = Script_Deallocate_Impl;
		Internal.Script_Update_Impl = Script_Update_Impl;
	}
}

void UCsTdManager_Creep::InitInternal(const FCsTdManager_Creep_Internal::FCsManagerPooledObjectMapParams& Params)
{
	Internal.Init(Params);
}

void UCsTdManager_Creep::Clear()
{
	Internal.Clear();
}

	// Pool
#pragma region

void UCsTdManager_Creep::CreatePool(const FECsTdCreep& Type, const int32& Size)
{
	// TODO: Check if the pool has already been created

	Internal.CreatePool(Type, Size);
	// TODO: Expose Payload Size somewhere
	Internal.ConstructPayloads(Type, 4);
}

FCsTdCreepPooled* UCsTdManager_Creep::ConstructContainer(const FECsTdCreep& Type)
{
	return new FCsTdCreepPooled();
}

		// Add
#pragma region

			// Pool
#pragma region

const FCsTdCreepPooled* UCsTdManager_Creep::AddToPool(const FECsTdCreep& Type, ICsTdCreep* Object)
{
	return Internal.AddToPool(Type, Object);
}

const FCsTdCreepPooled* UCsTdManager_Creep::AddToPool(const FECsTdCreep& Type, const FCsTdCreepPooled* Object)
{
	return Internal.AddToPool(Type, Object->GetObject());
}

const FCsTdCreepPooled* UCsTdManager_Creep::AddToPool(const FECsTdCreep& Type, UObject* Object)
{
	return Internal.AddToPool(Type, Object);
}

#pragma endregion Pool

			// Allocated Objects
#pragma region

const FCsTdCreepPooled* UCsTdManager_Creep::AddToAllocatedObjects(const FECsTdCreep& Type, ICsTdCreep* Creep, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, Creep, Object);
}

const FCsTdCreepPooled* UCsTdManager_Creep::AddToAllocatedObjects(const FECsTdCreep& Type, ICsTdCreep* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

const FCsTdCreepPooled* UCsTdManager_Creep::AddToAllocatedObjects(const FECsTdCreep& Type, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

#pragma endregion Allocated Objects

#pragma endregion Add

const TArray<FCsTdCreepPooled*>& UCsTdManager_Creep::GetPool(const FECsTdCreep& Type)
{
	return Internal.GetPool(Type);
}

const TArray<FCsTdCreepPooled*>& UCsTdManager_Creep::GetAllocatedObjects(const FECsTdCreep& Type)
{
	return Internal.GetAllocatedObjects(Type);
}

const int32& UCsTdManager_Creep::GetPoolSize(const FECsTdCreep& Type)
{
	return Internal.GetPoolSize(Type);
}

int32 UCsTdManager_Creep::GetAllocatedObjectsSize(const FECsTdCreep& Type)
{
	return Internal.GetAllocatedObjectsSize(Type);
}

bool UCsTdManager_Creep::IsExhausted(const FECsTdCreep& Type)
{
	return Internal.IsExhausted(Type);
}

	// Find
#pragma region

const FCsTdCreepPooled* UCsTdManager_Creep::FindObject(const FECsTdCreep& Type, const int32& Index)
{
	return Internal.FindObject(Type, Index);
}

const FCsTdCreepPooled* UCsTdManager_Creep::FindObject(const FECsTdCreep& Type, ICsTdCreep* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsTdCreepPooled* UCsTdManager_Creep::FindObject(const FECsTdCreep& Type, UObject* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsTdCreepPooled* UCsTdManager_Creep::FindSafeObject(const FECsTdCreep& Type, const int32& Index)
{
	return Internal.FindSafeObject(Type, Index);
}

const FCsTdCreepPooled* UCsTdManager_Creep::FindSafeObject(const FECsTdCreep& Type, ICsTdCreep* Object)
{
	return Internal.FindSafeObject(Type, Object);
} 

const FCsTdCreepPooled* UCsTdManager_Creep::FindSafeObject(const FECsTdCreep& Type, UObject* Object)
{
	return Internal.FindSafeObject(Type, Object);
}

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region

void UCsTdManager_Creep::Update(const FCsDeltaTime& DeltaTime)
{
	Internal.Update(DeltaTime);
}

void UCsTdManager_Creep::OnPreUpdate_Pool(const FECsTdCreep& Type)
{
	CurrentUpdatePoolType = Type;
	CurrentUpdatePoolObjectIndex = 0;
}

void UCsTdManager_Creep::OnUpdate_Object(const FECsTdCreep& Type, const FCsTdCreepPooled* Object)
{
	++CurrentUpdatePoolObjectIndex;
}

void UCsTdManager_Creep::OnPostUpdate_Pool(const FECsTdCreep& Type)
{
}

#pragma endregion Update

	// Payload
#pragma region

ICsTdCreepPayload* UCsTdManager_Creep::ConstructPayload(const FECsTdCreep& Type)
{
	return new FCsTdCreepPayload();
}

ICsTdCreepPayload* UCsTdManager_Creep::AllocatePayload(const FECsTdCreep& Type)
{
	return Internal.AllocatePayload(Type);
}

#pragma endregion Payload

	// Spawn
#pragma region

const FCsTdCreepPooled* UCsTdManager_Creep::Spawn(const FECsTdCreep& Type, ICsTdCreepPayload* Payload)
{
	return Internal.Spawn(Type, Payload);
}

#pragma endregion Spawn

	// Destroy
#pragma region

bool UCsTdManager_Creep::Destroy(const FECsTdCreep& Type, ICsTdCreep* Creep)
{
	return Internal.Destroy(Type, Creep);
}

bool UCsTdManager_Creep::Destroy(ICsTdCreep* Creep)
{
	return Internal.Destroy(Creep);
}


#pragma endregion Destroy

#pragma endregion Internal