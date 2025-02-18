// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Projectile/CsProjectileWeaponActorPooled.h"
#include "CsWp.h"

// CVar
#include "Projectile/CsCVars_ProjectileWeapon.h"
#include "Script/CsCVars_Script.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
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
#include "Library/Cslibrary_DataType.h"
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
#include "Component/CsWeapon_Component.h"
#include "Fire/TimeBetweenShots/CsWeapon_Fire_TimeBetweenShots.h"
#include "Fire/Projectile/CsWeapon_Fire_ProjectileImpl.h"
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

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsProjectileWeaponActorPooled)

// ACsProjectileWeaponActorPooled
//	Cached 
#pragma region

CS_START_CACHED_FUNCTION_NAME(CsProjectileWeaponActorPooled)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectileWeaponActorPooled, SetUpdateGroup)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectileWeaponActorPooled, Allocate)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectileWeaponActorPooled, SetWeaponType)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectileWeaponActorPooled, SetProjectileType)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectileWeaponActorPooled, Init)
	// AActor Interface
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectileWeaponActorPooled, BeginPlay)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectileWeaponActorPooled, PostInitializeComponents)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectileWeaponActorPooled, OnUpdate_HandleStates)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectileWeaponActorPooled, CanFire)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectileWeaponActorPooled, Fire)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectileWeaponActorPooled, Fire_Internal)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectileWeaponActorPooled, Fire_Internal_OnEnd)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectileWeaponActorPooled, GetTimeBetweenShots)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectileWeaponActorPooled, ProjectilesPerShot_GetCount)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectileWeaponActorPooled, ProjectilesPerShot_GetInterval)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectileWeaponActorPooled, FireProjectile)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectileWeaponActorPooled, SetProjectilePayload)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectileWeaponActorPooled, LaunchProjectile)
	CS_DEFINE_CACHED_FUNCTION_NAME(ACsProjectileWeaponActorPooled, UseSpreadParams)
CS_END_CACHED_FUNCTION_NAME

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
	ProjectileClass(nullptr),
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

using PooledPayloadLibrary = NCsPooledObject::NPayload::FLibrary;
using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
using PayloadType = NCsWeapon::NPayload::IPayload;
using FXPayloadImplType = NCsFX::NPayload::NImpl::FImpl;
using LaunchPayloadType = NCsWeapon::NFire::NProjectile::NLaunch::NPayload::FPayload;
using FXDataType = NCsWeapon::NProjectile::NData::NVisual::NFire::IFire;

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
	CS_SET_CONTEXT_AS_FUNCTION_NAME(BeginPlay);

	Super::BeginPlay();

	SkeletalMeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);

	ConstructCache();

	// Create Components
	{
		// TimeBetweenShots
		{
			UActorComponent* AC = NewObject<UActorComponent>(this, CS_SOFT_CLASS_PTR_LOAD_CHECKED(TimeBetweenShotsClass, UObject));
			AC->RegisterComponent();

			TimeBetweenShotsImpl = CS_INTERFACE_CAST_CHECKED(AC, UActorComponent, ICsWeapon_Fire_TimeBetweenShots);
			// Setup
			ICsWeapon_Component* WC = CS_INTERFACE_TO_INTERFACE_CAST_CHECKED(TimeBetweenShotsImpl, ICsWeapon_Fire_TimeBetweenShots, ICsWeapon_Component);
			WC->SetWeapon(this);
		}
		// Projectile
		{
			UActorComponent* AC = NewObject<UActorComponent>(this, CS_SOFT_CLASS_PTR_LOAD_CHECKED(ProjectileClass, UObject));
			AC->RegisterComponent();

			ProjectileImpl = CS_INTERFACE_CAST_CHECKED(AC, UActorComponent, ICsWeapon_Fire_Projectile);
			// Setup
			ICsWeapon_Component* WC = CS_INTERFACE_TO_INTERFACE_CAST_CHECKED(ProjectileImpl, ICsWeapon_Fire_Projectile, ICsWeapon_Component);
			WC->SetWeapon(this);
		}
	}

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
			/*const FString& ScopeName		   = NProjectileImpl::Str::Launch;
			const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponProjectile;
			const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponProjectileProjectileScopedTimerLaunch;

			ProjectileImpl->LaunchScopedHandle = FCsManager_ScopedTimer::Get().GetHandle(&ScopeName, ScopedGroup, ScopeLog);*/
		}
	}
