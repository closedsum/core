#include "Projectile/CsProjectileWeaponComponent.h"
#include "CsWp.h"

// CVar
#include "Projectile/CsCVars_ProjectileWeapon.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "Types/CsCached.h"
// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
#include "Payload/CsLibrary_Payload_Projectile.h"
#include "Data/CsLibrary_Data_Weapon.h"
#include "Data/CsLibrary_Data_Projectile.h"
#include "Managers/Sound/Payload/CsLibrary_Payload_Sound.h"
#include "Managers/FX/Payload/CsLibrary_Payload_FX.h"
#include "Projectile/Params/Launch/CsLibrary_Params_ProjectileWeapon_Launch.h"
#include "Library/CsLibrary_Camera.h"
// Settings
#include "Settings/CsWeaponSettings.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
#include "Managers/Weapon/CsManager_Weapon.h"
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
#include "Data/CsData_ProjectileCollision.h"
// Containers
#include "Containers/CsInterfaceMap.h"
// Pooled
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Projectile
#include "Payload/CsPayload_ProjectilePooledImpl.h"
#include "Payload/CsPayload_ProjectileImplSlice.h"
#include "Managers/Projectile/CsProjectilePooledImpl.h"
// Sound
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"
// FX
#include "Managers/FX/Payload/CsPayload_FXImpl.h"
// Params
#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_LaunchTrace.h"
#include "Projectile/Data/Sound/CsParams_ProjectileWeapon_SoundFire.h"

// Cached 
#pragma region

namespace NCsProjectileWeaponComponent
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsProjectileWeaponComponent, Init);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsProjectileWeaponComponent, OnUpdate_HandleStates);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsProjectileWeaponComponent, CanFire);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsProjectileWeaponComponent, Fire);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsProjectileWeaponComponent, Fire_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsProjectileWeaponComponent, FireProjectile);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsProjectileWeaponComponent, SetProjectilePayload);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsProjectileWeaponComponent, LaunchProjectile);
		}

		namespace Name
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsProjectileWeaponComponent, Fire_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsProjectileWeaponComponent, Abort_Fire_Internal);
		}

		namespace TimeBetweenShotsImpl
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsProjectileWeaponComponent::FTimeBetweenShotsImpl, OnElapsedTime);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsProjectileWeaponComponent::FTimeBetweenShotsImpl, OnElapsedTime_Internal);
			}

			namespace Name
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsProjectileWeaponComponent::FTimeBetweenShotsImpl, OnElapsedTime_Internal);
			}
		}

		namespace ProjectileImpl
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsProjectileWeaponComponent::FProjectileImpl, GetLaunchLocation);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsProjectileWeaponComponent::FProjectileImpl, GetLaunchDirection);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsProjectileWeaponComponent::FProjectileImpl, StartLaunch);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsProjectileWeaponComponent::FProjectileImpl, Launch);
			}
		}

		namespace SoundImpl
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsProjectileWeaponComponent::FSoundImpl, Play);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsProjectileWeaponComponent::FSoundImpl, SetPayload);
			}
		}

		namespace FXImpl
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsProjectileWeaponComponent::FFXImpl, Play);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsProjectileWeaponComponent::FFXImpl, SetPayload);
			}
		}
	}
}

#pragma endregion Cached

UCsProjectileWeaponComponent::UCsProjectileWeaponComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	// ICsUpdate
	UpdateGroup(),
	WeaponType(),
	Data(nullptr),
	ProjectileType(),
	MyOwner(nullptr),
	MyOwnerAsActor(nullptr),
	// State
	CurrentState(),
	IdleState(),
	FireState(),
	// Ammo
	CurrentAmmo(0),
	// Fire
	bFire(false),
	bFire_Last(false),
	Fire_StartTime(0.0f),
	FireCount(0),
	FireRoutineHandle(),
	// Projectile
	CurrentProjectilePerShotIndex(0),
	ProjectileImpl(nullptr),
	// Sound
	SoundImpl(nullptr)
{
}

// UObject Interface
#pragma region

void UCsProjectileWeaponComponent::BeginDestroy()
{
	Super::BeginDestroy();

	if (ProjectileImpl)
	{
		delete ProjectileImpl;
		ProjectileImpl = nullptr;
	}
}

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region

void UCsProjectileWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	MyOwner		   = GetOwner();
	MyOwnerAsActor = GetOwner();

	TimeBetweenShotsImpl.Outer = this;

	ProjectileImpl = ConstructProjectileImpl();
	ProjectileImpl->Weapon = this;

	SoundImpl = ConstructSoundImpl();
	SoundImpl->Weapon = this;

	FXImpl = ConstructFXImpl();
	FXImpl->Weapon = this;
}

#pragma endregion UActorComponent Interface

// ICsUpdate
#pragma region

void UCsProjectileWeaponComponent::Update(const FCsDeltaTime& DeltaTime)
{ 
	OnUpdate_HandleStates(DeltaTime);
}

#pragma endregion ICsUpdate

void UCsProjectileWeaponComponent::SetUpdateGroup(const FECsUpdateGroup& Group)
{
	checkf(EMCsUpdateGroup::Get().IsValidEnum(Group), TEXT("UCsProjectileWeaponComponent::SetUpdateGroup: Group: %s is NOT Valid."), Group.ToChar());

	UpdateGroup = Group;
}

void UCsProjectileWeaponComponent::SetWeaponType(const FECsWeapon& Type)
{
	checkf(EMCsWeapon::Get().IsValidEnum(Type), TEXT("UCsProjectileWeaponComponent::SetWeaponType: Type: %s is NOT Valid."), Type.ToChar());

	WeaponType = Type;
}

// ICsWeapon
#pragma region

#pragma endregion ICsWeapon

void UCsProjectileWeaponComponent::SetProjectileType(const FECsProjectile& Type)
{
	checkf(EMCsProjectile::Get().IsValidEnum(Type), TEXT("UCsProjectileWeaponComponent::SetProjectileType: Type: %s is NOT Valid."), Type.ToChar());

	ProjectileType = Type;
}

// ICsProjectileWeapon
#pragma region

void UCsProjectileWeaponComponent::StartFire()
{
	bFire = true;

	Update(FCsDeltaTime::Zero);
}

void UCsProjectileWeaponComponent::StopFire()
{
	bFire = false;

	Update(FCsDeltaTime::Zero);
}

#pragma endregion ICsProjectileWeapon

void UCsProjectileWeaponComponent::Init()
{
	using namespace NCsProjectileWeaponComponent::NCached;

	const FString& Context = Str::Init;

	checkf(EMCsUpdateGroup::Get().IsValidEnum(UpdateGroup), TEXT("%s: UpdateGroup: %s is NOT Valid."), *Context, UpdateGroup.ToChar());

	checkf(EMCsWeapon::Get().IsValidEnum(WeaponType), TEXT("%s: WeaponType: %s is NOT Valid."), *Context, WeaponType.ToChar());

	// Get Data
	Data = UCsManager_Weapon::Get(GetWorld()->GetGameState())->GetData(WeaponType.GetFName());

	checkf(Data, TEXT("%s: Data is NULL. Failed to get Data of type: ICsData_Weapon for Weapon: %s"), *Context, WeaponType.ToChar());

	checkf(FCsLibrary_Data_Weapon::IsValidChecked(Context, Data), TEXT("%s: Data is NOT Valid."), *Context);

	checkf(EMCsProjectile::Get().IsValidEnum(ProjectileType), TEXT("%s: WeaponType: %s is NOT Valid."), *Context, ProjectileType.ToChar());

	// Set States
	UCsWeaponSettings* Settings = GetMutableDefault<UCsWeaponSettings>();

	IdleState = Settings->ProjectileWeaponImpl.IdleState;

	checkf(EMCsWeaponState::Get().IsValidEnum(IdleState), TEXT("%s: IdleState: %s is NOT Valid."), *Context, IdleState.ToChar());

	FireState = Settings->ProjectileWeaponImpl.FireState;

	checkf(EMCsWeaponState::Get().IsValidEnum(FireState), TEXT("%s: FireState: %s is NOT Valid."), *Context, FireState.ToChar());

	CurrentState = IdleState;

	// Ammo
	typedef NCsWeapon::NProjectile::NData::IData ProjectileDataType;

	ProjectileDataType* PrjData = FCsLibrary_Data_Weapon::GetInterfaceChecked<ProjectileDataType>(Context, Data);

	CurrentAmmo = PrjData->GetMaxAmmo();
}

