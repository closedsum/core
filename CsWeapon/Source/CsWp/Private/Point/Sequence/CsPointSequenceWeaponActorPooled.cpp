#include "Point/Sequence/CsPointSequenceWeaponActorPooled.h"
#include "CsWp.h"

// CVar
#include "Point/Sequence/CsCVars_PointSequenceWeapon.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Managers/Time/CsLibrary_Manager_Time.h"
#include "Managers/Trace/CsLibrary_Manager_Trace.h"
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
#include "Managers/Sound/CsLibrary_Manager_Sound.h"
#include "Managers/FX/Actor/CsLibrary_Manager_FX.h"
	// Data
#include "Data/CsLibrary_Data_Weapon.h"
	// Payload
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
#include "Managers/Sound/Payload/CsLibrary_Payload_Sound.h"
#include "Managers/FX/Payload/CsLibrary_Payload_FX.h"
	// Modifier
#include "Modifier/CsLibrary_WeaponModifier.h"
	// Common
#include "Camera/CsLibrary_Camera.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_DataType.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsWeaponSettings.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
#include "Managers/Sound/CsManager_Sound.h"
#include "Managers/FX/Actor/CsManager_FX.h"
#include "Managers/Trace/CsManager_Trace.h"
// Data
#include "Data/CsData_Weapon.h"
#include "Point/Sequence/Data/CsData_PointSequenceWeapon.h"
#include "Point/Sequence/Data/Sound/Fire/CsData_PointSequenceWeapon_SoundFire.h"
#include "Point/Sequence/Data/Visual/Fire/CsData_PointSequenceWeapon_VisualFire.h"
// Containers
#include "Containers/CsInterfaceMap.h"
// Pooled
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Weapon
#include "Payload/CsPayload_WeaponImpl.h"
#include "Cache/CsCache_WeaponImpl.h"
#include "Modifier/Types/CsGetWeaponModifierType.h"
// Modifier
#include "CsModifier_Int.h"
#include "CsModifier_Float.h"
#include "CsModifier_Toggle.h"
// Sound
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"
// FX
#include "Managers/FX/Payload/CsPayload_FXImpl.h"
#include "Managers/FX/Params/CsParams_FX.h"
// Component
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
// Animation
#include "Animation/AnimInstance.h"

#if WITH_EDITOR
// Library
	// Common
#include "Library/CsLibrary_World.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsPointSequenceWeaponActorPooled)

// Cached 
#pragma region

namespace NCsPointSequenceWeaponActorPooled
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled, SetUpdateGroup);
			CS_DEFINE_CACHED_STRING(Group, "Group");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled, Allocate);

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled, SetWeaponType);
			CS_DEFINE_CACHED_STRING(Type, "Type");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled, Init);
			CS_DEFINE_CACHED_STRING(UpdateGroup, "UpdateGroup");
			CS_DEFINE_CACHED_STRING(WeaponType, "WeaponType");
			CS_DEFINE_CACHED_STRING(IdleState, "IdleState");
			CS_DEFINE_CACHED_STRING(FireState, "FireState");

			// AActor Interface
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled, PostInitializeComponents);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled, OnUpdate_HandleStates);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled, CanFire);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled, Fire);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled, Fire_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled, Fire_Internal_OnEnd);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled, GetTimeBetweenShots);
			// Point
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled, Sequence_GetCount);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled, Sequence_GetInterval);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled, SequencesPerShot_GetCount);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled, SequencesPerShot_GetInterval);
		}

		namespace Name
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(ACsPointSequenceWeaponActorPooled, Fire_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(ACsPointSequenceWeaponActorPooled, Abort_Fire_Internal);
		}

		namespace NTimeBetweenShotsImpl
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled::FTimeBetweenShotsImpl, OnElapsedTime);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled::FTimeBetweenShotsImpl, OnElapsedTime_Internal);
			}

			namespace Name
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(ACsPointSequenceWeaponActorPooled::FTimeBetweenShotsImpl, OnElapsedTime_Internal);
			}
		}

		namespace NSoundImpl
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled::FSoundImpl, Play);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled::FSoundImpl, SetPayload);
			}
		}

		namespace NFXImpl
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled::FFXImpl, Play);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsPointSequenceWeaponActorPooled::FFXImpl, SetPayload);
			}
		}
	}
}

#pragma endregion Cached

