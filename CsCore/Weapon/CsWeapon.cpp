// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/CsWeapon.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"
#include "Coroutine/CsCoroutineScheduler.h"
#include "Game/CsGameState.h"
#include "Player/CsPlayerState.h"
#include "Pawn/CsPawn.h"

#include "Animation/CsAnimInstance.h"

// Managers
#include "Managers/FX/CsManager_FX.h"
#include "Managers/Projectile/CsManager_Projectile.h"
#include "Managers/Projectile/CsProjectile.h"

ACsWeapon::ACsWeapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	//FireType_MAX  = ECsWeaponFire::ECsWeaponFire_MAX;
	//FIRE_TYPE_MAX = (uint8)FireType_MAX;

	//CurrentState = ECsWeaponState::Idle;
	//LastState	 = CurrentState;

	//IdleState = ECsWeaponState::Idle;

	//FiringState = ECsWeaponState::Firing;
	//ChargeFireStartAnim = ECsWeaponAnim::ECsWeaponAnim_MAX;
	//ChargeFireLoopAnim = ECsWeaponAnim::ECsWeaponAnim_MAX;

	//ReloadingState = ECsWeaponState::Reloading;
	//ReloadAnim = ECsWeaponAnim::Reload;

	// Make sure to call InitMultiValueMembers() in the Child Class
}

void ACsWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ACsWeapon::OutsideWorldBounds()
{
	return;
}

// Members
#pragma region

void ACsWeapon::InitMultiValueMembers()
{
	const uint8 SIZE = (uint8)FireType_MAX;

	// Firing
	{
		MaxAmmo.Init(1);
		MaxAmmo.GetDelegate.BindUObject(this, &ACsWeapon::GetMaxAmmo);
		ProjectilesPerShot.Init(SIZE);
		ProjectilesPerShot.GetDelegate.BindUObject(this, &ACsWeapon::GetProjectilesPerShot);
		CurrentProjectilePerShotIndex.Init(SIZE);
		DoFireOnRelease.Init(SIZE);
		IsFullAuto.Init(SIZE);
		TimeBetweenProjectilesPerShot.Init(SIZE);
		TimeBetweenProjectilesPerShot.GetDelegate.BindUObject(this, &ACsWeapon::GetTimeBetweenProjectilesPerShot);
		TimeBetweenShots.Init(SIZE);
		TimeBetweenShots.GetDelegate.BindUObject(this, &ACsWeapon::GetTimeBetweenShots);
		TimeBetweenAutoShots.Init(SIZE);
		TimeBetweenAutoShots.GetDelegate.BindUObject(this, &ACsWeapon::GetTimeBetweenShots);
		IsFirePressed.Init(SIZE);
		Last_IsFirePressed.Init(SIZE);
		IsFirePressed_StartTime.Init(SIZE);
		IsFireReleased_StartTime.Init(SIZE);
		Fire_StartTime.Init(SIZE);
		// Charge
		AllowChargeFire.Init(SIZE);
		MaxChargeFireTime.Init(SIZE);
		MaxChargeFireTime.GetDelegate.BindUObject(this, &ACsWeapon::GetMaxChargeFireTime);
		// Spread
		DoSpread.Init(SIZE);
		MinSpread.Init(SIZE);
		MinSpread.GetDelegate.BindUObject(this, &ACsWeapon::GetMinSpread);
		MaxSpread.Init(SIZE);
		MaxSpread.GetDelegate.BindUObject(this, &ACsWeapon::GetMaxSpread);
		SpreadAddedPerShot.Init(SIZE);
		SpreadAddedPerShot.GetDelegate.BindUObject(this, &ACsWeapon::GetSpreadAddedPerShot);
		SpreadRecoveryRate.Init(SIZE);
		SpreadRecoveryRate.GetDelegate.BindUObject(this, &ACsWeapon::GetSpreadRecoveryRate);
		FiringSpreadRecoveryDelay.Init(SIZE);
		FiringSpreadRecoveryDelay.GetDelegate.BindUObject(this, &ACsWeapon::GetFiringSpreadRecoveryDelay);
		CurrentBaseSpread.Init(SIZE);
		CurrentSpread.Init(SIZE);
		LastSpreadFireTime.Init(SIZE);
		// Anim
		LoopFireAnim.Init(SIZE);
		DoScaleFireAnim.Init(SIZE);
		// Sound
		LoopFireSound.Init(SIZE);
		// Hitscan
		IsHitscan.Init(SIZE);
		DoesHitscanUseRadius.Init(SIZE);
		DoesHitscanSimulateProjectileDuration.Init(SIZE);
		ObstaclePenetrations.Init(SIZE);
		ObstaclePenetrations.GetDelegate.BindUObject(this, &ACsWeapon::GetObstaclePenetractions);
		PawnPenetrations.Init(SIZE);
		PawnPenetrations.GetDelegate.BindUObject(this, &ACsWeapon::GetPawnPenetrations);
	}
	// Reload
	{
		ReloadTime.Init(1);
		ReloadTime.GetDelegate.BindUObject(this, &ACsWeapon::GetReloadTime);
		AllowRechargeAmmo.Init(1);
		AllowRechargeAmmoDuringFire.Init(1);
		RechargeSecondsPerAmmo.Init(1);
		RechargeSecondsPerAmmo.GetDelegate.BindUObject(this, &ACsWeapon::GetRechargeSecondsPerAmmo);
		RechargeStartupDelay.Init(1);
		RechargeStartupDelay.GetDelegate.BindUObject(this, &ACsWeapon::GetRechargeStartupDelay);
	}
}

	// Set
#pragma region

void ACsWeapon::SetMemberValue_bool(const TEnumAsByte<ECsWeaponCacheMultiValueMember::Type> &Member, const int32 &Index, const bool &Value)
{
	// Firing
	{
		if (Member == ECsWeaponCacheMultiValueMember::IsFirePressed) { return IsFirePressed.Set(Index, Value); }
		if (Member == ECsWeaponCacheMultiValueMember::Last_IsFirePressed) { return Last_IsFirePressed.Set(Index, Value); }
	}
}

void ACsWeapon::SetMemberValue_Script_bool(const FString &MemberName, const int32 &Index, const bool &Value)
{
#if WITH_EDITOR
	SetMemberValue_bool(ECsWeaponCacheMultiValueMember::ToType(MemberName), Index, Value);
#endif // #if WITH_EDITOR
}

void ACsWeapon::SetMemberValue_uint8(const TEnumAsByte<ECsWeaponCacheMultiValueMember::Type> &Member, const int32 &Index, const uint8 &Value)
{
	// Firing
	{
		if (Member == ECsWeaponCacheMultiValueMember::CurrentProjectilePerShotIndex) { CurrentProjectilePerShotIndex.Set(Index, Value); }
	}
}

void ACsWeapon::SetMemberValue_Script_uint8(const FString &MemberName, const int32 &Index, const uint8 &Value)
{
#if WITH_EDITOR
	SetMemberValue_uint8(ECsWeaponCacheMultiValueMember::ToType(MemberName), Index, Value);
#endif // #if WITH_EDITOR
}

void ACsWeapon::SetMemberValue_int32(const TEnumAsByte<ECsWeaponCacheMultiValueMember::Type> &Member, const int32 &Index, const int32 &Value)
{
	// Firing
	{
	}
}

void ACsWeapon::SetMemberValue_Script_int32(const FString &MemberName, const int32 &Index, const int32 &Value)
{
#if WITH_EDITOR
	SetMemberValue_int32(ECsWeaponCacheMultiValueMember::ToType(MemberName), Index, Value);
#endif // #if WITH_EDITOR
}

void ACsWeapon::SetMemberValue_float(const TEnumAsByte<ECsWeaponCacheMultiValueMember::Type> &Member, const int32 &Index, const float &Value)
{
	// Firing
	{
		if (Member == ECsWeaponCacheMultiValueMember::IsFirePressed_StartTime) { return IsFirePressed_StartTime.Set(Index, Value); }
		if (Member == ECsWeaponCacheMultiValueMember::IsFireReleased_StartTime) { return IsFireReleased_StartTime.Set(Index, Value); }
		// Spread
		if (Member == ECsWeaponCacheMultiValueMember::CurrentBaseSpread) { CurrentBaseSpread.Set(Index, Value); }
		if (Member == ECsWeaponCacheMultiValueMember::CurrentSpread) { CurrentSpread.Set(Index, Value); }
		if (Member == ECsWeaponCacheMultiValueMember::LastSpreadFireTime) { LastSpreadFireTime.Set(Index, Value); }
	}
}

