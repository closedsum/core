// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/CsPooledActor.h"
#include "Types/CsTypes_Projectile.h"
//#include "Data/CsData_ProjectileBase.h"
#include "CsProjectileBase.generated.h"

// Allocate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsProjectile_Override_Allocate_Internal, const int32&, PoolIndex);

class ACsProjectileBase;
class UCsData_ProjectileBase;

USTRUCT(BlueprintType)
struct FCsProjectileBaseCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TWeakObjectPtr<ACsProjectileBase> Projectile;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	//TWeakObjectPtr<UCsData_ProjectileBase> Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FECsProjectile Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	ECsProjectileRelevance Relevance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	ECsProjectileMovement Movement;

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

	FCsProjectileBaseCache()
	{
		Reset();
	}

	~FCsProjectileBaseCache(){}

	void Set(const int32 &InIndex, ACsProjectileBase* InProjectile)
	{
		Index = InIndex;
		Projectile = InProjectile;
	}

	void Init(FCsProjectileBasePayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		Relevance = Payload->Relevance;

		bAllocated = true;

		Instigator = Payload->Instigator;
		Owner	   = Payload->Owner;
		//Data	   = Payload->Data;

		//Type = Data->GetProjectileType();

		Parent = Payload->Parent;

		//SetLifeTime(Data->GetLifeTime());

		Time	   = InTime;
		RealTime   = InRealTime;
		SetFrame(InFrame);

		Location	  = Payload->Location;
		Direction	  = Payload->Direction;
		Rotation	  = Direction.Rotation();
		Transform.SetLocation(Location);
		Transform.SetRotation(Rotation.Quaternion());

		ChargePercent = Payload->ChargePercent;
		//Speed		  = Data->GetInitialSpeed() + Payload->AdditionalSpeed;
	}

	void Reset()
	{
		FCsPooledObjectCache::Reset();

		//Data.Reset();
		//Data  = nullptr;
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

	FORCEINLINE ACsProjectileBase* GetProjectile() { return Projectile.IsValid() ? Projectile.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetProjectile() { return Cast<T>(GetProjectile()); }

	//FORCEINLINE UCsData_ProjectileBase* GetData() { return Data.IsValid() ? Data.Get() : nullptr; }
	//template<typename T>
	//FORCEINLINE T* GetData() { return Cast<T>(GetData()); }
};

UCLASS()
class CSPRJ_API ACsProjectileBase : public ACsPooledActor
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
	FCsProjectileBaseCache Cache;

	UPROPERTY(BlueprintReadOnly, Category = "Projectile")
	FECsProjectile Type;

	void Init(const int32& Index, const FECsProjectile& InType);

	virtual void Allocate(FCsProjectileBasePayload* Payload);

	virtual void Allocate_Internal(FCsProjectileBasePayload* Payload);

	UPROPERTY(BlueprintAssignable, Category = "Projectile")
	FBindableDynEvent_CsProjectile_Override_Allocate_Internal Override_Allocate_Internal_ScriptEvent;

	virtual void DeAllocate() override;

	TWeakObjectPtr<ACsProjectileBase> FakeProjectile;

	ACsProjectileBase* GetFakeProjectile();

	UPROPERTY(BlueprintReadWrite, Category = "Projectile")
	ECsProjectileState State;

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
	ACsProjectileBase* Cache_GetProjectile();
	//UFUNCTION(BlueprintCallable, Category = "Projectile")
	//UCsData_ProjectileBase* Cache_GetData();

#pragma endregion Script
};

