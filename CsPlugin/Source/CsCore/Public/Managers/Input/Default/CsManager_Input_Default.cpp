// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/Default/CsManager_Input_Default.h"
#include "CsCore.h"

// CVar
#include "Managers/Input/CsCVars_Manager_Input.h"
// Library
	// Common
#include "Library/Load/CsLibrary_Load.h"
#include "Object/CsLibrary_Object.h"
#include "Player/CsLibrary_Player.h"
#include "Library/CsLibrary_Viewport.h"
#include "Library/CsLibrary_Math.h"
// Settings
#include "Managers/Input/CsSettings_Input.h"
#include "Managers/Input/CsSettings_Manager_Input.h"
// Player
#include "GameFramework/PlayerController.h"
//#include "Player/CsPlayerController.h"
//#include "Player/CsCheatManager.h"
#include "Engine/LocalPlayer.h"
// Input
#include "GameFramework/PlayerInput.h"
#include "Managers/Input/Default/CsInputListener.h"

// Cached
#pragma region

namespace NCsManagerInput
{
	namespace NCached
	{
		namespace Str
		{
			CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Input_Default, SetCurrentInputActionMap);
			CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Input_Default, ClearCurrentInputActionMap);

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Input_Default, PostProcessInput);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Input_Default, OnPostProcessInput_CaptureMouseInput);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Input_Default, OnPostProcessInput_CaptureTouchInput);
		}
	}

	namespace NCurrentMode
	{
		namespace NCached
		{
			namespace Str
			{
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Input_Default::FCurrentMode, SetValue);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Input_Default::FCurrentMode, ClearValue);
			}
		}
	}

	namespace NActiveMode
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Input_Default::FActiveMode, OnPostProcessInput);
			}
		}
	}
}

#pragma endregion Cached

UCsManager_Input_Default::UCsManager_Input_Default(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	// Owner
	OwnerAsController(nullptr),
	ControllerId(INDEX_NONE),
	// Manager_Input_Event
	OnPostProcessInput_Event(),
	OnGameEventInfo_Event(),
	OnGameEventInfos_Event(),
	OnAnyKey_Pressed_Event(),
	OnAnyKey_Pressed_ScriptEvent(),
	OnAnyKey_Released_Event(),
	OnAnyKey_Released_ScriptEvent(),
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
	// Listener
	Listeners(),
	// Actions
	Infos(),
	Actions(),
	Last_Actions(),
		// Mouse
	MouseActions(),
	CurrentMousePosition(FVector3f::ZeroVector),
		// Touch
	TouchActions(),
	TouchAxisActions(),
	// Mode
	CurrentMode(),
	ActiveMode(),
	// Profile
	InputProfile(),
	AllKeys()
{
}

// UObject Interface
#pragma region

void UCsManager_Input_Default::BeginDestroy()
{
	Super::BeginDestroy();

	typedef NCsObject::FLibrary ObjectLibrary;

	for (UCsInputListener* Listener : Listeners)
	{
		ObjectLibrary::SafeMarkAsGarbage(Listener);
	}
	Listeners.Reset();
}

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region

void UCsManager_Input_Default::OnRegister()
{
	Super::OnRegister();

	OwnerAsController = Cast<APlayerController>(GetOwner());
	
	Init();
}

#pragma endregion UActorComponent Interface

/*
void UCsManager_Input_Default::SetupInputComponent()
{
	if (!InputComponent)
	{
		InputComponent = NewObject<UInputComponent>(this, TEXT("InputComponent"));
		InputComponent->RegisterComponent();
	}
#if WITH_EDITOR
// Editor Game

	// RunEditorGameBatchConsoleCommands
	InputComponent->BindAction("RunEditorGameBatchConsoleCommands", IE_Pressed, this, &UCsManager_Input_Default::RunEditorGameBatchConsoleCommands_FirstPressed).bConsumeInput = false;
	// RunEditorGameJavascriptFile
	InputComponent->BindAction("RunEditorGameJavascriptFile", IE_Pressed, this, &UCsManager_Input_Default::RunEditorGameJavascriptFile_FirstPressed).bConsumeInput = false;

	UCsCheatManager* CheatManager   = Cast<UCsCheatManager>(OwnerAsController->CheatManager);

	OnRunEditorGameBatchConsoleCommands_FirstPressed_Event.AddUObject(CheatManager, &UCsCheatManager::RunEditorGameBatchConsoleCommands);
	OnRunEditorGameJavascriptFile_FirstPressed_Event.AddUObject(CheatManager, &UCsCheatManager::RunEditorGameJavascriptFile);

#endif // #if WITH_EDITOR
}
*/

// ICsManager_Input
#pragma region

void UCsManager_Input_Default::Init() 
{
	CurrentMode.Outer = this;
	ActiveMode.Outer = this;

	EKeys::GetAllKeys(AllKeys);

	const FCsSettings_Manager_Input& ManagerSettings = FCsSettings_Manager_Input::Get();

	Manager_Inputs.CreatePool(ManagerSettings.InputPoolSize);

	SetupInputActionEventInfos();
	SetupInputActionMapping();
	SetupGameEventDefinitions();

	const FCsSettings_Input& InputSettings = FCsSettings_Input::Get();

	// Initialize CurrentGameEventInfos
	const int32 EventCount = EMCsGameEvent::Get().Num();

	TArray<bool> EventsFound;

	EventsFound.Reset(EventCount);
	EventsFound.AddDefaulted(EventCount);

	for (int32 I = 0; I < EventCount; ++I)
	{
		EventsFound[I] = false;
	}

	GameEventPriorityList.Reset(EventCount);

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
	SetDefaultInputProfile();
}

void UCsManager_Input_Default::PreProcessInput(const float DeltaTime, const bool bGamePaused)
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
			Info.MarkDirty();
		}
	}
}

void UCsManager_Input_Default::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	using namespace NCsManagerInput::NCached;

	const FString& Context = Str::PostProcessInput;

	// Capture Mouse Inputs
	OnPostProcessInput_CaptureMouseInput(DeltaTime, bGamePaused);
	// Capture Touch Inputs
	OnPostProcessInput_CaptureTouchInput(DeltaTime, bGamePaused);

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

	CS_NON_SHIPPING_EXPR(OnPostProcessInput_LogInputAction());

	for (const FECsInputAction& Action : EMCsInputAction::Get())
	{
		FCsInputInfo& Info	 = InputActionEventInfos[Action.GetValue()];
		ECsInputEvent& Event = Info.Event;

		const ECsInputType& Type = Info.Type;

		if (Info.IsDirty())
		{
			// Action
			if (Type == ECsInputType::Action)
			{
				TryAddInput(Type, Action, Event, Info.Value, Info.Location);
			}
			// Axis
			else
			if (Type == ECsInputType::Axis)
			{
				float Value = Info.Value;

				TryAddInput(Type, Action, Event, Value, Info.Location);
			}
			// Location
			else
			if (Type == ECsInputType::Location)
			{
				const FVector3f& Location = Info.Location;

				TryAddInput(Type, Action, Event, Info.Value, Info.Location);	
			}
		}

		Info.FlushEvent();
		Info.ClearDirty();
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
				CurrentGameEventInfos[Index].ApplyInputCompletedValue(&CompletedValue);
			}
		}
	}

	CS_NON_SHIPPING_EXPR(LogProcessGameEventDefinition(Context));

	// Process Queue GameEvents
	for (const FCsGameEventInfo& Info : QueuedGameEventInfosForNextFrame)
	{
		const FECsGameEvent& Event  = Info.Event;
		const int32& Index			= GameEventPriorityMap[Event.GetValue()];

		CurrentGameEventInfos[Index] = Info;
	}
	QueuedGameEventInfosForNextFrame.Reset(QueuedGameEventInfosForNextFrame.Max());

	CS_NON_SHIPPING_EXPR(OnPostProcessInput_LogGameEventInfo());

	for (FCsGameEventInfo& Info : CurrentGameEventInfos)
	{
		if (Info.IsValid(Context, nullptr))
		{
			const FECsGameEvent& Event = Info.Event;

			// For "default" mouse related pressed events, also add the position information

			// Default__MouseLeftButtonPressed__ | Default__MouseRightButtonPressed__
			if (Event == NCsGameEvent::Default__MouseLeftButtonPressed__ ||
				Event == NCsGameEvent::Default__MouseRightButtonPressed__)
			{
				const int32& Index							= GameEventPriorityMap[NCsGameEvent::Default__MousePositionXY__.GetValue()];
				const FCsGameEventInfo& MousePositionXYInfo = CurrentGameEventInfos[Index];

				if (MousePositionXYInfo.IsValid(Context, nullptr))
				{
					Info.Location = MousePositionXYInfo.Location;
				}
			}

			CurrentValidGameEventInfos.Add(Info);

			OnGameEventInfo_Event.Broadcast(Info);
		}
	}

	if (CurrentValidGameEventInfos.Num() > CS_EMPTY)
		OnGameEventInfos_Event.Broadcast(CurrentValidGameEventInfos);

	OnPostProcessInput_Event.Broadcast(DeltaTime, bGamePaused);
}

