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

namespace ECsPoolTransactionOrder
{
	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString FillAny = TCsString(TEXT("FillAny"), TEXT("fillany"), TEXT("fill any"));
		const TCsString FillOrKill = TCsString(TEXT("FillOrKill"), TEXT("fillorkill"), TEXT("fill or kill"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::FillAny) { return Str::FillAny.Value; }
		if (EType == Type::FillOrKill) { return Str::FillOrKill.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::FillAny) { return Type::FillAny; }
		if (String == Str::FillOrKill) { return Type::FillOrKill; }
		return Type::ECsPoolTransactionOrder_MAX;
	}
}

#define ECS_POOL_TRANSACTION_ORDER_MAX (uint8)ECsPoolTransactionOrder::ECsPoolTransactionOrder_MAX
typedef ECsPoolTransactionOrder::Type TCsPoolTransactionOrder;

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

namespace ECsPooledObjectState
{
	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString WarmUp = TCsString(TEXT("WarmUp"), TEXT("warmup"), TEXT("warm up"));
		const TCsString Active = TCsString(TEXT("Active"), TEXT("active"), TEXT("active"));
		const TCsString Inactive = TCsString(TEXT("Inactive"), TEXT("inactive"), TEXT("inactive"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::WarmUp) { return Str::WarmUp.Value; }
		if (EType == Type::Active) { return Str::Active.Value; }
		if (EType == Type::Inactive) { return Str::Inactive.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::WarmUp) { return Type::WarmUp; }
		if (String == Str::Active) { return Type::Active; }
		if (String == Str::Inactive) { return Type::Inactive; }
		return Type::ECsPooledObjectState_MAX;
	}
}

#define ECS_POOLED_OBJECT_STATE_MAX (uint8)ECsPooledObjectState::ECsPooledObjectState_MAX
typedef ECsPooledObjectState::Type TCsPooledObjectState;

#define CS_POOLED_OBJECT_CACHE_INVALID_TYPE 255

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsPooledObjectCache_OnDeAllocate, const int32&, PoolIndex, const int32&, ActiveIndex, const uint8&, Type);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsPooledObjectCache_OnDeAllocate, const uint16&, const uint16&, const uint8&);

USTRUCT(BlueprintType)
struct FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
	uint16 Index;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	int32 Index_Script;

	UPROPERTY()
	uint16 ActiveIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	int32 ActiveIndex_Script;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	bool IsAllocated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TEnumAsByte<ECsPooledObjectState::Type> State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	uint8 Type;

	TWeakObjectPtr<UObject> Instigator;
	TWeakObjectPtr<UObject> Owner;
	TWeakObjectPtr<UObject> Parent;
	TWeakObjectPtr<UObject> DelegateInvoker;

	UPROPERTY(BlueprintAssignable, Category = "Cache")
	FBindableDynEvent_CsPooledObjectCache_OnDeAllocate OnDeAllocate_ScriptEvent;

	FBindableEvent_CsPooledObjectCache_OnDeAllocate OnDeAllocate_Event;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	float WarmUpTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	bool bLifeTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	float LifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	float Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	float RealTime;

	UPROPERTY()
	uint64 Frame;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	int32 Frame_Script;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	float ElapsedTime;

public:

	FCsPooledObjectCache()
	{
		Reset();
	}

	virtual ~FCsPooledObjectCache() {}

	virtual void Reset()
	{
		Reset_Internal();
	}

protected:

	void Reset_Internal()
	{
		SetActiveIndex(0);

		IsAllocated = false;
		State = ECsPooledObjectState::Inactive;

		Type = CS_POOLED_OBJECT_CACHE_INVALID_TYPE;

		if (UObject* Invoker = GetDelegateInvoker())
		{
#if WITH_EDITOR
			OnDeAllocate_ScriptEvent.Clear();
#endif // #if WITH_EDITOR
			OnDeAllocate_Event.Clear();
		}

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

	void SetIndex(const uint16 &InIndex)
	{
		Index = InIndex;
		Index_Script = (int32)Index;
	}

	void SetActiveIndex(const uint16 &InActiveIndex)
	{
		ActiveIndex = InActiveIndex;
		ActiveIndex_Script = (int32)ActiveIndex;
	}

	void DecrementActiveIndex()
	{
		ActiveIndex--;
		ActiveIndex_Script--;
	}
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

	UObject* GetInstigator() { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
	template<typename T>
	T* GetInstigator() { return Cast<T>(GetInstigator()); }

	UObject* GetOwner() { return Owner.IsValid() ? Owner.Get() : nullptr; }
	template<typename T>
	T* GetOwner() { return Cast<T>(GetOwner()); }

	UObject* GetParent() { return Parent.IsValid() ? Parent.Get() : nullptr; }
	template<typename T>
	T* GetParent() { return Cast<T>(GetParent()); }

	UObject* GetDelegateInvoker() { return DelegateInvoker.IsValid() ? DelegateInvoker.Get() : nullptr; }
	template<typename T>
	T* GetDelegateInvoker() { return Cast<T>(GetDelegateInvoker()); }

	void DeAllocate()
	{
#if WITH_EDITOR
		OnDeAllocate_ScriptEvent.Broadcast(Index_Script, ActiveIndex_Script, Type);
#endif // #if WITH_EDITOR
		OnDeAllocate_Event.Broadcast(Index, ActiveIndex, Type);

		Reset();
	}
};

USTRUCT(BlueprintType)
struct FCsPooledObjectPayload
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

	FCsPooledObjectPayload(){}
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

	UObject* GetInstigator() { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
	template<typename T>
	T* GetInstigator() { return Cast<T>(GetInstigator()); }

	UObject* GetOwner() { return Owner.IsValid() ? Owner.Get() : nullptr; }
	template<typename T>
	T* GetOwner() { return Cast<T>(GetOwner()); }

	UObject* GetParent() { return Parent.IsValid() ? Parent.Get() : nullptr; }
	template<typename T>
	T* GetParent() { return Cast<T>(GetParent()); }
};

#pragma endregion Pooled Objects