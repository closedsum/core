// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsProjectilePooledImpl.h"
#include "CsPrj.h"

// CVar
#include "Managers/Projectile/CsCVars_Projectile.h"
// Library
#include "Managers/Sound/CsLibrary_Manager_Sound.h"
#include "Managers/FX/Actor/CsLibrary_Manager_FX.h"
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"
#include "Managers/Damage/CsLibrary_Manager_Damage.h"
#include "Data/CsLibrary_Data_Projectile.h"
#include "Payload/CsLibrary_Payload_Projectile.h"
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
#include "Managers/Damage/Modifier/CsLibrary_DamageModifier.h"
#include "Modifier/CsLibrary_ProjectileModifier.h"
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsGetInterfaceMap.h"
// Components
#include "Components/SphereComponent.h"
#include "Managers/Projectile/CsProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
// Data
#include "Data/CsData_Projectile.h"
#include "Data/Collision/CsData_Projectile_Collision.h"
#include "Data/Visual/StaticMesh/CsData_Projectile_VisualStaticMesh.h"
#include "Data/Visual/CsData_Projectile_VisualTrail.h"
#include "Data/Visual/Impact/CsData_Projectile_VisualImpact.h"
#include "Data/Sound/CsData_Projectile_SoundImpact.h"
#include "Data/Damage/CsData_Projectile_Damage.h"
#include "Managers/Damage/Data/CsData_Damage.h"
#include "Managers/Damage/Data/Types/CsData_GetDamageDataType.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Projectile
#include "Cache/CsCache_ProjectileImpl.h"
#include "Payload/Modifier/CsPayload_Projectile_Modifier.h"
#include "Modifier/LifeTime/CsProjectileModifier_LifeTimeImpl.h"
#include "Modifier/Speed/CsProjectileModifier_InitialSpeedImpl.h"
#include "Modifier/Speed/CsProjectileModifier_MaxSpeedImpl.h"
// FX
#include "Managers/FX/Actor/CsFXActorPooled.h"
// Sound
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"
// Damage
#include "Managers/Damage/Value/Point/CsDamageValuePointImpl.h"
#include "Managers/Damage/Value/Range/CsDamageValueRangeImpl.h"
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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Allocate);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Deallocate);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Deallocate_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Launch);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, OnLaunch_SetModifiers);	
		}

		namespace ScopedTimer
		{
			CS_DEFINE_CACHED_STRING(SetCollision, "ACsProjectilePooledImpl::Launch_SetCollision");
			CS_DEFINE_CACHED_STRING(SetTrailVisual, "ACsProjectilePooledImpl::Launch_SetTrailVisual");
		}
	}

	namespace NDamageImpl
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl::FDamageImpl, SetValue);
			}
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
	HitCount(0),
	// ICsPooledObject
	Cache(nullptr),
	CacheImpl(nullptr),
	// ICsProjectile
	Data(nullptr),
	// Launch
	bLaunchOnAllocate(true),
	// FX
	TrailFXPooled(nullptr),
	// Damage
	DamageImpl()
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

	typedef NCsProjectile::NModifier::FAllocated AllocateModifierType;

	for (AllocateModifierType& Modifier : Modifiers)
	{
		Modifier.Clear();
	}
	Modifiers.Reset();
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

	DamageImpl.Outer = this;
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

	check(EMCsProjectile::Get().IsValidEnumChecked(Context, InType));

	if (Type != InType)
	{
		Type = InType;

		typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;

		// Get Data associated with Type
		Data = PrjManagerLibrary::GetDataChecked(Context, this, Type);
	}
}

// Collision
#pragma region

void ACsProjectilePooledImpl::AddIgnoreActor(AActor* Actor)
{
	IgnoreActors.Add(Actor);
}

AActor* ACsProjectilePooledImpl::GetIgnoreActor(const int32& Index)
{
	if (Index >= IgnoreActors.Num())
		return nullptr;
	return IgnoreActors[Index].IsValid() ? IgnoreActors[Index].Get() : nullptr;
}

void ACsProjectilePooledImpl::AddIgnoreComponent(UPrimitiveComponent* Component)
{
	IgnoreComponents.Add(Component);
}