ACsPointSequenceWeaponActorPooled::ACsPointSequenceWeaponActorPooled(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	// ICsUpdate
	UpdateGroup(),
	// Shutdown
	bShutdown(false),
	// ICsPooledObject
	Cache(nullptr),
	WeaponType(),
	Data(nullptr),
	PointSequenceWeaponData(nullptr),
	// Events
	OnAllocate_Event(),
	OnDeallocate_Start_Event(),
	OnHit_Event(),
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
	// Sound
	SoundImpl(nullptr),
	// FX
	FXImpl(nullptr)
{
	// StaticMeshComponent
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
using CsFXPayloadType = NCsFX::NPayload::IPayload;
using CacheImplType = NCsWeapon::NCache::NImpl::FImpl;
using FXDataType = NCsWeapon::NPoint::NSequence::NData::NVisual::NFire::IFire;

// UObject Interface
#pragma region

void ACsPointSequenceWeaponActorPooled::BeginDestroy()
{
	Super::BeginDestroy();
	
	Shutdown();
}

#pragma endregion UObject Interface

// AActor Interface
#pragma region

void ACsPointSequenceWeaponActorPooled::BeginPlay()
{
	Super::BeginPlay();

	SkeletalMeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);

	ConstructCache();

	PointImpl.Outer = this;

	TimeBetweenShotsImpl.Outer = this;

	SoundImpl = ConstructSoundImpl();
	SoundImpl->Weapon = this;

	FXImpl = ConstructFXImpl();
	FXImpl->Outer = this;

	// ScopedHandles
#if !UE_BUILD_SHIPPING
	{
		using namespace NCsPointSequenceWeaponActorPooled::NCached;

		// FireScopedHandle
		{
			const FString& ScopeName		   = Str::Fire_Internal;
			const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponPointSequence;
			const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponPointSequenceScopedTimerFire;

			FireScopedHandle.Handle = FCsManager_ScopedTimer::Get().GetHandle(&ScopeName, ScopedGroup, ScopeLog);
		}
	}
#endif // #if !UE_BUILD_SHIPPING
}

void ACsPointSequenceWeaponActorPooled::PostInitializeComponents()
{
	using namespace NCsPointSequenceWeaponActorPooled::NCached;

	const FString& Context = Str::PostInitializeComponents;

	Super::PostInitializeComponents();

#if WITH_EDITOR
	if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(this))
	{
		SkeletalMeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);

		ConstructCache();

		PointImpl.Outer = this;

		TimeBetweenShotsImpl.Outer = this;

		SoundImpl = ConstructSoundImpl();
		SoundImpl->Weapon = this;

		FXImpl = ConstructFXImpl();
		FXImpl->Outer = this;
	}
#endif // #if WITH_EDITOR
}

#pragma endregion AActor Interface

// ICsUpdate
#pragma region

void ACsPointSequenceWeaponActorPooled::Update(const FCsDeltaTime& DeltaTime)
{ 
	OnUpdate_HandleStates(DeltaTime);
}

#pragma endregion ICsUpdate

// Update
#pragma region

void ACsPointSequenceWeaponActorPooled::SetUpdateGroup(const FECsUpdateGroup& Group)
{
	using namespace NCsPointSequenceWeaponActorPooled::NCached;

	const FString& Context = Str::SetUpdateGroup;

	check(EMCsUpdateGroup::Get().IsValidEnumChecked(Context, Str::Group, Group));

	UpdateGroup = Group;
}

#pragma endregion Update

// ICsShutdown
#pragma region

void ACsPointSequenceWeaponActorPooled::Shutdown()
{
	CS_SAFE_DELETE_PTR(Cache)

	CS_SILENT_CLEAR_SCOPED_TIMER_HANDLE(FireScopedHandle.Handle)

	CS_SAFE_DELETE_PTR(SoundImpl)
	CS_SAFE_DELETE_PTR(FXImpl)

	bShutdown = true;
}

#pragma endregion ICsShutdown

// ICsPooledObject
#pragma region

