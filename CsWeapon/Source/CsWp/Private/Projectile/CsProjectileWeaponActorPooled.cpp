#include "Projectile/CsProjectileWeaponActorPooled.h"
#include "CsWp.h"

// CVar
#include "Projectile/CsCVars_ProjectileWeapon.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "Types/CsCached.h"
#include "Types/CsTypes_Math_Library.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Managers/Time/CsLibrary_Manager_Time.h"
#include "Managers/Trace/CsLibrary_Manager_Trace.h"
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"
#include "Managers/Sound/CsLibrary_Manager_Sound.h"
#include "Managers/FX/Actor/CsLibrary_Manager_FX.h"
	// Data
#include "Data/CsLibrary_Data_Weapon.h"
#include "Data/CsLibrary_Data_Projectile.h"
	// Payload
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
#include "Payload/CsLibrary_Payload_Projectile.h"
#include "Managers/Sound/Payload/CsLibrary_Payload_Sound.h"
#include "Managers/FX/Payload/CsLibrary_Payload_FX.h"
	// Modifier
#include "Modifier/CsLibrary_WeaponModifier.h"
	// Params
#include "Projectile/Params/Launch/CsLibrary_Params_ProjectileWeapon_Launch.h"
	// Common
#include "Camera/CsLibrary_Camera.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsWeaponSettings.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
#include "Managers/Projectile/CsManager_Projectile.h"
#include "Managers/Sound/CsManager_Sound.h"
#include "Managers/FX/Actor/CsManager_FX.h"
#include "Managers/Trace/CsManager_Trace.h"
// Data
#include "Data/CsData_Weapon.h"
#include "Projectile/Data/CsData_ProjectileWeapon.h"
#include "Projectile/Data/Sound/Fire/CsData_ProjectileWeapon_SoundFire.h"
#include "Projectile/Data/Visual/Fire/CsData_ProjectileWeapon_VisualFire.h"
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
#include "Modifier/Types/CsGetWeaponModifierType.h"
#include "Projectile/Params/Spread/CsProjectileWeapon_Spread_Variables.h"
// Projectile
	// Payload
#include "Payload/CsPayload_ProjectileImpl.h"
#include "Payload/CsPayload_ProjectileImplSlice.h"
		// Modifier
#include "Payload/Modifier/CsPayload_Projectile_ModifierImplSlice.h"
		// Target
#include "Payload/Target/CsPayload_Projectile_TargetImplSlice.h"
#include "CsProjectilePooledImpl.h"
// Modifier
#include "CsModifier_Int.h"
#include "CsModifier_Float.h"
#include "CsModifier_Toggle.h"
// Sound
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"
// FX
#include "Managers/FX/Payload/CsPayload_FXImpl.h"
// Params
#include "Projectile/Params/Launch/Trace/CsParams_ProjectileWeapon_LaunchTrace.h"
#include "Projectile/Data/Sound/Fire/CsParams_ProjectileWeapon_SoundFire.h"
// Component
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
// Animation
#include "Animation/AnimInstance.h"
// Interface
#include "Object/Orientation/CsObject_Orientation.h"

#if WITH_EDITOR
// Library
	// Common
#include "Library/CsLibrary_World.h"
#endif // #if WITH_EDITOR

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

			// AActor Interface
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, PostInitializeComponents);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, OnUpdate_HandleStates);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, CanFire);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, Fire);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, Fire_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, Fire_Internal_OnEnd);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, GetTimeBetweenShots);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, ProjectilesPerShot_GetCount);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, ProjectilesPerShot_GetInterval);

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, FireProjectile);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, SetProjectilePayload);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, LaunchProjectile);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsProjectileWeaponActorPooled, UseSpreadParams);
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
	// Shutdown
	bShutdown(false),
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
	OnFire_PreStart_Event(),
	OnFire_PreShot_Event(),
	FireIDs(),
	FireHandles(),
	FireScopedHandle(),
	// Projectile
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

	RootComponent = StaticMeshComponent;

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

	SkeletalMeshComponent->SetupAttachment(RootComponent);
}

// UObject Interface
#pragma region

void ACsProjectileWeaponActorPooled::BeginDestroy()
{
	Super::BeginDestroy();

	Shutdown();
}

#pragma endregion UObject Interface

// AActor Interface
#pragma region

void ACsProjectileWeaponActorPooled::BeginPlay()
{
	Super::BeginPlay();

	SkeletalMeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);

	ConstructCache();

	TimeBetweenShotsImpl.Outer = this;

	ProjectileImpl = ConstructProjectileImpl();
	ProjectileImpl->Outer = this;

	SoundImpl = ConstructSoundImpl();
	SoundImpl->Outer = this;

	FXImpl = ConstructFXImpl();
	FXImpl->Outer = this;

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

void ACsProjectileWeaponActorPooled::PostInitializeComponents()
{
	using namespace NCsProjectileWeaponActorPooled::NCached;

	const FString& Context = Str::PostInitializeComponents;

	Super::PostInitializeComponents();

#if WITH_EDITOR
	if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(this))
	{
		SkeletalMeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);

		ConstructCache();

		TimeBetweenShotsImpl.Outer = this;

		ProjectileImpl = ConstructProjectileImpl();
		ProjectileImpl->Outer = this;

		SoundImpl = ConstructSoundImpl();
		SoundImpl->Outer = this;

		FXImpl = ConstructFXImpl();
		FXImpl->Outer = this;

		// FireScopedHandle
		{
			const FString& ScopeName = Str::Fire_Internal;
			const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponProjectile;
			const FECsCVarLog& ScopeLog = NCsCVarLog::LogWeaponProjectileScopedTimerFire;

			FireScopedHandle.Handle = FCsManager_ScopedTimer::Get().GetHandle(&ScopeName, ScopedGroup, ScopeLog);
		}
		// LaunchScopedHandle
		{
			const FString& ScopeName = NProjectileImpl::Str::Launch;
			const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponProjectile;
			const FECsCVarLog& ScopeLog = NCsCVarLog::LogWeaponProjectileProjectileScopedTimerLaunch;

			ProjectileImpl->LaunchScopedHandle = FCsManager_ScopedTimer::Get().GetHandle(&ScopeName, ScopedGroup, ScopeLog);
		}
	}
#endif // #if WITH_EDITOR
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

// ICsShutdown
#pragma region

void ACsProjectileWeaponActorPooled::Shutdown()
{
	CS_SAFE_DELETE_PTR(Cache)
	CS_SILENT_CLEAR_SCOPED_TIMER_HANDLE(FireScopedHandle.Handle);

	if (ProjectileImpl)
	{
		CS_SILENT_CLEAR_SCOPED_TIMER_HANDLE(ProjectileImpl->LaunchScopedHandle);

		delete ProjectileImpl;
		ProjectileImpl = nullptr;
	}
	CS_SAFE_DELETE_PTR(SoundImpl)
	CS_SAFE_DELETE_PTR(FXImpl)

	bShutdown = true;
}

#pragma endregion ICsShutdown

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

	Data		  = WeaponManagerLibrary::GetDataChecked(Context, GetWorldContext(), WeaponType);
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

		const FTransform3f& Transform = WeaponPayload->GetTransform();

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
			typedef NCsMath::FLibrary MathLibrary;

			SetActorTransform(MathLibrary::Convert(Transform));
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
	ProjectileImpl->Reset();

	OnConsumeAmmo_Event.Clear();
	OnFire_PreStart_Event.Clear();
	OnFire_PreShot_Event.Clear();
	OnFire_End_Event.Clear();

	TimeBetweenShotsImpl.Clear();

	// End Routines
	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

	if (UCsCoroutineScheduler* Scheduler = CoroutineSchedulerLibrary::GetSafe(GetWorldContext()))
	{
		static TSet<FCsRoutineHandle> TempHandles;

		for (const FCsRoutineHandle& Handle : FireHandles)
		{
			TempHandles.Add(Handle);
		}

		for (const FCsRoutineHandle& Handle : TempHandles)
		{
			Scheduler->End(UpdateGroup, Handle);
		}
		TempHandles.Reset();
	}
	FireHandles.Reset();

	// Skin
	SetRootComponent(nullptr);

	StaticMeshComponent->SetComponentTickEnabled(false);
	StaticMeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	StaticMeshComponent->SetRelativeLocation(FVector3d::ZeroVector);
	StaticMeshComponent->SetHiddenInGame(true);
	StaticMeshComponent->ComponentTags.Reset(StaticMeshComponent->ComponentTags.Max());

	// TODO: FUTURE: Look into what can be preserved

	if (UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance())
		AnimInstance->StopAllMontages(0.0f);

	SkeletalMeshComponent->SetSkeletalMesh(nullptr);
	SkeletalMeshComponent->SetAnimInstanceClass(nullptr);
	SkeletalMeshComponent->SetComponentTickEnabled(false);
	SkeletalMeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	SkeletalMeshComponent->SetRelativeLocation(FVector3d::ZeroVector);
	SkeletalMeshComponent->SetHiddenInGame(false);
	SkeletalMeshComponent->ComponentTags.Reset(SkeletalMeshComponent->ComponentTags.Max());

	VisualMeshComponent = nullptr;

	WeaponType = EMCsWeapon::Get().GetMAX();

	Data = nullptr;
	PrjWeaponData = nullptr;

	ProjectileType = EMCsProjectile::Get().GetMAX();
	
	MyOwner = nullptr;
	MyOwnerAsActor = nullptr;

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

