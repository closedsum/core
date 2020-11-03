// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumMap.h"
#include "Types/Enum/CsEnumFlagMap.h"

#include "CsTypes_Math.generated.h"
#pragma once

// FCsRadius
#pragma region

USTRUCT(BlueprintType)
struct FCsRadius
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radius", meta = (ClampMin = "0", UIMin = "0"))
	float Radius;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Radius")
	float RadiusSq;

	FCsRadius()
	{
		Reset();
	}

	FCsRadius& operator=(const FCsRadius& B)
	{
		Radius = B.Radius;
		RadiusSq = B.RadiusSq;
		return *this;
	}

	bool operator==(const FCsRadius& B) const
	{
		return Radius == B.Radius && RadiusSq == B.RadiusSq;
	}

	bool operator!=(const FCsRadius& B) const
	{
		return !(*this == B);
	}

	void Square()
	{
		RadiusSq = Radius * Radius;
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("Radius=%3.3f"), Radius);
	}

	bool InitFromString(const FString& InSourceString)
	{
		Radius = 0.0f;

		// The initialization is only successful if the Radius values can all be parsed from the string
		const bool bSuccessful = FParse::Value(*InSourceString, TEXT("Radius="), Radius);

		Square();

		return bSuccessful;
	}

	void Reset()
	{
		Radius = 0.0f;
		Square();
	}
};

// PostEditChangeProperty FCsRadius
#define CS_PECP_FCS_RADIUS(PropertyName, MemberName)	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsRadius, Radius)) \
														{ \
															MemberName.Square(); \
														}

#pragma endregion FCsRadius

// ParametricFunctionType
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsParametricFunctionType : uint8
{
	Linear							UMETA(DisplayName = "Polynomial Degree 1"),
	Quadratic						UMETA(DisplayName = "Polynomial Degree 2"),
	Sine							UMETA(DisplayName = "Sine"),
	ECsParametricFunctionType_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsParametricFunctionType final : public TCsEnumMap<ECsParametricFunctionType>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsParametricFunctionType, ECsParametricFunctionType)
};

namespace NCsParametricFunctionType
{
	typedef ECsParametricFunctionType Type;

	namespace Ref
	{
		extern CSCORE_API const Type Linear;
		extern CSCORE_API const Type Quadratic;
		extern CSCORE_API const Type Sine;
		extern CSCORE_API const Type ECsParametricFunctionType_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion ParametricFunctionType

// FCsParametricFunctionAxis
#pragma region

USTRUCT(BlueprintType)
struct FCsParametricFunctionAxis
{
	GENERATED_USTRUCT_BODY()

	/** Types are Polynomial Degree 1 (Linear), Polynomial Degree 2 (Quadratic), Sine, ... etc */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	ECsParametricFunctionType Function;

