// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_Primitive.h"
#include "Types/CsTypes_Load.h"

#include "CsTypes_Pool.generated.h"
#pragma once

// Pooled Objects
#pragma region

	// PoolTransaction
#pragma region

UENUM(BlueprintType)
enum class ECsPoolTransaction : uint8
{
	Allocate				UMETA(DisplayName = "Allocate"),
	PreDeallocate			UMETA(DisplayName = "Pre-Deallocate"),
	Deallocate				UMETA(DisplayName = "Deallocate"),
	ECsPoolTransaction_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsPoolTransaction : public TCsEnumMap<ECsPoolTransaction>
{
	CS_DECLARE_ENUM_MAP_BODY(EMCsPoolTransaction)
};

namespace NCsPoolTransaction
{
	typedef ECsPoolTransaction Type;

	namespace Ref
	{
		extern CSCORE_API const Type Allocate;
		extern CSCORE_API const Type PreDeallocate;
		extern CSCORE_API const Type Deallocate;
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

UENUM(BlueprintType)
enum class ECsPoolTransactionOrder : uint8
{
	FillAny						UMETA(DisplayName = "Fill Any"),
	FillOrKill					UMETA(DisplayName = "Fill Or Kill"),
	ECsPoolTransactionOrder_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsPoolTransactionOrder : public TCsEnumMap<ECsPoolTransactionOrder>
{
	CS_DECLARE_ENUM_MAP_BODY(EMCsPoolTransactionOrder)
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

UENUM(BlueprintType)
namespace ECsPooledObjectState
{
	enum Type
	{
		WarmUp						UMETA(DisplayName = "Warm Up"),
		Active						UMETA(DisplayName = "Active"),
		Inactive					UMETA(DisplayName = "Inactive"),
		ECsPooledObjectState_MAX	UMETA(Hidden),
	};
}

typedef ECsPooledObjectState::Type TCsPooledObjectState;

struct CSCORE_API EMCsPoolObjectState : public TCsEnumMap<ECsPooledObjectState::Type>
{
protected:
	EMCsPoolObjectState() {}
	EMCsPoolObjectState(const EMCsPoolObjectState &) = delete;
	EMCsPoolObjectState(EMCsPoolObjectState &&) = delete;
public:
	~EMCsPoolObjectState() {}
private:
	static EMCsPoolObjectState* Instance;

public:
	static EMCsPoolObjectState& Get();
};

namespace ECsPooledObjectState
{
	namespace Ref
	{
		extern CSCORE_API const Type WarmUp;
		extern CSCORE_API const Type Active;
		extern CSCORE_API const Type Inactive;
		extern CSCORE_API const Type ECsPooledObjectState_MAX;
	}
}

USTRUCT(BlueprintType)
struct CSCORE_API FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "Cache")
	int32 Index;

	UPROPERTY(BlueprintReadWrite, Category = "Cache")
	bool IsAllocated;

	UPROPERTY(BlueprintReadWrite, Category = "Cache")
	TEnumAsByte<ECsPooledObjectState::Type> State;

	UPROPERTY(BlueprintReadWrite, Category = "Cache")
	TWeakObjectPtr<UObject> Instigator;
	UPROPERTY(BlueprintReadWrite, Category = "Cache")
	TWeakObjectPtr<UObject> Owner;
	UPROPERTY(BlueprintReadWrite, Category = "Cache")
	TWeakObjectPtr<UObject> Parent;

	UPROPERTY(BlueprintReadWrite, Category = "Cache")
	float WarmUpTime;
	UPROPERTY(BlueprintReadWrite, Category = "Cache")
	bool bLifeTime;
	UPROPERTY(BlueprintReadWrite, Category = "Cache")
	float LifeTime;

	UPROPERTY(BlueprintReadWrite, Category = "Cache")
	float Time;
	UPROPERTY(BlueprintReadWrite, Category = "Cache")
	float RealTime;

	UPROPERTY()
	uint64 Frame;
	UPROPERTY(BlueprintReadWrite, Category = "Cache")
	int32 Frame_Script;

	UPROPERTY(BlueprintReadWrite, Category = "Cache")
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
		IsAllocated = false;
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

USTRUCT(BlueprintType)
struct CSCORE_API FCsPooledObjectPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	bool IsAllocated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TWeakObjectPtr<UObject> Instigator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TWeakObjectPtr<UObject> Owner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TWeakObjectPtr<UObject> Parent;

	FCsPooledObjectPayload()
	{
		Reset();
	}
	virtual ~FCsPooledObjectPayload(){}

	virtual void Reset()
	{
		IsAllocated = false;

		Instigator.Reset();
		Instigator = nullptr;
		Owner.Reset();
		Owner = nullptr;
		Parent.Reset();
		Parent = nullptr;
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
};

#pragma endregion Pooled Objects