#pragma once
#include "Components/ActorComponent.h"
// Interfaces
#include "Managers/Time/CsUpdate.h"
#include "CsWeapon.h"
#include "Trace/CsTraceWeapon.h"
// Types
#include "Coroutine/CsTypes_Coroutine.h"
#include "Managers/Projectile/CsTypes_Projectile.h"
#include "Managers/Sound/CsTypes_Sound.h"
#include "Managers/FX/CsTypes_FX.h"
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"

#include "CsTraceWeaponComponent.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsTraceWeaponComponent_OnConsumeAmmo, UObject*, Weapon, const int32&, PreviousAmmo, const int32&, NewAmmo);

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
// NCsWeapon::NTrace::NData::NVisual::NFire::IFire
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NTrace, NData, NVisual, NFire, IFire)

class USceneComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;

UCLASS()
class CSWP_API UCsTraceWeaponComponent : public UActorComponent,
										 public ICsUpdate,
										 public ICsWeapon,
										 public ICsTraceWeapon
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

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Update", meta = (AllowPrivateAccess))
	FECsUpdateGroup UpdateGroup;

public:

	void SetUpdateGroup(const FECsUpdateGroup& Group);

	FORCEINLINE const FECsUpdateGroup& GetUpdateGroup() const 
	{
		return UpdateGroup;
	}

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Type", meta = (AllowPrivateAccess))
	FECsWeapon WeaponType;

public:

	void SetWeaponType(const FECsWeapon& Type);

protected:

	DataType* Data;

// ICsWeapon
#pragma region
public:

	FORCEINLINE DataType* GetData() const
	{
		return Data;
	}

	FORCEINLINE const FECsWeaponState& GetCurrentState() const
	{
		return CurrentState;
	}

#pragma endregion ICsWeapon

// ICsTraceWeapon
#pragma region
public:

	void StartFire();

	void StopFire();

#pragma endregion ICsTraceWeapon

// Components
#pragma region
protected:

	USceneComponent* RootComponent;

#pragma endregion Components

// Owner
#pragma region
protected:

	UObject* MyOwner;
	AActor* MyOwnerAsActor;

public:

	FORCEINLINE UObject* GetMyOwner() const 
	{
		return MyOwner;
	}

#pragma endregion Owner

public:

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

	FCsScopedTimerHandleWrapper FireScopedHandle;

public:

	/**
	*/
	struct CSWP_API FTimeBetweenShotsImpl
	{
		friend class UCsTraceWeaponComponent;

	protected:

		UCsTraceWeaponComponent* Outer;

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

	// Trace
#pragma region
public:

	/**
	*/
	struct CSWP_API FTraceImpl
	{
		friend class UCsTraceWeaponComponent;

	protected:

		UCsTraceWeaponComponent* Outer;

		USceneComponent* TraceComponentTransform;

		/**
 		* Delegate type for custom implementation of GetStart().
		*
		* return Start Location 
		*/
		DECLARE_DELEGATE_RetVal(FVector, FGetStart);

		/**  Delegate for custom implementation of GetStart(). */
		FGetStart GetStartImpl;

		/**
		* Delegate type for custom implementation of GetDirection().
		*
		* return Direction 
		*/
		DECLARE_DELEGATE_RetVal(FVector, FGetDirection);

		/** Delegate for custom implementation of GetDirection(). */
		FGetDirection GetDirectionImpl;

	public:

		FTraceImpl() :
			Outer(nullptr),
			TraceComponentTransform(nullptr),
			GetStartImpl(),
			GetDirectionImpl()
		{
		}

	public:

		FORCEINLINE void SetTraceComponentTransform(USceneComponent* Component)
		{
			TraceComponentTransform = Component;
		}

	protected:

		FVector GetStart();
		FVector GetDirection();
		FVector GetEnd(const FVector& Start);
	};

	FTraceImpl* TraceImpl;

protected:

	virtual FTraceImpl* ConstructTraceImpl();

	FCsScopedTimerHandle TraceScopedHandle;

	void Trace();

#pragma endregion Trace
	
	// Sound
#pragma region
public:

	struct CSWP_API FSoundImpl
	{
		friend class UCsTraceWeaponComponent;

	protected:

		UCsTraceWeaponComponent* Weapon;

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

	public:

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

	// FX
#pragma region
public:

	struct CSWP_API FFXImpl
	{
		friend class UCsTraceWeaponComponent;

	protected:

		UCsTraceWeaponComponent* Weapon;

		USceneComponent* Component;

	public:

		FFXImpl() :
			Weapon(nullptr),
			Component(nullptr)
		{
		}

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

#define FXDataType NCsWeapon::NTrace::NData::NVisual::NFire::IFire
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

#pragma endregion FX

#pragma endregion Fire

// Visual
#pragma region
protected:

	UStaticMeshComponent* StaticMeshComponent;

public:

	FORCEINLINE UStaticMeshComponent* GetStaticMeshComponent() const
	{
		return StaticMeshComponent;
	}

	FORCEINLINE UStaticMeshComponent* GetStaticMeshComponentChecked(const FString& Context) const
	{
		checkf(StaticMeshComponent, TEXT("%s: StaticMeshComponent is NULL."), *Context);

		return StaticMeshComponent;
	}

protected:

	USkeletalMeshComponent* SkeletalMeshComponent;

public:

	void ConstructSkeletalMeshComponent();

	FORCEINLINE USkeletalMeshComponent* GetSkeletalMeshComponent() const
	{
		return SkeletalMeshComponent;
	}

	FORCEINLINE USkeletalMeshComponent* GetSkeletalMeshComponentChecked(const FString& Context) const
	{
		checkf(SkeletalMeshComponent, TEXT("%s: SkeletalMeshComponent is NULL."), *Context);

		return SkeletalMeshComponent;
	}

#pragma endregion Visual

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