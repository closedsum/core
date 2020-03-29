// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/CsManager.h"
#include "Managers/WidgetActor/CsWidgetActor.h"
#include "CsManager_WidgetActor.generated.h"

#define CS_WIDGET_ACTOR_PAYLOAD_SIZE 255

class CSCOREDEPRECATED_API FCsManager_WidgetActor : public TCsManager_PooledObjects_TMap<FECsWidgetActorType, ACsWidgetActor, FCsWidgetActorPayload, CS_WIDGET_ACTOR_PAYLOAD_SIZE>
{
private:
	typedef TCsManager_PooledObjects_TMap<FECsWidgetActorType, ACsWidgetActor, FCsWidgetActorPayload, CS_WIDGET_ACTOR_PAYLOAD_SIZE> Super;

public:
	~FCsManager_WidgetActor();

	virtual void DeconstructObject(ACsWidgetActor* a) override;
	virtual FString GetObjectName(ACsWidgetActor* a) override;
	virtual const FString& EnumTypeToString(const FECsWidgetActorType &e) override;
	virtual const FString& EnumTypeToString(const int32 &index) override;
	virtual void Log(const FString& log) override;
};

UCLASS()
class CSCOREDEPRECATED_API AICsManager_WidgetActor  : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	virtual void PostActorCreated() override;

protected:

	FCsManager_WidgetActor * Internal;

	static TWeakObjectPtr<UObject> MyOwner;

	static UObject* GetMyOwner();
	template<typename T>
	static T* GetMyOwner()
	{
		return Cast<T>(GetMyOwner());
	}

public:

	static void Init(UObject* InOwner);

	static AICsManager_WidgetActor* Get(UWorld* InWorld);
	template<typename T>
	static T* Get(UWorld* InWorld)
	{
		return Cast<T>(GetWorld(InWorld));
	}

	virtual void Destroyed() override;

	UFUNCTION(BlueprintCallable, Category = "Manager WidgetActor")
	void Clear();

	void Shutdown();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manager WidgetActor")
	TMap<FECsWidgetActorType, UClass*> ClassMap;

	virtual ACsWidgetActor* ConstructObject(const FECsWidgetActorType &Type);

	UFUNCTION(BlueprintCallable, Category = "Manager WidgetActor")
	void CreatePool(const FECsWidgetActorType &Type, const int32 &Size);
	UFUNCTION(BlueprintCallable, Category = "Manager WidgetActor")
	void AddToPool(const FECsWidgetActorType &Type, ACsWidgetActor* Actor);
	UFUNCTION(BlueprintCallable, Category = "Manager WidgetActor")
	void AddToActivePool(const FECsWidgetActorType &Type, ACsWidgetActor* Actor);
	UFUNCTION(BlueprintCallable, Category = "Manager WidgetActor")
	void OnTick(const float &DeltaTime);
	UFUNCTION(BlueprintCallable, Category = "Manager WidgetActor")
	void GetAllActiveActors(TArray<ACsWidgetActor*> &OutActors);

	const TArray<class ACsWidgetActor*>* GetActors(const FECsWidgetActorType& Type);

	UFUNCTION(BlueprintCallable, Category = "Manager WidgetActor")
	int32 GetActivePoolSize(const FECsWidgetActorType &Type);
	UFUNCTION(BlueprintCallable, Category = "Manager WidgetActor")
	bool IsExhausted(const FECsWidgetActorType &Type);
	UFUNCTION(BlueprintCallable, Category = "Manager WidgetActor")
	bool DeAllocate(const FECsWidgetActorType &Type, const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Manager WidgetActor")
	void DeAllocateAll();

	FCsWidgetActorPayload* AllocatePayload();

	//UFUNCTION(BlueprintCallable, Category = "Manager WidgetActor")
	ACsWidgetActor* Display(const FECsWidgetActorType &Type, FCsWidgetActorPayload &Payload);
	ACsWidgetActor* Display(const FECsWidgetActorType &Type, FCsWidgetActorPayload* Payload);

	template<typename T>
	T* Display(const FECsWidgetActorType &Type, FCsWidgetActorPayload* Payload)
	{
		return Cast<T>(Display(Type, Payload));
	}
};