	/** "Axis" F(T) = A * T + B
	 *  "Axis" F(T) = A * T^2 + B * T + C
	 *  "Axis" F(T) = A * sin(B * T + C) + D
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	float A;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function", meta = (InlineEditConditionToggle))
	bool bIntervalA;
	UPROPERTY(EditAnywhere, Category = "Function", meta = (editcondition = "bIntervalA"))
	FFloatInterval IntervalA;

	/** "Axis" F(T) = A * T + B
	 *  "Axis" F(T) = A * T^2 + B * T + C
	 *  "Axis" F(T) = A * sin(B * T + C) + D
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	float B;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function", meta = (InlineEditConditionToggle))
	bool bIntervalB;
	UPROPERTY(EditAnywhere, Category = "Function", meta = (editcondition = "bIntervalB"))
	FFloatInterval IntervalB;

	/** "Axis" F(T) = A * T + B
	 *  "Axis" F(T) = A * T^2 + B * T + C
	 *  "Axis" F(T) = A * sin(B * T + C) + D
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	float C;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function", meta = (InlineEditConditionToggle))
	bool bIntervalC;
	UPROPERTY(EditAnywhere, Category = "Function", meta = (editcondition = "bIntervalC"))
	FFloatInterval IntervalC;

	/** "Axis" F(T) = A * T + B
	 *  "Axis" F(T) = A * T^2 + B * T + C
	 *  "Axis" F(T) = A * sin(B * T + C) + D
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	float D;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function", meta = (InlineEditConditionToggle))
	bool bIntervalD;
	UPROPERTY(EditAnywhere, Category = "Function", meta = (editcondition = "bIntervalD"))
	FFloatInterval IntervalD;

	FCsParametricFunctionAxis()
	{
		Function = ECsParametricFunctionType::Linear;
		A = 1.0f;
		bIntervalA = false;
		IntervalA.Min = 0.0f;
		IntervalA.Max = 0.0f;
		B = 1.0f;
		bIntervalB = false;
		IntervalB.Min = 0.0f;
		IntervalB.Max = 0.0f;
		C = 0.0f;
		bIntervalC = false;
		IntervalC.Min = 0.0f;
		IntervalC.Max = 0.0f;
		D = 0.0f;
		bIntervalD = false;
		IntervalD.Min = 0.0f;
		IntervalD.Max = 0.0f;
	}

	~FCsParametricFunctionAxis() {}

	FCsParametricFunctionAxis& operator=(const FCsParametricFunctionAxis& Axis)
	{
		Function = Axis.Function;
		A = Axis.A;
		bIntervalA = Axis.bIntervalA;
		IntervalA.Min = Axis.IntervalA.Min;
		IntervalA.Max = Axis.IntervalA.Max;
		B = Axis.B;
		bIntervalB = Axis.bIntervalB;
		IntervalB.Min = Axis.IntervalB.Min;
		IntervalB.Max = Axis.IntervalB.Max;
		C = Axis.C;
		bIntervalC = Axis.bIntervalC;
		IntervalC.Min = Axis.IntervalC.Min;
		IntervalC.Max = Axis.IntervalC.Max;
		D = Axis.D;
		bIntervalD = Axis.bIntervalD;
		IntervalD.Min = Axis.IntervalD.Min;
		IntervalD.Max = Axis.IntervalD.Max;
		return *this;
	}

	bool operator==(const FCsParametricFunctionAxis& Axis) const
	{
		return	Function == Axis.Function &&
				A == Axis.A &&
				B == Axis.B &&
				C == Axis.C &&
				D == Axis.D;
	}

	bool operator!=(const FCsParametricFunctionAxis& Axis) const
	{
		return !(*this == Axis);
	}

	void Seed()
	{
		A = bIntervalA ? FMath::RandRange(IntervalA.Min, IntervalA.Max) : A;
		B = bIntervalB ? FMath::RandRange(IntervalB.Min, IntervalB.Max) : B;
		C = bIntervalC ? FMath::RandRange(IntervalC.Min, IntervalC.Max) : C;
		D = bIntervalD ? FMath::RandRange(IntervalD.Min, IntervalD.Max) : D;
	}

	float Evaluate(const float &T)
	{
		// Linear
		if (Function == ECsParametricFunctionType::Linear)
			return A * T + B;
		// Quadratic
		if (Function == ECsParametricFunctionType::Quadratic)
			return (A * T * T) + (B * T) + C;
		// Sine
		if (Function == ECsParametricFunctionType::Sine)
			return A * FMath::Sin(B * T + C) + D;
		return 0.0f;
	}
};

#pragma endregion FCsParametricFunctionAxis

// FCsParametricFunction
#pragma region

USTRUCT(BlueprintType)
struct FCsParametricFunction
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function", meta = (InlineEditConditionToggle))
	bool bX;
	/** X = A * T + B
	 *  X = A * T^2 + B * T + C
	 *  X = A * sin(B * T + C) + D
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function", meta = (editcondition = "bX"))
	FCsParametricFunctionAxis X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function", meta = (InlineEditConditionToggle))
	bool bY;
	/** Y = A * T + B
	 *  Y = A * T^2 + B * T + C
	 *  Y = A * sin(B * T + C) + D
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function", meta = (editcondition = "bY"))
	FCsParametricFunctionAxis Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function", meta = (InlineEditConditionToggle))
	bool bZ;
	/** Z = A * T + B
	 *  Z = A * T^2 + B * T + C
	 *  Z = A * sin(B * T + C) + D
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function", meta = (editcondition = "bZ"))
	FCsParametricFunctionAxis Z;

	FCsParametricFunction() :
		bX(false),
		X(),
		bY(false),
		Y(),
		bZ(false),
		Z()
	{
	}

	~FCsParametricFunction() {}

	FCsParametricFunction& operator=(const FCsParametricFunction& B)
	{
		bX = B.bX;
		X = B.X;
		bY = B.bY;
		Y = B.Y;
		bZ = B.bZ;
		Z = B.Z;
		return *this;
	}

	bool operator==(const FCsParametricFunction& B) const
	{
		return	bX == B.bX && X == B.X && bY == B.bY && Y == B.Y && bZ == B.bZ && Z == B.Z;
	}

	bool operator!=(const FCsParametricFunction& B) const
	{
		return !(*this == B);
	}

	void Seed()
	{
		X.Seed();
		Y.Seed();
		Z.Seed();
	}

	FVector Evaluate(const float &T)
	{
		return FVector(bX ? X.Evaluate(T) : 0.0f, bY ? Y.Evaluate(T) : 0.0f, bZ ? Z.Evaluate(T) : 0.0f);
	}

	FVector Evaluate(const float &Time, const FVector &Location, const FTransform &Transform)
	{
		FVector Point = Location;

		if (bX)
			Point.X += X.Evaluate(Time);
		if (bY)
			Point.Y += Y.Evaluate(Time);
		if (bZ)
			Point.Z += Z.Evaluate(Time);

		FTransform LocalTransform = FTransform::Identity;
		LocalTransform.SetTranslation(Point);
		const FTransform WorldTransform = LocalTransform * Transform;

		return WorldTransform.GetTranslation();
	}
};

#pragma endregion FCsParametricFunction

// RotationRules
#pragma region

/**
*/
UENUM(BlueprintType, meta = (Bitflags))
enum class ECsRotationRules : uint8
{
	Pitch		UMETA(DisplayName = "Pitch"),	// 0
	Yaw			UMETA(DisplayName = "Yaw"),		// 1
	Roll		UMETA(DisplayName = "Roll"),	// 2
};

struct CSCORE_API EMCsRotationRules : public TCsEnumFlagMap<ECsRotationRules>
{
	CS_ENUM_FLAG_MAP_BODY(EMCsRotationRules, ECsRotationRules)
};

class AActor;
class USceneComponent;
class USkeletalMeshComponent;

namespace NCsRotationRules
{
	typedef ECsRotationRules Type;

