// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/Input/CsInput_Base.h"
#include "CsInput_Action.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsInputAction_FirstPressed, AActor*, ActionOwner);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsInputAction_Pressed, AActor*, ActionOwner);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsInputAction_FirstReleased, AActor*, ActionOwner);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsInputAction_FirstPressed, AActor*);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsInputAction_Pressed, AActor*);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsInputAction_FirstReleased, AActor*);

UCLASS()
class CSCORE_API UCsInput_Action : public UCsInput_Base
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "Input")
	void FirstPressed();

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsInputAction_FirstPressed FirstPressed_ScriptEvent;

	FBindableEvent_CsInputAction_FirstPressed FirstPressed_Event;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Pressed();

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsInputAction_Pressed Pressed_ScriptEvent;

	FBindableEvent_CsInputAction_Pressed Pressed_Event;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void FirstReleased();

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsInputAction_FirstReleased FirstReleased_ScriptEvent;

	FBindableEvent_CsInputAction_FirstReleased FirstReleased_Event;
};