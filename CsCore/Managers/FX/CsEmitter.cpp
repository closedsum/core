// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
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
void ACsEmitter::Allocate(const uint16& ActiveIndex, FCsFxElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)())
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

	Cache.Init<T>(ActiveIndex, InElement, Time, RealTime, Frame, InOwner, InParent, InObject, OnDeAllocate);

	SetActorHiddenInGame(false);
	SetTemplate(Particle);

	SetActorRelativeScale3D(Cache.Scale3D);
	SetActorRelativeLocation(Cache.Location);
	SetActorRelativeRotation(Cache.Rotation);

	// Owner
	if (AActor* MyOwner = Cast<AActor>(InOwner))
		SetOwner(MyOwner);
	// Parent
	if (AActor* Actor = Cast<AActor>(InParent))
		AttachToActor(Actor, FAttachmentTransformRules::KeepRelativeTransform, Cache.Bone);
	else
	if (USceneComponent* Component = Cast<USceneComponent>(InParent))
		AttachToComponent(Component, FAttachmentTransformRules::KeepRelativeTransform, Cache.Bone);
}

template<typename T>
void ACsEmitter::Allocate(const uint16& ActiveIndex, FCsFxElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, T* InObject, void (T::*OnDeAllocate)())
{
	Cache.Init<T>(ActiveIndex, InElement, Time, RealTime, Frame, InObject, OnDeAllocate);
}

template<typename T>
void ACsEmitter::Allocate(const uint16& ActiveIndex, FCsFxElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, const FVector &Location, const FRotator &Rotation, T* InObject, void (T::*OnDeAllocate)())
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

	Cache.Init<T>(ActiveIndex, InElement, Time, RealTime, Frame, InOwner, Location, Rotation, InObject, OnDeAllocate);

	SetActorHiddenInGame(false);
	SetTemplate(Particle);

	SetActorRelativeScale3D(Cache.Scale3D);

	// Owner
	if (AActor* MyOwner = Cast<AActor>(InOwner))
		SetOwner(MyOwner);

	SetActorLocationAndRotation(Location, Rotation);
}

template<typename T>
void ACsEmitter::Allocate(const uint16& ActiveIndex, FCsFxElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, const FVector &Location, const FRotator &Rotation, T* InObject, void (T::*OnDeAllocate)())
{
	Allocate(ActiveIndex, InElement, Time, RealTime, Frame, nullptr, Location Rotation, InObject, OnDeAllocate);
}

void ACsEmitter::Allocate(const uint16& ActiveIndex, FCsFxElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent, const FVector &Location, const FRotator &Rotation)
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

	Cache.Init(ActiveIndex, InElement, Time, RealTime, Frame, InOwner, InParent, Location, Rotation);

	SetActorHiddenInGame(false);
	SetTemplate(Particle);

	SetActorRelativeScale3D(Cache.Scale3D);

	// Owner
	if (AActor* MyOwner = Cast<AActor>(InOwner))
		SetOwner(MyOwner);
	// Parent
	if (AActor* Actor = Cast<AActor>(InParent))
		AttachToActor(Actor, FAttachmentTransformRules::KeepWorldTransform, Cache.Bone);
	else
	if (USceneComponent* Component = Cast<USceneComponent>(InParent))
		AttachToComponent(Component, FAttachmentTransformRules::KeepWorldTransform, Cache.Bone);

	SetActorLocationAndRotation(Location, Rotation);
}

void ACsEmitter::Allocate(const uint16& ActiveIndex, FCsFxElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent)
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

	Cache.Init(ActiveIndex, InElement, Time, RealTime, Frame, InOwner, InParent);

	SetActorHiddenInGame(false);
	SetTemplate(Particle);

	SetActorRelativeScale3D(Cache.Scale3D);
	SetActorRelativeLocation(Cache.Location);
	SetActorRelativeRotation(Cache.Rotation);

	// Owner
	if (AActor* MyOwner = Cast<AActor>(InOwner))
		SetOwner(MyOwner);
	// Parent
	if (AActor* Actor = Cast<AActor>(InParent))
		AttachToActor(Actor, FAttachmentTransformRules::KeepRelativeTransform, Cache.Bone);
	else
	if (USceneComponent* Component = Cast<USceneComponent>(InParent))
		AttachToComponent(Component, FAttachmentTransformRules::KeepRelativeTransform, Cache.Bone);
}

void ACsEmitter::Allocate(const uint16& ActiveIndex, FCsFxElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, const FVector &Location, const FRotator &Rotation)
{
	Allocate(ActiveIndex, InElement, Time, RealTime, Frame, InOwner, nullptr, Location, Rotation);
}

void ACsEmitter::Allocate(const uint16& ActiveIndex, FCsFxElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, const FVector &Location, const FRotator &Rotation)
{
	Allocate(ActiveIndex, InElement, Time, RealTime, Frame, nullptr, nullptr, Location, Rotation);
}

void ACsEmitter::Allocate(const uint16& ActiveIndex, FCsFxElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame)
{
	Cache.Init(ActiveIndex, InElement, Time, RealTime, Frame);
}

void ACsEmitter::Allocate(const uint16& ActiveIndex, FCsFxElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent, const FRotator &Rotation)
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

	Cache.Init(ActiveIndex, InElement, Time, RealTime, Frame, InOwner, InParent);

	SetActorHiddenInGame(false);
	SetTemplate(Particle);

	SetActorRelativeScale3D(Cache.Scale3D);

	// Owner
	if (AActor* MyOwner = Cast<AActor>(InOwner))
		SetOwner(MyOwner);
	// Parent
	if (AActor* Actor = Cast<AActor>(InParent))
		AttachToActor(Actor, FAttachmentTransformRules::KeepRelativeTransform, Cache.Bone);
	else
	if (USceneComponent* Component = Cast<USceneComponent>(InParent))
		AttachToComponent(Component, FAttachmentTransformRules::KeepRelativeTransform, Cache.Bone);

	SetActorRotation(Rotation);
}


void ACsEmitter::DeAllocate()
{
	// TODO: Might need to do some extra checks
	DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);

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

	SetActorHiddenInGame(true);
	SetActorRelativeTransform(FTransform::Identity);
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