	namespace Ref
	{
		extern CSCORE_API const Type Pitch;
		extern CSCORE_API const Type Yaw;
		extern CSCORE_API const Type Roll;
	}

	extern CSCORE_API const int32 None;
	extern CSCORE_API const int32 All;

	/**
	* Get the Rotation filtered by the bit mask, Rules.
	*
	* @param Rotation
	* @param Rules		 Bit mask for which components of the Rotation to return.
	*
	* return			Rotation filtered by the bit mask, Rules.
	*/
	CSCORE_API FRotator GetRotation(FRotator Rotation, const int32& Rules);

	/**
	* Get the Rotation filtered by the bit mask, Rules.
	* Check Rules has at least 1 bit flag set.
	* 
	* @param Rotation
	* @param Rules		 Bit mask for which components of the Rotation to return.
	*
	* return			Rotation filtered by the bit mask, Rules.
	*/
	CSCORE_API FRotator GetRotationChecked(const FString& Context, FRotator Rotation, const int32& Rules);

	/**
	* Get the rotation of Actor filtered by the bit mask, Rules. 
	*
	* @param Actor
	* @param Rules	Bit mask for which components of the Actor's rotation to return.
	*
	* return		Actor's rotation filtered by the bit mask, Rules. 
	*/
	CSCORE_API FRotator GetRotation(AActor* Actor, const int32& Rules);

