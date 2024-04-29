// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_Movement.generated.h"

// Mover
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsMover : uint8
{
	Actor			UMETA(DisplayName = "Actor"),
	Component		UMETA(DisplayName = "Component"),
	ECsMover_MAX	UMETA(Hidden),
};

struct CSTYPES_API EMCsMover : public TCsEnumMap<ECsMover>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsMover, ECsMover)
};

namespace NCsMover
{
	typedef ECsMover Type;

	namespace Ref
	{
		extern CSTYPES_API const Type Actor;
		extern CSTYPES_API const Type Component;
		extern CSTYPES_API const Type ECsMover_MAX;
	}

	extern CSTYPES_API const uint8 MAX;
}

namespace NCsMovement
{
	enum class EMover : uint8
	{
		Actor,
		Component,
		EMover_MAX
	};

	struct CSTYPES_API EMMover : public TCsEnumMap<EMover>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMMover, EMover)
	};

	namespace NMover
	{
		namespace Ref
		{
			typedef EMover Type;

			extern CSTYPES_API const Type Actor;
			extern CSTYPES_API const Type Component;
			extern CSTYPES_API const Type EMover_MAX;
		}
	}
}

#pragma endregion Mover

// MoveDestination
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsMoveDestination : uint8
{
	Location				UMETA(DisplayName = "Location"),
	Actor					UMETA(DisplayName = "Actor"),
	Component				UMETA(DisplayName = "Component"),
	Bone					UMETA(DisplayName = "Bone"),
	ECsMoveDestination_MAX	UMETA(Hidden),
};

struct CSTYPES_API EMCsMoveDestination : public TCsEnumMap<ECsMoveDestination>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsMoveDestination, ECsMoveDestination)
};

namespace NCsMoveDestination
{
	typedef ECsMoveDestination Type;

	namespace Ref
	{
		extern CSTYPES_API const Type Location;
		extern CSTYPES_API const Type Actor;
		extern CSTYPES_API const Type Component;
		extern CSTYPES_API const Type Bone;
		extern CSTYPES_API const Type ECsMoveDestination_MAX;
	}

	extern CSTYPES_API const uint8 MAX;
}

namespace NCsMovement
{
	enum class EDestination : uint8
	{
		Location,
		Actor,
		Component,
		Bone,
		EDestination_MAX
	};

	struct CSTYPES_API EMDestination : public TCsEnumMap<EDestination>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMDestination, EDestination)
	};

	namespace NDestination
	{
		namespace Ref
		{
			typedef EDestination Type;

			extern CSTYPES_API const Type Location;
			extern CSTYPES_API const Type Actor;
			extern CSTYPES_API const Type Component;
			extern CSTYPES_API const Type Bone;
			extern CSTYPES_API const Type EDestination_MAX;
		}
	}
}

#pragma endregion MoveDestination

// SpeedFormat
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsSpeedFormat : uint8
{
	UUpS				UMETA(DisplayName = "Unreal Units per Second"),
	MpH					UMETA(DisplayName = "Miles per Hour"),
	KpH					UMETA(DisplayName = "Kilometers per Hour"),
	ECsSpeedFormat_MAX	UMETA(Hidden),
};

struct CSTYPES_API EMCsSpeedFormat final : public TCsEnumMap<ECsSpeedFormat>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSpeedFormat, ECsSpeedFormat)
};

namespace NCsSpeedFormat
{
	typedef ECsSpeedFormat Type;

	namespace Ref
	{
		extern CSTYPES_API const Type UUpS;
		extern CSTYPES_API const Type MpH;
		extern CSTYPES_API const Type KpH;
		extern CSTYPES_API const Type ECsSpeedFormat_MAX;
	}

	extern CSTYPES_API const uint8 MAX;
}

namespace NCsSpeed
{
	enum class EFormat : uint8 
	{
		// Unreal Units per Second
		UUpS,
		// Miles per Hour
		MpH,
		// Kilometers per Hour
		KpH,
		EFormat_MAX
	};

	struct CSTYPES_API EMFormat final : public TCsEnumMap<EFormat>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMFormat, EFormat)
	};

	namespace NFormat
	{
		typedef EFormat Type;

		extern CSTYPES_API const Type UUpS;
		extern CSTYPES_API const Type MpH;
		extern CSTYPES_API const Type KpH;
		extern CSTYPES_API const Type EFormat_MAX;
	}
}

#pragma endregion SpeedFormat

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
struct CSTYPES_API FCsSpeed
{
	GENERATED_USTRUCT_BODY()

	/** UUpS: Unreal Units per Second */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement", meta = (DisplayName = "UUpS: Unreal Units per Second", ClampMin = "0.0", UIMin = "0.0"))
	float UUpS;

	/** MpH: Miles per Hour */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement", meta = (DisplayName = "MpH: Miles per Hour", ClampMin = "0.0", UIMin = "0.0"))
	float MpH;

