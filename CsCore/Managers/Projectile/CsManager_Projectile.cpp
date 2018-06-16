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
TWeakObjectPtr<UObject> AICsManager_Projectile::MyOwner;

// Internal
#pragma region

FCsManager_Projectile::~FCsManager_Projectile() {}

void FCsManager_Projectile::DeconstructObject(ACsProjectile* a)
{
	if (a && !a->IsPendingKill())
		a->Destroy(true);
}

FString FCsManager_Projectile::GetObjectName(ACsProjectile* a)
{
	return a->GetName();
}

const FString& FCsManager_Projectile::EnumTypeToString(const FECsProjectileType &e)
{
	return e.Name;
}

const FString& FCsManager_Projectile::EnumTypeToString(const int32 &index)
{
	return EMCsProjectileType::Get().GetEnumAt(index).Name;
}

void FCsManager_Projectile::Log_Internal(const FString& log)
{
	UE_LOG(LogCs, Warning, TEXT("%s"), *log);
}

#pragma endregion // Internal

AICsManager_Projectile::AICsManager_Projectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Internal = new FCsManager_Projectile();
	Internal->Init(TEXT("CsManager_Projectile"), TEXT("ACsProjectile"), nullptr, &CsCVarLogManagerProjectileTransactions);
	Internal->OnTick_Handle_Object.Unbind();
	Internal->OnTick_Handle_Object.BindUObject(this, &AICsManager_Projectile::OnTick_Handle_Projectile);
}

/*static*/ UObject* AICsManager_Projectile::GetMyOwner() { return MyOwner.IsValid() ? MyOwner.Get() : nullptr; }

/*static*/ void AICsManager_Projectile::Init(UObject* InOwner)
{
	MyOwner = InOwner;
}

/*static*/ AICsManager_Projectile* AICsManager_Projectile::Get(UWorld* InWorld)
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

void AICsManager_Projectile::Clear()
{
	Internal->Clear();
}

void AICsManager_Projectile::Shutdown()
{
	Clear();
	Internal->Shutdown();
	delete Internal;
}

void AICsManager_Projectile::Destroyed()
{
	Shutdown();

	Super::Destroyed();
}

ACsProjectile* AICsManager_Projectile::ConstructObject(const FECsProjectileType &Type)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags |= RF_Transient;

	ACsProjectile* Actor = GetWorld()->SpawnActor<ACsProjectile>(ACsProjectile::StaticClass(), SpawnInfo);
	Actor->SetReplicates(false);
	Actor->Role = ROLE_None;
	GetWorld()->RemoveNetworkActor(Actor);
	return Actor;
}

void AICsManager_Projectile::CreatePool(const FECsProjectileType &Type, const int32 &Size)
{
	Internal->CreatePool(Type, Size);
}

void AICsManager_Projectile::AddToPool(const FECsProjectileType &Type, ACsProjectile* Actor)
{
	Internal->AddToPool(Type, Actor);
}

void AICsManager_Projectile::AddToActivePool(const FECsProjectileType &Type, ACsProjectile* Actor)
{
	Internal->AddToActivePool(Type, Actor);
}

void AICsManager_Projectile::OnTick(const float &DeltaTime)
{
	Internal->OnTick(DeltaTime);
}

void AICsManager_Projectile::OnTick_Handle_Projectile(ACsProjectile* Projectile)
{
	// Check DrawDistance
	if (Projectile->Cache.DrawDistanceSq > 0.0f)
	{
		const float DistanceSq = UCsCommon::GetSquaredDistanceToLocalControllerEye(GetWorld(), Projectile->GetActorLocation());
		const bool Hide		   = DistanceSq > Projectile->Cache.DrawDistanceSq;

		if (Hide != Projectile->bHidden)
			Projectile->SetActorHiddenInGame(Hide);
	}
}

void AICsManager_Projectile::GetAllActiveActors(TArray<ACsProjectile*> &OutActors)
{
	Internal->GetAllActiveObjects(OutActors);
}

const TArray<class ACsProjectile*>* AICsManager_Projectile::GetActors(const FECsProjectileType& Type)
{
	return Internal->GetObjects(Type);
}

int32 AICsManager_Projectile::GetActivePoolSize(const FECsProjectileType &Type)
{
	return Internal->GetActivePoolSize(Type);
}

bool AICsManager_Projectile::IsExhausted(const FECsProjectileType &Type)
{
	return Internal->IsExhausted(Type);
}

bool AICsManager_Projectile::DeAllocate(const FECsProjectileType &Type, const int32 &Index)
{
	return Internal->DeAllocate(Type, Index);
}

void AICsManager_Projectile::DeAllocateAll()
{
	return Internal->DeAllocateAll();
}

FCsProjectilePayload* AICsManager_Projectile::AllocatePayload()
{
	return Internal->AllocatePayload();
}

ACsProjectile* AICsManager_Projectile::Fire(const FECsProjectileType &Type, FCsProjectilePayload &Payload)
{
	return Internal->Spawn(Type, &Payload);
}

ACsProjectile* AICsManager_Projectile::Fire(const FECsProjectileType &Type, FCsProjectilePayload *Payload)
{
	return Internal->Spawn(Type, Payload);
}