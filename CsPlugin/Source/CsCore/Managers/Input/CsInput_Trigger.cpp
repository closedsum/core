// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsInput_Trigger.h"
#include "CsCore.h"

// Managers
#include "Managers/Input/CsManager_Input.h"

UCsInput_Trigger::UCsInput_Trigger(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Info.Type		= ECsInputType::Trigger;
	Info.ValueType	= ECsInputValue::Float;
	Info.Event		= ECsInputEvent::Stationary;
	Info.Last_Event = ECsInputEvent::Stationary;
}

void UCsInput_Trigger::Raw(float Val)
{
	if ((Manager_Input->CurrentInputActionMap & ActionMap) == 0)
		return;
	FCsInput* Input	= Manager_Input->GetPreviousPreviousInputAction(Action);
																
	if (!Input && Info.Value != Val)
		FirstMoved(Val);
	else
	if (Info.Value != Val)
		Moved(Val);
	else
	if ((!Input && Info.Value == Val) || (Input && Input->Value != Info.Value && Info.Value == Val))
		FirstStationary(Val);
	else
	if (Info.Value == Val)
		Stationary(Val);
}

void UCsInput_Trigger::FirstMoved(const float &Val)
{
	Info.Set(ECsInputEvent::FirstMoved, Val);
	Manager_Input->AddInput(Action, Info.Event, Val);
}

void UCsInput_Trigger::Moved(const float &Val)
{
	Info.Set(ECsInputEvent::Moved, Val);
	Manager_Input->AddInput(Action, Info.Event, Val);
}

void UCsInput_Trigger::FirstStationary(const float &Val)
{
	Info.Set(ECsInputEvent::FirstStationary, Val);
	Manager_Input->AddInput(Action, Info.Event, Val);
}

void UCsInput_Trigger::Stationary(const float &Val)
{
	Info.Set(ECsInputEvent::Stationary, Val);
	Manager_Input->AddInput(Action, Info.Event, Val);
}