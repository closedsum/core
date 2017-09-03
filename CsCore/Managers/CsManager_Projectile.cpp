// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/CsManager_Projectile.h"
#include "CsCore.h"
#include "CsTypes.h"
#include "Weapon/CsProjectile.h"
// Data
#include "Data/CsData_Projectile.h"

ACsManager_Projectile::ACsManager_Projectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PoolSize = CS_PROJECTILE_POOL_SIZE;
	ProjectileClass = ACsProjectile::StaticClass();
}

void ACsManager_Projectile::PostActorCreated()
{
}

void ACsManager_Projectile::OnTick(const float &DeltaSeconds)
{
	const uint16 Count = ActiveProjectiles.Num();

	for (int32 I = Count - 1; I >= 0; I--)
	{
		ACsProjectile* Projectile = ActiveProjectiles[I];

		if (GetWorld()->TimeSeconds - Projectile->Cache.Time > Projectile->Cache.Duration)
		{
			Projectile->DeAllocate();
			ActiveProjectiles.RemoveAt(I);
		}
	}
}

void ACsManager_Projectile::CreatePool(const int32 &Size)
{
	PoolSize = Size;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags					|= RF_Transient;

	for (int32 I = 0; I < Size; I++)
	{
		ACsProjectile* Projectile = GetWorld()->SpawnActor<ACsProjectile>(ProjectileClass, SpawnInfo);

		//Projectile->IsActive = false;
		//Projectile->IsInPool = true;
		//Projectile->DeActivate();

		Projectile->SetReplicates(false);
		Projectile->Role = ROLE_None;
		GetWorld()->RemoveNetworkActor(Projectile);

		//ProjectilePool.Add(Projectile);
		//ProjectilesToDeActivate.Add(Projectile);

		//while (ProjectilesToDeActivate.Num() > 0)
		//	OnTick_HandleProjectilesToDeActivate();

		Pool[I] = Projectile;
	}
}

ACsProjectile* ACsManager_Projectile::Allocate(const TCsProjectileType &Type)
{
	for (uint16 I = 0; I < PoolSize; ++I)
	{
		PoolIndex				  = (PoolIndex + I) % PoolSize;
		ACsProjectile* Projectile = Pool[PoolIndex];

		if (!Projectile->Cache.IsAllocated)
		{
			Projectile->Cache.IsAllocated = true;
			Projectile->Cache.Type		  = Type;
			return Projectile;
		}
	}
	checkf(0, TEXT("ACsManager_Projectile::Allocate: Pool is exhausted"));
	return nullptr;
}

void ACsManager_Projectile::DeAllocate(const int32 &Index)
{
	const uint16 Count = ActiveProjectiles.Num();

	for (int32 I = Count - 1; I >= 0; I--)
	{
		ACsProjectile* Projectile = ActiveProjectiles[I];

		if (Projectile->PoolIndex == Index)
		{
			Projectile->DeAllocate();
			ActiveProjectiles.RemoveAt(I);
			return;
		}
	}
}

ACsProjectile* ACsManager_Projectile::Fire(ACsData_Projectile* InData, const FCsProjectileFireCache* Cache, UObject* InInstigator, UObject* InOwner, UObject* InParent)
{
	// Real
	ACsProjectile* RealProjectile = Allocate(ECsProjectileType::Real);
	RealProjectile->Allocate(InData, Cache, InInstigator, InOwner, InParent);
	ActiveProjectiles.Add(RealProjectile);
	
	// Fake
	ACsProjectile* FakeProjectile = Allocate(ECsProjectileType::Fake);
	FakeProjectile->Allocate(InData, Cache, InInstigator, InOwner, InParent);
	ActiveProjectiles.Add(FakeProjectile);

	RealProjectile->FakeProjectile = FakeProjectile;

	return RealProjectile;
}

ACsProjectile* ACsManager_Projectile::Fire(ACsData_Projectile* InData, const FCsProjectileFireCache* Cache, UObject* InInstigator, UObject* InOwner)
{
	return nullptr;
}

ACsProjectile* ACsManager_Projectile::Fire(ACsData_Projectile* InData, const FCsProjectileFireCache* Cache)
{
	return nullptr;
}

ACsProjectile* ACsManager_Projectile::Fire(ACsData_Projectile* InData, const FCsProjectileFireCache* Cache, UObject* InInstigator, UObject* InOwner, const FVector &Location)
{
	return nullptr;
}
/*
template<typename T>
ACsProjectile* ACsManager_Projectile::Fire(ACsData_Projectile* InData, const FCsProjectileFireCache* Cache, UObject* InInstigator, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)())
{
	InObject = nullptr;
	return nullptr;
}
template<typename T>
ACsProjectile* ACsManager_Projectile::Fire(ACsData_Projectile* InData, const FCsProjectileFireCache* Cache, UObject* InInstigator, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)())
{
	return nullptr;
}

template<typename T>
ACsProjectile* ACsManager_Projectile::Fire(ACsData_Projectile* InData, const FCsProjectileFireCache* Cache, UObject* InInstigator, T* InObject, void (T::*OnDeAllocate)())
{
	return nullptr;
}
template<typename T>
ACsProjectile* ACsManager_Projectile::Fire(ACsData_Projectile* InData, const FCsProjectileFireCache* Cache, UObject* InInstigator, UObject* InOwner, const FVector &Location, T* InObject, void (T::*OnDeAllocate)())
{
	return nullptr;
}
*/