UPrimitiveComponent* ACsProjectilePooledImpl::GetIgnoreComponent(const int32& Index)
{
	if (Index >= IgnoreComponents.Num())
		return nullptr;
	return IgnoreComponents[Index].IsValid() ? IgnoreComponents[Index].Get() : nullptr;
}

bool ACsProjectilePooledImpl::IsIgnored(AActor* Actor) const
{
	if (!Actor)
		return false;

	for (const TWeakObjectPtr<AActor>& A : IgnoreActors)
	{
		if (!A.IsValid())
			continue;

		if (Actor == A.Get())
			return true;
	}
	return false;
}

bool ACsProjectilePooledImpl::IsIgnored(UPrimitiveComponent* Component) const
{
	if (!Component)
		return false;

	for (const TWeakObjectPtr<UPrimitiveComponent>& C : IgnoreComponents)
	{
		if (!C.IsValid())
			continue;

		if (Component == C.Get())
			return true;
	}
	return false;
}

void ACsProjectilePooledImpl::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::OnHit;

	if (IsIgnored(OtherActor))
		return;

	if (IsIgnored(OtherComp))
		return;

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogProjectileCollision))
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

	typedef NCsProjectile::NData::FLibrary PrjDataLibrary;

	// ImpactVisualDataType (NCsProjectile::NData::NVisual::NImpact::IImpact)
	{
		typedef NCsProjectile::NData::NVisual::NImpact::IImpact ImpactVisualDataType;

		if (ImpactVisualDataType* ImpactVisualData = PrjDataLibrary::GetSafeInterfaceChecked<ImpactVisualDataType>(Context, Data))
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

		if (ImpactSoundDataType* ImpactSoundData = PrjDataLibrary::GetSafeInterfaceChecked<ImpactSoundDataType>(Context, Data))
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

		if (DamageDataType* DamageData = PrjDataLibrary::GetSafeInterfaceChecked<DamageDataType>(Context, Data))
		{
			// NOTE: For now reset and apply the modifiers on each hit.
			// FUTURE: Look into having additional rules on how the modifiers are applied
			
			// Apply Modifiers
			DamageImpl.SetValue(DamageData->GetDamageData());

			typedef NCsDamage::NModifier::FLibrary DamageModifierLibrary;

			DamageModifierLibrary::ConditionalModifyChecked(Context, DamageImpl.Modifiers, DamageImpl.GetValue());

			typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

			DamageManagerLibrary::ProcessDataChecked(Context, this, DamageImpl.GetValue(), DamageData->GetDamageData(), GetCache()->GetInstigator(), this, Hit);
		}
	}
	// GetDamageDataTypeDataType (NCsData::IGetDamageDataType)
	{
		typedef NCsData::IGetDamageDataType GetDamageDataTypeDataType;

		if (GetDamageDataTypeDataType* GetDamageDataType = PrjDataLibrary::GetSafeInterfaceChecked<GetDamageDataTypeDataType>(Context, Data))
		{
			typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;
			typedef NCsDamage::NData::IData DamageDataType;

			DamageDataType* DamageData = DamageManagerLibrary::GetDataChecked(Context, this, GetDamageDataType);

			// NOTE: For now reset and apply the modifiers on each hit.
			// FUTURE: Look into having additional rules on how the modifiers are applied

			// Apply Modifiers
			DamageImpl.SetValue(DamageData);

			typedef NCsDamage::NModifier::FLibrary DamageModifierLibrary;

			DamageModifierLibrary::ConditionalModifyChecked(Context, DamageImpl.Modifiers, DamageImpl.GetValue());

			typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

			DamageManagerLibrary::ProcessDataChecked(Context, this, DamageImpl.GetValue(), DamageData, GetCache()->GetInstigator(), this, Hit);
		}
	}

	// CollisionDataType (NCsProjectile::NData::NCollision::ICollision)
	typedef NCsProjectile::NData::NCollision::ICollision CollisionDataType;

	if (CollisionDataType* CollisionData = PrjDataLibrary::GetInterfaceChecked<CollisionDataType>(Context, Data))
	{
		if (CollisionData->IgnoreHitObjectAfterHit())
		{
			// Actor
			if (OtherActor)
			{
				AddIgnoreActor(OtherActor);
				CollisionComponent->MoveIgnoreActors.Add(OtherActor);
			}
			// Component
			if (OtherComp)
			{
				AddIgnoreComponent(OtherComp);
				CollisionComponent->MoveIgnoreComponents.Add(OtherComp);
			}
		}
	}

	--HitCount;

	OnHit_Internal(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	if (bDeallocateOnHit && HitCount <= 0)
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
	CacheImpl->Update(DeltaTime);
}

