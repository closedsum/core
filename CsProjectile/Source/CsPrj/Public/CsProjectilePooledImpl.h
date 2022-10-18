// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
// Interfaces
#include "Managers/Time/CsUpdate.h"
#include "Managers/Time/CsPause.h"
#include "Managers/Pool/CsPooledObject.h"
#include "CsProjectile.h"
#include "Event/CsProjectile_Event.h"
#include "Collision/CsGetCollisionHitCount.h"
// Types
#include "Types/CsTypes_Projectile.h"
#include "Types/CsTypes_Projectile_Tracking.h"
#include "Types/CsTypes_Damage.h"
#include "Value/Types/CsTypes_DamageValue.h"
#include "Managers/FX/CsTypes_FX.h"
// Coroutine
#include "Coroutine/CsRoutineHandle.h"
// Projectile
#include "Modifier/CsAllocated_ProjectileModifier.h"
// Damage
#include "Modifier/CsAllocated_DamageModifier.h"

#include "CsProjectilePooledImpl.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsProjectilePooledImpl_OnAllocate, ACsProjectilePooledImpl*, Projectile);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsProjectilePooledImpl_OnDeallocate_Start, ACsProjectilePooledImpl*, Projectile);
// FX
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsProjectilePooledImpl_OnOverride_TrailFX, ACsProjectilePooledImpl*, Projectile);

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
										  public ICsPooledObject,
										  public ICsProjectile,
										  public ICsProjectile_Event,
										  public ICsGetCollisionHitCount
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
	virtual void Tick(float DeltaSeconds) override;

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

	virtual FVector EvaluateMovementFunction(const float& Time);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	FECsProjectile Type;

	FORCEINLINE const FECsProjectile& GetType() const { return Type; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	int32 Generation;

	void SetType(const FECsProjectile& InType);

	UPROPERTY(BlueprintReadOnly, Category = "Projectile")
	ECsProjectileState State;

// ICsUpdate
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

// ICsPause
#pragma region
public:

	void Pause(bool bPaused);

#pragma endregion ICsPause

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

	void Deallocate();

#pragma endregion ICsPooledObject

// PooledObject
#pragma region
protected:

	virtual void Deallocate_Internal();

public:

	UFUNCTION(BlueprintCallable)
	int32 GetCache_Index();

	UPROPERTY(BlueprintAssignable)
	FCsProjectilePooledImpl_OnAllocate OnAllocate_ScriptEvent;

	UPROPERTY(BlueprintAssignable)
	FCsProjectilePooledImpl_OnDeallocate_Start OnDeallocate_Start_ScriptEvent;

#pragma endregion PooledObject

// ICsProjectile
#pragma region
public:

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
		FVector Direction;
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

// ICsGetCollisionHitCount
#pragma region
public:

	FORCEINLINE int32 GetCollisionHitCount() const { return HitCount; }

#pragma endregion ICsGetCollisionHitCount

// Movement
#pragma region
protected:

	void StartMovementFromData(const FVector& Direction);

	// Tracking
#pragma region
protected:

	struct FTrackingImpl
	{
		friend class ACsProjectilePooledImpl;

	private:

		ACsProjectilePooledImpl* Outer;

	public:

	#define TrackingDataType NCsProjectile::NData::NTracking::ITracking

		TrackingDataType* TrackingData;

		NCsProjectile::NTracking::EState CurrentState;

		NCsProjectile::NTracking::EObject ObjectType;

		USceneComponent* Component;

		USkeletalMeshComponent* MeshComponent;

		FName Bone;

		FVector Location;

		int32 ID;

		bool bReacquire;

		float ElapsedTime;

	public:

		FTrackingImpl() :
			TrackingData(nullptr),
			CurrentState(NCsProjectile::NTracking::EState::Inactive),
			ObjectType(NCsProjectile::NTracking::EObject::Component),
			Component(nullptr),
			MeshComponent(nullptr),
			Bone(NAME_None),
			Location(0.0f),
			ID(INDEX_NONE),
			bReacquire(false),
			ElapsedTime(0.0f)
		{
		}

		void Init(PayloadType* Payload);

		void Update(const FCsDeltaTime& DeltaTime);

		FVector GetDestination() const;

		FORCEINLINE void Reset()
		{
			TrackingData = nullptr;
			CurrentState = NCsProjectile::NTracking::EState::Inactive;
			ObjectType = NCsProjectile::NTracking::EObject::Component;
			Component = nullptr;
			MeshComponent = nullptr;
			Bone = NAME_None;
			Location = FVector::ZeroVector;
			ID = INDEX_NONE;
			bReacquire = false;
			ElapsedTime  = 0.0f;
		}

	#undef TrackingDataType
	};

	FTrackingImpl TrackingImpl;

public:

	virtual bool TrackingImpl_IsValid() const { return true; }

	virtual bool TrackingImpl_ReacquireDestination() { return false; }

	virtual FVector TrackingImpl_GetDestinationByID() const;

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

public:

	/** Whether to deallocate the projectile on hit (and HitCount <= 0). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	bool bDeallocateOnHit;

protected:

	int32 HitCount;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void OnHit_Internal(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {}

#pragma endregion Collision

// FX
#pragma region
protected:

	FCsFXActorPooled* TrailFXPooled;

	UPROPERTY(BlueprintReadWrite, Category = "Projectile|FX", meta = (AllowPrivateAccess = "true"))
	bool bOverride_TrailFX;

public:

	UPROPERTY(BlueprintAssignable, Category = "Projectile|FX")
	FCsProjectilePooledImpl_OnOverride_TrailFX OnOverride_TrailFX_ScriptEvent;

	UFUNCTION(BlueprintCallable)
	void SetTrailFXPooled(const FString& Context, const FECsFX& FX, const int32& Index);

#pragma endregion FX

// Modifier
#pragma region
protected:

#define AllocateModifierType NCsProjectile::NModifier::FAllocated
	TArray<AllocateModifierType> Modifiers;
#undef AllocateModifierType

#define CollisionDataType NCsProjectile::NData::NCollision::ICollision
	void ApplyHitCountModifiers(const FString& Context, const CollisionDataType* CollisionData);
#undef CollisionDataType

	void StartMovementFromModifiers(const FString& Context, const FVector& Direction);

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