// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsInput_Location.h"
#include "CsCore.h"

// Managers
#include "Managers/Input/CsManager_Input.h"

UCsInput_Location::UCsInput_Location(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCsInput_Location::Raw(const FVector &Location)
{
	if ((Manager_Input->CurrentInputActionMap & (ActionMap)) == 0)
		return;
																
	FCsInput* Input	= Manager_Input->GetPreviousPreviousInputAction(Action);
																
	if (!Input && Info.Location != Location)
		FirstMoved(Location);
	else
	if (Info.Location != Location)
		Moved(Location);
	else
	if ((!Input && Info.Location == Location) || (Input && Input->Location != Info.Location && Info.Location == Location))
		FirstStationary(Location);
	else
	if (Info.Location == Location)
		Stationary(Location);
}

void UCsInput_Location::FirstMoved(const FVector &Location)
{
	Info.Set(ECsInputEvent::FirstMoved, Location);
	Manager_Input->AddInput(Action, Info.Event, 0.0f, Location);
}

void UCsInput_Location::Moved(const FVector &Location)
{
	Info.Set(ECsInputEvent::Moved, Location);
	Manager_Input->AddInput(Action, Info.Event, 0.0f, Location);
}

void UCsInput_Location::FirstStationary(const FVector &Location)
{
	Info.Set(ECsInputEvent::FirstStationary, Location);
	Manager_Input->AddInput(Action, Info.Event, 0.0f, Location);
}

void UCsInput_Location::Stationary(const FVector &Location)
{
	Info.Set(ECsInputEvent::Stationary, Location);
	Manager_Input->AddInput(Action, Info.Event, 0.0f, Location);
}