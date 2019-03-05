// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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

	// WeaponState

USTRUCT(BlueprintType)
struct CSCORE_API FECsWeaponState : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsWeaponState() {}
	FECsWeaponState(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsWeaponState(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsWeaponState() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsWeaponState& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsWeaponState : public TCsEnumStructMap<FECsWeaponState, uint8>
{
protected:
	EMCsWeaponState() {}
	EMCsWeaponState(const EMCsWeaponState &) = delete;
	EMCsWeaponState(EMCsWeaponState &&) = delete;
public:
	~EMCsWeaponState() {}
private:
	static EMCsWeaponState* Instance;

public:
	static EMCsWeaponState& Get();
};

	// WeaponSlot

USTRUCT(BlueprintType)
struct CSCORE_API FECsWeaponSlot : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsWeaponSlot() {}
	FECsWeaponSlot(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsWeaponSlot(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsWeaponSlot() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsWeaponSlot& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsWeaponSlot : public TCsEnumStructMap<FECsWeaponSlot, uint8>
{
protected:
	EMCsWeaponSlot() {}
	EMCsWeaponSlot(const EMCsWeaponSlot &) = delete;
	EMCsWeaponSlot(EMCsWeaponSlot &&) = delete;
public:
	~EMCsWeaponSlot() {}
private:
	static EMCsWeaponSlot* Instance;

public:
	static EMCsWeaponSlot& Get();
};

	// WeaponFireMode

USTRUCT(BlueprintType)
struct CSCORE_API FECsWeaponFireMode : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsWeaponFireMode() {}
	FECsWeaponFireMode(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsWeaponFireMode(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsWeaponFireMode() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsWeaponFireMode& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsWeaponFireMode : public TCsEnumStructMap<FECsWeaponFireMode, uint8>
{
protected:
	EMCsWeaponFireMode() {}
	EMCsWeaponFireMode(const EMCsWeaponFireMode &) = delete;
	EMCsWeaponFireMode(EMCsWeaponFireMode &&) = delete;
public:
	~EMCsWeaponFireMode() {}
private:
	static EMCsWeaponFireMode* Instance;

public:
	static EMCsWeaponFireMode& Get();
};

	// WeaponGrip

USTRUCT(BlueprintType)
struct CSCORE_API FECsWeaponGrip : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsWeaponGrip() {}
	FECsWeaponGrip(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsWeaponGrip(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsWeaponGrip() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsWeaponGrip& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsWeaponGrip : public TCsEnumStructMap<FECsWeaponGrip, uint8>
{
protected:
	EMCsWeaponGrip() {}
	EMCsWeaponGrip(const EMCsWeaponGrip &) = delete;
	EMCsWeaponGrip(EMCsWeaponGrip &&) = delete;
public:
	~EMCsWeaponGrip() {}
private:
	static EMCsWeaponGrip* Instance;

public:
	static EMCsWeaponGrip& Get();
};

	// WeaponAnim

USTRUCT(BlueprintType)
struct CSCORE_API FECsWeaponAnim : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsWeaponAnim() {}
	FECsWeaponAnim(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsWeaponAnim(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsWeaponAnim() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsWeaponAnim& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsWeaponAnim : public TCsEnumStructMap<FECsWeaponAnim, uint8>
{
protected:
	EMCsWeaponAnim() {}
	EMCsWeaponAnim(const EMCsWeaponAnim &) = delete;
	EMCsWeaponAnim(EMCsWeaponAnim &&) = delete;
public:
	~EMCsWeaponAnim() {}
private:
	static EMCsWeaponAnim* Instance;

public:
	static EMCsWeaponAnim& Get();
};

	// WeaponBlendSpace

USTRUCT(BlueprintType)
struct CSCORE_API FECsWeaponBlendSpace : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsWeaponBlendSpace() {}
	FECsWeaponBlendSpace(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsWeaponBlendSpace(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsWeaponBlendSpace() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsWeaponBlendSpace& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsWeaponBlendSpace : public TCsEnumStructMap<FECsWeaponBlendSpace, uint8>
{
protected:
	EMCsWeaponBlendSpace() {}
	EMCsWeaponBlendSpace(const EMCsWeaponBlendSpace &) = delete;
	EMCsWeaponBlendSpace(EMCsWeaponBlendSpace &&) = delete;
public:
	~EMCsWeaponBlendSpace() {}
private:
	static EMCsWeaponBlendSpace* Instance;

public:
	static EMCsWeaponBlendSpace& Get();
};

	// WeaponAnimBlueprint

USTRUCT(BlueprintType)
struct CSCORE_API FECsWeaponAnimBlueprint : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsWeaponAnimBlueprint() {}
	FECsWeaponAnimBlueprint(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsWeaponAnimBlueprint(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsWeaponAnimBlueprint() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsWeaponAnimBlueprint& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsWeaponAnimBlueprint : public TCsEnumStructMap<FECsWeaponAnimBlueprint, uint8>
{
protected:
	EMCsWeaponAnimBlueprint() {}
	EMCsWeaponAnimBlueprint(const EMCsWeaponAnimBlueprint &) = delete;
	EMCsWeaponAnimBlueprint(EMCsWeaponAnimBlueprint &&) = delete;
public:
	~EMCsWeaponAnimBlueprint() {}
private:
	static EMCsWeaponAnimBlueprint* Instance;

public:
	static EMCsWeaponAnimBlueprint& Get();
};

	// WeaponSound

USTRUCT(BlueprintType)
struct CSCORE_API FECsWeaponSound : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsWeaponSound() {}
	FECsWeaponSound(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsWeaponSound(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsWeaponSound() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsWeaponSound& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsWeaponSound : public TCsEnumStructMap<FECsWeaponSound, uint8>
{
protected:
	EMCsWeaponSound() {}
	EMCsWeaponSound(const EMCsWeaponSound &) = delete;
	EMCsWeaponSound(EMCsWeaponSound &&) = delete;
public:
	~EMCsWeaponSound() {}
private:
	static EMCsWeaponSound* Instance;

public:
	static EMCsWeaponSound& Get();
};

	// WeaponOwner

USTRUCT(BlueprintType)
struct CSCORE_API FECsWeaponOwner : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsWeaponOwner() {}
	FECsWeaponOwner(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsWeaponOwner(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsWeaponOwner() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsWeaponOwner& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsWeaponOwner : public TCsEnumStructMap<FECsWeaponOwner, uint8>
{
protected:
	EMCsWeaponOwner() {}
	EMCsWeaponOwner(const EMCsWeaponOwner &) = delete;
	EMCsWeaponOwner(EMCsWeaponOwner &&) = delete;
public:
	~EMCsWeaponOwner() {}
private:
	static EMCsWeaponOwner* Instance;

public:
	static EMCsWeaponOwner& Get();
};

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

	FCsData_Weapon_FireMode_Animation() :
		LoopFireAnim(false),
		FireAnim(),
		DoScaleFireAnim(false)
	{
	}

	virtual ~FCsData_Weapon_FireMode_Animation() {}
};

USTRUCT(BlueprintType)
struct FCsData_FpsWeapon_FireMode_Animation
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

USTRUCT(BlueprintType)
struct FCsData_FpsWeapon_FireMode_Aiming : public FCsData_Weapon_FireMode_Aiming
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

	FCsData_Weapon_FireMode_Scope() :
		LocationDamageModifierRamp(),
		DoScopePower(false),
		MaxScopePower(0.0f),
		ScopePowerGrowthRate(0.0f)
	{
	}
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

	const FName& GetMuzzleBone(const int32 Index = 0)
	{
		const int32 Count = MuzzleFXs.Num();

		return MuzzleFXs[Index % Count].Bone;
	}
};

USTRUCT(BlueprintType)
struct FCsData_FpsWeapon_FireMode_FXs
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TArray<FCsFpvFxElement> MuzzleFXs;

	FCsData_FpsWeapon_FireMode_FXs() {}
	virtual ~FCsData_FpsWeapon_FireMode_FXs() {}

	FCsFxElement* GetMuzzleFX(const TCsViewType &ViewType, const int32 Index = 0)
	{
		const int32 Count = MuzzleFXs.Num();

		return MuzzleFXs[Index % Count].Get(ViewType);
	}

	const FName& GetMuzzleBone(const TCsViewType &ViewType, const int32 Index = 0)
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

	FCsData_Weapon_FireMode_Sounds() :
		FireSound(),
		LoopFireSound(false),
		FireLoopSound(),
		FireFinishSound()
	{
	}
	virtual ~FCsData_Weapon_FireMode_Sounds() {}
};

USTRUCT(BlueprintType)
struct FCsData_FpsWeapon_FireMode_Sounds
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

USTRUCT(BlueprintType)
struct CSCORE_API FECsData_Weapon_FireMode : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsData_Weapon_FireMode() {}
	FECsData_Weapon_FireMode(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsData_Weapon_FireMode(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsData_Weapon_FireMode() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsData_Weapon_FireMode& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsData_Weapon_FireMode : public TCsEnumStructMap<FECsData_Weapon_FireMode, uint8>
{
protected:
	EMCsData_Weapon_FireMode() {}
	EMCsData_Weapon_FireMode(const EMCsData_Weapon_FireMode &) = delete;
	EMCsData_Weapon_FireMode(EMCsData_Weapon_FireMode &&) = delete;
public:
	~EMCsData_Weapon_FireMode() {}
private:
	static EMCsData_Weapon_FireMode* Instance;

public:
	static EMCsData_Weapon_FireMode& Get();
};

#pragma endregion Weapon

// Melee
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

#pragma endregion Melee