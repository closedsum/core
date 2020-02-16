// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Projectile/CsManager_Projectile.h"
#include "CsCore.h"
#include "CsCVars.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Projectile/CsGetManagerProjectile.h"

#include "Library/CsLibrary_Common.h"

#include "Classes/Engine/World.h"
#include "Classes/Engine/Engine.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// Internal
#pragma region

FCsManager_Projectile_Internal::FCsManager_Projectile_Internal() 
	: Super()
{
}

void FCsManager_Projectile_Internal::OnAddToPool_UpdateScriptDelegates(FCsProjectilePooled* Object)
{
}

#pragma endregion Internal

// static initializations
UCsManager_Projectile* UCsManager_Projectile::s_Instance;
bool UCsManager_Projectile::s_bShutdown = false;

UCsManager_Projectile::UCsManager_Projectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// UObject Interface
#pragma region

void UCsManager_Projectile::BeginDestroy()
{
	Super::BeginDestroy();

	UCsManager_Projectile::Shutdown(this);
}

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region

void UCsManager_Projectile::OnRegister()
{
	Super::OnRegister();

	Init(this);
}

#pragma endregion UActorComponent Interface

// Singleton
#pragma region

/*static*/ UCsManager_Projectile* UCsManager_Projectile::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerProjectile(InRoot)->GetManager_Projectile();
#else
	if (s_bShutdown)
		return nullptr;

	if (!s_Instance)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Projectile::Get: Manager must be attached and registered on a game object in order to call Get()."));
		return nullptr;
	}

	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Projectile::Init(UCsManager_Projectile* Manager)
{
	s_bShutdown = false;

	if (s_Instance)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Projectile::Init: This is being called before the previous instance of the manager has been Shutdown."));
	}
	s_Instance = Manager;

	s_Instance->Initialize();
}

/*static*/ void UCsManager_Projectile::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerProjectile* GetManagerProjectile = Get_GetManagerProjectile(InRoot);
	UCsManager_Projectile* Manager_Projectile	  = GetManagerProjectile->GetManager_Projectile();
	Manager_Projectile->CleanUp();

	GetManagerProjectile->SetManager_Projectile(nullptr);