void ACsPointSequenceWeaponActorPooled::Allocate(PooledPayloadType* Payload)
{
	using namespace NCsPointSequenceWeaponActorPooled::NCached;

	const FString& Context = Str::Allocate;

	CS_IS_PTR_NULL_CHECKED(Payload)

	Cache->Allocate(Payload);

	PayloadType* WeaponPayload = PooledPayloadLibrary::GetInterfaceChecked<PayloadType>(Context, Payload);

	SetWeaponType(WeaponPayload->GetType());
	SetUpdateGroup(WeaponPayload->GetUpdateGroup());

	MyOwner		   = Payload->GetOwner();
	MyOwnerAsActor = Cast<AActor>(MyOwner);

	// Get Data
	typedef NCsWeapon::NPoint::NSequence::NData::IData PointSequenceWeaponDataType;

	Data					= CsWeaponManagerLibrary::GetDataChecked(Context, GetWorldContext(), WeaponType);
	PointSequenceWeaponData = CsWeaponDataLibrary::GetInterfaceChecked<PointSequenceWeaponDataType>(Context, Data);

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
	const FCsWeaponSettings_PointSequenceWeaponImpl& Settings = FCsWeaponSettings_PointSequenceWeaponImpl::Get();

	CS_IS_VALID_CHECKED(Settings);

	IdleState = Settings.IdleState;
	FireState	 = Settings.FireState;
	CurrentState = IdleState;

	CurrentAmmo = PointSequenceWeaponData->GetMaxAmmo();

	OnAllocate_Event.Broadcast(this, Payload);
}

void ACsPointSequenceWeaponActorPooled::Deallocate()
{
	OnDeallocate_Start_Event.Broadcast(this);

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
	PointSequenceWeaponData = nullptr;

	MyOwner = nullptr;
	MyOwnerAsActor = nullptr;

	CurrentState = IdleState;

	CurrentAmmo = 0;
	
	bHasFired = false;
	bFire = false;
	bFire_Last = false;
	Fire_StartTime = 0.0f;
	FireCount = 0;
	
	//ProjectileImpl->Reset();

	// bOverride_ProjectileImpl_GetLaunchDirection = false;

	OnConsumeAmmo_Event.Clear();
	OnFire_PreStart_Event.Clear();
	OnFire_PreShot_Event.Clear();
	OnFire_End_Event.Clear();

	TimeBetweenShotsImpl.Clear();

	Cache->Deallocate();
}

#pragma endregion ICsPooledObject

// PooledObject
#pragma region

void ACsPointSequenceWeaponActorPooled::ConstructCache()
{
	Cache = new CacheImplType();
}

#pragma endregion PooledObject

void ACsPointSequenceWeaponActorPooled::SetWeaponType(const FECsWeapon& Type)
{
	using namespace NCsPointSequenceWeaponActorPooled::NCached;

	const FString& Context = Str::SetWeaponType;

	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeapon, Type);

	WeaponType = Type;
}

// ICsWeapon
#pragma region

#pragma endregion ICsWeapon

// ICsPointSequenceWeapon
#pragma region

void ACsPointSequenceWeaponActorPooled::StartFire()
{
	bFire = true;

	Update(FCsDeltaTime::Zero);
}

void ACsPointSequenceWeaponActorPooled::StopFire()
{
	bFire = false;

	Update(FCsDeltaTime::Zero);
}

#pragma endregion ICsPointSequenceWeapon

#if WITH_EDITOR

const UObject* ACsPointSequenceWeaponActorPooled::GetWorldContext() const
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

void ACsPointSequenceWeaponActorPooled::OnUpdate_HandleStates(const FCsDeltaTime& DeltaTime)
{
	using namespace NCsPointSequenceWeaponActorPooled::NCached;

	const FString& Context = Str::OnUpdate_HandleStates;

	const FCsDeltaTime& TimeSinceStart = CsTimeManagerLibrary::GetTimeSinceStartChecked(Context, GetWorldContext(), UpdateGroup);

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogWeaponPointSequenceState))
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
			if (CS_CVAR_LOG_IS_SHOWING(LogWeaponPointSequenceStateTransition))
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
			if (CS_CVAR_LOG_IS_SHOWING(LogWeaponPointSequenceStateTransition))
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

void ACsPointSequenceWeaponActorPooled::ConsumeAmmo()
{
	int32 PreviousAmmo = CurrentAmmo;
	--CurrentAmmo;

	OnConsumeAmmo_Event.Broadcast(this, PreviousAmmo, CurrentAmmo);
}

#pragma endregion Ammo

// Fire
#pragma region

