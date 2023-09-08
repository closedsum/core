// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/FX/CsTypes_FX.h"
#include "Managers/Pool/CsTypes_Pool.h"
#include "Particles/Emitter.h"

#include "CsEmitter.generated.h"

USTRUCT(BlueprintType)
struct FCsFxCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	TWeakObjectPtr<class ACsEmitter> Emitter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	TWeakObjectPtr<class UParticleSystem> Particle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	ECsFXPriority Priority;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	float DeathTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	float DeathStartTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	bool IsDying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	FName Bone;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	float Scale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	FVector3f Scale3D;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	FVector3f Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	FRotator3f Rotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	FTransform3f Transform;

	FCsFxCache()
	{
		Reset();
	}

	~FCsFxCache(){}

	void Set(const int32 &InIndex, ACsEmitter* InEmitter)
	{
		Index = InIndex;
		Emitter = InEmitter;
	}
	/*
	void Init(FCsFxPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		bAllocated = true;

		Owner = Payload->Owner;
		Particle = Payload->Particle;
		Parent = Payload->Parent;
		Priority = Payload->Priority;

		SetLifeTime(Payload->LifeTime);

		DeathTime = Payload->DeathTime;
		IsDying = false;
		Bone = Payload->Bone;
		Scale = Payload->Scale;
		Scale3D = FVector3f(Scale);
		Location = Bone != NAME_None ? Payload->Location : FVector3f::ZeroVector;
		Rotation = Bone != NAME_None ? Payload->Rotation : FRotator3f::ZeroRotator;
		Transform.SetScale3D(Scale3D);
		Transform.SetLocation(Location);
		Transform.SetRotation(Rotation.Quaternion());
		Time = InTime;
		RealTime = InRealTime;
		SetFrame(InFrame);
	}
	*/
	virtual void Reset() override
	{
		FCsPooledObjectCache::Reset();

		Particle.Reset();
		Particle = nullptr;
		Priority = ECsFXPriority::Low;
		DeathTime = 0.0f;
		DeathStartTime = 0.0f;
		IsDying = false;
		Bone = NAME_None;
		Scale = 1.0f;
		Scale3D = FVector3f::OneVector;
		Location = FVector3f::ZeroVector;
		Rotation = FRotator3f::ZeroRotator;
		Transform = FTransform3f::Identity;
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

	UPROPERTY(BlueprintReadWrite, Category = "CsCore|FX")
	FCsFxCache Cache;

	int32 PoolIndex;

	virtual void PostActorCreated() override;

	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

	virtual void OutsideWorldBounds() override;

	void Init(const int32 &Index);
	void OnCreatePool();
	//void Allocate(FCsFxPayload* Payload);

	void DeAllocate();
	void StartDeath();

	float StartTime;

	bool Play();
	bool Stop();
};