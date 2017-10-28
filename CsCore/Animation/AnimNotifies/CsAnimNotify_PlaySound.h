// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Types/CsTypes.h"
#include "CsAnimNotify_PlaySound.generated.h"

class UAnimSequenceBase;
class USkeletalMeshComponent;
class USoundCue;

UCLASS(const, hidecategories=Object, collapsecategories, meta=(DisplayName="Custom Play Sound"))
class CSCORE_API UCsAnimNotify_PlaySound : public UAnimNotify
{
	GENERATED_BODY()

public:

	UCsAnimNotify_PlaySound();

	// Begin UAnimNotify interface
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	// End UAnimNotify interface

	// Sound to Play
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	TAssetPtr<USoundCue> Sound;

	UPROPERTY(VisibleDefaultsOnly, Transient, Category = "AnimNotify")
	TWeakObjectPtr<USoundCue> Sound_Internal;

	USoundCue* GetSound();

	FCsSoundElement SoundElement;

	// Volume Multiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimNotify", meta=(ExposeOnSpawn = true))
	float VolumeMultiplier;

	// Pitch Multiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimNotify", meta=(ExposeOnSpawn = true))
	float PitchMultiplier;

	// If this sound should follow its owner
	UPROPERTY(EditAnywhere, Category = "AnimNotify")
	uint32 bFollow:1;

	// Socket or bone name to attach sound to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimNotify", meta=(EditCondition="bFollow", ExposeOnSpawn = true))
	FName AttachName;
};



