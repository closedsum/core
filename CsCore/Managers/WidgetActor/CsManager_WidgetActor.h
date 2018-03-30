// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/CsManager.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_UI.h"
#include "CsManager_WidgetActor.generated.h"

UCLASS()
class CSCORE_API ACsManager_WidgetActor : public ACsManager
{
	GENERATED_UCLASS_BODY()

private:

	static TWeakObjectPtr<UObject> MyOwner;

	static UObject* GetMyOwner();

public:

	CS_DECLARE_WIDGET_ACTOR_TYPE

	void SetMyOwner(UObject* InOwner);
	static ACsManager_WidgetActor* Get(UWorld* InWorld);

	void Init(const TCsWidgetActorType &InWidgetActorType_MAX, TCsWidgetActorTypeToString InWidgetActorTypeToString);

	virtual void Clear() override;
	virtual void Shutdown() override;
	virtual void Destroyed() override;
	virtual void CreatePool(const TSubclassOf<class UObject> &ObjectClass, const uint8 &Type, const int32 &Size) override;
	virtual void AddToActivePool(UObject* InObject, const uint8& Type) override;
	virtual void OnTick(const float &DeltaSeconds) override;

	TMap<TCsWidgetActorType, TArray<class ACsWidgetActor*>> ActiveWidgetActors;

	virtual int32 GetActivePoolSize(const uint8 &Type) override;

	TMap<TCsWidgetActorType, uint8> PoolSizes;

	UPROPERTY()
	TArray<class ACsWidgetActor*> Pool;

	TMap<TCsWidgetActorType, TArray<class ACsWidgetActor*>> Pools;

	TMap<TCsWidgetActorType, uint8> PoolIndices;

	virtual bool IsExhausted(const uint8 &Type) override;

	virtual void LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, class UObject* InObject) override;

// Allocate / DeAllocate
#pragma region

	class ACsWidgetActor* Allocate(const TCsWidgetActorType &ClassType);

	virtual void DeAllocate(const uint8 &Type, const int32 &Index) override;
	virtual void DeAllocateAll() override;

#pragma endregion Allocate / DeAllocate

// Display
#pragma region

	class ACsWidgetActor* Display(const TCsWidgetActorType &Type, FCsWidgetActorPayload* Payload, UObject* InOwner, UObject* Parent);
	class ACsWidgetActor* Display(const TCsWidgetActorType &Type, FCsWidgetActorPayload* Payload, UObject* InOwner);
	class ACsWidgetActor* Display(const TCsWidgetActorType &Type, FCsWidgetActorPayload* Payload);

	template<typename T>
	void Display(const TCsWidgetActorType &Type, class ACsWidgetActor* OutWidgetActor, FCsWidgetActorPayload* Payload, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void Display(const TCsWidgetActorType &Type, class ACsWidgetActor* OutWidgetActor, FCsWidgetActorPayload* Payload, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void Display(const TCsWidgetActorType &Type, class ACsWidgetActor* OutWidgetActor, FCsWidgetActorPayload* Payload, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));

#pragma endregion Display
};