#if WITH_EDITOR

const UObject* ACsProjectileWeaponActorPooled::GetWorldContext() const
{
	if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(this))
	{
		if (MyOwnerAsActor)
		{
			return MyOwner;
		}
	}
	return this;
}

#endif // #if WITH_EDITOR

// State
#pragma region

void ACsProjectileWeaponActorPooled::OnUpdate_HandleStates(const FCsDeltaTime& DeltaTime)
{
	using namespace NCsProjectileWeaponActorPooled::NCached;

	const FString& Context = Str::OnUpdate_HandleStates;

	typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

	const FCsDeltaTime& TimeSinceStart = TimeManagerLibrary::GetTimeSinceStartChecked(Context, GetWorldContext(), UpdateGroup);

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

	const FCsDeltaTime& TimeSinceStart = TimeManagerLibrary::GetTimeSinceStartChecked(Context, GetWorldContext(), UpdateGroup);

	const float TimeBetweenShots = GetTimeBetweenShots();

	// Check if enough time has elapsed to fire again.
	const bool Pass_Time = !bHasFired || (TimeSinceStart.Time - Fire_StartTime > TimeBetweenShots);
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
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_Time (%s): %f - %f > %f"), ToChar(Pass_Time), TimeSinceStart.Time, Fire_StartTime, TimeBetweenShots);
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

	UCsCoroutineScheduler* Scheduler = CoroutineSchedulerLibrary::GetChecked(Context, GetWorldContext());

	typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

	const FCsDeltaTime& TimeSinceStart = TimeManagerLibrary::GetTimeSinceStartChecked(Context, GetWorldContext(), UpdateGroup);

	Fire_StartTime = TimeSinceStart.Time;

	// Setup Fire Routine
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

	#define COROUTINE Fire_Internal

	Payload->CoroutineImpl.BindUObject(this, &ACsProjectileWeaponActorPooled::COROUTINE);
	Payload->StartTime = TimeManagerLibrary::GetTimeChecked(Context, GetWorldContext(), UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);
	Payload->OnEnds.AddDefaulted();
	Payload->OnEnds.Last().BindUObject(this, &ACsProjectileWeaponActorPooled::Fire_Internal_OnEnd);
	Payload->AbortMessages.Add(Name::Abort_Fire_Internal);

	#undef COROUTINE

	const FGuid FireGuid = FGuid::NewGuid();
	uint32 FireID		 = GetTypeHash(FireGuid);

	FireIDs.Add(FireID);

	static const int32 FIRE_ID = 0;
	Payload->SetValue_UnsignedInt(FIRE_ID, FireID);

	Fire_PreStart(FireID);
	OnFire_PreStart_Event.Broadcast(this, FireID);

	Payload->SetValue_Flag(CS_FIRST, PrjWeaponData->HasInfiniteAmmo());

	// ProjectilePerShot
	static const int32 PROJECTILES_PER_SHOT = 0;
	int32 ProjectilesPerShot = ProjectilesPerShot_GetCount();
	Payload->SetValue_Int(PROJECTILES_PER_SHOT, ProjectilesPerShot);

	static const int32 PROJECTILES_PER_SHOT_INTERVAL = 0;
	Payload->SetValue_Float(PROJECTILES_PER_SHOT_INTERVAL, ProjectilesPerShot_GetInterval());

		// Cache Launch Location
	const bool UseCachedLaunchLocation = !PrjWeaponData->GetProjectilesPerShotParams().GetbCurrentLaunchLocation();
	static const int32 USE_CACHED_LAUNCH_LOCATION = 0;
	Payload->SetValue_Flag(USE_CACHED_LAUNCH_LOCATION, UseCachedLaunchLocation);

	if (UseCachedLaunchLocation)
	{
		static const int32 CACHED_LAUNCH_LOCATION = 0;
		Payload->SetValue_Vector(CACHED_LAUNCH_LOCATION, ProjectileImpl->GetLaunchLocation());
	}
		// Cache Launch Direction
	const bool UseCachedLaunchDirection = !PrjWeaponData->GetProjectilesPerShotParams().GetbCurrentLaunchDirection();
	static const int32 USE_CACHED_LAUNCH_DIRECTION = 1;
	Payload->SetValue_Flag(USE_CACHED_LAUNCH_DIRECTION, UseCachedLaunchDirection);

	if (UseCachedLaunchDirection)
	{
		static const int32 CACHED_LAUNCH_DIRECTION = 1;
		Payload->SetValue_Vector(CACHED_LAUNCH_DIRECTION, ProjectileImpl->GetLaunchDirection());
	}

	// Spread
	static const int32 SPREAD_SHAPE_RANDOM = 2;
	Payload->SetValue_Flag(SPREAD_SHAPE_RANDOM, false);
	static const int32 SPREAD_YAW_RANDOM = 3;
	Payload->SetValue_Flag(SPREAD_YAW_RANDOM, false);
	static const int32 SPREAD_PITCH_RANDOM = 4;
	Payload->SetValue_Flag(SPREAD_PITCH_RANDOM, false);

	if (UseSpreadParams())
	{
		typedef NCsWeapon::NProjectile::NSpread::FParams SpreadParamsType;

		const SpreadParamsType& SpreadParams = PrjWeaponData->GetSpreadParams();

		CS_IS_VALID_CHECKED(SpreadParams);

		typedef NCsWeapon::NProjectile::NSpread::NAngle::FParams SpreadAngleParamsType;
		typedef NCsWeapon::NProjectile::NSpread::NVariables::FResource SpreadVariablesResourceType;
		typedef NCsWeapon::NProjectile::NSpread::NVariables::FVariables SpreadVariablesType;

		SpreadVariablesResourceType* Resource = nullptr;

		// Shape
		if (SpreadParams.GetbShape())
		{
			typedef NCsWeapon::NProjectile::NSpread::NShape::FParams SpreadShapeParamsType;

			const SpreadShapeParamsType& ShapeParams = SpreadParams.GetShapeParams();

			if (ShapeParams.ShouldPrecalculate())
			{
				// TODO:
			}
			else
			{
				Payload->SetValue_Flag(SPREAD_SHAPE_RANDOM, true);
			}
		}
		// Yaw
		if (SpreadParams.GetbYaw())
		{
			const SpreadAngleParamsType& YawParams = SpreadParams.GetYawParams();

			if (YawParams.ShouldPrecalculate())
			{
				typedef NCsWeapon::NManager::NSpread::NVariables::FLibrary VariablesLibrary;
				
				Resource					   = VariablesLibrary::Allocate(Context, GetWorldContext());
				SpreadVariablesType* Variables = Resource->Get();

				Variables->SetSizeAndAddDefaulted(ProjectilesPerShot);
				YawParams.SetAnglesChecked(Context, ProjectilesPerShot, Variables->Yaws);
			}
			else
			{
				Payload->SetValue_Flag(SPREAD_YAW_RANDOM, true);
			}
		}
		// Pitch
		if (SpreadParams.GetbPitch())
		{
			const SpreadAngleParamsType& PitchParams = SpreadParams.GetPitchParams();

			if (PitchParams.ShouldPrecalculate())
			{
				typedef NCsWeapon::NManager::NSpread::NVariables::FLibrary VariablesLibrary;
				
				if (!Resource)
				{
					Resource = VariablesLibrary::Allocate(Context, GetWorldContext());
				}
				SpreadVariablesType* Variables = Resource->Get();

				Variables->SetSizeAndAddDefaulted(ProjectilesPerShot);
				PitchParams.SetAnglesChecked(Context, ProjectilesPerShot, Variables->Pitches);
			}
			else
			{
				Payload->SetValue_Flag(SPREAD_PITCH_RANDOM, true);
			}
		}

		if (Resource)
		{
			static const int32 SPREAD_VARIABLES = 0;
			Payload->SetValue_Void(SPREAD_VARIABLES, Resource);
		}
	}

	bHasFired = true;

	static const int32 START = -1;

	SoundImpl->Play(START);

	typedef ACsProjectileWeaponActorPooled::FProjectileImpl::FLaunchPayload LaunchPayloadType;

	LaunchPayloadType LaunchPayload;

	FXImpl->Play(START, LaunchPayload);

	FCsRoutineHandle Handle = Scheduler->Start(Payload);

	if (Handle.IsValid())
		FireHandles.Add(Handle);
}

