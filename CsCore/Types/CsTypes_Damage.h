// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Interpolation.h"
#include "Types/CsTypes_Curve.h"

#include "CsTypes_Damage.generated.h"
#pragma once

namespace ECsDamageType
{
	enum Type : uint8;
}

typedef ECsDamageType::Type TCsDamageType;

// DamageTypeToString
typedef const FString&(*TCsDamageTypeToString)(const TCsDamageType&);
// StringToDamageType
typedef TCsDamageType(*TCsStringToDamageType)(const FString&);

#define CS_DECLARE_DAMAGE_TYPE	TCsDamageType DamageType_MAX; \
								uint8 DAMAGE_TYPE_MAX; \
								TCsDamageTypeToString DamageTypeToString; \
								TCsStringToDamageType StringToDamageType;

#define CS_DEFINE_DAMAGE_TYPE	DamageType_MAX = ECsDamageType::ECsDamageType_MAX;\
								DAMAGE_TYPE_MAX = (uint8)DamageType_MAX \
								DamageTypeToString = &ECsDamageType::ToString; \
								StringToDamageType = &ECsDamageType::ToType;

namespace ECsHitType
{
	enum Type : uint8;
}

typedef ECsHitType::Type TCsHitType;

// HitTypeToString
typedef const FString&(*TCsHitTypeToString)(const TCsHitType&);
// StringToHitType
typedef TCsHitType(*TCsStringToHitType)(const FString&);

#define CS_DECLARE_HIT_TYPE	TCsHitType HitType_MAX; \
							uint8 HIT_TYPE_MAX; \
							TCsHitTypeToString HitTypeToString; \
							TCsStringToHitType StringToHitType;

#define CS_DEFINE_HIT_TYPE	HitType_MAX = ECsHitType::ECsHitType_MAX;\
							HIT_TYPE_MAX = (uint8)HitType_MAX \
							HitTypeToString = &ECsHitType::ToString; \
							StringToHitType = &ECsHitType::ToType

#define CS_INVALID_DAMAGE_TYPE 255
#define CS_INVALID_HIT_TYPE 255

USTRUCT(BlueprintType)
struct FCsDamageFalloff
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (InlineEditConditionToggle))
	bool bEasingType;
	/** Easing method for interpolating values between the Maximum Distance and the Current Distance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (editcondition = "bEasingType"))
	TEnumAsByte<ECsEasingType::Type> EasingType;

	TCsEasingFunction EasingFunction;

	/** Whether to use a Curve [0,1] determine the Falloff */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (InlineEditConditionToggle))
	bool bCurve;
	/** Curve [0,1] for interpolating values between the Maximum Distance and the Current Distance*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (editcondition = "bCurve"))
	FCsCurveFloat Curve;

	FCsDamageFalloff()
	{
		EasingType = ECsEasingType::Linear;
	}

	~FCsDamageFalloff() {}

	float GetFalloff(const float &Distance)
	{
		if (MaxDistance > 0.0f && Distance > MaxDistance)
			return Minimum;

		// Easing
		if (bEasingType)
		{
			const float Percent = Distance / MaxDistance;

			return FMath::Max(Minimum, (*EasingFunction)(Percent, 0.0f, 1.0f, 1.0f));
		}
		// Curve
		else
		if (bCurve)
		{
			const float Percent = Distance / MaxDistance;

			return FMath::Max(Minimum, Curve.Get()->GetFloatValue(Percent));
		}
		// Default
		else
		{
			if (Rate == 0.0f || Frequency == 0.0f)
				return 1.0f;

			return FMath::Max(Minimum, 1.0f - (Rate * FMath::FloorToFloat(Distance / Frequency)));
		}
	}
};

USTRUCT(BlueprintType)
struct FCsDamageRadial
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
	TEnumAsByte<ECsEasingType::Type> EasingType;

	TCsEasingFunction EasingFunction;

	/** Whether to use a Curve [0,1] instead of an Easing method to interpolate values between Min and Max */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (InlineEditConditionToggle))
	bool bCurve;
	/** Curve [0,1] for interpolating values between Min and Max */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (editcondition = "bCurve"))
	FCsCurveFloat Curve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MinRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxRadius;

	float DeltaRadius;

	/** Whether the Damage also afflicts the Owner */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (InlineEditConditionToggle))
	bool ApplyToOwner;
	/** Percentage of Damage to apply to the Owner */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (editcondition = "ApplyToOwner"), meta = (ClampMin = "0.0", UIMin = "0.0"))
	float OwnerPercent;

	FCsDamageRadial()
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

	float GetDamage(const FVector& Origin, const FVector &Location)
	{
		if (DeltaRadius == 0.0f)
			return 0.0f;

		const float Distance = (Location - Origin).Size();

		if (Distance < MinRadius)
			return 0.0f;
		if (Distance > MaxRadius)
			return 0.0f;
		if (Delta == 0.0f)
			return Min;

		const float Percent = (Distance - MinRadius) / DeltaRadius;

		if (bCurve)
			return Curve.Get()->GetFloatValue(Percent) * Delta + Min;
		return (*EasingFunction)(Percent, 0.0f, 1.0f, 1.0f) * Delta + Min;
	}

	float GetOwnerDamage(const FVector &Origin, const FVector &Location)
	{
		if (!ApplyToOwner)
			return 0.0f;
		if (OwnerPercent == 0.0f)
			return 0.0f;

		return OwnerPercent * GetDamage(Origin, Location);
	}
};

