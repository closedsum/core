// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsManager_Input.h"
#include "CsCore.h"

// CVar
#include "Managers/Input/CsCVars_Manager_Input.h"
// Library
#include "Library/CsLibrary_Common.h"
#include "Library/Load/CsLibrary_Load.h"
#include "Library/CsLibrary_Player.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Managers

// Player
#include "GameFramework/PlayerController.h"
//#include "Player/CsPlayerController.h"
//#include "Player/CsCheatManager.h"
#include "Engine/LocalPlayer.h"
// Input
#include "GameFramework/PlayerInput.h"
#include "../HeadMountedDisplay/Public/IMotionController.h"
#include "Managers/Input/CsInputListener.h"

// Cached
#pragma region

namespace NCsManagerInputCached
{
	namespace Str
	{
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Input, PostProcessInput);
	}
}

#pragma endregion Cached

UCsManager_Input::UCsManager_Input(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	// Owner
	OwnerAsController(nullptr),
	ControllerId(INDEX_NONE),
	OnPostProcessInput_Event(),
	CurrentDeltaTime(0.0f),
	Manager_Inputs(),
	QueuedInputsForNextFrame(),
	CurrentInputFrameIndex(0),
	CurrentInputFrame(nullptr),
	// Action Map
	InputActionEventInfos(),
	InputActionMapping(),
	CurrentInputActionMap(0),
	PressedKeys(),
	// Events
	GameEventDefinitions(),
	InputSentenceByGameEventMap(),
	GameEventPriorityList(),
	GameEventPriorityMap(),
	QueuedGameEventInfosForNextFrame(),
	CurrentGameEventInfos(),
	CurrentValidGameEventInfos(),
	bOnGameEventInfo(true),
	OnGameEventInfo_Event(),
	// Listener
	Listeners(),
	// Profile
	InputProfile(),
	AllKeys(),
	// Actions
	Infos(),
	Actions(),
	Last_Actions(),
	// Location Events
		// Mouse
	CurrentMousePosition(FVector::ZeroVector)
{
}

void UCsManager_Input::Init() 
{
	EKeys::GetAllKeys(AllKeys);

	UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

	const FCsSettings_Manager_Input& ManagerSettings = Settings->Manager_Input;

	Manager_Inputs.CreatePool(ManagerSettings.InputPoolSize);

	SetupInputActionEventInfos();
	SetupInputActionMapping();
	SetupGameEventDefinitions();

	const FCsSettings_Input& InputSettings = Settings->Input;

	// Initialize CurrentGameEventInfos
	const int32 EventCount = EMCsGameEvent::Get().Num();

	TArray<bool> EventsFound;

	EventsFound.Reset(EventCount);
	EventsFound.AddDefaulted(EventCount);

	for (int32 I = 0; I < EventCount; ++I)
	{
		EventsFound[I] = false;
	}

	for (const FECsGameEvent& Event : InputSettings.GameEventPriorityList)
	{
		EventsFound[Event.GetValue()] = true;

		GameEventPriorityList.Add(Event);
	}

	for (int32 I = 0; I < EventCount; ++I)
	{
		if (!EventsFound[I])
		{
			GameEventPriorityList.Add(EMCsGameEvent::Get().GetEnumAt(I));
		}
	}

	// Update GameEventPriorityMap
	CurrentGameEventInfos.Reset(EventCount);
	GameEventPriorityMap.Reset(EventCount);
	GameEventPriorityMap.AddDefaulted(EventCount);

	for (int32 I = 0; I < EventCount; ++I)
	{
		CurrentGameEventInfos.AddDefaulted();
		CurrentGameEventInfos.Last().Reset();

		const FECsGameEvent& Event = GameEventPriorityList[I];

		GameEventPriorityMap[Event.GetValue()] = I;
	}
}

// UObject Interface
#pragma region

void UCsManager_Input::BeginDestroy()
{
	Super::BeginDestroy();

	for (UCsInputListener* Listener : Listeners)
	{
		if (Listener &&
			!Listener->IsPendingKill())
		{
			Listener->MarkPendingKill();
		}
	}
	Listeners.Reset();
}

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region

void UCsManager_Input::OnRegister()
{
	Super::OnRegister();

	OwnerAsController = Cast<APlayerController>(GetOwner());
	
	Init();
}

#pragma endregion UActorComponent Interface

/*
void UCsManager_Input::SetupInputComponent()
{
	if (!InputComponent)
	{
		InputComponent = NewObject<UInputComponent>(this, TEXT("InputComponent"));
		InputComponent->RegisterComponent();
	}
#if WITH_EDITOR
// Editor Game

	// RunEditorGameBatchConsoleCommands
	InputComponent->BindAction("RunEditorGameBatchConsoleCommands", IE_Pressed, this, &UCsManager_Input::RunEditorGameBatchConsoleCommands_FirstPressed).bConsumeInput = false;
	// RunEditorGameJavascriptFile
	InputComponent->BindAction("RunEditorGameJavascriptFile", IE_Pressed, this, &UCsManager_Input::RunEditorGameJavascriptFile_FirstPressed).bConsumeInput = false;

	UCsCheatManager* CheatManager   = Cast<UCsCheatManager>(OwnerAsController->CheatManager);

	OnRunEditorGameBatchConsoleCommands_FirstPressed_Event.AddUObject(CheatManager, &UCsCheatManager::RunEditorGameBatchConsoleCommands);
	OnRunEditorGameJavascriptFile_FirstPressed_Event.AddUObject(CheatManager, &UCsCheatManager::RunEditorGameJavascriptFile);

#endif // #if WITH_EDITOR
}
*/

void UCsManager_Input::PreProcessInput(const float DeltaTime, const bool bGamePaused)
{
	// Update Event "state" for Actions
	for (const FECsInputAction& Action : EMCsInputAction::Get())
	{
		FCsInputInfo& Info	 = InputActionEventInfos[Action.GetValue()];
		ECsInputEvent& Event = Info.Event;

		const ECsInputType& Type = Info.Type;

		// Action
		if (Type == ECsInputType::Action)
		{
			// FirstPressed -> Pressed
			if (Event == ECsInputEvent::FirstPressed)
			{
				Event = ECsInputEvent::Pressed;
			}
			// FirstReleased -> Released
			else
			if (Event == ECsInputEvent::FirstReleased)
			{
				Event = ECsInputEvent::Released;
			}
		}
	}
}

void UCsManager_Input::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	using namespace NCsManagerInputCached;

	const FString& Context = Str::PostProcessInput;

	// Capture Mouse Inputs
	if (OwnerAsController->bShowMouseCursor)
	{
		// Default__MousePositionXY__
		{
			CurrentMousePosition = FVector::ZeroVector;
			
			if (OwnerAsController->GetMousePosition(CurrentMousePosition.X, CurrentMousePosition.Y))
			{
				FCsInputInfo& Info = InputActionEventInfos[NCsInputAction::Default__MousePositionXY__.GetValue()];

				ECsInputEvent& Event = Info.Event;

				Info.Last_Location = Info.Location;

				// Change
				if (Info.Location != CurrentMousePosition)
				{
					// FirstStationary | Stationary -> FirstMoved
					if (Event == ECsInputEvent::FirstStationary ||
						Event == ECsInputEvent::Stationary)
					{
						Event = ECsInputEvent::FirstMoved;
					}
					// FirstMoved -> Moved
					else
					if (Event == ECsInputEvent::FirstMoved)
					{
						Event = ECsInputEvent::Moved;
					}
				}
				// No Change
				else
				{
					// FirstMoved | Moved -> FirstStationary
					if (Event == ECsInputEvent::FirstMoved ||
						Event == ECsInputEvent::Moved)
					{
						Event = ECsInputEvent::FirstStationary;
					}
					// FirstStationary -> Stationary
					else
					if (Event == ECsInputEvent::FirstStationary)
					{
						Event = ECsInputEvent::Stationary;
					}
				}

				Info.Location = CurrentMousePosition;
			}
		}
		// Default__MouseLeftButton__
		{
			FCsInputInfo& Info = InputActionEventInfos[NCsInputAction::Default__MouseLeftButton__.GetValue()];

			const ECsInputEvent& Last_Event = Info.Last_Event;

			// FirstReleased | Released -> FirstPressed
			if (OwnerAsController->PlayerInput->IsPressed(EKeys::LeftMouseButton))
			{
				if (Last_Event == ECsInputEvent::FirstReleased ||
					Last_Event == ECsInputEvent::Released)
				{
					Info.Event = ECsInputEvent::FirstPressed;
				}
			}
			// FirstPressed | Pressed -> FirstReleased
			else
			{
				if (Last_Event == ECsInputEvent::FirstPressed ||
					Last_Event == ECsInputEvent::Pressed)
				{
					Info.Event = ECsInputEvent::FirstReleased;
				}
			}
		}
		// Default__MouseRightButton__
		{
			FCsInputInfo& Info = InputActionEventInfos[NCsInputAction::Default__MouseRightButton__.GetValue()];

			const ECsInputEvent& Last_Event = Info.Last_Event;

			// FirstReleased | Released -> FirstPressed
			if (OwnerAsController->PlayerInput->IsPressed(EKeys::RightMouseButton))
			{
				if (Last_Event == ECsInputEvent::FirstReleased ||
					Last_Event == ECsInputEvent::Released)
				{
					Info.Event = ECsInputEvent::FirstPressed;
				}
			}
			// FirstPressed | Pressed -> FirstReleased
			else
			{
				if (Last_Event == ECsInputEvent::FirstPressed ||
					Last_Event == ECsInputEvent::Pressed)
				{
					Info.Event = ECsInputEvent::FirstReleased;
				}
			}
		}
	}

	/*
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Controller->Player);

	if (LocalPlayer && LocalPlayer->ViewportClient)
	{
		FVector2D MousePosition;

		const bool bGotMousePosition = LocalPlayer->ViewportClient->GetMousePosition(MousePosition);
		
		Mouse_Location_Raw.ExecuteIfBound(FVector(MousePosition.X, MousePosition.Y, 0.0f));
	}
	*/

	// Capture VR related Input
	const bool IsVR = UCsLibrary_Common::IsVR();

	if (IsVR)
	{
		FRotator Rotation;
		FVector Location;

		UCsLibrary_Common::GetHMDOrientationAndPosition(Rotation, Location);

		//HMD_Rotation_Raw.ExecuteIfBound(Rotation);
		//HMD_Location_Raw.ExecuteIfBound(Location);
	}

	TArray<IMotionController*> Controllers = IModularFeatures::Get().GetModularFeatureImplementations<IMotionController>(IMotionController::GetModularFeatureName());

	for (IMotionController* Controller : Controllers)
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
		if (Controller->GetControllerOrientationAndPosition(LocalPlayerIndex, EMCsControllerHand::Get().ToName(ECsControllerHand::Left), Rotation, Location, WorldToMetersScale))
		{
		//	LeftHand_Rotation_Raw.ExecuteIfBound(Rotation);
		//	LeftHand_Location_Raw.ExecuteIfBound(Location);
		}
		// Right
		if (Controller->GetControllerOrientationAndPosition(LocalPlayerIndex, EMCsControllerHand::Get().ToName(ECsControllerHand::Right), Rotation, Location, WorldToMetersScale))
		{
		//	RightHand_Rotation_Raw.ExecuteIfBound(Rotation);
		//	RightHand_Location_Raw.ExecuteIfBound(Location);
		}
	}

	// Handle any Inputs that need to deallocated
	TCsDoubleLinkedList<FCsResource_Input*>* Current = Manager_Inputs.GetAllocatedHead();
	TCsDoubleLinkedList<FCsResource_Input*>* Next	 = Current;

	while (Next)
	{
		Current						 = Next;
		FCsResource_Input* Container = **Current;
		Next						 = Current->GetNextLink();

		FCsInput* Input = Container->Get();

		if (Input->ShouldDeallocate())
		{
			Input->Reset();
			Manager_Inputs.Deallocate(Container);
		}
	}

	// Setup Current InputFrame
	CurrentDeltaTime	   = DeltaTime;
	CurrentInputFrameIndex = (CurrentInputFrameIndex + 1) % CS_MAX_INPUT_FRAMES;
	CurrentInputFrame	   = &(InputFrames[CurrentInputFrameIndex]);

	{
		FCsTime Time;
		Time.Time = GetWorld()->GetTimeSeconds();
		Time.RealTime = GetWorld()->GetRealTimeSeconds();
		Time.Frame = 0ull;

		CurrentInputFrame->Init(Time);
	}

	for (const FECsInputAction& Action : EMCsInputAction::Get())
	{
		FCsInputInfo& Info	 = InputActionEventInfos[Action.GetValue()];
		ECsInputEvent& Event = Info.Event;

		const ECsInputType& Type = Info.Type;

		// Action
		if (Type == ECsInputType::Action)
		{
#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogInputRaw) ||
				FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogInputRawAction))
			{
				const float& Time			= CurrentInputFrame->Time.Time;
				const FString& CurrentEvent = EMCsInputEvent::Get().ToString(Info.Event);

				if (Info.HasEventChanged())
				{
					const FString& LastEvent = EMCsInputEvent::Get().ToString(Info.Last_Event);

					UE_LOG(LogCs, Warning, TEXT("%s (%s): Time: %f. Action: %s. Event: %s -> %s."), *Context, *(GetOwner()->GetName()), Time, Action.ToChar(), *LastEvent, *CurrentEvent);
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("%s (%s): Time: %f. Action: %s. Event: %s."), *Context, *(GetOwner()->GetName()), Time, Action.ToChar(), *CurrentEvent);
				}
			}
