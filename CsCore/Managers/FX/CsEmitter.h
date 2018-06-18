// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
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
	float Scale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FVector Scale3D;
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
		SetIndex(InIndex);
		Emitter = InEmitter;
	}
	void Init(const uint16& InActiveIndex, FCsFxPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		SetActiveIndex(InActiveIndex);

		IsAllocated = true;

		Owner = Payload->Owner;
		Particle = Payload->Particle;
		Parent = Payload->Parent;
		Priority = Payload->Priority;

		SetLifeTime(Payload->LifeTime);

		DeathTime = Payload->DeathTime;
		IsDying = false;
		Bone = Payload->Bone;
		Scale = Payload->Scale;
		Scale3D = FVector(Scale);
		Location = Bone != NAME_None ? Payload->Location : FVector::ZeroVector;
		Rotation = Bone != NAME_None ? Payload->Rotation : FRotator::ZeroRotator;
		Time = InTime;
		RealTime = InRealTime;
		SetFrame(InFrame);
	}

	virtual void Reset() override
	{
		Reset_Internal();

		IsAllocated = false;

		Particle.Reset();
		Particle = nullptr;
		Priority = ECsFxPriority::Low;
		DeathTime = 0.0f;
		DeathStartTime = 0.0f;
		IsDying = false;
		Bone = NAME_None;
		Scale = 1.0f;
		Scale3D = FVector::OneVector;
		Location = FVector::ZeroVector;
		Rotation = FRotator::ZeroRotator;
	}

	FORCEINLINE ACsEmitter* GetEmitter() { return Emitter.IsValid() ? Emitter.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetEmitter() { return Cast<T>(GetEmitter()); }

	FORCEINLINE class UParticleSystem* GetParticle() { return Particle.IsValid() ? Particle.Get() : nullptr; }
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
	void OnCreatePool();
	void Allocate(const uint16& ActiveIndex, FCsFxPayload* Payload);

	void DeAllocate();
	void StartDeath();

	float StartTime;

	bool Play();
	bool Stop();
};