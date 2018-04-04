// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes_View.h"
#include "Types/CsTypes_Projectile.h"
#include "Types/CsTypes_FX.h"
#include "CsData_Projectile.generated.h"

UCLASS(Abstract, hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Projectile : public ACsData
{
	GENERATED_UCLASS_BODY()

	virtual void Load(const ECsLoadFlags &LoadFlags = ECsLoadFlags::All) override;

	TCsProjectileType BaseProjectileType;

	TCsProjectileType GetBaseProjectileType();

// Stats
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual const FName& GetItemShortCode();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual const bool& GetOnAllocateDropItem();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual const bool& GetOnAllocateConsumeItem();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual const float& GetLifeTime();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual const float& GetMaxRange();

#pragma endregion Stats

// Movement
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual TEnumAsByte<ECsProjectileMovement::Type> GetMovementType();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual FVector EvaluateMovementFunction(const float &Time, const FVector &Location, const FTransform &Transform);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual const float& GetInitialSpeed();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual const float& GetMaxSpeed();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual const float& GetGravityMultiplier();

#pragma endregion Movement

// Damage
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Damage")
	virtual const int32& GetDamage();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	virtual const bool& CanDamageFalloff();
	
	UFUNCTION(BlueprintCallable, Category = "Damage")
	virtual float GetDamageFalloff(const float &Distance);

	UFUNCTION(BlueprintCallable, Category = "Damage")
	virtual const bool& CanDamageRadial();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	virtual float GetDamageRadial(const FVector &Origin, const FVector &Location);

#pragma endregion Damage

// Mesh
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	virtual UStaticMesh* GetMesh(const TEnumAsByte<ECsViewType::Type> &ViewType);

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	virtual float GetDrawDistance(const TEnumAsByte<ECsViewType::Type> &ViewType);

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	virtual float GetDrawDistanceSq(const TEnumAsByte<ECsViewType::Type> &ViewType);

#pragma endregion Mesh

// Transform
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Transform")
	virtual const FTransform& GetTransform();

#pragma endregion Transform

// Collision
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual TEnumAsByte<ECollisionEnabled::Type> GetCollisionEnabled();

	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual TEnumAsByte<ECollisionChannel> GetCollisionObjectType();

private:
	FCollisionResponseContainer DefaultCollisionResponseContainer;

public:

	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual FCollisionResponseContainer& GetCollisionResponseContainer();

	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual const float& GetSphereRadius();

#pragma endregion Collision

// FX
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "FX")
	virtual const bool& GetUseTrailFX();

	virtual FCsFxElement* GetTrailFX(const TCsViewType &ViewType);

#pragma endregion FX

// Impact
#pragma region
public:

	virtual class ACsData_ProjectileImpact* GetData_Impact();

#pragma endregion Impact
};