// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsManager_Input.h"
#include "CsCore.h"
#include "Player/CsPlayerController.h"
#include "Player/CsCheatManager.h"
#include "Common/CsCommon.h"
#include "CsCVars.h"

#include "../HeadMountedDisplay/Public/IMotionController.h"

ACsManager_Input::ACsManager_Input(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;

	CurrentInputFrameIndex	  = INDEX_NONE;
	//CurrentInputActionMap = ECsInputActionMap::Game;
}

/*static*/ ACsManager_Input* ACsManager_Input::Get(UWorld* InWorld)
{
	return UCsCommon::GetLocalPlayerController<ACsPlayerController>(InWorld)->Manager_Input;
}

AActor* ACsManager_Input::GetInputOwner()
{
	return InputOwner.IsValid() ? InputOwner.Get() : nullptr;
}

void ACsManager_Input::SetupInputComponent()
{
	if (!InputComponent)
	{
		InputComponent = NewObject<UInputComponent>(this, TEXT("InputComponent"));
		InputComponent->RegisterComponent();
	}
#if WITH_EDITOR
// Editor Game

	// RunEditorGameBatchConsoleCommands
	InputComponent->BindAction("RunEditorGameBatchConsoleCommands", IE_Pressed, this, &ACsManager_Input::RunEditorGameBatchConsoleCommands_FirstPressed).bConsumeInput = false;
	// RunEditorGameJavascriptFile
	InputComponent->BindAction("RunEditorGameJavascriptFile", IE_Pressed, this, &ACsManager_Input::RunEditorGameJavascriptFile_FirstPressed).bConsumeInput = false;

	APlayerController* Controller = Cast<APlayerController>(GetInputOwner());
	UCsCheatManager* CheatManager = Cast<UCsCheatManager>(Controller->CheatManager);

	OnRunEditorGameBatchConsoleCommands_FirstPressed_Event.AddUObject(CheatManager, &UCsCheatManager::RunEditorGameBatchConsoleCommands);
	OnRunEditorGameJavascriptFile_FirstPressed_Event.AddUObject(CheatManager, &UCsCheatManager::RunEditorGameJavascriptFile);

#endif // #if WITH_EDITOR
}

void ACsManager_Input::PreProcessInput(const float DeltaTime, const bool bGamePaused)
{
	CurrentGameFrame++;

	CurrentDeltaTime	   = DeltaTime;
	CurrentInputFrameIndex = (CurrentInputFrameIndex + 1) % CS_MAX_INPUT_FRAMES;

	InputFrames[CurrentInputFrameIndex].Init(GetWorld()->TimeSeconds, GetWorld()->RealTimeSeconds, DeltaTime, CurrentGameFrame);

	const bool IsVR = UCsCommon::IsVR();

	if (IsVR)
	{
		FRotator Rotation;
		FVector Location;

		UCsCommon::GetHMDOrientationAndPosition(Rotation, Location);

		HMD_Rotation_Raw.ExecuteIfBound(Rotation);
		HMD_Location_Raw.ExecuteIfBound(Location);
	}

	TArray<IMotionController*> Controllers = IModularFeatures::Get().GetModularFeatureImplementations<IMotionController>(IMotionController::GetModularFeatureName());

	const int32 Count = Controllers.Num();

	for (int32 I = 0; I < Count; I++)
	{
		const uint8 LocalPlayerIndex = 0;

		// Check controllers are being Tracked

		/*
		const ETrackingStatus LeftStatus = Controllers[I]->GetControllerTrackingStatus(LocalPlayerIndex, EControllerHand::Left);
		
		if (LeftStatus != ETrackingStatus::Tracked)
			continue;

		const ETrackingStatus RightStatus = Controllers[I]->GetControllerTrackingStatus(LocalPlayerIndex, EControllerHand::Right);

		if (RightStatus != ETrackingStatus::Tracked)
			continue;
		*/
		const float WorldToMetersScale = 100.0f;

		FRotator Rotation;
		FVector Location;

		// Left
		if (Controllers[I]->GetControllerOrientationAndPosition(LocalPlayerIndex, EControllerHand::Left, Rotation, Location, WorldToMetersScale))
		{
			LeftHand_Rotation_Raw.ExecuteIfBound(Rotation);
			LeftHand_Location_Raw.ExecuteIfBound(Location);
		}
		// Right
		if (Controllers[I]->GetControllerOrientationAndPosition(LocalPlayerIndex, EControllerHand::Right, Rotation, Location, WorldToMetersScale))
		{
			RightHand_Rotation_Raw.ExecuteIfBound(Rotation);
			RightHand_Location_Raw.ExecuteIfBound(Location);
		}
	}
}

