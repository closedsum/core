// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/CsTypes_Interpolation.h"
#include "Types/CsTypes_Curve.h"
#include "Engine/HitResult.h"

#include "CsTypes_Damage.generated.h"

// DamageType
#pragma region

/** Describes the category of Damage. */
USTRUCT(BlueprintType)
struct CSDMG_API FECsDamageType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsDamageType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsDamageType)

struct CSDMG_API EMCsDamageType : public TCsEnumStructMap<FECsDamageType, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsDamageType, FECsDamageType, uint8)
};

namespace NCsDamageType
{
	typedef FECsDamageType Type;
	typedef EMCsDamageType EnumMapType;

	extern CSDMG_API const Type Default;

	CSDMG_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion DamageType

// HitType
#pragma region

USTRUCT(BlueprintType)
struct CSDMG_API FECsHitType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsHitType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsHitType)

struct CSDMG_API EMCsHitType : public TCsEnumStructMap<FECsHitType, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsHitType, FECsHitType, uint8)
};

namespace NCsHitType
{
	typedef FECsHitType Type;

	namespace Ref
	{

	}
}

#pragma endregion HitType

#define CS_INVALID_DAMAGE_TYPE 255
#define CS_INVALID_HIT_TYPE 255

// HitDirection
#pragma region

UENUM(BlueprintType)
enum class ECsHitDirection : uint8
{
	Front				UMETA(DisplayName = "Front"),
	FrontRight			UMETA(DisplayName = "Front Right"),
	Right				UMETA(DisplayName = "Right"),
	BackRight			UMETA(DisplayName = "Back Right"),
	Back				UMETA(DisplayName = "Back"),
	BackLeft			UMETA(DisplayName = "Back Left"),
	Left				UMETA(DisplayName = "Left"),
	FrontLeft			UMETA(DisplayName = "Front Left"),
	ECsHitDirection_MAX	UMETA(Hidden),
};

struct CSDMG_API EMCsHitDirection final : public TCsEnumMap<ECsHitDirection>
{
	CS_ENUM_MAP_BODY(EMCsHitDirection, ECsHitDirection)
};

namespace NCsHitDirection
{
	typedef ECsHitDirection Type;

	namespace Ref
	{
		extern CSDMG_API const Type Front;
		extern CSDMG_API const Type FrontRight;
		extern CSDMG_API const Type Right;
		extern CSDMG_API const Type BackRight;
		extern CSDMG_API const Type Back;
		extern CSDMG_API const Type BackLeft;
		extern CSDMG_API const Type Left;
		extern CSDMG_API const Type FrontLeft;
		extern CSDMG_API const Type ECsHitDirection_MAX;
	}

	FORCEINLINE const Type& GetTypeFromAngleDelta(const float &Delta)
	{
		const float AbsDelta = FMath::Abs(Delta);

		// Front
		if (AbsDelta < 27.5f)
			return Ref::Front;
		// FrontRight
		if (Delta <= -27.5f && Delta >= -62.5f)
			return Ref::FrontRight;
		// Right
		if (Delta < -62.5f && Delta > -117.5f)
			return Ref::Right;
		// BackRight
		if (Delta <= -117.5f && Delta >= -162.5f)
			return Ref::BackRight;
		// Back
		if (AbsDelta <= 180.0f && AbsDelta > 162.5f)
			return Ref::Back;
		// BackLeft
		if (Delta >= 117.5f && Delta <= 162.5f)
			return Ref::BackLeft;
		// Left
		if (Delta > 62.5f && Delta < 117.5f)
			return Ref::Left;
		// FrontLeft
		if (Delta >= 27.5f && Delta <= 62.5f)
			return Ref::FrontLeft;
		return Ref::ECsHitDirection_MAX;
	}
}

#pragma endregion HitType

// FCsDamageFalloff
#pragma region

