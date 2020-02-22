// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsProjectileBase.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Library/CsLibrary_Common.h"
#include "Managers/Projectile/CsProjectileMovementComponent.h"

// Data
#include "Data/CsData_Weapon.h"
#include "Data/CsData_ProjectileBase.h"
#include "Data/CsData_ProjectileImpact.h"

// Managers
#include "Managers/FX/CsManager_FX.h"
#include "Managers/FX/CsEmitter.h"
#include "Managers/Damage/CsManager_Damage.h"
#include "Managers/InteractiveActor/CsDamageableActor.h"

#include "Pawn/CsPawn.h"
#include "Weapon/CsWeapon.h"

#define CS_COLLISION_PROJECTILE	ECC_GameTraceChannel2

ACsProjectileBase::ACsProjectileBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Warning_FellOutOfWorld	   = TEXT("ACsProjectileBase::FellOutOfWorld");
	Warning_OutsideWorldBounds = TEXT("ACsProjectileBase::OutsideWorldBounds");

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
	CollisionComponent->SetGenerateOverlapEvents(false);
	CollisionComponent->bReturnMaterialOnMove  = true;
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	CollisionComponent->PrimaryComponentTick.bStartWithTickEnabled = false;

	// Players can't walk on it
	CollisionComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComponent->CanCharacterStepUpOn = ECB_No;

	CollisionComponent->Deactivate();

	RootComponent = CollisionComponent;

	// Movement Component
	MovementComponent = ObjectInitializer.CreateDefaultSubobject<UCsProjectileMovementComponent>(this, TEXT("MovementComponent"));
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
	SetReplicatingMovement(false);

	InitialLifeSpan = 0.0f;
}

void ACsProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CollisionComponent->OnComponentHit.AddDynamic(this, &ACsProjectileBase::OnHitCallback);
	CollisionComponent->SetComponentTickEnabled(false);
	MovementComponent->SetComponentTickEnabled(false);
	MeshComponent->SetComponentTickEnabled(false);

	SetActorTickEnabled(false);
}

void ACsProjectileBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	OnTick_HandleCVars(DeltaSeconds);

	Cache.ElapsedTime += DeltaSeconds;

	OnTick_HandleMovementFunction(DeltaSeconds);
}

void ACsProjectileBase::OnTick_HandleCVars(const float &DeltaSeconds)
{
	if (CsCVarDrawProjectileCollision->GetInt() == CS_CVAR_DRAW)
	{
		if (Cache.Relevance != ECsProjectileRelevance::Fake)
		{
			const FVector Location = GetActorLocation();
			const float Radius	   = CollisionComponent->GetScaledSphereRadius();

			DrawDebugSphere(GetWorld(), Location, Radius, 16, FColor::Green, false, DeltaSeconds + 0.005f, 0, 0.25f);
		}
	}
}

void ACsProjectileBase::OnTick_HandleMovementFunction(const float &DeltaSeconds)
{
	UCsData_ProjectileBase* Data			 = Cache.GetData();
	const ECsProjectileMovement MovementType = Data->GetMovementType();

	if (MovementType != ECsProjectileMovement::Function)
		return;

	const FVector NextLocation	= EvaluateMovementFunction(Cache.ElapsedTime);
	const FVector MoveDelta		= NextLocation - GetActorLocation();
	const FQuat Rotation		= MoveDelta.ToOrientationQuat();

	MovementComponent->MoveUpdatedComponent(MoveDelta, Rotation, true, nullptr);

	DrawPath(DeltaSeconds);
}

