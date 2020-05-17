// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/CsTypes_Curve.h"
#include "Types/CsTypes_Sound.h"
#include "Managers/Projectile/CsTypes_Projectile.h"
#include "Types/CsTypes_FX.h"
#include "Types/CsTypes_Anim.h"
#include "Data/CsTypes_Data_ProjectileBase.h"

#include "CsTypes_Weapon.generated.h"
#pragma once

// FCsLocationDamageModifier
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsLocationDamageModifier
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName Bone;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Multiplier;

	FCsLocationDamageModifier()
	{
		Multiplier = 1.0f;
	}

	FCsLocationDamageModifier& operator=(const FCsLocationDamageModifier& B)
	{
		Bone = B.Bone;
		Multiplier = B.Multiplier;
		return *this;
	}

	bool operator==(const FCsLocationDamageModifier& B) const
	{
		return Bone == B.Bone && Multiplier == B.Multiplier;
	}

	bool operator!=(const FCsLocationDamageModifier& B) const
	{
		return !(*this == B);
	}

	static FCsLocationDamageModifier CreateAndCopy(const FCsLocationDamageModifier& B)
	{
		FCsLocationDamageModifier A;
		A = B;
		return A;
	}
};

#pragma endregion FCsLocationDamageModifier

// WeaponState
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsWeaponState : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponState)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponState)

struct CSCOREDEPRECATED_API EMCsWeaponState : public TCsEnumStructMap<FECsWeaponState, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponState, FECsWeaponState, uint8)
};

#pragma endregion WeaponState

// WeaponSlot
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsWeaponSlot : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponSlot)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponSlot)

struct CSCOREDEPRECATED_API EMCsWeaponSlot : public TCsEnumStructMap<FECsWeaponSlot, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponSlot, FECsWeaponSlot, uint8)
};

#pragma endregion WeaponSlot

// WeaponFireMode
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsWeaponFireMode : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponFireMode)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponFireMode)

struct CSCOREDEPRECATED_API EMCsWeaponFireMode : public TCsEnumStructMap<FECsWeaponFireMode, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponFireMode, FECsWeaponFireMode, uint8)
};

#pragma endregion WeaponFireMode

// WeaponGrip
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsWeaponGrip : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponGrip)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponGrip)

struct CSCOREDEPRECATED_API EMCsWeaponGrip : public TCsEnumStructMap<FECsWeaponGrip, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponGrip, FECsWeaponGrip, uint8)
};

#pragma endregion WeaponGrip

// WeaponAnim
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsWeaponAnim : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponAnim)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponAnim)

struct CSCOREDEPRECATED_API EMCsWeaponAnim : public TCsEnumStructMap<FECsWeaponAnim, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponAnim, FECsWeaponAnim, uint8)
};

#pragma endregion WeaponAnim

// WeaponBlendSpace
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsWeaponBlendSpace : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponBlendSpace)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponBlendSpace)

struct CSCOREDEPRECATED_API EMCsWeaponBlendSpace : public TCsEnumStructMap<FECsWeaponBlendSpace, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponBlendSpace, FECsWeaponBlendSpace, uint8)
};

#pragma endregion WeaponBlendSpace

// WeaponAnimBlueprint
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsWeaponAnimBlueprint : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponAnimBlueprint)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponAnimBlueprint)

struct CSCOREDEPRECATED_API EMCsWeaponAnimBlueprint : public TCsEnumStructMap<FECsWeaponAnimBlueprint, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponAnimBlueprint, FECsWeaponAnimBlueprint, uint8)
};

#pragma endregion WeaponAnimBlueprint

// WeaponSound
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsWeaponSound : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponSound)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponSound)

struct CSCOREDEPRECATED_API EMCsWeaponSound : public TCsEnumStructMap<FECsWeaponSound, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponSound, FECsWeaponSound, uint8)
};

#pragma endregion WeaponSound

// WeaponOwner
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsWeaponOwner : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponOwner)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponOwner)

