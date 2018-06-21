// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/CsManager.h"
#include "AI/Pawn/CsAIPawn.h"
#include "CsManager_AI.generated.h"

#define CS_AI_PAWN_PAYLOAD_SIZE 256

class FCsManager_AI : public TCsManager_PooledObjects_TMap<FECsAIType, ACsAIPawn, FCsAIPawnPayload, CS_AI_PAWN_PAYLOAD_SIZE>
{
public:
	~FCsManager_AI();

protected:

	TArray<class ACsAIController*> ControllerPool;

// Interface
#pragma region
public:

	virtual void DeconstructObject(ACsAIPawn* a) override;
	virtual void Shutdown() override;
	virtual FString GetObjectName(ACsAIPawn* a) override;
	virtual void CreatePool(const FECsAIType &e, const int32 &size) override;
	virtual void AddToPool(const FECsAIType &e, ACsAIPawn* a) override;
	virtual const FString& EnumTypeToString(const FECsAIType &e) override;
	virtual const FString& EnumTypeToString(const int32 &index) override;
	virtual void LogTransaction(const FString &functionName, const TEnumAsByte<ECsPoolTransaction::Type> &transaction, ACsAIPawn* o) override;
	virtual void Log(const FString& log) override;

#pragma endregion Interface
};

UCLASS()
class CSCORE_API AICsManager_AI : public AActor
{
	GENERATED_UCLASS_BODY()

protected:

	FCsManager_AI * Internal;

	static TWeakObjectPtr<UObject> MyOwner;

	static UObject* GetMyOwner();
	template<typename T>
	static T* GetMyOwner()
	{
		return Cast<T>(GetMyOwner());
	}

public:

	static void Init(UObject* InOwner);

	static AICsManager_AI* Get(UWorld* InWorld);
	template<typename T>
	T* Get(UWorld* InWorld)
	{
		return Cast<T>(Get(InWorld));
	}

	virtual void Destroyed() override;

	UFUNCTION(BlueprintCallable, Category = "Manager AI")
	void Clear();

	void Shutdown();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manager AI")
	TMap<FECsAIType, UClass*> ClassMap;

	virtual ACsAIPawn* ConstructObject(const FECsAIType &Type);

	UFUNCTION(BlueprintCallable, Category = "Manager AI")
	void CreatePool(const FECsAIType &Type, const int32 &Size);
	UFUNCTION(BlueprintCallable, Category = "Manager AI")
	void AddToPool(const FECsAIType &Type, ACsAIPawn* Actor);
	UFUNCTION(BlueprintCallable, Category = "Manager AI")
	void AddToActivePool(const FECsAIType &Type, ACsAIPawn* Actor);
	UFUNCTION(BlueprintCallable, Category = "Manager AI")
	void OnTick(const float &DeltaTime);
	UFUNCTION(BlueprintCallable, Category = "Manager AI")
	void GetAllActiveActors(TArray<ACsAIPawn*> &OutActors);

	const TArray<class ACsAIPawn*>* GetActors(const FECsAIType& Type);

	UFUNCTION(BlueprintCallable, Category = "Manager AI")
	int32 GetActivePoolSize(const FECsAIType &Type);
	UFUNCTION(BlueprintCallable, Category = "Manager AI")
	bool IsExhausted(const FECsAIType &Type);
	UFUNCTION(BlueprintCallable, Category = "Manager AI")
	bool DeAllocate(const FECsAIType &Type, const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Manager AI")
	void DeAllocateAll();

	FCsAIPawnPayload* AllocatePayload();

	UFUNCTION(BlueprintCallable, Category = "Manager AI")
	ACsAIPawn* Spawn(const FECsAIType &Type, FCsAIPawnPayload &Payload);
	ACsAIPawn* Spawn(const FECsAIType &Type, FCsAIPawnPayload* Payload);

	template<typename T>
	T* Spawn(const FECsAIType &Type, FCsAIPawnPayload* Payload)
	{
		return Cast<T>(Spawn(Type, Payload));
	}
};