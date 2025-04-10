// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "CsProjectilePooledImpl.h"
#include "CsPrj.h"

// CVar
#include "CsCVars_Projectile.h"
#include "Script/CsCVars_Script.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Library
#include "Managers/Time/CsLibrary_Manager_Time.h"
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Managers/Sound/CsLibrary_Manager_Sound.h"
#include "Managers/FX/Actor/CsLibrary_Manager_FX.h"
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"
#include "Managers/Damage/CsLibrary_Manager_Damage.h"
	// Data
#include "Data/CsLibrary_Data_Projectile.h"
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"
	// Payload
#include "Payload/CsLibrary_Payload_Projectile.h"
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
	// Cache
#include "Cache/CsLibrary_Cache_Projectile.h"
#include "Value/CsLibrary_DamageValue.h"
#include "Modifier/CsLibrary_DamageModifier.h"
#include "Modifier/CsLibrary_ProjectileModifier.h"
	// Modifier
#include "Modifier/CsLibrary_DamageModifier.h"
	// Common
#include "Actor/CsLibrary_Actor.h"
#include "Library/CsLibrary_SkeletalMesh.h"
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/FX/Actor/CsManager_FX.h"
// Settings
#include "Settings/CsTypes_ProjectileSettings.h"
// Data
#include "Data/CsData_Projectile.h"
#include "Data/Launch/CsData_Projectile_Launch.h"
#include "Data/Tracking/CsData_Projectile_Tracking.h"
#include "Data/Collision/CsData_Projectile_Collision.h"
#include "Data/Visual/StaticMesh/CsData_Projectile_VisualStaticMesh.h"
#include "Data/Visual/CsData_Projectile_VisualTrail.h"
#include "Data/Visual/Impact/CsData_Projectile_VisualImpact.h"
#include "Data/Sound/Impact/CsData_Projectile_SoundImpact.h"
#include "Data/Damage/CsData_Projectile_Damage.h"
	// Damage
#include "Managers/Damage/Data/CsData_Damage.h"
#include "Managers/Damage/Data/Types/CsData_GetDamageDataType.h"
#include "Managers/Damage/Data/Types/CsData_GetDamageDataTypes.h"
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"
// Containers
#include "Containers/CsGetInterfaceMap.h"
// Components
#include "Components/SphereComponent.h"
#include "CsProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Projectile
#include "Cache/CsCache_ProjectileImpl.h"
	// Payload
#include "Payload/Collision/CsPayload_Projectile_Collision.h"
#include "Payload/Modifier/CsPayload_Projectile_Modifier.h"
#include "Payload/Modifier/Damage/CsPayload_Projectile_ModifierDamage.h"
#include "Payload/Target/CsPayload_Projectile_Target.h"
#include "Payload/Damage/CsPayload_Projectile_Damage.h"
// Modifier
#include "Modifier/Types/CsGetProjectileModifierType.h"
#include "CsModifier_Int.h"
#include "CsModifier_Float.h"
// FX
#include "Managers/FX/Actor/CsFXActorPooled.h"
// Sound
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"
// Damage
#include "Value/Point/CsDamageValuePointImpl.h"
#include "Value/Range/CsDamageValueRangeImpl.h"
// Scoped
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"
// Physics
#include "PhysicalMaterials/PhysicalMaterial.h"

#if WITH_EDITOR
// Library
	// Common
#include "Library/CsLibrary_World.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsProjectilePooledImpl)

//#define CS_COLLISION_PROJECTILE	ECC_GameTraceChannel2

// Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME(CsProjectilePooledImpl)
	// AActor Interface
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectilePooledImpl, PostInitializeComponents)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectilePooledImpl, SetType)
	// ICsPooledObject
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectilePooledImpl, Allocate)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectilePooledImpl, Deallocate)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectilePooledImpl, Deallocate_Internal)
	// Launch
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectilePooledImpl, Launch)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectilePooledImpl, OnLaunch_SetModifiers)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectilePooledImpl, Launch_Delayed)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectilePooledImpl, Launch_Delayed_Internal)
	// ICsProjectile_Hit
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectilePooledImpl, Hit)
	// ICsProjectile_Tracking
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectilePooledImpl, Tracking_GetDestination)
	// Variables
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectilePooledImpl, AllocateVariables)
	// Collision
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectilePooledImpl, OnHit)
	// Modifier
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectilePooledImpl, ApplyMovementModifiers)
CS_END_CACHED_FUNCTION_NAME

namespace NCsProjectilePooledImpl
{
	namespace NCached
	{
		namespace Str
		{
			// AActor Interface
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, PostInitializeComponents);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, SetType);	
			// ICsPooledObject
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Allocate);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Deallocate);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Deallocate_Internal);
			// Launch
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Launch);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, OnLaunch_SetModifiers);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Launch_Delayed);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Launch_Delayed_Internal);
			// ICsProjectile_Hit
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Hit);
			// ICsProjectile_Tracking
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Tracking_GetDestination);
			// Variables
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, AllocateVariables);
			// Collision
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, OnHit);
			// Modifier
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, ApplyMovementModifiers);
		}

		namespace Name
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(ACsProjectilePooledImpl, Launch_Delayed_Internal);
		}

		namespace ScopedTimer
		{
			CS_DEFINE_CACHED_STRING(SetCollision, "ACsProjectilePooledImpl::Launch_SetCollision");
			CS_DEFINE_CACHED_STRING(SetTrailVisual, "ACsProjectilePooledImpl::Launch_SetTrailVisual");
		}
	}

	namespace NMovementImpl
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl::FMovementImpl, GetInitialSpeed);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl::FMovementImpl, GetMaxSpeed);
			}
		}
	}

	namespace NTrackingImpl
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl::FTrackingImpl, Init);
			}
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
	Generation(0),
	State(NCsProjectile::EState::Inactive),
	// Shutdown
	bShutdown(false),
	// ICsPooledObject
	Cache(nullptr),
	CacheImpl(nullptr),
	OnAllocate_ScriptEvent(),
	OnDeallocate_Start_ScriptEvent(),
	// ICsProjectile
	Data(nullptr),
	// Launch
	bLaunchOnAllocate(true),
	Launch_Delayed_Handle(),
	bLaunchComplete(false),
	// Events
	OnAllocate_Event(),
	OnDeallocate_Start_Event(),
	OnHit_Event(),
	// Variables,
	Variables(nullptr),
	// Movement
	MovementInfo(),
	MovementImpl(),
	bOverride_InitialSpeed(false),
	Override_InitialSpeed(false),
	OnOverride_InitialSpeed_ScriptEvent(),
	bOverride_MaxSpeed(false),
	Override_MaxSpeed(false),
	OnOverride_MaxSpeed_ScriptEvent(),
		// Tracking
	TrackingInfo(),
	TrackingImpl(),
	// Collision
	IgnoreActors(),
	IgnoreComponents(),
	IgnoredHitActors(),
	IgnoredHitComponents(),
	IgnoreIdByTypeMap(),
	bDeallocateOnHit(true),
	HitCount(0),
	// FX
	TrailFXPooled(nullptr),
	bOverride_TrailFX(false),
	OnOverride_TrailFX_ScriptEvent(),
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

using DataType = NCsProjectile::NData::IData;
using PooledCacheType = NCsPooledObject::NCache::ICache;
using CacheImplType = NCsProjectile::NCache::NImpl::FImpl;
using PooledPayloadLibrary = NCsPooledObject::NPayload::FLibrary;
using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
using PooledPayloadImplType = NCsPooledObject::NPayload::FImplSlice;
using PayloadType = NCsProjectile::NPayload::IPayload;
using HitResultType = NCsProjectile::NCollision::NHit::FResult;
using CollisionDataType = NCsProjectile::NData::NCollision::ICollision;
using DamageDataType = NCsDamage::NData::IData;
using ValueType = NCsDamage::NValue::IValue;
using RangeType = NCsDamage::NRange::IRange;

// UObject Interface
#pragma region

void ACsProjectilePooledImpl::BeginDestroy()
{
	Super::BeginDestroy();

	Shutdown();
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

	MovementInfo.Outer = this;
	MovementImpl.Outer = this;
	TrackingInfo.Outer = this;
	TrackingImpl.Outer = this;
	DamageImpl.Outer = this;
}