bool ACsPointSequenceWeaponActorPooled::CanFire() const
{
	using namespace NCsPointSequenceWeaponActorPooled::NCached;

	const FString& Context = Str::CanFire;
	
	const FCsDeltaTime& TimeSinceStart = CsTimeManagerLibrary::GetTimeSinceStartChecked(Context, GetWorldContext(), UpdateGroup);

	const float TimeBetweenShots = GetTimeBetweenShots();

	// Check if enough time has elapsed to fire again.
	const bool Pass_Time = !bHasFired || (TimeSinceStart.Time - Fire_StartTime > TimeBetweenShots);
	// Check if bFire is set, its not on release, and its either bFire is just set or FullAuto.
	const bool Pass_Fire = bFire && !PointSequenceWeaponData->DoFireOnRelease() && (PointSequenceWeaponData->IsFullAuto() || !bFire_Last);
	// Check if bFire has just been unset and on release.
	const bool Pass_FireOnRelease = !bFire && PointSequenceWeaponData->DoFireOnRelease() && bFire_Last;
	// Check if has ammo to fire.
	const bool Pass_Ammo = PointSequenceWeaponData->HasInfiniteAmmo() || CurrentAmmo > 0;
	// Check if Destination is Valid.
	const bool Pass_Destination = PointImpl.HasValidDestination();

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogWeaponPointSequenceCanFire))
	{
		const TCHAR*(*ToChar)(const bool& Value) = &CsDataTypeLibrary::ToChar;

		UE_LOG(LogCsWp, Warning, TEXT("%s"), *Context);
		// Pass_Time
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_Time (%s): %f - %f > %f"), ToChar(Pass_Time), TimeSinceStart.Time, Fire_StartTime, TimeBetweenShots);
		// Pass_Fire
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_Fire (%s): %s && %s && (%s || %s)"), ToChar(Pass_Fire), ToChar(bFire), ToChar(!PointSequenceWeaponData->DoFireOnRelease()), ToChar(PointSequenceWeaponData->IsFullAuto()), ToChar(!bFire_Last));
		// Pass_FireOnRelease
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_FireOnRelease (%s): %s && %s && %s"), ToChar(Pass_FireOnRelease), ToChar(!bFire), ToChar(PointSequenceWeaponData->DoFireOnRelease()), ToChar(bFire_Last));
		// Pass_Ammo
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_Ammo (%s): %s || %s"), ToChar(Pass_Ammo), ToChar(PointSequenceWeaponData->HasInfiniteAmmo()), ToChar(CurrentAmmo > 0));
		// Pass_Destination
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_Destination (%s)"), ToChar(Pass_Destination));

		// Result
		UE_LOG(LogCsWp, Warning, TEXT(" Result (%s): %s && (%s || %s) && %s %% %s"), ToChar(Pass_Time && (Pass_Fire || Pass_FireOnRelease) && Pass_Ammo), ToChar(Pass_Time), ToChar(Pass_Fire), ToChar(Pass_FireOnRelease), ToChar(Pass_Ammo), ToChar(Pass_Destination));
	}
#endif // #if !UE_BUILD_SHIPPING

	return Pass_Time && (Pass_Fire || Pass_FireOnRelease) && Pass_Ammo && Pass_Destination;
}

