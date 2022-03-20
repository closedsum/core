#include "Projectile/CsProjectileWeaponActorPooled.h"
#include "CsWp.h"

// CVar
#include "Projectile/CsCVars_ProjectileWeapon.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "Types/CsCached.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Managers/Time/CsLibrary_Manager_Time.h"
#include "Managers/Trace/CsLibrary_Manager_Trace.h"
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"
#include "Managers/Sound/CsLibrary_Manager_Sound.h"
#include "Data/CsLibrary_Data_Weapon.h"
#include "Data/CsLibrary_Data_Projectile.h"
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
#include "Payload/CsLibrary_Payload_Projectile.h"
#include "Managers/Sound/Payload/CsLibrary_Payload_Sound.h"
#include "Managers/FX/Payload/CsLibrary_Payload_FX.h"
#include "Projectile/Params/Launch/CsLibrary_Params_ProjectileWeapon_Launch.h"
#include "Library/CsLibrary_Camera.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsWeaponSettings.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
#include "Managers/Projectile/CsManager_Projectile.h"
#include "Managers/Sound/CsManager_Sound.h"
#include "Managers/FX/Actor/CsManager_FX_Actor.h"
#include "Managers/Trace/CsManager_Trace.h"
// Data
#include "Data/CsData_Weapon.h"
#include "Projectile/Data/CsData_ProjectileWeapon.h"
#include "Projectile/Data/Sound/CsData_ProjectileWeapon_SoundFire.h"
#include "Projectile/Data/Visual/CsData_ProjectileWeapon_VisualFire.h"
#include "Data/CsData_Projectile.h"
#include "Data/Types/CsData_GetProjectileType.h"
#include "Data/Collision/CsData_Projectile_Collision.h"
// Containers
#include "Containers/CsInterfaceMap.h"
// Pooled
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Weapon
#include "Payload/CsPayload_WeaponImpl.h"
#include "Cache/CsCache_WeaponImpl.h"
// Projectile
#include "Payload/CsPayload_ProjectileImpl.h"
#include "Payload/CsPayload_ProjectileImplSlice.h"
#include "Payload/Modifier/CsPayload_Projectile_ModifierImplSlice.h"
#include "Managers/Projectile/CsProjectilePooledImpl.h"
// Sound
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"
// FX
#include "Managers/FX/Payload/CsPayload_FXImpl.h"
// Params
#include "Projectile/Params/Launch/Trace/CsParams_ProjectileWeapon_LaunchTrace.h"
#include "Projectile/Data/Sound/CsParams_ProjectileWeapon_SoundFire.h"
// Component
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
// Animation
#include "Animation/AnimInstance.h"

// Cached 
#pragma region

namespace NCsProjectileWeaponActorPooled
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, SetUpdateGroup);
			CS_DEFINE_CACHED_STRING(Group, "Group");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, Allocate);

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, SetWeaponType);
			CS_DEFINE_CACHED_STRING(Type, "Type");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, SetProjectileType);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, Init);
			CS_DEFINE_CACHED_STRING(UpdateGroup, "UpdateGroup");
			CS_DEFINE_CACHED_STRING(WeaponType, "WeaponType");
			CS_DEFINE_CACHED_STRING(ProjectileType, "ProjectileType");
			CS_DEFINE_CACHED_STRING(IdleState, "IdleState");
			CS_DEFINE_CACHED_STRING(FireState, "FireState");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, OnUpdate_HandleStates);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, CanFire);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, Fire);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, Fire_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, FireProjectile);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, SetProjectilePayload);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, LaunchProjectile);
		}

		namespace Name
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(ACsProjectileWeaponActorPooled, Fire_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(ACsProjectileWeaponActorPooled, Abort_Fire_Internal);
		}

		namespace NTimeBetweenShotsImpl
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled::FTimeBetweenShotsImpl, OnElapsedTime);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled::FTimeBetweenShotsImpl, OnElapsedTime_Internal);
			}

			namespace Name
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(ACsProjectileWeaponActorPooled::FTimeBetweenShotsImpl, OnElapsedTime_Internal);
			}
		}

		namespace NProjectileImpl
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled::FProjectileImpl, GetLaunchLocation);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled::FProjectileImpl, GetLaunchDirection);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled::FProjectileImpl, Launch);
			}
		}

		namespace NSoundImpl
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled::FSoundImpl, Play);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled::FSoundImpl, SetPayload);
			}
		}

		namespace NFXImpl
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled::FFXImpl, Play);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled::FFXImpl, SetPayload);
			}
		}
	}
}

#pragma endregion Cached

