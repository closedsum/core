// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"
#include "Types/Property/Multi/CsProperty_Multi_FString_Enum_ThreeParams.h"

#include "CsTypes_Pool.generated.h"

// PoolTransaction
#pragma region

/**
* Type of transaction that is being executed for a Pooled Object.
*/
UENUM(BlueprintType)
enum class ECsPoolTransaction : uint8
{
	Allocate				UMETA(DisplayName = "Allocate"),
	Spawn					UMETA(DisplayName = "Spawn"),
	PreDeallocate			UMETA(DisplayName = "Pre-Deallocate"),
	Deallocate				UMETA(DisplayName = "Deallocate"),
	DeallocateByQueue		UMETA(DisplayName = "Deallocate by Queue"),
	DeallocateByUnknown		UMETA(DisplayName = "Deallocate by Unknown"),
	DeallocateByLifeTime	UMETA(DisplayName = "Deallocate by LifeTime"),
	Destroy					UMETA(DisplayName = "Destroy"),
	ECsPoolTransaction_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsPoolTransaction final : public TCsEnumMap<ECsPoolTransaction>
{
	CS_ENUM_MAP_BODY(EMCsPoolTransaction, ECsPoolTransaction)
};

namespace NCsPoolTransaction
{
	typedef ECsPoolTransaction Type;

	namespace Ref
	{
		extern CSCORE_API const Type Allocate;
		extern CSCORE_API const Type Spawn;
		extern CSCORE_API const Type PreDeallocate;
		extern CSCORE_API const Type Deallocate;
		extern CSCORE_API const Type DeallocateByQueue;
		extern CSCORE_API const Type DeallocateByUnknown;
		extern CSCORE_API const Type DeallocateByLifeTime;
		extern CSCORE_API const Type Destroy;
		extern CSCORE_API const Type ECsPoolTransaction_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		extern CSCORE_API const TCsString Allocate;
		extern CSCORE_API const TCsString PreDeallocate;
		extern CSCORE_API const TCsString Deallocate;
	}

	FORCEINLINE const FString& ToActionString(const Type &EType)
	{
		if (EType == Type::Allocate) { return Str::Allocate.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::PreDeallocate) { return Str::PreDeallocate.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::Deallocate) { return Str::Deallocate.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		return CS_INVALID_ENUM_TO_STRING;
	}
}

#define ECS_POOL_TRANSACTION_MAX NCsPoolTransaction::MAX

#pragma endregion PoolTransaction

// PoolTransactionOrder
#pragma region

UENUM(BlueprintType)
enum class ECsPoolTransactionOrder : uint8
{
	FillAny						UMETA(DisplayName = "Fill Any"),
	FillOrKill					UMETA(DisplayName = "Fill Or Kill"),
	ECsPoolTransactionOrder_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsPoolTransactionOrder final : public TCsEnumMap<ECsPoolTransactionOrder>
{
	CS_ENUM_MAP_BODY(EMCsPoolTransactionOrder, ECsPoolTransactionOrder)
};

namespace NCsPoolTransactionOrder
{
	typedef ECsPoolTransactionOrder Type;

	namespace Ref
	{
		extern CSCORE_API const Type FillAny;
		extern CSCORE_API const Type FillOrKill;
		extern CSCORE_API const Type ECsPoolTransactionOrder_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion PoolTransactionOrder

// PooledObjectState
#pragma region

UENUM(BlueprintType)
enum class ECsPooledObjectState : uint8
{
	WarmUp						UMETA(DisplayName = "Warm Up"),
	Active						UMETA(DisplayName = "Active"),
	Inactive					UMETA(DisplayName = "Inactive"),
	ECsPooledObjectState_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsPooledObjectState final : public TCsEnumMap<ECsPooledObjectState>
{
	CS_ENUM_MAP_BODY(EMCsPooledObjectState, ECsPooledObjectState)
};

namespace NCsPooledObjectState
{
	typedef ECsPooledObjectState Type;

