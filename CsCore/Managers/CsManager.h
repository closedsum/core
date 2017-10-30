// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
#include "Types/CsTypes_Primitive.h"
#include "CsManager.generated.h"

// Enums
#pragma region

UENUM(BlueprintType)
namespace ECsPoolTransaction
{
	enum Type
	{
		Allocate				UMETA(DisplayName = "Allocate"),
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
		const TCsString Deallocate = TCsString(TEXT("Deallocate"), TEXT("deallocate"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Allocate) { return Str::Allocate.Value; }
		if (EType == Type::Deallocate) { return Str::Deallocate.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Allocate) { return Type::Allocate; }
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
	virtual void CreatePool(const TSubclassOf<class AActor> &ActorClass, const uint8 &Type, const int32 &Size);
	virtual void CreatePool(const int32 &Size);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	void CreatePool_Script(const int32 &Size);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void AddToPool(AActor* InActor, const uint8 &Type);
	virtual void AddToPool(const TSubclassOf<class AActor> &ActorClass, const uint8 &Type, const int32 &Size);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void AddToActivePool(AActor* InActor, const uint8 &Type);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual int32 GetActivePoolSize(const uint8& Type);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual bool IsExhausted(const uint8 &Type);
	virtual void OnTick(const float &DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, UObject* InObject);

	virtual void DeAllocate(const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	void DeAllocate_Script(const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void DeAllocate(const uint8 &Type, const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void DeAllocateAll();

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void DeAllocateAll_Script();

	UPROPERTY(BlueprintReadWrite, Category = "Pool")
	int32 PoolSize;
};