void ACsManager_Input::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	// TODO: Potentially also capture sustained "released" inputs

	// TODO: This would be the place to process an action that is a combination of multiple inputs in a frame (or over multiple frames)

	FCsInputFrame& InputFrame = InputFrames[CurrentInputFrameIndex];

	// Add Queued Inputs
	const uint8 QueuedInputCount = QueuedInputsForNextFrame.Num();

	for (uint8 I = 0; I < QueuedInputCount; I++)
	{
		InputFrame.Inputs.Add(QueuedInputsForNextFrame[I]);
	}
	QueuedInputsForNextFrame.Reset();

	// Set FirstReleased Events to Released after 1 Frame

	// TODO: Potentially Optimize to O(n) versus O(n^2)
	const uint8 ActionCount = (uint8)InputAction_MAX;

	for (uint8 I = 0; I < ActionCount; I++)
	{
		// Transition From FirstPressed to Pressed
		if (*(Actions[I]) == ECsInputEvent::FirstPressed && 
			*(Last_Actions[I]) == ECsInputEvent::FirstPressed)
		{
			const TCsInputAction Action = (TCsInputAction)I;
			const uint8 InputCount		= InputFrame.Inputs.Num();

			bool Found = false;

			for (uint8 J = 0; J < InputCount; J++)
			{
				if (InputFrame.Inputs[J]->Action == Action)
				{
					Found = true;
					break;
				}
			}

			if (!Found)
				*(Actions[I]) = ECsInputEvent::Pressed;
		}
		// Transition from FirstReleased to Released
		if (*(Actions[I]) == ECsInputEvent::FirstReleased &&
			*(Last_Actions[I]) == ECsInputEvent::FirstReleased)
		{
			const TCsInputAction Action = (TCsInputAction)I;
			const uint8 InputCount	    = InputFrame.Inputs.Num();

			bool Found = false;

			for (uint8 J = 0; J < InputCount; J++)
			{
				if (InputFrame.Inputs[J]->Action == Action)
				{
					Found = true;
					break;
				}
			}

			if (!Found)
				*(Actions[I]) = ECsInputEvent::Released;
		}
		// Transition From FireMoved to Moved
		if (*(Actions[I]) == ECsInputEvent::FirstMoved && 
			*(Last_Actions[I]) == ECsInputEvent::FirstMoved)
		{
			const TCsInputAction Action = (TCsInputAction)I;
			const uint8 InputCount		= InputFrame.Inputs.Num();

			bool Found = false;

			for (uint8 J = 0; J < InputCount; J++)
			{
				if (InputFrame.Inputs[J]->Action == Action)
				{
					Found = true;
					break;
				}
			}

			if (!Found)
				*(Actions[I]) = ECsInputEvent::Moved;
		}
		// Transition from FirstStationary to Stationary
		if (*(Actions[I]) == ECsInputEvent::FirstStationary && 
			*(Last_Actions[I]) == ECsInputEvent::FirstStationary) 
		{
			const TCsInputAction Action = (TCsInputAction)I;
			const uint8 InputCount		= InputFrame.Inputs.Num();

			bool Found = false;

			for (uint8 J = 0; J < InputCount; J++)
			{
				if (InputFrame.Inputs[J]->Action == Action)
				{
					Found = true;
					break;
				}
			}

			if (!Found)
				*(Actions[I]) = ECsInputEvent::Stationary;
		}
		// Update Last_Actions.
		*(Last_Actions[I]) = *(Actions[I]);

		// Currently NO Bindings for PRESSED Inputs, so manually add them
		if (*(Actions[I]) == ECsInputEvent::Pressed)
			AddInput((TCsInputAction)I, ECsInputEvent::Pressed);
	}
	// Process Inputs
	AActor* ActionOwner    = GetInputOwner();
	const uint8 InputCount = InputFrame.Inputs.Num();

	for (uint8 I = 0; I < InputCount; I++)
	{
		ProcessInput(ActionOwner, nullptr, InputFrame.Inputs[I], DeltaTime);
	}

	// Log Actions
	if (CsCVarLogInputs->GetInt() == CS_CVAR_SHOW_LOG)
	{
		const FString InputActionMapAsString = (*InputActionMapToString)(CurrentInputActionMap);

		UE_LOG(LogCs, Log, TEXT("ACsManager_Input::PostProcessInput: ActionMap: %s Frame: %d Time: %f DeltaTime: %f Count: %d"), *InputActionMapAsString, InputFrame.Frame, InputFrame.Time, InputFrame.DeltaTime, InputFrame.Inputs.Num());

		for (uint8 I = 0; I < InputCount; I++)
		{
			const FCsInput* Input = InputFrame.Inputs[I];

			const FString Action = (*InputActionToString)(Input->Action);
			const FString Event = (*InputEventToString)(Input->Event);

			// Void - No Value
			if ((CsCVarLogInputAll->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogInputActions->GetInt() == CS_CVAR_SHOW_LOG) &&
				Infos[(uint8)Input->Action]->ValueType == ECsInputValue::Void)
			{
				UE_LOG(LogCs, Log, TEXT("ACsManager_Input::PostProcessInput: %s: %s"), *Action, *Event);
			}
			// Float
			if ((CsCVarLogInputAll->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogInputAxis->GetInt() == CS_CVAR_SHOW_LOG) &&
				Infos[(uint8)Input->Action]->ValueType == ECsInputValue::Float)
			{
				UE_LOG(LogCs, Log, TEXT("ACsManager_Input::PostProcessInput: %s: %s Value: %f"), *Action, *Event, Input->Value);
			}
			// Vector
			if ((CsCVarLogInputAll->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogInputLocations->GetInt() == CS_CVAR_SHOW_LOG) &&
				Infos[(uint8)Input->Action]->ValueType == ECsInputValue::Vector)
			{
				UE_LOG(LogCs, Log, TEXT("ACsManager_Input::PostProcessInput: %s: %s Value: %s"), *Action, *Event, *Input->Location.ToString());
			}
			// Rotator
			if ((CsCVarLogInputAll->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogInputRotations->GetInt() == CS_CVAR_SHOW_LOG) &&
				Infos[(uint8)Input->Action]->ValueType == ECsInputValue::Rotator)
			{
				UE_LOG(LogCs, Log, TEXT("ACsManager_Input::PostProcessInput: %s: %s Value: %s"), *Action, *Event, *Input->Rotation.ToString());
			}
		}
	}

	// Copy the Current Input Frame
	CurrentInputFrame = InputFrame;
	// Determine Game Events
	DetermineGameEvents(InputFrame.Inputs);
}