	namespace Ref
	{
		extern CSCORE_API const Type WarmUp;
		extern CSCORE_API const Type Active;
		extern CSCORE_API const Type Inactive;
		extern CSCORE_API const Type ECsPooledObjectState_MAX;
	}
}

namespace NCsPooledObject
{
	enum class EState : uint8
	{
		WarmUp,
		Active,
		Inactive,
		EState_MAX
	};

	struct CSCORE_API EMState final : public TCsEnumMap<EState>
	{
		CS_ENUM_MAP_BODY(EMState, EState)
	};

	namespace NState
	{
		typedef EState Type;

		namespace Ref
		{
			extern CSCORE_API const Type WarmUp;
			extern CSCORE_API const Type Active;
			extern CSCORE_API const Type Inactive;
			extern CSCORE_API const Type EState_MAX;
		}
	}
}

#pragma endregion PooledObjectState

// PooledObjectConstruction
#pragma region

/**
* Describes what type of pooled object to construct.
* NOTE: Currently only objects of type: UObject are supported
*/
UENUM(BlueprintType)
enum class ECsPooledObjectConstruction : uint8
{
	/** Construct a UObject via NewObject */
	Object							UMETA(DisplayName = "Object"),
	/** Construct a AActor via SpawnActor */
	Actor							UMETA(DisplayName = "Actor"),
	/** Construct a UObject via a custom method */
	CustomObject					UMETA(DisplayName = "Custom Object"),
	ECsPooledObjectConstruction_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsPooledObjectConstruction final : public TCsEnumMap<ECsPooledObjectConstruction>
{
	CS_ENUM_MAP_BODY(EMCsPooledObjectConstruction, ECsPooledObjectConstruction)
};

namespace NCsPooledObjectConstruction
{
	typedef ECsPooledObjectConstruction Type;

	namespace Ref
	{
		extern CSCORE_API const Type Object;
		extern CSCORE_API const Type Actor;
		extern CSCORE_API const Type CustomObject;
		extern CSCORE_API const Type ECsPooledObjectConstruction_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsPooledObject
{
	/**
	* Describes what type of pooled object to construct.
	* NOTE: Currently only objects of type: UObject are supported
	*/
	enum class EConstruction : uint8 
	{
		/** Construct a UObject via NewObject */
		Object,
		/** Construct a AActor via SpawnActor */
		Actor,
		/** Construct a UObject via a custom method */
		CustomObject,
		EConstruction_MAX
	};

	struct CSCORE_API EMConstruction final : public TCsEnumMap<EConstruction>
	{
		CS_ENUM_MAP_BODY(EMConstruction, EConstruction)
	};

	namespace NConstruction
	{
		namespace Ref
		{
			typedef EConstruction Type;

			extern CSCORE_API const Type Object;
			extern CSCORE_API const Type Actor;
			extern CSCORE_API const Type CustomObject;
			extern CSCORE_API const Type EConstruction_MAX;
		}
	}
}

#pragma endregion PooledObjectContruction

// PooledObjectUpdate
#pragma region

UENUM(BlueprintType)
enum class ECsPooledObjectUpdate : uint8
{
	/** */
	None						UMETA(DisplayName = "None"),
	/** */
	Self						UMETA(DisplayName = "Self"),
	/** */
	Manager						UMETA(DisplayName = "Manager"),
	/** */
	Owner						UMETA(DisplayName = "Owner"),
	/** */
	Instigator					UMETA(DisplayName = "Instigator"),
	ECsPooledObjectUpdate_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsPooledObjectUpdate final : public TCsEnumMap<ECsPooledObjectUpdate>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsPooledObjectUpdate, ECsPooledObjectUpdate)
};

namespace NCsPooledObjectUpdate
{
	typedef ECsPooledObjectUpdate Type;