	/** KpH: Kilometers per Hour */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement", meta = (DisplayName = "KpH: Kilometers per Hour", ClampMin = "0.0", UIMin = "0.0"))
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

	FORCEINLINE FString ToString() const { return FString::Printf(TEXT("%f UUpS %f MpH %f KpH"), UUpS, MpH, KpH); }

#if WITH_EDITOR
	void OnPostEditChange(const FName& PropertyName);
#endif // #if WITH_EDITOR

private:

	FORCEINLINE void __Nothing() const {}
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
	Acceleration				UMETA(DisplayName = "Acceleration"),
	/** Using a Duration and Easing Type, determine the Speed. */
	Easing						UMETA(DisplayName = "Easing"),
	/** Using a Duration and Curve, determine the Speed. */
	Curve						UMETA(DisplayName = "Curve"),
	ECsSpeedInterpMethod_MAX	UMETA(Hidden),
};

struct CSTYPES_API EMCsSpeedInterpMethod final : public TCsEnumMap<ECsSpeedInterpMethod>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSpeedInterpMethod, ECsSpeedInterpMethod)
};

namespace NCsSpeedInterpMethod
{
	typedef ECsSpeedInterpMethod Type;

	namespace Ref
	{
		extern CSTYPES_API const Type Acceleration;
		extern CSTYPES_API const Type Easing;
		extern CSTYPES_API const Type Curve;
		extern CSTYPES_API const Type ECsSpeedInterpMethod_MAX;
	}

	extern CSTYPES_API const uint8 MAX;
}

namespace NCsSpeed
{
	namespace NInterp
	{
		enum class EMethod : uint8
		{
			/** Apply the Acceleration as a Delta.
			 Usually in the form of sf = so + a * dt.
			  sf = Final Speed
			  so = Initial Speed
			  a = Acceleration
			  dt = Delta Time */
			Acceleration,
			/** Using a Duration and Easing Type, determine the Speed. */
			Easing,
			/** Using a Duration and Curve, determine the Speed. */
			Curve,
			EMethod_MAX
		};

		struct CSTYPES_API EMMethod final : public TCsEnumMap<EMethod>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMMethod, EMethod)
		};

		namespace NMethod
		{
			typedef EMethod Type;

			extern CSTYPES_API const Type Acceleration;
			extern CSTYPES_API const Type Easing;
			extern CSTYPES_API const Type Curve;
			extern CSTYPES_API const Type EMethod_MAX;
		}
	}
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

struct CSTYPES_API EMCsSpeedInterpDirection final : public TCsEnumMap<ECsSpeedInterpDirection>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSpeedInterpDirection, ECsSpeedInterpDirection)
};

namespace NCsSpeedInterpDirection
{
	typedef ECsSpeedInterpDirection Type;

	namespace Ref
	{
		extern CSTYPES_API const Type Increasing;
		extern CSTYPES_API const Type Decreasing;
		extern CSTYPES_API const Type ECsSpeedInterpDirection_MAX;
	}

	extern CSTYPES_API const uint8 MAX;
}

namespace NCsSpeed
{
	namespace NInterp
	{
		enum class EDirection : uint8 
		{
			/** Increasing toward the Target Speed. */
			Increasing,
			/** Decreasing toward the Target Speed. */
			Decreasing,
			EDirection_MAX
		};

		struct CSTYPES_API EMDirection final : public TCsEnumMap<EDirection>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMDirection, EDirection)
		};

		namespace NDirection
		{
			typedef EDirection Type;

			extern CSTYPES_API const Type Increasing;
			extern CSTYPES_API const Type Decreasing;
			extern CSTYPES_API const Type EDirection_MAX;
		}
	}
}

#pragma endregion SpeedInterpDirection

// FCsAcceleration
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSTYPES_API FCsAcceleration
{
	GENERATED_USTRUCT_BODY()

	/** UUpS/S: Unreal Units per Second Second. 
		 This is only Valid for Method == Delta (ECsAccelerationMethod::Delta). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement", meta = (DisplayName = "UUpS/S: Unreal Units per Second Second", ClampMin = "0.0", UIMin = "0.0"))
	float UUpSS;
	 
	/** MpH/S: Miles per Hour Second Second.
		 This is only Valid for Method == Delta (ECsAccelerationMethod::Delta). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement", meta = (DisplayName = "MpH/S: Miles per Hour Second", ClampMin = "0.0", UIMin = "0.0"))
	float MpHS;

	/** KpH/S: Kilometers per Hour Second.
		 This is only Valid for Method == Delta (ECsAccelerationMethod::Delta). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement", meta = (DisplayName = "KpH/S: Kilometers per Hour Second", ClampMin = "0.0", UIMin = "0.0"))
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

	FORCEINLINE FString ToString() const { return FString::Printf(TEXT("%f UUpSS %f MpHS %f KpHS"), UUpSS, MpHS, KpHS); }

#if WITH_EDITOR
	void OnPostEditChange(const FName& PropertyName);
#endif // #if WITH_EDITOR
};

#pragma endregion FCsAcceleration