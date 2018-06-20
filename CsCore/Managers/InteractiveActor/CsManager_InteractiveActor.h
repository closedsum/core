// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/CsManager.h"
#include "Managers/InteractiveActor/CsInteractiveActor.h"
#include "CsManager_InteractiveActor.generated.h"

#define CS_INTERACTIVE_ACTOR_PAYLOAD_SIZE 255

class FCsManager_InteractiveActor : public TCsManager_PooledObjects_TMap<FECsInteractiveType, ACsInteractiveActor, FCsInteractiveActorPayload, CS_INTERACTIVE_ACTOR_PAYLOAD_SIZE>
{
public:
	~FCsManager_InteractiveActor();

	virtual void DeconstructObject(ACsInteractiveActor* a) override;
	virtual FString GetObjectName(ACsInteractiveActor* a) override;
	virtual const FString& EnumTypeToString(const FECsInteractiveType &e) override;
	virtual const FString& EnumTypeToString(const int32 &index) override;
	virtual void Log(const FString& log) override;
};

UCLASS()
class CSCORE_API AICsManager_InteractiveActor : public AActor
{
	GENERATED_UCLASS_BODY()

protected:

	FCsManager_InteractiveActor* Internal;

public:

	static AICsManager_InteractiveActor* Get(UWorld* InWorld);
	template<typename T>
	static T* Get(UWorld* InWorld)
	{
		return Cast<T>(Get(InWorld));
	}

	virtual void Destroyed() override;

	UFUNCTION(BlueprintCallable, Category = "Manager InteractiveActor")
	void Clear();

	void Shutdown();

	virtual ACsInteractiveActor* ConstructObject(const FECsInteractiveType &Type);

	UFUNCTION(BlueprintCallable, Category = "Manager InteractiveActor")
	void CreatePool(const FECsInteractiveType &Type, const int32 &Size);
	UFUNCTION(BlueprintCallable, Category = "Manager InteractiveActor")
	void AddToPool(const FECsInteractiveType &Type, ACsInteractiveActor* Actor);
	UFUNCTION(BlueprintCallable, Category = "Manager InteractiveActor")
	void AddToActivePool(const FECsInteractiveType &Type, ACsInteractiveActor* Actor);
	UFUNCTION(BlueprintCallable, Category = "Manager InteractiveActor")
	void OnTick(const float &DeltaTime);
	UFUNCTION(BlueprintCallable, Category = "Manager InteractiveActor")
	void GetAllActiveActors(TArray<ACsInteractiveActor*> &OutActors);

	const TArray<class ACsInteractiveActor*>* GetActors(const FECsInteractiveType& Type);

	UFUNCTION(BlueprintCallable, Category = "Manager InteractiveActor")
	int32 GetActivePoolSize(const FECsInteractiveType &Type);
	UFUNCTION(BlueprintCallable, Category = "Manager InteractiveActor")
	bool IsExhausted(const FECsInteractiveType &Type);
	UFUNCTION(BlueprintCallable, Category = "Manager InteractiveActor")
	bool DeAllocate(const FECsInteractiveType &Type, const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Manager InteractiveActor")
	void DeAllocateAll();

	FCsInteractiveActorPayload* AllocatePayload();

	UFUNCTION(BlueprintCallable, Category = "Manager InteractiveActor")
	ACsInteractiveActor* Spawn(const FECsInteractiveType &Type, FCsInteractiveActorPayload &Payload);
	ACsInteractiveActor* Spawn(const FECsInteractiveType &Type, FCsInteractiveActorPayload* Payload);

	template<typename T>
	T* Spawn(const FECsInteractiveType &Type, FCsInteractiveActorPayload* Payload)
	{
		return Cast<T>(Spawn(Type, Payload));
	}
};