#endif // #if !UE_BUILD_SHIPPING
}

void ACsProjectileWeaponActorPooled::PostInitializeComponents()
{
	CS_SET_CONTEXT_AS_FUNCTION_NAME(PostInitializeComponents);

	Super::PostInitializeComponents();

#if WITH_EDITOR
	if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(this))
	{
		SkeletalMeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);

		ConstructCache();

		// TimeBetweenShots
		if (!TimeBetweenShotsImpl)
		{
			UActorComponent* AC = NewObject<UActorComponent>(this, CS_SOFT_CLASS_PTR_LOAD_CHECKED(TimeBetweenShotsClass, UObject));
			AC->RegisterComponent();

			TimeBetweenShotsImpl = CS_INTERFACE_CAST_CHECKED(AC, UActorComponent, ICsWeapon_Fire_TimeBetweenShots);
			// Setup
			ICsWeapon_Component* WC = CS_INTERFACE_TO_INTERFACE_CAST_CHECKED(TimeBetweenShotsImpl, ICsWeapon_Fire_TimeBetweenShots, ICsWeapon_Component);
			WC->SetWeapon(this);
		}
		// Projectile
		if (!ProjectileImpl)
		{
			UActorComponent* AC = NewObject<UActorComponent>(this, CS_SOFT_CLASS_PTR_LOAD_CHECKED(ProjectileClass, UObject));
			AC->RegisterComponent();

			ProjectileImpl = CS_INTERFACE_CAST_CHECKED(AC, UActorComponent, ICsWeapon_Fire_Projectile);
			// Setup
			ICsWeapon_Component* WC = CS_INTERFACE_TO_INTERFACE_CAST_CHECKED(ProjectileImpl, ICsWeapon_Fire_Projectile, ICsWeapon_Component);
			WC->SetWeapon(this);
		}

		SoundImpl = ConstructSoundImpl();
		SoundImpl->Outer = this;

		FXImpl = ConstructFXImpl();
		FXImpl->Outer = this;

		using namespace NCsProjectileWeaponActorPooled::NCached;

		// FireScopedHandle
		{
			const FString& ScopeName = Str::Fire_Internal;
			const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponProjectile;
			const FECsCVarLog& ScopeLog = NCsCVarLog::LogWeaponProjectileScopedTimerFire;

			FireScopedHandle.Handle = FCsManager_ScopedTimer::Get().GetHandle(&ScopeName, ScopedGroup, ScopeLog);
		}
		// LaunchScopedHandle
		{
			/*const FString& ScopeName = NProjectileImpl::Str::Launch;
			const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponProjectile;
			const FECsCVarLog& ScopeLog = NCsCVarLog::LogWeaponProjectileProjectileScopedTimerLaunch;

			ProjectileImpl->LaunchScopedHandle = FCsManager_ScopedTimer::Get().GetHandle(&ScopeName, ScopedGroup, ScopeLog);*/
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
	CS_SILENT_CLEAR_SCOPED_TIMER_HANDLE(FireScopedHandle.Handle)

	TimeBetweenShotsImpl = nullptr;
	ProjectileImpl = nullptr;
	/*if (ProjectileImpl)
	{
		CS_SILENT_CLEAR_SCOPED_TIMER_HANDLE(ProjectileImpl->LaunchScopedHandle)

		delete ProjectileImpl;
		ProjectileImpl = nullptr;
	}*/
	CS_SAFE_DELETE_PTR(SoundImpl)
	CS_SAFE_DELETE_PTR(FXImpl)

	bShutdown = true;
}

#pragma endregion ICsShutdown

// ICsPooledObject
#pragma region

