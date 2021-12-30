// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
// Interfaces
#include "Managers/Time/CsUpdate.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/Projectile/CsProjectile.h"
#include "Collision/CsGetCollisionHitCount.h"
// Types
#include "Types/CsTypes_Projectile.h"
#include "Managers/Damage/CsTypes_Damage.h"
#include "Managers/Damage/Value/CsTypes_DamageValue.h"
// Projectile
#include "Modifier/CsAllocated_ProjectileModifier.h"
// Damage
#include "Managers/Damage/Modifier/CsAllocated_DamageModifier.h"

#include "CsProjectilePooledImpl.generated.h"

// Delegates
#pragma region

#pragma endregion Delegates

class USphereComponent;
class UCsProjectileMovementComponent;
class UStaticMeshComponent;
class UPrimitiveComponent;

// NCsProjectile::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NData, IData)

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

// NCsDamage::NModifier::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, FResource)
// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)
// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)
// NCsDamage::NValue::NPoint::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NValue, NPoint, FImpl)
// NCsDamage::NValue::NRange::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NValue, NRange, FImpl)

UCLASS(Blueprintable)
class CSPRJ_API ACsProjectilePooledImpl : public AActor,
										  public ICsUpdate,
										  public ICsPooledObject,
										  public ICsProjectile,
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

	void SetType(const FECsProjectile& InType);

	UPROPERTY(BlueprintReadOnly, Category = "Projectile")
	ECsProjectileState State;

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

public:

	/** Whether to deallocate the projectile on hit (and HitCount <= 0). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	bool bDeallocateOnHit;

protected:

	int32 HitCount;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void OnHit_Internal(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

#pragma endregion Collision

// ICsUpdate
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

// PooledObject
#pragma region
protected:

	PooledCacheType* Cache;

#define CacheImplType NCsProjectile::NCache::FImpl
	CacheImplType* CacheImpl;
#undef CacheImplType

	virtual void ConstructCache();

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

	void Deallocate_Internal();

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

#pragma endregion Projectile

// Launch
#pragma region
protected:

	bool bLaunchOnAllocate;

public:

	virtual void OnLaunch_SetModifiers(PayloadType* Payload);

#pragma endregion Launch

// ICsGetCollisionHitCount
#pragma region
public:

	FORCEINLINE int32 GetCollisionHitCount() const { return HitCount; }

#pragma endregion ICsGetCollisionHitCount

// FX
#pragma region
public:

	FCsFXActorPooled* TrailFXPooled;

#pragma endregion FX

// Modifier
#pragma region
protected:

#define AllocateModifierType NCsProjectile::NModifier::FAllocated
	TArray<AllocateModifierType> Modifiers;
#undef AllocateModifierType

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
	#define AllocateModifierType NCsDamage::NModifier::FAllocated

		PointType* ValuePoint;
		RangeType* ValueRange;

		TArray<AllocateModifierType> Modifiers;
		
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

#pragma endregion Damage

#undef DataType
#undef PooledCacheType
#undef PooledPayloadType
#undef PayloadType
};