// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"
#include "Types/Enum/CsEnumFlagMap.h"
#include "Types/Enum/CsEnumMaskMap.h"
// Log
#include "Utility/CsLog.h"

#include "CsTypes_Math.generated.h"

// FCsRadius
#pragma region

USTRUCT(BlueprintType)
struct FCsRadius
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (ClampMin = "0", UIMin = "0"))
	float Radius;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Math")
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math")
	ECsParametricFunctionType Function;

	/** "Axis" F(T) = A * T + B
	 *  "Axis" F(T) = A * T^2 + B * T + C
	 *  "Axis" F(T) = A * sin(B * T + C) + D
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math")
	float A;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (InlineEditConditionToggle))
	bool bIntervalA;
	UPROPERTY(EditAnywhere, Category = "CsCore|Math", meta = (editcondition = "bIntervalA"))
	FFloatInterval IntervalA;

	/** "Axis" F(T) = A * T + B
	 *  "Axis" F(T) = A * T^2 + B * T + C
	 *  "Axis" F(T) = A * sin(B * T + C) + D
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math")
	float B;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (InlineEditConditionToggle))
	bool bIntervalB;
	UPROPERTY(EditAnywhere, Category = "CsCore|Math", meta = (editcondition = "bIntervalB"))
	FFloatInterval IntervalB;

	/** "Axis" F(T) = A * T + B
	 *  "Axis" F(T) = A * T^2 + B * T + C
	 *  "Axis" F(T) = A * sin(B * T + C) + D
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math")
	float C;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (InlineEditConditionToggle))
	bool bIntervalC;
	UPROPERTY(EditAnywhere, Category = "CsCore|Math", meta = (editcondition = "bIntervalC"))
	FFloatInterval IntervalC;

	/** "Axis" F(T) = A * T + B
	 *  "Axis" F(T) = A * T^2 + B * T + C
	 *  "Axis" F(T) = A * sin(B * T + C) + D
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math")
	float D;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (InlineEditConditionToggle))
	bool bIntervalD;
	UPROPERTY(EditAnywhere, Category = "CsCore|Math", meta = (editcondition = "bIntervalD"))
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (ScriptName = "m_bX", InlineEditConditionToggle))
	bool bX;
	/** X = A * T + B
	 *  X = A * T^2 + B * T + C
	 *  X = A * sin(B * T + C) + D
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (ScriptName = "m_X", editcondition = "bX"))
	FCsParametricFunctionAxis X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (ScriptName = "m_bY", InlineEditConditionToggle))
	bool bY;
	/** Y = A * T + B
	 *  Y = A * T^2 + B * T + C
	 *  Y = A * sin(B * T + C) + D
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (ScriptName = "m_Y", editcondition = "bY"))
	FCsParametricFunctionAxis Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (ScriptName = "m_bZ", InlineEditConditionToggle))
	bool bZ;
	/** Z = A * T + B
	 *  Z = A * T^2 + B * T + C
	 *  Z = A * sin(B * T + C) + D
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (ScriptName = "m_Z", editcondition = "bZ"))
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
	FORCEINLINE FRotator GetRotation(FRotator Rotation, const int32& Rules)
	{
		Rotation.Pitch = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Pitch) ? Rotation.Pitch : 0.0f;
		Rotation.Yaw   = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Yaw) ? Rotation.Yaw : 0.0f;
		Rotation.Roll  = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Roll) ? Rotation.Roll : 0.0f;

		return Rotation;
	}

	/**
	* Get the Rotation filtered by the bit mask, Rules.
	* Check Rules has at least 1 bit flag set.
	* 
	* @param Rotation
	* @param Rules		 Bit mask for which components of the Rotation to return.
	*
	* return			Rotation filtered by the bit mask, Rules.
	*/
	FORCEINLINE FRotator GetRotationChecked(const FString& Context, FRotator Rotation, const int32& Rules)
	{
		checkf(Rules != None, TEXT("%s: Rules == 0. No bit flags set."), *Context);

		Rotation.Pitch = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Pitch) ? Rotation.Pitch : 0.0f;
		Rotation.Yaw   = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Yaw) ? Rotation.Yaw : 0.0f;
		Rotation.Roll  = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Roll) ? Rotation.Roll : 0.0f;

		return Rotation;
	}

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

	FORCEINLINE FVector GetDirection(FVector Direction, const int32& Rules)
	{
		Direction.X = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Yaw) ? Direction.X : 0.0f;
		Direction.Y = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Yaw) ? Direction.Y : 0.0f;
		Direction.Z = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Pitch) ? Direction.Z : 0.0f;

		return Direction;
	}
}

