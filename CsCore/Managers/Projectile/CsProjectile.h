// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/CsPooledActor.h"
#include "Types/CsTypes_Pool.h"
#include "Types/CsTypes_Projectile.h"
#include "Data/CsData_Projectile.h"
#include "CsProjectile.generated.h"

// Allocate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsProjectile_Override_Allocate_Internal, const int32&, PoolIndex);

USTRUCT(BlueprintType)
struct FCsProjectileCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	TWeakObjectPtr<class ACsProjectile> Projectile;
	TWeakObjectPtr<class ACsData_Projectile> Data;

	TCsProjectileType Type_Script;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TEnumAsByte<ECsProjectileRelevance::Type> Relevance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TEnumAsByte<ECsProjectileMovement::Type> Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FVector Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FVector Direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FRotator Rotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FTransform Transform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	float ChargePercent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	float DrawDistanceSq;

	FCsProjectileCache()
	{
		Reset();
	}

	~FCsProjectileCache(){}

	void Set(const uint8 &InIndex, ACsProjectile* InProjectile)
	{
		SetIndex(InIndex);
		Projectile = InProjectile;
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, FCsProjectilePayload* Payload, float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InInstigator, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)())
	{
		SetActiveIndex(InActiveIndex);
		Relevance = Payload->Relevance;

		IsAllocated = true;

		Instigator = InInstigator;
		Owner	   = InOwner;
		Data	   = Payload->Data;

		Type_Script = Data->GetBaseProjectileType();
		Type		= (uint8)Type_Script;

		Parent	    = InParent;

		SetLifeTime(Data->GetLifeTime());

		Time	    = InTime;
		RealTime    = InRealTime;
		SetFrame(InFrame);

		Location	  = Payload->Location;
		Direction	  = Payload->Direction;
		Rotation	  = Direction.Rotation();
		Transform.SetLocation(Location);
		Transform.SetRotation(Rotation.Quaternion());

		ChargePercent = Payload->ChargePercent;
		Speed		  = Data->GetInitialSpeed() + Payload->AdditionalSpeed;

		if (InObject && OnDeAllocate)
		{
			DelegateInvoker = (UObject*)InObject;
#if WITH_EDITOR
			OnDeAllocate_ScriptEvent.AddUObject(InObject, OnDeAllocate);
#endif // #if WITH_EDITOR
			OnDeAllocate_Event.AddUObject(InObject, OnDeAllocate);
		}
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, FCsProjectilePayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame, T* InObject, void (T::*OnDeAllocate)())
	{
		Init(InActiveIndex, Payload, InTime, InRealTime, InFrame, nullptr, nullptr, nullptr, InObject, OnDeAllocate);
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, FCsProjectilePayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InInstigator, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)())
	{
		Init(InActiveIndex, Payload, InTime, InRealTime, InFrame, Instigator, InOwner, nullptr, InObject, OnDeAllocate);
	}

	void Init(const uint16& InActiveIndex, FCsProjectilePayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InInstigator, UObject* InOwner, UObject* InParent)
	{
		SetActiveIndex(InActiveIndex);
		Relevance = Payload->Relevance;

		IsAllocated = true;

		Instigator = InInstigator;
		Owner	   = InOwner;
		Data	   = Payload->Data;

		Type_Script = Data->GetBaseProjectileType();
		Type		= (uint8)Type_Script;

		Parent	   = InParent;

		SetLifeTime(Data->GetLifeTime());

		Time	   = InTime;
		RealTime   = InRealTime;
		SetFrame(InFrame);

		Location	  = Payload->Location;
		Direction	  = Payload->Direction;
		Rotation	  = Direction.Rotation();
		Transform.SetLocation(Location);
		Transform.SetRotation(Rotation.Quaternion());

		ChargePercent = Payload->ChargePercent;
		Speed		  = Data->GetInitialSpeed() + Payload->AdditionalSpeed;
	}

	void Init(const uint16& InActiveIndex, FCsProjectilePayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InInstigator, UObject* InOwner)
	{
		Init(InActiveIndex, Payload, InTime, InRealTime, InFrame, InInstigator, InOwner, nullptr);
	}

	void Init(const uint16& InActiveIndex, FCsProjectilePayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		Init(InActiveIndex, Payload, InTime, InRealTime, InFrame, nullptr, nullptr, nullptr);
	}

	void Reset()
	{
		Reset_Internal();

		Data.Reset();
		Data  = nullptr;
		Relevance = ECsProjectileRelevance::ECsProjectileRelevance_MAX;
		Movement = ECsProjectileMovement::ECsProjectileMovement_MAX;
		ElapsedTime = 0.0f;
		Location = FVector::ZeroVector;
		Direction = FVector::ZeroVector;
		Rotation = FRotator::ZeroRotator;
		Transform = FTransform::Identity;
		ChargePercent = 0.0f;
		Speed = 0.0f;
		DrawDistanceSq = 0.0f;
	}

	ACsProjectile* GetProjectile() { return Projectile.IsValid() ? Projectile.Get() : nullptr; }
	template<typename T>
	T* GetProjectile() { return Cast<T>(GetProjectile()); }

	ACsData_Projectile* GetData() { return Data.IsValid() ? Data.Get() : nullptr; }
	template<typename T>
	T* GetData() { return Cast<T>(GetData()); }
};

