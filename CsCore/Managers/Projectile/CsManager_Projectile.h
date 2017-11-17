// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes.h"
#include "Types/CsTypes_Projectile.h"
#include "Managers/CsManager.h"
#include "CsManager_Projectile.generated.h"

#define CS_PROJECTILE_POOL_SIZE 400

UCLASS()
class CSCORE_API ACsManager_Projectile : public ACsManager
{
	GENERATED_UCLASS_BODY()

	static ACsManager_Projectile* Get(UWorld* InWorld);

	virtual void Clear() override;
	virtual void Shutdown() override;
	virtual void Destroyed() override;
	virtual void CreatePool(const int32 &Size) override;
	virtual void OnTick(const float &DeltaSeconds);

	TSubclassOf<class ACsProjectile> ProjectileClass;

	TArray<class ACsProjectile*> ActiveProjectiles;

	UPROPERTY()
	TArray<class ACsProjectile*> Pool;

	uint16 PoolIndex;

	virtual void LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, class UObject* InObject) override;

	class ACsProjectile* Allocate(const TCsProjectileRelevance &Type);

	virtual void DeAllocate(const int32 &Index) override;

// Fire
#pragma region

	virtual class ACsProjectile* Fire(const TCsProjectileRelevance &Type, class ACsData_Projectile* InData, struct FCsProjectileFireCache* Cache, UObject* InInstigator, UObject* InOwner, UObject* InParent);
	virtual class ACsProjectile* Fire(const TCsProjectileRelevance &Type, class ACsData_Projectile* InData, struct FCsProjectileFireCache* Cache, UObject* InInstigator, UObject* InOwner);
	virtual class ACsProjectile* Fire(const TCsProjectileRelevance &Type, class ACsData_Projectile* InData, struct FCsProjectileFireCache* Cache);

	template<typename T>
	void Fire(class ACsProjectile* OutProjectile, const TCsProjectileRelevance &Type, class ACsData_Projectile* InData, struct FCsProjectileFireCache* Cache, UObject* InInstigator, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)());
	template<typename T>
	void Fire(class ACsProjectile* OutProjectile, const TCsProjectileRelevance &Type, class ACsData_Projectile* InData, struct FCsProjectileFireCache* Cache, UObject* InInstigator, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)());
	template<typename T>
	void Fire(class ACsProjectile* OutProjectile, const TCsProjectileRelevance &Type, class ACsData_Projectile* InData, struct FCsProjectileFireCache* Cache, UObject* InInstigator, T* InObject, void (T::*OnDeAllocate)());

#pragma endregion Fire
};