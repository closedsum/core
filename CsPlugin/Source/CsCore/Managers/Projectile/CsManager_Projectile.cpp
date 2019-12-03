// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Projectile/CsManager_Projectile.h"
#include "CsCore.h"

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

void UCsManager_Projectile::CreatePool(const FECsProjectile& Type, const int32& Size)
{
	checkf(Size > 0, TEXT("UCsManager_Projectile::CreatePool: Size must be GREATER THAN 0."));

	TArray<FCsProjectile>& Projectiles = Pools.FindOrAdd(Type);
	Projectiles.Reserve(Size);

	Internal->CreatePool(Type, Size);
}

	// Add
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

void UCsManager_Projectile::AddToPool(const FECsProjectile& Type, ICsProjectile* Object)
{
	checkf(Object, TEXT("UCsManager_Projectile::AddToPool: Object is NULL."));

	TArray<FCsProjectile>& Projectiles = CheckAndAddType_Pools(Type);
	Projectiles.AddDefaulted();
	FCsProjectile& P = Projectiles.Last();

	const int32 Index = Projectiles.Num() - 1;

	P.SetProjectile(Object);

	// UObject
	if (UObject* U = Object->_getUObject())
	{
		P.SetObject(U);

		UClass* Class = U->GetClass();

		// Check ICsPooledObject interface

			// Interface
		if (ICsPooledObject* Interface = Cast<ICsPooledObject>(U))
		{
			const FCsPooledObject& AddedObject = Internal->AddToPool(Type, Interface);

			checkf(Index == AddedObject.GetCache()->GetIndex(), TEXT("UCsManager_Projectile::AddToPool: Mismatch between Projectile (%d) and Pooled Object (%s)"), Index, AddedObject.GetCache()->GetIndex());

			P.SetPooledObject(AddedObject);
		}
			// Script Interface
		else
		if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
		{
			const FCsPooledObject& AddedObject =  Internal->AddToPool(Type, U);

			checkf(Index == AddedObject.GetCache()->GetIndex(), TEXT("UCsManager_Projectile::AddToPool: Mismatch between Projectile (%d) and Pooled Object (%s)"), Index, AddedObject.GetCache()->GetIndex());

			P.SetPooledObject(AddedObject);

			// Check delegates for the script interface.

			// GetCache
			checkf(Script_GetCache_Impl.IsBound(), TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT have Script_GetCache_Impl Bound to any function."), *(U->GetName()), *(Class->GetName()));
			// Allocate
			checkf(P.Script_Allocate_Impl.IsBound(), TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT have Script_Allocate_Impl Bound to any function."), *(U->GetName()), *(Class->GetName()));
			// Deallocate
			checkf(P.Script_Deallocate_Impl.IsBound(), TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT have Script_Deallocate_Impl Bound to any function."), *(U->GetName()), *(Class->GetName()));
		}
			// INVALID
		else
		{
			checkf(false, TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT implement interface: ICsPooledObject."), *(U->GetName()), *(Class->GetName()));
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

		Internal->AddToPool(Type, Interface);

		P.SetInterface(Interface);
	}
}

void UCsManager_Projectile::AddToPool(const FECsProjectile& Type, const FCsProjectile& Object)
{
	TArray<FCsProjectile>& Projectiles = CheckAndAddType_Pools(Type);
	Projectiles.AddDefaulted();
	FCsProjectile& P = Projectiles.Last();

	const int32 Index = Projectiles.Num() - 1;

	if (UObject* O = Object.GetObject())
	{
		P.SetObject(O);

		UClass* Class = O->GetClass();

		// Add ICsPooledObject interface

			// Interface
		if (ICsPooledObject* Interface = Object.GetInterface())
		{
			const FCsPooledObject& AddedObject = Internal->AddToPool(Type, Interface);

			checkf(Index == AddedObject.GetCache()->GetIndex(), TEXT("UCsManager_Projectile::AddToPool: Mismatch between Projectile (%d) and Pooled Object (%s)"), Index, AddedObject.GetCache()->GetIndex());

			P.SetPooledObject(AddedObject);
		}
			// Script Interface
		else
		if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
		{
			const FCsPooledObject& AddedObject = Internal->AddToPool(Type, O);

			checkf(Index == AddedObject.GetCache()->GetIndex(), TEXT("UCsManager_Projectile::AddToPool: Mismatch between Projectile (%d) and Pooled Object (%s)"), Index, AddedObject.GetCache()->GetIndex());

			P.SetPooledObject(AddedObject);

			// Check and bind delegates for the script interface.

			// GetCache
			checkf(P.Script_GetCache_Impl.IsBound(), TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT have Script_GetCache_Impl Bound to any function."), *(O->GetName()), *(Class->GetName()));
			// Allocate
			checkf(P.Script_Allocate_Impl.IsBound(), TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT have Script_Allocate_Impl Bound to any function."), *(O->GetName()), *(Class->GetName()));
			// Deallocate
			checkf(P.Script_Deallocate_Impl.IsBound(), TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT have Script_Deallocate_Impl Bound to any function."), *(O->GetName()), *(Class->GetName()));
		}
			// INVALID
		else
		{
			checkf(false, TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT implement interface: ICsPooledObject."), *(O->GetName()), *(Class->GetName()));
		}

		// Add ICsProjectile interface

			// Interface
		if (ICsProjectile* Projectile = Object.GetProjectile())
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

			checkf(P.Script_GetOwner_Impl.IsBound(), TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT have Script_GetOwner_Impl Bound to any function."), *(O->GetName()), *(Class->GetName()));

			// GetInstigator
			if (!P.Script_GetInstigator_Impl.IsBound())
				P.Script_GetInstigator_Impl = Script_GetInstigator_Impl;

			checkf(P.Script_GetInstigator_Impl.IsBound(), TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT have Script_GetInstigator_Impl Bound to any function."), *(O->GetName()), *(Class->GetName()));
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

		P.SetProjectile(Projectile);
	}
}

void UCsManager_Projectile::AddToPool(const FECsProjectile& Type, UObject* Object)
{
	checkf(Object, TEXT("UCsManager_Projectile::AddToPool: Object is NULL."));

	TArray<FCsProjectile>& Projectiles = CheckAndAddType_Pools(Type);
	Projectiles.AddDefaulted();
	FCsProjectile& P = Projectiles.Last();

	const int32 Index = Projectiles.Num() - 1;

	UClass* Class = Object->GetClass();

	// Add ICsPooledObject interface

		// Interface
	if (ICsPooledObject* Interface = Cast<ICsPooledObject>(Object))
	{
		const FCsPooledObject& AddedObject =  Internal->AddToPool(Type, Interface);

		checkf(Index == AddedObject.GetCache()->GetIndex(), TEXT("UCsManager_Projectile::AddToPool: Mismatch between Projectile (%d) and Pooled Object (%s)"), Index, AddedObject.GetCache()->GetIndex());

		P.SetPooledObject(AddedObject);
	}
		// Script Interface
	else
	if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
	{
		const FCsPooledObject& AddedObject =  Internal->AddToPool(Type, Object);

		checkf(Index == AddedObject.GetCache()->GetIndex(), TEXT("UCsManager_Projectile::AddToPool: Mismatch between Projectile (%d) and Pooled Object (%s)"), Index, AddedObject.GetCache()->GetIndex());

		P.SetPooledObject(AddedObject);

		// Check delegates for the script interface.

		// GetCache
		checkf(P.Script_GetCache_Impl.IsBound(), TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT have Script_GetCache_Impl Bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Allocate
		checkf(P.Script_Allocate_Impl.IsBound(), TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT have Script_Allocate_Impl Bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Deallocate
		checkf(P.Script_Deallocate_Impl.IsBound(), TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT have Script_Deallocate_Impl Bound to any function."), *(Object->GetName()), *(Class->GetName()));
	}
		// INVALID
	else
	{
		checkf(false, TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT implement interface: ICsPooledObject."), *(Object->GetName()), *(Class->GetName()));
	}

	// Add ICsProjectile interface

		// Projectile
	if (ICsProjectile* Projectile = Cast<ICsProjectile>(Object))
	{
		P.SetProjectile(Projectile);
	}
		// Script Projectile
	else
	if (Class->ImplementsInterface(UCsProjectile::StaticClass()))
	{
		P.SetScriptProjectile();

		// Check and bind delegates for the script interface.

		// GetOwner
		if (!P.Script_GetOwner_Impl.IsBound())
			P.Script_GetOwner_Impl = Script_GetOwner_Impl;

		checkf(P.Script_GetOwner_Impl.IsBound(), TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT have Script_GetOwner_Impl Bound to any function."), *(Object->GetName()), *(Class->GetName()));

		// GetInstigator
		if (!P.Script_GetInstigator_Impl.IsBound())
			P.Script_GetInstigator_Impl = Script_GetInstigator_Impl;

		checkf(P.Script_GetInstigator_Impl.IsBound(), TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT have Script_GetInstigator_Impl Bound to any function."), *(Object->GetName()), *(Class->GetName()));
	}
		// INVALID
	else
	{
		checkf(false, TEXT("UCsManager_Projectile::AddToPool: Object: %s with Class: %s does NOT implement interface: ICsProjectile."), *(Object->GetName()), *(Class->GetName()));
	}
}

void UCsManager_Projectile::OnAddToPool(const FECsProjectile& Type, const FCsPooledObject& Object)
{
	TArray<FCsProjectile>& Projectiles = Pools.FindOrAdd(Type);

	Projectiles.AddDefaulted();
	FCsProjectile& P = Projectiles.Last();

	const int32 Index = Projectiles.Num() - 1;

	checkf(Index == Object.GetCache()->GetIndex(), TEXT("UCsManager_Projectile::OnAddToPool: Mismatch between Projectile (%d) and Pooled Object (%s)"), Index, Object.GetCache()->GetIndex());

	P.SetPooledObject(Object);

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

		}
		// INVALID
		else
		{

		}
	}
}

void UCsManager_Projectile::AddToAllocatedPool(const FECsProjectile& Type, ICsProjectile* Object)
{
	checkf(Object, TEXT("UCsManager_Projectile::AddToAllocatedPool: Object is NULL."));
		
	if (UObject* U = Object->_getUObject())
	{
		if (ICsPooledObject* Interface = Cast<ICsPooledObject>(U))
		{
			const int32& Index = Interface->GetCache()->GetIndex();

			if (Index == INDEX_NONE)
			{
				AddToPool(Type, Object);

				Internal->AddToAllocatedPool(Type, Interface);

			}
			Internal->AddToAllocatedPool(Type, Interface);
		}

		//checkf(O, TEXT("UCsManager_Projectile::AddToAllocatedPool: Object is NULL or does NOT implement interface: ICsPooledObject."));
	}
}

#pragma endregion Add

const TArray<FCsPooledObject>& UCsManager_Projectile::GetAllAllocatedObjects(const FECsProjectile& Type)
{
	return Internal->GetAllAllocatedObjects(Type);
}

const TArray<FCsPooledObject>& UCsManager_Projectile::GetPool(const FECsProjectile& Type)
{
	return Internal->GetPool(Type);
}

const int32& UCsManager_Projectile::GetPoolSize(const FECsProjectile& Type)
{
	return Internal->GetPoolSize(Type);
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
	Internal->Update(DeltaTime);
}

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

		const TArray<FCsPooledObject>& Internal_AllocatedObjects = Internal->GetAllAllocatedObjects(Type);

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