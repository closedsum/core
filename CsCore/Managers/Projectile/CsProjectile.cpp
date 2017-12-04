// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsProjectile.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Data
#include "Data/CsData_Weapon.h"
#include "Data/CsData_Projectile.h"
#include "Data/CsData_ProjectileImpact.h"

// Managers
#include "Managers/FX/CsManager_FX.h"
#include "Managers/FX/CsEmitter.h"

#include "Pawn/CsPawn.h"
#include "Weapon/CsWeapon.h"

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
void ACsProjectile::Allocate(const uint16& ActiveIndex, const TCsProjectileRelevance &Relevance, ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache, UObject* InInstigator, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)())
{
	Cache.Init<T>(ActiveIndex, Relevance, InData, InFireCache, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), 0, InInstigator, InOwner, InParent, InObject, OnDeAllocate);

	Allocate_Internal();
}

template<typename T>
void ACsProjectile::Allocate(const uint16& ActiveIndex, const TCsProjectileRelevance &Relevance, ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache, T* InObject, void (T::*OnDeAllocate)())
{
	Allocate<T>(ActiveIndex, Relevance, InData, InFireCache, nullptr, nullptr, InObject, OnDeAllocate);
}

template<typename T>
void ACsProjectile::Allocate(const uint16& ActiveIndex, const TCsProjectileRelevance &Relevance, ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache, UObject* InInstigator, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)())
{
	Allocate<T>(ActiveIndex, Relevance, InData, InFireCache, nullptr, InOwner, InObject, OnDeAllocate);
}

void ACsProjectile::Allocate(const uint16& ActiveIndex, const TCsProjectileRelevance &Relevance, ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache, UObject* InInstigator, UObject* InOwner, UObject* InParent /*=nullptr*/)
{
	Cache.Init(ActiveIndex, Relevance, InData, InFireCache, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), 0, InInstigator, InOwner, InParent);

	Allocate_Internal();
}

void ACsProjectile::Allocate(const uint16& ActiveIndex, const TCsProjectileRelevance &Relevance, ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache)
{
	Allocate(ActiveIndex, Relevance, InData, InFireCache, nullptr, nullptr, nullptr);
}

void ACsProjectile::Allocate_Internal()
{
#if WITH_EDITOR 
	if (Override_Allocate_Internal_ScriptEvent.IsBound())
	{
		if (CsCVarLogOverrideFunctions->GetInt() == CS_CVAR_DISPLAY)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsProjectile::Allocate_Internal (%s): Using Override Function."), *GetName());
		}
		Override_Allocate_Internal_ScriptEvent.Broadcast(PoolIndex);
		return;
	}