void ACsWeapon::SetMemberValue_Script_float(const FString &MemberName, const int32 &Index, const float &Value)
{
#if WITH_EDITOR
	SetMemberValue_float(ECsWeaponCacheMultiValueMember::ToType(MemberName), Index, Value);
#endif // #if WITH_EDITOR
}

#pragma endregion Set

	// Get
#pragma region

bool ACsWeapon::GetMemberValue_bool(const TEnumAsByte<ECsWeaponCacheMultiValueMember::Type> &Member, const int32 &Index)
{
	// Firing
	{
		if (Member == ECsWeaponCacheMultiValueMember::DoFireOnRelease) { return DoFireOnRelease.Get(Index); }
		if (Member == ECsWeaponCacheMultiValueMember::IsFullAuto) { return IsFullAuto.Get(Index); }
		if (Member == ECsWeaponCacheMultiValueMember::IsFirePressed) { return IsFirePressed.Get(Index); }
		if (Member == ECsWeaponCacheMultiValueMember::Last_IsFirePressed) { return Last_IsFirePressed.Get(Index); }
		// Charge
		if (Member == ECsWeaponCacheMultiValueMember::AllowChargeFire) { return AllowChargeFire.Get(Index); }
		// Spread
		if (Member == ECsWeaponCacheMultiValueMember::DoSpread) { return DoSpread.Get(Index); }

		if (Member == ECsWeaponCacheMultiValueMember::LoopFireAnim) { return LoopFireAnim.Get(Index); }
		if (Member == ECsWeaponCacheMultiValueMember::DoScaleFireAnim) { return DoScaleFireAnim.Get(Index); }
		if (Member == ECsWeaponCacheMultiValueMember::LoopFireSound) { return LoopFireSound.Get(Index); }
		// Hitscan
		if (Member == ECsWeaponCacheMultiValueMember::IsHitscan) { return LoopFireAnim.Get(Index); }
		if (Member == ECsWeaponCacheMultiValueMember::DoesHitscanUseRadius) { return DoesHitscanUseRadius.Get(Index); }
		if (Member == ECsWeaponCacheMultiValueMember::DoesHitscanSimulateProjectileDuration) { return DoesHitscanSimulateProjectileDuration.Get(Index); }
	}
	// Reload
	{
		if (Member == ECsWeaponCacheMultiValueMember::AllowRechargeAmmo) { return AllowRechargeAmmo.Get(Index); }
		if (Member == ECsWeaponCacheMultiValueMember::AllowRechargeAmmoDuringFire) { return AllowRechargeAmmoDuringFire.Get(Index); }
	}
	return false;
}

bool ACsWeapon::GetMemberValue_Script_bool(const FString &MemberName, const int32 &Index)
{
#if WITH_EDITOR
	return GetMemberValue_bool(ECsWeaponCacheMultiValueMember::ToType(MemberName), Index);
#endif // #if WITH_EDITOR
	return false;
}

