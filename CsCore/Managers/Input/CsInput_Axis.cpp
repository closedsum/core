// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsInput_Axis.h"
#include "CsCore.h"

// Managers
#include "Managers/Input/CsManager_Input.h"

UCsInput_Axis::UCsInput_Axis(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Info.Type		= ECsInputType::Axis;
	Info.ValueType	= ECsInputValue::Float;
	Info.Event		= ECsInputEvent::Stationary;
	Info.Last_Event = ECsInputEvent::Stationary;
}

void UCsInput_Axis::Raw(float Val) 
{
	if ((Manager_Input->CurrentInputActionMap & ActionMap) == 0)
		return;
	if (Val != 0.0f && Info.Value == 0.0f)
		FirstMoved(Val);
	else
	if (Val != 0.0f && Info.Value != 0.0f)
		Moved(Val);
	else
	if (Val == 0.0f && Info.Value != 0.0f)
		FirstStationary(Val);
	else
	if (Val == 0.0f && Info.Value == 0.0f)
		Stationary(Val);
}

void UCsInput_Axis::FirstMoved(const float &Val)
{
	Info.Set(ECsInputEvent::FirstMoved, Val);
	Manager_Input->AddInput(Action, Info.Event, Val);
}

void UCsInput_Axis::Moved(const float &Val)
{
	Info.Set(ECsInputEvent::Moved, Val);
	Manager_Input->AddInput(Action, Info.Event, Val);
}

void UCsInput_Axis::FirstStationary(const float &Val)
{
	Info.Set(ECsInputEvent::FirstStationary, Val);
	Manager_Input->AddInput(Action, Info.Event, Val);
}

void UCsInput_Axis::Stationary(const float &Val)
{
	Info.Set(ECsInputEvent::Stationary, Val);
	Manager_Input->AddInput(Action, Info.Event, Val);
}