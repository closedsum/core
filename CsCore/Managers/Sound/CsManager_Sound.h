// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/CsManager.h"
#include "Managers/Sound/CsSound.h"
#include "CsManager_Sound.generated.h"

#define CS_SOUND_POOL_SIZE 32
#define CS_MAX_CONCURRENT_SOUNDS 16
#define CS_SOUND_PAYLOAD_SIZE 16

class FCsManager_Sound : public TCsManagerPooledObjects<FECsSoundType, ACsSound, FCsSoundPayload, CS_SOUND_PAYLOAD_SIZE>
{
public:
	~FCsManager_Sound();

// Interface
#pragma region

	virtual void DeconstructObject(ACsSound* a) override;
	virtual FString GetObjectName(ACsSound* a) override;
	virtual const FString& EnumTypeToString(const FECsSoundType &e) override;
	virtual const FString& EnumTypeToString(const int32 &index) override;
	virtual void LogTransaction_Internal(const FString& OutLog) override;

#pragma endregion Interface

	void Stop(FCsSoundElement* InSound, UObject* InOwner, UObject* InParent);
};

UCLASS()
class CSCORE_API AICsManager_Sound : public AActor
{
	GENERATED_UCLASS_BODY()

private:

	FCsManager_Sound * Internal;

	static TWeakObjectPtr<UObject> MyOwner;

	static UObject* GetMyOwner();

public:

	static void Init(UObject* InOwner);

	static AICsManager_Sound* Get(UWorld* InWorld);
	template<typename T>
	static T* Get(UWorld* InWorld)
	{
		return Cast<T>(Get(InWorld));
	}

	virtual void Destroyed() override;

	UFUNCTION(BlueprintCallable, Category = "Manager Sound")
	void Clear();

	void Shutdown();

	virtual ACsSound* ConstructObject(const FECsSoundType &Type);

	UFUNCTION(BlueprintCallable, Category = "Manager Sound")
	void CreatePool(const FECsSoundType &Type, const int32 &Size);
	UFUNCTION(BlueprintCallable, Category = "Manager Sound")
	void AddToPool(const FECsSoundType &Type, ACsSound* Sound);
	UFUNCTION(BlueprintCallable, Category = "Manager Sound")
	void AddToActivePool(const FECsSoundType &Type, ACsSound* Sound);
	UFUNCTION(BlueprintCallable, Category = "Manager Sound")
	void OnTick(const float &DeltaTime);
	UFUNCTION(BlueprintCallable, Category = "Manager Sound")
	void GetAllActiveActors(TArray<ACsSound*> &OutActors);

	const TArray<class ACsSound*>* GetActors(const FECsSoundType& Type);

	UFUNCTION(BlueprintCallable, Category = "Manager Sound")
	int32 GetActivePoolSize(const FECsSoundType &Type);
	UFUNCTION(BlueprintCallable, Category = "Manager Sound")
	bool IsExhausted(const FECsSoundType &Type);
	UFUNCTION(BlueprintCallable, Category = "Manager Sound")
	bool DeAllocate(const FECsSoundType &Type, const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Manager Sound")
	void DeAllocateAll();

	FCsSoundPayload* AllocatePayload();

	UFUNCTION(BlueprintCallable, Category = "Manager Sound")
	ACsSound* Play(const FECsSoundType &Type, FCsSoundPayload &Payload);
	ACsSound* Play(const FECsSoundType &Type, FCsSoundPayload* Payload);

	template<typename T>
	T* Play(const FECsSoundType &Type, FCsSoundPayload* Payload)
	{
		return Cast<T>(Play(Type, Payload));
	}

// Stop
#pragma region
public:

	void Stop(FCsSoundElement* InSound, UObject* InOwner, UObject* InParent);

#pragma endregion Stop

};