#endif // #if !UE_BUILD_SHIPPING	

			TryAddInput(Type, Action, Event);

			Info.FlushEvent();
		}
		// Axis
		else
		if (Type == ECsInputType::Axis)
		{
			float Value = Info.Value;

#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogInputRaw) ||
				FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogInputRawAxis))
			{
				const float& Time			= CurrentInputFrame->Time.Time;
				const FString& CurrentEvent = EMCsInputEvent::Get().ToString(Info.Event);

				if (Info.HasEventChanged())
				{
					const FString& LastEvent = EMCsInputEvent::Get().ToString(Info.Last_Event);

					UE_LOG(LogCs, Warning, TEXT("%s (%s): Time: %f. Action: %s. Event: %s -> %s. Value: %f -> %f."), *Context, *(GetOwner()->GetName()), Time, Action.ToChar(), *LastEvent, *CurrentEvent, Info.Last_Value, Value);
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("%s (%s): Time: %f. Action: %s. Event: %s. Value: %f."), *Context, *(GetOwner()->GetName()), Time, Action.ToChar(), *CurrentEvent, Value);
				}
			}
#endif // #if !UE_BUILD_SHIPPING

			TryAddInput(Type, Action, Event, Value);

			Info.FlushEvent();
		}
		// Location
		else
		if (Type == ECsInputType::Location)
		{
			const FVector& Location = Info.Location;

#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogInputRaw) ||
				FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogInputLocation))
			{
				const float& Time			= CurrentInputFrame->Time.Time;
				const FString& CurrentEvent = EMCsInputEvent::Get().ToString(Info.Event);

				if (Info.HasEventChanged())
				{
					const FString& LastEvent   = EMCsInputEvent::Get().ToString(Info.Last_Event);
					const FString LastLocation = Info.Last_Location.ToString();

					UE_LOG(LogCs, Warning, TEXT("%s (%s): Time: %f. Action: %s. Event: %s -> %s. Location: %s -> %s."), *Context, *(GetOwner()->GetName()), Time, Action.ToChar(), *LastEvent, *CurrentEvent, *LastLocation, *(Location.ToString()));
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("%s (%s): Time: %f. Action: %s. Event: %s. Location: %s."), *Context, *(GetOwner()->GetName()), Time, Action.ToChar(), *CurrentEvent, *(Location.ToString()));
				}
			}