ACsProjectileWeaponActorPooled::ACsProjectileWeaponActorPooled(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	// ICsUpdate
	UpdateGroup(),
	// ICsPooledObject
	Cache(nullptr),
	WeaponType(),
	Data(nullptr),
	PrjWeaponData(nullptr),
	ProjectileType(),
	// Owner
	MyOwner(nullptr),
	MyOwnerAsActor(nullptr),
	// Skin
	SkeletalMeshComponent(nullptr),
	StaticMeshComponent(nullptr),
	VisualMeshComponent(nullptr),
	// State
	CurrentState(),
	IdleState(),
	FireState(),
	// Ammo
	CurrentAmmo(0),
	// Fire
	bHasFired(false),
	bFire(false),
	bFire_Last(false),
	Fire_StartTime(0.0f),
	FireCount(0),
	FireHandle(),
	// Projectile
	CurrentProjectilePerShotIndex(0),
	ProjectileImpl(nullptr),
	bOverride_ProjectileImpl_GetLaunchDirection(false),
	// Sound
	SoundImpl(nullptr)
{
	// StatisMeshComponent
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetNotifyRigidBodyCollision(false);
	StaticMeshComponent->SetGenerateOverlapEvents(false);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	StaticMeshComponent->SetHiddenInGame(true);
	StaticMeshComponent->SetCastShadow(false);
	StaticMeshComponent->SetReceivesDecals(false);
	StaticMeshComponent->bUseAsOccluder = false;
	StaticMeshComponent->SetComponentTickEnabled(false);
	// SkeletalMeshComponent
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetNotifyRigidBodyCollision(false);
	SkeletalMeshComponent->SetGenerateOverlapEvents(false);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SkeletalMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SkeletalMeshComponent->SetHiddenInGame(true);
	SkeletalMeshComponent->SetCastShadow(false);
	SkeletalMeshComponent->SetReceivesDecals(false);
	SkeletalMeshComponent->bUseAsOccluder = false;
	SkeletalMeshComponent->SetComponentTickEnabled(false);
	SkeletalMeshComponent->bNoSkeletonUpdate = true;
	SkeletalMeshComponent->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	SkeletalMeshComponent->KinematicBonesUpdateType = EKinematicBonesUpdateToPhysics::SkipAllBones;
}

// UObject Interface
#pragma region

void ACsProjectileWeaponActorPooled::BeginDestroy()
{
	Super::BeginDestroy();
	
	CS_SILENT_CLEAR_SCOPED_TIMER_HANDLE(FireScopedHandle.Handle);

	if (ProjectileImpl)
	{
		CS_SILENT_CLEAR_SCOPED_TIMER_HANDLE(ProjectileImpl->LaunchScopedHandle);

		delete ProjectileImpl;
		ProjectileImpl = nullptr;
	}

	if (SoundImpl)
	{
		delete SoundImpl;
		SoundImpl = nullptr;
	}

	if (FXImpl)
	{
		delete FXImpl;
		FXImpl = nullptr;
	}
}

#pragma endregion UObject Interface

// AActor Interface
#pragma region

void ACsProjectileWeaponActorPooled::BeginPlay()
{
	Super::BeginPlay();

	TimeBetweenShotsImpl.Outer = this;

	ProjectileImpl = ConstructProjectileImpl();
	ProjectileImpl->Outer = this;

	SoundImpl = ConstructSoundImpl();
	SoundImpl->Weapon = this;

	FXImpl = ConstructFXImpl();
	FXImpl->Weapon = this;

	// ScopedHandles
#if !UE_BUILD_SHIPPING
	{
		using namespace NCsProjectileWeaponActorPooled::NCached;

		// FireScopedHandle
		{
			const FString& ScopeName		   = Str::Fire_Internal;
			const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponProjectile;
			const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponProjectileScopedTimerFire;

			FireScopedHandle.Handle = FCsManager_ScopedTimer::Get().GetHandle(&ScopeName, ScopedGroup, ScopeLog);
		}
		// LaunchScopedHandle
		{
			const FString& ScopeName		   = NProjectileImpl::Str::Launch;
			const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponProjectile;
			const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponProjectileProjectileScopedTimerLaunch;

			ProjectileImpl->LaunchScopedHandle = FCsManager_ScopedTimer::Get().GetHandle(&ScopeName, ScopedGroup, ScopeLog);
		}
	}
#endif // #if !UE_BUILD_SHIPPING
}

#pragma endregion AActor Interface

// ICsUpdate
#pragma region

void ACsProjectileWeaponActorPooled::Update(const FCsDeltaTime& DeltaTime)
{ 
	OnUpdate_HandleStates(DeltaTime);
}

#pragma endregion ICsUpdate

// Update
#pragma region

void ACsProjectileWeaponActorPooled::SetUpdateGroup(const FECsUpdateGroup& Group)
{
	using namespace NCsProjectileWeaponActorPooled::NCached;

	const FString& Context = Str::SetUpdateGroup;

	check(EMCsUpdateGroup::Get().IsValidEnumChecked(Context, Str::Group, Group));

	UpdateGroup = Group;
}

#pragma endregion Update

// ICsPooledObject
#pragma region

#define PooledPayloadType NCsPooledObject::NPayload::IPayload
void ACsProjectileWeaponActorPooled::Allocate(PooledPayloadType* Payload)
{
#undef PooledPayloadType

	using namespace NCsProjectileWeaponActorPooled::NCached;

	const FString& Context = Str::Allocate;

	CS_IS_PTR_NULL_CHECKED(Payload)

	Cache->Allocate(Payload);

	typedef NCsPooledObject::NPayload::FLibrary PayloadLibrary;
	typedef NCsWeapon::NPayload::IPayload PayloadType;

	PayloadType* WeaponPayload = PayloadLibrary::GetInterfaceChecked<PayloadType>(Context, Payload);

	SetWeaponType(WeaponPayload->GetType());
	SetUpdateGroup(WeaponPayload->GetUpdateGroup());

	MyOwner		   = Payload->GetOwner();
	MyOwnerAsActor = Cast<AActor>(MyOwner);

	// Get Data
	typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;
	typedef NCsWeapon::NProjectile::NData::IData PrjWeaponDataType;

	Data		  = WeaponManagerLibrary::GetDataChecked(Context, this, WeaponType);
	PrjWeaponData = WeaponDataLibrary::GetInterfaceChecked<PrjWeaponDataType>(Context, Data);

	ICsData_GetProjectileType* GetProjectileType = WeaponDataLibrary::GetInterfaceChecked<ICsData_GetProjectileType>(Context, Data);

	SetProjectileType(GetProjectileType->GetProjectileType());

	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);

	// TODO: May need to streamline this logic slightly
	
	// TODO: Set Skin

	// If the Parent is set, attach the Weapon to the Parent
	if (VisualMeshComponent)
	{
		USceneComponent* Parent = nullptr;

		UObject* Object = Payload->GetParent();

		// SceneComponent
		if (USceneComponent* Component = Cast<USceneComponent>(Object))
			Parent = Component;
		// Actor -> Get RootComponent
		else
		if (AActor* Actor = Cast<AActor>(Object))
			Parent = Actor->GetRootComponent();

		const FTransform& Transform = WeaponPayload->GetTransform();

		if (Parent)
		{
			// TODO: Get Bone Name
			const FName Bone = NAME_None;
			// TODO: Get Attachment Rule
			const FAttachmentTransformRules Rule = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

			VisualMeshComponent->AttachToComponent(Parent, Rule, Bone);
		}
		// NO Parent, set the Actor Transform
		else
		{
			SetActorTransform(Transform);
		}
	}

	// Set States
	const FCsWeaponSettings_ProjectileWeaponImpl& Settings = FCsWeaponSettings_ProjectileWeaponImpl::Get();

	CS_IS_VALID_CHECKED(Settings);

	IdleState	 = Settings.IdleState;
	FireState	 = Settings.FireState;
	CurrentState = IdleState;

	CurrentAmmo = PrjWeaponData->GetMaxAmmo();

	TimeBetweenShotsImpl.Base = PrjWeaponData->GetTimeBetweenShots();
	TimeBetweenShotsImpl.ResetValueToBase();
}

