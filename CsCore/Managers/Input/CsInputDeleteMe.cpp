#include "Public/Managers/Input/CsManager_Input.h"
#include "CsCore.h"
#include "CsCVars.h"

#include "Engine/Classes/Engine/World.h"

#include "Classes/Components/InputComponent.h"
#include "Classes/Engine/DataTable.h"
#include "Classes/Engine/UserDefinedStruct.h"

#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerInput.h"

// Cached
#pragma region

namespace NCsManagerInputCached
{
	namespace Str
	{
		const FString PostProcessInput = TEXT("PostProcessInput");
	}
}

#pragma endregion Cached

ACsManager_Input::ACsManager_Input(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;

	// Action Map
	CurrentInputActionMap = 0;
}

void ACsManager_Input::Init()
{
	SetupInputActionEventInfoMap();
	SetupInputActionMapping();
	SetupGameEventDefinitions();

	// Initialize CurrentGameEventInfos
	const int32 EventCount = GameEventPriorityList.Num();

#if WITH_EDITOR
	if (EMCsGameEvent::Get().Num() != EventCount)
	{

	}
#endif // #if WITH_EDITOR

	CurrentGameEventInfos.Reserve(EventCount);

	for (int32 I = 0; I < EventCount; ++I)
	{
		CurrentGameEventInfos.AddDefaulted();
		CurrentGameEventInfos.Last().Reset();
	}

	// Update GameEventPriorityMap
	for (int32 I = 0; I < EventCount; ++I)
	{
		const FECsGameEvent& Event = GameEventPriorityList[I];

		GameEventPriorityMap.Add(Event, I);
	}
}

void ACsManager_Input::SetupInputCompoonet()
{
	if (!InputComponent)
	{
		InputComponent = NewObject<UInputComponent>(this, TEXT("InputComponent"));
		InputComponent->RegisterComponent();
	}
}

void ACsManager_Input::PreProcessInput(const float DeltaTime, const bool bGamePaused)
{
	CurrentInputFrame.Inputs.Reset();
	CurrentInputFrame.Time = GetWorld()->GetTimeSeconds();
	CurrentInputFrame.RealTime = GetWorld()->GetRealTimeSeconds();

	UPlayerInput* PlayerInput = MyOwner->PlayerInput;

	TArray<FECsInputAction> Keys;
	InputActionEventInfoMap.GetKeys(Keys);

	for (const FECsInputAction& Action : Keys)
	{
		FCsInputEventInfo& Info = InputActionEventInfoMap[Action];

		Info.EndEvaluation();
	}

	// Check Actions
	for (const FInputActionKeyMapping& Mapping : PlayerInput->ActionMappings)
	{
		const FECsInputAction& Action	= EMCsInputAction::Get()[Mapping.ActionName];
		FCsInputEventInfo& Info			= InputActionEventInfoMap[Action];
		ECsInputEvent& Event			= Info.Event;

		if (Info.IsEvaluated())
			continue;

		Info.StartEvaluation();

		// Pressed
		if (PlayerInput->IsPressed(Mapping.Key))
		{
			// (FirstReleased | Released) -> FirstPressed
			if (Event == ECsInputEvent::FirstReleased ||
				Event == ECsInputEvent::Released)
			{
				Event = ECsInputEvent::FirstPressed;
			}
			// FirstPressed -> Pressed
			else
			if (Event == ECsInputEvent::FirstPressed)
			{
				Event = ECsInputEvent::Pressed;
			}
		}
		// Released
		else
		{
			// (FirstPressed | Pressed) -> FirstReleased
			if (Event == ECsInputEvent::FirstPressed ||
				Event == ECsInputEvent::Pressed)
			{
				Event = ECsInputEvent::FirstReleased;
			}
			// FirstReleased -> Released
			else
			if (Event == ECsInputEvent::FirstReleased)
			{
				Event = ECsInputEvent::Released;
			}
		}

		if (Info.HasEventChanged())
		{
#if WITH_EDITOR
			if (CsCVarLogManagerInputRawInput->GetInt() >= CS_CVAR_SHOW_LOG ||
				CsCVarLogManagerInputRawInputAction->GetInt() >= CS_CVAR_SHOW_LOG)
			{
				const float& Time			= CurrentInputFrame.Time;
				const FString& CurrentEvent = EMCsInputEvent::Get().ToString(Info.Event);
				const FString& LastEvent	= EMCsInputEvent::Get().ToString(Info.Last_Event);

				UE_LOG(LogCsCore, Warning, TEXT("ACsManager_Input::PreProcessInput (%s): Time: %f. Action: %s[%s]. Event: %s -> %s."), *(MyOwner->GetName()), Time, *Action.Name, *(Mapping.Key.ToString()), *LastEvent, *CurrentEvent);
			}
#endif // #if WITH_EDITOR

			TryAddInput(Info.Type, Action, Event);
		}
#if WITH_EDITOR
		else
		{
			if (CsCVarLogManagerInputRawInput->GetInt() >= CS_CVAR_SHOW_LOG_INPUT_ALL ||
				CsCVarLogManagerInputRawInputAction->GetInt() >= CS_CVAR_SHOW_LOG_INPUT_ALL)
			{
				const float& Time			= CurrentInputFrame.Time;
				const FString& CurrentEvent = EMCsInputEvent::Get().ToString(Info.Event);

				UE_LOG(LogCsCore, Warning, TEXT("ACsManager_Input::PreProcessInput (%s): Time: %f. Action: %s[%s]. Event: %s."), *(MyOwner->GetName()), Time, *(Action.Name), *(Mapping.Key.ToString()), *CurrentEvent);
			}
		}
#endif // #if WITH_EDITOR
		Info.FlushEvent();
	}

	// Check Axis
	for (const FInputAxisKeyMapping& Mapping : PlayerInput->AxisMappings)
	{
		const FECsInputAction& Action = EMCsInputAction::Get()[Mapping.AxisName];
		FCsInputEventInfo& Info		  = InputActionEventInfoMap[Action];
		ECsInputEvent& Event		  = Info.Event;

		if (Info.IsEvaluated())
			continue;

		Info.StartEvaluation();

		// TODO: Handle FirstMoved and FirstStationary

		const float Value = PlayerInput->GetKeyValue(Mapping.Key);

#if WITH_EDITOR
		if (CsCVarLogManagerInputRawInput->GetInt() >= CS_CVAR_SHOW_LOG ||
			CsCVarLogManagerInputRawInputAxis->GetInt() >= CS_CVAR_SHOW_LOG)
		{
			const float& Time			= CurrentInputFrame.Time;
			const FString& CurrentEvent = EMCsInputEvent::Get().ToString(Info.Event);

			UE_LOG(LogCsCore, Warning, TEXT("ACsManager_Input::PreProcessInput (%s): Time: %f. Action: %s[%s]. Event: %s. Value: %f"), *(MyOwner->GetName()), Time, *(Action.Name), *(Mapping.Key.ToString()), *CurrentEvent, Value);
		}
#endif // #if WITH_EDITOR

		TryAddInput(Info.Type, Action, Event, Value);
		Info.FlushEvent();
	}
}