	namespace Ref
	{
		extern CSCORE_API const Type None;
		extern CSCORE_API const Type Self;
		extern CSCORE_API const Type Manager;
		extern CSCORE_API const Type Owner;
		extern CSCORE_API const Type Instigator;
		extern CSCORE_API const Type ECsPooledObjectUpdate_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsPooledObject
{
	/**
	*/
	enum class EUpdate : uint8 
	{
		/** */
		None,
		/** */
		Self,
		/** */
		Manager,
		/** */
		Owner,
		/** */
		Instigator,
		EUpdate_MAX
	};

	struct CSCORE_API EMUpdate final : public TCsEnumMap<EUpdate>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMUpdate, EUpdate)
	};

	namespace NUpdate
	{
		namespace Ref
		{
			typedef EUpdate Type;

			extern CSCORE_API const Type None;
			extern CSCORE_API const Type Self;
			extern CSCORE_API const Type Manager;
			extern CSCORE_API const Type Owner;
			extern CSCORE_API const Type Instigator;
			extern CSCORE_API const Type EUpdate_MAX;
		}
	}
}

#pragma endregion PooledObjectUpdate

// FCsPooledObjectCache
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSCORE_API FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Pool")
	int32 Index;

	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Pool")
	bool bAllocated;

	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Pool")
	ECsPooledObjectState State;

	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Pool")
	TWeakObjectPtr<UObject> Instigator;
	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Pool")
	TWeakObjectPtr<UObject> Owner;
	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Pool")
	TWeakObjectPtr<UObject> Parent;

	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Pool")
	float WarmUpTime;
	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Pool", meta = (ScriptName = "m_bLifeTime"))
	bool bLifeTime;
	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Pool", meta = (ScriptName = "m_LifeTime"))
	float LifeTime;

	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Pool")
	float Time;
	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Pool")
	float RealTime;

	UPROPERTY()
	uint64 Frame;
	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Pool")
	int32 Frame_Script;

	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Pool")
	float ElapsedTime;

public:

	FCsPooledObjectCache() :
		Index(0)
	{
		Reset();
	}

	virtual ~FCsPooledObjectCache() {}

	virtual void Reset()
	{
		bAllocated = false;
		State = ECsPooledObjectState::Inactive;

		Instigator.Reset();
		Instigator = nullptr;
		Owner.Reset();
		Owner = nullptr;
		Parent.Reset();
		Parent = nullptr;
		WarmUpTime = 0.0f;
		SetLifeTime(0.0f);
		Time = 0.0f;
		RealTime = 0.0f;
		SetFrame(0);
		ElapsedTime = 0.0f;
	}

public:

	void SetFrame(const uint64 &InFrame)
	{
		Frame = InFrame;
		Frame_Script = (int32)Frame;
	}

	void SetLifeTime(const float &InLifeTime)
	{
		LifeTime = InLifeTime;
		bLifeTime = LifeTime > 0.0f;
	}

	FORCEINLINE UObject* GetInstigator() { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetInstigator() { return Cast<T>(GetInstigator()); }

	FORCEINLINE UObject* GetOwner() { return Owner.IsValid() ? Owner.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetOwner() { return Cast<T>(GetOwner()); }

	FORCEINLINE UObject* GetParent() { return Parent.IsValid() ? Parent.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetParent() { return Cast<T>(GetParent()); }

	void DeAllocate()
	{
		Reset();
	}
};

#pragma endregion FCsPooledObjectCache

// ManagerPooledObject
#pragma region

UENUM(BlueprintType)
enum class ECsManagerPooledObject : uint8
{
	Dynamic						UMETA(DisplayName = "Dynamic"),
	Fixed						UMETA(DisplayName = "Fixed"),
	ECsManagerPooledObject_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsManagerPooledObject final : public TCsEnumMap<ECsManagerPooledObject>
{
	CS_ENUM_MAP_BODY(EMCsManagerPooledObject, ECsManagerPooledObject)
};

namespace NCsManagerPooledObject
{
	typedef ECsManagerPooledObject Type;

	namespace Ref
	{
		extern CSCORE_API const Type Dynamic;
		extern CSCORE_API const Type Fixed;
		extern CSCORE_API const Type ECsManagerPooledObject_MAX;
	}
}

#pragma endregion ManagerPooledObject