void ACsProjectilePooledImpl::PostInitializeComponents()
{
	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::PostInitializeComponents;

	Super::PostInitializeComponents();

#if WITH_EDITOR
	if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(this))
	{
		CollisionComponent->OnComponentHit.AddDynamic(this, &ACsProjectilePooledImpl::OnHit);

		CollisionComponent->SetComponentTickEnabled(false);
		MovementComponent->SetComponentTickEnabled(false);
		MeshComponent->SetComponentTickEnabled(false);

		SetActorTickEnabled(false);

		ConstructCache();

		MovementInfo.Outer = this;
		MovementImpl.Outer = this;
		TrackingInfo.Outer = this;
		TrackingImpl.Outer = this;
		DamageImpl.Outer = this;
	}
#endif // #if WITH_EDITOR
}

void ACsProjectilePooledImpl::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	OnTick_HandleCVars(DeltaSeconds);
	/*
	Cache.ElapsedTime += DeltaSeconds;

	OnTick_HandleMovementFunction(DeltaSeconds);
	*/
}

bool ACsProjectilePooledImpl::ShouldTickIfViewportsOnly() const
{
#if WITH_EDITOR
	if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(this))
	{
		return true;
	}
#endif // #if WITH_EDITOR
	return Super::ShouldTickIfViewportsOnly();
}

void ACsProjectilePooledImpl::FellOutOfWorld(const UDamageType& DmgType)
{
	Deallocate_Internal();
	SetActorLocation(FVector3d::ZeroVector);
	Cache->QueueDeallocate();
}

void ACsProjectilePooledImpl::OutsideWorldBounds()
{
	Deallocate_Internal();
	SetActorLocation(FVector3d::ZeroVector);
	Cache->QueueDeallocate();
}

#pragma endregion AActor Interface

void ACsProjectilePooledImpl::OnTick_HandleCVars(const float& DeltaSeconds)
{
#if WITH_EDITOR
	const FCsSettings_Projectile_Debug& Debug = FCsSettings_Projectile_Debug::Get();
	
	Debug.Collision.Draw(this, CsActorLibrary::GetLocationChecked(this), CollisionComponent->GetScaledSphereRadius());
#endif // #if WITH_EDITOR
}

void ACsProjectilePooledImpl::OnTick_HandleMovementFunction(const float& DeltaSeconds)
{
	//UCsData_ProjectileBase* Data			 = Cache.GetData();
	/*
	const ECsProjectileMovement MovementType = ECsProjectileMovement::Simulated;//Data->GetMovementType();

	if (MovementType != ECsProjectileMovement::Function)
		return;

	const FVector3f NextLocation= EvaluateMovementFunction(Cache.ElapsedTime);
	const FVector3f MoveDelta	= NextLocation - GetActorLocation();
	const FQuat4f Rotation		= MoveDelta.ToOrientationQuat();

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
		const FVector3f P0 = EvaluateMovementFunction(T0);
		const float T1	 = CurrentTime + (I + 1) * DeltaTime;
		const FVector3f P1 = EvaluateMovementFunction(T1);

		DrawDebugLine(GetWorld(), P0, P1, FColor::Red, false, DeltaSeconds + 0.005f, 0, Thickness);
	}
	*/
}

FVector3f ACsProjectilePooledImpl::EvaluateMovementFunction(const float &Time)
{
	return FVector3f::ZeroVector;// Cache.GetData()->EvaluateMovementFunction(Time, Cache.Location, Cache.Transform);
}

void ACsProjectilePooledImpl::SetType(const FECsProjectile& InType)
{
	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::SetType;

	check(EMCsProjectile::Get().IsValidEnumChecked(Context, InType));

	if (Type != InType)
	{
		Type = InType;

		// Get Data associated with Type
		Data = CsPrjManagerLibrary::GetDataChecked(Context, GetWorldContext(), Type);
	}
}

// ICsUpdate
#pragma region

void ACsProjectilePooledImpl::Update(const FCsDeltaTime& DeltaTime)
{
	CacheImpl->Update(DeltaTime);
}

#pragma endregion ICsUpdate

// ICsPause
#pragma region

void ACsProjectilePooledImpl::Pause(bool bPaused)
{
	MovementComponent->SetActiveFlag(!bPaused);

	if (bPaused)
		CollisionComponent->Deactivate();
	else
		CollisionComponent->Activate();
}

#pragma endregion ICsPause

// ICsShutdown
#pragma region

void ACsProjectilePooledImpl::Shutdown()
{
	if (Cache)
	{
		delete Cache;
		Cache = nullptr;
	}

	using AllocateModifierType = NCsProjectile::NModifier::FAllocated;

	for (AllocateModifierType& Modifier : Modifiers)
	{
		Modifier.Clear();
	}
	Modifiers.Reset();
	
	bShutdown = true;
}

#pragma endregion ICsShutdown

void ACsProjectilePooledImpl::ConstructCache()
{
	CacheImpl = new CacheImplType();
	Cache	  = CacheImpl;
}

// ICsPooledObject
#pragma region

void ACsProjectilePooledImpl::Allocate(PooledPayloadType* Payload)
{
	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::Allocate;

	CS_IS_PTR_NULL_CHECKED(Payload)

	// Set Type
	PayloadType* ProjectilePayload = PooledPayloadLibrary::GetInterfaceChecked<PayloadType>(Context, Payload);

	Type = ProjectilePayload->GetType();

	Generation = ProjectilePayload->GetGeneration();

	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectile, Type)

	// TODO: Need to determine best place to set LifeTime from Data

	// Set Data on Cache
	CacheImpl->Allocate(Payload);

	// Get Data associated with Type
	// TODO: FUTURE: Add to list of preserved changes
	Data = CsPrjManagerLibrary::GetDataChecked(Context, GetWorldContext(), Type);
	// TODO: Redundant
	CS_EDITOR_EXPR(IsValidChecked_Data(Context));

	CacheImpl->SetData(Data);
	
	// Variables
	AllocateVariables(ProjectilePayload);

	if (bLaunchOnAllocate)
		Launch(ProjectilePayload);

	OnAllocate_Event.Broadcast(this, Payload);
	OnAllocate_ScriptEvent.Broadcast(this);
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

	OnDeallocate_Start_Event.Broadcast(this);
	OnDeallocate_Start_ScriptEvent.Broadcast(this);

	// End any Coroutines
	{
	#if WITH_EDITOR
		if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(this))
		{
			CsCoroutineSchedulerLibrary::SafeEndAndInvalidate(Context, GetWorldContext(), NCsUpdateGroup::GameState, Launch_Delayed_Handle, nullptr);
		}
		else
	#endif // #if WITH_EDITOR
		{
			CsCoroutineSchedulerLibrary::EndAndInvalidateChecked(Context, GetWorldContext(), NCsUpdateGroup::GameState, Launch_Delayed_Handle);
		}
	}

	GetState() = NCsProjectile::EState::Inactive;

	// FX
	if (TrailFXPooled)
	{
		// Deactivate the Trail FX
		PooledCacheType* FXCache = TrailFXPooled->GetCache();

		FXCache->QueueDeallocate();

		TrailFXPooled = nullptr;
	}

	// Collision
	IgnoreActors.Reset(IgnoreActors.Max());
	IgnoreComponents.Reset(IgnoreComponents.Max());
	IgnoredHitActors.Reset(IgnoredHitActors.Max());
	IgnoredHitComponents.Reset(IgnoredHitComponents.Max());

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
	if (Variables)
	{
		TrackingImpl.Reset();
	}

	MovementComponent->StopMovementImmediately();
	MovementComponent->SetComponentTickEnabled(false);
	MovementComponent->Deactivate();

	bLaunchComplete = false;

	// Deallocate attachments

	// Mesh
	CsMaterialLibrary::ClearOverrideChecked(Context, MeshComponent);
	MeshComponent->SetStaticMesh(nullptr);
	MeshComponent->SetVisibility(false);
	MeshComponent->SetHiddenInGame(true);
	MeshComponent->SetComponentTickEnabled(false);
	MeshComponent->Deactivate();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	
	// Modifiers
	Modifiers.Reset(Modifiers.Max());

	DamageImpl.Reset();

	// Variables
	using VariablesLibrary = NCsProjectile::NManager::NVariables::FLibrary;

	if (Variables)
	{
	#if WITH_EDITOR
		if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(this))
		{
			VariablesLibrary::SafeDeallocate(Context, GetWorldContext(), Variables, nullptr);
		}
		else
	#endif // #if WITH_EDITOR
		{
			VariablesLibrary::DeallocateChecked(Context, GetWorldContext(), Variables);
		}

		Variables = nullptr;
	}
	Cache->Reset();
}

int32 ACsProjectilePooledImpl::GetCache_Index()
{
	return Cache->GetIndex();
}