	/**
	* Get the rotation of Component filtered by the bit mask, Rules.
	*
	* @param Component
	* @param Rules		Bit mask for which components of the Component's rotation to return.
	*
	* return			Component's rotation filtered by the bit mask, Rules.
	*/
	CSCORE_API FRotator GetRotation(USceneComponent* Component, const int32& Rules);
}

#define CS_ROTATION_FLAGS_NONE 0
#define CS_ROTATION_FLAGS_PITCH 1
#define CS_ROTATION_FLAGS_YAW 2
#define CS_ROTATION_FLAGS_ROLL 4
#define CS_ROTATION_FLAGS_PITCH_AND_YAW 3

#pragma endregion RotationRules

// TransformRules
#pragma region

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsTransformRules : uint8
{
	Location	UMETA(DisplayName = "Location"),	// 0
	Rotation	UMETA(DisplayName = "Rotation"),	// 1
	Scale		UMETA(DisplayName = "Scale"),		// 2
};

struct CSCORE_API EMCsTransformRules : public TCsEnumFlagMap<ECsTransformRules>
{
	CS_ENUM_FLAG_MAP_BODY(EMCsTransformRules, ECsTransformRules)
};

class AActor;

namespace NCsTransformRules
{
	typedef ECsTransformRules Type;

	namespace Ref
	{
		extern CSCORE_API const Type Location;
		extern CSCORE_API const Type Rotation;
		extern CSCORE_API const Type Scale;
	}

	extern CSCORE_API const int32 None;
	extern CSCORE_API const int32 All;

	/**
	* Set the relative transform of an Actor to Transform based on some Rules,
	* which determine which component of the Transform to use.
	* See ECsTransformRules. 
	* 
	* @param Actor
	* @param Transform
	* @param Rules		Bit mask using the bit flag ECsTransformRules.
	*/
	CSCORE_API void SetRelativeTransform(AActor* Actor, const FTransform& Transform, const int32& Rules);

	/**
	* Set the transform of an Actor to Transform based on some Rules,
	* which determine which component of the Transform to use.
	* See ECsTransformRules.
	*
	* @param Actor
	* @param Transform
	* @param Rules		Bit mask using the bit flag ECsTransformRules.
	*/
	CSCORE_API void SetTransform(AActor* Actor, const FTransform& Transform, const int32& Rules);
}

#define CS_TRANSFORM_FLAGS_NONE 0

#pragma endregion TransformRules

// FCsOptionalVectorInterval
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsOptionalVectorInterval
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector")
	FVector Vector; // 3 x 64 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector", meta = (InlineEditConditionToggle))
	bool bIntervalX; // 1 bit

	UPROPERTY(EditAnywhere, Category = "Vector", meta = (editcondition = "bIntervalX"))
	FFloatInterval IntervalX; // 2 x 16 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector", meta = (InlineEditConditionToggle))
	bool bIntervalY; // 1 bit

	UPROPERTY(EditAnywhere, Category = "Vector", meta = (editcondition = "bIntervalX"))
	FFloatInterval IntervalY; // 2 x 16 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector", meta = (InlineEditConditionToggle))
	bool bIntervalZ;

	UPROPERTY(EditAnywhere, Category = "Vector", meta = (editcondition = "bIntervalX"))
	FFloatInterval IntervalZ;

	FCsOptionalVectorInterval()
	{
		Reset();
	}

	FORCEINLINE bool operator==(const FCsOptionalVectorInterval& B) const
	{
		return	Vector == B.Vector && 
				bIntervalX == B.bIntervalX && 
				IntervalX.Min == B.IntervalX.Min &&
				IntervalX.Max == B.IntervalX.Max &&
				bIntervalY == B.bIntervalY &&
				IntervalY.Min == B.IntervalY.Min &&
				IntervalY.Max == B.IntervalY.Max &&
				bIntervalZ == B.bIntervalZ &&
				IntervalZ.Min == B.IntervalZ.Min &&
				IntervalZ.Max == B.IntervalZ.Max;
	}