void ACsProjectileWeaponActorPooled::Deallocate()
{
	// End Routines
	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

	if (UCsCoroutineScheduler* Scheduler = CoroutineSchedulerLibrary::GetSafe(this))
	{
		Scheduler->End(UpdateGroup, FireHandle);
	}
	FireHandle.Invalidate();

	// Skin
	SetRootComponent(nullptr);

	StaticMeshComponent->SetComponentTickEnabled(false);
	StaticMeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	StaticMeshComponent->SetRelativeLocation(FVector::ZeroVector);
	StaticMeshComponent->SetHiddenInGame(true);
	StaticMeshComponent->ComponentTags.Reset(StaticMeshComponent->ComponentTags.Max());

	// TODO: FUTURE: Look into what can be preserved

	if (UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance())
		AnimInstance->StopAllMontages(0.0f);

	SkeletalMeshComponent->SetSkeletalMesh(nullptr);
	SkeletalMeshComponent->SetAnimInstanceClass(nullptr);
	SkeletalMeshComponent->SetComponentTickEnabled(false);
	SkeletalMeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	SkeletalMeshComponent->SetRelativeLocation(FVector::ZeroVector);
	SkeletalMeshComponent->SetHiddenInGame(false);
	SkeletalMeshComponent->ComponentTags.Reset(SkeletalMeshComponent->ComponentTags.Max());

	VisualMeshComponent = nullptr;

	WeaponType = EMCsWeapon::Get().GetMAX();

	Data = nullptr;
	PrjWeaponData = nullptr;

	ProjectileType = EMCsProjectile::Get().GetMAX();
	
	MyOwner = nullptr;
	MyOwnerAsActor = nullptr;

	SkeletalMeshComponent = nullptr;
	StaticMeshComponent = nullptr;
	VisualMeshComponent = nullptr;

	CurrentState = IdleState;

	CurrentAmmo = 0;
	
	bHasFired = false;
	bFire = false;
	bFire_Last = false;
	Fire_StartTime = 0.0f;
	FireCount = 0;
	
	// bOverride_ProjectileImpl_GetLaunchDirection = false;

	Cache->Deallocate();
}

#pragma endregion ICsPooledObject

// PooledObject
#pragma region

void ACsProjectileWeaponActorPooled::ConstructCache()
{
	typedef NCsWeapon::NCache::FImpl CacheImplType;

	Cache = new CacheImplType();
}

#pragma endregion PooledObject

void ACsProjectileWeaponActorPooled::SetWeaponType(const FECsWeapon& Type)
{
	using namespace NCsProjectileWeaponActorPooled::NCached;

	const FString& Context = Str::SetWeaponType;

	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeapon, Type);

	WeaponType = Type;
}

// ICsWeapon
#pragma region

#pragma endregion ICsWeapon

void ACsProjectileWeaponActorPooled::SetProjectileType(const FECsProjectile& Type)
{
	using namespace NCsProjectileWeaponActorPooled::NCached;

	const FString& Context = Str::SetProjectileType;

	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectile, Type);

	ProjectileType = Type;
}

// ICsProjectileWeapon
#pragma region

void ACsProjectileWeaponActorPooled::StartFire()
{
	bFire = true;

	Update(FCsDeltaTime::Zero);
}

void ACsProjectileWeaponActorPooled::StopFire()
{
	bFire = false;

	Update(FCsDeltaTime::Zero);
}

#pragma endregion ICsProjectileWeapon

// State
#pragma region

void ACsProjectileWeaponActorPooled::OnUpdate_HandleStates(const FCsDeltaTime& DeltaTime)
{
	using namespace NCsProjectileWeaponActorPooled::NCached;

	const FString& Context = Str::OnUpdate_HandleStates;

	typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

	const FCsDeltaTime& TimeSinceStart = TimeManagerLibrary::GetTimeSinceStartChecked(Context, this, UpdateGroup);

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogWeaponProjectileState))
	{
		UE_LOG(LogCsWp, Warning, TEXT("%s: CurrentState: %s."), *Context, CurrentState.ToChar());
	}
#endif // #if !UE_BUILD_SHIPPING

	// Idle
	if (CurrentState == IdleState)
	{
		if (CanFire())
		{
			Fire();

			TimeBetweenShotsImpl.OnElapsedTime();

			CurrentState = FireState;

#if !UE_BUILD_SHIPPING
			if (CS_CVAR_LOG_IS_SHOWING(LogWeaponProjectileStateTransition))
			{
				UE_LOG(LogCsWp, Warning, TEXT("%s: CurrentState: Idle -> Fire."), *Context);
			}
#endif // #if !UE_BUILD_SHIPPING
		}
	}

	// Fire
	if (CurrentState == FireState)
	{
		// If can fire, start firing
		if (CanFire())
		{
			Fire();

			TimeBetweenShotsImpl.OnElapsedTime();
		}
		// If no firing is active, go to idle
		else
		if (FireCount == 0)
		{
			CurrentState = IdleState;

#if !UE_BUILD_SHIPPING
			if (CS_CVAR_LOG_IS_SHOWING(LogWeaponProjectileStateTransition))
			{
				UE_LOG(LogCsWp, Warning, TEXT("%s: CurrentState: Fire -> Idle."), *Context);
			}
#endif // #if !UE_BUILD_SHIPPING
		}
	}

	bFire_Last = bFire;
}

#pragma endregion State

// Ammo
#pragma region

void ACsProjectileWeaponActorPooled::ConsumeAmmo()
{
	int32 PreviousAmmo = CurrentAmmo;
	--CurrentAmmo;

	OnConsumeAmmo_Event.Broadcast(this, PreviousAmmo, CurrentAmmo);
}

#pragma endregion Ammo

// Fire
#pragma region

