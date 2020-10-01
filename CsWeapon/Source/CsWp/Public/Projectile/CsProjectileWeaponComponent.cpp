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
#include "Managers/Sound/Payload/CsLibrary_Payload_Sound.h"
// Settings
#include "Settings/CsWeaponSettings.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
#include "Managers/Weapon/CsManager_Weapon.h"
#include "Managers/Projectile/CsManager_Projectile.h"
#include "Managers/Sound/CsManager_Sound.h"
// Data
#include "Data/CsData_Weapon.h"
#include "Projectile/Data/CsData_ProjectileWeapon.h"
#include "Projectile/Data/CsData_ProjectileWeaponSound.h"
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

// Cached
#pragma region

namespace NCsProjectileWeaponComponentCached
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
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsProjectileWeaponComponent, PlayFireSound);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsProjectileWeaponComponent, SetSoundPooledPayload);
	}

	namespace Name
	{
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsProjectileWeaponComponent, Fire_Internal);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsProjectileWeaponComponent, Abort_Fire_Internal);
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
	CurrentProjectilePerShotIndex(0)
{
}

// UActorComponent Interface
#pragma region

void UCsProjectileWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	MyOwner		   = GetOwner();
	MyOwnerAsActor = GetOwner();
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

ICsData_Weapon* UCsProjectileWeaponComponent::GetData() const
{
	return Data;
}

const FECsWeaponState& UCsProjectileWeaponComponent::GetCurrentState() const
{
	return CurrentState;
}

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
	using namespace NCsProjectileWeaponComponentCached;

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
	ICsData_ProjectileWeapon* PrjData = FCsLibrary_Data_Weapon::GetInterfaceChecked<ICsData_ProjectileWeapon>(Context, Data);

	CurrentAmmo = PrjData->GetMaxAmmo();
}

// State
#pragma region

void UCsProjectileWeaponComponent::OnUpdate_HandleStates(const FCsDeltaTime& DeltaTime)
{
	using namespace NCsProjectileWeaponComponentCached;

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
	using namespace NCsProjectileWeaponComponentCached;

	const FString& Context = Str::CanFire;
	
	const FCsDeltaTime& TimeSinceStart = UCsManager_Time::Get(GetWorld()->GetGameInstance())->GetTimeSinceStart(UpdateGroup);

	ICsData_ProjectileWeapon* PrjData = FCsLibrary_Data_Weapon::GetInterfaceChecked<ICsData_ProjectileWeapon>(Context, Data);

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
	using namespace NCsProjectileWeaponComponentCached;

	const FString& Context = Str::Fire;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(GetWorld()->GetGameInstance());

	// End previous Fire Routine
	Scheduler->End(UpdateGroup, FireRoutineHandle);

	const FCsDeltaTime& TimeSinceStart = UCsManager_Time::Get(GetWorld()->GetGameInstance())->GetTimeSinceStart(UpdateGroup);

	Fire_StartTime = TimeSinceStart.Time;

	// Setup Fire Routine
	FCsCoroutinePayload* Payload = Scheduler->AllocatePayload(UpdateGroup);

	Payload->CoroutineImpl.BindUObject(this, &UCsProjectileWeaponComponent::Fire_Internal);
	Payload->StartTime = UCsManager_Time::Get(GetWorld()->GetGameInstance())->GetTime(UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::Fire_Internal);
	Payload->SetFName(Name::Fire_Internal);
	Payload->OnEnds.AddDefaulted();
	Payload->OnEnds.Last().BindUObject(this, &UCsProjectileWeaponComponent::Fire_Internal_OnEnd);
	Payload->AbortMessages.Add(Name::Abort_Fire_Internal);

	// Cache pointer to ICsData_ProjectileWeapon
	ICsData_ProjectileWeapon* PrjData = FCsLibrary_Data_Weapon::GetInterfaceChecked<ICsData_ProjectileWeapon>(Context, Data);

	Payload->SetValue_Void(CS_FIRST, PrjData);

	FireRoutineHandle = Scheduler->Start(Payload);
}

