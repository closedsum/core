// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "GameFramework/Actor.h"
// Interfaces
#include "Update/CsUpdate.h"
#include "Shutdown/CsShutdown.h"
#include "Managers/Pool/CsPooledObject.h"
#include "CsWeapon.h"
#include "Projectile/CsProjectileWeapon.h"
// Types
#include "CsMacro_Cached.h"
#include "Coroutine/CsTypes_Coroutine.h"
#include "Types/CsTypes_Projectile.h"
#include "Managers/Sound/CsTypes_SoundPooled.h"
#include "Managers/FX/CsTypes_FX.h"
#include "Modifier/Types/CsTypes_WeaponModifier.h"
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"

#include "CsProjectileWeaponActorPooled.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsProjectileWeaponActorPooled_OnConsumeAmmo, UObject*, Weapon, const int32&, PreviousAmmo, const int32&, NewAmmo);

#pragma endregion Delegates

// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// PooledCacheType (NCsPooledObject::NCache::ICache)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NCache, ICache)

class AActor;
struct FCsRoutine;

// DataType (NCsWeapon::NData::IData)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)
// PrjWeaponDataType (NCsWeapon::NCsProjectile::NData::IData)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsWeapon, NProjectile, NData, IData)

class USkeletalMeshComponent;
class UStaticMeshComponent;
class UPrimitiveComponent;

// CsProjectilePayloadType (NCsProjectile::NPayload::IPayload)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NPayload, IPayload)
// CsFXPayloadType (NCsFX::NPayload::IPayload)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NPayload, IPayload)
// LaunchPayloadType (NCsWeapon::NFire::NProjectile::NLaunch::NPayload::FPayload)
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NFire, NProjectile, NLaunch, NPayload, FPayload)

// NCsWeapon::NProjectile::NData::NVisual::NFire::IFire
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NProjectile, NData, NVisual, NFire, IFire)

// CsWeaponModifierType (NCsWEapon::NModifier::IModifier)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NModifier, IModifier)

// NCsProjectile::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NModifier, IModifier)

class USceneComponent;

// NCsWeapon::NProjectile::NParams::NLaunch::ILaunch
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NProjectile, NParams, NLaunch, ILaunch)

class ICsWeapon_Fire_TimeBetweenShots;
class ICsWeapon_Fire_Projectile;

CS_FWD_DECLARE_CACHED_FUNCTION_NAME(CsProjectileWeaponActorPooled)

