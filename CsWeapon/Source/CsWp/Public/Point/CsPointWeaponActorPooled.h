#pragma once
#include "GameFramework/Actor.h"
// Interfaces
#include "Managers/Time/CsUpdate.h"
#include "Managers/Pool/CsPooledObject.h"
#include "CsWeapon.h"
#include "Point/CsPointWeapon.h"
#include "Event/CsWeapon_Event.h"
#include "Point/Event/CsPointWeapon_Event.h"
// Types
#include "Coroutine/CsTypes_Coroutine.h"
#include "Types/CsTypes_Projectile.h"
#include "Managers/Sound/CsTypes_Sound.h"
#include "Managers/FX/CsTypes_FX.h"
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"

#include "CsPointWeaponActorPooled.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsPointWeaponActorPooled_OnConsumeAmmo, UObject*, Weapon, const int32&, PreviousAmmo, const int32&, NewAmmo);

#pragma endregion Delegates

// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// NCsPooledObject::NCache::ICache
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NCache, ICache)

class AActor;
struct FCsRoutine;

// NCsWeapon::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)
// NCsWeapon::NPoint::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsWeapon, NPoint, NData, IData)
// NCsWeapon::NPoint::NData::NVisual::NFire::IFire
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NPoint, NData, NVisual, NFire, IFire)

class USkeletalMeshComponent;
class UStaticMeshComponent;
class UPrimitiveComponent;

// NCsSound::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSound, NPayload, IPayload)
// NCsFX::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NPayload, IPayload)

// NCsWeapon::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NModifier, IModifier)

class USceneComponent;

UCLASS(BlueprintType)
class CSWP_API ACsPointWeaponActorPooled : public AActor,
										   public ICsUpdate,
										   public ICsPooledObject,
										   public ICsWeapon,
										   public ICsPointWeapon,
										   public ICsWeapon_Event,
										   public ICsPointWeapon_Event
{
	GENERATED_UCLASS_BODY()

#define PooledCacheType NCsPooledObject::NCache::ICache
#define PooledPayloadType NCsPooledObject::NPayload::IPayload
#define DataType NCsWeapon::NData::IData
#define PointWeaponDataType NCsWeapon::NPoint::NData::IData
#define SoundPayloadType NCsSound::NPayload::IPayload
#define FXPayloadType NCsFX::NPayload::IPayload

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// AActor Interface
#pragma region
public:

	virtual void BeginPlay() override;

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

	PointWeaponDataType* PointWeaponData;

// ICsWeapon
#pragma region
public:

	FORCEINLINE DataType* GetData() const { return Data; }

	FORCEINLINE PointWeaponDataType* GetPointWeaponData() const { return PointWeaponData; }

	FORCEINLINE const FECsWeaponState& GetCurrentState() const { return CurrentState; }

#pragma endregion ICsWeapon

// ICsPointWeapon
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Weapon|ICsPointWeapon")
	void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon|ICsPointWeapon")
	void StopFire();

#pragma endregion ICsPointWeapon

// ICsWeapon_Event
#pragma region
public:

	FORCEINLINE ICsWeapon_Event::FOnAllocate& GetOnAllocate_Event() { return OnAllocate_Event; }
	FORCEINLINE ICsWeapon_Event::FOnDeallocate_Start& GetOnDeallocate_Start_Event() { return OnDeallocate_Start_Event; }

#pragma endregion ICsWeapon_Event

// ICsPointWeapon_Event
#pragma region
public:

	FORCEINLINE ICsPointWeapon_Event::FOnHit& GetOnHit_Event() { return OnHit_Event; }

#pragma endregion ICsPointWeapon_Event

// Events
#pragma region
protected:

	ICsWeapon_Event::FOnAllocate OnAllocate_Event;

	ICsWeapon_Event::FOnDeallocate_Start OnDeallocate_Start_Event;

	ICsPointWeapon_Event::FOnHit OnHit_Event;

#pragma endregion Events

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

#define WeaponModifierType NCsWeapon::NModifier::IModifier
	virtual void GetWeaponModifiers(TArray<WeaponModifierType*>& OutModifiers) const {}
#undef WeaponModifierType

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

	void Fire();

	void Fire_PreStart(const uint32& FireID);

public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFire_PreStart, ACsPointWeaponActorPooled* /*Weapon*/, const uint32& /*FireID*/);
	
	FOnFire_PreStart OnFire_PreStart_Event;

