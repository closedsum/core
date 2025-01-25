#pragma once
#include "GameFramework/Actor.h"
// Interfaces
#include "Update/CsUpdate.h"
#include "CsWeapon.h"
#include "Trace/CsTraceWeapon.h"
// Types
#include "Coroutine/CsTypes_Coroutine.h"
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"

#include "CsTraceWeaponActor.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsTraceWeaponActor_OnConsumeAmmo, UObject*, Weapon, const int32&, PreviousAmmo, const int32&, NewAmmo);

#pragma endregion Delegates

class AActor;
struct FCsRoutine;

// NCsWeapon::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)
// NCsWeapon::NTrace::NImpl::FTrace::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NTrace, NImpl, NTrace, FImpl)
// NCsWeapon::NTrace::NImpl::NFX::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NTrace, NImpl, NFX, FImpl)
// NCsWeapon::NTrace::NImpl::NSound::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NTrace, NImpl, NSound, FImpl)

class USceneComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;

UCLASS(BlueprintType, Blueprintable)
class CSWP_API ACsTraceWeaponActor : public AActor,
									 public ICsUpdate,
									 public ICsWeapon,
									 public ICsTraceWeapon
{
	GENERATED_UCLASS_BODY()

#define DataType NCsWeapon::NData::IData
#define TraceImplType NCsWeapon::NTrace::NImpl::NTrace::FImpl
#define FXImplType NCsWeapon::NTrace::NImpl::NFX::FImpl
#define SoundImplType NCsWeapon::NTrace::NImpl::NSound::FImpl

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

	FORCEINLINE const FECsUpdateGroup& GetUpdateGroup() const { return UpdateGroup; }

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

	FORCEINLINE DataType* GetData() const { return Data; }

	FORCEINLINE const FECsWeaponState& GetCurrentState() const { return CurrentState; }

#pragma endregion ICsWeapon

// ICsTraceWeapon
#pragma region
public:

	void StartFire();

	void StopFire();

#pragma endregion ICsTraceWeapon

protected:

	UObject* MyOwner;
	AActor* MyOwnerAsActor;

public:

	FORCEINLINE UObject* GetMyOwner() const { return MyOwner; }
	template<typename T>
	FORCEINLINE T* GetMyOwner() const { return Cast<T>(MyOwner); }

	FORCEINLINE void SetMyOwner(UObject* InOwner) { MyOwner = InOwner; }

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
		friend class ACsTraceWeaponActor;

	protected:

		ACsTraceWeaponActor* Outer;

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

	TraceImplType* TraceImpl;

protected:

	virtual TraceImplType* ConstructTraceImpl();

#pragma endregion Trace

	// Damage
#pragma region
public:

	/**
	*/
	struct CSWP_API FDamageImpl
	{
		friend class ACsTraceWeaponActor;

	protected:

		ACsTraceWeaponActor* Outer;
	};

	FDamageImpl DamageImpl;

#pragma endregion Damage

	// Sound
#pragma region
public:

	SoundImplType* SoundImpl;

protected:

	virtual SoundImplType* ConstructSoundImpl();

#pragma endregion Sound

	// FX
#pragma region
public:

	FXImplType* FXImpl;

protected:

	virtual FXImplType* ConstructFXImpl();

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
#undef TraceImplType
#undef FXImplType
#undef SoundImplType
};