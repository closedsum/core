// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsProjectilePooledImpl.h"
#include "CsPrj.h"

// CVar
#include "Managers/Projectile/CsCVars_Projectile.h"
// Library
#include "Library/CsLibrary_Common.h"
#include "Library/CsLibrary_Material.h"
#include "Managers/Pool/Cache/CsLibrary_PooledObjectCache.h"
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
#include "Data/CsLibrary_Data_Projectile.h"
#include "Payload/CsLibrary_Payload_Projectile.h"
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"
#include "Managers/Damage/Event/CsLibrary_DamageEvent.h"
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
#include "Managers/Damage/Modifier/CsLibrary_DamageModifier.h"
// Containers
#include "Containers/CsGetInterfaceMap.h"
// Components
#include "Components/SphereComponent.h"
#include "Managers/Projectile/CsProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
// Managers
#include "Managers/Projectile/CsManager_Projectile.h"
#include "Managers/FX/Actor/CsManager_FX_Actor.h"
#include "Managers/Damage/CsManager_Damage.h"
// Data
#include "Data/CsData_Projectile.h"
#include "Data/CsData_ProjectileCollision.h"
#include "Data/Visual/CsData_ProjectileStaticMeshVisual.h"
#include "Data/Visual/CsData_ProjectileTrailVisual.h"
#include "Data/Visual/CsData_ProjectileImpactVisual.h"
#include "Data/Damage/CsData_ProjectileDamage.h"
// Projectile
#include "Cache/CsProjectilePooledCacheImpl.h"
// FX
#include "Managers/FX/Cache/CsFXPooledCacheImpl.h"
#include "Managers/FX/Payload/CsFXPooledPayloadImpl.h"
// Damage
#include "Managers/Damage/Event/CsDamageEventImpl.h"
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"
// Game
#include "GameFramework/GameStateBase.h"

//#define CS_COLLISION_PROJECTILE	ECC_GameTraceChannel2

// Cached
#pragma region

namespace NCsProjectilePooledImplCached
{
	namespace Str
	{
		CS_DEFINE_CACHED_STRING(SetType, "ACsProjectilePooledImpl::SetType");
		CS_DEFINE_CACHED_STRING(OnHit, "ACsProjectilePooledImpl::OnHit");
		CS_DEFINE_CACHED_STRING(Update, "ACsProjectilePooledImpl::Update");
		CS_DEFINE_CACHED_STRING(Deallocate, "ACsProjectilePooledImpl::Deallocate");
		CS_DEFINE_CACHED_STRING(Launch, "ACsProjectilePooledImpl::Launch");
		CS_DEFINE_CACHED_STRING(OnLaunch_SetModifiers, "ACsProjectilePooledImpl::OnLaunch_SetModifiers");
		CS_DEFINE_CACHED_STRING(OnHit_CreateDamageEvent, "ACsProjectilePooledImpl::OnHit_CreateDamageEvent");
	}
}

#pragma endregion Cached

ACsProjectilePooledImpl::ACsProjectilePooledImpl(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	Type(),
	State(),
	// Collision
	IgnoreActors(),
	bDeallocateOnHit(true),
	// ICsPooledObject
	Cache(nullptr),
	// ICsProjectile
	Data(nullptr),
	bLaunchOnAllocate(false),
	// FX
	TrailFXPooled(nullptr),
	// Damage
	DamageModifiers(),
	OnBroadcastDamage_Event(),
	OnBroadcastDamageContainer_Event()
{
	// Collision Component
	CollisionComponent = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComponent->AlwaysLoadOnClient  = true;
	CollisionComponent->AlwaysLoadOnServer  = true;
	CollisionComponent->bTraceComplexOnMove = true;
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//CollisionComponent->SetCollisionObjectType(CS_COLLISION_PROJECTILE);
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

// UObject Interface
#pragma region

void ACsProjectilePooledImpl::BeginDestroy()
{
	Super::BeginDestroy();

	if (Cache)
	{
		delete Cache;
		Cache = nullptr;
	}
}

#pragma endregion UObject Interface

// AActor Interface
#pragma region

void ACsProjectilePooledImpl::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentHit.AddDynamic(this, &ACsProjectilePooledImpl::OnHit);

	CollisionComponent->SetComponentTickEnabled(false);
	MovementComponent->SetComponentTickEnabled(false);
	MeshComponent->SetComponentTickEnabled(false);

	SetActorTickEnabled(false);

	ConstructCache();

	// Bind Events
	OnBroadcastDamageContainer_Event.AddUObject(UCsManager_Damage::Get(GetWorld()->GetGameState()), &UCsManager_Damage::ProcessDamageEventContainer);
}

void ACsProjectilePooledImpl::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/*
	OnTick_HandleCVars(DeltaSeconds);

	Cache.ElapsedTime += DeltaSeconds;

	OnTick_HandleMovementFunction(DeltaSeconds);
	*/
}