#pragma endregion ICsManager_Input

void UCsManager_Input_Default::OnPostProcessInput_CaptureMouseInput(const float& DeltaTime, const bool bGamePaused)
{
	// TODO: Add Logging of Actions
#if PLATFORM_WINDOWS

	CS_NON_SHIPPING_EXPR(OnPostProcessInput_LogCaptureMouseInput());

	// Default__MousePositionXY__
	{
		CurrentMousePosition = FVector3f::ZeroVector;
			
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

			Info.MarkDirty();
		}
	}
	// TODO: Need to eventually bind Mouse Button events like Touch Pressed events

	// Default__MouseLeftButton__ | // Default__MouseRightButton__
	for (const FECsInputAction& Action : MouseActions)
	{
		FCsInputInfo& Info = InputActionEventInfos[Action.GetValue()];

		Info.Last_Location = Info.Location;
		Info.Location	   = CurrentMousePosition;

		const ECsInputEvent& Last_Event = Info.Last_Event;

		const FKey& Key = Action == NCsInputAction::Default__MouseLeftButton__ ? EKeys::LeftMouseButton : EKeys::RightMouseButton;

		// FirstReleased | Released -> FirstPressed
		// FirstPressed -> Pressed
		if (OwnerAsController->PlayerInput->IsPressed(Key))
		{
			if (Last_Event == ECsInputEvent::FirstReleased ||
				Last_Event == ECsInputEvent::Released)
			{
				Info.Event = ECsInputEvent::FirstPressed;
			}
			else
			if (Last_Event == ECsInputEvent::FirstPressed)
			{
				Info.Event = ECsInputEvent::Pressed;
			}
		}
		// FirstPressed | Pressed -> FirstReleased
		// FirstReleased -> Released
		else
		{
			// FirstPressed | Pressed -> FirstReleased
			if (Last_Event == ECsInputEvent::FirstPressed ||
				Last_Event == ECsInputEvent::Pressed)
			{
				Info.Event = ECsInputEvent::FirstReleased;
			}
			// FirstReleased -> Released
			else
			if (Last_Event == ECsInputEvent::FirstReleased)
			{
				Info.Event = ECsInputEvent::Released;
			}
			// Released
			else
			{
				Info.ResetLocation();
			}
		}
		Info.MarkDirty();
	}
#endif // #if PLATFORM_WINDOWS
}

void UCsManager_Input_Default::OnPostProcessInput_LogCaptureMouseInput()
{
	using namespace NCsManagerInput::NCached;

	const FString& Context = Str::OnPostProcessInput_CaptureMouseInput;

	FVector3f MousePosition = FVector3f::ZeroVector;

	// Location | Location Event Change
	if (CS_CVAR_LOG_IS_SHOWING(LogInputMouseLocation) ||
		CS_CVAR_LOG_IS_SHOWING(LogInputMouseLocationEventChange))
	{
		const bool LogLocation			  = CS_CVAR_LOG_IS_SHOWING(LogInputMouseLocation);
		const bool LogLocationEventChange = CS_CVAR_LOG_IS_SHOWING(LogInputMouseLocationEventChange);

		// Default__MousePositionXY__
		{
			if (OwnerAsController->GetMousePosition(MousePosition.X, MousePosition.Y))
			{
				const FECsInputAction& Action = NCsInputAction::Default__MousePositionXY__;
				FCsInputInfo& Info			  = InputActionEventInfos[Action.GetValue()];
				const ECsInputEvent& Event	  = Info.Event;

				const FVector3f& Location = Info.Location;

				const float& Time = CurrentInputFrame->Time.Time;

				if (LogLocation)
				{
					UE_LOG(LogCs, Warning, TEXT("%s (%d): Time: %f."), *Context, ControllerId, Time);
					UE_LOG(LogCs, Warning, TEXT(" Action: %s. Event: %s. Location: (%3.3f, %3.3f)"), Action.ToChar(), EMCsInputEvent::Get().ToChar(Event), MousePosition.X, MousePosition.Y);
				}

				// Change
				if (Info.Location != MousePosition)
				{
					// FirstStationary | Stationary -> FirstMoved
					if (Event == ECsInputEvent::FirstStationary ||
						Event == ECsInputEvent::Stationary)
					{
						UE_LOG(LogCs, Warning, TEXT("%s (%d): Time: %f."), *Context, ControllerId, Time);
						UE_LOG(LogCs, Warning, TEXT(" Action: %s. Event: %s -> FirstMoved. Location: (%3.3f, %3.3f) -> (%3.3f, %3.3f)"), Action.ToChar(), EMCsInputEvent::Get().ToChar(Event), Location.X, Location.Y, MousePosition.X, MousePosition.Y);
					}
					// FirstMoved -> Moved
					else
					if (Event == ECsInputEvent::FirstMoved)
					{
						UE_LOG(LogCs, Warning, TEXT("%s (%d): Time: %f."), *Context, ControllerId, Time);
						UE_LOG(LogCs, Warning, TEXT(" Action: %s. Event: FirstMoved -> Moved. Location: (%3.3f, %3.3f) -> (%3.3f, %3.3f)"), Action.ToChar(), Location.X, Location.Y, MousePosition.X, MousePosition.Y);
					}
				}
				// No Change
				else
				{
					// FirstMoved | Moved -> FirstStationary
					if (Event == ECsInputEvent::FirstMoved ||
						Event == ECsInputEvent::Moved)
					{
						UE_LOG(LogCs, Warning, TEXT("%s (%d): Time: %f."), *Context, ControllerId, Time);
						UE_LOG(LogCs, Warning, TEXT(" Action: %s. Event: %s -> FirstStationary. Location: (%3.3f, %3.3f)"), Action.ToChar(), EMCsInputEvent::Get().ToChar(Event), MousePosition.X, MousePosition.Y);
					}
					// FirstStationary -> Stationary
					else
					if (Event == ECsInputEvent::FirstStationary)
					{
						UE_LOG(LogCs, Warning, TEXT("%s (%d): Time: %f."), *Context, ControllerId, Time);
						UE_LOG(LogCs, Warning, TEXT(" Action: %s. Event: FirstStationary -> Stationary. Location: (%3.3f, %3.3f)"), Action.ToChar(), MousePosition.X, MousePosition.Y);
					}
				}
			}
		}
	}
	// Action | Action Event Changed
	if (CS_CVAR_LOG_IS_SHOWING(LogInputMouseAction) ||
		CS_CVAR_LOG_IS_SHOWING(LogInputMouseActionEventChange))
	{ 
		const bool LogAction			= CS_CVAR_LOG_IS_SHOWING(LogInputMouseAction);
		const bool LogActionEventChange = CS_CVAR_LOG_IS_SHOWING(LogInputMouseActionEventChange);

		const float& Time = CurrentInputFrame->Time.Time;

		if (LogAction)
		{
			UE_LOG(LogCs, Warning, TEXT("%s (%d): Time: %f."), *Context, ControllerId, Time);
		}

		// Default__MouseLeftButton__ | Default__MouseRightButton__
		for (const FECsInputAction& Action : MouseActions)
		{
			FCsInputInfo& Info = InputActionEventInfos[Action.GetValue()];

			const ECsInputEvent& Event		= Info.Event;
			const ECsInputEvent& Last_Event = Info.Last_Event;

			const FKey& Key = Action == NCsInputAction::Default__MouseLeftButton__ ? EKeys::LeftMouseButton : EKeys::RightMouseButton;

			if (LogAction)
			{
				UE_LOG(LogCs, Warning, TEXT(" Action: %s. Event: %s. Location: (%3.3f, %3.3f)"), Action.ToChar(), MousePosition.X, MousePosition.Y);
			}

			// FirstReleased | Released -> FirstPressed
			// FirstPressed -> Pressed
			if (OwnerAsController->PlayerInput->IsPressed(Key))
			{
				// FirstReleased | Released -> FirstPressed
				if (Last_Event == ECsInputEvent::FirstReleased ||
					Last_Event == ECsInputEvent::Released)
				{
					if (LogActionEventChange)
					{
						UE_LOG(LogCs, Warning, TEXT("%s (%d): Time: %f."), *Context, ControllerId, Time);
						UE_LOG(LogCs, Warning, TEXT(" Action: %s. Event: %s -> FirstPressed. Location: (%3.3f, %3.3f)"), Action.ToChar(), EMCsInputEvent::Get().ToChar(Event), MousePosition.X, MousePosition.Y);
					}
				}
				// FirstPressed -> Pressed
				else
				if (Last_Event == ECsInputEvent::FirstPressed)
				{
					if (LogActionEventChange)
					{
						UE_LOG(LogCs, Warning, TEXT("%s (%d): Time: %f."), *Context, ControllerId, Time);
						UE_LOG(LogCs, Warning, TEXT(" Action: %s. Event: FirstPressed -> Pressed. Location: (%3.3f, %3.3f)"), Action.ToChar(), MousePosition.X, MousePosition.Y);
					}
				}
			}
			// FirstPressed | Pressed -> FirstReleased
			// FirstReleased -> Released
			else
			{
				// FirstPressed | Pressed -> FirstReleased
				if (Last_Event == ECsInputEvent::FirstPressed ||
					Last_Event == ECsInputEvent::Pressed)
				{
					if (LogActionEventChange)
					{
						UE_LOG(LogCs, Warning, TEXT("%s (%d): Time: %f."), *Context, ControllerId, Time);
						UE_LOG(LogCs, Warning, TEXT(" Action: %s. Event: %s -> FirstReleased. Location: (%3.3f, %3.3f)"), Action.ToChar(), EMCsInputEvent::Get().ToChar(Event), MousePosition.X, MousePosition.Y);
					}
				}
				// FirstReleased -> Released
				else
				if (Last_Event == ECsInputEvent::FirstReleased)
				{
					if (LogActionEventChange)
					{
						UE_LOG(LogCs, Warning, TEXT("%s (%d): Time: %f."), *Context, ControllerId, Time);
						UE_LOG(LogCs, Warning, TEXT(" Action: %s. Event: FirstReleased -> Released. Location: (%3.3f, %3.3f)"), Action.ToChar(), MousePosition.X, MousePosition.Y);
					}
				}
			}
		}
	}
}