UObject* ACsProjectilePooledImpl::GetCache_Instigator()
{
	return Cache->GetInstigator();
}

#pragma endregion PooledObject

// ICsProjectile
#pragma region

void ACsProjectilePooledImpl::Launch(PayloadType* Payload)
{
	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::Launch;

	CS_IS_PTR_NULL_CHECKED(Payload)

	// Set / Cache any Modifiers from the Payload
	OnLaunch_SetModifiers(Payload);

	// Set Additional Datas
	{
		// Damage
		using DmgPayloadType = NCsProjectile::NPayload::NDamage::IDamage;

		if (const DmgPayloadType* DmgPayload = CsPrjPayloadLibrary::GetSafeInterfaceChecked<DmgPayloadType>(Context, Payload))
		{
			DamageImpl.DataTypes.Append(DmgPayload->GetDamageDataTypes());
		}
	}

	// Launch Params
	using LaunchDataType = NCsProjectile::NData::NLaunch::ILaunch;
	using LaunchParamsType = NCsProjectile::NLaunch::FParams;

	LaunchDataType* LaunchData			 = CsPrjDataLibrary::GetSafeInterfaceChecked<LaunchDataType>(Context, Data);
	const LaunchParamsType* LaunchParams = LaunchData ? &(LaunchData->GetLaunchParams()) : nullptr;

	const bool ShouldDelayLaunch = LaunchParams ? LaunchParams->GetDelay() > 0.0f : false;

	// LifeTime
	{
		float LifeTime = Cache->GetLifeTime();
		float Delay	   = ShouldDelayLaunch ? LaunchParams->GetDelay() : 0.0f;

		LifeTime = CsProjectileModifierLibrary::ModifyFloatChecked(Context, Modifiers, NCsProjectileModifier::LifeTime, LifeTime);

		// TODO: Add Modifier for Delay
		CsProjectileCacheLibrary::SetLifeTimeChecked(Context, Cache, LifeTime + Delay);
	}

	//const ECsProjectileRelevance& Relevance = Cache.Relevance;

	SetActorHiddenInGame(false);

	RootComponent = CollisionComponent;

	// VisualDataType (NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh)
	{
		using VisualDataType = NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh;

		if (VisualDataType* VisualData = CsPrjDataLibrary::GetSafeInterfaceChecked<VisualDataType>(Context, Data))
		{
			// TODO: Allocate Static Mesh Actor and get Static Mesh Component

			MeshComponent->AttachToComponent(CollisionComponent, FAttachmentTransformRules::KeepRelativeTransform);
			MeshComponent->SetRelativeLocation(FVector::ZeroVector);

			using StaticMeshInfoType = NCsProjectile::NVisual::NStaticMesh::FInfo;

			const StaticMeshInfoType& StaticMeshInfo = VisualData->GetStaticMeshInfo();

			UStaticMesh* Mesh = StaticMeshInfo.GetMesh();

			MeshComponent->SetStaticMesh(Mesh);
			MeshComponent->SetWorldScale3D(CsMathLibrary::Convert(StaticMeshInfo.GetScale()));
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
		const FVector Direction = Payload->GetDirection();
		FRotator Rotation		= Direction.Rotation();

		TeleportTo(Payload->GetLocation(), Rotation, false, true);
	}

	// Real Visible
	//if (Relevance == ECsProjectileRelevance::RealVisible)
	{
		MovementComponent->UpdatedComponent = CollisionComponent;
		MovementComponent->Activate();
		MovementComponent->SetComponentTickEnabled(true);
	}

	// Trail FX
	{
		const FString& ScopeName		   = ScopedTimer::SetTrailVisual;
		const FECsScopedGroup& ScopedGroup = NCsScopedGroup::Projectile;
		const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogProjectileScopedTimerLaunchSetTrailVisual;

		CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);
		
#if WITH_EDITOR
		if (bOverride_TrailFX)
		{
			if (CS_CVAR_LOG_IS_SHOWING(LogOverrideFunctions))
			{
				UE_LOG(LogCsPrj, Warning, TEXT("%s: Trail FX is OVERRIDDEN for %s."), *Context, *(GetName()));
			}

			OnOverride_TrailFX_ScriptEvent.Broadcast(this);
		}
		else
#endif // #if WITH_EDITOR
		{
			using VisualDataType = NCsProjectile::NData::NVisual::NTrail::ITrail;

			if (VisualDataType* VisualData = CsPrjDataLibrary::GetSafeInterfaceChecked<VisualDataType>(Context, Data))
			{
				PooledPayloadImplType PayloadImpl;
				PayloadImpl.Owner  = this;

				if (MeshComponent->GetStaticMesh())
					PayloadImpl.Parent = MeshComponent;
				else
					PayloadImpl.Parent = CollisionComponent;

				using TrailInfoType = NCsProjectile::NVisual::NTrail::FInfo;

				const TrailInfoType& TrailInfo = VisualData->GetTrailInfo();

				const FCsFX& FX = TrailInfo.GetFX();

				TrailFXPooled = const_cast<FCsFXActorPooled*>(CsFXManagerLibrary::SpawnChecked(Context, GetWorldContext(), &PayloadImpl, FX));
			}
		}
	}

	// CollisionDataType (NCsProjectile::NData::NCollision::ICollision)
	{
		const FString& ScopeName		   = ScopedTimer::SetCollision;
		const FECsScopedGroup& ScopedGroup = NCsScopedGroup::Projectile;
		const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogProjectileScopedTimerLaunchSetCollision;

		CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

		using CollisionDataType = NCsProjectile::NData::NCollision::ICollision;

		if (CollisionDataType* CollisionData = CsPrjDataLibrary::GetSafeInterfaceChecked<CollisionDataType>(Context, Data))
		{
			const FCsCollisionPreset& CollisionPreset = CollisionData->GetCollisionPreset();

			if (CollisionPreset.CollisionEnabled != ECollisionEnabled::NoCollision)
			{
				PooledPayloadType* PooledPayload = CsPrjPayloadLibrary::GetInterfaceChecked<PooledPayloadType>(Context, Payload);

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

				using CollisionPayloadType = NCsProjectile::NPayload::NCollision::ICollision;

				CollisionPayloadType* CollisionPayload = CsPrjPayloadLibrary::GetInterfaceChecked<CollisionPayloadType>(Context, Payload);

				for (AActor* Actor : CollisionPayload->GetIgnoreActorsOnHit())
				{
					IgnoredHitActors.Add(Actor);
					CollisionComponent->MoveIgnoreActors.Add(Actor);
				}

				for (UPrimitiveComponent* Component : CollisionPayload->GetIgnoreComponentsOnHit())
				{
					IgnoredHitComponents.Add(Component);
					CollisionComponent->MoveIgnoreComponents.Add(Component);
				}

				Variables->CollisionInfo.GetRadius() = CollisionData->GetCollisionRadius();

				const bool ShouldDelayCollision = ShouldDelayLaunch && LaunchParams->GetDelayParams().GetbCollision();

				if (!ShouldDelayCollision)
				{
					CollisionComponent->SetCollisionObjectType(CollisionPreset.ObjectType);
					CollisionComponent->SetSphereRadius(CollisionData->GetCollisionRadius());
					CollisionComponent->SetCollisionResponseToChannels(CollisionPreset.CollisionResponses);

					CollisionComponent->SetNotifyRigidBodyCollision(CollisionPreset.bSimulationGeneratesHitEvents);
					CollisionComponent->SetGenerateOverlapEvents(CollisionPreset.bGenerateOverlapEvents);

					CollisionComponent->UpdateBounds();
					CollisionComponent->Activate();
					CollisionComponent->SetComponentTickEnabled(true);

					CollisionComponent->SetCollisionEnabled(CollisionPreset.CollisionEnabled);
				}
			}

			ApplyHitCountModifiers(Context, CollisionData);
			// TODO: Move to Data
			MovementComponent->bHandleDeflection = false;
		}
	}
	
	SetActorTickEnabled(true);

	if (ShouldDelayLaunch)
	{
		GetState() = NCsProjectile::EState::LaunchDelay;

		FLaunch_Delayed_Payload DelayedPayload;
		DelayedPayload.Direction = Payload->GetDirection();

		Launch_Delayed(DelayedPayload);
	}
	else
	{
		// Movement
		
		// Simulated
		if (MovementType == ECsProjectileMovement::Simulated)
		{
			StartMovementFromModifiers(Context, Payload->GetDirection());
		}
		bLaunchComplete = true;
		GetState() = NCsProjectile::EState::Active;
	}

	TrackingImpl.Init(Payload);
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

// Projectile
#pragma region

UObject* ACsProjectilePooledImpl::GetDataAsObject()
{
	return Data->_getUObject();
}

#pragma endregion Projectile

// Launch
#pragma region

void ACsProjectilePooledImpl::OnLaunch_SetModifiers(const PayloadType* Payload)
{
	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::OnLaunch_SetModifiers;

	// ModifierPayloadType (NCsProjectile::NPayload::NModifier::IModifier)
	{
		using PrjModifierLibrary = NCsProjectile::NManager::NModifier::FLibrary;
		using ModifierPayloadType = NCsProjectile::NPayload::NModifier::IModifier;

		if (const ModifierPayloadType* ModifierPayload = CsPrjPayloadLibrary::GetSafeInterfaceChecked<ModifierPayloadType>(Context, Payload))
		{
			PrjModifierLibrary::CopyChecked(Context, GetWorldContext(), ModifierPayload->GetModifiers(), Modifiers);
		}
	}
	// DmgModifierPayloadType (NCsProjectile::NPayload::NModifier::NDamage::IDamage)
	{
		using DmgModifierLibrary = NCsDamage::NManager::NModifier::FLibrary;
		using DmgModifierPayloadType = NCsProjectile::NPayload::NModifier::NDamage::IDamage;

		if (const DmgModifierPayloadType* DmgModifierPayload = CsPrjPayloadLibrary::GetSafeInterfaceChecked<DmgModifierPayloadType>(Context, Payload))
		{
			DmgModifierLibrary::CopyChecked(Context, GetWorldContext(), DmgModifierPayload->GetDamageModifiers(), DamageImpl.Modifiers);
		}
	}
}

void ACsProjectilePooledImpl::Launch_Delayed(const FLaunch_Delayed_Payload& Payload)
{
	CS_SET_CONTEXT_AS_FUNCTION_NAME(Launch_Delayed);

	// TODO: NOTE: Need a way UpdateGroup is passed via Payload

	CS_COROUTINE_SETUP_UOBJECT(ACsProjectilePooledImpl, Launch_Delayed_Internal, NCsUpdateGroup::GameState, this, GetWorldContext());

	using LaunchDataType = NCsProjectile::NData::NLaunch::ILaunch ;
	using LaunchParamsType = NCsProjectile::NLaunch::FParams;

	LaunchDataType* LaunchData			 = CsPrjDataLibrary::GetSafeInterfaceChecked<LaunchDataType>(Context, Data);
	const LaunchParamsType& LaunchParams = LaunchData->GetLaunchParams();

	CS_COROUTINE_PAYLOAD_PASS_FLOAT_START
	CS_COROUTINE_PAYLOAD_PASS_VECTOR_START
	CS_COROUTINE_PAYLOAD_PASS_FLAG_START

	// Delay
	CS_COROUTINE_PAYLOAD_PASS_FLOAT(LaunchParams.GetDelay());
	// Direction
	CS_COROUTINE_PAYLOAD_PASS_VECTOR(Payload.Direction);
	// Should Update Collision
	CS_COROUTINE_PAYLOAD_PASS_FLAG(LaunchParams.GetDelayParams().GetbCollision());

	Launch_Delayed_Handle = CS_COROUTINE_START(GetWorldContext());
}

char ACsProjectilePooledImpl::Launch_Delayed_Internal(FCsRoutine* R)
{
	CS_SET_CONTEXT_AS_FUNCTION_NAME(Launch_Delayed_Internal);

	CS_COROUTINE_READ_FLOAT_START
	CS_COROUTINE_READ_VECTOR_START
	CS_COROUTINE_READ_FLAG_START
	
	// Delay
	CS_COROUTINE_READ_FLOAT_CONST_REF(R, Delay);
	// Direction
	CS_COROUTINE_READ_VECTOR_CONST_REF(R, Direction);
	// Should Update Collision
	CS_COROUTINE_READ_FLAG_CONST_REF(R, ShouldUpdateCollision);

	CS_COROUTINE_BEGIN(R);

	CS_COROUTINE_WAIT_UNTIL(R, R->GetElapsedTime().Time >= Delay);

	// Movement
	{
		StartMovementFromModifiers(Context, Direction);
	}
	// Collision
	if (ShouldUpdateCollision)
	{
		using namespace NCsProjectilePooledImpl::NCached;

		const FString& ScopeName		   = ScopedTimer::SetCollision;
		const FECsScopedGroup& ScopedGroup = NCsScopedGroup::Projectile;
		const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogProjectileScopedTimerLaunchSetCollision;

		CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

		if (CollisionDataType* CollisionData = CsPrjDataLibrary::GetSafeInterfaceChecked<CollisionDataType>(Context, Data))
		{
			const FCsCollisionPreset& CollisionPreset = CollisionData->GetCollisionPreset();

			if (CollisionPreset.CollisionEnabled != ECollisionEnabled::NoCollision)
			{
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

	bLaunchComplete = true;
	GetState() = NCsProjectile::EState::Active;

	CS_COROUTINE_END(R);
}

#pragma endregion Launch

// ICsProjectile_Movement
#pragma region

void ACsProjectilePooledImpl::Movement_SetLocation(const FVector& Location)
{
	Variables->GetLocation() = GetActorLocation();
}

FVector ACsProjectilePooledImpl::Movement_GetLocation() const
{
	return Variables->GetLocation();
}

void ACsProjectilePooledImpl::Movement_SetRotation(const FRotator& Rotation)
{
	SetActorRotation(Rotation);
}

void ACsProjectilePooledImpl::Movement_SetVelocity(const FVector& Velocity)
{
	MovementComponent->Velocity = Velocity;
}

#pragma endregion ICsProjectile_Movement

// ICsProjectile_Collision
#pragma region

void ACsProjectilePooledImpl::Hit(const HitResultType& Result)
{
	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::Hit;

	UPrimitiveComponent* HitComponent = Result.GetMyComponent();
	AActor* OtherActor				  = Result.GetOtherActor();
	UPrimitiveComponent* OtherComp	  = Result.GetOtherComponent();
	const FVector3f& NormalImpulse	  = Result.NormalImpulse;
	const FHitResult& HitResult		  = Result.Hit;

	if (IsIgnored(Result.OtherType, Result.OtherID))
		return;
	if (IsIgnoredOnHit(OtherActor))
		return;
	if (IsIgnoredOnHit(OtherComp))
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
		UE_LOG(LogCsPrj, Warning, TEXT("-- bBlockingHit: %s"), HitResult.bBlockingHit ? TEXT("True") : TEXT("False"));
		UE_LOG(LogCsPrj, Warning, TEXT("-- bStartPenetrating"), HitResult.bStartPenetrating ? TEXT("True") : TEXT("False"));
		UE_LOG(LogCsPrj, Warning, TEXT("-- Time: %f"), HitResult.Time);
		UE_LOG(LogCsPrj, Warning, TEXT("-- Location: %s"), *(HitResult.Location.ToString()));
		UE_LOG(LogCsPrj, Warning, TEXT("-- ImpactPoint: %s"), *(HitResult.ImpactPoint.ToString()));
		UE_LOG(LogCsPrj, Warning, TEXT("-- Normal: %s"), *(HitResult.Normal.ToString()));
		UE_LOG(LogCsPrj, Warning, TEXT("-- ImpactNormal: %s"), *(HitResult.ImpactNormal.ToString()));
		UE_LOG(LogCsPrj, Warning, TEXT("-- TraceStart: %s"), *(HitResult.TraceStart.ToString()));
		UE_LOG(LogCsPrj, Warning, TEXT("-- TraceEnd: %s"), *(HitResult.TraceEnd.ToString()));
		UE_LOG(LogCsPrj, Warning, TEXT("-- PenetrationDepth: %f"), HitResult.PenetrationDepth);
		UE_LOG(LogCsPrj, Warning, TEXT("-- Item: %d"), HitResult.Item);
		UE_LOG(LogCsPrj, Warning, TEXT("-- PhysMaterial: %s"), HitResult.PhysMaterial.IsValid() ? *(HitResult.PhysMaterial->GetName()) : TEXT("None"));
		UE_LOG(LogCsPrj, Warning, TEXT("-- Actor: %s"), HitResult.HasValidHitObjectHandle() ? *(HitResult.GetActor()->GetName()) : TEXT("None"));
		UE_LOG(LogCsPrj, Warning, TEXT("-- Component: %s"), HitResult.Component.IsValid() ? *(HitResult.Component->GetName()) : TEXT("None"));
		UE_LOG(LogCsPrj, Warning, TEXT("-- BoneName: %s"), HitResult.BoneName.IsValid() ? *(HitResult.BoneName.ToString()) : TEXT("None"));
		UE_LOG(LogCsPrj, Warning, TEXT("-- FaceIndex: %d"), HitResult.FaceIndex);
	}
#endif // #if !UE_BUILD_SHIPPING

	ClearHitObjects();

	// Get Physics Surface
	UPhysicalMaterial* PhysMaterial = HitResult.PhysMaterial.IsValid() ? HitResult.PhysMaterial.Get() : nullptr;
	EPhysicalSurface SurfaceType	= PhysMaterial ? (EPhysicalSurface)PhysMaterial->SurfaceType : EPhysicalSurface::SurfaceType_Default;

	// ImpactVisualDataType (NCsProjectile::NData::NVisual::NImpact::IImpact)
	OnHit_TryImpactVisual(Context, HitComponent, OtherActor, OtherComp, CsMathLibrary::Convert(NormalImpulse), HitResult);
	// ImpactSoundDataType (NCsProjectile::NData::NSound::NImpact::IImpact)
	{
		using ImpactSoundDataType = NCsProjectile::NData::NSound::NImpact::IImpact;
		using ImpactSoundInfoType = NCsProjectile::NImpact::NSound::FInfo;

		if (ImpactSoundDataType* ImpactSoundData = CsPrjDataLibrary::GetSafeInterfaceChecked<ImpactSoundDataType>(Context, Data))
		{
			const ImpactSoundInfoType& Info = ImpactSoundData->GetImpactSoundInfo(SurfaceType);

			if (Info.GetbSound())
			{
				PooledPayloadImplType Payload;
				Payload.Instigator = Cache->GetInstigator();

				FTransform Transform = FTransform::Identity;
				Transform.SetLocation(HitResult.Location);
				Transform.SetRotation(HitResult.ImpactNormal.Rotation().Quaternion());

				CsSoundManagerLibrary::SpawnChecked(Context, GetWorldContext(), &Payload, Info.GetSound(), Transform);
			}
		}
	}
	// DamageDataType (NCsProjectile::NData::NDamage::IDamage)

		// TODO: Deprecate
	{
		using PrjDamageDataType = NCsProjectile::NData::NDamage::IDamage;

		if (PrjDamageDataType* PrjDamageData = CsPrjDataLibrary::GetSafeInterfaceChecked<PrjDamageDataType>(Context, Data))
		{
			DamageDataType* DamageData = PrjDamageData->GetDamageData();

			static TArray<DamageDataType*> DamageDatas;
			DamageDatas.Add(DamageData);
			CsDamageManagerLibrary::AddDatasChecked(Context, GetWorldContext(), DamageImpl.DataTypes, DamageDatas);

			static TArray<FECsDamageData> DamageDataTypes;
			DamageDataTypes.Add(CsDamageManagerLibrary::GetDataTypeChecked(Context, GetWorldContext(), DamageData));
			DamageDataTypes.Append(DamageImpl.DataTypes);

			// NOTE: For now reset and apply the modifiers on each hit.
			// FUTURE: Look into having additional rules on how the modifiers are applied

			const int32 Count = DamageDataTypes.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				DamageData = DamageDatas[I];

				// Apply Modifiers
				DamageImpl.SetValue(DamageData);

				using ProcessPayloadType = NCsDamage::NData::NProcess::FPayload;

				static ProcessPayloadType ProcessPayload;

				ProcessPayload.Value	  = DamageImpl.GetValue();
				ProcessPayload.Type		  = DamageDataTypes[I];
				ProcessPayload.Data		  = DamageData;
				ProcessPayload.Instigator = GetCache()->GetInstigator();
				ProcessPayload.Causer	  = this;
				// TODO: Maybe store this value each tick / update
				ProcessPayload.Direction  = MovementComponent->Velocity.GetSafeNormal();
				ProcessPayload.HitResult  = HitResult;

				CsDamageModifierLibrary::CopyChecked(Context, DamageImpl.Modifiers, ProcessPayload.Modifiers);
				CsDamageManagerLibrary::ProcessDataChecked(Context, GetWorldContext(), ProcessPayload);

				ProcessPayload.Reset();

				DamageDatas.RemoveAt(I, 1, false);
				DamageDataTypes.RemoveAt(I, 1, false);
			}
		}
	}
	// CsGetDamageDataTypeDataType (NCsData::IGetDamageDataType)
	{
		if (CsGetDamageDataTypeDataType* GetDamageDataType = CsPrjDataLibrary::GetSafeInterfaceChecked<CsGetDamageDataTypeDataType>(Context, Data))
		{
			DamageDataType* DamageData = CsDamageManagerLibrary::GetDataChecked(Context, GetWorldContext(), GetDamageDataType);

			static TArray<DamageDataType*> DamageDatas;
			DamageDatas.Add(DamageData);
			CsDamageManagerLibrary::AddDatasChecked(Context, GetWorldContext(), DamageImpl.DataTypes, DamageDatas);

			static TArray<FECsDamageData> DamageDataTypes;
			DamageDataTypes.Add(GetDamageDataType->GetDamageDataType());
			DamageDataTypes.Append(DamageImpl.DataTypes);

			// NOTE: For now reset and apply the modifiers on each hit.
			// FUTURE: Look into having additional rules on how the modifiers are applied

			const int32 Count = DamageDataTypes.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				DamageData = DamageDatas[I];

				// Apply Modifiers
				DamageImpl.SetValue(DamageData);

				using ProcessPayloadType = NCsDamage::NData::NProcess::FPayload;

				static ProcessPayloadType ProcessPayload;

				ProcessPayload.Value	  = DamageImpl.GetValue();
				ProcessPayload.Type		  = DamageDataTypes[I];
				ProcessPayload.Data		  = DamageData;
				ProcessPayload.Instigator = GetCache()->GetInstigator();
				ProcessPayload.Causer	  = this;
				// TODO: Maybe store this value each tick / update
				ProcessPayload.Direction  = MovementComponent->Velocity.GetSafeNormal();
				ProcessPayload.HitResult  = HitResult;

				CsDamageModifierLibrary::CopyChecked(Context, DamageImpl.Modifiers, ProcessPayload.Modifiers);
				CsDamageManagerLibrary::ProcessDataChecked(Context, GetWorldContext(), ProcessPayload);

				ProcessPayload.Reset();

				DamageDatas.RemoveAt(I, 1, false);
				DamageDataTypes.RemoveAt(I, 1, false);
			}
		}
	}
	// CsGetDamageDataTypesDataType (NCsData::IGetDamageDataTypes)
	{
		if (CsGetDamageDataTypesDataType* GetDamageDataTypes = CsPrjDataLibrary::GetSafeInterfaceChecked<CsGetDamageDataTypesDataType>(Context, Data))
		{
			static TArray<DamageDataType*> DamageDatas;
			CsDamageManagerLibrary::GetDatasChecked(Context, GetWorldContext(), GetDamageDataTypes, DamageDatas);
			CsDamageManagerLibrary::AddDatasChecked(Context, GetWorldContext(), DamageImpl.DataTypes, DamageDatas);

			static TArray<FECsDamageData> DamageDataTypes;
			DamageDataTypes.Append(GetDamageDataTypes->GetDamageDataTypes());
			DamageDataTypes.Append(DamageImpl.DataTypes);

			// NOTE: For now reset and apply the modifiers on each hit.
			// FUTURE: Look into having additional rules on how the modifiers are applied

			const int32 Count = DamageDataTypes.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				DamageDataType* DamageData = DamageDatas[I];

				// Apply Modifiers
				DamageImpl.SetValue(DamageData);

				using ProcessPayloadType = NCsDamage::NData::NProcess::FPayload;

				static ProcessPayloadType ProcessPayload;

				ProcessPayload.Value	  = DamageImpl.GetValue();
				ProcessPayload.Type		  = DamageDataTypes[I];
				ProcessPayload.Data		  = DamageData;
				ProcessPayload.Instigator = GetCache()->GetInstigator();
				ProcessPayload.Causer	  = this;
				// TODO: Maybe store this value each tick / update
				ProcessPayload.Direction  = MovementComponent->Velocity.GetSafeNormal();
				ProcessPayload.HitResult  = HitResult;

				CsDamageModifierLibrary::CopyChecked(Context, DamageImpl.Modifiers, ProcessPayload.Modifiers);
				CsDamageManagerLibrary::ProcessDataChecked(Context, GetWorldContext(), ProcessPayload);

				ProcessPayload.Reset();

				DamageDatas.RemoveAt(I, 1, false);
				DamageDataTypes.RemoveAt(I, 1, false);
			}
		}
	}

	// CollisionDataType (NCsProjectile::NData::NCollision::ICollision)
	using CollisionDataType = NCsProjectile::NData::NCollision::ICollision;

	if (CollisionDataType* CollisionData = CsPrjDataLibrary::GetSafeInterfaceChecked<CollisionDataType>(Context, Data))
	{
		if (CollisionData->IgnoreHitObjectAfterHit())
		{
			// ID
			if (Result.OtherType != INDEX_NONE &&
				Result.OtherID != INDEX_NONE)
			{
				AddIgnored(Result.OtherType, Result.OtherID);
			}
			// Actor
			if (OtherActor)
			{
				AddIgnoredHitActor(OtherActor);
				AddIgnoreActor(OtherActor);
				CollisionComponent->MoveIgnoreActors.Add(OtherActor);
			}
			// Component
			if (OtherComp)
			{
				AddIgnoredHitComponent(OtherComp);
				AddIgnoreComponent(OtherComp);
				CollisionComponent->MoveIgnoreComponents.Add(OtherComp);
			}
		}
	}

	--HitCount;

	OnHit_Internal(HitComponent, OtherActor, OtherComp, CsMathLibrary::Convert(NormalImpulse), HitResult);

	if (bDeallocateOnHit && HitCount <= 0)
		Cache->QueueDeallocate();

	OnHit_Event.Broadcast(this, HitResult);
}