void ACsPointSequenceWeaponActorPooled::Fire()
{
	using namespace NCsPointSequenceWeaponActorPooled::NCached;

	const FString& Context = Str::Fire;

	UCsCoroutineScheduler* Scheduler   = CsCoroutineSchedulerLibrary::GetChecked(Context, GetWorldContext());
	const FCsDeltaTime& TimeSinceStart = CsTimeManagerLibrary::GetTimeSinceStartChecked(Context, GetWorldContext(), UpdateGroup);

	Fire_StartTime = TimeSinceStart.Time;

	// Setup Fire Routine
	typedef NCsCoroutine::NPayload::FImpl CoroutinePayloadType;

	CoroutinePayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

	#define COROUTINE Fire_Internal

	Payload->CoroutineImpl.BindUObject(this, &ACsPointSequenceWeaponActorPooled::COROUTINE);
	Payload->StartTime = CsTimeManagerLibrary::GetTimeChecked(Context, GetWorldContext(), UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);
	Payload->OnEnds.AddDefaulted();
	Payload->OnEnds.Last().BindUObject(this, &ACsPointSequenceWeaponActorPooled::Fire_Internal_OnEnd);
	Payload->AbortMessages.Add(Name::Abort_Fire_Internal);

	#undef COROUTINE

	const FGuid FireGuid = FGuid::NewGuid();
	uint32 FireID		 = GetTypeHash(FireGuid);

	FireIDs.Add(FireID);

	static const int32 FIRE_ID = 0;
	Payload->SetValue_UnsignedInt(FIRE_ID, FireID);

	Fire_PreStart(FireID);
	OnFire_PreStart_Event.Broadcast(this, FireID);

	Payload->SetValue_Flag(CS_FIRST, PointSequenceWeaponData->HasInfiniteAmmo());

	// SequencesPerShot
	static const int32 SEQUENCES_PER_SHOT = 0;
	int32 SequencesPerShot = SequencesPerShot_GetCount();
	Payload->SetValue_Int(SEQUENCES_PER_SHOT, SequencesPerShot);

	static const int32 SEQUENCES_PER_SHOT_INTERVAL = 0;
	Payload->SetValue_Float(SEQUENCES_PER_SHOT_INTERVAL, SequencesPerShot_GetInterval());

	bHasFired = true;

	FCsRoutineHandle Handle = Scheduler->Start(Payload);

	if (Handle.IsValid())
		FireHandles.Add(Handle);
}

void ACsPointSequenceWeaponActorPooled::Fire_PreStart(const uint32& FireID)
{
}

char ACsPointSequenceWeaponActorPooled::Fire_Internal(FCsRoutine* R)
{
	using namespace NCsPointSequenceWeaponActorPooled::NCached;

	const FString& Context = Str::Fire_Internal;

	static const int32 FIRE_ID = 0;
	const uint32& FireID = R->GetValue_UnsignedInt(FIRE_ID);

	// bInfiniteAmmo
	const bool& bInfiniteAmmo = R->GetValue_Flag(CS_FIRST);
	// SequencesPerShot
	static const int32 SEQUENCES_PER_SHOT = 0;
	const int32& SequencesPerShot = R->GetValue_Int(SEQUENCES_PER_SHOT);
		// SequencesPerShot.Interval
	static const int32 SEQUENCES_PER_SHOT_INTERVAL = 0;
	const float& SequencesPerShot_Interval = R->GetValue_Float(SEQUENCES_PER_SHOT_INTERVAL);

	static const int32 CURRENT_SEQUENCE_PER_SHOT_INDEX = 1;
	int32& CurrentSequencePerShotIndex = R->GetValue_Int(CURRENT_SEQUENCE_PER_SHOT_INDEX);

	FCsDeltaTime& ElapsedTime = R->GetValue_DeltaTime(CS_FIRST);

	ElapsedTime += R->GetDeltaTime();
	
	CS_COROUTINE_BEGIN(R);

	++FireCount;

	do 
	{
		{
			CS_SET_SCOPED_TIMER_HANDLE(FireScopedHandle)

			ElapsedTime.Reset();

			Fire_PreShot(FireID);
			OnFire_PreShot_Event.Broadcast(this, FireID, CurrentSequencePerShotIndex);

			if (!bInfiniteAmmo)
				ConsumeAmmo();

			{
				//ProjectileImpl->Launch(LaunchPayload);
				Sequence_Execute(CurrentSequencePerShotIndex);
				SoundImpl->Play();
				FXImpl->Play();
			}

			// Increment the shot index
			CurrentSequencePerShotIndex = FMath::Min(CurrentSequencePerShotIndex + 1, SequencesPerShot);

			// Check if more points should be fired, if so wait
			if (CurrentSequencePerShotIndex < SequencesPerShot)
			{
				CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= SequencesPerShot_Interval);
			}

			CS_UPDATE_SCOPED_TIMER_HANDLE(FireScopedHandle)
		}
	} while (CurrentSequencePerShotIndex < SequencesPerShot);

	CS_COROUTINE_END(R);
}

void ACsPointSequenceWeaponActorPooled::Fire_PreShot(const uint32& FireID)
{
}

