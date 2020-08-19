#pragma once
#include "Components/ActorComponent.h"
// Interfaces
#include "Managers/Time/CsUpdate.h"
#include "CsWeapon.h"
#include "Projectile/CsProjectileWeapon.h"
// Types
#include "Coroutine/CsTypes_Coroutine.h"
#include "Managers/Projectile/CsTypes_Projectile.h"
#include "Managers/Sound/CsTypes_Sound.h"
#include "CsProjectileWeaponComponent.generated.h"

class ICsData_Weapon;
class AActor;
struct FCsRoutine;
struct ICsPayload_Projectile;
struct FCsProjectilePooled;
struct ICsSoundPooledPayload;

UCLASS()
class CSWP_API UCsProjectileWeaponComponent : public UActorComponent,
											  public ICsUpdate,
											  public ICsWeapon,
											  public ICsProjectileWeapon
{
	GENERATED_UCLASS_BODY()

// UActorComponent Interface
#pragma region
public:

	virtual void BeginPlay() override;

#pragma endregion UActorComponent Interface

// ICsUpdate
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

protected:

	FECsUpdateGroup UpdateGroup;

public:

	void SetUpdateGroup(const FECsUpdateGroup& Group);

protected:

	FECsWeapon WeaponType;

public:

	void SetWeaponType(const FECsWeapon& Type);

protected:

	ICsData_Weapon* Data;

// ICsWeapon
#pragma region
public:

	ICsData_Weapon* GetData() const;

	const FECsWeaponState& GetCurrentState() const;

#pragma endregion ICsWeapon

protected: 

	FECsProjectile ProjectileType;

public:

	void SetProjectileType(const FECsProjectile& Type);

// ICsProjectileWeapon
#pragma region
public:

	void StartFire();

	void StopFire();

#pragma endregion ICsProjectileWeapon

protected:

	UObject* MyOwner;
	AActor* MyOwnerAsActor;

public:

	virtual void Init();

// State
#pragma region
protected:

	FECsWeaponState CurrentState;

	void OnUpdate_HandleStates(const FCsDeltaTime& DeltaTime);

	FECsWeaponState IdleState;
	FECsWeaponState FireState;

#pragma endregion State

// Ammo
#pragma region
protected:

	int32 CurrentAmmo;

#pragma endregion Ammo

// Fire
#pragma region
protected:

	bool CanFire() const;

	/** Whether to fire the weapon. */
	bool bFire;

	/** The value of bFire last Update. */
	bool bFire_Last;

	float Fire_StartTime;

	int32 FireCount;

	FCsRoutineHandle FireRoutineHandle;

	/**
	*
	*/
	void Fire();

	/**
	*
	*
	* @param R
	* return
	*/
	char Fire_Internal(FCsRoutine* R);

	/**
	*/
	void Fire_Internal_OnEnd(FCsRoutine* R);

	// Projectile
#pragma region
protected:

	/** */
	int32 CurrentProjectilePerShotIndex;

	void FireProjectile();

	virtual void SetTypeForProjectile(const FCsProjectilePooled* ProjectilePooled);

	virtual void SetProjectilePayload(ICsPayload_Projectile* Payload);

	virtual FVector GetLaunchProjectileLocation();

	virtual FVector GetLaunchProjectileDirection();

	virtual void LaunchProjectile(const FCsProjectilePooled* ProjectilePooled, ICsPayload_Projectile* Payload);

#pragma endregion Projectile
	
	// Sound
#pragma region
protected:

	void PlayFireSound();

	void SetSoundPooledPayload(ICsSoundPooledPayload* Payload, const FCsSound& Sound);

#pragma endregion Sound

#pragma endregion
};