USTRUCT(BlueprintType)
struct FCsDamageEvent
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	uint8 Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool IsAllocated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	TWeakObjectPtr<UObject> Instigator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	TWeakObjectPtr<UObject> Causer;

	TCsDamageType DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	uint8 DamageType_Script;

	TCsHitType HitType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	uint8 HitType_Script;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	//TEnumAsByte<EProjectileType::Type> ProjectileType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool HasImpulse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	FHitResult HitInfo;

	FCsDamageEvent()
	{
		Reset();
	}
	virtual ~FCsDamageEvent(){}

	FCsDamageEvent& operator=(const FCsDamageEvent& B)
	{
		Damage = B.Damage;
		Instigator = B.Instigator;
		Causer = B.Causer;
		DamageType = B.DamageType;
		DamageType_Script = B.DamageType_Script;
		HitType = B.HitType;
		HitType_Script = B.HitType_Script;
		HasImpulse = B.HasImpulse;
		HitInfo = B.HitInfo;
		return *this;
	}

	bool operator==(const FCsDamageEvent& B) const
	{
		return Damage == B.Damage &&
			   Instigator == B.Instigator &&
			   Causer == B.Causer &&
			   DamageType == B.DamageType &&
			   DamageType_Script == B.DamageType_Script &&
		 	   HitType == B.HitType &&
			   HitType_Script == B.HitType_Script &&
			   HasImpulse == B.HasImpulse;
	}

	bool operator!=(const FCsDamageEvent& B) const
	{
		return !(*this == B);
	}

	void Init(const uint8 &InIndex)
	{
		Index = InIndex;
	}

	void Reset()
	{
		Damage = 0.0f;
		Instigator.Reset();
		Instigator = nullptr;
		Causer.Reset();
		Causer = nullptr;
		DamageType = (TCsDamageType)0;
		DamageType_Script = CS_INVALID_DAMAGE_TYPE;
		HitType = (TCsHitType)0;
		HitType_Script = CS_INVALID_HIT_TYPE;
		HasImpulse = false;
		HitInfo.Reset(0.0f, false);
	}

	void SetDamageType(const TCsDamageType &InDamageType)
	{
		DamageType		  = InDamageType;
		DamageType_Script = (uint8)DamageType;
	}

	void SetHitType(const TCsHitType &InHitType)
	{
		HitType		   = InHitType;
		HitType_Script = (uint8)HitType;
	}

	UObject* GetInstigator() { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
	template<typename T>
	T* GetInstigator() { return Cast<T>(GetInstigator()); }

	UObject* GetCauser() { return Causer.IsValid() ? Causer.Get() : nullptr; }
	template<typename T>
	T* GetCauser() { return Cast<T>(GetCauser()); }
};