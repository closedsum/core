// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/CsManager.h"
#include "Types/CsTypes.h"
#include "CsManager_AI.generated.h"

typedef FString(*TCsAITypeToString)(const ECsAIType::Type&);

UCLASS()
class CSCORE_API ACsManager_AI : public ACsManager
{
	GENERATED_UCLASS_BODY()

	virtual void Shutdown() override;

	TCsAIType AIType_MAX;

	TCsAITypeToString AITypeToString;

	void Init(const TCsAIType &InAIType_MAX, TCsAITypeToString InAITypeToString);

	virtual void Destroyed() override;
	virtual void CreatePool(const TSubclassOf<class UObject> &ObjectClass, const uint8 &Type, const int32 &Size);
	virtual void AddToPool(UObject* InObject, const uint8& Type);
	virtual void AddToActivePool(UObject* InObject, const uint8& Type);
	virtual void OnTick(const float &DeltaSeconds) override;

	static ACsManager_AI* Get(UWorld* InWorld);

	TMap<TCsAIType, uint8> PoolSizes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pool")
	TArray<class ACsAIPawn*> Pool;

	TMap<TCsAIType, TArray<class ACsAIPawn*>> Pools;

	TMap<TCsAIType, uint8> PoolIndices;

	TMap<TCsAIType, TArray<class ACsAIPawn*>> ActiveAIPawns;

	virtual int32 GetActivePoolSize(const uint8 &Type) override;

	class ACsAIPawn* Allocate(const TCsAIType &Type);

	virtual void DeAllocate(const uint8 &Type, const int32 &Index) override;
	virtual void DeAllocateAll() override;

	class ACsAIPawn* WakeUp(const TCsAIType &Type, UObject* InOwner, UObject* Parent);
	class ACsAIPawn* WakeUp(const TCsAIType &Type, UObject* InOwner);
	class ACsAIPawn* WakeUp(const TCsAIType &Type);

	template<typename T>
	void WakeUp(const TCsAIType &Type, class ACsAIPawn* &OutPawn, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void WakeUp(const TCsAIType &Type, class ACsAIPawn* &OutPawn, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void WakeUp(const TCsAIType &Type, class ACsAIPawn* &OutPawn, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
};