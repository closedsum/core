#pragma once
#include "Components/ActorComponent.h"
// Interfaces
#include "Managers/Time/CsUpdate.h"
#include "CsWeapon.h"
#include "Beam/CsBeamWeapon.h"
// Types
#include "Coroutine/CsTypes_Coroutine.h"
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"
#include "Types/CsTypes_Beam.h"

#include "CsBeamWeaponComponent.generated.h"

// Delegates
#pragma region

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsBeamWeaponComponent_OnConsumeCharge, UObject*, Weapon, const int32&, PreviousCharge, const int32&, NewCharge);

#pragma endregion Delegates

class AActor;
struct FCsRoutine;

// NCsWeapon::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)
// NCsWeapon::NBeam::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsWeapon, NBeam, NData, IData)
// NCsWeapon::NBeam::NImpl::NBeam::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NBeam, NImpl, NBeam, FImpl)
// NCsWeapon::NBeam::NImpl::NFX::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NBeam, NImpl, NFX, FImpl)
// NCsWeapon::NBeam::NImpl::NSound::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NBeam, NImpl, NSound, FImpl)

class USceneComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;

UCLASS()
class CSWP_API UCsBeamWeaponComponent : public UActorComponent,
										 public ICsUpdate,
										 public ICsWeapon,
										 public ICsBeamWeapon
{
	GENERATED_UCLASS_BODY()

#define DataType NCsWeapon::NData::IData
#define BeamImplType NCsWeapon::NBeam::NImpl::NBeam::FImpl
#define FXImplType NCsWeapon::NBeam::NImpl::NFX::FImpl
#define SoundImplType NCsWeapon::NBeam::NImpl::NSound::FImpl

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

// Update
#pragma region
protected:

	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Update", meta = (AllowPrivateAccess))
	FECsUpdateGroup UpdateGroup;

public:

	void SetUpdateGroup(const FECsUpdateGroup& Group);

	FORCEINLINE const FECsUpdateGroup& GetUpdateGroup() const 
	{
		return UpdateGroup;
	}

#pragma endregion Update

// Weapon
#pragma region
protected:

	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Type", meta = (AllowPrivateAccess))
	FECsWeapon WeaponType;

public:

	void SetWeaponType(const FECsWeapon& Type);

protected:

	DataType* Data;

#define BeamDataType NCsWeapon::NBeam::NData::IData

	BeamDataType* BeamData;

public:

	FORCEINLINE const BeamDataType* GetBeamData() const { return BeamData; }

#undef BeamDataType

#pragma endregion Weapon

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

// Beam
#pragma region
protected:

	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Beam", meta = (AllowPrivateAccess))
	FECsBeam BeamType;

public:

	UFUNCTION(BlueprintCallable, Category = "Weapon|Beam")
	void SetBeamType(const FECsBeam& Type);

	FORCEINLINE const FECsBeam& GetBeamType() const { return BeamType; }

#pragma endregion Beam

// ICsBeamWeapon
#pragma region
public:

	void StartFire();

	void StopFire();

#pragma endregion ICsBeamWeapon

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

// Charge
#pragma region
protected:

	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Charge", meta = (AllowPrivateAccess))
	int32 CurrentCharge;

	virtual void ConsumeCharge();

public:

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnConsumeCharge, ICsWeapon* /*Weapon*/, const int32& /*PreviousCharge*/, const int32& /*NewCharge*/);

	FOnConsumeCharge OnConsumeCharge_Event;

#pragma endregion Charge

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
		friend class UCsBeamWeaponComponent;

	protected:

		UCsBeamWeaponComponent* Outer;

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

	// Beam
#pragma region
public:

	BeamImplType* BeamImpl;

protected:

	virtual BeamImplType* ConstructBeamImpl();

#pragma endregion Beam
	
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

	FORCEINLINE UStaticMeshComponent* GetStaticMeshComponent() const { return StaticMeshComponent; }

	FORCEINLINE UStaticMeshComponent* GetStaticMeshComponentChecked(const FString& Context) const
	{
		checkf(StaticMeshComponent, TEXT("%s: StaticMeshComponent is NULL."), *Context);

		return StaticMeshComponent;
	}

protected:

	USkeletalMeshComponent* SkeletalMeshComponent;

public:

	void ConstructSkeletalMeshComponent();

	FORCEINLINE USkeletalMeshComponent* GetSkeletalMeshComponent() const { return SkeletalMeshComponent; }

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
#undef BeamImplType
#undef FXImplType
#undef SoundImplType
};