// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsProjectilePooledImpl.h"
#include "CsPrj.h"

// CVar
#include "Managers/Projectile/CsCVars_Projectile.h"
// Library
#include "Library/CsLibrary_Common.h"
#include "Material/CsLibrary_Material.h"
#include "Managers/Pool/Cache/CsLibrary_Cache_PooledObject.h"
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
#include "Data/CsLibrary_Data_Projectile.h"
#include "Payload/CsLibrary_Payload_Projectile.h"
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"
#include "Managers/Damage/Event/CsLibrary_DamageEvent.h"
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
#include "Managers/Damage/Modifier/CsLibrary_DamageModifier.h"
#include "Managers/Sound/CsLibrary_Manager_Sound.h"
#include "Managers/FX/Actor/CsLibrary_Manager_FX.h"
// Containers
#include "Containers/CsGetInterfaceMap.h"
// Components
#include "Components/SphereComponent.h"
#include "Managers/Projectile/CsProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
// Managers
#include "Managers/Projectile/CsManager_Projectile.h"
#include "Managers/Damage/CsManager_Damage.h"
// Data
#include "Data/CsData_Projectile.h"
#include "Data/CsData_ProjectileCollision.h"
#include "Data/Visual/CsData_Projectile_VisualStaticMesh.h"
#include "Data/Visual/CsData_Projectile_VisualTrail.h"
#include "Data/Visual/CsData_Projectile_VisualImpact.h"
#include "Data/Sound/CsData_Projectile_SoundImpact.h"
#include "Data/Damage/CsData_ProjectileDamage.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Projectile
#include "Cache/CsCache_ProjectilePooledImpl.h"
#include "Payload/Damage/CsPayload_ProjectileModifierDamage.h"
// FX
#include "Managers/FX/Cache/CsCache_FXImpl.h"
#include "Managers/FX/Payload/CsPayload_FXImpl.h"
#include "Managers/FX/Actor/CsFXActorPooled.h"
// Sound
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"
// Damage
#include "Managers/Damage/Event/CsDamageEventImpl.h"
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"
// Game
#include "GameFramework/GameStateBase.h"
// Scoped
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"

//#define CS_COLLISION_PROJECTILE	ECC_GameTraceChannel2

// Cached
#pragma region