#endif // #if WITH_EDITOR

	ACsPawn* InstigatingPawn   = Cast<ACsPawn>(Cache.GetInstigator());
	const bool IsLocalClient   = UCsCommon::IsLocalPawn(GetWorld(), InstigatingPawn);
	const TCsViewType ViewType = IsLocalClient ? ECsViewType::FirstPerson : ECsViewType::ThirdPerson;

	ACsWeapon* OwnerWeapon				= Cast<ACsWeapon>(Cache.GetOwner());
	ACsData_Weapon* Data_Weapon			= OwnerWeapon ? OwnerWeapon->GetMyData_Weapon() : nullptr;
	ACsData_Projectile* Data_Projectile = Cache.GetData();

	const TCsProjectileRelevance Relevance = Cache.Relevance;

	// Move

	// Real Invisible
	if (Relevance == ECsProjectileRelevance::RealInvisible)
	{
		MeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		MeshComponent->SetVisibility(false);
		
		MovementComponent->UpdatedComponent = CollisionComponent;
		MovementComponent->Activate();
		MovementComponent->SetComponentTickEnabled(true);
		//MovementComponent->MaxSimulationIterations = CVarSimulationIterationsProjectile->GetInt();
	}
	// Real Visible
	if (Relevance == ECsProjectileRelevance::RealVisible)
	{
		MovementComponent->UpdatedComponent = CollisionComponent;
		MovementComponent->Activate();
		MovementComponent->SetComponentTickEnabled(true);
	}
	// Fake
	if (Relevance == ECsProjectileRelevance::Fake)
	{
		MeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		RootComponent = MeshComponent;
		MovementComponent->UpdatedComponent = MeshComponent;
		MovementComponent->Activate();
		MovementComponent->SetComponentTickEnabled(true);
	}

	// Mesh / Visual

	// Real Visible | Fake
	if (Relevance == ECsProjectileRelevance::RealVisible ||
		Relevance == ECsProjectileRelevance::Fake)
	{
		// Mesh
		MeshComponent->SetStaticMesh(Data_Projectile->GetMesh(ViewType));
		MeshComponent->SetRelativeTransform(Data_Projectile->GetTransform());
		MeshComponent->Activate();
		MeshComponent->SetVisibility(true);
		MeshComponent->SetHiddenInGame(false);
		MeshComponent->SetComponentTickEnabled(true);

		// Trail
		ACsManager_FX* Manager_FX = ACsManager_FX::Get(GetWorld());
		ACsEmitter* TrailFX		  = Manager_FX->Play(Data_Projectile->GetTrailFX(ViewType), OwnerWeapon, MeshComponent, Cache.Rotation.GetInverse());
		TrailFX->Cache.LifeTime   = Data_Projectile->GetLifeTime();
	}

	// Collision

	// Real Visible | Real Invisible
	if (Relevance == ECsProjectileRelevance::RealVisible ||
		Relevance == ECsProjectileRelevance::RealInvisible)
	{
		CollisionComponent->Activate();

		if (AActor* MyInstigator = Cast<AActor>(Cache.GetInstigator()))
			IgnoreActors.Add(MyInstigator);

		if (OwnerWeapon)
			IgnoreActors.Add(OwnerWeapon);

		const int32 Count = IgnoreActors.Num();

		for (int32 I = 0; I < Count; I++)
		{
			AActor* Actor = IgnoreActors[I].IsValid() ? IgnoreActors[I].Get() : nullptr;

			if (!Actor)
				continue;

			CollisionComponent->MoveIgnoreActors.Add(Actor);
		}

		//FCollisionResponseContainer CapsuleResponseContainer(ECR_Ignore);
		//CapsuleResponseContainer.SetResponse(ECC_Pawn, ECR_Block);
		//CapsuleResponseContainer.SetResponse(MBO_COLLISION_PROJECTILE, ECR_Ignore);

		CollisionComponent->SetCollisionObjectType(Data_Projectile->GetCollisionObjectType());
		CollisionComponent->SetCollisionResponseToChannels(Data_Projectile->GetCollisionResponseContainer());
		CollisionComponent->SetCollisionEnabled(Data_Projectile->GetCollisionEnabled());
		CollisionComponent->SetNotifyRigidBodyCollision(true);

		CollisionComponent->SetComponentTickEnabled(true);

		CollisionComponent->SetSphereRadius(Data_Projectile->GetSphereRadius());
	}
	// Fake
	if (Relevance == ECsProjectileRelevance::Fake)
	{
		CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CollisionComponent->SetCollisionObjectType(Data_Projectile->GetCollisionObjectType());
		CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
		CollisionComponent->SetNotifyRigidBodyCollision(false);
	}

	// Homing
	/*
	if (Cache)
	{
		if (AActor* HomingTarget = Cast<AActor>(Cache->GetHomingTarget()))
		{
			SetHomingTarget(HomingTarget, Cache->HomingAccelerationMagnitude, Cache->HomingBoneName);
		}
	}
	*/
	
	SetActorTickEnabled(true);
	TeleportTo(Cache.Location, Cache.Rotation, false, true);

	const float DrawDistanceSq = Data_Projectile->GetDrawDistanceSq(ViewType);

	if (DrawDistanceSq > 0)
	{
		const float DistanceSq = UCsCommon::GetSquaredDistanceToLocalControllerEye(GetWorld(), GetActorLocation());
		const bool Hide		   = DistanceSq > DrawDistanceSq;

		if (Hide != bHidden)
			SetActorHiddenInGame(Hide);
	}

	MovementComponent->InitialSpeed			  = Cache.Speed;
	MovementComponent->MaxSpeed				  = Data_Projectile->GetMaxSpeed();
	MovementComponent->Velocity				  = MovementComponent->InitialSpeed * Cache.Direction;
	MovementComponent->ProjectileGravityScale = Data_Projectile->GetGravityMultiplier();
}

