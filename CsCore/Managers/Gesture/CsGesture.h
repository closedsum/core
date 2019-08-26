// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "../CoreUObject/Public/UObject/Object.h"
#include "Types/CsTypes.h"
#include "Managers/Input/CsTypes_Input.h"
#include "CsGesture.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsGesture_Override_ProcessInputs, const FCsInputFrame&, InputFrame);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableDynEvent_CsGesture_OnComplete);
DECLARE_MULTICAST_DELEGATE(FBindableEvent_CsGesture_OnComplete);

UCLASS()
class CSCORE_API UCsGesture : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "Gesture")
	TWeakObjectPtr<class UWorld> CurrentWorld;

	UFUNCTION(BlueprintCallable, Category = "Gesture")
	void SetCurrentWorld(UWorld* InWorld);
	UFUNCTION(BlueprintCallable, Category = "Gesture")
	UWorld* GetCurrentWorld();

	UPROPERTY(BlueprintReadOnly, Category = "Gesture")
	FECsGestureType Type;

	UPROPERTY(BlueprintReadOnly, Category = "Gesture")
	bool Completed;

	UPROPERTY(BlueprintAssignable, Category = "Gesture")
	FBindableDynEvent_CsGesture_OnComplete OnComplete_ScriptEvent;

	FBindableEvent_CsGesture_OnComplete OnComplete_Event;

	UFUNCTION(BlueprintCallable, Category = "Gesture")
	virtual bool CanProcessInputs();

	UPROPERTY(BlueprintAssignable, Category = "Gesture")
	FBindableDynEvent_CsGesture_Override_ProcessInputs Override_ProcessInputs_ScriptEvent;

	UFUNCTION(BlueprintCallable, Category = "Gesture")
	virtual void ProcessInputs(struct FCsInputFrame &InputFrame);
};