// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "GameFramework/Actor.h"
// Interfaces
#include "Update/CsUpdate.h"
#include "Shutdown/CsShutdown.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/Beam/ICsBeam.h"
// Types
#include "Managers/Time/CsTypes_Update.h"
#include "Types/CsTypes_Beam.h"
#include "Coroutine/CsRoutineHandle.h"
#include "Types/CsTypes_Damage.h"
#include "Value/Types/CsTypes_DamageValue.h"
// Damage
#include "Modifier/CsAllocated_DamageModifier.h"

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
// CacheImplType (NCsBeam::NCache::NImpl::FImpl)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsBeam, NCache, NImpl, FImpl)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// NCsBeam::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsBeam, NPayload, IPayload)

struct FCsRoutine;

// NCsBeam::NData::NCollision::ICollision
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsBeam, NData, NCollision, ICollision)
// NCsBeam::NCollision::NParams::FFrequency
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsBeam, NCollision, NParams, FFrequency)
// NCsBeam::NCollision::NShape::FShape
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsBeam, NCollision, NShape, FShape)

// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)
// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)
// NCsDamage::NValue::NPoint::NImpl::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsDamage, NValue, NPoint, NImpl, FImpl)
// NCsDamage::NValue::NRange::NImpl::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsDamage, NValue, NRange, NImpl, FImpl)

UCLASS(Blueprintable)
class CSBEAM_API ACsBeamActorPooledImpl : public AActor,
										  public ICsUpdate,
										  public ICsShutdown,
										  public ICsPooledObject,
										  public ICsBeam
{
	GENERATED_UCLASS_BODY()

private:

	using DataType = NCsBeam::NData::IData;
	using PooledCacheType = NCsPooledObject::NCache::ICache;
	using CacheImplType = NCsBeam::NCache::NImpl::FImpl;
	using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
	using PayloadType = NCsBeam::NPayload::IPayload;

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

// ICsUpdate
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

// Update
#pragma region
protected:

	FECsUpdateGroup UpdateGroup;

public:

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

// PooledObject
#pragma region
protected:

	PooledCacheType* Cache;

	CacheImplType* CacheImpl;

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

#pragma endregion Beam

// Collision
#pragma region
protected:

	struct FCollisionImpl
	{
		friend class ACsBeamActorPooledImpl;

	private:

		using CollisionDataType = NCsBeam::NData::NCollision::ICollision;
		using CollisionFrequencyParamsType = NCsBeam::NCollision::NParams::FFrequency;
		using CollisionShapeType = NCsBeam::NCollision::NShape::FShape;

	private:
		
		ACsBeamActorPooledImpl* Outer;
		
		CollisionDataType* CollisionData;
	
		CollisionFrequencyParamsType* FrequencyParams;

		CollisionShapeType* Shape;

		int32 CurrentCount;
		int32 CountdownToDeallocate;

		TArray<TWeakObjectPtr<const AActor>> IgnoreActors;

		TSet<TWeakObjectPtr<AActor>> IgnoreActorSet;

		TArray<TWeakObjectPtr<UPrimitiveComponent>> IgnoreComponents;

		TSet<TWeakObjectPtr<UPrimitiveComponent>> IgnoreComponentSet;

	public:

		FCollisionImpl() :
			Outer(nullptr),
			CollisionData(nullptr),
			FrequencyParams(nullptr),
			Shape(nullptr),
			CurrentCount(0),
			CountdownToDeallocate(0),
			IgnoreActors(),
			IgnoreActorSet(),
			IgnoreComponents(),
			IgnoreComponentSet(),
			EmitInternalHandle()
		{
		}

	private:

		void AddIgnoreActor(AActor* Actor);

		const AActor* GetIgnoreActor(const int32& Index);

		void AddIgnoreComponent(UPrimitiveComponent* Component);

		UPrimitiveComponent* GetIgnoreComponent(const int32& Index);

		bool IsIgnored(AActor* Actor) const;
		bool IsIgnored(UPrimitiveComponent* Component) const;

		void ConditionalEmit();
		void Emit();
		char Emit_Internal(FCsRoutine* R);

		FCsRoutineHandle EmitInternalHandle;

		void PerformPass();

		void Shutdown();
	};

	FCollisionImpl CollisionImpl;

public:

	/** Whether to deallocate the beam on hit (and CollisionCount <= 0). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Beam")
	bool bDeallocateOnCollision;

protected:

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* CollidingComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector3d NormalImpulse, const FHitResult& Hit);

#pragma endregion Collision

// Damage
#pragma region
public:

	struct FDamageImpl
	{
		friend class ACsBeamActorPooledImpl;

	private:

		using ValueType = NCsDamage::NValue::IValue;
		using ValuePointImplType = NCsDamage::NValue::NPoint::NImpl::FImpl;
		using ValueRangeImplType = NCsDamage::NValue::NRange::NImpl::FImpl;
		using AllocateModifierType = NCsDamage::NModifier::FAllocated;
		using CsDamageDataType = NCsDamage::NData::IData;

	private:

		ACsBeamActorPooledImpl* Outer;

		FECsDamageValue Type;

		ValuePointImplType* ValuePoint;
		ValueRangeImplType* ValueRange;

		TArray<AllocateModifierType> Modifiers;

	public:

		FDamageImpl();
		virtual ~FDamageImpl();

		void SetValue(CsDamageDataType* InData);

		ValueType* GetValue();

		void ResetValue();
		void Reset();
	};

	FDamageImpl DamageImpl;

#pragma endregion Damage
};