#pragma once
#include "GameFramework/Actor.h"
// Interfaces
#include "Update/CsUpdate.h"
#include "Shutdown/CsShutdown.h"
#include "Managers/Pool/CsPooledObject.h"
#include "CsWeapon.h"
#include "Projectile/CsProjectileWeapon.h"
// Types
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

// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// NCsPooledObject::NCache::ICache
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NCache, ICache)

class AActor;
struct FCsRoutine;

// NCsWeapon::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)
// NCsWeapon::NCsProjectile::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsWeapon, NProjectile, NData, IData)

class USkeletalMeshComponent;
class UStaticMeshComponent;
class UPrimitiveComponent;

// NCsProjectile::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NPayload, IPayload)
// NCsSound::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSound, NPayload, IPayload)
// NCsFX::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NPayload, IPayload)

// NCsWeapon::NProjectile::NData::NVisual::NFire::IFire
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NProjectile, NData, NVisual, NFire, IFire)

// NCsWEapon::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NModifier, IModifier)

// NCsProjectile::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NModifier, IModifier)

class USceneComponent;

// NCsWeapon::NProjectile::NParams::NLaunch::ILaunch
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NProjectile, NParams, NLaunch, ILaunch)

UCLASS(BlueprintType)
class CSWP_API ACsProjectileWeaponActorPooled : public AActor,
											    public ICsUpdate,
												public ICsShutdown,
											    public ICsPooledObject,
											    public ICsWeapon,
											    public ICsProjectileWeapon
{
	GENERATED_UCLASS_BODY()

#define PooledCacheType NCsPooledObject::NCache::ICache
#define PooledPayloadType NCsPooledObject::NPayload::IPayload
#define DataType NCsWeapon::NData::IData
#define PrjWeaponDataType NCsWeapon::NProjectile::NData::IData
#define ProjectilePayloadType NCsProjectile::NPayload::IPayload
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

	PrjWeaponDataType* PrjWeaponData;

// ICsWeapon
#pragma region
public:

	FORCEINLINE DataType* GetData() const { return Data; }

	FORCEINLINE PrjWeaponDataType* GetPrjWeaponData() const { return PrjWeaponData; }

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

public:

	/**
	*/
	struct CSWP_API FTimeBetweenShotsImpl
	{
		friend class ACsProjectileWeaponActorPooled;

	protected:

		ACsProjectileWeaponActorPooled* Outer;

	public:

		/** This is the value BEFORE any modifications. */
		float Base;

		/** This is the value AFTER any modifications. */
		float Value;

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

		FORCEINLINE const float& GetValue() const { return Value; }

		FORCEINLINE void ResetValueToBase() { Value = Base; }

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

	// Projectile
#pragma region
protected:

	int32 ProjectilesPerShot_GetCount() const;

	float ProjectilesPerShot_GetInterval() const;

public:

	/**
	*/
	struct CSWP_API FProjectileImpl
	{
		friend class ACsProjectileWeaponActorPooled;

	protected:

		ACsProjectileWeaponActorPooled* Outer;

	// Launch
	protected:

		USceneComponent* LaunchComponentLocation;

		USceneComponent* LaunchComponentDirection;

		FCsScopedTimerHandle LaunchScopedHandle;

	public:

		FVector3f CustomLaunchLocation;

		FVector3f CustomLaunchDirection;

	// Target
	public:

		bool bTarget;

		USceneComponent* TargetComponent;

		FVector3f TargetLocation;

		FName TargetBone;

		int32 TargetID;

	public:

		FProjectileImpl() :
			Outer(nullptr),
			// Launch
			LaunchComponentLocation(nullptr),
			LaunchComponentDirection(nullptr),
			LaunchScopedHandle(),
			CustomLaunchLocation(FVector3f::ZeroVector),
			CustomLaunchDirection(FVector3f::ZeroVector),
			// Target
			bTarget(false),
			TargetComponent(nullptr),
			TargetLocation(0.0f),
			TargetBone(NAME_None),
			TargetID(INDEX_NONE)
		{
		}
		virtual ~FProjectileImpl(){}

	public:

		FORCEINLINE void SetLaunchComponentLocation(USceneComponent* Component) { LaunchComponentLocation = Component; }
		FORCEINLINE void SetLaunchComponentDirection(USceneComponent* Component) { LaunchComponentDirection = Component; }

	public:

		struct FLaunchPayload
		{
		public:

			struct FShot
			{
			public:

				bool bCachedLaunchLocation;
				FVector3f CachedLaunchLocation;

				bool bCachedLaunchDirection;
				FVector3f CachedLaunchDirection;

				FShot() :
					bCachedLaunchLocation(false),
					CachedLaunchLocation(0.0f),
					bCachedLaunchDirection(false),
					CachedLaunchDirection(0.0f)
				{
				}

				FORCEINLINE bool UseCachedLaunchLocation() const { return bCachedLaunchLocation; }

				FORCEINLINE void SetCachedLaunchLocation(const FVector3f& Value)
				{
					CachedLaunchLocation = Value;
					bCachedLaunchLocation = true;
				}

				FORCEINLINE bool UseCachedLaunchDirection() const { return bCachedLaunchDirection; }

				FORCEINLINE void SetCachedLaunchDirection(const FVector3f& Value)
				{
					CachedLaunchDirection = Value;
					bCachedLaunchDirection = true;
				}
			};

			FShot Shot;

			bool bSpread;

			struct FSpread
			{
			public:
	
				bool bOffset;
				FVector3f Offset;

				int32 Axis;

				bool bYaw;
				float Yaw;

				bool bPitch;
				float Pitch;

				FSpread() :
					bOffset(false),
					Offset(0.0f),
					Axis(0),
					bYaw(false),
					Yaw(0.0f),
					bPitch(false),
					Pitch(0.0f)
				{
				}

				FORCEINLINE bool HasOffset() const { return bOffset; }
				
				FORCEINLINE void SetOffset(const FVector3f& Value)
				{
					if (Value != FVector3f::ZeroVector)
					{
						Offset = Value;
						bOffset = true;
					}
				}

				FORCEINLINE bool HasYaw() const { return bYaw; }

				FORCEINLINE void SetYaw(const float& Value)
				{
					if (Value != 0.0f)
					{
						Yaw = Value;
						bYaw = true;
					}
				}

				FORCEINLINE bool HasPitch() const { return bPitch; }

				FORCEINLINE void SetPitch(const float& Value)
				{
					if (Value != 0.0f)
					{
						Pitch = Value;
						bPitch = true;
					}
				}
			};

			FSpread Spread;

			FLaunchPayload() :
				Shot(),
				bSpread(false),
				Spread()
			{
			}
		};

	#define LaunchPayloadType ACsProjectileWeaponActorPooled::FProjectileImpl::FLaunchPayload

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
		virtual bool SetPayload(const FString& Context, ProjectilePayloadType* Payload, const LaunchPayloadType& LaunchPayload);

	public:

		virtual FVector3f GetLaunchLocation(const LaunchPayloadType& LaunchPayload);
		FORCEINLINE FVector3f GetLaunchLocation() { return GetLaunchLocation(LaunchPayloadType()); }

	protected:

		FVector3f GetLaunchSpreadLocation(const FVector3f& InLocation, const LaunchPayloadType& LaunchPayload);

	public:

		virtual FVector3f GetLaunchDirection(const LaunchPayloadType& LaunchPayload);
		FORCEINLINE FVector3f GetLaunchDirection() { return GetLaunchDirection(LaunchPayloadType()); }

	protected:

		FVector3f GetLaunchSpreadDirection(const FVector3f& InDirection, const LaunchPayloadType& LaunchPayload);

	#define LaunchParamsType NCsWeapon::NProjectile::NParams::NLaunch::ILaunch
		void Log_GetLaunchDirection(const LaunchParamsType* LaunchParams, const FVector3f& Direction);
	#undef LaunchParamsType

		void Launch(const LaunchPayloadType& LaunchPayload);

		FORCEINLINE void Reset()
		{
			LaunchComponentLocation = nullptr;
			LaunchComponentDirection = nullptr;
			CustomLaunchLocation = FVector3f::ZeroVector;
			CustomLaunchDirection = FVector3f::ZeroVector;

			ResetTarget();
		}

		FORCEINLINE void ResetTarget()
		{
			bTarget = false;
			TargetComponent = nullptr;
			TargetLocation = FVector3f::ZeroVector;
			TargetBone = NAME_None;
			TargetID = INDEX_NONE;
		}

	#undef LaunchPayloadType
	};

	FProjectileImpl* ProjectileImpl;

protected:

	virtual FProjectileImpl* ConstructProjectileImpl();

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

#define PrjModifierType NCsProjectile::NModifier::IModifier
	virtual void GetProjectileModifiers(TArray<PrjModifierType*>& OutModifiers) const {}
#undef PrjModifierType

public:

#define LaunchPayloadType ACsProjectileWeaponActorPooled::FProjectileImpl::FLaunchPayload
	virtual bool Projectile_SetPayload(const FString& Context, ProjectilePayloadType* Payload, const LaunchPayloadType& LaunchPayload) { return true; }
#undef LaunchPayloadType

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

#define LaunchPayloadType ACsProjectileWeaponActorPooled::FProjectileImpl::FLaunchPayload

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
		void SetPayload(const int32 CurrentProjectilePerShotIndex, FXPayloadType* Payload, const FCsFX& FX, const LaunchPayloadType& LaunchPayload);

#undef LaunchPayloadType

#define FXDataType NCsWeapon::NProjectile::NData::NVisual::NFire::IFire
		/**
		*
		*
		* @param Payload
		* @param FXData
		*/
		void SetPayload(const int32 CurrentProjectilePerShotIndex, FXPayloadType* Payload, FXDataType* FXData);

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

#undef PooledCacheType
#undef PooledPayloadType
#undef DataType
#undef PrjWeaponDataType
#undef ProjectilePayloadType
#undef SoundPayloadType
#undef FXPayloadType
};