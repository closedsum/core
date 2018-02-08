// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/Input/CsInput_Base.h"
#include "CsInput_Axis.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInputAxis_FirstMoved, AActor*, ActionOwner, const float&, Val);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInputAxis_Moved, AActor*, ActionOwner, const float&, Val);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInputAxis_FirstStationary, AActor*, ActionOwner, const float&, Val);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInputAxis_Stationary, AActor*, ActionOwner, const float&, Val);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInputAxis_FirstMoved, AActor*, const float&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInputAxis_Moved, AActor*, const float&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInputAxis_FirstStationary, AActor*, const float&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInputAxis_Stationary, AActor*, const float&);

UCLASS()
class CSCORE_API UCsInput_Axis : public UCsInput_Base
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	FCsInput Input_Last;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Raw(float Val);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void FirstMoved(const float &Val);

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsInputAxis_FirstMoved FirstMoved_ScriptEvent;

	FBindableEvent_CsInputAxis_FirstMoved FirstMoved_Event;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Moved(const float &Val);

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsInputAxis_Moved Moved_ScriptEvent;

	FBindableEvent_CsInputAxis_Moved Moved_Event;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void FirstStationary(const float &Val);

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsInputAxis_FirstStationary FirstStationary_ScriptEvent;

	FBindableEvent_CsInputAxis_FirstStationary FirstStationary_Event;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Stationary(const float &Val);

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsInputAxis_Stationary Stationary_ScriptEvent;

	FBindableEvent_CsInputAxis_Stationary Stationary_Event;
};