// State
#pragma region

void UCsProjectileWeaponComponent::OnUpdate_HandleStates(const FCsDeltaTime& DeltaTime)
{
	using namespace NCsProjectileWeaponComponent::NCached;

	const FString& Context = Str::OnUpdate_HandleStates;

	const FCsDeltaTime& TimeSinceStart = UCsManager_Time::Get(GetWorld()->GetGameInstance())->GetTimeSinceStart(UpdateGroup);

#if !UE_BUILD_SHIPPING
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogWeaponProjectileState))
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
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogWeaponProjectileStateTransition))
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
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogWeaponProjectileStateTransition))
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

void UCsProjectileWeaponComponent::ConsumeAmmo()
{
	int32 PreviousAmmo = CurrentAmmo;
	--CurrentAmmo;

	OnConsumeAmmo_Event.Broadcast(this, PreviousAmmo, CurrentAmmo);
}

#pragma endregion Ammo

// Fire
#pragma region

bool UCsProjectileWeaponComponent::CanFire() const
{
	using namespace NCsProjectileWeaponComponent::NCached;

	const FString& Context = Str::CanFire;
	
	const FCsDeltaTime& TimeSinceStart = UCsManager_Time::Get(GetWorld()->GetGameInstance())->GetTimeSinceStart(UpdateGroup);

	typedef NCsWeapon::NProjectile::NData::IData ProjectileDataType;

	ProjectileDataType* PrjData = FCsLibrary_Data_Weapon::GetInterfaceChecked<ProjectileDataType>(Context, Data);

	// Check if enough time has elapsed to fire again.
	const bool Pass_Time = (TimeSinceStart.Time - Fire_StartTime > PrjData->GetTimeBetweenShots());
	// Check if bFire is set, its not on release, and its either bFire is just set or FullAuto.
	const bool Pass_Fire = bFire && !PrjData->DoFireOnRelease() && (PrjData->IsFullAuto() || !bFire_Last);
	// Check if bFire has just been unset and on release.
	const bool Pass_FireOnRelease = !bFire && PrjData->DoFireOnRelease() && bFire_Last;
	// Check if has ammo to fire.
	const bool Pass_Ammo = PrjData->HasInfiniteAmmo() || CurrentAmmo > 0;

#if !UE_BUILD_SHIPPING
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogWeaponProjectileCanFire))
	{
		using namespace NCsCached;

		UE_LOG(LogCsWp, Warning, TEXT("%s"), *Context);
		// Pass_Time
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_Time (%s): %f - %f > %f"), ToChar(Pass_Time), TimeSinceStart.Time, Fire_StartTime, PrjData->GetTimeBetweenShots());
		// Pass_Fire
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_Fire (%s): %s && %s && (%s || %s)"), ToChar(Pass_Fire), ToChar(bFire), ToChar(!PrjData->DoFireOnRelease()), ToChar(PrjData->IsFullAuto()), ToChar(!bFire_Last));
		// Pass_FireOnRelease
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_FireOnRelease (%s): %s && %s && %s"), ToChar(Pass_FireOnRelease), ToChar(!bFire), ToChar(PrjData->DoFireOnRelease()), ToChar(bFire_Last));
		// Pass_Ammo
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_Ammo (%s): %s || %s"), ToChar(Pass_Ammo), ToChar(PrjData->HasInfiniteAmmo()), ToChar(CurrentAmmo > 0));

		// Result
		UE_LOG(LogCsWp, Warning, TEXT(" Result (%s): %s && (%s || %s) && %s"), ToChar(Pass_Time && (Pass_Fire || Pass_FireOnRelease) && Pass_Ammo), ToChar(Pass_Time), ToChar(Pass_Fire), ToChar(Pass_FireOnRelease), ToChar(Pass_Ammo));
	}
#endif // #if !UE_BUILD_SHIPPING

	return Pass_Time && (Pass_Fire || Pass_FireOnRelease) && Pass_Ammo;
}

