// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "CsProjectilePooledImpl.h"
#include "CsPrj.h"

// CVar
#include "CsCVars_Projectile.h"
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
#include "Library/CsLibrary_SkeletalMesh.h"
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/FX/Actor/CsManager_FX_Actor.h"
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
#include "Modifier/CsModifier_Int.h"
#include "Modifier/CsModifier_Float.h"
// FX
#include "Managers/FX/Actor/CsFXActorPooled.h"
// Sound
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"
// Damage
#include "Value/Point/CsDamageValuePointImpl.h"
#include "Value/Range/CsDamageValueRangeImpl.h"
// Scoped
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"

#if WITH_EDITOR
// Library
	// Common
#include "Library/CsLibrary_World.h"
#endif // #if WITH_EDITOR

//#define CS_COLLISION_PROJECTILE	ECC_GameTraceChannel2

// Cached
#pragma region

namespace NCsProjectilePooledImpl
{
	namespace NCached
	{
		namespace Str
		{
			// AActor Interface
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, PostInitializeComponents);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, SetType);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, OnHit);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Allocate);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Deallocate);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Deallocate_Internal);
			// Launch
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Launch);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, OnLaunch_SetModifiers);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Launch_Delayed);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, Launch_Delayed_Internal);
			// Variables
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectilePooledImpl, AllocateVariables);
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
	MovementImpl(),
	bOverride_InitialSpeed(false),
	Override_InitialSpeed(false),
	OnOverride_InitialSpeed_ScriptEvent(),
	bOverride_MaxSpeed(false),
	Override_MaxSpeed(false),
	OnOverride_MaxSpeed_ScriptEvent(),
		// Tracking
	TrackingImpl(),
	// Collision
	IgnoreActors(),
	IgnoreComponents(),
	IgnoredHitActors(),
	IgnoredHitComponents(),
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

	MovementImpl.Outer = this;
	TrackingImpl.Outer = this;
	DamageImpl.Outer = this;
}