#pragma endregion ICsUpdate

void ACsProjectilePooledImpl::ConstructCache()
{
	typedef NCsProjectile::NCache::FImpl CacheImplType;

	CacheImpl = new CacheImplType();
	Cache	  = CacheImpl;
}

// ICsPooledObject
#pragma region

#define PooledPayloadType NCsPooledObject::NPayload::IPayload
void ACsProjectilePooledImpl::Allocate(PooledPayloadType* Payload)
{
#undef PooledPayloadType

	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::Allocate;

	CS_IS_PTR_NULL_CHECKED(Payload)

	// Set Type
	typedef NCsProjectile::NPayload::IPayload PayloadType;
	typedef NCsPooledObject::NPayload::FLibrary PooledPayloadLibrary;

	PayloadType* ProjectilePayload = PooledPayloadLibrary::GetInterfaceChecked<PayloadType>(Context, Payload);

	Type = ProjectilePayload->GetType();

	check(EMCsProjectile::Get().IsValidEnumChecked(Context, Type));

	// Get Data associated with Type
	// TODO: FUTURE: Add to list of preserved changes
	typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;

	Data = PrjManagerLibrary::GetDataChecked(Context, this, Type);

	// TODO: Need to determine best place to set LifeTime from Data

	// Set Data on Cache
	CacheImpl->Allocate(Payload);
	CacheImpl->SetData(Data);
	
	if (bLaunchOnAllocate)
		Launch(ProjectilePayload);
}

void ACsProjectilePooledImpl::Deallocate()
{
	Deallocate_Internal();
	Cache->Deallocate();
}

#pragma endregion ICsPooledObject

// PooledObject
#pragma region

void ACsProjectilePooledImpl::Deallocate_Internal()
{
	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::Deallocate_Internal;

	// FX
	if (TrailFXPooled)
	{
		// Deactivate the Trail FX
		typedef NCsPooledObject::NCache::ICache CacheType;

		CacheType* FXCache = TrailFXPooled->GetCache();

		FXCache->QueueDeallocate();

		TrailFXPooled = nullptr;
	}

	// Collision
	IgnoreActors.Reset(IgnoreActors.Max());
	IgnoreComponents.Reset(IgnoreComponents.Max());

	HitCount = 0;

	CollisionComponent->Deactivate();
	CollisionComponent->MoveIgnoreActors.Reset(CollisionComponent->MoveIgnoreActors.Max());
	CollisionComponent->MoveIgnoreComponents.Reset(CollisionComponent->MoveIgnoreComponents.Max());
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
	Modifiers.Reset(Modifiers.Max());
	DamageImpl.Modifiers.Reset(DamageImpl.Modifiers.Max());

	Cache->Reset();
}

#pragma endregion PooledObject

// ICsProjectile
#pragma region

