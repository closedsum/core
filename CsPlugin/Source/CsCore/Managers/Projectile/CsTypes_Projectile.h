// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsTypes_Pool.h"
#include "Types/CsTypes_Load.h"

#include "CsTypes_Projectile.generated.h"
#pragma once

// FCsData_ProjectileBasePtr
#pragma region

class ACsData_ProjectileBase;

USTRUCT(BlueprintType)
struct CSCORE_API FCsData_ProjectileBasePtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TSoftClassPtr<ACsData_ProjectileBase> Data;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Data_LoadFlags;

private:
	UPROPERTY(Transient)
	ACsData_ProjectileBase* Data_Internal;

public:
	FCsData_ProjectileBasePtr() :
		Data_LoadFlags(0),
		Data_Internal(nullptr)
	{
		CS_SET_BLUEPRINT_BITFLAG(Data_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE bool operator==(const FCsData_ProjectileBasePtr& B) const
	{
		return Data == B.Data && Data_LoadFlags == B.Data_LoadFlags && Data_Internal == B.Data_Internal;
	}

	FORCEINLINE bool operator!=(const FCsData_ProjectileBasePtr& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE class ACsData_ProjectileBase* Get() const
	{
		return Data_Internal;
	}
};

#pragma endregion FCsData_ProjectileBasePtr

// FCsData_ProjectileImpactPtr
#pragma region

class ACsData_ProjectileImpact;

USTRUCT(BlueprintType)
struct CSCORE_API FCsData_ProjectileImpactPtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TSoftClassPtr<ACsData_ProjectileImpact> Data;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Data_LoadFlags;

private:
	UPROPERTY(Transient)
	ACsData_ProjectileImpact* Data_Internal;

public:
	FCsData_ProjectileImpactPtr() :
		Data_LoadFlags(0),
		Data_Internal(nullptr)
	{
		CS_SET_BLUEPRINT_BITFLAG(Data_LoadFlags, ECsLoadFlags::Game);
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

#pragma endregion FCsData_ProjectileImpactPtr

// ProjectileRelevance
#pragma region

UENUM(BlueprintType)
enum class ECsProjectileRelevance : uint8
{
	RealVisible					UMETA(DisplayName = "Real Visible"),
	RealInvisible				UMETA(DisplayName = "Real Invisible"),
	Fake						UMETA(DisplayName = "Fake"),
	ECsProjectileRelevance_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsProjectileRelevance : public TCsEnumMap<ECsProjectileRelevance>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileRelevance, ECsProjectileRelevance)
};

namespace NCsProjectileRelevance
{
	typedef ECsProjectileRelevance Type;

	namespace Ref
	{
		extern CSCORE_API const Type RealVisible;
		extern CSCORE_API const Type RealInvisible;
		extern CSCORE_API const Type Fake;
		extern CSCORE_API const Type ECsProjectileRelevance_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion ProjectileRelevance

// Projectile
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsProjectile : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsProjectile)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsProjectile)

struct CSCORE_API EMCsProjectile : public TCsEnumStructMap<FECsProjectile, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsProjectile, FECsProjectile, uint8)
};

#pragma endregion Projectile

// ProjectileState
#pragma region

UENUM(BlueprintType)
enum class ECsProjectileState : uint8
{
	Active				   UMETA(DisplayName = "Active"),
	DeActivating		   UMETA(DisplayName = "DeActivating"),
	InActive			   UMETA(DisplayName = "InActive"),
	ECsProjectileState_MAX UMETA(Hidden),
};

struct CSCORE_API EMCsProjectileState : public TCsEnumMap<ECsProjectileState>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileState, ECsProjectileState)
};

namespace NCsProjectileState
{
	typedef ECsProjectileState Type;

	namespace Ref
	{
		extern CSCORE_API const Type Active;
		extern CSCORE_API const Type DeActivating;
		extern CSCORE_API const Type InActive;
		extern CSCORE_API const Type ECsProjectileState_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion ProjectileState

// ProjectileDeActivate
#pragma region

UENUM(BlueprintType)
enum class ECsProjectileDeActivate : uint8
{
	Collision					UMETA(DisplayName = "Collision"),
	Movement					UMETA(DisplayName = "Movement"),
	Mesh						UMETA(DisplayName = "Mesh"),
	ECsProjectileDeActivate_MAX UMETA(Hidden),
};

struct CSCORE_API EMCsProjectileDeActivate : public TCsEnumMap<ECsProjectileDeActivate>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileDeActivate, ECsProjectileDeActivate)
};

namespace NCsProjectileDeActivate
{
	typedef ECsProjectileDeActivate Type;

