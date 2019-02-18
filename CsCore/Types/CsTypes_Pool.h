// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_Primitive.h"
#include "Types/CsTypes_Load.h"

#include "CsTypes_Pool.generated.h"
#pragma once

// Pooled Objects
#pragma region

UENUM(BlueprintType)
namespace ECsPoolTransaction
{
	enum Type
	{
		Allocate				UMETA(DisplayName = "Allocate"),
		PreDeallocate			UMETA(DisplayName = "Pre-Deallocate"),
		Deallocate				UMETA(DisplayName = "Deallocate"),
		ECsPoolTransaction_MAX	UMETA(Hidden),
	};
}

namespace ECsPoolTransaction
{
	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Allocate = TCsString(TEXT("Allocate"), TEXT("allocate"), TEXT("Allocating"));
		const TCsString PreDeallocate = TCsString(TEXT("PreDeallocate"), TEXT("predeallocate"), TEXT("PreDeallocating"));
		const TCsString Deallocate = TCsString(TEXT("Deallocate"), TEXT("deallocate"), TEXT("Deallocating"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Allocate) { return Str::Allocate.Value; }
		if (EType == Type::PreDeallocate) { return Str::PreDeallocate.Value; }
		if (EType == Type::Deallocate) { return Str::Deallocate.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const FString& ToActionString(const Type &EType)
	{
		if (EType == Type::Allocate) { return Str::Allocate.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::PreDeallocate) { return Str::PreDeallocate.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::Deallocate) { return Str::Deallocate.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Allocate) { return Type::Allocate; }
		if (String == Str::PreDeallocate) { return Type::PreDeallocate; }
		if (String == Str::Deallocate) { return Type::Deallocate; }
		return Type::ECsPoolTransaction_MAX;
	}
}

#define ECS_POOL_TRANSACTION_MAX (uint8)ECsPoolTransaction::ECsPoolTransaction_MAX
typedef ECsPoolTransaction::Type TCsPoolTransaction;

UENUM(BlueprintType)
namespace ECsPoolTransactionOrder
{
	enum Type
	{
		FillAny						UMETA(DisplayName = "Fill Any"),
		FillOrKill					UMETA(DisplayName = "Fill Or Kill"),
		ECsPoolTransactionOrder_MAX	UMETA(Hidden),
	};
}

typedef ECsPoolTransactionOrder::Type TCsPoolTransactionOrder;

struct CSCORE_API EMCsPoolTransactionOrder : public TCsEnumMap<ECsPoolTransactionOrder::Type>
{
protected:
	EMCsPoolTransactionOrder() {}
	EMCsPoolTransactionOrder(const EMCsPoolTransactionOrder &) = delete;
	EMCsPoolTransactionOrder(EMCsPoolTransactionOrder &&) = delete;
public:
	~EMCsPoolTransactionOrder() {}
private:
	static EMCsPoolTransactionOrder* Instance;

public:
	static EMCsPoolTransactionOrder& Get();
};

namespace ECsPoolTransactionOrder
{
	namespace Ref
	{
		extern CSCORE_API const Type FillAny;
		extern CSCORE_API const Type FillOrKill;
		extern CSCORE_API const Type ECsPoolTransactionOrder_MAX;
	}
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