#define CS_ROTATION_FLAGS_NONE 0
#define CS_ROTATION_FLAGS_PITCH 1
#define CS_ROTATION_FLAGS_YAW 2
#define CS_ROTATION_FLAGS_ROLL 4
#define CS_ROTATION_FLAGS_PITCH_AND_YAW 3

#pragma endregion RotationRules

// Transform
#pragma region

/**
* Describes the members of FTransform.
*/
UENUM(BlueprintType)
enum class ECsTransform : uint8
{
	Translation			UMETA(DisplayName = "Translation"),
	Rotation			UMETA(DisplayName = "Rotation"),
	Scale				UMETA(DisplayName = "Scale"),
	ECsTransform_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsTransform : public TCsEnumMap<ECsTransform>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTransform, ECsTransform)
};

namespace NCsTransform
{
	namespace Ref
	{
		typedef ECsTransform Type;

		extern CSCORE_API const Type Translation;
		extern CSCORE_API const Type Rotation;
		extern CSCORE_API const Type Scale;
		extern CSCORE_API const Type ECsTransform_MAX;
	}
}

#pragma endregion Transform

// TransformSpace
#pragma region

/**
* Describes how the member of FTransform is modified (Relative, World, ... etc)
*/
UENUM(BlueprintType)
enum class ECsTransformSpace : uint8
{
	Relative				UMETA(DisplayName = "Relative"),
	World					UMETA(DisplayName = "World"),
	ECsTransformSpace_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsTransformSpace : public TCsEnumMap<ECsTransformSpace>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTransformSpace, ECsTransformSpace)
};

namespace NCsTransformSpace
{
	namespace Ref
	{
		typedef ECsTransformSpace Type;

		extern CSCORE_API const Type Relative;
		extern CSCORE_API const Type World;
		extern CSCORE_API const Type ECsTransformSpace_MAX;
	}
}

#pragma endregion TransformSpace

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

class USceneComponent;
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
	* Set the relative transform of a SceneComponent to Transform based on some Rules,
	* which determine which component of the Transform to use.
	* See ECsTransformRules.
	*
	* @param Component
	* @param Transform
	* @param Rules		Bit mask using the bit flag ECsTransformRules.
	*/
	CSCORE_API void SetRelativeTransform(USceneComponent* Component, const FTransform& Transform, const int32& Rules);

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
	* Set the transform of a SceneComponent to Transform based on some Rules,
	* which determine which component of the Transform to use.
	* See ECsTransformRules.
	*
	* @param Component
	* @param Transform
	* @param Rules		Bit mask using the bit flag ECsTransformRules.
	*/
	CSCORE_API void SetTransform(USceneComponent* Component, const FTransform& Transform, const int32& Rules);

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

	/**
	* Set the transform of a SceneComponent to Transform based on some Rules,
	* which determine which component of the Transform to use.
	* See ECsTransformRules.
	*
	* @param Component
	* @param Transform
	* @param Rules		Bit mask using the bit flag ECsTransformRules.
	* @param Spaces
	*/
	CSCORE_API void SetTransform(USceneComponent* Component, const FTransform& Transform, const int32& Rules, const ECsTransformSpace(&Spaces)[(uint8)ECsTransform::ECsTransform_MAX]);

	/**
	* Compare transforms A and B with Rules to determine which components are equal.
	* 
	* @param A
	* @oaran B
	* @param Rules		Bit mask using the bit flag ECsTransformRules.
	* return
	*/
	CSCORE_API bool AreTransformsEqual(const FTransform& A, const FTransform& B, const int32& Rules);
}

