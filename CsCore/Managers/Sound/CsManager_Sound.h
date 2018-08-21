// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/CsManager.h"
#include "Managers/Sound/CsSound.h"
#include "CsManager_Sound.generated.h"

#define CS_SOUND_POOL_SIZE 32
#define CS_MAX_CONCURRENT_SOUNDS 16
#define CS_SOUND_PAYLOAD_SIZE 16

class FCsManager_Sound : public TCsManager_PooledObjects<ACsSound, FCsSoundPayload, CS_SOUND_PAYLOAD_SIZE>
{
private:
	typedef TCsManager_PooledObjects<ACsSound, FCsSoundPayload, CS_SOUND_PAYLOAD_SIZE> Super;

public:
	~FCsManager_Sound();

// Interface
#pragma region

	virtual void DeconstructObject(ACsSound* a) override;
	virtual FString GetObjectName(ACsSound* a) override;
	virtual void LogTransaction(const FString &functionName, const TEnumAsByte<ECsPoolTransaction::Type> &transaction, ACsSound* o) override;
	virtual void Log(const FString& log) override;
	virtual ACsSound* Spawn(FCsSoundPayload* payload) override;

#pragma endregion Interface

	void Stop(FCsSoundElement* InSound, UObject* InOwner, UObject* InParent);
};

UCLASS()
class CSCORE_API AICsManager_Sound : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	virtual void PostActorCreated() override;

protected:

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

	virtual ACsSound* ConstructObject();

	UFUNCTION(BlueprintCallable, Category = "Manager Sound")
	void CreatePool(const int32 &Size);
	UFUNCTION(BlueprintCallable, Category = "Manager Sound")
	void AddToPool(ACsSound* Sound);
	UFUNCTION(BlueprintCallable, Category = "Manager Sound")
	void AddToActivePool(ACsSound* Sound);
	UFUNCTION(BlueprintCallable, Category = "Manager Sound")
	void OnTick(const float &DeltaTime);

	const TMap<int32, ACsSound*>& GetAllActiveActors();

	const TArray<ACsSound*>& GetActors();

	UFUNCTION(BlueprintCallable, Category = "Manager Sound")
	int32 GetActivePoolSize();
	UFUNCTION(BlueprintCallable, Category = "Manager Sound")
	bool IsExhausted();
	UFUNCTION(BlueprintCallable, Category = "Manager Sound")
	bool DeAllocate(const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Manager Sound")
	void DeAllocateAll();

	FCsSoundPayload* AllocatePayload();

	UFUNCTION(BlueprintCallable, Category = "Manager Sound")
	ACsSound* Play(FCsSoundPayload &Payload);
	ACsSound* Play(FCsSoundPayload* Payload);

	template<typename T>
	T* Play(FCsSoundPayload* Payload)
	{
		return Cast<T>(Play(Payload));
	}

// Stop
#pragma region
public:

	void Stop(FCsSoundElement* InSound, UObject* InOwner, UObject* InParent);

#pragma endregion Stop

};