void UCsProjectileWeaponComponent::Fire()
{
	using namespace NCsProjectileWeaponComponent::NCached;

	const FString& Context = Str::Fire;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(GetWorld()->GetGameInstance());

	// End previous Fire Routine
	Scheduler->End(UpdateGroup, FireRoutineHandle);

	const FCsDeltaTime& TimeSinceStart = UCsManager_Time::Get(GetWorld()->GetGameInstance())->GetTimeSinceStart(UpdateGroup);

	Fire_StartTime = TimeSinceStart.Time;

	// Setup Fire Routine
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

	Payload->CoroutineImpl.BindUObject(this, &UCsProjectileWeaponComponent::Fire_Internal);
	Payload->StartTime = UCsManager_Time::Get(GetWorld()->GetGameInstance())->GetTime(UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::Fire_Internal);
	Payload->SetFName(Name::Fire_Internal);
	Payload->OnEnds.AddDefaulted();
	Payload->OnEnds.Last().BindUObject(this, &UCsProjectileWeaponComponent::Fire_Internal_OnEnd);
	Payload->AbortMessages.Add(Name::Abort_Fire_Internal);

	// Cache pointer to ICsData_ProjectileWeapon
	typedef NCsWeapon::NProjectile::NData::IData ProjectileDataType;

	ProjectileDataType* PrjData = FCsLibrary_Data_Weapon::GetInterfaceChecked<ProjectileDataType>(Context, Data);

	Payload->SetValue_Flag(CS_FIRST, PrjData->HasInfiniteAmmo());
	Payload->SetValue_Int(CS_FIRST, PrjData->GetProjectilesPerShot());
	Payload->SetValue_Float(CS_FIRST, PrjData->GetTimeBetweenProjectilesPerShot());

	FireRoutineHandle = Scheduler->Start(Payload);
}

char UCsProjectileWeaponComponent::Fire_Internal(FCsRoutine* R)
{
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
			ElapsedTime.Reset();

			if (!bInfiniteAmmo)
				ConsumeAmmo();

			ProjectileImpl->StartLaunch();
			SoundImpl->Play();
			FXImpl->Play();

			// Increment the shot index
			CurrentProjectilePerShotIndex = FMath::Min(CurrentProjectilePerShotIndex + 1, ProjectilesPerShot);

			// Check if more projectiles should be fired, if so wait
			if (CurrentProjectilePerShotIndex < ProjectilesPerShot)
			{
				CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= TimeBetweenProjectilesPerShot);
			}
		}
	} while (CurrentProjectilePerShotIndex < ProjectilesPerShot);

	CS_COROUTINE_END(R);
}

void UCsProjectileWeaponComponent::Fire_Internal_OnEnd(FCsRoutine* R)
{
	--FireCount;
}

void UCsProjectileWeaponComponent::FTimeBetweenShotsImpl::OnElapsedTime()
{
	using namespace NCsProjectileWeaponComponent::NCached::TimeBetweenShotsImpl;

	const FString& Context = Str::OnElapsedTime;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(Outer->GetWorld()->GetGameInstance());

	// Setup Routine
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(Outer->GetUpdateGroup());

	Payload->CoroutineImpl.BindRaw(this, &UCsProjectileWeaponComponent::FTimeBetweenShotsImpl::OnElapsedTime_Internal);
	Payload->StartTime = UCsManager_Time::Get(Outer->GetWorld()->GetGameInstance())->GetTime(Outer->GetUpdateGroup());
	Payload->Owner.SetObject(Outer);
	Payload->SetName(Str::OnElapsedTime_Internal);
	Payload->SetFName(Name::OnElapsedTime_Internal);

	// Get total elapsed time (= TimeBetweenShots)
	typedef NCsWeapon::NProjectile::NData::IData ProjectileDataType;

	ProjectileDataType* PrjData = FCsLibrary_Data_Weapon::GetInterfaceChecked<ProjectileDataType>(Context, Outer->GetData());

	Payload->SetValue_Float(CS_FIRST, PrjData->GetTimeBetweenShots());

	Scheduler->Start(Payload);
}

