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
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"

#include "CsProjectileWeaponComponent.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsProjectileWeaponComponent_OnConsumeAmmo, UObject*, Weapon, const int32&, PreviousAmmo, const int32&, NewAmmo);

#pragma endregion Delegates

class ICsData_Weapon;
class AActor;
struct FCsRoutine;

namespace NCsProjectile {
	namespace NPayload {
		struct IPayload; } }

namespace NCsSound {
	namespace NPayload {
		struct IPayload; } }

struct FCsProjectilePooled;

class USceneComponent;

UCLASS()
class CSWP_API UCsProjectileWeaponComponent : public UActorComponent,
											  public ICsUpdate,
											  public ICsWeapon,
											  public ICsProjectileWeapon
{
	GENERATED_UCLASS_BODY()

#define ProjectilePayloadType NCsProjectile::NPayload::IPayload
#define SoundPayloadType NCsSound::NPayload::IPayload

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

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Update", meta = (AllowPrivateAccess))
	FECsUpdateGroup UpdateGroup;

public:

	void SetUpdateGroup(const FECsUpdateGroup& Group);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Type", meta = (AllowPrivateAccess))
	FECsWeapon WeaponType;

public:

	void SetWeaponType(const FECsWeapon& Type);

protected:

	ICsData_Weapon* Data;

// ICsWeapon
#pragma region
public:

	FORCEINLINE ICsData_Weapon* GetData() const
	{
		return Data;
	}

	FORCEINLINE const FECsWeaponState& GetCurrentState() const
	{
		return CurrentState;
	}

#pragma endregion ICsWeapon

protected: 

	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Projectile", meta = (AllowPrivateAccess))
	FECsProjectile ProjectileType;

public:

	void SetProjectileType(const FECsProjectile& Type);

	FORCEINLINE const FECsProjectile& GetProjectileType() const
	{
		return ProjectileType;
	}

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

	FORCEINLINE UObject* GetMyOwner() const 
	{
		return MyOwner;
	}

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
	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Fire|Projectile", meta = (AllowPrivateAccess))
	int32 CurrentProjectilePerShotIndex;

public:

	/**
	*/
	struct CSWP_API FProjectileImpl
	{
		friend class UCsProjectileWeaponComponent;

	protected:

		UCsProjectileWeaponComponent* Weapon;

		USceneComponent* LaunchComponentTransform;

		FCsScopedTimerHandle GetLaunchLocationScopedHandle;

		FCsScopedTimerHandle GetLaunchDirectionScopedHandle;

	public:

		FProjectileImpl() :
			Weapon(nullptr),
			LaunchComponentTransform(nullptr),
			GetLaunchLocationScopedHandle(),
			GetLaunchDirectionScopedHandle()
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
		*
		* @param Context			The calling context.
		* @param ProjectilePooled
		* return					Whether the type was successfully set.
		*/
		virtual bool SetType(const FString& Context, const FCsProjectilePooled* ProjectilePooled);

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

		void StartLaunch();

		/**
		*
		*
		* @param ProjectilePooled
		* @param Payload
		*/
		virtual void Launch(const FCsProjectilePooled* ProjectilePooled, ProjectilePayloadType* Payload);
	};

	FProjectileImpl* ProjectileImpl;

protected:

	virtual FProjectileImpl* ConstructProjectileImpl();

#pragma endregion Projectile
	
	// Sound
#pragma region
public:

	struct CSWP_API FSoundImpl
	{
		friend class UCsProjectileWeaponComponent;

	protected:

		UCsProjectileWeaponComponent* Weapon;

	public:

		FSoundImpl() :
			Weapon(nullptr)
		{
		}

	protected:

		/**
		*/
		void Play();

		/**
		*
		*
		* @param Payload
		* @param Sound
		*/
		void SetPayload(SoundPayloadType* Payload, const FCsSound& Sound);
	};

	FSoundImpl* SoundImpl;

protected:

	virtual FSoundImpl* ConstructSoundImpl();

#pragma endregion Sound

#pragma endregion Fire

// Print
#pragma region
public:

	FString PrintNameAndClass();

	FString PrintNameClassAndOwner();

#pragma endregion Print

#undef ProjectilePayloadType
#undef SoundPayloadType
};