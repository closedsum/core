// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

#include "CsTypes_Math.generated.h"
#pragma once

// Math
#pragma region

UENUM(BlueprintType)
namespace ECsParametricMovementFunctionType
{
	enum Type
	{
		Linear									UMETA(DisplayName = "Polynomial Degree 1"),
		Quadratic								UMETA(DisplayName = "Polynomial Degree 2"),
		Sine									UMETA(DisplayName = "Sine"),
		ECsParametricMovementFunctionType_MAX	UMETA(Hidden),
	};
}

namespace ECsParametricMovementFunctionType
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
		return Type::ECsParametricMovementFunctionType_MAX;
	}
}

#define ECS_PARAMETRIC_MOVEMENT_FUNCTION_TYPE_MAX (uint8)ECsParametricMovementFunctionType::ECsParametricMovementFunctionType_MAX
typedef ECsParametricMovementFunctionType::Type TCsParametricMovementFunctionType;

USTRUCT(BlueprintType)
struct FCsParametricMovementFunctionAxis
{
	GENERATED_USTRUCT_BODY()

	/** Types are Polynomial Degree 1 (Linear), Polynomial Degree 2 (Quadtratic), Sine, ... etc */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	TEnumAsByte<ECsParametricMovementFunctionType::Type> Function;

	/** "Axis" F(T) = A * T + B
	 *  "Axis" F(T) = A * T^2 + B * T + C
	 *  "Axis" F(T) = A * sin(B * T + C) + D
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	float A;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function", meta = (InlineEditConditionToggle))
	bool bIntervalA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function", meta = (editcondition = "bIntervalA"))
	FFloatInterval IntervalA;

	/** "Axis" F(T) = A * T + B
	 *  "Axis" F(T) = A * T^2 + B * T + C
	 *  "Axis" F(T) = A * sin(B * T + C) + D
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	float B;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function", meta = (InlineEditConditionToggle))
	bool bIntervalB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function", meta = (editcondition = "bIntervalB"))
	FFloatInterval IntervalB;

	/** "Axis" F(T) = A * T + B
	 *  "Axis" F(T) = A * T^2 + B * T + C
	 *  "Axis" F(T) = A * sin(B * T + C) + D
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	float C;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function", meta = (InlineEditConditionToggle))
	bool bIntervalC;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function", meta = (editcondition = "bIntervalC"))
	FFloatInterval IntervalC;

	/** "Axis" F(T) = A * T + B
	 *  "Axis" F(T) = A * T^2 + B * T + C
	 *  "Axis" F(T) = A * sin(B * T + C) + D
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	float D;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function", meta = (InlineEditConditionToggle))
	bool bIntervalD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function", meta = (editcondition = "bIntervalD"))
	FFloatInterval IntervalD;

	FCsParametricMovementFunctionAxis()
	{
		IsActive = true;
		Function = ECsParametricMovementFunctionType::Linear;
		A = 1.0f;
		bIntervalA = false;
		IntervalA.Min = 0.0f;
		IntervalA.Max = 0.0f;
		B = 1.0f;
		C = 1.0f;
		D = 0.0f;
	}

	~FCsProjectileMovementFunctionAxis() {}

	FCsProjectileMovementFunctionAxis& operator=(const FCsProjectileMovementFunctionAxis& D)
	{
		IsActive = D.IsActive;
		Function = D.Function;
		A = D.A;
		B = D.B;
		N = D.N;
		C = D.C;
		return *this;
	}

	bool operator==(const FCsProjectileMovementFunctionAxis& D) const
	{
		return	IsActive == D.IsActive &&
			Function == D.Function &&
			A == D.A &&
			B == D.B &&
			N == D.N &&
			C == D.C;
	}

	bool operator!=(const FCsProjectileMovementFunctionAxis& D) const
	{
		return !(*this == D);
	}

	float Evaluate(const float &T)
	{
		if (!IsActive)
			return 0.0f;
		// A * (B*T)^N + C
		if (Function == ECsProjectileMovementFunctionType::Linear)
			return A * FMath::Pow(B * T, N) + C;
		// A * sin((B*T)^N) + C
		if (Function == ECsProjectileMovementFunctionType::Sine)
			return A * FMath::Sin(FMath::Pow(B * T, N)) + C;
		return 0.0f;
	}
};

USTRUCT(BlueprintType)
struct FCsProjectileMovementFunction
{
	GENERATED_USTRUCT_BODY()

		/** X = A * ((B*G(t))^N) + C. G(t) = t, sin(t), ... etc. */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
		FCsProjectileMovementFunctionAxis X;
	/** Y = A * ((B*G(t))^N) + C. G(t) = t, sin(t), ... etc. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
		FCsProjectileMovementFunctionAxis Y;
	/** Z = A * ((B*G(t))^N) + C. G(t) = t, sin(t), ... etc. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
		FCsProjectileMovementFunctionAxis Z;

	FCsProjectileMovementFunction() {}
	~FCsProjectileMovementFunction() {}

	FCsProjectileMovementFunction& operator=(const FCsProjectileMovementFunction& B)
	{
		X = B.X;
		Y = B.Y;
		Z = B.Z;
		return *this;
	}

	bool operator==(const FCsProjectileMovementFunction& B) const
	{
		return	X == B.X && Y == B.Y && Z == B.Z;
	}

	bool operator!=(const FCsProjectileMovementFunction& B) const
	{
		return !(*this == B);
	}

	FVector Evaluate(const float &T)
	{
		return FVector(X.Evaluate(T), Y.Evaluate(T), Z.Evaluate(T));
	}

	FVector Evaluate(const float &Time, const FVector &Location, const FTransform &Transform)
	{
		FVector Point = Evaluate(Time);

		// Override the Components that are NOT Active
		if (!X.IsActive)
			Point.X += Location.X;
		if (!Y.IsActive)
			Point.Y += Location.Y;
		if (!Z.IsActive)
			Point.Z += Location.Z;

		FTransform LocalTransform = FTransform::Identity;
		LocalTransform.SetTranslation(Point);
		const FTransform WorldTransform = LocalTransform * Transform;

		return WorldTransform.GetTranslation();
	}
};

#pragma endregion Math