char UCsProjectileWeaponComponent::FTimeBetweenShotsImpl::OnElapsedTime_Internal(FCsRoutine* R)
{
	FCsDeltaTime& ElapsedTime			   = R->GetValue_DeltaTime(CS_FIRST);
	const FCsDeltaTime PreviousElapsedTime = ElapsedTime;

	ElapsedTime += R->DeltaTime;

	const float& TimeBetweenShots = R->GetValue_Float(CS_FIRST);

	// Broadcast ElapsedTime events

		// Time
	const float& PreviousTime = PreviousElapsedTime.Time;
	const float NewTime		   = FMath::Max(ElapsedTime.Time, TimeBetweenShots);

	OnElapsedTime_Event.Broadcast(Outer, PreviousTime, NewTime);
	// Percent
	const float PreviousPercent = PreviousElapsedTime.Time / TimeBetweenShots;
	const float NewPercent		= FMath::Min(ElapsedTime.Time / TimeBetweenShots, 1.0f);

	OnElapsedTimeAsPercent_Event.Broadcast(Outer, PreviousPercent, NewPercent);

	CS_COROUTINE_BEGIN(R);

	ElapsedTime.Reset();

	CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= TimeBetweenShots);

	CS_COROUTINE_END(R);
}

	// Projectile
#pragma region

bool UCsProjectileWeaponComponent::FProjectileImpl::SetType(const FString& Context, const FCsProjectilePooled* ProjectilePooled)
{
	ACsProjectilePooledImpl* Projectile = ProjectilePooled->GetObject<ACsProjectilePooledImpl>();

	checkf(Projectile, TEXT("%s: Projectile is NULL. Projectile is not of type: ACsProjectilePooledImpl."), *Context);

	Projectile->SetType(Weapon->GetProjectileType());
	return true;
}

#define ProjectilePayloadType NCsProjectile::NPayload::IPayload
bool UCsProjectileWeaponComponent::FProjectileImpl::SetPayload(const FString& Context, ProjectilePayloadType* Payload)
{
#undef ProjectilePayloadType

	bool Result = true;

	// PooledObject
	{
		typedef NCsPooledObject::NPayload::FImplSlice SliceType;
		typedef NCsPooledObject::NPayload::IPayload SliceInterfaceType;

		if (SliceType* Slice = FCsLibrary_Payload_Projectile::SafeStaticCastChecked<SliceType, SliceInterfaceType>(Context, Payload))
		{
			Slice->Instigator = Weapon;
			Slice->Owner	  = Weapon->GetMyOwner();
		}
		else
		{
			Result &= false;
		}
	}
	// Projectile
	{
		typedef NCsProjectile::NPayload::FImplSlice SliceType;
		typedef NCsProjectile::NPayload::IPayload SliceInterfaceType;

		if (SliceType* Slice = FCsLibrary_Payload_Projectile::SafeStaticCastChecked<SliceType, SliceInterfaceType>(Context, Payload))
		{
			Slice->Location  = GetLaunchLocation();
			Slice->Direction = GetLaunchDirection();
		}
		else
		{
			Result &= false;
		}
	}
	return Result;
}

#define ProjectilePayloadType NCsProjectile::NPayload::IPayload
bool UCsProjectileWeaponComponent::FProjectileImpl::CopyPayload(const FString& Context, const ProjectilePayloadType* From, ProjectilePayloadType* To)
{
#undef ProjectilePayloadType
	return FCsLibrary_Payload_Projectile::CopyChecked(Context, From, To);
}