#pragma endregion ICsProjectile_Collision

// ICsProjectile_Tracking
#pragma region

FVector ACsProjectilePooledImpl::Tracking_GetDestination() const
{
	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::Tracking_GetDestination;

	using TrackingDestinationType = NCsProjectile::NTracking::EDestination;

	// Component
	if (TrackingInfo.GetDestinationType() == TrackingDestinationType::Object)
	{
		return TrackingInfo.GetComponent()->GetComponentLocation();
	}
	// Bone
	if (TrackingInfo.GetDestinationType() == TrackingDestinationType::Bone)
	{
		return TrackingInfo.GetMeshComponent()->GetSocketLocation(TrackingInfo.GetBone());
	}
	// Location
	if (TrackingInfo.GetDestinationType() == TrackingDestinationType::Location)
	{
		return TrackingInfo.GetLocation();
	}
	check(0);
	return FVector::ZeroVector;
}

#pragma endregion ICsProjectile_Tracking

#if WITH_EDITOR

const UObject* ACsProjectilePooledImpl::GetWorldContext() const
{
	if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(this))
	{
		return Cache->GetInstigator();
	}
	return this;
}

#endif // #if WITH_EDITOR

// Variables
#pragma region

void ACsProjectilePooledImpl::AllocateVariables(const PayloadType* Payload)
{
	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::AllocateVariables;

	using VariablesLibrary = NCsProjectile::NManager::NVariables::FLibrary;
	using VariablesPayloadType = NCsProjectile::NVariables::NAllocate::FPayload;

	VariablesPayloadType VariablesPayload;
	VariablesPayload.Projectile	= this;
	VariablesPayload.Type		= Type;
	VariablesPayload.Location	= Payload->GetLocation();
	VariablesPayload.Direction  = Payload->GetDirection();

	using CollisionDataType = NCsProjectile::NData::NCollision::ICollision;

	if (CollisionDataType* CollisionData = CsPrjDataLibrary::GetSafeInterfaceChecked<CollisionDataType>(Context, Data))
	{
		VariablesPayload.CollisionRadius	 = CollisionData->GetCollisionRadius();
		VariablesPayload.CollisionHalfHeight = CollisionData->GetCollisionRadius();
	}

	Variables = VariablesLibrary::AllocateChecked(Context, GetWorldContext(), VariablesPayload);
}