#endif // #if !UE_BUILD_SHIPPING

			TryAddInput(Type, Action, Event, 0.0f, Info.Location);

			Info.FlushEvent();
		}
	}

	// Add Queue Inputs
	for (FCsInput* Input : QueuedInputsForNextFrame)
	{
		CurrentInputFrame->Inputs.Add(Input);
	}
	QueuedInputsForNextFrame.Reset(QueuedInputsForNextFrame.Max());

	// TODO: Need to rework how events are being fired. Not just firing from TryAddInput

#if !UE_BUILD_SHIPPING
	for (const FCsInput* Input : CurrentInputFrame->Inputs)
	{
		const FECsInputAction& Action = Input->Action;
		const ECsInputEvent& Event	  = Input->Event;
		const FCsInputInfo& Info	  = InputActionEventInfos[Action.GetValue()];
		const ECsInputType& Type	  = Info.Type;

		const bool ShowLog = FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogInput) ||
							(Type == ECsInputType::Action && FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogInputAction)) ||
							(Type == ECsInputType::Axis && FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogInputAxis));

		if (ShowLog)
		{
			const float& Time			 = CurrentInputFrame->Time.Time;
			const FString& EventAsString = EMCsInputEvent::Get().ToString(Input->Event);

			UE_LOG(LogCs, Warning, TEXT("%s (%s): Time: %f. Action: %s Event: %s."), *Context, *(GetOwner()->GetName()), Time, Action.ToChar(), *EventAsString);
		}
	}
#endif // #if !UE_BUILD_SHIPPING

	// Reset CurrentGameEventInfos
	for (FCsGameEventInfo& Info : CurrentGameEventInfos)
	{
		Info.Reset();
	}
	CurrentValidGameEventInfos.Reset(CurrentValidGameEventInfos.Max());

	// Process GameEventDefinitions
	for (FCsGameEventDefinition& Def : GameEventDefinitions)
	{
		const FECsGameEvent& Event = Def.Event;
		FCsInputSentence& Sentence = Def.Sentence;

		Sentence.ProcessInput(CurrentInputFrame);

		if (Sentence.IsCompleted())
		{
			const int32& Index					= GameEventPriorityMap[Event.GetValue()];
			CurrentGameEventInfos[Index].Event  = Event;

			CurrentGameEventInfos[Index].SetDefinition(&Def);

			// TODO: FUTURE: Handle multiple values. Only handle the FIRST value.
			const TArray<FCsInputCompletedValue>& CompletedValues = Sentence.GetCompletedValues();
			const FCsInputCompletedValue& CompletedValue		  = CompletedValues[CS_FIRST];
			
			CurrentGameEventInfos[Index].ApplyInputCompletedValue(CompletedValue);

#if !UE_BUILD_SHIPPING
			LogProcessGameEventDefinition(Context, Event, Sentence);
#endif // #if !UE_BUILD_SHIPPING
		}
	}

	// Process Queue GameEvents
	for (const FCsGameEventInfo& Info : QueuedGameEventInfosForNextFrame)
	{
		const FECsGameEvent& Event  = Info.Event;
		const int32& Index			= GameEventPriorityMap[Event.GetValue()];

		CurrentGameEventInfos[Index] = Info;
	}
	QueuedGameEventInfosForNextFrame.Reset(QueuedGameEventInfosForNextFrame.Max());

	for (FCsGameEventInfo& Info : CurrentGameEventInfos)
	{
		if (Info.IsValid())
		{
			const FECsGameEvent& Event = Info.Event;

			// For "default" mouse related pressed events, also add the position information

			// Default__MouseLeftButtonPressed__ | Default__MouseRightButtonPressed__
			if (Event == NCsGameEvent::Default__MouseLeftButtonPressed__ ||
				Event == NCsGameEvent::Default__MouseRightButtonPressed__)
			{
				const int32& Index							= GameEventPriorityMap[NCsGameEvent::Default__MousePositionXY__.GetValue()];
				const FCsGameEventInfo& MousePositionXYInfo = CurrentGameEventInfos[Index];

				if (MousePositionXYInfo.IsValid())
				{
					Info.Location = MousePositionXYInfo.Location;
				}
			}

			CurrentValidGameEventInfos.Add(Info);

#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogInputGameEvent))
			{
				const float& Time = CurrentInputFrame->Time.Time;

				UE_LOG(LogCs, Warning, TEXT("%s (%s): Time: %f. Event: %s."), *Context, *(GetOwner()->GetName()), Time, Info.Event.ToChar());
			}
#endif // #if !UE_BUILD_SHIPPING

			OnGameEventInfo_Event.Broadcast(Info);
		}
	}

	if (CurrentValidGameEventInfos.Num() > CS_EMPTY)
		OnGameEventInfos_Event.Broadcast(CurrentValidGameEventInfos);

	OnPostProcessInput_Event.Broadcast(DeltaTime, bGamePaused);
}

FCsInput* UCsManager_Input::AllocateInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value /*=0.0f*/, const FVector& Location /*=FVector::ZeroVector*/, const FRotator& Rotation /*=FRotator::ZeroRotator*/)
{
	FCsInput* Input = Manager_Inputs.AllocateResource();

	Input->Set(Action, Event, Value, Location, Rotation);

	return Input;
}