UCLASS()
class CSCORE_API ACsProjectile : public ACsPooledActor
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	class USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
	class UCsProjectileMovementComponent* MovementComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class UStaticMeshComponent* MeshComponent;

	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnTick_HandleCVars(const float &DeltaSeconds) override;
	virtual void OnTick_HandleMovementFunction(const float &DeltaSeconds);

	void DrawPath(const float &DeltaSeconds);
	void DrawPath_Internal(const float &DeltaSeconds, const float &Interval, const uint8 &SegmentsPerInterval, const float &Thickness);

	virtual FVector EvaluateMovementFunction(const float &Time);

	UPROPERTY(BlueprintReadWrite, Category = "Projectile")
	FCsProjectileCache Cache;

	void Init(const int32 &Index);

	template<typename T>
	void Allocate(const uint16& ActiveIndex, FCsProjectilePayload* Payload, UObject* InInstigator, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)());

	template<typename T>
	void Allocate(const uint16& ActiveIndex, FCsProjectilePayload* Payload, T* InObject, void (T::*OnDeAllocate)());

	template<typename T>
	void Allocate(const uint16& ActiveIndex, FCsProjectilePayload* Payload, UObject* InInstigator, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)());

	virtual void Allocate(const uint16& ActiveIndex, FCsProjectilePayload* Payload, UObject* InInstigator, UObject* InOwner, UObject* InParent = nullptr);
	virtual void Allocate(const uint16& ActiveIndex, FCsProjectilePayload* Payload);

	virtual void Allocate_Internal(FCsProjectilePayload* Payload);

	UPROPERTY(BlueprintAssignable, Category = "Projectile")
	FBindableDynEvent_CsProjectile_Override_Allocate_Internal Override_Allocate_Internal_ScriptEvent;

	virtual void DeAllocate() override;

	TWeakObjectPtr<ACsProjectile> FakeProjectile;

	ACsProjectile* GetFakeProjectile();

	UPROPERTY(BlueprintReadWrite, Category = "Projectile")
	TEnumAsByte<ECsProjectileState::Type> State;

	float InitialSpeed;
	float CurrentSpeed;
	float Damage;

	UPROPERTY()
	TArray<TWeakObjectPtr<AActor>> IgnoreActors;

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void AddIgnoreActor(AActor* InActor);
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	AActor* GetIgnoreActor(const int32 &Index);

	UFUNCTION()
	virtual void OnHitCallback(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);

// Script
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	UObject* Cache_GetOwner();
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	UObject* Cache_GetInstigator();
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	ACsProjectile* Cache_GetProjectile();
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	ACsData_Projectile* Cache_GetData();

#pragma endregion Script
};

