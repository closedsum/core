#pragma once
#include "GameFramework/Actor.h"
// Interfaces
#include "Update/CsUpdate.h"
#include "Shutdown/CsShutdown.h"
#include "Managers/Pool/CsPooledObject.h"
#include "CsWeapon.h"
#include "Point/Sequence/CsPointSequenceWeapon.h"
#include "Event/CsWeapon_Event.h"
#include "Point/Sequence/Event/CsPointSequenceWeapon_Event.h"
// Types
#include "Coroutine/CsTypes_Coroutine.h"
#include "Types/CsTypes_Projectile.h"
#include "Managers/Sound/CsTypes_SoundPooled.h"
#include "Managers/FX/CsTypes_FX.h"
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"

#include "CsPointSequenceWeaponActorPooled.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsPointSequenceWeaponActorPooled_OnConsumeAmmo, UObject*, Weapon, const int32&, PreviousAmmo, const int32&, NewAmmo);

#pragma endregion Delegates

// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// NCsPooledObject::NCache::ICache
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NCache, ICache)

class AActor;
struct FCsRoutine;

// NCsWeapon::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)
// NCsWeapon::NPoint::NSequence::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NPoint, NSequence, NData, IData)
// NCsWeapon::NPoint::NSequence::NData::NVisual::NFire::IFire
CS_FWD_DECLARE_STRUCT_NAMESPACE_6(NCsWeapon, NPoint, NSequence, NData, NVisual, NFire, IFire)

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
class CSWP_API ACsPointSequenceWeaponActorPooled : public AActor,
										   public ICsUpdate,
										   public ICsShutdown,
										   public ICsPooledObject,
										   public ICsWeapon,
										   public ICsPointSequenceWeapon,
										   public ICsWeapon_Event,
										   public ICsPointSequenceWeapon_Event
{
	GENERATED_UCLASS_BODY()

#define PooledCacheType NCsPooledObject::NCache::ICache
#define PooledPayloadType NCsPooledObject::NPayload::IPayload
#define DataType NCsWeapon::NData::IData
#define PointSequenceWeaponDataType NCsWeapon::NPoint::NSequence::NData::IData
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

	PointSequenceWeaponDataType* PointSequenceWeaponData;

// ICsWeapon
#pragma region
public:

	FORCEINLINE DataType* GetData() const { return Data; }

	FORCEINLINE PointSequenceWeaponDataType* GetPointSequenceWeaponData() const { return PointSequenceWeaponData; }

	FORCEINLINE const FECsWeaponState& GetCurrentState() const { return CurrentState; }

#pragma endregion ICsWeapon

// ICsPointSequenceWeapon
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Weapon|ICsPointSequenceWeapon")
	void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon|ICsPointSequenceWeapon")
	void StopFire();

#pragma endregion ICsPointSequenceWeapon

// ICsWeapon_Event
#pragma region
public:

	FORCEINLINE ICsWeapon_Event::FOnAllocate& GetOnAllocate_Event() { return OnAllocate_Event; }
	FORCEINLINE ICsWeapon_Event::FOnDeallocate_Start& GetOnDeallocate_Start_Event() { return OnDeallocate_Start_Event; }

#pragma endregion ICsWeapon_Event

// ICsPointSequenceWeapon_Event
#pragma region
public:

	FORCEINLINE ICsPointSequenceWeapon_Event::FOnHit& GetOnHit_Event() { return OnHit_Event; }

#pragma endregion ICsPointSequenceWeapon_Event

// Events
#pragma region
protected:

	ICsWeapon_Event::FOnAllocate OnAllocate_Event;

	ICsWeapon_Event::FOnDeallocate_Start OnDeallocate_Start_Event;

	ICsPointSequenceWeapon_Event::FOnHit OnHit_Event;

#pragma endregion Events

protected:

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

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFire_PreStart, ACsPointSequenceWeaponActorPooled* /*Weapon*/, const uint32& /*FireID*/);
	
	FOnFire_PreStart OnFire_PreStart_Event;

protected:

	char Fire_Internal(FCsRoutine* R);

	void Fire_PreShot(const uint32& FireID);

public:

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnFire_PreShot, ACsPointSequenceWeaponActorPooled* /*Weapon*/, const uint32& /*FireID*/, const int32& /*CurrentProjectilePerShotIndex*/);

	FOnFire_PreShot OnFire_PreShot_Event;

protected:

	void Fire_Internal_OnEnd(FCsRoutine* R);

public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFire_End, ACsPointSequenceWeaponActorPooled* /*Weapon*/, FCsRoutine* /*R*/);

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
		friend class ACsPointSequenceWeaponActorPooled;

	protected:

		ACsPointSequenceWeaponActorPooled* Outer;

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

	int32 Sequence_GetCount() const;

	float Sequence_GetInterval() const;

	int32 SequencesPerShot_GetCount() const;

	float SequencesPerShot_GetInterval() const;

public:

	struct CSWP_API FPointImpl
	{
		friend class ACsPointSequenceWeaponActorPooled;

	private:

		ACsPointSequenceWeaponActorPooled* Outer;

	public:

		FVector3f Start;

		bool bDestination;

		FVector3f Destination;

		FPointImpl() :
			Outer(nullptr),
			Start(FVector3f::ZeroVector),
			bDestination(false),
			Destination(FVector3f::ZeroVector)
		{
		}

		FORCEINLINE bool HasValidDestination() const { return bDestination; }

		FORCEINLINE float CalculateDistance() const { return (Destination - Start).Size(); }

		FORCEINLINE FVector3f CalculateDirection() const { return (Destination - Start).GetSafeNormal(); }
		FORCEINLINE FVector3f CalculateInverseDirection() const { return -1.0f * CalculateDirection(); }
	};

	FPointImpl PointImpl;

protected:

	virtual void Sequence_Execute(const int32& CurrentSequencePerShotIndex);

#pragma endregion Point
	
	// Sound
#pragma region
public:

	struct CSWP_API FSoundImpl
	{
		friend class ACsPointSequenceWeaponActorPooled;

	protected:

		ACsPointSequenceWeaponActorPooled* Weapon;

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
		friend class ACsPointSequenceWeaponActorPooled;

	protected:

		ACsPointSequenceWeaponActorPooled* Outer;

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

	#define FXDataType NCsWeapon::NPoint::NSequence::NData::NVisual::NFire::IFire
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
#undef PointSequenceWeaponDataType
#undef SoundPayloadType
#undef FXPayloadType
};