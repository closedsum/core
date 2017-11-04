// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes.h"
#include "Types/CsTypes_FX.h"
#include "Particles/Emitter.h"
#include "CsEmitter.generated.h"

USTRUCT(BlueprintType)
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
	FName Bone;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FVector Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FRotator Rotation;

	FCsFxCache()
	{
		Reset();
	}

	~FCsFxCache(){}

	void Set(const uint8 &InIndex, ACsEmitter* InEmitter)
	{
		Index   = InIndex;
		Emitter = InEmitter;
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)())
	{
		ActiveIndex = InActiveIndex;
		ActiveIndex_Script = (uint8)ActiveIndex;

		IsAllocated = true;

		Owner = InOwner;
		Cue = InElement->Get();
		Parent = InParent;
		Priority = InElement->Priority;
		LifeTime = InElement->LifeTime;
		DeathTime = InElement->DeathTime;
		IsDying = false;
		Bone = InElement->Bone;
		Location = Bone != NAME_None ? InElement->Location : FVector::ZeroVector;
		Rotation = Bone != NAME_None ? InElement->Rotation : FRotator::ZeroRotator;
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
	void Init(const uint16& InActiveIndex, FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, T* InObject, void (T::*OnDeAllocate)())
	{
		Init(InActiveIndex, InElement, InTime, InRealTime, InFrame, nullptr, nullptr, InObject, OnDeAllocate);
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, const FVector &InLocation, const FRotator &InRotation, T* InObject, void (T::*OnDeAllocate)())
	{
		Init(InActiveIndex, InElement, InTime, InRealTime, InFrame, InOwner, nullptr, InObject, OnDeAllocate);

		if (Bone != NAME_None)
		{
			Location = InLocation;
			Rotation = InRotation;
		}
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &inFrame, const FVector &InLocation, const FVector &InRotation, T* InObject, void (T::*OnDeAllocate)())
	{
		Init(InActiveIndex, InElement, InTime, InRealTime, inFrame, nullptr, InLocation, InRotation, InObject, OnDeAllocate);
	}

	void Init(const uint16& InActiveIndex, FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent, const FVector &InLocation, const FRotator &InRotation)
	{
		ActiveIndex = InActiveIndex;
		ActiveIndex_Script = (int32)ActiveIndex;

		IsAllocated = true;

		Owner = InOwner;
		Particle = InElement->Get();
		Parent = InParent;
		Priority = InElement->Priority;
		LifeTime = InElement->LifeTime;
		DeathTime = InElement->DeathTime;
		IsDying = false;
		Bone = InElement->Bone;
		Location = Bone != NAME_None ? InElement->Location : InLocation;
		Rotation = Bone != NAME_None ? InElement->Rotation : InRotation;
		Time = InTime;
		RealTime = InRealTime;
		Frame = InFrame;
	}

	void Init(const uint16& InActiveIndex, FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent)
	{
		Init(InActiveIndex, InElement, InTime, InRealTime, InFrame, InOwner, InParent, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	void Init(const uint16& InActiveIndex, FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, const FVector &InLocation, const FRotator &InRotation)
	{
		Init(InActiveIndex, InElement, InTime, InRealTime, InFrame, nullptr, InOwner, InLocation, InRotation);
	}

	void Init(const uint16& InActiveIndex, FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, const FVector &InLocation, const FRotator &InRotation)
	{
		Init(InActiveIndex, InElement, InTime, InRealTime, InFrame, nullptr, nullptr, InLocation, InRotation);
	}

	void Init(const uint16& InActiveIndex, FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		Init(InActiveIndex, InElement, InTime, InRealTime, InFrame, nullptr, nullptr, FVector::ZeroVector, FRotator::ZeroRotator);
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
		Bone = NAME_None;
		Location = FVector::ZeroVector;
		Rotation = FRotator::ZeroRotator;
	}

	ACsEmitter* GetEmitter() { return Emitter.IsValid() ? Emitter.Get() : nullptr; }
	class UParticleSystem* GetParticle() { return Particle.IsValid() ? Particle.Get() : nullptr; }
};

UCLASS()
class CSCORE_API ACsEmitter : public AEmitter
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "FX")
	FCsFxCache Cache;

	int32 PoolIndex;

	virtual void PostActorCreated() override;

	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

	virtual void OutsideWorldBounds() override;

	void Init(const int32 &Index);

	template<typename T>
	void Allocate(const uint16& ActiveIndex, FCsFxElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)());

	template<typename T>
	void Allocate(const uint16& ActiveIndex, FCsFxElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, T* InObject, void (T::*OnDeAllocate)());

	template<typename T>
	void Allocate(const uint16& ActiveIndex, FCsFxElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, const FVector &Location, const FRotator &Rotation, T* InObject, void (T::*OnDeAllocate)());

	template<typename T>
	void Allocate(const uint16& ActiveIndex, FCsFxElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, const FVector &Location, const FRotator &Rotation, T* InObject, void (T::*OnDeAllocate)());

	void Allocate(const uint16& ActiveIndex, FCsFxElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent, const FVector &Location, const FRotator &Rotation);
	void Allocate(const uint16& ActiveIndex, FCsFxElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent);
	void Allocate(const uint16& ActiveIndex, FCsFxElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, const FVector &Location, const FRotator &Rotation);
	void Allocate(const uint16& ActiveIndex, FCsFxElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, const FVector &Location, const FRotator &Rotation);
	void Allocate(const uint16& ActiveIndex, FCsFxElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame);

	void DeAllocate();
	void StartDeath();

	float StartTime;

	bool Play();
	bool Stop();
};