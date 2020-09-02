// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "Managers/FX/CsTypes_FX.h"
#include "CsAnimNotify_PlayParticleEffect.generated.h"

USTRUCT()
struct FCsAnimNotifyFX
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "FX")
	class UParticleSystem* Particle;

	UPROPERTY(EditAnywhere, Category = "FX")
	ECsFXPriority Priority;

	UPROPERTY(EditAnywhere, Category = "FX", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float LifeTime;

	UPROPERTY(EditAnywhere, Category = "FX", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float DeathTime;

	UPROPERTY(EditAnywhere, Category = "FX", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Scale;

	UPROPERTY(EditAnywhere, Category = "FX")
	FCsFpvDrawDistance DrawDistances;

	UPROPERTY(EditAnywhere, Category = "FX")
	FName Bone;

	UPROPERTY(EditAnywhere, Category = "FX")
	FVector Location;

	UPROPERTY(EditAnywhere, Category = "FX")
	FRotator Rotation;

	FQuat RotationQuat;

	FCsAnimNotifyFX() :
		Particle(nullptr),
		Priority(ECsFXPriority::Medium),
		LifeTime(0.0f),
		DeathTime(1.0f),
		Scale(1.0f),
		DrawDistances(),
		Bone(NAME_None),
		Location(0.0f),
		Rotation(0.0f)
	{
	}

	FCsAnimNotifyFX& operator=(const FCsAnimNotifyFX& B)
	{
		Particle = B.Particle;
		LifeTime = B.LifeTime;
		DeathTime = B.DeathTime;
		Scale = B.Scale;
		DrawDistances = B.DrawDistances;
		Bone = B.Bone;
		Location = B.Location;
		Rotation = B.Rotation;
		return *this;
	}

	bool operator==(const FCsAnimNotifyFX& B) const
	{
		return (Particle == B.Particle &&
				LifeTime == B.LifeTime &&
				DeathTime == B.DeathTime &&
				Scale == B.Scale &&
				DrawDistances == B.DrawDistances &&
				Bone == B.Bone &&
				Location == B.Location &&
				Rotation == B.Rotation);
	}

	bool operator!=(const FCsAnimNotifyFX& B) const
	{
		return !(*this == B);
	}
};

class UAnimSequenceBase;
class UParticleSystem;
class USkeletalMeshComponent;

UCLASS(const, hidecategories=Object, collapsecategories, meta=(DisplayName="Custom Play Particle Effect"))
class CSCORE_API UCsAnimNotify_PlayParticleEffect : public UAnimNotify
{
	GENERATED_BODY()

public:

	UCsAnimNotify_PlayParticleEffect();

	// Begin UObject interface
	virtual void PostLoad() override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;
#endif
	// End UObject interface

	// Begin UAnimNotify interface
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	// End UAnimNotify interface

	UPROPERTY(EditAnywhere, Category = "AnimNotify")
	FCsAnimNotifyFX FX;

	FCsFxElement_DEPRECATED FxElement;
};