// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/CsManager.h"
#include "Types/CsTypes_Interactive.h"
#include "CsManager_InteractiveActor.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsManagerInteractiveActor_OnDeAllocateEX_Internal, const uint16&, const uint16&, const ECsInteractiveType::Type&);

#define CS_INTERACTIVE_ACTOR_PAYLOAD_SIZE 255

UCLASS()
class CSCORE_API ACsManager_InteractiveActor : public ACsManager
{
	GENERATED_UCLASS_BODY()

	static ACsManager_InteractiveActor* Get(UWorld* InWorld);

	virtual void Clear() override;
	virtual void Shutdown() override;

	CS_DECLARE_INTERACTIVE_TYPE

	void SetInteractiveActorType(const TCsInteractiveType &InInteractiveType_MAX, TCsInteractiveTypeToString InInteractiveTypeToString);

	virtual void Destroyed() override;
	virtual void CreatePool(const TSubclassOf<class UObject> &ObjectClass, const uint8 &Type, const int32 &Size) override;
	virtual void AddToPool(UObject* InObject, const uint8& Type) override;
	virtual void AddToActivePool(UObject* InObject, const uint8& Type) override;
	virtual void OnTick(const float &DeltaSeconds) override;

	TMap<TCsInteractiveType, uint16> PoolSizes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pool")
	TArray<class ACsInteractiveActor*> Pool;

	TMap<TCsInteractiveType, TArray<class ACsInteractiveActor*>> Pools;

	TMap<TCsInteractiveType, uint16> PoolIndices;

	TMap<TCsInteractiveType, TArray<class ACsInteractiveActor*>> ActiveActors;

public:

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void GetAllActiveActors(TArray<class ACsInteractiveActor*> &OutActors);

	const TArray<class ACsInteractiveActor*>* GetActors(const TCsInteractiveType& Type);

	virtual int32 GetActivePoolSize(const uint8& Type) override;

	virtual bool IsExhausted(const uint8 &Type) override;

	virtual void LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, class UObject* InObject) override;

// Allocate / DeAllocate
#pragma region
public:

	class ACsInteractiveActor* Allocate(const TCsInteractiveType &Type);

	virtual void DeAllocate(const uint8 &Type, const int32 &Index) override;
	virtual void DeAllocateAll() override;

	virtual void OnDeAllocate(const uint16 &Index, const uint16 &ActiveIndex, const uint8 &Type);

	FBindableEvent_CsManagerInteractiveActor_OnDeAllocateEX_Internal OnDeAllocateEX_Internal_Event;

#pragma endregion Allocate / DeAllocate

// Payload
#pragma region
private:

	FCsInteractiveActorPayload Payloads[CS_INTERACTIVE_ACTOR_PAYLOAD_SIZE];

	uint8 PayloadIndex;

public:

	FCsInteractiveActorPayload* AllocatePayload();

#pragma endregion Payload

// WakeUp
#pragma region

	class ACsInteractiveActor* WakeUp(const TCsInteractiveType &Type, FCsInteractiveActorPayload* Payload, UObject* InOwner, UObject* Parent);
	class ACsInteractiveActor* WakeUp(const TCsInteractiveType &Type, FCsInteractiveActorPayload* Payload, UObject* InOwner);
	class ACsInteractiveActor* WakeUp(const TCsInteractiveType &Type, FCsInteractiveActorPayload* Payload);

	template<typename T>
	void WakeUp(const TCsInteractiveType &Type, class ACsInteractiveActor* &OutActor, FCsInteractiveActorPayload* Payload, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void WakeUp(const TCsInteractiveType &Type, class ACsInteractiveActor* &OutActor, FCsInteractiveActorPayload* Payload, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void WakeUp(const TCsInteractiveType &Type, class ACsInteractiveActor* &OutActor, FCsInteractiveActorPayload* Payload, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));

#pragma endregion WakeUp
};