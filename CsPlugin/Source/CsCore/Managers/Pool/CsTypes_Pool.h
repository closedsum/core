// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

#include "CsTypes_Pool.generated.h"
#pragma once

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
	CS_ENUM_MAP_BODY(EMCsPoolTransaction, ECsPoolTransaction)
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

UENUM(BlueprintType)
enum class ECsPooledObjectState : uint8
{
	WarmUp						UMETA(DisplayName = "Warm Up"),
	Active						UMETA(DisplayName = "Active"),
	Inactive					UMETA(DisplayName = "Inactive"),
	ECsPooledObjectState_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsPoolObjectState : public TCsEnumMap<ECsPooledObjectState>
{
	CS_ENUM_MAP_BODY(EMCsPoolObjectState, ECsPooledObjectState)
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

class UObject;

USTRUCT(BlueprintType)
struct CSCORE_API FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "Cache")
	int32 Index;

	UPROPERTY(BlueprintReadWrite, Category = "Cache")
	bool bAllocated;

	UPROPERTY(BlueprintReadWrite, Category = "Cache")
	ECsPooledObjectState State;

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

class UObject;

USTRUCT(BlueprintType)
struct CSCORE_API FCsPooledObjectPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	bool bAllocated;

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
		bAllocated = false;

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

class UObject;
struct ICsPooledObjectPayload;

struct CSCORE_API ICsPooledObjectCache
{
	virtual const int32& GetIndex() const = 0;

	virtual const bool& IsAllocated() const = 0;

	virtual const ECsPooledObjectState& GetState() const = 0;

	virtual UObject* GetInstigator() const = 0;

	virtual UObject* GetOwner() const = 0;

	virtual UObject* GetParent() const = 0;

	virtual const float& GetWarmUpTime() const = 0;

	virtual const bool& UseLifeTime() const = 0;

	virtual const float& GetLifeTime() const = 0;

	virtual const float& GetTime() const = 0;

	virtual const float& GetRealTime() const = 0;

	virtual const uint64& GetFrame() const = 0;

	virtual const float& GetElapsedTime() const = 0;

	virtual void Init(const int32& InIndex) = 0;

	virtual void Allocate(ICsPooledObjectPayload* Payload, const float& InTime, const float& InRealTime, const uint64& InFrame) = 0;

	virtual void Deallocate() = 0;

	virtual void Reset() = 0;
};

class UObject;

struct CSCORE_API ICsPooledObjectPayload
{
	virtual const bool& IsAllocated() const = 0;

	virtual UObject* GetInstigator() const = 0;

	virtual UObject* GetOwner() const = 0;

	virtual UObject* GetParent() const = 0;

	virtual void Allocate() = 0;

	virtual void Reset() = 0;
};

class UWorld;

class CSCORE_API ICsManager_PooledObjects
{
	virtual void Clear() = 0;
	virtual void Shutdown() = 0;

	virtual UWorld* GetCurrentWorld() = 0;
};