void ACsManager_Input::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	// Add Queue Inputs
	for (const FCsInput& Input : QueuedInputsForNextFrame)
	{
		CurrentInputFrame.Inputs.Add(Input);
	}
	QueuedInputsForNextFrame.Reset();

	// TODO: Need to rework how events are being fired. Not just firing from TryAddInput

#if WITH_EDITOR
	for (const FCsInput& Input : CurrentInputFrame.Inputs)
	{
		const FECsInputAction& Action	= Input.Action;
		const ECsInputEvent& Event		= Input.Event;
		const FCsInputEventInfo& Info	= InputActionEventInfoMap[Action];
		const ECsInputType& Type		= Info.Type;

		const bool ShowLog = CsCVarLogManagerInputAll->GetInt() == CS_CVAR_SHOW_LOG ||
							 (Type == ECsInputType::Action && CsCVarLogManagerInputAction->GetInt() == CS_CVAR_SHOW_LOG) ||
							 (Type == ECsInputType::Axis && CsCVarLogManagerInputAxis->GetInt() == CS_CVAR_SHOW_LOG);

		if (ShowLog)
		{
			const float& Time			 = CurrentInputFrame.Time;
			const FString& EventAsString = EMCsInputEvent::Get().ToString(Input.Event);

			UE_LOG(LogCsCore, Warning, TEXT("ACsManager_Input::PostProcessInput (%s): Time: %f. Action: %s Event: %s."), *(MyOwner->GetName()), Time, *(Action.Name), *EventAsString);
		}
	}
