// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Managers/CsManager.h"
#include "Managers/Projectile/CsProjectileBase.h"
#include "CsManager_Projectile.generated.h"

#define CS_PROJECTILE_POOL_SIZE 400
#define CS_PROJECTILE_PAYLOAD_SIZE 255

class FCsManager_Projectile : public TCsManager_PooledObjects_TMap<FECsProjectileType, ACsProjectileBase, FCsProjectilePayload, CS_PROJECTILE_PAYLOAD_SIZE>
{
private:
	typedef TCsManager_PooledObjects_TMap<FECsProjectileType, ACsProjectileBase, FCsProjectilePayload, CS_PROJECTILE_PAYLOAD_SIZE> Super;

public:
	~FCsManager_Projectile();

// Interface
#pragma region

	virtual void DeconstructObject(class ACsProjectileBase* a) override;
	virtual FString GetObjectName(class ACsProjectileBase* a) override;
	virtual const FString& EnumTypeToString(const FECsProjectileType &e) override;
	virtual const FString& EnumTypeToString(const int32 &index) override;
	virtual void Log(const FString& log) override;

#pragma endregion Interface
};

UCLASS()
class CSCORE_API AICsManager_Projectile : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	virtual void PostActorCreated() override;

protected:

	FCsManager_Projectile* Internal;

	static TWeakObjectPtr<UObject> MyOwner;

	static UObject* GetMyOwner();
	template<typename T>
	static T* GetMyOwner()
	{
		Cast<T>(GetMyOwner());
	}

public:

	static void Init(UObject* InOwner);

	static AICsManager_Projectile* Get(UWorld* InWorld);
	template<typename T>
	static T* Get(UWorld* InWorld)
	{
		return Cast<T>(Get(InWorld));
	}

	virtual void Destroyed() override;

	UFUNCTION(BlueprintCallable, Category = "Manager Projectile")
	void Clear();

	void Shutdown();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manager Projectile")
	TMap<FECsProjectileType, UClass*> ClassMap;

	virtual ACsProjectileBase* ConstructObject(const FECsProjectileType &Type);

	UFUNCTION(BlueprintCallable, Category = "Manager Projectile")
	void CreatePool(const FECsProjectileType &Type, const int32 &Size);
	UFUNCTION(BlueprintCallable, Category = "Manager Projectile")
	void AddToPool(const FECsProjectileType &Type, ACsProjectileBase* Process);
	UFUNCTION(BlueprintCallable, Category = "Manager Projectile")
	void AddToActivePool(const FECsProjectileType &Type, ACsProjectileBase* Process);
	
	UFUNCTION(BlueprintCallable, Category = "Manager Projectile")
	void OnTick(const float &DeltaTime);
	
	virtual void OnTick_Handle_Projectile(ACsProjectileBase* Projectile);

	UFUNCTION(BlueprintCallable, Category = "Manager Projectile")
	void GetAllActiveActors(TArray<ACsProjectileBase*> &OutActors);

	const TArray<ACsProjectileBase*>* GetActors(const FECsProjectileType& Type);

	UFUNCTION(BlueprintCallable, Category = "Manager Projectile")
	int32 GetActivePoolSize(const FECsProjectileType &Type);
	UFUNCTION(BlueprintCallable, Category = "Manager Projectile")
	bool IsExhausted(const FECsProjectileType &Type);
	UFUNCTION(BlueprintCallable, Category = "Manager Projectile")
	bool DeAllocate(const FECsProjectileType &Type, const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Manager Projectile")
	void DeAllocateAll();

	FCsProjectilePayload* AllocatePayload();

	//UFUNCTION(BlueprintCallable, Category = "Manager Projectile")
	ACsProjectileBase* Fire(const FECsProjectileType &Type, FCsProjectilePayload &Payload);
	ACsProjectileBase* Fire(const FECsProjectileType &Type, FCsProjectilePayload* Payload);

	template<typename T>
	T* Fire(const FECsProjectileType &Type, FCsProjectilePayload* Payload)
	{
		return Cast<T>(Spawn(Type, Payload));
	}
};