bool ACsProjectileWeaponActorPooled::CanFire() const
{
	using namespace NCsProjectileWeaponActorPooled::NCached;

	const FString& Context = Str::CanFire;
	
	typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

	const FCsDeltaTime& TimeSinceStart = TimeManagerLibrary::GetTimeSinceStartChecked(Context, this, UpdateGroup);

	// Check if enough time has elapsed to fire again.
	const bool Pass_Time = !bHasFired || (TimeSinceStart.Time - Fire_StartTime > TimeBetweenShotsImpl.Value);
	// Check if bFire is set, its not on release, and its either bFire is just set or FullAuto.
	const bool Pass_Fire = bFire && !PrjWeaponData->DoFireOnRelease() && (PrjWeaponData->IsFullAuto() || !bFire_Last);
	// Check if bFire has just been unset and on release.
	const bool Pass_FireOnRelease = !bFire && PrjWeaponData->DoFireOnRelease() && bFire_Last;
	// Check if has ammo to fire.
	const bool Pass_Ammo = PrjWeaponData->HasInfiniteAmmo() || CurrentAmmo > 0;

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogWeaponProjectileCanFire))
	{
		using namespace NCsCached;

		UE_LOG(LogCsWp, Warning, TEXT("%s"), *Context);
		// Pass_Time
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_Time (%s): %f - %f > %f"), ToChar(Pass_Time), TimeSinceStart.Time, Fire_StartTime, TimeBetweenShotsImpl.Value);
		// Pass_Fire
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_Fire (%s): %s && %s && (%s || %s)"), ToChar(Pass_Fire), ToChar(bFire), ToChar(!PrjWeaponData->DoFireOnRelease()), ToChar(PrjWeaponData->IsFullAuto()), ToChar(!bFire_Last));
		// Pass_FireOnRelease
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_FireOnRelease (%s): %s && %s && %s"), ToChar(Pass_FireOnRelease), ToChar(!bFire), ToChar(PrjWeaponData->DoFireOnRelease()), ToChar(bFire_Last));
		// Pass_Ammo
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_Ammo (%s): %s || %s"), ToChar(Pass_Ammo), ToChar(PrjWeaponData->HasInfiniteAmmo()), ToChar(CurrentAmmo > 0));

		// Result
		UE_LOG(LogCsWp, Warning, TEXT(" Result (%s): %s && (%s || %s) && %s"), ToChar(Pass_Time && (Pass_Fire || Pass_FireOnRelease) && Pass_Ammo), ToChar(Pass_Time), ToChar(Pass_Fire), ToChar(Pass_FireOnRelease), ToChar(Pass_Ammo));
	}
#endif // #if !UE_BUILD_SHIPPING

	return Pass_Time && (Pass_Fire || Pass_FireOnRelease) && Pass_Ammo;
}

void ACsProjectileWeaponActorPooled::Fire()
{
	using namespace NCsProjectileWeaponActorPooled::NCached;

	const FString& Context = Str::Fire;

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

	UCsCoroutineScheduler* Scheduler = CoroutineSchedulerLibrary::GetChecked(Context, this);

	// End previous Fire Routine
	Scheduler->End(UpdateGroup, FireHandle);

	typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

	const FCsDeltaTime& TimeSinceStart = TimeManagerLibrary::GetTimeSinceStartChecked(Context, this, UpdateGroup);

	Fire_StartTime = TimeSinceStart.Time;

	// Setup Fire Routine
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

	#define COROUTINE Fire_Internal

	Payload->CoroutineImpl.BindUObject(this, &ACsProjectileWeaponActorPooled::COROUTINE);
	Payload->StartTime = TimeManagerLibrary::GetTimeChecked(Context, this, UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);
	Payload->OnEnds.AddDefaulted();
	Payload->OnEnds.Last().BindUObject(this, &ACsProjectileWeaponActorPooled::Fire_Internal_OnEnd);
	Payload->AbortMessages.Add(Name::Abort_Fire_Internal);

	#undef COROUTINE

	Payload->SetValue_Flag(CS_FIRST, PrjWeaponData->HasInfiniteAmmo());
	Payload->SetValue_Int(CS_FIRST, PrjWeaponData->GetProjectilesPerShot());
	Payload->SetValue_Float(CS_FIRST, PrjWeaponData->GetTimeBetweenProjectilesPerShot());

	bHasFired = true;

	FireHandle = Scheduler->Start(Payload);
}

char ACsProjectileWeaponActorPooled::Fire_Internal(FCsRoutine* R)
{
	using namespace NCsProjectileWeaponActorPooled::NCached;

	const bool& bInfiniteAmmo				   = R->GetValue_Flag(CS_FIRST);
	const int32& ProjectilesPerShot			   = R->GetValue_Int(CS_FIRST);
	const float& TimeBetweenProjectilesPerShot = R->GetValue_Float(CS_FIRST);

	FCsDeltaTime& ElapsedTime = R->GetValue_DeltaTime(CS_FIRST);

	ElapsedTime += R->DeltaTime;
	
	CS_COROUTINE_BEGIN(R);

	++FireCount;

	do 
	{
		{
			CS_SET_SCOPED_TIMER_HANDLE(FireScopedHandle);

			ElapsedTime.Reset();

			if (!bInfiniteAmmo)
				ConsumeAmmo();

			ProjectileImpl->Launch();
			SoundImpl->Play();
			FXImpl->Play();

			// Increment the shot index
			CurrentProjectilePerShotIndex = FMath::Min(CurrentProjectilePerShotIndex + 1, ProjectilesPerShot);

			// Check if more projectiles should be fired, if so wait
			if (CurrentProjectilePerShotIndex < ProjectilesPerShot)
			{
				CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= TimeBetweenProjectilesPerShot);
			}

			CS_UPDATE_SCOPED_TIMER_HANDLE(FireScopedHandle);
		}
	} while (CurrentProjectilePerShotIndex < ProjectilesPerShot);

	CS_COROUTINE_END(R);
}

void ACsProjectileWeaponActorPooled::Fire_Internal_OnEnd(FCsRoutine* R)
{
	--FireCount;
}

void ACsProjectileWeaponActorPooled::FTimeBetweenShotsImpl::OnElapsedTime()
{
	using namespace NCsProjectileWeaponActorPooled::NCached::NTimeBetweenShotsImpl;

	const FString& Context = Str::OnElapsedTime;

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

	UCsCoroutineScheduler* Scheduler = CoroutineSchedulerLibrary::GetChecked(Context, Outer);

	// Setup Routine
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(Outer->GetUpdateGroup());

	#define COROUTINE OnElapsedTime_Internal

	typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

	Payload->CoroutineImpl.BindRaw(this, &ACsProjectileWeaponActorPooled::FTimeBetweenShotsImpl::COROUTINE);
	Payload->StartTime = TimeManagerLibrary::GetTimeChecked(Context, Outer, Outer->GetUpdateGroup());
	Payload->Owner.SetObject(Outer);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);

	#undef COROUTINE

	// Get total elapsed time (= TimeBetweenShots)
	typedef NCsWeapon::NProjectile::NData::IData ProjectileDataType;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	static const int32 TIME_BETWEEN_SHOTS = 0;
	Payload->SetValue_Float(TIME_BETWEEN_SHOTS, Value);

	Scheduler->Start(Payload);
}

