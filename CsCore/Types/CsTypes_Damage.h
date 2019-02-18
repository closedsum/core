// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Interpolation.h"
#include "Types/CsTypes_Curve.h"

#include "CsTypes_Damage.generated.h"
#pragma once

// DamageType
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsDamageType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsDamageType() {}
	FECsDamageType(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsDamageType(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsDamageType() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsDamageType& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsDamageType : public TCsEnumStructMap<FECsDamageType, uint8>
{
protected:
	EMCsDamageType() {}
	EMCsDamageType(const EMCsDamageType &) = delete;
	EMCsDamageType(EMCsDamageType &&) = delete;
public:
	~EMCsDamageType() {}
private:
	static EMCsDamageType* Instance;

public:
	static EMCsDamageType& Get();
};

#pragma endregion DamageType

// HitType
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsHitType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsHitType() {}
	FECsHitType(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsHitType(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsHitType() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsHitType& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsHitType : public TCsEnumStructMap<FECsHitType, uint8>
{
protected:
	EMCsHitType() {}
	EMCsHitType(const EMCsHitType &) = delete;
	EMCsHitType(EMCsHitType &&) = delete;
public:
	~EMCsHitType() {}
private:
	static EMCsHitType* Instance;

public:
	static EMCsHitType& Get();
};

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

struct CSCORE_API EMCsHitDirection : public TCsEnumMap<ECsHitDirection>
{
protected:
	EMCsHitDirection() {}
	EMCsHitDirection(const EMCsHitDirection &) = delete;
	EMCsHitDirection(EMCsHitDirection &&) = delete;
public:
	~EMCsHitDirection() {}
private:
	static EMCsHitDirection* Instance;

public:
	static EMCsHitDirection& Get();
};

namespace NCsHitDirection
{
	typedef ECsHitDirection Type;

	namespace Ref
	{
		extern CSCORE_API const Type Front;
		extern CSCORE_API const Type FrontRight;
		extern CSCORE_API const Type Right;
		extern CSCORE_API const Type BackRight;
		extern CSCORE_API const Type Back;
		extern CSCORE_API const Type BackLeft;
		extern CSCORE_API const Type Left;
		extern CSCORE_API const Type FrontLeft;
		extern CSCORE_API const Type ECsHitDirection_MAX;
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

USTRUCT(BlueprintType)
struct CSCORE_API FCsDamageFalloff
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
	ECsEasingType EasingType;

	TCsEasingFunction EasingFunction;

	/** Whether to use a Curve [0,1] determine the Falloff */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (InlineEditConditionToggle))
	bool bCurve;
	/** Curve [0,1] for interpolating values between the Maximum Distance and the Current Distance*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (editcondition = "bCurve"))
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
struct CSCORE_API FCsDamageRadial
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
		if (!bApplyToOwner)
			return 0.0f;
		if (OwnerPercent == 0.0f)
			return 0.0f;

		return OwnerPercent * GetDamage(Origin, Location);
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsDamageEvent
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	uint8 Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool bAllocated;

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
	//TEnumAsByte<EProjectileType::Type> ProjectileType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool HasImpulse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	FHitResult HitInfo;

	FCsDamageEvent() :
		Index(0)
	{
		Reset();
	}
	virtual ~FCsDamageEvent(){}

	FORCEINLINE FCsDamageEvent& operator=(const FCsDamageEvent& B)
	{
		Damage = B.Damage;
		Instigator = B.Instigator;
		Causer = B.Causer;
		DamageType = B.DamageType;
		HitType = B.HitType;
		HasImpulse = B.HasImpulse;
		HitInfo = B.HitInfo;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsDamageEvent& B) const
	{
		return Damage == B.Damage &&
			   Instigator == B.Instigator &&
			   Causer == B.Causer &&
			   DamageType == B.DamageType &&
		 	   HitType == B.HitType &&
			   HasImpulse == B.HasImpulse;
	}

	FORCEINLINE bool operator!=(const FCsDamageEvent& B) const
	{
		return !(*this == B);
	}

	void Init(const uint8 &InIndex)
	{
		Index = InIndex;
	}

	void Reset()
	{
		bAllocated = false;
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
struct CSCORE_API FCsDamageResult
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	uint8 Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool bAllocated;

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

	FCsDamageResult() :
		Index(0)
	{
		Reset();
	}
	virtual ~FCsDamageResult() {}

	FORCEINLINE FCsDamageResult& operator=(const FCsDamageResult& B)
	{
		Damage = B.Damage;
		
		Victim = B.Victim;
		DamageType = B.DamageType;
		HitType = B.HitType;
		HitInfo = B.HitInfo;
		return *this;
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

	void Init(const uint8 &InIndex)
	{
		Index = InIndex;
	}

	void Reset()
	{
		bAllocated = false;
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