uint8 ACsWeapon::GetMemberValue_uint8(const TEnumAsByte<ECsWeaponCacheMultiValueMember::Type> &Member, const int32 &Index)
{
#if WITH_EDITOR
	// Firing
	{
		if (Member == ECsWeaponCacheMultiValueMember::ProjectilesPerShot) { return ProjectilesPerShot.GetEX((TCsWeaponFire)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::CurrentProjectilePerShotIndex) { return CurrentProjectilePerShotIndex.Get(Index); }
	}
#endif // #if WITH_EDITOR
	return 0;
}

uint8 ACsWeapon::GetMemberValue_Script_uint8(const FString &MemberName, const int32 &Index)
{
#if WITH_EDITOR
	return GetMemberValue_uint8(ECsWeaponCacheMultiValueMember::ToType(MemberName), Index);
#endif // #if WITH_EDITOR
	return 0;
}

int32 ACsWeapon::GetMemberValue_int32(const TEnumAsByte<ECsWeaponCacheMultiValueMember::Type> &Member, const int32 &Index)
{
	// Firing
	{
		if (Member == ECsWeaponCacheMultiValueMember::MaxAmmo) { return MaxAmmo.GetEX((TCsWeaponFire)Index); }
		// Hitscan
		if (Member == ECsWeaponCacheMultiValueMember::ObstaclePenetrations) { return ObstaclePenetrations.GetEX((TCsWeaponFire)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::PawnPenetrations) { return PawnPenetrations.GetEX((TCsWeaponFire)Index); }
	}
	return 0;
}

int32 ACsWeapon::GetMemberValue_Script_int32(const FString &MemberName, const int32 &Index)
{
#if WITH_EDITOR
	return GetMemberValue_int32(ECsWeaponCacheMultiValueMember::ToType(MemberName), Index);
#endif // #if WITH_EDITOR
	return 0;
}

float ACsWeapon::GetMemberValue_float(const TEnumAsByte<ECsWeaponCacheMultiValueMember::Type> &Member, const int32 &Index)
{
	// Firing
	{
		if (Member == ECsWeaponCacheMultiValueMember::TimeBetweenProjectilesPerShot) { return TimeBetweenProjectilesPerShot.GetEX((TCsWeaponFire)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::TimeBetweenShots) { return TimeBetweenShots.GetEX((TCsWeaponFire)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::TimeBetweenAutoShots) { return TimeBetweenAutoShots.GetEX((TCsWeaponFire)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::IsFirePressed_StartTime) { return IsFirePressed_StartTime.Get(Index); }
		if (Member == ECsWeaponCacheMultiValueMember::IsFireReleased_StartTime) { return IsFireReleased_StartTime.Get(Index); }
		// Charge
		if (Member == ECsWeaponCacheMultiValueMember::MaxChargeFireTime) { return MaxChargeFireTime.GetEX((TCsWeaponFire)Index); }
		// Spread
		if (Member == ECsWeaponCacheMultiValueMember::MinSpread) { return MinSpread.GetEX((TCsWeaponFire)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::MaxSpread) { return MaxSpread.GetEX((TCsWeaponFire)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::SpreadAddedPerShot) { return SpreadAddedPerShot.GetEX((TCsWeaponFire)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::SpreadRecoveryRate) { return SpreadRecoveryRate.GetEX((TCsWeaponFire)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::FiringSpreadRecoveryDelay) { return FiringSpreadRecoveryDelay.GetEX((TCsWeaponFire)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::CurrentBaseSpread) { return CurrentBaseSpread.Get(Index); }
		if (Member == ECsWeaponCacheMultiValueMember::CurrentSpread) { return CurrentSpread.Get(Index); }
		if (Member == ECsWeaponCacheMultiValueMember::LastSpreadFireTime) { return LastSpreadFireTime.Get(Index); }
	}
	// Reload
	{
		if (Member == ECsWeaponCacheMultiValueMember::ReloadTime) { return ReloadTime.GetEX((TCsWeaponFire)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::RechargeSecondsPerAmmo) { return RechargeSecondsPerAmmo.GetEX((TCsWeaponFire)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::RechargeStartupDelay) { return RechargeStartupDelay.GetEX((TCsWeaponFire)Index); }
	}
	return 0.0f;
}

float ACsWeapon::GetMemberValue_Script_float(const FString &MemberName, const int32 &Index)
{
#if WITH_EDITOR
	return GetMemberValue_float(ECsWeaponCacheMultiValueMember::ToType(MemberName), Index);
#endif // #if WITH_EDITOR
	return 0.0f;
}

#pragma endregion Get

	// Add
#pragma region

void ACsWeapon::AddMemberValue_uint8(const int32 &Index, const FString &MemberName, const uint8 &Value)
{
#if WITH_EDITOR
	// Firing
	{
		if (MemberName == "CurrentProjectilePerShotIndex") { return CurrentProjectilePerShotIndex.Add(Index, Value); }
	}
#endif // #if WITH_EDITOR
}

#pragma endregion Add

#pragma endregion Members

// Data
#pragma region

ACsData_Weapon* ACsWeapon::GetMyData_Weapon()
{
	return MyData_Weapon.IsValid() ? MyData_Weapon.Get() : nullptr;
}

#pragma endregion Data

// Routines
#pragma region

void ACsWeapon::AddRoutine(UObject* InWeapon, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<ACsWeapon>(InWeapon)->AddRoutine_Internal(Routine, (TEnumAsByte<ECsWeaponRoutine::Type>)Type);
}

bool ACsWeapon::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	TCsWeaponRoutine RoutineType = (TCsWeaponRoutine)Type;

	// PlayAnimation_Reload_Internal
	if (RoutineType == ECsWeaponRoutine::PlayAnimation_Reload_Internal)
	{
		PlayAnimation_Reload_Internal_Routine = Routine;
		return true;
	}
	// StartChargeShot_Internal
	if (RoutineType == ECsWeaponRoutine::StartChargeFire_Internal)
	{
		StartChargeFire_Internal_Routine = Routine;
		return true;
	}
	// FireWeapon_Internal
	if (RoutineType == ECsWeaponRoutine::FireWeapon_Internal)
	{
		FireWeapon_Internal_Routine = Routine;
		return true;
	}
	return false;
}

void ACsWeapon::RemoveRoutine(UObject* InWeapon, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<ACsWeapon>(InWeapon)->RemoveRoutine_Internal(Routine, (TEnumAsByte<ECsWeaponRoutine::Type>)Type);
}

bool ACsWeapon::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	TCsWeaponRoutine RoutineType = (TCsWeaponRoutine)Type;

	// PlayAnimation_Reload_Internal
	if (RoutineType == ECsWeaponRoutine::PlayAnimation_Reload_Internal)
	{
		check(Routine == PlayAnimation_Reload_Internal_Routine);
		PlayAnimation_Reload_Internal_Routine = nullptr;
		return true;
	}
	// StartChargeShot_Internal
	if (RoutineType == ECsWeaponRoutine::StartChargeFire_Internal)
	{
		check(Routine == StartChargeFire_Internal_Routine);
		StartChargeFire_Internal_Routine = nullptr;
		return true;
	}
	// FireWeapon_Internal
	if (RoutineType == ECsWeaponRoutine::FireWeapon_Internal)
	{
		check(Routine == FireWeapon_Internal_Routine);
		FireWeapon_Internal_Routine = nullptr;
		return true;
	}
	return false;
}

void ACsWeapon::ClearRoutines()
{
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();

	Scheduler->BroadcastMessage(ECsCoroutineSchedule::Tick, ECsCoroutineMessage::Stop, FName("Stop PlayAnimation_Reload_Internal"), this);
	Scheduler->BroadcastMessage(ECsCoroutineSchedule::Tick, ECsCoroutineMessage::Stop, FName("Stop StartChargeFire_Internal"), this);
	Scheduler->BroadcastMessage(ECsCoroutineSchedule::Tick, ECsCoroutineMessage::Stop, FName("Stop FireWeapon_Internal"), this);
}

#pragma endregion Routines

// Owner
#pragma region

void ACsWeapon::SetMyOwner(UObject* InMyOwner)
{
	MyOwner = InMyOwner;
}

UObject* ACsWeapon::GetMyOwner()
{
	return MyOwner.IsValid() ? MyOwner.Get() : nullptr;
}

void ACsWeapon::SetMyPawn(class ACsPawn* InMyPawn)
{
	SetMyOwner(InMyPawn);

	MyPawn	   = InMyPawn;
	Instigator = InMyPawn;

	SetOwner(InMyPawn);
}

ACsPawn* ACsWeapon::GetMyPawn()
{
	return MyPawn.IsValid() ? MyPawn.Get() : nullptr;
}

TEnumAsByte<ECsViewType::Type> ACsWeapon::GetCurrentViewType()
{
#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		if (UCsAnimInstance* AnimInstance = Cast<UCsAnimInstance>(GetMyOwner()))
			return AnimInstance->CurrentViewType;
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		if (ACsPawn* Pawn = GetMyPawn())
			return UCsCommon::IsLocalPawn(GetWorld(), Pawn) ? ECsViewType::FirstPerson : ECsViewType::ThirdPerson;
	}
	return ECsViewType::ThirdPerson;
}

#pragma endregion Owner

// State
#pragma region

void ACsWeapon::OnTick(const float &DeltaSeconds)
{
#if WITH_EDITOR 
	if (Override_OnTick_ScriptEvent.IsBound())
	{
		if (CsCVarLogOverrideFunctions->GetInt() == CS_CVAR_DISPLAY)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsWeapon::OnTick (%s): Using Override Function."), *GetName());
		}
		Override_OnTick_ScriptEvent.Broadcast(WeaponIndex, DeltaSeconds);
		return;
	}
#endif // #if WITH_EDITOR

#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		const float TimeSeconds = GetWorld()->GetTimeSeconds();

		// Spread
		for (uint8 I = 0; I < FIRE_TYPE_MAX; I++)
		{
			const TCsWeaponFire FireType = (TCsWeaponFire)I;

			if (DoSpread.Get(I))
			{
				// Firing
				if (TimeSeconds - LastSpreadFireTime.Get(I) > FiringSpreadRecoveryDelay.Get(I))
				{
					CurrentBaseSpread.Set(CS_WEAPON_DATA_VALUE, FMath::Max(CurrentBaseSpread.Get(CS_WEAPON_DATA_VALUE) - (SpreadRecoveryRate.GetEX(FireType) * DeltaSeconds), MinSpread.GetEX(FireType)));
				}
				CurrentSpread.Set(CS_WEAPON_DATA_VALUE, FMath::Clamp(CurrentBaseSpread.Get(CS_WEAPON_DATA_VALUE), 0.f, MaxSpread.GetEX(FireType)));
			}
		}
	}

#if WITH_EDITOR 
	OnTick_ScriptEvent.Broadcast(WeaponIndex, DeltaSeconds);
#endif // #if WITH_EDITOR

	OnTick_HandleStates();

	Last_IsFirePressed  = IsFirePressed;
}

void ACsWeapon::OnTick_HandleStates()
{
	ACsData_Weapon* Data_Weapon = GetMyData_Weapon();
	const uint8 maxAmmo			 = MaxAmmo.GetEX(CS_WEAPON_DATA_VALUE);

	const float TimeSeconds = GetWorld()->GetTimeSeconds();

	// Recharge Ammo
	if (AllowRechargeAmmo.Get(CS_WEAPON_DATA_VALUE) && 
		IsRechargingAmmo &&
		!HasUnlimitedAmmo && 
		CurrentAmmo < maxAmmo)
	{
		if (TimeSeconds > NextRechargeAmmoTime)
		{
			CurrentAmmo++;
			CurrentAmmo = FMath::Min(CurrentAmmo, maxAmmo);

			if (CurrentAmmo == maxAmmo)
			{
				IsRechargingAmmo = false;
			}
			else
			{
				NextRechargeAmmoTime = NextRechargeAmmoTime + RechargeSecondsPerAmmo.GetEX(CS_WEAPON_DATA_VALUE);
			}
		}
	}

	// Handle Fire / Melee / etc from Idle
	CheckState_Idle();

	// Firing
	if (CurrentState == FiringState)
	{
		bool Pass = false;

		for (uint8 I = 0; I < FIRE_TYPE_MAX; I++)
		{
			const TCsWeaponFire FireType = (TCsWeaponFire)I;

			const bool IsPressed = IsFirePressed.Get(FireType);

			const bool Pass_AutoShots = IsPressed && IsFullAuto.Get(FireType) && TimeSeconds - Fire_StartTime.Get(FireType) > TimeBetweenAutoShots.GetEX(FireType);
			const bool Pass_Shots	  = IsPressed && TimeSeconds - Fire_StartTime.Get(FireType) > TimeBetweenShots.GetEX(FireType);

			if (Pass_AutoShots || Pass_Shots)
			{
				Pass |= true;

				// If out of ammo, Reload
				if (CurrentAmmo == 0)
				{
					StopSound(FireType, FireSound);

					ReloadStartTime = GetWorld()->TimeSeconds;
					IsReloading		= true;

					PlayAnimation_Reload();

					LastState    = CurrentState;
					CurrentState = ReloadingState;
				}
				else
				{
					// If using an automatic weapon / continuous fire, then
					// do the firing again
					if ((Pass_AutoShots && CanFire_Auto(FireType)) ||
						(Pass_Shots && CanFire(FireType)))
					{
						HandleState_Firing(FireType);
					}
					// Stop Firing, go to Idle
					else
					{
						//StopFireSound();
						StopSound(FireType, FireSound);
						StopAnimation(FireType, FireAnim);

						LastState    = CurrentState;
						CurrentState = IdleState;

						if (AllowRechargeAmmo.Get(CS_WEAPON_DATA_VALUE) && 
							!AllowRechargeAmmoDuringFire.Get(CS_WEAPON_DATA_VALUE))
						{
							RechargeAmmo_StartTime = TimeSeconds;
							NextRechargeAmmoTime   = RechargeAmmo_StartTime + RechargeSecondsPerAmmo.GetEX(CS_WEAPON_DATA_VALUE) + RechargeStartupDelay.GetEX(CS_WEAPON_DATA_VALUE);
							IsRechargingAmmo	   = true;
						}
						CheckState_Idle();
					}
				}
			}
		}
	}

	// Reloading
	if (CurrentState == ReloadingState)
	{
		if (TimeSeconds - ReloadStartTime > ReloadTime.GetEX(CS_WEAPON_DATA_VALUE))
		{
			CurrentAmmo  = maxAmmo;
			IsReloading  = false;
			LastState    = CurrentState;
			CurrentState = IdleState;

#if WITH_EDITOR 
			// In Editor Preview Window
			if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
			{
			}
			// In Game
			else
#endif // #if WITH_EDITOR
			{
				//MyPawn->OnReloadFinishEvent.Broadcast();
			}
			CheckState_Idle();
		}
	}
}
/*
void ACsWeapon::OnRep_Seed()
{
	FMath::SRandInit(Seed);
	RandStream = FRandomStream(Seed);
	bSeedInitialized = true;
}
*/
void ACsWeapon::CheckState_Idle()
{
#if WITH_EDITOR
	if (Override_CheckState_Idle_ScriptEvent.IsBound())
	{
		if (CsCVarLogOverrideFunctions->GetInt() == CS_CVAR_DISPLAY)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsWeapon::CheckState_Idle (%s): Using Override Function."), *GetName());
		}
		Override_CheckState_Idle_ScriptEvent.Broadcast(WeaponIndex);
		return;
	}
#endif // #if WITH_EDITOR

	if (CurrentState == IdleState)
	{
		const float TimeSeconds = GetWorld()->GetTimeSeconds();

		if (IsReloading &&
			TimeSeconds - ReloadStartTime > ReloadTime.GetEX(CS_WEAPON_DATA_VALUE))
		{
			CurrentAmmo = MaxAmmo.GetEX(CS_WEAPON_DATA_VALUE);
			IsReloading = false;
		}

		if (!IsReloading &&
			CurrentAmmo == 0 &&
			TimeSeconds - Fire_StartTime.Min() > FMath::Max(TimeBetweenShots.Max(), TimeBetweenAutoShots.Max()))
		{
			ReloadStartTime = TimeSeconds;
			IsReloading		= true;

			PlayAnimation_Reload();

			LastState	 = CurrentState;
			CurrentState = ReloadingState;
		}

		HandleChargeFire();

		bool Pass_Firing = false;

		for (uint8 I = 0; I < FIRE_TYPE_MAX; I++)
		{
			const TCsWeaponFire FireType = (TCsWeaponFire)I;

			if ((IsFullAuto.Get(I) && CanFire_Auto(FireType)) ||
				CanFire(FireType))
			{
				Pass_Firing |= true;

				if (LoopFireSound.Get(I))
					PlaySound(FireType, FireSound);

				if (LoopFireAnim.Get(I))
					PlayAnimation(FireType, FireAnim);

				if (AllowRechargeAmmo.Get(CS_WEAPON_DATA_VALUE) && !AllowRechargeAmmoDuringFire.Get(CS_WEAPON_DATA_VALUE))
				{
					IsRechargingAmmo = false;
				}
				HandleState_Firing(FireType);
			}
		}
	}
}

void ACsWeapon::HandleState_Firing(const TCsWeaponFire &FireType)
{
	CurrentProjectilePerShotIndex.Set(FireType, CurrentAmmo > ProjectilesPerShot.GetEX(FireType) ? 0 : ProjectilesPerShot.GetEX(FireType) - CurrentAmmo);

	FireWeapon(FireType);

	ACsData_Weapon* Data_Weapon = GetMyData_Weapon();

	const float TimeSeconds = GetWorld()->TimeSeconds;

	if (!HasUnlimitedAmmo)
	{
		// Recharge Ammo
		if (AllowRechargeAmmo.Get(CS_WEAPON_DATA_VALUE))
		{
			if (AllowRechargeAmmoDuringFire.Get(CS_WEAPON_DATA_VALUE))
			{
				IsRechargingAmmo	 = true;
				NextRechargeAmmoTime = TimeSeconds + RechargeSecondsPerAmmo.GetEX(CS_WEAPON_DATA_VALUE) + RechargeStartupDelay.GetEX(CS_WEAPON_DATA_VALUE);
			}
		}
	}

	Fire_StartTime.Set(FireType, TimeSeconds);
	LastState	   = CurrentState;
	CurrentState   = FiringState;
}

bool ACsWeapon::CanFire(const TCsWeaponFire &FireType)
{
	const float TimeSeconds = GetWorld()->GetTimeSeconds();

	const bool IsBot			  = false;// Cast<AShooterBot>(MyPawn) != nullptr;
	const bool AllowFire		  = !DoingEquipTransition && IsEquipped && TimeSeconds - Fire_StartTime.Get(FireType) > TimeBetweenShots.GetEX(FireType);
	const bool Pass_IsFirePressed = IsFirePressed.Get(FireType) && !DoFireOnRelease.Get(FireType) && (IsFullAuto.Get(FireType) || (!Last_IsFirePressed.Get(FireType) && IsFirePressed.Get(FireType)) || IsBot) && AllowFire;
	const bool Pass_FireOnRelease = DoFireOnRelease.Get(FireType) && ((Last_IsFirePressed.Get(FireType) && !IsFirePressed.Get(FireType))) && AllowFire;
	const bool Pass_Ammo		  = CurrentAmmo > 0 || HasUnlimitedAmmo;

	return (Pass_IsFirePressed || Pass_FireOnRelease) && Pass_Ammo && !IsReloading;
}

bool ACsWeapon::CanFire_Auto(const TCsWeaponFire &FireType)
{
	const float TimeSeconds = GetWorld()->GetTimeSeconds();

	const bool IsBot			  = false;// Cast<AShooterBot>(MyPawn) != nullptr;
	const bool AllowFire		  = !DoingEquipTransition && IsEquipped && TimeSeconds - Fire_StartTime.Get(FireType) > TimeBetweenAutoShots.GetEX(FireType);
	const bool Pass_IsFirePressed = IsFirePressed.Get(FireType) && !DoFireOnRelease.Get(FireType) && (IsFullAuto.Get(FireType) || (!Last_IsFirePressed.Get(FireType) && IsFirePressed.Get(FireType)) || IsBot) && AllowFire;
	const bool Pass_FireOnRelease = DoFireOnRelease.Get(FireType) && ((Last_IsFirePressed.Get(FireType) && !IsFirePressed.Get(FireType))) && AllowFire;
	const bool Pass_Ammo		  = CurrentAmmo > 0 || HasUnlimitedAmmo;

	return (Pass_IsFirePressed || Pass_FireOnRelease) && Pass_Ammo && !IsReloading;
}

void ACsWeapon::Enable()
{
	CurrentAmmo = MaxAmmo.Get(CS_WEAPON_DATA_VALUE);
}

void ACsWeapon::Disable()
{
	if (CurrentState == FiringState || GetSound(FireSound))
	{
		for (uint8 I = 0; I < FIRE_TYPE_MAX; I++)
		{
			StopSound((TCsWeaponFire)I, FireSound);
		}
	}

	LastState    = CurrentState;
	CurrentState = IdleState;

	for (uint8 I = 0; I < FIRE_TYPE_MAX; I++)
	{
		IsFirePressed.Set(I, false);
		Last_IsFirePressed.Set(I, false);
	}

	PerformingChargeFire = false;

	if (GetMyData_Weapon())
	{
		for (uint8 I = 0; I < FIRE_TYPE_MAX; I++)
		{
			if (LoopFireAnim.Get(I))
				StopAnimation((TCsWeaponFire)I, FireAnim);
		}
	}

	for (uint8 I = 0; I < CS_PROJECTILE_FIRE_CACHE_POOL_SIZE; ++I)
	{
		ProjectileFireCaches[I].Reset();
	}

	ProjectileFireCachePoolIndex = 0;

	ClearRoutines();
}

void ACsWeapon::Reset()
{
	Disable();
}

void ACsWeapon::Show(){}
void ACsWeapon::Hide(){}

#pragma endregion State

void ACsWeapon::OnCalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
}

// Animation
#pragma region

void ACsWeapon::PlayAnimation(const TCsWeaponFire &FireType, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/)
{
}

void ACsWeapon::PlayAnimation_Reload()
{
	if (PlayAnimation_Reload_Internal_Routine && PlayAnimation_Reload_Internal_Routine->IsValid())
		PlayAnimation_Reload_Internal_Routine->End();

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	CsCoroutine Function		  = &ACsWeapon::PlayAnimation_Reload_Internal;
	CsCoroutineStopCondition Stop = &ACsWeapon::PlayAnimation_Reload_StopCondition;
	CsAddRoutine Add			  = &ACsWeapon::AddRoutine;
	CsRemoveRoutine Remove		  = &ACsWeapon::RemoveRoutine;
	const uint8 Type			  = (uint8)ECsWeaponRoutine::PlayAnimation_Reload_Internal;

	FCsRoutine* R = Scheduler->Allocate(Schedule, Function, Stop, this, Add, Remove, Type, true, false);
	R->timers[0]  = GetWorld()->TimeSeconds;
	R->ints[0]    = 0;
	R->floats[0]  = GetAnimationLength(FireType_MAX, ReloadAnim);

	Scheduler->StartRoutine(Schedule, R);
}

PT_THREAD(ACsWeapon::PlayAnimation_Reload_Internal(struct FCsRoutine* r))
{
	ACsWeapon* mw			 = Cast<ACsWeapon>(r->GetActor());
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w				 = mw->GetWorld();

	const TCsWeaponAnim ReloadAnim = mw->ReloadAnim;
	const float ReloadTime		   = r->floats[0];

	const float CurrentTime = w->GetTimeSeconds();
	const float StartTime   = r->startTime;

	CS_COROUTINE_BEGIN(r);

	r->AddMessage(ECsCoroutineMessage::Stop, FName("Stop PlayAnimation_Reload_Internal"));

	mw->PlayAnimation(mw->FireType_MAX, ReloadAnim, 0);

	if (ReloadTime > 0)
		CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - StartTime >= ReloadTime);
	
	CS_COROUTINE_END(r);
}

void ACsWeapon::PlayAnimation_Reload_StopCondition(struct FCsRoutine* r)
{
	ACsWeapon* mw = Cast<ACsWeapon>(r->GetActor());

#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(mw->GetWorld()) &&
		mw)
	{
		if (!mw->GetMyOwner())
			r->End();
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		if (!mw)
			r->End();
	}
}

float ACsWeapon::GetAnimationLength(const TCsWeaponFire &FireType, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/)
{
	return 0.0f;
}

void ACsWeapon::StopAnimation(const TCsWeaponFire &FireType, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/)
{
}

#pragma endregion Animation

// Sound
#pragma region

UObject* ACsWeapon::GetSoundParent() { return nullptr; }
ACsSound* ACsWeapon::GetSound(const TCsWeaponSound &SoundType){ return nullptr; }

void ACsWeapon::PlaySound(const TCsWeaponFire &FireType, const TCsWeaponSound &SoundType)
{
	ACsData_Weapon* Data	   = GetMyData_Weapon();
	const TCsViewType ViewType = GetCurrentViewType();

	Data->PlaySound(GetWorld(), ViewType, FireType, SoundType, GetMyPawn(), GetSoundParent());
}

void ACsWeapon::StopSound(const TCsWeaponFire &FireType, const TCsWeaponSound &SoundType)
{
	ACsData_Weapon* Data	   = GetMyData_Weapon();
	const TCsViewType ViewType = GetCurrentViewType();

	Data->StopSound(GetWorld(), ViewType, FireType, SoundType, GetMyPawn(), GetSoundParent());
}

#pragma endregion Sound

// Firing
#pragma region

int32 ACsWeapon::GetMaxAmmo(const int32 &Index) { return MaxAmmo.Get(Index); }
uint8 ACsWeapon::GetProjectilesPerShot(const TCsWeaponFire &FireType) { return ProjectilesPerShot.Get(FireType); }
float ACsWeapon::GetTimeBetweenProjectilesPerShot(const TCsWeaponFire &FireType) { return TimeBetweenProjectilesPerShot.Get(FireType); }
float ACsWeapon::GetTimeBetweenShots(const TCsWeaponFire &FireType) { return TimeBetweenShots.Get(FireType); }
float ACsWeapon::GetTimeBetweenAutoShots(const TCsWeaponFire &FireType) { return TimeBetweenAutoShots.Get(FireType); }

void ACsWeapon::SetIsFirePressed(const TCsWeaponFire &FireType, const bool &Value, const bool &DoOnTick)
{
	IsFirePressed.Set(FireType, Value);

	const float TimeSeconds = GetWorld()->GetTimeSeconds();

	if (Value)
	{
		IsFirePressed_StartTime.Set(FireType, TimeSeconds);
	}
	else
	{
		IsFireReleased_StartTime.Set(FireType, TimeSeconds);
	}

#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		if (DoOnTick)
			OnTick(0.0f);
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		if (DoOnTick)
			OnTick(0.0f);
	}
}

	// Charge
#pragma region

float ACsWeapon::GetMaxChargeFireTime(const TCsWeaponFire &FireType) { return MaxChargeFireTime.Get(FireType); }

void ACsWeapon::HandleChargeFire()
{
	if (PerformingChargeFire)
		return;
	
	for (uint8 I = 0; I < FIRE_TYPE_MAX; I++)
	{
		if (AllowChargeFire.Get(I) &&
			IsFirePressed.Get(I))
		{
			StartChargeFire((TCsWeaponFire)I);
			return;
		}
	}
}

void ACsWeapon::StartChargeFire(const TCsWeaponFire &FireType)
{
	PerformingChargeFire = true;
	ChargeFire_StartTime = GetWorld()->TimeSeconds;

	if (StartChargeFire_Internal_Routine && StartChargeFire_Internal_Routine->IsValid())
		StartChargeFire_Internal_Routine->End();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	CsCoroutine Function		  = &ACsWeapon::StartChargeFire_Internal;
	CsCoroutineStopCondition Stop = &ACsWeapon::StartChargeFire_StopCondition;
	CsAddRoutine Add			  = &ACsWeapon::AddRoutine;
	CsRemoveRoutine Remove		  = &ACsWeapon::RemoveRoutine;
	const uint8 Type			  = (uint8)ECsWeaponRoutine::StartChargeFire_Internal;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsRoutine* R					 = Scheduler->Allocate(Schedule, Function, Stop, this, Add, Remove, Type, true, false);
	R->timers[0]					 = GetWorld()->GetTimeSeconds();
	R->ints[0]						 = (uint8)FireType;

	Scheduler->StartRoutine(Schedule, R);
}

PT_THREAD(ACsWeapon::StartChargeFire_Internal(struct FCsRoutine* r))
{
	ACsWeapon* mw			 = Cast<ACsWeapon>(r->GetActor());
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w				 = mw->GetWorld();

	const float CurrentTime = w->TimeSeconds;
	float StartTime			= r->timers[0];
	float WaitTime			= r->floats[0];
	float FireStartLoopTime = FMath::Max(mw->TimeBetweenShots.Max(), mw->TimeBetweenAutoShots.Max());

	const TCsWeaponFire FireType = (TCsWeaponFire)r->ints[0];

	const float StartToLoopBlendTime = 0.1f;

	CS_COROUTINE_BEGIN(r);

	r->AddMessage(ECsCoroutineMessage::Stop, FName("Stop StartChargeFire_Internal"));

	// ChargeFireStart
	mw->PlayAnimation(FireType, mw->ChargeFireStartAnim);

	r->timers[0] = CurrentTime;
	StartTime = CurrentTime;

	r->floats[0] = mw->GetAnimationLength(FireType, mw->ChargeFireStartAnim);
	WaitTime = r->floats[0];

	CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - StartTime >= FMath::Max(WaitTime - StartToLoopBlendTime, 0.0f));

	// ChargeFireLoop
	mw->PlayAnimation(FireType, mw->ChargeFireLoopAnim);

	CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - r->startTime >= FireStartLoopTime);

	CS_COROUTINE_END(r);
}

