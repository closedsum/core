// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Projectile/CsManager_Projectile.h"
#include "CsCore.h"

// Internal
#pragma region

FCsManager_Projectile_Internal::FCsManager_Projectile_Internal() 
	: Super()
{
}

const FString& FCsManager_Projectile_Internal::KeyTypeToString(const FECsProjectile& Type)
{
	return Type.Name;
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

/*static*/ UCsManager_Projectile* UCsManager_Projectile::Get()
{
	if (s_bShutdown)
		return nullptr;

	if (!s_Instance)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Projectile::Get: Manager must be attached and registered on a game object in order to call Get()."));
		return nullptr;
	}

	return s_Instance;
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

/*static*/ void UCsManager_Projectile::Shutdown()
{
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance = nullptr;
	s_bShutdown = true;
}

void UCsManager_Projectile::Initialize()
{
	ConstructInternal();
}

void UCsManager_Projectile::CleanUp()
{
	Internal->Shutdown();

	for (UObject* P : Pool)
	{
		if (P && !P->IsPendingKill())
			P->MarkPendingKill();
	}
	delete Internal;
}

#pragma endregion Singleton

// Internal
#pragma region

void UCsManager_Projectile::ConstructInternal()
{
	Internal = new FCsManager_Projectile_Internal();
}

void UCsManager_Projectile::InitInternal(const TCsManager_Internal::FCsManagerPooledObjectMapParams& Params)
{
	Internal->Init(Params);
}

void UCsManager_Projectile::Clear()
{
	Internal->Clear();
}

void UCsManager_Projectile::CreatePool(const FECsProjectile& Type, const int32& Size)
{
	Internal->CreatePool(Type, Size);
}

	// Add
#pragma region

void UCsManager_Projectile::AddToPool(const FECsProjectile& Type, ICsProjectile* Object)
{
	checkf(Object, TEXT("UCsManager_Projectile::AddToPool: Object is NULL."));

	TArray<FCsProjectile>& Projectiles = CheckAndAddType_Pools(Type);
	Projectiles.AddDefaulted();
	FCsProjectile& P = Projectiles.Last();

	P.SetProjectile(Object);

	// UObject
	if (UObject* U = Object->_getUObject())
	{
		UClass* Class = U->GetClass();

		// Check ICsPooledObject interface

			// Interface
		if (ICsPooledObject* Interface = Cast<ICsPooledObject>(U))
		{
			Internal->AddToPool(Type, Interface);

			P.SetInterface(Interface);
		}
			// Script Interface
		else
		if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
		{
			checkf(false, TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s implements a script interface of ICsPooledObject. This method does NOT support script interfaces."), *(U->GetName()), *(Class->GetName()));
		}
			// INVALID
		else
		{
			checkf(false, TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT implement interface: ICsPooledObject."), *(U->GetName()), *(Class->GetName()));
		}

		P.SetObject(U);
	}
	else
	{
#if !UE_BUILD_SHIPPING
		ICsPooledObject* Interface = dynamic_cast<ICsPooledObject*>(Object);
#else
		ICsPooledObject* Interface = (ICsPooledObject*)Object;
#endif // #if !UE_BUILD_SHIPPING

		checkf(Interface, TEXT("UCsManager_Projectile::AddToPool: Interface is NULL or does NOT implement interface: ICsPooledObject."));

		Internal->AddToPool(Type, Interface);

		P.SetInterface(Interface);
	}
}

void UCsManager_Projectile::AddToPool(const FECsProjectile& Type, FCsProjectile& Object)
{
	if (UObject* O = Object.GetObject())
	{
		UClass* Class = O->GetClass();

		// Add ICsPooledObject interface

			// Interface
		if (ICsPooledObject* Interface = Object.GetInterface())
		{
			Internal->AddToPool(Type, Interface);
		}
			// Script Interface
		else
		if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
		{
			// Check Script delegates are bound.

			//Script_GetOwner_Impl.BindStatic
			// TODO
		}
			// INVALID
		else
		{
			checkf(false, TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT implement interface: ICsPooledObject."), *(O->GetName()), *(Class->GetName()));
		}

		// Add ICsProjectile interface
		TArray<FCsProjectile>& Projectiles = CheckAndAddType_Pools(Type);
		Projectiles.AddDefaulted();
		FCsProjectile& P = Projectiles.Last();

			// Interface
		if (ICsProjectile* Projectile = Object.GetProjectile())
		{
			P.SetProjectile(Projectile);
		}
			// Script Interface
		else
		if (Class->ImplementsInterface(UCsProjectile::StaticClass()))
		{
			// Check Script delegates are bound.

			// GetOwner
			//if (!Object.Script_GetOwner_Impl.IsBound())
			//	Object.Script_GetOwner_Impl = Script_GetOwner_Impl;

			checkf(Object.Script_GetOwner_Impl.IsBound(), TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT have Script_GetOwner_Impl Bound to any function."), *(O->GetName()), *(Class->GetName()));

			// GetInstigator
			checkf(Object.Script_GetInstigator_Impl.IsBound(), TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT have Script_GetInstigator_Impl Bound to any function."), *(O->GetName()), *(Class->GetName()));

			P.SetProjectile(Projectile);
		}
			// INVALID
		else
		{
			checkf(false, TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT implement interface: ICsProjectile."), *(O->GetName()), *(Class->GetName()));
		}
	}
	else
	{
		// Add ICsPooledObject interface
		ICsPooledObject* Interface = Object.GetInterface();

		checkf(Interface, TEXT("UCsManager_Projectile::AddToPool: Interface is NULL."));

		Internal->AddToPool(Type, Interface);

		// Add ICsProjectile interface
		ICsProjectile* Projectile = Object.GetProjectile();

		checkf(Projectile, TEXT("UCsManager_Projectile::AddToPool: Projectile is NULL."));

		TArray<FCsProjectile>& Projectiles = CheckAndAddType_Pools(Type);
		Projectiles.AddDefaulted();
		FCsProjectile& P = Projectiles.Last();

		P.SetProjectile(Projectile);
	}
}

void UCsManager_Projectile::AddToPool(const FECsProjectile& Type, UObject* Object)
{
	checkf(Object, TEXT("UCsManager_Projectile::AddToPool: Object is NULL."));

	UClass* Class = Object->GetClass();

	// Add ICsPooledObject interface

		// Interface
	if (ICsPooledObject* Interface = Cast<ICsPooledObject>(Object))
	{
		Internal->AddToPool(Type, Interface);
	}
		// Script Interface
	else
	if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
	{
		checkf(false, TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s implements a script interface of type: ICsPooledObject. This method does NOT support script interfaces."), *(Object->GetName()), *(Class->GetName()));
	}
		// INVALID
	else
	{
		checkf(false, TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT implement interface: ICsPooledObject."), *(Object->GetName()), *(Class->GetName()));
	}

	// Add ICsProjectile interface
	TArray<FCsProjectile>& Projectiles = CheckAndAddType_Pools(Type);
	Projectiles.AddDefaulted();
	FCsProjectile& P = Projectiles.Last();

		// Projectile
	if (ICsProjectile* Projectile = Cast<ICsProjectile>(Object))
	{
		P.SetProjectile(Projectile);
	}
		// Script Projectile
	else
	if (Class->ImplementsInterface(UCsProjectile::StaticClass()))
	{
		checkf(false, TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s implements a script interface of ICsProjectile. This method does NOT support script interfaces."), *(Object->GetName()), *(Class->GetName()));
	}
		// INVALID
	else
	{
		checkf(false, TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT implement interface: ICsProjectile."), *(Object->GetName()), *(Class->GetName()));
	}
}

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

void UCsManager_Projectile::AddToAllocatedPool(const FECsProjectile& Type, ICsProjectile* Object)
{
	checkf(Object, TEXT("UCsManager_Projectile::AddToAllocatedPool: Object is NULL."));
		
	UObject* U		   = Object->_getUObject();
	ICsPooledObject* O = Cast<ICsPooledObject>(U);

	checkf(O, TEXT("UCsManager_Projectile::AddToAllocatedPool: Object is NULL or does NOT implement interface: ICsPooledObject."));

	Internal->AddToAllocatedPool(Type, O);
}

#pragma endregion Add

const TArray<FCsPooledObject>& UCsManager_Projectile::GetAllAllocatedObjects(const FECsProjectile& Type)
{
	return Internal->GetAllAllocatedObjects(Type);
}

const TArray<FCsPooledObject>& UCsManager_Projectile::GetObjects(const FECsProjectile& Type)
{
	return Internal->GetObjects(Type);
}

int32 UCsManager_Projectile::GetAllocatedPoolSize(const FECsProjectile& Type)
{
	return Internal->GetAllocatedPoolSize(Type);
}

bool UCsManager_Projectile::IsExhausted(const FECsProjectile& Type)
{
	return Internal->IsExhausted(Type);
}

void UCsManager_Projectile::Update(const float& DeltaTime)
{
	return Internal->Update(DeltaTime);
}

	// Payload
#pragma region

void UCsManager_Projectile::CreatePayloads(const FECsProjectile& Type, const int32& Size)
{
	Internal->DestroyPayloads(Type);

	ICsManager_PooledObject* Interface = Internal->GetPool(Type);
	FCsManager_PooledObject* P			= (FCsManager_PooledObject*)Interface;

	P->GetCreatePayloads_Impl().Unbind();
	P->GetCreatePayloads_Impl().BindRaw(P, &FCsManager_PooledObject::CreatePayloads<FCsProjectilePayload>);

	Internal->CreatePayloads(Type, Size);
}

ICsPooledObjectPayload* UCsManager_Projectile::AllocatePayload(const FECsProjectile& Type)
{
	return Internal->AllocatePayload(Type);
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

		const TArray<FCsPooledObject>& Internal_AllocatedObjects = Internal->GetAllAllocatedObjects(Type);;

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