#endif // #if WITH_EDITOR

	// Reset CurrentGameEventInfos
	for (FCsGameEventInfo& Info : CurrentGameEventInfos)
	{
		Info.Reset();
	}
	CurrentValidGameEventInfos.Reset();

	// Process GameEventDefinitions
	TArray<FECsGameEvent> Keys;
	GameEventDefinitions.GetKeys(Keys);

	for (const FECsGameEvent& Event : Keys)
	{
		FCsInputSentence& Sentence = GameEventDefinitions[Event];

		Sentence.ProcessInput(CurrentInputFrame);

		if (Sentence.bCompleted)
		{
			const int32& Index				   = GameEventPriorityMap[Event];
			CurrentGameEventInfos[Index].Event = Event;

#if WITH_EDITOR
			LogProcessGameEventDefinition(NCsManagerInputCached::Str::PostProcessInput, Event, Sentence);
#endif // #if WITH_EDITOR
		}
	}

	// Process Queue GameEvents
	for (const FCsGameEventInfo& Info : QueuedGameEventInfosForNextFrame)
	{
		const FECsGameEvent& Event = Info.Event;
		const int32& Index		   = GameEventPriorityMap[Event];

		CurrentGameEventInfos[Index] = Info;
	}
	QueuedGameEventInfosForNextFrame.Reset();

	for (const FCsGameEventInfo& Info : CurrentGameEventInfos)
	{
		if (Info.IsValid())
		{
			CurrentValidGameEventInfos.Add(Info);

#if WITH_EDITOR
			if (CsCVarLogManagerInputGameEvents->GetInt() == CS_CVAR_SHOW_LOG)
			{
				const float& Time = CurrentInputFrame.Time;

				UE_LOG(LogCsCore, Warning, TEXT("ACsManager_Input::PostProcessInput (%s): Time: %f. Event: %s."), *(MyOwner->GetName()), Time, *(Info.Event.Name));
			}
#endif // #if WITH_EDITOR
		}
	}
}

void ACsManager_Input::QueueInput(FECsInputAction Action, ECsInputEvent Event, float Value /*= 0.0f*/, FVector Location /*= FVector::ZeroVector*/, FRotator Rotation /*= FRotator::ZeroRotator*/)
{
	QueuedInputsForNextFrame.AddDefaulted();
	FCsInput& Input = QueuedInputsForNextFrame.Last();
	Input.Action = Action;
	Input.Event = Event;
	Input.Value = Value;
	Input.Location = Location;
	Input.Rotation = Rotation;
}

bool ACsManager_Input::TryAddInput(const ECsInputType& Type, const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value /*= 0.0f*/, const FVector& Location /*= FVector::ZeroVector*/, const FRotator& Rotation /*= FRotator::ZeroRotator*/)
{
	if (CanAddInput(Action))
	{
		ECsInputEvent OutEvent = ProcessInputEvent(Type, Action, Event, Value, Location, Rotation);

		AddInput(Action, OutEvent, Value, Location, Rotation);

		// Action
		if (Type == ECsInputType::Action)
			OnAction_ScriptEvent.Broadcast(Action, OutEvent);
		// Axis
		if (Type == ECsInputType::Axis)
			OnAxis_ScriptEvent.Broadcast(Action, Value);
		return true;
	}
	return false;
}

bool ACsManager_Input::CanAddInput(const FECsInputAction& Action)
{
	if (InputActionMapping.Find(Action) == nullptr)
	{
#if WITH_EDITOR
#endif // #if WITH_EDITOR
		return false;
	}
	return (CurrentInputActionMap & InputActionMapping[Action]) > 0;
}

ECsInputEvent ACsManager_Input::ProcessInputEvent(const EXaInputType& Type, const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value, const FVector& Location, const FRotator& Rotation)
{
	return Event;
}

void ACsManager_Input::AddInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value /*= 0.0f*/, const FVector& Location /*= FVector::ZeroVector*/, const FRotator& Rotation /*= FRotator::ZeroRotator*/)
{
	CurrentInputFrame.Inputs.AddDefaulted();
	FCsInput& Input = CurrentInputFrame.Inputs.Last();
	Input.Action = Action;
	Input.Event = Event;
	Input.Value = Value;
	Input.Location = Location;
	Input.Rotation = Rotation;
}

// Action Map
#pragma region

void ACsManager_Input::SetupInputActionEventInfoMap()
{
	UPlayerInput* PlayerInput = MyOwner->PlayerInput;

	const int32& ActionCount = EMCsInputAction::Get().Num();

	for (int32 I = 0; I < ActionCount; ++I)
	{
		const FECsInputAction& Action = EMCsInputAction::Get().GetEnumAt(I);
		FCsInputEventInfo Info;
		Info.Type		= ECsInputType::ECsInputType_MAX;
		Info.ValueType	= ECsInputValue::Void;
		Info.Event		= ECsInputEvent::ECsInputEvent_MAX;
		Info.Last_Event = ECsInputEvent::ECsInputEvent_MAX;

		InputActionEventInfoMap.Add(Action, Info);

		FCsInputEventInfo& EventInfo = InputActionEventInfoMap[Action];

		bool Found = false;

		// Check Actions
		for (const FInputActionKeyMapping& Mapping : PlayerInput->ActionMappings)
		{
			if (Action.Name_Internal == Mapping.ActionName)
			{
				EventInfo.Type		= ECsInputType::Action;
				EventInfo.Event		= ECsInputEvent::Released;
				EventInfo.Last_Event = ECsInputEvent::Released;
			}
		}

		if (Found)
			continue;

		// Check Axis
		for (const FInputAxisKeyMapping& Mapping : PlayerInput->AxisMappings)
		{
			if (Action.Name_Internal == Mapping.AxisName)
			{
				EventInfo.Type		= ECsInputType::Axis;
				EventInfo.Event		= ECsInputEvent::Stationary;
				EventInfo.Last_Event = ECsInputEvent::Stationary;
			}
		}
	}
}