void ACsManager_Input::ProcessInput(AActor* ActionOwner, const struct FCsInput* PreviousInput, const struct FCsInput* CurrentInput, const float DeltaTime)
{
	if (!CurrentInput)
		return;

	const TCsInputAction Action	   = CurrentInput->Action;
	const TCsInputEvent Event	   = CurrentInput->Event;
	const TCsInputEvent Last_Event = Infos[(uint8)Action]->Last_Event;
	const float Value			   = CurrentInput->Value;
	const FVector Location		   = CurrentInput->Location;
	const FRotator Rotation		   = CurrentInput->Rotation;

	// Pressed
	if (Infos[(uint8)Action]->Type == ECsInputType::Action)
	{
		if (Event == ECsInputEvent::Pressed &&
			(Last_Event == ECsInputEvent::FirstPressed || Last_Event == ECsInputEvent::Pressed))
		{
			Infos[(uint8)Action]->Duration += DeltaTime;
		}
		else
		{
			Infos[(uint8)Action]->Duration = 0.0f;
		}

		Default_Event.Broadcast(ActionOwner, (uint8)Action, Event);
#if WITH_EDITOR
		Default_ScriptEvent.Broadcast((uint8)Action, Event);
#endif // #if WITH_EDITOR

		// FirstPressed
		if (Event == ECsInputEvent::FirstPressed)
		{
			FirstPressed_Event.Broadcast(ActionOwner, (uint8)Action);
#if WITH_EDITOR
			FirstPressed_ScriptEvent.Broadcast((uint8)Action);
#endif // #if WITH_EDITOR
			return;
		}
		// Pressed
		if (Event == ECsInputEvent::Pressed)
		{
			Pressed_Event.Broadcast(ActionOwner, (uint8)Action);
#if WITH_EDITOR
			Pressed_ScriptEvent.Broadcast((uint8)Action);
#endif // #if WITH_EDITOR
			return;
		}
		// FirstReleased
		if (Event == ECsInputEvent::FirstReleased)
		{
			FirstReleased_Event.Broadcast(ActionOwner, (uint8)Action);
#if WITH_EDITOR
			FirstReleased_ScriptEvent.Broadcast((uint8)Action);
#endif // #if WITH_EDITOR
			return;
		}
		return;
	}
	// Axis
	if (Infos[(uint8)Action]->Type == ECsInputType::Axis)
	{
		if ((Event == ECsInputEvent::FirstMoved || Event == ECsInputEvent::Moved) &&
			(Last_Event == ECsInputEvent::FirstMoved || Last_Event == ECsInputEvent::Moved))
		{
			Infos[(uint8)Action]->Duration += DeltaTime;
		}
		else
		{
			Infos[(uint8)Action]->Duration = 0.0f;
		}

		Axis_Event.Broadcast(ActionOwner, (uint8)Action, Event, Value);
#if WITH_EDITOR
		Axis_ScriptEvent.Broadcast((uint8)Action, Event, Value);
#endif // #if WITH_EDITOR

		// FirstMoved
		if (Event == ECsInputEvent::FirstMoved)
		{
			Axis_FirstMoved_Event.Broadcast(ActionOwner, (uint8)Action, Value);
#if WITH_EDITOR
			Axis_FirstMoved_ScriptEvent.Broadcast((uint8)Action, Value);
#endif // #if WITH_EDITOR
			return;
		}
		// Moved
		if (Event == ECsInputEvent::Moved)
		{
			Axis_Moved_Event.Broadcast(ActionOwner, (uint8)Action, Value);
#if WITH_EDITOR
			Axis_Moved_ScriptEvent.Broadcast((uint8)Action, Value);
#endif // #if WITH_EDITOR
			return;
		}
		// FirstStationary
		if (Event == ECsInputEvent::FirstStationary)
		{
			Axis_FirstStationary_Event.Broadcast(ActionOwner, (uint8)Action, Value);
#if WITH_EDITOR
			Axis_FirstStationary_ScriptEvent.Broadcast((uint8)Action, Value);
#endif // #if WITH_EDITOR
			return;
		}
		// Stationary
		if (Event == ECsInputEvent::Stationary)
		{
			Axis_Stationary_Event.Broadcast(ActionOwner, (uint8)Action, Value);
#if WITH_EDITOR
			Axis_Stationary_ScriptEvent.Broadcast((uint8)Action, Value);
#endif // #if WITH_EDITOR
			return;
		}
		return;
	}
	// Location
	if (Infos[(uint8)Action]->Type == ECsInputType::Location)
	{
		Location_Event.Broadcast(ActionOwner, (uint8)Action, Event, Location);
#if WITH_EDITOR
		Location_ScriptEvent.Broadcast((uint8)Action, Event, Location);
#endif // #if WITH_EDITOR

		// FirstMoved
		if (Event == ECsInputEvent::FirstMoved)
		{
			Location_FirstMoved_Event.Broadcast(ActionOwner, (uint8)Action, Location);
#if WITH_EDITOR
			Location_FirstMoved_ScriptEvent.Broadcast((uint8)Action, Location);
#endif // #if WITH_EDITOR
			return;
		}
		// Moved
		if (Event == ECsInputEvent::Moved)
		{
			Location_Moved_Event.Broadcast(ActionOwner, (uint8)Action, Location);
#if WITH_EDITOR
			Location_Moved_ScriptEvent.Broadcast((uint8)Action, Location);
#endif // #if WITH_EDITOR
			return;
		}
		// FirstStationary
		if (Event == ECsInputEvent::FirstStationary)
		{
			Location_FirstStationary_Event.Broadcast(ActionOwner, (uint8)Action, Location);
#if WITH_EDITOR
			Location_FirstStationary_ScriptEvent.Broadcast((uint8)Action, Location);
#endif // #if WITH_EDITOR
			return;
		}
		// Stationary
		if (Event == ECsInputEvent::Stationary)
		{
			Location_Stationary_Event.Broadcast(ActionOwner, (uint8)Action, Location);
#if WITH_EDITOR
			Location_Stationary_ScriptEvent.Broadcast((uint8)Action, Location);
#endif // #if WITH_EDITOR
			return;
		}
		return;
	}
	// Rotation
	if (Infos[(uint8)Action]->Type == ECsInputType::Rotation)
	{
		Rotation_Event.Broadcast(ActionOwner, (uint8)Action, Event, Rotation);
#if WITH_EDITOR
		Rotation_ScriptEvent.Broadcast((uint8)Action, Event, Rotation);
#endif // #if WITH_EDITOR

		// FirstMoved
		if (Event == ECsInputEvent::FirstMoved)
		{
			Rotation_FirstMoved_Event.Broadcast(ActionOwner, (uint8)Action, Rotation);
#if WITH_EDITOR
			Rotation_FirstMoved_ScriptEvent.Broadcast((uint8)Action, Rotation);
#endif // #if WITH_EDITOR
			return;
		}
		// Moved
		if (Event == ECsInputEvent::Moved)
		{
			Rotation_Moved_Event.Broadcast(ActionOwner, (uint8)Action, Rotation);
#if WITH_EDITOR
			Rotation_Moved_ScriptEvent.Broadcast((uint8)Action, Rotation);
#endif // #if WITH_EDITOR
			return;
		}
		// FirstStationary
		if (Event == ECsInputEvent::FirstStationary)
		{
			Rotation_FirstStationary_Event.Broadcast(ActionOwner, (uint8)Action, Rotation);
#if WITH_EDITOR
			Rotation_FirstStationary_ScriptEvent.Broadcast((uint8)Action, Rotation);
#endif // #if WITH_EDITOR
			return;
		}
		// Stationary
		if (Event == ECsInputEvent::Stationary)
		{
			Rotation_Stationary_Event.Broadcast(ActionOwner, (uint8)Action, Rotation);
#if WITH_EDITOR
			Rotation_Stationary_ScriptEvent.Broadcast((uint8)Action, Rotation);
#endif // #if WITH_EDITOR
			return;
		}
		return;
	}
}