#define CS_TRANSFORM_FLAGS_NONE 0

#pragma endregion TransformRules

// TransformLocationMember
#pragma region

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsTransformLocationMember : uint8
{
	X	UMETA(DisplayName = "X"),	// 0
	Y	UMETA(DisplayName = "Y"),	// 1
	Z	UMETA(DisplayName = "Z"),	// 2
};

struct CSCORE_API EMCsTransformLocationMember : public TCsEnumFlagMap<ECsTransformLocationMember>
{
	CS_ENUM_FLAG_MAP_BODY(EMCsTransformLocationMember, ECsTransformLocationMember)
};

namespace NCsTransformLocationMember
{
	typedef ECsTransformLocationMember Type;

	namespace Ref
	{
		extern CSCORE_API const Type X;
		extern CSCORE_API const Type Y;
		extern CSCORE_API const Type Z;
	}

	extern CSCORE_API const uint32 None;
	extern CSCORE_API const uint32 All;
}

namespace NCsTransform
{
	namespace NLocation
	{
		enum class EMember : uint32
		{
			X = 1 << 0,
			Y = 1 << 1,
			Z = 1 << 2
		};

		struct CSCORE_API EMMember : public TCsEnumMaskMap<EMember>
		{
			CS_ENUM_MASK_MAP_BODY(EMMember, EMember)
		};

		namespace NMember
		{
			typedef EMember Type;

			namespace Ref
			{
				extern CSCORE_API const Type X;
				extern CSCORE_API const Type Y;
				extern CSCORE_API const Type Z;
			}

			extern CSCORE_API const uint32 None;
			extern CSCORE_API const uint32 All;
		}
	}
}

#pragma endregion TransformLocationMember

// FCsTransform_Location_Multiplier
#pragma region

// NCsTransform::NLocation::FMultiplier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTransform, NLocation, FMultiplier)

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsTransform_Location_Multiplier
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math")
	float Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (Bitmask, BitmaskEnum = "ECsTransformLocationMember"))
	int32 Members;

	FCsTransform_Location_Multiplier() :
		Multiplier(1.0f),
		Members(7) // All | 1 + 2 + 4
	{
	}

#define ProxyType NCsTransform::NLocation::FMultiplier
	void CopyToProxy(ProxyType* Proxy);
	void CopyToProxyAsValue(ProxyType* Proxy) const;
#undef ProxyType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	FORCEINLINE FVector Modify(const FVector& Value, const float& Scale) const
	{
		FVector NewValue = Value;

		typedef ECsTransformLocationMember MemberType;

		NewValue.X *= CS_TEST_BLUEPRINT_BITFLAG(Members, MemberType::X) ? Multiplier * Scale : 1.0f;
		NewValue.Y *= CS_TEST_BLUEPRINT_BITFLAG(Members, MemberType::Y) ? Multiplier * Scale : 1.0f;
		NewValue.Z *= CS_TEST_BLUEPRINT_BITFLAG(Members, MemberType::Z) ? Multiplier * Scale : 1.0f;

		return NewValue;
	}
};

namespace NCsTransform
{
	namespace NLocation
	{
		struct CSCORE_API FMultiplier
		{
		private:

			CS_DECLARE_MEMBER_WITH_PROXY(Multiplier, float)
			CS_DECLARE_MEMBER_WITH_PROXY(Members, int32)

		public:

			FMultiplier() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Multiplier, 1.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Members, 7) // All | 1 + 2 + 4
			{
				CS_CTOR_SET_MEMBER_PROXY(Multiplier);
				CS_CTOR_SET_MEMBER_PROXY(Members);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Multiplier, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Members, int32)

			FORCEINLINE void Copy(const FMultiplier& From)
			{
				SetMultiplier(From.GetMultiplier());
				SetMembers(From.GetMembers());
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

			FORCEINLINE FVector Modify(const FVector& Value, const float& Scale) const
			{
				FVector NewValue = Value;

				typedef NCsTransform::NLocation::EMember MemberType;

				NewValue.X *= CS_TEST_BITFLAG(GetMembers(), MemberType::X) ? GetMultiplier() * Scale : 1.0f;
				NewValue.Y *= CS_TEST_BITFLAG(GetMembers(), MemberType::Y) ? GetMultiplier() * Scale : 1.0f;
				NewValue.Z *= CS_TEST_BITFLAG(GetMembers(), MemberType::Z) ? GetMultiplier() * Scale : 1.0f;

				return NewValue;
			}
		};
	}
}