void UCsManager_Input_Default::OnPostProcessInput_CaptureTouchInput(const float& DeltaTime, const bool bGamePaused)
{
	using namespace NCsManagerInput::NCached;

	const FString& Context = Str::OnPostProcessInput_CaptureTouchInput;
	
	// TODO: See if there is a check if Touch is even a viable input
#if !PLATFORM_ANDROID && !PLATFORM_IOS
	return;
#endif // #if !PLATFORM_ANDROID && !PLATFORM_IOS

	CS_NON_SHIPPING_EXPR(OnPostProcessInput_LogCaptureTouchInput());

	UPlayerInput* PlayerInput = OwnerAsController->PlayerInput;

	// Get Viewport Size
	// TODO: CHECK: On Android it seems PlayerInput->Touches (X,Y) are NOT in the range [0,0] -> [1,1]
	/*
	typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

	const FIntPoint Size = ViewportLibrary::GetSizeChecked(Context, this);
	*/
	// Check if any Touch Locations have been updated
	typedef NCsMath::FLibrary MathLibrary;

	const int32 Count = TouchAxisActions.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		const FECsInputAction& Action = TouchAxisActions[I];
		FCsInputInfo& Info			  = InputActionEventInfos[Action.GetValue()];

		FVector3f CurrentPosition = Info.Location;

		const FVector3f Touch = MathLibrary::Convert(PlayerInput->Touches[I]);
		const bool IsPressed  = Touch.Z != 0.0f;

		if (IsPressed)
		{
			// TODO: CHECK: On Android it seems PlayerInput->Touches (X,Y) are NOT in the range [0,0] -> [1,1]
			//CurrentPosition.X = FMath::FloorToFloat(Touch.X * Size.X);
			//CurrentPosition.Y = FMath::FloorToFloat(Touch.Y * Size.Y);
			CurrentPosition.X = Touch.X;
			CurrentPosition.Y = Touch.Y;		
		}

		ECsInputEvent& Event = Info.Event;

		Info.Last_Location = Info.Location;

		// Change
		if (Info.Location != CurrentPosition)
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

		Info.Location = CurrentPosition;

		Info.MarkDirty();
	}
}

void UCsManager_Input_Default::OnPostProcessInput_LogCaptureTouchInput()
{
	using namespace NCsManagerInput::NCached;

	const FString& Context = Str::OnPostProcessInput_CaptureTouchInput;

	typedef NCsMath::FLibrary MathLibrary;

	// Action | Action Event Change
	if (CS_CVAR_LOG_IS_SHOWING(LogInputTouchAction) ||
		CS_CVAR_LOG_IS_SHOWING(LogInputTouchActionEventChange))
	{
		TArray<FECsInputAction> ActionsToPrint;
		ActionsToPrint.Reset(TouchActions.Num());

		const bool LogAction			= CS_CVAR_LOG_IS_SHOWING(LogInputTouchAction);
		const bool LogActionEventChange = CS_CVAR_LOG_IS_SHOWING(LogInputTouchActionEventChange);

		for (const FECsInputAction& Action : TouchActions)
		{
			FCsInputInfo& Info		 = InputActionEventInfos[Action.GetValue()];
			const ECsInputType& Type = Info.Type;

			// Action
			if (Type == ECsInputType::Action)
			{
				if (Info.HasEventChanged() &&
					(LogAction ||
					 LogActionEventChange))
				{
					ActionsToPrint.Add(Action);
				}
				else
				if (LogAction)
				{
					ActionsToPrint.Add(Action);
				}
			}
		}

		if (ActionsToPrint.Num() > CS_EMPTY)
		{
			const float& Time = CurrentInputFrame->Time.Time;

			UE_LOG(LogCs, Warning, TEXT("%s (%d): Time: %f."), *Context, ControllerId, Time);

			for (const FECsInputAction& Action : ActionsToPrint)
			{
				FCsInputInfo& Info			= InputActionEventInfos[Action.GetValue()];
				const ECsInputType& Type	= Info.Type;
				ECsInputEvent& Event		= Info.Event;
				const FString& CurrentEvent = EMCsInputEvent::Get().ToString(Event);
				const FVector3f& Location   = Info.Location;

				// Action
				if (Type == ECsInputType::Action)
				{
					if (Info.HasEventChanged() &&
						(LogAction ||
						 LogActionEventChange))
					{
						const FString& LastEvent = EMCsInputEvent::Get().ToString(Info.Last_Event);

						UE_LOG(LogCs, Warning, TEXT(" Action: %s. Event: %s -> %s. Location: (%3.3f, %3.3f)"), Action.ToChar(), *LastEvent, *CurrentEvent, Location.X, Location.Y);
					}
					else
					if (LogAction)
					{
						UE_LOG(LogCs, Warning, TEXT(" Action: %s. Event: %s. Location: (%3.3f, %3.3f)"), Action.ToChar(), *CurrentEvent, Location.X, Location.Y);
					}
				}
			}
		}
	}
	// Location
	if (CS_CVAR_LOG_IS_SHOWING(LogInputTouchLocation))
	{
		UPlayerInput* PlayerInput = OwnerAsController->PlayerInput;

		const int32 Count = TouchAxisActions.Num();

		TArray<int32> Indices;
		Indices.Reset(Count);

		for (int32 I = 0; I < Count; ++I)
		{
			const FECsInputAction& Action = TouchAxisActions[I];
			const FVector3f Touch		  = MathLibrary::Convert(PlayerInput->Touches[I]);

			const bool IsPressed = Touch.Z != 0.0f;

			if (IsPressed)
			{
				Indices.Add(I);
			}
		}

		if (Indices.Num() > CS_EMPTY)
		{
			const float& Time = CurrentInputFrame->Time.Time;

			UE_LOG(LogCs, Warning, TEXT("%s (%d): Time: %f."), *Context, ControllerId, Time);

			for (const int32& I : Indices)
			{
				const FECsInputAction& Action = TouchAxisActions[I];
				const FVector3f Touch		  = MathLibrary::Convert(PlayerInput->Touches[I]);

				const bool IsPressed = Touch.Z != 0.0f;

				if (IsPressed)
				{
					UE_LOG(LogCs, Warning, TEXT(" Action: %s. Location: (%3.3f, %3.3f)"), Action.ToChar(), Touch.X, Touch.Y);
				}
			}
		}
	}
	// Location Event Change
	if (CS_CVAR_LOG_IS_SHOWING(LogInputTouchLocationEventChange))
	{
		UPlayerInput* PlayerInput = OwnerAsController->PlayerInput;

		const int32 Count = TouchAxisActions.Num();

		TArray<int32> Indices;
		Indices.Reset(Count);

		for (int32 I = 0; I < Count; ++I)
		{
			const FECsInputAction& Action = TouchAxisActions[I];
			FCsInputInfo& Info			  = InputActionEventInfos[Action.GetValue()];

			FVector3f CurrentPosition = Info.Location;

			const FVector3f Touch = MathLibrary::Convert(PlayerInput->Touches[I]);
			const bool IsPressed = Touch.Z != 0.0f;

			if (IsPressed)
			{
				CurrentPosition.X = Touch.X;
				CurrentPosition.Y = Touch.Y;		
			}

			const ECsInputEvent& Event = Info.Event;

			// Change
			if (Info.Location != CurrentPosition)
			{
				// FirstStationary | Stationary -> FirstMoved
				if (Event == ECsInputEvent::FirstStationary ||
					Event == ECsInputEvent::Stationary)
				{
					Indices.Add(I);
				}
				// FirstMoved -> Moved
				else
				if (Event == ECsInputEvent::FirstMoved)
				{
					Indices.Add(I);
				}
			}
			// No Change
			else
			{
				// FirstMoved | Moved -> FirstStationary
				if (Event == ECsInputEvent::FirstMoved ||
					Event == ECsInputEvent::Moved)
				{
					Indices.Add(I);
				}
				// FirstStationary -> Stationary
				else
				if (Event == ECsInputEvent::FirstStationary)
				{
					Indices.Add(I);
				}
			}
		}

		if (Indices.Num() > CS_EMPTY)
		{
			const float& Time = CurrentInputFrame->Time.Time;

			UE_LOG(LogCs, Warning, TEXT("%s (%d): Time: %f."), *Context, ControllerId, Time);

			for (const int32& I : Indices)
			{
				const FECsInputAction& Action = TouchAxisActions[I];
				FCsInputInfo& Info			  = InputActionEventInfos[Action.GetValue()];

				FVector3f CurrentPosition = Info.Location;

				const FVector3f Touch = MathLibrary::Convert(PlayerInput->Touches[I]);
				const bool IsPressed = Touch.Z != 0.0f;

				if (IsPressed)
				{
					CurrentPosition.X = Touch.X;
					CurrentPosition.Y = Touch.Y;
				}

				const ECsInputEvent& Event = Info.Event;

				// Change
				if (Info.Location != CurrentPosition)
				{
					// FirstStationary | Stationary -> FirstMoved
					if (Event == ECsInputEvent::FirstStationary ||
						Event == ECsInputEvent::Stationary)
					{
						UE_LOG(LogCs, Warning, TEXT(" %s: %s -> FirstMoved. Location: (%3.3f, %3.3f)"), Action.ToChar(), EMCsInputEvent::Get().ToChar(Event), Touch.X, Touch.Y);
					}
					// FirstMoved -> Moved
					else
					if (Event == ECsInputEvent::FirstMoved)
					{
						UE_LOG(LogCs, Warning, TEXT(" %s: FirstMoved -> Moved. Location: (%3.3f, %3.3f)"), Action.ToChar(), Touch.X, Touch.Y);
					}
				}
				// No Change
				else
				{
					// FirstMoved | Moved -> FirstStationary
					if (Event == ECsInputEvent::FirstMoved ||
						Event == ECsInputEvent::Moved)
					{
						UE_LOG(LogCs, Warning, TEXT(" %s: %s -> FirstStationary. Location: (%3.3f, %3.3f)"), Action.ToChar(), EMCsInputEvent::Get().ToChar(Event), Touch.X, Touch.Y);
					}
					// FirstStationary -> Stationary
					else
					if (Event == ECsInputEvent::FirstStationary)
					{
						UE_LOG(LogCs, Warning, TEXT(" %s: FirstStationary -> Stationary. Location: (%3.3f, %3.3f)"), Action.ToChar(), Touch.X, Touch.Y);
					}
				}
			}
		}
	}
}

