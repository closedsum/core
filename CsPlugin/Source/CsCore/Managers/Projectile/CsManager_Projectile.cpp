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

	UCsManager_Projectile::Shutdown();
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

		UCsLibrary_Common::GetAllLocalPlayerControllers(World, Controllers);

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

	Internal->OnCreatePool_AddToPool_Event.AddUObject(this, &UCsManager_Projectile::OnCreatePool_AddToPool);
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

	TArray<FCsProjectile>& Projectiles = Pools.FindOrAdd(Type);
	Projectiles.Reserve(Size);
	TArray<FCsProjectile>& Objects = AllocatedObjects.FindOrAdd(Type);
	Objects.Reserve(Size);

	Internal->CreatePool(Type, Size);
}

void UCsManager_Projectile::OnCreatePool_AddToPool(const FECsProjectile& Type, const FCsPooledObject& Object)
{
	AddToPool_Internal(Type, Object);
}

		// Add
#pragma region

			// Pool
#pragma region

TArray<FCsProjectile>& UCsManager_Projectile::CheckAndAddType_Pools(const FECsProjectile& Type)
{
	TArray<FCsProjectile>* ValuePtr = Pools.Find(Type);

	if (!ValuePtr)
	{
		TArray<FCsProjectile>& Value = Pools.Add(Type);
		AllocatedObjects.Add(Type);
		return Value;
	}
	return *ValuePtr;
}