#pragma endregion FCsTransform_Location_Multiplier

// TransformRotationMember
#pragma region

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsTransformRotationMember : uint8
{
	Pitch	UMETA(DisplayName = "Pitch"),	// 0
	Yaw		UMETA(DisplayName = "Yaw"),		// 1
	Roll	UMETA(DisplayName = "Roll"),	// 2
};

struct CSCORE_API EMCsTransformRotationMember : public TCsEnumFlagMap<ECsTransformRotationMember>
{
	CS_ENUM_FLAG_MAP_BODY(EMCsTransformRotationMember, ECsTransformRotationMember)
};

namespace NCsTransformRotationMember
{
	typedef ECsTransformRotationMember Type;

	namespace Ref
	{
		extern CSCORE_API const Type Pitch;
		extern CSCORE_API const Type Yaw;
		extern CSCORE_API const Type Roll;
	}

	extern CSCORE_API const uint32 None;
	extern CSCORE_API const uint32 All;
}

namespace NCsTransform
{
	namespace NRotation
	{
		enum class EMember : uint32
		{
			Pitch	= 1 << 0,
			Yaw		= 1 << 1,
			Roll	= 1 << 2
		};

		struct CSCORE_API EMMember : public TCsEnumMaskMap<EMember>
		{
			CS_ENUM_MASK_MAP_BODY(EMMember, EMember)
		};

		namespace NMember
		{
			typedef EMember Type;

			namespace Ref
			{
				extern CSCORE_API const Type Pitch;
				extern CSCORE_API const Type Yaw;
				extern CSCORE_API const Type Roll;
			}

			extern CSCORE_API const uint32 None;
			extern CSCORE_API const uint32 All;
		}
	}
}

#pragma endregion TransformRotationMember

// FCsTransform_Rotation_Multiplier
#pragma region

// NCsTransform::NRotation::FMultiplier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTransform, NRotation, FMultiplier)

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsTransform_Rotation_Multiplier
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math")
	float Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (Bitmask, BitmaskEnum = "ECsTransformRotationMember"))
	int32 Members;

	FCsTransform_Rotation_Multiplier() :
		Multiplier(1.0f),
		Members(7) // All | 1 + 2 + 4
	{
	}

#define ProxyType NCsTransform::NRotation::FMultiplier
	void CopyToProxy(ProxyType* Proxy);
	void CopyToProxyAsValue(ProxyType* Proxy) const;
#undef ProxyType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	FORCEINLINE FRotator Modify(const FRotator& Value, const float& Scale) const
	{
		FRotator NewValue = Value;

		typedef ECsTransformRotationMember MemberType;

		NewValue.Pitch *= CS_TEST_BLUEPRINT_BITFLAG(Members, MemberType::Pitch) ? Multiplier * Scale : 1.0f;
		NewValue.Yaw   *= CS_TEST_BLUEPRINT_BITFLAG(Members, MemberType::Yaw) ? Multiplier * Scale : 1.0f;
		NewValue.Roll  *= CS_TEST_BLUEPRINT_BITFLAG(Members, MemberType::Roll) ? Multiplier * Scale : 1.0f;

		return NewValue;
	}
};

namespace NCsTransform
{
	namespace NRotation
	{
		struct CSCORE_API FMultiplier
		{
		private:

			CS_DECLARE_MEMBER_WITH_PROXY(Multiplier, float)
			CS_DECLARE_MEMBER_WITH_PROXY(Members, int32)

		public:

			FMultiplier() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Multiplier, 1.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Members, 7) // All | 1 + 2 + 4
			{
				CS_CTOR_SET_MEMBER_PROXY(Multiplier);
				CS_CTOR_SET_MEMBER_PROXY(Members);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Multiplier, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Members, int32)