char ACsProjectileWeaponActorPooled::FTimeBetweenShotsImpl::OnElapsedTime_Internal(FCsRoutine* R)
{
	FCsDeltaTime& ElapsedTime			   = R->GetValue_DeltaTime(CS_FIRST);
	const FCsDeltaTime PreviousElapsedTime = ElapsedTime;

	ElapsedTime += R->DeltaTime;

	static const int32 TIME_BETWEEN_SHOTS = 0;
	const float& Captured_TimeBetweenShots = R->GetValue_Float(TIME_BETWEEN_SHOTS);

	// Broadcast ElapsedTime events

		// Time
	const float& PreviousTime = PreviousElapsedTime.Time;
	const float NewTime		   = FMath::Max(ElapsedTime.Time, Captured_TimeBetweenShots);

	OnElapsedTime_Event.Broadcast(Outer, PreviousTime, NewTime);
	// Percent
	const float PreviousPercent = PreviousElapsedTime.Time / Captured_TimeBetweenShots;
	const float NewPercent		= FMath::Min(ElapsedTime.Time / Captured_TimeBetweenShots, 1.0f);

	OnElapsedTimeAsPercent_Event.Broadcast(Outer, PreviousPercent, NewPercent);

	CS_COROUTINE_BEGIN(R);

	ElapsedTime.Reset();

	CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= Captured_TimeBetweenShots);

	OnComplete_Event.Broadcast(Outer);

	CS_COROUTINE_END(R);
}

	// Projectile
#pragma region

#define ProjectilePayloadType NCsProjectile::NPayload::IPayload

bool ACsProjectileWeaponActorPooled::FProjectileImpl::SetPayload(const FString& Context, ProjectilePayloadType* Payload)
{
	bool Result = true;

	typedef NCsProjectile::NPayload::FLibrary PrjPayloadLibrary;

	// PooledObject
	{
		typedef NCsPooledObject::NPayload::FImplSlice SliceType;
		typedef NCsPooledObject::NPayload::IPayload SliceInterfaceType;

		SliceType* Slice = PrjPayloadLibrary::StaticCastChecked<SliceType, SliceInterfaceType>(Context, Payload);
		Slice->Instigator = Outer;
		Slice->Owner	  = Outer->GetMyOwner();
	}
	// Projectile
	{
		typedef NCsProjectile::NPayload::FImplSlice SliceType;
		typedef NCsProjectile::NPayload::IPayload SliceInterfaceType;

		SliceType* Slice = PrjPayloadLibrary::StaticCastChecked<SliceType, SliceInterfaceType>(Context, Payload);
		Slice->Type		 = Outer->GetProjectileType();
		Slice->Location  = GetLaunchLocation();
		Slice->Direction = GetLaunchDirection();
	}
	// Projectile Modifiers
	{
		typedef NCsProjectile::NPayload::NModifier::FImplSlice SliceType;
		typedef NCsProjectile::NPayload::NModifier::IModifier SliceInterfaceType;

		if (SliceType* Slice = PrjPayloadLibrary::SafeStaticCastChecked<SliceType, SliceInterfaceType>(Context, Payload))
		{
			typedef NCsProjectile::NModifier::IModifier PrjModifierType;

			static TArray<PrjModifierType*> Modifiers;
			Modifiers.Reset(Modifiers.Max());

			Outer->GetProjectileModifiers(Modifiers);

			Slice->SetModifiers(Modifiers);
		}
	}
	return Result;
}

bool ACsProjectileWeaponActorPooled::FProjectileImpl::CopyPayload(const FString& Context, const ProjectilePayloadType* From, ProjectilePayloadType* To)
{
	return NCsProjectile::NPayload::FLibrary::CopyChecked(Context, From, To);
}

#undef ProjectilePayloadType

FVector ACsProjectileWeaponActorPooled::FProjectileImpl::GetLaunchLocation()
{
	using namespace NCsProjectileWeaponActorPooled::NCached::NProjectileImpl;

	const FString& ScopeName		   = Str::GetLaunchLocation;
	const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponProjectile;
	const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponProjectileScopedTimerGetLaunchLocation;

	CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

	const FString& Context = Str::GetLaunchLocation;

	// Get Data Slice
	typedef NCsWeapon::NProjectile::NData::IData WeaponDataType;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	WeaponDataType* WeaponData = WeaponDataLibrary::GetInterfaceChecked<WeaponDataType>(Context, Outer->GetData());
	
	// Get Launch Params
	using namespace NCsWeapon::NProjectile::NParams::NLaunch;

	const ILaunch* LaunchParams = WeaponData->GetLaunchParams();

	checkf(LaunchParams, TEXT("%s: Failed to get LaunchParams from Data."), *Context);

	const ELocation& LocationType = LaunchParams->GetLocationType();

	// Owner
	if (LocationType == ELocation::Owner)
	{
		UObject* TheOwner = Outer->GetMyOwner();

		checkf(TheOwner, TEXT("%s: No Owner found for %s."), *Context, *(Outer->PrintNameAndClass()));

		// Actor
		if (AActor* Actor = Cast<AActor>(TheOwner))
			return Actor->GetActorLocation();
		// Component
		if (USceneComponent* Component = Cast<USceneComponent>(TheOwner))
			return Component->GetComponentLocation();

		checkf(0, TEXT("%s: Failed to get Location from %s."), *Context, *(Outer->PrintNameClassAndOwner()));
	}
	// Bone
	if (LocationType == ELocation::Bone)
	{
		checkf(0, TEXT("NOT IMPLEMENTED"));
	}
	// Component
	if (LocationType == ELocation::Component)
	{
		checkf(LaunchComponentTransform, TEXT("%s: LaunchComponentTransform is NULL."));

		return LaunchComponentTransform->GetComponentLocation();
	}
	return FVector::ZeroVector;
}

