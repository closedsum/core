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

	virtual void Shutdown() override;
	virtual void Destroyed() override;

	static ACsManager_AI* Get(UWorld* InWorld);

	CS_DECLARE_AI_TYPE

	void Init(const TCsAIType &InAIType_MAX, TCsAITypeToString InAITypeToString);

	virtual void CreatePool(const TSubclassOf<class UObject> &ObjectClass, const uint8 &Type, const int32 &Size);
	virtual void AddToPool(UObject* InObject, const uint8& Type);
	virtual void AddToActivePool(UObject* InObject, const uint8& Type);
	virtual void OnTick(const float &DeltaSeconds) override;

	TMap<TCsAIType, uint8> PoolSizes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pool")
	TArray<class ACsAIController*> ControllerPool;

	TMap<TCsAIType, TArray<class ACsAIController*>> ControllerPools;
	TMap<TCsAIType, TArray<class ACsAIController*>> ActiveControllers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pool")
	TArray<class ACsAIPawn*> Pool;

	TMap<TCsAIType, TArray<class ACsAIPawn*>> Pools;
	TMap<TCsAIType, TArray<class ACsAIPawn*>> ActivePawns;
	TMap<TCsAIType, uint8> PoolIndices;

	virtual int32 GetActivePoolSize(const uint8 &Type) override;

private:

	virtual void LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, class UObject* InObject) override;

	class ACsAIPawn* Allocate(const TCsAIType &Type);

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

	class ACsAIPawn* WakeUp(const TCsAIType &Type, FCsAIPawnPayload* Payload, UObject* InOwner, UObject* Parent);
	class ACsAIPawn* WakeUp(const TCsAIType &Type, FCsAIPawnPayload* Payload, UObject* InOwner);
	class ACsAIPawn* WakeUp(const TCsAIType &Type, FCsAIPawnPayload* Payload);

	template<typename T>
	void WakeUp(const TCsAIType &Type, class ACsAIPawn* &OutPawn, FCsAIPawnPayload* Payload, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void WakeUp(const TCsAIType &Type, class ACsAIPawn* &OutPawn, FCsAIPawnPayload* Payload, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void WakeUp(const TCsAIType &Type, class ACsAIPawn* &OutPawn, FCsAIPawnPayload* Payload, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));

#pragma endregion Wake Up
};