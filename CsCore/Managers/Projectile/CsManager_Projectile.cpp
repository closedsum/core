// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsManager_Projectile.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Types/CsTypes.h"
#include "Common/CsCommon.h"
#include "Managers/Projectile/CsProjectile.h"
#include "Game/CsGameState.h"
// Data
#include "Data/CsData_Projectile.h"

// static initializations
TWeakObjectPtr<UObject> ACsManager_Projectile::MyOwner;

// Cache
#pragma region

namespace ECsManagerProjectileCachedString
{
	namespace Str
	{
		// Functions
		const FString OnTick = TEXT("ACsManager_Projectile::OnTick");
		const FString Fire = TEXT("ACsManager_Projectile::Fire");
		const FString DeAllocate = TEXT("ACsManager_Projectile::DeAllocate");
	};
}

#pragma endregion Cache

ACsManager_Projectile::ACsManager_Projectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ProjectileClass = ACsProjectile::StaticClass();
}

/*static*/ UObject* ACsManager_Projectile::GetMyOwner() { return MyOwner.IsValid() ? MyOwner.Get() : nullptr; }

/*static*/ void ACsManager_Projectile::Init(UObject* InOwner)
{
	MyOwner = InOwner;
}

/*static*/ ACsManager_Projectile* ACsManager_Projectile::Get(UWorld* InWorld)
{
#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(InWorld))
	{
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		return Cast<ACsGameState>(GetMyOwner())->Manager_Projectile;
	}
	return nullptr;
}

void ACsManager_Projectile::Clear()
{
	Super::Clear();

	Pool.Reset();
	ActiveProjectiles.Reset();
}

void ACsManager_Projectile::Shutdown()
{
	Super::Shutdown();

	const int32 Count = Pool.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (Pool[I] && !Pool[I]->IsPendingKill())
			Pool[I]->Destroy(true);
	}
	Clear();
}

void ACsManager_Projectile::Destroyed()
{
	const int32 Count = Pool.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (Pool[I] && !Pool[I]->IsPendingKill())
			Pool[I]->Destroy(true);
	}
	Clear();

	Super::Destroyed();
}

void ACsManager_Projectile::CreatePool(const TSubclassOf<class UObject> &ObjectClass, const int32 &Size)
{
	PoolSize = Size;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags |= RF_Transient;

	for (int32 I = 0; I < Size; ++I)
	{
		ACsProjectile* Projectile = GetWorld()->SpawnActor<ACsProjectile>(ObjectClass, SpawnInfo);

		Projectile->SetReplicates(false);
		Projectile->Role = ROLE_None;
		GetWorld()->RemoveNetworkActor(Projectile);
		Projectile->Init(I);
		Projectile->DeAllocate();
		Pool.Add(Projectile);
	}
}

void ACsManager_Projectile::CreatePool(const int32 &Size)
{
	CreatePool(ProjectileClass, Size);
}