void UCsManager_Input_Default::OnPostProcessInput_CaptureVRInput()
{
	const bool IsVR = false;//UCsLibrary_Common::IsVR();

	if (IsVR)
	{
		FRotator3f Rotation;
		FVector3f Location;

		//UCsLibrary_Common::GetHMDOrientationAndPosition(Rotation, Location);

		//HMD_Rotation_Raw.ExecuteIfBound(Rotation);
		//HMD_Location_Raw.ExecuteIfBound(Location);
	}

	/*
	TArray<IMotionController*> Controllers = IModularFeatures::Get().GetModularFeatureImplementations<IMotionController>(IMotionController::GetModularFeatureName());

	for (IMotionController* Controller : Controllers)
	{
		const uint8 LocalPlayerIndex = 0;

		// Check controllers are being Tracked

		const float WorldToMetersScale = 100.0f;

		FRotator3f Rotation;
		FVector3f Location;

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
	*/
}

void UCsManager_Input_Default::OnPostProcessInput_LogInputAction()
{
	using namespace NCsManagerInput::NCached;

	const FString& Context = Str::PostProcessInput;

	const bool LogAll = CS_CVAR_LOG_IS_SHOWING(LogInput);
	const bool LogAllEventChange = CS_CVAR_LOG_IS_SHOWING(LogInputEventChange);
	// Action
	const bool LogAction = CS_CVAR_LOG_IS_SHOWING(LogInputAction);
	const bool LogActionEventChange = CS_CVAR_LOG_IS_SHOWING(LogInputActionEventChange);
	// Axis
	const bool LogAxis = CS_CVAR_LOG_IS_SHOWING(LogInputAxis);
	const bool LogAxisEventChange = CS_CVAR_LOG_IS_SHOWING(LogInputAxisEventChange);
	// Location
	const bool LogLocation = CS_CVAR_LOG_IS_SHOWING(LogInputLocation);
	const bool LogLocationEventChange = CS_CVAR_LOG_IS_SHOWING(LogInputLocationEventChange);

	if (LogAll ||
		LogAllEventChange ||
		LogAction ||
		LogActionEventChange ||
		LogAxis ||
		LogAxisEventChange ||
		LogLocation ||
		LogLocationEventChange)
	{
		TArray<FECsInputAction> ActionsToPrint;

		ActionsToPrint.Reset(EMCsInputAction::Get().Num());
		
		for (const FECsInputAction& Action : EMCsInputAction::Get())
		{
			FCsInputInfo& Info			= InputActionEventInfos[Action.GetValue()];
			const ECsInputType& Type	= Info.Type;

			// Action
			if (Type == ECsInputType::Action)
			{
				if (Info.HasEventChanged() &&
					(LogAll ||
					 LogAllEventChange ||
					 LogAction ||
					 LogActionEventChange))
				{
					ActionsToPrint.Add(Action);
				}
				else
				if (LogAll ||
				    LogAction)
				{
					ActionsToPrint.Add(Action);
				}
			}
			// Axis
			else
			if (Type == ECsInputType::Axis)
			{
				const float& Value = Info.Value;

				if (Info.HasEventChanged() &&
					(LogAll ||
					 LogAllEventChange ||
					 LogAxis ||
					 LogAxisEventChange))
				{
					ActionsToPrint.Add(Action);
				}
				else
				if (LogAll ||
					LogAxis)
				{
					ActionsToPrint.Add(Action);
				}
			}
			// Location
			else
			if (Type == ECsInputType::Location)
			{
				const FVector3f& Location = Info.Location;

				if (Info.HasEventChanged() &&
					(LogAll ||
					 LogAllEventChange ||
					 LogLocation ||
					 LogLocationEventChange))
				{
					ActionsToPrint.Add(Action);
				}
				else
				if (LogAll ||
					LogLocation)
				{
					ActionsToPrint.Add(Action);
				}
			}
		}

		if (ActionsToPrint.Num() > CS_EMPTY)
		{
			const float& Time = CurrentInputFrame->Time.Time;

			UE_LOG(LogCs, Warning, TEXT("%s (%d): Time: %f."), *Context, ControllerId, Time);

			for (const FECsInputAction& Action : ActionsToPrint)
			{
				FCsInputInfo& Info			= InputActionEventInfos[Action.GetValue()];
				const ECsInputType& Type	= Info.Type;
				ECsInputEvent& Event		= Info.Event;
				const FString& CurrentEvent = EMCsInputEvent::Get().ToString(Event);

				// Action
				if (Type == ECsInputType::Action)
				{
					if (Info.HasEventChanged() &&
						(LogAll ||
						 LogAllEventChange ||
						 LogAction ||
						 LogActionEventChange))
					{
						const FString& LastEvent = EMCsInputEvent::Get().ToString(Info.Last_Event);

						UE_LOG(LogCs, Warning, TEXT(" Action: %s. Event: %s -> %s."), Action.ToChar(), *LastEvent, *CurrentEvent);
					}
					else
					if (LogAll ||
						LogAction)
					{
						UE_LOG(LogCs, Warning, TEXT(" Action: %s. Event: %s."), Action.ToChar(), *CurrentEvent);
					}
				}
				// Axis
				else
				if (Type == ECsInputType::Axis)
				{
					const float& Value = Info.Value;

					if (Info.HasEventChanged() &&
						(LogAll ||
						 LogAllEventChange ||
						 LogAxis ||
						 LogAxisEventChange))
					{
						const FString& LastEvent = EMCsInputEvent::Get().ToString(Info.Last_Event);

						UE_LOG(LogCs, Warning, TEXT(" Action: %s. Event: %s -> %s. Value: %f -> %f."), Action.ToChar(), *LastEvent, *CurrentEvent, Info.Last_Value, Value);
					}
					else
					if (LogAll ||
						LogAxis)
					{
						UE_LOG(LogCs, Warning, TEXT(" Action: %s. Event: %s. Value: %f."), Action.ToChar(), *CurrentEvent, Value);
					}
				}
				// Location
				else
				if (Type == ECsInputType::Location)
				{
					const FVector3f& Location = Info.Location;

					if (Info.HasEventChanged() &&
						(LogAll ||
						 LogAllEventChange ||
						 LogLocation ||
						 LogLocationEventChange))
					{
						const FString& LastEvent   = EMCsInputEvent::Get().ToString(Info.Last_Event);
						const FString LastLocation = Info.Last_Location.ToString();

						UE_LOG(LogCs, Warning, TEXT(" Action: %s. Event: %s -> %s. Location: %s -> %s."), Action.ToChar(), *LastEvent, *CurrentEvent, *LastLocation, *(Location.ToString()));
					}
					else
					if (LogAll ||
						LogLocation)
					{
						UE_LOG(LogCs, Warning, TEXT(" Action: %s. Event: %s. Location: %s."), Action.ToChar(), *CurrentEvent, *(Location.ToString()));
					}
				}
			}
		}
	}
}