void ACsProjectilePooledImpl::FellOutOfWorld(const UDamageType& DmgType)
{
	Deallocate_Internal();
	SetActorLocation(FVector::ZeroVector);
	Cache->QueueDeallocate();
}

void ACsProjectilePooledImpl::OutsideWorldBounds()
{
	Deallocate_Internal();
	SetActorLocation(FVector::ZeroVector);
	Cache->QueueDeallocate();
}

#pragma endregion AActor Interface

void ACsProjectilePooledImpl::OnTick_HandleCVars(const float& DeltaSeconds)
{
	/*
	if (CsCVarDrawProjectileCollision->GetInt() == CS_CVAR_DRAW)
	{
		if (Cache.Relevance != ECsProjectileRelevance::Fake)
		{
			const FVector Location = GetActorLocation();
			const float Radius	   = CollisionComponent->GetScaledSphereRadius();

			DrawDebugSphere(GetWorld(), Location, Radius, 16, FColor::Green, false, DeltaSeconds + 0.005f, 0, 0.25f);
		}
	}
	*/
}

void ACsProjectilePooledImpl::OnTick_HandleMovementFunction(const float& DeltaSeconds)
{
	//UCsData_ProjectileBase* Data			 = Cache.GetData();
	/*
	const ECsProjectileMovement MovementType = ECsProjectileMovement::Simulated;//Data->GetMovementType();

	if (MovementType != ECsProjectileMovement::Function)
		return;

	const FVector NextLocation	= EvaluateMovementFunction(Cache.ElapsedTime);
	const FVector MoveDelta		= NextLocation - GetActorLocation();
	const FQuat Rotation		= MoveDelta.ToOrientationQuat();

	MovementComponent->MoveUpdatedComponent(MoveDelta, Rotation, true, nullptr);

	DrawPath(DeltaSeconds);
	*/
}

void ACsProjectilePooledImpl::DrawPath(const float& DeltaSeconds)
{
	// Local Player
	/*
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
	*/
	// Any Instigator
	/*
	if (CsCVarDrawProjectilePath->GetInt() == CS_CVAR_DRAW)
	{
		const float Interval			= FMath::Max(CS_CVAR_DRAW_PROJECTILE_PATH_INTERVAL, CsCVarDrawProjectilePathInterval->GetFloat());
		const uint8 SegmentsPerInterval = FMath::Max(CS_CVAR_DRAW_PROJECTILE_PATH_SEGMENTS_PER_INTERVAL, CsCVarDrawProjectilePathSegmentsPerInterval->GetInt());
		const float Thickness			= FMath::Max(CS_CVAR_DRAW_PROJECTILE_PATH_THICKNESS, CsCVarDrawProjectilePathThickness->GetFloat());

		DrawPath_Internal(DeltaSeconds, Interval, SegmentsPerInterval, Thickness);
	}
	*/
}

void ACsProjectilePooledImpl::DrawPath_Internal(const float& DeltaSeconds, const float& Interval, const uint8& SegmentsPerInterval, const float& Thickness)
{
	/*
	const float DeltaTime	  = Interval / (float)SegmentsPerInterval;
	const float RemainingTime = Cache.LifeT%ime - Cache.ElapsedTime;
	const uint16 Segments	  = FMath::FloorToInt(RemainingTime / DeltaTime) - 1;

	float CurrentTime = Cache.ElapsedTime;
	6
	for (uint16 I = 0; I < Segments; ++I)
	{
		const float T0   = CurrentTime + I * DeltaTime;
		const FVector P0 = EvaluateMovementFunction(T0);
		const float T1	 = CurrentTime + (I + 1) * DeltaTime;
		const FVector P1 = EvaluateMovementFunction(T1);

		DrawDebugLine(GetWorld(), P0, P1, FColor::Red, false, DeltaSeconds + 0.005f, 0, Thickness);
	}
	*/
}

