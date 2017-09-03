// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerState.h"
#include "CsPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPlayerState_OnTick, const uint8&, MappingId, const float&, DeltaSeconds);

UCLASS()
class CSCORE_API ACsPlayerState : public APlayerState
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable, Category = "Tick")
	FBindableDynEvent_CsPlayerState_OnTick OnTick_ScriptEvent;
};