void ACsProjectileWeaponActorPooled::Fire_PreStart(const uint32& FireID)
{
}

char ACsProjectileWeaponActorPooled::Fire_Internal(FCsRoutine* R)
{
	using namespace NCsProjectileWeaponActorPooled::NCached;

	const FString& Context = Str::Fire_Internal;

	static const int32 FIRE_ID = 0;
	const uint32& FireID = R->GetValue_UnsignedInt(FIRE_ID);

	// bInfiniteAmmo
	const bool& bInfiniteAmmo = R->GetValue_Flag(CS_FIRST);
	// ProjectilesPerShot
	static const int32 PROJECTILES_PER_SHOT = 0;
	const int32& ProjectilesPerShot			= R->GetValue_Int(PROJECTILES_PER_SHOT);
		// ProjectilesPerShot.Interval
	static const int32 PROJECTILES_PER_SHOT_INTERVAL = 0;
	const float& ProjectilesPerShot_Interval = R->GetValue_Float(PROJECTILES_PER_SHOT_INTERVAL);

	static const int32 CURRENT_PROJECTIVE_PER_SHOT_INDEX = 1;
	int32& CurrentProjectilePerShotIndex = R->GetValue_Int(CURRENT_PROJECTIVE_PER_SHOT_INDEX);
		// bLaunchLocation
	static const int32 USE_CACHED_LAUNCH_LOCATION = 0;
	const bool& UseCachedLaunchLocation = R->GetValue_Flag(USE_CACHED_LAUNCH_LOCATION);
	static const int32 CACHED_LAUNCH_LOCATION = 0;
	const FVector3f& CachedLaunchLocation = R->GetValue_Vector(CACHED_LAUNCH_LOCATION);
		// bLaunchDirection
	static const int32 USE_CACHED_LAUNCH_DIRECTION = 1;
	const bool& UseCachedLaunchDirection = R->GetValue_Flag(USE_CACHED_LAUNCH_DIRECTION);
	static const int32 CACHED_LAUNCH_DIRECTION = 1;
	const FVector3f& CachedLaunchDirection = R->GetValue_Vector(CACHED_LAUNCH_DIRECTION);

	// Spread
	typedef NCsWeapon::NProjectile::NSpread::NVariables::FResource SpreadVariablesResourceType;
	typedef NCsWeapon::NProjectile::NSpread::NVariables::FVariables SpreadVariablesType;

	static const int32 SPREAD_VARIABLES_RESOURCE = 0;
	SpreadVariablesResourceType* SpreadVariablesResource = R->GetValue_Void<SpreadVariablesResourceType>(SPREAD_VARIABLES_RESOURCE);
	SpreadVariablesType* SpreadVariables				 = SpreadVariablesResource ? SpreadVariablesResource->Get() : nullptr;

	static const int32 SPREAD_INDEX = 2;
	int32& SpreadIndex = R->GetValue_Int(SPREAD_INDEX);
		// Shape
	static const int32 SPREAD_SHAPE_RANDOM = 2;
	const bool& IsSpreadShapeRandom = R->GetValue_Flag(SPREAD_SHAPE_RANDOM);
		// Yaw
	static const int32 SPREAD_YAW_RANDOM = 3;
	const bool& IsSpreadYawRandom = R->GetValue_Flag(SPREAD_YAW_RANDOM);
		// Pitch
	static const int32 SPREAD_PITCH_RANDOM = 4;
	const bool& IsSpreadPitchRandom = R->GetValue_Flag(SPREAD_PITCH_RANDOM);

	FCsDeltaTime& ElapsedTime = R->GetValue_DeltaTime(CS_FIRST);

	ElapsedTime += R->GetDeltaTime();
	
	CS_COROUTINE_BEGIN(R);

	++FireCount;

	do 
	{
		{
			CS_SET_SCOPED_TIMER_HANDLE(FireScopedHandle);

			ElapsedTime.Reset();

			Fire_PreShot(FireID);
			OnFire_PreShot_Event.Broadcast(this, FireID, CurrentProjectilePerShotIndex);

			if (!bInfiniteAmmo)
				ConsumeAmmo();

			{
				typedef ACsProjectileWeaponActorPooled::FProjectileImpl::FLaunchPayload LaunchPayloadType;

				LaunchPayloadType LaunchPayload;

				// ProjectilesPerShot

				if (UseCachedLaunchLocation)
				{
					LaunchPayload.Shot.SetCachedLaunchLocation(CachedLaunchLocation);
				}

				if (UseCachedLaunchDirection)
				{
					LaunchPayload.Shot.SetCachedLaunchDirection(CachedLaunchDirection);
				}

				// Spread
				if (SpreadVariables)
				{
					LaunchPayload.bSpread = true;
					LaunchPayload.Spread.SetOffset(SpreadVariables->Offsets[SpreadIndex]);
					LaunchPayload.Spread.SetYaw(SpreadVariables->Yaws[SpreadIndex]);
					LaunchPayload.Spread.SetPitch(SpreadVariables->Pitches[SpreadIndex]);
				}
					// Shape
				if (IsSpreadShapeRandom)
				{
					typedef NCsWeapon::NProjectile::NSpread::FParams SpreadParamsType;

					LaunchPayload.bSpread = true;

					const SpreadParamsType& SpreadParams = PrjWeaponData->GetSpreadParams();

					LaunchPayload.Spread.SetOffset(SpreadParams.GetShapeParams().GetRandomOffsetChecked(Context));
					LaunchPayload.Spread.Axis = (int32)SpreadParams.GetShapeParams().GetAxis();
				}
					// Yaw
				if (IsSpreadYawRandom)
				{
					typedef NCsWeapon::NProjectile::NSpread::FParams SpreadParamsType;

					LaunchPayload.bSpread = true;

					const SpreadParamsType& SpreadParams = PrjWeaponData->GetSpreadParams();

					LaunchPayload.Spread.SetYaw(SpreadParams.GetYawParams().GetRandomAngleChecked(Context));
				}
					// Pitch
				if (IsSpreadPitchRandom)
				{
					typedef NCsWeapon::NProjectile::NSpread::FParams SpreadParamsType;

					LaunchPayload.bSpread = true;

					const SpreadParamsType& SpreadParams = PrjWeaponData->GetSpreadParams();

					LaunchPayload.Spread.SetPitch(SpreadParams.GetPitchParams().GetRandomAngleChecked(Context));
				}

				ProjectileImpl->Launch(LaunchPayload);
				SoundImpl->Play(CurrentProjectilePerShotIndex);
				FXImpl->Play(CurrentProjectilePerShotIndex, LaunchPayload);
			}

			// Increment the shot index
			CurrentProjectilePerShotIndex = FMath::Min(CurrentProjectilePerShotIndex + 1, ProjectilesPerShot);

			++SpreadIndex;

			// Check if more projectiles should be fired, if so wait
			if (CurrentProjectilePerShotIndex < ProjectilesPerShot)
			{
				CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= ProjectilesPerShot_Interval);
			}

			CS_UPDATE_SCOPED_TIMER_HANDLE(FireScopedHandle);
		}
	} while (CurrentProjectilePerShotIndex < ProjectilesPerShot);

	CS_COROUTINE_END(R);
}

void ACsProjectileWeaponActorPooled::Fire_PreShot(const uint32& FireID)
{
}

