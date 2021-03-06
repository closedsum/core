// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Weapon/CsWeapon_DEPRECATED.h"
#include "CsCoreDEPRECATED.h"
#include "Weapon/CsCVars_Weapon.h"
#include "Player/CsCVars_Player.h"

// Library
#include "Library/CsLibrary_Common.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Anim
#include "Animation/CsAnimInstance.h"
// Data
#include "Data/CsData_ProjectileBase.h"
#include "Data/CsData_ProjectileImpact.h"
#include "Data/CsData_Character.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
//#include "Managers/FX/CsManager_FX.h"
#include "Managers/Projectile/CsManager_Projectile.h"
#include "Managers/Projectile/CsProjectileBase.h"
#include "Managers/Damage/CsManager_Damage.h"
#include "Managers/Trace/CsManager_Trace.h"
#include "Managers/Inventory/CsManager_Inventory.h"
#include "Managers/InteractiveActor/CsDamageableActor.h"
// Game
#include "Game/CsGameInstance_DEPRECATED.h"
#include "Game/CsGameState_DEPRECATED.h"
// Player
#include "Player/CsPlayerStateBase.h"
#include "Pawn/CsPawn.h"

#include "Animation/CsAnimInstance.h"

// Cache
#pragma region

namespace NCsWeaponCached
{
	namespace Name
	{
		// Functions
		const FName PlayAnimation_Reload_Internal = FName("ACsWeapon_DEPRECATED::PlayAnimation_Reload_Internal");
		const FName StartChargeFire_Internal = FName("ACsWeapon_DEPRECATED::StartChargeFire_Internal");
		const FName FireWeapon_Internal = FName("ACsWeapon_DEPRECATED::FireWeapon_Internal");
		const FName DrawFireProjectile_Internal = FName("ACsWeapon_DEPRECATED::DrawFireProjectile_Internal");
		// Stop Messages
		const FName Stop_PlayAnimation_Reload_Internal = FName("Stop PlayAnimation_Reload_Internal");
		const FName Stop_StartChargeFire_Internal = FName("Stop StartCharageFire_Internal");
		const FName Stop_FireWeapon_Internal = FName("Stop FireWeapon_Internal");
		const FName Stop_DrawFireProjectile_Internal = FName("Stop DrawFireProjectile_Internal");
	}

	namespace Str
	{
		// Functions
		const FString PlayAnimation_Reload_Internal = TEXT("ACsWeapon_DEPRECATED::PlayAnimation_Reload_Internal");
		const FString StartChargeFire_Internal = TEXT("ACsWeapon_DEPRECATED::StartChargeFire_Internal");
		const FString FireWeapon_Internal = TEXT("ACsWeapon_DEPRECATED::FireWeapon_Internal");
		const FString DrawFireProjectile_Internal = TEXT("ACsWeapon_DEPRECATED::DrawFireProjectile_Internal");
	}
}

#pragma endregion Cache

// Enums
#pragma region

	// WeaponMultiValueMember
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsWeaponMultiValueMember)