void ACsProjectileWeaponActorPooled::Allocate(PooledPayloadType* Payload)
{
	using namespace NCsProjectileWeaponActorPooled::NCached;

	const FString& Context = Str::Allocate;

	CS_IS_PTR_NULL_CHECKED(Payload)

	Cache->Allocate(Payload);

	PayloadType* WeaponPayload = PooledPayloadLibrary::GetInterfaceChecked<PayloadType>(Context, Payload);

	SetWeaponType(WeaponPayload->GetType());
	SetUpdateGroup(WeaponPayload->GetUpdateGroup());

	MyOwner		   = Payload->GetOwner();
	MyOwnerAsActor = Cast<AActor>(MyOwner);

	// Get Data
	typedef NCsWeapon::NProjectile::NData::IData PrjWeaponDataType;

	Data		  = CsWeaponManagerLibrary::GetDataChecked(Context, GetWorldContext(), WeaponType);
	PrjWeaponData = CsWeaponDataLibrary::GetInterfaceChecked<PrjWeaponDataType>(Context, Data);

	ICsData_GetProjectileType* GetProjectileType = CsWeaponDataLibrary::GetInterfaceChecked<ICsData_GetProjectileType>(Context, Data);

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

	TimeBetweenShotsImpl->SetBase(PrjWeaponData->GetTimeBetweenShots());
	TimeBetweenShotsImpl->ResetValueToBase();
}

