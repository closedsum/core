// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_Primitive.h"
#include "Types/CsTypes_Load.h"

#include "CsTypes_Projectile.generated.h"
#pragma once

// Projectile
#pragma region

// ACsData_Projectile
USTRUCT(BlueprintType)
struct FCsData_ProjectilePtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TAssetSubclassOf<class ACsData_Projectile> Data;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Data_LoadFlags;

private:
	UPROPERTY(Transient)
	class ACsData_Projectile* Data_Internal;

public:
	FCsData_ProjectilePtr()
	{
		CS_SET_BLUEPRINT_BITFLAG(Data_LoadFlags, ECsLoadFlags::Game);
	}

	FCsData_ProjectilePtr& operator=(const FCsData_ProjectilePtr& B)
	{
		Data = B.Data;
		Data_LoadFlags = B.Data_LoadFlags;
		Data_Internal = B.Data_Internal;
		return *this;
	}

	bool operator==(const FCsData_ProjectilePtr& B) const
	{
		return Data == B.Data && Data_LoadFlags == B.Data_LoadFlags && Data_Internal == B.Data_Internal;
	}

	bool operator!=(const FCsData_ProjectilePtr& B) const
	{
		return !(*this == B);
	}

	class ACsData_Projectile* Get() const
	{
		return Data_Internal;
	}
};

// ACsData_ProjectileImpact
USTRUCT(BlueprintType)
struct FCsData_ProjectileImpactPtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TAssetSubclassOf<class ACsData_ProjectileImpact> Data;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Data_LoadFlags;

private:
	UPROPERTY(Transient)
	class ACsData_ProjectileImpact* Data_Internal;

public:
	FCsData_ProjectileImpactPtr()
	{
		CS_SET_BLUEPRINT_BITFLAG(Data_LoadFlags, ECsLoadFlags::Game);
	}

	FCsData_ProjectileImpactPtr& operator=(const FCsData_ProjectileImpactPtr& B)
	{
		Data = B.Data;
		Data_LoadFlags = B.Data_LoadFlags;
		Data_Internal = B.Data_Internal;
		return *this;
	}

	bool operator==(const FCsData_ProjectileImpactPtr& B) const
	{
		return Data == B.Data && Data_LoadFlags == B.Data_LoadFlags && Data_Internal == B.Data_Internal;
	}

	bool operator!=(const FCsData_ProjectileImpactPtr& B) const
	{
		return !(*this == B);
	}

	class ACsData_ProjectileImpact* Get() const
	{
		return Data_Internal;
	}
};

UENUM(BlueprintType)
namespace ECsProjectileRelevance
{
	enum Type
	{
		RealVisible					UMETA(DisplayName = "Real Visible"),
		RealInvisible				UMETA(DisplayName = "Real Invisible"),
		Fake						UMETA(DisplayName = "Fake"),
		ECsProjectileRelevance_MAX	UMETA(Hidden),
	};
}

#define ECS_PROJECTILE_RELEVANCE_MAX (uint8)ECsProjectileRelevance::ECsProjectileRelevance_MAX
typedef ECsProjectileRelevance::Type TCsProjectileRelevance;

namespace ECsProjectileRelevance
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString RealVisible = TCsString(TEXT("RealVisible"), TEXT("realvisible"));
		const TCsString RealInvisible = TCsString(TEXT("RealInvisible"), TEXT("realinvisible"));
		const TCsString Fake = TCsString(TEXT("Fake"), TEXT("fake"));
	}

	namespace Ref
	{
		const TCsProjectileRelevance RealVisible = Type::RealInvisible;
		const TCsProjectileRelevance RealInvisible = Type::RealInvisible;
		const TCsProjectileRelevance Fake = Type::Fake;
		const TCsProjectileRelevance ECsProjectileRelevance_MAX = Type::ECsProjectileRelevance_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::RealVisible) { return Str::RealVisible.Value; }
		if (EType == Type::RealInvisible) { return Str::RealInvisible.Value; }
		if (EType == Type::Fake) { return Str::Fake.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &String)
	{
		if (String == Str::RealVisible) { return Ref::RealVisible; }
		if (String == Str::RealInvisible) { return Ref::RealInvisible; }
		if (String == Str::Fake) { return Ref::Fake; }
		return Ref::ECsProjectileRelevance_MAX;
	}
}