void UCsManager_Input::AddInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value /*=0.0f*/, const FVector& Location /*=FVector::ZeroVector*/, const FRotator& Rotation /*=FRotator::ZeroRotator*/)
{
	FCsInput* Input = AllocateInput(Action, Event, Value, Location, Rotation);
	InputFrames[CurrentInputFrameIndex].Inputs.Add(Input);
}

bool UCsManager_Input::CanAddInput(const FECsInputAction& Action)
{
	if (int32* Mask = InputActionMapping.Find(Action))
	{
		return (CurrentInputActionMap & *Mask) > 0;
	}
	return false;
}

bool UCsManager_Input::TryAddInput(const ECsInputType& Type, const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value /*= 0.0f*/, const FVector& Location /*= FVector::ZeroVector*/, const FRotator& Rotation /*= FRotator::ZeroRotator*/)
{
	if (CanAddInput(Action))
	{
		const ECsInputEvent& OutEvent = ProcessInputEvent(Type, Action, Event, Value, Location, Rotation);

		AddInput(Action, OutEvent, Value, Location, Rotation);
		return true;
	}
	return false;
}

const ECsInputEvent& UCsManager_Input::ProcessInputEvent(const ECsInputType& Type, const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value, const FVector& Location, const FRotator& Rotation)
{
	return Event;
}

void UCsManager_Input::QueueInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value /*=0.0f*/, const FVector& Location /*=FVector::ZeroVector*/, const FRotator& Rotation /*=FRotator::ZeroRotator*/)
{
	FCsInput* Input = AllocateInput(Action, Event, Value, Location, Rotation);

	QueuedInputsForNextFrame.Add(Input);
}

void UCsManager_Input::ConsumeInput(const FECsInputAction& Action)
{
	FCsInputFrame& InputFrame = InputFrames[CurrentInputFrameIndex];

	for (FCsInput* Input : InputFrame.Inputs)
	{
		if (Input->Action == Action)
		{
			Input->bConsumed = true;
			break;
		}
	}
}

// Action Map
#pragma region

void UCsManager_Input::SetupInputActionEventInfos()
{
	UPlayerInput* PlayerInput = OwnerAsController->PlayerInput;

	const int32& ActionCount = EMCsInputAction::Get().Num();

	InputActionEventInfos.Reset(ActionCount);
	InputActionEventInfos.AddDefaulted(ActionCount);
	Listeners.Reset(ActionCount);
	Listeners.AddDefaulted(ActionCount);

	for (const FECsInputAction& Action : EMCsInputAction::Get())
	{
		FCsInputInfo& Info = InputActionEventInfos[Action.GetValue()];

		// Ignore creating listener for "default" mouse related actions

		// Default__MousePositionXY__
		if (Action == NCsInputAction::Default__MousePositionXY__)
		{
			Info.Type		= ECsInputType::Location;
			Info.ValueType	= ECsInputValue::Vector;
			Info.Event		= ECsInputEvent::Stationary;
			Info.Last_Event = ECsInputEvent::Stationary;
			continue;
		}
		// Default__MouseLeftButton__
		if (Action == NCsInputAction::Default__MouseLeftButton__)
		{
			Info.Type		= ECsInputType::Action;
			Info.ValueType	= ECsInputValue::Void;
			Info.Event		= ECsInputEvent::Released;
			Info.Last_Event = ECsInputEvent::Released;
			continue;
		}
		// Default__MouseRightButton__
		if (Action == NCsInputAction::Default__MouseRightButton__)
		{
			Info.Type		= ECsInputType::Action;
			Info.ValueType	= ECsInputValue::Void;
			Info.Event		= ECsInputEvent::Released;
			Info.Last_Event = ECsInputEvent::Released;
			continue;
		}

		Listeners[Action.GetValue()] = NewObject<UCsInputListener>(this);

		// Check Actions
		for (const FInputActionKeyMapping& Mapping : PlayerInput->ActionMappings)
		{
			if (Action.GetFName() == Mapping.ActionName)
			{
				if (Info.IsValid())
					continue;

				Listeners[Action.GetValue()]->Init(Action, ECsInputType::Action, this);

				Info.Type		 = ECsInputType::Action;
				Info.ValueType	 = ECsInputValue::Void;
				Info.Event		 = ECsInputEvent::Released;
				Info.Last_Event  = ECsInputEvent::Released;
			}
		}

		// Check Axis
		for (const FInputAxisKeyMapping& Mapping : PlayerInput->AxisMappings)
		{
			if (Action.GetFName() == Mapping.AxisName)
			{
				if (Info.IsValid())
					continue;

				Listeners[Action.GetValue()]->Init(Action, ECsInputType::Axis, this);

				Info.Type		 = ECsInputType::Axis;
				Info.ValueType	 = ECsInputValue::Float;
				Info.Event		 = ECsInputEvent::Stationary;
				Info.Last_Event	 = ECsInputEvent::Stationary;
			}
		}
	}
}

void UCsManager_Input::SetupInputActionMapping()
{
	UCsDeveloperSettings* Settings		   = GetMutableDefault<UCsDeveloperSettings>();
	const FCsSettings_Input& InputSettings = Settings->Input;

	const TMap<FECsInputActionMap, FCsInputActionSet>& InputActionMappings = InputSettings.InputActionMappings;

	for (const FECsInputActionMap& Map : EMCsInputActionMap::Get())
	{
		const int32& Mask			 = Map.Mask;
		const FCsInputActionSet& Set = InputActionMappings[Map];

		// Initialize InputActionMapping
		for (const FECsInputAction& Action : Set.Actions)
		{
			if (InputActionMapping.Find(Action))
			{
				InputActionMapping[Action] |= Mask;
			}
			else
			{
				InputActionMapping.Add(Action, Mask);
			}
		}
	}
}

/*
void UCsManager_Input::SetInputActionMappingByMap(FECsInputActionMap Map)
{
	CurrentInputActionMap |= 1 << static_cast<int32>(Map);
}
*/

void UCsManager_Input::SetCurrentInputActionMap(const FECsInputActionMap& Map)
{
	CS_SET_BITFLAG(CurrentInputActionMap, Map.Mask);
}

void UCsManager_Input::SetCurrentInputActionMap(const int32& Map)
{
	CS_SET_BITFLAG(CurrentInputActionMap, Map);
}

void UCsManager_Input::ClearCurrentInputActionMap(const FECsInputActionMap& Map)
{
	CS_CLEAR_BITFLAG(CurrentInputActionMap, Map.Mask);
}

void UCsManager_Input::ClearCurrentInputActionMap(const int32& Map)
{
	CS_CLEAR_BITFLAG(CurrentInputActionMap, Map);
}

#pragma endregion Action Map

FCsInput* UCsManager_Input::GetPreviousInputAction(const FECsInputAction& Action)
{
	const int32 LastInputFrame = UCsLibrary_Common::Mod(CurrentInputFrameIndex - 1, CS_MAX_INPUT_FRAMES);
	FCsInput* Input			   = InputFrames[LastInputFrame].GetInput(Action);

	return Input;
}