			FORCEINLINE void Copy(const FMultiplier& From)
			{
				SetMultiplier(From.GetMultiplier());
				SetMembers(From.GetMembers());
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

			FORCEINLINE FRotator Modify(const FRotator& Value, const float& Scale) const
			{
				FRotator NewValue = Value;

				typedef NCsTransform::NRotation::EMember MemberType;

				NewValue.Pitch *= CS_TEST_BITFLAG(GetMembers(), MemberType::Pitch) ? GetMultiplier() * Scale : 1.0f;
				NewValue.Yaw   *= CS_TEST_BITFLAG(GetMembers(), MemberType::Yaw) ? GetMultiplier() * Scale : 1.0f;
				NewValue.Roll  *= CS_TEST_BITFLAG(GetMembers(), MemberType::Roll) ? GetMultiplier() * Scale : 1.0f;

				return NewValue;
			}
		};
	}
}

#pragma endregion FCsTransform_Rotation_Multiplier

// TransformScaleMember
#pragma region

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsTransformScaleMember : uint8
{
	X	UMETA(DisplayName = "X"),	// 0
	Y	UMETA(DisplayName = "Y"),	// 1
	Z	UMETA(DisplayName = "Z"),	// 2
};

struct CSCORE_API EMCsTransformScaleMember : public TCsEnumFlagMap<ECsTransformScaleMember>
{
	CS_ENUM_FLAG_MAP_BODY(EMCsTransformScaleMember, ECsTransformScaleMember)
};

namespace NCsTransformScaleMember
{
	typedef ECsTransformScaleMember Type;

	namespace Ref
	{
		extern CSCORE_API const Type X;
		extern CSCORE_API const Type Y;
		extern CSCORE_API const Type Z;
	}

	extern CSCORE_API const uint32 None;
	extern CSCORE_API const uint32 All;
}

namespace NCsTransform
{
	namespace NScale
	{
		enum class EMember : uint32
		{
			X = 1 << 0,
			Y = 1 << 1,
			Z = 1 << 2
		};

		struct CSCORE_API EMMember : public TCsEnumMaskMap<EMember>
		{
			CS_ENUM_MASK_MAP_BODY(EMMember, EMember)
		};

		namespace NMember
		{
			typedef EMember Type;

			namespace Ref
			{
				extern CSCORE_API const Type X;
				extern CSCORE_API const Type Y;
				extern CSCORE_API const Type Z;
			}

			extern CSCORE_API const uint32 None;
			extern CSCORE_API const uint32 All;
		}
	}
}

#pragma endregion TransformScaleMember

// FCsTransform_Scale_Multiplier
#pragma region

// NCsTransform::NScale::FMultiplier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTransform, NScale, FMultiplier)

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsTransform_Scale_Multiplier
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math")
	float Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (Bitmask, BitmaskEnum = "ECsTransformScaleMember"))
	int32 Members;

	FCsTransform_Scale_Multiplier() :
		Multiplier(1.0f),
		Members(7) // All | 1 + 2 + 4
	{
	}

#define ProxyType NCsTransform::NScale::FMultiplier
	void CopyToProxy(ProxyType* Proxy);
	void CopyToProxyAsValue(ProxyType* Proxy) const;
#undef ProxyType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	FORCEINLINE FVector Modify(const FVector& Value, const float& Scale) const
	{
		FVector NewValue = Value;

		typedef ECsTransformScaleMember MemberType;

		NewValue.X *= CS_TEST_BLUEPRINT_BITFLAG(Members, MemberType::X) ? Multiplier * Scale : 1.0f;
		NewValue.Y *= CS_TEST_BLUEPRINT_BITFLAG(Members, MemberType::Y) ? Multiplier * Scale : 1.0f;
		NewValue.Z *= CS_TEST_BLUEPRINT_BITFLAG(Members, MemberType::Z) ? Multiplier * Scale : 1.0f;

		return NewValue;
	}
};

namespace NCsTransform
{
	namespace NScale
	{
		struct CSCORE_API FMultiplier
		{
		private:

			CS_DECLARE_MEMBER_WITH_PROXY(Multiplier, float)
			CS_DECLARE_MEMBER_WITH_PROXY(Members, int32)

		public:

			FMultiplier() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Multiplier, 1.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Members, 7) // All | 1 + 2 + 4
			{
				CS_CTOR_SET_MEMBER_PROXY(Multiplier);
				CS_CTOR_SET_MEMBER_PROXY(Members);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Multiplier, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Members, int32)

			FORCEINLINE void Copy(const FMultiplier& From)
			{
				SetMultiplier(From.GetMultiplier());
				SetMembers(From.GetMembers());
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

			FORCEINLINE FVector Modify(const FVector& Value, const float& Scale) const
			{
				FVector NewValue = Value;

				typedef NCsTransform::NScale::EMember MemberType;

				NewValue.X *= CS_TEST_BITFLAG(GetMembers(), MemberType::X) ? GetMultiplier() * Scale : 1.0f;
				NewValue.Y *= CS_TEST_BITFLAG(GetMembers(), MemberType::Y) ? GetMultiplier() * Scale : 1.0f;
				NewValue.Z *= CS_TEST_BITFLAG(GetMembers(), MemberType::Z) ? GetMultiplier() * Scale : 1.0f;

				return NewValue;
			}
		};
	}
}

#pragma endregion FCsTransform_Scale_Multiplier

// FCsOptionalVectorInterval
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsOptionalVectorInterval
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math")
	FVector Vector; // 3 x 64 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (InlineEditConditionToggle))
	bool bIntervalX; // 1 bit

	UPROPERTY(EditAnywhere, Category = "CsCore|Math", meta = (editcondition = "bIntervalX"))
	FFloatInterval IntervalX; // 2 x 16 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (InlineEditConditionToggle))
	bool bIntervalY; // 1 bit

	UPROPERTY(EditAnywhere, Category = "CsCore|Math", meta = (editcondition = "bIntervalX"))
	FFloatInterval IntervalY; // 2 x 16 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (InlineEditConditionToggle))
	bool bIntervalZ;

	UPROPERTY(EditAnywhere, Category = "CsCore|Math", meta = (editcondition = "bIntervalX"))
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math")
	FRotator Rotator; // 3 x 64 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (InlineEditConditionToggle))
	bool bIntervalRoll; // 1 bit

	UPROPERTY(EditAnywhere, Category = "CsCore|Math", meta = (editcondition = "bIntervalRoll"))
	FFloatInterval IntervalRoll; // 2 x 16 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (InlineEditConditionToggle))
	bool bIntervalPitch; // 1 bit

	UPROPERTY(EditAnywhere, Category = "CsCore|Math", meta = (editcondition = "bIntervalPitch"))
	FFloatInterval IntervalPitch; // 2 x 16 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (InlineEditConditionToggle))
	bool bIntervalYaw;

	UPROPERTY(EditAnywhere, Category = "CsCore|Math", meta = (editcondition = "bIntervalYaw"))
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

// FCsRay
#pragma region

/**
* Mimics FRay
*/
USTRUCT(BlueprintType)
struct FCsRay
{
	GENERATED_USTRUCT_BODY()

public:

	/** Ray origin point */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math")
	FVector Origin;

	/** Ray direction vector (always normalized) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math")
	FVector Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Math", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Distance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Math")
	FVector End;

	/** Default constructor initializes ray to Zero origin and Z-axis direction */
	FCsRay() :
		Origin(FVector::ZeroVector),
		Direction(FVector(0, 0, 1)),
		Distance(1000000.0f), // TODO: have a better number for FLT_MAX without overflow
		End(FVector::ZeroVector)
	{
	}

	/** 
	  * Initialize Ray with origin, direction, and distance.
	  *
	  * @param InOrigin					Ray Origin Point
	  * @param InDirection				Ray Direction Vector
	  * @param InDistance
	  * @param bDirectionIsNormalized	Direction will be normalized unless this is passed as true (default false)
	  */
	FCsRay(const FVector& InOrigin, const FVector& InDirection, const float& InDistance, bool bDirectionIsNormalized = false)
	{
		Origin = InOrigin;
		Direction = InDirection;

		if (!bDirectionIsNormalized)
		{
			Direction.Normalize();
		}
		End = CalculateEnd();
	}

