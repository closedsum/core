// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
// Interfaces
#include "Managers/Time/CsUpdate.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/Beam/ICsBeam.h"
// Types
#include "Managers/Time/CsTypes_Update.h"
#include "Types/CsTypes_Beam.h"
#include "Coroutine/CsRoutineHandle.h"
#include "Managers/Damage/CsTypes_Damage.h"
#include "Managers/Damage/Value/CsTypes_DamageValue.h"
// Damage
#include "Managers/Damage/Modifier/CsAllocated_DamageModifier.h"

#include "CsBeamActorPooledImpl.generated.h"

// Delegates
#pragma region

#pragma endregion Delegates

class UStaticMeshComponent;
class UPrimitiveComponent;

// NCsBeam::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsBeam, NData, IData)

// NCsPooledObject::NCache::ICache
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NCache, ICache)
// NCsBeam::NCache::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsBeam, NCache, FImpl)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// NCsBeam::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsBeam, NPayload, IPayload)

struct FCsRoutine;

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
class CSBEAM_API ACsBeamActorPooledImpl : public AActor,
										  public ICsUpdate,
										  public ICsPooledObject,
										  public ICsBeam
{
	GENERATED_UCLASS_BODY()

#define DataType NCsBeam::NData::IData
#define PooledCacheType NCsPooledObject::NCache::ICache
#define PooledPayloadType NCsPooledObject::NPayload::IPayload
#define PayloadType NCsBeam::NPayload::IPayload

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// AActor Interface
#pragma region
public:

	virtual void BeginPlay() override;

	virtual void FellOutOfWorld(const UDamageType& DmgType) override;

	virtual void OutsideWorldBounds() override;

#pragma endregion AActor Interface

public:

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Beam")
	FECsBeam Type;

	void SetType(const FECsBeam& InType);

// Collision
#pragma region
protected:

	UPROPERTY()
	TArray<TWeakObjectPtr<AActor>> IgnoreActors;

	UPROPERTY()
	TSet<TWeakObjectPtr<AActor>> IgnoreActorSet;

	void AddIgnoreActor(AActor* Actor);

	AActor* GetIgnoreActor(const int32& Index);

	UPROPERTY()
	TArray<TWeakObjectPtr<UPrimitiveComponent>> IgnoreComponents;

	UPROPERTY()
	TSet<TWeakObjectPtr<UPrimitiveComponent>> IgnoreComponentSet;

	void AddIgnoreComponent(UPrimitiveComponent* Component);

	UPrimitiveComponent* GetIgnoreComponent(const int32& Index);

	bool IsIgnored(AActor* Actor) const;
	bool IsIgnored(UPrimitiveComponent* Component) const;

public:

	/** Whether to deallocate the beam on hit (and CollisionCount <= 0). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Beam")
	bool bDeallocateOnCollision;

protected:

	int32 CollisionCount;
	int32 CollisionCountdownToDeallocate;

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* CollidingComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

#pragma endregion Collision

// ICsUpdate
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

// Update
#pragma region
protected:

	FECsUpdateGroup UpdateGroup;

#pragma endregion Update

// PooledObject
#pragma region
protected:

	PooledCacheType* Cache;

#define CacheImplType NCsBeam::NCache::FImpl
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

// ICsBeam
#pragma region
public:

	void On();
	void Off();

	FORCEINLINE DataType* GetData() const { return Data; }

	UObject* GetOwner() const;

	UObject* GetInstigator() const;

#pragma endregion ICsBeam

// Beam
#pragma region
protected:

	DataType* Data;

	// On
#pragma region
protected:

	bool bOnOnAllocate;

	void PrepareOn(PayloadType* Payload);
	void OnPrepareOn_SetModifiers(PayloadType* Payload);

#pragma endregion On

	// Off
#pragma region
protected:

	bool bOnOffDeallocate;

#pragma endregion Off

	// Emit
#pragma region
protected:

	void Emit();
	char Emit_Internal(FCsRoutine* R);

	FCsRoutineHandle EmitInternalHandle;

#pragma endregion Emit

#pragma endregion Beam

// Damage
#pragma region
public:

	struct FDamageImpl
	{
		friend class ACsBeamActorPooledImpl;

	private:

		ACsBeamActorPooledImpl* Outer;

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