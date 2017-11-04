// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsProjectile.h"
#include "CsCore.h"
#include "GameFramework/ProjectileMovementComponent.h"
// Data
#include "Data/CsData_Projectile.h"

#define CS_COLLISION_PROJECTILE	ECC_GameTraceChannel2

ACsProjectile::ACsProjectile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Collision Component
	CollisionComponent = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComponent->AlwaysLoadOnClient  = true;
	CollisionComponent->AlwaysLoadOnServer  = true;
	CollisionComponent->bTraceComplexOnMove = true;
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionComponent->SetCollisionObjectType(CS_COLLISION_PROJECTILE);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->bGenerateOverlapEvents = false;
	CollisionComponent->bReturnMaterialOnMove  = true;
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	CollisionComponent->PrimaryComponentTick.bStartWithTickEnabled = false;

	// Players can't walk on it
	CollisionComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComponent->CanCharacterStepUpOn = ECB_No;

	CollisionComponent->Deactivate();

	RootComponent = CollisionComponent;

	// Movement Component
	MovementComponent = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent							  = nullptr;// CollisionComponent;
	MovementComponent->InitialSpeed								  = 1.f;
	MovementComponent->MaxSpeed									  = 1.f;
	MovementComponent->bRotationFollowsVelocity					  = true;
	MovementComponent->MaxSimulationIterations					  = 1;
	MovementComponent->PrimaryComponentTick.bStartWithTickEnabled = false;
	MovementComponent->Deactivate();

	// Mesh Component
	MeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeshComponent->SetCastShadow(false);
	MeshComponent->bCastDynamicShadow						  = false;
	MeshComponent->PrimaryComponentTick.bStartWithTickEnabled = false;
	MeshComponent->Deactivate();

	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;
	SetRemoteRoleForBackwardsCompat(ROLE_None);
	bReplicates		   = false;
	bReplicateMovement = false;

	InitialLifeSpan = 0.0f;
}

void ACsProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CollisionComponent->OnComponentHit.AddDynamic(this, &ACsProjectile::OnHitCallback);
	CollisionComponent->SetComponentTickEnabled(false);
	MovementComponent->SetComponentTickEnabled(false);
	MeshComponent->SetComponentTickEnabled(false);

	SetActorTickEnabled(false);
}

void ACsProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACsProjectile::Init(const int32 &Index)
{
	PoolIndex = Index;

	Cache.Set(Index, this);
}

template<typename T>
void ACsProjectile::Allocate(const uint16& ActiveIndex, ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache, UObject* InInstigator, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)())
{
	Cache.Init<T>(ActiveIndex, Relevance, InData, InFireCache, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), 0, InInstigator, InOwner, InParent, InObject, OnDeAllocate);
}

template<typename T>
void ACsProjectile::Allocate(const uint16& ActiveIndex, ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache, T* InObject, void (T::*OnDeAllocate)())
{
	Cache.Init<T>(ActiveIndex, Relevance, InData, InFireCache, GetWorld()->GetTimeSeconds, GetWorld()->GetRealTimeSeconds(), 0, nullptr, nullptr, InObject, OnDeAllocate);
}

template<typename T>
void ACsProjectile::Allocate(const uint16& ActiveIndex, ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache, UObject* InInstigator, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)())
{
	Cache.Init<T>(ActiveIndex, Relevance, InData, InFireCache, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), 0, InInstigator, InOwner, InObject, OnDeAllocate);
}

template<typename T>
void ACsProjectile::Allocate(const uint16& ActiveIndex, ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache, const FVector &Location, T* InObject, void (T::*OnDeAllocate)())
{
	Cache.Init<T>(ActiveIndex, Relevance, InData, InFireCache, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), 0, InObject, OnDeAllocate);
}

void ACsProjectile::Allocate(const uint16& ActiveIndex, ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache, UObject* InInstigator, UObject* InOwner, UObject* InParent /*=nullptr*/)
{
	Cache.Init(ActiveIndex, Relevance, InData, InFireCache, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), 0, InInstigator, InOwner, InParent);
}

void ACsProjectile::Allocate(const uint16& ActiveIndex, ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache)
{
	Cache.Init(ActiveIndex, Relevance, InData, InFireCache, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), InFireCache->Frame);
}

void ACsProjectile::Allocate_Internal()
{
}

void ACsProjectile::DeAllocate()
{
	Super::DeAllocate();

	// Collision
	CollisionComponent->Deactivate();
	CollisionComponent->ClearMoveIgnoreActors();
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetComponentTickEnabled(false);
	CollisionComponent->SetNotifyRigidBodyCollision(false);
	// Movement
	MovementComponent->StopMovementImmediately();
	MovementComponent->SetComponentTickEnabled(false);
	MovementComponent->Deactivate();
	// Mesh
	MeshComponent->SetVisibility(false);
	MeshComponent->SetHiddenInGame(true);
	MeshComponent->SetComponentTickEnabled(false);
	MeshComponent->Deactivate();

	if (ACsProjectile* Projectile = GetFakeProjectile())
		Projectile->DeAllocate();
	Cache.Reset();
}

ACsProjectile* ACsProjectile::GetFakeProjectile()
{
	return FakeProjectile.IsValid() ? FakeProjectile.Get() : nullptr;
}

void ACsProjectile::OnHitCallback(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	OnHitCallback_Internal(HitComp, OtherActor, OtherComp, NormalImpulse, HitResult);
}

void ACsProjectile::OnHitCallback_Internal(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
}