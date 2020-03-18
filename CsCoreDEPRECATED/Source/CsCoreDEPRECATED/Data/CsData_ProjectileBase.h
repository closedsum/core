// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData_Impl.h"
#include "Types/CsTypes_View.h"
#include "Managers/Projectile/CsTypes_Projectile.h"
#include "Types/CsTypes_FX.h"
#include "CsData_ProjectileBase.generated.h"

class UCsData_ProjectileImpact;

UCLASS(Abstract)
class CSCOREDEPRECATED_API UCsData_ProjectileBase : public UCsData_Impl
{
	GENERATED_UCLASS_BODY()

	virtual void Load(const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game) override;

	virtual const FECsProjectile& GetProjectileType();

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
	virtual ECsProjectileMovement GetMovementType();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual FVector EvaluateMovementFunction(const float& Time, const FVector& Location, const FTransform& Transform);

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
	virtual float GetDamageRadial(const FVector& Origin, const FVector& Location);

#pragma endregion Damage

// Mesh
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	virtual UStaticMesh* GetMesh(const ECsViewType& ViewType);

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	virtual float GetDrawDistance(const ECsViewType& ViewType);

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	virtual float GetDrawDistanceSq(const ECsViewType& ViewType);

#pragma endregion Mesh

// Transform
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Transform")
	virtual const FTransform& GetMyTransform();

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

	virtual FCsFxElement* GetTrailFX(const ECsViewType& ViewType);

#pragma endregion FX

// Impact
#pragma region
public:

	virtual UCsData_ProjectileImpact* GetData_Impact();

#pragma endregion Impact
};