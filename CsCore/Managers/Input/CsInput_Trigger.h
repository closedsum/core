// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/Input/CsInput_Base.h"
#include "CsInput_Trigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInputTrigger_FirstMoved, AActor*, ActionOwner, const float&, Val);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInputTrigger_Moved, AActor*, ActionOwner, const float&, Val);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInputTrigger_FirstStationary, AActor*, ActionOwner, const float&, Val);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInputTrigger_Stationary, AActor*, ActionOwner, const float&, Val);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInputTrigger_FirstMoved, AActor*, const float&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInputTrigger_Moved, AActor*, const float&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInputTrigger_FirstStationary, AActor*, const float&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInputTrigger_Stationary, AActor*, const float&);

UCLASS()
class CSCORE_API UCsInput_Trigger : public UCsInput_Base
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	FCsInput Input_Last;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Raw(float Val);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void FirstMoved(const float &Val);

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsInputTrigger_FirstMoved FirstMoved_ScriptEvent;

	FBindableEvent_CsInputTrigger_FirstMoved FirstMoved_Event;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Moved(const float &Val);

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsInputTrigger_Moved Moved_ScriptEvent;

	FBindableEvent_CsInputTrigger_Moved Moved_Event;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void FirstStationary(const float &Val);

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsInputTrigger_FirstStationary FirstStationary_ScriptEvent;

	FBindableEvent_CsInputTrigger_FirstStationary FirstStationary_Event;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Stationary(const float &Val);

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsInputTrigger_Stationary Stationary_ScriptEvent;

	FBindableEvent_CsInputTrigger_Stationary Stationary_Event;
};