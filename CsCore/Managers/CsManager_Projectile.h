// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsTypes.h"
#include "Managers/CsManager.h"
#include "CsManager_Projectile.generated.h"

#define CS_PROJECTILE_POOL_SIZE 400

UCLASS()
class CSCORE_API ACsManager_Projectile : public ACsManager
{
	GENERATED_UCLASS_BODY()

	virtual void PostActorCreated() override;
	virtual void OnTick(const float &DeltaSeconds);

	virtual void CreatePool(const int32 &Size) override;

	TSubclassOf<class ACsProjectile> ProjectileClass;

	TArray<class ACsProjectile*> ActiveProjectiles;

	UPROPERTY()
	class ACsProjectile* Pool[CS_PROJECTILE_POOL_SIZE];

	uint16 PoolIndex;

	class ACsProjectile* Allocate(const TCsProjectileType &Type);

	virtual void DeAllocate(const int32 &Index) override;

	class ACsProjectile* Fire(class ACsData_Projectile* InData, const struct FCsProjectileFireCache* Cache, UObject* InInstigator, UObject* InOwner, UObject* InParent);
	class ACsProjectile* Fire(class ACsData_Projectile* InData, const struct FCsProjectileFireCache* Cache, UObject* InInstigator, UObject* InOwner);
	class ACsProjectile* Fire(class ACsData_Projectile* InData, const struct FCsProjectileFireCache* Cache);
	class ACsProjectile* Fire(class ACsData_Projectile* InData, const struct FCsProjectileFireCache* Cache, UObject* InInstigator, UObject* InOwner, const FVector &Location);
	// TODO: Fix compile error
	/*
	template<typename T>
	class ACsProjectile* Fire(class ACsData_Projectile* InData, const struct FCsProjectileFireCache* Cache, UObject* InInstigator, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)());
	template<typename T>
	class ACsProjectile* Fire(class ACsData_Projectile* InData, const struct FCsProjectileFireCache* Cache, UObject* InInstigator, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)());
	template<typename T>
	class ACsProjectile* Fire(class ACsData_Projectile* InData, const struct FCsProjectileFireCache* Cache, UObject* InInstigator, T* InObject, void (T::*OnDeAllocate)());
	template<typename T>
	class ACsProjectile* Fire(class ACsData_Projectile* InData, const struct FCsProjectileFireCache* Cache, UObject* InInstigator, UObject* InOwner, const FVector &Location, T* InObject, void (T::*OnDeAllocate)());
	*/
};