void ACsWeapon::StartChargeFire_StopCondition(struct FCsRoutine* r)
{
	ACsWeapon* mw = Cast<ACsWeapon>(r->GetActor());

	const TCsWeaponFire FireType = (TCsWeaponFire)r->ints[0];

#if WITH_EDITOR 
	// In Editor Preview Window
	if (mw && UCsCommon::IsPlayInEditorPreview(mw->GetWorld()))
	{
		if (!mw->GetMyOwner())
		{
			mw->StopAnimation(FireType, mw->ChargeFireStartAnim);
			mw->StopAnimation(FireType, mw->ChargeFireLoopAnim);
			r->End();
		}
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		if (mw)
		{
			mw->StopAnimation(FireType, mw->ChargeFireStartAnim);
			mw->StopAnimation(FireType, mw->ChargeFireLoopAnim);
		}
		r->End();
	}
}

float ACsWeapon::GetChargeFireHeldTime()
{
	return GetWorld()->TimeSeconds - ChargeFire_StartTime;
}

float ACsWeapon::GetChargeFireHeldPercent(const TCsWeaponFire &FireType)
{
	return FMath::Clamp(GetChargeFireHeldTime(), 0.0f, MaxChargeFireTime.GetEX(FireType) / MaxChargeFireTime.GetEX(FireType));
}