void ACsManager_Input::SetupInputActionMapping()
{
	// Populate InputActionMappings from Blueprint version
	const int32& MapCount = EMCsInputActionMap::Get().Num();

	for (int32 I = 0; I < MapCount; ++I)
	{
		const FECsInputActionMap& Map = EMCsInputActionMap::Get().GetEnumAt(I);

		TArray<FName> Names;
		BP_GetInputActionNamesFromMapping(Map, Names);

		InputActionMappings.Add(Map);

#if WITH_EDITOR
		if (Names.Num() == CS_EMPTY)
		{
			UE_LOG(LogCsCore, Warning, TEXT("ACsManager_Input::SetupGameEventDefinitions (%s): No InputActions set for Map: %s."), *(MyOwner->GetName()), *(Map.Name));
		}
#endif // #if WITH_EDITOR

		for (const FName& Name : Names)
		{
			const FECsInputAction& Action = EMCsInputAction::Get().GetEnum(Name);

			InputActionMappings[Map].Add(Action);
		}

		const int32 Mask = 1 << static_cast<int32>(Map);
		const TSet<FECsInputAction>& Actions = InputActionMappings[Map];

		// Initialize InputActionMapping
		for (const FECsInputAction& Action : Actions)
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

void ACsManager_Input::BP_GetInputActionNamesFromMapping_Implementation(const FECsInputActionMap& Map, TArray<FName>& OutNames)
{
}

void ACsManager_Input::SetInputActionMappingByMap(FECsInputActionMap Map)
{
	CurrentInputActionMap |= 1 << static_cast<int32>(Map);
}

#pragma endregion Action Map

// Events
#pragma region

void ACsManager_Input::SetupGameEventDefinitions()
{
	const int32& Count = EMCsGameEvent::Get().Num();

	for (int32 I = 0; I < Count; ++I)
	{
		const FECsGameEvent& Event = EMCsGameEvent::Get().GetEnumAt(I);

		FCsGameEventDefinitionSimpleInfo Def;
		BP_GetGameEventDefinitionSimpleFromGameEvent(Event, Def);

		if (Def.IsValid())
		{
			if (!GameEventDefinitions.Find(Event))
			{
				GameEventDefinitions.Add(Event);
			}

			GameEventDefinitions[Event].Reset();
			GameEventDefinitions[Event].Phrases.AddDefaulted();
			GameEventDefinitions[Event].Phrases[CS_FIRST].AddAndInputToWord(CS_FIRST, Def.Action, NCsInputEvent::ToType(Def.Event));
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCsCore, Warning, TEXT("ACsManager_Input::SetupGameEventDefinitions (%s): No GameEventDefinition set for GameEvent: %s."), *(MyOwner->GetName()), *(Event.Name));
		}
#endif // #if WITH_EDITOR
	}
}

void ACsManager_Input::BP_GetGameEventDefinitionSimpleFromGameEvent_Implementation(const FECsGameEvent& Event, FCsGameEventDefinitionSimpleInfo& Def)
{
}

#if WITH_EDITOR

void ACsManager_Input::LogProcessGameEventDefinition(const FString& FunctionName, const FECsGameEvent& Event, const FCsInputSentence& Sentence)
{
	if (CsCVarLogManagerInputGameEventDefinitions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		// For now handle a simple definition

		if (Sentence.Phrases.Num() > CS_EMPTY &&
			Sentence.Phrases[CS_FIRST].Words.Num() > CS_EMPTY &&
			Sentence.Phrases[CS_FIRST].Words[CS_FIRST].AndInputs.Num() > CS_EMPTY)
		{
			const FCsInput& Input			  = Sentence.Phrases[CS_FIRST].Words[CS_FIRST].AndInputs[CS_FIRST];
			const FECsInputAction& Action	  = Input.Action;
			const FString& InputEventAsString = EMCsInputEvent::Get().ToString(Input.Event);

			const float& Time = CurrentInputFrame.Time;
	
			UE_LOG(LogR6Master, Warning, TEXT("ACsManager_Input::%s (%s): Time: %f. (%s, %s) -> %s."), *FunctionName, *(MyOwner->GetName()), Time, *(Action.Name), *InputEventAsString, *(Event.Name));
		}
	}
}

#endif // #if WITH_EDITOR

void ACsManager_Input::QueueGameEvent(const FECsGameEvent& Event)
{
	QueuedGameEventInfosForNextFrame.AddDefaulted();
	QueuedGameEventInfosForNextFrame.Last().Event = Event;
}

#pragma endregion Events