void UCsManager_Input_Default::OnPostProcessInput_LogCurrentInputFrame()
{
	using namespace NCsManagerInput::NCached;

	const FString& Context = Str::PostProcessInput;

	if (CS_CVAR_LOG_IS_SHOWING(LogInputFrame))
	{
		const int32 Count = CurrentInputFrame->Inputs.Num();

		if (Count > CS_EMPTY)
		{
			UE_LOG(LogCs, Warning, TEXT("%s (%d): %d Inputs. Time: %f."), *Context, ControllerId, Count);

			for (int32 I = 0; I < Count; ++I)
			{
				const FCsInput* Input		  = CurrentInputFrame->Inputs[I];
				const FECsInputAction& Action = Input->Action;
				const ECsInputEvent& Event	  = Input->Event;
				const FCsInputInfo& Info	  = InputActionEventInfos[Action.GetValue()];
				const ECsInputType& Type	  = Info.Type;

				const float& Time			 = CurrentInputFrame->Time.Time;
				const FString& EventAsString = EMCsInputEvent::Get().ToString(Input->Event);

				UE_LOG(LogCs, Warning, TEXT(" [%d] Action: %s Event: %s."), I, Action.ToChar(), *EventAsString);
			}
		}
	}
}

void UCsManager_Input_Default::OnPostProcessInput_LogGameEventInfo()
{
	using namespace NCsManagerInput::NCached;

	const FString& Context = Str::PostProcessInput;

	if (CS_CVAR_LOG_IS_SHOWING(LogInputGameEvent))
	{
		int32 Count = 0;

		for (FCsGameEventInfo& Info : CurrentGameEventInfos)
		{
			if (Info.IsValid(Context, nullptr))
			{
				++Count;
				break;
			}
		}

		if (Count > CS_EMPTY)
		{
			const float& Time = CurrentInputFrame->Time.Time;

			UE_LOG(LogCs, Warning, TEXT("%s (%d): Time: %f."), *Context, ControllerId, Time);

			for (FCsGameEventInfo& Info : CurrentGameEventInfos)
			{
				if (Info.IsValid(Context, nullptr))
				{
					const FECsGameEvent& Event = Info.Event;

					UE_LOG(LogCs, Warning, TEXT(" Event: %s."), Event.ToChar());
					UE_LOG(LogCs, Warning, TEXT(" Value: %f."), Info.Value);
					UE_LOG(LogCs, Warning, TEXT(" Location: %s."), *(Info.Location.ToCompactString()));
				}
			}
		}
	}
}

FCsInput* UCsManager_Input_Default::AllocateInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value /*=0.0f*/, const FVector3f& Location /*=FVector3f::ZeroVector*/, const FRotator3f& Rotation /*=FRotator3f::ZeroRotator*/)
{
	FCsInput* Input = Manager_Inputs.AllocateResource();

	Input->Set(Action, Event, Value, Location, Rotation);

	return Input;
}

void UCsManager_Input_Default::AddInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value /*=0.0f*/, const FVector3f& Location /*=FVector3f::ZeroVector*/, const FRotator3f& Rotation /*=FRotator3f::ZeroRotator*/)
{
	FCsInput* Input = AllocateInput(Action, Event, Value, Location, Rotation);
	InputFrames[CurrentInputFrameIndex].Inputs.Add(Input);
}

bool UCsManager_Input_Default::CanAddInput(const FECsInputAction& Action)
{
	return (CurrentInputActionMap & InputActionMapping[Action.GetValue()]) > 0;
}

bool UCsManager_Input_Default::TryAddInput(const ECsInputType& Type, const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value /*= 0.0f*/, const FVector3f& Location /*= FVector3f::ZeroVector*/, const FRotator3f& Rotation /*= FRotator3f::ZeroRotator*/)
{
	if (CanAddInput(Action))
	{
		const ECsInputEvent& OutEvent = ProcessInputEvent(Type, Action, Event, Value, Location, Rotation);

		AddInput(Action, OutEvent, Value, Location, Rotation);
		return true;
	}
	return false;
}

const ECsInputEvent& UCsManager_Input_Default::ProcessInputEvent(const ECsInputType& Type, const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value, const FVector3f& Location, const FRotator3f& Rotation)
{
	return Event;
}

void UCsManager_Input_Default::QueueInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value /*=0.0f*/, const FVector3f& Location /*=FVector3f::ZeroVector*/, const FRotator3f& Rotation /*=FRotator3f::ZeroRotator*/)
{
	FCsInput* Input = AllocateInput(Action, Event, Value, Location, Rotation);

	QueuedInputsForNextFrame.Add(Input);
}

void UCsManager_Input_Default::ConsumeInput(const FECsInputAction& Action)
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

