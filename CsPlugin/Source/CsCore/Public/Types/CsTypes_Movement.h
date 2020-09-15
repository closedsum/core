// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Interpolation.h"

#include "CsTypes_Movement.generated.h"
#pragma once

// 1 uu = ~ 0.00000621372 mi
// 1 mi = 160934 uu
// 1 sec = ~0.000277778 hr
// 1 hr = 3600 sec

// UUpS to MpH = 3600 / 160943 = ~ 0.022368167612
#define CS_UNREAL_UNITS_PER_SECOND_TO_MILES_PER_HOUR 0.022368167612f
// MpH to UUpS = 160943 / 3600 = ~ 44.7063889
#define CS_MILES_PER_HOUR_TO_UNREAL_UNITS_PER_SECOND 44.7063889f
// UUpS to KpH = 3600 / 100000 = 0.036
#define CS_UNREAL_UNITS_PER_SECOND_TO_KILOMETERS_PER_HOUR 0.036f
// KpH to UUpS = 100000 / 3600 = ~ 27.7777778
#define CS_KILOMETERS_PER_HOUR_TO_UNREAL_UNITS_PER_SECOND 27.7777778f
// MpH to KpH
#define CS_MILES_PER_HOUR_TO_KILOMETERS_PER_HOUR 1.60934f
// KpH to MpH
#define CS_KILOMETERS_PER_HOUR_TO_MILES_PER_HOUR 0.621371

// FCsSpeed
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSpeed
{
	GENERATED_USTRUCT_BODY()

	/** UUpS: Unreal Units per Second */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "UUpS: Unreal Units per Second", ClampMin = "0.0", UIMin = "0.0"))
	float UUpS;

	/** MpH: Miles per Hour */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "MpH: Miles per Hour", ClampMin = "0.0", UIMin = "0.0"))
	float MpH;

	/** KpH: Kilometers per Hour */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "KpH: Kilometers per Hour", ClampMin = "0.0", UIMin = "0.0"))
	float KpH;

	FCsSpeed() :
		UUpS(0.0f),
		MpH(0.0f),
		KpH(0.0f)
	{
	}

	FORCEINLINE void FromUUpS()
	{
		MpH = CS_UNREAL_UNITS_PER_SECOND_TO_MILES_PER_HOUR * UUpS;
		KpH = CS_UNREAL_UNITS_PER_SECOND_TO_KILOMETERS_PER_HOUR * UUpS;
	}

	FORCEINLINE void FromMpH()
	{
		UUpS = CS_MILES_PER_HOUR_TO_UNREAL_UNITS_PER_SECOND * MpH;
		KpH = CS_MILES_PER_HOUR_TO_KILOMETERS_PER_HOUR * MpH;
	}

	FORCEINLINE void FromKpH()
	{
		UUpS = CS_KILOMETERS_PER_HOUR_TO_UNREAL_UNITS_PER_SECOND * KpH;
		MpH = CS_KILOMETERS_PER_HOUR_TO_MILES_PER_HOUR * KpH;
	}

#if WITH_EDITOR
	void OnPostEditChange(const FName& PropertyName);
#endif // #if WITH_EDITOR
};

#pragma endregion FCsSpeed

// SpeedInterpMethod
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsSpeedInterpMethod : uint8
{
	/** Apply the Acceleration as a Delta. 
	     Usually in the form of sf = so + a * dt. 
		  sf = Final Speed 
		  so = Initial Speed
		  a = Acceleration
		  dt = Delta Time */
	Acceleration				UMETA(DisplayName = "Delta"),
	/** Using a Duration and Easing Type, determine the Speed. */
	Easing						UMETA(DisplayName = "Easing"),
	/** Using a Duration and Curve, determine the Speed. */
	Curve						UMETA(DisplayName = "Curve"),
	ECsSpeedInterpMethod_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSpeedInterpMethod final : public TCsEnumMap<ECsSpeedInterpMethod>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSpeedInterpMethod, ECsSpeedInterpMethod)
};

namespace NCsSpeedInterpMethod
{
	typedef ECsSpeedInterpMethod Type;

	namespace Ref
	{
		extern CSCORE_API const Type Acceleration;
		extern CSCORE_API const Type Easing;
		extern CSCORE_API const Type Curve;
		extern CSCORE_API const Type ECsSpeedInterpMethod_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion SpeedInterpMethod

// SpeedInterpDirection
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsSpeedInterpDirection : uint8
{
	/** Increasing toward the Target Speed. */
	Increasing					UMETA(DisplayName = "Increasing"),
	/** Decreasing toward the Target Speed. */
	Decreasing					UMETA(DisplayName = "Decreasing"),
	ECsSpeedInterpDirection_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSpeedInterpDirection final : public TCsEnumMap<ECsSpeedInterpDirection>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSpeedInterpDirection, ECsSpeedInterpDirection)
};

namespace NCsSpeedInterpDirection
{
	typedef ECsSpeedInterpDirection Type;

