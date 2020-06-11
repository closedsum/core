// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsTypes_Pool.h"
#include "Types/CsTypes_Load.h"
#include "Containers/CsInterfaceMap.h"
#include "Containers/CsWeakObjectPtr.h"
#include "Engine/DataTable.h"

#include "CsTypes_Projectile.generated.h"
#pragma once

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

namespace NCsProjectile
{
	typedef FECsProjectile Type;

	CSPRJ_API void PopulateEnumMapFromSettings(const FString& Context);
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

// FCsProjectileFirePayload
#pragma region

USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileFirePayload
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

// FCsProjectileBasePayload
#pragma region

class UCsData_ProjectileBase;

struct CSPRJ_API FCsProjectileBasePayload : public ICsPooledObjectPayload
{
public:

	bool bAllocated;

	UObject* Instigator;

	UObject* Owner;

	UObject* Parent;

	ECsProjectileRelevance Relevance;

	TWeakObjectPtr<UCsData_ProjectileBase> Data;

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

	FORCEINLINE UCsData_ProjectileBase* GetData() { return Data.IsValid() ? Data.Get() : nullptr; }
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

#pragma endregion FCsProjectileBasePayload

// ICsProjectilePayload
#pragma region

struct CSPRJ_API ICsProjectilePayload : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsProjectilePayload(){}

	virtual const FVector& GetDirection() const = 0;

	virtual const FVector& GetLocation() const = 0;
};

#pragma endregion ICsProjectilePayload

// FCsProjectilePayload
#pragma region

class UObject;

struct CSPRJ_API FCsProjectilePayload : public ICsPooledObjectPayload,
										public ICsProjectilePayload
{
private:

	FCsInterfaceMap* InterfaceMap;

	bool bAllocated;

public:

	UObject* Instigator;

	UObject* Owner;

	UObject* Parent;
	
	FVector Direction;

	FVector Location;

public:

	FCsProjectilePayload() :
		InterfaceMap(nullptr),
		bAllocated(false),
		Instigator(nullptr),
		Owner(nullptr),
		Parent(nullptr),
		Direction(0.0f),
		Location(0.0f)
	{
		InterfaceMap = new FCsInterfaceMap();

		InterfaceMap->Add<ICsPooledObjectPayload>(static_cast<ICsPooledObjectPayload*>(this));
		InterfaceMap->Add<ICsProjectilePayload>(static_cast<ICsProjectilePayload*>(this));
	}

	~FCsProjectilePayload()
	{
		delete InterfaceMap;
	}

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

// ICsPooledObjectPayload
#pragma region
public:

	FORCEINLINE const bool& IsAllocated() const
	{
		return bAllocated;
	}

	FORCEINLINE UObject* GetInstigator() const
	{
		return Instigator;
	}

	FORCEINLINE UObject* GetOwner() const
	{
		return Owner;
	}

	FORCEINLINE UObject* GetParent() const
	{
		return Parent;
	}

	FORCEINLINE void Allocate()
	{
		bAllocated = true;
	}

	void Reset()
	{
		bAllocated = false;
		Instigator = nullptr;
		Owner = nullptr;
		Parent = nullptr;

		Direction = FVector::ZeroVector;
		Location = FVector::ZeroVector;
	}

#pragma endregion ICsPooledObjectPayload

public:

	template<typename T>
	FORCEINLINE T* GetInstigator() const
	{
		return Cast<T>(GetInstigator());
	}

	template<typename T>
	FORCEINLINE T* GetOwner() const
	{
		return Cast<T>(GetOwner());
	}

	template<typename T>
	FORCEINLINE T* GetParent() const
	{
		return Cast<T>(GetParent());
	}

// ICsProjectilePayload
#pragma region
public:

	FORCEINLINE const FVector& GetDirection() const
	{
		return Direction;
	}

	FORCEINLINE const FVector& GetLocation() const
	{
		return Location;
	}

#pragma endregion ICsProjectilePayload
};

#pragma endregion FCsProjectilePayload

// FCsScriptProjectilePayload
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSPRJ_API FCsScriptProjectilePayload : public FCsScriptPooledObjectPayload
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	FVector Location;

