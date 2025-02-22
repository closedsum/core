// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Components/ActorComponent.h"
// Interface
#include "Component/CsWeapon_Component.h"
#include "Fire/Projectile/CsWeapon_Fire_Projectile.h"
//#include "Fire/TimeBetweenShots/CsWeapon_Fire_TimeBetweenShots.h"
//#include "Fire/TimeBetweenShots/CsWeapon_Fire_TimeBetweenShots_Event.h"
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Cached.h"
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"

#include "CsWeapon_Fire_ProjectileImpl.generated.h"

CS_FWD_DECLARE_CACHED_FUNCTION_NAME(CsWeapon_Fire_ProjectileImpl)

class ICsWeapon;
class ICsProjectileWeapon;
class ICsGetProjectileType;
struct FCsRoutine;

CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NPayload, IPayload)
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NProjectile, NParams, NLaunch, ILaunch)

UCLASS(BlueprintType)
class CSWP_API UCsWeapon_Fire_ProjectileImpl : public UActorComponent,
											   public ICsWeapon_Component,
											   public ICsWeapon_Fire_Projectile
{
	GENERATED_UCLASS_BODY()

private:

	CS_USING_CACHED_FUNCTION_NAME(CsWeapon_Fire_ProjectileImpl);

	using PayloadType = NCsWeapon::NFire::NProjectile::NLaunch::NPayload::FPayload;
	using CsProjectilePayloadType = NCsProjectile::NPayload::IPayload;
	using ParamsType = NCsWeapon::NProjectile::NParams::NLaunch::ILaunch;

// ICsWeapon_Component
#pragma region
public:

	void SetWeapon(ICsWeapon* InWeapon);
	FORCEINLINE ICsWeapon* GetWeapon() const { return Weapon; }

#pragma endregion ICsWeapon_Component

// Weapon_Component
#pragma region
private:

	ICsWeapon* Weapon;

	UObject* WeaponAsObject;

	ICsProjectileWeapon* ProjectileWeapon;

	ICsGetProjectileType* GetProjectileType;

#pragma endregion Weapon_Component

// ICsWeapon_Fire_Projectile
#pragma region
public:

	FORCEINLINE void SetLaunchComponentLocation(USceneComponent* Component)  { ComponentLocation = Component; }
	FORCEINLINE void SetLaunchComponentDirection(USceneComponent* Component) { ComponentDirection = Component; }
	FVector GetLaunchLocation(const PayloadType& Payload);
	FORCEINLINE FVector GetLaunchLocation() { return GetLaunchLocation(PayloadType()); }
	FVector GetLaunchDirection(const PayloadType& LaunchPayload);
	FORCEINLINE FVector GetLaunchDirection() { return GetLaunchDirection(PayloadType()); };

	void Launch(const PayloadType& LaunchPayload);

	void Clear(){}

#pragma endregion ICsWeapon_Fire_Projectile

// Weapon_Fire_Projectile
#pragma region
private:

	USceneComponent* ComponentLocation;

	USceneComponent* ComponentDirection;

	FVector CustomLocation;

	FVector CustomDirection;

	FCsScopedTimerHandle LaunchScopedHandle;

protected:

	/** If set, calls Override_GetLaunchDirection when calling
	    GetLaunchDirection(). 
		This flag is intended to be set by Blueprint | script and allow a non-native 
		path to adjust the launch direction of the projectile. */
	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Fire|Projectile")
	bool bOverride_GetLaunchDirection;

	/** 
	* Only Valid if bOverride_GetLaunchDirection == true. 
	* This provides a non-native (Blueprint | script) path to adjust the launch direction 
	* of the projectile. 
	* 
	* return Launch Direction.
	*/
	UFUNCTION(BlueprintImplementableEvent)
	FVector Override_GetLaunchDirection();

private:

	/**
	*
	* Currently supports To types of:
	*  NCsPooledObject::NPayload::FImplSlice (NCsPooledObject::NPayload::IPayload)
	*  NCsProjectile::NPayload::NImplSlice::FImplSlice (NCsProjectile::NPayload::IPayload)
	*
	* @param Context	The calling context.
	* @param Payload	The payload to set.
	* return			Whether the payload was successfully set.
	*/
	bool SetPayload(const FString& Context, CsProjectilePayloadType* Payload, const PayloadType& LaunchPayload);

	void Log_GetLaunchDirection(const ParamsType* LaunchParams, const FVector& Direction);

#pragma endregion Weapon_Fire_Projectile

// Spread
#pragma region
private:

	FVector GetLaunchSpreadLocation(const FVector& InLocation, const PayloadType& Payload);

	FVector GetLaunchSpreadDirection(const FVector& InDirection, const PayloadType& Payload);

#pragma endregion Spread

// Target
#pragma region
private:

	bool bTarget;

	USceneComponent* TargetComponent;

	FVector TargetLocation;

	FName TargetBone;

	int32 TargetID;

#pragma endregion Target

// Print
#pragma region
private:

	FString PrintWeaponNameAndClass();

	FString PrintWeaponNameClassAndOwner();

#pragma endregion Print
};