void ACsProjectileWeaponActorPooled::Fire_Internal_OnEnd(FCsRoutine* R)
{
	using namespace NCsProjectileWeaponActorPooled::NCached;

	const FString& Context = Str::Fire_Internal_OnEnd;

	if (R->GetSafeOwnerAsObject())
	{
		OnFire_End_Event.Broadcast(this, R);

		typedef NCsWeapon::NProjectile::NSpread::NVariables::FResource SpreadVariablesResourceType;

		static const int32 SPREAD_VARIABLES_RESOURCE = 0;
		SpreadVariablesResourceType* SpreadVariablesResource = R->GetValue_Void<SpreadVariablesResourceType>(SPREAD_VARIABLES_RESOURCE);

		if (SpreadVariablesResource)
		{
			typedef NCsWeapon::NManager::NSpread::NVariables::FLibrary VariablesLibrary;

			VariablesLibrary::Deallocate(Context, GetWorldContext(), SpreadVariablesResource);
		}
		FireHandles.Remove(R->GetHandle());

		static const int32 FIRE_ID = 0;
		const uint32& FireID = R->GetValue_UnsignedInt(FIRE_ID);

		FireIDs.Remove(FireID);
		--FireCount;
	}
}

void ACsProjectileWeaponActorPooled::FTimeBetweenShotsImpl::OnElapsedTime()
{
	using namespace NCsProjectileWeaponActorPooled::NCached::NTimeBetweenShotsImpl;

	const FString& Context = Str::OnElapsedTime;

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

	UCsCoroutineScheduler* Scheduler = CoroutineSchedulerLibrary::GetChecked(Context, Outer->GetWorldContext());

	// Setup Routine
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(Outer->GetUpdateGroup());

	#define COROUTINE OnElapsedTime_Internal

	typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

	Payload->CoroutineImpl.BindRaw(this, &ACsProjectileWeaponActorPooled::FTimeBetweenShotsImpl::COROUTINE);
	Payload->StartTime = TimeManagerLibrary::GetTimeChecked(Context, Outer->GetWorldContext(), Outer->GetUpdateGroup());
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

	ElapsedTime += R->GetDeltaTime();

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

float ACsProjectileWeaponActorPooled::GetTimeBetweenShots() const
{ 
	using namespace NCsProjectileWeaponActorPooled::NCached;

	const FString& Context = Str::GetTimeBetweenShots;

	typedef NCsWeapon::NModifier::IModifier ModifierType;

	static TArray<ModifierType*> Modifiers;
	Modifiers.Reset(Modifiers.Max());

	GetWeaponModifiers(Modifiers);

	float Value = TimeBetweenShotsImpl.GetValue();

	// TODO: Priority

	typedef NCsWeapon::NModifier::FLibrary ModifierLibrary;

	return ModifierLibrary::ModifyFloatChecked(Context, Modifiers, NCsWeaponModifier::PrjWp_TimeBetweenShots, Value);
}

	// Projectile
#pragma region

int32 ACsProjectileWeaponActorPooled::ProjectilesPerShot_GetCount() const
{
	using namespace NCsProjectileWeaponActorPooled::NCached;

	const FString& Context = Str::ProjectilesPerShot_GetCount;

	typedef NCsWeapon::NModifier::IModifier ModifierType;

	static TArray<ModifierType*> Modifiers;
	Modifiers.Reset(Modifiers.Max());

	GetWeaponModifiers(Modifiers);

	float Value = PrjWeaponData->GetProjectilesPerShotParams().GetCount();

	// TODO: Priority

	typedef NCsWeapon::NModifier::FLibrary ModifierLibrary;

	return ModifierLibrary::ModifyIntChecked(Context, Modifiers, NCsWeaponModifier::PrjWp_ProjectilesPerShot_Count, Value);
}

float ACsProjectileWeaponActorPooled::ProjectilesPerShot_GetInterval() const
{
	using namespace NCsProjectileWeaponActorPooled::NCached;

	const FString& Context = Str::ProjectilesPerShot_GetInterval;

	typedef NCsWeapon::NModifier::IModifier ModifierType;

	static TArray<ModifierType*> Modifiers;
	Modifiers.Reset(Modifiers.Max());

	GetWeaponModifiers(Modifiers);

	float Value = PrjWeaponData->GetProjectilesPerShotParams().GetInterval();

	// TODO: Priority

	typedef NCsWeapon::NModifier::FLibrary ModifierLibrary;

	return ModifierLibrary::ModifyFloatChecked(Context, Modifiers, NCsWeaponModifier::PrjWp_ProjectilesPerShot_Interval, Value);
}

#define ProjectilePayloadType NCsProjectile::NPayload::IPayload
#define LaunchPayloadType ACsProjectileWeaponActorPooled::FProjectileImpl::FLaunchPayload

bool ACsProjectileWeaponActorPooled::FProjectileImpl::SetPayload(const FString& Context, ProjectilePayloadType* Payload, const LaunchPayloadType& LaunchPayload)
{
	bool Result = true;

	// PooledObject
	{
		typedef NCsPooledObject::NPayload::FImplSlice SliceType;
		typedef NCsPooledObject::NPayload::IPayload SliceInterfaceType;

		SliceType* Slice = CsPrjPayloadLibrary::StaticCastChecked<SliceType, SliceInterfaceType>(Context, Payload);
		Slice->Instigator = Outer->GetMyOwner();
		Slice->Owner	  = Outer;
	}
	// Projectile
	{
		typedef NCsProjectile::NPayload::FImplSlice SliceType;
		typedef NCsProjectile::NPayload::IPayload SliceInterfaceType;

		SliceType* Slice = CsPrjPayloadLibrary::StaticCastChecked<SliceType, SliceInterfaceType>(Context, Payload);
		Slice->Type		 = Outer->GetProjectileType();
		Slice->Location  = GetLaunchLocation(LaunchPayload);
		Slice->Direction = GetLaunchDirection(LaunchPayload);
	}
	// Projectile Modifiers
	{
		typedef NCsProjectile::NPayload::NModifier::FImplSlice SliceType;
		typedef NCsProjectile::NPayload::NModifier::IModifier SliceInterfaceType;

		if (SliceType* Slice = CsPrjPayloadLibrary::SafeStaticCastChecked<SliceType, SliceInterfaceType>(Context, Payload))
		{
			typedef NCsProjectile::NModifier::IModifier PrjModifierType;

			static TArray<PrjModifierType*> Modifiers;
			
			Outer->GetProjectileModifiers(Modifiers);
			Slice->CopyAndEmptyFromModifiers(Outer, Modifiers);
		}
	}
	// Projectile Target
	{
		typedef NCsProjectile::NPayload::NTarget::FImplSlice SliceType;
		typedef NCsProjectile::NPayload::NTarget::ITarget SliceInterfaceType;

		if (SliceType* Slice = CsPrjPayloadLibrary::SafeStaticCastChecked<SliceType, SliceInterfaceType>(Context, Payload))
		{
			Slice->bTarget	= bTarget;
			Slice->Component = TargetComponent;
			Slice->Location = TargetLocation;
			Slice->Bone		= TargetBone;
			Slice->ID		= TargetID;
		}
	}
	return Outer->Projectile_SetPayload(Context, Payload, LaunchPayload);
}

#undef ProjectilePayloadType

FVector3f ACsProjectileWeaponActorPooled::FProjectileImpl::GetLaunchLocation(const LaunchPayloadType& LaunchPayload)
{
	using namespace NCsProjectileWeaponActorPooled::NCached::NProjectileImpl;

	const FString& ScopeName		   = Str::GetLaunchLocation;
	const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponProjectile;
	const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponProjectileScopedTimerGetLaunchLocation;

	CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

	const FString& Context = Str::GetLaunchLocation;
	
	if (LaunchPayload.Shot.UseCachedLaunchLocation())
		return GetLaunchSpreadLocation(LaunchPayload.Shot.CachedLaunchLocation, LaunchPayload);

	// Get Launch Params
	typedef NCsWeapon::NProjectile::NParams::NLaunch::FLibrary ParamsLibrary;
	typedef NCsWeapon::NProjectile::NParams::NLaunch::ILaunch LaunchParamsType;
	typedef NCsWeapon::NProjectile::NParams::NLaunch::ELocation LaunchLocationType;
	typedef NCsWeapon::NProjectile::NParams::NLaunch::NLocation::EOffsetSpace LaunchLocationOffsetSpace;
	typedef NCsWeapon::NProjectile::NParams::NLaunch::EDirection LaunchDirectionType;

	const LaunchParamsType* LaunchParams = ParamsLibrary::GetChecked(Context, Outer->GetData());

	const LaunchLocationType& LocationType				 = LaunchParams->GetLocationType();
	const LaunchLocationOffsetSpace& LocationOffsetSpace = LaunchParams->GetLocationOffsetSpace();
	const int32& LocationOffsetSpaceRules				 = LaunchParams->GetLocationOffsetSpaceRules();
	const int32 InvLocationOffsetSpaceRules				 = ~LocationOffsetSpaceRules & ((int32)NCsRotationRules::All);
	const FRotator3f& LocationOffsetSpaceOffset			 = LaunchParams->GetLocationOffsetSpaceOffset();
	const FVector3f& LocationOffset						 = LaunchParams->GetLocationOffset();

	typedef NCsMath::FLibrary MathLibrary;

	// Determine Offset
	FVector3f Offset = LocationOffset * NCsRotationRules::GetDirection(FVector3f::OneVector, InvLocationOffsetSpaceRules);
	{
		// None
		if (LocationOffsetSpace == LaunchLocationOffsetSpace::None)
		{
			Offset = LocationOffset;
		}
		// Owner
		else
		if (LocationOffsetSpace == LaunchLocationOffsetSpace::Owner)
		{
			UObject* TheOwner = Outer->GetMyOwner();

			checkf(TheOwner, TEXT("%s: No Owner found for %s."), *Context, *(Outer->PrintNameAndClass()));

			bool IsValidOwner = false;

			FRotator3f Rotation = FRotator3f::ZeroRotator;

			// CsObject_Orientation
			if (ICsObject_Orientation* Object_Movement = Cast<ICsObject_Orientation>(TheOwner))
			{
				Rotation	 = NCsRotationRules::GetRotation(Object_Movement->Orientation_GetRotation3f(), LocationOffsetSpaceRules);
				IsValidOwner = true;
			}
			// AActor
			else
			if (AActor* Actor = Cast<AActor>(TheOwner))
			{
				Rotation	 = NCsRotationRules::GetRotation(Actor, LocationOffsetSpaceRules);
				IsValidOwner = true;
			}
			// USceneComponent
			else
			if (USceneComponent* Component = Cast<USceneComponent>(TheOwner))
			{
				Rotation	  = NCsRotationRules::GetRotation(Component, LocationOffsetSpaceRules);
				IsValidOwner  = true;
			}

			if (IsValidOwner)
			{
				FVector3f Dir	= Rotation.Vector();

				const FRotator3f RotationOffset = NCsRotationRules::GetRotation(LocationOffsetSpaceOffset, LocationOffsetSpaceRules);

				Dir = Dir.RotateAngleAxis(RotationOffset.Pitch, MathLibrary::GetRightFromNormal(Dir));
				Dir = Dir.RotateAngleAxis(RotationOffset.Yaw, FVector3f::UpVector);
				
				FVector3f Right, Up;
				MathLibrary::GetRightAndUpFromNormal(Dir, Right, Up);

				Offset += LocationOffset.X * Dir + LocationOffset.Y * Right + LocationOffset.Z * Up;
			}
			else
			{
				checkf(0, TEXT("%s: Failed to get Location from %s."), *Context, *(Outer->PrintNameClassAndOwner()));
			}
		}
		// Bone
		else
		if (LocationOffsetSpace == LaunchLocationOffsetSpace::Owner)
		{
			checkf(0, TEXT("NOT IMPLEMENTED"));
		}
		// Component
		else
		if (LocationOffsetSpace == LaunchLocationOffsetSpace::Component)
		{
			CS_IS_PTR_NULL_CHECKED(LaunchComponentDirection)

			const FRotator3f Rotation = NCsRotationRules::GetRotation(LaunchComponentDirection, LocationOffsetSpaceRules);
			FVector3f Dir				= Rotation.Vector();

			const FRotator3f RotationOffset = NCsRotationRules::GetRotation(LocationOffsetSpaceOffset, LocationOffsetSpaceRules);

			Dir = Dir.RotateAngleAxis(RotationOffset.Pitch, MathLibrary::GetRightFromNormal(Dir));
			Dir = Dir.RotateAngleAxis(RotationOffset.Yaw, FVector3f::UpVector);

			FVector3f Right, Up;
			MathLibrary::GetRightAndUpFromNormal(Dir, Right, Up);

			Offset += LocationOffset.X * Dir + LocationOffset.Y * Right + LocationOffset.Z * Up;
		}
		// Camera
		else
		if (LocationOffsetSpace == LaunchLocationOffsetSpace::Camera)
		{
			// Try to get camera through the owner
			if (UObject* TheOwner = Outer->GetMyOwner())
			{
				typedef NCsCamera::FLibrary CameraLibrary;

				FVector3f Dir	= CameraLibrary::GetDirectionChecked(Context, Outer, LocationOffsetSpaceRules);

				const FRotator3f RotationOffset = NCsRotationRules::GetRotation(LocationOffsetSpaceOffset, LocationOffsetSpaceRules);

				Dir = Dir.RotateAngleAxis(RotationOffset.Pitch, MathLibrary::GetRightFromNormal(Dir));
				Dir = Dir.RotateAngleAxis(RotationOffset.Yaw, FVector3f::UpVector);

				FVector3f Right, Up;
				MathLibrary::GetRightAndUpFromNormal(Dir, Right, Up);

				Offset += LocationOffset.X * Dir + LocationOffset.Y * Right + LocationOffset.Z * Up;
			}
			else
			{
				checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *(Outer->PrintNameAndClass()));
			}
		}
		// Custom
		else
		if (LocationOffsetSpace == LaunchLocationOffsetSpace::Custom)
		{
			checkf(0, TEXT("NOT IMPLEMENTED"));
		}
	}

	// TODO: Have "Apply Spread" for other Location Types
	
	// Owner
	if (LocationType == LaunchLocationType::Owner)
	{
		UObject* TheOwner = Outer->GetMyOwner();

		checkf(TheOwner, TEXT("%s: No Owner found for %s."), *Context, *(Outer->PrintNameAndClass()));

		FVector3f Location = FVector3f::ZeroVector;

		// Actor
		if (AActor* Actor = Cast<AActor>(TheOwner))
		{
			Location = MathLibrary::Convert(Actor->GetActorLocation()) + Offset;
		}
		// Component
		else
		if (USceneComponent* Component = Cast<USceneComponent>(TheOwner))
		{
			Location = MathLibrary::Convert(Component->GetComponentLocation()) + Offset;
		}
		else
		{
			checkf(0, TEXT("%s: Failed to get Location from %s."), *Context, *(Outer->PrintNameClassAndOwner()));
		}
		return GetLaunchSpreadLocation(Location, LaunchPayload);
	}
	// Bone
	if (LocationType == LaunchLocationType::Bone)
	{
		checkf(0, TEXT("NOT IMPLEMENTED"));
	}
	// Component
	if (LocationType == LaunchLocationType::Component)
	{
		CS_IS_PTR_NULL_CHECKED(LaunchComponentLocation)

		FVector3f Location = MathLibrary::Convert(LaunchComponentLocation->GetComponentLocation()) + Offset;

		return GetLaunchSpreadLocation(Location, LaunchPayload);
	}
	// Custom
	if (LocationType == LaunchLocationType::Custom)
	{
		FVector3f Location = CustomLaunchLocation + Offset;

		// TODO: Get the Launch Direction properly
		
		// TEMP: Just assume DirectionType is Custom

		return GetLaunchSpreadLocation(Location, LaunchPayload);
	}
	checkf(0, TEXT("%s: Failed to get Location from %s."), *Context, *(Outer->PrintNameClassAndOwner()));
	return FVector3f::ZeroVector;
}

