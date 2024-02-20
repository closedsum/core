// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
// Interfaces
#include "Managers/Time/CsUpdate.h"
#include "Managers/Time/CsPause.h"
#include "Shutdown/CsShutdown.h"
#include "Managers/Pool/CsPooledObject.h"
#include "CsProjectile.h"
	// Event
#include "Event/CsProjectile_Event.h"
	// Movement
#include "Movement/CsProjectile_Movement.h"
	// Collision
#include "Collision/CsProjectile_Collision.h"
#include "Collision/CsGetCollisionHitCount.h"
	// Tracking
#include "Tracking/CsProjectile_Tracking.h"
// Types
#include "Types/CsTypes_Projectile.h"
#include "Types/CsTypes_Projectile_Tracking.h"
#include "Types/CsTypes_Damage.h"
#include "Value/Types/CsTypes_DamageValue.h"
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"
#include "Managers/FX/CsTypes_FX.h"
// Coroutine
#include "Coroutine/CsRoutineHandle.h"
// Projectile
#include "Variables/CsProjectile_Variables.h"
#include "Modifier/CsAllocated_ProjectileModifier.h"
// Damage
#include "Modifier/CsAllocated_DamageModifier.h"

#include "CsProjectilePooledImpl.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsProjectilePooledImpl_OnAllocate, ACsProjectilePooledImpl*, Projectile);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsProjectilePooledImpl_OnDeallocate_Start, ACsProjectilePooledImpl*, Projectile);
	// Movement
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsProjectilePooledImpl_OnOverride_InitialSpeed, ACsProjectilePooledImpl*, Projectile);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsProjectilePooledImpl_OnOverride_MaxSpeed, ACsProjectilePooledImpl*, Projectile);
	// FX
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsProjectilePooledImpl_OnOverride_TrailFX, ACsProjectilePooledImpl*, Projectile);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FCsProjectilePooledImpl_OnOverride_ImpactFX, ACsProjectilePooledImpl*, Projectile, UPrimitiveComponent*, HitComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, FVector3f, NormalImpulse, const FHitResult&, Hit);

#pragma endregion Delegates

struct FCsRoutine;

class USphereComponent;
class UCsProjectileMovementComponent;
class UStaticMeshComponent;
class UPrimitiveComponent;

// NCsPooledObject::NCache::ICache
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NCache, ICache)
// NCsProjectile::NCache::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NCache, FImpl)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// NCsProjectile::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NPayload, IPayload)

class ICsFXActorPooled;
struct FCsFXActorPooled;

// NCsProjectile::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NData, IData)
// NCsProjectile::NData::NCollision::ICollision
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NData, NCollision, ICollision)
// NCsProjectile::NData::NTracking::ITracking
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NData, NTracking, ITracking)

class USceneComponent;
class USkeletalMeshComponent;

// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)
// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)
// NCsDamage::NValue::NPoint::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NValue, NPoint, FImpl)
// NCsDamage::NValue::NRange::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NValue, NRange, FImpl)
// NCsDamage::NRange::IRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NRange, IRange)
// NCsDamage::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, IModifier)