void ACsProjectilePooledImpl::PostInitializeComponents()
{
	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::PostInitializeComponents;

	Super::PostInitializeComponents();

#if WITH_EDITOR
	typedef NCsWorld::FLibrary WorldLibrary;

	if (WorldLibrary::IsPlayInEditorOrEditorPreview(this))
	{
		CollisionComponent->OnComponentHit.AddDynamic(this, &ACsProjectilePooledImpl::OnHit);

		CollisionComponent->SetComponentTickEnabled(false);
		MovementComponent->SetComponentTickEnabled(false);
		MeshComponent->SetComponentTickEnabled(false);

		SetActorTickEnabled(false);

		ConstructCache();

		MovementImpl.Outer = this;
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

void ACsProjectilePooledImpl::Shutdown()
{
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

void ACsProjectilePooledImpl::OnTick_HandleCVars(const float& DeltaSeconds)
{
#if WITH_EDITOR
	const FCsSettings_Projectile_Debug& Debug = FCsSettings_Projectile_Debug::Get();
	
	Debug.Collision.Draw(this, GetActorLocation(), CollisionComponent->GetScaledSphereRadius());
#endif // #if WITH_EDITOR
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
		Data = PrjManagerLibrary::GetDataChecked(Context, GetWorldContext(), Type);
	}
}

// ICsUpdate
#pragma region

void ACsProjectilePooledImpl::Update(const FCsDeltaTime& DeltaTime)
{
	Variables->GetLocation() = GetActorLocation();

	TrackingImpl.Update(DeltaTime);
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

	Generation = ProjectilePayload->GetGeneration();

	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectile, Type)

	// TODO: Need to determine best place to set LifeTime from Data

	// Set Data on Cache
	CacheImpl->Allocate(Payload);

	// Get Data associated with Type
	// TODO: FUTURE: Add to list of preserved changes
	typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;

	Data = PrjManagerLibrary::GetDataChecked(Context, GetWorldContext(), Type);
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
		typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

	#if WITH_EDITOR
		typedef NCsWorld::FLibrary WorldLibrary;

		if (WorldLibrary::IsPlayInEditorOrEditorPreview(this))
		{
			CoroutineSchedulerLibrary::SafeEndAndInvalidate(Context, GetWorldContext(), NCsUpdateGroup::GameState, Launch_Delayed_Handle, nullptr);
		}
		else
	#endif // #if WITH_EDITOR
		{
			CoroutineSchedulerLibrary::EndAndInvalidateChecked(Context, GetWorldContext(), NCsUpdateGroup::GameState, Launch_Delayed_Handle);
		}
	}

	GetState() = NCsProjectile::EState::Inactive;

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
	typedef NCsMaterial::FLibrary MaterialLibrary;

	MaterialLibrary::ClearOverrideChecked(Context, MeshComponent);
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
	typedef NCsProjectile::NManager::NVariables::FLibrary VariablesLibrary;

	if (Variables)
	{
	#if WITH_EDITOR
		typedef NCsWorld::FLibrary WorldLibrary;

		if (WorldLibrary::IsPlayInEditorOrEditorPreview(this))
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

#define PayloadType NCsProjectile::NPayload::IPayload
void ACsProjectilePooledImpl::Launch(PayloadType* Payload)
{
#undef PayloadType
	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::Launch;

	CS_IS_PTR_NULL_CHECKED(Payload)

	// Set / Cache any Modifiers from the Payload
	OnLaunch_SetModifiers(Payload);

	// Set Additional Datas
	{
		// Damage
		typedef NCsProjectile::NPayload::FLibrary PayloadLibrary;
		typedef NCsProjectile::NPayload::NDamage::IDamage DmgPayloadType;

		if (const DmgPayloadType* DmgPayload = PayloadLibrary::GetSafeInterfaceChecked<DmgPayloadType>(Context, Payload))
		{
			DamageImpl.DataTypes.Append(DmgPayload->GetDamageDataTypes());
		}
	}

	// Launch Params
	typedef NCsProjectile::NData::FLibrary PrjDataLibrary;
	typedef NCsProjectile::NData::NLaunch::ILaunch LaunchDataType;
	typedef NCsProjectile::NLaunch::FParams LaunchParamsType;

	LaunchDataType* LaunchData			 = PrjDataLibrary::GetSafeInterfaceChecked<LaunchDataType>(Context, Data);
	const LaunchParamsType* LaunchParams = LaunchData ? &(LaunchData->GetLaunchParams()) : nullptr;

	const bool ShouldDelayLaunch = LaunchParams ? LaunchParams->GetDelay() > 0.0f : false;

	// LifeTime
	{
		float LifeTime = Cache->GetLifeTime();
		float Delay	   = ShouldDelayLaunch ? LaunchParams->GetDelay() : 0.0f;

		typedef NCsProjectile::NModifier::FLibrary ModifierLibrary;

		LifeTime = ModifierLibrary::ModifyFloatChecked(Context, Modifiers, NCsProjectileModifier::LifeTime, LifeTime);

		// TODO: Add Modifier for Delay

		typedef NCsProjectile::NCache::FLibrary CacheLibrary;

		CacheLibrary::SetLifeTimeChecked(Context, Cache, LifeTime + Delay);
	}

	//const ECsProjectileRelevance& Relevance = Cache.Relevance;

	SetActorHiddenInGame(false);

	RootComponent = CollisionComponent;

	// VisualDataType (NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh)
	{
		typedef NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh VisualDataType;

		if (VisualDataType* VisualData = PrjDataLibrary::GetSafeInterfaceChecked<VisualDataType>(Context, Data))
		{
			// TODO: Allocate Static Mesh Actor and get Static Mesh Component

			MeshComponent->AttachToComponent(CollisionComponent, FAttachmentTransformRules::KeepRelativeTransform);
			MeshComponent->SetRelativeLocation(FVector::ZeroVector);

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
			typedef NCsProjectile::NData::NVisual::NTrail::ITrail VisualDataType;

			if (VisualDataType* VisualData = PrjDataLibrary::GetSafeInterfaceChecked<VisualDataType>(Context, Data))
			{
				typedef NCsFX::NManager::FLibrary FXManagerLibrary;
				typedef NCsPooledObject::NPayload::FImplSlice PayloadImplType;

				PayloadImplType PayloadImpl;
				PayloadImpl.Owner  = this;

				if (MeshComponent->GetStaticMesh())
					PayloadImpl.Parent = MeshComponent;
				else
					PayloadImpl.Parent = CollisionComponent;

				const FCsFX& TrailFX = VisualData->GetTrailFX();

				TrailFXPooled = const_cast<FCsFXActorPooled*>(FXManagerLibrary::SpawnChecked(Context, GetWorldContext(), &PayloadImpl, TrailFX));
			}
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

				typedef NCsProjectile::NPayload::NCollision::ICollision CollisionPayloadType;

				CollisionPayloadType* CollisionPayload = ProjectilePayloadLibrary::GetInterfaceChecked<CollisionPayloadType>(Context, Payload);

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

#define PayloadType NCsProjectile::NPayload::IPayload
void ACsProjectilePooledImpl::OnLaunch_SetModifiers(const PayloadType* Payload)
{
#undef PayloadType

	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::OnLaunch_SetModifiers;

	typedef NCsProjectile::NPayload::FLibrary PayloadLibrary;

	// ModifierPayloadType (NCsProjectile::NPayload::NModifier::IModifier)
	{
		typedef NCsProjectile::NPayload::NModifier::IModifier ModifierPayloadType;

		if (const ModifierPayloadType* ModifierPayload = PayloadLibrary::GetSafeInterfaceChecked<ModifierPayloadType>(Context, Payload))
		{
			typedef NCsProjectile::NManager::NModifier::FLibrary PrjModifierLibrary;

			PrjModifierLibrary::CopyChecked(Context, GetWorldContext(), ModifierPayload->GetModifiers(), Modifiers);
		}
	}
	// DmgModifierPayloadType (NCsProjectile::NPayload::NModifier::NDamage::IDamage)
	{
		typedef NCsProjectile::NPayload::NModifier::NDamage::IDamage DmgModifierPayloadType;

		if (const DmgModifierPayloadType* DmgModifierPayload = PayloadLibrary::GetSafeInterfaceChecked<DmgModifierPayloadType>(Context, Payload))
		{
			typedef NCsDamage::NManager::NModifier::FLibrary DmgModifierLibrary;

			DmgModifierLibrary::CopyChecked(Context, GetWorldContext(), DmgModifierPayload->GetDamageModifiers(), DamageImpl.Modifiers);
		}
	}
}

void ACsProjectilePooledImpl::Launch_Delayed(const FLaunch_Delayed_Payload& Payload)
{
	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::Launch_Delayed;

	// TODO: NOTE: Need a way UpdateGroup is passed via Payload

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

	UCsCoroutineScheduler* Scheduler   = CoroutineSchedulerLibrary::GetChecked(Context, GetWorldContext());
	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameState;

	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* CoroutinePayload = Scheduler->AllocatePayload(UpdateGroup);

	#define COROUTINE Launch_Delayed_Internal

	typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

	CoroutinePayload->CoroutineImpl.BindUObject(this, &ACsProjectilePooledImpl::COROUTINE);
	CoroutinePayload->StartTime = TimeManagerLibrary::GetTimeChecked(Context, GetWorldContext(), UpdateGroup);
	CoroutinePayload->Owner.SetObject(this);
	CoroutinePayload->SetName(Str::COROUTINE);
	CoroutinePayload->SetFName(Name::COROUTINE);

	#undef COROUTINE

	typedef NCsProjectile::NData::FLibrary PrjDataLibrary;
	typedef NCsProjectile::NData::NLaunch::ILaunch LaunchDataType;
	typedef NCsProjectile::NLaunch::FParams LaunchParamsType;

	LaunchDataType* LaunchData			 = PrjDataLibrary::GetSafeInterfaceChecked<LaunchDataType>(Context, Data);
	const LaunchParamsType& LaunchParams = LaunchData->GetLaunchParams();

	// Delay
	static const int32 DELAY = 0;
	CoroutinePayload->SetValue_Float(DELAY, LaunchParams.GetDelay());

	// Direction
	static const int32 DIRECTION = 0;
	CoroutinePayload->SetValue_Vector(DIRECTION, Payload.Direction);

	// Should Update Collision
	static const int32 SHOULD_UPDATE_COLLISION = 0;
	CoroutinePayload->SetValue_Flag(SHOULD_UPDATE_COLLISION, LaunchParams.GetDelayParams().GetbCollision());

	Launch_Delayed_Handle = Scheduler->Start(CoroutinePayload);
}

char ACsProjectilePooledImpl::Launch_Delayed_Internal(FCsRoutine* R)
{
	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::Launch_Delayed_Internal;

	// Delay
	static const int32 DELAY = 0;
	const float& Delay = R->GetValue_Float(DELAY);

	// Direction
	static const int32 DIRECTION = 0;
	const FVector& Direction = R->GetValue_Vector(DIRECTION);
	
	// Should Update Collision
	static const int32 SHOULD_UPDATE_COLLISION = 0;
	const bool& ShouldUpdateCollision = R->GetValue_Flag(SHOULD_UPDATE_COLLISION);

	CS_COROUTINE_BEGIN(R);

	CS_COROUTINE_WAIT_UNTIL(R, R->ElapsedTime.Time >= Delay);

	// Movement
	{
		StartMovementFromModifiers(Context, Direction);
	}
	// Collision
	if (ShouldUpdateCollision)
	{
		const FString& ScopeName		   = ScopedTimer::SetCollision;
		const FECsScopedGroup& ScopedGroup = NCsScopedGroup::Projectile;
		const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogProjectileScopedTimerLaunchSetCollision;

		CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

		typedef NCsProjectile::NData::FLibrary PrjDataLibrary;
		typedef NCsProjectile::NData::NCollision::ICollision CollisionDataType;

		if (CollisionDataType* CollisionData = PrjDataLibrary::GetSafeInterfaceChecked<CollisionDataType>(Context, Data))
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

#if WITH_EDITOR

const UObject* ACsProjectilePooledImpl::GetWorldContext() const
{
	typedef NCsWorld::FLibrary WorldLibrary;

	if (WorldLibrary::IsPlayInEditorOrEditorPreview(this))
	{
		return Cache->GetInstigator();
	}
	return this;
}

#endif // #if WITH_EDITOR

// Variables
#pragma region

#define PayloadType NCsProjectile::NPayload::IPayload
void ACsProjectilePooledImpl::AllocateVariables(const PayloadType* Payload)
{
#undef PayloadType

	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::AllocateVariables;

	typedef NCsProjectile::NManager::NVariables::FLibrary VariablesLibrary;
	typedef NCsProjectile::NVariables::NAllocate::FPayload VariablesPayloadType;

	VariablesPayloadType VariablesPayload;
	VariablesPayload.Projectile	= this;
	VariablesPayload.Type		= Type;
	VariablesPayload.Location	= Payload->GetLocation();

	typedef NCsProjectile::NData::FLibrary PrjDataLibrary;
	typedef NCsProjectile::NData::NCollision::ICollision CollisionDataType;

	if (CollisionDataType* CollisionData = PrjDataLibrary::GetSafeInterfaceChecked<CollisionDataType>(Context, Data))
	{
		VariablesPayload.CollisionRadius = CollisionData->GetCollisionRadius();
	}

	Variables = VariablesLibrary::AllocateChecked(Context, GetWorldContext(), VariablesPayload);
}

#pragma endregion Variables

// Movement
#pragma region

float ACsProjectilePooledImpl::FMovementImpl::GetInitialSpeed(const EStart& Start) const
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
			typedef NCsProjectile::NModifier::FLibrary ModifierLibrary;

			InitialSpeed = ModifierLibrary::ModifyFloatChecked(Context, Outer->GetModifiers(), NCsProjectileModifier::InitialSpeed, InitialSpeed);
			return InitialSpeed;
		}
	}
	checkf(0, TEXT("%s: Failed to Get Initial Speed."), *Context);
	return 0.0f;
}

float ACsProjectilePooledImpl::FMovementImpl::GetMaxSpeed(const EStart& Start) const
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
			typedef NCsProjectile::NModifier::FLibrary ModifierLibrary;

			MaxSpeed = ModifierLibrary::ModifyFloatChecked(Context, Outer->GetModifiers(), NCsProjectileModifier::MaxSpeed, MaxSpeed);
			return MaxSpeed;
		}
	}
	checkf(0, TEXT("%s: Failed to Get Max Speed."), *Context);
	return 0.0f;
}

void ACsProjectilePooledImpl::StartMovementFromData(const FVector& Direction)
{
	typedef ACsProjectilePooledImpl::FMovementImpl::EStart StartType;

	MovementComponent->InitialSpeed = MovementImpl.GetInitialSpeed(StartType::FromData);
	MovementComponent->MaxSpeed		= MovementImpl.GetMaxSpeed(StartType::FromData);

	if (MovementComponent->InitialSpeed > MovementComponent->MaxSpeed)
		MovementComponent->InitialSpeed = MovementComponent->MaxSpeed;

	MovementComponent->Velocity				  = MovementComponent->InitialSpeed * Direction;
	MovementComponent->ProjectileGravityScale = Data->GetGravityScale();
}

	// Tracking
#pragma region

#define PayloadType NCsProjectile::NPayload::IPayload
void ACsProjectilePooledImpl::FTrackingImpl::Init(PayloadType* Payload)
{
#undef PayloadType
	
	using namespace NCsProjectilePooledImpl::NTrackingImpl::NCached;

	const FString& Context = Str::Init;

	typedef NCsProjectile::NPayload::FLibrary PayloadLibrary;
	typedef NCsProjectile::NPayload::NTarget::ITarget TargetPayloadType;

	TargetPayloadType* TargetPayload = PayloadLibrary::GetInterfaceChecked<TargetPayloadType>(Context, Payload);

	if (!TargetPayload->HasTarget())
		return;

	typedef NCsProjectile::NData::FLibrary DataLibrary;
	typedef NCsProjectile::NData::NTracking::ITracking TrackingDataType;

	TrackingData = DataLibrary::GetSafeInterfaceChecked<TrackingDataType>(Context, Outer->GetData());

	if (TrackingData &&
		TrackingData->ShouldUseTracking())
	{
		Clear();

		typedef NCsProjectile::NTracking::FParams TrackingParamsType;
		typedef NCsProjectile::NTracking::EDestination TrackingDestinationType;

		const TrackingParamsType& TrackingParams = TrackingData->GetTrackingParams();
		GetDelay()								 = TrackingParams.GetDelay();
		//GetDestinationType()					 = TrackingParams.GetDestination();
		GetOffset()								 = TrackingParams.GetOffset();
		bReacquire								 = TrackingParams.GetbReacquireDestination();
		GetDuration()							 = TrackingParams.GetDuration();
		GetMinDotThreshold()					 = TrackingParams.GetMinDotThreshold();
		GetMaxDotBeforeUsingPitch()				 = TrackingParams.GetMaxDotBeforeUsingPitch();
		GetRotationRate()						 = TrackingParams.GetRotationRate();

		// Object | Bone
		if (USceneComponent* Component = TargetPayload->GetTargetComponent())
		{
			const FName& Bone = TargetPayload->GetTargetBone();

			// Bone
			if (Bone != NAME_None)
			{
				GetMeshComponent() = CS_CAST_CHECKED(Component, USceneComponent, USkeletalMeshComponent);

				typedef NCsSkeletalMesh::FLibrary SkeletalMeshLibrary;

				check(SkeletalMeshLibrary::IsBoneValidChecked(Context, GetMeshComponent(), Bone));

				GetBone()			 = Bone;
				GetDestinationType() = TrackingDestinationType::Bone;
			}
			// Object
			else
			{
				GetDestinationType() = TrackingDestinationType::Object;
			}
		}
		// Custom | Location
		else
		{
			const int32& ID = TargetPayload->GetTargetID();

			// Custom
			if (ID != INDEX_NONE)
			{
				GetID()				 = TargetPayload->GetTargetID();
				GetDestinationType() = TrackingDestinationType::Custom;
			}
			// Location
			else
			{
				GetLocation()		 = TargetPayload->GetTargetLocation();
				GetDestinationType() = TrackingDestinationType::Location;
			}
		}
		GetCurrentState() = GetDelay() > 0.0f ? NCsProjectile::NTracking::EState::Delay : NCsProjectile::NTracking::EState::Active;
	}
}

void ACsProjectilePooledImpl::FTrackingImpl::Update(const FCsDeltaTime& DeltaTime)
{
	if (GetCurrentState() == NCsProjectile::NTracking::EState::Inactive)
		return;

	if (!Outer->TrackingImpl_IsValid())
	{
		if (!Outer->TrackingImpl_ReacquireDestination())
		{
			GetCurrentState() = NCsProjectile::NTracking::EState::Inactive;
		}
		return;
	}

	// Delay
	if (GetCurrentState() == NCsProjectile::NTracking::EState::Delay)
	{
		if (GetElapsedTime() >= GetDelay())
		{
			GetCurrentState() = NCsProjectile::NTracking::EState::Active;
		}
	}
	// Active
	if (GetCurrentState() == NCsProjectile::NTracking::EState::Active)
	{
		if (GetDuration() > 0.0f &&
			GetElapsedTime() >= GetDuration())
		{
			GetCurrentState() = NCsProjectile::NTracking::EState::Inactive;
		}
		else
		{
			typedef NCsMath::FLibrary MathLibrary;

			float Speed = 0.0f;
			float SpeedSq = 0.0f;
			
			FVector VelocityDir				 = Outer->IsLaunchComplete() ? MathLibrary::GetSafeNormal(Outer->MovementComponent->Velocity, SpeedSq, Speed) : Outer->GetActorRotation().Vector();
			const FVector CurrentDestination = GetDestination();

			FVector Direction = (CurrentDestination - Outer->GetActorLocation()).GetSafeNormal();

			const float& MinDotThreshold		= GetMinDotThreshold();
			const float& MaxDotBeforeUsingPitch = GetMaxDotBeforeUsingPitch();

			const float Dot = FVector::DotProduct(VelocityDir, Direction);

			if (Dot >= MinDotThreshold)
			{
				FVector Destination = CurrentDestination;

				// "Normal" Tracking
				if (Dot > MaxDotBeforeUsingPitch)
				{
					Destination = CurrentDestination;
				}
				// Ignore Pitch / Z
				else
				{
					Destination.Z = Outer->GetActorLocation().Z;
				}

				Destination	+= GetOffset();
				Direction    = (Destination - Outer->GetActorLocation()).GetSafeNormal();

				VelocityDir = FMath::VInterpNormalRotationTo(VelocityDir, Direction, DeltaTime.Time, GetRotationRate());

				if (Outer->IsLaunchComplete())
					Outer->MovementComponent->Velocity = Speed * VelocityDir;
				else
					Outer->SetActorRotation(VelocityDir.Rotation());
			}
		}
	}
	GetElapsedTime() += DeltaTime.Time;
}

FVector ACsProjectilePooledImpl::FTrackingImpl::GetDestination() const
{
	typedef NCsProjectile::NTracking::EDestination TrackingDestinationType;

	// Component
	if (GetDestinationType() == TrackingDestinationType::Object)
		return GetComponent()->GetComponentLocation();
	// Bone
	if (GetDestinationType() == TrackingDestinationType::Bone)
		return GetMeshComponent()->GetSocketLocation(GetBone());
	// Location
	if (GetDestinationType() == TrackingDestinationType::Location)
		return GetLocation();
	// Custom / ID
	if (GetDestinationType() == TrackingDestinationType::Custom)
		return Outer->TrackingImpl_GetDestinationByCustom();
	check(0);
	return FVector::ZeroVector;
}

FVector ACsProjectilePooledImpl::TrackingImpl_GetDestinationByCustom() const
{
	return FVector::ZeroVector;
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

void ACsProjectilePooledImpl::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	using namespace NCsProjectilePooledImpl::NCached;

	const FString& Context = Str::OnHit;

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

	ClearHitObjects();

	// Get Physics Surface
	UPhysicalMaterial* PhysMaterial = Hit.PhysMaterial.IsValid() ? Hit.PhysMaterial.Get() : nullptr;
	EPhysicalSurface SurfaceType	= PhysMaterial ? (EPhysicalSurface)PhysMaterial->SurfaceType : EPhysicalSurface::SurfaceType_Default;

	typedef NCsProjectile::NData::FLibrary PrjDataLibrary;

	// ImpactVisualDataType (NCsProjectile::NData::NVisual::NImpact::IImpact)
	OnHit_TryImpactVisual(Context, HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	// ImpactSoundDataType (NCsProjectile::NData::NSound::NImpact::IImpact)
	{
		typedef NCsProjectile::NData::NSound::NImpact::IImpact ImpactSoundDataType;

		if (ImpactSoundDataType* ImpactSoundData = PrjDataLibrary::GetSafeInterfaceChecked<ImpactSoundDataType>(Context, Data))
		{
			typedef NCsProjectile::NImpact::NSound::FInfo ImpactSoundInfoType;

			const ImpactSoundInfoType& Info = ImpactSoundData->GetImpactSoundInfo(SurfaceType);

			if (Info.GetbSound())
			{
				typedef NCsSound::NManager::FLibrary SoundManagerLibrary;
				typedef NCsPooledObject::NPayload::FImplSlice PayloadImplType;

				PayloadImplType Payload;
				Payload.Instigator = Cache->GetInstigator();

				FTransform Transform = FTransform::Identity;
				Transform.SetLocation(Hit.Location);
				Transform.SetRotation(Hit.ImpactNormal.Rotation().Quaternion());

				SoundManagerLibrary::SpawnChecked(Context, GetWorldContext(), &Payload, Info.GetSound(), Transform);
			}
		}
	}
	// DamageDataType (NCsProjectile::NData::NDamage::IDamage)

		// TODO: Deprecate
	{
		typedef NCsProjectile::NData::NDamage::IDamage PrjDamageDataType;

		if (PrjDamageDataType* PrjDamageData = PrjDataLibrary::GetSafeInterfaceChecked<PrjDamageDataType>(Context, Data))
		{
			typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;
			typedef NCsDamage::NModifier::FLibrary DamageModifierLibrary;
			typedef NCsDamage::NData::IData DamageDataType;

			DamageDataType* DamageData = PrjDamageData->GetDamageData();

			static TArray<DamageDataType*> DamageDatas;
			DamageDatas.Add(DamageData);
			DamageManagerLibrary::AddDatasChecked(Context, GetWorldContext(), DamageImpl.DataTypes, DamageDatas);

			static TArray<FECsDamageData> DamageDataTypes;
			DamageDataTypes.Add(DamageManagerLibrary::GetDataTypeChecked(Context, GetWorldContext(), DamageData));
			DamageDataTypes.Append(DamageImpl.DataTypes);

			// NOTE: For now reset and apply the modifiers on each hit.
			// FUTURE: Look into having additional rules on how the modifiers are applied
			
			const int32 Count = DamageDataTypes.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				DamageData = DamageDatas[I];

				// Apply Modifiers
				DamageImpl.SetValue(DamageData);

				typedef NCsDamage::NData::NProcess::FPayload ProcessPayloadType;

				static ProcessPayloadType ProcessPayload;

				ProcessPayload.Value	  = DamageImpl.GetValue();
				ProcessPayload.Type		  = DamageDataTypes[I];
				ProcessPayload.Data		  = DamageData;
				ProcessPayload.Instigator = GetCache()->GetInstigator();
				ProcessPayload.Causer	  = this;
				// TODO: Maybe store this value each tick / update
				ProcessPayload.Direction  = MovementComponent->Velocity.GetSafeNormal();
				ProcessPayload.HitResult  = Hit;

				DamageModifierLibrary::CopyChecked(Context, DamageImpl.Modifiers, ProcessPayload.Modifiers);
				DamageManagerLibrary::ProcessDataChecked(Context, GetWorldContext(), ProcessPayload);

				ProcessPayload.Reset();

				DamageDatas.RemoveAt(I, 1, false);
				DamageDataTypes.RemoveAt(I, 1, false);
			}
		}
	}
	// GetDamageDataTypeDataType (NCsData::IGetDamageDataType)
	{
		typedef NCsData::IGetDamageDataType GetDamageDataTypeDataType;

		if (GetDamageDataTypeDataType* GetDamageDataType = PrjDataLibrary::GetSafeInterfaceChecked<GetDamageDataTypeDataType>(Context, Data))
		{
			typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;
			typedef NCsDamage::NModifier::FLibrary DamageModifierLibrary;
			typedef NCsDamage::NData::IData DamageDataType;

			DamageDataType* DamageData = DamageManagerLibrary::GetDataChecked(Context, GetWorldContext(), GetDamageDataType);

			static TArray<DamageDataType*> DamageDatas;
			DamageDatas.Add(DamageData);
			DamageManagerLibrary::AddDatasChecked(Context, GetWorldContext(), DamageImpl.DataTypes, DamageDatas);

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

				typedef NCsDamage::NData::NProcess::FPayload ProcessPayloadType;

				static ProcessPayloadType ProcessPayload;

				ProcessPayload.Value	  = DamageImpl.GetValue();
				ProcessPayload.Type		  = DamageDataTypes[I];
				ProcessPayload.Data		  = DamageData;
				ProcessPayload.Instigator = GetCache()->GetInstigator();
				ProcessPayload.Causer	  = this;
				// TODO: Maybe store this value each tick / update
				ProcessPayload.Direction  = MovementComponent->Velocity.GetSafeNormal();
				ProcessPayload.HitResult  = Hit;

				DamageModifierLibrary::CopyChecked(Context, DamageImpl.Modifiers, ProcessPayload.Modifiers);
				DamageManagerLibrary::ProcessDataChecked(Context, GetWorldContext(), ProcessPayload);

				ProcessPayload.Reset();

				DamageDatas.RemoveAt(I, 1, false);
				DamageDataTypes.RemoveAt(I, 1, false);
			}
		}
	}
	// GetDamageDataTypeDataTypes (NCsData::IGetDamageDataTypes)
	{
		typedef NCsData::IGetDamageDataTypes GetDamageDataTypeDataTypes;

		if (GetDamageDataTypeDataTypes* GetDamageDataTypes = PrjDataLibrary::GetSafeInterfaceChecked<GetDamageDataTypeDataTypes>(Context, Data))
		{
			typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;
			typedef NCsDamage::NModifier::FLibrary DamageModifierLibrary;
			typedef NCsDamage::NData::IData DamageDataType;

			static TArray<DamageDataType*> DamageDatas;
			DamageManagerLibrary::GetDatasChecked(Context, GetWorldContext(), GetDamageDataTypes, DamageDatas);
			DamageManagerLibrary::AddDatasChecked(Context, GetWorldContext(), DamageImpl.DataTypes, DamageDatas);

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

				typedef NCsDamage::NData::NProcess::FPayload ProcessPayloadType;

				static ProcessPayloadType ProcessPayload;

				ProcessPayload.Value	  = DamageImpl.GetValue();
				ProcessPayload.Type		  = DamageDataTypes[I];
				ProcessPayload.Data		  = DamageData;
				ProcessPayload.Instigator = GetCache()->GetInstigator();
				ProcessPayload.Causer	  = this;
				// TODO: Maybe store this value each tick / update
				ProcessPayload.Direction  = MovementComponent->Velocity.GetSafeNormal();
				ProcessPayload.HitResult  = Hit;

				DamageModifierLibrary::CopyChecked(Context, DamageImpl.Modifiers, ProcessPayload.Modifiers);
				DamageManagerLibrary::ProcessDataChecked(Context, GetWorldContext(), ProcessPayload);

				ProcessPayload.Reset();

				DamageDatas.RemoveAt(I, 1, false);
				DamageDataTypes.RemoveAt(I, 1, false);
			}
		}
	}

	// CollisionDataType (NCsProjectile::NData::NCollision::ICollision)
	typedef NCsProjectile::NData::NCollision::ICollision CollisionDataType;

	if (CollisionDataType* CollisionData = PrjDataLibrary::GetSafeInterfaceChecked<CollisionDataType>(Context, Data))
	{
		if (CollisionData->IgnoreHitObjectAfterHit())
		{
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

	OnHit_Internal(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	if (bDeallocateOnHit && HitCount <= 0)
		Cache->QueueDeallocate();

	OnHit_Event.Broadcast(this, Hit);
}

void ACsProjectilePooledImpl::OnHit_TryImpactVisual(const FString& Context, UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
#if WITH_EDITOR
	if (bOverride_ImpactFX)
	{
		if (CS_CVAR_LOG_IS_SHOWING(LogOverrideFunctions))
		{
			UE_LOG(LogCsPrj, Warning, TEXT("%s: Trail FX is OVERRIDDEN for %s."), *Context, *(GetName()));
		}

		OnOverride_ImpactFX_ScriptEvent.Broadcast(this, HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	}
	else
#endif // #if WITH_EDITOR
	{
		// Get Physics Surface
		UPhysicalMaterial* PhysMaterial = Hit.PhysMaterial.IsValid() ? Hit.PhysMaterial.Get() : nullptr;
		EPhysicalSurface SurfaceType	= PhysMaterial ? (EPhysicalSurface)PhysMaterial->SurfaceType : EPhysicalSurface::SurfaceType_Default;

		typedef NCsProjectile::NData::FLibrary PrjDataLibrary;

		// ImpactVisualDataType (NCsProjectile::NData::NVisual::NImpact::IImpact)
		{
			typedef NCsProjectile::NData::NVisual::NImpact::IImpact ImpactVisualDataType;

			if (ImpactVisualDataType* ImpactVisualData = PrjDataLibrary::GetSafeInterfaceChecked<ImpactVisualDataType>(Context, Data))
			{	
				typedef NCsProjectile::NImpact::NVisual::FInfo ImpactVisualInfoType;
				typedef NCsProjectile::NImpact::NVisual::NFX::FInfo ImpactFXInfoType;
				
				const ImpactVisualInfoType& Info = ImpactVisualData->GetImpactVisualInfo(SurfaceType);
				const ImpactFXInfoType& FXInfo   = Info.GetFXInfo();

				if (FXInfo.GetbFX())
				{
					typedef NCsFX::NManager::FLibrary FXManagerLibrary;
					typedef NCsPooledObject::NPayload::FImplSlice PayloadImplType;

					PayloadImplType Payload;
					Payload.Instigator = Cache->GetInstigator();

					FTransform Transform = FTransform::Identity;
					Transform.SetLocation(Hit.Location);

					typedef NCsProjectile::NImpact::NVisual::EDirection DirectionType;

					const DirectionType& Direction = FXInfo.GetDirection();
					// Normal
					if (Direction == DirectionType::Normal)
					{
						Transform.SetRotation(Hit.ImpactNormal.Rotation().Quaternion());
					}
					// Inverse Normal
					else
					if (Direction == DirectionType::Normal)
					{
						Transform.SetRotation((-Hit.ImpactNormal).Rotation().Quaternion());
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

					FXManagerLibrary::SpawnChecked(Context, GetWorldContext(), &Payload, FXInfo.GetFX(), Transform);
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

	typedef NCsFX::NManager::FLibrary FXManagerLibrary;

	TrailFXPooled = const_cast<FCsFXActorPooled*>(FXManagerLibrary::FindSafeObject(Context, GetWorldContext(), FX, Index, Log));
}

#pragma endregion FX

// Modifier
#pragma region

#define CollisionDataType NCsProjectile::NData::NCollision::ICollision
void ACsProjectilePooledImpl::ApplyHitCountModifiers(const FString& Context, const CollisionDataType* CollisionData)
{
#undef CollisionDataType
	HitCount = CollisionData->GetHitCount();

	typedef NCsProjectile::NModifier::FLibrary ModifierLibrary;

	HitCount = ModifierLibrary::ModifyIntChecked(Context, Modifiers, NCsProjectileModifier::HitCount, HitCount);
}

void ACsProjectilePooledImpl::StartMovementFromModifiers(const FString& Context, const FVector& Direction)
{
	typedef ACsProjectilePooledImpl::FMovementImpl::EStart StartType;

	MovementComponent->InitialSpeed = MovementImpl.GetInitialSpeed(StartType::FromModifiers);
	MovementComponent->MaxSpeed		= MovementImpl.GetMaxSpeed(StartType::FromModifiers);

	if (MovementComponent->InitialSpeed > MovementComponent->MaxSpeed)
		MovementComponent->InitialSpeed = MovementComponent->MaxSpeed;

	MovementComponent->Velocity				  = MovementComponent->InitialSpeed * Direction;
	MovementComponent->ProjectileGravityScale = Data->GetGravityScale();
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

	typedef NCsDamage::NModifier::FAllocated AllocateModifierType;

	for (AllocateModifierType& Modifier : Modifiers)
	{
		Modifier.Clear();
	}
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

	DataTypes.Reset(DataTypes.Max());
	Modifiers.Reset(Modifiers.Max());
}

#define RangeType NCsDamage::NRange::IRange
const RangeType* ACsProjectilePooledImpl::GetDamageRangeChecked(const FString& Context)
{
	typedef NCsProjectile::NData::FLibrary PrjDataLibrary;
	typedef NCsDamage::NData::FLibrary DmgDataLibrary;
	typedef NCsDamage::NData::IData DmgDataType;
	typedef NCsDamage::NData::NShape::IShape DmgShapeDataType;

	// NOTE: For now assume the ONLY way to get RangeType is from a Damage Shape.
	//		  Damage Shape is an object that implements the interface: DmgShapeDataType (NCsDamage::NData::NShape::IShape)
	
	// DamageDataType (NCsProjectile::NData::NDamage::IDamage)
	{
		typedef NCsProjectile::NData::NDamage::IDamage PrjDmgDataType;

		if (const PrjDmgDataType* PrjDmgData = PrjDataLibrary::GetSafeInterfaceChecked<PrjDmgDataType>(Context, Data))
		{
			const DmgDataType* DmgData = PrjDmgData->GetDamageData();

			if (const DmgShapeDataType* DmgShapeData = DmgDataLibrary::GetSafeInterfaceChecked<DmgShapeDataType>(Context, DmgData))
			{
				return DmgShapeData->GetRange();
			}
		}
	}
	// GetDamageDataTypeDataType (NCsData::IGetDamageDataType)
	{
		typedef NCsData::IGetDamageDataType GetDamageDataTypeDataType;

		if (const GetDamageDataTypeDataType* GetDamageDataType = PrjDataLibrary::GetSafeInterfaceChecked<GetDamageDataTypeDataType>(Context, Data))
		{
			typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

			const DmgDataType* DmgData = DamageManagerLibrary::GetDataChecked(Context, GetWorldContext(), GetDamageDataType);

			if (const DmgShapeDataType* DmgShapeData = DmgDataLibrary::GetSafeInterfaceChecked<DmgShapeDataType>(Context, DmgData))
			{
				return DmgShapeData->GetRange();
			}
		}
	}
	// GetDamageDataTypeDataTypes (NCsData::IGetDamageDataTypes)
	{
		typedef NCsData::IGetDamageDataTypes GetDamageDataTypeDataTypes;

		if (const GetDamageDataTypeDataTypes* GetDamageDataTypes = PrjDataLibrary::GetSafeInterfaceChecked<GetDamageDataTypeDataTypes>(Context, Data))
		{
			typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

			static TArray<DmgDataType*> DamageDatas;

			DamageManagerLibrary::GetDatasChecked(Context, GetWorldContext(), GetDamageDataTypes, DamageDatas);

			for (const DmgDataType* DmgData : DamageDatas)
			{
				if (const DmgShapeDataType* DmgShapeData = DmgDataLibrary::GetSafeInterfaceChecked<DmgShapeDataType>(Context, DmgData))
				{
					DamageDatas.Reset(DamageDatas.Max());
					return DmgShapeData->GetRange();
				}
			}
			DamageDatas.Reset(DamageDatas.Max());
		}
	}
	checkf(0, TEXT("%s: Failed to get Damage Data from %s"), *Context, *PrjDataLibrary::PrintDataAndClass(Data));
	return nullptr;
}
#undef RangeType

float ACsProjectilePooledImpl::GetMaxDamageRangeChecked(const FString& Context)
{
	typedef NCsDamage::NModifier::FLibrary DmgModifierLibrary;
	typedef NCsDamage::NRange::IRange RangeType;

	const RangeType* Range = GetDamageRangeChecked(Context);

	return DmgModifierLibrary::GetMaxRangeChecked(Context, DamageImpl.Modifiers, Range);
}

#pragma endregion Damage