void UCsManager_Input_Default::SetupInputActionEventInfos()
{
	UPlayerInput* PlayerInput = OwnerAsController->PlayerInput;

	const int32& ActionCount = EMCsInputAction::Get().Num();

	InputActionEventInfos.Reset(ActionCount);
	InputActionEventInfos.AddDefaulted(ActionCount);
	Listeners.Reset(ActionCount);
	Listeners.AddDefaulted(ActionCount);

	// AnyKey
	{
		const FECsInputAction& AnyKeyAction = FCsSettings_Input::Get().AnyKeyAction;

		// Check AnyKeyAction is actually bound to EKeys::AnyKey
		bool Found = false;

		for (const FInputActionKeyMapping& Mapping : PlayerInput->ActionMappings)
		{
			if (Mapping.ActionName == AnyKeyAction.GetFName() &&
				Mapping.Key == EKeys::AnyKey)
			{
				Found = true;
			}
		}

		checkf(Found, TEXT("UCsManager_Input_Default::SetupInputActionEventInfos: UCsDeveloperSettings->Input.AnyKeyAction: %s is NOT bound to the Key: AnyKey."), AnyKeyAction.ToChar());

		UInputComponent* InputComponent = OwnerAsController->InputComponent;

		// Pressed
		{
			FInputActionBinding& Binding = InputComponent->BindAction<UCsManager_Input_Default>(AnyKeyAction.GetFName(), EInputEvent::IE_Pressed, this, &UCsManager_Input_Default::OnAnyKey_Pressed);
			Binding.bConsumeInput = false;
		}
		// Released
		{
			FInputActionBinding& Binding = InputComponent->BindAction<UCsManager_Input_Default>(AnyKeyAction.GetFName(), EInputEvent::IE_Released, this, &UCsManager_Input_Default::OnAnyKey_Released);
			Binding.bConsumeInput = false;
		}
	}
	// Mouse
	{
		MouseActions.Reset(2);
		MouseActions.Add(NCsInputAction::Default__MouseLeftButton__);
		MouseActions.Add(NCsInputAction::Default__MouseRightButton__);
	}
	// Touch
	{
		const int32 Count = EKeys::NUM_TOUCH_KEYS - 1;

		// Add Action Mappings for Touch Events (Pressed / Released)
		{
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

			for (const FECsInputAction& Action : TouchActions)
			{
				FCsInputInfo& Info = InputActionEventInfos[Action.GetValue()];

				Info.Type		= ECsInputType::Action;
				Info.ValueType	= ECsInputValue::Void;
				Info.Event		= ECsInputEvent::Released;
				Info.Last_Event = ECsInputEvent::Released;
			}

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
				FInputTouchBinding& Binding = InputComponent->BindTouch<UCsManager_Input_Default>(EInputEvent::IE_Pressed, this, &UCsManager_Input_Default::OnTouchAction_Pressed);
				Binding.bConsumeInput		= false;
			}
			// Released
			{
				FInputTouchBinding& Binding = InputComponent->BindTouch<UCsManager_Input_Default>(EInputEvent::IE_Released, this, &UCsManager_Input_Default::OnTouchAction_Released);
				Binding.bConsumeInput		= false;
			}
		}
		// Add Axis Actions
		{
			TouchAxisActions.Reset(Count);
			TouchAxisActions.Add(NCsInputAction::Default__TouchPositionXY_0__);
			TouchAxisActions.Add(NCsInputAction::Default__TouchPositionXY_1__);
			TouchAxisActions.Add(NCsInputAction::Default__TouchPositionXY_2__);
			TouchAxisActions.Add(NCsInputAction::Default__TouchPositionXY_3__);
			TouchAxisActions.Add(NCsInputAction::Default__TouchPositionXY_4__);
			TouchAxisActions.Add(NCsInputAction::Default__TouchPositionXY_5__);
			TouchAxisActions.Add(NCsInputAction::Default__TouchPositionXY_6__);
			TouchAxisActions.Add(NCsInputAction::Default__TouchPositionXY_7__);
			TouchAxisActions.Add(NCsInputAction::Default__TouchPositionXY_8__);
			TouchAxisActions.Add(NCsInputAction::Default__TouchPositionXY_9__);

			for (const FECsInputAction& Action : TouchAxisActions)
			{
				FCsInputInfo& Info = InputActionEventInfos[Action.GetValue()];

				Info.Type		= ECsInputType::Location;
				Info.ValueType	= ECsInputValue::Vector;
				Info.Event		= ECsInputEvent::Stationary;
				Info.Last_Event = ECsInputEvent::Stationary;
			}
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

		// Ignore Touch Actions
		if (TouchActions.Contains(Action))
			continue;
		// Ignore Touch Axis Actions
		if (TouchAxisActions.Contains(Action))
			continue;

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

void UCsManager_Input_Default::SetupInputActionMapping()
{
	// Initialize InputActionMapping
	InputActionMapping.Reset(EMCsInputAction::Get().Num());

	for (const FECsInputAction& Action : EMCsInputAction::Get())
	{
		InputActionMapping.Add(0);
	}

	const FCsSettings_Input& InputSettings = FCsSettings_Input::Get();

	const TMap<FECsInputActionMap, FCsInputActionSet>& InputActionMappings = InputSettings.InputActionMappings;

	for (const FECsInputActionMap& Map : EMCsInputActionMap::Get())
	{
		const int32& Mask			 = Map.Mask;
		const FCsInputActionSet& Set = InputActionMappings[Map];

		// HACK: TODO: Investigate and fix
		{
			FCsInputActionSet& FixSet = const_cast<FCsInputActionSet&>(Set);
			FixSet.ConditionalRebuild();
		}

		// Set masks for InputActionMapping
		for (const FECsInputAction& Action : Set.Actions)
		{
			InputActionMapping[Action.GetValue()] |= Mask;
		}
	}
}

/*
void UCsManager_Input_Default::SetInputActionMappingByMap(FECsInputActionMap Map)
{
	CurrentInputActionMap |= 1 << static_cast<int32>(Map);
}
*/

#pragma endregion Action Map

FCsInput* UCsManager_Input_Default::GetPreviousInputAction(const FECsInputAction& Action)
{
	typedef NCsMath::FLibrary MathLibrary;

	const int32 LastInputFrame = MathLibrary::Mod(CurrentInputFrameIndex - 1, CS_MAX_INPUT_FRAMES);
	FCsInput* Input			   = InputFrames[LastInputFrame].GetInput(Action);

	return Input;
}

FCsInput* UCsManager_Input_Default::GetPreviousInputAction(const FECsInputAction& Action, const ECsInputEvent& Event)
{
	typedef NCsMath::FLibrary MathLibrary;

	const int32 LastInputFrame = MathLibrary::Mod(CurrentInputFrameIndex - 1, CS_MAX_INPUT_FRAMES);
	FCsInput* Input			   = InputFrames[LastInputFrame].GetInput(Action, Event);

	return Input;
}

FCsInput* UCsManager_Input_Default::GetPreviousInputAction(const FECsInputAction& Action, const TArray<ECsInputEvent>& Events)
{
	typedef NCsMath::FLibrary MathLibrary;

	const int32 LastInputFrame = MathLibrary::Mod(CurrentInputFrameIndex - 1, CS_MAX_INPUT_FRAMES);
	FCsInput* Input			   = InputFrames[LastInputFrame].GetInput(Action, Events);

	return Input;
}

FCsInput* UCsManager_Input_Default::GetPreviousPreviousInputAction(const FECsInputAction& Action)
{
	typedef NCsMath::FLibrary MathLibrary;

	const int32 LastInputFrame = MathLibrary::Mod(CurrentInputFrameIndex - 2, CS_MAX_INPUT_FRAMES);
	FCsInput* Input			   = InputFrames[LastInputFrame].GetInput(Action);

	return Input;
}

// Events
#pragma region

void UCsManager_Input_Default::SetupGameEventDefinitions()
{
	// Populate GameEventDefinitions
	const FCsSettings_Input& InputSettings = FCsSettings_Input::Get();

	GameEventDefinitions.Reset();
	InputSentenceByGameEventMap.Reset();

	for (const FCsGameEventDefinition& Def : InputSettings.GameEventDefinitions)
	{
		GameEventDefinitions.Add(Def);
	}

	for (const FCsGameEventDefinition& Def : GameEventDefinitions)
	{
		const FECsGameEvent& Event = Def.Event;

		checkf(Def.IsValid(), TEXT("UCsManager_Input_Default::SetupGameEventDefinitions (%s): GameEventDefinition set with GameEvent: %s is NOT Valid. Check the Sentence."), *(GetOwner()->GetName()), Event.ToChar());

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
	// GameEventDefinitions_ActionOneOrWordOneEventNoCompleteValue
	{
		typedef FCsGameEventDefinitionActionOneOrWordOneEventNoCompletedValue DefinitionType;

		for (const DefinitionType& Def : InputSettings.GameEventDefinitions_ActionOneOrWordOneEventNoCompleteValue)
		{
			Def.AddDefinition(GameEventDefinitions, InputSentenceByGameEventMap);
		}
	}
	// GameEventDefinitions_AxisOneOrWordNoComparePassThroughValue
	{
		typedef FCsGameEventDefinitionAxisOneOrWordNoComparePassThroughValue DefinitionType;

		for (const DefinitionType& Def : InputSettings.GameEventDefinitions_AxisOneOrWordNoComparePassThroughValue)
		{
			Def.AddDefinition(GameEventDefinitions, InputSentenceByGameEventMap);
		}
	}

	// Setup default game events for "default" mouse related actions
#if PLATFORM_WINDOWS
	// Default__MousePositionXY__
	{
		const FECsGameEvent& Event = NCsGameEvent::Default__MousePositionXY__;

		if (!InputSentenceByGameEventMap.Find(Event))
		{
			FCsGameEventDefinition Def;
			Def.Event = Event;

			FCsInputSentence& Sentence	= Def.Sentence;
			FCsInputPhrase& Phrase		= Sentence.Phrases.AddDefaulted_GetRef();
			FCsInputWord& Word			= Phrase.Words.AddDefaulted_GetRef();
			FCsInputDescription& Desc	= Word.AndInputs.AddDefaulted_GetRef();

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

			FCsInputSentence& Sentence	= Def.Sentence;
			FCsInputPhrase& Phrase		= Sentence.Phrases.AddDefaulted_GetRef();
			FCsInputWord& Word			= Phrase.Words.AddDefaulted_GetRef();
			FCsInputDescription& Desc	= Word.AndInputs.AddDefaulted_GetRef();

			Desc.Action = NCsInputAction::Default__MouseLeftButton__;
			Desc.Event = ECsInputEvent::FirstPressed;
			Desc.CompareValue.ValueType = ECsInputValue::Void;
			Desc.CompletedValue.ValueType = ECsInputValue::Vector;

			InputSentenceByGameEventMap.Add(Event, Sentence);
			GameEventDefinitions.Add(Def);
		}
	}
	// Default__MouseLeftButtonReleased__
	{
		const FECsGameEvent& Event = NCsGameEvent::Default__MouseLeftButtonReleased__;

		if (!InputSentenceByGameEventMap.Find(Event))
		{
			FCsGameEventDefinition Def;
			Def.Event = Event;

			FCsInputSentence& Sentence	= Def.Sentence;
			FCsInputPhrase& Phrase		= Sentence.Phrases.AddDefaulted_GetRef();
			FCsInputWord& Word			= Phrase.Words.AddDefaulted_GetRef();
			FCsInputDescription& Desc	= Word.AndInputs.AddDefaulted_GetRef();

			Desc.Action = NCsInputAction::Default__MouseLeftButton__;
			Desc.Event = ECsInputEvent::FirstReleased;
			Desc.CompareValue.ValueType = ECsInputValue::Void;
			Desc.CompletedValue.ValueType = ECsInputValue::Vector;

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

			FCsInputSentence& Sentence	= Def.Sentence;
			FCsInputPhrase& Phrase		= Sentence.Phrases.AddDefaulted_GetRef();
			FCsInputWord& Word			= Phrase.Words.AddDefaulted_GetRef();
			FCsInputDescription& Desc	= Word.AndInputs.AddDefaulted_GetRef();

			Desc.Action = NCsInputAction::Default__MouseRightButton__;
			Desc.Event = ECsInputEvent::FirstPressed;
			Desc.CompareValue.ValueType = ECsInputValue::Void;
			Desc.CompletedValue.ValueType = ECsInputValue::Vector;

			InputSentenceByGameEventMap.Add(Event, Sentence);
			GameEventDefinitions.Add(Def);
		}
	}
	// Default__MouseRightButtonReleased__
	{
		const FECsGameEvent& Event = NCsGameEvent::Default__MouseRightButtonReleased__;

		if (!InputSentenceByGameEventMap.Find(Event))
		{
			FCsGameEventDefinition Def;
			Def.Event = Event;

			FCsInputSentence& Sentence	= Def.Sentence;
			FCsInputPhrase& Phrase		= Sentence.Phrases.AddDefaulted_GetRef();
			FCsInputWord& Word			= Phrase.Words.AddDefaulted_GetRef();
			FCsInputDescription& Desc	= Word.AndInputs.AddDefaulted_GetRef();

			Desc.Action = NCsInputAction::Default__MouseRightButton__;
			Desc.Event = ECsInputEvent::FirstReleased;
			Desc.CompareValue.ValueType = ECsInputValue::Void;
			Desc.CompletedValue.ValueType = ECsInputValue::Vector;

			InputSentenceByGameEventMap.Add(Event, Sentence);
			GameEventDefinitions.Add(Def);
		}
	}
#endif // #if PLATFORM_WINDOWS


#if WITH_EDITOR
	for (const FECsGameEvent& Event : EMCsGameEvent::Get())
	{
		if (!InputSentenceByGameEventMap.Find(Event))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Input_Default::SetupGameEventDefinitions (%s): No GameEventDefinition set for GameEvent: %s."), *(GetOwner()->GetName()), Event.ToChar());
		}
	}
#endif // #if WITH_EDITOR
}

void UCsManager_Input_Default::LogProcessGameEventDefinition(const FString& Context)
{
	if (CS_CVAR_LOG_IS_SHOWING(LogInputGameEventDefinition))
	{
		int32 Count = 0;

		for (FCsGameEventDefinition& Def : GameEventDefinitions)
		{
			FCsInputSentence& Sentence = Def.Sentence;

			if (Sentence.IsCompleted())
			{
				++Count;
			}
		}

		if (Count > CS_EMPTY)
		{
			const float& Time = CurrentInputFrame->Time.Time;

			UE_LOG(LogCs, Warning, TEXT("%s (%d): Time: %f.."), *Context, ControllerId, Time);

			for (FCsGameEventDefinition& Def : GameEventDefinitions)
			{
				const FECsGameEvent& Event = Def.Event;
				FCsInputSentence& Sentence = Def.Sentence;

				if (Sentence.IsCompleted())
				{
					// For now handle a simple definition
					if (Sentence.Phrases.Num() > CS_EMPTY &&
						Sentence.Phrases[CS_FIRST].Words.Num() > CS_EMPTY &&
						Sentence.Phrases[CS_FIRST].Words[CS_FIRST].AndInputs.Num() > CS_EMPTY)
					{
						const FCsInputDescription& Input = Sentence.Phrases[CS_FIRST].Words[CS_FIRST].AndInputs[CS_FIRST];
						const FECsInputAction& Action = Input.Action;
						const FString& InputEventAsString = EMCsInputEvent::Get().ToString(Input.Event);

						UE_LOG(LogCs, Warning, TEXT(" (%s, %s) -> %s."), Action.ToChar(), *InputEventAsString, Event.ToChar());
					}
				}
			}
		}
	}
}

void UCsManager_Input_Default::QueueGameEvent(const FECsGameEvent& Event)
{
	QueuedGameEventInfosForNextFrame.AddDefaulted();
	QueuedGameEventInfosForNextFrame.Last().Event = Event;
}

void UCsManager_Input_Default::ClearQueuedGameEvents()
{
	QueuedGameEventInfosForNextFrame.Reset(QueuedGameEventInfosForNextFrame.Max());
}

bool UCsManager_Input_Default::HasActionEventOccured(const FECsInputAction& Action, const ECsInputEvent& Event)
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

float UCsManager_Input_Default::GetInputValue(const FECsInputAction& Action)
{
	FCsInputFrame& InputFrame = InputFrames[CurrentInputFrameIndex];

	for (FCsInput* Input : InputFrame.Inputs)
	{
		if (Input->Action == Action)
			return Input->Value;
	}
	return 0.0f;
}

FVector3f UCsManager_Input_Default::GetInputLocation(const FECsInputAction& Action)
{
	FCsInputFrame& InputFrame = InputFrames[CurrentInputFrameIndex];

	for (FCsInput* Input : InputFrame.Inputs)
	{
		if (Input->Action == Action)
			return Input->Location;
	}
	return FVector3f::ZeroVector;
}

ECsInputEvent UCsManager_Input_Default::GetInputEvent(const FECsInputAction& Action)
{
	FCsInputFrame& InputFrame = InputFrames[CurrentInputFrameIndex];

	for (FCsInput* Input : InputFrame.Inputs)
	{
		if (Input->Action == Action)
			return Input->Event;
	}
	return ECsInputEvent::ECsInputEvent_MAX;
}

float UCsManager_Input_Default::GetInputDuration(const FECsInputAction& Action)
{
	return Infos[Action.Value]->Duration;
}

// Listener
#pragma region

void UCsManager_Input_Default::OnAnyKey_Pressed(FKey Key)
{
	OnAnyKey_Pressed_Event.Broadcast(Key);
	OnAnyKey_Pressed_ScriptEvent.Broadcast(Key);
}

void UCsManager_Input_Default::OnAnyKey_Released(FKey Key)
{
	OnAnyKey_Released_Event.Broadcast(Key);
	OnAnyKey_Released_ScriptEvent.Broadcast(Key);
}

void UCsManager_Input_Default::OnAction_Pressed(const FECsInputAction& Action, const FKey& Key)
{
	FCsInputInfo& Info   = InputActionEventInfos[Action.GetValue()];
	ECsInputEvent& Event = Info.Event;

	Event = ECsInputEvent::FirstPressed;

	Info.Key = Key;
	
	Info.MarkDirty();
}

void UCsManager_Input_Default::OnAction_Released(const FECsInputAction& Action, const FKey& Key)
{
	FCsInputInfo& Info	 = InputActionEventInfos[Action.GetValue()];
	ECsInputEvent& Event = Info.Event;

	Event = ECsInputEvent::FirstReleased;

	Info.MarkDirty();
}

void UCsManager_Input_Default::OnTouchAction_Pressed(ETouchIndex::Type Index, FVector3d Location)
{
	typedef NCsMath::FLibrary MathLibrary;

	const FECsInputAction& Action = TouchActions[(uint8)Index];

	FCsInputInfo& Info   = InputActionEventInfos[Action.GetValue()];
	ECsInputEvent& Event = Info.Event;

	Info.ResetLocation();

	Info.Location = MathLibrary::Convert(Location);

	Event = ECsInputEvent::FirstPressed;

	Info.MarkDirty();
}

void UCsManager_Input_Default::OnTouchAction_Released(ETouchIndex::Type Index, FVector3d Location)
{
	typedef NCsMath::FLibrary MathLibrary;

	const FECsInputAction& Action = TouchActions[(uint8)Index];

	FCsInputInfo& Info	 = InputActionEventInfos[Action.GetValue()];
	ECsInputEvent& Event = Info.Event;

	Info.ResetLocation();

	Info.Location = MathLibrary::Convert(Location);

	Event = ECsInputEvent::FirstReleased;

	Info.MarkDirty();
}

void UCsManager_Input_Default::OnAxis(const FECsInputAction& Action, const float& Value)
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

	Info.MarkDirty();
}

#pragma endregion Listener

// Actions
#pragma region

#pragma endregion Actions

// Game Events
#pragma region

void UCsManager_Input_Default::CreateGameEventDefinitionSimple(TArray<FCsGameEventDefinition>& Definitions, const FECsGameEvent& GameEvent, const FECsInputAction& Action, const ECsInputEvent& Event)
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

void UCsManager_Input_Default::FCurrentMode::SetValue(const FString& Context, const ECsInputMode& Mode)
{
	Last_Value = Value;

	CS_SET_BLUEPRINT_BITFLAG(Value, Mode);

	if (Last_Value != Value)
		OnChange_Event.Broadcast(Last_Value, Value);
}

void UCsManager_Input_Default::FCurrentMode::SetValue(const FString& Context, const int32& Mode)
{
	checkf(Mode >= 0, TEXT("%s: Mode: %s is NOT Valid."), *Context, Mode);

	Last_Value = Value;

	CS_SET_BLUEPRINT_BITFLAG(Value, Mode);

	if (Last_Value != Value)
		OnChange_Event.Broadcast(Last_Value, Value);
}

void UCsManager_Input_Default::FCurrentMode::ClearValue(const FString& Context, const ECsInputMode& Mode)
{
	Last_Value = Value;

	CS_CLEAR_BLUEPRINT_BITFLAG(Value, Mode);

	if (Last_Value != Value)
		OnChange_Event.Broadcast(Last_Value, Value);
}

void UCsManager_Input_Default::FCurrentMode::ClearValue(const FString& Context, const int32& Mode)
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

void UCsManager_Input_Default::FActiveMode::OnPostProcessInput(const float& DeltaTime, const bool bGamePaused)
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
		Outer->OnActiveMode_Change_ScriptEvent.Broadcast(Last_Value, Value);
	}

	Last_Value = Value;
}