float ACsWeapon::GetCurrentChargeFireHeldTime()
{
	return PerformingChargeFire ? GetWorld()->TimeSeconds - ChargeFire_StartTime : 0.0f;
}

float ACsWeapon::GetCurrentChargeFireHeldPercent(const TCsWeaponFire &FireType)
{
	return PerformingChargeFire ? FMath::Clamp(GetChargeFireHeldTime(), 0.0f, MaxChargeFireTime.GetEX(FireType) / MaxChargeFireTime.GetEX(FireType)) : 0.0f;
}

void ACsWeapon::StopChargeFire(const TCsWeaponFire &FireType)
{
	if (!AllowChargeFire.Get(FireType))
		return;

	PerformingChargeFire = false;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();

	Scheduler->BroadcastMessage(ECsCoroutineSchedule::Tick, ECsCoroutineMessage::Stop, TEXT("Stop StartChargeFire_Internal"), this);

	if (StartChargeFire_Internal_Routine && StartChargeFire_Internal_Routine->IsValid())
		StartChargeFire_Internal_Routine->End();

	StopAnimation(FireType, ChargeFireStartAnim);
	StopAnimation(FireType, ChargeFireLoopAnim);
}

#pragma endregion Charge

	// Spread
#pragma region

float ACsWeapon::GetMinSpread(const TCsWeaponFire &FireType) { return MinSpread.Get(FireType); }
float ACsWeapon::GetMaxSpread(const TCsWeaponFire &FireType) { return MaxSpread.Get(FireType); }
float ACsWeapon::GetSpreadAddedPerShot(const TCsWeaponFire &FireType) { return SpreadAddedPerShot.Get(FireType); }
float ACsWeapon::GetSpreadRecoveryRate(const TCsWeaponFire &FireType) { return SpreadRecoveryRate.Get(FireType); }
float ACsWeapon::GetFiringSpreadRecoveryDelay(const TCsWeaponFire &FireType) { return FiringSpreadRecoveryDelay.Get(FireType); }
float ACsWeapon::GetMovingSpreadBonus(const TCsWeaponFire &FireType) { return MovingSpreadBonus.Get(FireType); }