void ACsPointSequenceWeaponActorPooled::Fire_Internal_OnEnd(FCsRoutine* R)
{
	using namespace NCsPointSequenceWeaponActorPooled::NCached;

	const FString& Context = Str::Fire_Internal_OnEnd;

	if (R->GetSafeOwnerAsObject())
	{
		OnFire_End_Event.Broadcast(this, R);

		static const int32 FIRE_ID = 0;
		const uint32& FireID = R->GetValue_UnsignedInt(FIRE_ID);

		FireIDs.Remove(FireID);
		--FireCount;
	}
}

void ACsPointSequenceWeaponActorPooled::FTimeBetweenShotsImpl::OnElapsedTime()
{
	using namespace NCsPointSequenceWeaponActorPooled::NCached::NTimeBetweenShotsImpl;

	const FString& Context = Str::OnElapsedTime;

	UCsCoroutineScheduler* Scheduler = CsCoroutineSchedulerLibrary::GetChecked(Context, Outer->GetWorldContext());

	// Setup Routine
	typedef NCsCoroutine::NPayload::FImpl CoroutinePayloadType;

	CoroutinePayloadType* Payload = Scheduler->AllocatePayload(Outer->GetUpdateGroup());

	#define COROUTINE OnElapsedTime_Internal

	Payload->CoroutineImpl.BindRaw(this, &ACsPointSequenceWeaponActorPooled::FTimeBetweenShotsImpl::COROUTINE);
	Payload->StartTime = CsTimeManagerLibrary::GetTimeChecked(Context, Outer->GetWorldContext(), Outer->GetUpdateGroup());
	Payload->Owner.SetObject(Outer);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);

	#undef COROUTINE

	static const int32 TIME_BETWEEN_SHOTS = 0;
	Payload->SetValue_Float(TIME_BETWEEN_SHOTS, Outer->GetTimeBetweenShots());

	Scheduler->Start(Payload);
}

char ACsPointSequenceWeaponActorPooled::FTimeBetweenShotsImpl::OnElapsedTime_Internal(FCsRoutine* R)
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

float ACsPointSequenceWeaponActorPooled::GetTimeBetweenShots() const
{ 
	using namespace NCsPointSequenceWeaponActorPooled::NCached;

	const FString& Context = Str::GetTimeBetweenShots;

	static TArray<CsWeaponModifierType*> Modifiers;

	GetWeaponModifiers(Modifiers);

	float Value = PointSequenceWeaponData->GetTimeBetweenShots();

	// TODO: Priority
	return CsWeaponModifierLibrary::ModifyFloatAndEmptyChecked(Context, Modifiers, NCsWeaponModifier::PointSeqWp_TimeBetweenShots, Value);
}

	// Point
#pragma region

int32 ACsPointSequenceWeaponActorPooled::Sequence_GetCount() const
{
	using namespace NCsPointSequenceWeaponActorPooled::NCached;

	const FString& Context = Str::Sequence_GetCount;

	static TArray<CsWeaponModifierType*> Modifiers;

	GetWeaponModifiers(Modifiers);

	float Value = PointSequenceWeaponData->GetSequenceParams().GetCount();

	// TODO: Priority
	return CsWeaponModifierLibrary::ModifyIntAndEmptyChecked(Context, Modifiers, NCsWeaponModifier::PointSeqWp_Sequence_Count, Value);
}

float ACsPointSequenceWeaponActorPooled::Sequence_GetInterval() const
{
	using namespace NCsPointSequenceWeaponActorPooled::NCached;

	const FString& Context = Str::SequencesPerShot_GetInterval;

	static TArray<CsWeaponModifierType*> Modifiers;

	GetWeaponModifiers(Modifiers);

	float Value = PointSequenceWeaponData->GetSequenceParams().GetInterval();

	// TODO: Priority
	return CsWeaponModifierLibrary::ModifyFloatAndEmptyChecked(Context, Modifiers, NCsWeaponModifier::PointSeqWp_Sequence_Interval, Value);
}

int32 ACsPointSequenceWeaponActorPooled::SequencesPerShot_GetCount() const
{
	using namespace NCsPointSequenceWeaponActorPooled::NCached;

	const FString& Context = Str::SequencesPerShot_GetCount;

	static TArray<CsWeaponModifierType*> Modifiers;

	GetWeaponModifiers(Modifiers);

	float Value = PointSequenceWeaponData->GetSequencesPerShotParams().GetCount();

	// TODO: Priority
	return CsWeaponModifierLibrary::ModifyIntAndEmptyChecked(Context, Modifiers, NCsWeaponModifier::PointSeqWp_SequencesPerShot_Count, Value);
}