#pragma endregion Variables

// Movement
#pragma region

float ACsProjectilePooledImpl::FMovementImpl::CalculateInitialSpeed(const EStart& Start) const
{
	using namespace NCsProjectilePooledImpl::NMovementImpl::NCached;

	const FString& Context = Str::GetInitialSpeed;

#if WITH_EDITOR
	if (Outer->GetbOverride_InitialSpeed())
	{
		if (CS_CVAR_LOG_IS_SHOWING(LogOverrideFunctions))
		{
			UE_LOG(LogCsPrj, Warning, TEXT("%s: Initial Speed is OVERRIDDEN for %s."), *Context, *(Outer->GetName()));
		}
		Outer->OnOverride_InitialSpeed_ScriptEvent.Broadcast(Outer);
		return Outer->GetOverride_InitialSpeed();
	}
	else
#endif // #if WITH_EDITOR
	{
		// From Data
		if (Start == EStart::FromData)
		{
			return Outer->GetData()->GetInitialSpeed();
		}
		// From Modifiers
		if (Start == EStart::FromModifiers)
		{
			float InitialSpeed = Outer->GetData()->GetInitialSpeed();

			// Check to apply any Movement Modifiers
			InitialSpeed = CsProjectileModifierLibrary::ModifyFloatChecked(Context, Outer->GetModifiers(), NCsProjectileModifier::InitialSpeed, InitialSpeed);
			return InitialSpeed;
		}
	}
	checkf(0, TEXT("%s: Failed to Get Initial Speed."), *Context);
	return 0.0f;
}

