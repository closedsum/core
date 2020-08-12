// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsInputListener.h"
#include "CsCore.h"

// Managers
#include "Managers/Input/CsManager_Input.h"
// Input
#include "Components/InputComponent.h"
// Player
#include "GameFramework/PlayerController.h"


UCsInputListener::UCsInputListener(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCsInputListener::Init(const FECsInputAction& InAction, const ECsInputType& InType, UCsManager_Input* Manager_Input)
{
	Action	= InAction;
	Type	= InType;

	APlayerController* Controller	= Manager_Input->OwnerAsController;
	UInputComponent* InputComponent = Controller->InputComponent;

	// Action
	if (Type == ECsInputType::Action)
	{
		InputComponent->BindAction<UCsInputListener>(Action.GetFName(), EInputEvent::IE_Pressed, this, &UCsInputListener::OnAction_Pressed);
		InputComponent->BindAction<UCsInputListener>(Action.GetFName(), EInputEvent::IE_Released, this, &UCsInputListener::OnAction_Released);

		OnAction_Pressed_Event.BindUObject(Manager_Input, &UCsManager_Input::OnAction_Pressed);
		OnAction_Released_Event.BindUObject(Manager_Input, &UCsManager_Input::OnAction_Released);
	}
	// Axis
	else
	if (Type == ECsInputType::Axis)
	{
		InputComponent->BindAxis<UCsInputListener>(Action.GetFName(), this, &UCsInputListener::OnAxis);

		OnAxis_Event.BindUObject(Manager_Input, &UCsManager_Input::OnAxis);
	}
}

void UCsInputListener::OnAction_Pressed()
{
	OnAction_Pressed_Event.Execute(Action);
}

void UCsInputListener::OnAction_Released()
{
	OnAction_Released_Event.Execute(Action);
}

void UCsInputListener::OnAxis(float Value)
{
	OnAxis_Event.Execute(Action, Value);
}