void ACsProjectileBase::DrawPath(const float &DeltaSeconds)
{
	// Local Player
	if (CsCVarDrawLocalPlayerProjectilePath->GetInt() == CS_CVAR_DRAW)
	{
		APawn* Pawn					 = Cast<APawn>(Cache.GetInstigator());
		const bool IsLocalInstigator = UCsLibrary_Common::IsLocalPawn(GetWorld(), Pawn);

		if (IsLocalInstigator)
		{
			const float Interval			= FMath::Max(CS_CVAR_DRAW_LOCAL_PLAYER_PROJECTILE_PATH_INTERVAL, CsCVarDrawLocalPlayerProjectilePathInterval->GetFloat());
			const uint8 SegmentsPerInterval = FMath::Max(CS_CVAR_DRAW_LOCAL_PLAYER_PROJECTILE_PATH_SEGMENTS_PER_INTERVAL, CsCVarDrawLocalPlayerProjectilePathSegmentsPerInterval->GetInt());
			const float Thickness			= FMath::Max(CS_CVAR_DRAW_LOCAL_PLAYER_PROJECTILE_PATH_THICKNESS, CsCVarDrawLocalPlayerProjectilePathThickness->GetFloat());

			DrawPath_Internal(DeltaSeconds, Interval, SegmentsPerInterval, Thickness);
			return;
		}
	}
	// Any Instigator
	if (CsCVarDrawProjectilePath->GetInt() == CS_CVAR_DRAW)
	{
		const float Interval			= FMath::Max(CS_CVAR_DRAW_PROJECTILE_PATH_INTERVAL, CsCVarDrawProjectilePathInterval->GetFloat());
		const uint8 SegmentsPerInterval = FMath::Max(CS_CVAR_DRAW_PROJECTILE_PATH_SEGMENTS_PER_INTERVAL, CsCVarDrawProjectilePathSegmentsPerInterval->GetInt());
		const float Thickness			= FMath::Max(CS_CVAR_DRAW_PROJECTILE_PATH_THICKNESS, CsCVarDrawProjectilePathThickness->GetFloat());

		DrawPath_Internal(DeltaSeconds, Interval, SegmentsPerInterval, Thickness);
	}
}

void ACsProjectileBase::DrawPath_Internal(const float &DeltaSeconds, const float &Interval, const uint8 &SegmentsPerInterval, const float &Thickness)
{
	const float DeltaTime	  = Interval / (float)SegmentsPerInterval;
	const float RemainingTime = Cache.LifeTime - Cache.ElapsedTime;
	const uint16 Segments	  = FMath::FloorToInt(RemainingTime / DeltaTime) - 1;

	float CurrentTime = Cache.ElapsedTime;

	for (uint16 I = 0; I < Segments; ++I)
	{
		const float T0   = CurrentTime + I * DeltaTime;
		const FVector P0 = EvaluateMovementFunction(T0);
		const float T1	 = CurrentTime + (I + 1) * DeltaTime;
		const FVector P1 = EvaluateMovementFunction(T1);

		DrawDebugLine(GetWorld(), P0, P1, FColor::Red, false, DeltaSeconds + 0.005f, 0, Thickness);
	}
}

FVector ACsProjectileBase::EvaluateMovementFunction(const float &Time)
{
	return Cache.GetData()->EvaluateMovementFunction(Time, Cache.Location, Cache.Transform);
}

void ACsProjectileBase::Init(const int32& Index, const FECsProjectile& InType)
{
	PoolIndex = Index;
	Type	  = InType;

	Cache.Set(Index, this);
}

void ACsProjectileBase::Allocate(FCsProjectileBasePayload* Payload)
{
	Cache.Init(Payload, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), UCsLibrary_Common::GetCurrentFrame(GetWorld()));

	Allocate_Internal(Payload);

}

void ACsProjectileBase::Allocate_Internal(FCsProjectileBasePayload* Payload)
{
#if WITH_EDITOR 
	if (Override_Allocate_Internal_ScriptEvent.IsBound())
	{
		if (CsCVarLogOverrideFunctions->GetInt() == CS_CVAR_DISPLAY)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsProjectileBase::Allocate_Internal (%s): Using Override Function."), *GetName());
		}
		Override_Allocate_Internal_ScriptEvent.Broadcast(PoolIndex);
		return;
	}
