// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Animation/AnimNotifies/CsAnimNotify_PlayParticleEffect.h"
#include "CsCore.h"
#include "Common/CsCommon.h"

#include "Particles/ParticleSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "ParticleHelper.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimSequenceBase.h"

// Manager
#include "Managers/FX/CsManager_FX.h"

/////////////////////////////////////////////////////
// UAnimNotify_PlayParticleEffect

UCsAnimNotify_PlayParticleEffect::UCsAnimNotify_PlayParticleEffect()
	: Super()
{
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(192, 255, 99, 255);
#endif // WITH_EDITORONLY_DATA
}

void UCsAnimNotify_PlayParticleEffect::PostLoad()
{
	Super::PostLoad();

	FX.RotationQuat = FQuat(FX.Rotation);
}

#if WITH_EDITOR
void UCsAnimNotify_PlayParticleEffect::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	const FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	// Rotation
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsAnimNotifyFX, Rotation))
	{
		FX.RotationQuat = FQuat(FX.Rotation);
	}
	Super::PostEditChangeProperty(e);
}
#endif

FString UCsAnimNotify_PlayParticleEffect::GetNotifyName_Implementation() const
{
	if (FX.Particle)
	{
		return FX.Particle->GetName();
	}
	else
	{
		return Super::GetNotifyName_Implementation();
	}
}

void UCsAnimNotify_PlayParticleEffect::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	if (!FX.Particle)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsAnimNotify_PlayParticleEffect::Notify (%s): No Particle set on Notify for Anim: %s"), *(MeshComp->SkeletalMesh->GetName()), *(Animation->GetName()));
		return;
	}

	UWorld* CurrentWorld = MeshComp->GetWorld();

	// TODO: need to check case of AnimInstance

	const bool InGame = UCsCommon::IsPlayInGame(CurrentWorld) || UCsCommon::IsPlayInPIE(CurrentWorld);

	// Use FX Manager
	if (InGame)
	{
		ACsManager_FX* Manager_FX = ACsManager_FX::Get(CurrentWorld);

		FxElement.Set(FX.Particle);
		FxElement.Priority  = FX.Priority;
		FxElement.LifeTime  = FX.LifeTime;
		FxElement.DeathTime = FX.DeathTime;
		FxElement.Scale		= FX.Scale;
		FxElement.DrawDistances = FX.DrawDistances;
		FxElement.Bone		= FX.Bone;
		FxElement.Location	= FX.Location;
		FxElement.Rotation  = FX.Rotation;
		
		Manager_FX->Play(&FxElement, MeshComp->GetOwner() ? Cast<UObject>(MeshComp->GetOwner()) : Cast<UObject>(MeshComp->GetAttachParent()), MeshComp);
	}
	else
	{
		if (FX.Particle->IsImmortal())
		{
			UE_LOG(LogCs, Warning, TEXT("UCsAnimNotify_PlayParticleEffect::Notify (%s):: Anim: %s tried to spawn infinitely looping particle system: %s."), *(MeshComp->SkeletalMesh->GetName()), *GetNameSafe(Animation), *GetNameSafe(FX.Particle));
			return;
		}

		if (FX.Bone != NAME_None)
		{
			UGameplayStatics::SpawnEmitterAttached(FX.Particle, MeshComp, FX.Bone, FX.Location, FX.Rotation);
		}
		else
		{
			const FTransform MeshTransform = MeshComp->GetSocketTransform(FX.Bone);
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(MeshTransform.TransformPosition(FX.Location));
			SpawnTransform.SetRotation(MeshTransform.GetRotation() * FX.RotationQuat);
			UGameplayStatics::SpawnEmitterAtLocation(MeshComp->GetWorld(), FX.Particle, SpawnTransform);
		}
	}
}
