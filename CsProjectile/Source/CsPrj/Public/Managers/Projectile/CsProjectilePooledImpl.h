// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
// Interfaces
#include "Managers/Time/CsUpdate.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/Projectile/CsProjectile.h"
// Types
#include "Types/CsTypes_Projectile.h"
#include "Managers/Damage/Value/CsTypes_DamageValue.h"

#include "CsProjectilePooledImpl.generated.h"

// Delegates
#pragma region

#pragma endregion Delegates

class USphereComponent;
class UCsProjectileMovementComponent;
class UStaticMeshComponent;

// NCsProjectile::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NData, IData)

// NCsPooledObject::NCache::ICache
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NCache, ICache)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// NCsProjectile::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NPayload, IPayload)
// NCsProjectile::NData::NDamage::IDamage
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NData, NDamage, IDamage)

class ICsFXActorPooled;
struct FCsFXActorPooled;

// NCsDamage::NEvent::IEvent
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NEvent, IEvent)
// NCsDamage::NEvent::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NEvent, FResource)
// NCsDamage::NModifier::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, FResource)
// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

UCLASS(Blueprintable)
class CSPRJ_API ACsProjectilePooledImpl : public AActor,
										  public ICsUpdate,
										  public ICsPooledObject,
										  public ICsProjectile
{
	GENERATED_UCLASS_BODY()

#define DataType NCsProjectile::NData::IData

#define DamageEventType NCsDamage::NEvent::IEvent
#define DamageEventResourceType NCsDamage::NEvent::FResource
#define DamageModifierResourceType NCsDamage::NModifier::FResource
#define DamageDataType NCsDamage::NData::IData

#define ProjectileDamageDataType NCsProjectile::NData::NDamage::IDamage

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

	void SetType(const FECsProjectile& InType);

	UPROPERTY(BlueprintReadOnly, Category = "Projectile")
	ECsProjectileState State;

// Collision
#pragma region
protected:

	UPROPERTY()
	TArray<TWeakObjectPtr<AActor>> IgnoreActors;

	void AddIgnoreActor(AActor* InActor);

	AActor* GetIgnoreActor(const int32 &Index);

public:

	/** Whether to deallocate the projectile on hit. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	bool bDeallocateOnHit;

protected:

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void OnHit_Internal(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

#pragma endregion Collision

// ICsUpdate
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

protected:

	PooledCacheType* Cache;

	virtual void ConstructCache();

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

	void Deallocate_Internal();

#pragma endregion PooledObject

protected:

	DataType* Data;

// ICsProjectile
#pragma region
public:

	FORCEINLINE DataType* GetData() const { return Data; }

	UObject* GetOwner() const;

	UObject* GetInstigator() const;

#pragma endregion ICsProjectile

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	bool bLaunchOnAllocate;

	void Launch(PooledPayloadType* Payload);

	virtual void OnLaunch_SetModifiers(PayloadType* Payload);

// FX
#pragma region
public:

	FCsFXActorPooled* TrailFXPooled;

#pragma endregion FX

// Damage
#pragma region
public:

	struct FDamageImpl
	{
		friend class ACsProjectilePooledImpl;

	private:

		ACsProjectilePooledImpl* Outer;


		TArray<DamageModifierResourceType*> Modifiers;
		
	public:

		/**
		* Event to broadcast a damage event of type: (DamageEventType) NCsDamage::NEvent::IEvent.
		*
		* @param Event	DamageEvent.
		*/
		DECLARE_MULTICAST_DELEGATE_OneParam(FOnBroadcast, const DamageEventType* /*Event*/);

		/** */
		FOnBroadcast OnBroadcast_Event;

		/**
		* Event to broadcast a damage event container of type: (DamageEventResourceType) NCsDamage::NDamage::FResource.
		*
		* @param Event	DamageEvent Container.
		*/
		DECLARE_MULTICAST_DELEGATE_OneParam(FOnBroadcastContainer, const DamageEventResourceType* /*Event*/);

		/** */
		FOnBroadcastContainer OnBroadcastContainer_Event;

		FDamageImpl() :
			Outer(nullptr),
			Modifiers(),
			OnBroadcast_Event(),
			OnBroadcastContainer_Event()
		{
		}

		virtual ~FDamageImpl(){}

	protected:

		/**
		* Get an allocated DamageEvent container from Manager_Event and set the appropriate members for 
		* broadcasting the event.
		* The DamageEvent will get deallocated / reset after the scope of the broadcast event 
		* completes.
		*
		* @param HitResult	The HitResult from a OnComponentHit event
		* return			DamageEvent
		*/
		virtual const DamageEventResourceType* OnHit_CreateEvent(const FHitResult& HitResult);

		virtual const DamageEventResourceType* OnHit_CreateEvent(const FHitResult& HitResult, DamageDataType* DamageData);
	};

	FDamageImpl DamageImpl;

#pragma endregion Damage

#undef DataType

#undef DamageEventType
#undef DamageEventResourceType
#undef DamageModifierResourceType
#undef DamageDataType

#undef ProjectileDamageDataType

#undef PooledCacheType

#undef PooledPayloadType

#undef PayloadType
};