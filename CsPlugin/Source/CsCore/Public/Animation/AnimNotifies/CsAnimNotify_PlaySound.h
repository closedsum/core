// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Animation/AnimNotifies/AnimNotify.h"
// Types
#include "Managers/Sound/CsTypes_Sound.h"

#include "CsAnimNotify_PlaySound.generated.h"

class UAnimSequenceBase;
class USkeletalMeshComponent;

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
	FCsSound Sound;
};