struct CSCOREDEPRECATED_API EMCsWeaponOwner : public TCsEnumStructMap<FECsWeaponOwner, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponOwner, FECsWeaponOwner, uint8)
};

#pragma endregion WeaponOwner

// FCsData_Weapon_FireMode_Firing
#pragma region

class UCsData_ProjectileBase;

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsData_Weapon_FireMode_Firing
{
	GENERATED_USTRUCT_BODY()

	/** Whether to do weapon fire on release of input */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool DoFireOnRelease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool AllowChargeFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0.05", UIMin = "0.05"))
	float MaxChargeFireTime;

	/** Time before force ending the charge fire. If 0, charge fire will NOT be forced to end. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float ForceReleaseChargeFireTime;

	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (ClampMin = "1.0", UIMin = "1.0"))
	float ChargeFireDamageMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "1.0", UIMin = "1.0"))
	float ChargeFireSpeedMultiplier;

	/** Is the fully automatic weapon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool IsFullAuto;

	/** Number of projectiles to fire per shot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "1", UIMin = "1"))
	uint8 ProjectilesPerShot;

	/** Time between each projectile fired per shot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float TimeBetweenProjectilesPerShot;

	/** Time between two consecutive shots */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float TimeBetweenShots;

	/** Time between two consecutive shots in full auto */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float TimeBetweenAutoShots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool IsHitscan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool DoesHitscanUseRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool DoesHitscanSimulateProjectileDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 ObstaclePenetrations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 PawnPenetrations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	TArray<FCsLocationDamageModifier> LocationDamageModifiers;

	/* Whether to also use a Fake Projectile when firing a projectile */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool UseFake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FCsData_ProjectileBasePtr Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FCsData_ProjectileBasePtr ChargeData;

	FCsData_Weapon_FireMode_Firing() :
		DoFireOnRelease(false),
		AllowChargeFire(false),
		MaxChargeFireTime(0.0f),
		ForceReleaseChargeFireTime(0.0f),
		ChargeFireDamageMultiplier(0.0f),
		ChargeFireSpeedMultiplier(0.0f),
		IsFullAuto(false),
		ProjectilesPerShot(0),
		TimeBetweenProjectilesPerShot(0.0f),
		TimeBetweenShots(0.0f),
		TimeBetweenAutoShots(0.0f),
		IsHitscan(false),
		DoesHitscanUseRadius(false),
		DoesHitscanSimulateProjectileDuration(false),
		ObstaclePenetrations(0),
		PawnPenetrations(0),
		UseFake(false),
		Data(),
		ChargeData()
	{
	}
	virtual ~FCsData_Weapon_FireMode_Firing() {}

	UCsData_ProjectileBase* GetData()
	{
		return Data.Get();
	}

	UCsData_ProjectileBase* GetChargeData()
	{
		return ChargeData.Get();
	}
};

#pragma endregion FCsData_Weapon_FireMode_Firing

// FCsData_Weapon_FireMode_Animation
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsData_Weapon_FireMode_Animation
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool LoopFireAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	FCsAnimMontage FireAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool DoScaleFireAnim;

	FCsData_Weapon_FireMode_Animation() :
		LoopFireAnim(false),
		FireAnim(),
		DoScaleFireAnim(false)
	{
	}

	virtual ~FCsData_Weapon_FireMode_Animation() {}
};

#pragma endregion FCsData_Weapon_FireMode_Animation

// FCsData_FpsWeapon_FireMode_Animation
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsData_FpsWeapon_FireMode_Animation
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool LoopFireAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	FCsFpvAnimMontage FireAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool DoScaleFireAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool LoopAdsFireAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	FCsFpvAnimMontage AdsFireAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool DoScaleAdsFireAnim;

	FCsData_FpsWeapon_FireMode_Animation() :
		LoopFireAnim(false),
		FireAnims(),
		DoScaleFireAnim(false),
		LoopAdsFireAnim(false),
		AdsFireAnims(),
		DoScaleAdsFireAnim(false)
	{
	}
	virtual ~FCsData_FpsWeapon_FireMode_Animation() {}
};