FVector3f ACsProjectileWeaponActorPooled::FProjectileImpl::GetLaunchSpreadLocation(const FVector3f& InLocation, const LaunchPayloadType& LaunchPayload)
{
	FVector3f Location = InLocation;

	if (LaunchPayload.bSpread &&
		LaunchPayload.Spread.HasOffset())
	{
		typedef NCsMath::FLibrary MathLibrary;

		static const int32 AXIS_UP				 = 0;
		static const int32 AXIS_LAUNCH_DIRECTION = 1;

		// Up
		if (LaunchPayload.Spread.Axis == AXIS_UP)
		{
			Location.X += LaunchPayload.Spread.Offset.X;
			Location.Y += LaunchPayload.Spread.Offset.Y;
		}
		else
		if (LaunchPayload.Spread.Axis == AXIS_LAUNCH_DIRECTION)
		{
			const FVector3f Direction = GetLaunchDirection();

			Location += LaunchPayload.Spread.Offset.X * MathLibrary::GetRightFromNormal(Direction);
			Location += LaunchPayload.Spread.Offset.Y * MathLibrary::GetUpFromNormal(Direction);
		}	
	}
	return Location;
}

FVector3f ACsProjectileWeaponActorPooled::FProjectileImpl::GetLaunchDirection(const LaunchPayloadType& LaunchPayload)
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

	// Get Launch Params
	typedef NCsWeapon::NProjectile::NParams::NLaunch::FLibrary ParamsLibrary;
	typedef NCsWeapon::NProjectile::NParams::NLaunch::ILaunch LaunchParamsType;
	typedef NCsWeapon::NProjectile::NParams::NLaunch::ELocation LaunchLocationType;
	typedef NCsWeapon::NProjectile::NParams::NLaunch::EDirection LaunchDirectionType;

	const LaunchParamsType* LaunchParams = ParamsLibrary::GetChecked(Context, Outer->GetData());

	const LaunchLocationType& LocationType   = LaunchParams->GetLocationType();
	const LaunchDirectionType& DirectionType = LaunchParams->GetDirectionType();
	const FRotator3f& DirectionOffset			 = LaunchParams->GetDirectionOffset();
	int32 DirectionScalar					 = LaunchParams->InvertDirection() ? -1.0f : 1.0f;
	const int32& DirectionRules				 = LaunchParams->GetDirectionRules();

	if (LaunchPayload.Shot.UseCachedLaunchDirection())
	{
		const FVector3f Dir = NCsRotationRules::GetDirection(LaunchPayload.Shot.CachedLaunchDirection, DirectionRules);

		return GetLaunchSpreadDirection(Dir, LaunchPayload);
	}

	typedef NCsMath::FLibrary MathLibrary;

	// Owner
	if (DirectionType == LaunchDirectionType::Owner)
	{
		if (UObject* TheOwner = Outer->GetMyOwner())
		{
			// AActor
			if (AActor* Actor = Cast<AActor>(TheOwner))
			{
				const FRotator3f Rotation = NCsRotationRules::GetRotation(Actor, DirectionRules);
				FVector3f Dir				= Rotation.Vector();

				const FRotator3f RotationOffset = NCsRotationRules::GetRotation(DirectionOffset, DirectionRules);

				Dir = Dir.RotateAngleAxis(RotationOffset.Pitch, MathLibrary::GetRightFromNormal(Dir));
				Dir = Dir.RotateAngleAxis(RotationOffset.Yaw, FVector3f::UpVector);
				Dir = DirectionScalar * GetLaunchSpreadDirection(Dir, LaunchPayload);
				CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(LaunchParams, Dir));
				return Dir;
			}
			// USceneComponent
			if (USceneComponent* Component = Cast<USceneComponent>(TheOwner))
			{
				const FRotator3f Rotation = NCsRotationRules::GetRotation(Component, DirectionRules);
				FVector3f Dir				= Rotation.Vector();

				const FRotator3f RotationOffset = NCsRotationRules::GetRotation(DirectionOffset, DirectionRules);

				Dir = Dir.RotateAngleAxis(RotationOffset.Pitch, MathLibrary::GetRightFromNormal(Dir));
				Dir = Dir.RotateAngleAxis(RotationOffset.Yaw, FVector3f::UpVector);
				Dir = DirectionScalar * GetLaunchSpreadDirection(Dir, LaunchPayload);
				CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(LaunchParams, Dir));
				return Dir;
			}
			checkf(0, TEXT("%s: Failed to get Direction from %s."), *Context, *(Outer->PrintNameClassAndOwner()));
		}
	}
	// Bone
	if (DirectionType == LaunchDirectionType::Bone)
	{
		checkf(0, TEXT("NOT IMPLEMENTED"));
	}
	// Component
	if (DirectionType == LaunchDirectionType::Component)
	{
		const FRotator3f Rotation = NCsRotationRules::GetRotation(LaunchComponentDirection, DirectionRules);
		FVector3f Dir			  = Rotation.Vector();

		const FRotator3f RotationOffset = NCsRotationRules::GetRotation(DirectionOffset, DirectionRules);

		Dir = Dir.RotateAngleAxis(RotationOffset.Pitch, MathLibrary::GetRightFromNormal(Dir));
		Dir = Dir.RotateAngleAxis(RotationOffset.Yaw, FVector3f::UpVector);
		Dir = DirectionScalar * GetLaunchSpreadDirection(Dir, LaunchPayload);
		CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(LaunchParams, Dir));
		return Dir;
	}
	// Camera
	if (DirectionType == LaunchDirectionType::Camera)
	{
		// Try to get camera through the owner
		if (UObject* TheOwner = Outer->GetMyOwner())
		{
			typedef NCsCamera::FLibrary CameraLibrary;

			FVector3f Dir	= CameraLibrary::GetDirectionChecked(Context, Outer, DirectionRules);

			const FRotator3f RotationOffset = NCsRotationRules::GetRotation(DirectionOffset, DirectionRules);

			Dir = Dir.RotateAngleAxis(RotationOffset.Pitch, MathLibrary::GetRightFromNormal(Dir));
			Dir = Dir.RotateAngleAxis(RotationOffset.Yaw, FVector3f::UpVector);
			Dir = DirectionScalar * GetLaunchSpreadDirection(Dir, LaunchPayload);
			CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(LaunchParams, Dir));
			return Dir;
		}
		checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *(Outer->PrintNameAndClass()));
	}
	// ITrace | Get Launch Trace Params
	if (DirectionType == LaunchDirectionType::Trace)
	{
		typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace TraceParamsType;

		const TraceParamsType* LaunchTraceParams = ParamsLibrary::GetInterfaceChecked<TraceParamsType>(Context, LaunchParams);
		
		// Start
		typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EStart LaunchTraceStartType;

		const LaunchTraceStartType& TraceStart = LaunchTraceParams->GetTraceStartType();

		FVector3f Start = FVector3f::ZeroVector;

		// LaunchLocation
		if (TraceStart == LaunchTraceStartType::LaunchLocation)
		{
			Start = GetLaunchLocation(LaunchPayload);
		}
		// Owner
		else
		if (TraceStart == LaunchTraceStartType::Owner)
		{
			checkf(0, TEXT("NOT IMPLEMENTED"));
		}
		// Bone
		else
		if (TraceStart == LaunchTraceStartType::Bone)
		{
			checkf(0, TEXT("NOT IMPLEMENTED"));
		}
		// Component
		else
		if (TraceStart == LaunchTraceStartType::Component)
		{
			CS_IS_PTR_NULL_CHECKED(LaunchComponentLocation)

			Start = MathLibrary::Convert(LaunchComponentLocation->GetComponentLocation());
		}
		// Camera
		else
		if (TraceStart == LaunchTraceStartType::Camera)
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
		typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EDirection LaunchTraceDirectionType;

		const LaunchTraceDirectionType& TraceDirection  = LaunchTraceParams->GetTraceDirectionType();

		FVector3f Dir = FVector3f::ZeroVector;

		// Owner
		if (TraceDirection == LaunchTraceDirectionType::Owner)
		{
			checkf(0, TEXT("NOT IMPLEMENTED"));
		}
		// Bone
		else
		if (TraceDirection == LaunchTraceDirectionType::Bone)
		{
			checkf(0, TEXT("NOT IMPLEMENTED"));
		}
		// Component
		else
		if (TraceDirection == LaunchTraceDirectionType::Component)
		{
			CS_IS_PTR_NULL_CHECKED(LaunchComponentDirection)

			const FRotator3f Rotation = MathLibrary::Convert(NCsRotationRules::GetRotation(LaunchComponentDirection->GetComponentRotation(), DirectionRules));

			Dir = Rotation.Vector();
		}
		else
		// Camera
		if (TraceDirection == LaunchTraceDirectionType::Camera)
		{
			// Try to get camera through the owner
			if (UObject* TheOwner = Outer->GetMyOwner())
			{
				typedef NCsCamera::FLibrary CameraLibrary;

				const FRotator3f Rotation = CameraLibrary::GetRotationChecked(Context, TheOwner, DirectionRules);

				Dir = Rotation.Vector();
			}
			// TODO: For now assert
			else
			{
				checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *(Outer->PrintNameAndClass()));
			}
		}

		const float& Distance = LaunchTraceParams->GetTraceDistance();

		const FVector3f End = Start + Distance * Dir;

		// Perform Trace
		typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;
		typedef NCsTrace::NRequest::FRequest RequestType;

		UCsManager_Trace* Manager_Trace = TraceManagerLibrary::GetChecked(Context, Outer->GetWorldContext());

		RequestType* Request = Manager_Trace->AllocateRequest();
		Request->Start		 = Start;
		Request->End		 = End;

		// Get collision information related to the projectile to be used in the trace.

		typedef NCsProjectile::NData::IData PrjDataType;
		typedef NCsProjectile::NData::NCollision::ICollision PrjCollisionDataType;

		PrjDataType* PrjData				   = CsPrjManagerLibrary::GetChecked(Context, Outer->GetWorldContext())->GetDataChecked(Context, Outer->GetProjectileType());
		PrjCollisionDataType* PrjCollisionData = CsPrjDataLibrary::GetInterfaceChecked<PrjCollisionDataType>(Context, PrjData);

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

		FVector3f LookAtLocation = FVector3f::ZeroVector;

		if (Response &&
			Response->bResult)
		{
			LookAtLocation = Start + Response->OutHits[CS_FIRST].Distance * Dir;
		}
		else
		{
			LookAtLocation = Start + Distance * Dir;
		}

		const FVector3f LaunchLocation  = GetLaunchLocation(LaunchPayload);
		FVector3f LaunchDirection		  = (LookAtLocation - LaunchLocation).GetSafeNormal();

		const FRotator3f RotationOffset = NCsRotationRules::GetRotation(DirectionOffset, DirectionRules);

		LaunchDirection = LaunchDirection.RotateAngleAxis(RotationOffset.Pitch, MathLibrary::GetRightFromNormal(LaunchDirection));
		LaunchDirection = LaunchDirection.RotateAngleAxis(RotationOffset.Yaw, FVector3f::UpVector);

		// Check the direction is in FRONT of the Start. The trace could produce a result BEHIND the start

		if (Start == LaunchDirection ||
			FVector3f::DotProduct(Dir, LaunchDirection) > 0)
		{
			CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(LaunchParams, DirectionScalar * LaunchDirection));
			return LaunchDirection;
		}
		CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(LaunchParams, DirectionScalar * Dir));
		return Dir;
	}
	// Custom
	if (DirectionType == LaunchDirectionType::Custom)
	{		
		const FRotator3f RotationOffset = NCsRotationRules::GetRotation(DirectionOffset, DirectionRules);
		FVector3f Direction			  = NCsRotationRules::GetDirection(CustomLaunchDirection, DirectionRules);

		Direction = Direction.RotateAngleAxis(RotationOffset.Pitch, MathLibrary::GetRightFromNormal(Direction));
		Direction = Direction.RotateAngleAxis(RotationOffset.Yaw, FVector3f::UpVector);

		Direction = DirectionScalar * GetLaunchSpreadDirection(Direction, LaunchPayload);

		CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(LaunchParams, Direction));
		return Direction;
	}
	CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(LaunchParams, FVector3f::ZeroVector));
	return FVector3f::ZeroVector;
}