namespace NCsProjectilePooledImpl
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, SetType);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, OnHit);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Update);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Deallocate);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Launch);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, OnLaunch_SetModifiers);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, OnHit_CreateDamageEvent);
		}

		namespace ScopedTimer
		{
			CS_DEFINE_CACHED_STRING(SetCollision, "ACsProjectilePooledImpl::Launch_SetCollision");
			CS_DEFINE_CACHED_STRING(SetTrailVisual, "ACsProjectilePooledImpl::Launch_SetTrailVisual");
		}
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
	using namespace NCsProjectilePooledImpl::NCached;

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
		typedef NCsPooledObject::NCache::FLibrary PooledCacheLibrary;
		typedef NCsProjectile::NCache::FImplPooled CacheImplType;

		CacheImplType* CacheImpl = PooledCacheLibrary::PureStaticCastChecked<CacheImplType>(Context, Cache);

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
	using namespace NCsProjectilePooledImpl::NCached;

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

	// ImpactVisualDataType (NCsProjectile::NData::NVisual::NImpact::IImpact)
	{
		typedef NCsProjectile::NData::NVisual::NImpact::IImpact ImpactVisualDataType;

		if (ImpactVisualDataType* ImpactVisualData = FCsLibrary_Data_Projectile::GetSafeInterfaceChecked<ImpactVisualDataType>(Context, Data))
		{
			typedef NCsFX::NManager::FLibrary FXManagerLibrary;
			typedef NCsPooledObject::NPayload::FImplSlice PayloadImplType;

			PayloadImplType Payload;
			Payload.Instigator = Cache->GetInstigator();

			const FCsFX& ImpactFX = ImpactVisualData->GetImpactFX(SurfaceType);

			FTransform Transform = FTransform::Identity;
			Transform.SetLocation(Hit.Location);
			Transform.SetRotation(Hit.ImpactNormal.Rotation().Quaternion());

			FXManagerLibrary::SpawnChecked(Context, this, &Payload, ImpactFX, Transform);
		}
	}
	// ImpactSoundDataType (NCsProjectile::NData::NSound::NImpact::IImpact)
	{
		typedef NCsProjectile::NData::NSound::NImpact::IImpact ImpactSoundDataType;

		if (ImpactSoundDataType* ImpactSoundData = FCsLibrary_Data_Projectile::GetSafeInterfaceChecked<ImpactSoundDataType>(Context, Data))
		{
			typedef NCsSound::NManager::FLibrary SoundManagerLibrary;
			typedef NCsPooledObject::NPayload::FImplSlice PayloadImplType;

			PayloadImplType Payload;
			Payload.Instigator = Cache->GetInstigator();

			const FCsSound& ImpactSound = ImpactSoundData->GetImpactSound(SurfaceType);

			FTransform Transform = FTransform::Identity;
			Transform.SetLocation(Hit.Location);
			Transform.SetRotation(Hit.ImpactNormal.Rotation().Quaternion());

			SoundManagerLibrary::SpawnChecked(Context, this, &Payload, ImpactSound, Transform);
		}
	}
	// DamageDataType (NCsProjectile::NData::NDamage::IDamage)
	{
		typedef NCsProjectile::NData::NDamage::IDamage DamageDataType;

		if (DamageDataType* DamageData = FCsLibrary_Data_Projectile::GetSafeInterfaceChecked<DamageDataType>(Context, Data))
		{
			typedef NCsDamage::NEvent::FResource DamageEventResourceType;

			const DamageEventResourceType* Event = OnHit_CreateDamageEvent(Hit);

			OnBroadcastDamage_Event.Broadcast(Event->Get());
			OnBroadcastDamageContainer_Event.Broadcast(Event);
		}
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
	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::Update;

	typedef NCsPooledObject::NCache::FLibrary PooledCacheLibrary;
	typedef NCsProjectile::NCache::FImplPooled CacheImplType;

	CacheImplType* CacheImpl = PooledCacheLibrary::PureStaticCastChecked<CacheImplType>(Context, Cache);

	CacheImpl->Update(DeltaTime);
}

#pragma endregion ICsUpdate

void ACsProjectilePooledImpl::ConstructCache()
{
	typedef NCsProjectile::NCache::FImplPooled CacheImplType;

	Cache = new CacheImplType();
}

// ICsPooledObject
#pragma region