protected:

	char Fire_Internal(FCsRoutine* R);

	void Fire_PreShot(const uint32& FireID);

public:

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnFire_PreShot, ACsPointWeaponActorPooled* /*Weapon*/, const uint32& /*FireID*/, const int32& /*CurrentProjectilePerShotIndex*/);

	FOnFire_PreShot OnFire_PreShot_Event;

protected:

	void Fire_Internal_OnEnd(FCsRoutine* R);

public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFire_End, ACsPointWeaponActorPooled* /*Weapon*/, FCsRoutine* /*R*/);

	FOnFire_End OnFire_End_Event;

protected:

	TSet<uint32> FireIDs;

	TSet<FCsRoutineHandle> FireHandles;

	FCsScopedTimerHandleWrapper FireScopedHandle;

public:

	/**
	*/
	struct CSWP_API FTimeBetweenShotsImpl
	{
		friend class ACsPointWeaponActorPooled;

	protected:

		ACsPointWeaponActorPooled* Outer;

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

		FORCEINLINE void Clear()
		{
			OnElapsedTime_Event.Clear();
			OnElapsedTimeAsPercent_Event.Clear();
			OnComplete_Event.Clear();
		}
	};

	FTimeBetweenShotsImpl TimeBetweenShotsImpl;

protected:

	float GetTimeBetweenShots() const;

	// Point
#pragma region
protected:

	int32 PointsPerShot_GetCount() const;

	float PointsPerShot_GetInterval() const;

public:

	struct CSWP_API FPointImpl
	{
		friend class ACsPointWeaponActorPooled;

	private:

		ACsPointWeaponActorPooled* Outer;

	public:

		FVector Start;

		bool bDestination;

		FVector Destination;

		FPointImpl() :
			Outer(nullptr),
			Start(FVector::ZeroVector),
			bDestination(false),
			Destination(FVector::ZeroVector)
		{
		}

		FORCEINLINE bool HasValidDestination() const { return bDestination; }

		FORCEINLINE float CalculateDistance() const { return (Destination - Start).Size(); }

		FORCEINLINE FVector CalculateDirection() const { return (Destination - Start).GetSafeNormal(); }
		FORCEINLINE FVector CalculateInverseDirection() const { return -1.0f * CalculateDirection(); }
	};

	FPointImpl PointImpl;

protected:

	virtual void Point_Execute(const int32& CurrentPointPerShotIndex);

#pragma endregion Point
	
	// Sound
#pragma region
public:

	struct CSWP_API FSoundImpl
	{
		friend class ACsPointWeaponActorPooled;

	protected:

		ACsPointWeaponActorPooled* Weapon;

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
		friend class ACsPointWeaponActorPooled;

	protected:

		ACsPointWeaponActorPooled* Outer;

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

		void Play();
	
	public:

	#define FXDataType NCsWeapon::NPoint::NData::NVisual::NFire::IFire
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
	UFUNCTION(BlueprintCallable, Category = "Weapon|Point|Fire|FX")
	void FXImpl_SetComponent(USceneComponent* Component);

#pragma endregion FX

#pragma endregion Fire

// Print
#pragma region
public:

	FString PrintNameAndClass();

	FString PrintNameClassAndOwner();

#pragma endregion Print

#undef PooledCacheType
#undef PooledPayloadType
#undef DataType
#undef PointWeaponDataType
#undef SoundPayloadType
#undef FXPayloadType
};