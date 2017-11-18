// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/CsPooledActor.h"
#include "Types/CsTypes_Projectile.h"
#include "Data/CsData_Projectile.h"
#include "CsProjectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsProjectile_Allocate_Internal, const int32&, PoolIndex);

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
	FVector Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FVector Direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	float ChargePercent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	float Speed;

	FCsProjectileCache()
	{
		Reset();
	}

	~FCsProjectileCache(){}

	void Set(const uint8 &InIndex, ACsProjectile* InProjectile)
	{
		Index	   = InIndex;
		Projectile = InProjectile;
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, const TCsProjectileRelevance &InRelevance, ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache, float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InInstigator, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)())
	{
		ActiveIndex		   = InActiveIndex;
		ActiveIndex_Script = (int32)ActiveIndex;
		Relevance		   = InRelevance;

		IsAllocated = true;

		Instigator = InInstigator;
		Owner	   = InOwner;
		Data	   = InData;

		Type_Script = InData->GetBaseProjectileType();
		Type		= (uint8)Type_Script;

		Parent	   = InParent;
		Time	   = InTime;
		RealTime   = InRealTime;
		Frame	   = InFrame;

		LifeTime	  = InData->GetLifeTime();
		Location	  = InFireCache->Location;
		Direction	  = InFireCache->Direction;
		ChargePercent = InFireCache->ChargePercent;
		Speed		  = InData->GetInitialSpeed() + InFireCache->AdditionalSpeed;

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
	void Init(const uint16& InActiveIndex, const TCsProjectileRelevance &InRelevance, ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache, const float &InTime, const float &InRealTime, const uint64 &InFrame, T* InObject, void (T::*OnDeAllocate)())
	{
		Init(InActiveIndex, InRelevance, InData, InFireCache, InTime, InRealTime, InFrame, nullptr, nullptr, nullptr, InObject, OnDeAllocate);
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, const TCsProjectileRelevance &InRelevance, ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InInstigator, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)())
	{
		Init(InActiveIndex, InRelevance, InData, InFireCache, InTime, InRealTime, InFrame, Instigator, InOwner, nullptr, InObject, OnDeAllocate);
	}

	void Init(const uint16& InActiveIndex, const TCsProjectileRelevance &InRelevance, ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InInstigator, UObject* InOwner, UObject* InParent)
	{
		ActiveIndex		   = InActiveIndex;
		ActiveIndex_Script = (int32)ActiveIndex;
		Relevance		   = InRelevance;

		IsAllocated = true;

		Instigator = InInstigator;
		Owner	   = InOwner;
		Data	   = InData;

		Type_Script = InData->GetBaseProjectileType();
		Type		= (uint8)Type_Script;

		Parent	   = InParent;
		Time	   = InTime;
		RealTime   = InRealTime;
		Frame	   = InFrame;

		LifeTime	  = InData->GetLifeTime();
		Location	  = InFireCache->Location;
		Direction	  = InFireCache->Direction;
		ChargePercent = InFireCache->ChargePercent;
		Speed		  = InData->GetInitialSpeed() + InFireCache->AdditionalSpeed;
	}

	void Init(const uint16& InActiveIndex, const TCsProjectileRelevance &InRelevance, ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InInstigator, UObject* InOwner)
	{
		Init(InActiveIndex, InRelevance, InData, InFireCache, InTime, InRealTime, InFrame, InInstigator, InOwner, nullptr);
	}

	void Init(const uint16& InActiveIndex, const TCsProjectileRelevance &InRelevance, ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		Init(InActiveIndex, InRelevance, InData, InFireCache, InTime, InRealTime, InFrame, nullptr, nullptr, nullptr);
	}

	void Reset()
	{
		Super::Reset();

		Data.Reset();
		Data  = nullptr;
		Relevance = ECsProjectileRelevance::ECsProjectileRelevance_MAX;
		Location = FVector::ZeroVector;
		Direction = FVector::ZeroVector;
		ChargePercent = 0.0f;
		Speed = 0.0f;
	}

	ACsProjectile* GetProjectile() { return Projectile.IsValid() ? Projectile.Get() : nullptr; }
	ACsData_Projectile* GetData() { return Data.IsValid() ? Data.Get() : nullptr; }
};

UCLASS()
class CSCORE_API ACsProjectile : public ACsPooledActor
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	class USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
	class UProjectileMovementComponent* MovementComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class UStaticMeshComponent* MeshComponent;

	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite, Category = "Projectile")
	FCsProjectileCache Cache;

	void Init(const int32 &Index);

	template<typename T>
	void Allocate(const uint16& ActiveIndex, const TCsProjectileRelevance &Relevance, class ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache, UObject* InInstigator, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)());

	template<typename T>
	void Allocate(const uint16& ActiveIndex, const TCsProjectileRelevance &Relevance, class ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache, T* InObject, void (T::*OnDeAllocate)());

	template<typename T>
	void Allocate(const uint16& ActiveIndex, const TCsProjectileRelevance &Relevance, class ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache, UObject* InInstigator, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)());

	virtual void Allocate(const uint16& ActiveIndex, const TCsProjectileRelevance &Relevance, class ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache, UObject* InInstigator, UObject* InOwner, UObject* InParent = nullptr);
	virtual void Allocate(const uint16& ActiveIndex, const TCsProjectileRelevance &Relevance, class ACsData_Projectile* InData, FCsProjectileFireCache* InFireCache);

	virtual void Allocate_Internal();

	UPROPERTY(BlueprintAssignable, Category = "Projectile")
	FBindableDynEvent_CsProjectile_Allocate_Internal Override_Allocate_Internal_ScriptEvent;

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

