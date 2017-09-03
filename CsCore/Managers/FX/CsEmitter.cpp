// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsEmitter.h"
#include "CsCore.h"

#define CS_EMITTER_DEFAULT_LOCATION FVector(10000.0f)

ACsEmitter::ACsEmitter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bDestroyOnSystemFinish = false;

	GetParticleSystemComponent()->PrimaryComponentTick.bStartWithTickEnabled = false;
}

void ACsEmitter::PostActorCreated()
{
	Super::PostActorCreated();

	if (UParticleSystemComponent* Component = GetParticleSystemComponent())
	{
		Component->bAutoDestroy = false;
		Component->SecondsBeforeInactive = 0.0f;
	}
}

void ACsEmitter::FellOutOfWorld(const class UDamageType& dmgType)
{
	UE_LOG(LogCs, Warning, TEXT("ACsEmitter::FellOutOfWorld: Warning. Pool Objected with PoolIndex: %d is being FORCED DeAllocated."), PoolIndex);
	DeAllocate();
}

void ACsEmitter::OutsideWorldBounds()
{
	UE_LOG(LogCs, Warning, TEXT("ACsEmitter::OutsideWorldBounds: Warning. Pool Objected with PoolIndex: %d is being FORCED DeAllocated."), PoolIndex);
	DeAllocate();
}

void ACsEmitter::Init(const int32 &Index)
{
	PoolIndex = Index;

	Cache.Set(Index, this);
}

template<typename T>
void ACsEmitter::Allocate(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)())
{
	Cache.Init<T>(InElement, InTime, InRealTime, InFrame, InOwner, InParent, InObject, OnDeAllocate);
}

template<typename T>
void ACsEmitter::Allocate(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, T* InObject, void (T::*OnDeAllocate)())
{
	Cache.Init<T>(InElement, InTime, InRealTime, InFrame, InObject, OnDeAllocate);
}

template<typename T>
void ACsEmitter::Allocate(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, const FVector &InLocation, T* InObject, void (T::*OnDeAllocate)())
{
	Cache.Init<T>(InElement, InTime, InRealTime, InFrame, InOwner, InLocation, InObject, OnDeAllocate);
}

template<typename T>
void ACsEmitter::Allocate(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &inFrame, const FVector &InLocation, T* InObject, void (T::*OnDeAllocate)())
{
	Cache.Init<T>(InElement, InTime, InRealTime, inFrame, nullptr, inLocation, InObject, OnDeAllocate);
}

void ACsEmitter::Allocate(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent, const FVector &InLocation)
{
	Cache.Init(InElement, InTime, InRealTime, InFrame, InOwner, InParent, InLocation);
}

void ACsEmitter::Allocate(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent)
{
	UParticleSystem* Particle = InElement->Get();

	if (!Particle)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsEmitter::Allocate: Warning. Trying to Allocate Emitter with nullptr Particle System."));
		return;
	}

	if (!GetParticleSystemComponent())
	{
		UE_LOG(LogCs, Warning, TEXT("ACsEmitter::Allocate: Warning. Particle System Component is nullptr for %s"), *GetName());
		return;
	}

	Cache.Init(InElement, InTime, InRealTime, InFrame, InOwner, InParent);

	SetActorHiddenInGame(false);
	SetTemplate(Particle);

	SetActorRelativeScale3D(FVector(InElement->Scale));
	SetActorRelativeLocation(InElement->Location);
	SetActorRelativeRotation(InElement->Rotation);

	// Owner
	if (AActor* MyOwner = Cast<AActor>(InOwner))
		SetOwner(MyOwner);
	// Parent
	if (AActor* Actor = Cast<AActor>(InParent))
		AttachToActor(Actor, FAttachmentTransformRules::KeepRelativeTransform, InElement->Bone);
	else
	if (USceneComponent* Component = Cast<USceneComponent>(InParent))
		AttachToComponent(Component, FAttachmentTransformRules::KeepRelativeTransform, InElement->Bone);
}

void ACsEmitter::Allocate(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, const FVector &InLocation)
{
	Cache.Init(InElement, InTime, InRealTime, InFrame, InOwner, InLocation);
}

void ACsEmitter::Allocate(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, const FVector &InLocation)
{
	Cache.Init(InElement, InTime, InRealTime, InFrame, InLocation);
}

void ACsEmitter::Allocate(FCsFxElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame)
{
	Cache.Init(InElement, InTime, InRealTime, InFrame);
}

void ACsEmitter::DeAllocate()
{
	// TODO: Might need to do some extra checks
	DetachRootComponentFromParent();

	Cache.Reset();

	if (UParticleSystemComponent* Component = GetParticleSystemComponent())
	{
		Component->SetVisibility(false);
		Component->KillParticlesForced();
		Component->SetHiddenInGame(true);
		Component->Deactivate();
		Component->SetComponentTickEnabled(false);
		Component->CustomTimeDilation = 1.0f;
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsEmitter::Allocate: Warning. Particle System Component is nullptr for %s"), *GetName());
	}

	SetActorRelativeTransform(FTransform::Identity);
	SetActorScale3D(CS_VECTOR_ONE);
	SetActorLocation(CS_EMITTER_DEFAULT_LOCATION);
	SetTemplate(nullptr);
	SetOwner(nullptr);
}

void ACsEmitter::StartDeath()
{
	if (UParticleSystemComponent* Component = GetParticleSystemComponent())
	{
		Component->DeactivateSystem();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsEmitter::StartDeath: Warning. Particle System Component is nullptr for %s"), *GetName());
	}
	Cache.IsDying		  = true;
	Cache.DeathStartTime = GetWorld()->GetTimeSeconds();
}

bool ACsEmitter::Play()
{
	// Particle
	if (UParticleSystemComponent* Component = GetParticleSystemComponent())
	{
		Component->SetComponentTickEnabled(true);
		Component->SetVisibility(true);
		Component->SetHiddenInGame(false);
		Component->Activate();
		Component->bAutoDestroy = false;
		return true;
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsEmitter::Allocate: Warning. Particle System Component is nullptr for %s"), *GetName());
	}
	return false;
}

bool ACsEmitter::Stop()
{
	return true;
}