FCsInput* ACsManager_Input::AllocateInput(const TCsInputAction &Action, const TCsInputEvent &Event, const float &Value /*=0.0f*/, const FVector &Location /*=FVector::ZeroVector*/, const FRotator &Rotation /*=FRotator::ZeroRotator*/)
{
	// Get Input from Pool
	uint16 LastIndex = FMath::Min((int32)CurrentInputPoolIndex, (int32)CS_INPUT_POOL_SIZE);

	if (CurrentInputPoolIndex >= CS_INPUT_POOL_SIZE)
		CurrentInputPoolIndex = 0;

	for (int32 I = 0; I < CS_INPUT_POOL_SIZE; I++)
	{
		const uint16 Index = (I + LastIndex) % CS_INPUT_POOL_SIZE;
		CurrentInputPoolIndex++;

		FCsInput* Input = &InputPool[Index];

		if (Input->PoolIndex == CS_INVALID_INPUT_POOL_INDEX)
			Input->Init(Index);
		// Add Input to InputFrame
		if (!Input->IsAllocated)
		{
			Input->Allocate(Action, Event, Value, Location, Rotation);
			return Input;
		}
	}
	checkf(0, TEXT("ACsManager_Input::AllocateInput: Input Pool has been exhaused."))
	return nullptr;
}