#endif // #if WITH_EDITOR

	ACsPawn* InstigatingPawn   = Cast<ACsPawn>(Cache.GetInstigator());
	const bool IsLocalClient   = UCsLibrary_Common::IsLocalPawn(GetWorld(), InstigatingPawn);
	const ECsViewType& ViewType = IsLocalClient ? ECsViewType::FirstPerson : ECsViewType::ThirdPerson;

	ACsWeapon* OwnerWeapon					= Cast<ACsWeapon>(Cache.GetOwner());
	UCsData_Weapon* Data_Weapon				= OwnerWeapon ? OwnerWeapon->GetMyData_Weapon() : nullptr;
	UCsData_ProjectileBase* Data_Projectile = Cache.GetData();

	const ECsProjectileRelevance& Relevance = Cache.Relevance;

	SetActorHiddenInGame(false);

	// Move
	MovementComponent->MovementType = Data_Projectile->GetMovementType();

	// Real Invisible
	if (Relevance == ECsProjectileRelevance::RealInvisible)
	{
		MeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		MeshComponent->SetVisibility(false);
		
		RootComponent = CollisionComponent;
		MovementComponent->UpdatedComponent = CollisionComponent;
		MovementComponent->Activate();
		MovementComponent->SetComponentTickEnabled(true);
		//MovementComponent->MaxSimulationIterations = CVarSimulationIterationsProjectile->GetInt();
	}
	// Real Visible
	if (Relevance == ECsProjectileRelevance::RealVisible)
	{
		RootComponent = CollisionComponent;
		MeshComponent->AttachToComponent(CollisionComponent, FAttachmentTransformRules::KeepRelativeTransform);

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
		MeshComponent->SetRelativeTransform(Data_Projectile->GetMyTransform());
		MeshComponent->Activate();
		MeshComponent->SetVisibility(true);
		MeshComponent->SetHiddenInGame(false);
		MeshComponent->SetComponentTickEnabled(true);

		// Trail
		if (Data_Projectile->GetUseTrailFX())
		{
			AICsManager_FX* Manager_FX = AICsManager_FX::Get(GetWorld());
			FCsFxElement* FX		   = Data_Projectile->GetTrailFX(ViewType);

			FCsFxPayload* FxPayload = Manager_FX->AllocatePayload();
			FxPayload->Set(FX);
			FxPayload->Owner = OwnerWeapon;
			FxPayload->Parent = MeshComponent;
			FxPayload->Rotation = Cache.Rotation.GetInverse();

			ACsEmitter* TrailFX		  = Manager_FX->Play(FxPayload);
			TrailFX->Cache.LifeTime   = Data_Projectile->GetLifeTime();
		}
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

		for (int32 I = 0; I < Count; ++I)
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
		CollisionComponent->SetSphereRadius(Data_Projectile->GetSphereRadius());
		CollisionComponent->SetCollisionEnabled(Data_Projectile->GetCollisionEnabled());
		CollisionComponent->SetNotifyRigidBodyCollision(true);

		CollisionComponent->SetComponentTickEnabled(true);
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

	const ECsProjectileMovement MovementType = Data_Projectile->GetMovementType();

	// Simulated
	if (MovementType == ECsProjectileMovement::Simulated)
	{
		if (Relevance == ECsProjectileRelevance::Fake)
		{
			FRotationMatrix Matrix = FRotationMatrix(Cache.Rotation);
			const FVector Down	   = Data_Projectile->GetSphereRadius() * -Matrix.GetScaledAxis(EAxis::Z);

			TeleportTo(Cache.Location + Down, Cache.Rotation, false, true);
		}
		else
		{
			TeleportTo(Cache.Location, Cache.Rotation, false, true);
		}
	}
	// Function
	else
	if (MovementType == ECsProjectileMovement::Function)
	{
		TeleportTo(EvaluateMovementFunction(0.0f), Cache.Rotation, false, true);
	}

	const float DrawDistanceSq = Data_Projectile->GetDrawDistanceSq(ViewType);
	Cache.DrawDistanceSq	   = DrawDistanceSq;

	if (DrawDistanceSq > 0)
	{
		const float DistanceSq = UCsLibrary_Common::GetSquaredDistanceToLocalControllerEye(GetWorld(), GetActorLocation());
		const bool Hide		   = DistanceSq > DrawDistanceSq;

		if (Hide != IsHidden())
			SetActorHiddenInGame(Hide);
	}

	// Simulated
	if (MovementType == ECsProjectileMovement::Simulated)
	{
		MovementComponent->InitialSpeed			  = Cache.Speed;
		MovementComponent->MaxSpeed				  = Data_Projectile->GetMaxSpeed();
		MovementComponent->Velocity				  = MovementComponent->InitialSpeed * Cache.Direction;
		MovementComponent->ProjectileGravityScale = Data_Projectile->GetGravityMultiplier();
	}
}

