// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Weapon/CsWeapon.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"
#include "Coroutine/CsCoroutineScheduler.h"

#include "Animation/CsAnimInstance.h"

// Data
#include "Data/CsData_ProjectileImpact.h"

// Managers
#include "Managers/FX/CsManager_FX.h"
#include "Managers/Projectile/CsManager_Projectile.h"
#include "Managers/Projectile/CsProjectile.h"
#include "Managers/Damage/CsManager_Damage.h"

#include "Game/CsGameInstance.h"
#include "Game/CsGameState.h"
#include "Player/CsPlayerState.h"
#include "Pawn/CsPawn.h"

#include "Managers/InteractiveActor/CsDamageableActor.h"

// Cache
#pragma region

namespace ECsWeaponCachedName
{
	namespace Name
	{
		// Functions
		const FName PlayAnimation_Reload_Internal = FName("ACsWeapon::PlayAnimation_Reload_Internal");
		const FName StartChargeFire_Internal = FName("ACsWeapon::StartChargeFire_Internal");
		const FName FireWeapon_Internal = FName("ACsWeapon::FireWeapon_Internal");
		const FName DrawFireProjectile_Internal = FName("ACsWeapon::DrawFireProjectile_Internal");
		// Stop Messages
		const FName Stop_PlayAnimation_Reload_Internal = FName("Stop PlayAnimation_Reload_Internal");
		const FName Stop_StartChargeFire_Internal = FName("Stop StartCharageFire_Internal");
		const FName Stop_FireWeapon_Internal = FName("Stop FireWeapon_Internal");
		const FName Stop_DrawFireProjectile_Internal = FName("Stop DrawFireProjectile_Internal");
	}
}

namespace ECsWeaponCachedString
{
	namespace Str
	{
		// Functions
		const FString PlayAnimation_Reload_Internal = TEXT("ACsWeapon::PlayAnimation_Reload_Internal");
		const FString StartChargeFire_Internal = TEXT("ACsWeapon::StartChargeFire_Internal");
		const FString FireWeapon_Internal = TEXT("ACsWeapon::FireWeapon_Internal");
		const FString DrawFireProjectile_Internal = TEXT("ACsWeapon::DrawFireProjectile_Internal");
	}
}

#pragma endregion Cache

// Enums
#pragma region

UENUM(BlueprintType)
namespace ECsWeaponRoutine
{
	enum Type
	{
		PlayAnimation_Reload_Internal		UMETA(DisplayName = "PlayAnimation_Reload_Internal"),
		StartChargeFire_Internal			UMETA(DisplayName = "StartChargeFire_Internal"),
		FireWeapon_Internal					UMETA(DisplayName = "FireWeapon_Internal"),
		ECsWeaponRoutine_MAX				UMETA(Hidden),
	};
}

