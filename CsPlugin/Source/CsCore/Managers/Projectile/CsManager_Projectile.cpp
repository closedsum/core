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

	Internal->OnAddToPool_Event.AddUObject(this, &UCsManager_Projectile::OnAddToPool);
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

void UCsManager_Projectile::AddToPool(const FECsProjectile& Type, ICsProjectile* Object)
{
	checkf(Object, TEXT("UCsManager_Projectile::AddToPool: Object is NULL."));

	UObject* U		   = Object->_getUObject();
	ICsPooledObject* O = Cast<ICsPooledObject>(U);

	checkf(O, TEXT("UCsManager_Projectile::AddToPool: Object is NULL or does NOT implement interface: ICsPooledObject."));

	Internal->AddToPool(Type, O);
}

TArray<FCsProjectile>& UCsManager_Projectile::CheckAndAddType_Pools(const FECsProjectile& Type)
{
	TArray<FCsProjectile>* ValuePtr = Pools.Find(Type);

	if (!ValuePtr)
	{
		TArray<FCsProjectile>& Value = Pools.Add(Type);
		ActiveObjects.Add(Type);
		return Value;
	}
	return *ValuePtr;
}

void UCsManager_Projectile::OnAddToPool(const FECsProjectile& Type, const FCsPooledObject& Object)
{
	TArray<FCsProjectile>& Projectiles = CheckAndAddType_Pools(Type);
	Projectiles.AddDefaulted();
	FCsProjectile& P = Projectiles.Last();

	ICsPooledObject* Interface = Object.GetInterface();

	P.SetInterface(Interface);
#if !UE_BUILD_SHIPPING
	ICsProjectile* IP = Object.IsObject() ? Object.GetSafeObject<ICsProjectile>() : dynamic_cast<ICsProjectile*>(Interface);
#else
	ICsProjectile* IP = Object.IsObject() ? Object.GetSafeObject<ICsProjectile>() : (ICsProjectile*)Interface;
#endif // #if !UE_BUILD_SHIPPING

	checkf(IP, TEXT("UCsManager_Projectile::OnAddToPool: Object does NOT implement interface: ICsProjectile."));

	P.SetProjectile(IP);
	P.SetObject(Object.GetSafeObject());
}

void UCsManager_Projectile::AddToActivePool(const FECsProjectile& Type, ICsProjectile* Object)
{
	checkf(Object, TEXT("UCsManager_Projectile::AddToActivePool: Object is NULL."));
		
#if !UE_BUILD_SHIPPING
	ICsPooledObject* O = dynamic_cast<ICsPooledObject*>(Object);
#else
	IRsPooledObject* O = (IRsPooledObject*)Object;
#endif // #if !UE_BUILD_SHIPPING

	checkf(O, TEXT("UCsManager_Projectile::AddToActivePool: Object is NULL or does NOT implement interface: ICsPooledObject."));

	Internal->AddToActivePool(Type, O);
}

const TArray<FCsPooledObject>& UCsManager_Projectile::GetAllActiveObjects(const FECsProjectile& Type)
{
	return Internal->GetAllActiveObjects(Type);
}

const TArray<FCsPooledObject>& UCsManager_Projectile::GetObjects(const FECsProjectile& Type)
{
	return Internal->GetObjects(Type);
}

int32 UCsManager_Projectile::GetActivePoolSize(const FECsProjectile& Type)
{
	return Internal->GetActivePoolSize(Type);
}

bool UCsManager_Projectile::IsExhausted(const FECsProjectile& Type)
{
	return Internal->IsExhausted(Type);
}

void UCsManager_Projectile::OnTick(const float &DeltaTime)
{
	return Internal->OnTick(DeltaTime);
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

	ActiveObjects[Type].Add(P);

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
		// Remove from ActiveObjects

		TArray<FCsProjectile>& Projectiles = Pools[Type];

		const int32& ProjectileIndex = O->GetCache()->GetIndex();
		const FCsProjectile& P		 = Projectiles[ProjectileIndex];

		// Rebuild ActiveObjects from Internal ActiveObjects

		TArray<FCsProjectile>& Objects = ActiveObjects[Type];

		const int32 OldSize = Objects.Num();

		const TArray<FCsPooledObject>& Internal_ActiveObjects = Internal->GetAllActiveObjects(Type);;

		const int32 NewSize = Internal_ActiveObjects.Num();

		for (int32 I = 0; I <= NewSize; ++I)
		{
			const FCsPooledObject& Container = Internal_ActiveObjects[I];
			ICsPooledObject* Interface		 = Container.GetInterface();
			const int32& Index				 = Interface->GetCache()->GetIndex();

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