void ACsManager_Projectile::OnTick(const float &DeltaSeconds)
{
	const int32 Count	 = ActiveProjectiles.Num();
	uint16 EarliestIndex = Count;

	for (int32 I = Count - 1; I >= 0; --I)
	{
		ACsProjectile* Projectile = ActiveProjectiles[I];

		// Check if Projectile was DeAllocated NOT in a normal way (i.e. Out of Bounds)
		if (!Projectile->Cache.IsAllocated)
		{
			if (Projectile->Cache.Relevance == ECsProjectileRelevance::RealVisible ||
				Projectile->Cache.Relevance == ECsProjectileRelevance::RealInvisible)
			{
				UE_LOG(LogCs, Warning, TEXT("ACsManager_Projectile::OnTick: Projectile: %s at PoolIndex: %s was prematurely deallocted NOT in a normal way."), *(Projectile->GetName()), Projectile->Cache.Index);
			}

			LogTransaction(ECsManagerProjectileCachedString::Str::OnTick, ECsPoolTransaction::Deallocate, Projectile);

			ActiveProjectiles.RemoveAt(I);

			if (I < EarliestIndex)
				EarliestIndex = I;
			continue;
		}

		if (GetWorld()->GetTimeSeconds() - Projectile->Cache.Time > Projectile->Cache.LifeTime)
		{
			LogTransaction(ECsManagerProjectileCachedString::Str::OnTick, ECsPoolTransaction::Deallocate, Projectile);

			Projectile->DeAllocate();
			ActiveProjectiles.RemoveAt(I);

			if (I < EarliestIndex)
				EarliestIndex = I;
			continue;
		}
		// Check DrawDistance
		if (Projectile->Cache.DrawDistanceSq > 0.0f)
		{
			const float DistanceSq = UCsCommon::GetSquaredDistanceToLocalControllerEye(GetWorld(), Projectile->GetActorLocation());
			const bool Hide		   = DistanceSq > Projectile->Cache.DrawDistanceSq;

			if (Hide != Projectile->bHidden)
				Projectile->SetActorHiddenInGame(Hide);
		}
	}
	// Update ActiveIndex
	if (EarliestIndex != Count)
	{
		const uint8 Max = ActiveProjectiles.Num();

		for (uint8 I = EarliestIndex; I < Max; ++I)
		{
			ACsProjectile* Projectile = ActiveProjectiles[I];
			Projectile->Cache.SetActiveIndex(I);
		}
	}
}

void ACsManager_Projectile::LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, UObject* InObject)
{
	if (CsCVarLogManagerProjectileTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		ACsProjectile* Projectile = Cast<ACsProjectile>(InObject);

		const FString TransactionAsString = ECsPoolTransaction::ToActionString(Transaction);

		const FString ProjectileName   = Projectile->GetName();
		const FString DataName		   = Projectile->Cache.GetData()->ShortCode.ToString();
		const float CurrentTime		   = GetWorld()->GetTimeSeconds();
		const UObject* ProjectileOwner = Projectile->Cache.GetOwner();
		const FString OwnerName		   = ProjectileOwner ? ProjectileOwner->GetName() : ECsCachedString::Str::None;
		const UObject* Parent		   = Projectile->Cache.GetParent();
		const FString ParentName	   = Parent ? Parent->GetName() : ECsCachedString::Str::None;
		const FString LocationAsString = Projectile->GetActorLocation().ToString();
		const FString DirectionAsString = Projectile->GetActorRotation().Vector().GetSafeNormal().ToString();

		if (ProjectileOwner && Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Projectile: %s with Data: %s at %f for %s attached to %s at %s moving at %s."), *FunctionName, *TransactionAsString, *ProjectileName, *DataName, CurrentTime, *OwnerName, *ParentName, *LocationAsString, *DirectionAsString);
		}
		else
		if (ProjectileOwner)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Projectile: %s with Data: %s at %f for %s at %s moving at %s."), *FunctionName, *TransactionAsString, *ProjectileName, *DataName, CurrentTime, *OwnerName, *LocationAsString, *DirectionAsString);
		}
		else
		if (Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Projectile: %s with Data: %s at %f attached to %s at %s moving at %s."), *TransactionAsString, *FunctionName, *ProjectileName, *DataName, CurrentTime, *ParentName, *LocationAsString, *DirectionAsString);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Projectile: %s with Data: %s at %f at %s moving at %s."), *FunctionName, *TransactionAsString, *ProjectileName, *DataName, CurrentTime, *LocationAsString, *DirectionAsString);
		}
	}
}

ACsProjectile* ACsManager_Projectile::Allocate()
{
	for (uint16 I = 0; I < PoolSize; ++I)
	{
		PoolIndex				  = (PoolIndex + I) % PoolSize;
		ACsProjectile* Projectile = Pool[PoolIndex];

		if (!Projectile->Cache.IsAllocated)
		{
			Projectile->Cache.IsAllocated = true;
			return Projectile;
		}
	}
	checkf(0, TEXT("ACsManager_Projectile::Allocate: Pool is exhausted"));
	return nullptr;
}

