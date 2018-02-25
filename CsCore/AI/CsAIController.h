// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "AIController.h"
#include "CsAIController.generated.h"

UCLASS()
class CSCORE_API ACsAIController : public AAIController
{
	GENERATED_UCLASS_BODY()

	virtual void OnConstructor(const FObjectInitializer& ObjectInitializer);
	
	bool UseAIPerceptionComponent;

	/** A PlayerState of this class will be associated with every player to replicate relevant player information to all clients. */
	UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category = Classes)
	TSubclassOf<APlayerState> PlayerStateClass;

	virtual void InitPlayerState() override;
};