#pragma endregion Spread

FVector ACsWeapon::GetFireWeaponStartLocation()
{
	return FVector::ZeroVector;
}

FVector ACsWeapon::GetFireWeaponStartDirection()
{
	return FVector::ZeroVector;
}

FCsProjectileFireCache* ACsWeapon::AllocateProjectileFireCache(const TCsWeaponFire &FireType)
{
	const uint8 Count = CS_PROJECTILE_FIRE_CACHE_POOL_SIZE;
	uint8 PoolIndex	  = 0;
	uint8 OldestIndex = 0;

	for (uint8 I = 0; I < Count; ++I)
	{
		FCsProjectileFireCache* Cache = &ProjectileFireCaches[ProjectileFireCachePoolIndex];

		if (!Cache->IsAllocated)
		{
			Cache->IsAllocated = true;

			Cache->Time = GetWorld()->GetTimeSeconds();
			Cache->RealTime = GetWorld()->GetRealTimeSeconds();
			Cache->Frame = 0;

			Cache->Location		 = GetFireWeaponStartLocation();
			Cache->Direction	 = GetFireWeaponStartDirection();
			Cache->ChargePercent = GetCurrentChargeFireHeldPercent((TCsWeaponFire)(uint8)FireType);

			/*
			ACsGameState* GameState		   = GetWorld()->GetGameState<ACsGameState>();
			ACsPlayerState* MyPlayerState	   = Cast<ACsPlayerState>(MyPawn->PlayerState);
			const uint8 MappingId			   = MyPlayerState ? MyPlayerState->PlayerData.AimAssistTargetMappingId : CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID;
			ACsPlayerState* TargetPlayerState = GameState->GetPlayerState(MappingId);
			ACsCharacter* TargetPawn		   = TargetPlayerState ? TargetPlayerState->GetMyPawn() : nullptr;

			Cache->HomingTarget				   = TargetPawn;
			Cache->HomingAccelerationMagnitude = 100.0f;

			const FName BoneName = TargetPawn ? TargetPawn->GetMesh()->GetBoneName(MyPlayerState->PlayerData.AimAssistBoneIndex) : NAME_Name;

			Cache->HomingBoneName = BoneName;
			*/
			return Cache;
		}

		if (ProjectileFireCaches[OldestIndex].Time < Cache->Time)
			OldestIndex = ProjectileFireCachePoolIndex;
		ProjectileFireCachePoolIndex = (ProjectileFireCachePoolIndex + I) % Count;
	}

	UE_LOG(LogCs, Warning, TEXT("ACsWeapon::AllocateProjectileFireCache: Warning. Pool is exhausted. Using Oldest Active Projectile Fire Cache."));

	ProjectileFireCaches[OldestIndex].IsAllocated = true;
	return &ProjectileFireCaches[OldestIndex];
}

void ACsWeapon::FireWeapon(const TCsWeaponFire &FireType)
{
#if WITH_EDITOR 
	if (Override_FireWeapon_ScriptEvent.IsBound())
	{
		if (CsCVarLogOverrideFunctions->GetInt() == CS_CVAR_DISPLAY)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsWeapon::FireWeapon (%s): Using Override Function."), *GetName());
		}
		Override_FireWeapon_ScriptEvent.Broadcast(WeaponIndex, FireType);
		return;
	}
#endif // #if WITH_EDITOR

	if (FireWeapon_Internal_Routine && FireWeapon_Internal_Routine->IsValid())
		FireWeapon_Internal_Routine->End();

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	CsCoroutine Function		  = &ACsWeapon::FireWeapon_Internal;
	CsCoroutineStopCondition Stop = &ACsWeapon::FireWeapon_StopCondition;
	CsAddRoutine Add			  = &ACsWeapon::AddRoutine;
	CsRemoveRoutine Remove		  = &ACsWeapon::RemoveRoutine;
	const uint8 Type			  = (uint8)ECsWeaponRoutine::FireWeapon_Internal;

	FCsRoutine* R = Scheduler->Allocate(Schedule, Function, Stop, this, Add, Remove, Type, true, false);
	R->timers[0]  = GetWorld()->TimeSeconds;
	R->ints[0]	  = (uint8)FireType;

	Scheduler->StartRoutine(Schedule, R);
}

