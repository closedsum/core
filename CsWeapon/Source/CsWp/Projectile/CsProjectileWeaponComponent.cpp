#include "Projectile/CsProjectileWeaponComponent.h"
#include "CsWp.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Library
#include "Payload/CsLibrary_Payload_Projectile.h"
#include "Data/CsLibrary_Data_Weapon.h"
#include "Managers/Sound/Payload/CsLibrary_SoundPooledPayload.h"
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
// Projectile
#include "Payload/CsPayload_ProjectilePooledImpl.h"
#include "Managers/Projectile/CsProjectilePooledImpl.h"
// Sound
#include "Managers/Sound/Payload/CsSoundPooledPayloadImpl.h"

// Cached
#pragma region

namespace NCsProjectileWeaponComponentCached
{
	namespace Str
	{
		const FString Init = TEXT("UCsProjectileWeaponComponent::Init");
		const FString CanFire = TEXT("UCsProjectileWeaponComponent::CanFire");
		const FString Fire = TEXT("UCsProjectileWeaponComponent::Fire");
		const FString Fire_Internal = TEXT("UCsProjectileWeaponComponent::Fire_Internal");
		const FString FireProjectile = TEXT("UCsProjectileWeaponComponent::FireProjectile");
		const FString SetProjectilePayload = TEXT("UCsProjectileWeaponComponent::SetProjectilePayload");
		const FString LaunchProjectile = TEXT("UCsProjectileWeaponComponent::LaunchProjectile");
		const FString PlayFireSound = TEXT("UCsProjectileWeaponComponent::PlayFireSound");
		const FString SetSoundPooledPayload = TEXT("UCsProjectileWeaponComponent::SetSoundPooledPayload");
	}

	namespace Name
	{
		const FName Fire_Internal = FName("UCsProjectileWeaponComponent::Fire_Internal");
		const FName Abort_Fire_Internal = FName("Abort_Fire_Internal");
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

	checkf(EMCsProjectile::Get().IsValidEnum(ProjectileType), TEXT("%s: WeaponType: %s is NOT Valid."), *Context, ProjectileType.ToChar());

	// Set States
	UCsWeaponSettings* Settings = GetMutableDefault<UCsWeaponSettings>();

	IdleState = Settings->ProjectileWeaponImpl.IdleState;

	checkf(EMCsWeaponState::Get().IsValidEnum(IdleState), TEXT("%s: IdleState: %s is NOT Valid."), *Context, IdleState.ToChar());

	FireState = Settings->ProjectileWeaponImpl.FireState;

