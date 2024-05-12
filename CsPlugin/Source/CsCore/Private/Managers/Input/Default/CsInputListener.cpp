// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/Default/CsInputListener.h"

// Managers
#include "Managers/Input/Default/CsManager_Input_Default.h"
// Input
#include "Components/InputComponent.h"
// Player
#include "GameFramework/PlayerController.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsInputListener)

UCsInputListener::UCsInputListener(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	Action(),
	Type(ECsInputType::ECsInputType_MAX),
	OnAction_Pressed_Event(),
	OnAction_Released_Event(),
	OnAxis_Event()
{
}

void UCsInputListener::Init(const FECsInputAction& InAction, const ECsInputType& InType, UCsManager_Input_Default* Manager_Input)
{
	Action	= InAction;
	Type	= InType;
	
	APlayerController* Controller	= Manager_Input->GetOwnerAsController();
	UInputComponent* InputComponent = Controller->InputComponent;

	// Action
	if (Type == ECsInputType::Action)
	{
		// Pressed
		{
			FInputActionBinding& Binding = InputComponent->BindAction<UCsInputListener>(Action.GetFName(), EInputEvent::IE_Pressed, this, &UCsInputListener::OnAction_Pressed);
			Binding.bConsumeInput		 = false;
		}
		// Released
		{
			FInputActionBinding& Binding = InputComponent->BindAction<UCsInputListener>(Action.GetFName(), EInputEvent::IE_Released, this, &UCsInputListener::OnAction_Released);
			Binding.bConsumeInput		 = false;
		}

		OnAction_Pressed_Event.BindUObject(Manager_Input, &UCsManager_Input_Default::OnAction_Pressed);
		OnAction_Released_Event.BindUObject(Manager_Input, &UCsManager_Input_Default::OnAction_Released);
	}
	// Axis
	else
	if (Type == ECsInputType::Axis)
	{
		FInputAxisBinding& Binding = InputComponent->BindAxis<UCsInputListener>(Action.GetFName(), this, &UCsInputListener::OnAxis);
		Binding.bConsumeInput	   = false;

		OnAxis_Event.BindUObject(Manager_Input, &UCsManager_Input_Default::OnAxis);
	}
}

void UCsInputListener::OnAction_Pressed(FKey Key)
{
	OnAction_Pressed_Event.Execute(Action, Key);
}

void UCsInputListener::OnAction_Released(FKey Key)
{
	OnAction_Released_Event.Execute(Action, Key);
}

void UCsInputListener::OnAxis(float Value)
{
	OnAxis_Event.Execute(Action, Value);
}