// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes.h"
#include "Particles/Emitter.h"
#include "CsEmitter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableDynEvent_CsFxCache_OnDeAllocate);
DECLARE_DELEGATE(FBindableEvent_CsFxCache_OnDeAllocate);

USTRUCT()
struct FCsFxCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	TWeakObjectPtr<class ACsEmitter> Emitter;
	TWeakObjectPtr<class UParticleSystem> Particle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TEnumAsByte<ECsFxPriority::Type> Priority;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	float DeathTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	float DeathStartTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	bool IsDying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FVector Location;

	FCsFxCache()
	{
		Reset();
	}

	void Set(const uint8 &InIndex, ACsEmitter* InEmitter)
	{
		Index   = InIndex;
		Emitter = InEmitter;
	}

	template<typename T>
	void Init(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)())
	{
		Owner = InOwner;
		Cue = InElement->Get();
		Parent = InParent;
		Priority = InElement->Priority;
		LifeTime = InElement->LifeTime;
		DeathTime = InElement->DeathTime;
		IsDying = false;
		Time = InTime;
		RealTime = InRealTime;
		Frame = InFrame;

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
	void Init(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, T* InObject, void (T::*OnDeAllocate)())
	{
		Init(InElement, InTime, InRealTime, InFrame, nullptr, nullptr, InObject, OnDeAllocate);
	}

	template<typename T>
	void Init(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, const FVector &InLocation, T* InObject, void (T::*OnDeAllocate)())
	{
		Init(InElement, InTime, InRealTime, InFrame, InOwner, nullptr, InObject, OnDeAllocate);

		Location = InLocation;
	}

	template<typename T>
	void Init(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &inFrame, const FVector &InLocation, T* InObject, void (T::*OnDeAllocate)())
	{
		Init(InElement, InTime, InRealTime, inFrame, nullptr, InLocation, InObject, OnDeAllocate);
	}

	void Init(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent, const FVector &InLocation)
	{
		IsAllocated = true;

		Owner = InOwner;
		Particle = InElement->Get();
		Parent = InParent;
		Priority = InElement->Priority;
		LifeTime = InElement->LifeTime;
		DeathTime = InElement->DeathTime;
		IsDying = false;
		Time = InTime;
		RealTime = InRealTime;
		Frame = InFrame;
		Location = InLocation;
	}

	void Init(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent)
	{
		Init(InElement, InTime, InRealTime, InFrame, InOwner, InParent, FVector::ZeroVector);
	}

	void Init(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, const FVector &InLocation)
	{
		Init(InElement, InTime, InRealTime, InFrame, nullptr, InOwner, InLocation);
	}

	void Init(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, const FVector &InLocation)
	{
		Init(InElement, InTime, InRealTime, InFrame, nullptr, nullptr, InLocation);
	}

	void Init(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		Init(InElement, InTime, InRealTime, InFrame, nullptr, nullptr, FVector::ZeroVector);
	}

	virtual void Reset() override
	{
		Super::Reset();

		IsAllocated = false;

		Particle.Reset();
		Particle = nullptr;
		Priority = ECsFxPriority::Low;
		DeathTime = 0.0f;
		DeathStartTime = 0.0f;
		IsDying = false;
	}

	ACsEmitter* GetEmitter() { return Emitter.IsValid() ? Emitter.Get() : nullptr; }
	class UParticleSystem* GetCue() { return Particle.IsValid() ? Particle.Get() : nullptr; }
};

UCLASS()
class CSCORE_API ACsEmitter : public AEmitter
{
	GENERATED_UCLASS_BODY()

public:

	FCsFxCache Cache;

	int32 PoolIndex;

	bool IsAllocated;

	virtual void PostActorCreated() override;

	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

	virtual void OutsideWorldBounds() override;

	void Init(const int32 &Index);

	template<typename T>
	void Allocate(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)());

	template<typename T>
	void Allocate(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, T* InObject, void (T::*OnDeAllocate)());

	template<typename T>
	void Allocate(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, const FVector &inLocation, T* InObject, void (T::*OnDeAllocate)());

	template<typename T>
	void Allocate(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &inFrame, const FVector &inLocation, T* InObject, void (T::*OnDeAllocate)());

	void Allocate(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent, const FVector &InLocation);
	void Allocate(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent);
	void Allocate(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, const FVector &InLocation);
	void Allocate(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, const FVector &InLocation);
	void Allocate(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame);

	void DeAllocate();
	void StartDeath();

	float StartTime;

	bool Play();
	bool Stop();
};