PT_THREAD(ACsWeapon::FireWeapon_Internal(struct FCsRoutine* r))
{
	ACsWeapon* mw			 = Cast<ACsWeapon>(r->GetActor());
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w				 = mw->GetWorld();

	const TCsWeaponFire FireType = (TCsWeaponFire)r->ints[0];

	const float CurrentTime = w->TimeSeconds;
	float StartTime			= r->timers[0];

#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(w))
	{
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
	}

	CS_COROUTINE_BEGIN(r);

	r->AddMessage(ECsCoroutineMessage::Stop, FName("Stop FireWeapon_Internal"));

	mw->StopChargeFire(FireType);

	do
	{
		{
			// Set the StartTime
			r->timers[0] = CurrentTime;
			StartTime    = CurrentTime;

			// Play Fire Sound
			if (!mw->LoopFireSound.Get(FireType))
				mw->PlaySound(FireType, mw->FireSound);
			// Play Fire Animation
			if (!mw->LoopFireAnim.Get(FireType))
				mw->PlayAnimation(FireType, mw->FireAnim);

#if WITH_EDITOR 
			// In Editor Preview Window
			if (UCsCommon::IsPlayInEditorPreview(w))
			{
			}
			// In Game
			else
#endif // #if WITH_EDITOR
			{
				FCsProjectileFireCache* Cache = mw->AllocateProjectileFireCache(FireType);
				/*
				if (mw->IsHitscan.Get(FireType))
					mw->FireHitscan(FireType, Cache);
				else
					mw->FireProjectile(FireType, Cache);
				*/
				mw->FireProjectile(FireType, Cache);
			}

			mw->PlayMuzzleFlash(FireType);
			
			mw->CurrentProjectilePerShotIndex.Add(FireType, 1);
		}

		if (mw->CurrentProjectilePerShotIndex.Get(FireType) < mw->ProjectilesPerShot.Get(FireType))
		{
			CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - StartTime >= mw->TimeBetweenProjectilesPerShot.Get(FireType));
		}
	} while (mw->CurrentProjectilePerShotIndex.Get(FireType) < mw->ProjectilesPerShot.Get(FireType));

	mw->CurrentState = mw->IdleState;
	CS_COROUTINE_END(r);
}

void ACsWeapon::FireWeapon_StopCondition(struct FCsRoutine* r)
{
	ACsWeapon* mw				  = Cast<ACsWeapon>(r->GetActor());
	const TCsWeaponFire FireType = (TCsWeaponFire)r->ints[0];

#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(mw->GetWorld()) &&
		mw)
	{
		if (!mw->GetMyOwner())
		{
			mw->StopAnimation(FireType, mw->FireAnim);

			r->End();
		}
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		if (mw &&
			!mw->GetMyOwner())
		{
			mw->StopAnimation(FireType, mw->FireAnim);

			FCsProjectileFireCache* Cache = (FCsProjectileFireCache*)r->voidPointers[0];

			Cache->Reset();
			r->End();
		}
	}
}

FVector ACsWeapon::GetOwnerRightVector()
{
	if (AActor* Actor = Cast<AActor>(GetMyOwner()))
		return Actor->GetActorRightVector();
	if (USceneComponent* Component = Cast<USceneComponent>(GetMyOwner()))
		return Component->GetRightVector();
	return FVector::RightVector;
}

void ACsWeapon::FireProjectile(const TCsWeaponFire &FireType, FCsProjectileFireCache* Cache)
{
	const FVector RealStart   = Cache->Location;
	FVector RealDir			  = Cache->Direction;
	const float MaxTraceRange = 30000.0f;
	const FVector RealEnd	  = RealStart + MaxTraceRange * RealDir;

	ACsData_Weapon* Data_Weapon = GetMyData_Weapon();

	const TCsViewType ViewType = GetCurrentViewType();
	const FVector FakeStart	   = GetMuzzleLocation(ViewType, FireType);
	FVector FakeDir			   = (RealEnd - FakeStart).GetSafeNormal();

	// Spread
	if (DoSpread.Get(FireType))
	{
		if (CurrentSpread.Get(FireType) > 0.f)
		{
			// Real
			const float SpreadPitch = RandStream.FRand() * CurrentSpread.Get(FireType);
			const FVector Right		= GetOwnerRightVector();
			FVector Dir				= RealDir.RotateAngleAxis(SpreadPitch, Right);
			const float SpreadRoll  = RandStream.FRand() * 360.f;
			Dir						= Dir.RotateAngleAxis(SpreadRoll, RealDir);

			RealDir = Dir;

			// Fake
			Dir = FakeDir.RotateAngleAxis(SpreadPitch, Right);
			Dir = Dir.RotateAngleAxis(SpreadRoll, FakeDir);

			FakeDir = Dir;
		}
		CurrentBaseSpread.Set(FireType, FMath::Min(CurrentBaseSpread.Get(FireType) + SpreadAddedPerShot.GetEX(FireType), MaxSpread.GetEX(FireType)));
		LastSpreadFireTime.Set(FireType, GetWorld()->TimeSeconds);
	}
	// Update Cache

	ACsGameState* GameState					  = GetWorld()->GetGameState<ACsGameState>();
	ACsManager_Projectile* Manager_Projectile = GameState->Manager_Projectile;
	ACsData_Projectile* Data_Projectile		  = Data_Weapon->GetData_Projectile(FireType, Cache->ChargePercent > 0.0f);

	const bool UseFakeProjectile = Data_Weapon->UseFakeProjectile(FireType);

	// Real
	Cache->Location = RealStart;
	Cache->Direction = RealDir;
	ACsProjectile* RealProjectile = Manager_Projectile->Fire(UseFakeProjectile ? ECsProjectileRelevance::RealInvisible : ECsProjectileRelevance::RealVisible, Data_Projectile, Cache, GetMyOwner(), this);
	// Fake
	if (UseFakeProjectile)
	{
		FCsProjectileFireCache* FakeCache = AllocateProjectileFireCache(FireType);
		FakeCache->Location = FakeStart;
		FakeCache->Direction = FakeDir;
		ACsProjectile* FakeProjectile = Manager_Projectile->Fire(ECsProjectileRelevance::Fake, Data_Projectile, FakeCache, GetMyOwner(), this);

		RealProjectile->FakeProjectile = FakeProjectile;
		FakeCache->Reset();
	}
	Cache->Reset();
}

void ACsWeapon::FireProjectile_Script(const uint8 &FireType, FCsProjectileFireCache &Cache)
{
	FireProjectile((TCsWeaponFire)FireType, &Cache);
}

	// Hitscan
#pragma region

int32 ACsWeapon::GetObstaclePenetractions(const TCsWeaponFire &FireType) { return ObstaclePenetrations.Get(FireType); }
int32 ACsWeapon::GetPawnPenetrations(const TCsWeaponFire &FireType) { return PawnPenetrations.Get(FireType); }

