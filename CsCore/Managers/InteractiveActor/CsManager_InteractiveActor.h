// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/CsManager.h"
#include "CsTypes.h"
#include "CsManager_InteractiveActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsManagerInteractiveActor_OnDeAllocate, const int32&, Index, const int32&, ActiveIndex, const uint8&, Type);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsManagerInteractiveActor_OnDeAllocate, const uint16&, const uint16&, const ECsInteractiveType::Type&);

typedef FString(*TCsInteractiveTypeToString)(const ECsInteractiveType::Type&);

UCLASS()
class CSCORE_API ACsManager_InteractiveActor : public ACsManager
{
	GENERATED_UCLASS_BODY()

	static ACsManager_InteractiveActor* Get(UWorld* InWorld);

	virtual void Clear() override;
	virtual void Shutdown() override;

	TCsInteractiveType InteractiveType_MAX;

	TCsInteractiveTypeToString InteractiveTypeToString;

	void Init(const TCsInteractiveType &InInteractiveType_MAX, TCsInteractiveTypeToString InInteractiveTypeToString);

	virtual void Destroyed() override;
	virtual void CreatePool(const TSubclassOf<class AActor> &ActorClass, const uint8 &Type, const int32 &Size);
	virtual void AddToPool(AActor* InActor, const uint8& Type);
	virtual void AddToActivePool(AActor* InActor, const uint8& Type);
	virtual void OnTick(const float &DeltaSeconds) override;

	TMap<TCsInteractiveType, uint8> PoolSizes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pool")
	TArray<class ACsInteractiveActor*> Pool;

	TMap<TCsInteractiveType, TArray<class ACsInteractiveActor*>> Pools;

	TMap<TCsInteractiveType, uint8> PoolIndices;

	TMap<TCsInteractiveType, TArray<class ACsInteractiveActor*>> ActiveActors;

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void GetAllActiveActors(TArray<class ACsInteractiveActor*> &OutActors);

	virtual int32 GetActivePoolSize(const uint8& Type) override;

	virtual bool IsExhausted(const uint8 &Type) override;

	class ACsInteractiveActor* Allocate(const TCsInteractiveType &Type);

	virtual void DeAllocate(const uint8 &Type, const int32 &Index) override;
	virtual void DeAllocateAll() override;

	virtual void OnDeAllocate(const uint16 &Index, const uint16 &ActiveIndex, const uint8 &Type);

	UPROPERTY(BlueprintAssignable, Category = "Pool")
	FBindableDynEvent_CsManagerInteractiveActor_OnDeAllocate OnDeAllocate_ScriptEvent;

	FBindableEvent_CsManagerInteractiveActor_OnDeAllocate OnDeAllocate_Event;

	class ACsInteractiveActor* WakeUp(const TCsInteractiveType &Type, UObject* InOwner, UObject* Parent);
	class ACsInteractiveActor* WakeUp(const TCsInteractiveType &Type, UObject* InOwner);
	class ACsInteractiveActor* WakeUp(const TCsInteractiveType &Type);

	template<typename T>
	void WakeUp(const TCsInteractiveType &Type, class ACsInteractiveActor* &OutActor, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void WakeUp(const TCsInteractiveType &Type, class ACsInteractiveActor* &OutActor, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void WakeUp(const TCsInteractiveType &Type, class ACsInteractiveActor* &OutActor, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
};