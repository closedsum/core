// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumMap.h"
// DataTable
#include "Engine/DataTable.h"

#include "CsTypes_Projectile.generated.h"

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

struct CSPRJ_API EMCsProjectileRelevance : public TCsEnumMap<ECsProjectileRelevance>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileRelevance, ECsProjectileRelevance)
};

namespace NCsProjectileRelevance
{
	typedef ECsProjectileRelevance Type;

	namespace Ref
	{
		extern CSPRJ_API const Type RealVisible;
		extern CSPRJ_API const Type RealInvisible;
		extern CSPRJ_API const Type Fake;
		extern CSPRJ_API const Type ECsProjectileRelevance_MAX;
	}

	extern CSPRJ_API const uint8 MAX;
}

#pragma endregion ProjectileRelevance

// Projectile
#pragma region

USTRUCT(BlueprintType)
struct CSPRJ_API FECsProjectile : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsProjectile)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsProjectile)

struct CSPRJ_API EMCsProjectile : public TCsEnumStructMap<FECsProjectile, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsProjectile, FECsProjectile, uint8)
};

struct FCsPrjDataRootSet;

namespace NCsProjectile
{
	typedef FECsProjectile Type;

	CSPRJ_API void FromEnumSettings(const FString& Context);

	CSPRJ_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSPRJ_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion Projectile

// ProjectileClass
#pragma region

USTRUCT(BlueprintType)
struct CSPRJ_API FECsProjectileClass : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsProjectileClass)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsProjectileClass)

struct CSPRJ_API EMCsProjectileClass : public TCsEnumStructMap<FECsProjectileClass, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsProjectileClass, FECsProjectileClass, uint8)
};

namespace NCsProjectileClass
{
	typedef FECsProjectileClass Type;

	CSPRJ_API void FromEnumSettings(const FString& Context);

	CSPRJ_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSPRJ_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

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

struct CSPRJ_API EMCsProjectileState : public TCsEnumMap<ECsProjectileState>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileState, ECsProjectileState)
};

namespace NCsProjectileState
{
	typedef ECsProjectileState Type;

	namespace Ref
	{
		extern CSPRJ_API const Type Active;
		extern CSPRJ_API const Type DeActivating;
		extern CSPRJ_API const Type InActive;
		extern CSPRJ_API const Type ECsProjectileState_MAX;
	}

	extern CSPRJ_API const uint8 MAX;
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

struct CSPRJ_API EMCsProjectileDeActivate : public TCsEnumMap<ECsProjectileDeActivate>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileDeActivate, ECsProjectileDeActivate)
};

namespace NCsProjectileDeActivate
{
	typedef ECsProjectileDeActivate Type;

	namespace Ref
	{
		extern CSPRJ_API const Type Collision;
		extern CSPRJ_API const Type Movement;
		extern CSPRJ_API const Type Mesh;
		extern CSPRJ_API const Type ECsProjectileDeActivate_MAX;
	}

	extern CSPRJ_API const uint8 MAX;
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

struct CSPRJ_API EMCsProjectileMovement : public TCsEnumMap<ECsProjectileMovement>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileMovement, ECsProjectileMovement)
};

namespace NCsProjectileMovement
{
	typedef ECsProjectileMovement Type;

	namespace Ref
	{
		extern CSPRJ_API const Type Simulated;
		extern CSPRJ_API const Type Function;
		extern CSPRJ_API const Type ECsProjectileMovement_MAX;
	}

	extern CSPRJ_API const uint8 MAX;
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

struct CSPRJ_API EMCsProjectileMovementFunctionType : public TCsEnumMap<ECsProjectileMovementFunctionType>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileMovementFunctionType, ECsProjectileMovementFunctionType)
};

namespace NCsProjectileMovementFunctionType
{
	typedef ECsProjectileMovementFunctionType Type;

	namespace Ref
	{
		extern CSPRJ_API const Type Linear;
		extern CSPRJ_API const Type Sine;
		extern CSPRJ_API const Type ECsProjectileMovementFunctionType_MAX;
	}

	extern CSPRJ_API const uint8 MAX;
}

#pragma endregion ProjectileMovementFunctionType

// ProjectileData
#pragma region

USTRUCT(BlueprintType)
struct CSPRJ_API FECsProjectileData : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

		CS_ENUM_UINT8_BODY(FECsProjectileData)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsProjectileData)

struct CSPRJ_API EMCsProjectileData : public TCsEnumStructMap<FECsProjectileData, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsProjectileData, FECsProjectileData, uint8)
};

namespace NCsProjectileData
{
	typedef FECsProjectileData Type;
	typedef EMCsProjectileData EnumMapType;

	extern CSPRJ_API const Type Projectile;
	extern CSPRJ_API const Type ProjectileCollision;
	extern CSPRJ_API const Type ProjectileStaticMeshVisual;
	extern CSPRJ_API const Type ProjectileTrailVisual;
}

#pragma endregion ProjectileData

// FCsProjectileMovementFunctionAxis
#pragma region

USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileMovementFunctionAxis
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
struct CSPRJ_API FCsProjectileMovementFunction
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

// FCsProjectilePtr
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectilePtr
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsProjectile"))
	TSoftClassPtr<UObject> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Load_Flags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UObject* Projectile_Internal;

	UPROPERTY(Transient, BlueprintReadOnly)
	UClass* Projectile_Class;

	FCsProjectilePtr() :
		Projectile(nullptr),
		Load_Flags(0),
		Projectile_Internal(nullptr),
		Projectile_Class(nullptr)
	{
	}

	FORCEINLINE UObject* Get() const { return Projectile_Internal; }

	template<typename T>
	FORCEINLINE T* Get() const
	{
		return Cast<T>(Get());
	}

	FORCEINLINE UClass* GetClass() const { return Projectile_Class; }
};

#pragma endregion FCsProjectilePtr

// FCsData_ProjectilePtr
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSPRJ_API FCsData_ProjectilePtr
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsData_Projectile"))
	TSoftClassPtr<UObject> Data;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Load_Flags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UObject* Data_Internal;

	UPROPERTY(Transient, BlueprintReadOnly)
	UClass* Data_Class;

	FCsData_ProjectilePtr() :
		Data(nullptr),
		Load_Flags(0),
		Data_Internal(nullptr),
		Data_Class(nullptr)
	{
	}

	FORCEINLINE UObject* Get() const { return Data_Internal; }

	template<typename T>
	FORCEINLINE T* Get() const { return Cast<T>(Get()); }

	FORCEINLINE UClass* GetClass() const { return Data_Class; }
};

#pragma endregion FCsData_ProjectilePtr

// FCsProjectileClassEntry
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileClassEntry : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/** The enum (FECsProjectile) name for the projectile class. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	/** The enum (FECsProjectile) display name for the projectile class. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;

	/** Soft Reference to a projectile of type: ICsProjectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsProjectilePtr Class;

	FCsProjectileClassEntry() :
		Name(),
		DisplayName(), 
		Class()
	{
	}
};

#pragma endregion FCsProjectileClassEntry

// FCsProjectileEntry
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileEntry : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/** The enum (FECsProjectile) name for the projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	/** The enum (FECsProjectile) display name for the projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;

	/** Class Type. This is used to get the actual class from a data table
	    of projectile classes (FCsPrjDataRootSet.ProjectileClasses). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsProjectileClass Class;

	/** Soft Reference to a data of type: ICsData_Projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsData_ProjectilePtr Data;

	FCsProjectileEntry() :
		Name(),
		DisplayName(), 
		Class(),
		Data()
	{
	}
};

#pragma endregion FCsProjectileEntry