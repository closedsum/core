// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_Primitive.h"
#include "Types/CsTypes_Curve.h"
#include "Types/CsTypes_Sound.h"
#include "Types/CsTypes_Projectile.h"
#include "Types/CsTypes_FX.h"
#include "Types/CsTypes_Anim.h"

#include "CsTypes_Weapon.generated.h"
#pragma once

USTRUCT(BlueprintType)
struct FCsLocationDamageModifier
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	FName Bone;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
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

// Weapon
#pragma region

namespace ECsWeaponSlot
{
	enum Type : uint8;
}

typedef ECsWeaponSlot::Type TCsWeaponSlot;

// WeaponSlotToString
typedef FString(*TCsWeaponSlotToString)(const TCsWeaponSlot&);
// StringToWeaponSlot
typedef TCsWeaponSlot(*TCsStringToWeaponSlot)(const FString&);

#define CS_DECLARE_WEAPON_SLOT	TCsWeaponSlot WeaponSlot_MAX; \
								uint8 WEAPON_SLOT_MAX; \
								TCsWeaponSlotToString WeaponSlotToString; \
								TCsStringToWeaponSlot StringToWeaponSlot;

#define CS_DEFINE_WEAPON_SLOT	WeaponSlot_MAX = ECsWeaponSlot::ECsWeaponSlot_MAX;\
								WEAPON_SLOT_MAX = (uint8)WeaponSlot_MAX \
								WeaponSlotToString = &ECsWeaponSlot::ToString; \
								StringToWeaponSlot = &ECsWeaponSlot::ToType;

namespace ECsWeaponFireMode
{
	enum Type : uint8;
}

typedef ECsWeaponFireMode::Type TCsWeaponFireMode;

// WeaponFireModeToString
typedef FString(*TCsWeaponFireModeToString)(const TCsWeaponFireMode&);
// StringToWeaponFireMode
typedef TCsWeaponFireMode(*TCsStringToWeaponFireMode)(const FString&);

#define CS_DECLARE_WEAPON_FIRE_MODE	TCsWeaponFireMode WeaponFireMode_MAX; \
									uint8 WEAPON_FIRE_MODE_MAX; \
									TCsWeaponFireModeToString WeaponFireModeToString; \
									TCsStringToWeaponFireMode StringToWeaponFireMode;

#define CS_DEFINE_WEAPON_FIRE_MODE	WeaponFireMode_MAX = ECsWeaponFireMode::ECsWeaponFireMode_MAX;\
									WEAPON_FIRE_MODE_MAX = (uint8)WeaponFireMode_MAX; \
									WeaponFireModeToString = &ECsWeaponFireMode::ToString; \
									StringToWeaponFireMode = &ECsWeaponFireMode::ToType;

namespace ECsWeaponGrip
{
	enum Type : uint8;
}

typedef ECsWeaponGrip::Type TCsWeaponGrip;

// WeaponGripToString
typedef FString(*TCsWeaponGripToString)(const TCsWeaponGrip&);
// StringToWeaponGrip
typedef TCsWeaponGrip(*TCsStringToWeaponGrip)(const FString&);

#define CS_DECLARE_WEAPON_GRIP	TCsWeaponGrip WeaponGrip_MAX; \
								uint8 WEAPON_GRIP_MAX; \
								TCsWeaponGripToString WeaponGripToString; \
								TCsStringToWeaponGrip StringToWeaponGrip;

#define CS_DEFINE_WEAPON_GRIP	WeaponGrip_MAX = ECsWeaponGrip::ECsWeaponGrip_MAX;\
								WEAPON_GRIP_MAX = (uint8)WeaponGrip_MAX \
								WeaponGripToString = &ECsWeaponGrip::ToString; \
								StringToWeaponGrip = &ECsWeaponGrip::ToType;

namespace ECsWeaponAnim
{
	enum Type : uint8;
}

typedef ECsWeaponAnim::Type TCsWeaponAnim;

// WeaponAnimToString
typedef FString(*TCsWeaponAnimToString)(const TCsWeaponAnim&);
// StringToWeaponAnim
typedef TCsWeaponAnim(*TCsStringToWeaponAnim)(const FString&);

#define CS_DECLARE_WEAPON_ANIM	TCsWeaponAnim WeaponAnim_MAX; \
								uint8 WEAPON_ANIM_MAX; \
								TCsWeaponAnimToString WeaponAnimToString; \
								TCsStringToWeaponAnim StringToWeaponAnim;

#define CS_DEFINE_WEAPON_ANIM	WeaponAnim_MAX = ECsWeaponAnim::ECsWeaponAnim_MAX;\
								WEAPON_ANIM_MAX = (uint8)WeaponAnim_MAX; \
								WeaponAnimToString = &ECsWeaponAnim::ToString; \
								StringToWeaponAnim = &ECsWeaponAnim::ToType;

namespace ECsWeaponBlendSpace
{
	enum Type : uint8;
}

typedef ECsWeaponBlendSpace::Type TCsWeaponBlendSpace;

namespace ECsWeaponAnimBlueprint
{
	enum Type : uint8;
}

typedef ECsWeaponAnimBlueprint::Type TCsWeaponAnimBlueprint;

namespace ECsWeaponSound
{
	enum Type : uint8;
}

typedef ECsWeaponSound::Type TCsWeaponSound;

namespace ECsWeaponOwner
{
	enum Type : uint8;
}