#else
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerProjectile* UCsManager_Projectile::Get_GetManagerProjectile(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Projectile::Get_GetManagerProjectile: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Projectile::Get_GetManagerProjectile: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Projectile::Get_GetManagerProjectile: Manager_Singleton is NULL."));

	ICsGetManagerProjectile* GetManagerProjectile = Cast<ICsGetManagerProjectile>(Manager_Singleton);

	checkf(GetManagerProjectile, TEXT("UCsManager_Projectile::Get_GetManagerProjectile: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerItem."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerProjectile;
}

/*static*/ ICsGetManagerProjectile* UCsManager_Projectile::GetSafe_GetManagerProjectile(UObject* Object)
{
	if (!Object)
		return nullptr;

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
		return nullptr;

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
		return nullptr;

	return Cast<ICsGetManagerProjectile>(Manager_Singleton);
}

/*static*/ UCsManager_Projectile* UCsManager_Projectile::GetSafe(UObject* Object)
{
	if (ICsGetManagerProjectile* GetManagerProjectile = GetSafe_GetManagerProjectile(Object))
		return GetManagerProjectile->GetManager_Projectile();
	return nullptr;
}

/*static*/ UCsManager_Projectile* UCsManager_Projectile::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game Instance
		if (UCsManager_Projectile* Manager = GetSafe(World->GetGameInstance()))
			return Manager;
		// Game State
		if (UCsManager_Projectile* Manager = GetSafe(World->GetGameState()))
			return Manager;

		// Player Controller
		TArray<APlayerController*> Controllers;

		//UCsLibrary_Common::GetAllLocalPlayerControllers(World, Controllers);

		if (Controllers.Num() == CS_EMPTY)
			return nullptr;

		for (APlayerController* Controller : Controllers)
		{
			if (UCsManager_Projectile* Manager = GetSafe(Controller))
				return Manager;
		}

		UE_LOG(LogCs, Warning, TEXT("UCsManager_Projectile::GetFromWorldContextObject: Failed to Manager Item of type UCsManager_Projectile from GameInstance, GameState, or PlayerController."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_Projectile::Initialize()
{
	ConstructInternal();
}

void UCsManager_Projectile::CleanUp()
{
	Internal->Shutdown();
	Pool.Reset();
	delete Internal;
}

#pragma endregion Singleton

// Internal
#pragma region

void UCsManager_Projectile::ConstructInternal()
{
	Internal = new FCsManager_Projectile_Internal();

	Internal->OnPreUpdate_Pool_Impl.BindUObject(this, &UCsManager_Projectile::OnPreUpdate_Pool);
	Internal->OnUpdate_Object_Event.AddUObject(this, &UCsManager_Projectile::OnUpdate_Object);
	Internal->OnPostUpdate_Pool_Impl.BindUObject(this, &UCsManager_Projectile::OnPostUpdate_Pool);

	// Bind delegates for a script interface.
	Internal->Script_GetCache_Impl = Script_GetCache_Impl;
	Internal->Script_Allocate_Impl = Script_Allocate_Impl;
	Internal->Script_Deallocate_Impl = Script_Deallocate_Impl;
}

void UCsManager_Projectile::InitInternal(const TCsManager_Internal::FCsManagerPooledObjectMapParams& Params)
{
	Internal->Init(Params);
}

void UCsManager_Projectile::Clear()
{
	Internal->Clear();
}

	// Pool
#pragma region

void UCsManager_Projectile::CreatePool(const FECsProjectile& Type, const int32& Size)
{
	checkf(Size > 0, TEXT("UCsManager_Projectile::CreatePool: Size must be GREATER THAN 0."));

	// TODO: Check if the pool has already been created

	Internal->CreatePool(Type, Size);
}

		// Add
#pragma region

			// Pool
#pragma region

const FCsProjectilePooled* UCsManager_Projectile::AddToPool(const FECsProjectile& Type, ICsProjectile* Object)
{
	checkf(Object, TEXT("UCsManager_Projectile::AddToPool: Object is NULL."));

	return Internal->AddToPool(Type, Object);
}

const FCsProjectilePooled* UCsManager_Projectile::AddToPool(const FECsProjectile& Type, const FCsProjectilePooled* Object)
{
	UObject* O = Object->GetObject();

	checkf(O, TEXT("UCsManager_Projectile::AddToPool: O is NULL."));

	return Internal->AddToPool(Type, O);
}

const FCsProjectilePooled* UCsManager_Projectile::AddToPool(const FECsProjectile& Type, UObject* Object)
{
	checkf(Object, TEXT("UCsManager_Projectile::AddToPool: Object is NULL."));

	return Internal->AddToPool(Type, Object);
}

#pragma endregion Pool

			// Allocated Objects
#pragma region

const FCsProjectilePooled* UCsManager_Projectile::AddToAllocatedObjects(const FECsProjectile& Type, ICsProjectile* Projectile, UObject* Object)
{
	checkf(Projectile, TEXT("UCsManager_Projectile::AddToAllocatedObjects: PooledObject is NULL."));

	checkf(Object, TEXT("UCsManager_Projectile::AddToAllocatedObjects: Object is NULL."));

	return Internal->AddToAllocatedObjects(Type, Projectile, Object);
}

const FCsProjectilePooled* UCsManager_Projectile::AddToAllocatedObjects(const FECsProjectile& Type, ICsProjectile* Object)
{
	checkf(Object, TEXT("UCsManager_Projectile::AddToAllocatedObjects: Object is NULL."));
		
	return Internal->AddToAllocatedObjects(Type, Object, Object->_getUObject());
}

const FCsProjectilePooled* UCsManager_Projectile::AddToAllocatedObjects(const FECsProjectile& Type, UObject* Object)
{
	checkf(Object, TEXT("UCsManager_Projectile::AddToAllocatedObjects: Object is NULL."));

	return Internal->AddToAllocatedObjects(Type, Object);
}

#pragma endregion Allocated Objects

#pragma endregion Add

const TArray<FCsProjectilePooled*>& UCsManager_Projectile::GetPool(const FECsProjectile& Type)
{
	return Internal->GetPool(Type);
}

const TArray<FCsProjectilePooled*>& UCsManager_Projectile::GetAllocatedObjects(const FECsProjectile& Type)
{
	return Internal->GetAllocatedObjects(Type);
}

const int32& UCsManager_Projectile::GetPoolSize(const FECsProjectile& Type)
{
	return Internal->GetPoolSize(Type);
}

int32 UCsManager_Projectile::GetAllocatedObjectsSize(const FECsProjectile& Type)
{
	return Internal->GetAllocatedObjectsSize(Type);
}

bool UCsManager_Projectile::IsExhausted(const FECsProjectile& Type)
{
	return Internal->IsExhausted(Type);
}

	// Find
#pragma region

const FCsProjectilePooled* UCsManager_Projectile::FindObject(const FECsProjectile& Type, const int32& Index)
{
	return Internal->FindObject(Type, Index);
}

const FCsProjectilePooled* UCsManager_Projectile::FindObject(const FECsProjectile& Type, ICsProjectile* Object)
{
	return Internal->FindObject(Type, Object);
}

const FCsProjectilePooled* UCsManager_Projectile::FindObject(const FECsProjectile& Type, UObject* Object)
{
	return Internal->FindObject(Type, Object);
}

const FCsProjectilePooled* UCsManager_Projectile::FindSafeObject(const FECsProjectile& Type, const int32& Index)
{
	return Internal->FindSafeObject(Type, Index);
}

const FCsProjectilePooled* UCsManager_Projectile::FindSafeObject(const FECsProjectile& Type, ICsProjectile* Object)
{
	return Internal->FindSafeObject(Type, Object);
}

const FCsProjectilePooled* UCsManager_Projectile::FindSafeObject(const FECsProjectile& Type, UObject* Object)
{
	return Internal->FindSafeObject(Type, Object);
}

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region

void UCsManager_Projectile::Update(const FCsDeltaTime& DeltaTime)
{
	Internal->Update(DeltaTime);
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

	// Payload
#pragma region

ICsProjectilePayload* UCsManager_Projectile::AllocatePayload(const FECsProjectile& Type)
{
	return Internal->AllocatePayload(Type);
}

#pragma endregion Payload

	// Spawn
#pragma region

const FCsProjectilePooled* UCsManager_Projectile::Spawn(const FECsProjectile& Type, ICsProjectilePayload* Payload)
{
	return Internal->Spawn(Type, Payload);
}

#pragma endregion Spawn

	// Destroy
#pragma region

bool UCsManager_Projectile::Destroy(const FECsProjectile& Type, ICsProjectile* Projectile)
{
	return Internal->Destroy(Type, Projectile);
}

bool UCsManager_Projectile::Destroy(ICsProjectile* Projectile)
{
	return Internal->Destroy(Projectile);
}


#pragma endregion Destroy

#pragma endregion Internal