void ACsProjectileWeaponActorPooled::Deallocate()
{
	ProjectileImpl->Clear();

	OnConsumeAmmo_Event.Clear();
	OnFire_PreStart_Event.Clear();
	OnFire_PreShot_Event.Clear();
	OnFire_End_Event.Clear();

	TimeBetweenShotsImpl->Clear();

	// End Routines
	if (UCsCoroutineScheduler* Scheduler = CsCoroutineSchedulerLibrary::GetSafe(GetWorldContext()))
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
	typedef NCsWeapon::NCache::NImpl::FImpl CacheImplType;

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

			TimeBetweenShotsImpl->Evaluate();

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

			TimeBetweenShotsImpl->Evaluate();
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
		const TCHAR*(*ToChar)(const bool& Value) = &CsDataTypeLibrary::ToChar;

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
	CS_SET_CONTEXT_AS_FUNCTION_NAME(Fire);

	CS_COROUTINE_SETUP_UOBJECT(ACsProjectileWeaponActorPooled, Fire_Internal, UpdateGroup, this, GetWorldContext());

	const FCsDeltaTime& TimeSinceStart = CsTimeManagerLibrary::GetTimeSinceStartChecked(Context, GetWorldContext(), UpdateGroup);

	Fire_StartTime = TimeSinceStart.Time;

	const FGuid FireGuid = FGuid::NewGuid();
	uint32 FireID		 = GetTypeHash(FireGuid);

	FireIDs.Add(FireID);

	CS_COROUTINE_PAYLOAD_PASS_UNSIGNED_INT_START
	CS_COROUTINE_PAYLOAD_PASS_FLAG_START
	CS_COROUTINE_PAYLOAD_PASS_INT_START
	CS_COROUTINE_PAYLOAD_PASS_FLOAT_START
	CS_COROUTINE_PAYLOAD_PASS_VECTOR_START
	CS_COROUTINE_PAYLOAD_PASS_VECTOR3F_START
	CS_COROUTINE_PAYLOAD_PASS_VOID_START

	CS_COROUTINE_PAYLOAD_PASS_UNSIGNED_INT(FireID);

	Fire_PreStart(FireID);
	OnFire_PreStart_Event.Broadcast(this, FireID);

	CS_COROUTINE_PAYLOAD_PASS_FLAG(PrjWeaponData->HasInfiniteAmmo());

	// ProjectilePerShot
	int32 ProjectilesPerShot = ProjectilesPerShot_GetCount();
	CS_COROUTINE_PAYLOAD_PASS_INT(ProjectilesPerShot);

	CS_COROUTINE_PAYLOAD_PASS_FLOAT(ProjectilesPerShot_GetInterval());

		// Cache Launch Location
	const bool UseCachedLaunchLocation = !PrjWeaponData->GetProjectilesPerShotParams().GetbCurrentLaunchLocation();
	CS_COROUTINE_PAYLOAD_PASS_FLAG(UseCachedLaunchLocation);

	if (UseCachedLaunchLocation)
	{
		CS_COROUTINE_PAYLOAD_PASS_VECTOR(ProjectileImpl->GetLaunchLocation());
	}
		// Cache Launch Direction
	const bool UseCachedLaunchDirection = !PrjWeaponData->GetProjectilesPerShotParams().GetbCurrentLaunchDirection();
	CS_COROUTINE_PAYLOAD_PASS_FLAG(UseCachedLaunchDirection);

	if (UseCachedLaunchDirection)
	{
		CS_COROUTINE_PAYLOAD_PASS_VECTOR(ProjectileImpl->GetLaunchDirection());
	}

	// Spread
	if (UseSpreadParams())
	{
		using SpreadParamsType = NCsWeapon::NProjectile::NSpread::FParams;
		using SpreadShapeParamsType = NCsWeapon::NProjectile::NSpread::NShape::FParams;
		using SpreadAngleParamsType = NCsWeapon::NProjectile::NSpread::NAngle::FParams;
		using SpreadVariablesLibrary = NCsWeapon::NManager::NSpread::NVariables::FLibrary;
		using SpreadVariablesResourceType = NCsWeapon::NProjectile::NSpread::NVariables::FResource;
		using SpreadVariablesType = NCsWeapon::NProjectile::NSpread::NVariables::FVariables;

		const SpreadParamsType& SpreadParams = PrjWeaponData->GetSpreadParams();

		CS_IS_VALID_CHECKED(SpreadParams);

		SpreadVariablesResourceType* Resource = nullptr;

		// Shape
		if (SpreadParams.GetbShape())
		{
			const SpreadShapeParamsType& ShapeParams = SpreadParams.GetShapeParams();

			if (ShapeParams.ShouldPrecalculate())
			{
				// TODO:
				CS_COROUTINE_PAYLOAD_PASS_FLAG(false);
			}
			else
			{
				CS_COROUTINE_PAYLOAD_PASS_FLAG(true);
			}
		}
		else
		{
			CS_COROUTINE_PAYLOAD_PASS_FLAG(false);
		}
		// Yaw
		if (SpreadParams.GetbYaw())
		{
			const SpreadAngleParamsType& YawParams = SpreadParams.GetYawParams();

			if (YawParams.ShouldPrecalculate())
			{
				Resource					   = SpreadVariablesLibrary::Allocate(Context, GetWorldContext());
				SpreadVariablesType* Variables = Resource->Get();

				Variables->SetSizeAndAddDefaulted(ProjectilesPerShot);
				YawParams.SetAnglesChecked(Context, ProjectilesPerShot, Variables->Yaws);

				CS_COROUTINE_PAYLOAD_PASS_FLAG(false);
			}
			else
			{
				CS_COROUTINE_PAYLOAD_PASS_FLAG(true);
			}
		}
		else
		{
			CS_COROUTINE_PAYLOAD_PASS_FLAG(false);
		}
		// Pitch
		if (SpreadParams.GetbPitch())
		{
			const SpreadAngleParamsType& PitchParams = SpreadParams.GetPitchParams();

			if (PitchParams.ShouldPrecalculate())
			{
				if (!Resource)
				{
					Resource = SpreadVariablesLibrary::Allocate(Context, GetWorldContext());
				}
				SpreadVariablesType* Variables = Resource->Get();

				Variables->SetSizeAndAddDefaulted(ProjectilesPerShot);
				PitchParams.SetAnglesChecked(Context, ProjectilesPerShot, Variables->Pitches);

				CS_COROUTINE_PAYLOAD_PASS_FLAG(false);
			}
			else
			{
				CS_COROUTINE_PAYLOAD_PASS_FLAG(true);
			}
		}
		else
		{
			CS_COROUTINE_PAYLOAD_PASS_FLAG(false);
		}

		if (Resource)
		{
			CS_COROUTINE_PAYLOAD_PASS_VOID(Resource);
		}
	}
	else
	{
		// Shape
		CS_COROUTINE_PAYLOAD_PASS_FLAG(false);
		// Yaw
		CS_COROUTINE_PAYLOAD_PASS_FLAG(false);
		// Pitch
		CS_COROUTINE_PAYLOAD_PASS_FLAG(false);
	}

	bHasFired = true;

	static const int32 START = -1;

	SoundImpl->Play(START);

	LaunchPayloadType LaunchPayload;

	FXImpl->Play(START, LaunchPayload);

	FCsRoutineHandle Handle = CS_COROUTINE_START(GetWorldContext());

	if (Handle.IsValid())
		FireHandles.Add(Handle);
}

void ACsProjectileWeaponActorPooled::Fire_PreStart(const uint32& FireID)
{
}