namespace ECsProjectileType
{
	enum Type : uint8;
}

typedef ECsProjectileType::Type TCsProjectileType;

UENUM(BlueprintType)
namespace ECsProjectileState
{
	enum Type
	{
		Active				   UMETA(DisplayName = "Active"),
		DeActivating		   UMETA(DisplayName = "DeActivating"),
		InActive			   UMETA(DisplayName = "InActive"),
		ECsProjectileState_MAX UMETA(Hidden),
	};
}

namespace ECsProjectileState
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Active = TCsString(TEXT("Active"), TEXT("active"));
		const TCsString DeActivating = TCsString(TEXT("DeActivating"), TEXT("deactivating"));
		const TCsString InActive = TCsString(TEXT("InActive"), TEXT("inactive"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Active) { return Str::Active.Value; }
		if (EType == Type::DeActivating) { return Str::DeActivating.Value; }
		if (EType == Type::InActive) { return Str::InActive.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Active) { return Type::Active; }
		if (String == Str::DeActivating) { return Type::DeActivating; }
		if (String == Str::InActive) { return Type::InActive; }
		return Type::ECsProjectileState_MAX;
	}
}

#define ECS_PROJECTILE_STATE_MAX (uint8)ECsProjectileState::ECsProjectileState_MAX
typedef ECsProjectileState::Type TCsProjectileState;

UENUM(BlueprintType)
namespace ECsProjectileDeActivate
{
	enum Type
	{
		Collision					UMETA(DisplayName = "Collision"),
		Movement					UMETA(DisplayName = "Movement"),
		Mesh						UMETA(DisplayName = "Mesh"),
		ECsProjectileDeActivate_MAX UMETA(Hidden),
	};
}

namespace ECsProjectileDeActivate
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Collision = TCsString(TEXT("Collision"), TEXT("collision"));
		const TCsString Movement = TCsString(TEXT("Movement"), TEXT("movement"));
		const TCsString Mesh = TCsString(TEXT("Mesh"), TEXT("mesh"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Collision) { return Str::Collision.Value; }
		if (EType == Type::Movement) { return Str::Movement.Value; }
		if (EType == Type::Mesh) { return Str::Mesh.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Collision) { return Type::Collision; }
		if (String == Str::Movement) { return Type::Movement; }
		if (String == Str::Mesh) { return Type::Mesh; }
		return Type::ECsProjectileDeActivate_MAX;
	}
}

#define ECS_PROJECTILE_DEACTIVATE_MAX (uint8)ECsProjectileDeActivate::ECsProjectileDeActivate_MAX
typedef ECsProjectileDeActivate::Type TCsProjectileDeActivate;

UENUM(BlueprintType)
namespace ECsProjectileMovement
{
	enum Type
	{
		Simulated					UMETA(DisplayName = "Simulated"),
		Function					UMETA(DisplayName = "Function"),
		ECsProjectileMovement_MAX	UMETA(Hidden),
	};
}

namespace ECsProjectileMovement
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Simulated = TCsString(TEXT("Simulated"), TEXT("simulated"));
		const TCsString Function = TCsString(TEXT("Function"), TEXT("function"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Simulated) { return Str::Simulated.Value; }
		if (EType == Type::Function) { return Str::Function.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Simulated) { return Type::Simulated; }
		if (String == Str::Function) { return Type::Function; }
		return Type::ECsProjectileMovement_MAX;
	}
}

#define ECS_PROJECTILE_MOVEMENT_MAX (uint8)ECsProjectileMovement::ECsProjectileMovement_MAX
typedef ECsProjectileMovement::Type TCsProjectileMovement;