FVector ACsProjectileWeaponActorPooled::FProjectileImpl::GetLaunchDirection()
{
	using namespace NCsProjectileWeaponActorPooled::NCached::NProjectileImpl;

	const FString& ScopeName		   = Str::GetLaunchDirection;
	const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponProjectile;
	const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponProjectileScopedTimerGetLaunchDirection;

	CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

	const FString& Context = Str::GetLaunchDirection;

#if WITH_EDITOR
	if (Outer->ShouldOverride_ProjectileImpl_GetLaunchDirection())
	{
		if (CS_CVAR_LOG_IS_SHOWING(LogOverrideFunctions))
		{
			UE_LOG(LogCsWp, Warning, TEXT("%s OVERRIDDEN for %s."), *Context, *(Outer->GetName()));
		}
		return Outer->Override_ProjectileImpl_GetLaunchDirection();
	}
#endif // #if WITH_EDITOR

	// Get Data Slice
	typedef NCsWeapon::NProjectile::NData::IData WeaponDataType;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	WeaponDataType* WeaponData = WeaponDataLibrary::GetInterfaceChecked<WeaponDataType>(Context, Outer->GetData());
	
	// Get Launch Params
	using namespace NCsWeapon::NProjectile::NParams::NLaunch;

	const ILaunch* LaunchParams = WeaponData->GetLaunchParams();

	checkf(LaunchParams, TEXT("%s: Failed to get LaunchParams from Data."), *Context);

	const ELocation& LocationType   = LaunchParams->GetLocationType();
	const EDirection& DirectionType = LaunchParams->GetDirectionType();
	const int32& DirectionRules		= LaunchParams->GetDirectionRules();

	checkf(DirectionRules != NCsRotationRules::None, TEXT("%s: No DirectionRules set in Launchparams for Data."), *Context);

	// Owner
	if (DirectionType == EDirection::Owner)
	{
		if (UObject* TheOwner = Outer->GetMyOwner())
		{
			// AActor
			if (AActor* Actor = Cast<AActor>(TheOwner))
			{
				const FVector Dir = NCsRotationRules::GetRotation(Actor, DirectionRules).Vector();
				CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(LaunchParams, Dir));
				return Dir;
			}
			// USceneComponent
			if (USceneComponent* Component = Cast<USceneComponent>(TheOwner))
			{
				const FVector Dir = NCsRotationRules::GetRotation(Component, DirectionRules).Vector();
				CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(LaunchParams, Dir));
				return Dir;
			}
			checkf(0, TEXT("%s: Failed to get Direction from %s."), *Context, *(Outer->PrintNameClassAndOwner()));
		}
	}
	// Bone
	if (DirectionType == EDirection::Bone)
	{
		checkf(0, TEXT("NOT IMPLEMENTED"));
	}
	// Component
	if (DirectionType == EDirection::Component)
	{
		checkf(LaunchComponentTransform, TEXT("%s: LaunchComponentTransform is NULL."));
		
		const FRotator Rotation = NCsRotationRules::GetRotation(LaunchComponentTransform, DirectionRules);

		const FVector Dir = Rotation.Vector();
		CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(LaunchParams, Dir));
		return Dir;
	}
	// Camera
	if (DirectionType == EDirection::Camera)
	{
		// Try to get camera through the owner
		if (UObject* TheOwner = Outer->GetMyOwner())
		{
			typedef NCsCamera::FLibrary CameraLibrary;

			const FVector Dir = CameraLibrary::GetDirectionChecked(Context, TheOwner);
			CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(LaunchParams, Dir));
			return Dir;
		}
		checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *(Outer->PrintNameAndClass()));
	}
	// ITrace | Get Launch Trace Params
	if (DirectionType == EDirection::Trace)
	{
		using namespace NCsWeapon::NProjectile::NParams::NLaunch::NTrace;

		const ITrace* LaunchTraceParams = FLibrary::GetInterfaceChecked<ITrace>(Context, LaunchParams);
		
		// Start
		const ETraceStart& TraceStart = LaunchTraceParams->GetTraceStartType();

		FVector Start = FVector::ZeroVector;

		// LaunchLocation
		if (TraceStart == ETraceStart::LaunchLocation)
		{
			Start = GetLaunchLocation();
		}
		// Owner
		else
		if (TraceStart == ETraceStart::Owner)
		{
			checkf(0, TEXT("NOT IMPLEMENTED"));
		}
		// Bone
		else
		if (TraceStart == ETraceStart::Bone)
		{
			checkf(0, TEXT("NOT IMPLEMENTED"));
		}
		// Component
		else
		if (TraceStart == ETraceStart::Component)
		{
			checkf(LaunchComponentTransform, TEXT("%s: LaunchComponentTransform is NULL."));

			Start = LaunchComponentTransform->GetComponentLocation();
		}
		// Camera
		else
		if (TraceStart == ETraceStart::Camera)
		{
			// Try to get camera through the owner
			if (UObject* TheOwner = Outer->GetMyOwner())
			{
				typedef NCsCamera::FLibrary CameraLibrary;

				Start = CameraLibrary::GetLocationChecked(Context, TheOwner);
			}
			// TODO: For now assert
			else
			{
				checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *(Outer->PrintNameAndClass()));
			}
		}

		// Direction
		const ETraceDirection& TraceDirection  = LaunchTraceParams->GetTraceDirectionType();

		FVector Dir = FVector::ZeroVector;

		// Owner
		if (TraceDirection == ETraceDirection::Owner)
		{
			checkf(0, TEXT("NOT IMPLEMENTED"));
		}
		// Bone
		else
		if (TraceDirection == ETraceDirection::Bone)
		{
			checkf(0, TEXT("NOT IMPLEMENTED"));
		}
		// Component
		else
		if (TraceDirection == ETraceDirection::Component)
		{
			checkf(LaunchComponentTransform, TEXT("%s: LaunchComponentTransform is NULL."));

			const FRotator Rotation = NCsRotationRules::GetRotation(LaunchComponentTransform->GetComponentRotation(), DirectionRules);

			Dir = Rotation.Vector();
		}
		else
		// Camera
		if (TraceDirection == ETraceDirection::Camera)
		{
			// Try to get camera through the owner
			if (UObject* TheOwner = Outer->GetMyOwner())
			{
				typedef NCsCamera::FLibrary CameraLibrary;

				Dir = CameraLibrary::GetDirectionChecked(Context, TheOwner, DirectionRules);
			}
			// TODO: For now assert
			else
			{
				checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *(Outer->PrintNameAndClass()));
			}
		}

		const float& Distance = LaunchTraceParams->GetTraceDistance();

		const FVector End = Start + Distance * Dir;

		// Perform Trace
		typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;
		typedef NCsTrace::NRequest::FRequest RequestType;

		UCsManager_Trace* Manager_Trace = TraceManagerLibrary::GetChecked(Context, Outer);

		RequestType* Request = Manager_Trace->AllocateRequest();
		Request->Start		 = Start;
		Request->End		 = End;

		// Get collision information related to the projectile to be used in the trace.

		typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;
		typedef NCsProjectile::NData::FLibrary PrjDataLibrary;
		typedef NCsProjectile::NData::IData PrjDataType;
		typedef NCsProjectile::NData::NCollision::ICollision PrjCollisionDataType;

		PrjDataType* PrjData				   = PrjManagerLibrary::GetChecked(Context, Outer)->GetDataChecked(Context, Outer->GetProjectileType());
		PrjCollisionDataType* PrjCollisionData = PrjDataLibrary::GetInterfaceChecked<PrjCollisionDataType>(Context, PrjData);

		const FCsCollisionPreset& CollisionPreset		 = PrjCollisionData->GetCollisionPreset();
		const TEnumAsByte<ECollisionChannel>& ObjectType = CollisionPreset.ObjectType;

		Request->ObjectParams.AddObjectTypesToQuery(ObjectType);

		Request->Type = LaunchTraceParams->GetTraceType();

		if (Request->Type == ECsTraceType::Sweep)
		{
			//Request->Shape = 
		}
		
		typedef NCsTrace::NResponse::FResponse ResponseType;

		ResponseType* Response = Manager_Trace->Trace(Request);

		FVector LookAtLocation = FVector::ZeroVector;

		if (Response &&
			Response->bResult)
		{
			LookAtLocation = Start + Response->OutHits[CS_FIRST].Distance * Dir;
		}
		else
		{
			LookAtLocation = Start + Distance * Dir;
		}

		const FVector LaunchLocation  = GetLaunchLocation();
		const FVector LaunchDirection = (LookAtLocation - LaunchLocation).GetSafeNormal();

		// Check the direction is in FRONT of the Start. The trace could produce a result BEHIND the start

		if (Start == LaunchDirection ||
			FVector::DotProduct(Dir, LaunchDirection) > 0)
		{
			CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(LaunchParams, LaunchDirection));
			return LaunchDirection;
		}
		CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(LaunchParams, Dir));
		return Dir;
	}
	// Custom
	if (DirectionType == EDirection::Custom)
	{
		CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(LaunchParams, CustomLaunchDirection));
		return CustomLaunchDirection;
	}
	CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(LaunchParams, FVector::ZeroVector));
	return FVector::ZeroVector;
}