char UCsProjectileWeaponComponent::Fire_Internal(FCsRoutine* R)
{
	ICsData_ProjectileWeapon* PrjData = R->GetValue_Void<ICsData_ProjectileWeapon>(CS_FIRST);

	FCsDeltaTime& ElapsedTime = R->GetValue_DeltaTime(CS_FIRST);

	ElapsedTime += R->DeltaTime;
	
	CS_COROUTINE_BEGIN(R);

	++FireCount;

	do 
	{
		{
			ElapsedTime.Reset();

			if (!PrjData->HasInfiniteAmmo())
				ConsumeAmmo();

			FireProjectile();
			PlayFireSound();

			// Increment the shot index
			CurrentProjectilePerShotIndex = FMath::Min(CurrentProjectilePerShotIndex + 1, PrjData->GetProjectilesPerShot());

			// Check if more projectiles should be fired, if so wait
			if (CurrentProjectilePerShotIndex < PrjData->GetProjectilesPerShot())
			{
				CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= PrjData->GetTimeBetweenProjectilesPerShot());
			}
		}
	} while (CurrentProjectilePerShotIndex < PrjData->GetProjectilesPerShot());

	CS_COROUTINE_END(R);
}

void UCsProjectileWeaponComponent::Fire_Internal_OnEnd(FCsRoutine* R)
{
	--FireCount;
}

	// Projectile
#pragma region

void UCsProjectileWeaponComponent::FireProjectile()
{
	using namespace NCsProjectileWeaponComponentCached;

	const FString& Context = Str::FireProjectile;

	typedef NCsProjectile::NPayload::IPayload PayloadInterfaceType;

	UCsManager_Projectile* Manager_Projectile = UCsManager_Projectile::Get(GetWorld()->GetGameState());

	// Get Payload
	PayloadInterfaceType* Payload1 = Manager_Projectile->AllocatePayload(ProjectileType);

	// Set appropriate members on Payload
	const bool SetSuccess = SetProjectilePayload(Context, Payload1);

	checkf(SetSuccess, TEXT("%s: Failed to set Payload1."), *Context);

	// Cache copy of Payload for Launch
	PayloadInterfaceType* Payload2 = Manager_Projectile->AllocatePayload(ProjectileType);
	
	const bool CopySuccess = CopyProjectilePayload(Context, Payload1, Payload2);

	checkf(CopySuccess, TEXT("%s: Failed to copy Payload1 to Payload2."), *Context);

	// Spawn
	const FCsProjectilePooled* ProjectilePooled = Manager_Projectile->Spawn(ProjectileType, Payload1);

	const bool TypeSuccess = SetTypeForProjectile(Context, ProjectilePooled);

	checkf(TypeSuccess, TEXT("%s: Failed to set type for Projectile."), *Context);

	// Launch
	LaunchProjectile(ProjectilePooled, Payload2);
}

bool UCsProjectileWeaponComponent::SetTypeForProjectile(const FString& Context, const FCsProjectilePooled* ProjectilePooled)
{
	ACsProjectilePooledImpl* Projectile = ProjectilePooled->GetObject<ACsProjectilePooledImpl>();

	checkf(Projectile, TEXT("%s: Projectile is NULL. Projectile is not of type: ACsProjectilePooledImpl."), *Context);

	Projectile->SetType(ProjectileType);
	return true;
}

bool UCsProjectileWeaponComponent::SetProjectilePayload(const FString& Context, NCsProjectile::NPayload::IPayload* Payload)
{
	bool Result = true;

	// PooledObject
	{
		typedef NCsPooledObject::NPayload::FImplSlice SliceType;
		typedef NCsPooledObject::NPayload::IPayload SliceInterfaceType;

		if (SliceType* Slice = FCsLibrary_Payload_Projectile::SafeStaticCastChecked<SliceType, SliceInterfaceType>(Context, Payload))
		{
			Slice->Instigator = this;
			Slice->Owner	  = MyOwner;
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
			Slice->Location  = GetLaunchProjectileLocation();
			Slice->Direction = GetLaunchProjectileDirection();
		}
		else
		{
			Result &= false;
		}
	}
	return Result;
}