FCsInput* UCsManager_Input::GetPreviousInputAction(const FECsInputAction& Action, const ECsInputEvent& Event)
{
	const int32 LastInputFrame = UCsLibrary_Common::Mod(CurrentInputFrameIndex - 1, CS_MAX_INPUT_FRAMES);
	FCsInput* Input			   = InputFrames[LastInputFrame].GetInput(Action, Event);

	return Input;
}

FCsInput* UCsManager_Input::GetPreviousInputAction(const FECsInputAction& Action, const TArray<ECsInputEvent>& Events)
{
	const int32 LastInputFrame = UCsLibrary_Common::Mod(CurrentInputFrameIndex - 1, CS_MAX_INPUT_FRAMES);
	FCsInput* Input			   = InputFrames[LastInputFrame].GetInput(Action, Events);

	return Input;
}

FCsInput* UCsManager_Input::GetPreviousPreviousInputAction(const FECsInputAction& Action)
{
	const int32 LastInputFrame = UCsLibrary_Common::Mod(CurrentInputFrameIndex - 2, CS_MAX_INPUT_FRAMES);
	FCsInput* Input			   = InputFrames[LastInputFrame].GetInput(Action);

	return Input;
}

// Events
#pragma region

void UCsManager_Input::SetupGameEventDefinitions()
{
	UCsDeveloperSettings* Settings		   = GetMutableDefault<UCsDeveloperSettings>();
	const FCsSettings_Input& InputSettings = Settings->Input;

	for (const FCsGameEventDefinition& Def : InputSettings.GameEventDefinitions)
	{
		GameEventDefinitions.Add(Def);
	}

	for (const FCsGameEventDefinition& Def : GameEventDefinitions)
	{
		const FECsGameEvent& Event = Def.Event;

		if (!Def.IsValid())
		{
#if WITH_EDITOR
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Input::SetupGameEventDefinitions (%s): GameEventDefinition set with GameEvent: %s is NOT Valid. Check the Sentence."), *(GetOwner()->GetName()), Event.ToChar());
#endif // #if WITH_EDITOR
			continue;
		}

		const FCsInputSentence& Sentence = Def.Sentence;

		InputSentenceByGameEventMap.Add(Event, Sentence);
	}

	const TSet<FCsGameEventDefinitionSimple>& GameEventDefinitionsSimple = InputSettings.GameEventDefinitionsSimple;

	for (const FCsGameEventDefinitionSimple& Def : GameEventDefinitionsSimple)
	{
		const FECsGameEvent& GameEvent = Def.GameEvent;
		const FECsInputAction& Action  = Def.Action;
		const ECsInputEvent& Event     = Def.Event;

		if (!Def.IsValid())
		{
#if WITH_EDITOR
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Input::SetupGameEventDefinitions (%s): GameEventDefinitionSimple set with GameEvent: %s is NOT Valid. Action: %s. Event: %s"), *(GetOwner()->GetName()), GameEvent.ToChar(), Action.ToChar(), EMCsInputEvent::Get().ToChar(Event));
#endif // #if WITH_EDITOR
			continue;
		}

		if (InputSentenceByGameEventMap.Find(GameEvent))
		{
#if WITH_EDITOR
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Input::SetupGameEventDefinitions (%s): GameEventDefinitionSimple set with GameEvent: %s is already Set in GameEventDefinitions."), *(GetOwner()->GetName()), GameEvent.ToChar());
#endif // #if WITH_EDITOR
			continue;
		}

		FCsInputSentence Sentence;
		Sentence.Reset();
		Sentence.Phrases.AddDefaulted();
		Sentence.Phrases[CS_FIRST].AddAndInputToWord(CS_FIRST, Action, Event);

		InputSentenceByGameEventMap.Add(GameEvent, Sentence);

		FCsGameEventDefinition GameEventDefinition;
		GameEventDefinition.Event	 = GameEvent;
		GameEventDefinition.Sentence = Sentence;

		GameEventDefinitions.Add(GameEventDefinition);
	}

	// Setup default game events for "default" mouse related actions

	// Default__MousePositionXY__
	{
		const FECsGameEvent& Event = NCsGameEvent::Default__MousePositionXY__;

		if (!InputSentenceByGameEventMap.Find(Event))
		{
			FCsGameEventDefinition Def;
			Def.Event = Event;

			Def.Sentence.Phrases.AddDefaulted();
			FCsInputSentence& Sentence = Def.Sentence;
			FCsInputPhrase& Phrase = Sentence.Phrases[CS_FIRST];
			Phrase.Words.AddDefaulted();
			FCsInputWord& Word = Phrase.Words[CS_FIRST];
			Word.AndInputs.AddDefaulted();
			FCsInputDescription& Desc = Word.AndInputs[CS_FIRST];
			Desc.Action = NCsInputAction::Default__MousePositionXY__;
			Desc.bAnyEvent = true;
			Desc.CompareValue.ValueType = ECsInputValue::Vector;
			Desc.CompletedValue.ValueType = ECsInputValue::Vector;
			Desc.CompletedValue.ReturnType = ECsInputCompletedValueReturnType::PassThrough;

			InputSentenceByGameEventMap.Add(Event, Sentence);
			GameEventDefinitions.Add(Def);
		} 
	}
	// Default__MouseLeftButtonPressed__
	{
		const FECsGameEvent& Event = NCsGameEvent::Default__MouseLeftButtonPressed__;

		if (!InputSentenceByGameEventMap.Find(Event))
		{
			FCsGameEventDefinition Def;
			Def.Event = Event;

			Def.Sentence.Phrases.AddDefaulted();
			FCsInputSentence& Sentence = Def.Sentence;
			FCsInputPhrase& Phrase = Sentence.Phrases[CS_FIRST];
			Phrase.Words.AddDefaulted();
			FCsInputWord& Word = Phrase.Words[CS_FIRST];
			Word.AndInputs.AddDefaulted();
			FCsInputDescription& Desc = Word.AndInputs[CS_FIRST];
			Desc.Action = NCsInputAction::Default__MouseLeftButton__;
			Desc.Event = ECsInputEvent::FirstPressed;
			Desc.CompareValue.ValueType = ECsInputValue::Void;
			Desc.CompletedValue.ValueType = ECsInputValue::Void;

			InputSentenceByGameEventMap.Add(Event, Sentence);
			GameEventDefinitions.Add(Def);
		}
	}
	// Default__MouseRightButtonPressed__
	{
		const FECsGameEvent& Event = NCsGameEvent::Default__MouseRightButtonPressed__;

		if (!InputSentenceByGameEventMap.Find(Event))
		{
			FCsGameEventDefinition Def;
			Def.Event = Event;

			Def.Sentence.Phrases.AddDefaulted();
			FCsInputSentence& Sentence = Def.Sentence;
			FCsInputPhrase& Phrase = Sentence.Phrases[CS_FIRST];
			Phrase.Words.AddDefaulted();
			FCsInputWord& Word = Phrase.Words[CS_FIRST];
			Word.AndInputs.AddDefaulted();
			FCsInputDescription& Desc = Word.AndInputs[CS_FIRST];
			Desc.Action = NCsInputAction::Default__MouseRightButton__;
			Desc.Event = ECsInputEvent::FirstPressed;
			Desc.CompareValue.ValueType = ECsInputValue::Void;
			Desc.CompletedValue.ValueType = ECsInputValue::Void;

			InputSentenceByGameEventMap.Add(Event, Sentence);
			GameEventDefinitions.Add(Def);
		}
	}


#if WITH_EDITOR
	for (const FECsGameEvent& Event : EMCsGameEvent::Get())
	{
		if (!InputSentenceByGameEventMap.Find(Event))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Input::SetupGameEventDefinitions (%s): No GameEventDefinition set for GameEvent: %s."), *(GetOwner()->GetName()), Event.ToChar());
		}
	}
