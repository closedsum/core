// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsInput_Rotation.h"
#include "CsCore.h"

// Managers
#include "Managers/Input/CsManager_Input.h"

UCsInput_Rotation::UCsInput_Rotation(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Info.Type		= ECsInputType::Rotation;
	Info.ValueType	= ECsInputValue::Rotator;
	Info.Event		= ECsInputEvent::Stationary;
	Info.Last_Event = ECsInputEvent::Stationary;
}

void UCsInput_Rotation::Raw(const FRotator &Rotation)
{
	if ((Manager_Input->CurrentInputActionMap & ActionMap) == 0)
		return;
																
	FCsInput* Input	= Manager_Input->GetPreviousPreviousInputAction(Action);
																
	if (!Input && Info.Rotation != Rotation)
		FirstMoved(Rotation);
	else
	if (Info.Rotation != Rotation)
		Moved(Rotation);
	else
	if ((!Input && Info.Rotation == Rotation) || (Input && Input->Rotation != Info.Rotation && Info.Rotation == Rotation))
		FirstStationary(Rotation);
	else
	if (Info.Rotation == Rotation)
		Stationary(Rotation);
}

void UCsInput_Rotation::FirstMoved(const FRotator &Rotation)
{
	Info.Set(ECsInputEvent::FirstMoved, Rotation);
	Manager_Input->AddInput(Action, Info.Event, 0.0f, FVector::ZeroVector, Rotation);
}

void UCsInput_Rotation::Moved(const FRotator &Rotation)
{
	Info.Set(ECsInputEvent::Moved, Rotation);
	Manager_Input->AddInput(Action, Info.Event, 0.0f, FVector::ZeroVector, Rotation);
}

void UCsInput_Rotation::FirstStationary(const FRotator &Rotation)
{
	Info.Set(ECsInputEvent::FirstStationary, Rotation);
	Manager_Input->AddInput(Action, Info.Event, 0.0f, FVector::ZeroVector, Rotation);
}

void UCsInput_Rotation::Stationary(const FRotator &Rotation)
{
	Info.Set(ECsInputEvent::Stationary, Rotation);
	Manager_Input->AddInput(Action, Info.Event, 0.0f, FVector::ZeroVector, Rotation);
}