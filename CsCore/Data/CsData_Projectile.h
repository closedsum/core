// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes_View.h"
#include "Types/CsTypes_Projectile.h"
#include "Types/CsTypes_FX.h"
#include "CsData_Projectile.generated.h"

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Projectile : public ACsData
{
	GENERATED_UCLASS_BODY()

	virtual void Load(const ECsLoadFlags &LoadFlags = ECsLoadFlags::All) override;

	TCsProjectileType ProjectileType_Internal;
	TCsProjectileType ProjectileType_Internal_MAX;

	virtual TCsProjectileType GetBaseProjectileType();

// Stats
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual float GetLifeTime();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual float GetMaxRange();

#pragma endregion Stats

// Movement
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual float GetInitialSpeed();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual float GetMaxSpeed();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual float GetGravityMultiplier();

#pragma endregion Movement

// Damage
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Damage")
	virtual int32 GetDamage();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	virtual float GetDamageFalloffRate();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	virtual float GetDamageFalloffFrequency();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	virtual float GetDamageFalloffMinimum();

#pragma endregion Damage

// Mesh
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	virtual UStaticMesh* GetMesh(const TEnumAsByte<ECsViewType::Type> &ViewType);

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	virtual float GetDrawDistance(const TEnumAsByte<ECsViewType::Type> &ViewType);

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	virtual float GetDrawDistanceSq(const TEnumAsByte<ECsViewType::Type> &ViewType);

#pragma endregion Mesh

// Transform
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Transform")
	virtual FTransform GetTransform();

#pragma endregion Transform

// Collision
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual TEnumAsByte<ECollisionEnabled::Type> GetCollisionEnabled();

	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual TEnumAsByte<ECollisionChannel> GetCollisionObjectType();

	FCollisionResponseContainer DefaultCollisionResponseContainer;
	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual FCollisionResponseContainer& GetCollisionResponseContainer();

	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual float GetSphereRadius();

#pragma endregion Collision

// FX
#pragma region

	virtual FCsFxElement* GetTrailFX(const TCsViewType &ViewType);

#pragma endregion FX

// Impact
#pragma region

	virtual class ACsData_ProjectileImpact* GetData_Impact();

#pragma endregion Impact
};