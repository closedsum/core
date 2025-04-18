// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_StructOps.h"
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumMap.h"
// Data
#include "Data/CsTableRowBase_Data.h"
// Utility
#include "Utility/CsPrjLog.h"

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
	typedef EMCsProjectile EnumMapType;
	typedef FECsProjectile Type;

	FORCEINLINE void Create(const FString& Name, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, UserDefinedEnum); }
	FORCEINLINE void CreateCustom(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, DisplayName, UserDefinedEnum); }
	FORCEINLINE bool IsValidEnum(const FString& Name) { return EnumMapType::Get().IsValidEnum(Name); }
	FORCEINLINE bool IsValidEnumByDisplayName(const FString& DisplayName) { return EnumMapType::Get().IsValidEnumByDisplayName(DisplayName); }

	CSPRJ_API void FromEnumSettings(const FString& Context);

	CSPRJ_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSPRJ_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion Projectile

// FCsData_ECsProjectile
#pragma region

USTRUCT(BlueprintType)
struct CSPRJ_API FCsData_ECsProjectile
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj")
	FECsProjectile Value;

	FCsData_ECsProjectile() :
		Value()
	{
	}

	FORCEINLINE FECsProjectile* GetPtr() { return &Value; }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

#pragma endregion FCsData_Projectile

// FCsDataNoPropertyView_ECsProjectile
#pragma region

USTRUCT(BlueprintType)
struct CSPRJ_API FCsDataNoPropertyView_ECsProjectile
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj")
	FECsProjectile Value;

	FCsDataNoPropertyView_ECsProjectile() :
		Value()
	{
	}

	FORCEINLINE const FECsProjectile& Get() const { return Value; }
	FORCEINLINE FECsProjectile* GetPtr() { return &Value; }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

#pragma endregion FCsDataNoPropertyView_ECsProjectile

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
	typedef EMCsProjectileClass EnumMapType;
	typedef FECsProjectileClass Type;

	FORCEINLINE void Create(const FString& Name, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, UserDefinedEnum); }
	FORCEINLINE void CreateCustom(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, DisplayName, UserDefinedEnum); }
	FORCEINLINE bool IsValidEnum(const FString& Name) { return EnumMapType::Get().IsValidEnum(Name); }
	FORCEINLINE bool IsValidEnumByDisplayName(const FString& DisplayName) { return EnumMapType::Get().IsValidEnumByDisplayName(DisplayName); }

	CSPRJ_API void FromEnumSettings(const FString& Context);

	CSPRJ_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSPRJ_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion Projectile

// ProjectileState
#pragma region

namespace NCsProjectile
{
	enum class EState : uint8 
	{
		LaunchDelay,
		Active,
		Inactive
	};
}

#pragma endregion ProjectileState

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

	FORCEINLINE FVector3f Evaluate(const float &T)
	{
		return FVector3f(X.Evaluate(T), Y.Evaluate(T), Z.Evaluate(T));
	}

	FORCEINLINE FVector3f Evaluate(const float &Time, const FVector3f &Location, const FTransform3f &Transform)
	{
		FVector3f Point = Evaluate(Time);

		// Override the Components that are NOT Active
		if (!X.IsActive)
			Point.X += Location.X;
		if (!Y.IsActive)
			Point.Y += Location.Y;
		if (!Z.IsActive)
			Point.Z += Location.Z;

		FTransform3f LocalTransform = FTransform3f::Identity;
		LocalTransform.SetTranslation(Point);
		const FTransform3f WorldTransform = LocalTransform * Transform;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj", meta = (MustImplement = "/Script.CsPrj.CsProjectile"))
	TSoftClassPtr<UObject> Projectile;

	UPROPERTY(BlueprintReadOnly, Category = "CsPrj")
	int32 Projectile_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsPrj")
	UObject* Projectile_Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsPrj")
	UClass* Projectile_Class;

	FCsProjectilePtr() :
		Projectile(nullptr),
		Projectile_LoadFlags(0),
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

	CS_STRUCT_OPS_DATA_UNLOAD(FCsProjectilePtr)

	FORCEINLINE void Unload()
	{
		Projectile.ResetWeakPtr();
		Projectile_Internal = nullptr;
		Projectile_Class = nullptr;
	}
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj", meta = (MustImplement = "/Script.CsPrj.CsData_Projectile"))
	TSoftClassPtr<UObject> Data;

	UPROPERTY(BlueprintReadOnly, Category = "CsPrj")
	int32 Data_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsPrj")
	UObject* Data_Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsPrj")
	UClass* Data_Class;

	FCsData_ProjectilePtr() :
		Data(nullptr),
		Data_LoadFlags(0),
		Data_Internal(nullptr),
		Data_Class(nullptr)
	{
	}

	FORCEINLINE UObject* Get() const { return Data_Internal; }

	template<typename T>
	FORCEINLINE T* Get() const { return Cast<T>(Get()); }

	FORCEINLINE UClass* GetClass() const { return Data_Class; }

	UObject* SafeLoad(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

	UObject* SafeLoadSoftClass(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

	CS_STRUCT_OPS_DATA_UNLOAD(FCsData_ProjectilePtr)

	void Unload();
};

#pragma endregion FCsData_ProjectilePtr

// FCsProjectileClassEntry
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileClassEntry : public FCsTableRowBase_Data
{
	GENERATED_USTRUCT_BODY()

	/** The enum (FECsProjectile) name for the projectile class. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FString Name;

	/** The enum (FECsProjectile) display name for the projectile class. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FString DisplayName;

	/** Soft Reference to a projectile of type: ICsProjectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FCsProjectilePtr Class;

	FCsProjectileClassEntry() :
		Name(),
		DisplayName(), 
		Class()
	{
	}

// FCsTableRowBase_Data
#pragma region
public:

	virtual void Unload() override
	{
		Class.Unload();
	}

#pragma endregion FCsTableRowBase_Data

	CS_STRUCT_OPS_DATA_UNLOAD(FCsProjectileClassEntry)
};

#pragma endregion FCsProjectileClassEntry

// FCsProjectileEntry
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileEntry : public FCsTableRowBase_Data
{
	GENERATED_USTRUCT_BODY()

	/** The enum (FECsProjectile) name for the projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FString Name;

	/** The enum (FECsProjectile) display name for the projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FString DisplayName;

	/** Class Type. This is used to get the actual class from a data table
	    of projectile classes (FCsPrjDataRootSet.ProjectileClasses). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FECsProjectileClass Class;

	/** Soft Reference to a data of type: ICsData_Projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FCsData_ProjectilePtr Data;

	FCsProjectileEntry() :
		Name(),
		DisplayName(), 
		Class(),
		Data()
	{
	}

// FCsTableRowBase_Data
#pragma region
public:

	virtual void Unload() override
	{
		Data.Unload();
	}

#pragma endregion FCsTableRowBase_Data

	CS_STRUCT_OPS_DATA_UNLOAD(FCsProjectileEntry)
};

#pragma endregion FCsProjectileEntry