UCLASS(BlueprintType)
class CSWP_API ACsProjectileWeaponActorPooled : public AActor,
											    public ICsUpdate,
												public ICsShutdown,
											    public ICsPooledObject,
											    public ICsWeapon,
											    public ICsProjectileWeapon
{
	GENERATED_UCLASS_BODY()

private:

	CS_USING_CACHED_FUNCTION_NAME(CsProjectileWeaponActorPooled);

	using PooledCacheType = NCsPooledObject::NCache::ICache;
	using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
	using DataType = NCsWeapon::NData::IData;
	using PrjWeaponDataType = NCsWeapon::NProjectile::NData::IData;
	using CsProjectilePayloadType = NCsProjectile::NPayload::IPayload;
	using CsFXPayloadType = NCsFX::NPayload::IPayload;
	using LaunchPayloadType = NCsWeapon::NFire::NProjectile::NLaunch::NPayload::FPayload;
	using CsWeaponModifierType = NCsWeapon::NModifier::IModifier;
	using CsProjectileModifierType = NCsProjectile::NModifier::IModifier;

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// AActor Interface
#pragma region
public:

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

#pragma endregion AActor Interface

// ICsUpdate
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Weapon|Update")
	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

// Update
#pragma region
protected:

	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Update", meta = (AllowPrivateAccess))
	FECsUpdateGroup UpdateGroup;

public:

	UFUNCTION(BlueprintCallable, Category = "Weapon|Update")
	void SetUpdateGroup(const FECsUpdateGroup& Group);

	FORCEINLINE const FECsUpdateGroup& GetUpdateGroup() const { return UpdateGroup; }

#pragma endregion Update

// ICsShutdown
#pragma region
public:

	void Shutdown();

	FORCEINLINE bool HasShutdown() const { return bShutdown; }

#pragma endregion ICsShutdown

// Shutdown
#pragma region
private:

	bool bShutdown;

#pragma endregion Shutdown

// ICsPooledObject
#pragma region
public:

	FORCEINLINE PooledCacheType* GetCache() const { return Cache; }

	void Allocate(PooledPayloadType* Payload);

	virtual void Deallocate();

#pragma endregion ICsPooledObject

// PooledObject
#pragma region
private:

	PooledCacheType* Cache;

	void ConstructCache();

#pragma endregion PooledObject

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Type", meta = (AllowPrivateAccess))
	FECsWeapon WeaponType;

public:

	UFUNCTION(BlueprintCallable, Category = "Weapon|Type")
	void SetWeaponType(const FECsWeapon& Type);

protected:

	DataType* Data;

	PrjWeaponDataType* PrjWeaponData;

// ICsWeapon
#pragma region
public:

	FORCEINLINE UObject* GetWeaponOwner() const					{ return MyOwner; }
	FORCEINLINE DataType* GetData() const						{ return Data; }
	FORCEINLINE const FECsWeaponState& GetCurrentState() const	{ return CurrentState; }

#pragma endregion ICsWeapon

protected: 

	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Projectile", meta = (AllowPrivateAccess))
	FECsProjectile ProjectileType;

public:

	UFUNCTION(BlueprintCallable, Category = "Weapon|Projectile")
	void SetProjectileType(const FECsProjectile& Type);

	FORCEINLINE const FECsProjectile& GetProjectileType() const { return ProjectileType; }

// ICsProjectileWeapon
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Weapon|ICsProjectileWeapon")
	void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon|ICsProjectileWeapon")
	void StopFire();

#pragma endregion ICsProjectileWeapon

// ProjectileWeapon
#pragma region
public:

	FORCEINLINE PrjWeaponDataType* GetPrjWeaponData() const { return PrjWeaponData; }

#pragma endregion ProjectileWeapon

public:

#if WITH_EDITOR
	const UObject* GetWorldContext() const;
#else
	FORCEINLINE const UObject* GetWorldContext() const { return this; }
#endif // #if WITH_EDITOR

// Owner
#pragma region
protected:

	UObject* MyOwner;
	AActor* MyOwnerAsActor;

public:

	UFUNCTION(BlueprintPure, Category = "Weapon|Owner")
	FORCEINLINE UObject* GetMyOwner() const 
	{
		return MyOwner;
	}

#pragma endregion Owner

// Skin
#pragma region
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMeshComponent;

public:

	FORCEINLINE USkeletalMeshComponent* GetSkeletalMeshComponent() const { return SkeletalMeshComponent; }

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	UPrimitiveComponent* VisualMeshComponent;

#pragma endregion Skin

// State
#pragma region
protected:

	UPROPERTY(BlueprintReadOnly, Category = "Weapon|State", meta = (AllowPrivateAccess))
	FECsWeaponState CurrentState;

	void OnUpdate_HandleStates(const FCsDeltaTime& DeltaTime);

	FECsWeaponState IdleState;
	FECsWeaponState FireState;

#pragma endregion State

protected:

	virtual void GetWeaponModifiers(TArray<CsWeaponModifierType*>& OutModifiers) const {}

// Ammo
#pragma region
protected:

	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Ammo", meta = (AllowPrivateAccess))
	int32 CurrentAmmo;

	virtual void ConsumeAmmo();

public:

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnConsumeAmmo, ICsWeapon* /*Weapon*/, const int32& /*PreviousAmmo*/, const int32& /*NewAmmo*/);

	FOnConsumeAmmo OnConsumeAmmo_Event;

#pragma endregion Ammo

// Fire
#pragma region
public:

	bool CanFire() const;

protected:

	/** Whether Fire has been called at least once. */
	bool bHasFired;

	/** Whether to fire the weapon. */
	bool bFire;

	/** The value of bFire last Update. */
	bool bFire_Last;

	float Fire_StartTime;

	int32 FireCount;

	void Fire();

	void Fire_PreStart(const uint32& FireID);

public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFire_PreStart, ACsProjectileWeaponActorPooled* /*Weapon*/, const uint32& /*FireID*/);
	
	FOnFire_PreStart OnFire_PreStart_Event;

protected:

	char Fire_Internal(FCsRoutine* R);

	void Fire_PreShot(const uint32& FireID);

public:

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnFire_PreShot, ACsProjectileWeaponActorPooled* /*Weapon*/, const uint32& /*FireID*/, const int32& /*CurrentProjectilePerShotIndex*/);

	FOnFire_PreShot OnFire_PreShot_Event;

protected:

	void Fire_Internal_OnEnd(FCsRoutine* R);

public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFire_End, ACsProjectileWeaponActorPooled* /*Weapon*/, FCsRoutine* /*R*/);

	FOnFire_End OnFire_End_Event;

protected:

	TSet<uint32> FireIDs;

	TSet<FCsRoutineHandle> FireHandles;

	FCsScopedTimerHandleWrapper FireScopedHandle;

	// TimeBetweenShots
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Fire|Time Between Shots", meta = (MustImplement = "/Script.CsWp.CsWeapon_Fire_TimeBetweenShots"))
	TSoftClassPtr<UObject> TimeBetweenShotsClass;

protected:

	ICsWeapon_Fire_TimeBetweenShots* TimeBetweenShotsImpl;

	float GetTimeBetweenShots() const;

	// Projectile