namespace ECsWeaponMultiValueMember
{
	// Scope
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember MaxAmmo = EMCsWeaponMultiValueMember::Get().Create(TEXT("MaxAmmo"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember ProjectilesPerShot = EMCsWeaponMultiValueMember::Get().Create(TEXT("ProjectilesPerShot"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember CurrentProjectilePerShotIndex = EMCsWeaponMultiValueMember::Get().Create(TEXT("CurrentProjectilePerShotIndex"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember DoFireOnRelease = EMCsWeaponMultiValueMember::Get().Create(TEXT("DoFireOnRelease"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember IsFullAuto = EMCsWeaponMultiValueMember::Get().Create(TEXT("IsFullAuto"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember TimeBetweenProjectilesPerShot = EMCsWeaponMultiValueMember::Get().Create(TEXT("TimeBetweenProjectilesPerShot"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember TimeBetweenShots = EMCsWeaponMultiValueMember::Get().Create(TEXT("TimeBetweenShots"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember TimeBetweenAutoShots = EMCsWeaponMultiValueMember::Get().Create(TEXT("TimeBetweenAutoShots"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember IsFirePressed = EMCsWeaponMultiValueMember::Get().Create(TEXT("IsFirePressed"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember Last_IsFirePressed = EMCsWeaponMultiValueMember::Get().Create(TEXT("Last_IsFirePressed"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember IsFirePressed_StartTime = EMCsWeaponMultiValueMember::Get().Create(TEXT("IsFirePressed_StartTime"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember IsFireReleased_StartTime = EMCsWeaponMultiValueMember::Get().Create(TEXT("IsFireReleased_StartTime"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember Fire_StartTime = EMCsWeaponMultiValueMember::Get().Create(TEXT("Fire_StartTime"));
	// Charge
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember AllowChargeFire = EMCsWeaponMultiValueMember::Get().Create(TEXT("AllowChargeFire"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember MaxChargeFireTime = EMCsWeaponMultiValueMember::Get().Create(TEXT("MaxChargeFireTime"));
	// Spread
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember DoSpread = EMCsWeaponMultiValueMember::Get().Create(TEXT("DoSpread"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember MinSpread = EMCsWeaponMultiValueMember::Get().Create(TEXT("MinSpread"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember MaxSpread = EMCsWeaponMultiValueMember::Get().Create(TEXT("MaxSpread"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember SpreadAddedPerShot = EMCsWeaponMultiValueMember::Get().Create(TEXT("SpreadAddedPerShot"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember SpreadRecoveryRate = EMCsWeaponMultiValueMember::Get().Create(TEXT("SpreadRecoveryRate"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember FiringSpreadRecoveryDelay = EMCsWeaponMultiValueMember::Get().Create(TEXT("FiringSpreadRecoveryDelay"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember CurrentBaseSpread = EMCsWeaponMultiValueMember::Get().Create(TEXT("CurrentBaseSpread"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember CurrentSpread = EMCsWeaponMultiValueMember::Get().Create(TEXT("CurrentSpread"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember LastSpreadFireTime = EMCsWeaponMultiValueMember::Get().Create(TEXT("LastSpreadFireTime"));
	// Anim
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember LoopFireAnim = EMCsWeaponMultiValueMember::Get().Create(TEXT("LoopFireAnim"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember DoScaleFireAnim = EMCsWeaponMultiValueMember::Get().Create(TEXT("DoScaleFireAnim"));
	// Sound
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember LoopFireSound = EMCsWeaponMultiValueMember::Get().Create(TEXT("LoopFireSound"));
	// Hitscan
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember IsHitscan = EMCsWeaponMultiValueMember::Get().Create(TEXT("IsHitscan"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember DoesHitscanUseRadius = EMCsWeaponMultiValueMember::Get().Create(TEXT("DoesHitscanUseRadius"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember DoesHitscanSimulateProjectileDuration = EMCsWeaponMultiValueMember::Get().Create(TEXT("DoesHitscanSimulateProjectileDuration"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember ObstaclePenetrations = EMCsWeaponMultiValueMember::Get().Create(TEXT("ObstaclePenetrations"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember PawnPenetrations = EMCsWeaponMultiValueMember::Get().Create(TEXT("PawnPenetrations"));
	// Reload
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember ReloadTime = EMCsWeaponMultiValueMember::Get().Create(TEXT("ReloadTime"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember AllowRechargeAmmo = EMCsWeaponMultiValueMember::Get().Create(TEXT("AllowRechargeAmmo"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember AllowRechargeAmmoDuringFire = EMCsWeaponMultiValueMember::Get().Create(TEXT("AllowRechargeAmmoDuringFire"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember RechargeSecondsPerAmmo = EMCsWeaponMultiValueMember::Get().Create(TEXT("RechargeSecondsPerAmmo"));
	CSCOREDEPRECATED_API const FECsWeaponMultiValueMember RechargeStartupDelay = EMCsWeaponMultiValueMember::Get().Create(TEXT("RechargeStartupDelay"));
}

	// WeaponRoutine
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsWeaponRoutine)

namespace ECsWeaponRoutine
{
	CSCOREDEPRECATED_API const FECsWeaponRoutine PlayAnimation_Reload_Internal = EMCsWeaponRoutine::Get().Create(TEXT("PlayAnimation_Reload_Internal"));
	CSCOREDEPRECATED_API const FECsWeaponRoutine StartChargeFire_Internal = EMCsWeaponRoutine::Get().Create(TEXT("StartChargeFire_Internal"));
	CSCOREDEPRECATED_API const FECsWeaponRoutine FireWeapon_Internal = EMCsWeaponRoutine::Get().Create(TEXT("FireWeapon_Internal"));
}

#pragma endregion Enums

ACsWeapon_DEPRECATED::ACsWeapon_DEPRECATED(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	//CS_DEFINE_WEAPON_FIRE_MODE

	//CurrentState = ECsWeaponState::Idle;
	//LastState	 = CurrentState;

	//IdleState = ECsWeaponState::Idle;

	//PrimaryFireMode

	//FiringState = ECsWeaponState::Firing;
	//FireAnim = ECsWeaponAnim::Fire;
	//ChargeFireStartAnim = ECsWeaponAnim::ECsWeaponAnim_MAX;
	//ChargeFireLoopAnim = ECsWeaponAnim::ECsWeaponAnim_MAX;

	//ReloadingState = ECsWeaponState::Reloading;
	//ReloadAnim = ECsWeaponAnim::Reload;

	// Make sure to call InitMultiValueMembers() in the Child Class

	CurrentAmmoHandle.Set(&CurrentAmmo);
	CurrentAmmoHandle.OnChange_Event.AddUObject(this, &ACsWeapon_DEPRECATED::OnChange_CurrentAmmo);

	bReloadingHandle.Set(&bReloading);
	bReloadingHandle.OnChange_Event.AddUObject(this, &ACsWeapon_DEPRECATED::OnChange_bReloading);
}

void ACsWeapon_DEPRECATED::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ACsWeapon_DEPRECATED::OutsideWorldBounds()
{
	return;
}

void ACsWeapon_DEPRECATED::PostActorCreated()
{
	Super::PostActorCreated();

	if (UCsLibrary_Common::IsPlayInEditor(GetWorld()) || UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
		return;

	UCsGameInstance_DEPRECATED* GameInstance = Cast<UCsGameInstance_DEPRECATED>(GetGameInstance());
	UniqueObjectId				  = GameInstance->GetUniqueObjectId();
}

void ACsWeapon_DEPRECATED::Destroyed()
{
	Super::Destroyed();

	if (UCsLibrary_Common::IsPlayInEditor(GetWorld()) || UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
		return;

	UCsGameInstance_DEPRECATED* GameInstance = Cast<UCsGameInstance_DEPRECATED>(GetGameInstance());
	GameInstance->UnregisterUniqueObject(UniqueObjectId);
}

// Members
#pragma region

void ACsWeapon_DEPRECATED::InitMultiValueMembers()
{
	// Firing
	{
		MaxAmmo.Init(1);
		MaxAmmo.GetDelegate.BindUObject(this, &ACsWeapon_DEPRECATED::GetMaxAmmo);
		InitMultiRefValueMember<uint8>(ProjectilesPerShot, 0);
		ProjectilesPerShot.GetDelegate.BindUObject(this, &ACsWeapon_DEPRECATED::GetProjectilesPerShot);
		InitMultiValueMember<uint8>(CurrentProjectilePerShotIndex, 0);
		InitMultiRefValueMember<bool>(DoFireOnRelease, false);
		InitMultiRefValueMember<bool>(IsFullAuto, false);
		InitMultiRefValueMember<float>(TimeBetweenProjectilesPerShot, 0.0f);
		TimeBetweenProjectilesPerShot.GetDelegate.BindUObject(this, &ACsWeapon_DEPRECATED::GetTimeBetweenProjectilesPerShot);
		InitMultiRefValueMember<float>(TimeBetweenShots, 0.0f);
		TimeBetweenShots.GetDelegate.BindUObject(this, &ACsWeapon_DEPRECATED::GetTimeBetweenShots);
		InitMultiRefValueMember<float>(TimeBetweenAutoShots, 0.0f);
		TimeBetweenAutoShots.GetDelegate.BindUObject(this, &ACsWeapon_DEPRECATED::GetTimeBetweenShots);
		InitMultiValueMember<bool>(IsFirePressed, false);
		InitMultiValueMember<bool>(Last_IsFirePressed, false);
		InitMultiValueMember<float>(IsFirePressed_StartTime, 0.0f);
		InitMultiValueMember<float>(IsFireReleased_StartTime, 0.0f);
		InitMultiValueMember<float>(Fire_StartTime, 0.0f);
		// Charge
		InitMultiRefValueMember<bool>(AllowChargeFire, false);
		InitMultiRefValueMember<float>(MaxChargeFireTime, 0.0f);
		MaxChargeFireTime.GetDelegate.BindUObject(this, &ACsWeapon_DEPRECATED::GetMaxChargeFireTime);
		// Spread
		InitMultiRefValueMember<bool>(DoSpread, false);
		InitMultiRefValueMember<float>(MinSpread, 0.0f);
		MinSpread.GetDelegate.BindUObject(this, &ACsWeapon_DEPRECATED::GetMinSpread);
		InitMultiRefValueMember<float>(MaxSpread, 0.0f);
		MaxSpread.GetDelegate.BindUObject(this, &ACsWeapon_DEPRECATED::GetMaxSpread);
		InitMultiRefValueMember<float>(SpreadAddedPerShot, 0.0f);
		SpreadAddedPerShot.GetDelegate.BindUObject(this, &ACsWeapon_DEPRECATED::GetSpreadAddedPerShot);
		InitMultiRefValueMember<float>(SpreadRecoveryRate, 0.0f);
		SpreadRecoveryRate.GetDelegate.BindUObject(this, &ACsWeapon_DEPRECATED::GetSpreadRecoveryRate);
		InitMultiRefValueMember<float>(FiringSpreadRecoveryDelay, 0.0f);
		FiringSpreadRecoveryDelay.GetDelegate.BindUObject(this, &ACsWeapon_DEPRECATED::GetFiringSpreadRecoveryDelay);
		InitMultiRefValueMember<float>(MovingSpreadBonus, 0.0f);
		MovingSpreadBonus.GetDelegate.BindUObject(this, &ACsWeapon_DEPRECATED::GetMovingSpreadBonus);
		InitMultiValueMember<float>(CurrentBaseSpread, 0.0f);
		InitMultiValueMember<float>(CurrentSpread, 0.0f);
		InitMultiValueMember<float>(LastSpreadFireTime, 0.0f);
		// Anim
		InitMultiRefValueMember<bool>(LoopFireAnim, false);
		InitMultiRefValueMember<bool>(DoScaleFireAnim, false);
		// Sound
		InitMultiRefValueMember<bool>(LoopFireSound, false);
		// Hitscan
		InitMultiRefValueMember<bool>(IsHitscan, false);
		InitMultiRefValueMember<bool>(DoesHitscanUseRadius, false);
		InitMultiRefValueMember<bool>(DoesHitscanSimulateProjectileDuration, false);
		InitMultiRefValueMember<int32>(ObstaclePenetrations, 0);
		ObstaclePenetrations.GetDelegate.BindUObject(this, &ACsWeapon_DEPRECATED::GetObstaclePenetractions);
		InitMultiRefValueMember<int32>(PawnPenetrations, 0);
		PawnPenetrations.GetDelegate.BindUObject(this, &ACsWeapon_DEPRECATED::GetPawnPenetrations);
	}
	// Reload
	{
		ReloadTime.Init(1);
		ReloadTime.GetDelegate.BindUObject(this, &ACsWeapon_DEPRECATED::GetReloadTime);
		AllowRechargeAmmo.Init(1);
		AllowRechargeAmmoDuringFire.Init(1);
		RechargeSecondsPerAmmo.Init(1);
		RechargeSecondsPerAmmo.GetDelegate.BindUObject(this, &ACsWeapon_DEPRECATED::GetRechargeSecondsPerAmmo);
		RechargeStartupDelay.Init(1);
		RechargeStartupDelay.GetDelegate.BindUObject(this, &ACsWeapon_DEPRECATED::GetRechargeStartupDelay);
	}
}

	// Set
#pragma region

void ACsWeapon_DEPRECATED::SetMemberValue_bool(const FECsWeaponMultiValueMember& Member, const FECsWeaponFireMode& FireMode, const bool &Value)
{
	// Firing
	{
		if (Member == ECsWeaponMultiValueMember::IsFirePressed) { IsFirePressed.Set(FireMode, Value); }
		if (Member == ECsWeaponMultiValueMember::Last_IsFirePressed) { Last_IsFirePressed.Set(FireMode, Value); }
	}
}

void ACsWeapon_DEPRECATED::SetMemberValue_uint8(const FECsWeaponMultiValueMember& Member, const FECsWeaponFireMode& FireMode, const uint8 &Value)
{
	// Firing
	{
		if (Member == ECsWeaponMultiValueMember::CurrentProjectilePerShotIndex) { CurrentProjectilePerShotIndex.Set(FireMode, Value); }
	}
}

void ACsWeapon_DEPRECATED::SetMemberValue_int32(const FECsWeaponMultiValueMember& Member, const FECsWeaponFireMode& FireMode, const int32 &Value)
{
	// Firing
	{
	}
}

void ACsWeapon_DEPRECATED::SetMemberValue_float(const FECsWeaponMultiValueMember& Member, const FECsWeaponFireMode& FireMode, const float &Value)
{
	// Firing
	{
		if (Member == ECsWeaponMultiValueMember::IsFirePressed_StartTime) { IsFirePressed_StartTime.Set(FireMode, Value); }
		if (Member == ECsWeaponMultiValueMember::IsFireReleased_StartTime) { IsFireReleased_StartTime.Set(FireMode, Value); }
		// Spread
		if (Member == ECsWeaponMultiValueMember::CurrentBaseSpread) { CurrentBaseSpread.Set(FireMode, Value); }
		if (Member == ECsWeaponMultiValueMember::CurrentSpread) { CurrentSpread.Set(FireMode, Value); }
		if (Member == ECsWeaponMultiValueMember::LastSpreadFireTime) { LastSpreadFireTime.Set(FireMode, Value); }
	}
}

void ACsWeapon_DEPRECATED::SetMultiValueMembers()
{
	UCsData_ProjectileWeapon_DEPRECATED* Data = GetMyData_Weapon<UCsData_ProjectileWeapon_DEPRECATED>();

	// MaxAmmo
	MaxAmmo.ResetValues();
	int32 iVal = Data->GetMaxAmmo();
	MaxAmmo.Set(iVal);
	MaxAmmo.Set(CS_WEAPON_DATA_VALUE, Data->GetMaxAmmoAddr());

	ResetCurrentAmmo(CS_WEAPON_DATA_VALUE);

	// Firing
	{
		// DoFireOnRelease
		SetMemberMultiRefValue<bool>(DoFireOnRelease, FiringDataFireMode, TEXT("DoFireOnRelease"));
		// IsFullAuto
		SetMemberMultiRefValue<bool>(IsFullAuto, FiringDataFireMode, TEXT("IsFullAuto"));
		// AllowChargeFire
		SetMemberMultiRefValue<bool>(AllowChargeFire, FiringDataFireMode, TEXT("AllowChargeFire"));
		// MaxChargeFireTime
		SetMemberMultiRefValue<float>(MaxChargeFireTime, FiringDataFireMode, TEXT("MaxChargeFireTime"));
		// ProjectilesPerShot
		SetMemberMultiRefValue<uint8>(ProjectilesPerShot, FiringDataFireMode, TEXT("ProjectilesPerShot"));
		// CurrentProjectilePerShotIndex
		SetMemberMultiValue<uint8>(CurrentProjectilePerShotIndex, 0);
		// TimeBetweenProjectilesPerShot
		SetMemberMultiRefValue<float>(TimeBetweenProjectilesPerShot, FiringDataFireMode, TEXT("TimeBetweenProjectilesPerShot"));
		// TimeBetweenShots
		SetMemberMultiRefValue<float>(TimeBetweenShots, FiringDataFireMode, TEXT("TimeBetweenShots"));
		// TimeBetweenAutoShots
		SetMemberMultiRefValue<float>(TimeBetweenAutoShots, FiringDataFireMode, TEXT("TimeBetweenAutoShots"));
		// IsFirePressed
		SetMemberMultiValue<bool>(IsFirePressed, false);
		// Last_IsFirePressed
		SetMemberMultiValue<bool>(Last_IsFirePressed, false);
		// IsFirePressed_StartTime
		SetMemberMultiValue<float>(IsFirePressed_StartTime, 0.0f);
		// IsFireReleased_StartTime
		SetMemberMultiValue<float>(IsFireReleased_StartTime, 0.0f);
		// Fire_StartTime
		SetMemberMultiValue<float>(Fire_StartTime, 0.0f);
		// IsHitScan
		SetMemberMultiRefValue<bool>(IsHitscan, FiringDataFireMode, TEXT("IsHitScan"));
		// DoesHitscanUseRadius
		SetMemberMultiRefValue<bool>(DoesHitscanUseRadius, FiringDataFireMode, TEXT("DoesHitscanUseRadius"));
		// DoesHitscanSimulateProjectileDuration
		SetMemberMultiRefValue<bool>(DoesHitscanSimulateProjectileDuration, FiringDataFireMode, TEXT("DoesHitscanSimulateProjectileDuration"));
		// ObstaclePenetrations
		SetMemberMultiRefValue<int32>(ObstaclePenetrations, FiringDataFireMode, TEXT("ObstaclePenetrations"));
		// SetMemberMultiRefValue
		SetMemberMultiRefValue<int32>(PawnPenetrations, FiringDataFireMode, TEXT("PawnPenetrations"));

	}
	// Animation
	{
		// LoopFireAnim
		SetMemberMultiRefValue<bool>(LoopFireAnim, AnimationDataFireMode, TEXT("LoopFireAnim"));
		// DoScaleFireAnim
		SetMemberMultiRefValue<bool>(DoScaleFireAnim, AnimationDataFireMode, TEXT("DoScaleFireAnim"));
	}
	// Aiming
	{
		// DoSpread
		SetMemberMultiRefValue<bool>(DoSpread, AimingDataFireMode, TEXT("DoSpread"));
		// MinSpread
		SetMemberMultiRefValue<float>(MinSpread, AimingDataFireMode, TEXT("MinSpread"));
		// MaxSpread
		SetMemberMultiRefValue<float>(MaxSpread, AimingDataFireMode, TEXT("MaxSpread"));
		// SpreadAddedPerShot
		SetMemberMultiRefValue<float>(SpreadAddedPerShot, AimingDataFireMode, TEXT("SpreadAddedPerShot"));
		// SpreadRecoveryRate
		SetMemberMultiRefValue<float>(SpreadRecoveryRate, AimingDataFireMode, TEXT("SpreadRecoveryRate"));
		// FiringSpreadRecoveryDelay
		SetMemberMultiRefValue<float>(FiringSpreadRecoveryDelay, AimingDataFireMode, TEXT("FiringSpreadRecoveryDelay"));
		// MovingSpreadBonus
		SetMemberMultiRefValue<float>(MovingSpreadBonus, AimingDataFireMode, TEXT("MovingSpreadBonus"));
	}
	// Sounds
	{
		// LoopFireSound
		SetMemberMultiRefValue<bool>(LoopFireSound, SoundsDataFireMode, TEXT("LoopFireSound"));
	}
	// Stats
	{
		// AllowRechargeAmmo
		SetMemberRefValue<bool>(AllowRechargeAmmo, TEXT("AllowRechargeAmmo"));
		// AllowRechargeAmmoDuringFire
		SetMemberRefValue<bool>(AllowRechargeAmmoDuringFire, TEXT("AllowRechargeAmmoDuringFire"));

		// RechargeSecondsPerAmmo
		RechargeSecondsPerAmmo.ResetValues();
		float fVal = Data->GetRechargeSecondsPerAmmo();
		RechargeSecondsPerAmmo.Set(fVal);
		RechargeSecondsPerAmmo.Set(CS_WEAPON_DATA_VALUE, Data->GetRechargeSecondsPerAmmoAddr());
		// RechargeStartupDelay
		RechargeStartupDelay.ResetValues();
		fVal = Data->GetRechargeStartupDelay();
		RechargeStartupDelay.Set(fVal);
		RechargeStartupDelay.Set(CS_WEAPON_DATA_VALUE, Data->GetRechargeStartupDelayAddr());
		// ReloadTime
		ReloadTime.ResetValues();
		fVal = Data->GetReloadTime();
		ReloadTime.Set(fVal);
		ReloadTime.Set(CS_WEAPON_DATA_VALUE, Data->GetReloadTimeAddr());
	}
}

#pragma endregion Set

	// Get
#pragma region

bool ACsWeapon_DEPRECATED::GetMemberValue_bool(const FECsWeaponMultiValueMember& Member, const FECsWeaponFireMode& FireMode)
{
	// Firing
	{
		if (Member == ECsWeaponMultiValueMember::DoFireOnRelease) { return DoFireOnRelease.Get(FireMode); }
		if (Member == ECsWeaponMultiValueMember::IsFullAuto) { return IsFullAuto.Get(FireMode); }
		if (Member == ECsWeaponMultiValueMember::IsFirePressed) { return IsFirePressed.Get(FireMode); }
		if (Member == ECsWeaponMultiValueMember::Last_IsFirePressed) { return Last_IsFirePressed.Get(FireMode); }
		// Charge
		if (Member == ECsWeaponMultiValueMember::AllowChargeFire) { return AllowChargeFire.Get(FireMode); }
		// Spread
		if (Member == ECsWeaponMultiValueMember::DoSpread) { return DoSpread.Get(FireMode); }

		if (Member == ECsWeaponMultiValueMember::LoopFireAnim) { return LoopFireAnim.Get(FireMode); }
		if (Member == ECsWeaponMultiValueMember::DoScaleFireAnim) { return DoScaleFireAnim.Get(FireMode); }
		if (Member == ECsWeaponMultiValueMember::LoopFireSound) { return LoopFireSound.Get(FireMode); }
		// Hitscan
		if (Member == ECsWeaponMultiValueMember::IsHitscan) { return IsHitscan.Get(FireMode); }
		if (Member == ECsWeaponMultiValueMember::DoesHitscanUseRadius) { return DoesHitscanUseRadius.Get(FireMode); }
		if (Member == ECsWeaponMultiValueMember::DoesHitscanSimulateProjectileDuration) { return DoesHitscanSimulateProjectileDuration.Get(FireMode); }
	}
	// Reload
	{
		if (Member == ECsWeaponMultiValueMember::AllowRechargeAmmo) { return AllowRechargeAmmo.Get(FireMode); }
		if (Member == ECsWeaponMultiValueMember::AllowRechargeAmmoDuringFire) { return AllowRechargeAmmoDuringFire.Get(FireMode); }
	}
	return false;
}

uint8 ACsWeapon_DEPRECATED::GetMemberValue_uint8(const FECsWeaponMultiValueMember& Member, const FECsWeaponFireMode& FireMode)
{
	// Firing
	{
		if (Member == ECsWeaponMultiValueMember::ProjectilesPerShot) { return ProjectilesPerShot.GetEX(FireMode); }
		if (Member == ECsWeaponMultiValueMember::CurrentProjectilePerShotIndex) { return CurrentProjectilePerShotIndex.Get(FireMode); }
	}
	return 0;
}

int32 ACsWeapon_DEPRECATED::GetMemberValue_int32(const FECsWeaponMultiValueMember& Member, const FECsWeaponFireMode& FireMode)
{
	// Firing
	{
		if (Member == ECsWeaponMultiValueMember::MaxAmmo) { return MaxAmmo.GetEX(CS_WEAPON_DATA_VALUE); }
		// Hitscan
		if (Member == ECsWeaponMultiValueMember::ObstaclePenetrations) { return ObstaclePenetrations.GetEX(FireMode); }
		if (Member == ECsWeaponMultiValueMember::PawnPenetrations) { return PawnPenetrations.GetEX(FireMode); }
	}
	return 0;
}

float ACsWeapon_DEPRECATED::GetMemberValue_float(const FECsWeaponMultiValueMember& Member, const FECsWeaponFireMode& FireMode)
{
	// Firing
	{
		if (Member == ECsWeaponMultiValueMember::TimeBetweenProjectilesPerShot) { return TimeBetweenProjectilesPerShot.GetEX(FireMode); }
		if (Member == ECsWeaponMultiValueMember::TimeBetweenShots) { return TimeBetweenShots.GetEX(FireMode); }
		if (Member == ECsWeaponMultiValueMember::TimeBetweenAutoShots) { return TimeBetweenAutoShots.GetEX(FireMode); }
		if (Member == ECsWeaponMultiValueMember::IsFirePressed_StartTime) { return IsFirePressed_StartTime.Get(FireMode); }
		if (Member == ECsWeaponMultiValueMember::IsFireReleased_StartTime) { return IsFireReleased_StartTime.Get(FireMode); }
		// Charge
		if (Member == ECsWeaponMultiValueMember::MaxChargeFireTime) { return MaxChargeFireTime.GetEX(FireMode); }
		// Spread
		if (Member == ECsWeaponMultiValueMember::MinSpread) { return MinSpread.GetEX(FireMode); }
		if (Member == ECsWeaponMultiValueMember::MaxSpread) { return MaxSpread.GetEX(FireMode); }
		if (Member == ECsWeaponMultiValueMember::SpreadAddedPerShot) { return SpreadAddedPerShot.GetEX(FireMode); }
		if (Member == ECsWeaponMultiValueMember::SpreadRecoveryRate) { return SpreadRecoveryRate.GetEX(FireMode); }
		if (Member == ECsWeaponMultiValueMember::FiringSpreadRecoveryDelay) { return FiringSpreadRecoveryDelay.GetEX(FireMode); }
		if (Member == ECsWeaponMultiValueMember::CurrentBaseSpread) { return CurrentBaseSpread.Get(FireMode); }
		if (Member == ECsWeaponMultiValueMember::CurrentSpread) { return CurrentSpread.Get(FireMode); }
		if (Member == ECsWeaponMultiValueMember::LastSpreadFireTime) { return LastSpreadFireTime.Get(FireMode); }
	}
	// Reload
	{
		if (Member == ECsWeaponMultiValueMember::ReloadTime) { return ReloadTime.GetEX(FireMode); }
		if (Member == ECsWeaponMultiValueMember::RechargeSecondsPerAmmo) { return RechargeSecondsPerAmmo.GetEX(FireMode); }
		if (Member == ECsWeaponMultiValueMember::RechargeStartupDelay) { return RechargeStartupDelay.GetEX(FireMode); }
	}
	return 0.0f;
}

#pragma endregion Get

	// Add
#pragma region

void ACsWeapon_DEPRECATED::AddMemberValue_uint8(const FECsWeaponMultiValueMember& Member, const FECsWeaponFireMode& FireMode, const uint8 &Value)
{
#if WITH_EDITOR
	// Firing
	{
		if (Member == ECsWeaponMultiValueMember::CurrentProjectilePerShotIndex) { return CurrentProjectilePerShotIndex.Add(FireMode, Value); }
	}
#endif // #if WITH_EDITOR
}

#pragma endregion Add

#pragma endregion Members

// Managers
#pragma region

ACsManager_Inventory* ACsWeapon_DEPRECATED::GetMyManager_Inventory()
{
	if (ACsPawn* Pawn = GetMyOwner<ACsPawn>())
	{
		ACsPlayerStateBase* PlayerState = Pawn->GetPlayerState<ACsPlayerStateBase>();
		return PlayerState->Manager_Inventory;
	}
	return nullptr;
}

#pragma endregion Managers

// Data
#pragma region

UCsData_Weapon_DEPRECATED* ACsWeapon_DEPRECATED::GetMyData_Weapon()
{
	return MyData_Weapon.IsValid() ? MyData_Weapon.Get() : nullptr;
}

UCsData_ProjectileBase* ACsWeapon_DEPRECATED::GetMyData_Projectile(const FECsWeaponFireMode& FireMode, const bool &IsCharged)
{
	return GetMyData_Weapon<UCsData_ProjectileWeapon_DEPRECATED>()->GetData_Projectile(FireMode, IsCharged);
}

#pragma endregion Data

// Routines
#pragma region

void ACsWeapon_DEPRECATED::AddRoutine(UObject* InWeapon, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<ACsWeapon_DEPRECATED>(InWeapon)->AddRoutine_Internal(Routine, Type);
}

bool ACsWeapon_DEPRECATED::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	const FECsWeaponRoutine& RoutineType = EMCsWeaponRoutine::Get().GetEnumAt(Type);

	// PlayAnimation_Reload_Internal
	if (RoutineType == ECsWeaponRoutine::PlayAnimation_Reload_Internal)
	{
		PlayAnimation_Reload_Internal_Routine = Routine;
		return true;
	}
	// StartChargeFire_Internal
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

void ACsWeapon_DEPRECATED::RemoveRoutine(UObject* InWeapon, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<ACsWeapon_DEPRECATED>(InWeapon)->RemoveRoutine_Internal(Routine, Type);
}

bool ACsWeapon_DEPRECATED::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	const FECsWeaponRoutine& RoutineType = EMCsWeaponRoutine::Get().GetEnumAt(Type);

	// PlayAnimation_Reload_Internal
	if (RoutineType == ECsWeaponRoutine::PlayAnimation_Reload_Internal)
	{
		check(Routine == PlayAnimation_Reload_Internal_Routine);
		PlayAnimation_Reload_Internal_Routine = nullptr;
		return true;
	}
	// StartChargeFire_Internal
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

void ACsWeapon_DEPRECATED::ClearRoutines()
{
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(GetGameInstance());

	Scheduler->BroadcastMessage(NCsUpdateGroup::GameState, ECsCoroutineMessage::Abort, NCsWeaponCached::Name::Stop_PlayAnimation_Reload_Internal, this);
	Scheduler->BroadcastMessage(NCsUpdateGroup::GameState, ECsCoroutineMessage::Abort, NCsWeaponCached::Name::Stop_StartChargeFire_Internal, this);
	Scheduler->BroadcastMessage(NCsUpdateGroup::GameState, ECsCoroutineMessage::Abort, NCsWeaponCached::Name::Stop_FireWeapon_Internal, this);
	Scheduler->BroadcastMessage(NCsUpdateGroup::GameState, ECsCoroutineMessage::Abort, NCsWeaponCached::Name::Stop_DrawFireProjectile_Internal, this);
}

#pragma endregion Routines

// Owner
#pragma region

void ACsWeapon_DEPRECATED::SetMyOwner(UObject* InMyOwner)
{
	MyOwner = InMyOwner;
}

UObject* ACsWeapon_DEPRECATED::GetMyOwner()
{
	return MyOwner.IsValid() ? MyOwner.Get() : nullptr;
}

bool ACsWeapon_DEPRECATED::IsValidOwnerTypeInGame()
{ 
	return true; 
}

void ACsWeapon_DEPRECATED::SetMyPawn(class ACsPawn* InMyPawn)
{
	SetMyOwner(InMyPawn);

	MyPawn	   = InMyPawn;
	SetInstigator(InMyPawn);

	SetOwner(InMyPawn);
}

ACsPawn* ACsWeapon_DEPRECATED::GetMyPawn()
{
	return MyPawn.IsValid() ? MyPawn.Get() : nullptr;
}

ECsViewType ACsWeapon_DEPRECATED::GetCurrentViewType()
{
#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
	{
		if (UCsAnimInstance* AnimInstance = GetMyOwner<UCsAnimInstance>())
			return AnimInstance->CurrentViewType;
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		if (ACsPawn* Pawn = GetMyPawn())
			return UCsLibrary_Common::IsLocalPawn(GetWorld(), Pawn) ? ECsViewType::FirstPerson : ECsViewType::ThirdPerson;
	}
	return ECsViewType::ECsViewType_MAX;
}

#pragma endregion Owner

// State
#pragma region

void ACsWeapon_DEPRECATED::OnTick(const float &DeltaSeconds)
{
#if WITH_EDITOR 
	if (Override_OnTick_ScriptEvent.IsBound())
	{
		if (CsCVarLogOverrideFunctions->GetInt() == CS_CVAR_DISPLAY)
		{
			UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("ACsWeapon_DEPRECATED::OnTick (%s): Using Override Function."), *GetName());
		}
		Override_OnTick_ScriptEvent.Broadcast(WeaponSlot, DeltaSeconds);
		return;
	}
#endif // #if WITH_EDITOR

#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
	{
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		const float TimeSeconds = GetWorld()->GetTimeSeconds();
		const int32& Count		= EMCsWeaponFireMode::Get().Num();

		// Spread
		for (int32 I = 0; I < Count; ++I)
		{
			const FECsWeaponFireMode& FireMode = EMCsWeaponFireMode::Get().GetEnumAt(I);

			if (DoSpread[FireMode])
			{
				// Firing
				if (TimeSeconds - LastSpreadFireTime[FireMode] > FiringSpreadRecoveryDelay[FireMode])
				{
					CurrentBaseSpread.Set(FireMode, FMath::Max(CurrentBaseSpread[FireMode] - (SpreadRecoveryRate.GetEX(FireMode) * DeltaSeconds), MinSpread.GetEX(FireMode)));
				}
				CurrentSpread.Set(FireMode, FMath::Clamp(CurrentBaseSpread[FireMode], 0.f, MaxSpread.GetEX(FireMode)));
			}
		}
	}

#if WITH_EDITOR 
	OnTick_ScriptEvent.Broadcast(WeaponSlot, DeltaSeconds);
#endif // #if WITH_EDITOR

	OnTick_HandleStates();

	Last_IsFirePressed  = IsFirePressed;
}

void ACsWeapon_DEPRECATED::OnTick_HandleStates()
{
	UCsData_Weapon_DEPRECATED* Data_Weapon = GetMyData_Weapon();
	const int32 maxAmmo			= MaxAmmo.GetEX(CS_WEAPON_DATA_VALUE);

	const float TimeSeconds = GetWorld()->GetTimeSeconds();

	// Recharge Ammo
	if (AllowRechargeAmmo[CS_WEAPON_DATA_VALUE] && 
		bRechargingAmmo &&
		!bUnlimitedAmmo &&
		CurrentAmmo < maxAmmo)
	{
		if (TimeSeconds > NextRechargeAmmoTime)
		{
			IncrementCurrentAmmo(CS_WEAPON_DATA_VALUE);

			if (CurrentAmmo == maxAmmo)
			{
				bRechargingAmmo = false;
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

		const int32& Count = EMCsWeaponFireMode::Get().Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FECsWeaponFireMode& FireMode = EMCsWeaponFireMode::Get().GetEnumAt(I);

			const bool IsPressed = IsFirePressed[FireMode];

			const bool Pass_AutoShots = IsPressed && IsFullAuto[FireMode] && TimeSeconds - Fire_StartTime[FireMode] > TimeBetweenAutoShots.GetEX(FireMode);
			const bool Pass_Shots	  = IsPressed && TimeSeconds - Fire_StartTime[FireMode] > TimeBetweenShots.GetEX(FireMode);

			if (Pass_AutoShots || Pass_Shots)
			{
				Pass |= true;

				// If out of ammo, Reload
				if (ShouldAutoReload(FireMode))
				{
					StopSound(FireMode, FireSound);

					ReloadStartTime = GetWorld()->TimeSeconds;
					bReloadingHandle = true;

					PlayAnimation_Reload();

					LastState    = CurrentState;
					CurrentState = ReloadingState;
				}
				else
				{
					// If using an automatic weapon / continuous fire, then
					// do the firing again
					if ((Pass_AutoShots && CanFire_Auto(FireMode)) ||
						(Pass_Shots && CanFire(FireMode)))
					{
						HandleState_Firing(FireMode);
					}
					// Stop Firing, go to Idle
					else
					{
						//StopFireSound();
						StopSound(FireMode, FireSound);
						StopAnimation(FireMode, FireAnim);

						LastState    = CurrentState;
						CurrentState = IdleState;

						if (AllowRechargeAmmo[CS_WEAPON_DATA_VALUE] && 
							!AllowRechargeAmmoDuringFire[CS_WEAPON_DATA_VALUE])
						{
							RechargeAmmo_StartTime = TimeSeconds;
							NextRechargeAmmoTime   = RechargeAmmo_StartTime + RechargeSecondsPerAmmo.GetEX(CS_WEAPON_DATA_VALUE) + RechargeStartupDelay.GetEX(CS_WEAPON_DATA_VALUE);
							bRechargingAmmo		   = true;
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
			ResetCurrentAmmo(CS_WEAPON_DATA_VALUE);

			bReloadingHandle = false;
			LastState		= CurrentState;
			CurrentState	= IdleState;

#if WITH_EDITOR 
			// In Editor Preview Window
			if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
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
void ACsWeapon_DEPRECATED::OnRep_Seed()
{
	FMath::SRandInit(Seed);
	RandStream = FRandomStream(Seed);
	bSeedInitialized = true;
}
*/
void ACsWeapon_DEPRECATED::CheckState_Idle()
{
#if WITH_EDITOR
	if (Override_CheckState_Idle_ScriptEvent.IsBound())
	{
		if (CsCVarLogOverrideFunctions->GetInt() == CS_CVAR_DISPLAY)
		{
			UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("ACsWeapon_DEPRECATED::CheckState_Idle (%s): Using Override Function."), *GetName());
		}
		Override_CheckState_Idle_ScriptEvent.Broadcast(WeaponSlot);
		return;
	}
#endif // #if WITH_EDITOR

	if (CurrentState == IdleState)
	{
		const float TimeSeconds = GetWorld()->GetTimeSeconds();

		if (bReloading &&
			TimeSeconds - ReloadStartTime > ReloadTime.GetEX(CS_WEAPON_DATA_VALUE))
		{
			ResetCurrentAmmo(CS_WEAPON_DATA_VALUE);
			bReloadingHandle = false;
		}

		if (ShouldAutoReload(EMCsWeaponFireMode::Get().GetMAX()))
		{
			ReloadStartTime = TimeSeconds;
			bReloadingHandle = true;

			PlayAnimation_Reload();

			LastState	 = CurrentState;
			CurrentState = ReloadingState;
		}

		HandleChargeFire();

		bool Pass_Firing = false;

		const int32& Count = EMCsWeaponFireMode::Get().Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FECsWeaponFireMode& FireMode = EMCsWeaponFireMode::Get().GetEnumAt(I);

			if ((IsFullAuto[FireMode] && CanFire_Auto(FireMode)) ||
				CanFire(FireMode))
			{
				Pass_Firing |= true;

				if (LoopFireSound[FireMode])
					PlaySound(FireMode, FireSound);

				if (LoopFireAnim[FireMode])
					PlayAnimation(FireMode, FireAnim);

				if (AllowRechargeAmmo[CS_WEAPON_DATA_VALUE] && !AllowRechargeAmmoDuringFire[CS_WEAPON_DATA_VALUE])
				{
					bRechargingAmmo = false;
				}
				HandleState_Firing(FireMode);
			}
		}
	}
}

void ACsWeapon_DEPRECATED::HandleState_Firing(const FECsWeaponFireMode& FireMode)
{
	CurrentProjectilePerShotIndex.Set(FireMode, CurrentAmmo > ProjectilesPerShot.GetEX(FireMode) ? 0 : ProjectilesPerShot.GetEX(FireMode) - CurrentAmmo);

	const float TimeSeconds = GetWorld()->GetTimeSeconds();

	Fire_StartTime.Set(FireMode, TimeSeconds);
	LastState    = CurrentState;
	CurrentState = FiringState;

	FireWeapon(FireMode);

	if (!bUnlimitedAmmo)
	{
		//CurrentAmmo = FMath::Max(0, CurrentAmmo - ProjectilesPerShot.Get(FireMode));

		// Recharge Ammo
		if (AllowRechargeAmmo[CS_WEAPON_DATA_VALUE])
		{
			if (AllowRechargeAmmoDuringFire[CS_WEAPON_DATA_VALUE])
			{
				bRechargingAmmo	     = true;
				NextRechargeAmmoTime = TimeSeconds + RechargeSecondsPerAmmo.GetEX(CS_WEAPON_DATA_VALUE) + RechargeStartupDelay.GetEX(CS_WEAPON_DATA_VALUE);
			}
		}
	}
}

bool ACsWeapon_DEPRECATED::CanFire(const FECsWeaponFireMode& FireMode)
{
	const float TimeSeconds = GetWorld()->GetTimeSeconds();

	const bool IsBot			  = false;// Cast<AShooterBot>(MyPawn) != nullptr;
	const bool AllowFire		  = !DoingEquipTransition && IsEquipped && (TimeSeconds - Fire_StartTime[FireMode] > TimeBetweenShots.GetEX(FireMode));
	const bool Pass_IsFirePressed = AllowFire && IsFirePressed[FireMode] && !DoFireOnRelease[FireMode] && (IsFullAuto[FireMode] || (!Last_IsFirePressed[FireMode] && IsFirePressed[FireMode]) || IsBot);
	const bool Pass_FireOnRelease = AllowFire && DoFireOnRelease[FireMode] && ((Last_IsFirePressed[FireMode] && !IsFirePressed[FireMode]));
	const bool Pass_Ammo		  = CurrentAmmo > 0 || bUnlimitedAmmo;

	return (Pass_IsFirePressed || Pass_FireOnRelease) && Pass_Ammo && !bReloading;
}

bool ACsWeapon_DEPRECATED::CanFire_Auto(const FECsWeaponFireMode& FireMode)
{
	const float TimeSeconds = GetWorld()->GetTimeSeconds();

	const bool IsBot			  = false;// Cast<AShooterBot>(MyPawn) != nullptr;
	const bool AllowFire		  = !DoingEquipTransition && IsEquipped && (TimeSeconds - Fire_StartTime[FireMode] > TimeBetweenAutoShots.GetEX(FireMode));
	const bool Pass_IsFirePressed = AllowFire && IsFirePressed.Get(FireMode) && !DoFireOnRelease[FireMode] && (IsFullAuto[FireMode] || (!Last_IsFirePressed[FireMode] && IsFirePressed[FireMode]) || IsBot);
	const bool Pass_FireOnRelease = AllowFire && DoFireOnRelease[FireMode] && ((Last_IsFirePressed[FireMode] && !IsFirePressed[FireMode]));
	const bool Pass_Ammo		  = CurrentAmmo > 0 || bUnlimitedAmmo;

	return (Pass_IsFirePressed || Pass_FireOnRelease) && Pass_Ammo && !bReloading;
}

void ACsWeapon_DEPRECATED::Enable()
{
	ResetCurrentAmmo(CS_WEAPON_DATA_VALUE);
}

void ACsWeapon_DEPRECATED::Disable()
{
	const int32& Count = EMCsWeaponFireMode::Get().Num();

	//if (CurrentState == FiringState || GetSound(FireSound))
	{
		for (int32 I = 0; I < Count; ++I)
		{
			const FECsWeaponFireMode& FireMode = EMCsWeaponFireMode::Get().GetEnumAt(I);

			StopSound(FireMode, FireSound);
		}
	}

	LastState    = CurrentState;
	CurrentState = IdleState;

	for (int32 I = 0; I < Count; ++I)
	{
		const FECsWeaponFireMode& FireMode = EMCsWeaponFireMode::Get().GetEnumAt(I);

		IsFirePressed.Set(FireMode, false);
		Last_IsFirePressed.Set(FireMode, false);
	}

	PerformingChargeFire = false;

	if (GetMyData_Weapon())
	{
		for (int32 I = 0; I < Count; ++I)
		{
			const FECsWeaponFireMode& FireMode = EMCsWeaponFireMode::Get().GetEnumAt(I);

			if (LoopFireAnim[FireMode])
				StopAnimation(FireMode, FireAnim);
		}
	}

	for (uint8 I = 0; I < CS_PROJECTILE_FIRE_PAYLOAD_POOL_SIZE; ++I)
	{
		ProjectileFirePayloads[I].Reset();
	}

	ProjectileFirePayloadPoolIndex = 0;

	ClearRoutines();
}

void ACsWeapon_DEPRECATED::Reset()
{
	Disable();

	FireCount = 0;
}

void ACsWeapon_DEPRECATED::Show(){}
void ACsWeapon_DEPRECATED::Hide(){}

#pragma endregion State

void ACsWeapon_DEPRECATED::OnCalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
}

// Animation
#pragma region

void ACsWeapon_DEPRECATED::PlayAnimation(const FECsWeaponFireMode& FireMode, const FECsWeaponAnim &AnimType, const int32 &Index /*=0*/)
{
}

void ACsWeapon_DEPRECATED::PlayAnimation_Reload()
{
	if (PlayAnimation_Reload_Internal_Routine)
		PlayAnimation_Reload_Internal_Routine->End(ECsCoroutineEndReason::UniqueInstance);

	const FECsUpdateGroup& Group = NCsUpdateGroup::GameState;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(GetGameInstance());
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload(Group);

	Payload->CoroutineImpl.BindStatic(&ACsWeapon_DEPRECATED::PlayAnimation_Reload_Internal);
	Payload->StartTime = UCsManager_Time::Get(GetGameInstance())->GetTime(Group);
	Payload->Owner.SetObject(this);

	Payload->SetName(NCsWeaponCached::Str::PlayAnimation_Reload_Internal);
	Payload->SetFName(NCsWeaponCached::Name::PlayAnimation_Reload_Internal);
	
	Payload->SetValue_Float(CS_FIRST, GetAnimationLength(EMCsWeaponFireMode::Get().GetMAX(), ReloadAnim));

	Scheduler->Start(Payload);
}

CS_COROUTINE(ACsWeapon_DEPRECATED, PlayAnimation_Reload_Internal)
{
	ACsWeapon_DEPRECATED* mw			 = r->GetOwnerAsObject<ACsWeapon_DEPRECATED>();
	UWorld* w				 = mw->GetWorld();

	const FECsWeaponAnim& ReloadAnim = mw->ReloadAnim;
	const float& ReloadTime			 = r->GetValue_Float(CS_FIRST);

	const FCsDeltaTime& ElapsedTime  = r->ElapsedTime;

	CS_COROUTINE_BEGIN(r);

	r->AddMessage(ECsCoroutineMessage::Abort, NCsWeaponCached::Name::Stop_PlayAnimation_Reload_Internal);

	mw->PlayAnimation(EMCsWeaponFireMode::Get().GetMAX(), ReloadAnim, 0);

	if (ReloadTime > 0)
		CS_COROUTINE_WAIT_UNTIL(r, ElapsedTime.Time >= ReloadTime);
	
	CS_COROUTINE_END(r);
}

float ACsWeapon_DEPRECATED::GetAnimationLength(const FECsWeaponFireMode& FireMode, const FECsWeaponAnim &AnimType, const int32 &Index /*=0*/)
{
	return 0.0f;
}

void ACsWeapon_DEPRECATED::StopAnimation(const FECsWeaponFireMode& FireMode, const FECsWeaponAnim &AnimType, const int32 &Index /*=0*/)
{
}

#pragma endregion Animation

// Sound
#pragma region

UObject* ACsWeapon_DEPRECATED::GetSoundParent() { return nullptr; }
//ACsSound* ACsWeapon_DEPRECATED::GetSound(const FECsWeaponSound &SoundType){ return nullptr; }

void ACsWeapon_DEPRECATED::PlaySound(const FECsWeaponFireMode& FireMode, const FECsWeaponSound &SoundType)
{
	UCsData_ProjectileWeapon_DEPRECATED* Data	= GetMyData_Weapon<UCsData_ProjectileWeapon_DEPRECATED>();
	const ECsViewType ViewType		= GetCurrentViewType();

	Data->PlaySound(GetWorld(), ViewType, FireMode, SoundType, GetMyOwner(), GetSoundParent());
}

void ACsWeapon_DEPRECATED::StopSound(const FECsWeaponFireMode& FireMode, const FECsWeaponSound &SoundType)
{
	UCsData_ProjectileWeapon_DEPRECATED* Data  = GetMyData_Weapon<UCsData_ProjectileWeapon_DEPRECATED>();
	const ECsViewType ViewType		= GetCurrentViewType();

	Data->StopSound(GetWorld(), ViewType, FireMode, SoundType, GetMyOwner(), GetSoundParent());
}

#pragma endregion Sound

// Equip / UnEquip
#pragma region

void ACsWeapon_DEPRECATED::Equip()
{
	IsEquipped = true;

	OnEquip_Event.Broadcast(WeaponSlot, CurrentAmmo, GetMaxAmmo(CS_WEAPON_DATA_VALUE), GetAmmoReserve(CS_WEAPON_DATA_VALUE, PrimaryFireMode, false));
#if WITH_EDITOR
	OnEquip_ScriptEvent.Broadcast(WeaponSlot, CurrentAmmo, GetMaxAmmo(CS_WEAPON_DATA_VALUE), GetAmmoReserve(CS_WEAPON_DATA_VALUE, PrimaryFireMode, false));
#endif // #if WITH_EDITOR
}

void ACsWeapon_DEPRECATED::UnEquip()
{
	IsEquipped = false;

	OnUnEquip_Event.Broadcast(WeaponSlot);
#if WITH_EDITOR
	OnUnEquip_ScriptEvent.Broadcast(WeaponSlot);
#endif // #if WITH_EDITOR
}

bool ACsWeapon_DEPRECATED::CanUnEquip()
{
	if (!IsEquipped)
		return false;
	if (DoingEquipTransition)
		return false;

	const int32& Count = EMCsWeaponFireMode::Get().Num();

	for (int32 I = 0; I < Count; ++I)
	{
		const FECsWeaponFireMode& FireMode = EMCsWeaponFireMode::Get().GetEnumAt(I);

		if (CurrentProjectilePerShotIndex[FireMode] < ProjectilesPerShot[FireMode] - 1)
			return false;
	}
	return true;
}

#pragma endregion Equip / UnEquip

// Firing
#pragma region

	// Ammo
#pragma region

int32 ACsWeapon_DEPRECATED::GetMaxAmmo(const int32 &Index) { return MaxAmmo.Get(Index); }

void ACsWeapon_DEPRECATED::OnChange_CurrentAmmo(const int32 &Value)
{
	OnChange_CurrentAmmo_Event.Broadcast(WeaponSlot, CurrentAmmo, GetMaxAmmo(CS_WEAPON_DATA_VALUE), GetAmmoReserve(CS_WEAPON_DATA_VALUE, PrimaryFireMode, false));
#if WITH_EDITOR
	OnChange_CurrentAmmo_ScriptEvent.Broadcast(WeaponSlot, CurrentAmmo, GetMaxAmmo(CS_WEAPON_DATA_VALUE), GetAmmoReserve(CS_WEAPON_DATA_VALUE, PrimaryFireMode, false));
#endif // #if WITH_EDITOR
}

void ACsWeapon_DEPRECATED::IncrementCurrentAmmo(const int32 &Index)
{
#if WITH_EDITOR
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
	{
		if (CurrentAmmo < GetMaxAmmo(Index))
			++CurrentAmmo;
	}
	else
#endif // #if WITH_EDITOR
	if (GetMyData_Weapon()->UseInventory())
	{
		// TODO: Later might need a way to store the LastFireMode used
		ACsManager_Inventory* Manager_Inventory = GetMyManager_Inventory();

		const FName& ShortCode = GetAmmoShortCode(PrimaryFireMode, false);

		if (ShortCode == NAME_None)
		{
			UCsData_ProjectileBase* Data_Projectile = GetMyData_Projectile(PrimaryFireMode, false);

			UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("ACsWeapon_DEPRECATED::IncrementCurrentAmmo: No ItemShortCode set for Projectile: %s"), *(Data_Projectile->ShortCode.ToString()));
			check(0);
		}

		const int32 AmmoReserve	= Manager_Inventory->GetItemCount(ShortCode);

		if (CurrentAmmo < GetMaxAmmo(Index) &&
			CurrentAmmo < AmmoReserve)
		{
			++CurrentAmmo;
		}
	}
	else
	{
		if (CurrentAmmo < GetMaxAmmo(Index))
			++CurrentAmmo;
	}
	CurrentAmmoHandle.Resolve();
}

void ACsWeapon_DEPRECATED::ResetCurrentAmmo(const int32 &Index) 
{ 
#if WITH_EDITOR
	// In Editor Preview Window
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
	{
		CurrentAmmo = GetMaxAmmo(Index);
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	if (GetMyData_Weapon()->UseInventory())
	{
		// TODO: Later might need a way to store the LastFireMode used
		ACsManager_Inventory* Manager_Inventory = GetMyManager_Inventory();

		const FName& ShortCode = GetAmmoShortCode(PrimaryFireMode, false);

		if (ShortCode == NAME_None)
		{
			UCsData_ProjectileBase* Data_Projectile = GetMyData_Projectile(PrimaryFireMode, false);

			UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("ACsWeapon_DEPRECATED::ResetCurrentAmmo: No ItemShortCode set for Projectile: %s"), *(Data_Projectile->ShortCode.ToString()));
			check(0);
		}

		const int32 AmmoReserve	= Manager_Inventory->GetItemCount(ShortCode);
		const int32 maxAmmo		= GetMaxAmmo(Index);

		CurrentAmmo = AmmoReserve > maxAmmo ? maxAmmo : AmmoReserve;
	}
	else
	{
		CurrentAmmo = GetMaxAmmo(Index);
	}
	CurrentAmmoHandle.Resolve();
}

const FName& ACsWeapon_DEPRECATED::GetAmmoShortCode(const FECsWeaponFireMode& FireMode, const bool &IsCharged) 
{ 
	return GetMyData_Projectile<UCsData_ProjectileBase>(FireMode, IsCharged)->GetItemShortCode();
}

int32 ACsWeapon_DEPRECATED::GetAmmoReserve(const int32 &Index, const FECsWeaponFireMode& FireMode, const bool &IsCharged)
{
#if WITH_EDITOR
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
	{
		return GetMaxAmmo(Index);
	}
#endif // #if WITH_EDITOR

	if (GetMyData_Weapon()->UseInventory())
	{
		ACsManager_Inventory* Manager_Inventory = GetMyManager_Inventory();

		const FName& ShortCode = GetAmmoShortCode(FireMode, IsCharged);

		if (ShortCode == NAME_None)
		{
			UCsData_ProjectileBase* Data_Projectile = GetMyData_Projectile(FireMode, IsCharged);

			UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("ACsWeapon_DEPRECATED::GetAmmoReserve: No ItemShortCode set for Projectile: %s"), *(Data_Projectile->ShortCode.ToString()));
			check(0);
		}
		return Manager_Inventory->GetItemCount(ShortCode);
	}
	return GetMaxAmmo(Index);
}

void ACsWeapon_DEPRECATED::ConsumeAmmo(const FECsWeaponFireMode& FireMode, const bool& IsCharged)
{
	--CurrentAmmo;
	CurrentAmmoHandle.Resolve();
	
	if (GetMyData_Weapon()->UseInventory())
	{
		UCsData_ProjectileBase* Data_Projectile = GetMyData_Projectile<UCsData_ProjectileBase>(PrimaryFireMode, false);
		const FName& ShortCode = Data_Projectile->GetItemShortCode();

		OnConsumeAmmo_Event.Broadcast(ShortCode);
#if WITH_EDITOR
		OnConsumeAmmo_ScriptEvent.Broadcast(ShortCode);
#endif // #if WITH_EDITOR
	}
}

void ACsWeapon_DEPRECATED::ConsumeAmmoItem(const FECsWeaponFireMode& FireMode, const bool &IsCharged, TArray<FCsItem*> &OutItems)
{
#if WITH_EDITOR
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
		return;
#endif // #if WITH_EDITOR

	if (GetMyData_Weapon()->UseInventory())
	{
		ACsManager_Inventory* Manager_Inventory = GetMyManager_Inventory();
		UCsData_ProjectileBase* Data_Projectile	= GetMyData_Projectile<UCsData_ProjectileBase>(FireMode, IsCharged);
		const FName& ShortCode					= Data_Projectile->GetItemShortCode();

		if (ShortCode == NAME_None)
		{
			UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("ACsWeapon_DEPRECATED::ConsumeAmmoItem: No ItemShortCode set for Projectile: %s"), *(Data_Projectile->ShortCode.ToString()));
			check(0);
		}

		// Consume Item
		if (Data_Projectile->GetOnAllocateConsumeItem())
		{
			Manager_Inventory->ConsumeFirstItem(ShortCode, OutItems);
		}
		// Drop Item
		else
		if (Data_Projectile->GetOnAllocateDropItem())
		{
			Manager_Inventory->DropFirstItem(ShortCode);
		}
		OnConsumeAmmoItem_Event.Broadcast(ShortCode, OutItems);
	}
}

#pragma endregion Ammo

uint8 ACsWeapon_DEPRECATED::GetProjectilesPerShot(const FECsWeaponFireMode& FireMode) { return ProjectilesPerShot.Get(FireMode); }
float ACsWeapon_DEPRECATED::GetTimeBetweenProjectilesPerShot(const FECsWeaponFireMode& FireMode) { return TimeBetweenProjectilesPerShot.Get(FireMode); }
float ACsWeapon_DEPRECATED::GetTimeBetweenShots(const FECsWeaponFireMode& FireMode) { return TimeBetweenShots.Get(FireMode); }
float ACsWeapon_DEPRECATED::GetTimeBetweenAutoShots(const FECsWeaponFireMode& FireMode) { return TimeBetweenAutoShots.Get(FireMode); }

void ACsWeapon_DEPRECATED::SetIsFirePressed(const FECsWeaponFireMode& FireMode, const bool &Value, const bool &DoOnTick)
{
	IsFirePressed.Set(FireMode, Value);

	const float TimeSeconds = GetWorld()->GetTimeSeconds();

	if (Value)
	{
		IsFirePressed_StartTime.Set(FireMode, TimeSeconds);
	}
	else
	{
		IsFireReleased_StartTime.Set(FireMode, TimeSeconds);
	}

#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
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

float ACsWeapon_DEPRECATED::GetMaxChargeFireTime(const FECsWeaponFireMode& FireMode) { return MaxChargeFireTime.Get(FireMode); }

void ACsWeapon_DEPRECATED::HandleChargeFire()
{
	if (PerformingChargeFire)
		return;
	
	const int32& Count = EMCsWeaponFireMode::Get().Num();

	for (int32 I = 0; I < Count; ++I)
	{
		const FECsWeaponFireMode& FireMode = EMCsWeaponFireMode::Get().GetEnumAt(I);

		if (AllowChargeFire[FireMode] &&
			IsFirePressed[FireMode])
		{
			StartChargeFire(FireMode);
			return;
		}
	}
}

void ACsWeapon_DEPRECATED::StartChargeFire(const FECsWeaponFireMode& FireMode)
{
	PerformingChargeFire = true;
	ChargeFire_StartTime = GetWorld()->TimeSeconds;

	if (StartChargeFire_Internal_Routine)
		StartChargeFire_Internal_Routine->End(ECsCoroutineEndReason::UniqueInstance);

	const FECsUpdateGroup& Group = NCsUpdateGroup::GameState;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(GetGameInstance());
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload(Group);

	Payload->CoroutineImpl.BindStatic(&ACsWeapon_DEPRECATED::StartChargeFire_Internal);
	Payload->StartTime = UCsManager_Time::Get(GetGameInstance())->GetTime(Group);
	Payload->Owner.SetObject(this);

	Payload->SetName(NCsWeaponCached::Str::StartChargeFire_Internal);
	Payload->SetFName(NCsWeaponCached::Name::StartChargeFire_Internal);

	Payload->SetValue_Int(CS_FIRST,	FireMode.Value);

	Scheduler->Start(Payload);
}

CS_COROUTINE(ACsWeapon_DEPRECATED, StartChargeFire_Internal)
{
	ACsWeapon_DEPRECATED* mw = r->GetOwnerAsObject<ACsWeapon_DEPRECATED>();

	const FCsTime& CurrentTime = UCsManager_Time::Get(mw->GetGameInstance())->GetTime(r->GetGroup());
	
	FCsTime& StartTime		= r->GetValue_Timer(CS_FIRST);
	const float ElapsedTime = CurrentTime.Time - StartTime.Time;

	const float& WaitTime	 = r->GetValue_Float(CS_FIRST);
	float FireStartLoopTime  = FMath::Max(mw->TimeBetweenShots.Max(), mw->TimeBetweenAutoShots.Max());

	const FECsWeaponFireMode& FireMode = EMCsWeaponFireMode::Get().GetEnumAt(r->GetValue_Int(CS_FIRST));

	const float StartToLoopBlendTime = 0.1f;

	CS_COROUTINE_BEGIN(r);

	StartTime = CurrentTime;

	r->AddMessage(ECsCoroutineMessage::Abort, NCsWeaponCached::Name::Stop_StartChargeFire_Internal);

	// ChargeFireStart
	mw->PlayAnimation(FireMode, mw->ChargeFireStartAnim);

	r->SetValue_Float(CS_FIRST, mw->GetAnimationLength(FireMode, mw->ChargeFireStartAnim));

	CS_COROUTINE_WAIT_UNTIL(r, ElapsedTime >= FMath::Max(WaitTime - StartToLoopBlendTime, 0.0f));

	StartTime = CurrentTime;

	// ChargeFireLoop
	mw->PlayAnimation(FireMode, mw->ChargeFireLoopAnim);

	CS_COROUTINE_WAIT_UNTIL(r, ElapsedTime >= FireStartLoopTime);

	CS_COROUTINE_END(r);
}

bool ACsWeapon_DEPRECATED::StartChargeFire_StopCondition(FCsRoutine* r)
{
	ACsWeapon_DEPRECATED* mw = r->GetOwnerAsObject<ACsWeapon_DEPRECATED>();

	const FECsWeaponFireMode& FireMode = EMCsWeaponFireMode::Get().GetEnumAt(r->GetValue_Int(CS_FIRST));

#if WITH_EDITOR 
	// In Editor Preview Window
	if (mw && UCsLibrary_Common::IsPlayInEditorPreview(mw->GetWorld()))
	{
		if (!mw->GetMyOwner())
		{
			mw->StopAnimation(FireMode, mw->ChargeFireStartAnim);
			mw->StopAnimation(FireMode, mw->ChargeFireLoopAnim);
			return true;
		}
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		if (mw)
		{
			mw->StopAnimation(FireMode, mw->ChargeFireStartAnim);
			mw->StopAnimation(FireMode, mw->ChargeFireLoopAnim);
		}
		return true;
	}
	return false;
}

float ACsWeapon_DEPRECATED::GetChargeFireHeldTime()
{
	return GetWorld()->TimeSeconds - ChargeFire_StartTime;
}

float ACsWeapon_DEPRECATED::GetChargeFireHeldPercent(const FECsWeaponFireMode& FireMode)
{
	return FMath::Clamp(GetChargeFireHeldTime(), 0.0f, MaxChargeFireTime.GetEX(FireMode) / MaxChargeFireTime.GetEX(FireMode));
}

float ACsWeapon_DEPRECATED::GetCurrentChargeFireHeldTime()
{
	return PerformingChargeFire ? GetWorld()->TimeSeconds - ChargeFire_StartTime : 0.0f;
}

float ACsWeapon_DEPRECATED::GetCurrentChargeFireHeldPercent(const FECsWeaponFireMode& FireMode)
{
	return PerformingChargeFire ? FMath::Clamp(GetChargeFireHeldTime(), 0.0f, MaxChargeFireTime.GetEX(FireMode) / MaxChargeFireTime.GetEX(FireMode)) : 0.0f;
}

void ACsWeapon_DEPRECATED::StopChargeFire(const FECsWeaponFireMode& FireMode)
{
	if (!AllowChargeFire[FireMode])
		return;

	PerformingChargeFire = false;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(GetGameInstance());

	Scheduler->BroadcastMessage(NCsUpdateGroup::GameState, ECsCoroutineMessage::Abort, NCsWeaponCached::Name::Stop_StartChargeFire_Internal, this);

	if (StartChargeFire_Internal_Routine)
		StartChargeFire_Internal_Routine->End(ECsCoroutineEndReason::UniqueInstance);

	StopAnimation(FireMode, ChargeFireStartAnim);
	StopAnimation(FireMode, ChargeFireLoopAnim);
}

#pragma endregion Charge

	// Spread
#pragma region

float ACsWeapon_DEPRECATED::GetMinSpread(const FECsWeaponFireMode& FireMode) { return MinSpread.Get(FireMode); }
float ACsWeapon_DEPRECATED::GetMaxSpread(const FECsWeaponFireMode& FireMode) { return MaxSpread.Get(FireMode); }
float ACsWeapon_DEPRECATED::GetSpreadAddedPerShot(const FECsWeaponFireMode& FireMode) { return SpreadAddedPerShot.Get(FireMode); }
float ACsWeapon_DEPRECATED::GetSpreadRecoveryRate(const FECsWeaponFireMode& FireMode) { return SpreadRecoveryRate.Get(FireMode); }
float ACsWeapon_DEPRECATED::GetFiringSpreadRecoveryDelay(const FECsWeaponFireMode& FireMode) { return FiringSpreadRecoveryDelay.Get(FireMode); }
float ACsWeapon_DEPRECATED::GetMovingSpreadBonus(const FECsWeaponFireMode& FireMode) { return MovingSpreadBonus.Get(FireMode); }

#pragma endregion Spread

FVector ACsWeapon_DEPRECATED::GetFireWeaponStartLocation(const FECsWeaponFireMode& FireMode)
{
	return FVector::ZeroVector;
}

FVector ACsWeapon_DEPRECATED::GetFireWeaponStartDirection(const FECsWeaponFireMode& FireMode)
{
	return FVector::ZeroVector;
}

FCsProjectileFirePayload* ACsWeapon_DEPRECATED::AllocateProjectileFirePayload(const FECsWeaponFireMode& FireMode)
{
	const uint8 Count = CS_PROJECTILE_FIRE_PAYLOAD_POOL_SIZE;
	uint8 PoolIndex	  = 0;

	for (uint8 I = 0; I < Count; ++I)
	{
		FCsProjectileFirePayload* Payload = &ProjectileFirePayloads[ProjectileFirePayloadPoolIndex];

		if (!Payload->bAllocated)
		{
			Payload->bAllocated = true;

			Payload->Time		= GetWorld()->GetTimeSeconds();
			Payload->RealTime	= GetWorld()->GetRealTimeSeconds();
			Payload->Frame		= UCsLibrary_Common::GetCurrentFrame(GetWorld());

			Payload->Location		 = GetFireWeaponStartLocation(FireMode);
			Payload->Direction	 = GetFireWeaponStartDirection(FireMode);
			Payload->ChargePercent = GetCurrentChargeFireHeldPercent(FireMode);

			/*
			ACsGameState_DEPRECATED* GameState		   = GetWorld()->GetGameState<ACsGameState_DEPRECATED>();
			ACsPlayerState* MyPlayerState	   = Cast<ACsPlayerState>(MyPawn->PlayerState);
			const uint8 MappingId			   = MyPlayerState ? MyPlayerState->PlayerData.AimAssistTargetMappingId : CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID;
			ACsPlayerState* TargetPlayerState = GameState->GetPlayerState(MappingId);
			ACsCharacter* TargetPawn		   = TargetPlayerState ? TargetPlayerState->GetMyPawn() : nullptr;

			Cache->HomingTarget				   = TargetPawn;
			Cache->HomingAccelerationMagnitude = 100.0f;

			const FName BoneName = TargetPawn ? TargetPawn->GetMesh()->GetBoneName(MyPlayerState->PlayerData.AimAssistBoneIndex) : NAME_Name;

			Cache->HomingBoneName = BoneName;
			*/
			return Payload;
		}
		ProjectileFirePayloadPoolIndex = (ProjectileFirePayloadPoolIndex + I) % Count;
	}

	UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("ACsWeapon_DEPRECATED::AllocateProjectileFirePayload: Warning. Pool is exhausted. Using Oldest Active Projectile Fire Payload."));
	return nullptr;
}

void ACsWeapon_DEPRECATED::FireWeapon(const FECsWeaponFireMode& FireMode)
{
#if WITH_EDITOR 
	if (Override_FireWeapon_ScriptEvent.IsBound())
	{
		if (CsCVarLogOverrideFunctions->GetInt() == CS_CVAR_DISPLAY)
		{
			UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("ACsWeapon_DEPRECATED::FireWeapon (%s): Using Override Function."), *GetName());
		}
		Override_FireWeapon_ScriptEvent.Broadcast(WeaponSlot, FireMode);
		return;
	}
#endif // #if WITH_EDITOR

	if (FireWeapon_Internal_Routine)
		FireWeapon_Internal_Routine->End(ECsCoroutineEndReason::UniqueInstance);
	
	const FECsUpdateGroup& Group = NCsUpdateGroup::GameState;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(GetGameInstance());
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload(Group);

	Payload->CoroutineImpl.BindStatic(&ACsWeapon_DEPRECATED::FireWeapon_Internal);
	Payload->StartTime = UCsManager_Time::Get(GetGameInstance())->GetTime(Group);
	Payload->Owner.SetObject(this);
	Payload->SetName(NCsWeaponCached::Str::FireWeapon_Internal);
	Payload->SetFName(NCsWeaponCached::Name::FireWeapon_Internal);

	Payload->SetValue_Int(CS_FIRST, FireMode.Value);

	Scheduler->Start(Payload);
}

CS_COROUTINE(ACsWeapon_DEPRECATED, FireWeapon_Internal)
{
	ACsWeapon_DEPRECATED* mw = r->GetOwnerAsObject<ACsWeapon_DEPRECATED>();
	UWorld* w	  = mw->GetWorld();

	const FECsWeaponFireMode& FireMode = EMCsWeaponFireMode::Get().GetEnumAt(r->GetValue_Int(CS_FIRST));

	const FCsTime& CurrentTime = UCsManager_Time::Get(mw->GetGameInstance())->GetTime(r->GetGroup());
	FCsDeltaTime& ElapsedTime	   = r->GetValue_DeltaTime(CS_FIRST);

	ElapsedTime += r->DeltaTime;

#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsLibrary_Common::IsPlayInEditorPreview(w))
	{
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
	}

	CS_COROUTINE_BEGIN(r);

	r->AddMessage(ECsCoroutineMessage::Abort, NCsWeaponCached::Name::Stop_FireWeapon_Internal);

	mw->StopChargeFire(FireMode);

	do
	{
		{
			// Set the StartTime
			ElapsedTime.Reset();

			// Play Fire Sound
			if (!mw->LoopFireSound.Get(FireMode))
				mw->PlaySound(FireMode, mw->FireSound);
			// Play Fire Animation
			if (!mw->LoopFireAnim.Get(FireMode))
				mw->PlayAnimation(FireMode, mw->FireAnim);

#if WITH_EDITOR 
			// In Editor Preview Window
			if (UCsLibrary_Common::IsPlayInEditorPreview(w))
			{
				mw->ConsumeAmmo(FireMode, false);
			}
			// In Game
			else
#endif // #if WITH_EDITOR
			{
				FCsProjectileFirePayload* Payload = mw->AllocateProjectileFirePayload(FireMode);
				
				mw->ConsumeAmmoItem(FireMode, Payload->ChargePercent > 0.0f, Payload->Items);
				mw->ConsumeAmmo(FireMode, Payload->ChargePercent > 0.0f);

				if (mw->IsHitscan.Get(FireMode))
					mw->FireHitscan(FireMode, Payload);
				else
					mw->FireProjectile(FireMode, Payload);
				++(mw->FireCount);
				Payload->Reset();
			}
			mw->PlayMuzzleFlash(FireMode);
			
			mw->CurrentProjectilePerShotIndex.Add(FireMode, 1);
		}

		if (mw->CurrentProjectilePerShotIndex[FireMode] < mw->ProjectilesPerShot[FireMode])
		{
			CS_COROUTINE_WAIT_UNTIL(r, ElapsedTime.Time >= mw->TimeBetweenProjectilesPerShot[FireMode]);
		}
	} while (mw->CurrentProjectilePerShotIndex[FireMode] < mw->ProjectilesPerShot[FireMode]);

	mw->CurrentState = mw->IdleState;
	CS_COROUTINE_END(r);
}

bool ACsWeapon_DEPRECATED::FireWeapon_StopCondition(FCsRoutine* r)
{
	ACsWeapon_DEPRECATED* mw				       = r->GetOwnerAsObject<ACsWeapon_DEPRECATED>();
	const FECsWeaponFireMode& FireMode = EMCsWeaponFireMode::Get().GetEnumAt(r->GetValue_Int(CS_FIRST));

	if (mw &&
		!mw->GetMyOwner())
	{
		mw->StopAnimation(FireMode, mw->FireAnim);
		return true;
	}
	return false;
}

FVector ACsWeapon_DEPRECATED::GetOwnerRightVector()
{
	if (AActor* Actor = GetMyOwner<AActor>())
		return Actor->GetActorRightVector();
	if (USceneComponent* Component = GetMyOwner<USceneComponent>())
		return Component->GetRightVector();
	return FVector::RightVector;
}

FVector ACsWeapon_DEPRECATED::GetFireProjectileDestination()
{
	return FVector::ZeroVector;
}

void ACsWeapon_DEPRECATED::FireProjectile(const FECsWeaponFireMode& FireMode, FCsProjectileFirePayload* FirePayload)
{
	const FVector& RealStart  = FirePayload->Location;
	FVector RealDir			  = FirePayload->Direction;

	UCsData_ProjectileWeapon_DEPRECATED* Data_Weapon	= GetMyData_Weapon<UCsData_ProjectileWeapon_DEPRECATED>();
	UCsData_ProjectileBase* Data_Projectile	= Data_Weapon->GetData_Projectile(FireMode, FirePayload->ChargePercent > 0.0f);
	const bool UseFakeProjectile			= Data_Weapon->UseFakeProjectile(FireMode);

	FVector RealEnd = RealStart;

	if (UseFakeProjectile)
	{
		RealEnd = GetFireProjectileDestination();
	}
	else
	{
		static const float MAX_RANGE = 30000.0f;
		RealEnd						 = RealStart + MAX_RANGE * RealDir;
	}

	const ECsViewType ViewType = GetCurrentViewType();
	const FVector FakeStart	   = GetMuzzleLocation(ViewType, FireMode);
	FVector FakeDir			   = (RealEnd - FakeStart).GetSafeNormal();

	// Spread
	if (DoSpread.Get(FireMode))
	{
		if (CurrentSpread.Get(FireMode) > 0.f)
		{
			// Real
			const float SpreadPitch = RandStream.FRand() * CurrentSpread.Get(FireMode);
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
		CurrentBaseSpread.Set(FireMode, FMath::Min(CurrentBaseSpread[FireMode] + SpreadAddedPerShot.GetEX(FireMode), MaxSpread.GetEX(FireMode)));
		LastSpreadFireTime.Set(FireMode, GetWorld()->TimeSeconds);
	}
	FireProjectile_Internal(FireMode, FirePayload);

	// Allocate Projectiles
	ACsGameState_DEPRECATED* GameState					  = GetWorld()->GetGameState<ACsGameState_DEPRECATED>();
	UCsManager_Projectile* Manager_Projectile = GameState->Manager_Projectile;
	
	// Real
	FCsProjectileBasePayload* Payload = nullptr;// Manager_Projectile->AllocatePayload<FCsProjectileBasePayload>(Data_Projectile->GetProjectileType());

	Payload->Relevance = UseFakeProjectile ? ECsProjectileRelevance::RealInvisible : ECsProjectileRelevance::RealVisible;
	Payload->Instigator = GetMyOwner();
	Payload->Owner		= this;
	Payload->Data		= Data_Projectile;

	FirePayload->Location  = RealStart;
	FirePayload->Direction = RealDir;

	Payload->Set(FirePayload);

	ACsProjectileBase* RealProjectile = nullptr;// Manager_Projectile->Fire(Data_Projectile->GetProjectileType(), Payload);

	const bool IsLocalPawn = UCsLibrary_Common::IsLocalPawn(GetWorld(), GetMyPawn());

	if ((CsCVarDrawLocalPlayerWeaponFireProjectile->GetInt() == CS_CVAR_DRAW &&
		 IsLocalPawn) ||
		CsCVarDrawWeaponFireProjectile->GetInt() == CS_CVAR_DRAW)
	{
		DrawFireProjectile(RealProjectile, RealStart, RealEnd);
	}

	// Fake
	if (UseFakeProjectile)
	{
		FCsProjectileBasePayload* FakePayload = nullptr;// Manager_Projectile->AllocatePayload<FCsProjectileBasePayload>(Data_Projectile->GetProjectileType());

		FakePayload->Relevance	= ECsProjectileRelevance::Fake;
		FakePayload->Instigator = GetMyOwner();
		FakePayload->Owner		= this;
		FakePayload->Data		= Data_Projectile;

		FCsProjectileFirePayload* FakeFirePayload = AllocateProjectileFirePayload(FireMode);
		FakeFirePayload->Location				  = FakeStart;
		FakeFirePayload->Direction			      = FakeDir;

		FakePayload->Set(FakeFirePayload);

		ACsProjectileBase* FakeProjectile = nullptr;// Manager_Projectile->Fire(Data_Projectile->GetProjectileType(), FakePayload);

		FakeFirePayload->Reset();

		RealProjectile->FakeProjectile = FakeProjectile;
		
		if ((CsCVarDrawLocalPlayerWeaponFireProjectile->GetInt() == CS_CVAR_DRAW &&
			IsLocalPawn) ||
			CsCVarDrawWeaponFireProjectile->GetInt() == CS_CVAR_DRAW)
		{
			DrawFireProjectile(FakeProjectile, FakeStart, RealEnd);
		}
	}
}

void ACsWeapon_DEPRECATED::FireProjectile_Internal(const FECsWeaponFireMode& FireMode, FCsProjectileFirePayload* Payload) {}

void ACsWeapon_DEPRECATED::DrawFireProjectile(class ACsProjectileBase* Projectile, const FVector &Start, const FVector &End)
{
	const FECsUpdateGroup& Group = NCsUpdateGroup::GameState;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(GetGameInstance());
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload(Group);

	Payload->CoroutineImpl.BindStatic(&ACsWeapon_DEPRECATED::DrawFireProjectile_Internal);
	Payload->StartTime = UCsManager_Time::Get(GetGameInstance())->GetTime(Group);
	Payload->Owner.SetObject(this);
	Payload->SetName(NCsWeaponCached::Str::DrawFireProjectile_Internal);
	Payload->SetFName(NCsWeaponCached::Name::DrawFireProjectile_Internal);

	static const int32 START_INDEX = 0;
	Payload->SetValue_Vector(START_INDEX, Start);

	static const int32 END_INDEX = 1;
	Payload->SetValue_Vector(END_INDEX, End);

	Scheduler->Start(Payload);
}

CS_COROUTINE(ACsWeapon_DEPRECATED, DrawFireProjectile_Internal)
{
	ACsProjectileBase* p = r->GetOwnerAsObject<ACsProjectileBase>();
	UWorld* w			 = p->GetWorld();
	
	static const int32 START_INDEX = 0;
	const FVector& Start = r->GetValue_Vector(START_INDEX);
	
	static const int32 END_INDEX = 1;
	const FVector& End = r->GetValue_Vector(END_INDEX);

	const FCsDeltaTime& DeltaTime = r->DeltaTime;

	CS_COROUTINE_BEGIN(r);

	r->AddMessage(ECsCoroutineMessage::Abort, NCsWeaponCached::Name::Stop_DrawFireProjectile_Internal);

	do
	{
		DrawDebugLine(w, Start, End, FColor::Red, false, DeltaTime.Time + 0.005f, 0, 0.25f);

		CS_COROUTINE_YIELD(r);

	} while (p->Cache.bAllocated);

	CS_COROUTINE_END(r);
}

	// Hitscan
#pragma region

int32 ACsWeapon_DEPRECATED::GetObstaclePenetractions(const FECsWeaponFireMode& FireMode) { return ObstaclePenetrations.Get(FireMode); }
int32 ACsWeapon_DEPRECATED::GetPawnPenetrations(const FECsWeaponFireMode& FireMode) { return PawnPenetrations.Get(FireMode); }

void ACsWeapon_DEPRECATED::GetFireHitscanIgnoreActors(TArray<AActor*> &OutActors)
{ 
	OutActors.Add(this);

	if (AActor* Actor = GetMyOwner<AActor>())
		OutActors.Add(Actor);
}

void ACsWeapon_DEPRECATED::GetFireHitscanIgnoreComponents(TArray<UPrimitiveComponent*> &OutComponents){}

void ACsWeapon_DEPRECATED::FireHitscan(const FECsWeaponFireMode& FireMode, const FCsProjectileFirePayload* Payload)
{
	//ACsPawn* Pawn					 = GetMyPawn();
	//ACsPlayerState* MyPlayerState	 = Cast<ACsPlayerState>(Pawn->PlayerState);
	UCsData_ProjectileWeapon_DEPRECATED* Data_Weapon	= GetMyData_Weapon<UCsData_ProjectileWeapon_DEPRECATED>();
	UCsData_ProjectileBase* Data_Projectile	= Data_Weapon->GetData_Projectile(FireMode, Payload->ChargePercent > 0.0f);
	ACsManager_Trace* Manager_Trace			= ACsManager_Trace::Get(GetWorld());

	const ECollisionChannel ProjectileCollision = Data_Projectile->GetCollisionObjectType();

	const FVector& Start	   = Payload->Location;
	const FVector& Dir		   = Payload->Direction;
	const float& MaxTraceRange = Data_Projectile->GetMaxRange();
	const FVector End		   = Start + MaxTraceRange * Dir;

		// Ignored Actors
	TArray<AActor*> IgnoredActors;
	GetFireHitscanIgnoreActors(IgnoredActors);
		// Ignored Components
	TArray<UPrimitiveComponent*> IgnoredComponents;
	GetFireHitscanIgnoreComponents(IgnoredComponents);

	// See which Pawns we can hit and which we should ignore
	TArray<ACsPawn*> HittablePawns;
	
	const bool AllowInfinitePawnPenetrations	 = PawnPenetrations.GetEX(FireMode) < 0;
	const bool AllowInfiniteObstaclePenetrations = ObstaclePenetrations.GetEX(FireMode) < 0;

	int32 RecordedPawnPenetrations     = 0;
	int32 RecordedObstaclePenetrations = 0;
	bool HitFound					   = true;

	FHitResult HitResult;

	// Hit trace/ Hit simulation
	while ((AllowInfinitePawnPenetrations || RecordedPawnPenetrations <= PawnPenetrations.GetEX(FireMode)) &&
		   (AllowInfiniteObstaclePenetrations || RecordedObstaclePenetrations <= ObstaclePenetrations.GetEX(FireMode)) &&
		    HitFound)
	{
		HitFound = false;

		HitResult.Reset(0.0f, false);

		// Hitscan with cylinder
		if (DoesHitscanUseRadius[FireMode])
		{
			// See if this line is close enough to hit any enemy characters
			const int32 HitPawnCount = HittablePawns.Num();

			for (int32 I = HitPawnCount - 1; I >= 0; --I)
			{
				ACsPawn* HitPawn				  = HittablePawns[I];
				UCsData_Character* Data_Character = HitPawn->GetMyData_Character();

				const float ProjectileRadius = Data_Projectile->GetSphereRadius();

				// Head
				if (FCsHeadCollision* HeadCollision = Data_Character->GetHeadCollision())
				{
					const float HeadRadius	= HeadCollision->Radius;
					const FName BoneName	= HeadCollision->BoneName;
					const FVector Offset	= HeadCollision->Offset;

					const FVector HeadLocation = HitPawn->GetMesh()->GetBoneLocation(BoneName) + Offset;
					const FVector HeadPoint    = FMath::ClosestPointOnSegment(HeadLocation, Start, End);

					const float DistanceToHead = FVector::Dist(HeadPoint, HeadLocation);

					// Head is close enough to potential trace. Try tracing directly to the Head
					if (DistanceToHead < HeadRadius + ProjectileRadius)
					{
						const float TraceDist	  = 1.5f * (HeadLocation - Start).Size();
						const FVector TargetPoint = HeadLocation + TraceDist * (HeadLocation - Start);

						FCsTraceRequest* Request = Manager_Trace->AllocateRequest();

						Request->Caller		= this;
						Request->CallerId	= UniqueObjectId;
						Request->Start		= Start;
						Request->End		= TargetPoint;
						Request->bAsync		= false;
						Request->Type		= ECsTraceType::Line;
						Request->Method		= ECsTraceMethod::Single;
						Request->Query		= ECsTraceQuery::Channel;
						Request->Channel	= ProjectileCollision;
						Request->Params.bReturnPhysicalMaterial = true;
						Request->Params.AddIgnoredActors(IgnoredActors);
						Request->Params.AddIgnoredComponents(IgnoredComponents);

						FCsTraceResponse* Response = Manager_Trace->Trace(Request);

						HitFound = Response->bResult;

						if (Response->OutHits.Num() > CS_EMPTY)
							UCsLibrary_Common::CopyHitResult(Response->OutHits[CS_FIRST], HitResult);

						Response->Reset();

						HittablePawns.RemoveAt(I);
						break;
					}
				}

				// Body
				const FVector BodyLocation = HitPawn->GetCapsuleComponent()->GetComponentLocation();

				const FVector BodyLocationXY = FVector(BodyLocation.X, BodyLocation.Y, 0);
				const float BodyLocationZ    = BodyLocation.Z;

				const FVector BodyPoint = FMath::ClosestPointOnSegment(BodyLocation, Start, End);

				const FVector BodyPointXY = FVector(BodyPoint.X, BodyPoint.Y, 0);
				const float BodyPointZ    = BodyPoint.Z;

				const float BodyXYDistFromLine = FVector::Dist(BodyPointXY, BodyLocationXY);
				const float BodyZDistFromLine  = FMath::Abs(BodyLocationZ - BodyPointZ);

				const float CharacterRadius  = HittablePawns[I]->GetCapsuleComponent()->GetScaledCapsuleRadius();
				const float CharacterHeight  = HittablePawns[I]->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

				// Body is close enough to potential trace. Try tracing directly to the body
				if (BodyXYDistFromLine < CharacterRadius + ProjectileRadius && BodyZDistFromLine < CharacterHeight + ProjectileRadius)
				{
					const float TraceDist     = 1.5f * (BodyLocation - Start).Size();
					const FVector TargetPoint = BodyLocation + TraceDist * (BodyLocation - Start);
					
					FCsTraceRequest* Request = Manager_Trace->AllocateRequest();

					Request->Caller		= this;
					Request->CallerId	= UniqueObjectId;
					Request->Start		= Start;
					Request->End		= TargetPoint;
					Request->bAsync		= false;
					Request->Type		= ECsTraceType::Line;
					Request->Method		= ECsTraceMethod::Single;
					Request->Query		= ECsTraceQuery::Channel;
					Request->Channel	= ProjectileCollision;
					Request->Params.bReturnPhysicalMaterial = true;
					Request->Params.AddIgnoredActors(IgnoredActors);
					Request->Params.AddIgnoredComponents(IgnoredComponents);

					FCsTraceResponse* Response = Manager_Trace->Trace(Request);

					HitFound = Response->bResult;

					if (Response->OutHits.Num() > CS_EMPTY)
						UCsLibrary_Common::CopyHitResult(Response->OutHits[CS_FIRST], HitResult);

					Response->Reset();

					HittablePawns.RemoveAt(I);
					break;
				}
			}
		}
		// Hit NOT Found and NO Hitscan with cylinder
		if (!HitFound || 
			!DoesHitscanUseRadius[FireMode])
		{
			FCsTraceRequest* Request = Manager_Trace->AllocateRequest();

			Request->Caller		= this;
			Request->CallerId	= UniqueObjectId;
			Request->Start		= Start;
			Request->End		= End;
			Request->bAsync		= false;
			Request->Type		= ECsTraceType::Line;
			Request->Method		= ECsTraceMethod::Single;
			Request->Query		= ECsTraceQuery::Channel;
			Request->Channel	= ProjectileCollision;
			Request->Params.bReturnPhysicalMaterial = true;
			Request->Params.AddIgnoredActors(IgnoredActors);
			Request->Params.AddIgnoredComponents(IgnoredComponents);

			FCsTraceResponse* Response = Manager_Trace->Trace(Request);

			HitFound = Response->bResult;

			if (Response->OutHits.Num() > CS_EMPTY)
				UCsLibrary_Common::CopyHitResult(Response->OutHits[CS_FIRST], HitResult);

			Response->Reset();

			if ((CsCVarDrawLocalPlayerWeaponFireProjectile->GetInt() == CS_CVAR_DRAW &&
				UCsLibrary_Common::IsLocalPawn(GetWorld(), GetMyPawn())) ||
				CsCVarDrawWeaponFireProjectile->GetInt() == CS_CVAR_DRAW)
			{
				const float DrawTime = FMath::Max(TimeBetweenAutoShots.GetEX(FireMode), TimeBetweenShots.GetEX(FireMode));

				DrawDebugLine(GetWorld(), Start, HitFound ? HitResult.Location : End, FColor::Red, false, DrawTime, 0, 1.0f);
			}
		}
		// Hit IS Found. Check penetrations and modifiers
		if (HitFound)
		{
			//ACsManager_Damage* Manager_Damage = ACsManager_Damage::Get(GetWorld());
			FCsDamageEvent* Event = nullptr;// Manager_Damage->AllocateEvent();

			Event->Damage	  = Data_Projectile->GetDamage();
			Event->Instigator = GetMyOwner();
			Event->Causer	  = this;
			//Event->SetDamageType();
			//Event->SetHitType();
			
			UCsLibrary_Common::CopyHitResult(HitResult, Event->HitInfo);
			
			//if (PawnToHit && UShooterStatics::IsOnSameTeam(GetWorld(), PawnToHit, MyPawn))
			//{
			//	continue;
			//}

			ACsPawn* HitPawn = Cast<ACsPawn>(HitResult.GetActor());

			if (HitPawn)
				++RecordedPawnPenetrations;
			else
				++RecordedObstaclePenetrations;

			// Pawn
			if (HitPawn)
			{
				if (HitPawn->GetLocalRole() == ROLE_Authority)
				{
					// Apply Damage Modifiers
					float& Damage = Event->Damage;

					// Location based Damage
					Damage *= Data_Weapon->GetLocationDamageModifier(FireMode, HitResult.BoneName);

					// Damage Falloff
					if (Data_Projectile->CanDamageFalloff())
						Damage *= Data_Projectile->GetDamageFalloff(HitResult.Distance);
					// Damage Radial
					else
					if (Data_Projectile->CanDamageRadial())
						Damage = Data_Projectile->GetDamageRadial(HitResult.Location, HitPawn->GetActorLocation());

					HitPawn->ApplyDamage(Event);
				}
			}
			// World
			else
			{
			}

			// Play Impact FX / Sound
			UPhysicalMaterial* PhysicalMaterial = HitResult.PhysMaterial.IsValid() ? HitResult.PhysMaterial.Get() : nullptr;

			if (PhysicalMaterial)
			{
				// FX
				Data_Projectile->GetData_Impact()->PlayImpactFX(GetWorld(), PhysicalMaterial->SurfaceType, nullptr, HitResult.Location, HitResult.ImpactNormal);
				// Sound
				Data_Projectile->GetData_Impact()->PlayImpactSound(GetWorld(), PhysicalMaterial->SurfaceType, nullptr, HitResult.Location);
			}

			//float TimeUntilHit = HitResult.Distance / Data_Projectile->InitialSpeed;

			//if (DoesHitscanSimulateProjectileDuration.Get(FireMode))
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
			Event->Reset();
		}
	}
}

#pragma endregion Hitscan

UObject* ACsWeapon_DEPRECATED::GetMuzzleFlashParent(const ECsViewType& ViewType) { return nullptr; }

FVector ACsWeapon_DEPRECATED::GetMuzzleLocation(const ECsViewType& ViewType, const FECsWeaponFireMode& FireMode)
{
	return FVector::ZeroVector;
}

void ACsWeapon_DEPRECATED::PlayMuzzleFlash(const FECsWeaponFireMode& FireMode)
{
	/*
	AICsManager_FX* Manager_FX = nullptr;

#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
	{
		if (UCsAnimInstance* AnimInstance = GetMyOwner<UCsAnimInstance>())
			Manager_FX = AnimInstance->GetManager_FX();
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		ACsGameState_DEPRECATED* GameState = GetWorld()->GetGameState<ACsGameState_DEPRECATED>();
		Manager_FX				 = GameState->Manager_FX;
	}

	UCsData_ProjectileWeapon_DEPRECATED* Data_Weapon = GetMyData_Weapon<UCsData_ProjectileWeapon_DEPRECATED>();
	const ECsViewType ViewType			  = GetCurrentViewType();
	FCsFxElement* FX					  = Data_Weapon->GetMuzzleFX(ViewType, FireMode, CurrentProjectilePerShotIndex.Get(FireMode));

	if (!FX->Get())
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("ACsWeapon_DEPRECATED::PlayMuzzleFlash: Attempting to Play a NULL ParticleSystem."));
		return;
	}

	FCsFxPayload* Payload = Manager_FX->AllocatePayload();
	Payload->Set(FX);
	Payload->Owner = GetMyPawn();
	Payload->Parent = GetMuzzleFlashParent(ViewType);

	Manager_FX->Play(Payload);
	*/
}

#pragma endregion Firing

// Reload
#pragma region

void ACsWeapon_DEPRECATED::OnChange_bReloading(const bool &Value)
{
	OnChange_bReloading_Event.Broadcast(WeaponSlot, Value);
#if WITH_EDITOR
	OnChange_bReloading_ScriptEvent.Broadcast(WeaponSlot, Value);
#endif // #if WITH_EDITOR
}

float ACsWeapon_DEPRECATED::GetReloadTime(const int32 &Index) { return ReloadTime.Get(Index); }
float ACsWeapon_DEPRECATED::GetRechargeSecondsPerAmmo(const int32 &Index) { return RechargeSecondsPerAmmo.Get(Index); }
float ACsWeapon_DEPRECATED::GetRechargeStartupDelay(const int32 &Index) { return RechargeStartupDelay.Get(Index); }

bool ACsWeapon_DEPRECATED::CanReload()
{
	if (CurrentState == ReloadingState || bReloading)
		return false;

	// Check Ammo
	const int32 AmmoReserve = GetAmmoReserve(CS_WEAPON_DATA_VALUE, PrimaryFireMode, false);

	if (AmmoReserve == CS_EMPTY)
		return false;
	return true;
}

bool ACsWeapon_DEPRECATED::CanAutoReload(const FECsWeaponFireMode& FireMode)
{
	if (!CanReload())
		return false;

	// Check time since last Fire
	const float TimeSeconds = GetWorld()->GetTimeSeconds();

	if (FireMode == EMCsWeaponFireMode::Get().GetMAX())
	{
		if (TimeSeconds - Fire_StartTime.Min() < FMath::Max(TimeBetweenShots.Max(), TimeBetweenAutoShots.Max()))
			return false;
	}
	else
	{
		const bool Pass_AutoShots = IsFullAuto[FireMode] && TimeSeconds - Fire_StartTime[FireMode] > TimeBetweenAutoShots.GetEX(FireMode);
		const bool Pass_Shots	  = TimeSeconds - Fire_StartTime[FireMode] > TimeBetweenShots.GetEX(FireMode);

		if (!Pass_AutoShots && !Pass_Shots)
			return false;
	}
	return true;
}

bool ACsWeapon_DEPRECATED::ShouldAutoReload(const FECsWeaponFireMode& FireMode)
{
	if (CurrentAmmo > CS_EMPTY)
		return false;
	return CanAutoReload(FireMode);
}

void ACsWeapon_DEPRECATED::Reload()
{
	if (!CanReload())
		return;

	// Idle
	if (CurrentState == IdleState)
	{
		if (CurrentAmmo == MaxAmmo.GetEX(CS_WEAPON_DATA_VALUE))
			return;
	}
	// Firing
	if (CurrentState == FiringState)
	{
		UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(GetGameInstance());

		const int32& Count = EMCsWeaponFireMode::Get().Num();

		for (int32 I = 0; I < Count; ++I)
		{
			StopChargeFire(EMCsWeaponFireMode::Get().GetEnumAt(I));
		}

		Scheduler->BroadcastMessage(NCsUpdateGroup::GameState, ECsCoroutineMessage::Abort, NCsWeaponCached::Name::Stop_FireWeapon_Internal, this);

		for (int32 I = 0; I < Count; ++I)
		{
			StopAnimation(EMCsWeaponFireMode::Get().GetEnumAt(I), FireAnim);
		}
	}

	ReloadStartTime = GetWorld()->TimeSeconds;
	bReloadingHandle = true;

	PlayAnimation_Reload();

	LastState    = CurrentState;
	CurrentState = ReloadingState;
}

#pragma endregion Reload