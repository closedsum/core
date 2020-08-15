// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsProjectilePooledImpl.h"
#include "CsPrj.h"

// CVar
#include "Managers/Projectile/CsCVars_Projectile.h"
// Library
#include "Library/CsLibrary_Common.h"
#include "Managers/Pool/Cache/CsLibrary_PooledObjectCache.h"
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
#include "Data/CsLibrary_Data_Projectile.h"
#include "Managers/Damage/Expression/CsLibrary_DamageExpression.h"
#include "Managers/Damage/Event/CsLibrary_DamageEvent.h"
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
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
#include "Managers/Damage/Shape/CsDamageShape.h"
// Game
#include "GameFramework/GameStateBase.h"

//#define CS_COLLISION_PROJECTILE	ECC_GameTraceChannel2

// Cached
#pragma region

namespace NCsProjectilePooledImplCached
{
	namespace Str
	{
		const FString SetType = TEXT("ACsProjectilePooledImpl::SetType");
		const FString OnHit = TEXT("ACsProjectilePooledImpl::OnHit");
		const FString Update = TEXT("ACsProjectilePooledImpl::Update");
		const FString Deallocate = TEXT("ACsProjectilePooledImpl::Deallocate");
		const FString Launch = TEXT("ACsProjectilePooledImpl::Launch");
		const FString OnAllocate_SetDamageContainersAndTypes = TEXT("ACsProjectilePooledImpl::OnAllocate_SetDamageContainersAndTypes");
		const FString OnHit_GetDamageEventContainer = TEXT("ACsProjectilePooledImpl::OnHit_GetDamageEventContainer");
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
	DamageValueContainer(nullptr),
	DamageValueType(),
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
		UE_LOG(LogCsPrj, Warning, TEXT("%s: Projectile: %s Hit: %s"), *Context, *(GetName()), *(OtherComp->GetName()));
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
		const FCsResource_DamageEvent* Event = OnHit_GetDamageEventContainer(Hit);

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

	// Set Damage Value if the projectile supports damage
	OnAllocate_SetDamageContainersAndTypes();

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
	UCsLibrary_Common::ClearOverrideMaterials(MeshComponent);
	MeshComponent->SetStaticMesh(nullptr);
	MeshComponent->SetVisibility(false);
	MeshComponent->SetHiddenInGame(true);
	MeshComponent->SetComponentTickEnabled(false);
	MeshComponent->Deactivate();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

	// DamageValue
	if (DamageValueContainer)
	{
		UCsManager_Damage::Get(GetWorld()->GetGameState())->DeallocateValue(DamageValueType, DamageValueContainer);

		DamageValueContainer = nullptr;
		DamageValueType = EMCsDamageValue::Get().GetMAX();
	}
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
	ICsProjectilePayload* ProjectilePayload = FCsLibrary_Payload_PooledObject::GetInterfaceChecked<ICsProjectilePayload>(Context, Payload);

	// Get Projectile Cache
	ICsProjectileCache* ProjectileCache = FCsLibrary_PooledObjectCache::GetInterfaceChecked<ICsProjectileCache>(Context, Cache);

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

// Damage
#pragma region

void ACsProjectilePooledImpl::OnAllocate_SetDamageContainersAndTypes()
{
	using namespace NCsProjectilePooledImplCached;

	const FString& Context = Str::OnAllocate_SetDamageContainersAndTypes;

	DamageValueContainer = nullptr;
	DamageValueType		 = EMCsDamageValue::Get().GetMAX();

	// ICsData_ProjectileDamage
	if (ICsData_ProjectileDamage* DamageData = FCsLibrary_Data_Projectile::GetSafeInterfaceChecked<ICsData_ProjectileDamage>(Context, Data))
	{
		// Get Damage Expression
		ICsDamageExpression* DamageExpression = DamageData->GetDamageExpression();

		checkf(DamageExpression, TEXT("%s: DamageExpression is NULL."), *Context);

		// Value
		{
			// Range
			if (ICsDamageShape* DamageShape = FCsLibrary_DamageExpression::GetSafeInterfaceChecked<ICsDamageShape>(Context, DamageExpression))
			{
				DamageValueType = NCsDamageValue::Range;
			}
			// Point
			else
			{
				DamageValueType = NCsDamageValue::Point;
			}

			DamageValueContainer = UCsManager_Damage::Get(GetWorld()->GetGameState())->AllocateValue(DamageValueType);

			// Copy "base" damage
			ICsDamageValue* DamageValue = DamageValueContainer->Get();

			FCsLibrary_DamageValue::CopyChecked(Context, DamageExpression->GetValue(), DamageValue);
		}
		// Range
		{

		}
		// Apply any modifiers
		OnAllocate_ApplyDamageModifier(DamageValueContainer->Get());
	}
}

void ACsProjectilePooledImpl::OnAllocate_ApplyDamageModifier(ICsDamageValue* DamageValue)
{
	// TODO: Potentially have Damage Modifiers "packaged" with Payload
}

const FCsResource_DamageEvent* ACsProjectilePooledImpl::OnHit_GetDamageEventContainer(const FHitResult& HitResult)
{
	using namespace NCsProjectilePooledImplCached;

	const FString& Context = Str::OnHit_GetDamageEventContainer;

	// Get Container from Manager_Damage
	FCsResource_DamageEvent* Container = UCsManager_Damage::Get(GetWorld()->GetGameState())->AllocateEvent();
	ICsDamageEvent* Event			   = Container->Get();

	FCsDamageEventImpl* EventImpl = FCsLibrary_DamageEvent::PureStaticCastChecked<FCsDamageEventImpl>(Context, Event);

	// ICsData_ProjectileDamage
	ICsData_ProjectileDamage* DamageData = FCsLibrary_Data_Projectile::GetInterfaceChecked<ICsData_ProjectileDamage>(Context, Data);
	// Get Damage Expression
	ICsDamageExpression* DamageExpression = DamageData->GetDamageExpression();

	checkf(DamageExpression, TEXT("%s: DamageExpression is NULL."), *Context);

	checkf(DamageValueContainer, TEXT("s: DamageValueContainer is NULL."), *Context);

	EventImpl->DamageValueContainer = DamageValueContainer;
	EventImpl->DamageValueType		= DamageValueType;
	EventImpl->DamageValue			= DamageValueContainer->Get();
	EventImpl->Expression			= DamageExpression;
	EventImpl->Instigator			= Cache->GetInstigator();
	EventImpl->Causer				= this;
	EventImpl->Origin				= HitResult;
	EventImpl->HitResult			= HitResult;

	// Clear reference to DamageValueContainer
	DamageValueContainer = nullptr;
	DamageValueType = EMCsDamageValue::Get().GetMAX();

	return Container;
}

#pragma endregion Damage