FVector UCsProjectileWeaponComponent::FProjectileImpl::GetLaunchLocation()
{
	using namespace NCsProjectileWeaponComponent::NCached::ProjectileImpl;

	const FString& Context = Str::GetLaunchLocation;

	// Get Data Slice
	typedef NCsWeapon::NProjectile::NData::IData WeaponDataType;

	WeaponDataType* WeaponData = FCsLibrary_Data_Weapon::GetInterfaceChecked<WeaponDataType>(Context, Weapon->GetData());
	
	// Get Launch Params
	using namespace NCsWeapon::NProjectile::NParams::NLaunch;

	const ILaunch* LaunchParams = WeaponData->GetLaunchParams();

	checkf(LaunchParams, TEXT("%s: Failed to get LaunchParams from Data."), *Context);

	const ELocation& LocationType = LaunchParams->GetLocationType();

	// Owner
	if (LocationType == ELocation::Owner)
	{
		UObject* TheOwner = Weapon->GetMyOwner();

		checkf(TheOwner, TEXT("%s: No Owner found for %s."), *Context, *(Weapon->PrintNameAndClass()));

		// Actor
		if (AActor* Actor = Cast<AActor>(TheOwner))
			return Actor->GetActorLocation();
		// Component
		if (USceneComponent* Component = Cast<USceneComponent>(TheOwner))
			return Component->GetComponentLocation();

		checkf(0, TEXT("%s: Failed to get Location from %s."), *Context, *(Weapon->PrintNameClassAndOwner()));
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

FVector UCsProjectileWeaponComponent::FProjectileImpl::GetLaunchDirection()
{
	using namespace NCsProjectileWeaponComponent::NCached::ProjectileImpl;

	const FString& Context = Str::GetLaunchDirection;

	// Get Data Slice
	typedef NCsWeapon::NProjectile::NData::IData WeaponDataType;

	WeaponDataType* WeaponData = FCsLibrary_Data_Weapon::GetInterfaceChecked<WeaponDataType>(Context, Weapon->GetData());
	
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
		if (UObject* TheOwner = Weapon->GetMyOwner())
		{
			// AActor
			if (AActor* Actor = Cast<AActor>(TheOwner))
				return NCsRotationRules::GetRotation(Actor, DirectionRules).Vector();
			// USceneComponent
			if (USceneComponent* Component = Cast<USceneComponent>(TheOwner))
				return NCsRotationRules::GetRotation(Component, DirectionRules).Vector();
			checkf(0, TEXT("%s: Failed to get Direction from %s."), *Context, *(Weapon->PrintNameClassAndOwner()));
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

		return Rotation.Vector();
	}
	// Camera
	if (DirectionType == EDirection::Camera)
	{
		// Try to get camera through the owner
		if (UObject* TheOwner = Weapon->GetMyOwner())
		{
			return FCsLibrary_Camera::GetDirectionChecked(Context, TheOwner);
		}
		checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *(Weapon->PrintNameAndClass()));
	}
	// ITrace | Get Launch Trace Params
	if (DirectionType == EDirection::Trace)
	{
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
			if (UObject* TheOwner = Weapon->GetMyOwner())
			{
				Start = FCsLibrary_Camera::GetLocationChecked(Context, TheOwner);
			}
			// TODO: For now assert
			else
			{
				checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *(Weapon->PrintNameAndClass()));
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
			if (UObject* TheOwner = Weapon->GetMyOwner())
			{
				Dir = FCsLibrary_Camera::GetDirectionChecked(Context, TheOwner, DirectionRules);
			}
			// TODO: For now assert
			else
			{
				checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *(Weapon->PrintNameAndClass()));
			}
		}

		const float& Distance = LaunchTraceParams->GetTraceDistance();

		const FVector End = Start + Distance * Dir;

		// Perform Trace
		UCsManager_Trace* Manager_Trace = UCsManager_Trace::Get(Weapon->GetWorld()->GetGameState());

		FCsTraceRequest* Request = Manager_Trace->AllocateRequest();
		Request->Start = Start;
		Request->End = End;

		// Get collision information related to the projectile to be used in the trace.
		ICsData_Projectile* PrjData					  = UCsManager_Projectile::Get(Weapon->GetWorld()->GetGameState())->GetDataChecked(Context, Weapon->GetProjectileType());
		ICsData_ProjectileCollision* PrjCollisionData = FCsLibrary_Data_Projectile::GetInterfaceChecked<ICsData_ProjectileCollision>(Context, PrjData);

		const FCsCollisionPreset& CollisionPreset		 = PrjCollisionData->GetCollisionPreset();
		const TEnumAsByte<ECollisionChannel>& ObjectType = CollisionPreset.ObjectType;

		Request->ObjectParams.AddObjectTypesToQuery(ObjectType);

		Request->Type = LaunchTraceParams->GetTraceType();

		if (Request->Type == ECsTraceType::Sweep)
		{
			//Request->Shape = 
		}
		
		FCsTraceResponse* Response = Manager_Trace->Trace(Request);

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
			return LaunchDirection;
		}
		return Dir;
	}
	return FVector::ZeroVector;
}