char ACsProjectileWeaponActorPooled::Fire_Internal(FCsRoutine* R)
{
	CS_SET_CONTEXT_AS_FUNCTION_NAME(Fire_Internal);

	CS_COROUTINE_READ_UNSIGNED_INT_START
	CS_COROUTINE_READ_FLAG_START
	CS_COROUTINE_READ_INT_START
	CS_COROUTINE_READ_FLOAT_START
	CS_COROUTINE_READ_VECTOR_START
	CS_COROUTINE_READ_VECTOR3F_START
	CS_COROUTINE_READ_VOID_START
	CS_COROUTINE_READ_DELTA_TIME_START

	CS_COROUTINE_READ_UNSIGNED_INT_CONST_REF(R, FireID);

	// bInfiniteAmmo
	CS_COROUTINE_READ_FLAG_CONST_REF(R, bInfiniteAmmo);
	// ProjectilesPerShot
	CS_COROUTINE_READ_INT_CONST_REF(R, ProjectilesPerShot);
		// ProjectilesPerShot.Interval
	CS_COROUTINE_READ_FLOAT_CONST_REF(R, ProjectilesPerShot_Interval);

	CS_COROUTINE_READ_INT_REF(R, CurrentProjectilePerShotIndex);
		// bLaunchLocation
	CS_COROUTINE_READ_FLAG_CONST_REF(R, UseCachedLaunchLocation);
	CS_COROUTINE_READ_VECTOR_CONST_REF(R, CachedLaunchLocation);
		// bLaunchDirection
	CS_COROUTINE_READ_FLAG_CONST_REF(R, UseCachedLaunchDirection);
	CS_COROUTINE_READ_VECTOR_CONST_REF(R, CachedLaunchDirection);

	// Spread
	using SpreadParamsType = NCsWeapon::NProjectile::NSpread::FParams;
	using SpreadVariablesResourceType = NCsWeapon::NProjectile::NSpread::NVariables::FResource;
	using SpreadVariablesType = NCsWeapon::NProjectile::NSpread::NVariables::FVariables;

	static const int32 SPREAD_VARIABLES_RESOURCE = 0;
	SpreadVariablesResourceType* SpreadVariablesResource = R->GetValue_Void<SpreadVariablesResourceType>(SPREAD_VARIABLES_RESOURCE);
	SpreadVariablesType* SpreadVariables				 = SpreadVariablesResource ? SpreadVariablesResource->Get() : nullptr;

	CS_COROUTINE_READ_INT_REF(R, SpreadIndex);
		// Shape
	CS_COROUTINE_READ_FLAG_CONST_REF(R, IsSpreadShapeRandom);
		// Yaw
	CS_COROUTINE_READ_FLAG_CONST_REF(R, IsSpreadYawRandom);
		// Pitch
	CS_COROUTINE_READ_FLAG_CONST_REF(R, IsSpreadPitchRandom);

	CS_COROUTINE_READ_DELTA_TIME_REF(R, ElapsedTime);

	ElapsedTime += R->GetDeltaTime();
	
	CS_COROUTINE_BEGIN(R);

	++FireCount;

	do 
	{
		{
			CS_SET_SCOPED_TIMER_HANDLE(FireScopedHandle)

			ElapsedTime.Reset();

			Fire_PreShot(FireID);
			OnFire_PreShot_Event.Broadcast(this, FireID, CurrentProjectilePerShotIndex);

			if (!bInfiniteAmmo)
				ConsumeAmmo();

			{
				LaunchPayloadType LaunchPayload;

				// ProjectilesPerShot

				if (UseCachedLaunchLocation)
				{
					LaunchPayload.Shot.SetCachedLocation(CachedLaunchLocation);
				}

				if (UseCachedLaunchDirection)
				{
					LaunchPayload.Shot.SetCachedDirection(CachedLaunchDirection);
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
					LaunchPayload.bSpread = true;

					const SpreadParamsType& SpreadParams = PrjWeaponData->GetSpreadParams();

					LaunchPayload.Spread.SetOffset(SpreadParams.GetShapeParams().GetRandomOffsetChecked(Context));
					LaunchPayload.Spread.Axis = (int32)SpreadParams.GetShapeParams().GetAxis();
				}
					// Yaw
				if (IsSpreadYawRandom)
				{
					LaunchPayload.bSpread = true;

					const SpreadParamsType& SpreadParams = PrjWeaponData->GetSpreadParams();

					LaunchPayload.Spread.SetYaw(SpreadParams.GetYawParams().GetRandomAngleChecked(Context));
				}
					// Pitch
				if (IsSpreadPitchRandom)
				{
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

			CS_UPDATE_SCOPED_TIMER_HANDLE(FireScopedHandle)
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

float ACsProjectileWeaponActorPooled::GetTimeBetweenShots() const
{ 
	using namespace NCsProjectileWeaponActorPooled::NCached;

	const FString& Context = Str::GetTimeBetweenShots;

	typedef NCsWeapon::NModifier::IModifier ModifierType;

	static TArray<ModifierType*> Modifiers;
	Modifiers.Reset(Modifiers.Max());

	GetWeaponModifiers(Modifiers);

	float Value = TimeBetweenShotsImpl->GetValue();

	// TODO: Priority
	return CsWeaponModifierLibrary::ModifyFloatChecked(Context, Modifiers, NCsWeaponModifier::PrjWp_TimeBetweenShots, Value);
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
	return CsWeaponModifierLibrary::ModifyIntChecked(Context, Modifiers, NCsWeaponModifier::PrjWp_ProjectilesPerShot_Count, Value);
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
	return CsWeaponModifierLibrary::ModifyFloatChecked(Context, Modifiers, NCsWeaponModifier::PrjWp_ProjectilesPerShot_Interval, Value);
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

	return CsWeaponModifierLibrary::ToggleChecked(Context, Modifiers, NCsWeaponModifier::PrjWp_UseSpreadParams);
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

	if (SoundDataType* SoundData = CsWeaponDataLibrary::GetSafeInterfaceChecked<SoundDataType>(Context, Outer->GetData()))
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

void ACsProjectileWeaponActorPooled::FFXImpl::Play(const int32 CurrentProjectilePerShotIndex, const LaunchPayloadType& LaunchPayload)
{
	using namespace NCsProjectileWeaponActorPooled::NCached::NFXImpl;

	const FString& Context = Str::Play;

	// FXDataType (NCsWeapon::NProjectile::NData::NVisual::NFire::IFire)
	typedef NCsWeapon::NProjectile::NData::NVisual::NFire::IFire FXDataType;

	if (FXDataType* FXData = CsWeaponDataLibrary::GetSafeInterfaceChecked<FXDataType>(Context, Outer->GetData()))
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
				CsFXPayloadType* Payload = Manager_FX->AllocatePayload(FX.Type);
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
					CsFXPayloadType* Payload = Manager_FX->AllocatePayload(FX.Type);
					// Set appropriate values on payload
					SetPayload(CurrentProjectilePerShotIndex, Payload, FX, LaunchPayload);
					SetPayload(CurrentProjectilePerShotIndex, Payload, FXData);

					Manager_FX->Spawn(FX.Type, Payload);
				}
			}
		}
	}
}

void ACsProjectileWeaponActorPooled::FFXImpl::SetPayload(const int32 CurrentProjectilePerShotIndex, CsFXPayloadType* Payload, const FCsFX& FX, const LaunchPayloadType& LaunchPayload)
{
	using namespace NCsProjectileWeaponActorPooled::NCached::NFXImpl;

	const FString& Context = Str::SetPayload;

	FXPayloadImplType* PayloadImpl = CsFXPayloadLibrary::PureStaticCastChecked<FXPayloadImplType>(Context, Payload);

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

	FXDataType* FXData = CsWeaponDataLibrary::GetInterfaceChecked<FXDataType>(Context, Outer->GetData());

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
		const FVector Location = Outer->ProjectileImpl->GetLaunchLocation(LaunchPayload);
		PayloadImpl->Transform.SetTranslation(Location);

		const FVector Direction = Outer->ProjectileImpl->GetLaunchDirection(LaunchPayload);
		FQuat Rotation		    = FX.Transform.GetRotation();
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
		checkf(0, TEXT("%s: AttachType::Custom is NOT implemented."), *Context);
	}
}

void ACsProjectileWeaponActorPooled::FFXImpl::SetPayload(const int32 CurrentProjectilePerShotIndex, CsFXPayloadType* Payload, FXDataType* FXData)
{
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

	FXPayloadImplType* PayloadImpl = CsFXPayloadLibrary::PureStaticCastChecked<FXPayloadImplType>(Context, Payload);

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
		checkf(0, TEXT("%s: AttachType::Custom is NOT implemented."), *Context);
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