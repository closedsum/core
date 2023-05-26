// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsEmitter.h"
#include "CsCore.h"

// Component
#include "Particles/ParticleSystemComponent.h"

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

void ACsEmitter::OnCreatePool()
{
}

/*
void ACsEmitter::Allocate(FCsFxPayload* Payload)
{
	UParticleSystem* Particle = Payload->GetParticle();

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

	Cache.Init(Payload, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), UCsLibrary_Common::GetCurrentFrame(GetWorld()));

	SetActorHiddenInGame(false);
	SetTemplate(Particle);

	SetActorRelativeScale3D(Cache.Scale3D);

	bool IsLocalAttachment = false;

	// Owner
	if (AActor* MyOwner = Cache.GetOwner<AActor>())
	{
		SetOwner(MyOwner);
	}
	// Parent
	if (AActor* Actor = Cache.GetParent<AActor>())
	{
		IsLocalAttachment = true;
		AttachToActor(Actor, FAttachmentTransformRules::KeepWorldTransform, Cache.Bone);
	}
	else
	if (USceneComponent* Component = Cache.GetParent<USceneComponent>())
	{
		IsLocalAttachment = true;
		AttachToComponent(Component, FAttachmentTransformRules::KeepWorldTransform, Cache.Bone);
	}

	if (IsLocalAttachment)
		SetActorRelativeTransform(Cache.Transform);
	else
		SetActorLocationAndRotation(Cache.Location, Cache.Rotation);
	Play();
}
*/

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