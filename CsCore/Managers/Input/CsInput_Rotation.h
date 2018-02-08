// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/Input/CsInput_Base.h"
#include "CsInput_Rotation.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInputRotation_FirstMoved, AActor*, ActionOwner, const FRotator&, Rotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInputRotation_Moved, AActor*, ActionOwner, const FRotator&, Rotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInputRotation_FirstStationary, AActor*, ActionOwner, const FRotator&, Rotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInputRotation_Stationary, AActor*, ActionOwner, const FRotator&, Rotation);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInputRotation_FirstMoved, AActor*, const FRotator&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInputRotation_Moved, AActor*, const FRotator&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInputRotation_FirstStationary, AActor*, const FRotator&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInputRotation_Stationary, AActor*, const FRotator&);

UCLASS()
class CSCORE_API UCsInput_Rotation : public UCsInput_Base
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	FCsInput Input_Last;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Raw(const FRotator &Rotation);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void FirstMoved(const FRotator &Rotation);

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsInputRotation_FirstMoved FirstMoved_ScriptEvent;

	FBindableEvent_CsInputRotation_FirstMoved FirstMoved_Event;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Moved(const FRotator &Rotation);

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsInputRotation_Moved Moved_ScriptEvent;

	FBindableEvent_CsInputRotation_Moved Moved_Event;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void FirstStationary(const FRotator &Rotation);

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsInputRotation_FirstStationary FirstStationary_ScriptEvent;

	FBindableEvent_CsInputRotation_FirstStationary FirstStationary_Event;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Stationary(const FRotator &Rotation);

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsInputRotation_Stationary Stationary_ScriptEvent;

	FBindableEvent_CsInputRotation_Stationary Stationary_Event;
};