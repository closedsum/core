// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

#include "CsTypes_Math.generated.h"
#pragma once

// Math
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

UENUM(BlueprintType)
namespace ECsParametricFunctionType
{
	enum Type
	{
		Linear							UMETA(DisplayName = "Polynomial Degree 1"),
		Quadratic						UMETA(DisplayName = "Polynomial Degree 2"),
		Sine							UMETA(DisplayName = "Sine"),
		ECsParametricFunctionType_MAX	UMETA(Hidden),
	};
}

namespace ECsParametricFunctionType
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Linear = TCsString(TEXT("Linear"), TEXT("linear"));
		const TCsString Quadratic = TCsString(TEXT("Quadratic"), TEXT("quadratic"));
		const TCsString Sine = TCsString(TEXT("Sine"), TEXT("sine"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Linear) { return Str::Linear.Value; }
		if (EType == Type::Quadratic) { return Str::Quadratic.Value; }
		if (EType == Type::Sine) { return Str::Sine.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Linear) { return Type::Linear; }
		if (String == Str::Quadratic) { return Type::Quadratic; }
		if (String == Str::Sine) { return Type::Sine; }
		return Type::ECsParametricFunctionType_MAX;
	}
}

#define ECS_PARAMETRIC_FUNCTION_TYPE_MAX (uint8)ECsParametricFunctionType::ECsParametricFunctionType_MAX
typedef ECsParametricFunctionType::Type TCsParametricFunctionType;

USTRUCT(BlueprintType)
struct FCsParametricFunctionAxis
{
	GENERATED_USTRUCT_BODY()

	/** Types are Polynomial Degree 1 (Linear), Polynomial Degree 2 (Quadratic), Sine, ... etc */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	TEnumAsByte<ECsParametricFunctionType::Type> Function;

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

	FCsParametricFunction() {}
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

#pragma endregion Math