void ACsWeapon::FireHitscan(const TCsWeaponFire &FireType, const FCsProjectileFireCache* Cache)
{
	/*
	ACsCharacter* Pawn					 = GetMyPawn();
	ACsPlayerState* MyPlayerState		 = Cast<ACsPlayerState>(Pawn->PlayerState);
	ACsData_Weapon* Data_Weapon		 = GetMyData_Weapon();
	ACsData_Projectile* Data_Projectile = Data_Weapon->GetData_Projectile(FireType, Cache->ChargePercent > 0.0f);

	const FVector Start		  = Cache->Location;
	const FVector Dir		  = Cache->Direction;
	const float MaxTraceRange = 30000.0f;
	const FVector End		  = Start + MaxTraceRange * Dir;

	FCollisionQueryParams CollisionParams   = FCollisionQueryParams();
	CollisionParams.bReturnPhysicalMaterial = true;
	CollisionParams.AddIgnoredActor(GetMyPawn());

	// See which characters we can hit and which we should ignore
	TArray<ACsCharacter*> HittablePawns;
	
	int32 RecordedPlayerPenetrations   = 0;
	int32 RecordedObstaclePenetrations = 0;
	bool HitFound					   = true;

	// Hit trace/ Hit simulation
	while ((PlayerPenetrations.Get(FireType) < 0 || RecordedPlayerPenetrations <= PlayerPenetrations.Get(FireType)) &&
		   (ObstaclePenetrations.Get(FireType) < 0 || RecordedObstaclePenetrations <= ObstaclePenetrations.Get(FireType)) &&
		    HitFound)
	{
		HitFound = false;

		FHitResult HitResult;

		// Hitscan with cylinder
		if (DoesHitscanUseRadius.Get(FireType))
		{
			// See if this line is close enough to hit any enemy characters
			const int32 HitPawnCount = HittablePawns.Num();

			for (int32 I = HitPawnCount - 1; I >= 0; I--)
			{
				ACsCharacter* HitPawn = HittablePawns[I];
				//AShooterBot* Bot = Cast<AShooterBot>(ThisChar);

				ACsData_Character* Data_Character = HitPawn->GetMyData_Ship();

				const float HeadRadius = Data_Character->HeadCollision.Radius;
				const FName BoneName   = Data_Character->HeadCollision.BoneName;
				const FVector Offset   = Data_Character->HeadCollision.Offset;

				const FVector HeadLocation = HitPawn->GetMesh()->GetBoneLocation(BoneName) + Offset;
				const FVector BodyLocation = HitPawn->GetCapsuleComponent()->GetComponentLocation();

				const FVector BodyLocationXY = FVector(BodyLocation.X, BodyLocation.Y, 0);
				const float BodyLocationZ    = BodyLocation.Z;

				const FVector HeadPoint = FMath::ClosestPointOnSegment(HeadLocation, Start, End);
				const FVector BodyPoint = FMath::ClosestPointOnSegment(BodyLocation, Start, End);

				const FVector BodyPointXY = FVector(BodyPoint.X, BodyPoint.Y, 0);
				const float BodyPointZ    = BodyPoint.Z;

				const float DistanceToHead = FVector::Dist(HeadPoint, HeadLocation);

				const float BodyXYDistFromLine = FVector::Dist(BodyPointXY, BodyLocationXY);
				const float BodyZDistFromLine  = FMath::Abs(BodyLocationZ - BodyPointZ);

				const float CharacterRadius  = HittablePawns[I]->GetCapsuleComponent()->GetScaledCapsuleRadius();
				const float CharacterHeight  = HittablePawns[I]->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
				const float ProjectileRadius = Data_Projectile->SphereRadius;

				// Head is close enough to potential trace. Try tracing directly to the Head
				if (DistanceToHead < HeadRadius + ProjectileRadius)
				{
					const float TraceDist	  = 1.5f * (HeadLocation - Start).Size();
					const FVector TargetPoint = HeadLocation + TraceDist * (HeadLocation - Start);
					HitFound				  = GetWorld()->LineTraceSingleByChannel(HitResult, Start, TargetPoint, MBO_COLLISION_PROJECTILE, CollisionParams);
					HittablePawns.RemoveAt(I);
					break;
				}
				// Body is close enough to potential trace. Try tracing directly to the body
				else 
				if (BodyXYDistFromLine < CharacterRadius + ProjectileRadius && BodyZDistFromLine < CharacterHeight + ProjectileRadius)
				{
					const float TraceDist     = 1.5f * (BodyLocation - Start).Size();
					const FVector TargetPoint = BodyLocation + TraceDist * (BodyLocation - Start);
					HitFound				  = GetWorld()->LineTraceSingleByChannel(HitResult, Start, TargetPoint, MBO_COLLISION_PROJECTILE, CollisionParams);
					HittablePawns.RemoveAt(I);
					break;
				}
			}
		}
		// Hit NOT Found and NO Hitscan with cylinder
		if (!HitFound || 
			!DoesHitscanUseRadius.Get(FireType))
		{
			HitFound = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, MBO_COLLISION_PROJECTILE, CollisionParams);
		}
		// Hit IS Found. Check penetrations and modifiers
		if (HitFound)
		{
			ACsCharacter* HitPawn = Cast<ACsCharacter>(HitResult.Actor.Get());
			CollisionParams.AddIgnoredActor(HitResult.Actor.Get());
			
			//if (PawnToHit && UShooterStatics::IsOnSameTeam(GetWorld(), PawnToHit, MyPawn))
			//{
			//	continue;
			//}
			
			float Damage = Data_Projectile->Damage;

			if (HitPawn)
				RecordedPlayerPenetrations++;
			else
				RecordedObstaclePenetrations++;

			
			//float TimeUntilHit = HitResult.Distance / Data_Projectile->InitialSpeed;

			//if (DoesHitscanSimulateProjectileDuration.Get(FireType))
			//{
			//	FakeProjectile->Lifetime = TimeUntilHit;
			//}
			//else
			//{
			//	if (ProjectileData->LeaveTrail)
			//	{
			//		FakeProjectile->Lifetime = ProjectileData->TrailDurationAfterHit;
			//		FakeProjectile->TeleportTo(CurHit.ImpactPoint, FakeProjectile->GetActorRotation());
			//		FakeProjectile->SpawnLocation = Origin;
			//		float Length = FMath::Max(ProjectileData->TrailMeshLength, FVector::Dist(CurHit.ImpactPoint, Origin) / ProjectileData->TrailMeshLength);
			//		FVector Scale = ProjectileData->Scale;
			//		Scale.X *= Length;
			//		FakeProjectile->TracerMeshComp->SetWorldScale3D(Scale);
			//		FakeProjectile->StopMovement();
			//		FakeProjectile->MeshComp->SetVisibility(false);
			//		//FakeProjectile->DeActivate();
			//	}
			//	else
			//	{
			//		FakeProjectile->Lifetime = ProjectileData->Lifetime;
			//	}
			//}
			
			//FakeProjectile->PlayImpactFX(CurHit.Location, CurHit);

			if (Pawn->Role == ROLE_Authority)
			{
				if (!HitPawn)
					continue;

				const int32 Count = Data_Weapon->FireTypes[(uint8)FireType].Firing.LocationDamageModifiers.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					if (HitResult.BoneName.ToString() == Data_Weapon->FireTypes[(uint8)FireType].Firing.LocationDamageModifiers[I].Bone)
					{
						Damage *= Data_Weapon->FireTypes[(uint8)FireType].Firing.LocationDamageModifiers[I].Multiplier;
						break;
					}
				}

				// Damage Falloff
				float Falloff = 0.f;

				if (Data_Projectile->DamageFalloffRate > 0.f && 
					Data_Projectile->DamageFalloffFrequency > 0.f)
				{
					Falloff = FMath::Max(Data_Projectile->DamageFalloffMinimum, 1.f - (Data_Projectile->DamageFalloffRate * FMath::FloorToFloat(HitResult.Distance / Data_Projectile->DamageFalloffFrequency)));
				}
				else
				{
					Falloff = 1.f;
				}

				Damage *= Falloff;

				//PawnToHit->ShooterTakeDamage(Damage, FShooterDamageEvent(EDamageType::Normal), MyPawn->GetController(), MyPawn);
			}
		}
	}
	*/
}

#pragma endregion Hitscan

UObject* ACsWeapon::GetMuzzleFlashParent() { return nullptr; }

FVector ACsWeapon::GetMuzzleLocation(const TCsViewType &ViewType, const TCsWeaponFire &FireType)
{
	return FVector::ZeroVector; // GetMyData_Weapon()->GetMuzzleLocation(GetMesh(ViewType), ViewType, FireType, CurrentProjectilePerShotIndex.Get(FireType));
}

void ACsWeapon::PlayMuzzleFlash(const TCsWeaponFire &FireType)
{
	ACsManager_FX* Manager_FX = nullptr;

#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		if (UCsAnimInstance* AnimInstance = Cast<UCsAnimInstance>(GetMyOwner()))
			Manager_FX = AnimInstance->GetManager_FX();
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>();
		Manager_FX				 = GameState->Manager_FX;
	}

	ACsData_Weapon* Data_Weapon = GetMyData_Weapon();
	const TCsViewType ViewType	= GetCurrentViewType();
	FCsFxElement* FX			= Data_Weapon->GetMuzzleFX(ViewType, FireType, CurrentProjectilePerShotIndex.Get(FireType));

	Manager_FX->Play(FX, GetMyPawn(), GetMuzzleFlashParent());
}

#pragma endregion Firing

// Reload
#pragma region

float ACsWeapon::GetReloadTime(const int32 &Index) { return ReloadTime.Get(Index); }
float ACsWeapon::GetRechargeSecondsPerAmmo(const int32 &Index) { return RechargeSecondsPerAmmo.Get(Index); }
float ACsWeapon::GetRechargeStartupDelay(const int32 &Index) { return RechargeStartupDelay.Get(Index); }

void ACsWeapon::Reload()
{
	if (CurrentState == ReloadingState || IsReloading)
		return;

	// Idle
	if (CurrentState == IdleState)
	{
		if (CurrentAmmo == MaxAmmo.Get(CS_WEAPON_DATA_VALUE))
			return;
	}
	// Firing
	if (CurrentState == FiringState)
	{
		UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();

		for (uint8 I = 0; I < FIRE_TYPE_MAX; I++)
		{
			StopChargeFire((TCsWeaponFire)I);
		}

		Scheduler->BroadcastMessage(ECsCoroutineSchedule::Tick, ECsCoroutineMessage::Stop, FName("Stop FireWeapon_Internal"), this);

		for (uint8 I = 0; I < FIRE_TYPE_MAX; I++)
		{
			StopAnimation((TCsWeaponFire)I, FireAnim);
		}
	}

	ReloadStartTime = GetWorld()->TimeSeconds;
	IsReloading		= true;

	PlayAnimation_Reload();

	LastState    = CurrentState;
	CurrentState = ReloadingState;
}

#pragma endregion Reload