float ACsProjectilePooledImpl::FMovementImpl::CalculateMaxSpeed(const EStart& Start) const
{
	using namespace NCsProjectilePooledImpl::NMovementImpl::NCached;

	const FString& Context = Str::GetMaxSpeed;

#if WITH_EDITOR
	if (Outer->GetbOverride_MaxSpeed())
	{
		if (CS_CVAR_LOG_IS_SHOWING(LogOverrideFunctions))
		{
			UE_LOG(LogCsPrj, Warning, TEXT("%s: Max Speed is OVERRIDDEN for %s."), *Context, *(Outer->GetName()));
		}
		Outer->OnOverride_MaxSpeed_ScriptEvent.Broadcast(Outer);
		return Outer->GetOverride_MaxSpeed();
	}
	else
#endif // #if WITH_EDITOR
	{
		// From Data
		if (Start == EStart::FromData)
		{
			return Outer->GetData()->GetMaxSpeed();
		}
		// From Modifiers
		if (Start == EStart::FromModifiers)
		{
			float MaxSpeed = Outer->GetData()->GetMaxSpeed();

			// Check to apply any Movement Modifiers
			MaxSpeed = CsProjectileModifierLibrary::ModifyFloatChecked(Context, Outer->GetModifiers(), NCsProjectileModifier::MaxSpeed, MaxSpeed);
			return MaxSpeed;
		}
	}
	checkf(0, TEXT("%s: Failed to Get Max Speed."), *Context);
	return 0.0f;
}

void ACsProjectilePooledImpl::StartMovementFromData(const FVector& Direction)
{
	using StartType = ACsProjectilePooledImpl::FMovementImpl::EStart;

	MovementInfo.GetInitialSpeed() = MovementImpl.CalculateInitialSpeed(StartType::FromData);
	MovementInfo.GetMaxSpeed()	   = MovementImpl.CalculateMaxSpeed(StartType::FromData);

	if (MovementInfo.GetInitialSpeed() > MovementInfo.GetMaxSpeed())
		MovementInfo.GetInitialSpeed() = MovementInfo.GetMaxSpeed();

	MovementInfo.GetSpeed()		   = MovementInfo.GetInitialSpeed();
	MovementInfo.GetDirection()	   = Direction;
	MovementInfo.GetVelocity()	   = MovementInfo.GetInitialSpeed() * Direction;
	MovementInfo.GetGravityScale() = Data->GetGravityScale();

	MovementComponent->InitialSpeed			  = MovementInfo.GetInitialSpeed();
	MovementComponent->MaxSpeed				  = MovementInfo.GetMaxSpeed();
	MovementComponent->Velocity				  = MovementInfo.GetVelocity();
	MovementComponent->ProjectileGravityScale = MovementInfo.GetGravityScale();
}

	// Tracking
#pragma region