USTRUCT(BlueprintType)
struct CSDMG_API FCsDamageFalloff
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Rate;
	/** Distance interval at which Falloff Rate occurs */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Frequency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Minimum;

	/** Maximum Distance at which Falloff happens */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxDistance;

	/** Whether to use an Easing Function to determine the Falloff */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ScriptName = "m_bEasingType", InlineEditConditionToggle))
	bool bEasingType;
	/** Easing method for interpolating values between the Maximum Distance and the Current Distance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ScriptName = "m_EasingType", editcondition = "bEasingType"))
	ECsEasingType EasingType;

	TCsEasingFunction EasingFunction;

	/** Whether to use a Curve [0,1] determine the Falloff */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ScriptName = "m_bCurve", InlineEditConditionToggle))
	bool bCurve;
	/** Curve [0,1] for interpolating values between the Maximum Distance and the Current Distance*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ScriptName = "m_Curve", editcondition = "bCurve"))
	FCsCurveFloat Curve;

	FCsDamageFalloff() :
		Rate(0.0f),
		Frequency(0.0f),
		Minimum(0.0f),
		MaxDistance(0.0f),
		bEasingType(false),
		bCurve(false),
		Curve()
	{
		EasingType = ECsEasingType::Linear;
	}

	~FCsDamageFalloff() {}

	float GetFalloff(const float &Distance);
};

#pragma endregion FCsDamageFalloff

// FCsDamageRadial
#pragma region

USTRUCT(BlueprintType)
struct CSDMG_API FCsDamageRadial
{
	GENERATED_USTRUCT_BODY()

	/** Min Damage */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Min;
	/** Max Damage */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Max;

	float Delta;

	/** Easing method for interpolating values between Min and Max */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	ECsEasingType EasingType;

	TCsEasingFunction EasingFunction;

	/** Whether to use a Curve [0,1] instead of an Easing method to interpolate values between Min and Max */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ScriptName = "m_bCurve", InlineEditConditionToggle))
	bool bCurve;
	/** Curve [0,1] for interpolating values between Min and Max */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ScriptName = "m_Curve", editcondition = "bCurve"))
	FCsCurveFloat Curve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MinRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxRadius;

	float DeltaRadius;

	/** Whether the Damage also afflicts the Owner */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (InlineEditConditionToggle))
	bool bApplyToOwner;
	/** Percentage of Damage to apply to the Owner */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (editcondition = "bApplyToOwner"), meta = (ClampMin = "0.0", UIMin = "0.0"))
	float OwnerPercent;

	FCsDamageRadial() :
		Min(0.0f),
		Max(0.0f),
		Delta(0.0f),
		bCurve(false),
		Curve(),
		MinRadius(0.0f),
		MaxRadius(0.0f),
		DeltaRadius(0.0f),
		bApplyToOwner(false),
		OwnerPercent(0.0f)
	{
		EasingType = ECsEasingType::Linear;
	}

	~FCsDamageRadial(){}

	void Init()
	{
		Max   = Max < Min ? Min : Max;
		Delta = Max - Min;
		
		if (MaxRadius < MinRadius)
		{
			MaxRadius = MinRadius;
			MinRadius = 0.0f;
		}
		DeltaRadius = MaxRadius - MinRadius;
	}

	void OnPostLoad() { Init(); }
	void OnLoad() { Init(); }

	float GetDamage(const FVector3f& Origin, const FVector3f& Location);

	float GetOwnerDamage(const FVector3f& Origin, const FVector3f& Location)
	{
		if (!bApplyToOwner)
			return 0.0f;
		if (OwnerPercent == 0.0f)
			return 0.0f;

		return OwnerPercent * GetDamage(Origin, Location);
	}
};

#pragma endregion FCsDamageRadial

USTRUCT(BlueprintType)
struct CSDMG_API FCsDamageEvent
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	TWeakObjectPtr<UObject> Instigator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	TWeakObjectPtr<UObject> Causer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	FECsDamageType DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	FECsHitType HitType;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	//EProjectileType ProjectileType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool HasImpulse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	FHitResult HitInfo;

	FCsDamageEvent()
	{
		Reset();
	}

	void Reset()
	{
		Damage = 0.0f;
		Instigator.Reset();
		Instigator = nullptr;
		Causer.Reset();
		Causer = nullptr;
		DamageType = EMCsDamageType::Get().GetMAX();
		HitType = EMCsHitType::Get().GetMAX();
		HasImpulse = false;
		HitInfo.Reset(0.0f, false);
	}

	FORCEINLINE UObject* GetInstigator() { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetInstigator() { return Cast<T>(GetInstigator()); }

	FORCEINLINE UObject* GetCauser() { return Causer.IsValid() ? Causer.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetCauser() { return Cast<T>(GetCauser()); }
};

USTRUCT(BlueprintType)
struct CSDMG_API FCsDamageResult
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	TWeakObjectPtr<UObject> Victim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	FECsDamageType DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	FECsHitType HitType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	FHitResult HitInfo;

	FCsDamageResult()
	{
		Reset();
	}

	FORCEINLINE bool operator==(const FCsDamageResult& B) const
	{
		return	Damage == B.Damage &&
				Victim == B.Victim &&
				DamageType == B.DamageType &&
				HitType == B.HitType;
	}

	FORCEINLINE bool operator!=(const FCsDamageResult& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		Damage = 0.0f;
		Victim.Reset();
		Victim = nullptr;
		DamageType = EMCsDamageType::Get().GetMAX();
		HitType = EMCsHitType::Get().GetMAX();
		HitInfo.Reset(0.0f, false);
	}

	FORCEINLINE UObject* GetVictim() { return Victim.IsValid() ? Victim.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetVictim() { return Cast<T>(GetVictim()); }
};