#define PayloadType NCsProjectile::NPayload::IPayload
void ACsProjectilePooledImpl::Launch(PayloadType* Payload)
{
#undef PayloadType
	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::Launch;

	CS_IS_PTR_NULL_CHECKED(Payload)

	// Set / Cache any Modifiers from the Payload
	OnLaunch_SetModifiers(Payload);

	// LifeTime
	{
		typedef NCsProjectile::NModifier::FLibrary ModifierLibrary;
		typedef NCsProjectile::NModifier::FAllocated AllocatedModifierType;
		typedef NCsProjectile::NModifier::IModifier ModifierType;
		typedef NCsProjectile::NModifier::NLifeTime::FImpl LifeTimeModifierType;

		for (AllocatedModifierType& AllocatedModifier : Modifiers)
		{
			ModifierType* Modifier = AllocatedModifier.Get();

			if (ModifierLibrary::Is<LifeTimeModifierType>(Context, Modifier))
			{
				Modifier->Modify(this);
			}
		}
	}

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
	
	typedef NCsProjectile::NData::FLibrary PrjDataLibrary;

	// VisualDataType (NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh)
	{
		typedef NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh VisualDataType;

		if (VisualDataType* VisualData = PrjDataLibrary::GetSafeInterfaceChecked<VisualDataType>(Context, Data))
		{
			// TODO: Allocate Static Mesh Actor and get Static Mesh Component

			MeshComponent->AttachToComponent(CollisionComponent, FAttachmentTransformRules::KeepRelativeTransform);

			UStaticMesh* Mesh = VisualData->GetStaticMesh().Mesh.GetChecked(Context);

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
		const FVector& Direction = Payload->GetDirection();
		FRotator Rotation		 = Direction.Rotation();

		TeleportTo(Payload->GetLocation(), Rotation, false, true);
	}

	// Trail FX
	{
		const FString& ScopeName		   = ScopedTimer::SetTrailVisual;
		const FECsScopedGroup& ScopedGroup = NCsScopedGroup::Projectile;
		const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogProjectileScopedTimerLaunchSetTrailVisual;

		CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);
		
		typedef NCsProjectile::NData::NVisual::NTrail::ITrail VisualDataType;

		if (VisualDataType* VisualData = PrjDataLibrary::GetSafeInterfaceChecked<VisualDataType>(Context, Data))
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

		if (CollisionDataType* CollisionData = PrjDataLibrary::GetSafeInterfaceChecked<CollisionDataType>(Context, Data))
		{
			const FCsCollisionPreset& CollisionPreset = CollisionData->GetCollisionPreset();

			if (CollisionPreset.CollisionEnabled != ECollisionEnabled::NoCollision)
			{
				typedef NCsProjectile::NPayload::FLibrary ProjectilePayloadLibrary;
				typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;

				PooledPayloadType* PooledPayload = ProjectilePayloadLibrary::GetInterfaceChecked<PooledPayloadType>(Context, Payload);

				// Instigator
				if (AActor* Actor = Cast<AActor>(PooledPayload->GetInstigator()))
					IgnoreActors.Add(Actor);
				// Owner
				if (AActor* Actor = Cast<AActor>(PooledPayload->GetOwner()))
					IgnoreActors.Add(Actor);
				// Parent
				if (AActor* Actor = Cast<AActor>(PooledPayload->GetParent()))
					IgnoreActors.Add(Actor);

				const int32 Count = IgnoreActors.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					AActor* Actor = IgnoreActors[I].IsValid() ? IgnoreActors[I].Get() : nullptr;

					if (!Actor)
						continue;

					CollisionComponent->MoveIgnoreActors.Add(Actor);
				}

				CollisionComponent->SetCollisionObjectType(CollisionPreset.ObjectType);
				CollisionComponent->SetSphereRadius(CollisionData->GetCollisionRadius());
				CollisionComponent->SetCollisionResponseToChannels(CollisionPreset.CollisionResponses);

				CollisionComponent->SetNotifyRigidBodyCollision(CollisionPreset.bSimulationGeneratesHitEvents);
				CollisionComponent->SetGenerateOverlapEvents(CollisionPreset.bGenerateOverlapEvents);

				CollisionComponent->Activate();
				CollisionComponent->SetComponentTickEnabled(true);

				CollisionComponent->SetCollisionEnabled(CollisionPreset.CollisionEnabled);
			}

			HitCount = CollisionData->GetHitCount();
			// TODO: Move to Data
			MovementComponent->bHandleDeflection = false;
		}
	}
	
	SetActorTickEnabled(true);

	// Simulated
	if (MovementType == ECsProjectileMovement::Simulated)
	{
		MovementComponent->InitialSpeed			  = Data->GetInitialSpeed();
		MovementComponent->MaxSpeed				  = Data->GetMaxSpeed();

		// Check to apply any Speed Modifiers
		typedef NCsProjectile::NModifier::FLibrary ModifierLibrary;
		typedef NCsProjectile::NModifier::FAllocated AllocatedModifierType;
		typedef NCsProjectile::NModifier::IModifier ModifierType;

		for (AllocatedModifierType& AllocatedModifier : Modifiers)
		{
			ModifierType* Modifier = AllocatedModifier.Get();

			typedef NCsProjectile::NModifier::NSpeed::NInitial::FImpl InitialSpeedModifierType;
			typedef NCsProjectile::NModifier::NSpeed::NMax::FImpl MaxSpeedModifierType;

			if (ModifierLibrary::Is<InitialSpeedModifierType>(Context, Modifier) ||
				ModifierLibrary::Is<MaxSpeedModifierType>(Context, Modifier))
			{
				Modifier->Modify(this);
			}
		}

		if (MovementComponent->InitialSpeed > MovementComponent->MaxSpeed)
			MovementComponent->InitialSpeed = MovementComponent->MaxSpeed;

		MovementComponent->Velocity				  = MovementComponent->InitialSpeed * Payload->GetDirection();
		MovementComponent->ProjectileGravityScale = Data->GetGravityScale();
	}
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