void UCsManager_Input_Default::FActiveMode::PrintSet(const FString& Context, const FECsInputAction& Action, const FCsInputInfo& Info, const ECsInputMode& Mode)
{
	if (CS_CVAR_LOG_IS_SHOWING(LogInputActiveMode))
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

void UCsManager_Input_Default::FActiveMode::PrintSummary(const FString& Context)
{
	if (CS_CVAR_LOG_IS_SHOWING(LogInputActiveMode))
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Value (%s) -> (%s)"), *Context, *(EMCsInputMode::Get().MaskToString(Last_Value)), *(EMCsInputMode::Get().MaskToString(Value)));
	}
}

#pragma endregion Active

#pragma endregion Mode

// Profile
#pragma region

void UCsManager_Input_Default::SetDefaultInputProfile()
{
	// TODO: NOTE: FUTURE: May need to distinguish between 1 Player, 2 Player, ... etc

	UPlayerInput* PlayerInput = OwnerAsController->PlayerInput;

	// Check Actions
	for (const FInputActionKeyMapping& Mapping : PlayerInput->ActionMappings)
	{
		const FECsInputAction& Action = EMCsInputAction::Get().GetEnum(Mapping.ActionName);

		FCsInputActionMappings* Mappings = nullptr;

		// Gamepad
		if (Mapping.Key.IsGamepadKey())
		{
			Mappings = DefaultInputProfile.GetMappingsPtr(ECsInputDevice::Gamepad);
		}
		// Mouse
		else
		if (Mapping.Key.IsMouseButton())
		{
			Mappings = DefaultInputProfile.GetMappingsPtr(ECsInputDevice::MouseAndKeyboard);
		}
		// Touch - Do Nothing for now
		else
		if (Mapping.Key.IsTouch())
		{
			// Do Nothing
		}
		// Keyboard
		else
		{
			Mappings = DefaultInputProfile.GetMappingsPtr(ECsInputDevice::MouseAndKeyboard);
		}

		if (Mappings)
		{
			FCsInputActionMapping& Map = Mappings->GetOrAddMapping(Action);
			Map.Key					  = Mapping.Key;
		}
	}

	// Check Axis
	for (const FInputAxisKeyMapping& Mapping : PlayerInput->AxisMappings)
	{
		const FECsInputAction& Action = EMCsInputAction::Get().GetEnum(Mapping.AxisName);

		FCsInputActionMappings* Mappings = nullptr;

		// Gamepad
		if (Mapping.Key.IsGamepadKey())
		{
			Mappings = DefaultInputProfile.GetMappingsPtr(ECsInputDevice::Gamepad);
		}
		// Mouse
		else
		if (Mapping.Key.IsMouseButton())
		{
			Mappings = DefaultInputProfile.GetMappingsPtr(ECsInputDevice::MouseAndKeyboard);
		}
		// Touch - Do Nothing for now
		else
		if (Mapping.Key.IsTouch())
		{
			// Do Nothing
		}
		// Keyboard
		else
		{
			Mappings = DefaultInputProfile.GetMappingsPtr(ECsInputDevice::MouseAndKeyboard);
		}

		if (Mappings)
		{
			FCsInputActionMapping& Map = Mappings->GetOrAddMapping(Action);
			Map.Key					   = Mapping.Key;
			Map.Scale				   = Mapping.Scale;
		}
	}
}