float ACsPointSequenceWeaponActorPooled::SequencesPerShot_GetInterval() const
{
	using namespace NCsPointSequenceWeaponActorPooled::NCached;

	const FString& Context = Str::SequencesPerShot_GetInterval;

	static TArray<CsWeaponModifierType*> Modifiers;

	GetWeaponModifiers(Modifiers);

	float Value = PointSequenceWeaponData->GetSequencesPerShotParams().GetInterval();

	// TODO: Priority
	return CsWeaponModifierLibrary::ModifyFloatAndEmptyChecked(Context, Modifiers, NCsWeaponModifier::PointSeqWp_SequencesPerShot_Interval, Value);
}

void ACsPointSequenceWeaponActorPooled::Sequence_Execute(const int32& CurrentSequencePerShotIndex)
{
	checkf(0, TEXT("ACsPointSequenceWeaponActorPooled::Sequence_Execute:: NOT IMPLEMENTED."));
}

#pragma endregion Point

	// Sound
#pragma region

void ACsPointSequenceWeaponActorPooled::FSoundImpl::Play()
{
	using namespace NCsPointSequenceWeaponActorPooled::NCached::NSoundImpl;

	const FString& Context = Str::Play;

	// SoundDataType (NCsWeapon::NPoint::NSequence::NData::NSound::NFire::IFire)
	typedef NCsWeapon::NPoint::NSequence::NData::NSound::NFire::IFire SoundDataType;

	if (SoundDataType* SoundData = CsWeaponDataLibrary::GetSafeInterfaceChecked<SoundDataType>(Context, Weapon->GetData()))
	{
		if (SoundData->UseFireSoundParams())
		{
			typedef NCsWeapon::NPoint::NSequence::NFire::NSound::FParams ParamsType;

			const ParamsType& Params = SoundData->GetFireSoundParams();
			const FCsSound& Sound	 = Params.GetSound();

			typedef NCsPooledObject::NPayload::FImplSlice PayloadImplType;

			PayloadImplType Payload;
			Payload.Instigator = Weapon;
			Payload.Owner	   = Weapon->GetMyOwner();

			// TODO: Make sure Outer is defined
			CsSoundManagerLibrary::SpawnChecked(Context, Weapon, &Payload, Sound);
		}
	}
}

ACsPointSequenceWeaponActorPooled::FSoundImpl* ACsPointSequenceWeaponActorPooled::ConstructSoundImpl()
{
	return new ACsPointSequenceWeaponActorPooled::FSoundImpl();
}

#pragma endregion Sound

	// FX
#pragma region

void ACsPointSequenceWeaponActorPooled::FFXImpl::Play()
{
	using namespace NCsPointSequenceWeaponActorPooled::NCached::NFXImpl;

	const FString& Context = Str::Play;

	// FXDataType (NCsWeapon::NPoint::NSequence::NData::NVisual::NFire::IFire)
	typedef NCsWeapon::NPoint::NSequence::NData::NVisual::NFire::IFire FXDataType;

	if (FXDataType* FXData = CsWeaponDataLibrary::GetSafeInterfaceChecked<FXDataType>(Context, Outer->GetData()))
	{
		if (FXData->UseFireVisualParams())
		{
			typedef NCsWeapon::NPoint::NSequence::NFire::NVisual::FParams ParamsType;

			const ParamsType& Params = FXData->GetFireVisualParams();
			const FCsFX& FX			 = Params.GetFX();

			UNiagaraSystem* FXAsset = FX.GetChecked(Context);

			// Get Manager
			UCsManager_FX* Manager_FX = CsFXManagerLibrary::GetChecked(Context, Outer->GetWorldContext());
			// Allocate payload
			CsFXPayloadType* Payload = Manager_FX->AllocatePayload(FX.Type);
			// Set appropriate values on payload
			SetPayload(Payload, FXData);

			Manager_FX->Spawn(FX.Type, Payload);
		}
	}
}

