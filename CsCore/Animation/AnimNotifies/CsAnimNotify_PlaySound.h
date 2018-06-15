// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Types/CsTypes_Sound.h"
#include "CsAnimNotify_PlaySound.generated.h"

USTRUCT(BlueprintType)
struct FCsAnimNotifySound
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundCue* Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	FECsSoundType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TEnumAsByte<ECsSoundPriority::Type> Priority;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	bool bSpatialize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	float VolumeMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	float PitchMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	FName Bone;

	FCsAnimNotifySound()
	{
		Priority = ECsSoundPriority::Medium;
		bSpatialize = true;
		VolumeMultiplier = 1.0f;
		PitchMultiplier = 1.0f;
		Bone = NAME_None;
	}

	FCsAnimNotifySound& operator=(const FCsAnimNotifySound& B)
	{
		Sound = B.Sound;
		Priority = B.Priority;
		bSpatialize = B.bSpatialize;
		VolumeMultiplier = B.VolumeMultiplier;
		PitchMultiplier = B.PitchMultiplier;
		Bone = B.Bone;
		return *this;
	}

	bool operator==(const FCsAnimNotifySound& B) const
	{
		return Sound == B.Sound &&
			   Priority == B.Priority &&
			   bSpatialize == B.bSpatialize &&
			   VolumeMultiplier == B.VolumeMultiplier &&
			   PitchMultiplier == B.PitchMultiplier &&
			   Bone == B.Bone;
	}

	bool operator!=(const FCsAnimNotifySound& B) const
	{
		return !(*this == B);
	}
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	FCsAnimNotifySound Sound;

	FCsSoundElement SoundElement;
};