	/**
	  * Initialize Ray with origin, direction, and distance.
	  *
	  * @param InOrigin					Ray Origin Point
	  * @param InDirection				Ray Direction Vector
	  * @param bDirectionIsNormalized	Direction will be normalized unless this is passed as true (default false)
	  */
	FCsRay(const FVector& InOrigin, const FVector& InDirection, bool bDirectionIsNormalized = false)
	{
		Origin = InOrigin;
		Direction = InDirection;

		if (!bDirectionIsNormalized)
		{
			Direction.Normalize();
		}
		Distance = GetDefaultDistance();
		End = CalculateEnd();
	}

public:

	FORCEINLINE static float GetDefaultDistance() { return 1000000.0f; }

	/** 
	 * Calculate position on ray at given distance/parameter
	 *
	 * @param RayParameter	Scalar distance along Ray
	 * @return				Point on Ray
	 */
	FORCEINLINE FVector PointAt(float RayParameter) const
	{
		return Origin + RayParameter * Direction;
	}

	/**
	 * Calculate ray parameter (distance from origin to closest point) for query Point
	 *
	 * @param Point Query Point
	 * @return		Distance along ray from origin to closest point
	 */
	FORCEINLINE float GetParameter(const FVector& Point) const
	{
		return FVector::DotProduct((Point - Origin), Direction);
	}

	/**
	 * Find minimum squared distance from query point to ray
	 *
	 * @param Point Query Point
	 * @return		Squared distance to Ray
	 */
	FORCEINLINE float DistSquared(const FVector& Point) const
	{
		float RayParameter = FVector::DotProduct((Point - Origin), Direction);
		if (RayParameter < 0)
		{
			return FVector::DistSquared(Origin, Point);
		}
		else 
		{
			FVector ProjectionPt = Origin + RayParameter * Direction;
			return FVector::DistSquared(ProjectionPt, Point);
		}
	}

	/**
	 * Find closest point on ray to query point
	 * 
	 * @param Point Query point
	 * @return		Closest point on Ray
	 */
	FORCEINLINE FVector ClosestPoint(const FVector& Point) const
	{
		float RayParameter = FVector::DotProduct((Point - Origin), Direction);
		if (RayParameter < 0) 
		{
			return Origin;
		}
		else 
		{
			return Origin + RayParameter * Direction;
		}
	}
	
	FORCEINLINE FVector CalculateEnd() const
	{
		return Origin + Distance * Direction;
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsRay

// DotDimension
#pragma region

/**
* Describes dimensions for a dot check.
*/
UENUM(BlueprintType)
enum class ECsDotDimension : uint8
{
	/** 2D: X,Y */
	XY					UMETA(DisplayName = "2D: X,Y"),
	/** 3D: X,Y,Z */
	XYZ					UMETA(DisplayName = "3D: X,Y,Z"),
	ECsDotDimension_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsDotDimension : public TCsEnumMap<ECsDotDimension>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsDotDimension, ECsDotDimension)
};

namespace NCsDotDimension
{
	typedef ECsDotDimension Type;

	namespace Ref
	{
		extern CSCORE_API const Type XY;
		extern CSCORE_API const Type XYZ;
		extern CSCORE_API const Type ECsDotDimension_MAX;
	}
}

namespace NCsDot
{
	/**
	* Describes dimensions for a dot check.
	*/
	enum class EDimension : uint8 
	{
		/** 2D: X,Y */
		XY,
		/** 3D: X,Y,Z */
		XYZ,
		EDimension_MAX
	};

	struct CSCORE_API EMDimension : public TCsEnumMap<EDimension>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMDimension, EDimension)
	};

	namespace NDimension
	{
		typedef EDimension Type;

		namespace Ref
		{
			extern CSCORE_API const Type XY;
			extern CSCORE_API const Type XYZ;
			extern CSCORE_API const Type EDimension_MAX;
		}
	}
}

#pragma endregion DotDimension