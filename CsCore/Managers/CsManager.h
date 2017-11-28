// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
#include "Types/CsTypes_Primitive.h"
#include "CsManager.generated.h"

// OnAllocate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManager_OnAllocate, const int32&, PoolIndex);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsManager_OnAllocate, const uint16&);
// OnDeAllocate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManager_OnDeAllocate, const int32&, PoolIndex);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsManager_OnDeAllocate, const uint16&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsManager_OnDeAllocateEX, const int32&, PoolIndex, const int32&, ActiveIndex, const uint8&, Type);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsManager_OnDeAllocateEX, const uint16&, const uint16&, const uint8&);

// Enums
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
	typedef FCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Allocate = TCsString(TEXT("Allocate"), TEXT("allocate"));
		const TCsString PreDeallocate = TCsString(TEXT("PreDeallocate"), TEXT("predeallocate"));
		const TCsString Deallocate = TCsString(TEXT("Deallocate"), TEXT("deallocate"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Allocate) { return Str::Allocate.Value; }
		if (EType == Type::PreDeallocate) { return Str::PreDeallocate.Value; }
		if (EType == Type::Deallocate) { return Str::Deallocate.Value; }
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
typedef TEnumAsByte<ECsPoolTransaction::Type> TCsPoolTransaction;

#pragma endregion Enums

UCLASS()
class CSCORE_API ACsManager : public AActor
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void Clear();
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void Shutdown();
	
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void CreatePool(const TSubclassOf<class UObject> &ObjectClass, const uint8 &Type, const int32 &Size);
	virtual void CreatePool(const TSubclassOf<class UObject> &ObjectClass, const int32 &Size);
	virtual void CreatePool(const int32 &Size);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	void CreatePool_Script(const int32 &Size);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void AddToPool(UObject* InObject, const uint8 &Type);
	virtual void AddToPool(const TSubclassOf<class UObject> &ObjectClass, const uint8 &Type, const int32 &Size);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void AddToActivePool(UObject* InObject, const uint8 &Type);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual int32 GetActivePoolSize(const uint8& Type);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual bool IsExhausted(const uint8 &Type);
	virtual void OnTick(const float &DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, UObject* InObject);

// Allocate
#pragma region

	UPROPERTY(BlueprintAssignable, Category = "Pool")
	FBindableDynEvent_CsManager_OnAllocate OnAllocate_ScriptEvent;

	FBindableEvent_CsManager_OnAllocate OnAllocate_Event;
	
#pragma endregion Allocate

// DeAllocate
#pragma region

	virtual void DeAllocate(const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	void DeAllocate_Script(const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void DeAllocate(const uint8 &Type, const int32 &Index);

	UPROPERTY(BlueprintAssignable, Category = "Pool")
	FBindableDynEvent_CsManager_OnDeAllocate OnDeAllocate_ScriptEvent;

	FBindableEvent_CsManager_OnDeAllocate OnDeAllocate_Event;

	UPROPERTY(BlueprintAssignable, Category = "Pool")
	FBindableDynEvent_CsManager_OnDeAllocateEX OnDeAllocateEX_ScriptEvent;

	FBindableEvent_CsManager_OnDeAllocateEX OnDeAllocateEX_Event;

	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void DeAllocateAll();

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void DeAllocateAll_Script();

#pragma endregion DeAllocate

	UPROPERTY(BlueprintReadWrite, Category = "Pool")
	int32 PoolSize;
};