typedef ECsWeaponOwner::Type TCsWeaponOwner;

// WeaponOwnerToString
typedef FString(*TCsWeaponOwnerToString)(const TCsWeaponOwner&);
// StringToWeaponOwner
typedef TCsWeaponOwner(*TCsStringToWeaponOwner)(const FString&);

#define CS_DECLARE_WEAPON_OWNER	TCsWeaponOwner WeaponOwner_MAX; \
								uint8 WEAPON_OWNER_MAX; \
								TCsWeaponOwnerToString WeaponOwnerToString; \
								TCsStringToWeaponOwner StringToWeaponOwner;

#define CS_DEFINE_WEAPON_OWNER	WeaponOwner_MAX = ECsWeaponOwner::ECsWeaponOwner_MAX;\
								WEAPON_OWNER_MAX = (uint8)WeaponOwner_MAX \
								WeaponOwnerToString = &ECsWeaponOwner::ToString; \
								StringToWeaponOwner = &ECsWeaponOwner::ToType;

USTRUCT(BlueprintType)
struct FCsData_Weapon_FireMode_Firing
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
	FCsData_ProjectilePtr Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FCsData_ProjectilePtr ChargeData;

	FCsData_Weapon_FireMode_Firing() {}
	virtual ~FCsData_Weapon_FireMode_Firing() {}

	class ACsData_Projectile* GetData()
	{
		return Data.Get();
	}

	class ACsData_Projectile* GetChargeData()
	{
		return ChargeData.Get();
	}
};

USTRUCT(BlueprintType)
struct FCsData_Weapon_FireMode_Animation
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool LoopFireAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	FCsAnimMontage FireAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool DoScaleFireAnim;

	FCsData_Weapon_FireMode_Animation() {}
	virtual ~FCsData_Weapon_FireMode_Animation() {}
};

USTRUCT(BlueprintType)
struct FCsData_FpsWeapon_FireMode_Animation
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool LoopFireAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	FCsFpsAnimMontage FireAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool DoScaleFireAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool LoopAdsFireAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	FCsFpsAnimMontage AdsFireAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool DoScaleAdsFireAnim;

	FCsData_FpsWeapon_FireMode_Animation() {}
	virtual ~FCsData_FpsWeapon_FireMode_Animation() {}
};

USTRUCT(BlueprintType)
struct FCsData_Weapon_FireMode_Movement
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

	FCsData_Weapon_FireMode_Movement() {}
	virtual ~FCsData_Weapon_FireMode_Movement() {}
};

USTRUCT(BlueprintType)
struct FCsData_Weapon_FireMode_Aiming
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

	FCsData_Weapon_FireMode_Aiming() {}
	virtual ~FCsData_Weapon_FireMode_Aiming() {}
};

USTRUCT(BlueprintType)
struct FCsData_FpsWeapon_FireMode_Aiming : public FCsData_Weapon_FireMode_Aiming
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
	float JumpSpreadImpulse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
	float ScopeAccuracyBonus;

	FCsData_FpsWeapon_FireMode_Aiming(){}
	~FCsData_FpsWeapon_FireMode_Aiming() {}
};

USTRUCT(BlueprintType)
struct FCsData_Weapon_FireMode_Scope
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

	FCsData_Weapon_FireMode_Scope() {}
	virtual ~FCsData_Weapon_FireMode_Scope() {}
};

USTRUCT(BlueprintType)
struct FCsData_Weapon_FireMode_FXs
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
};

USTRUCT(BlueprintType)
struct FCsData_FpsWeapon_FireMode_FXs
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TArray<FCsFpsFxElement> MuzzleFXs;

	FCsData_FpsWeapon_FireMode_FXs() {}
	virtual ~FCsData_FpsWeapon_FireMode_FXs() {}

	FCsFxElement* GetMuzzleFX(const TCsViewType &ViewType, const int32 Index = 0)
	{
		const int32 Count = MuzzleFXs.Num();

		return MuzzleFXs[Index % Count].Get(ViewType);
	}

	FName GetMuzzleBone(const TCsViewType &ViewType, const int32 Index = 0)
	{
		const int32 Count = MuzzleFXs.Num();

		return MuzzleFXs[Index % Count].GetBone(ViewType);
	}
};

USTRUCT(BlueprintType)
struct FCsData_Weapon_FireMode_Sounds
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

	FCsData_Weapon_FireMode_Sounds() {}
	virtual ~FCsData_Weapon_FireMode_Sounds() {}
};

USTRUCT(BlueprintType)
struct FCsData_FpsWeapon_FireMode_Sounds
{
	GENERATED_USTRUCT_BODY()

	/** single fire sound (bLoopedFireSound not set) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	FCsFpsSoundElement FireSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	bool LoopFireSound;

	/** looped fire sound (bLoopedFireSound set) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	FCsFpsSoundElement FireLoopSounds;

	/** finished burst sound (bLoopedFireSound set) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	FCsFpsSoundElement FireFinishSounds;

	FCsData_FpsWeapon_FireMode_Sounds() {}
	virtual ~FCsData_FpsWeapon_FireMode_Sounds() {}
};

namespace ECsData_Weapon_FireMode
{
	enum Type : uint8;
}

typedef ECsData_Weapon_FireMode::Type TCsData_Weapon_FireMode;

#pragma endregion Weapon