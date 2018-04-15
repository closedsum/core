// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes.h"
#include "Types/CsTypes_Projectile.h"
#include "Managers/CsManager.h"
#include "CsManager_Projectile.generated.h"

#define CS_PROJECTILE_POOL_SIZE 400
#define CS_PROJECTILE_PAYLOAD_SIZE 255

UCLASS()
class CSCORE_API ACsManager_Projectile : public ACsManager
{
	GENERATED_UCLASS_BODY()

private:

	static TWeakObjectPtr<UObject> MyOwner;

	static UObject* GetMyOwner();

public:

	static void Init(UObject* InOwner);
	static ACsManager_Projectile* Get(UWorld* InWorld);

	virtual void Clear() override;
	virtual void Shutdown() override;
	virtual void Destroyed() override;
	virtual void CreatePool(const TSubclassOf<class UObject> &ObjectClass, const int32 &Size) override;
	virtual void CreatePool(const int32 &Size) override;
	virtual void OnTick(const float &DeltaSeconds);

	TSubclassOf<class ACsProjectile> ProjectileClass;

	UPROPERTY()
	TArray<class ACsProjectile*> Pool;

	uint16 PoolIndex;

	TArray<class ACsProjectile*> ActiveProjectiles;

	virtual void LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, class UObject* InObject) override;

	class ACsProjectile* Allocate();

	virtual void DeAllocate(const int32 &Index) override;

// Payload
#pragma region
private:

	FCsProjectilePayload Payloads[CS_PROJECTILE_PAYLOAD_SIZE];

	uint8 PayloadIndex;

public:

	FCsProjectilePayload * AllocatePayload();

#pragma endregion Payload

// Fire
#pragma region
public: 

	virtual class ACsProjectile* Fire(FCsProjectilePayload* Payload, UObject* InInstigator, UObject* InOwner, UObject* InParent);
	virtual class ACsProjectile* Fire(FCsProjectilePayload* Payload, UObject* InInstigator, UObject* InOwner);
	virtual class ACsProjectile* Fire(FCsProjectilePayload* Payload);

	template<typename T>
	void Fire(class ACsProjectile* OutProjectile, FCsProjectilePayload* Payload, UObject* InInstigator, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)());
	template<typename T>
	void Fire(class ACsProjectile* OutProjectile, FCsProjectilePayload* Payload, UObject* InInstigator, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)());
	template<typename T>
	void Fire(class ACsProjectile* OutProjectile, FCsProjectilePayload* Payload, UObject* InInstigator, T* InObject, void (T::*OnDeAllocate)());

#pragma endregion Fire
};