UCLASS(Blueprintable)
class CSPRJ_API ACsProjectilePooledImpl : public AActor,
										  public ICsUpdate,
										  public ICsPause,
										  public ICsShutdown,
										  public ICsPooledObject,
										  public ICsProjectile,
										  // Event
										  public ICsProjectile_Event,
										  // Movement
										  public ICsProjectile_Movement,
										  // Collision
										  public ICsProjectile_Collision,
										  public ICsGetCollisionHitCount,
										  // Tracking
										  public ICsProjectile_Tracking
{
	GENERATED_UCLASS_BODY()

#define DataType NCsProjectile::NData::IData
#define PooledCacheType NCsPooledObject::NCache::ICache
#define PooledPayloadType NCsPooledObject::NPayload::IPayload
#define PayloadType NCsProjectile::NPayload::IPayload

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
	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;

	virtual void FellOutOfWorld(const UDamageType& DmgType) override;

	virtual void OutsideWorldBounds() override;

#pragma endregion AActor Interface

public:

	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
	UCsProjectileMovementComponent* MovementComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UStaticMeshComponent* MeshComponent;

	virtual void OnTick_HandleCVars(const float& DeltaSeconds);
	virtual void OnTick_HandleMovementFunction(const float& DeltaSeconds);

	void DrawPath(const float& DeltaSeconds);
	void DrawPath_Internal(const float& DeltaSeconds, const float& Interval, const uint8& SegmentsPerInterval, const float& Thickness);

	virtual FVector3f EvaluateMovementFunction(const float& Time);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsPrj|Projectile")
	FECsProjectile Type;

	FORCEINLINE const FECsProjectile& GetType() const { return Type; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsPrj|Projectile")
	int32 Generation;

	void SetType(const FECsProjectile& InType);

#define StateType NCsProjectile::EState
	
	StateType State;

	FORCEINLINE const StateType& GetState() const { return State; }
private:
	FORCEINLINE StateType& GetState() { return State; }

#undef StateType

// ICsUpdate
#pragma region
public:

	virtual void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

// ICsPause
#pragma region
public:

	void Pause(bool bPaused);

#pragma endregion ICsPause

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

// PooledObject
#pragma region
protected:

#define CacheImplType NCsProjectile::NCache::FImpl

	PooledCacheType* Cache;

	CacheImplType* CacheImpl;

public:

	CacheImplType* GetCacheImpl() const { return CacheImpl; }

protected:

	virtual void ConstructCache();

#undef CacheImplType

#pragma endregion PooledObject

// ICsPooledObject
#pragma region
public:

	FORCEINLINE PooledCacheType* GetCache() const { return Cache; }

	void Allocate(PooledPayloadType* Payload);

	virtual void Deallocate();

#pragma endregion ICsPooledObject

// PooledObject
#pragma region
protected:

	virtual void Deallocate_Internal();

public:

	UFUNCTION(BlueprintCallable, Category = "CsPrj|Projectile|Pooled Object")
	int32 GetCache_Index();

	UFUNCTION(BlueprintCallable, Category = "CsPrj|Projectile|Pooled Object")
	UObject* GetCache_Instigator();

	UPROPERTY(BlueprintAssignable)
	FCsProjectilePooledImpl_OnAllocate OnAllocate_ScriptEvent;

	UPROPERTY(BlueprintAssignable)
	FCsProjectilePooledImpl_OnDeallocate_Start OnDeallocate_Start_ScriptEvent;

#pragma endregion PooledObject

// ICsProjectile
#pragma region
public:

	FORCEINLINE const FECsProjectile& GetProjectileType() const { return GetType(); }

	void Launch(PayloadType* Payload);

	FORCEINLINE DataType* GetData() const { return Data; }

	UObject* GetOwner() const;

	UObject* GetInstigator() const;

#pragma endregion ICsProjectile

// Projectile
#pragma region
protected:

	DataType* Data;

	virtual void IsValidChecked_Data(const FString& Context){}

public:

	UFUNCTION(BlueprintCallable)
	UObject* GetDataAsObject();

#pragma endregion Projectile

// Launch
#pragma region
protected:

	bool bLaunchOnAllocate;

public:

	virtual void OnLaunch_SetModifiers(const PayloadType* Payload);

private:

	struct FLaunch_Delayed_Payload
	{
		FVector3f Direction;
	};

	void Launch_Delayed(const FLaunch_Delayed_Payload& Payload);
	char Launch_Delayed_Internal(FCsRoutine* R);

	FCsRoutineHandle Launch_Delayed_Handle;

	bool bLaunchComplete;

public:

	FORCEINLINE const bool& IsLaunchComplete() const { return bLaunchComplete; }

#pragma endregion Launch

// ICsProjectile_Event
#pragma region
public:

	FORCEINLINE ICsProjectile_Event::FOnAllocate& GetOnAllocate_Event() { return OnAllocate_Event; }
	FORCEINLINE ICsProjectile_Event::FOnDeallocate_Start& GetOnDeallocate_Start_Event() { return OnDeallocate_Start_Event; }
	FORCEINLINE ICsProjectile_Event::FOnHit& GetOnHit_Event() { return OnHit_Event; }

#pragma endregion ICsProjectile_Event

// Events
#pragma region
private:

	ICsProjectile_Event::FOnAllocate OnAllocate_Event;

	ICsProjectile_Event::FOnDeallocate_Start OnDeallocate_Start_Event;

	ICsProjectile_Event::FOnHit OnHit_Event;

#pragma endregion Events

// ICsProjectile_Movement
#pragma region
public:

	void Movement_SetLocation(const FVector3f& Location);

	FVector3f Movement_GetLocation() const;

	void Movement_SetRotation(const FRotator3f& Rotation);

	void Movement_SetVelocity(const FVector3f& Velocity);

#pragma endregion ICsProjectile_Movement

// ICsProjectile_Collision
#pragma region
public:

#define HitResultType NCsProjectile::NCollision::NHit::FResult
	void Hit(const HitResultType& Result);
#undef HitResultType

#pragma endregion ICsProjectile_Collision

// ICsGetCollisionHitCount
#pragma region
public:

	FORCEINLINE int32 GetCollisionHitCount() const { return HitCount; }

#pragma endregion ICsGetCollisionHitCount

// ICsProjectile_Tracking
#pragma region
public:

	virtual bool Tracking_IsValid() const { return true; }

	virtual bool Tracking_ReacquireDestination() { return false; }

	virtual FVector3f Tracking_GetDestination() const;

#pragma endregion ICsProjectile_Tracking

protected:

#if WITH_EDITOR
	const UObject* GetWorldContext() const;
#else
	FORCEINLINE const UObject* GetWorldContext() const { return this; }
#endif // #if WITH_EDITOR

// Variables
#pragma region
protected:

#define VariablesType NCsProjectile::NVariables::FVariables

	VariablesType* Variables;

public:

	FORCEINLINE const VariablesType* GetVariables() const { return Variables; }
	FORCEINLINE VariablesType* GetVariables() { return Variables; }

#undef VariablesType

protected:

	virtual void AllocateVariables(const PayloadType* Payload);

#pragma endregion Variables

// Movement
#pragma region
public:

	struct FMovementInfo
	{
		friend class ACsProjectilePooledImpl;

	private:

		ACsProjectilePooledImpl* Outer;

	public:

		FMovementInfo() :
			Outer(nullptr)
		{
		}

	#define VariablesProxyType NCsProjectile::NVariables::FVariables::FMovementInfo
		FORCEINLINE const VariablesProxyType& GetProxy() const { return Outer->GetVariables()->MovementInfo; }
		FORCEINLINE VariablesProxyType& GetProxy() { return Outer->GetVariables()->MovementInfo; }
	#undef VariablesProxyType

		FORCEINLINE const float& GetInitialSpeed() const { return GetProxy().GetInitialSpeed(); }
		FORCEINLINE float& GetInitialSpeed() { return GetProxy().GetInitialSpeed(); }
		FORCEINLINE const float& GetMaxSpeed() const { return GetProxy().GetMaxSpeed(); }
		FORCEINLINE float& GetMaxSpeed() { return GetProxy().GetMaxSpeed(); }
		FORCEINLINE const FVector3f& GetDirection() const { return GetProxy().GetDirection(); }
		FORCEINLINE FVector3f& GetDirection() { return GetProxy().GetDirection(); }
		FORCEINLINE const FVector3f& GetVelocity() const { return GetProxy().GetVelocity(); }
		FORCEINLINE FVector3f& GetVelocity() { return GetProxy().GetVelocity(); }
		FORCEINLINE const float& GetSpeed() const { return GetProxy().GetSpeed(); }
		FORCEINLINE float& GetSpeed() { return GetProxy().GetSpeed(); }
		FORCEINLINE const float& GetGravityScale() const { return GetProxy().GetGravityScale(); }
		FORCEINLINE float& GetGravityScale() { return GetProxy().GetGravityScale(); }
	};

	FMovementInfo MovementInfo;

	struct FMovementImpl
	{
		friend class ACsProjectilePooledImpl;

	private:

		ACsProjectilePooledImpl* Outer;

	public:

		enum class EStart : uint8 
		{
			FromData,
			FromModifiers
		};

		FMovementImpl() :
			Outer(nullptr)
		{
		}

		float CalculateInitialSpeed(const EStart& Start) const;
		float CalculateMaxSpeed(const EStart& Start) const;
	};

	FMovementImpl MovementImpl;

protected:

	UPROPERTY(BlueprintReadWrite, Category = "CsPrj|Projectile|Movement", meta = (ScriptName = "m_bOverride_InitialSpeed", AllowPrivateAccess = "true"))
	bool bOverride_InitialSpeed;

public:

	FORCEINLINE bool GetbOverride_InitialSpeed() const { return bOverride_InitialSpeed; }

protected:

	UPROPERTY(BlueprintReadWrite, Category = "CsPrj|Projectile|Movement", meta = (ScriptName = "m_Override_InitialSpeed", AllowPrivateAccess = "true"))
	float Override_InitialSpeed;

public:

	FORCEINLINE const float& GetOverride_InitialSpeed() const { return Override_InitialSpeed; }


	UPROPERTY(BlueprintAssignable, Category = "CsPrj|Projectile|Movement")
	FCsProjectilePooledImpl_OnOverride_InitialSpeed OnOverride_InitialSpeed_ScriptEvent;

protected:

	UPROPERTY(BlueprintReadWrite, Category = "CsPrj|Projectile|Movement", meta = (ScriptName = "m_bOverride_MaxSpeed", AllowPrivateAccess = "true"))
	bool bOverride_MaxSpeed;

public:

	FORCEINLINE bool GetbOverride_MaxSpeed() const { return bOverride_MaxSpeed; }

protected:

	UPROPERTY(BlueprintReadWrite, Category = "CsPrj|Projectile|Movement", meta = (ScriptName = "m_Override_MaxSpeed", AllowPrivateAccess = "true"))
	float Override_MaxSpeed;

public:

	FORCEINLINE const float& GetOverride_MaxSpeed() const { return Override_MaxSpeed; }

	UPROPERTY(BlueprintAssignable, Category = "CsPrj|Projectile|Movement")
	FCsProjectilePooledImpl_OnOverride_MaxSpeed OnOverride_MaxSpeed_ScriptEvent;

protected:

	void StartMovementFromData(const FVector3f& Direction);

	// Tracking
#pragma region
public:

	struct FTrackingInfo
	{
		friend class ACsProjectilePooledImpl;

	private:

		ACsProjectilePooledImpl* Outer;

	public:

		FTrackingInfo() :
			Outer(nullptr)
		{
		}

	#define VariablesProxyType NCsProjectile::NVariables::FVariables::FTrackingInfo
		FORCEINLINE const VariablesProxyType& GetProxy() const { return Outer->GetVariables()->TrackingInfo; }
		FORCEINLINE VariablesProxyType& GetProxy() { return Outer->GetVariables()->TrackingInfo; }
	#undef VariablesProxyType

		FORCEINLINE const float& GetDelay() const { return GetProxy().GetDelay(); }
		FORCEINLINE float& GetDelay() { return GetProxy().GetDelay(); }
		FORCEINLINE const NCsProjectile::NTracking::EState& GetCurrentState() const { return GetProxy().GetState(); }
		FORCEINLINE NCsProjectile::NTracking::EState& GetCurrentState() { return GetProxy().GetState(); }
	#define DestinationType NCsProjectile::NTracking::EDestination
		FORCEINLINE const DestinationType& GetDestinationType() const { return GetProxy().GetDestinationType(); }
		FORCEINLINE DestinationType& GetDestinationType() { return GetProxy().GetDestinationType(); }
	#undef DestinationType 
		FORCEINLINE const uint32& GetDestinationMask() const { return GetProxy().GetDestinationMask(); }
		FORCEINLINE uint32& GetDestinationMask() { return GetProxy().GetDestinationMask(); }
		FORCEINLINE const USceneComponent* GetComponent() const { return GetProxy().GetComponent(); }
		FORCEINLINE USceneComponent*& GetComponent() { return GetProxy().GetComponent(); }
		FORCEINLINE const USkeletalMeshComponent* GetMeshComponent() const { return GetProxy().GetMeshComponent(); }
		FORCEINLINE USkeletalMeshComponent*& GetMeshComponent() { return GetProxy().GetMeshComponent(); }
		FORCEINLINE const FName& GetBone() const { return GetProxy().GetBone(); }
		FORCEINLINE FName& GetBone() { return GetProxy().GetBone(); }
		FORCEINLINE const FVector3f& GetLocation() const { return GetProxy().GetDestination(); }
		FORCEINLINE FVector3f& GetLocation() { return GetProxy().GetDestination(); }
		FORCEINLINE const int32& GetID() const { return GetProxy().GetTargetID(); }
		FORCEINLINE int32& GetID() { return GetProxy().GetTargetID(); }
		FORCEINLINE const float& GetDuration() const { return GetProxy().GetDuration(); }
		FORCEINLINE float& GetDuration() { return GetProxy().GetDuration(); }
		FORCEINLINE const float& GetElapsedTime() const { return GetProxy().GetElapsedTime(); }
		FORCEINLINE float& GetElapsedTime() { return GetProxy().GetElapsedTime(); }
		FORCEINLINE const FVector3f& GetOffset() const { return GetProxy().GetOffset(); }
		FORCEINLINE FVector3f& GetOffset() { return GetProxy().GetOffset(); }
		FORCEINLINE const float& GetMinDotThreshold() const { return GetProxy().GetMinDotThreshold(); }
		FORCEINLINE float& GetMinDotThreshold() { return GetProxy().GetMinDotThreshold(); }
		FORCEINLINE const float& GetMaxDotBeforeUsingPitch() const { return GetProxy().GetMaxDotBeforeUsingPitch(); }
		FORCEINLINE float& GetMaxDotBeforeUsingPitch() { return GetProxy().GetMaxDotBeforeUsingPitch(); }
		FORCEINLINE const float& GetRotationRate() const { return GetProxy().GetRotationRate(); }
		FORCEINLINE float& GetRotationRate() { return GetProxy().GetRotationRate(); }

		FORCEINLINE void DestinationMask_SetReacquire() { GetProxy().DestinationMask_SetReacquire(); }
		FORCEINLINE void DestinationMask_MarkReacquire() { GetProxy().DestinationMask_MarkReacquire(); }
		FORCEINLINE void DestinationMask_ClearReacquire() { GetProxy().DestinationMask_ClearReacquire(); }
		FORCEINLINE bool DestinationMask_HasReacquire() { return GetProxy().DestinationMask_HasReacquire(); }
	};

	FTrackingInfo TrackingInfo;

	struct FTrackingImpl
	{
		friend class ACsProjectilePooledImpl;

	private:

		ACsProjectilePooledImpl* Outer;

	public:

	#define TrackingDataType NCsProjectile::NData::NTracking::ITracking

		TrackingDataType* TrackingData;

	public:

		FTrackingImpl() :
			TrackingData(nullptr)
		{
		}

	public:

		void Init(PayloadType* Payload);

		FORCEINLINE void Reset()
		{
			TrackingData = nullptr;
		}

	#undef TrackingDataType
	};

	FTrackingImpl TrackingImpl;

#pragma endregion Tracking

#pragma endregion Movement

// Collision
#pragma region
protected:

	UPROPERTY()
	TArray<TWeakObjectPtr<AActor>> IgnoreActors;

	void AddIgnoreActor(AActor* Actor);

	AActor* GetIgnoreActor(const int32& Index);

	UPROPERTY()
	TArray<TWeakObjectPtr<UPrimitiveComponent>> IgnoreComponents;

	void AddIgnoreComponent(UPrimitiveComponent* Component);

	UPrimitiveComponent* GetIgnoreComponent(const int32& Index);

	bool IsIgnored(AActor* Actor) const;
	bool IsIgnored(UPrimitiveComponent* Component) const;

	TArray<TWeakObjectPtr<AActor>> IgnoredHitActors;

	virtual void AddIgnoredHitActor(AActor* Actor);

	bool IsIgnoredOnHit(AActor* Actor) const;

	TArray<TWeakObjectPtr<UPrimitiveComponent>> IgnoredHitComponents;

	virtual void AddIgnoredHitComponent(UPrimitiveComponent* Component);

	bool IsIgnoredOnHit(UPrimitiveComponent* Component) const;

	virtual void ClearHitObjects();

	TMap<int32, TSet<int32>> IgnoreIdByTypeMap;

	FORCEINLINE bool IsIgnored(const int32& InType, const int32& InID) const
	{
		if (InType == INDEX_NONE)
			return false;

		if (const TSet<int32>* IdsPtr = IgnoreIdByTypeMap.Find(InType))
		{
			return IdsPtr->Contains(InID);
		}
		return false;
	}

	FORCEINLINE void AddIgnored(const int32& InType, const int32& InID)
	{
		check(InType != INDEX_NONE);
		check(InID != INDEX_NONE);

		TSet<int32>& IDs = IgnoreIdByTypeMap.FindOrAdd(InType);
		IDs.Add(InID);
	}

	void ClearIgnored();

public:

	/** Whether to deallocate the projectile on hit (and HitCount <= 0). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	bool bDeallocateOnHit;

protected:

	int32 HitCount;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector3d NormalImpulse, const FHitResult& Hit);

	virtual void OnHit_Internal(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector3d NormalImpulse, const FHitResult& Hit) {}

	void OnHit_TryImpactVisual(const FString& Context, UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector3d NormalImpulse, const FHitResult& Hit);

#pragma endregion Collision

// FX
#pragma region
protected:

	FCsFXActorPooled* TrailFXPooled;

	UPROPERTY(BlueprintReadWrite, Category = "CsPrj|Projectile|FX", meta = (AllowPrivateAccess = "true"))
	bool bOverride_TrailFX;

public:

	UPROPERTY(BlueprintAssignable, Category = "CsPrj|Projectile|FX")
	FCsProjectilePooledImpl_OnOverride_TrailFX OnOverride_TrailFX_ScriptEvent;

	UFUNCTION(BlueprintCallable)
	void SetTrailFXPooled(const FString& Context, const FECsFX& FX, const int32& Index);

protected:

	UPROPERTY(BlueprintReadWrite, Category = "CsPrj|Projectile|FX", meta = (AllowPrivateAccess = "true"))
	bool bOverride_ImpactFX;

public:

	UPROPERTY(BlueprintAssignable, Category = "CsPrj|Projectile|FX")
	FCsProjectilePooledImpl_OnOverride_ImpactFX OnOverride_ImpactFX_ScriptEvent;

#pragma endregion FX

// Modifier
#pragma region
protected:

#define AllocateModifierType NCsProjectile::NModifier::FAllocated

	TArray<AllocateModifierType> Modifiers;

public:

	FORCEINLINE const TArray<AllocateModifierType>& GetModifiers() const { return Modifiers; }

#undef AllocateModifierType

protected:

#define CollisionDataType NCsProjectile::NData::NCollision::ICollision
	void ApplyHitCountModifiers(const FString& Context, const CollisionDataType* CollisionData);
#undef CollisionDataType

	void StartMovementFromModifiers(const FString& Context, const FVector3f& Direction);

#pragma endregion Modifier

// Damage
#pragma region
public:

	struct FDamageImpl
	{
		friend class ACsProjectilePooledImpl;

	private:

		ACsProjectilePooledImpl* Outer;

		FECsDamageValue Type;

	#define PointType NCsDamage::NValue::NPoint::FImpl
	#define RangeType NCsDamage::NValue::NRange::FImpl
	#define AllocatedModifierType NCsDamage::NModifier::FAllocated

		PointType* ValuePoint;
		RangeType* ValueRange;

		TArray<FECsDamageData> DataTypes;

		TArray<AllocatedModifierType> Modifiers;
		
	#undef PointType
	#undef RangeType
	#undef AllocatedModifierType

	public:

		FDamageImpl();
		virtual ~FDamageImpl();

	#define DamageDataType NCsDamage::NData::IData
		void SetValue(DamageDataType* InData);
	#undef DamageDataType

	#define ValueType NCsDamage::NValue::IValue
		ValueType* GetValue();
	#undef ValueType

		void ResetValue();
		void Reset();
	};

	FDamageImpl DamageImpl;

private:

#define RangeType NCsDamage::NRange::IRange
	const RangeType* GetDamageRangeChecked(const FString& Context);
#undef RangeType

	float GetMaxDamageRangeChecked(const FString& Context);

#pragma endregion Damage

#undef DataType
#undef PooledCacheType
#undef PooledPayloadType
#undef PayloadType
};