// Launch
#pragma region

#define PayloadType NCsProjectile::NPayload::IPayload
void ACsProjectilePooledImpl::OnLaunch_SetModifiers(PayloadType* Payload)
{
#undef PayloadType

	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::OnLaunch_SetModifiers;

	// ModifierPayloadType (NCsProjectile::NPayload::NModifier::IModifier)
	{
		typedef NCsProjectile::NPayload::FLibrary PayloadLibrary;
		typedef NCsProjectile::NPayload::NModifier::IModifier ModifierPayloadType;

		if (ModifierPayloadType* ModifierPayload = PayloadLibrary::GetSafeInterfaceChecked<ModifierPayloadType>(Context, Payload))
		{
			typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;
			typedef NCsProjectile::NModifier::IModifier ModifierType;

			PrjManagerLibrary::CreateCopyOfModifiersChecked(Context, this, ModifierPayload->GetModifiers(), Modifiers);

			typedef NCsProjectile::NModifier::FLibrary ModifierLibrary;

			ModifierLibrary::GetDamageModifiersChecked(Context, Modifiers, DamageImpl.Modifiers);
		}
	}
}

#pragma endregion Launch

// Damage
#pragma region

ACsProjectilePooledImpl::FDamageImpl::FDamageImpl() :
	Outer(nullptr),
	Type(),
	ValuePoint(nullptr),
	ValueRange(nullptr),
	Modifiers()
{
	typedef NCsDamage::NValue::NPoint::FImpl PointType;
	typedef NCsDamage::NValue::NRange::FImpl RangeType;

	ValuePoint = new PointType();
	ValueRange = new RangeType();
}

ACsProjectilePooledImpl::FDamageImpl::~FDamageImpl()
{
	delete ValuePoint;
	ValuePoint = nullptr;

	delete ValueRange;
	ValueRange = nullptr;

	Modifiers.Reset();
}

#define DamageDataType NCsDamage::NData::IData
void ACsProjectilePooledImpl::FDamageImpl::SetValue(DamageDataType* InData)
{
#undef DamageDataType

	using namespace NCsProjectilePooledImpl::NDamageImpl::NCached;

	const FString& Context = Str::SetValue;

	typedef NCsDamage::NValue::FLibrary DamageValueLibrary;
	typedef NCsDamage::NValue::IValue ValueType;

	const ValueType* Value = InData->GetValue();
	Type				   = DamageValueLibrary::GetTypeChecked(Context, Value);

	ResetValue();
	DamageValueLibrary::CopyChecked(Context, Value, GetValue());
}

#define ValueType NCsDamage::NValue::IValue
ValueType* ACsProjectilePooledImpl::FDamageImpl::GetValue()
{
#undef ValueType

	// Point
	if (Type == NCsDamageValue::Point)
		return ValuePoint;
	// Range
	if (Type == NCsDamageValue::Range)
		return ValueRange;

	checkf(0, TEXT("ACsProjectilePooledImpl::FDamageImpl::GetValue: No Value associated with Type: %s."), Type.ToChar());
	return nullptr;
}

void ACsProjectilePooledImpl::FDamageImpl::ResetValue()
{
	ValuePoint->Reset();
	ValueRange->Reset();
}

void ACsProjectilePooledImpl::FDamageImpl::Reset()
{
	ResetValue();

	Modifiers.Reset(Modifiers.Max());
}

#pragma endregion Damage