#pragma region
protected:

	int32 ProjectilesPerShot_GetCount() const;

	float ProjectilesPerShot_GetInterval() const;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Fire|Projectile", meta = (MustImplement = "/Script.CsWp.CsWeapon_Fire_Projectile"))
	TSoftClassPtr<UObject> ProjectileClass;

protected:

	ICsWeapon_Fire_Projectile* ProjectileImpl;

public:

	UFUNCTION(BlueprintCallable, Category = "Weapon|Fire|Projectile")
	void ProjectileImpl_SetLaunchComponentLocation(USceneComponent* Component);

	UFUNCTION(BlueprintCallable, Category = "Weapon|Fire|Projectile")
	void ProjectileImpl_SetLaunchComponentDirection(USceneComponent* Component);

protected:

	/** If set, calls Override_ProjectileImpl_GetLaunchDirection when calling
	    ProjectileImpl->GetLaunchDirection(). 
		This flag is intended to be set by Blueprint | script and allow a non-native 
		path to adjust the launch direction of the projectile. */
	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Fire|Projectile")
	bool bOverride_ProjectileImpl_GetLaunchDirection;

public:

	FORCEINLINE bool ShouldOverride_ProjectileImpl_GetLaunchDirection() const { return bOverride_ProjectileImpl_GetLaunchDirection; }

protected:

	/** 
	* Only Valid if bOverride_ProjectileImpl_GetLaunchDirection == true. 
	* This provides a non-native (Blueprint | script) path to adjust the launch direction 
	* of the projectile. 
	* 
	* return Launch Direction.
	*/
	UFUNCTION(BlueprintImplementableEvent)
	FVector3f Override_ProjectileImpl_GetLaunchDirection();

	bool UseSpreadParams() const;

public:

	virtual void GetProjectileModifiers(TArray<CsProjectileModifierType*>& OutModifiers) const {}

public:

	virtual bool Projectile_SetPayload(const FString& Context, CsProjectilePayloadType* Payload, const LaunchPayloadType& LaunchPayload) { return true; }

#pragma endregion Projectile
	
	// Sound
#pragma region
public:

	struct CSWP_API FSoundImpl
	{
		friend class ACsProjectileWeaponActorPooled;

	protected:

		ACsProjectileWeaponActorPooled* Outer;

		USceneComponent* Component;

	public:

		FSoundImpl() :
			Outer(nullptr),
			Component(nullptr)
		{
		}

	public:

		FORCEINLINE void SetComponent(USceneComponent* InComponent)
		{
			Component = InComponent;
		}

	protected:

		/**
		*/
		void Play(const int32 CurrentProjectilePerShotIndex);
	};

	FSoundImpl* SoundImpl;

protected:

	virtual FSoundImpl* ConstructSoundImpl();

#pragma endregion Sound

	// FX
#pragma region
public:

	struct CSWP_API FFXImpl
	{
		friend class ACsProjectileWeaponActorPooled;

	protected:

		ACsProjectileWeaponActorPooled* Outer;

		USceneComponent* Component;

	public:

		FFXImpl() :
			Outer(nullptr),
			Component(nullptr)
		{
		}

		/**
		* Set the Component from which FX are emitted from.
		* Usually this is the Root Component of the Weapon or the Owner of the Weapon.
		*
		* @param Component
		*/
		FORCEINLINE void SetComponent(USceneComponent* InComponent)
		{
			Component = InComponent;
		}

	protected:

		using FXDataType = NCsWeapon::NProjectile::NData::NVisual::NFire::IFire;

		/**
		*/
		void Play(const int32 CurrentProjectilePerShotIndex, const LaunchPayloadType& LaunchPayload);
	
	public:

		/**
		*
		*
		* @param Payload
		* @param FX
		*/
		void SetPayload(const int32 CurrentProjectilePerShotIndex, CsFXPayloadType* Payload, const FCsFX& FX, const LaunchPayloadType& LaunchPayload);


		/**
		*
		*
		* @param Payload
		* @param FXData
		*/
		void SetPayload(const int32 CurrentProjectilePerShotIndex, CsFXPayloadType* Payload, FXDataType* FXData);
	};

	FFXImpl* FXImpl;

protected:

	virtual FFXImpl* ConstructFXImpl();

public:

	/**
	* Set the Component from which FX are emitted from.
	* Usually this is the Root Component of the Weapon or the Owner of the Weapon.
	* 
	* @param Component
	*/
	UFUNCTION(BlueprintCallable, Category = "Weapon|Fire|FX")
	void FXImpl_SetComponent(USceneComponent* Component);

#pragma endregion FX

#pragma endregion Fire

// Modifier
#pragma region
public:

	virtual bool GetModifiedIntProperty(const FECsWeaponModifier& ModifierType, int32& OutValue) const;
	virtual bool GetModifiedFloatProperty(const FECsWeaponModifier& ModifierType, float& OutValue) const;

#pragma endregion Modifier

// Print
#pragma region
public:

	FString PrintNameAndClass();

	FString PrintNameClassAndOwner();

#pragma endregion Print
};