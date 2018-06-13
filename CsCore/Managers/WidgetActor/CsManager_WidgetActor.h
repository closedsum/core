// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/CsManager.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_UI.h"
#include "CsManager_WidgetActor.generated.h"

#define CS_WIDGET_ACTOR_PAYLOAD_SIZE 255

UCLASS()
class CSCORE_API ACsManager_WidgetActor : public ACsManager
{
	GENERATED_UCLASS_BODY()

private:

	static TWeakObjectPtr<UObject> MyOwner;

	static UObject* GetMyOwner();

public:

	static void Init(UObject* InOwner);
	static ACsManager_WidgetActor* Get(UWorld* InWorld);

	virtual void Clear() override;
	virtual void Shutdown() override;
	virtual void Destroyed() override;
	virtual void CreatePool(const TSubclassOf<class UObject> &ObjectClass, const uint8 &Type, const int32 &Size) override;
	virtual void AddToActivePool(UObject* InObject, const uint8& Type) override;
	virtual void OnTick(const float &DeltaSeconds) override;

	TMap<FECsWidgetActorType, TArray<class ACsWidgetActor*>> ActiveActors;

	virtual int32 GetActivePoolSize(const uint8 &Type) override;

protected:

	TMap<FECsWidgetActorType, uint8> PoolSizes;

	UPROPERTY()
	TArray<class ACsWidgetActor*> Pool;

	TMap<FECsWidgetActorType, TArray<class ACsWidgetActor*>> Pools;

	TMap<FECsWidgetActorType, uint8> PoolIndices;
	
public:

	const TArray<class ACsWidgetActor*>* GetActors(const FECsWidgetActorType& Type);

	virtual bool IsExhausted(const uint8 &Type) override;

	virtual void LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, class UObject* InObject) override;

// Allocate / DeAllocate
#pragma region
protected:

	class ACsWidgetActor* Allocate(const FECsWidgetActorType &ClassType);

public:

	virtual void DeAllocate(const uint8 &Type, const int32 &Index) override;
	virtual void DeAllocateAll() override;

#pragma endregion Allocate / DeAllocate

// Payload
#pragma region
private:

	FCsWidgetActorPayload Payloads[CS_WIDGET_ACTOR_PAYLOAD_SIZE];

	uint8 PayloadIndex;

public:

	FCsWidgetActorPayload * AllocatePayload();

#pragma endregion Payload

// Display
#pragma region
public:

	class ACsWidgetActor* Display(const FECsWidgetActorType &Type, FCsWidgetActorPayload* Payload, UObject* InOwner, UObject* Parent);
	class ACsWidgetActor* Display(const FECsWidgetActorType &Type, FCsWidgetActorPayload* Payload, UObject* InOwner);
	class ACsWidgetActor* Display(const FECsWidgetActorType &Type, FCsWidgetActorPayload* Payload);

	template<typename T>
	void Display(const FECsWidgetActorType &Type, class ACsWidgetActor* OutWidgetActor, FCsWidgetActorPayload* Payload, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void Display(const FECsWidgetActorType &Type, class ACsWidgetActor* OutWidgetActor, FCsWidgetActorPayload* Payload, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void Display(const FECsWidgetActorType &Type, class ACsWidgetActor* OutWidgetActor, FCsWidgetActorPayload* Payload, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));

#pragma endregion Display
};