	namespace Ref
	{
		extern CSCORE_API const Type Increasing;
		extern CSCORE_API const Type Decreasing;
		extern CSCORE_API const Type ECsSpeedInterpDirection_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion SpeedInterpDirection

// FCsAcceleration
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsAcceleration
{
	GENERATED_USTRUCT_BODY()

	/** UUpS/S: Unreal Units per Second Second. 
		 This is only Valid for Method == Delta (ECsAccelerationMethod::Delta). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "UUpS/S: Unreal Units per Second Second", ClampMin = "0.0", UIMin = "0.0"))
	float UUpSS;
	 
	/** MpH/S: Miles per Hour Second Second.
		 This is only Valid for Method == Delta (ECsAccelerationMethod::Delta). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "MpH/S: Miles per Hour Second", ClampMin = "0.0", UIMin = "0.0"))
	float MpHS;

	/** KpH/S: Kilometers per Hour Second.
		 This is only Valid for Method == Delta (ECsAccelerationMethod::Delta). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "KpH/S: Kilometers per Hour Second", ClampMin = "0.0", UIMin = "0.0"))
	float KpHS;

	FCsAcceleration() :
		UUpSS(0.0f),
		MpHS(0.0f),
		KpHS(0.0f)
	{
	}

	FORCEINLINE void FromUUpSS()
	{
		MpHS = CS_UNREAL_UNITS_PER_SECOND_TO_MILES_PER_HOUR * UUpSS;
		KpHS = CS_UNREAL_UNITS_PER_SECOND_TO_KILOMETERS_PER_HOUR * UUpSS;
	}

	FORCEINLINE void FromMpHS()
	{
		UUpSS = CS_MILES_PER_HOUR_TO_UNREAL_UNITS_PER_SECOND * MpHS;
		KpHS = CS_MILES_PER_HOUR_TO_KILOMETERS_PER_HOUR * MpHS;
	}

	FORCEINLINE void FromKpHS()
	{
		UUpSS = CS_KILOMETERS_PER_HOUR_TO_UNREAL_UNITS_PER_SECOND * KpHS;
		MpHS = CS_KILOMETERS_PER_HOUR_TO_MILES_PER_HOUR * KpHS;
	}

#if WITH_EDITOR
	void OnPostEditChange(const FName& PropertyName);
#endif // #if WITH_EDITOR
};

#pragma endregion FCsAcceleration

// FCsSpeedInterp
#pragma region

class UCurveFloat;

/**
* Describes how speed should be interpolated.
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsSpeedInterp
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsSpeedInterpMethod Method;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsSpeedInterpDirection Direction;

	/** 
		 This is only Valid for Method == Easing (ECsSpeedInterpMethod::Easing). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsEasingType Easing;

	/**
		 This is only Valid for Method == Curve (ECsSpeedInterpMethod::Curve). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* Curve;

	/** Time (Duration) it should take to go from Min Speed to Max Speed. 
	     This is only Valid for Methods:
		   Easing	(ECsSpeedInterpMethod::Easing) 
		   Curve	(ECsSpeedInterpMethod::Curve) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Time;

	/** This is only Valid for Method == Acceleration (ECsSpeedInterpMethod::Acceleration). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsAcceleration Acceleration;

	FCsSpeedInterp() :
		Method(ECsSpeedInterpMethod::Acceleration),
		Direction(ECsSpeedInterpDirection::Increasing),
		Easing(ECsEasingType::Linear),
		Curve(nullptr),
		Acceleration()
	{
	}

	bool IsValidChecked() const;

#if WITH_EDITOR
	void OnPostEditChange(const TSet<FString>& PropertyNames, const FName& PropertyName);
#endif // #if WITH_EDITOR
};

#pragma endregion FCsSpeedInterp

// FCsSpeedInterpHelper
#pragma region

struct FCsSpeedInterp;

/**
*
*/
struct CSCORE_API FCsSpeedInterpHelper
{
public:

	/** Usually the same as MinSpeedAsPercent.
		[-1.0f, 1.0f] inclusive. */
	float MinBound;

	/** Usually 1.0f.
		[-1.0f, 1.0f] inclusive. */
	float MaxBound;

	/** Max Speed in UUpS (Unreal Units per Second). 
		This is considered be a value of 1.9f on a normalized scale. */
	float MaxSpeed;

	/** Minimum Speed in UUpS (Unreal Units per Second). */
	float MinSpeed;

	/** Minimum Speed as a percent. 
		 MinSpeed / MaxSpeed. 
		 [0.0f, 1.0f] inclusive. */
	float MinSpeedAsPercent;

	/** The desired speed to reach in UUpS (Unreal Units per Second). 
		Should be <= MaxSpeed. */
	float TargetSpeed;

	/** Target Speed as a percent. 
		 TargetSpeed / MaxSpeed. */
	float TargetSpeedAsPercent;

	/** Describes how to interpolate Speed over time. */
	FCsSpeedInterp* Interp;

	/** Sign 1 or -1 to indicate whether Speed is increasing (1) or 
	    decreasing (-1) to TargetSpeedAsPercent */
	float DirectionSign;

	/** Interp's Acceleration as a percent. 
		 Interp->Acceleration.UUpSS / MaxSpeed.
		 [0.0f , 1.0f] inclusive. 
		 Only Valid if Interp->Method == Acceleration (ECsSpeedInterpMethod::Acceleration) */
	float AccelerationAsPercent;

	float CurrentSpeedAsPercent;

	float CurrentAlpha;

	FCsSpeedInterpHelper() :
		MinBound(0.0f),
		MaxBound(1.0f),
		MaxSpeed(0.0f),
		MinSpeed(0.0f),
		MinSpeedAsPercent(0.0f),
		TargetSpeed(0.0f),
		TargetSpeedAsPercent(0.0f),
		Interp(nullptr),
		DirectionSign(1.0f),
		AccelerationAsPercent(0.0f),
		CurrentSpeedAsPercent(0.0f),
		CurrentAlpha(0.0f)
	{
	}

	void SetMinSpeed(const float& Speed);

	void SetTargetSpeed(const float& Speed);

	void SetTargetSpeedAsPercent(const float& Percent);

	void SetInterp(FCsSpeedInterp* InInterp);

	/**
	*
	*
	* @param Percent Value [0.0f, 1.0f] Inclusive.
	*/
	void SetCurrentSpeedAsPercent(const float& Percent);

	void Update(const float& DeltaTime);
};

#pragma endregion FCsSpeedInterpHelper