#pragma endregion FCsData_FpsWeapon_FireMode_Animation

// FCsData_Weapon_FireMode_Movement
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsData_Weapon_FireMode_Movement
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool DoSlowWhileFiring;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SlowWhileFiringRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool DoKickback;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool DoKickbackOnGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float KickbackStrength;

	FCsData_Weapon_FireMode_Movement() :
		DoSlowWhileFiring(false),
		SlowWhileFiringRate(0.0f),
		DoKickback(false),
		DoKickbackOnGround(false),
		KickbackStrength(0.0f)
	{
	}
	virtual ~FCsData_Weapon_FireMode_Movement() {}
};

#pragma endregion FCsData_Weapon_FireMode_Movement

// FCsData_Weapon_FireMode_Aiming
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsData_Weapon_FireMode_Aiming
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
	bool IsHoming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
	float HomingAccelerationMagnitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
	bool DoSpread;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
	float MinSpread;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
	float MaxSpread;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
	float SpreadAddedPerShot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
	float SpreadRecoveryRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
	float FiringSpreadRecoveryDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
	float MovingSpreadBonus;

	FCsData_Weapon_FireMode_Aiming() :
		IsHoming(false),
		HomingAccelerationMagnitude(0.0f),
		DoSpread(false),
		MinSpread(0.0f),
		MaxSpread(0.0f),
		SpreadAddedPerShot(0.0f),
		SpreadRecoveryRate(0.0f),
		FiringSpreadRecoveryDelay(0.0f),
		MovingSpreadBonus(0.0f)
	{
	}

	virtual ~FCsData_Weapon_FireMode_Aiming() {}
};

#pragma endregion FCsData_Weapon_FireMode_Aiming

// FCsData_FpsWeapon_FireMode_Aiming
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsData_FpsWeapon_FireMode_Aiming : public FCsData_Weapon_FireMode_Aiming
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
	float JumpSpreadImpulse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
	float ScopeAccuracyBonus;

	FCsData_FpsWeapon_FireMode_Aiming() :
		JumpSpreadImpulse(0.0f),
		ScopeAccuracyBonus(0.0f)
	{
	}
	~FCsData_FpsWeapon_FireMode_Aiming() {}
};

#pragma endregion FCsData_FpsWeapon_FireMode_Aiming

// FCsData_Weapon_FireMode_Scope
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsData_Weapon_FireMode_Scope
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scope")
	TArray<FCsLocationDamageModifier> MinLocationDamageModifiers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scope")
	TArray<FCsLocationDamageModifier> MaxLocationDamageModifiers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scope")
	FCsCurveFloat LocationDamageModifierRamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scope", meta = (ClampMin = "0.0", UIMin = "0.0"))
	bool DoScopePower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scope", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxScopePower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scope", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float ScopePowerGrowthRate;

public:

	FCsData_Weapon_FireMode_Scope() :
		LocationDamageModifierRamp(),
		DoScopePower(false),
		MaxScopePower(0.0f),
		ScopePowerGrowthRate(0.0f)
	{
	}
	virtual ~FCsData_Weapon_FireMode_Scope() {}
};

#pragma endregion FCsData_Weapon_FireMode_Scope

// FCsData_Weapon_FireMode_FXs
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsData_Weapon_FireMode_FXs
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TArray<FCsFxElement> MuzzleFXs;

	FCsData_Weapon_FireMode_FXs() {}
	virtual ~FCsData_Weapon_FireMode_FXs() {}

	FCsFxElement* GetMuzzleFX(const int32 Index = 0)
	{
		const int32 Count = MuzzleFXs.Num();

		return Count > CS_EMPTY ? &(MuzzleFXs[Index % Count]) : nullptr;
	}

	const FName& GetMuzzleBone(const int32 Index = 0)
	{
		const int32 Count = MuzzleFXs.Num();

		return MuzzleFXs[Index % Count].Bone;
	}
};

#pragma endregion FCsData_Weapon_FireMode_FXs

