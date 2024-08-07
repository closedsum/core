// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Input/CsTypes_Input.h"
#include "InputCoreTypes.h"
// Input
#include "Managers/Input/Action/CsInputAction.h"

#include "CsInputListener.generated.h"

class UCsManager_Input_Default;

UCLASS()
class CSINPUT_API UCsInputListener : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	FECsInputAction Action;

	ECsInputType Type;

	void Init(const FECsInputAction& InAction, const ECsInputType& InType, UCsManager_Input_Default* Manager_Input);

	// Action

	void OnAction_Pressed(FKey Key);

	DECLARE_DELEGATE_TwoParams(FOnAction_Pressed, const FECsInputAction& /*Action*/, const FKey& /*Key*/);

	FOnAction_Pressed OnAction_Pressed_Event;

	void OnAction_Released(FKey Key);

	DECLARE_DELEGATE_TwoParams(FOnAction_Released, const FECsInputAction& /*Action*/, const FKey& /*Key*/);

	FOnAction_Released OnAction_Released_Event;

	// Axis

	void OnAxis(float Value);

	DECLARE_DELEGATE_TwoParams(FOnAxis, const FECsInputAction& /*Action*/, const float& /*Value*/);

	FOnAxis OnAxis_Event;
};