	namespace Ref
	{
		extern CSCORE_API const Type Collision;
		extern CSCORE_API const Type Movement;
		extern CSCORE_API const Type Mesh;
		extern CSCORE_API const Type ECsProjectileDeActivate_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion ProjectileDeActivate

// ProjectileMovement
#pragma region

UENUM(BlueprintType)
enum class ECsProjectileMovement : uint8
{
	Simulated					UMETA(DisplayName = "Simulated"),
	Function					UMETA(DisplayName = "Function"),
	ECsProjectileMovement_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsProjectileMovement : public TCsEnumMap<ECsProjectileMovement>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileMovement, ECsProjectileMovement)
};

namespace NCsProjectileMovement
{
	typedef ECsProjectileMovement Type;

	namespace Ref
	{
		extern CSCORE_API const Type Simulated;
		extern CSCORE_API const Type Function;
		extern CSCORE_API const Type ECsProjectileMovement_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion ProjectileMovement

// ProjectileMovementFunctionType
#pragma region

UENUM(BlueprintType)
enum class ECsProjectileMovementFunctionType : uint8
{
	Linear									UMETA(DisplayName = "t"),
	Sine									UMETA(DisplayName = "sin(t)"),
	ECsProjectileMovementFunctionType_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsProjectileMovementFunctionType : public TCsEnumMap<ECsProjectileMovementFunctionType>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileMovementFunctionType, ECsProjectileMovementFunctionType)
};

namespace NCsProjectileMovementFunctionType
{
	typedef ECsProjectileMovementFunctionType Type;

	namespace Ref
	{
		extern CSCORE_API const Type Linear;
		extern CSCORE_API const Type Sine;
		extern CSCORE_API const Type ECsProjectileMovementFunctionType_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion ProjectileMovementFunctionType

// FCsProjectileMovementFunctionAxis
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsProjectileMovementFunctionAxis
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	bool IsActive;
	/** Types are t, sin(t), ... etc */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	ECsProjectileMovementFunctionType Function;

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

#pragma endregion FCsProjectileMovementFunctionAxis

// FCsProjectileMovementFunction
#pragma region

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

#pragma endregion FCsProjectileMovementFunction

// FCsProjectileFirePayload
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsProjectileFirePayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	bool bAllocated;

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
		bAllocated = B.bAllocated;
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
		return	bAllocated == B.bAllocated &&
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
		bAllocated = false;
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

#pragma endregion FCsProjectileFirePayload

// FCsProjectilePayload
#pragma region

class ACsData_ProjectileBase;

struct CSCORE_API FCsProjectileBasePayload : public ICsPooledObjectPayload
{
public:

	bool bAllocated;

	UObject* Instigator;

	UObject* Owner;

	UObject* Parent;

	ECsProjectileRelevance Relevance;

	TWeakObjectPtr<ACsData_ProjectileBase> Data;

	float ChargePercent;

	FVector Direction;

	FVector Location;

	float AdditionalSpeed;

	TWeakObjectPtr<AActor> HomingTarget;

	FName HomingBone;

	float HomingAccelerationMagnitude;

	FCsProjectileBasePayload()
	{
		Reset();
	}

	~FCsProjectileBasePayload(){}

	FORCEINLINE bool operator==(const FCsProjectileBasePayload& B) const
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

	FORCEINLINE bool operator!=(const FCsProjectileBasePayload& B) const
	{
		return !(*this == B);
	}

// ICsPooledObjectPayload
#pragma region
public:

	const bool& IsAllocated() const
	{
		return bAllocated;
	}

	UObject* GetInstigator() const
	{
		return Instigator;
	}

	UObject* GetOwner() const
	{
		return Owner;
	}

	UObject* GetParent() const
	{
		return Parent;
	}

	void Allocate()
	{
		bAllocated = true;
	}

	void Reset()
	{
		bAllocated = false;

		Instigator = nullptr;
		Owner = nullptr;
		Parent = nullptr;

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

#pragma endregion ICsPooledObjectPayload

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

	FORCEINLINE ACsData_ProjectileBase* GetData() { return Data.IsValid() ? Data.Get() : nullptr; }
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

#pragma endregion FCsProjectilePayload

// ICsProjectilePayload
#pragma region

struct CSCORE_API ICsProjectilePayload
{
	virtual const FVector& GetDirection() const = 0;

	virtual const FVector& GetLocation() const = 0;

	virtual ~ICsProjectilePayload(){}
};

#pragma endregion ICsProjectilePayload

// FCsScriptProjectilePayload
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSCORE_API FCsScriptProjectilePayload
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "Payload")
	UObject* Instigator;

	UPROPERTY(BlueprintReadWrite, Category = "Payload")
	UObject* Owner;

	UPROPERTY(BlueprintReadWrite, Category = "Payload")
	UObject* Parent;

	UPROPERTY(BlueprintReadWrite, Category = "Payload")
	FVector Location;

	UPROPERTY(BlueprintReadWrite, Category = "Payload")
	FVector Direction;

	FCsScriptProjectilePayload() :
		Instigator(nullptr),
		Owner(nullptr),
		Parent(nullptr),
		Location(0.0f),
		Direction(0.0f)
	{
	}
	~FCsScriptProjectilePayload() {}
};

#pragma endregion FCsScriptProjectilePayload