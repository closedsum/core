// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsInput_Action.h"
#include "CsCore.h"

// Managers
#include "Managers/Input/CsManager_Input.h"

UCsInput_Action::UCsInput_Action(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Info.Type		= ECsInputType::Action;
	Info.ValueType	= ECsInputValue::Void;
	Info.Event		= ECsInputEvent::Released;
	Info.Last_Event = ECsInputEvent::Released;
}

void UCsInput_Action::FirstPressed()
{
	if ((Manager_Input->CurrentInputActionMap & ActionMap) == 0)
		return;

	Info.Event = ECsInputEvent::FirstPressed;
	Manager_Input->AddInput(Action, ECsInputEvent::FirstPressed);
}

void UCsInput_Action::Pressed()
{
	if (Info.Last_Event == ECsInputEvent::FirstPressed)
		Info.Event = ECsInputEvent::Pressed;
	Manager_Input->AddInput(Action, ECsInputEvent::Pressed);
}

void UCsInput_Action::FirstReleased()
{
	if ((Manager_Input->CurrentInputActionMap & ActionMap) == 0)
		return;

	Info.Event = ECsInputEvent::FirstReleased;
	Manager_Input->AddInput(Action, ECsInputEvent::FirstReleased);
}