FVector ACsProjectilePooledImpl::EvaluateMovementFunction(const float &Time)
{
	return FVector::ZeroVector;// Cache.GetData()->EvaluateMovementFunction(Time, Cache.Location, Cache.Transform);
}

void ACsProjectilePooledImpl::SetType(const FECsProjectile& InType)
{
	using namespace NCsProjectilePooledImplCached;

	const FString& Context = Str::SetType;

	checkf(EMCsProjectile::Get().IsValidEnum(InType), TEXT("%s: InType: %s is NOT Valid."), *Context, InType.ToChar());

	if (Type != InType)
	{
		Type = InType;

		UCsManager_Projectile* Manager_Projectile = UCsManager_Projectile::Get(GetWorld()->GetGameState());

		// Get Data associated with Type
		Data = Manager_Projectile->GetDataChecked(Context, Type);

		// TODO: Need to determine best place to set LifeTime from Data

		// Set Data on Cache
		FCsProjectilePooledCacheImpl* CacheImpl = FCsLibrary_PooledObjectCache::PureStaticCastChecked<FCsProjectilePooledCacheImpl>(Context, Cache);

		CacheImpl->SetData(Data);
	}
}

// Collision
#pragma region

void ACsProjectilePooledImpl::AddIgnoreActor(AActor* InActor)
{
	IgnoreActors.Add(InActor);
}

AActor* ACsProjectilePooledImpl::GetIgnoreActor(const int32 &Index)
{
	if (Index >= IgnoreActors.Num())
		return nullptr;
	return IgnoreActors[Index].IsValid() ? IgnoreActors[Index].Get() : nullptr;
}

void ACsProjectilePooledImpl::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	using namespace NCsProjectilePooledImplCached;

	const FString& Context = Str::OnHit;

#if !UE_BUILD_SHIPPING
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogProjectileCollision))
	{
		UE_LOG(LogCsPrj, Warning, TEXT("%s (%s):"), *Context, *(GetName()));

		UE_LOG(LogCsPrj, Warning, TEXT("- HitComponent: %s"), HitComponent ? *(HitComponent->GetName()) : TEXT("None"));
		UE_LOG(LogCsPrj, Warning, TEXT("- OtherActor: %s"), OtherActor ? *(OtherActor->GetName()) : TEXT("None"));
		UE_LOG(LogCsPrj, Warning, TEXT("- OtherComp: %s"), OtherComp ? *(OtherComp->GetName()) : TEXT("None"));
		UE_LOG(LogCsPrj, Warning, TEXT("- NormalImpulse: %s"), *(NormalImpulse.ToString()));
		// HitResult
		UE_LOG(LogCsPrj, Warning, TEXT("- Hit"));
		UE_LOG(LogCsPrj, Warning, TEXT("-- bBlockingHit: %s"), Hit.bBlockingHit ? TEXT("True") : TEXT("False"));
		UE_LOG(LogCsPrj, Warning, TEXT("-- bStartPenetrating"), Hit.bStartPenetrating ? TEXT("True") : TEXT("False"));
		UE_LOG(LogCsPrj, Warning, TEXT("-- Time: %f"), Hit.Time);
		UE_LOG(LogCsPrj, Warning, TEXT("-- Location: %s"), *(Hit.Location.ToString()));
		UE_LOG(LogCsPrj, Warning, TEXT("-- ImpactPoint: %s"), *(Hit.ImpactPoint.ToString()));
		UE_LOG(LogCsPrj, Warning, TEXT("-- Normal: %s"), *(Hit.Normal.ToString()));
		UE_LOG(LogCsPrj, Warning, TEXT("-- ImpactNormal: %s"), *(Hit.ImpactNormal.ToString()));
		UE_LOG(LogCsPrj, Warning, TEXT("-- TraceStart: %s"), *(Hit.TraceStart.ToString()));
		UE_LOG(LogCsPrj, Warning, TEXT("-- TraceEnd: %s"), *(Hit.TraceEnd.ToString()));
		UE_LOG(LogCsPrj, Warning, TEXT("-- PenetrationDepth: %f"), Hit.PenetrationDepth);
		UE_LOG(LogCsPrj, Warning, TEXT("-- Item: %d"), Hit.Item);
		UE_LOG(LogCsPrj, Warning, TEXT("-- PhysMaterial: %s"), Hit.PhysMaterial.IsValid() ? *(Hit.PhysMaterial->GetName()) : TEXT("None"));
		UE_LOG(LogCsPrj, Warning, TEXT("-- Actor: %s"), Hit.Actor.IsValid() ? *(Hit.Actor->GetName()) : TEXT("None"));
		UE_LOG(LogCsPrj, Warning, TEXT("-- Component: %s"), Hit.Component.IsValid() ? *(Hit.Component->GetName()) : TEXT("None"));
		UE_LOG(LogCsPrj, Warning, TEXT("-- BoneName: %s"), Hit.BoneName.IsValid() ? *(Hit.BoneName.ToString()) : TEXT("None"));
		UE_LOG(LogCsPrj, Warning, TEXT("-- FaceIndex: %d"), Hit.FaceIndex);
	}