UENUM(BlueprintType)
namespace ECsProjectileMovementFunctionType
{
	enum Type
	{
		Linear									UMETA(DisplayName = "t"),
		Sine									UMETA(DisplayName = "sin(t)"),
		ECsProjectileMovementFunctionType_MAX	UMETA(Hidden),
	};
}

namespace ECsProjectileMovementFunctionType
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Linear = TCsString(TEXT("Linear"), TEXT("linear"));
		const TCsString Sine = TCsString(TEXT("Sine"), TEXT("sine"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Linear) { return Str::Linear.Value; }
		if (EType == Type::Sine) { return Str::Sine.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Linear) { return Type::Linear; }
		if (String == Str::Sine) { return Type::Sine; }
		return Type::ECsProjectileMovementFunctionType_MAX;
	}
}

#define ECS_PROJECTILE_MOVEMENT_FUNCTION_TYPE_MAX (uint8)ECsProjectileMovementFunctionType::ECsProjectileMovementFunctionType_MAX
typedef ECsProjectileMovementFunctionType::Type TCsProjectileMovementFunctionType;

USTRUCT(BlueprintType)
struct FCsProjectileMovementFunctionAxis
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	bool IsActive;
	/** Types are t, sin(t), ... etc */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	TEnumAsByte<ECsProjectileMovementFunctionType::Type> Function;

	/** "Axis" F(t) = A * ((B*G(t))^N) + C. G(t) = t, sin(t), ... etc. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	float A;
	/** "Axis" F(t) = A * ((B*G(t))^N) + C. G(t) = t, sin(t), ... etc. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	float B;
	/** "Axis" F(t) = A * ((B*G(t))^N) + C. G(t) = t, sin(t), ... etc. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	float N;
	/** "Axis" F(t) = A * ((B*G(t))^N) + C. G(t) = t, sin(t), ... etc. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	float C;

	FCsProjectileMovementFunctionAxis()
	{
		IsActive = true;
		Function = ECsProjectileMovementFunctionType::Linear;
		A = 1.0f;
		B = 1.0f;
		N = 1.0f;
		C = 0.0f;
	}

	~FCsProjectileMovementFunctionAxis(){}

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

	FCsProjectileMovementFunction(){}
	~FCsProjectileMovementFunction(){}

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

USTRUCT(BlueprintType)
struct FCsProjectileFireCache
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	bool IsAllocated;

	UPROPERTY()
	float Time;
	UPROPERTY()
	float RealTime;
	UPROPERTY()
	uint64 Frame;

	UPROPERTY()
	float ChargePercent;

	UPROPERTY()
	FVector Direction;

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	float AdditionalSpeed;

	UPROPERTY()
	TWeakObjectPtr<AActor> HomingTarget;

	UPROPERTY()
	FName HomingBoneName;

	UPROPERTY()
	float HomingAccelerationMagnitude;

	FCsProjectileFireCache()
	{
		Reset();
	}

	FCsProjectileFireCache& operator=(const FCsProjectileFireCache& B)
	{
		IsAllocated = B.IsAllocated;
		Time = B.Time;
		RealTime = B.RealTime;
		Frame = B.Frame;
		ChargePercent = B.ChargePercent;
		Location = B.Location;
		Direction = B.Direction;
		AdditionalSpeed = B.AdditionalSpeed;
		HomingTarget = B.HomingTarget;
		HomingBoneName = B.HomingBoneName;
		HomingAccelerationMagnitude = B.HomingAccelerationMagnitude;
		return *this;
	}

	bool operator==(const FCsProjectileFireCache& B) const
	{
		return IsAllocated == B.IsAllocated &&
			Time == B.Time &&
			RealTime == B.RealTime &&
			Frame == B.Frame &&
			ChargePercent == B.ChargePercent &&
			Location == B.Location &&
			Direction == B.Direction &&
			AdditionalSpeed == B.AdditionalSpeed &&
			HomingTarget == B.HomingTarget &&
			HomingBoneName == B.HomingBoneName &&
			HomingAccelerationMagnitude == B.HomingAccelerationMagnitude;
	}

	bool operator!=(const FCsProjectileFireCache& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		IsAllocated = false;
		Time = 0.0f;
		RealTime = 0.0f;
		Frame = 0;
		ChargePercent = 0.0f;
		Location = FVector::ZeroVector;
		Direction = FVector::ZeroVector;
		AdditionalSpeed = 0.0f;
		HomingTarget.Reset();
		HomingTarget = NULL;
		HomingBoneName = NAME_None;
		HomingAccelerationMagnitude = 0.0f;
	}

	AActor* GetHomingTarget() const
	{
		return HomingTarget.IsValid() ? HomingTarget.Get() : NULL;
	}
};

USTRUCT(BlueprintType)
struct FCsProjectilePayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	bool IsAllocated;

	UPROPERTY()
	TEnumAsByte<ECsProjectileRelevance::Type> Relevance;

	UPROPERTY()
	TWeakObjectPtr<class ACsData_Projectile> Data;

	UPROPERTY()
	float ChargePercent;

	UPROPERTY()
	FVector Direction;

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	float AdditionalSpeed;

	UPROPERTY()
	TWeakObjectPtr<AActor> HomingTarget;

	UPROPERTY()
	FName HomingBone;

	UPROPERTY()
	float HomingAccelerationMagnitude;

	FCsProjectilePayload(){}
	~FCsProjectilePayload(){}

	FCsProjectilePayload& operator=(const FCsProjectilePayload& B)
	{
		IsAllocated = B.IsAllocated;
		Relevance = B.Relevance;
		Data = B.Data;
		ChargePercent = B.ChargePercent;
		Location = B.Location;
		Direction = B.Direction;
		AdditionalSpeed = B.AdditionalSpeed;
		HomingTarget = B.HomingTarget;
		HomingBone = B.HomingBone;
		HomingAccelerationMagnitude = B.HomingAccelerationMagnitude;
		return *this;
	}

	bool operator==(const FCsProjectilePayload& B) const
	{
		return	IsAllocated == B.IsAllocated &&
				Relevance == B.Relevance &&
				Data == B.Data &&
				ChargePercent == B.ChargePercent &&
				Location == B.Location &&
				Direction == B.Direction &&
				AdditionalSpeed == B.AdditionalSpeed &&
				HomingTarget == B.HomingTarget &&
				HomingBone == B.HomingBone &&
				HomingAccelerationMagnitude == B.HomingAccelerationMagnitude;
	}

	bool operator!=(const FCsProjectilePayload& B) const
	{
		return !(*this == B);
	}

	void Set(FCsProjectileFireCache* Payload)
	{
		ChargePercent = Payload->ChargePercent;
		Location = Payload->Location;
		Direction = Payload->Direction;
		AdditionalSpeed = Payload->AdditionalSpeed;
		HomingTarget = Payload->HomingTarget;
		HomingBone = Payload->HomingBoneName;
		HomingAccelerationMagnitude = Payload->HomingAccelerationMagnitude;
	}

	void Reset()
	{
		Relevance = ECsProjectileRelevance::ECsProjectileRelevance_MAX;
		ChargePercent = 0.0f;
		Location = FVector::ZeroVector;
		Direction = FVector::ZeroVector;
		AdditionalSpeed = 0.0f;
		HomingTarget.Reset();
		HomingTarget = nullptr;
		HomingBone = NAME_None;
		HomingAccelerationMagnitude = 0.0f;
	}

	ACsData_Projectile* GetData() { return Data.IsValid() ? Data.Get() : nullptr; }
	template<typename T>
	T* GetData() { return Cast<T>(GetData()); }

	AActor* GetHomingTarget() const
	{
		return HomingTarget.IsValid() ? HomingTarget.Get() : nullptr;
	}

	template<typename T>
	T* GetHomingTarget() const
	{
		return Cast<T>(GetHomingTarget());
	}
};

#pragma endregion Projectile