void ACsManager_Input::AddInput(const TCsInputAction &Action, const TCsInputEvent &Event, const float &Value /*=0.0f*/, const FVector &Location /*=FVector::ZeroVector*/, const FRotator &Rotation /*=FRotator::ZeroRotator*/)
{
	FCsInput* Input = AllocateInput(Action, Event, Value, Location, Rotation);
	InputFrames[CurrentInputFrameIndex].Inputs.Add(Input);
}

void ACsManager_Input::QueueInput(const TCsInputAction &Action, const TCsInputEvent &Event, const float &Value /*=0.0f*/, const FVector &Location /*=FVector::ZeroVector*/, const FRotator &Rotation /*=FRotator::ZeroRotator*/)
{
	FCsInput* Input = AllocateInput(Action, Event, Value, Location, Rotation);

	QueuedInputsForNextFrame.Add(Input);
}

FCsInput* ACsManager_Input::GetPreviousInputAction(const TCsInputAction &Action)
{
	const int32 LastInputFrame = UCsCommon::Mod(CurrentInputFrameIndex - 1, CS_MAX_INPUT_FRAMES);
	FCsInput* Input			   = InputFrames[LastInputFrame].GetInput(Action);

	return Input;
}

FCsInput* ACsManager_Input::GetPreviousInputAction(const TCsInputAction &Action, const TCsInputEvent &Event)
{
	const int32 LastInputFrame = UCsCommon::Mod(CurrentInputFrameIndex - 1, CS_MAX_INPUT_FRAMES);
	FCsInput* Input			   = InputFrames[LastInputFrame].GetInput(Action, Event);

	return Input;
}