void ACsPointSequenceWeaponActorPooled::FFXImpl::SetPayload(CsFXPayloadType* Payload, FXDataType* FXData)
{
	using namespace NCsPointSequenceWeaponActorPooled::NCached::NFXImpl;

	const FString& Context = Str::SetPayload;

	typedef NCsWeapon::NPoint::NSequence::NFire::NVisual::FParams ParamsType;
	typedef NCsWeapon::NPoint::NSequence::NFire::NVisual::EAttach AttachType;

	const ParamsType& Params = FXData->GetFireVisualParams();
	const FCsFX& FX			 = Params.GetFX();
	const AttachType& Type	 = Params.GetAttach();

	CsFXPayloadImplType* PayloadImpl = CsFXPayloadLibrary::PureStaticCastChecked<CsFXPayloadImplType>(Context, Payload);

	PayloadImpl->Instigator					= Outer;
	PayloadImpl->Owner						= Outer->GetMyOwner();
	PayloadImpl->FXSystem					= FX.GetChecked(Context);
	PayloadImpl->DeallocateMethod			= FX.GetDeallocateMethod();
	PayloadImpl->LifeTime					= FX.LifeTime;
	PayloadImpl->AttachmentTransformRules	= FX.AttachmentTransformRules;
	PayloadImpl->Bone						= FX.Bone;
	PayloadImpl->TransformRules				= FX.TransformRules;
	PayloadImpl->Transform					= FX.Transform;

	using ParamsLibrary = NCsFX::NManager::NParameter::FLibrary;

	// None
	if (Type == AttachType::None)
	{
		// Spawn Location
		FVector Location = CsMathLibrary::Convert(Params.GetbDestinationAsStart() ? Outer->PointImpl.Destination : Outer->PointImpl.Start);

		FTransform Transform  = PayloadImpl->Transform;
		FVector Translation   = Transform.GetTranslation();
		Translation			 += Location;

		Transform.SetTranslation(Translation);

		PayloadImpl->Transform = Transform;

		// Distance
		if (Params.GetbDistanceParameter())
		{
			using FloatParamsType = NCsFX::NParameter::NFloat::FFloatType;

			FloatParamsType* FloatParameter = ParamsLibrary::AllocateFloatChecked(Context, Outer->GetWorldContext());

			FloatParameter->SetName(Params.GetDistanceParameter());
			FloatParameter->SetValue(Outer->PointImpl.CalculateDistance());

			PayloadImpl->Parameters.Add(FloatParameter);
		}
		// Orientation
		if (Params.GetbOrientationParameter())
		{
			using VectorParamsType = NCsFX::NParameter::NVector::FVectorType;

			VectorParamsType* VectorParameter = ParamsLibrary::AllocateVectorChecked(Context, Outer->GetWorldContext());

			VectorParameter->SetName(Params.GetOrientationParameter());

			float DirectionScalar = Params.GetbDestinationAsStart() ? -1.0f : 1.0f;

			VectorParameter->SetValue(DirectionScalar * Outer->PointImpl.CalculateDirection());

			PayloadImpl->Parameters.Add(VectorParameter);
		}
	}
	// Owner
	else
	if (Type == AttachType::Owner)
	{
		PayloadImpl->Parent = Outer->GetMyOwner();

		// TODO: Distance Parameter

		// TODO: Orientation Parameter
	}
	// Component
	else
	if (Type == AttachType::Component)
	{
		PayloadImpl->Parent = Component;

		// TODO: Distance Parameter

		// TODO: Orientation Parameter
	}
	// Custom
	else
	{
		checkf(0, TEXT("%s: AttachType::Custom is NOT implemented."), *Context);
	}
}

ACsPointSequenceWeaponActorPooled::FFXImpl* ACsPointSequenceWeaponActorPooled::ConstructFXImpl()
{
	return new ACsPointSequenceWeaponActorPooled::FFXImpl();
}

void ACsPointSequenceWeaponActorPooled::FXImpl_SetComponent(USceneComponent* Component)
{
	FXImpl->SetComponent(Component);
}

#pragma endregion FX

#pragma endregion Fire

// Print
#pragma region

FString ACsPointSequenceWeaponActorPooled::PrintNameAndClass()
{
	return FString::Printf(TEXT("Weapon: %s with Class: %s"), *(GetName()), *(GetClass()->GetName()));
}

FString ACsPointSequenceWeaponActorPooled::PrintNameClassAndOwner()
{
	return FString::Printf(TEXT("Weapon: %s with Class: %s with MyOwner: %s"), *(GetName()), *(GetClass()->GetName()), *(MyOwner->GetName()));
}

#pragma endregion Print