void UCsProjectileWeaponComponent::FProjectileImpl::StartLaunch()
{
	using namespace NCsProjectileWeaponComponent::NCached::ProjectileImpl;

	const FString& Context = Str::StartLaunch;

	typedef NCsProjectile::NPayload::IPayload PayloadType;

	UCsManager_Projectile* Manager_Projectile = UCsManager_Projectile::Get(Weapon->GetWorld()->GetGameState());

	// Get Payload
	PayloadType* Payload1 = Manager_Projectile->AllocatePayload(Weapon->GetProjectileType());

	// Set appropriate members on Payload
	const bool SetSuccess = SetPayload(Context, Payload1);

	checkf(SetSuccess, TEXT("%s: Failed to set Payload1."), *Context);

	// Cache copy of Payload for Launch
	PayloadType* Payload2 = Manager_Projectile->AllocatePayload(Weapon->GetProjectileType());

	const bool CopySuccess = CopyPayload(Context, Payload1, Payload2);

	checkf(CopySuccess, TEXT("%s: Failed to copy Payload1 to Payload2."), *Context);

	// Spawn
	const FCsProjectilePooled* ProjectilePooled = Manager_Projectile->Spawn(Weapon->GetProjectileType(), Payload1);

	const bool TypeSuccess = SetType(Context, ProjectilePooled);

	checkf(TypeSuccess, TEXT("%s: Failed to set type for Projectile."), *Context);

	// Launch
	Launch(ProjectilePooled, Payload2);
}

#define ProjectilePayloadType NCsProjectile::NPayload::IPayload
void UCsProjectileWeaponComponent::FProjectileImpl::Launch(const FCsProjectilePooled* ProjectilePooled, ProjectilePayloadType* Payload)
{
#undef ProjectilePayloadType

	using namespace NCsProjectileWeaponComponent::NCached::ProjectileImpl;

	const FString& Context = Str::Launch;

	typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;

	PooledPayloadType* ObjectPayload    = NCsInterfaceMap::GetInterfaceChecked<PooledPayloadType>(Context, Payload);
	ACsProjectilePooledImpl* Projectile	= ProjectilePooled->GetObject<ACsProjectilePooledImpl>();

	checkf(Projectile, TEXT("%s: Projectile is NULL. Projectile is not of type: ACsProjectilePooledImpl."), *Context);

	if (!Projectile->bLaunchOnAllocate)
		Projectile->Launch(ObjectPayload);

	// Release payload so it returns to the pool
	ObjectPayload->Reset();
}

UCsProjectileWeaponComponent::FProjectileImpl* UCsProjectileWeaponComponent::ConstructProjectileImpl()
{
	return new UCsProjectileWeaponComponent::FProjectileImpl();
}

#pragma endregion Projectile

	// Sound
#pragma region

void UCsProjectileWeaponComponent::FSoundImpl::Play()
{
	using namespace NCsProjectileWeaponComponent::NCached::SoundImpl;

	const FString& Context = Str::Play;

	// NCsWeapon::NProjectile::NData::NSound::NFire::IFire | ICsData_ProjectileWeapon_SoundFire
	typedef NCsWeapon::NProjectile::NData::NSound::NFire::IFire SoundDataType;

	if (SoundDataType* SoundData = FCsLibrary_Data_Weapon::GetSafeInterfaceChecked<SoundDataType>(Context, Weapon->GetData()))
	{
		typedef NCsWeapon::NProjectile::NData::NSound::NFire::NParams::IParams ParamsType;

		ParamsType* Params = SoundData->GetFireSoundParams();
		const FCsSound& Sound = Params->GetSound();

		USoundBase* SoundAsset = Sound.GetChecked(Context);

		// Get Manager
		UCsManager_Sound* Manager_Sound = UCsManager_Sound::Get(Weapon->GetWorld()->GetGameState());
		// Allocate payload
		typedef NCsSound::NPayload::IPayload PayloadType;

		PayloadType* Payload = Manager_Sound->AllocatePayload(Sound.Type);
		// Set appropriate values on payload
		SetPayload(Payload, Sound);

		Manager_Sound->Spawn(Sound.Type, Payload);
	}
}