FVector3f ACsProjectileWeaponActorPooled::FProjectileImpl::GetLaunchSpreadDirection(const FVector3f& InDirection, const LaunchPayloadType& LaunchPayload)
{
	FVector3f Direction = InDirection;

	if (LaunchPayload.bSpread)
	{
		// Yaw
		if (LaunchPayload.Spread.HasYaw())
		{
			Direction = Direction.RotateAngleAxis(LaunchPayload.Spread.Yaw, FVector3f::UpVector);
		}
		// Pitch
		if (LaunchPayload.Spread.HasPitch())
		{
			typedef NCsMath::FLibrary MathLibrary;

			Direction = MathLibrary::RotateNormalAngleRight(Direction, LaunchPayload.Spread.Pitch);
		}
	}
	return Direction;
}

#define LaunchParamsType NCsWeapon::NProjectile::NParams::NLaunch::ILaunch
void ACsProjectileWeaponActorPooled::FProjectileImpl::Log_GetLaunchDirection(const LaunchParamsType* LaunchParams, const FVector3f& Direction)
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

void ACsProjectileWeaponActorPooled::FProjectileImpl::Launch(const LaunchPayloadType& LaunchPayload)
{
	CS_SCOPED_TIMER(LaunchScopedHandle);

	using namespace NCsProjectileWeaponActorPooled::NCached::NProjectileImpl;

	const FString& Context = Str::Launch;

	typedef NCsProjectile::NPayload::IPayload PayloadType;

	UCsManager_Projectile* Manager_Projectile = CsPrjManagerLibrary::GetChecked(Context, Outer->GetWorldContext());

	// Get Payload
	const FECsProjectile& PrjType = Outer->GetProjectileType();
	PayloadType* Payload		  = Manager_Projectile->AllocatePayload(PrjType);

	// Set appropriate members on Payload
	const bool SetSuccess = SetPayload(Context, Payload, LaunchPayload);

	checkf(SetSuccess, TEXT("%s: Failed to set Payload."), *Context);

	// Spawn
	const FCsProjectilePooled* ProjectilePooled = Manager_Projectile->Spawn(PrjType, Payload);
}