	checkf(EMCsWeaponState::Get().IsValidEnum(FireState), TEXT("%s: FireState: %s is NOT Valid."), *Context, FireState.ToChar())
}

// State
#pragma region

void UCsProjectileWeaponComponent::OnUpdate_HandleStates(const FCsDeltaTime& DeltaTime)
{
	const FCsTime& Time = UCsManager_Time::Get(GetWorld()->GetGameInstance())->GetTime(UpdateGroup);

	// Idle
	if (CurrentState == IdleState)
	{
		if (CanFire())
		{
			Fire();

			CurrentState = FireState;
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
		}
	}
}

#pragma endregion State

// Fire
#pragma region

bool UCsProjectileWeaponComponent::CanFire() const
{
	using namespace NCsProjectileWeaponComponentCached;

	const FString& Context = Str::CanFire;

	const FCsTime& Time = UCsManager_Time::Get(GetWorld()->GetGameInstance())->GetTime(UpdateGroup);

	ICsData_ProjectileWeapon* PrjData = FCsLibrary_Data_Weapon::GetInterfaceChecked<ICsData_ProjectileWeapon>(Context, Data);

	// Check if enough time has elapsed to fire again.
	const bool Pass_Time = (Time.Time - Fire_StartTime > PrjData->GetTimeBetweenShots());
	// Check if bFire is set, its not on release, and its either bFire is just set or FullAuto.
	const bool Pass_Fire = bFire && !PrjData->DoFireOnRelease() && (PrjData->IsFullAuto() || !bFire_Last);
	// Check if bFire has just been unset and on release.
	const bool Pass_FireOnRelease = !bFire && PrjData->DoFireOnRelease() && bFire_Last;

	return Pass_Time && (Pass_Fire || Pass_FireOnRelease);
}

void UCsProjectileWeaponComponent::Fire()
{
	using namespace NCsProjectileWeaponComponentCached;

	const FString& Context = Str::Fire;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(GetWorld()->GetGameInstance());

	// End previous Fire Routine
	Scheduler->End(UpdateGroup, FireRoutineHandle);

	const FCsTime& Time = UCsManager_Time::Get(GetWorld()->GetGameInstance())->GetTime(UpdateGroup);

	Fire_StartTime = Time.Time;

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

			FireProjectile();
			PlayFireSound();

			// Increment the shot index
			CurrentProjectilePerShotIndex = FMath::Min(CurrentProjectilePerShotIndex + 1, PrjData->GetMaxAmmo());

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
	UCsManager_Projectile* Manager_Projectile = UCsManager_Projectile::Get(GetWorld()->GetGameState());

	// Get Payload
	ICsPayload_Projectile* Payload1 = Manager_Projectile->AllocatePayload(ProjectileType);

	// Set appropriate members on Payload
	SetProjectilePayload(Payload1);

	// Cache copy of Payload for Launch
	ICsPayload_Projectile* Payload2 = Manager_Projectile->AllocatePayload(ProjectileType);
	
	SetProjectilePayload(Payload2);

	// Spawn
	const FCsProjectilePooled* ProjectilePooled = Manager_Projectile->Spawn(ProjectileType, Payload1);

	SetTypeForProjectile(ProjectilePooled);

	// Launch
	LaunchProjectile(ProjectilePooled, Payload2);
}

void UCsProjectileWeaponComponent::SetTypeForProjectile(const FCsProjectilePooled* ProjectilePooled)
{
	ACsProjectilePooledImpl* Projectile = ProjectilePooled->GetObject<ACsProjectilePooledImpl>();

	checkf(Projectile, TEXT("UCsProjectileWeaponComponent::SetTypeForProjectile: Projectile is NULL. Projectile is not of type: ACsProjectilePooledImpl."));

	Projectile->SetType(ProjectileType);
}

void UCsProjectileWeaponComponent::SetProjectilePayload(ICsPayload_Projectile* Payload)
{
	using namespace NCsProjectileWeaponComponentCached;

	const FString& Context = Str::SetProjectilePayload;

	FCsPayload_ProjectilePooledImpl* PayloadImpl = FCsLibrary_Payload_Projectile::PureStaticCastChecked<FCsPayload_ProjectilePooledImpl>(Str::SetProjectilePayload, Payload);

	PayloadImpl->Instigator = this;
	PayloadImpl->Owner		= MyOwner;
	PayloadImpl->Location	= GetLaunchProjectileLocation();
	PayloadImpl->Direction	= GetLaunchProjectileDirection();
}

FVector UCsProjectileWeaponComponent::GetLaunchProjectileLocation()
{
	return MyOwnerAsActor->GetActorLocation();
}

FVector UCsProjectileWeaponComponent::GetLaunchProjectileDirection()
{
	return FVector::ZeroVector;
}

void UCsProjectileWeaponComponent::LaunchProjectile(const FCsProjectilePooled* ProjectilePooled, ICsPayload_Projectile* Payload)
{
	using namespace NCsProjectileWeaponComponentCached;

	const FString& Context = Str::LaunchProjectile;

	ICsPayload_PooledObject* ObjectPayload = NCsInterfaceMap::GetInterfaceChecked<ICsPayload_PooledObject>(Context, Payload);

	ACsProjectilePooledImpl* Projectile = ProjectilePooled->GetObject<ACsProjectilePooledImpl>();

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
			ICsSoundPooledPayload* Payload = Manager_Sound->AllocatePayload(Sound.Type);
			// Set appropriate values on payload
			SetSoundPooledPayload(Payload, Sound);

			Manager_Sound->Spawn(Sound.Type, Payload);
		}
		else
		{

		}
	}
}

void UCsProjectileWeaponComponent::SetSoundPooledPayload(ICsSoundPooledPayload* Payload, const FCsSound& Sound)
{
	using namespace NCsProjectileWeaponComponentCached;

	const FString& Context = Str::SetSoundPooledPayload;

	FCsSoundPooledPayloadImpl* PayloadImpl = FCsLibrary_SoundPooledPayload::PureStaticCastChecked<FCsSoundPooledPayloadImpl>(Context, Payload);

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