#endif // #if !UE_BUILD_SHIPPING

	// Get Physics Surface
	UPhysicalMaterial* PhysMaterial = Hit.PhysMaterial.IsValid() ? Hit.PhysMaterial.Get() : nullptr;
	EPhysicalSurface SurfaceType	= PhysMaterial ? PhysMaterial->SurfaceType : EPhysicalSurface::SurfaceType_Default;

	// ICsData_ProjectileImpactVisual
	if (ICsData_ProjectileImpactVisual* ImpactVisualData = FCsLibrary_Data_Projectile::GetSafeInterfaceChecked<ICsData_ProjectileImpactVisual>(Context, Data))
	{
		const FCsFX& ImpactFX = ImpactVisualData->GetImpactFX(SurfaceType);

		UNiagaraSystem* FXSystem = ImpactFX.Get();

		checkf(FXSystem, TEXT("%s: FXSystem is NULL for Visual Data inteface: ICsData_ProjectileImpactVisual"), *Context);

		// Get Manager
		UCsManager_FX_Actor* Manager_FX_Actor = UCsManager_FX_Actor::Get(GetWorld()->GetGameState());
		// Get Payload
		FCsFXPooledPayloadImpl* FXPayload = Manager_FX_Actor->AllocatePayload<FCsFXPooledPayloadImpl>(ImpactFX.Type);
		// Set appropriate data on Payload
		FXPayload->Instigator = Cache->GetInstigator();

		FXPayload->Transform.SetLocation(Hit.Location);
		FXPayload->Transform.SetRotation(Hit.ImpactNormal.Rotation().Quaternion());

		FXPayload->FXSystem			= FXSystem;
		FXPayload->DeallocateMethod = ImpactFX.DeallocateMethod;
		FXPayload->LifeTime			= ImpactFX.LifeTime;
		// Spawn FX
		Manager_FX_Actor->Spawn(ImpactFX.Type, FXPayload);
	}
	// ICsData_ProjectileDamage
	if (ICsData_ProjectileDamage* DamageData = FCsLibrary_Data_Projectile::GetSafeInterfaceChecked<ICsData_ProjectileDamage>(Context, Data))
	{
		const FCsResource_DamageEvent* Event = OnHit_CreateDamageEvent(Hit);

		OnBroadcastDamage_Event.Broadcast(Event->Get());
		OnBroadcastDamageContainer_Event.Broadcast(Event);
	}

	OnHit_Internal(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	if (bDeallocateOnHit)
		Cache->QueueDeallocate();
}