#undef LaunchPayloadType

ACsProjectileWeaponActorPooled::FProjectileImpl* ACsProjectileWeaponActorPooled::ConstructProjectileImpl()
{
	return new ACsProjectileWeaponActorPooled::FProjectileImpl();
}

void ACsProjectileWeaponActorPooled::ProjectileImpl_SetLaunchComponentLocation(USceneComponent* Component)
{
	ProjectileImpl->SetLaunchComponentLocation(Component);
}

void ACsProjectileWeaponActorPooled::ProjectileImpl_SetLaunchComponentDirection(USceneComponent* Component)
{
	ProjectileImpl->SetLaunchComponentDirection(Component);
}

bool ACsProjectileWeaponActorPooled::UseSpreadParams() const
{
	using namespace NCsProjectileWeaponActorPooled::NCached;

	const FString& Context = Str::UseSpreadParams;

	if (PrjWeaponData->UseSpreadParams())
		return true;

	typedef NCsWeapon::NModifier::IModifier ModifierType;

	static TArray<ModifierType*> Modifiers;
	Modifiers.Reset(Modifiers.Max());

	GetWeaponModifiers(Modifiers);

	typedef NCsWeapon::NModifier::FLibrary ModifierLibrary;

	return ModifierLibrary::ToggleChecked(Context, Modifiers, NCsWeaponModifier::PrjWp_UseSpreadParams);
}

#pragma endregion Projectile

	// Sound
#pragma region

void ACsProjectileWeaponActorPooled::FSoundImpl::Play(const int32 CurrentProjectilePerShotIndex)
{
	using namespace NCsProjectileWeaponActorPooled::NCached::NSoundImpl;

	const FString& Context = Str::Play;

	// SoundDataType (NCsWeapon::NProjectile::NData::NSound::NFire::IFire)
	typedef NCsWeapon::NProjectile::NData::NSound::NFire::IFire SoundDataType;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	if (SoundDataType* SoundData = WeaponDataLibrary::GetSafeInterfaceChecked<SoundDataType>(Context, Outer->GetData()))
	{
		typedef NCsWeapon::NProjectile::NFire::NSound::FParams ParamsType;

		const ParamsType& Params = SoundData->GetFireSoundParams();

		static const int32 START = -1;

		// Start
		if (CurrentProjectilePerShotIndex == START)
		{
			if (Params.GetbStartParams())
			{
				typedef NCsWeapon::NProjectile::NFire::NSound::NStart::FParams StartParamsType;

				const StartParamsType& StartParams = Params.GetStartParams();

				const FCsSound& Sound = StartParams.GetSound();

				typedef NCsPooledObject::NPayload::FImplSlice PayloadImplType;

				PayloadImplType Payload;
				Payload.Instigator = Outer;
				Payload.Owner	   = Outer->GetMyOwner();

				typedef NCsSound::NManager::FLibrary SoundManagerLibrary;
				// TODO: Make sure Outer is defined
				SoundManagerLibrary::SpawnChecked(Context, Outer->GetWorldContext(), &Payload, Sound);
			}
		}
		// Shot
		else
		{
			if (Params.GetbShotParams())
			{
				typedef NCsWeapon::NProjectile::NFire::NSound::NShot::FParams ShotParamsType;

				const ShotParamsType& ShotParams = Params.GetShotParams();

				// Either Skip First or Always
				if (!ShotParams.GetbSkipFirst() ||
					CurrentProjectilePerShotIndex > 0)
				{
					const FCsSound& Sound = ShotParams.GetSound();

					typedef NCsPooledObject::NPayload::FImplSlice PayloadImplType;

					PayloadImplType Payload;
					Payload.Instigator = Outer;
					Payload.Owner	   = Outer->GetMyOwner();

					typedef NCsSound::NManager::FLibrary SoundManagerLibrary;
					// TODO: Make sure Outer is defined
					SoundManagerLibrary::SpawnChecked(Context, Outer->GetWorldContext(), &Payload, Sound);
				}
			}
		}
	}
}