	FORCEINLINE bool operator!=(const FCsOptionalVectorInterval& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
	{
		Vector = FVector::ZeroVector;
		// X
		bIntervalX = false;
		IntervalX.Min = 0.0f;
		IntervalX.Max = 0.0f;
		// Y
		bIntervalY = false;
		IntervalY.Min = 0.0f;
		IntervalY.Max = 0.0f;
		// Z
		bIntervalZ = false;
		IntervalZ.Min = 0.0f;
		IntervalZ.Max = 0.0f;
	}

	FORCEINLINE uint32 GetBits() const
	{
		return  (3 * 64) // Vector
			   + 1 // bIntervalX
			   + (2 * 64) // IntervalX
			   + 1 // bIntervalY
			   + (2 * 64) // IntervalY
			   + 1 // bIntervalZ
			   + (2 * 64); // IntervalZ
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}

	void Seed()
	{
		Vector.X = bIntervalX ? FMath::RandRange(IntervalX.Min, IntervalX.Max) : Vector.X;
		Vector.Y = bIntervalY ? FMath::RandRange(IntervalY.Min, IntervalY.Max) : Vector.Y;
		Vector.Z = bIntervalZ ? FMath::RandRange(IntervalZ.Min, IntervalZ.Max) : Vector.Z;
	}

	FORCEINLINE const FVector& Get()
	{
		return Vector;
	}
};

#pragma endregion FCsOptionalVectorInterval

// FCsOptionalRotatorInterval
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsOptionalRotatorInterval
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator")
	FRotator Rotator; // 3 x 64 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator", meta = (InlineEditConditionToggle))
	bool bIntervalRoll; // 1 bit

	UPROPERTY(EditAnywhere, Category = "Rotator", meta = (editcondition = "bIntervalRoll"))
	FFloatInterval IntervalRoll; // 2 x 16 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator", meta = (InlineEditConditionToggle))
	bool bIntervalPitch; // 1 bit

	UPROPERTY(EditAnywhere, Category = "Rotator", meta = (editcondition = "bIntervalPitch"))
	FFloatInterval IntervalPitch; // 2 x 16 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator", meta = (InlineEditConditionToggle))
	bool bIntervalYaw;

	UPROPERTY(EditAnywhere, Category = "Rotator", meta = (editcondition = "bIntervalYaw"))
	FFloatInterval IntervalYaw;

	FCsOptionalRotatorInterval()
	{
		Reset();
	}

	FORCEINLINE bool operator==(const FCsOptionalRotatorInterval& B) const
	{
		return	Rotator == B.Rotator &&
				bIntervalRoll == B.bIntervalRoll &&
				IntervalRoll.Min == B.IntervalRoll.Min &&
				IntervalRoll.Max == B.IntervalRoll.Max &&
				bIntervalPitch == B.bIntervalPitch &&
				IntervalPitch.Min == B.IntervalPitch.Min &&
				IntervalPitch.Max == B.IntervalPitch.Max &&
				bIntervalYaw == B.bIntervalYaw &&
				IntervalYaw.Min == B.IntervalYaw.Min &&
				IntervalYaw.Max == B.IntervalYaw.Max;
	}

	FORCEINLINE bool operator!=(const FCsOptionalRotatorInterval& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
	{
		Rotator = FRotator::ZeroRotator;
		// Roll
		bIntervalRoll = false;
		IntervalRoll.Min = 0.0f;
		IntervalRoll.Max = 0.0f;
		// Pitch
		bIntervalPitch = false;
		IntervalPitch.Min = 0.0f;
		IntervalPitch.Max = 0.0f;
		// Yaw
		bIntervalYaw = false;
		IntervalYaw.Min = 0.0f;
		IntervalYaw.Max = 0.0f;
	}

	FORCEINLINE uint32 GetBits() const
	{
		return  (3 * 64) // Rotator
				+ 1 // bIntervalRoll
				+ (2 * 64) // IntervalRoll
				+ 1 // bIntervalPitch
				+ (2 * 64) // IntervalPitch
				+ 1 // bIntervalYaw
				+ (2 * 64); // IntervalYaw
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}

	void Seed()
	{
		Rotator.Roll = bIntervalRoll ? FMath::RandRange(IntervalRoll.Min, IntervalRoll.Max) : Rotator.Roll;
		Rotator.Pitch = bIntervalPitch ? FMath::RandRange(IntervalPitch.Min, IntervalPitch.Max) : Rotator.Pitch;
		Rotator.Yaw = bIntervalYaw ? FMath::RandRange(IntervalYaw.Min, IntervalYaw.Max) : Rotator.Yaw;
	}

	FORCEINLINE const FRotator& Get()
	{
		return Rotator;
	}
};

#pragma endregion FCsOptionalRotatorInterval