bool UCsManager_Input_Default::CanSaveInputActionMapping(const ECsInputDevice& Device, const FECsInputAction& Action)
{
	return true;
}

FString UCsManager_Input_Default::GetSavePath()
{
	return FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir()) + TEXT("/");
}

FString UCsManager_Input_Default::GetInputProfileFilenameAndPath()
{
	return GetSavePath() + TEXT("InputProfile") + FString::FromInt(ControllerId) + TEXT(".json");
}

void UCsManager_Input_Default::SaveInputProfile()
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

void UCsManager_Input_Default::LoadDefaultInputProfile()
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

void UCsManager_Input_Default::LoadInputProfile()
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
					//Mapping.Key	= GetKey(Mapping.KeyName);
				}
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Input_Default::LoadInputProfile: %s is NOT Valid"), *InputProfileFilename);
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Input_Default::LoadInputProfile: %s NOT found. Loading Default Input Profile."), *InputProfileFilename);

		LoadDefaultInputProfile();
	}
}

bool UCsManager_Input_Default::IsValidKey(const ECsInputDevice& Device, const FKey& Key)
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

const FKey& UCsManager_Input_Default::GetKey(const FString& KeyName)
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

const FECsInputAction& UCsManager_Input_Default::GetActionFromKey(const ECsInputDevice& Device, const FKey& Key)
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

const FKey& UCsManager_Input_Default::GetKeyFromAction(const ECsInputDevice& Device, const FECsInputAction& Action)
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

const FKey& UCsManager_Input_Default::GetKeyFromAction(const FECsInputAction& Action)
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

void UCsManager_Input_Default::UnbindActionMapping(const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key)
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
			Mapping.Key	= EKeys::Invalid;
			break;
		}
	}
	PlayerInput->ForceRebuildingKeyMaps(false);
}

void UCsManager_Input_Default::UnbindAxisMapping(const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key)
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
			Mapping.Key = EKeys::Invalid;
			break;
		}
	}
	PlayerInput->ForceRebuildingKeyMaps(false);
}

void UCsManager_Input_Default::UnbindMapping(const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key)
{
	if (Infos[Action.Value]->Type == ECsInputType::Action)
		UnbindActionMapping(Device, Action, Key);
	if (Infos[Action.Value]->Type == ECsInputType::Axis)
		UnbindAxisMapping(Device, Action, Key);
}

// TODO: Need to store the original Key "Keyboard" mappings for Input. Do similar for control setup

void UCsManager_Input_Default::RebindActionMapping(const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key)
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

void UCsManager_Input_Default::RebindAxisMapping(const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key)
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

void UCsManager_Input_Default::RebindMapping(const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key)
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

void UCsManager_Input_Default::RunEditorGameBatchConsoleCommands_FirstPressed()
{
	OnRunEditorGameBatchConsoleCommands_FirstPressed_Event.Broadcast();
}

void UCsManager_Input_Default::RunEditorGameJavascriptFile_FirstPressed()
{
	OnRunEditorGameJavascriptFile_FirstPressed_Event.Broadcast();
}

#pragma endregion Editor Game

#endif // #if WITH_EDITOR