#define SoundPayloadType NCsSound::NPayload::IPayload
void UCsProjectileWeaponComponent::FSoundImpl::SetPayload(SoundPayloadType* Payload, const FCsSound& Sound)
{
#undef SoundPayloadType

	using namespace NCsProjectileWeaponComponent::NCached::SoundImpl;

	const FString& Context = Str::SetPayload;

	typedef NCsSound::NPayload::FImpl PayloadImplType;

	PayloadImplType* PayloadImpl = FCsLibrary_Payload_Sound::PureStaticCastChecked<PayloadImplType>(Context, Payload);

	PayloadImpl->Instigator					= Weapon;
	PayloadImpl->Owner						= Weapon->GetMyOwner();
	PayloadImpl->Sound						= Sound.GetChecked(Context);
	PayloadImpl->SoundAttenuation			= Sound.GetAttenuation();
	PayloadImpl->DeallocateMethod			= Sound.DeallocateMethod;
	PayloadImpl->LifeTime					= Sound.LifeTime;
	PayloadImpl->AttachmentTransformRules	= Sound.AttachmentTransformRules;
	PayloadImpl->Bone						= Sound.Bone;
	PayloadImpl->TransformRules				= Sound.TransformRules;
	PayloadImpl->Transform					= Sound.Transform;
}

UCsProjectileWeaponComponent::FSoundImpl* UCsProjectileWeaponComponent::ConstructSoundImpl()
{
	return new UCsProjectileWeaponComponent::FSoundImpl();
}

#pragma endregion Sound

	// FX
#pragma region

void UCsProjectileWeaponComponent::FFXImpl::Play()
{
	using namespace NCsProjectileWeaponComponent::NCached::FXImpl;

	const FString& Context = Str::Play;

	// NCsWeapon::NProjectile::NData::NVisual::NFire::IFire | ICsData_ProjectileWeapon_VisualFire
	typedef NCsWeapon::NProjectile::NData::NVisual::NFire::IFire FXDataType;

	if (FXDataType* FXData = FCsLibrary_Data_Weapon::GetSafeInterfaceChecked<FXDataType>(Context, Weapon->GetData()))
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

		Manager_FX->Spawn(FX.Type, Payload);
	}
}

#define FXPayloadType NCsFX::NPayload::IPayload
void UCsProjectileWeaponComponent::FFXImpl::SetPayload(FXPayloadType* Payload, const FCsFX& FX)
{
#undef FXPayloadType

	using namespace NCsProjectileWeaponComponent::NCached::FXImpl;

	const FString& Context = Str::SetPayload;

	typedef NCsFX::NPayload::FImpl PayloadImplType;

	PayloadImplType* PayloadImpl = FCsLibrary_Payload_FX::PureStaticCastChecked<PayloadImplType>(Context, Payload);

	PayloadImpl->Instigator					= Weapon;
	PayloadImpl->Owner						= Weapon->GetMyOwner();
	PayloadImpl->FXSystem					= FX.GetChecked(Context);
	PayloadImpl->DeallocateMethod			= FX.DeallocateMethod;
	PayloadImpl->LifeTime					= FX.LifeTime;
	PayloadImpl->AttachmentTransformRules	= FX.AttachmentTransformRules;
	PayloadImpl->Bone						= FX.Bone;
	PayloadImpl->TransformRules				= FX.TransformRules;
	PayloadImpl->Transform					= FX.Transform;

	typedef NCsWeapon::NProjectile::NData::NVisual::NFire::IFire FXDataType;

	FXDataType* FXData = FCsLibrary_Data_Weapon::GetInterfaceChecked<FXDataType>(Context, Weapon->GetData());

	typedef NCsWeapon::NProjectile::NData::NVisual::NFire::FParams ParamsType;

	const ParamsType& Params = FXData->GetFireFXParams();

	typedef NCsWeapon::NProjectile::NData::NVisual::NFire::EAttach AttachType;

	const AttachType& Type = Params.GetAttachType();

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

UCsProjectileWeaponComponent::FFXImpl* UCsProjectileWeaponComponent::ConstructFXImpl()
{
	return new UCsProjectileWeaponComponent::FFXImpl();
}

#pragma endregion FX

#pragma endregion Fire

// Print
#pragma region

FString UCsProjectileWeaponComponent::PrintNameAndClass()
{
	return FString::Printf(TEXT("Weapon: %s with Class: %s"), *(GetName()), *(GetClass()->GetName()));
}

FString UCsProjectileWeaponComponent::PrintNameClassAndOwner()
{
	return FString::Printf(TEXT("Weapon: %s with Class: %s with MyOwner: %s"), *(GetName()), *(GetClass()->GetName()), *(MyOwner->GetName()));
}

#pragma endregion Print