const FCsProjectile& UCsManager_Projectile::AddToPool(const FECsProjectile& Type, ICsProjectile* Object)
{
	checkf(Object, TEXT("UCsManager_Projectile::AddToPool: Object is NULL."));

	// UObject
	if (UObject* O = Object->_getUObject())
	{
		UClass* Class = O->GetClass();

		// Check ICsPooledObject interface

			// Interface
		if (ICsPooledObject* Interface = Cast<ICsPooledObject>(O))
		{
			const FCsPooledObject& PooledObject =  Internal->AddToPool(Type, Interface, O);

			return AddToPool_Internal(Type, PooledObject);
		}
			// Script Interface
		else
		if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
		{
			const FCsPooledObject& PooledObject = Internal->AddToPool(Type, O);

			return AddToPool_Internal(Type, PooledObject);
		}
			// INVALID
		else
		{
			checkf(false, TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT implement interface: ICsPooledObject."), *(O->GetName()), *(Class->GetName()));
		}
	}
	else
	{
#if !UE_BUILD_SHIPPING
		ICsPooledObject* Interface = dynamic_cast<ICsPooledObject*>(Object);
#else
		ICsPooledObject* Interface = (ICsPooledObject*)Object;
#endif // #if !UE_BUILD_SHIPPING

		checkf(Interface, TEXT("UCsManager_Projectile::AddToPool: Interface is NULL or does NOT implement interface: ICsPooledObject."));

		const FCsPooledObject& PooledObject = Internal->AddToPool(Type, Interface);

		return AddToPool_Internal(Type, PooledObject);
	}
	return FCsProjectile::Empty;
}

const FCsProjectile& UCsManager_Projectile::AddToPool(const FECsProjectile& Type, const FCsProjectile& Object)
{
	if (UObject* O = Object.GetObject())
	{
		UClass* Class = O->GetClass();

		// Add ICsPooledObject interface

			// Interface
		if (ICsPooledObject* Interface = Object.GetInterface())
		{
			const FCsPooledObject& PooledObject = Internal->AddToPool(Type, Interface, O);

			return AddToPool_Internal(Type, PooledObject);
		}
			// Script Interface
		else
		if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
		{
			const FCsPooledObject& PooledObject = Internal->AddToPool(Type, O);

			return AddToPool_Internal(Type, PooledObject);
		}
			// INVALID
		else
		{
			checkf(false, TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT implement interface: ICsPooledObject."), *(O->GetName()), *(Class->GetName()));
		}
	}
	else
	{
		// Add ICsPooledObject interface
		ICsPooledObject* Interface = Object.GetInterface();

		checkf(Interface, TEXT("UCsManager_Projectile::AddToPool: Interface is NULL."));

		const FCsPooledObject& PooledObject = Internal->AddToPool(Type, Interface);

		return AddToPool_Internal(Type, PooledObject);
	}
	return FCsProjectile::Empty;
}

const FCsProjectile& UCsManager_Projectile::AddToPool(const FECsProjectile& Type, UObject* Object)
{
	checkf(Object, TEXT("UCsManager_Projectile::AddToPool: Object is NULL."));

	UClass* Class = Object->GetClass();

	// Add ICsPooledObject interface

		// Interface
	if (ICsPooledObject* Interface = Cast<ICsPooledObject>(Object))
	{
		const FCsPooledObject& O = Internal->AddToPool(Type, Interface);

		return AddToPool_Internal(Type, O);
	}
		// Script Interface
	else
	if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
	{
		const FCsPooledObject& O = Internal->AddToPool(Type, Object);

		return AddToPool_Internal(Type, O);
	}
		// INVALID
	else
	{
		checkf(false, TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT implement interface: ICsPooledObject."), *(Object->GetName()), *(Class->GetName()));
	}
	return FCsProjectile::Empty;
}

const FCsProjectile& UCsManager_Projectile::AddToPool_Internal(const FECsProjectile& Type, const FCsPooledObject& Object)
{
	TArray<FCsProjectile>& Projectiles = CheckAndAddType_Pools(Type);

	Projectiles.AddDefaulted();
	FCsProjectile& P = Projectiles.Last();

	const int32 Index = Projectiles.Num() - 1;

	checkf(Index == Object.GetCache()->GetIndex(), TEXT("UCsManager_Projectile::OnAddToPool: Mismatch between Projectile (%d) and Pooled Object (%s)"), Index, Object.GetCache()->GetIndex());

	P.SetPooledObject(Object);

	// UObject
	if (UObject* O = P.GetObject())
	{
		UClass* Class = O->GetClass();

		// Interface
		if (ICsProjectile* Projectile = Cast<ICsProjectile>(O))
		{
			P.SetProjectile(Projectile);
		}
		// Script Interface
		else
		if (Class->ImplementsInterface(UCsProjectile::StaticClass()))
		{
			P.SetScriptProjectile();

			// Check and bind delegates for the script interface.

			// GetOwner
			if (!P.Script_GetOwner_Impl.IsBound())
				P.Script_GetOwner_Impl = Script_GetOwner_Impl;

			checkf(P.Script_GetOwner_Impl.IsBound(), TEXT("UCsManager_Projectile::OnAddToPool: Object: %s with Class: %s does NOT have Script_GetOwner_Impl Bound to any function."), *(O->GetName()), *(Class->GetName()));

			// GetInstigator
			if (!P.Script_GetInstigator_Impl.IsBound())
				P.Script_GetInstigator_Impl = Script_GetInstigator_Impl;

			checkf(P.Script_GetInstigator_Impl.IsBound(), TEXT("UCsManager_Projectile::OnAddToPool: Object: %s with Class: %s does NOT have Script_GetInstigator_Impl Bound to any function."), *(O->GetName()), *(Class->GetName()));
		}
		// INVALID
		else
		{
			checkf(false, TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT implement interface: ICsProjectile."), *(O->GetName()), *(Class->GetName()));
		}
	}
	else
	{
		ICsPooledObject* Interface = Object.GetInterface();

#if !UE_BUILD_SHIPPING
		ICsProjectile* Projectile = dynamic_cast<ICsProjectile*>(Interface);
#else
		ICsProjectile* Projectile = (ICsProjectile*)Interface;
#endif // #if !UE_BUILD_SHIPPING

		checkf(Projectile, TEXT("UCsManager_Projectile::OnAddToPool: Projectile is NULL or does NOT implement interface: ICsProjectile."));

		P.SetProjectile(Projectile);
	}
	return P;
}

#pragma endregion Pool

			// Allocated Objects
#pragma region

TArray<FCsProjectile>& UCsManager_Projectile::CheckAndAddType_AllocatedObjects(const FECsProjectile& Type)
{
	TArray<FCsProjectile>* ValuePtr = AllocatedObjects.Find(Type);

	if (!ValuePtr)
	{
		Pools.Add(Type);
		TArray<FCsProjectile>& Value = AllocatedObjects.Add(Type);
		return Value;
	}
	return *ValuePtr;
}

const FCsProjectile& UCsManager_Projectile::AddToAllocatedObjects(const FECsProjectile& Type, ICsProjectile* PooledObject, UObject* Object)
{
	checkf(PooledObject, TEXT("UCsManager_Projectile::AddToAllocatedObjects: PooledObject is NULL."));

	checkf(Object, TEXT("UCsManager_Projectile::AddToAllocatedObjects: Object is NULL."));

	UClass* Class = Object->GetClass();

	// Interface
	if (ICsPooledObject* Interface = Cast<ICsPooledObject>(Object))
	{
		const FCsPooledObject& O = Internal->AddToAllocatedObjects(Type, Interface, Object);

		return AddToAllocatedObjects_Internal(Type, O);
	}
	// Script Interface
	else
	if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
	{
		const FCsPooledObject& O = Internal->AddToAllocatedObjects(Type, Object);

		return AddToAllocatedObjects_Internal(Type, O);
	}
	else
	{
#if !UE_BUILD_SHIPPING
		ICsPooledObject* InterfaceObject = dynamic_cast<ICsPooledObject*>(PooledObject);
#else
		ICsPooledObject* InterfaceObject = (ICsPooledObject*)PooledObject;
#endif // #if !UE_BUILD_SHIPPING

		checkf(InterfaceObject, TEXT("UCsManager_Projectile::AddToAllocatedObjects: InterfaceObject is NULL or does NOT implement interface: ICsPooledObject."));

		const FCsPooledObject& O = Internal->AddToAllocatedObjects(Type, InterfaceObject);

		return AddToAllocatedObjects_Internal(Type, O);
	}
	return FCsProjectile::Empty;
}

const FCsProjectile& UCsManager_Projectile::AddToAllocatedObjects(const FECsProjectile& Type, ICsProjectile* Object)
{
	checkf(Object, TEXT("UCsManager_Projectile::AddToAllocatedObjects: Object is NULL."));
		
	if (UObject* O = Object->_getUObject())
	{
		UClass* Class = O->GetClass();

		// Interface
		if (ICsPooledObject* Interface = Cast<ICsPooledObject>(O))
		{
			const FCsPooledObject& PooledObject = Internal->AddToAllocatedObjects(Type, Interface, O);

			return AddToAllocatedObjects_Internal(Type, PooledObject);
		}
		// Script Interface
		else
		if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
		{
			const FCsPooledObject& PooledObject = Internal->AddToAllocatedObjects(Type, O);

			return AddToAllocatedObjects_Internal(Type, PooledObject);
		}
		// INVALID
		else
		{
			checkf(false, TEXT("UCsManager_Projectile::AddToAllocatedObjects: Object does NOT implement interface: ICsPooledObject."));
		}
	}
	else
	{
#if !UE_BUILD_SHIPPING
		ICsPooledObject* InterfaceObject = dynamic_cast<ICsPooledObject*>(Object);
#else
		ICsPooledObject* InterfaceObject = (ICsPooledObject*)Object;
#endif // #if !UE_BUILD_SHIPPING

		checkf(InterfaceObject, TEXT("UCsManager_Projectile::AddToAllocatedObjects: InterfaceObject is NULL or does NOT implement interface: ICsPooledObject."));

		const FCsPooledObject& PooledObject = Internal->AddToAllocatedObjects(Type, InterfaceObject);

		return AddToAllocatedObjects_Internal(Type, PooledObject);
	}
	return FCsProjectile::Empty;
}

const FCsProjectile& UCsManager_Projectile::AddToAllocatedObjects(const FECsProjectile& Type, UObject* Object)
{
	checkf(Object, TEXT("UCsManager_Projectile::AddToAllocatedObjects: Object is NULL."));

	UClass* Class = Object->GetClass();

	// Interface
	if (ICsPooledObject* Interface = Cast<ICsPooledObject>(Object))
	{
		const FCsPooledObject& O = Internal->AddToAllocatedObjects(Type, Interface, Object);

		return AddToAllocatedObjects_Internal(Type, O);
	}
	// Script Interface
	else
	if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
	{
		const FCsPooledObject& O = Internal->AddToAllocatedObjects(Type, Object);

		return AddToAllocatedObjects_Internal(Type, O);
	}
	else
	{
		checkf(false, TEXT("UCsManager_Projectile::AddToAllocatedObjects: Object does NOT implement interface: ICsPooledObject."));
	}
	return FCsProjectile::Empty;
}

const FCsProjectile& UCsManager_Projectile::AddToAllocatedObjects_Internal(const FECsProjectile& Type, const FCsPooledObject& Object)
{
	TArray<FCsProjectile>& Objects = CheckAndAddType_AllocatedObjects(Type);

	Objects.AddDefaulted();
	FCsProjectile& O = Objects.Last();

	const int32& Index = Object.GetCache()->GetIndex();

	O = Pools[Type][Index];

	return O;
}

#pragma endregion Allocated Objects

#pragma endregion Add

const TArray<FCsProjectile>& UCsManager_Projectile::GetPool(const FECsProjectile& Type)
{
	return CheckAndAddType_AllocatedObjects(Type);
}

const TArray<FCsProjectile>& UCsManager_Projectile::GetAllocatedObjects(const FECsProjectile& Type)
{
	return CheckAndAddType_Pools(Type);
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

const FCsProjectile& UCsManager_Projectile::FindObject(const FECsProjectile& Type, const int32& Index)
{
	const FCsPooledObject& O = Internal->FindObject(Type, Index);

	return CheckAndAddType_Pools(Type)[Index];
}

const FCsProjectile& UCsManager_Projectile::FindObject(const FECsProjectile& Type, ICsProjectile* Object)
{
	if (UObject* U = Object->_getUObject())
	{
		UClass* Class = U->GetClass();

		// Interface
		if (ICsPooledObject* Interface = Cast<ICsPooledObject>(U))
		{
			const FCsPooledObject& O = Internal->FindObject(Type, Interface);

			return FindObject_Internal(Type, O);
		}
		// Script Interface
		else
		if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
		{
			const FCsPooledObject& O = Internal->FindObject(Type, U);

			return FindObject_Internal(Type, O);
		}
		// INVALID
		else
		{
			checkf(false, TEXT("UCsManager_Projectile::FindObject: Object: %s with Class: %s does NOT implement interface: ICsPooledObject."), *(U->GetName()), *(Class->GetName()));
		}
	}
	else
	{
#if !UE_BUILD_SHIPPING
		ICsPooledObject* Interface = dynamic_cast<ICsPooledObject*>(Object);
#else
		ICsPooledObject* Interface = (ICsPooledObject*)Object;
#endif // #if !UE_BUILD_SHIPPING

		checkf(Interface, TEXT("UCsManager_Projectile::FindObject: Object does NOT implement interface: ICsPooledObject."));

		const FCsPooledObject& O = Internal->FindObject(Type, Interface);

		return FindObject_Internal(Type, O);
	}
	return FCsProjectile::Empty;
}

const FCsProjectile& UCsManager_Projectile::FindObject(const FECsProjectile& Type, UObject* Object)
{
	const FCsPooledObject& O = Internal->FindObject(Type, Object);
	const int32& Index		 = O.GetCache()->GetIndex();

	return CheckAndAddType_Pools(Type)[Index];
}

const FCsProjectile& UCsManager_Projectile::FindObject_Internal(const FECsProjectile& Type, const FCsPooledObject& Object)
{
	const int32& Index = Object.GetCache()->GetIndex();

	return CheckAndAddType_Pools(Type)[Index];
}

const FCsProjectile& UCsManager_Projectile::FindSafeObject(const FECsProjectile& Type, const int32& Index)
{
	if (Index < 0)
		return FCsProjectile::Empty;

	const FCsPooledObject& O = Internal->FindSafeObject(Type, Index);

	if (!O.IsValid())
		return FCsProjectile::Empty;

	TArray<FCsProjectile>& Projectiles = CheckAndAddType_Pools(Type);

	if (Index >= Projectiles.Num())
		return FCsProjectile::Empty;

	return Projectiles[Index];
}

const FCsProjectile& UCsManager_Projectile::FindSafeObject(const FECsProjectile& Type, ICsProjectile* Object)
{
	if (!Object)
		return FCsProjectile::Empty;

	if (UObject* U = Object->_getUObject())
	{
		UClass* Class = U->GetClass();

		// Interface
		if (ICsPooledObject* Interface = Cast<ICsPooledObject>(U))
		{
			const FCsPooledObject& O = Internal->FindObject(Type, Interface);

			return FindSafeObject_Internal(Type, O);
		}
		// Script Interface
		else
		if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
		{
			const FCsPooledObject& O = Internal->FindObject(Type, U);

			return FindSafeObject_Internal(Type, O);
		}
		// INVALID
		else
		{
			return FCsProjectile::Empty;
		}
	}
	else
	{
#if !UE_BUILD_SHIPPING
		ICsPooledObject* Interface = dynamic_cast<ICsPooledObject*>(Object);
#else
		ICsPooledObject* Interface = (ICsPooledObject*)Object;
#endif // #if !UE_BUILD_SHIPPING

		if (!Interface)
			return FCsProjectile::Empty;

		const FCsPooledObject& O = Internal->FindObject(Type, Interface);

		return FindSafeObject_Internal(Type, O);
	}
	return FCsProjectile::Empty;
}

const FCsProjectile& UCsManager_Projectile::FindSafeObject(const FECsProjectile& Type, UObject* Object)
{
	if (!Object)
		return FCsProjectile::Empty;

	const FCsPooledObject& O = Internal->FindObject(Type, Object);

	return FindSafeObject_Internal(Type, O);
}

const FCsProjectile& UCsManager_Projectile::FindSafeObject_Internal(const FECsProjectile& Type, const FCsPooledObject& Object)
{
	if (!Object.IsValid())
		return FCsProjectile::Empty;

	const int32& Index = Object.GetCache()->GetIndex();

	TArray<FCsProjectile>& Projectiles = CheckAndAddType_Pools(Type);

	if (Index >= Projectiles.Num())
		return FCsProjectile::Empty;

	return Projectiles[Index];
}

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region

void UCsManager_Projectile::Update(const float& DeltaTime)
{
	Internal->Update(DeltaTime);
}

void UCsManager_Projectile::OnPreUpdate_Pool(const FECsProjectile& Type)
{
	CurrentUpdatePoolType = Type;
	CurrentUpdatePoolObjectIndex = 0;
}

void UCsManager_Projectile::OnUpdate_Object(const FECsProjectile& Type, const FCsPooledObject& Object)
{
	const int32& Index = Object.GetCache()->GetIndex();

	TArray<FCsProjectile>& Projectiles = AllocatedObjects[Type];

	Projectiles[CurrentUpdatePoolObjectIndex] = Projectiles[Index];

	++CurrentUpdatePoolObjectIndex;
}

void UCsManager_Projectile::OnPostUpdate_Pool(const FECsProjectile& Type)
{
	TArray<FCsProjectile>& Projectiles = AllocatedObjects[Type];
	const int32 ProjectilesSize		   = Projectiles.Num();

	for (int32 I = ProjectilesSize - 1; I >= CurrentUpdatePoolObjectIndex; --I)
	{
		Projectiles.RemoveAt(I, 1, false);
	}
}

#pragma endregion Update

	// Payload
#pragma region

void UCsManager_Projectile::ConstructPayloads(const FECsProjectile& Type, const int32& Size)
{
	Internal->DeconstructPayloads(Type);

	ICsManager_PooledObject* Interface = Internal->GetManagerPooledObjects(Type);
	FCsManager_PooledObject* P		   = (FCsManager_PooledObject*)Interface;

	P->GetConstructPayloads_Impl().Unbind();
	P->GetConstructPayloads_Impl().BindRaw(P, &FCsManager_PooledObject::ConstructPayloads<FCsProjectilePayload>);

	Internal->ConstructPayloads(Type, Size);
}

FCsProjectilePayload* UCsManager_Projectile::AllocatePayload(const FECsProjectile& Type)
{
	return Internal->AllocatePayload<FCsProjectilePayload>(Type);
}

#pragma endregion Payload

	// Spawn
#pragma region

const FCsProjectile& UCsManager_Projectile::Spawn(const FECsProjectile& Type, ICsPooledObjectPayload* Payload)
{
	checkf(Payload, TEXT("UCsManager_Projectile::Spawn: Payload is NULL."));

	const FCsPooledObject& Object = Internal->Spawn(Type, Payload);

	ICsPooledObject* Interface = Object.GetInterface();
	const int32& Index		   = Interface->GetCache()->GetIndex();

	TArray<FCsProjectile>& Projectiles = Pools[Type];
	const FCsProjectile& P			   = Projectiles[Index];

	AllocatedObjects[Type].Add(P);

	OnSpawn_Event.Broadcast(Type, P);

	if (OnSpawn_ScriptEvent.IsBound() &&
		P.IsObject())
	{
		OnSpawn_ScriptEvent.Broadcast(Type, TScriptInterface<ICsProjectile>(P.GetSafeObject()));
	}
	return P;
}

#pragma endregion Spawn

	// Destroy
#pragma region

bool UCsManager_Projectile::Destroy(const FECsProjectile& Type, ICsProjectile* Projectile)
{
	checkf(EMCsProjectile::Get().IsValidEnum(Type), TEXT("UCsManager_Projectile::Destroy: Type: %s is NOT a valid Enum."), *(Type.Name));
	
	checkf(Projectile, TEXT("UCsManager_Projectile::Destroy: Projectile is NULL."));

#if !UE_BUILD_SHIPPING
	ICsPooledObject* O = dynamic_cast<ICsPooledObject*>(Projectile);
#else
	ICsPooledObject* O = (ICsPooledObject*)Projectile;
#endif // #if !UE_BUILD_SHIPPING

	checkf(O, TEXT("UCsManager_Projectile::Destroy: Projectile is NULL or does NOT implement interface: ICsPooledObject."));

	if (Internal->Destroy(Type, O))
	{
		// Remove from AllocatedObjects

		TArray<FCsProjectile>& Projectiles = Pools[Type];

		const int32& ProjectileIndex = O->GetCache()->GetIndex();
		const FCsProjectile& P		 = Projectiles[ProjectileIndex];

		// Rebuild AllocatedObjects from Internal AllocatedObjects

		TArray<FCsProjectile>& Objects = AllocatedObjects[Type];

		const int32 OldSize = Objects.Num();

		const TArray<FCsPooledObject>& Internal_AllocatedObjects = Internal->GetAllocatedObjects(Type);

		const int32 NewSize = Internal_AllocatedObjects.Num();

		for (int32 I = 0; I <= NewSize; ++I)
		{
			const FCsPooledObject& Container = Internal_AllocatedObjects[I];
			const int32& Index				 = Container.GetCache()->GetIndex();

			Objects[I] = Projectiles[Index];
		}

		for (int32 I = OldSize - 1; I >= NewSize; --I)
		{
			Objects.RemoveAt(I, 1, false);
		}
		OnDestroy_Event.Broadcast(Type, P);
		return true;
	}
	return false;
}

bool UCsManager_Projectile::Destroy(ICsProjectile* Projectile)
{
	checkf(Projectile, TEXT("UCsManager_Projectile::Destroy: Projectile is NULL."));

#if !UE_BUILD_SHIPPING
	ICsPooledObject* O = dynamic_cast<ICsPooledObject*>(Projectile);
#else
	ICsPooledObject* O = (ICsPooledObject*)Projectile;
#endif // #if !UE_BUILD_SHIPPING

	checkf(O, TEXT("UCsManager_Projectile::Destroy: Projectile is NULL or does NOT implement interface: ICsPooledObject."));

	const int32& Index = O->GetCache()->GetIndex();

	bool TypeFound = false;

	for (TPair<FECsProjectile, TArray<FCsProjectile>>& Pair : Pools)
	{
		const FECsProjectile& Type		   = Pair.Key;
		TArray<FCsProjectile>& Projectiles = Pair.Value;

		if (Index >= Projectiles.Num())
			continue;

		for (FCsProjectile& P : Projectiles)
		{
			ICsPooledObject* Interface = P.GetInterface();
			
			if (Index == Interface->GetCache()->GetIndex())
			{
				return Destroy(Type, P.GetProjectile());
			}
		}
	}
	return false;
}


#pragma endregion Destroy

#pragma endregion Internal