#define LaunchParamsType NCsWeapon::NProjectile::NParams::NLaunch::ILaunch
void ACsProjectileWeaponActorPooled::FProjectileImpl::Log_GetLaunchDirection(const LaunchParamsType* LaunchParams, const FVector& Direction)
{
#undef LaunchParamsType

	using namespace NCsWeapon::NProjectile::NParams::NLaunch;

	if (CS_CVAR_LOG_IS_SHOWING(LogWeaponProjectileLaunchDirection))
	{
		UE_LOG(LogCsWp, Warning, TEXT("ACsProjectileWeaponActorPooled::FProjectileImpl::GetLaunchDirection"));
		UE_LOG(LogCsWp, Warning, TEXT(" Weapon: %s"), *(Outer->GetName()));
		UE_LOG(LogCsWp, Warning, TEXT(" Class: %s"), *(Outer->GetClass()->GetName()));
		UE_LOG(LogCsWp, Warning, TEXT(" Owner: %s"), Outer->GetOwner() ? *(Outer->GetOwner()->GetName()) : TEXT("None"));

		const EDirection& DirectionType = LaunchParams->GetDirectionType();

		UE_LOG(LogCsWp, Warning, TEXT(" DirectionType: %s"), EMDirection::Get().ToChar(DirectionType));
		UE_LOG(LogCsWp, Warning, TEXT(" Direction: %s"), *(Direction.ToString()));
	}
}

void ACsProjectileWeaponActorPooled::FProjectileImpl::Launch()
{
	CS_SCOPED_TIMER(LaunchScopedHandle);

	using namespace NCsProjectileWeaponActorPooled::NCached::NProjectileImpl;

	const FString& Context = Str::Launch;

	typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;
	typedef NCsProjectile::NPayload::IPayload PayloadType;

	UCsManager_Projectile* Manager_Projectile = PrjManagerLibrary::GetChecked(Context, Outer);

	// Get Payload
	const FECsProjectile& PrjType = Outer->GetProjectileType();

	PayloadType* Payload1 = Manager_Projectile->AllocatePayload(PrjType);

	// Set appropriate members on Payload
	const bool SetSuccess = SetPayload(Context, Payload1);

	checkf(SetSuccess, TEXT("%s: Failed to set Payload1."), *Context);

	// Cache copy of Payload for Launch
	PayloadType* Payload2 = Manager_Projectile->AllocatePayload(PrjType);

	const bool CopySuccess = CopyPayload(Context, Payload1, Payload2);

	checkf(CopySuccess, TEXT("%s: Failed to copy Payload1 to Payload2."), *Context);

	// Spawn
	const FCsProjectilePooled* ProjectilePooled = Manager_Projectile->Spawn(PrjType, Payload1);

	// Release payload so it returns to the pool
	typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;

	PooledPayloadType* ObjectPayload = NCsInterfaceMap::GetInterfaceChecked<PooledPayloadType>(Context, Payload2);
	ObjectPayload->Reset();
}

ACsProjectileWeaponActorPooled::FProjectileImpl* ACsProjectileWeaponActorPooled::ConstructProjectileImpl()
{
	return new ACsProjectileWeaponActorPooled::FProjectileImpl();
}

void ACsProjectileWeaponActorPooled::ProjectileImpl_SetLaunchComponentTransform(USceneComponent* Component)
{
	ProjectileImpl->SetLaunchComponentTransform(Component);
}

#define PrjModifierType NCsProjectile::NModifier::IModifier
void ACsProjectileWeaponActorPooled::GetProjectileModifiers(TArray<PrjModifierType*>& OutModifiers)
{
#undef PrjModifierType
}

#pragma endregion Projectile

	// Sound
#pragma region

void ACsProjectileWeaponActorPooled::FSoundImpl::Play()
{
	using namespace NCsProjectileWeaponActorPooled::NCached::NSoundImpl;

	const FString& Context = Str::Play;

	// SoundDataType (NCsWeapon::NProjectile::NData::NSound::NFire::IFire)
	typedef NCsWeapon::NProjectile::NData::NSound::NFire::IFire SoundDataType;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	if (SoundDataType* SoundData = WeaponDataLibrary::GetSafeInterfaceChecked<SoundDataType>(Context, Weapon->GetData()))
	{
		typedef NCsWeapon::NProjectile::NData::NSound::NFire::NParams::FImpl ParamsType;

		const ParamsType& Params = SoundData->GetFireSoundParams();
		const FCsSound& Sound	 = Params.GetSound();

		typedef NCsPooledObject::NPayload::FImplSlice PayloadImplType;

		PayloadImplType Payload;
		Payload.Instigator = Weapon;
		Payload.Owner = Weapon->GetMyOwner();

		typedef NCsSound::NManager::FLibrary SoundManagerLibrary;
		// TODO: Make sure Outer is defined
		SoundManagerLibrary::SpawnChecked(Context, Weapon, &Payload, Sound);
	}
}