void ACsManager_Projectile::DeAllocate(const int32 &Index)
{
	const uint16 Count = ActiveProjectiles.Num();

	if (Count == CS_EMPTY)
		return;

	for (int32 I = Count - 1; I >= 0; --I)
	{
		ACsProjectile* Projectile = ActiveProjectiles[I];

		// Update ActiveIndex
		if (I > CS_FIRST)
		{
			Projectile->Cache.DecrementActiveIndex();
		}

		if (Projectile->Cache.Index == Index)
		{
			LogTransaction(ECsManagerProjectileCachedString::Str::DeAllocate, ECsPoolTransaction::Deallocate, Projectile);

			Projectile->DeAllocate();
			ActiveProjectiles.RemoveAt(I);
			return;
		}
	}

	// Correct on Cache "Miss"
	for (int32 I = 1; I < Count; ++I)
	{
		ACsProjectile* Projectile = ActiveProjectiles[I];
		// Reset ActiveIndex
		Projectile->Cache.SetActiveIndex(I);
	}
	UE_LOG(LogCs, Warning, TEXT("ACsManager_Projectile::DeAllocate: Projectile at PoolIndex: %d is already deallocated."), Index);
}

// Fire
#pragma region

ACsProjectile* ACsManager_Projectile::Fire(const TCsProjectileRelevance &Relevance, ACsData_Projectile* InData, FCsProjectileFireCache* Cache, UObject* InInstigator, UObject* InOwner, UObject* InParent)
{
	ACsProjectile* Projectile = Allocate();
	const int32 Count		  = ActiveProjectiles.Num();

	Projectile->Allocate((uint16)Count, Relevance, InData, Cache, InInstigator, InOwner, InParent);

	LogTransaction(ECsManagerProjectileCachedString::Str::Fire, ECsPoolTransaction::Allocate, Projectile);

	ActiveProjectiles.Add(Projectile);
	return Projectile;
}

ACsProjectile* ACsManager_Projectile::Fire(const TCsProjectileRelevance &Relevance, ACsData_Projectile* InData, FCsProjectileFireCache* Cache, UObject* InInstigator, UObject* InOwner)
{
	return Fire(Relevance, InData, Cache, InInstigator, InOwner, nullptr);
}

ACsProjectile* ACsManager_Projectile::Fire(const TCsProjectileRelevance &Relevance, ACsData_Projectile* InData, FCsProjectileFireCache* Cache)
{
	return Fire(Relevance, InData, Cache, nullptr, nullptr, nullptr);;
}

template<typename T>
void ACsManager_Projectile::Fire(ACsProjectile* OutProjectile, const TCsProjectileRelevance &Relevance, ACsData_Projectile* InData, FCsProjectileFireCache* Cache, UObject* InInstigator, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)())
{
	OutProjectile	  = Allocate();
	const int32 Count = ActiveProjectiles.Num();

	OutProjectile->Allocate((uint16)Count, Relevance, InData, Cache, InInstigator, InOwner, InParent);

	LogTransaction(ECsManagerProjectileCachedString::Str::Fire, ECsPoolTransaction::Allocate, OutProjectile);

	ActiveProjectiles.Add(OutProjectile);
}
template<typename T>
void ACsManager_Projectile::Fire(ACsProjectile* OutProjectile, const TCsProjectileRelevance &Relevance, ACsData_Projectile* InData, FCsProjectileFireCache* Cache, UObject* InInstigator, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)())
{
	Fire<T>(OutProjectile, Relevance, InData, Cache, InInstigator, InOwner, nullptr, InObject, OnDeAllocate);
}

template<typename T>
void ACsManager_Projectile::Fire(ACsProjectile* OutProjectile, const TCsProjectileRelevance &Relevance, ACsData_Projectile* InData, FCsProjectileFireCache* Cache, UObject* InInstigator, T* InObject, void (T::*OnDeAllocate)())
{
	Fire<T>(OutProjectile, Relevance, InData, Cache, InInstigator, nullptr, nullptr, InObject, OnDeAllocate);
}

#pragma endregion Fire