// FCsData_FpsWeapon_FireMode_FXs
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsData_FpsWeapon_FireMode_FXs
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TArray<FCsFpvFxElement> MuzzleFXs;

	FCsData_FpsWeapon_FireMode_FXs() {}
	virtual ~FCsData_FpsWeapon_FireMode_FXs() {}

	FCsFxElement* GetMuzzleFX(const ECsViewType& ViewType, const int32 Index = 0)
	{
		const int32 Count = MuzzleFXs.Num();

		return MuzzleFXs[Index % Count].Get(ViewType);
	}

	const FName& GetMuzzleBone(const ECsViewType& ViewType, const int32 Index = 0)
	{
		const int32 Count = MuzzleFXs.Num();

		return MuzzleFXs[Index % Count].GetBone(ViewType);
	}
};

#pragma endregion FCsData_FpsWeapon_FireMode_FXs

// FCsData_Weapon_FireMode_Sounds
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsData_Weapon_FireMode_Sounds
{
	GENERATED_USTRUCT_BODY()

	/** single fire sound (bLoopedFireSound not set) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	FCsSoundElement FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	bool LoopFireSound;

	/** looped fire sound (bLoopedFireSound set) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	FCsSoundElement FireLoopSound;

	/** finished burst sound (bLoopedFireSound set) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	FCsSoundElement FireFinishSound;

	FCsData_Weapon_FireMode_Sounds() :
		FireSound(),
		LoopFireSound(false),
		FireLoopSound(),
		FireFinishSound()
	{
	}
	virtual ~FCsData_Weapon_FireMode_Sounds() {}
};

#pragma endregion FCsData_Weapon_FireMode_Sounds

// FCsData_FpsWeapon_FireMode_Sounds
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsData_FpsWeapon_FireMode_Sounds
{
	GENERATED_USTRUCT_BODY()

	/** single fire sound (bLoopedFireSound not set) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	FCsFpvSoundElement FireSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	bool LoopFireSound;

	/** looped fire sound (bLoopedFireSound set) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	FCsFpvSoundElement FireLoopSounds;

	/** finished burst sound (bLoopedFireSound set) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	FCsFpvSoundElement FireFinishSounds;

	FCsData_FpsWeapon_FireMode_Sounds() :
		FireSounds(),
		LoopFireSound(false),
		FireLoopSounds(),
		FireFinishSounds()
	{
	}
	virtual ~FCsData_FpsWeapon_FireMode_Sounds() {}
};

#pragma endregion FCsData_FpsWeapon_FireMode_Sounds

// Data_Weapon_FireMode 
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsData_Weapon_FireMode : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsData_Weapon_FireMode)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsData_Weapon_FireMode)

struct CSCOREDEPRECATED_API EMCsData_Weapon_FireMode : public TCsEnumStructMap<FECsData_Weapon_FireMode, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsData_Weapon_FireMode, FECsData_Weapon_FireMode, uint8)
};

#pragma endregion Data_Weapon_FireMode 

// MeleeStyle
#pragma region

namespace ECsMeleeStyle
{
	enum Type : uint8;
}

typedef ECsMeleeStyle::Type TCsMeleeStyle;

// MeleeStyleToString
typedef const FString&(*TCsMeleeStyleToString)(const TCsMeleeStyle&);
// StringToMeleeStyle
typedef TCsMeleeStyle(*TCsStringToMeleeStyle)(const FString&);

#define CS_DECLARE_MELEE_STYLE	TCsMeleeStyle MeleeStyle_MAX; \
								uint8 MELEE_STYLE_MAX; \
								TCsMeleeStyleToString MeleeStyleToString; \
								TCsStringToMeleeStyle StringToMeleeStyle;

#define CS_DEFINE_MELEE_STYLE	MeleeStyle_MAX = ECsWeaponSlot::ECsWeaponSlot_MAX;\
								MELEE_STYLE_MAX = (uint8)WeaponSlot_MAX \
								MeleeStyleToString = &ECsMeleeStyle::ToString; \
								StringToMeleeStyle = &ECsMeleeStyle::ToType;

#pragma endregion MeleeStyle