#define PooledPayloadType NCsPooledObject::NPayload::IPayload
void ACsProjectilePooledImpl::Allocate(PooledPayloadType* Payload)
{
#undef PooledPayloadType

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
	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::Deallocate;

	IgnoreActors.Reset();

	// FX
	if (TrailFXPooled)
	{
		// Deactivate the Trail FX
		typedef NCsPooledObject::NCache::FLibrary PooledCacheLibrary;
		typedef NCsPooledObject::NCache::ICache CacheType;
		typedef NCsFX::NCache::FImpl CacheImplType;

		CacheType* FXCache		   = TrailFXPooled->GetCache();
		CacheImplType* FXCacheImpl = PooledCacheLibrary::PureStaticCastChecked<CacheImplType>(Context, FXCache);

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
	typedef NCsMaterial::FLibrary MaterialLibrary;

	MaterialLibrary::ClearOverride(MeshComponent);
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

UObject* ACsProjectilePooledImpl::GetOwner() const
{
	return Cache->GetOwner();
}

UObject* ACsProjectilePooledImpl::GetInstigator() const
{
	return Cache->GetInstigator();
}

#pragma endregion ICsProjectile

#define PooledPayloadType NCsPooledObject::NPayload::IPayload
void ACsProjectilePooledImpl::Launch(PooledPayloadType* Payload)
{
#undef PooledPayloadType

	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::Launch;

	checkf(Payload, TEXT("%s: Payload is NULL."), *Context);

	// Get Projectile Payload
	typedef NCsProjectile::NPayload::IPayload PayloadType;
	typedef NCsPooledObject::NPayload::FLibrary PooledPayloadLibrary;

	PayloadType* ProjectilePayload = PooledPayloadLibrary::GetInterfaceChecked<PayloadType>(Context, Payload);

	// Get Projectile Cache
	typedef NCsPooledObject::NCache::FLibrary PooledCacheLibrary;
	typedef NCsProjectile::NCache::ICache CacheType;

	CacheType* ProjectileCache = PooledCacheLibrary::GetInterfaceChecked<CacheType>(Context, Cache);

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
	
	// VisualDataType (NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh)
	{
		typedef NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh VisualDataType;

		if (VisualDataType* VisualData = FCsLibrary_Data_Projectile::GetSafeInterfaceChecked<VisualDataType>(Context, Data))
		{
			// TODO: Allocate Static Mesh Actor and get Static Mesh Component

			MeshComponent->AttachToComponent(CollisionComponent, FAttachmentTransformRules::KeepRelativeTransform);

			UStaticMesh* Mesh = VisualData->GetStaticMesh().Get();

			checkf(Mesh, TEXT("%s: Mesh is NULL from Visual Data interface: ICsData_Projectile_VisualStaticMesh"), *Context);

			MeshComponent->SetStaticMesh(Mesh);
			MeshComponent->SetWorldScale3D(VisualData->GetStaticMesh().Scale);
			MeshComponent->Activate();
			MeshComponent->SetVisibility(true);
			MeshComponent->SetHiddenInGame(false);
			MeshComponent->SetComponentTickEnabled(true);
		}
	}

	const ECsProjectileMovement MovementType = ECsProjectileMovement::Simulated;// Data_Projectile->GetMovementType();

	// Simulated
	if (MovementType == ECsProjectileMovement::Simulated)
	{
		const FVector& Direction = ProjectilePayload->GetDirection();
		FRotator Rotation		 = Direction.Rotation();

		TeleportTo(ProjectilePayload->GetLocation(), Rotation, false, true);
	}

	// Trail FX
	{
		const FString& ScopeName		   = ScopedTimer::SetTrailVisual;
		const FECsScopedGroup& ScopedGroup = NCsScopedGroup::Projectile;
		const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogProjectileScopedTimerLaunchSetTrailVisual;

		CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);
		
		typedef NCsProjectile::NData::NVisual::NTrail::ITrail VisualDataType;

		if (VisualDataType* VisualData = FCsLibrary_Data_Projectile::GetSafeInterfaceChecked<VisualDataType>(Context, Data))
		{
			typedef NCsFX::NManager::FLibrary FXManagerLibrary;
			typedef NCsPooledObject::NPayload::FImplSlice PayloadImplType;

			PayloadImplType PayloadImpl;
			PayloadImpl.Owner = this;
			PayloadImpl.Parent = MeshComponent;

			const FCsFX& TrailFX = VisualData->GetTrailFX();

			TrailFXPooled = const_cast<FCsFXActorPooled*>(FXManagerLibrary::SpawnChecked(Context, this, &PayloadImpl, TrailFX));
		}
	}

	// CollisionDataType (NCsProjectile::NData::NCollision::ICollision)
	{
		const FString& ScopeName		   = ScopedTimer::SetCollision;
		const FECsScopedGroup& ScopedGroup = NCsScopedGroup::Projectile;
		const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogProjectileScopedTimerLaunchSetCollision;

		CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

		typedef NCsProjectile::NData::NCollision::ICollision CollisionDataType;

		if (CollisionDataType* CollisionData = FCsLibrary_Data_Projectile::GetSafeInterfaceChecked<CollisionDataType>(Context, Data))
		{
			const FCsCollisionPreset& CollisionPreset = CollisionData->GetCollisionPreset();

			if (CollisionPreset.CollisionEnabled != ECollisionEnabled::NoCollision)
			{
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

				CollisionComponent->Activate();
				CollisionComponent->SetComponentTickEnabled(true);

				CollisionComponent->SetCollisionEnabled(CollisionPreset.CollisionEnabled);
			}
		}
	}
	
	SetActorTickEnabled(true);

	// Simulated
	if (MovementType == ECsProjectileMovement::Simulated)
	{
		MovementComponent->InitialSpeed			  = Data->GetInitialSpeed();
		MovementComponent->MaxSpeed				  = Data->GetMaxSpeed();
		MovementComponent->Velocity				  = MovementComponent->InitialSpeed * ProjectilePayload->GetDirection();
		MovementComponent->ProjectileGravityScale = Data->GetGravityScale();
	}
}

#define PayloadType NCsProjectile::NPayload::IPayload
void ACsProjectilePooledImpl::OnLaunch_SetModifiers(PayloadType* Payload)
{
#undef PayloadType

	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::OnLaunch_SetModifiers;

	// NCsProjectile::NPayload::NModifier::NDamage::IDamage
	{
		typedef NCsProjectile::NPayload::NModifier::NDamage::IDamage ModDamagePayloadType;

		if (ModDamagePayloadType* DmgModifierPayload = FCsLibrary_Payload_Projectile::GetSafeInterfaceChecked<ModDamagePayloadType>(Context, Payload))
		{
			typedef NCsDamage::NModifier::IModifier ModifierType;

			const TArray<ModifierType*> Modifiers = DmgModifierPayload->GetDamageModifiers();

			DamageModifiers.Reset(FMath::Max(DamageModifiers.Max(), Modifiers.Num()));

			UCsManager_Damage* Manager_Damage = UCsManager_Damage::Get(GetWorld()->GetGameState());

			for (const ModifierType* From : Modifiers)
			{
				DamageModifiers.Add(Manager_Damage->CreateCopyOfModifier(Context, From));
			}
		}
	}
}

// Damage
#pragma region

#define DamageEventResourceType NCsDamage::NEvent::FResource
const DamageEventResourceType* ACsProjectilePooledImpl::OnHit_CreateDamageEvent(const FHitResult& HitResult)
{
#undef DamageEventResourceType

	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::OnHit_CreateDamageEvent;

	// ICsData_ProjectileDamage
	ICsData_ProjectileDamage* PrjDamageData = FCsLibrary_Data_Projectile::GetInterfaceChecked<ICsData_ProjectileDamage>(Context, Data);
	// Get Damage Data
	typedef NCsDamage::NData::IData DamageDataType;

	DamageDataType* DamageData = PrjDamageData->GetDamageData();

	return OnHit_CreateDamageEvent(HitResult, DamageData);
}

#define DamageEventResourceType NCsDamage::NEvent::FResource
#define DamageDataType NCsDamage::NData::IData
const DamageEventResourceType* ACsProjectilePooledImpl::OnHit_CreateDamageEvent(const FHitResult& HitResult, DamageDataType* DamageData)
{
	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::OnHit_CreateDamageEvent;

	checkf(DamageData, TEXT("%s: DamageData is NULL."), *Context);

	UObject* ContextRoot			  = GetWorld()->GetGameState();
	UCsManager_Damage* Manager_Damage = UCsManager_Damage::Get(ContextRoot);

	// Get Container from Manager_Damage
	DamageEventResourceType* Container = Manager_Damage->AllocateEvent();

		// Event
	typedef NCsDamage::NEvent::IEvent DamageEventType;

	DamageEventType* Event = Container->Get();
		// Event Impl
	typedef NCsDamage::NEvent::FImpl DamageEventImplType;

	DamageEventImplType* EventImpl = FCsLibrary_DamageEvent::PureStaticCastChecked<DamageEventImplType>(Context, Event);

		// Value
	EventImpl->DamageValue.CopyFrom(ContextRoot, DamageData->GetValue());

	typedef NCsDamage::NValue::IValue DamageValueType;

	DamageValueType* DamageValue = EventImpl->DamageValue.Value;

		// Range
	typedef NCsDamage::NRange::IRange DamageRangeType;

	DamageRangeType* DamageRange = nullptr;

	if (const DamageRangeType* Range = Manager_Damage->GetRange(Context, DamageData))
	{
		EventImpl->DamageRange.CopyFrom(ContextRoot, Range);
		DamageRange = EventImpl->DamageRange.Range;
	}

	// Apply Damage Modifiers
	typedef NCsDamage::NModifier::FResource MoidifierResourceType;

	for (MoidifierResourceType* Modifier : DamageModifiers)
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
#undef DamageEventResourceType
#undef DamageDataType

#pragma endregion Damage