	UPROPERTY(BlueprintReadWrite)
	FVector Direction;

	FCsScriptProjectilePayload() :
		Super(),
		Location(0.0f),
		Direction(0.0f)
	{
	}
	~FCsScriptProjectilePayload() {}
};

#pragma endregion FCsScriptProjectilePayload

// ICsProjectileCache
#pragma region

struct CSPRJ_API ICsProjectileCache : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsProjectileCache(){}
};

#pragma endregion ICsProjectileCache

// FCsProjectileCache
#pragma region

class UObject;

struct CSPRJ_API FCsProjectileCache : public ICsPooledObjectCache,
									  public ICsProjectileCache
{
private:

	FCsInterfaceMap* InterfaceMap;

	int32 Index;

	bool bAllocated;

	bool bQueueDeallocate;

	ECsPooledObjectState State;

	ECsPooledObjectUpdate UpdateType;

	TCsWeakObjectPtr<UObject> Instigator;

	TCsWeakObjectPtr<UObject> Owner;

	TCsWeakObjectPtr<UObject> Parent;

	float WarmUpTime;

	float LifeTime;

	FCsTime StartTime;

	FCsDeltaTime ElapsedTime;

public:

	FCsProjectileCache() : 
		InterfaceMap(nullptr),
		Index(INDEX_NONE),
		bAllocated(false),
		bQueueDeallocate(false),
		State(ECsPooledObjectState::Inactive),
		UpdateType(ECsPooledObjectUpdate::Manager),
		Instigator(),
		Owner(),
		Parent(),
		WarmUpTime(0.0f),
		LifeTime(0.0f),
		StartTime(),
		ElapsedTime()
	{
		InterfaceMap = new FCsInterfaceMap();

		InterfaceMap->Add<ICsPooledObjectCache>(static_cast<ICsPooledObjectCache*>(this));
		InterfaceMap->Add<ICsProjectileCache>(static_cast<ICsProjectileCache*>(this));
	}

	~FCsProjectileCache()
	{
		delete InterfaceMap;
	}

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

// ICsPooledObjectCache
#pragma region
public:

	void Init(const int32& InIndex)
	{
		Index = InIndex;
	}

	FORCEINLINE const int32& GetIndex() const
	{
		return Index;
	}

	void Allocate(ICsPooledObjectPayload* Payload, const FCsTime& InTime)
	{

	}

	FORCEINLINE const bool& IsAllocated() const
	{
		return bAllocated;
	}

	void Deallocate()
	{
		bAllocated = false;
		bQueueDeallocate = false;
	}

	FORCEINLINE void QueueDeallocate()
	{
		bQueueDeallocate = true;
	}

	FORCEINLINE const bool& ShouldDeallocate() const
	{
		return bQueueDeallocate;
	}

	FORCEINLINE const ECsPooledObjectState& GetState() const
	{
		return State;
	}

	FORCEINLINE const ECsPooledObjectUpdate& GetUpdateType() const
	{
		return UpdateType;
	}

	FORCEINLINE UObject* GetInstigator() const
	{
		return Instigator.Get();
	}

	FORCEINLINE UObject* GetOwner() const
	{
		return Owner.Get();
	}

	FORCEINLINE UObject* GetParent() const
	{
		return Parent.Get();
	}

	FORCEINLINE const float& GetWarmUpTime() const
	{
		return WarmUpTime;
	}

	FORCEINLINE const float& GetLifeTime() const
	{
		return LifeTime;
	}

	FORCEINLINE const FCsTime& GetStartTime() const
	{
		return StartTime;
	}

	FORCEINLINE const FCsDeltaTime& GetElapsedTime() const
	{
		return ElapsedTime;
	}

	FORCEINLINE bool HasLifeTimeExpired()
	{
		return false;
	}

	void Reset()
	{

	}

#pragma endregion ICsPooledObjectCache

// ICsProjectileCache
#pragma region
public:

#pragma endregion ICsProjectileCache
};

#pragma endregion FCsProjectileCache

// FCsProjectileEntry
#pragma region

USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileEntry : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;

	FCsProjectileEntry() :
		Name(),
		DisplayName()
	{
	}
};

#pragma endregion FCsProjectileEntry