// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/CsPooledActor.h"
#include "CsTypes.h"
#include "CsProjectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableDynEvent_CsProjectileCache_OnDeAllocate);
DECLARE_DELEGATE(FBindableEvent_CsProjectileCache_OnDeAllocate);

USTRUCT()
struct FCsProjectileCache
{
	GENERATED_USTRUCT_BODY()

	uint8 Index;

	bool IsAllocated;

	TCsProjectileType Type;

	TWeakObjectPtr<UObject> Instigator;
	TWeakObjectPtr<UObject> Owner;
	TWeakObjectPtr<class ACsProjectile> Projectile;
	TWeakObjectPtr<class ACsData_Projectile> Data;
	TWeakObjectPtr<UObject> Parent;
	TWeakObjectPtr<UObject> DelegateInvoker;

	UPROPERTY(BlueprintAssignable, Category = "Projectile")
	FBindableDynEvent_CsProjectileCache_OnDeAllocate OnDeAllocate_ScriptEvent;

	FBindableEvent_CsProjectileCache_OnDeAllocate OnDeAllocate_Event;

	TCsSoundPriority Priority;

	float Duration;

	bool IsLooping;

	float Time;
	float RealTime;
	uint64 Frame;

	FVector Location;
	FVector Direction;
	float Speed;

	FCsProjectileCache()
	{
		Reset();
	}

	void Set(const uint8 &InIndex, ACsProjectile* InProjectile)
	{
		Index	   = InIndex;
		Projectile = InProjectile;
	}

	template<typename T>
	void Init(ACsData_Projectile* InData, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InInstigator, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)())
	{
		Instigator = InInstigator;
		Owner	   = InOwner;
		Data	   = InData;
		Parent	   = InParent;
		Time	   = InTime;
		RealTime   = InRealTime;
		Frame	   = InFrame;

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
	void Init(ACsData_Projectile* InData, const float &InTime, const float &InRealTime, const uint64 &InFrame, T* InObject, void (T::*OnDeAllocate)())
	{
		Init(InData, InTime, InRealTime, InFrame, NULL, NULL, NULL, InObject, OnDeAllocate);
	}

	template<typename T>
	void Init(ACsData_Projectile* InData, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InInstigator, UObject* InOwner, const FVector &InLocation, T* InObject, void (T::*OnDeAllocate)())
	{
		Init(InData, InTime, InRealTime, InFrame, Instigator, InOwner, NULL, InObject, OnDeAllocate);

		Location = InLocation;
	}

	template<typename T>
	void Init(ACsData_Projectile* InData, const float &InTime, const float &InRealTime, const uint64 &inFrame, const FVector &InLocation, T* InObject, void (T::*OnDeAllocate)())
	{
		Init(InData, InTime, InRealTime, inFrame, NULL, NULL, InLocation, InObject, OnDeAllocate);
	}

	void Init(ACsData_Projectile* InData, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InInstigator, UObject* InOwner, UObject* InParent, const FVector &InLocation)
	{
		IsAllocated = true;

		Instigator = InInstigator;
		Owner	   = InOwner;
		Data	   = InData;
		Parent	   = InParent;
		Time	   = InTime;
		RealTime   = InRealTime;
		Frame	   = InFrame;
		Location   = InLocation;
	}

	void Init(ACsData_Projectile* InData, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InInstigator, UObject* InOwner, UObject* InParent)
	{
		Init(InData, InTime, InRealTime, InFrame, InInstigator, InOwner, InParent, FVector::ZeroVector);
	}

	void Init(ACsData_Projectile* InData, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InInstigator, UObject* InOwner, const FVector &InLocation)
	{
		Init(InData, InTime, InRealTime, InFrame, InInstigator, InOwner, NULL, InLocation);
	}

	void Init(ACsData_Projectile* InData, const float &InTime, const float &InRealTime, const uint64 &InFrame, const FVector &InLocation)
	{
		Init(InData, InTime, InRealTime, InFrame, NULL, NULL, NULL, InLocation);
	}

	void Init(ACsData_Projectile* InData, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		Init(InData, InTime, InRealTime, InFrame, NULL, NULL, NULL, FVector::ZeroVector);
	}

	void Reset()
	{
		IsAllocated = false;

		if (UObject* Invoker = GetDelegateInvoker())
		{
#if WITH_EDITOR
			OnDeAllocate_ScriptEvent.RemoveAll(Invoker);
#endif // #if WITH_EDITOR
			OnDeAllocate_Event.Unbind();
		}

		Instigator.Reset();
		Instigator = NULL;
		Owner.Reset();
		Owner = NULL;
		Data.Reset();
		Data  = NULL;
		Parent.Reset();
		Parent	  = NULL;
		Duration  = 0.0f;
		IsLooping = false;
		Time	  = 0.0f;
		RealTime  = 0.0f;
		Frame	  = 0;
	}

	UObject* GetInstigator() { return Instigator.IsValid() ? Instigator.Get() : NULL; }
	UObject* GetOwner() { return Owner.IsValid() ? Owner.Get() : NULL; }
	ACsProjectile* GetProjectile() { return Projectile.IsValid() ? Projectile.Get() : NULL; }
	ACsData_Projectile* GetData() { return Data.IsValid() ? Data.Get() : NULL; }
	UObject* GetParent() { return Parent.IsValid() ? Parent.Get() : NULL; }
	UObject* GetDelegateInvoker() { return DelegateInvoker.IsValid() ? DelegateInvoker.Get() : NULL; }

	void DeAllocate()
	{
#if WITH_EDITOR
		OnDeAllocate_ScriptEvent.Broadcast();
#endif // #if WITH_EDITOR
		OnDeAllocate_Event.ExecuteIfBound();

		Reset();
	}
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

	FCsProjectileCache Cache;

	template<typename T>
	void Allocate(class ACsData_Projectile* InData, const FCsProjectileFireCache* InFireCache, UObject* InInstigator, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)());

	template<typename T>
	void Allocate(class ACsData_Projectile* InData, const FCsProjectileFireCache* InFireCache, T* InObject, void (T::*OnDeAllocate)());

	template<typename T>
	void Allocate(class ACsData_Projectile* InData, const FCsProjectileFireCache* InFireCache, UObject* InInstigator, UObject* InOwner, const FVector &Location, T* InObject, void (T::*OnDeAllocate)());

	template<typename T>
	void Allocate(class ACsData_Projectile* InData, const FCsProjectileFireCache* InFireCache, const FVector &InLocation, T* InObject, void (T::*OnDeAllocate)());

	virtual void Allocate(class ACsData_Projectile* InData, const FCsProjectileFireCache* InFireCache, UObject* InInstigator, UObject* InOwner, UObject* InParent = NULL, const FVector &Location = FVector::ZeroVector);
	virtual void Allocate(class ACsData_Projectile* InData, const FCsProjectileFireCache* InFireCache, const FVector &Location);

	virtual void Allocate_Internal();

	virtual void DeAllocate() override;

	TCsProjectileType Type;

	TWeakObjectPtr<ACsProjectile> FakeProjectile;

	ACsProjectile* GetFakeProjectile();

	TCsProjectileState State;

	float InitialSpeed;
	float CurrentSpeed;
	float Damage;

	UFUNCTION()
	void OnHitCallback(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);

	virtual void OnHitCallback_Internal(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);
};

