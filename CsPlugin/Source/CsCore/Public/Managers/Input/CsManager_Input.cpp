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

namespace NCsManagerInput
{
	namespace NCached
	{
		namespace Str
		{
			CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Input, SetCurrentInputActionMap);
			CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Input, ClearCurrentInputActionMap);

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Input, PostProcessInput);
		}
	}

	namespace NCurrentMode
	{
		namespace NCached
		{
			namespace Str
			{
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Input::FCurrentMode, SetValue);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Input::FCurrentMode, ClearValue);
			}
		}
	}

	namespace NActiveMode
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Input::FActiveMode, OnPostProcessInput);
			}
		}
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
	// Actions
	Infos(),
	Actions(),
	Last_Actions(),
	// Location Events
		// Mouse
	CurrentMousePosition(FVector::ZeroVector),
	// Touch
	TouchActions(),
	// Mode
	CurrentMode(),
	ActiveMode(),
	// Profile
	InputProfile(),
	AllKeys()
{
}

void UCsManager_Input::Init() 
{
	CurrentMode.Outer = this;
	ActiveMode.Outer = this;

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

	for (const FECsGameEvent& Event : InputSettings.GameEventPriorityList_Internal)
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
	ActiveMode.ResetValue();

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
	using namespace NCsManagerInput::NCached;

	const FString& Context = Str::PostProcessInput;

	// Capture Mouse Inputs
	OnPostProcessInput_CaptureMouseInput(DeltaTime, bGamePaused);

	// Capture VR related Input
	OnPostProcessInput_CaptureVRInput();

	// Handle any changes to ActiveMode
	ActiveMode.OnPostProcessInput(DeltaTime, bGamePaused);

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
		Time.Time	  = GetWorld()->GetTimeSeconds();
		Time.RealTime = GetWorld()->GetRealTimeSeconds();
		Time.Frame	  = 0ull;

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
			CS_NON_SHIPPING_EXPR(OnPostProcessInput_LogInputAction(Action));

			TryAddInput(Type, Action, Event, Info.Value, Info.Location);

			Info.FlushEvent();
		}
		// Axis
		else
		if (Type == ECsInputType::Axis)
		{
			CS_NON_SHIPPING_EXPR(OnPostProcessInput_LogInputAxis(Action));

			float Value = Info.Value;

			TryAddInput(Type, Action, Event, Value, Info.Location);

			Info.FlushEvent();
		}
		// Location
		else
		if (Type == ECsInputType::Location)
		{
			CS_NON_SHIPPING_EXPR(OnPostProcessInput_LogInputLocation(Action));

			const FVector& Location = Info.Location;

			TryAddInput(Type, Action, Event, Info.Value, Info.Location);

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

	CS_NON_SHIPPING_EXPR(OnPostProcessInput_LogCurrentInputFrame());

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

			// TODO: FUTURE: Handle multiple values properly. Multiple MAY STOMP over each other.
			const TArray<FCsInputCompletedValue>& CompletedValues = Sentence.GetCompletedValues();

			for (const FCsInputCompletedValue& CompletedValue : CompletedValues)
			{
				CurrentGameEventInfos[Index].ApplyInputCompletedValue(CompletedValue);
			}
			CS_NON_SHIPPING_EXPR(LogProcessGameEventDefinition(Context, Event, Sentence));
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

			CS_NON_SHIPPING_EXPR(OnPostProcessInput_LogGameEventInfo(Info));

			OnGameEventInfo_Event.Broadcast(Info);
		}
	}

	if (CurrentValidGameEventInfos.Num() > CS_EMPTY)
		OnGameEventInfos_Event.Broadcast(CurrentValidGameEventInfos);

	OnPostProcessInput_Event.Broadcast(DeltaTime, bGamePaused);
}