void ACsProjectile::DeAllocate()
{
	Super::DeAllocate();

	IgnoreActors.Reset();

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

		// DeAllocate attachments
	const TArray<USceneComponent*>& AttachChildren = MeshComponent->GetAttachChildren();
	const int32 Count							    = AttachChildren.Num();

	for (int32 I = 0; I < Count; I++)
	{
		USceneComponent* Component = AttachChildren[I];
		AActor* Actor			   = Component->GetOwner();

		// FX
		if (ACsEmitter* FX = Cast<ACsEmitter>(Actor))
		{
			FX->Cache.LifeTime    = 0.0f;
			FX->Cache.UseLifeTime = true;
		}
	}

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

void ACsProjectile::AddIgnoreActor(AActor* InActor)
{
	IgnoreActors.Add(InActor);
}

AActor* ACsProjectile::GetIgnoreActor(const int32 &Index)
{
	if (Index >= IgnoreActors.Num())
		return nullptr;
	return IgnoreActors[Index].IsValid() ? IgnoreActors[Index].Get() : nullptr;
}

void ACsProjectile::OnHitCallback(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	if (!Cache.IsAllocated)
		return;

	// Impact Normal
	if (CsCVarDrawProjectileImpactNormal->GetInt() == CS_CVAR_DRAW)
	{
		const FVector Start   = HitResult.Location;
		const float Length	  = FMath::Max(CS_CVAR_DRAW_PROJECTILE_IMPACT_NORMAL_LENGTH, CsCVarDrawProjectileImpactNormalLength->GetFloat());
		const FVector End	  = Start + Length * HitResult.ImpactNormal;
		const float Duration  = FMath::Max(CS_CVAR_DRAW_PROJECTILE_IMPACT_NORMAL_DURATION, CsCVarDrawProjectileImpactNormalDuration->GetFloat());
		const float Thickness = FMath::Max(CS_CVAR_DRAW_PROJECTILE_IMPACT_NORMAL_THICKNESS, CsCVarDrawProjectileImpactNormalThickness->GetFloat());

		DrawDebugDirectionalArrow(GetWorld(), Start, End, 10.0f, FColor::Red, false, Duration, 0, Thickness);
	}

	// Play Impact FX / Sound
	UPhysicalMaterial* PhysicalMaterial = HitResult.PhysMaterial.IsValid() ? HitResult.PhysMaterial.Get() : nullptr;

	if (PhysicalMaterial)
	{
		// FX
		Cache.GetData()->GetData_Impact()->PlayImpactFX(GetWorld(), PhysicalMaterial->SurfaceType, Cache.GetOwner(), HitResult.Location, HitResult.ImpactNormal);
		// Sound
		Cache.GetData()->GetData_Impact()->PlayImpactSound(GetWorld(), PhysicalMaterial->SurfaceType, Cache.GetOwner(), HitResult.Location);
	}

	Cache.LifeTime = 0.0f;
}

// Script
#pragma region

UObject* ACsProjectile::Cache_GetOwner() { return Cache.GetOwner(); }
UObject* ACsProjectile::Cache_GetInstigator() { return Cache.GetInstigator(); }
ACsProjectile* ACsProjectile::Cache_GetProjectile() { return Cache.GetProjectile(); }
ACsData_Projectile* ACsProjectile::Cache_GetData() { return Cache.GetData(); }

#pragma endregion Script