#endif // #if WITH_EDITOR
}

void UCsManager_Input::LogProcessGameEventDefinition(const FString& Context, const FECsGameEvent& Event, const FCsInputSentence& Sentence)
{
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogInputGameEventDefinition))
	{
		// For now handle a simple definition

		if (Sentence.Phrases.Num() > CS_EMPTY &&
			Sentence.Phrases[CS_FIRST].Words.Num() > CS_EMPTY &&
			Sentence.Phrases[CS_FIRST].Words[CS_FIRST].AndInputs.Num() > CS_EMPTY)
		{
			const FCsInputDescription& Input  = Sentence.Phrases[CS_FIRST].Words[CS_FIRST].AndInputs[CS_FIRST];
			const FECsInputAction& Action	  = Input.Action;
			const FString& InputEventAsString = EMCsInputEvent::Get().ToString(Input.Event);

			const float& Time = CurrentInputFrame->Time.Time;

			UE_LOG(LogCs, Warning, TEXT("%s (%s): Time: %f. (%s, %s) -> %s."), *Context, *(GetOwner()->GetName()), Time, Action.ToChar(), *InputEventAsString, Event.ToChar());
		}
	}
}

void UCsManager_Input::QueueGameEvent(const FECsGameEvent& Event)
{
	QueuedGameEventInfosForNextFrame.AddDefaulted();
	QueuedGameEventInfosForNextFrame.Last().Event = Event;
}

void UCsManager_Input::ClearQueuedGameEvents()
{
	QueuedGameEventInfosForNextFrame.Reset(QueuedGameEventInfosForNextFrame.Max());
}

bool UCsManager_Input::HasActionEventOccured(const FECsInputAction& Action, const ECsInputEvent& Event)
{
	FCsInputFrame& InputFrame = InputFrames[CurrentInputFrameIndex];

	for (FCsInput* Input : InputFrame.Inputs)
	{
		if (Input->Action == Action && Input->Event == Event)
			return true;
	}
	return false;
}

#pragma endregion Events

float UCsManager_Input::GetInputValue(const FECsInputAction& Action)
{
	FCsInputFrame& InputFrame = InputFrames[CurrentInputFrameIndex];

	for (FCsInput* Input : InputFrame.Inputs)
	{
		if (Input->Action == Action)
			return Input->Value;
	}
	return 0.0f;
}

FVector UCsManager_Input::GetInputLocation(const FECsInputAction& Action)
{
	FCsInputFrame& InputFrame = InputFrames[CurrentInputFrameIndex];

	for (FCsInput* Input : InputFrame.Inputs)
	{
		if (Input->Action == Action)
			return Input->Location;
	}
	return FVector::ZeroVector;
}

ECsInputEvent UCsManager_Input::GetInputEvent(const FECsInputAction& Action)
{
	FCsInputFrame& InputFrame = InputFrames[CurrentInputFrameIndex];

	for (FCsInput* Input : InputFrame.Inputs)
	{
		if (Input->Action == Action)
			return Input->Event;
	}
	return ECsInputEvent::ECsInputEvent_MAX;
}

float UCsManager_Input::GetInputDuration(const FECsInputAction& Action)
{
	return Infos[Action.Value]->Duration;
}

// Listener
#pragma region

void UCsManager_Input::OnAction_Pressed(const FECsInputAction& Action)
{
	FCsInputInfo& Info   = InputActionEventInfos[Action.GetValue()];
	ECsInputEvent& Event = Info.Event;

	Event = ECsInputEvent::FirstPressed;
}

void UCsManager_Input::OnAction_Released(const FECsInputAction& Action)
{
	FCsInputInfo& Info	 = InputActionEventInfos[Action.GetValue()];
	ECsInputEvent& Event = Info.Event;

	Event = ECsInputEvent::FirstReleased;
}

void UCsManager_Input::OnAxis(const FECsInputAction& Action, const float& Value)
{
	FCsInputInfo& Info   = InputActionEventInfos[Action.GetValue()];
	ECsInputEvent& Event = Info.Event;

	Info.Last_Value = Info.Value;

	// Change
	if (Info.Value != Value)
	{
		// FirstStationary | Stationary -> FirstMoved
		if (Event == ECsInputEvent::FirstStationary ||
			Event == ECsInputEvent::Stationary)
		{
			Event = ECsInputEvent::FirstMoved;
		}
		// FirstMoved -> Moved
		else
		if (Event == ECsInputEvent::FirstMoved)
		{
			Event = ECsInputEvent::Moved;
		}
	}
	// No Change
	else
	{
		// FirstMoved | Moved -> FirstStationary
		if (Event == ECsInputEvent::FirstMoved ||
			Event == ECsInputEvent::Moved)
		{
			Event = ECsInputEvent::FirstStationary;
		}
		// FirstStationary -> Stationary
		else
		if (Event == ECsInputEvent::FirstStationary)
		{
			Event = ECsInputEvent::Stationary;
		}
	}
	Info.Value = Value;
}

#pragma endregion Listener

// Profile
#pragma region

bool UCsManager_Input::CanSaveInputActionMapping(const ECsInputDevice& Device, const FECsInputAction& Action)
{
	return true;
}

FString UCsManager_Input::GetSavePath()
{
	return FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir()) + TEXT("/");
}

FString UCsManager_Input::GetInputProfileFilenameAndPath()
{
	return GetSavePath() + TEXT("InputProfile") + FString::FromInt(ControllerId) + TEXT(".json");
}

void UCsManager_Input::SaveInputProfile()
{
	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);

	JsonWriter->WriteObjectStart();

	//UCsLibrary_Load::WriteStructToJson(JsonWriter, (void*)(&InputProfile), FCsInputProfile::StaticStruct(), nullptr);

	JsonWriter->WriteObjectEnd();

	JsonWriter->Close();

	const FString Filename = GetInputProfileFilenameAndPath();

	FFileHelper::SaveStringToFile(OutputString, *Filename);
}