void ACsProjectileBase::DeAllocate()
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
	const int32 Count							   = AttachChildren.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		USceneComponent* Component = AttachChildren[I];
		AActor* Actor			   = Component->GetOwner();

		// FX
		if (ACsEmitter* FX = Cast<ACsEmitter>(Actor))
		{
			FX->Cache.LifeTime  = 0.0f;
			FX->Cache.bLifeTime = true;
		}
	}

	// Mesh
	UCsLibrary_Common::ClearOverrideMaterials(MeshComponent);
	MeshComponent->SetStaticMesh(nullptr);
	MeshComponent->SetVisibility(false);
	MeshComponent->SetHiddenInGame(true);
	MeshComponent->SetComponentTickEnabled(false);
	MeshComponent->Deactivate();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

	if (ACsProjectileBase* Projectile = GetFakeProjectile())
		Projectile->DeAllocate();
	Cache.DeAllocate();
}

ACsProjectileBase* ACsProjectileBase::GetFakeProjectile()
{
	return FakeProjectile.IsValid() ? FakeProjectile.Get() : nullptr;
}

void ACsProjectileBase::AddIgnoreActor(AActor* InActor)
{
	IgnoreActors.Add(InActor);
}

AActor* ACsProjectileBase::GetIgnoreActor(const int32 &Index)
{
	if (Index >= IgnoreActors.Num())
		return nullptr;
	return IgnoreActors[Index].IsValid() ? IgnoreActors[Index].Get() : nullptr;
}

void ACsProjectileBase::OnHitCallback(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	if (!Cache.bAllocated)
		return;

	ACsManager_Damage* Manager_Damage = ACsManager_Damage::Get(GetWorld());
	FCsDamageEvent* Event			  = Manager_Damage->AllocateEvent();

	Event->Damage	  = Cache.GetData()->GetDamage();
	Event->Instigator = Cache.GetInstigator();
	Event->Causer	  = Cache.GetOwner();
	//Event->SetDamageType();
	//Event->SetHitType();
	Event->HitInfo = HitResult;

	// Process Damage on SERVER Only
	if (GetLocalRole() == ROLE_Authority)
	{
		// DamageableActor
		if (ACsDamageableActor* DamageableActor = Cast<ACsDamageableActor>(HitResult.GetActor()))
		{
			DamageableActor->ApplyDamage(Event);
		}
		// Pawn
		if (ACsPawn* Pawn = Cast<ACsPawn>(HitResult.GetActor()))
		{
			Pawn->ApplyDamage(Event);
		}
	}

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

	Event->Reset();

	Cache.bLifeTime = true;
	Cache.LifeTime	= 0.0f;
}

// Script
#pragma region

UObject* ACsProjectileBase::Cache_GetOwner() { return Cache.GetOwner(); }
UObject* ACsProjectileBase::Cache_GetInstigator() { return Cache.GetInstigator(); }
ACsProjectileBase* ACsProjectileBase::Cache_GetProjectile() { return Cache.GetProjectile(); }
UCsData_ProjectileBase* ACsProjectileBase::Cache_GetData() { return Cache.GetData(); }

#pragma endregion Script