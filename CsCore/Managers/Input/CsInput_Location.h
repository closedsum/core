// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/Input/CsInput_Base.h"
#include "CsInput_Location.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInputLocation_FirstMoved, AActor*, ActionOwner, const FVector&, Location);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInputLocation_Moved, AActor*, ActionOwner, const FVector&, Location);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInputLocation_FirstStationary, AActor*, ActionOwner, const FVector&, Location);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInputLocation_Stationary, AActor*, ActionOwner, const FVector&, Location);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInputLocation_FirstMoved, AActor*, const FVector&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInputLocation_Moved, AActor*, const FVector&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInputLocation_FirstStationary, AActor*, const FVector&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInputLocation_Stationary, AActor*, const FVector&);

UCLASS()
class CSCORE_API UCsInput_Location : public UCsInput_Base
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	FCsInput Input_Last;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Raw(const FVector &Location);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void FirstMoved(const FVector &Location);

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsInputLocation_FirstMoved FirstMoved_ScriptEvent;

	FBindableEvent_CsInputLocation_FirstMoved FirstMoved_Event;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Moved(const FVector &Location);

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsInputLocation_Moved Moved_ScriptEvent;

	FBindableEvent_CsInputLocation_Moved Moved_Event;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void FirstStationary(const FVector &Location);

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsInputLocation_FirstStationary FirstStationary_ScriptEvent;

	FBindableEvent_CsInputLocation_FirstStationary FirstStationary_Event;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Stationary(const FVector &Location);

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsInputLocation_Stationary Stationary_ScriptEvent;

	FBindableEvent_CsInputLocation_Stationary Stationary_Event;
};