void UCsManager_Input::OnPostProcessInput_CaptureMouseInput(const float& DeltaTime, const bool bGamePaused)
{
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

			Info.ResetLocation();

			const ECsInputEvent& Last_Event = Info.Last_Event;

			// FirstReleased | Released -> FirstPressed
			if (OwnerAsController->PlayerInput->IsPressed(EKeys::LeftMouseButton))
			{
				if (Last_Event == ECsInputEvent::FirstReleased ||
					Last_Event == ECsInputEvent::Released)
				{
					Info.Event	  = ECsInputEvent::FirstPressed;
					Info.Location = CurrentMousePosition;
				}
			}
			// FirstPressed | Pressed -> FirstReleased
			else
			{
				if (Last_Event == ECsInputEvent::FirstPressed ||
					Last_Event == ECsInputEvent::Pressed)
				{
					Info.Event	  = ECsInputEvent::FirstReleased;
					Info.Location = CurrentMousePosition;
				}
			}
		}
		// Default__MouseRightButton__
		{
			FCsInputInfo& Info = InputActionEventInfos[NCsInputAction::Default__MouseRightButton__.GetValue()];

			Info.ResetLocation();

			const ECsInputEvent& Last_Event = Info.Last_Event;

			// FirstReleased | Released -> FirstPressed
			if (OwnerAsController->PlayerInput->IsPressed(EKeys::RightMouseButton))
			{
				if (Last_Event == ECsInputEvent::FirstReleased ||
					Last_Event == ECsInputEvent::Released)
				{
					Info.Event	  = ECsInputEvent::FirstPressed;
					Info.Location = CurrentMousePosition;
				}
			}
			// FirstPressed | Pressed -> FirstReleased
			else
			{
				if (Last_Event == ECsInputEvent::FirstPressed ||
					Last_Event == ECsInputEvent::Pressed)
				{
					Info.Event	  = ECsInputEvent::FirstReleased;
					Info.Location = CurrentMousePosition;
				}
			}
		}
	}
}

void UCsManager_Input::OnPostProcessInput_CaptureVRInput()
{
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
}

void UCsManager_Input::OnPostProcessInput_LogInputAction(const FECsInputAction& Action)
{
	using namespace NCsManagerInput::NCached;

	const FString& Context = Str::PostProcessInput;

	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogInputRaw) ||
		FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogInputRawAction))
	{
		FCsInputInfo& Info = InputActionEventInfos[Action.GetValue()];

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
}

void UCsManager_Input::OnPostProcessInput_LogInputAxis(const FECsInputAction& Action)
{
	using namespace NCsManagerInput::NCached;

	const FString& Context = Str::PostProcessInput;

	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogInputRaw) ||
		FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogInputRawAxis))
	{
		FCsInputInfo& Info = InputActionEventInfos[Action.GetValue()];

		float Value					= Info.Value;
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
}

void UCsManager_Input::OnPostProcessInput_LogInputLocation(const FECsInputAction& Action)
{
	using namespace NCsManagerInput::NCached;

	const FString& Context = Str::PostProcessInput;

	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogInputRaw) ||
		FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogInputLocation))
	{
		FCsInputInfo& Info = InputActionEventInfos[Action.GetValue()];

		const FVector& Location		= Info.Location;
		const float& Time			= CurrentInputFrame->Time.Time;
		const FString& CurrentEvent = EMCsInputEvent::Get().ToString(Info.Event);

		if (Info.HasEventChanged())
		{
			const FString& LastEvent = EMCsInputEvent::Get().ToString(Info.Last_Event);
			const FString LastLocation = Info.Last_Location.ToString();

			UE_LOG(LogCs, Warning, TEXT("%s (%s): Time: %f. Action: %s. Event: %s -> %s. Location: %s -> %s."), *Context, *(GetOwner()->GetName()), Time, Action.ToChar(), *LastEvent, *CurrentEvent, *LastLocation, *(Location.ToString()));
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s (%s): Time: %f. Action: %s. Event: %s. Location: %s."), *Context, *(GetOwner()->GetName()), Time, Action.ToChar(), *CurrentEvent, *(Location.ToString()));
		}
	}
}

void UCsManager_Input::OnPostProcessInput_LogCurrentInputFrame()
{
	using namespace NCsManagerInput::NCached;

	const FString& Context = Str::PostProcessInput;

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
}

