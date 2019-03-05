// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/CsPooledActor.h"
#include "Types/CsTypes_Projectile.h"
#include "Data/CsData_Projectile.h"
#include "CsProjectile.generated.h"

// Allocate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsProjectile_Override_Allocate_Internal, const int32&, PoolIndex);

USTRUCT(BlueprintType)
struct FCsProjectileCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TWeakObjectPtr<class ACsProjectile> Projectile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TWeakObjectPtr<class ACsData_Projectile> Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FECsProjectileType Type;

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

	void Set(const int32 &InIndex, ACsProjectile* InProjectile)
	{
		Index = InIndex;
		Projectile = InProjectile;
	}

	void Init(FCsProjectilePayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		Relevance = Payload->Relevance;

		IsAllocated = true;

		Instigator = Payload->Instigator;
		Owner	   = Payload->Owner;
		Data	   = Payload->Data;

		Type = Data->GetProjectileType();

		Parent = Payload->Parent;

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

	void Reset()
	{
		FCsPooledObjectCache::Reset();

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

	FORCEINLINE ACsProjectile* GetProjectile() { return Projectile.IsValid() ? Projectile.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetProjectile() { return Cast<T>(GetProjectile()); }

	FORCEINLINE ACsData_Projectile* GetData() { return Data.IsValid() ? Data.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetData() { return Cast<T>(GetData()); }
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

	UPROPERTY(BlueprintReadOnly, Category = "Projectile")
	FECsProjectileType Type;

	void Init(const int32 &Index, const FECsProjectileType& InType);

	virtual void Allocate(FCsProjectilePayload* Payload);

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