void ACsProjectilePooledImpl::FTrackingImpl::Init(PayloadType* Payload)
{
	using namespace NCsProjectilePooledImpl::NTrackingImpl::NCached;

	const FString& Context = Str::Init;

	using TargetPayloadType = NCsProjectile::NPayload::NTarget::ITarget;

	TargetPayloadType* TargetPayload = CsPrjPayloadLibrary::GetInterfaceChecked<TargetPayloadType>(Context, Payload);

	if (!TargetPayload->HasTarget())
		return;

	using TrackingDataType = NCsProjectile::NData::NTracking::ITracking;

	TrackingData = CsPrjDataLibrary::GetSafeInterfaceChecked<TrackingDataType>(Context, Outer->GetData());

	if (TrackingData &&
		TrackingData->ShouldUseTracking())
	{
		using TrackingParamsType = NCsProjectile::NTracking::FParams;
		using TrackingDestinationType = NCsProjectile::NTracking::EDestination;

		const TrackingParamsType& TrackingParams = TrackingData->GetTrackingParams();
		Outer->TrackingInfo.GetDelay()		= TrackingParams.GetDelay();
		//GetDestinationType()				= TrackingParams.GetDestination();
		Outer->TrackingInfo.GetOffset()		= TrackingParams.GetOffset();

		if (TrackingParams.GetbReacquireDestination())
			Outer->TrackingInfo.DestinationMask_SetReacquire();

		Outer->TrackingInfo.GetDuration()				= TrackingParams.GetDuration();
		Outer->TrackingInfo.GetMinDotThreshold()		= TrackingParams.GetMinDotThreshold();
		Outer->TrackingInfo.GetMaxDotBeforeUsingPitch()	= TrackingParams.GetMaxDotBeforeUsingPitch();
		Outer->TrackingInfo.GetRotationRate()			= TrackingParams.GetRotationRate();

		// Object | Bone
		if (USceneComponent* Component = TargetPayload->GetTargetComponent())
		{
			const FName& Bone = TargetPayload->GetTargetBone();

			// Bone
			if (Bone != NAME_None)
			{
				Outer->TrackingInfo.GetMeshComponent() = CS_CAST_CHECKED(Component, USceneComponent, USkeletalMeshComponent);

				check(CsSkeletalMeshLibrary::IsBoneValidChecked(Context, Outer->TrackingInfo.GetMeshComponent(), Bone));

				Outer->TrackingInfo.GetBone()			 = Bone;
				Outer->TrackingInfo.GetDestinationType() = TrackingDestinationType::Bone;
			}
			// Object
			else
			{
				Outer->TrackingInfo.GetDestinationType() = TrackingDestinationType::Object;
			}
		}
		// Custom | Location
		else
		{
			const int32& ID = TargetPayload->GetTargetID();

			// Custom
			if (ID != INDEX_NONE)
			{
				Outer->TrackingInfo.GetID()				 = TargetPayload->GetTargetID();
				Outer->TrackingInfo.GetDestinationType() = TrackingDestinationType::Custom;
			}
			// Location
			else
			{
				Outer->TrackingInfo.GetLocation()		 = TargetPayload->GetTargetLocation();
				Outer->TrackingInfo.GetDestinationType() = TrackingDestinationType::Location;
			}
		}
		Outer->TrackingInfo.GetCurrentState() = Outer->TrackingInfo.GetDelay() > 0.0f ? NCsProjectile::NTracking::EState::Delay : NCsProjectile::NTracking::EState::Active;
	}
}

#pragma endregion Tracking

#pragma endregion Movement

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

void ACsProjectilePooledImpl::AddIgnoredHitActor(AActor* Actor)
{
	IgnoredHitActors.Add(Actor);
}

bool ACsProjectilePooledImpl::IsIgnoredOnHit(AActor* Actor) const
{
	if (IsIgnored(Actor))
		return true;

	for (const TWeakObjectPtr<AActor>& A : IgnoredHitActors)
	{
		if (!A.IsValid())
			continue;

		if (Actor == A.Get())
			return true;
	}
	return false;
}

void ACsProjectilePooledImpl::AddIgnoredHitComponent(UPrimitiveComponent* Component)
{
	IgnoredHitComponents.Add(Component);
}

bool ACsProjectilePooledImpl::IsIgnoredOnHit(UPrimitiveComponent* Component) const
{
	if (IsIgnored(Component))
		return false;

	for (const TWeakObjectPtr<UPrimitiveComponent>& C : IgnoredHitComponents)
	{
		if (!C.IsValid())
			continue;

		if (Component == C.Get())
			return true;
	}
	return false;
}

void ACsProjectilePooledImpl::ClearHitObjects()
{
	for (TWeakObjectPtr<AActor>& A : IgnoredHitActors)
	{
		if (!A.IsValid() || !A.Get())
			continue;

		int32 Count = IgnoreActors.Num();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			TWeakObjectPtr<AActor>& B = IgnoreActors[I];

			if (B.IsValid() &&
				A.Get() == B.Get())
			{
				IgnoreActors.RemoveAt(I, 1, false);
			}
		}

		Count = CollisionComponent->MoveIgnoreActors.Num();
		
		for (int32 I = Count - 1; I >= 0; --I)
		{
			AActor* B = CollisionComponent->MoveIgnoreActors[I];

			if (A.Get() == B)
			{
				CollisionComponent->MoveIgnoreActors.RemoveAt(I, 1, false);
			}
		}
	}

	IgnoredHitActors.Reset(IgnoredHitActors.Max());

	for (TWeakObjectPtr<UPrimitiveComponent>& A : IgnoredHitComponents)
	{
		if (!A.IsValid() || !A.Get())
			continue;

		int32 Count = IgnoreComponents.Num();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			TWeakObjectPtr<UPrimitiveComponent>& B = IgnoreComponents[I];

			if (B.IsValid() &&
				A.Get() == B.Get())
			{
				IgnoreComponents.RemoveAt(I, 1, false);
			}
		}

		Count = CollisionComponent->MoveIgnoreComponents.Num();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			UPrimitiveComponent* B = CollisionComponent->MoveIgnoreComponents[I];

			if (A.Get() == B)
			{
				CollisionComponent->MoveIgnoreComponents.RemoveAt(I, 1, false);
			}
		}
	}

	IgnoredHitComponents.Reset(IgnoredHitComponents.Max());
}

void ACsProjectilePooledImpl::ClearIgnored()
{
	for (TPair<int32, TSet<int32>>& Pair : IgnoreIdByTypeMap)
	{
		TSet<int32>& IDs = Pair.Value;

		IDs.Reset();
	}
}

void ACsProjectilePooledImpl::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	using HitResultType = NCsProjectile::NCollision::NHit::FResult;

	HitResultType Result;
	Result.MyComponent	 = HitComponent;
	Result.OtherActor	 = OtherActor;
	Result.OtherComponent = OtherComp;
	Result.NormalImpulse = CsMathLibrary::Convert(NormalImpulse);
	Result.Hit			 = HitResult;

	Hit(Result);
}

void ACsProjectilePooledImpl::OnHit_TryImpactVisual(const FString& Context, UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
#if WITH_EDITOR
	if (bOverride_ImpactFX)
	{
		if (CS_CVAR_LOG_IS_SHOWING(LogOverrideFunctions))
		{
			UE_LOG(LogCsPrj, Warning, TEXT("%s: Trail FX is OVERRIDDEN for %s."), *Context, *(GetName()));
		}

		OnOverride_ImpactFX_ScriptEvent.Broadcast(this, HitComponent, OtherActor, OtherComp, CsMathLibrary::Convert(NormalImpulse), HitResult);
	}
	else
#endif // #if WITH_EDITOR
	{
		// Get Physics Surface
		UPhysicalMaterial* PhysMaterial = HitResult.PhysMaterial.IsValid() ? HitResult.PhysMaterial.Get() : nullptr;
		EPhysicalSurface SurfaceType	= PhysMaterial ? (EPhysicalSurface)PhysMaterial->SurfaceType : EPhysicalSurface::SurfaceType_Default;

		// ImpactVisualDataType (NCsProjectile::NData::NVisual::NImpact::IImpact)
		{
			using ImpactVisualDataType = NCsProjectile::NData::NVisual::NImpact::IImpact;

			if (ImpactVisualDataType* ImpactVisualData = CsPrjDataLibrary::GetSafeInterfaceChecked<ImpactVisualDataType>(Context, Data))
			{	
				using ImpactVisualInfoType = NCsProjectile::NImpact::NVisual::FInfo;
				using ImpactFXInfoType = NCsProjectile::NImpact::NVisual::NFX::FInfo;
				
				const ImpactVisualInfoType& Info = ImpactVisualData->GetImpactVisualInfo(SurfaceType);
				const ImpactFXInfoType& FXInfo   = Info.GetFXInfo();

				if (FXInfo.GetbFX())
				{
					PooledPayloadImplType Payload;
					Payload.Instigator = Cache->GetInstigator();

					FTransform Transform = FTransform::Identity;
					Transform.SetLocation(HitResult.Location);

					using DirectionType = NCsProjectile::NImpact::NVisual::EDirection;

					const DirectionType& Direction = FXInfo.GetDirection();
					// Normal
					if (Direction == DirectionType::Normal)
					{
						Transform.SetRotation(HitResult.ImpactNormal.Rotation().Quaternion());
					}
					// Inverse Normal
					else
					if (Direction == DirectionType::Normal)
					{
						Transform.SetRotation((-HitResult.ImpactNormal).Rotation().Quaternion());
					}
					// Velocity
					else
					if (Direction == DirectionType::Velocity)
					{
						const FVector Normal = MovementComponent->Velocity.GetSafeNormal();

						Transform.SetRotation(Normal.Rotation().Quaternion());
					}
					// Inverse Velocity
					else
					if (Direction == DirectionType::InverseVelocity)
					{
						const FVector Normal = -1.0f * MovementComponent->Velocity.GetSafeNormal();

						Transform.SetRotation(Normal.Rotation().Quaternion());
					}
	
					if (Info.GetFXInfo().GetbScaleByDamageRange())
					{
						float MaxRange = GetMaxDamageRangeChecked(Context);

						Transform.SetScale3D(MaxRange * FVector::OneVector);
					}

					CsFXManagerLibrary::SpawnChecked(Context, GetWorldContext(), &Payload, FXInfo.GetFX(), Transform);
				}
			}
		}
	}
}

