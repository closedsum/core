// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Weapon/CsProjectile.h"
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
}

void ACsProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

template<typename T>
void ACsProjectile::Allocate(ACsData_Projectile* InData, const FCsProjectileFireCache* InFireCache, UObject* InInstigator, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)())
{
	Cache.Init<T>(InData, InFireCache->Time, InFireCache->RealTime, InFireCache->Frame, InInstigator, InOwner, InParent, InObject, OnDeAllocate);
}

template<typename T>
void ACsProjectile::Allocate(ACsData_Projectile* InData, const FCsProjectileFireCache* InFireCache, T* InObject, void (T::*OnDeAllocate)())
{
	Cache.Init<T>(InData, InFireCache->Time, InFireCache->RealTime, InFireCache->Frame, nullptr, nullptr, InObject, OnDeAllocate);
}

template<typename T>
void ACsProjectile::Allocate(ACsData_Projectile* InData, const FCsProjectileFireCache* InFireCache, UObject* InInstigator, UObject* InOwner, const FVector &InLocation, T* InObject, void (T::*OnDeAllocate)())
{
	Cache.Init<T>(InData, InFireCache->Time, InFireCache->RealTime, InFireCache->Frame, InInstigator, InOwner, InLocation, InObject, OnDeAllocate);
}

template<typename T>
void ACsProjectile::Allocate(ACsData_Projectile* InData, const FCsProjectileFireCache* InFireCache, const FVector &Location, T* InObject, void (T::*OnDeAllocate)())
{
	Cache.Init<T>(InData, InFireCache->Time, InFireCache->RealTime, InFireCache->Frame, Location, InObject, OnDeAllocate);
}

void ACsProjectile::Allocate(ACsData_Projectile* InData, const FCsProjectileFireCache* InFireCache, UObject* InInstigator, UObject* InOwner, UObject* InParent /*=nullptr*/, const FVector &Location /*=FVector::ZeroVector*/)
{
	Cache.Init(InData, InFireCache->Time, InFireCache->RealTime, InFireCache->Frame, InInstigator, InOwner, InParent, Location);
}

void ACsProjectile::Allocate(ACsData_Projectile* InData, const FCsProjectileFireCache* InFireCache, const FVector &Location)
{
	Cache.Init(InData, InFireCache->Time, InFireCache->RealTime, InFireCache->Frame, Location);
}

void ACsProjectile::Allocate_Internal()
{
}

void ACsProjectile::DeAllocate()
{
	Super::DeAllocate();

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