void UCsManager_Input::OnPostProcessInput_LogGameEventInfo(const FCsGameEventInfo& Info)
{
	using namespace NCsManagerInput::NCached;

	const FString& Context = Str::PostProcessInput;

	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogInputGameEvent))
	{
		const float& Time = CurrentInputFrame->Time.Time;

		UE_LOG(LogCs, Warning, TEXT("%s (%s): Time: %f. Event: %s."), *Context, *(GetOwner()->GetName()), Time, Info.Event.ToChar());
	}
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

	// Touch
	{
		const int32 Count = EKeys::NUM_TOUCH_KEYS - 1;

		// Add Action Mappings for Touch Events (Pressed / Released)
		TArray<FInputActionKeyMapping> ActionKeyMappings;
		ActionKeyMappings.Reset(Count);
		ActionKeyMappings.AddDefaulted(Count);

		TouchActions.Reset(Count);
		TouchActions.Add(NCsInputAction::Default__Touch_0__);
		TouchActions.Add(NCsInputAction::Default__Touch_1__);
		TouchActions.Add(NCsInputAction::Default__Touch_2__);
		TouchActions.Add(NCsInputAction::Default__Touch_3__);
		TouchActions.Add(NCsInputAction::Default__Touch_4__);
		TouchActions.Add(NCsInputAction::Default__Touch_5__);
		TouchActions.Add(NCsInputAction::Default__Touch_6__);
		TouchActions.Add(NCsInputAction::Default__Touch_7__);
		TouchActions.Add(NCsInputAction::Default__Touch_8__);
		TouchActions.Add(NCsInputAction::Default__Touch_9__);

		for (int32 I = 0; I < Count; ++I)
		{
			FInputActionKeyMapping& Mapping = ActionKeyMappings[I];
			const FECsInputAction& Action   = TouchActions[I];

			Mapping.ActionName = Action.GetFName();
			Mapping.Key		   = EKeys::TouchKeys[I];

			PlayerInput->AddActionMapping(Mapping);
		}

		UInputComponent* InputComponent = OwnerAsController->InputComponent;

		// Pressed
		{
			FInputTouchBinding& Binding = InputComponent->BindTouch<UCsManager_Input>(EInputEvent::IE_Pressed, this, &UCsManager_Input::OnTouchAction_Pressed);
			Binding.bConsumeInput		= false;
		}
		// Released
		{
			FInputTouchBinding& Binding = InputComponent->BindTouch<UCsManager_Input>(EInputEvent::IE_Released, this, &UCsManager_Input::OnTouchAction_Pressed);
			Binding.bConsumeInput		= false;
		}
	}

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
			//Info.Key		= EKeys::MouseX;
			//Info.Key		= EKeys::MouseY;
			continue;
		}
		// Default__MouseLeftButton__
		if (Action == NCsInputAction::Default__MouseLeftButton__)
		{
			Info.Type		= ECsInputType::Action;
			Info.ValueType	= ECsInputValue::Void;
			Info.Event		= ECsInputEvent::Released;
			Info.Last_Event = ECsInputEvent::Released;
			Info.Key		= EKeys::LeftMouseButton;
			continue;
		}
		// Default__MouseRightButton__
		if (Action == NCsInputAction::Default__MouseRightButton__)
		{
			Info.Type		= ECsInputType::Action;
			Info.ValueType	= ECsInputValue::Void;
			Info.Event		= ECsInputEvent::Released;
			Info.Last_Event = ECsInputEvent::Released;
			Info.Key		= EKeys::RightMouseButton;
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

		// HACK: TODO: Investigate and fox
		{
			FCsInputActionSet& FixSet = const_cast<FCsInputActionSet&>(Set);
			FixSet.ConditionalRebuild();
		}

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
	// Populate GameEventDefinitions
	UCsDeveloperSettings* Settings		   = GetMutableDefault<UCsDeveloperSettings>();
	const FCsSettings_Input& InputSettings = Settings->Input;

	for (const FCsGameEventDefinition& Def : InputSettings.GameEventDefinitions)
	{
		GameEventDefinitions.Add(Def);
	}

	for (const FCsGameEventDefinition& Def : GameEventDefinitions)
	{
		const FECsGameEvent& Event = Def.Event;

		checkf(Def.IsValid(), TEXT("UCsManager_Input::SetupGameEventDefinitions (%s): GameEventDefinition set with GameEvent: %s is NOT Valid. Check the Sentence."), *(GetOwner()->GetName()), Event.ToChar());

		const FCsInputSentence& Sentence = Def.Sentence;

		InputSentenceByGameEventMap.Add(Event, Sentence);
	}

	// GameEventDefinitions_ActionOneOrWordNoCompleteValue
	{
		typedef FCsGameEventDefinitionActionOneOrWordNoCompletedValue DefinitionType;

		for (const DefinitionType& Def : InputSettings.GameEventDefinitions_ActionOneOrWordNoCompleteValue)
		{
			Def.AddDefinition(GameEventDefinitions, InputSentenceByGameEventMap);
		}
	}
	//GameEventDefinitions_AxisOneOrWordNoComparePassThroughValue
	{
		typedef FCsGameEventDefinitionAxisOneOrWordNoComparePassThroughValue DefinitionType;

		for (const DefinitionType& Def : InputSettings.GameEventDefinitions_AxisOneOrWordNoComparePassThroughValue)
		{
			Def.AddDefinition(GameEventDefinitions, InputSentenceByGameEventMap);
		}
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

void UCsManager_Input::OnAction_Pressed(const FECsInputAction& Action, const FKey& Key)
{
	FCsInputInfo& Info   = InputActionEventInfos[Action.GetValue()];
	ECsInputEvent& Event = Info.Event;

	Event = ECsInputEvent::FirstPressed;

	Info.Key = Key;
}

void UCsManager_Input::OnAction_Released(const FECsInputAction& Action, const FKey& Key)
{
	FCsInputInfo& Info	 = InputActionEventInfos[Action.GetValue()];
	ECsInputEvent& Event = Info.Event;

	Event = ECsInputEvent::FirstReleased;
}

void UCsManager_Input::OnTouchAction_Pressed(ETouchIndex::Type Index, FVector Location)
{
	const FECsInputAction& Action = TouchActions[(uint8)Index];

	FCsInputInfo& Info   = InputActionEventInfos[Action.GetValue()];
	ECsInputEvent& Event = Info.Event;

	Info.ResetLocation();

	Info.Location = Location;

	Event = ECsInputEvent::FirstPressed;
}

void UCsManager_Input::OnTouchAction_Released(ETouchIndex::Type Index, FVector Location)
{
	const FECsInputAction& Action = TouchActions[(uint8)Index];

	FCsInputInfo& Info	 = InputActionEventInfos[Action.GetValue()];
	ECsInputEvent& Event = Info.Event;

	Info.ResetLocation();

	Info.Location = Location;

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

// Mode
#pragma region

	// Current
#pragma region

void UCsManager_Input::FCurrentMode::SetValue(const FString& Context, const ECsInputMode& Mode)
{
	Last_Value = Value;

	CS_SET_BLUEPRINT_BITFLAG(Value, Mode);

	if (Last_Value != Value)
		OnChange_Event.Broadcast(Last_Value, Value);
}

void UCsManager_Input::FCurrentMode::SetValue(const FString& Context, const int32& Mode)
{
	checkf(Mode >= 0, TEXT("%s: Mode: %s is NOT Valid."), *Context, Mode);

	Last_Value = Value;

	CS_SET_BLUEPRINT_BITFLAG(Value, Mode);

	if (Last_Value != Value)
		OnChange_Event.Broadcast(Last_Value, Value);
}

void UCsManager_Input::FCurrentMode::ClearValue(const FString& Context, const ECsInputMode& Mode)
{
	Last_Value = Value;

	CS_CLEAR_BLUEPRINT_BITFLAG(Value, Mode);

	if (Last_Value != Value)
		OnChange_Event.Broadcast(Last_Value, Value);
}

void UCsManager_Input::FCurrentMode::ClearValue(const FString& Context, const int32& Mode)
{
	checkf(Mode >= 0, TEXT("%s: Mode: %s is NOT Valid."), *Context, Mode);

	Last_Value = Value;

	CS_CLEAR_BLUEPRINT_BITFLAG(Value, Mode);

	if (Last_Value != Value)
		OnChange_Event.Broadcast(Last_Value, Value);
}

#pragma endregion Current

	// Active
#pragma region

void UCsManager_Input::FActiveMode::OnPostProcessInput(const float& DeltaTime, const bool bGamePaused)
{
	using namespace NCsManagerInput::NActiveMode::NCached;

	const FString& Context = Str::OnPostProcessInput;

	const TArray<FCsInputInfo>& _Infos = Outer->GetInputActionEventInfos();

	for (const FECsInputAction& Action : EMCsInputAction::Get())
	{
		const FCsInputInfo& Info   = _Infos[Action.GetValue()];
		const ECsInputEvent& Event = Info.Event;
		const FKey& Key			   = Info.Key;

		const ECsInputType& Type = Info.Type;

		// Action
		if (Type == ECsInputType::Action)
		{
			if (Event == ECsInputEvent::FirstPressed ||
				Event == ECsInputEvent::FirstReleased)
			{
				// Mouse
				if (Key.IsMouseButton())
				{
					CS_NON_SHIPPING_EXPR(PrintSet(Context, Action, Info, ECsInputMode::Mouse));
					CS_SET_BLUEPRINT_BITFLAG(Value, ECsInputMode::Mouse);
				}
				// Gamepad
				else
				if (Key.IsGamepadKey())
				{
					CS_NON_SHIPPING_EXPR(PrintSet(Context, Action, Info, ECsInputMode::Gamepad));
					CS_SET_BLUEPRINT_BITFLAG(Value, ECsInputMode::Gamepad);
				}
				// Touch
				else
				if (Key.IsTouch())
				{
					CS_NON_SHIPPING_EXPR(PrintSet(Context, Action, Info, ECsInputMode::Touch));
					CS_SET_BLUEPRINT_BITFLAG(Value, ECsInputMode::Touch);
				}
				// Keyboard - DEFAULT
				else
				if (Key != EKeys::AnyKey)
				{
					CS_NON_SHIPPING_EXPR(PrintSet(Context, Action, Info, ECsInputMode::Keyboard));
					CS_SET_BLUEPRINT_BITFLAG(Value, ECsInputMode::Keyboard);
				}
			}
		}
		// Axis TODO: Handle Properly
		else
		if (Type == ECsInputType::Axis)
		{
			if (Event == ECsInputEvent::FirstMoved ||
				Event == ECsInputEvent::Moved)
			{
			}
		}
		// Location
		else
		if (Type == ECsInputType::Location)
		{
			if (Event == ECsInputEvent::FirstMoved ||
				Event == ECsInputEvent::Moved)
			{
				if (Action == NCsInputAction::Default__MousePositionXY__)
				{
					CS_NON_SHIPPING_EXPR(PrintSet(Context, Action, Info, ECsInputMode::Mouse));
					CS_SET_BLUEPRINT_BITFLAG(Value, ECsInputMode::Mouse);
				}
			}
		}
	}

	if (Value != Last_Value)
	{
		CS_NON_SHIPPING_EXPR(PrintSummary(Context));
		OnChange_Event.Broadcast(Last_Value, Value);
	}

	Last_Value = Value;
}

void UCsManager_Input::FActiveMode::PrintSet(const FString& Context, const FECsInputAction& Action, const FCsInputInfo& Info, const ECsInputMode& Mode)
{
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogInputActiveMode))
	{
		const ECsInputType& Type   = Info.Type;
		const ECsInputEvent& Event = Info.Event;
		const FKey& Key			   = Info.Key;
		

		UE_LOG(LogCs, Warning, TEXT("%s: Action: %s Type: %s Event: %s Key: %s"), *Context, Action.ToChar(), EMCsInputType::Get().ToChar(Type), EMCsInputEvent::Get().ToChar(Event), *(Key.ToString()));
		UE_LOG(LogCs, Warning, TEXT(" Setting Mode: %s."), EMCsInputMode::Get().ToChar(Mode));

		int32 Previous = Value;
		int32 New	   = Previous;

		CS_SET_BLUEPRINT_BITFLAG(New, Mode);

		UE_LOG(LogCs, Warning, TEXT(" Value (%s) -> (%s)"), *(EMCsInputMode::Get().MaskToString(Previous)), *(EMCsInputMode::Get().MaskToString(New)));
	}
}

void UCsManager_Input::FActiveMode::PrintSummary(const FString& Context)
{
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogInputActiveMode))
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Value (%s) -> (%s)"), *Context, *(EMCsInputMode::Get().MaskToString(Last_Value)), *(EMCsInputMode::Get().MaskToString(Value)));
	}
}

#pragma endregion Active

#pragma endregion Mode

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
	typedef NCsPlayer::NInput::FLibrary PlayerInputLibrary;

	UPlayerInput* PlayerInput = PlayerInputLibrary::GetFirstLocal(GetWorld());

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