#pragma endregion Collision

// FX
#pragma region

void ACsProjectilePooledImpl::SetTrailFXPooled(const FString& Context, const FECsFX& FX, const int32& Index)
{
	void(*Log)(const FString&) = &NCsProjectile::FLog::Warning;

	CS_IS_INT_GREATER_THAN_OR_EQUAL_EXIT(Index, 0)

	TrailFXPooled = const_cast<FCsFXActorPooled*>(CsFXManagerLibrary::FindSafeObject(Context, GetWorldContext(), FX, Index, Log));
}

#pragma endregion FX

// Modifier
#pragma region

void ACsProjectilePooledImpl::ApplyHitCountModifiers(const FString& Context, const CollisionDataType* CollisionData)
{
	HitCount = CollisionData->GetHitCount();
	HitCount = CsProjectileModifierLibrary::ModifyIntChecked(Context, Modifiers, NCsProjectileModifier::HitCount, HitCount);
}

void ACsProjectilePooledImpl::StartMovementFromModifiers(const FString& Context, const FVector& Direction)
{
	using StartType = ACsProjectilePooledImpl::FMovementImpl::EStart;

	MovementInfo.GetInitialSpeed() = MovementImpl.CalculateInitialSpeed(StartType::FromModifiers);
	MovementInfo.GetMaxSpeed()	   = MovementImpl.CalculateMaxSpeed(StartType::FromModifiers);

	if (MovementInfo.GetInitialSpeed() > MovementInfo.GetMaxSpeed())
		MovementInfo.GetInitialSpeed() = MovementInfo.GetMaxSpeed();

	MovementInfo.GetSpeed()		   = MovementInfo.GetInitialSpeed();
	MovementInfo.GetDirection()	   = Direction;
	MovementInfo.GetVelocity()	   = MovementInfo.GetInitialSpeed() * Direction;
	MovementInfo.GetGravityScale() = Data->GetGravityScale();

	MovementComponent->InitialSpeed			  = MovementInfo.GetInitialSpeed();
	MovementComponent->MaxSpeed				  = MovementInfo.GetMaxSpeed();
	MovementComponent->Velocity				  = MovementInfo.GetVelocity();
	MovementComponent->ProjectileGravityScale = MovementInfo.GetGravityScale();
}

#pragma endregion Modifier

// Damage
#pragma region

ACsProjectilePooledImpl::FDamageImpl::FDamageImpl() :
	Outer(nullptr),
	Type(),
	ValuePoint(nullptr),
	ValueRange(nullptr),
	DataTypes(),
	Modifiers()
{
	ValuePoint = new PointImplType();
	ValueRange = new RangeImplType();
}

ACsProjectilePooledImpl::FDamageImpl::~FDamageImpl()
{
	delete ValuePoint;
	ValuePoint = nullptr;

	delete ValueRange;
	ValueRange = nullptr;

	using AllocateModifierType = NCsDamage::NModifier::FAllocated;

	for (AllocateModifierType& Modifier : Modifiers)
	{
		Modifier.Clear();
	}
	Modifiers.Reset();
}

void ACsProjectilePooledImpl::FDamageImpl::SetValue(DamageDataType* InData)
{
	using namespace NCsProjectilePooledImpl::NDamageImpl::NCached;

	const FString& Context = Str::SetValue;

	const ValueType* Value = InData->GetValue();
	Type				   = CsDamageValueLibrary::GetTypeChecked(Context, Value);

	ResetValue();
	CsDamageValueLibrary::CopyChecked(Context, Value, GetValue());
}

ValueType* ACsProjectilePooledImpl::FDamageImpl::GetValue()
{
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

	DataTypes.Reset(DataTypes.Max());
	Modifiers.Reset(Modifiers.Max());
}

const RangeType* ACsProjectilePooledImpl::GetDamageRangeChecked(const FString& Context)
{
	using DmgShapeDataType = NCsDamage::NData::NShape::IShape;

	// NOTE: For now assume the ONLY way to get RangeType is from a Damage Shape.
	//		  Damage Shape is an object that implements the interface: DmgShapeDataType (NCsDamage::NData::NShape::IShape)
	
	// PrjDmgDataType (NCsProjectile::NData::NDamage::IDamage)
	{
		using PrjDmgDataType = NCsProjectile::NData::NDamage::IDamage;

		if (const PrjDmgDataType* PrjDmgData = CsPrjDataLibrary::GetSafeInterfaceChecked<PrjDmgDataType>(Context, Data))
		{
			const DamageDataType* DmgData = PrjDmgData->GetDamageData();

			if (const DmgShapeDataType* DmgShapeData = CsDamageDataLibrary::GetSafeInterfaceChecked<DmgShapeDataType>(Context, DmgData))
			{
				return DmgShapeData->GetRange();
			}
		}
	}
	// CsGetDamageDataTypeDataType (NCsData::IGetDamageDataType)
	{
		if (const CsGetDamageDataTypeDataType* GetDamageDataType = CsPrjDataLibrary::GetSafeInterfaceChecked<CsGetDamageDataTypeDataType>(Context, Data))
		{
			const DamageDataType* DmgData = CsDamageManagerLibrary::GetDataChecked(Context, GetWorldContext(), GetDamageDataType);

			if (const DmgShapeDataType* DmgShapeData = CsDamageDataLibrary::GetSafeInterfaceChecked<DmgShapeDataType>(Context, DmgData))
			{
				return DmgShapeData->GetRange();
			}
		}
	}
	// GetDamageDataTypeDataTypes (NCsData::IGetDamageDataTypes)
	{
		if (const CsGetDamageDataTypesDataType* GetDamageDataTypes = CsPrjDataLibrary::GetSafeInterfaceChecked<CsGetDamageDataTypesDataType>(Context, Data))
		{
			static TArray<DamageDataType*> DamageDatas;

			CsDamageManagerLibrary::GetDatasChecked(Context, GetWorldContext(), GetDamageDataTypes, DamageDatas);

			for (const DamageDataType* DmgData : DamageDatas)
			{
				if (const DmgShapeDataType* DmgShapeData = CsDamageDataLibrary::GetSafeInterfaceChecked<DmgShapeDataType>(Context, DmgData))
				{
					DamageDatas.Reset(DamageDatas.Max());
					return DmgShapeData->GetRange();
				}
			}
			DamageDatas.Reset(DamageDatas.Max());
		}
	}
	checkf(0, TEXT("%s: Failed to get Damage Data from %s"), *Context, *CsPrjDataLibrary::PrintDataAndClass(Data));
	return nullptr;
}

float ACsProjectilePooledImpl::GetMaxDamageRangeChecked(const FString& Context)
{
	const RangeType* Range = GetDamageRangeChecked(Context);

	return CsDamageModifierLibrary::GetMaxRangeChecked(Context, DamageImpl.Modifiers, Range);
}

#pragma endregion Damage