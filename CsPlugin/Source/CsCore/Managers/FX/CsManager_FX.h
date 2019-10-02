// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/CsManager.h"
#include "Managers/FX/CsEmitter.h"
#include "CsManager_FX.generated.h"

#define CS_FX_PAYLOAD_SIZE 255

class FCsManager_FX : public TCsManager_PooledObjects<ACsEmitter, FCsFxPayload, CS_FX_PAYLOAD_SIZE>
{
private:
	typedef TCsManager_PooledObjects<ACsEmitter, FCsFxPayload, CS_FX_PAYLOAD_SIZE> Super;

public:
	~FCsManager_FX();

	// Interface
#pragma region

	virtual void DeconstructObject(ACsEmitter* a) override;
	virtual FString GetObjectName(ACsEmitter* a) override;
	virtual void LogTransaction(const FString& functionName, const ECsPoolTransaction& transaction, ACsEmitter* o) override;
	virtual void Log(const FString& log) override;
	virtual void OnTick(const float& deltaTime) override;
	virtual ACsEmitter* Allocate() override;

#pragma endregion Interface

#if WITH_EDITOR
	void ToggleEmitterEditorIcons(const bool& toggle);
#endif // #if WITH_EDITOR
};

UCLASS()
class CSCORE_API AICsManager_FX : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	virtual void PostActorCreated() override;

protected:

	FCsManager_FX* Internal;

	static TWeakObjectPtr<UObject> MyOwner;

	static UObject* GetMyOwner();
	template<typename T>
	static T* GetMyOwner()
	{
		return Cast<T>(GetMyOwner());
	}

public:

	static void Init(UObject* InOwner);

	static AICsManager_FX* Get(UWorld* InWorld);
	template<typename T>
	T* Get(UWorld* InWorld)
	{
		return Cast<T>(Get(InWorld));
	}

	virtual void Destroyed() override;

	UFUNCTION(BlueprintCallable, Category = "Manager FX")
	void Clear();

	void Shutdown();

	virtual ACsEmitter* ConstructObject();

	UFUNCTION(BlueprintCallable, Category = "Manager FX")
	void CreatePool(const int32& Size);
	UFUNCTION(BlueprintCallable, Category = "Manager FX")
	void AddToPool(ACsEmitter* Sound);
	UFUNCTION(BlueprintCallable, Category = "Manager FX")
	void AddToActivePool(ACsEmitter* Sound);
	UFUNCTION(BlueprintCallable, Category = "Manager FX")
	void OnTick(const float& DeltaTime);

	const TMap<int32, ACsEmitter*>& GetAllActiveActors();

	const TArray<ACsEmitter*>& GetActors();

	UFUNCTION(BlueprintCallable, Category = "Manager FX")
	int32 GetActivePoolSize();
	UFUNCTION(BlueprintCallable, Category = "Manager FX")
	bool IsExhausted();
	UFUNCTION(BlueprintCallable, Category = "Manager FX")
	bool DeAllocate(const int32& Index);
	UFUNCTION(BlueprintCallable, Category = "Manager FX")
	void DeAllocateAll();

	FCsFxPayload* AllocatePayload();

	//UFUNCTION(BlueprintCallable, Category = "Manager FX")
	ACsEmitter* Play(FCsFxPayload& Payload);
	ACsEmitter* Play(FCsFxPayload* Payload);

	template<typename T>
	T* Play(FCsFxPayload* Payload)
	{
		return Cast<T>(Play(Payload));
	}

#if WITH_EDITOR
	void ToggleEmitterEditorIcons(const bool& Toggle);
#endif // #if WITH_EDITOR
};