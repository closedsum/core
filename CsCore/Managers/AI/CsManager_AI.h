// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/CsManager.h"
#include "Types/CsTypes_AI.h"
#include "CsManager_AI.generated.h"

#define CS_AI_PAWN_PAYLOAD_SIZE 256

UCLASS()
class CSCORE_API ACsManager_AI : public ACsManager
{
	GENERATED_UCLASS_BODY()

protected:

	static TWeakObjectPtr<UObject> MyOwner;

public:

	static UObject* GetMyOwner();
	template<typename T>
	static T* GetMyOwner()
	{
		return Cast<T>(GetMyOwner());
	}

	virtual void Shutdown() override;
	virtual void Destroyed() override;

	static void Init(UObject* InOwner);
	static ACsManager_AI* Get(UWorld* InWorld);

	virtual void CreatePool(const TSubclassOf<class UObject> &ObjectClass, const uint8 &Type, const int32 &Size);
	virtual void AddToPool(UObject* InObject, const uint8& Type);
	virtual void AddToActivePool(UObject* InObject, const uint8& Type);
	virtual void OnTick(const float &DeltaSeconds) override;

	TMap<FECsAIType, uint8> PoolSizes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pool")
	TArray<class ACsAIController*> ControllerPool;

	TMap<FECsAIType, TArray<class ACsAIController*>> ControllerPools;
	TMap<FECsAIType, TArray<class ACsAIController*>> ActiveControllers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pool")
	TArray<class ACsAIPawn*> Pool;

	TMap<FECsAIType, TArray<class ACsAIPawn*>> Pools;
	TMap<FECsAIType, TArray<class ACsAIPawn*>> ActivePawns;
	TMap<FECsAIType, uint8> PoolIndices;

	virtual int32 GetActivePoolSize(const uint8 &Type) override;

private:

	virtual void LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, class UObject* InObject) override;

	class ACsAIPawn* Allocate(const FECsAIType &Type);

	virtual void DeAllocate(const uint8 &Type, const int32 &Index) override;
	virtual void DeAllocateAll() override;

// Payload
#pragma region
private:

	FCsAIPawnPayload Payloads[CS_AI_PAWN_PAYLOAD_SIZE];

	uint8 PayloadIndex;

public:

	FCsAIPawnPayload* AllocatePayload();

#pragma endregion Payload

// Wake Up
#pragma region
public:

	class ACsAIPawn* WakeUp(const FECsAIType &Type, FCsAIPawnPayload* Payload, UObject* InOwner, UObject* Parent);
	class ACsAIPawn* WakeUp(const FECsAIType &Type, FCsAIPawnPayload* Payload, UObject* InOwner);
	class ACsAIPawn* WakeUp(const FECsAIType &Type, FCsAIPawnPayload* Payload);

	template<typename T>
	void WakeUp(const FECsAIType &Type, class ACsAIPawn* &OutPawn, FCsAIPawnPayload* Payload, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void WakeUp(const FECsAIType &Type, class ACsAIPawn* &OutPawn, FCsAIPawnPayload* Payload, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void WakeUp(const FECsAIType &Type, class ACsAIPawn* &OutPawn, FCsAIPawnPayload* Payload, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));

#pragma endregion Wake Up
};