FCsInput* ACsManager_Input::GetPreviousInputAction(const TCsInputAction &Action, const TArray<TCsInputEvent> &Events)
{
	const int32 LastInputFrame = UCsCommon::Mod(CurrentInputFrameIndex - 1, CS_MAX_INPUT_FRAMES);
	FCsInput* Input			   = InputFrames[LastInputFrame].GetInput(Action, Events);

	return Input;
}

FCsInput* ACsManager_Input::GetPreviousPreviousInputAction(const TCsInputAction &Action)
{
	const int32 LastInputFrame = UCsCommon::Mod(CurrentInputFrameIndex - 2, CS_MAX_INPUT_FRAMES);
	FCsInput* Input = InputFrames[LastInputFrame].GetInput(Action);

	return Input;
}

void ACsManager_Input::DetermineGameEvents(const TArray<FCsInput*> &Inputs)
{
}

bool ACsManager_Input::HasActionEventOccured(const TCsInputAction &Action, const TCsInputEvent &Event)
{
	FCsInputFrame& InputFrame = InputFrames[CurrentInputFrameIndex];

	const int32 Count = InputFrame.Inputs.Num();

	for (int32 I = 0; I < Count; I++)
	{
		FCsInput* Input = InputFrame.Inputs[I];

		if (Input->Action == Action && Input->Event == Event)
			return true;
	}
	return false;
}

float ACsManager_Input::GetInputValue(const TCsInputAction &Action)
{
	FCsInputFrame& InputFrame = InputFrames[CurrentInputFrameIndex];

	const int32 Count = InputFrame.Inputs.Num();

	for (int32 I = 0; I < Count; I++)
	{
		FCsInput* Input = InputFrame.Inputs[I];

		if (Input->Action == Action)
			return Input->Value;
	}
	return 0.0f;
}

FVector ACsManager_Input::GetInputLocation(const TCsInputAction &Action)
{
	FCsInputFrame& InputFrame = InputFrames[CurrentInputFrameIndex];

	const int32 Count = InputFrame.Inputs.Num();

	for (int32 I = 0; I < Count; I++)
	{
		FCsInput* Input = InputFrame.Inputs[I];

		if (Input->Action == Action)
			return Input->Location;
	}
	return FVector::ZeroVector;
}

TCsInputEvent ACsManager_Input::GetInputEvent(const TCsInputAction& Action)
{
	FCsInputFrame& InputFrame = InputFrames[CurrentInputFrameIndex];

	const int32 Count = InputFrame.Inputs.Num();

	for (int32 I = 0; I < Count; I++)
	{
		FCsInput* Input = InputFrame.Inputs[I];

		if (Input->Action == Action)
			return Input->Event;
	}
	return ECsInputEvent::ECsInputEvent_MAX;
}

TEnumAsByte<ECsInputEvent::Type> ACsManager_Input::GetInputEvent_Script(const uint8& Action)
{
	return GetInputEvent((TCsInputAction)Action);
}

float ACsManager_Input::GetInputDuration(const TCsInputAction &Action)
{
	return Infos[(uint8)Action]->Duration;
}

#if WITH_EDITOR

// Editor Game
#pragma region

void ACsManager_Input::RunEditorGameBatchConsoleCommands_FirstPressed()
{
	OnRunEditorGameBatchConsoleCommands_FirstPressed_Event.Broadcast();
}

void ACsManager_Input::RunEditorGameJavascriptFile_FirstPressed()
{
	OnRunEditorGameJavascriptFile_FirstPressed_Event.Broadcast();
}

#pragma endregion Editor Game

#endif // #if WITH_EDITOR

// Actions
#pragma region

#pragma endregion Actions