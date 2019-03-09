// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Pool.h"

#include "CsTypes_Projectile.generated.h"
#pragma once

// ACsData_Projectile
USTRUCT(BlueprintType)
struct CSCORE_API FCsData_ProjectilePtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TSoftClassPtr<class ACsData_Projectile> Data;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Data_LoadFlags;

private:
	UPROPERTY(Transient)
	class ACsData_Projectile* Data_Internal;

public:
	FCsData_ProjectilePtr() :
		Data_LoadFlags(0),
		Data_Internal(nullptr)
	{
		CS_SET_BLUEPRINT_BITFLAG(Data_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE FCsData_ProjectilePtr& operator=(const FCsData_ProjectilePtr& B)
	{
		Data = B.Data;
		Data_LoadFlags = B.Data_LoadFlags;
		Data_Internal = B.Data_Internal;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsData_ProjectilePtr& B) const
	{
		return Data == B.Data && Data_LoadFlags == B.Data_LoadFlags && Data_Internal == B.Data_Internal;
	}

	FORCEINLINE bool operator!=(const FCsData_ProjectilePtr& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE class ACsData_Projectile* Get() const
	{
		return Data_Internal;
	}
};

// ACsData_ProjectileImpact
USTRUCT(BlueprintType)
struct CSCORE_API FCsData_ProjectileImpactPtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TSoftClassPtr<class ACsData_ProjectileImpact> Data;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Data_LoadFlags;

private:
	UPROPERTY(Transient)
	class ACsData_ProjectileImpact* Data_Internal;

public:
	FCsData_ProjectileImpactPtr() :
		Data_LoadFlags(0),
		Data_Internal(nullptr)
	{
		CS_SET_BLUEPRINT_BITFLAG(Data_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE FCsData_ProjectileImpactPtr& operator=(const FCsData_ProjectileImpactPtr& B)
	{
		Data = B.Data;
		Data_LoadFlags = B.Data_LoadFlags;
		Data_Internal = B.Data_Internal;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsData_ProjectileImpactPtr& B) const
	{
		return Data == B.Data && Data_LoadFlags == B.Data_LoadFlags && Data_Internal == B.Data_Internal;
	}

	FORCEINLINE bool operator!=(const FCsData_ProjectileImpactPtr& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE class ACsData_ProjectileImpact* Get() const
	{
		return Data_Internal;
	}
};

// ProjectileRelevance
#pragma region

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

typedef ECsProjectileRelevance::Type TCsProjectileRelevance;

struct CSCORE_API EMCsProjectileRelevance : public TCsEnumMap<ECsProjectileRelevance::Type>
{
protected:
	EMCsProjectileRelevance() {}
	EMCsProjectileRelevance(const EMCsProjectileRelevance &) = delete;
	EMCsProjectileRelevance(EMCsProjectileRelevance &&) = delete;
public:
	~EMCsProjectileRelevance() {}
private:
	static EMCsProjectileRelevance* Instance;

public:
	static EMCsProjectileRelevance& Get();
};

namespace ECsProjectileRelevance
{
	namespace Ref
	{
		extern CSCORE_API const Type RealVisible;
		extern CSCORE_API const Type RealInvisible;
		extern CSCORE_API const Type Fake;
		extern CSCORE_API const Type ECsProjectileRelevance_MAX;
	}
}

#pragma endregion ProjectileRelevance

// ProjectileType
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsProjectileType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsProjectileType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsProjectileType)

struct CSCORE_API EMCsProjectileType : public TCsEnumStructMap<FECsProjectileType, uint8>
{
	CS_DECLARE_ENUM_STRUCT_MAP_BODY(EMCsProjectileType)
};

#pragma endregion ProjectileType

// ProjectileState
#pragma region

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

typedef ECsProjectileState::Type TCsProjectileState;

struct CSCORE_API EMCsProjectileState : public TCsEnumMap<ECsProjectileState::Type>
{
	CS_DECLARE_ENUM_MAP_BODY(EMCsProjectileState)
};

namespace ECsProjectileState
{
	namespace Ref
	{
		extern CSCORE_API const Type Active;
		extern CSCORE_API const Type DeActivating;
		extern CSCORE_API const Type InActive;
		extern CSCORE_API const Type ECsProjectileState_MAX;
	}
}

#pragma endregion ProjectileState

// ProjectileDeActivate
#pragma region

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

typedef ECsProjectileDeActivate::Type TCsProjectileDeActivate;

struct CSCORE_API EMCsProjectileDeActivate : public TCsEnumMap<ECsProjectileDeActivate::Type>
{
	CS_DECLARE_ENUM_MAP_BODY(EMCsProjectileDeActivate)
};

namespace ECsProjectileDeActivate
{
	namespace Ref
	{
		extern CSCORE_API const Type Collision;
		extern CSCORE_API const Type Movement;
		extern CSCORE_API const Type Mesh;
		extern CSCORE_API const Type ECsProjectileDeActivate_MAX;
	}
}

#pragma endregion ProjectileDeActivate

// ProjectileMovement
#pragma region

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

typedef ECsProjectileMovement::Type TCsProjectileMovement;

struct CSCORE_API EMCsProjectileMovement : public TCsEnumMap<ECsProjectileMovement::Type>
{
	CS_DECLARE_ENUM_MAP_BODY(EMCsProjectileMovement)
};

namespace ECsProjectileMovement
{
	namespace Ref
	{
		extern CSCORE_API const Type Simulated;
		extern CSCORE_API const Type Function;
		extern CSCORE_API const Type ECsProjectileMovement_MAX;
	}
}

#pragma endregion ProjectileMovement

// ProjectileMovementFunctionType
#pragma region

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

typedef ECsProjectileMovementFunctionType::Type TCsProjectileMovementFunctionType;

struct CSCORE_API EMCsProjectileMovementFunctionType : public TCsEnumMap<ECsProjectileMovementFunctionType::Type>
{
	CS_DECLARE_ENUM_MAP_BODY(EMCsProjectileMovementFunctionType)
};

namespace ECsProjectileMovementFunctionType
{
	namespace Ref
	{
		extern CSCORE_API const Type Linear;
		extern CSCORE_API const Type Sine;
		extern CSCORE_API const Type ECsProjectileMovementFunctionType_MAX;
	}
}

#pragma endregion ProjectileMovementFunctionType

USTRUCT(BlueprintType)
struct CSCORE_API FCsProjectileMovementFunctionAxis
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

	FORCEINLINE FCsProjectileMovementFunctionAxis& operator=(const FCsProjectileMovementFunctionAxis& D)
	{
		IsActive = D.IsActive;
		Function = D.Function;
		A = D.A;
		B = D.B;
		N = D.N;
		C = D.C;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsProjectileMovementFunctionAxis& D) const
	{
		return	IsActive == D.IsActive &&
				Function == D.Function &&
				A == D.A &&
				B == D.B &&
				N == D.N &&
				C == D.C;
	}

	FORCEINLINE bool operator!=(const FCsProjectileMovementFunctionAxis& D) const
	{
		return !(*this == D);
	}

	FORCEINLINE float Evaluate(const float &T)
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
struct CSCORE_API FCsProjectileMovementFunction
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

	FORCEINLINE FCsProjectileMovementFunction& operator=(const FCsProjectileMovementFunction& B)
	{
		X = B.X;
		Y = B.Y;
		Z = B.Z;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsProjectileMovementFunction& B) const
	{
		return	X == B.X && Y == B.Y && Z == B.Z;
	}

	FORCEINLINE bool operator!=(const FCsProjectileMovementFunction& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE FVector Evaluate(const float &T)
	{
		return FVector(X.Evaluate(T), Y.Evaluate(T), Z.Evaluate(T));
	}

	FORCEINLINE FVector Evaluate(const float &Time, const FVector &Location, const FTransform &Transform)
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
struct CSCORE_API FCsProjectileFirePayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	bool IsAllocated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	float Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	float RealTime;
	UPROPERTY()
	uint64 Frame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	float ChargePercent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	FVector Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	float AdditionalSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	TWeakObjectPtr<AActor> HomingTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	FName HomingBoneName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	float HomingAccelerationMagnitude;

	TArray<struct FCsItem*> Items;

	FCsProjectileFirePayload()
	{
		Reset();
	}

	FORCEINLINE FCsProjectileFirePayload& operator=(const FCsProjectileFirePayload& B)
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

	FORCEINLINE bool operator==(const FCsProjectileFirePayload& B) const
	{
		return	IsAllocated == B.IsAllocated &&
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

	FORCEINLINE bool operator!=(const FCsProjectileFirePayload& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
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
		Items.Reset();
	}

	FORCEINLINE AActor* GetHomingTarget() const
	{
		return HomingTarget.IsValid() ? HomingTarget.Get() : NULL;
	}

	template<typename T>
	FORCEINLINE T* GetHomingTarget() const
	{
		return Cast<T>(GetHomingTarget());
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsProjectilePayload : public FCsPooledObjectPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	TEnumAsByte<ECsProjectileRelevance::Type> Relevance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	TWeakObjectPtr<class ACsData_Projectile> Data;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	float ChargePercent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	FVector Direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	FVector Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	float AdditionalSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	TWeakObjectPtr<AActor> HomingTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	FName HomingBone;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	float HomingAccelerationMagnitude;

	FCsProjectilePayload()
	{
		Reset();
	}

	~FCsProjectilePayload(){}

	FORCEINLINE FCsProjectilePayload& operator=(const FCsProjectilePayload& B)
	{
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

	FORCEINLINE bool operator==(const FCsProjectilePayload& B) const
	{
		return	Relevance == B.Relevance &&
				Data == B.Data &&
				ChargePercent == B.ChargePercent &&
				Location == B.Location &&
				Direction == B.Direction &&
				AdditionalSpeed == B.AdditionalSpeed &&
				HomingTarget == B.HomingTarget &&
				HomingBone == B.HomingBone &&
				HomingAccelerationMagnitude == B.HomingAccelerationMagnitude;
	}

	FORCEINLINE bool operator!=(const FCsProjectilePayload& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Set(FCsProjectileFirePayload* Payload)
	{
		ChargePercent = Payload->ChargePercent;
		Location = Payload->Location;
		Direction = Payload->Direction;
		AdditionalSpeed = Payload->AdditionalSpeed;
		HomingTarget = Payload->HomingTarget;
		HomingBone = Payload->HomingBoneName;
		HomingAccelerationMagnitude = Payload->HomingAccelerationMagnitude;
	}

	FORCEINLINE virtual void Reset() override
	{
		Super::Reset();

		Relevance = ECsProjectileRelevance::ECsProjectileRelevance_MAX;
		Instigator.Reset();
		ChargePercent = 0.0f;
		Location = FVector::ZeroVector;
		Direction = FVector::ZeroVector;
		AdditionalSpeed = 0.0f;
		HomingTarget.Reset();
		HomingTarget = nullptr;
		HomingBone = NAME_None;
		HomingAccelerationMagnitude = 0.0f;
	}

	FORCEINLINE ACsData_Projectile* GetData() { return Data.IsValid() ? Data.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetData() { return Cast<T>(GetData()); }

	FORCEINLINE AActor* GetHomingTarget() const
	{
		return HomingTarget.IsValid() ? HomingTarget.Get() : nullptr;
	}

	template<typename T>
	FORCEINLINE T* GetHomingTarget() const
	{
		return Cast<T>(GetHomingTarget());
	}
};