ACsProjectileWeaponActorPooled::FSoundImpl* ACsProjectileWeaponActorPooled::ConstructSoundImpl()
{
	return new ACsProjectileWeaponActorPooled::FSoundImpl();
}

#pragma endregion Sound

	// FX
#pragma region

void ACsProjectileWeaponActorPooled::FFXImpl::Play()
{
	using namespace NCsProjectileWeaponActorPooled::NCached::NFXImpl;

	const FString& Context = Str::Play;

	// FXDataType (NCsWeapon::NProjectile::NData::NVisual::NFire::IFire)
	typedef NCsWeapon::NProjectile::NData::NVisual::NFire::IFire FXDataType;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	if (FXDataType* FXData = WeaponDataLibrary::GetSafeInterfaceChecked<FXDataType>(Context, Weapon->GetData()))
	{
		typedef NCsWeapon::NProjectile::NData::NVisual::NFire::FParams ParamsType;

		const ParamsType& Params = FXData->GetFireFXParams();
		const FCsFX& FX			 = Params.GetFX();

		UNiagaraSystem* FXAsset = FX.GetChecked(Context);

		// Get Manager
		UCsManager_FX_Actor* Manager_FX = UCsManager_FX_Actor::Get(Weapon->GetWorld()->GetGameState());
		// Allocate payload
		typedef NCsFX::NPayload::IPayload PayloadType;

		PayloadType* Payload = Manager_FX->AllocatePayload(FX.Type);
		// Set appropriate values on payload
		SetPayload(Payload, FX);
		SetPayload(Payload, FXData);

		Manager_FX->Spawn(FX.Type, Payload);
	}
}

#define FXPayloadType NCsFX::NPayload::IPayload
void ACsProjectileWeaponActorPooled::FFXImpl::SetPayload(FXPayloadType* Payload, const FCsFX& FX)
{
#undef FXPayloadType

	using namespace NCsProjectileWeaponActorPooled::NCached::NFXImpl;

	const FString& Context = Str::SetPayload;

	typedef NCsFX::NPayload::FImpl PayloadImplType;
	typedef NCsFX::NPayload::FLibrary PayloadLibrary;

	PayloadImplType* PayloadImpl = PayloadLibrary::PureStaticCastChecked<PayloadImplType>(Context, Payload);

	PayloadImpl->Instigator					= Weapon;
	PayloadImpl->Owner						= Weapon->GetMyOwner();
	PayloadImpl->FXSystem					= FX.GetChecked(Context);
	PayloadImpl->DeallocateMethod			= FX.GetDeallocateMethod();
	PayloadImpl->LifeTime					= FX.LifeTime;
	PayloadImpl->AttachmentTransformRules	= FX.AttachmentTransformRules;
	PayloadImpl->Bone						= FX.Bone;
	PayloadImpl->TransformRules				= FX.TransformRules;
	PayloadImpl->Transform					= FX.Transform;

	typedef NCsWeapon::NProjectile::NData::NVisual::NFire::IFire FXDataType;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	FXDataType* FXData = WeaponDataLibrary::GetInterfaceChecked<FXDataType>(Context, Weapon->GetData());

	typedef NCsWeapon::NProjectile::NData::NVisual::NFire::FParams ParamsType;

	const ParamsType& Params = FXData->GetFireFXParams();

	typedef NCsWeapon::NProjectile::NData::NVisual::NFire::EAttach AttachType;

	const AttachType& Type = Params.GetAttach();

	// None
	if (Type == AttachType::None)
	{
		// Do Nothing
	}
	// Owner
	else
	if (Type == AttachType::Owner)
	{
		PayloadImpl->Parent = Weapon->GetMyOwner();
	}
	// Component
	else
	if (Type == AttachType::Component)
	{
		PayloadImpl->Parent = Component;
	}
	// Custom
	else
	{
		checkf(0, TEXT("%s: AttachType::Custom is NOT implemented."));
	}
}

#define FXPayloadType NCsFX::NPayload::IPayload
#define FXDataType NCsWeapon::NProjectile::NData::NVisual::NFire::IFire
void ACsProjectileWeaponActorPooled::FFXImpl::SetPayload(FXPayloadType* Payload, FXDataType* FXData)
{
#undef FXPayloadType
#undef FXDataType

	using namespace NCsProjectileWeaponActorPooled::NCached::NFXImpl;

	const FString& Context = Str::SetPayload;

	typedef NCsWeapon::NProjectile::NData::NVisual::NFire::FParams ParamsType;

	const ParamsType& Params = FXData->GetFireFXParams();

	typedef NCsWeapon::NProjectile::NData::NVisual::NFire::EAttach AttachType;

	const AttachType& Type = Params.GetAttach();

	typedef NCsFX::NPayload::FImpl PayloadImplType;
	typedef NCsFX::NPayload::FLibrary PayloadLibrary;

	PayloadImplType* PayloadImpl = PayloadLibrary::PureStaticCastChecked<PayloadImplType>(Context, Payload);

	// None
	if (Type == AttachType::None)
	{
		// Do Nothing
	}
	// Owner
	else
	if (Type == AttachType::Owner)
	{
		PayloadImpl->Parent = Weapon->GetMyOwner();
	}
	// Component
	else
	if (Type == AttachType::Component)
	{
		PayloadImpl->Parent = Component;
	}
	// Custom
	else
	{
		checkf(0, TEXT("%s: AttachType::Custom is NOT implemented."));
	}
}

ACsProjectileWeaponActorPooled::FFXImpl* ACsProjectileWeaponActorPooled::ConstructFXImpl()
{
	return new ACsProjectileWeaponActorPooled::FFXImpl();
}

void ACsProjectileWeaponActorPooled::FXImpl_SetComponent(USceneComponent* Component)
{
	FXImpl->SetComponent(Component);
}

#pragma endregion FX

#pragma endregion Fire

void ACsProjectileWeaponActorPooled::ResetValuesToBase()
{
	TimeBetweenShotsImpl.ResetValueToBase();
}

// Print
#pragma region

FString ACsProjectileWeaponActorPooled::PrintNameAndClass()
{
	return FString::Printf(TEXT("Weapon: %s with Class: %s"), *(GetName()), *(GetClass()->GetName()));
}

FString ACsProjectileWeaponActorPooled::PrintNameClassAndOwner()
{
	return FString::Printf(TEXT("Weapon: %s with Class: %s with MyOwner: %s"), *(GetName()), *(GetClass()->GetName()), *(MyOwner->GetName()));
}

#pragma endregion Print