// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
// Interfaces
#include "Managers/Time/CsUpdate.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/Projectile/CsProjectile.h"
// Types
#include "Managers/Projectile/CsTypes_Projectile.h"
#include "Managers/Damage/Value/CsTypes_DamageValue.h"

#include "CsProjectilePooledImpl.generated.h"

// Delegates
#pragma region

#pragma endregion Delegates

class USphereComponent;
class UCsProjectileMovementComponent;
class UStaticMeshComponent;
struct ICsPooledObjectCache;
struct ICsPayload_PooledObject;
struct ICsPayload_Projectile;
class ICsData_Projectile;
class ICsFXActorPooled;
struct FCsFXActorPooled;
struct ICsDamageEvent;
struct FCsResource_DamageEvent;
struct FCsResource_DamageModifier;
class ICsData_Damage;

UCLASS(Blueprintable)
class CSPRJ_API ACsProjectilePooledImpl : public AActor,
										  public ICsUpdate,
										  public ICsPooledObject,
										  public ICsProjectile
{
	GENERATED_UCLASS_BODY()

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

	ICsPooledObjectCache* Cache;

	virtual void ConstructCache();

// ICsPooledObject
#pragma region
public:

	ICsPooledObjectCache* GetCache() const;

	void Allocate(ICsPayload_PooledObject* Payload);

	void Deallocate();

#pragma endregion ICsPooledObject

protected:

	void Deallocate_Internal();

protected:

	ICsData_Projectile* Data;

// ICsProjectile
#pragma region
public:

	ICsData_Projectile* GetData() const;

	UObject* GetOwner() const;

	UObject* GetInstigator() const;

#pragma endregion ICsProjectile

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	bool bLaunchOnAllocate;

	void Launch(ICsPayload_PooledObject* Payload);

	virtual void OnLaunch_SetModifiers(ICsPayload_Projectile* Payload);

// FX
#pragma region
public:

	FCsFXActorPooled* TrailFXPooled;

#pragma endregion FX

// Damage
#pragma region
protected:

	TArray<FCsResource_DamageModifier*> DamageModifiers;

public:

	/**
	* Event to broadcast a damage event of type: ICsDamageEvent.
	*
	* @param Event	DamageEvent.
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnBroadcastDamage, const ICsDamageEvent* /*Event*/);

	/** */
	FOnBroadcastDamage OnBroadcastDamage_Event;

	/**
	* Event to broadcast a damage event container of type: FCsResource_DamageEvent.
	*
	* @param Event	DamageEvent Container.
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnBroadcastDamageContainer, const FCsResource_DamageEvent* /*Event*/);

	/** */
	FOnBroadcastDamageContainer OnBroadcastDamageContainer_Event;

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
	virtual const FCsResource_DamageEvent* OnHit_CreateDamageEvent(const FHitResult& HitResult);

	virtual const FCsResource_DamageEvent* OnHit_CreateDamageEvent(const FHitResult& HitResult, ICsData_Damage* DamageData);

#pragma endregion Damage
};