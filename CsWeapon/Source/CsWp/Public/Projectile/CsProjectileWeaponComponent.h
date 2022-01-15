#pragma once
#include "Components/ActorComponent.h"
// Interfaces
#include "Managers/Time/CsUpdate.h"
#include "CsWeapon.h"
#include "Projectile/CsProjectileWeapon.h"
// Types
#include "Coroutine/CsTypes_Coroutine.h"
#include "Types/CsTypes_Projectile.h"
#include "Managers/Sound/CsTypes_Sound.h"
#include "Managers/FX/CsTypes_FX.h"
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"

#include "CsProjectileWeaponComponent.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsProjectileWeaponComponent_OnConsumeAmmo, UObject*, Weapon, const int32&, PreviousAmmo, const int32&, NewAmmo);

#pragma endregion Delegates

class AActor;
struct FCsRoutine;

// NCsWeapon::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)
// NCsProjectile::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NPayload, IPayload)
// NCsSound::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSound, NPayload, IPayload)
// NCsFX::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NPayload, IPayload)
// NCsWeapon::NProjectile::NData::NVisual::NFire::IFire
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NProjectile, NData, NVisual, NFire, IFire)
// NCsProjectile::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NModifier, IModifier)

struct FCsProjectilePooled;

class USceneComponent;

// NCsWeapon::NProjectile::NParams::NLaunch::ILaunch
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NProjectile, NParams, NLaunch, ILaunch)

UCLASS(BlueprintType)
class CSWP_API UCsProjectileWeaponComponent : public UActorComponent,
											  public ICsUpdate,
											  public ICsWeapon,
											  public ICsProjectileWeapon
{
	GENERATED_UCLASS_BODY()

#define DataType NCsWeapon::NData::IData
#define ProjectilePayloadType NCsProjectile::NPayload::IPayload
#define SoundPayloadType NCsSound::NPayload::IPayload
#define FXPayloadType NCsFX::NPayload::IPayload

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region
public:

	virtual void BeginPlay() override;

#pragma endregion UActorComponent Interface

// ICsUpdate
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Weapon|Update")
	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Update", meta = (AllowPrivateAccess))
	FECsUpdateGroup UpdateGroup;

public:

	UFUNCTION(BlueprintCallable, Category = "Weapon|Update")
	void SetUpdateGroup(const FECsUpdateGroup& Group);

	FORCEINLINE const FECsUpdateGroup& GetUpdateGroup() const { return UpdateGroup; }

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Type", meta = (AllowPrivateAccess))
	FECsWeapon WeaponType;

public:

	UFUNCTION(BlueprintCallable, Category = "Weapon|Type")
	void SetWeaponType(const FECsWeapon& Type);

protected:

	DataType* Data;

// ICsWeapon
#pragma region
public:

	FORCEINLINE DataType* GetData() const { return Data; }

	FORCEINLINE const FECsWeaponState& GetCurrentState() const { return CurrentState; }

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

public:

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Init();

// State
#pragma region
protected:

	UPROPERTY(BlueprintReadOnly, Category = "Weapon|State", meta = (AllowPrivateAccess))
	FECsWeaponState CurrentState;

	void OnUpdate_HandleStates(const FCsDeltaTime& DeltaTime);

	FECsWeaponState IdleState;
	FECsWeaponState FireState;

#pragma endregion State

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
protected:

	bool CanFire() const;

	/** Whether Fire has been called at least once. */
	bool bHasFired;

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

	FCsScopedTimerHandleWrapper FireScopedHandle;

public:

	float TimeBetweenShots;

	/**
	*/
	struct CSWP_API FTimeBetweenShotsImpl
	{
		friend class UCsProjectileWeaponComponent;

	protected:

		UCsProjectileWeaponComponent* Outer;

	public:

		/**
		* Delegate type for getting the time elapsed between "shots" after Fire() is called.
		* 
		* @param Weapon
		* @param PreviousTime
		* @param NewTime
		*/
		DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnElapsedTime, ICsWeapon* /*Weapon*/, const float& /*PreviousTime*/, const float& /*NewTime*/);

		/** Delegate for getting the time elapsed between "shots" after Fire() is called. */
		FOnElapsedTime OnElapsedTime_Event;

		/**
		* Delegate type for getting the time elapsed as a percent between "shots" after Fire() is called.
		* 
		* @param Weapon
		* @param PreviousValue
		* @param NewValue
		*/
		DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnElapsedTimeAsPercent, ICsWeapon* /*Weapon*/, const float& /*PreviousValue*/, const float& /*NewValue*/);

		/** Delegate for getting the time elapsed as a percent between "shots" after Fire() is called. */
		FOnElapsedTimeAsPercent OnElapsedTimeAsPercent_Event;

		/**
		* Delegate type for when Fire() has "completed". Meaning time between shots amount of time has elapsed from
		* Fire() being called.
		* 
		* @param Weapon
		*/
		DECLARE_MULTICAST_DELEGATE_OneParam(FOnComplete, ICsWeapon* /*Weapon*/);

		FOnComplete OnComplete_Event;

		FTimeBetweenShotsImpl() :
			Outer(nullptr),
			OnElapsedTime_Event(),
			OnElapsedTimeAsPercent_Event(),
			OnComplete_Event()
		{
		}

	private:

		void OnElapsedTime();

		char OnElapsedTime_Internal(FCsRoutine* R);
	};

	FTimeBetweenShotsImpl TimeBetweenShotsImpl;

	// Projectile