void ACsProjectilePooledImpl::OnHit_Internal(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

#pragma endregion Collision

// ICsUpdate
#pragma region

void ACsProjectilePooledImpl::Update(const FCsDeltaTime& DeltaTime)
{
	using namespace NCsProjectilePooledImplCached;

	const FString& Context = Str::Update;

	FCsProjectilePooledCacheImpl* CacheImpl = FCsLibrary_PooledObjectCache::PureStaticCastChecked<FCsProjectilePooledCacheImpl>(Context, Cache);

	CacheImpl->Update(DeltaTime);
}

#pragma endregion ICsUpdate

void ACsProjectilePooledImpl::ConstructCache()
{
	Cache = new FCsProjectilePooledCacheImpl();
}

// ICsPooledObject
#pragma region

ICsPooledObjectCache* ACsProjectilePooledImpl::GetCache() const
{
	return Cache;
}

void ACsProjectilePooledImpl::Allocate(ICsPayload_PooledObject* Payload)
{
	checkf(Payload, TEXT("ACsProjectilePooledImpl::Allocate: Payload is NULL."));

	Cache->Allocate(Payload);

	if (bLaunchOnAllocate)
		Launch(Payload);
}

void ACsProjectilePooledImpl::Deallocate()
{
	Deallocate_Internal();
	Cache->Deallocate();
}

#pragma endregion ICsPooledObject

void ACsProjectilePooledImpl::Deallocate_Internal()
{
	using namespace NCsProjectilePooledImplCached;

	const FString& Context = Str::Deallocate;

	IgnoreActors.Reset();

	// FX
	if (TrailFXPooled)
	{
		// Deactivate the Trail FX
		ICsPooledObjectCache* FXCache	  = TrailFXPooled->GetCache();
		FCsFXPooledCacheImpl* FXCacheImpl = FCsLibrary_PooledObjectCache::PureStaticCastChecked<FCsFXPooledCacheImpl>(Context, FXCache);

		FXCacheImpl->QueueDeallocate();

		TrailFXPooled = nullptr;
	}

	// Collision
	CollisionComponent->Deactivate();
	CollisionComponent->ClearMoveIgnoreActors();
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetComponentTickEnabled(false);
	CollisionComponent->SetGenerateOverlapEvents(false);
	CollisionComponent->SetNotifyRigidBodyCollision(false);
	// Movement
	MovementComponent->StopMovementImmediately();
	MovementComponent->SetComponentTickEnabled(false);
	MovementComponent->Deactivate();

	// Deallocate attachments

	// Mesh
	FCsLibrary_Material::ClearOverrideMaterials(MeshComponent);
	MeshComponent->SetStaticMesh(nullptr);
	MeshComponent->SetVisibility(false);
	MeshComponent->SetHiddenInGame(true);
	MeshComponent->SetComponentTickEnabled(false);
	MeshComponent->Deactivate();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	
	// Modifiers
	DamageModifiers.Reset(DamageModifiers.Max());
}

// ICsProjectile
#pragma region

ICsData_Projectile* ACsProjectilePooledImpl::GetData() const
{
	return Data;
}

UObject* ACsProjectilePooledImpl::GetOwner() const
{
	return Cache->GetOwner();
}

UObject* ACsProjectilePooledImpl::GetInstigator() const
{
	return Cache->GetInstigator();
}

#pragma endregion ICsProjectile

void ACsProjectilePooledImpl::Launch(ICsPayload_PooledObject* Payload)
{
	using namespace NCsProjectilePooledImplCached;

	const FString& Context = Str::Launch;

	checkf(Payload, TEXT("%s: Payload is NULL."), *Context);

	// Get Projectile Payload
	ICsPayload_Projectile* ProjectilePayload = FCsLibrary_Payload_PooledObject::GetInterfaceChecked<ICsPayload_Projectile>(Context, Payload);

	// Get Projectile Cache
	ICsProjectileCache* ProjectileCache = FCsLibrary_PooledObjectCache::GetInterfaceChecked<ICsProjectileCache>(Context, Cache);

	// Set Damage Value if the projectile supports damage
	OnLaunch_SetModifiers(ProjectilePayload);

	//const ECsProjectileRelevance& Relevance = Cache.Relevance;

	SetActorHiddenInGame(false);

	// Real Visible
	//if (Relevance == ECsProjectileRelevance::RealVisible)
	{
		RootComponent = CollisionComponent;

		MovementComponent->UpdatedComponent = CollisionComponent;
		MovementComponent->Activate();
		MovementComponent->SetComponentTickEnabled(true);
	}
	
	// ICsData_ProjectileStaticMeshVisual | Static Mesh
	if (ICsData_ProjectileStaticMeshVisual* VisualData = FCsLibrary_Data_Projectile::GetSafeInterfaceChecked<ICsData_ProjectileStaticMeshVisual>(Context, Data))
	{
		// TODO: Allocate Static Mesh Actor and get Static Mesh Component

		MeshComponent->AttachToComponent(CollisionComponent, FAttachmentTransformRules::KeepRelativeTransform);

		UStaticMesh* Mesh = VisualData->GetStaticMesh().Get();

		checkf(Mesh, TEXT("%s: Mesh is NULL from Visual Data interface: ICsData_ProjectileStaticMeshVisual"), *(Str::Launch));

		MeshComponent->SetStaticMesh(Mesh);
		MeshComponent->SetWorldScale3D(VisualData->GetStaticMesh().Scale);
		MeshComponent->Activate();
		MeshComponent->SetVisibility(true);
		MeshComponent->SetHiddenInGame(false);
		MeshComponent->SetComponentTickEnabled(true);
	}

	// ICsData_ProjectileCollision | Collision
	if (ICsData_ProjectileCollision* CollisionData = FCsLibrary_Data_Projectile::GetSafeInterfaceChecked<ICsData_ProjectileCollision>(Context, Data))
	{
		const FCsCollisionPreset& CollisionPreset  = CollisionData->GetCollisionPreset();

		if (CollisionPreset.CollisionEnabled != ECollisionEnabled::NoCollision)
		{
			CollisionComponent->Activate();

			// Instigator
			if (AActor* Actor = Cast<AActor>(Payload->GetInstigator()))
				IgnoreActors.Add(Actor);
			// Owner
			if (AActor* Actor = Cast<AActor>(Payload->GetOwner()))
				IgnoreActors.Add(Actor);
			// Parent
			if (AActor* Actor = Cast<AActor>(Payload->GetParent()))
				IgnoreActors.Add(Actor);

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

			CollisionComponent->SetCollisionObjectType(CollisionPreset.ObjectType);
			CollisionComponent->SetSphereRadius(CollisionData->GetCollisionRadius());
			CollisionComponent->SetCollisionResponseToChannels(CollisionPreset.CollisionResponses);
				
			CollisionComponent->SetNotifyRigidBodyCollision(CollisionPreset.bSimulationGeneratesHitEvents);
			CollisionComponent->SetGenerateOverlapEvents(CollisionPreset.bGenerateOverlapEvents);

			CollisionComponent->SetCollisionEnabled(CollisionPreset.CollisionEnabled);

			CollisionComponent->SetComponentTickEnabled(true);
		}
	}
	
	SetActorTickEnabled(true);

	const ECsProjectileMovement MovementType = ECsProjectileMovement::Simulated;// Data_Projectile->GetMovementType();

	// Simulated
	if (MovementType == ECsProjectileMovement::Simulated)
	{
		const FVector& Direction = ProjectilePayload->GetDirection();
		FRotator Rotation		 = Direction.Rotation();

		TeleportTo(ProjectilePayload->GetLocation(), Rotation, false, true);
	}

	// Trail FX
	if (ICsData_ProjectileTrailVisual* VisualData = FCsLibrary_Data_Projectile::GetSafeInterfaceChecked<ICsData_ProjectileTrailVisual>(Context, Data))
	{
		const FCsFX& TrailFX     = VisualData->GetTrailFX();
		UNiagaraSystem* FXSystem = TrailFX.Get();

		checkf(FXSystem, TEXT("%s: FXSystem is NULL for Visual Data inteface: ICsData_ProjectileTrailVisual"), *Context);

		// Get Manager
		UCsManager_FX_Actor* Manager_FX_Actor = UCsManager_FX_Actor::Get(GetWorld()->GetGameState());
		// Get Payload
		FCsFXPooledPayloadImpl* FXPayload = Manager_FX_Actor->AllocatePayload<FCsFXPooledPayloadImpl>(TrailFX.Type);
		// Set appropriate data on Payload
		FXPayload->Owner					= this;
		FXPayload->Parent					= MeshComponent;
		FXPayload->FXSystem					= FXSystem;
		FXPayload->DeallocateMethod			= TrailFX.DeallocateMethod;
		FXPayload->LifeTime					= TrailFX.LifeTime;
		FXPayload->AttachmentTransformRules = TrailFX.AttachmentTransformRules;
		FXPayload->Transform				= TrailFX.Transform;
		// Spawn FX
		TrailFXPooled = const_cast<FCsFXActorPooled*>(Manager_FX_Actor->Spawn(TrailFX.Type, FXPayload));
	}

	// Simulated
	if (MovementType == ECsProjectileMovement::Simulated)
	{
		MovementComponent->InitialSpeed			  = Data->GetInitialSpeed();
		MovementComponent->MaxSpeed				  = Data->GetMaxSpeed();
		MovementComponent->Velocity				  = MovementComponent->InitialSpeed * ProjectilePayload->GetDirection();
		MovementComponent->ProjectileGravityScale = Data->GetGravityScale();
	}
}

void ACsProjectilePooledImpl::OnLaunch_SetModifiers(ICsPayload_Projectile* Payload)
{
	using namespace NCsProjectilePooledImplCached;

	const FString& Context = Str::OnLaunch_SetModifiers;

	// ICsPayload_ProjectileModiferDamage
	if (ICsPayload_ProjectileModifierDamage* DmgModifierPayload = FCsLibrary_Payload_Projectile::GetSafeInterfaceChecked<ICsPayload_ProjectileModifierDamage>(Context, Payload))
	{
		const TArray<ICsDamageModifier*> Modifiers = DmgModifierPayload->GetDamageModifiers();

		DamageModifiers.Reserve(FMath::Max(DamageModifiers.Max(), Modifiers.Num()));

		UCsManager_Damage* Manager_Damage = UCsManager_Damage::Get(GetWorld()->GetGameState());

		for (const ICsDamageModifier* From : Modifiers)
		{
			DamageModifiers.Add(Manager_Damage->CreateCopyOfModifier(Context, From));
		}
	}
}

// Damage
#pragma region

const FCsResource_DamageEvent* ACsProjectilePooledImpl::OnHit_CreateDamageEvent(const FHitResult& HitResult)
{
	using namespace NCsProjectilePooledImplCached;

	const FString& Context = Str::OnHit_CreateDamageEvent;

	// ICsData_ProjectileDamage
	ICsData_ProjectileDamage* PrjDamageData = FCsLibrary_Data_Projectile::GetInterfaceChecked<ICsData_ProjectileDamage>(Context, Data);
	// Get Damage Data
	ICsData_Damage* DamageData = PrjDamageData->GetDamageData();

	return OnHit_CreateDamageEvent(HitResult, DamageData);
}

const FCsResource_DamageEvent* ACsProjectilePooledImpl::OnHit_CreateDamageEvent(const FHitResult& HitResult, ICsData_Damage* DamageData)
{
	using namespace NCsProjectilePooledImplCached;

	const FString& Context = Str::OnHit_CreateDamageEvent;

	checkf(DamageData, TEXT("%s: DamageData is NULL."), *Context);

	UObject* ContextRoot			  = GetWorld()->GetGameState();
	UCsManager_Damage* Manager_Damage = UCsManager_Damage::Get(ContextRoot);

	// Get Container from Manager_Damage
	FCsResource_DamageEvent* Container = Manager_Damage->AllocateEvent();
	ICsDamageEvent* Event			   = Container->Get();

	FCsDamageEventImpl* EventImpl = FCsLibrary_DamageEvent::PureStaticCastChecked<FCsDamageEventImpl>(Context, Event);

		// Value
	EventImpl->DamageValue.CopyFrom(ContextRoot, DamageData->GetValue());
	ICsDamageValue* DamageValue = EventImpl->DamageValue.Value;

		// Range
	ICsDamageRange* DamageRange = nullptr;

	if (const ICsDamageRange* Range = Manager_Damage->GetRange(Context, DamageData))
	{
		EventImpl->DamageRange.CopyFrom(ContextRoot, Range);
		DamageRange = EventImpl->DamageRange.Range;
	}

	// Apply Damage Modifiers
	for (FCsResource_DamageModifier* Modifier : DamageModifiers)
	{
		Manager_Damage->ModifyValue(Context, Modifier->Get(), DamageData, DamageValue);

		if (DamageRange)
		{
			Manager_Damage->ModifyRange(Context, Modifier->Get(), DamageData, DamageRange);
		}
	}

	EventImpl->Data			= DamageData;
	EventImpl->Instigator	= Cache->GetInstigator();
	EventImpl->Causer		= this;
	EventImpl->Origin		= HitResult;
	EventImpl->HitResult	= HitResult;

	return Container;
}

#pragma endregion Damage