ACsProjectileWeaponActorPooled::FSoundImpl* ACsProjectileWeaponActorPooled::ConstructSoundImpl()
{
	return new ACsProjectileWeaponActorPooled::FSoundImpl();
}

#pragma endregion Sound

	// FX
#pragma region

#define LaunchPayloadType ACsProjectileWeaponActorPooled::FProjectileImpl::FLaunchPayload

void ACsProjectileWeaponActorPooled::FFXImpl::Play(const int32 CurrentProjectilePerShotIndex, const LaunchPayloadType& LaunchPayload)
{
	using namespace NCsProjectileWeaponActorPooled::NCached::NFXImpl;

	const FString& Context = Str::Play;

	// FXDataType (NCsWeapon::NProjectile::NData::NVisual::NFire::IFire)
	typedef NCsWeapon::NProjectile::NData::NVisual::NFire::IFire FXDataType;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	if (FXDataType* FXData = WeaponDataLibrary::GetSafeInterfaceChecked<FXDataType>(Context, Outer->GetData()))
	{
		typedef NCsWeapon::NProjectile::NFire::NVisual::FParams ParamsType;

		const ParamsType& Params = FXData->GetFireVisualParams();

		static const int32 START = -1;

		// Start
		if (CurrentProjectilePerShotIndex == START)
		{
			if (Params.GetbStartParams())
			{
				typedef NCsWeapon::NProjectile::NFire::NVisual::NStart::FParams StartParamsType;

				const StartParamsType& StartParams = Params.GetStartParams();

				const FCsFX& FX	= StartParams.GetFX();

				UNiagaraSystem* FXAsset = FX.GetChecked(Context);

				// Get Manager
				UCsManager_FX* Manager_FX = CsFXManagerLibrary::GetChecked(Context, Outer->GetWorldContext());
				// Allocate payload
				typedef NCsFX::NPayload::IPayload PayloadType;

				PayloadType* Payload = Manager_FX->AllocatePayload(FX.Type);
				// Set appropriate values on payload
				SetPayload(CurrentProjectilePerShotIndex, Payload, FX, LaunchPayload);
				SetPayload(CurrentProjectilePerShotIndex, Payload, FXData);

				Manager_FX->Spawn(FX.Type, Payload);
			}
		}
		// Shot
		else
		{
			if (Params.GetbShotParams())
			{
				typedef NCsWeapon::NProjectile::NFire::NVisual::NShot::FParams ShotParamsType;

				const ShotParamsType& ShotParams = Params.GetShotParams();

				// Either Skip First or Always
				if (!ShotParams.GetbSkipFirst() ||
					CurrentProjectilePerShotIndex > 0)
				{
					const FCsFX& FX	= ShotParams.GetFX();

					UNiagaraSystem* FXAsset = FX.GetChecked(Context);

					// Get Manager
					UCsManager_FX* Manager_FX = CsFXManagerLibrary::GetChecked(Context, Outer->GetWorldContext());
					// Allocate payload
					typedef NCsFX::NPayload::IPayload PayloadType;

					PayloadType* Payload = Manager_FX->AllocatePayload(FX.Type);
					// Set appropriate values on payload
					SetPayload(CurrentProjectilePerShotIndex, Payload, FX, LaunchPayload);
					SetPayload(CurrentProjectilePerShotIndex, Payload, FXData);

					Manager_FX->Spawn(FX.Type, Payload);
				}
			}
		}
	}
}

#define FXPayloadType NCsFX::NPayload::IPayload
void ACsProjectileWeaponActorPooled::FFXImpl::SetPayload(const int32 CurrentProjectilePerShotIndex, FXPayloadType* Payload, const FCsFX& FX, const LaunchPayloadType& LaunchPayload)
{
#undef FXPayloadType

	using namespace NCsProjectileWeaponActorPooled::NCached::NFXImpl;

	const FString& Context = Str::SetPayload;

	typedef NCsFX::NPayload::FImpl PayloadImplType;
	typedef NCsFX::NPayload::FLibrary PayloadLibrary;

	PayloadImplType* PayloadImpl = PayloadLibrary::PureStaticCastChecked<PayloadImplType>(Context, Payload);

	PayloadImpl->Instigator					= Outer;
	PayloadImpl->Owner						= Outer->GetMyOwner();
	PayloadImpl->FXSystem					= FX.GetChecked(Context);
	PayloadImpl->DeallocateMethod			= FX.GetDeallocateMethod();
	PayloadImpl->LifeTime					= FX.LifeTime;
	PayloadImpl->AttachmentTransformRules	= FX.AttachmentTransformRules;
	PayloadImpl->Bone						= FX.Bone;
	PayloadImpl->TransformRules				= FX.TransformRules;
	PayloadImpl->Transform					= FX.Transform;

	typedef NCsWeapon::NProjectile::NData::NVisual::NFire::IFire FXDataType;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	FXDataType* FXData = WeaponDataLibrary::GetInterfaceChecked<FXDataType>(Context, Outer->GetData());

	typedef NCsWeapon::NProjectile::NFire::NVisual::FParams ParamsType;
	typedef NCsWeapon::NProjectile::NFire::NVisual::EAttach AttachType;

	const ParamsType& Params = FXData->GetFireVisualParams();
	
	AttachType Type = AttachType::None;

	static const int32 START = -1;

	if (CurrentProjectilePerShotIndex == START)
	{
		Type = Params.GetStartParams().GetAttach();
	}
	else
	{
		Type = Params.GetShotParams().GetAttach();
	}

	// None
	if (Type == AttachType::None)
	{
		const FVector3f Location = Outer->ProjectileImpl->GetLaunchLocation(LaunchPayload);
		PayloadImpl->Transform.SetTranslation(Location);

		const FVector3f Direction = Outer->ProjectileImpl->GetLaunchDirection(LaunchPayload);
		FQuat4f Rotation		  = FX.Transform.GetRotation();
		PayloadImpl->Transform.SetRotation(Direction.ToOrientationQuat() * Rotation);
	}
	// Owner
	else
	if (Type == AttachType::Owner)
	{
		PayloadImpl->Parent = Outer->GetMyOwner();
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

#undef LaunchPayloadType

#define FXPayloadType NCsFX::NPayload::IPayload
#define FXDataType NCsWeapon::NProjectile::NData::NVisual::NFire::IFire
void ACsProjectileWeaponActorPooled::FFXImpl::SetPayload(const int32 CurrentProjectilePerShotIndex, FXPayloadType* Payload, FXDataType* FXData)
{
#undef FXPayloadType
#undef FXDataType

	using namespace NCsProjectileWeaponActorPooled::NCached::NFXImpl;

	const FString& Context = Str::SetPayload;

	typedef NCsWeapon::NProjectile::NFire::NVisual::FParams ParamsType;
	typedef NCsWeapon::NProjectile::NFire::NVisual::EAttach AttachType;

	const ParamsType& Params = FXData->GetFireVisualParams();
	
	AttachType Type = AttachType::None;

	static const int32 START = -1;

	if (CurrentProjectilePerShotIndex == START)
	{
		Type = Params.GetStartParams().GetAttach();
	}
	else
	{
		Type = Params.GetShotParams().GetAttach();
	}

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
		PayloadImpl->Parent = Outer->GetMyOwner();
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

// Modifier
#pragma region

bool ACsProjectileWeaponActorPooled::GetModifiedIntProperty(const FECsWeaponModifier& ModifierType, int32& OutValue) const
{
	// ProjectilesPerShot.Count
	if (ModifierType == NCsWeaponModifier::PrjWp_ProjectilesPerShot_Count)
	{
		OutValue = ProjectilesPerShot_GetCount();
		return true;
	}
	return false;
}

bool ACsProjectileWeaponActorPooled::GetModifiedFloatProperty(const FECsWeaponModifier& ModifierType, float& OutValue) const
{
	// TimeBetweenShots
	if (ModifierType == NCsWeaponModifier::PrjWp_TimeBetweenShots)
	{
		OutValue = GetTimeBetweenShots();
		return true;
	}
	// ProjectilePerShot: Interval
	if (ModifierType == NCsWeaponModifier::PrjWp_ProjectilesPerShot_Interval)
	{
		OutValue = ProjectilesPerShot_GetInterval();
		return true;
	}
	return false;
}

#pragma endregion Modifier

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