bool UCsProjectileWeaponComponent::CopyProjectilePayload(const FString& Context, const NCsProjectile::NPayload::IPayload* From, NCsProjectile::NPayload::IPayload* To)
{
	return FCsLibrary_Payload_Projectile::CopyChecked(Context, From, To);
}

FVector UCsProjectileWeaponComponent::GetLaunchProjectileLocation()
{
	return MyOwnerAsActor->GetActorLocation();
}

FVector UCsProjectileWeaponComponent::GetLaunchProjectileDirection()
{
	return FVector::ZeroVector;
}

void UCsProjectileWeaponComponent::LaunchProjectile(const FCsProjectilePooled* ProjectilePooled, NCsProjectile::NPayload::IPayload* Payload)
{
	using namespace NCsProjectileWeaponComponentCached;

	const FString& Context = Str::LaunchProjectile;

	NCsPooledObject::NPayload::IPayload* ObjectPayload = NCsInterfaceMap::GetInterfaceChecked<NCsPooledObject::NPayload::IPayload>(Context, Payload);
	ACsProjectilePooledImpl* Projectile				   = ProjectilePooled->GetObject<ACsProjectilePooledImpl>();

	checkf(Projectile, TEXT("%s: Projectile is NULL. Projectile is not of type: ACsProjectilePooledImpl."), *Context);

	if (!Projectile->bLaunchOnAllocate)
		Projectile->Launch(ObjectPayload);

	// Release payload so it returns to the pool
	ObjectPayload->Reset();
}

#pragma endregion Projectile

// Sound
#pragma region

void UCsProjectileWeaponComponent::PlayFireSound()
{
	using namespace NCsProjectileWeaponComponentCached;

	const FString& Context = Str::PlayFireSound;

	// ICsData_ProjectileWeaponSound
	if (ICsData_ProjectileWeaponSound* SoundData = FCsLibrary_Data_Weapon::GetSafeInterfaceChecked<ICsData_ProjectileWeaponSound>(Context, Data))
	{
		const FCsSound& Sound = SoundData->GetFireSound();

		if (USoundBase* SoundAsset = Sound.Get())
		{
			// Get Manager
			UCsManager_Sound* Manager_Sound = UCsManager_Sound::Get(GetWorld()->GetGameState());
			// Allocate payload
			NCsSound::NPayload::IPayload* Payload = Manager_Sound->AllocatePayload(Sound.Type);
			// Set appropriate values on payload
			SetSoundPooledPayload(Payload, Sound);

			Manager_Sound->Spawn(Sound.Type, Payload);
		}
		else
		{

		}
	}
}

void UCsProjectileWeaponComponent::SetSoundPooledPayload(NCsSound::NPayload::IPayload* Payload, const FCsSound& Sound)
{
	using namespace NCsProjectileWeaponComponentCached;

	const FString& Context = Str::SetSoundPooledPayload;

	NCsSound::NPayload::FImpl* PayloadImpl = FCsLibrary_Payload_Sound::PureStaticCastChecked<NCsSound::NPayload::FImpl>(Context, Payload);

	PayloadImpl->Instigator					= this;
	PayloadImpl->Owner						= MyOwner;
	PayloadImpl->Sound						= Sound.Get();
	PayloadImpl->SoundAttenuation			= Sound.GetAttenuation();
	PayloadImpl->DeallocateMethod			= Sound.DeallocateMethod;
	PayloadImpl->LifeTime					= Sound.LifeTime;
	PayloadImpl->AttachmentTransformRules	= Sound.AttachmentTransformRules;
	PayloadImpl->Bone						= Sound.Bone;
	PayloadImpl->TransformRules				= Sound.TransformRules;
	PayloadImpl->Transform					= Sound.Transform;
}

#pragma endregion Sound

#pragma endregion Fire