void UCsManager_Input::LoadDefaultInputProfile()
{
	InputProfile.Reset();

	UPlayerInput* PlayerInput = OwnerAsController->PlayerInput;

	// ActionMappings
	const int32 ActionCount = PlayerInput->ActionMappings.Num();

	for (int32 I = 0; I < ActionCount; ++I)
	{
		FInputActionKeyMapping& Mapping = PlayerInput->ActionMappings[I];

		if (!EMCsInputAction::Get().IsValidEnum(Mapping.ActionName))
			continue;

		const FECsInputAction& Action = EMCsInputAction::Get()[Mapping.ActionName];
		const FKey& Key				  = Mapping.Key;
		const FString KeyName		  = Key.GetDisplayName().ToString();

		// MouseAndKeyboard
		if (CanSaveInputActionMapping(ECsInputDevice::MouseAndKeyboard, Action) &&
			IsValidKey(ECsInputDevice::MouseAndKeyboard, Key))
		{
			InputProfile.AddMapping(ECsInputDevice::MouseAndKeyboard, Action, KeyName, Key);
		}
		// Gamepad
		if (CanSaveInputActionMapping(ECsInputDevice::Gamepad, Action) &&
			IsValidKey(ECsInputDevice::Gamepad, Key))
		{
			InputProfile.AddMapping(ECsInputDevice::Gamepad, Action, KeyName, Key);
		}
	}
	// AxisMappings
	const int32 AxisCount = PlayerInput->AxisMappings.Num();

	for (int32 I = 0; I < AxisCount; ++I)
	{
		FInputAxisKeyMapping& Mapping = PlayerInput->AxisMappings[I];

		if (!EMCsInputAction::Get().IsValidEnum(Mapping.AxisName))
			continue;

		const FECsInputAction& Action = EMCsInputAction::Get()[Mapping.AxisName];
		const FKey& Key				  = Mapping.Key;
		const FString KeyName		  = Key.GetDisplayName().ToString();

		// MouseAndKeyboard
		if (CanSaveInputActionMapping(ECsInputDevice::MouseAndKeyboard, Action) &&
			IsValidKey(ECsInputDevice::MouseAndKeyboard, Key))
		{
			InputProfile.AddMapping(ECsInputDevice::MouseAndKeyboard, Action, KeyName, Key);
		}
		// Gamepad
		if (CanSaveInputActionMapping(ECsInputDevice::Gamepad, Action) &&
			IsValidKey(ECsInputDevice::Gamepad, Key))
		{
			InputProfile.AddMapping(ECsInputDevice::Gamepad, Action, KeyName, Key);
		}
	}
}

void UCsManager_Input::LoadInputProfile()
{
	const FString InputProfileFilename = GetInputProfileFilenameAndPath();

	FString DataJson;

	if (FFileHelper::LoadFileToString(DataJson, *InputProfileFilename))
	{
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(DataJson);

		TSharedPtr<FJsonObject> JsonParsed;

		if (FJsonSerializer::Deserialize(JsonReader, JsonParsed) && JsonParsed.IsValid())
		{
			//UCsLibrary_Load::ReadStructFromJson(JsonParsed, &InputProfile, FCsInputProfile::StaticStruct(), nullptr);

			// Update Action and Key members

			for (FCsInputActionMappings& DeviceMapping : InputProfile.DeviceMappings)
			{
				TArray<FCsInputActionMapping>& Mappings = DeviceMapping.Mappings;

				for (FCsInputActionMapping& Mapping : Mappings)
				{
					Mapping.Key	= GetKey(Mapping.KeyName);
				}
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Input::LoadInputProfile: %s is NOT Valid"), *InputProfileFilename);
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Input::LoadInputProfile: %s NOT found. Loading Default Input Profile."), *InputProfileFilename);

		LoadDefaultInputProfile();
	}
}

bool UCsManager_Input::IsValidKey(const ECsInputDevice& Device, const FKey& Key)
{
	if (Key == EKeys::Invalid)
		return false;

	// MouseAndKeyboard
	if (Device == ECsInputDevice::MouseAndKeyboard)
	{
		if (Key.IsGamepadKey())
			return false;
		if (Key == EKeys::MouseX || Key == EKeys::MouseY)
			return false;
	}
	// Gamepad
	if (Device == ECsInputDevice::Gamepad)
	{
		if (!Key.IsGamepadKey())
			return false;
	}
	return true;
}

const FKey& UCsManager_Input::GetKey(const FString& KeyName)
{
	if (KeyName == NCsCached::Str::Empty)
		return EKeys::Invalid;

	const int32 KeyCount = AllKeys.Num();

	for (int32 I = 1; I < KeyCount; ++I)
	{
		const FKey& Key = AllKeys[I];

		if (KeyName == Key.GetDisplayName().ToString())
			return Key;
	}
	return EKeys::Invalid;
}

const FECsInputAction& UCsManager_Input::GetActionFromKey(const ECsInputDevice& Device, const FKey& Key)
{
	FCsInputActionMappings& DeviceMapping   = InputProfile.DeviceMappings[(uint8)Device];
	TArray<FCsInputActionMapping>& Mappings = DeviceMapping.Mappings;

	for (FCsInputActionMapping& Mapping : Mappings)
	{
		if (Mapping.Key == Key)
			return Mapping.Action;
	}
	return EMCsInputAction::Get().GetMAX();
}

const FKey& UCsManager_Input::GetKeyFromAction(const ECsInputDevice& Device, const FECsInputAction& Action)
{
	FCsInputActionMappings& DeviceMapping   = InputProfile.DeviceMappings[(uint8)Device];
	TArray<FCsInputActionMapping>& Mappings = DeviceMapping.Mappings;

	for (FCsInputActionMapping& Mapping : Mappings)
	{
		if (Mapping.Action == Action)
			return Mapping.Key;
	}
	return EKeys::Invalid;
}

const FKey& UCsManager_Input::GetKeyFromAction(const FECsInputAction& Action)
{
	UPlayerInput* PlayerInput = FCsLibrary_Player::GetFirstLocalPlayerInput(GetWorld());

	const FString& ActionAsString = Action.GetName();
	const FName& ActionName		  = Action.GetFName();

	for (FInputActionKeyMapping& Mapping : PlayerInput->ActionMappings)
	{
		if (ActionName == Mapping.ActionName)
			return Mapping.Key;
	}

	for (FInputAxisKeyMapping& Mapping : PlayerInput->AxisMappings)
	{
		if (ActionName == Mapping.AxisName)
			return Mapping.Key;
	}
	return EKeys::Invalid;
}

void UCsManager_Input::UnbindActionMapping(const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key)
{
	UPlayerInput* PlayerInput = OwnerAsController->PlayerInput;

	const FName& ActionName = Action.GetFName();
	// Remove binding from PlayerInput ActionMapping
	const int32 MappingCount = PlayerInput->ActionMappings.Num();

	for (int32 I = MappingCount - 1; I >= 0; --I)
	{
		FInputActionKeyMapping& Mapping = PlayerInput->ActionMappings[I];

		if (ActionName == Mapping.ActionName &&
			Key == Mapping.Key)
		{
			PlayerInput->ActionMappings.RemoveAt(I);
			break;
		}
	}
	// Clear Key on Mapping from InputProfile
	FCsInputActionMappings& DeviceMapping  = InputProfile.DeviceMappings[(uint8)Device];
	TArray<FCsInputActionMapping>& Mappings = DeviceMapping.Mappings;

	const int32 Count = Mappings.Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
		FCsInputActionMapping& Mapping = Mappings[I];

		if (Action == Mapping.Action &&
			Key == Mapping.Key)
		{
			Mapping.KeyName = NCsCached::Str::Empty;
			Mapping.Key		= EKeys::Invalid;
			break;
		}
	}
	PlayerInput->ForceRebuildingKeyMaps(false);
}

void UCsManager_Input::UnbindAxisMapping(const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key)
{
	UPlayerInput* PlayerInput = OwnerAsController->PlayerInput;

	const FName& ActionName = Action.GetFName();
	// Remove binding from PlayerInput ActionMapping
	const int32 MappingCount = PlayerInput->AxisMappings.Num();

	for (int32 I = MappingCount - 1; I >= 0; --I)
	{
		FInputAxisKeyMapping& Mapping = PlayerInput->AxisMappings[I];

		if (ActionName == Mapping.AxisName &&
			Key == Mapping.Key)
		{
			PlayerInput->AxisMappings.RemoveAt(I);
			break;
		}
	}
	// Clear Key on Mapping from InputProfile
	FCsInputActionMappings& DeviceMapping   = InputProfile.DeviceMappings[(uint8)Device];
	TArray<FCsInputActionMapping>& Mappings = DeviceMapping.Mappings;

	const int32 Count = Mappings.Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
		FCsInputActionMapping& Mapping = Mappings[I];

		if (Action == Mapping.Action &&
			Key == Mapping.Key)
		{
			Mapping.KeyName = NCsCached::Str::Empty;
			Mapping.Key = EKeys::Invalid;
			break;
		}
	}
	PlayerInput->ForceRebuildingKeyMaps(false);
}