namespace ECsWeaponRoutine
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString PlayAnimation_Reload_Internal = TCsString(TEXT("PlayAnimation_Reload_Internal"), TEXT("playanimation_reload_internal"), TEXT("play animation reload internal"));
		const TCsString StartChargeFire_Internal = TCsString(TEXT("StartChargeFire_Internal"), TEXT("startchargefire_internal"), TEXT("start charge fire internal"));
		const TCsString FireWeapon_Internal = TCsString(TEXT("FireWeapon_Internal"), TEXT("fireweapon_internal"), TEXT("fire weapon internal"));
	}

	inline FString ToString(const Type &EType)
	{
		if (EType == Type::PlayAnimation_Reload_Internal) { return Str::PlayAnimation_Reload_Internal.Value; }
		if (EType == Type::StartChargeFire_Internal) { return Str::StartChargeFire_Internal.Value; }
		if (EType == Type::FireWeapon_Internal) { return Str::FireWeapon_Internal.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	inline Type ToType(const FString &String)
	{
		if (String == Str::PlayAnimation_Reload_Internal) { return Type::PlayAnimation_Reload_Internal; }
		if (String == Str::StartChargeFire_Internal) { return Type::StartChargeFire_Internal; }
		if (String == Str::FireWeapon_Internal) { return Type::FireWeapon_Internal; }
		return Type::ECsWeaponRoutine_MAX;
	}
}

#define ECS_WEAPON_ROUTINE_MAX (uint8)ECsWeaponRoutine::ECsWeaponRoutine_MAX
typedef ECsWeaponRoutine::Type TCsWeaponRoutine;

#pragma endregion Enums

ACsWeapon::ACsWeapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	//CS_DEFINE_WEAPON_FIRE_MODE

	//CurrentState = ECsWeaponState::Idle;
	//LastState	 = CurrentState;

	//IdleState = ECsWeaponState::Idle;

	//FiringState = ECsWeaponState::Firing;
	//FireAnim = ECsWeaponAnim::Fire;
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

void ACsWeapon::PostActorCreated()
{
	Super::PostActorCreated();

	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(GetGameInstance());
	UniqueObjectId				  = GameInstance->GetUniqueObjectId();
}

// Members
#pragma region

void ACsWeapon::InitMultiValueMembers()
{
	const uint8 SIZE = (uint8)WeaponFireMode_MAX;

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

void ACsWeapon::SetMemberValue_bool(const uint8 &Member, const int32 &Index, const bool &Value)
{
	SetMemberValue_bool((TCsWeaponCacheMultiValueMember)Member, Index, Value);
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

void ACsWeapon::SetMemberValue_uint8(const uint8 &Member, const int32 &Index, const uint8 &Value)
{
	SetMemberValue_uint8((TCsWeaponCacheMultiValueMember)Member, Index, Value);
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


void ACsWeapon::SetMemberValue_int32(const uint8 &Member, const int32 &Index, const int32 &Value)
{
	SetMemberValue_int32((TCsWeaponCacheMultiValueMember)Member, Index, Value);
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

void ACsWeapon::SetMemberValue_float(const uint8 &Member, const int32 &Index, const float &Value)
{
	SetMemberValue_float((TCsWeaponCacheMultiValueMember)Member, Index, Value);
}

void ACsWeapon::SetMemberValue_Script_float(const FString &MemberName, const int32 &Index, const float &Value)
{
#if WITH_EDITOR
	SetMemberValue_float(ECsWeaponCacheMultiValueMember::ToType(MemberName), Index, Value);
#endif // #if WITH_EDITOR
}

void ACsWeapon::SetMultiValueMembers()
{
	ACsData_ProjectileWeapon* Data = GetMyData_Weapon<ACsData_ProjectileWeapon>();

	// MaxAmmo
	MaxAmmo.ResetValues();
	int32 iVal = Data->GetMaxAmmo();
	MaxAmmo.Set(iVal);
	MaxAmmo.Set(CS_WEAPON_DATA_VALUE, Data->GetMaxAmmoAddr());

	CurrentAmmo = MaxAmmo.Get(CS_WEAPON_DATA_VALUE);

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
		if (Member == ECsWeaponCacheMultiValueMember::IsHitscan) { return IsHitscan.Get(Index); }
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

bool ACsWeapon::GetMemberValue_bool(const uint8 &Member, const int32 &Index)
{
	return GetMemberValue_bool((TCsWeaponCacheMultiValueMember)Member, Index);
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
	// Firing
	{
		if (Member == ECsWeaponCacheMultiValueMember::ProjectilesPerShot) { return ProjectilesPerShot.GetEX((TCsWeaponFireMode)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::CurrentProjectilePerShotIndex) { return CurrentProjectilePerShotIndex.Get(Index); }
	}
	return 0;
}

uint8 ACsWeapon::GetMemberValue_uint8(const uint8 &Member, const int32 &Index)
{
	return GetMemberValue_uint8((TCsWeaponCacheMultiValueMember)Member, Index);
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
		if (Member == ECsWeaponCacheMultiValueMember::MaxAmmo) { return MaxAmmo.GetEX((TCsWeaponFireMode)Index); }
		// Hitscan
		if (Member == ECsWeaponCacheMultiValueMember::ObstaclePenetrations) { return ObstaclePenetrations.GetEX((TCsWeaponFireMode)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::PawnPenetrations) { return PawnPenetrations.GetEX((TCsWeaponFireMode)Index); }
	}
	return 0;
}

int32 ACsWeapon::GetMemberValue_int32(const uint8 &Member, const int32 &Index)
{
	return GetMemberValue_int32((TCsWeaponCacheMultiValueMember)Member, Index);
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
		if (Member == ECsWeaponCacheMultiValueMember::TimeBetweenProjectilesPerShot) { return TimeBetweenProjectilesPerShot.GetEX((TCsWeaponFireMode)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::TimeBetweenShots) { return TimeBetweenShots.GetEX((TCsWeaponFireMode)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::TimeBetweenAutoShots) { return TimeBetweenAutoShots.GetEX((TCsWeaponFireMode)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::IsFirePressed_StartTime) { return IsFirePressed_StartTime.Get(Index); }
		if (Member == ECsWeaponCacheMultiValueMember::IsFireReleased_StartTime) { return IsFireReleased_StartTime.Get(Index); }
		// Charge
		if (Member == ECsWeaponCacheMultiValueMember::MaxChargeFireTime) { return MaxChargeFireTime.GetEX((TCsWeaponFireMode)Index); }
		// Spread
		if (Member == ECsWeaponCacheMultiValueMember::MinSpread) { return MinSpread.GetEX((TCsWeaponFireMode)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::MaxSpread) { return MaxSpread.GetEX((TCsWeaponFireMode)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::SpreadAddedPerShot) { return SpreadAddedPerShot.GetEX((TCsWeaponFireMode)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::SpreadRecoveryRate) { return SpreadRecoveryRate.GetEX((TCsWeaponFireMode)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::FiringSpreadRecoveryDelay) { return FiringSpreadRecoveryDelay.GetEX((TCsWeaponFireMode)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::CurrentBaseSpread) { return CurrentBaseSpread.Get(Index); }
		if (Member == ECsWeaponCacheMultiValueMember::CurrentSpread) { return CurrentSpread.Get(Index); }
		if (Member == ECsWeaponCacheMultiValueMember::LastSpreadFireTime) { return LastSpreadFireTime.Get(Index); }
	}
	// Reload
	{
		if (Member == ECsWeaponCacheMultiValueMember::ReloadTime) { return ReloadTime.GetEX((TCsWeaponFireMode)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::RechargeSecondsPerAmmo) { return RechargeSecondsPerAmmo.GetEX((TCsWeaponFireMode)Index); }
		if (Member == ECsWeaponCacheMultiValueMember::RechargeStartupDelay) { return RechargeStartupDelay.GetEX((TCsWeaponFireMode)Index); }
	}
	return 0.0f;
}

float ACsWeapon::GetMemberValue_float(const uint8 &Member, const int32 &Index)
{
	return GetMemberValue_float((TCsWeaponCacheMultiValueMember)Member, Index);
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

ACsData_Projectile* ACsWeapon::GetMyData_Projectile(const TCsWeaponFireMode &FireMode, const bool &IsCharged)
{
	return GetMyData_Weapon<ACsData_ProjectileWeapon>()->GetData_Projectile(FireMode, IsCharged);
}

#pragma endregion Data

// Routines
#pragma region

void ACsWeapon::AddRoutine(UObject* InWeapon, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<ACsWeapon>(InWeapon)->AddRoutine_Internal(Routine, Type);
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

void ACsWeapon::RemoveRoutine(UObject* InWeapon, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<ACsWeapon>(InWeapon)->RemoveRoutine_Internal(Routine, Type);
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

void ACsWeapon::ClearRoutines()
{
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();

	Scheduler->BroadcastMessage(ECsCoroutineSchedule::Tick, ECsCoroutineMessage::Stop, ECsWeaponCachedName::Name::Stop_PlayAnimation_Reload_Internal, this);
	Scheduler->BroadcastMessage(ECsCoroutineSchedule::Tick, ECsCoroutineMessage::Stop, ECsWeaponCachedName::Name::Stop_StartChargeFire_Internal, this);
	Scheduler->BroadcastMessage(ECsCoroutineSchedule::Tick, ECsCoroutineMessage::Stop, ECsWeaponCachedName::Name::Stop_FireWeapon_Internal, this);
	Scheduler->BroadcastMessage(ECsCoroutineSchedule::Tick, ECsCoroutineMessage::Stop, ECsWeaponCachedName::Name::Stop_DrawFireProjectile_Internal, this);
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

bool ACsWeapon::IsValidOwnerTypeInGame()
{ 
	return true; 
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
		if (UCsAnimInstance* AnimInstance = GetMyOwner<UCsAnimInstance>())
			return AnimInstance->CurrentViewType;
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		if (ACsPawn* Pawn = GetMyPawn())
			return UCsCommon::IsLocalPawn(GetWorld(), Pawn) ? ECsViewType::FirstPerson : ECsViewType::ThirdPerson;
	}
	return ECsViewType::ECsViewType_MAX;
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
		for (uint8 I = 0; I < WEAPON_FIRE_MODE_MAX; ++I)
		{
			const TCsWeaponFireMode FireMode = (TCsWeaponFireMode)I;

			if (DoSpread.Get(I))
			{
				// Firing
				if (TimeSeconds - LastSpreadFireTime.Get(I) > FiringSpreadRecoveryDelay.Get(I))
				{
					CurrentBaseSpread.Set(CS_WEAPON_DATA_VALUE, FMath::Max(CurrentBaseSpread.Get(CS_WEAPON_DATA_VALUE) - (SpreadRecoveryRate.GetEX(FireMode) * DeltaSeconds), MinSpread.GetEX(FireMode)));
				}
				CurrentSpread.Set(CS_WEAPON_DATA_VALUE, FMath::Clamp(CurrentBaseSpread.Get(CS_WEAPON_DATA_VALUE), 0.f, MaxSpread.GetEX(FireMode)));
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
	const int32 maxAmmo			= MaxAmmo.GetEX(CS_WEAPON_DATA_VALUE);

	const float TimeSeconds = GetWorld()->GetTimeSeconds();

	// Recharge Ammo
	if (AllowRechargeAmmo.Get(CS_WEAPON_DATA_VALUE) && 
		IsRechargingAmmo &&
		!HasUnlimitedAmmo && 
		CurrentAmmo < maxAmmo)
	{
		if (TimeSeconds > NextRechargeAmmoTime)
		{
			IncrementCurrentAmmo(CS_WEAPON_DATA_VALUE);

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

		for (uint8 I = 0; I < WEAPON_FIRE_MODE_MAX; ++I)
		{
			const TCsWeaponFireMode FireMode = (TCsWeaponFireMode)I;

			const bool IsPressed = IsFirePressed.Get(FireMode);

			const bool Pass_AutoShots = IsPressed && IsFullAuto.Get(FireMode) && TimeSeconds - Fire_StartTime.Get(FireMode) > TimeBetweenAutoShots.GetEX(FireMode);
			const bool Pass_Shots	  = IsPressed && TimeSeconds - Fire_StartTime.Get(FireMode) > TimeBetweenShots.GetEX(FireMode);

			if (Pass_AutoShots || Pass_Shots)
			{
				Pass |= true;

				// If out of ammo, Reload
				if (CurrentAmmo == 0)
				{
					StopSound(FireMode, FireSound);

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
			ResetCurrentAmmo(CS_WEAPON_DATA_VALUE);

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
			ResetCurrentAmmo(CS_WEAPON_DATA_VALUE);
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

		for (uint8 I = 0; I < WEAPON_FIRE_MODE_MAX; ++I)
		{
			const TCsWeaponFireMode FireMode = (TCsWeaponFireMode)I;

			if ((IsFullAuto.Get(I) && CanFire_Auto(FireMode)) ||
				CanFire(FireMode))
			{
				Pass_Firing |= true;

				if (LoopFireSound.Get(I))
					PlaySound(FireMode, FireSound);

				if (LoopFireAnim.Get(I))
					PlayAnimation(FireMode, FireAnim);

				if (AllowRechargeAmmo.Get(CS_WEAPON_DATA_VALUE) && !AllowRechargeAmmoDuringFire.Get(CS_WEAPON_DATA_VALUE))
				{
					IsRechargingAmmo = false;
				}
				HandleState_Firing(FireMode);
			}
		}
	}
}

void ACsWeapon::HandleState_Firing(const TCsWeaponFireMode &FireMode)
{
	CurrentProjectilePerShotIndex.Set(FireMode, CurrentAmmo > ProjectilesPerShot.GetEX(FireMode) ? 0 : ProjectilesPerShot.GetEX(FireMode) - CurrentAmmo);

	const float TimeSeconds = GetWorld()->TimeSeconds;

	Fire_StartTime.Set(FireMode, TimeSeconds);
	LastState    = CurrentState;
	CurrentState = FiringState;

	FireWeapon(FireMode);

	if (!HasUnlimitedAmmo)
	{
		CurrentAmmo = FMath::Max(0, CurrentAmmo - ProjectilesPerShot.Get(FireMode));

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
}

bool ACsWeapon::CanFire(const TCsWeaponFireMode &FireMode)
{
	const float TimeSeconds = GetWorld()->GetTimeSeconds();

	const bool IsBot			  = false;// Cast<AShooterBot>(MyPawn) != nullptr;
	const bool AllowFire		  = !DoingEquipTransition && IsEquipped && TimeSeconds - Fire_StartTime.Get(FireMode) > TimeBetweenShots.GetEX(FireMode);
	const bool Pass_IsFirePressed = IsFirePressed.Get(FireMode) && !DoFireOnRelease.Get(FireMode) && (IsFullAuto.Get(FireMode) || (!Last_IsFirePressed.Get(FireMode) && IsFirePressed.Get(FireMode)) || IsBot) && AllowFire;
	const bool Pass_FireOnRelease = DoFireOnRelease.Get(FireMode) && ((Last_IsFirePressed.Get(FireMode) && !IsFirePressed.Get(FireMode))) && AllowFire;
	const bool Pass_Ammo		  = CurrentAmmo > 0 || HasUnlimitedAmmo;

	return (Pass_IsFirePressed || Pass_FireOnRelease) && Pass_Ammo && !IsReloading;
}

bool ACsWeapon::CanFire_Auto(const TCsWeaponFireMode &FireMode)
{
	const float TimeSeconds = GetWorld()->GetTimeSeconds();

	const bool IsBot			  = false;// Cast<AShooterBot>(MyPawn) != nullptr;
	const bool AllowFire		  = !DoingEquipTransition && IsEquipped && TimeSeconds - Fire_StartTime.Get(FireMode) > TimeBetweenAutoShots.GetEX(FireMode);
	const bool Pass_IsFirePressed = IsFirePressed.Get(FireMode) && !DoFireOnRelease.Get(FireMode) && (IsFullAuto.Get(FireMode) || (!Last_IsFirePressed.Get(FireMode) && IsFirePressed.Get(FireMode)) || IsBot) && AllowFire;
	const bool Pass_FireOnRelease = DoFireOnRelease.Get(FireMode) && ((Last_IsFirePressed.Get(FireMode) && !IsFirePressed.Get(FireMode))) && AllowFire;
	const bool Pass_Ammo		  = CurrentAmmo > 0 || HasUnlimitedAmmo;

	return (Pass_IsFirePressed || Pass_FireOnRelease) && Pass_Ammo && !IsReloading;
}

void ACsWeapon::Enable()
{
	ResetCurrentAmmo(CS_WEAPON_DATA_VALUE);
}

void ACsWeapon::Disable()
{
	if (CurrentState == FiringState || GetSound(FireSound))
	{
		for (uint8 I = 0; I < WEAPON_FIRE_MODE_MAX; ++I)
		{
			StopSound((TCsWeaponFireMode)I, FireSound);
		}
	}

	LastState    = CurrentState;
	CurrentState = IdleState;

	for (uint8 I = 0; I < WEAPON_FIRE_MODE_MAX; ++I)
	{
		IsFirePressed.Set(I, false);
		Last_IsFirePressed.Set(I, false);
	}

	PerformingChargeFire = false;

	if (GetMyData_Weapon())
	{
		for (uint8 I = 0; I < WEAPON_FIRE_MODE_MAX; ++I)
		{
			if (LoopFireAnim.Get(I))
				StopAnimation((TCsWeaponFireMode)I, FireAnim);
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

void ACsWeapon::PlayAnimation(const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/)
{
}

void ACsWeapon::PlayAnimation_Reload()
{
	if (PlayAnimation_Reload_Internal_Routine && PlayAnimation_Reload_Internal_Routine->IsValid())
		PlayAnimation_Reload_Internal_Routine->End(ECsCoroutineEndReason::UniqueInstance);

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &ACsWeapon::PlayAnimation_Reload_Internal;
	Payload->Actor			= this;
	Payload->Stop			= &ACsWeapon::PlayAnimation_Reload_StopCondition;
	Payload->Add			= &ACsWeapon::AddRoutine;
	Payload->Remove			= &ACsWeapon::RemoveRoutine;
	Payload->Type			= (uint8)ECsWeaponRoutine::PlayAnimation_Reload_Internal;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsWeaponCachedName::Name::PlayAnimation_Reload_Internal;
	Payload->NameAsString	= ECsWeaponCachedString::Str::PlayAnimation_Reload_Internal;
	

	FCsRoutine* R = Scheduler->Allocate(Payload);
	R->timers[0]  = GetWorld()->TimeSeconds;
	R->ints[0]    = 0;
	R->floats[0]  = GetAnimationLength(WeaponFireMode_MAX, ReloadAnim);

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

	r->AddMessage(ECsCoroutineMessage::Stop, ECsWeaponCachedName::Name::Stop_PlayAnimation_Reload_Internal);

	mw->PlayAnimation(mw->WeaponFireMode_MAX, ReloadAnim, 0);

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
			r->End(ECsCoroutineEndReason::StopCondition);
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		if (!mw)
			r->End(ECsCoroutineEndReason::StopCondition);
	}
}

float ACsWeapon::GetAnimationLength(const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/)
{
	return 0.0f;
}

void ACsWeapon::StopAnimation(const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/)
{
}

#pragma endregion Animation

// Sound
#pragma region

UObject* ACsWeapon::GetSoundParent() { return nullptr; }
ACsSound* ACsWeapon::GetSound(const TCsWeaponSound &SoundType){ return nullptr; }

void ACsWeapon::PlaySound(const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType)
{
	ACsData_ProjectileWeapon* Data	= GetMyData_Weapon<ACsData_ProjectileWeapon>();
	const TCsViewType ViewType		= GetCurrentViewType();

#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		Data->PlaySound(GetWorld(), ViewType, FireMode, SoundType, GetMyPawn(), GetSoundParent());
	}
}

void ACsWeapon::StopSound(const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType)
{
	ACsData_ProjectileWeapon* Data  = GetMyData_Weapon<ACsData_ProjectileWeapon>();
	const TCsViewType ViewType		= GetCurrentViewType();

#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		Data->StopSound(GetWorld(), ViewType, FireMode, SoundType, GetMyPawn(), GetSoundParent());
	}
}

#pragma endregion Sound

// Equip / UnEquip
#pragma region

bool ACsWeapon::CanUnEquip()
{
	if (!IsEquipped)
		return false;
	if (DoingEquipTransition)
		return false;

	for (uint8 I = 0; I < WEAPON_FIRE_MODE_MAX; ++I)
	{
		if (CurrentProjectilePerShotIndex.Get(I) < ProjectilesPerShot.Get(I) - 1)
			return false;
	}
	return true;
}

#pragma endregion Equip / UnEquip

// Firing
#pragma region

int32 ACsWeapon::GetMaxAmmo(const int32 &Index) { return MaxAmmo.Get(Index); }
void ACsWeapon::IncrementCurrentAmmo(const int32 &Index)
{
	CurrentAmmo++;
	CurrentAmmo = FMath::Min(CurrentAmmo, GetMaxAmmo(Index));
}
void ACsWeapon::ResetCurrentAmmo(const int32 &Index) { CurrentAmmo = GetMaxAmmo(Index); }
uint8 ACsWeapon::GetProjectilesPerShot(const TCsWeaponFireMode &FireMode) { return ProjectilesPerShot.Get(FireMode); }
float ACsWeapon::GetTimeBetweenProjectilesPerShot(const TCsWeaponFireMode &FireMode) { return TimeBetweenProjectilesPerShot.Get(FireMode); }
float ACsWeapon::GetTimeBetweenShots(const TCsWeaponFireMode &FireMode) { return TimeBetweenShots.Get(FireMode); }
float ACsWeapon::GetTimeBetweenAutoShots(const TCsWeaponFireMode &FireMode) { return TimeBetweenAutoShots.Get(FireMode); }

void ACsWeapon::SetIsFirePressed(const TCsWeaponFireMode &FireMode, const bool &Value, const bool &DoOnTick)
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

float ACsWeapon::GetMaxChargeFireTime(const TCsWeaponFireMode &FireMode) { return MaxChargeFireTime.Get(FireMode); }

void ACsWeapon::HandleChargeFire()
{
	if (PerformingChargeFire)
		return;
	
	for (uint8 I = 0; I < WEAPON_FIRE_MODE_MAX; ++I)
	{
		if (AllowChargeFire.Get(I) &&
			IsFirePressed.Get(I))
		{
			StartChargeFire((TCsWeaponFireMode)I);
			return;
		}
	}
}

void ACsWeapon::StartChargeFire(const TCsWeaponFireMode &FireMode)
{
	PerformingChargeFire = true;
	ChargeFire_StartTime = GetWorld()->TimeSeconds;

	if (StartChargeFire_Internal_Routine && StartChargeFire_Internal_Routine->IsValid())
		StartChargeFire_Internal_Routine->End(ECsCoroutineEndReason::UniqueInstance);

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &ACsWeapon::StartChargeFire_Internal;
	Payload->Actor			= this;
	Payload->Stop			= &ACsWeapon::StartChargeFire_StopCondition;
	Payload->Add			= &ACsWeapon::AddRoutine;
	Payload->Remove			= &ACsWeapon::RemoveRoutine;
	Payload->Type			= (uint8)ECsWeaponRoutine::StartChargeFire_Internal;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsWeaponCachedName::Name::StartChargeFire_Internal;
	Payload->NameAsString	= ECsWeaponCachedString::Str::StartChargeFire_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);
	R->timers[0]  = GetWorld()->GetTimeSeconds();
	R->ints[0]	  = (uint8)FireMode;

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

	const TCsWeaponFireMode FireMode = (TCsWeaponFireMode)r->ints[0];

	const float StartToLoopBlendTime = 0.1f;

	CS_COROUTINE_BEGIN(r);

	r->AddMessage(ECsCoroutineMessage::Stop, ECsWeaponCachedName::Name::Stop_StartChargeFire_Internal);

	// ChargeFireStart
	mw->PlayAnimation(FireMode, mw->ChargeFireStartAnim);

	r->timers[0] = CurrentTime;
	StartTime = CurrentTime;

	r->floats[0] = mw->GetAnimationLength(FireMode, mw->ChargeFireStartAnim);
	WaitTime = r->floats[0];

	CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - StartTime >= FMath::Max(WaitTime - StartToLoopBlendTime, 0.0f));

	// ChargeFireLoop
	mw->PlayAnimation(FireMode, mw->ChargeFireLoopAnim);

	CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - r->startTime >= FireStartLoopTime);

	CS_COROUTINE_END(r);
}

void ACsWeapon::StartChargeFire_StopCondition(struct FCsRoutine* r)
{
	ACsWeapon* mw = Cast<ACsWeapon>(r->GetActor());

	const TCsWeaponFireMode FireMode = (TCsWeaponFireMode)r->ints[0];

#if WITH_EDITOR 
	// In Editor Preview Window
	if (mw && UCsCommon::IsPlayInEditorPreview(mw->GetWorld()))
	{
		if (!mw->GetMyOwner())
		{
			mw->StopAnimation(FireMode, mw->ChargeFireStartAnim);
			mw->StopAnimation(FireMode, mw->ChargeFireLoopAnim);
			r->End(ECsCoroutineEndReason::StopMessage);
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
		r->End(ECsCoroutineEndReason::StopCondition);
	}
}

float ACsWeapon::GetChargeFireHeldTime()
{
	return GetWorld()->TimeSeconds - ChargeFire_StartTime;
}

float ACsWeapon::GetChargeFireHeldPercent(const TCsWeaponFireMode &FireMode)
{
	return FMath::Clamp(GetChargeFireHeldTime(), 0.0f, MaxChargeFireTime.GetEX(FireMode) / MaxChargeFireTime.GetEX(FireMode));
}

float ACsWeapon::GetCurrentChargeFireHeldTime()
{
	return PerformingChargeFire ? GetWorld()->TimeSeconds - ChargeFire_StartTime : 0.0f;
}

float ACsWeapon::GetCurrentChargeFireHeldPercent(const TCsWeaponFireMode &FireMode)
{
	return PerformingChargeFire ? FMath::Clamp(GetChargeFireHeldTime(), 0.0f, MaxChargeFireTime.GetEX(FireMode) / MaxChargeFireTime.GetEX(FireMode)) : 0.0f;
}

void ACsWeapon::StopChargeFire(const TCsWeaponFireMode &FireMode)
{
	if (!AllowChargeFire.Get(FireMode))
		return;

	PerformingChargeFire = false;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();

	Scheduler->BroadcastMessage(ECsCoroutineSchedule::Tick, ECsCoroutineMessage::Stop, ECsWeaponCachedName::Name::Stop_StartChargeFire_Internal, this);

	if (StartChargeFire_Internal_Routine && StartChargeFire_Internal_Routine->IsValid())
		StartChargeFire_Internal_Routine->End(ECsCoroutineEndReason::UniqueInstance);

	StopAnimation(FireMode, ChargeFireStartAnim);
	StopAnimation(FireMode, ChargeFireLoopAnim);
}

#pragma endregion Charge

	// Spread
#pragma region

float ACsWeapon::GetMinSpread(const TCsWeaponFireMode &FireMode) { return MinSpread.Get(FireMode); }
float ACsWeapon::GetMaxSpread(const TCsWeaponFireMode &FireMode) { return MaxSpread.Get(FireMode); }
float ACsWeapon::GetSpreadAddedPerShot(const TCsWeaponFireMode &FireMode) { return SpreadAddedPerShot.Get(FireMode); }
float ACsWeapon::GetSpreadRecoveryRate(const TCsWeaponFireMode &FireMode) { return SpreadRecoveryRate.Get(FireMode); }
float ACsWeapon::GetFiringSpreadRecoveryDelay(const TCsWeaponFireMode &FireMode) { return FiringSpreadRecoveryDelay.Get(FireMode); }
float ACsWeapon::GetMovingSpreadBonus(const TCsWeaponFireMode &FireMode) { return MovingSpreadBonus.Get(FireMode); }

#pragma endregion Spread

FVector ACsWeapon::GetFireWeaponStartLocation(const TCsWeaponFireMode &FireMode)
{
	return FVector::ZeroVector;
}

FVector ACsWeapon::GetFireWeaponStartDirection(const TCsWeaponFireMode &FireMode)
{
	return FVector::ZeroVector;
}

FCsProjectileFireCache* ACsWeapon::AllocateProjectileFireCache(const TCsWeaponFireMode &FireMode)
{
	const uint8 Count = CS_PROJECTILE_FIRE_CACHE_POOL_SIZE;
	uint8 PoolIndex	  = 0;

	for (uint8 I = 0; I < Count; ++I)
	{
		FCsProjectileFireCache* Cache = &ProjectileFireCaches[ProjectileFireCachePoolIndex];

		if (!Cache->IsAllocated)
		{
			Cache->IsAllocated = true;

			Cache->Time		= GetWorld()->GetTimeSeconds();
			Cache->RealTime = GetWorld()->GetRealTimeSeconds();
			Cache->Frame	= UCsCommon::GetCurrentFrame(GetWorld());

			Cache->Location		 = GetFireWeaponStartLocation(FireMode);
			Cache->Direction	 = GetFireWeaponStartDirection(FireMode);
			Cache->ChargePercent = GetCurrentChargeFireHeldPercent(FireMode);

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
		ProjectileFireCachePoolIndex = (ProjectileFireCachePoolIndex + I) % Count;
	}

	UE_LOG(LogCs, Warning, TEXT("ACsWeapon::AllocateProjectileFireCache: Warning. Pool is exhausted. Using Oldest Active Projectile Fire Cache."));
	return nullptr;
}

void ACsWeapon::FireWeapon(const TCsWeaponFireMode &FireMode)
{
#if WITH_EDITOR 
	if (Override_FireWeapon_ScriptEvent.IsBound())
	{
		if (CsCVarLogOverrideFunctions->GetInt() == CS_CVAR_DISPLAY)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsWeapon::FireWeapon (%s): Using Override Function."), *GetName());
		}
		Override_FireWeapon_ScriptEvent.Broadcast(WeaponIndex, FireMode);
		return;
	}
#endif // #if WITH_EDITOR

	if (FireWeapon_Internal_Routine && FireWeapon_Internal_Routine->IsValid())
		FireWeapon_Internal_Routine->End(ECsCoroutineEndReason::UniqueInstance);
	
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &ACsWeapon::FireWeapon_Internal;
	Payload->Actor			= this;
	Payload->Stop			= &ACsWeapon::FireWeapon_StopCondition;
	Payload->Add			= &ACsWeapon::AddRoutine;
	Payload->Remove			= &ACsWeapon::RemoveRoutine;
	Payload->Type			= (uint8)ECsWeaponRoutine::FireWeapon_Internal;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsWeaponCachedName::Name::FireWeapon_Internal;
	Payload->NameAsString	= ECsWeaponCachedString::Str::FireWeapon_Internal;

	FCsRoutine* R   = Scheduler->Allocate(Payload);
	R->timers[0]    = GetWorld()->GetTimeSeconds();
	R->ints[0]	    = (uint8)FireMode;

	Scheduler->StartRoutine(Schedule, R);
}

PT_THREAD(ACsWeapon::FireWeapon_Internal(struct FCsRoutine* r))
{
	ACsWeapon* mw			 = Cast<ACsWeapon>(r->GetActor());
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w				 = mw->GetWorld();

	const TCsWeaponFireMode FireMode = (TCsWeaponFireMode)r->ints[0];

	const float CurrentTime = w->GetTimeSeconds();
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

	r->AddMessage(ECsCoroutineMessage::Stop, ECsWeaponCachedName::Name::Stop_FireWeapon_Internal);

	mw->StopChargeFire(FireMode);

	do
	{
		{
			// Set the StartTime
			r->timers[0] = CurrentTime;
			StartTime    = CurrentTime;

			// Play Fire Sound
			if (!mw->LoopFireSound.Get(FireMode))
				mw->PlaySound(FireMode, mw->FireSound);
			// Play Fire Animation
			if (!mw->LoopFireAnim.Get(FireMode))
				mw->PlayAnimation(FireMode, mw->FireAnim);

#if WITH_EDITOR 
			// In Editor Preview Window
			if (UCsCommon::IsPlayInEditorPreview(w))
			{
			}
			// In Game
			else
#endif // #if WITH_EDITOR
			{
				FCsProjectileFireCache* Cache = mw->AllocateProjectileFireCache(FireMode);
				
				if (mw->IsHitscan.Get(FireMode))
					mw->FireHitscan(FireMode, Cache);
				else
					mw->FireProjectile(FireMode, Cache);
				Cache->Reset();
			}

			mw->PlayMuzzleFlash(FireMode);
			
			mw->CurrentProjectilePerShotIndex.Add(FireMode, 1);
		}

		if (mw->CurrentProjectilePerShotIndex.Get(FireMode) < mw->ProjectilesPerShot.Get(FireMode))
		{
			CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - StartTime >= mw->TimeBetweenProjectilesPerShot.Get(FireMode));
		}
	} while (mw->CurrentProjectilePerShotIndex.Get(FireMode) < mw->ProjectilesPerShot.Get(FireMode));

	mw->CurrentState = mw->IdleState;
	CS_COROUTINE_END(r);
}

void ACsWeapon::FireWeapon_StopCondition(struct FCsRoutine* r)
{
	ACsWeapon* mw				     = Cast<ACsWeapon>(r->GetActor());
	const TCsWeaponFireMode FireMode = (TCsWeaponFireMode)r->ints[0];

#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(mw->GetWorld()) &&
		mw)
	{
		if (!mw->GetMyOwner())
		{
			mw->StopAnimation(FireMode, mw->FireAnim);

			r->End(ECsCoroutineEndReason::StopCondition);
		}
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		if (mw &&
			!mw->GetMyOwner())
		{
			mw->StopAnimation(FireMode, mw->FireAnim);

			FCsProjectileFireCache* Cache = (FCsProjectileFireCache*)r->voidPointers[0];

			Cache->Reset();
			r->End(ECsCoroutineEndReason::StopCondition);
		}
	}
}

FVector ACsWeapon::GetOwnerRightVector()
{
	if (AActor* Actor = GetMyOwner<AActor>())
		return Actor->GetActorRightVector();
	if (USceneComponent* Component = GetMyOwner<USceneComponent>())
		return Component->GetRightVector();
	return FVector::RightVector;
}

FVector ACsWeapon::GetFireProjectileDestination()
{
	return FVector::ZeroVector;
}

void ACsWeapon::FireProjectile(const TCsWeaponFireMode &FireMode, FCsProjectileFireCache* Cache)
{
	const FVector RealStart   = Cache->Location;
	FVector RealDir			  = Cache->Direction;

	ACsData_ProjectileWeapon* Data_Weapon	= GetMyData_Weapon<ACsData_ProjectileWeapon>();
	ACsData_Projectile* Data_Projectile		= Data_Weapon->GetData_Projectile(FireMode, Cache->ChargePercent > 0.0f);
	const bool UseFakeProjectile			= Data_Weapon->UseFakeProjectile(FireMode);

	FVector RealEnd = RealStart;

	if (UseFakeProjectile)
	{
		RealEnd = GetFireProjectileDestination();
	}
	else
	{
		const float MaxRange = 30000.0f;
		RealEnd				 = RealStart + MaxRange * RealDir;
	}

	const TCsViewType ViewType = GetCurrentViewType();
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
		CurrentBaseSpread.Set(FireMode, FMath::Min(CurrentBaseSpread.Get(FireMode) + SpreadAddedPerShot.GetEX(FireMode), MaxSpread.GetEX(FireMode)));
		LastSpreadFireTime.Set(FireMode, GetWorld()->TimeSeconds);
	}
	FireProjectile_Internal(FireMode, Cache);

	// Update Cache

	ACsGameState* GameState					  = GetWorld()->GetGameState<ACsGameState>();
	ACsManager_Projectile* Manager_Projectile = GameState->Manager_Projectile;

	// Real
	Cache->Location				  = RealStart;
	Cache->Direction			  = RealDir;
	ACsProjectile* RealProjectile = Manager_Projectile->Fire(UseFakeProjectile ? ECsProjectileRelevance::RealInvisible : ECsProjectileRelevance::RealVisible, Data_Projectile, Cache, GetMyOwner(), this);
	
	const bool IsLocalPawn = UCsCommon::IsLocalPawn(GetWorld(), GetMyPawn());

	if ((CsCVarDrawLocalPlayerWeaponFireProjectile->GetInt() == CS_CVAR_DRAW &&
		 IsLocalPawn) ||
		CsCVarDrawWeaponFireProjectile->GetInt() == CS_CVAR_DRAW)
	{
		DrawFireProjectile(RealProjectile, RealStart, RealEnd);
	}

	// Fake
	if (UseFakeProjectile)
	{
		FCsProjectileFireCache* FakeCache = AllocateProjectileFireCache(FireMode);
		FakeCache->Location				  = FakeStart;
		FakeCache->Direction			  = FakeDir;
		ACsProjectile* FakeProjectile	  = Manager_Projectile->Fire(ECsProjectileRelevance::Fake, Data_Projectile, FakeCache, GetMyOwner(), this);

		RealProjectile->FakeProjectile = FakeProjectile;
		FakeCache->Reset();

		if ((CsCVarDrawLocalPlayerWeaponFireProjectile->GetInt() == CS_CVAR_DRAW &&
			IsLocalPawn) ||
			CsCVarDrawWeaponFireProjectile->GetInt() == CS_CVAR_DRAW)
		{
			DrawFireProjectile(FakeProjectile, FakeStart, RealEnd);
		}
	}
	Cache->Reset();
}

void ACsWeapon::FireProjectile_Internal(const TCsWeaponFireMode &FireMode, FCsProjectileFireCache* Cache) {}

void ACsWeapon::FireProjectile_Script(const uint8 &FireMode, FCsProjectileFireCache &Cache)
{
	FireProjectile((TCsWeaponFireMode)FireMode, &Cache);
}

void ACsWeapon::DrawFireProjectile(class ACsProjectile* Projectile, const FVector &Start, const FVector &End)
{
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload     = Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	Payload->Schedule			= Schedule;
	Payload->Function			= &ACsWeapon::DrawFireProjectile_Internal;
	Payload->Actor				= this;
	Payload->Object				= Projectile;
	Payload->Stop				= &ACsWeapon::FireWeapon_StopCondition;
	Payload->DoInit				= true;
	Payload->PerformFirstRun	= false;
	Payload->Name				= ECsWeaponCachedName::Name::DrawFireProjectile_Internal;
	Payload->NameAsString		= ECsWeaponCachedString::Str::DrawFireProjectile_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);
	R->timers[0] = GetWorld()->GetTimeSeconds();
	R->vectors[0] = Start;
	R->vectors[1] = End;

	Scheduler->StartRoutine(Schedule, R);
}

PT_THREAD(ACsWeapon::DrawFireProjectile_Internal(struct FCsRoutine* r))
{
	ACsProjectile* p		 = Cast<ACsProjectile>(r->GetRObject());
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w				 = p->GetWorld();

	const FVector Start		 = r->vectors[0];
	const FVector End		 = r->vectors[1];
	const float DeltaSeconds = r->deltaSeconds;

	CS_COROUTINE_BEGIN(r);

	r->AddMessage(ECsCoroutineMessage::Stop, ECsWeaponCachedName::Name::Stop_DrawFireProjectile_Internal);

	do
	{
		DrawDebugLine(w, Start, End, FColor::Red, false, DeltaSeconds + 0.005f, 0, 0.25f);

		CS_COROUTINE_YIELD(r);

	} while (p->Cache.IsAllocated);

	CS_COROUTINE_END(r);
}

	// Hitscan
#pragma region

int32 ACsWeapon::GetObstaclePenetractions(const TCsWeaponFireMode &FireMode) { return ObstaclePenetrations.Get(FireMode); }
int32 ACsWeapon::GetPawnPenetrations(const TCsWeaponFireMode &FireMode) { return PawnPenetrations.Get(FireMode); }

void ACsWeapon::GetFireHitscanIgnoreActors(TArray<AActor*> &OutActors)
{ 
	OutActors.Add(this);

	if (AActor* Actor = GetMyOwner<AActor>())
		OutActors.Add(Actor);
}

void ACsWeapon::FireHitscan(const TCsWeaponFireMode &FireMode, const FCsProjectileFireCache* Cache)
{
	//ACsPawn* Pawn					 = GetMyPawn();
	//ACsPlayerState* MyPlayerState	 = Cast<ACsPlayerState>(Pawn->PlayerState);
	ACsData_ProjectileWeapon* Data_Weapon	= GetMyData_Weapon<ACsData_ProjectileWeapon>();
	ACsData_Projectile* Data_Projectile		= Data_Weapon->GetData_Projectile(FireMode, Cache->ChargePercent > 0.0f);

	const ECollisionChannel ProjectileCollision = Data_Projectile->GetCollisionObjectType();

	const FVector Start		  = Cache->Location;
	const FVector Dir		  = Cache->Direction;
	const float MaxTraceRange = Data_Projectile->GetMaxRange();
	const FVector End		  = Start + MaxTraceRange * Dir;

	FCollisionQueryParams CollisionParams   = FCollisionQueryParams();
	CollisionParams.bReturnPhysicalMaterial = true;
	
	TArray<AActor*> IgnoredActors;
	GetFireHitscanIgnoreActors(IgnoredActors);
	CollisionParams.AddIgnoredActors(IgnoredActors);

	// See which Pawns we can hit and which we should ignore
	TArray<ACsPawn*> HittablePawns;
	
	const bool AllowInfinitePawnPenetrations	 = PawnPenetrations.Get(FireMode) < 0;
	const bool AllowInfiniteObstaclePenetrations = ObstaclePenetrations.Get(FireMode) < 0;

	int32 RecordedPawnPenetrations     = 0;
	int32 RecordedObstaclePenetrations = 0;
	bool HitFound					   = true;

	FHitResult HitResult;

	// Hit trace/ Hit simulation
	while ((AllowInfinitePawnPenetrations || RecordedPawnPenetrations <= PawnPenetrations.Get(FireMode)) &&
		   (AllowInfiniteObstaclePenetrations || RecordedObstaclePenetrations <= ObstaclePenetrations.Get(FireMode)) &&
		    HitFound)
	{
		HitFound = false;

		HitResult.Reset(0.0f, false);

		// Hitscan with cylinder
		if (DoesHitscanUseRadius.Get(FireMode))
		{
			// See if this line is close enough to hit any enemy characters
			const int32 HitPawnCount = HittablePawns.Num();

			for (int32 I = HitPawnCount - 1; I >= 0; --I)
			{
				/*
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
					HitFound				  = GetWorld()->LineTraceSingleByChannel(HitResult, Start, TargetPoint, ProjectileCollision, CollisionParams);
					HittablePawns.RemoveAt(I);
					break;
				}
				// Body is close enough to potential trace. Try tracing directly to the body
				else 
				if (BodyXYDistFromLine < CharacterRadius + ProjectileRadius && BodyZDistFromLine < CharacterHeight + ProjectileRadius)
				{
					const float TraceDist     = 1.5f * (BodyLocation - Start).Size();
					const FVector TargetPoint = BodyLocation + TraceDist * (BodyLocation - Start);
					HitFound				  = GetWorld()->LineTraceSingleByChannel(HitResult, Start, TargetPoint, ProjectileCollision, CollisionParams);
					HittablePawns.RemoveAt(I);
					break;
				}
				*/
			}
		}
		// Hit NOT Found and NO Hitscan with cylinder
		if (!HitFound || 
			!DoesHitscanUseRadius.Get(FireMode))
		{
			HitFound = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ProjectileCollision, CollisionParams);

			if ((CsCVarDrawLocalPlayerWeaponFireProjectile->GetInt() == CS_CVAR_DRAW &&
				UCsCommon::IsLocalPawn(GetWorld(), GetMyPawn())) ||
				CsCVarDrawWeaponFireProjectile->GetInt() == CS_CVAR_DRAW)
			{
				const float DrawTime = FMath::Max(TimeBetweenAutoShots.GetEX(FireMode), TimeBetweenShots.GetEX(FireMode));

				DrawDebugLine(GetWorld(), Start, HitFound ? HitResult.Location : End, FColor::Red, false, DrawTime, 0, 1.0f);
			}
		}
		// Hit IS Found. Check penetrations and modifiers
		if (HitFound)
		{
			ACsManager_Damage* Manager_Damage = ACsManager_Damage::Get(GetWorld());
			FCsDamageEvent* Event			  = Manager_Damage->Allocate();

			Event->Damage	  = Data_Projectile->GetDamage();
			Event->Instigator = GetMyOwner();
			Event->Causer	  = this;
			//Event->SetDamageType();
			//Event->SetHitType();
			Event->HitInfo = HitResult;

			ACsPawn* HitPawn = Cast<ACsPawn>(HitResult.Actor.Get());
			CollisionParams.AddIgnoredActor(HitResult.Actor.Get());
			
			//if (PawnToHit && UShooterStatics::IsOnSameTeam(GetWorld(), PawnToHit, MyPawn))
			//{
			//	continue;
			//}

			if (HitPawn)
				RecordedPawnPenetrations++;
			else
				RecordedObstaclePenetrations++;

			// Pawn
			if (HitPawn)
			{
				if (HitPawn->Role == ROLE_Authority)
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

UObject* ACsWeapon::GetMuzzleFlashParent(const TCsViewType &ViewType) { return nullptr; }

FVector ACsWeapon::GetMuzzleLocation(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode)
{
	return FVector::ZeroVector;
}

void ACsWeapon::PlayMuzzleFlash(const TCsWeaponFireMode &FireMode)
{
	ACsManager_FX* Manager_FX = nullptr;

#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		if (UCsAnimInstance* AnimInstance = GetMyOwner<UCsAnimInstance>())
			Manager_FX = AnimInstance->GetManager_FX();
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>();
		Manager_FX				 = GameState->Manager_FX;
	}

	ACsData_ProjectileWeapon* Data_Weapon = GetMyData_Weapon<ACsData_ProjectileWeapon>();
	const TCsViewType ViewType			  = GetCurrentViewType();
	FCsFxElement* FX					  = Data_Weapon->GetMuzzleFX(ViewType, FireMode, CurrentProjectilePerShotIndex.Get(FireMode));

	Manager_FX->Play(FX, GetMyPawn(), GetMuzzleFlashParent(ViewType));
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

		for (uint8 I = 0; I < WEAPON_FIRE_MODE_MAX; ++I)
		{
			StopChargeFire((TCsWeaponFireMode)I);
		}

		Scheduler->BroadcastMessage(ECsCoroutineSchedule::Tick, ECsCoroutineMessage::Stop, ECsWeaponCachedName::Name::Stop_FireWeapon_Internal, this);

		for (uint8 I = 0; I < WEAPON_FIRE_MODE_MAX; ++I)
		{
			StopAnimation((TCsWeaponFireMode)I, FireAnim);
		}
	}

	ReloadStartTime = GetWorld()->TimeSeconds;
	IsReloading		= true;

	PlayAnimation_Reload();

	LastState    = CurrentState;
	CurrentState = ReloadingState;
}

#pragma endregion Reload