#pragma region
protected:

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Fire|Projectile", meta = (AllowPrivateAccess))
	int32 CurrentProjectilePerShotIndex;

public:

	/**
	*/
	struct CSWP_API FProjectileImpl
	{
		friend class UCsProjectileWeaponComponent;

	protected:

		UCsProjectileWeaponComponent* Outer;

		USceneComponent* LaunchComponentTransform;

		FCsScopedTimerHandle LaunchScopedHandle;

	public:

		FVector CustomLaunchDirection;

	public:

		FProjectileImpl() :
			Outer(nullptr),
			LaunchComponentTransform(nullptr),
			LaunchScopedHandle(),
			CustomLaunchDirection(FVector::ZeroVector)
		{
		}

	public:

		FORCEINLINE void SetLaunchComponentTransform(USceneComponent* Component)
		{
			LaunchComponentTransform = Component;
		}

	protected:

		/**
		*
		* Currently supports To types of:
		*  NCsPooledObject::NPayload::FImplSlice (NCsPooledObject::NPayload::IPayload)
		*  NCsProjectile::NPayload::FImplSlice (NCsProjectile::NPayload::IPayload)
		*
		* @param Context	The calling context.
		* @param Payload	The payload to set.
		* return			Whether the payload was successfully set.
		*/
		virtual bool SetPayload(const FString& Context, ProjectilePayloadType* Payload);

		/**
		* Copy the slice of values from From to To with checks.
		* Currently supports To types of:
		*  NCsPooledObject::NPayload::FImplSlice (NCsPooledObject::NPayload::IPayload)
		*  NCsProjectile::NPayload::FImplSlice (NCsProjectile::NPayload::IPayload)
		*
		* @param Context	The calling context.
		* @param From		What to copy.
		* @param To			What to copy to.
		* return			Whether the From copied to To successfully.
		*/
		virtual bool CopyPayload(const FString& Context, const ProjectilePayloadType* From, ProjectilePayloadType* To);

		virtual FVector GetLaunchLocation();

		virtual FVector GetLaunchDirection();

	#define LaunchParamsType NCsWeapon::NProjectile::NParams::NLaunch::ILaunch
		void Log_GetLaunchDirection(const LaunchParamsType* LaunchParams, const FVector& Direction);
	#undef LaunchParamsType

		void Launch();
	};

	FProjectileImpl* ProjectileImpl;

protected:

	virtual FProjectileImpl* ConstructProjectileImpl();

public:

	UFUNCTION(BlueprintCallable, Category = "Weapon|Fire|Projectile")
	void ProjectileImpl_SetLaunchComponentTransform(USceneComponent* Component);

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
	FVector Override_ProjectileImpl_GetLaunchDirection();

public:

#define PrjModifierType NCsProjectile::NModifier::IModifier
	virtual void GetProjectileModifiers(TArray<PrjModifierType*>& OutModifiers);
#undef PrjModifierType

#pragma endregion Projectile
	
	// Sound
#pragma region
public:

	struct CSWP_API FSoundImpl
	{
		friend class UCsProjectileWeaponComponent;

	protected:

		UCsProjectileWeaponComponent* Weapon;

		USceneComponent* Component;

	public:

		FSoundImpl() :
			Weapon(nullptr),
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
		void Play();
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
		friend class UCsProjectileWeaponComponent;

	protected:

		UCsProjectileWeaponComponent* Weapon;

		USceneComponent* Component;

	public:

		FFXImpl() :
			Weapon(nullptr),
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

		/**
		*/
		void Play();
	
	public:

		/**
		*
		*
		* @param Payload
		* @param FX
		*/
		void SetPayload(FXPayloadType* Payload, const FCsFX& FX);

#define FXDataType NCsWeapon::NProjectile::NData::NVisual::NFire::IFire
		/**
		*
		*
		* @param Payload
		* @param FXData
		*/
		void SetPayload(FXPayloadType* Payload, FXDataType* FXData);

#undef FXDataType
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

// Print
#pragma region
public:

	FString PrintNameAndClass();

	FString PrintNameClassAndOwner();

#pragma endregion Print

#undef DataType
#undef ProjectilePayloadType
#undef SoundPayloadType
#undef FXPayloadType
};