void UCsManager_Input::UnbindMapping(const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key)
{
	if (Infos[Action.Value]->Type == ECsInputType::Action)
		UnbindActionMapping(Device, Action, Key);
	if (Infos[Action.Value]->Type == ECsInputType::Axis)
		UnbindAxisMapping(Device, Action, Key);
}

// TODO: Need to store the original Key "Keyboard" mappings for Input. Do similar for control setup

void UCsManager_Input::RebindActionMapping(const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key)
{
	if (!IsValidKey(Device, Key))
		return;

	UPlayerInput* PlayerInput = OwnerAsController->PlayerInput;
	
	FCsInputActionMapping& Mapping = InputProfile.GetMapping(Device, Action);
	const FKey PreviousKey		   = Mapping.Key;

	// If it is the SAME Key, Do Nothing
	if (Key == PreviousKey)
		return;
	
	// Check if another Action is already mapped to the Key
	const FECsInputAction OtherAction = GetActionFromKey(Device, Key);

	// Unbind ActionMapping for OtherAction bound to Key
	if (OtherAction != EMCsInputAction::Get().GetMAX())
	{
		UnbindMapping(Device, OtherAction, Key);
	}

	const FName& ActionName = Action.GetFName();

	bool Found = false;

	for (FInputActionKeyMapping& ActionMapping : PlayerInput->ActionMappings)
	{
		if (ActionName == ActionMapping.ActionName &&
			PreviousKey == ActionMapping.Key)
		{
			ActionMapping.Key = Key;
			Found = true;
			break;
		}
	}
	// Add Mapping if it is NOT found
	if (!Found)
	{
		PlayerInput->ActionMappings.AddDefaulted();

		const int32 Count = PlayerInput->ActionMappings.Num();

		FInputActionKeyMapping& ActionMapping = PlayerInput->ActionMappings[Count];
		ActionMapping.ActionName			  = Action.GetFName();
		ActionMapping.Key					  = Mapping.Key;
	}

	InputProfile.SetKey(Device, Action, Key);

	PlayerInput->ForceRebuildingKeyMaps(false);
}

void UCsManager_Input::RebindAxisMapping(const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key)
{
	if (!IsValidKey(Device, Key))
		return;

	UPlayerInput* PlayerInput = OwnerAsController->PlayerInput;

	FCsInputActionMapping& Mapping = InputProfile.GetMapping(Device, Action);
	const FKey PreviousKey		   = Mapping.Key;

	// If it is the SAME Key, Do Nothing
	if (Key == PreviousKey)
		return;

	// Check if another Action is already mapped to the Key
	const FECsInputAction& OtherAction = GetActionFromKey(Device, Key);

	// Unbind ActionMapping for OtherAction bound to Key
	if (OtherAction != EMCsInputAction::Get().GetMAX())
	{
		UnbindMapping(Device, OtherAction, Key);
	}

	const FName& ActionName = Action.GetFName();
	
	bool Found = false;

	for (FInputAxisKeyMapping& AxisMapping : PlayerInput->AxisMappings)
	{
		if (ActionName == AxisMapping.AxisName &&
			PreviousKey == AxisMapping.Key)
		{
			AxisMapping.Key = Key;
			Found = true;
			break;
		}
	}
	// Add Mapping if it is NOT found
	if (!Found)
	{
		PlayerInput->AxisMappings.AddDefaulted();

		const int32 Count = PlayerInput->AxisMappings.Num();

		FInputAxisKeyMapping& AxisMapping = PlayerInput->AxisMappings[Count];
		AxisMapping.AxisName			  = Action.GetFName();
		AxisMapping.Key					  = Mapping.Key;
		AxisMapping.Scale				  = Mapping.Scale;
	}
	InputProfile.SetKey(Device, Action, Key);

	PlayerInput->ForceRebuildingKeyMaps(false);
}

void UCsManager_Input::RebindMapping(const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key)
{
	if (Infos[Action.Value]->Type == ECsInputType::Action)
		RebindActionMapping(Device, Action, Key);
	if (Infos[Action.Value]->Type == ECsInputType::Axis)
		RebindAxisMapping(Device, Action, Key);
}

#pragma endregion Profile

#if WITH_EDITOR

// Editor Game
#pragma region

void UCsManager_Input::RunEditorGameBatchConsoleCommands_FirstPressed()
{
	OnRunEditorGameBatchConsoleCommands_FirstPressed_Event.Broadcast();
}

void UCsManager_Input::RunEditorGameJavascriptFile_FirstPressed()
{
	OnRunEditorGameJavascriptFile_FirstPressed_Event.Broadcast();
}

#pragma endregion Editor Game

#endif // #if WITH_EDITOR

// Actions
#pragma region

#pragma endregion Actions

// Game Events
#pragma region

void UCsManager_Input::CreateGameEventDefinitionSimple(TArray<FCsGameEventDefinition>& Definitions, const FECsGameEvent& GameEvent, const FECsInputAction& Action, const ECsInputEvent& Event)
{
	Definitions.AddDefaulted();
	FCsGameEventDefinition& Def = Definitions[Definitions.Num() - 1];
	Def.Event = GameEvent;
	// Sentence
	{
		FCsInputSentence& Sentence = Def.Sentence;
		Sentence.Phrases.AddDefaulted();
		// Phrase
		{
			FCsInputPhrase& Phrase = Sentence.Phrases[Sentence.Phrases.Num() - 1];
			Phrase.Words.AddDefaulted();
			// Word
			{
				FCsInputWord& Word = Phrase.Words[Phrase.Words.Num() - 1];
				Word.AddOrInput(Action, Event);
			}
		}
	}
}

#pragma endregion Game Events