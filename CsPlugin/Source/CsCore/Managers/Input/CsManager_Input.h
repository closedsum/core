// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Classes/Components/ActorComponent.h"
#include "Managers/Input/CsTypes_Input.h"
#include "CsManager_Input.generated.h"

#define CS_INPUT_POOL_SIZE 65535
#define CS_MAX_INPUT_FRAMES 300

// TODO: Future: It doesn't seem necessary to have a "generic" call back that takes in the action and event at this point

// Input Delegates
#pragma region

	// Pressed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerInput_Action, const FECsInputAction&, Action, const ECsInputEvent&, Event);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerInput_FirstPressed, const FECsInputAction&, Action);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerInput_Pressed, const FECsInputAction&, Action);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerInput_FirstReleased, const FECsInputAction&, Action);

	// Axis
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsManagerInput_Axis, const FECsInputAction&, Action, const ECsInputEvent&, Event, const float&, Val);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerInput_Axis_FirstMoved, const FECsInputAction&, Action, const float&, Val);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerInput_Axis_Moved, const FECsInputAction&, Action, const float&, Val);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerInput_Axis_FirstStationary, const FECsInputAction&, Action, const float&, Val);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerInput_Axis_Stationary, const FECsInputAction&, Action, const float&, Val);

	// Location
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsManagerInput_Location, const FECsInputAction&, Action, const ECsInputEvent&, Event, const FVector&, Location);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerInput_Location_FirstMoved, const FECsInputAction&, Action, const FVector&, Location);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerInput_Location_Moved, const FECsInputAction&, Action, const FVector&, Location);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerInput_Location_FirstStationary, const FECsInputAction&, Action, const FVector&, Location);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerInput_Location_Stationary, const FECsInputAction&, Action, const FVector&, Location);

DECLARE_DELEGATE_OneParam(FBindableCall_CsManagerInput_Location_Raw, const FVector&);

	// Rotation
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsManagerInput_Rotation, const FECsInputAction&, Action, const ECsInputEvent&, Event, const FRotator&, Rotation);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerInput_Rotation_FirstMoved, const FECsInputAction&, Action, const FRotator&, Rotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerInput_Rotation_Moved, const FECsInputAction&, Action, const FRotator&, Rotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerInput_Rotation_FirstStationary, const FECsInputAction&, Action, const FRotator&, Rotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerInput_Rotation_Stationary, const FECsInputAction&, Action, const FRotator&, Rotation);

DECLARE_DELEGATE_OneParam(FBindableCall_CsManagerInput_Rotation_Raw, const FRotator&);

// Macros - Should ONLY be used for testing
#pragma region

#define CS_DEFINE_INPUT_ACTION_VALUES(INPUT, MAP)	DefineInputValues<UCsInput_Action>(INPUT, EMCsInputAction::Get().GetEnum(FString(#INPUT)), MAP)

#define CS_BIND_ACTION_INPUT(INPUT) InputComponent->BindAction(#INPUT, IE_Pressed, INPUT, &UCsInput_Action::FirstPressed).bConsumeInput = false; \
									InputComponent->BindAction(#INPUT, IE_Released, INPUT, &UCsInput_Action::FirstReleased).bConsumeInput = false;

#define CS_IS_INPUT_ACTION_FIRST_PRESSED(Input, ACTION) Input->Action == ECsInputAction::ACTION && Input->Event == ECsInputEvent::FirstPressed


#define CS_DEFINE_INPUT_AXIS_VALUES_OLD(INPUT)	Infos[ECsInputAction::INPUT] = &INPUT; \
												INPUT.Type = ECsInputType::Axis; \
												INPUT.ValueType = ECsInputValue::Float; \
												Actions[ECsInputAction::INPUT] = &INPUT.Event; \
												INPUT.Event = ECsInputEvent::Stationary; \
												Last_Actions[ECsInputAction::INPUT] = &INPUT.Last_Event; \
												INPUT.Last_Event = ECsInputEvent::Stationary; \

#define CS_DEFINE_INPUT_AXIS_VALUES(INPUT, MAP)	DefineInputValues<UCsInput_Axis>(INPUT, EMCsInputAction::Get().GetEnum(FString(#INPUT)), MAP)

#define CS_BIND_AXIS_INPUT(INPUT) InputComponent->BindAxis(#INPUT, INPUT, &UCsInput_Axis::Raw).bConsumeInput = false

#define CS_DEFINE_INPUT_TRIGGER_VALUES(INPUT, MAP)	DefineInputValues<UCsInput_Trigger>(INPUT, EMCsInputAction::Get().GetEnum(FString(#INPUT)), MAP)

#define CS_BIND_TRIGGER_INPUT(INPUT) InputComponent->BindAxis(#INPUT, INPUT, &UCsInput_Trigger::Raw).bConsumeInput = false;

#define CS_DEFINE_INPUT_LOCATION_VALUES(INPUT, MAP)	DefineInputValues<UCsInput_Location>(INPUT, EMCsInputAction::Get().GetEnum(FString(#INPUT)), MAP)

#define CS_DEFINE_INPUT_ROTATION_VALUES(INPUT, MAP)	DefineInputValues<UCsInput_Rotation>(INPUT, EMCsInputAction::Get().GetEnum(FString(#INPUT)), MAP)

#pragma endregion Macros

#pragma endregion Input Delegates

// Game Action Delegates

class AActor;
class APlayerController;

UCLASS(Blueprintable)
class CSCORE_API UCsManager_Input : public UActorComponent
{
	GENERATED_UCLASS_BODY()

	virtual void Init();

	static UCsManager_Input* Get(UWorld* World, const int32& Index = INDEX_NONE);

// UActorComponent Interface
#pragma region
protected:

	virtual void OnRegister() override;

#pragma endregion UActorComponent Interface

// Owner
#pragma region
public:

	UPROPERTY(BlueprintReadOnly, Category = "Manager|Input|Owner")
	APlayerController* OwnerAsController;

	UPROPERTY(BlueprintReadOnly, Category = "Owner")
	int32 ControllerId;

#pragma endregion Owner

	virtual void PreProcessInput(const float DeltaTime, const bool bGamePaused);
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused);
	virtual void ProcessInput(AActor* ActionOwner, const struct FCsInput* PreviousInput, const struct FCsInput* CurrentInput, const float DeltaTime);

	float CurrentDeltaTime;

	FCsInput InputPool[CS_INPUT_POOL_SIZE];

	FCsInput* AllocateInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value = 0.0f, const FVector& Location = FVector::ZeroVector, const FRotator& Rotation = FRotator::ZeroRotator);

	void AddInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value=0.0f, const FVector& Location=FVector::ZeroVector, const FRotator& Rotation=FRotator::ZeroRotator);

	bool CanAddInput(const FECsInputAction& Action);

	bool TryAddInput(const ECsInputType& Type, const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value = 0.0f, const FVector& Location = FVector::ZeroVector, const FRotator& Rotation = FRotator::ZeroRotator);

	const ECsInputEvent& ProcessInputEvent(const ECsInputType& Type, const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value, const FVector& Location, const FRotator& Rotation);

	TArray<FCsInput*> QueuedInputsForNextFrame;

	void QueueInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value = 0.0f, const FVector& Location = FVector::ZeroVector, const FRotator& Rotation = FRotator::ZeroRotator);

	void ConsumeInput(const FECsInputAction& Action);

	uint16 CurrentInputPoolIndex;

	FCsInputFrame InputFrames[CS_MAX_INPUT_FRAMES];

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	int32 CurrentInputFrameIndex;

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	FCsInputFrame CurrentInputFrame;

// Action Map
#pragma region
public:

	TMap<FECsInputAction, FCsInputInfo> InputActionEventInfoMap;

	void SetupInputActionEventInfoMap();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Manager|Input|Action Map")
	TMap<FECsInputActionMap, FCsInputActionSet> InputActionMappings;

	void SetupInputActionMapping();

	UPROPERTY(BlueprintReadOnly, Category = "Manager|Input|Action Map")
	TMap<FECsInputAction, int32> InputActionMapping;

	UPROPERTY(BlueprintReadWrite, Category = "Manager|Input|Action Map")
	int32 CurrentInputActionMap;

	UFUNCTION(BlueprintCallable, Category = "Manager|Input|Action Map")
	void SetCurrentInputActionMap(const FECsInputActionMap& Map);
	void SetCurrentInputActionMap(const int32& Map);

	UFUNCTION(BlueprintCallable, Category = "Manager|Input|Action Map")
	void ClearCurrentInputActionMap(const FECsInputActionMap& Map);
	void ClearCurrentInputActionMap(const int32& Map);

#pragma endregion Action Map

	TArray<FKey> PressedKeys;

	FCsInput* GetPreviousInputAction(const FECsInputAction& Action);
	FCsInput* GetPreviousInputAction(const FECsInputAction& Action, const ECsInputEvent& Event);
	FCsInput* GetPreviousInputAction(const FECsInputAction& Action, const TArray<ECsInputEvent>& Events);
	FCsInput* GetPreviousPreviousInputAction(const FECsInputAction& Action);

// Events
#pragma region
public:

	UPROPERTY(EditDefaultsOnly, Category = "Events")
	TSet<FCsGameEventDefinitionSimple> GameEventDefinitionsSimple;

	UPROPERTY(EditDefaultsOnly, Category = "Events")
	TSet<FCsGameEventDefinition> GameEventDefinitions;

	UPROPERTY(BlueprintReadOnly, Category = "Events")
	TMap<FECsGameEvent, FCsInputSentence> GameEventDefinitionMap;

	void SetupGameEventDefinitions();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Events")
	TArray<FECsGameEvent> GameEventPriorityList;

	UPROPERTY(BlueprintReadOnly, Category = "Events")
	TMap<FECsGameEvent, int32> GameEventPriorityMap;

	TArray<FCsGameEventInfo> CurrentGameEventInfos;

	UPROPERTY(BlueprintReadOnly, Category = "Events")
	TArray<FCsGameEventInfo> CurrentValidGameEventInfos;

	UPROPERTY(BlueprintReadOnly, Category = "Events")
	TArray<FCsGameEventInfo> QueuedGameEventInfosForNextFrame;

#if WITH_EDITOR
	void LogProcessGameEventDefinition(const FString& FunctionName, const FECsGameEvent& Event, const FCsInputSentence& Sentence);
#endif // #if WITH_EDITOR

	virtual void QueueGameEvent(const FECsGameEvent& Event);

	void ClearQueuedGameEvents();

	virtual void DetermineGameEvents(const TArray<FCsInput*>& InInputs);

	UFUNCTION(BlueprintCallable, Category = "Input")
	bool HasActionEventOccured(const FECsInputAction& Action, const ECsInputEvent& Event);

#pragma endregion Events

	UFUNCTION(BlueprintCallable, Category = "Input")
	float GetInputValue(const FECsInputAction& Action);
	UFUNCTION(BlueprintCallable, Category = "Input")
	FVector GetInputLocation(const FECsInputAction& Action);

	UFUNCTION(BlueprintCallable, Category = "Input")
	ECsInputEvent GetInputEvent(const FECsInputAction& Action);

	UFUNCTION(BlueprintCallable, Category = "Input")
	float GetInputDuration(const FECsInputAction& Action);

// Profile
#pragma region
public:

	virtual bool CanSaveInputActionMapping(const ECsInputDevice& Device, const FECsInputAction& Action);

	FCsInputProfile InputProfile;

	FString GetSavePath();
	FString GetInputProfileFilenameAndPath();

	void SaveInputProfile();
	void LoadDefaultInputProfile();
	void LoadInputProfile();

	bool IsValidKey(const ECsInputDevice& Device, const FKey& Key);

	struct FKey GetKey(const FString &KeyName);
	
	const FECsInputAction& GetActionFromKey(const ECsInputDevice& Device, const FKey& Key);
	FKey GetKeyFromAction(const ECsInputDevice& Device, const FECsInputAction& Action);
	FKey GetKeyFromAction(const FECsInputAction& Action);

	void UnbindActionMapping(const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key);
	void UnbindAxisMapping(const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key);
	void UnbindMapping(const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key);

	void RebindActionMapping(const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key);
	void RebindAxisMapping(const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key);
	void RebindMapping(const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key);

#pragma endregion Profile

#if WITH_EDITOR

// Editor Game
#pragma region
public:

	DECLARE_MULTICAST_DELEGATE(FOnRunEditorGameBatchConsoleCommands_FirstPressed);

	FOnRunEditorGameBatchConsoleCommands_FirstPressed OnRunEditorGameBatchConsoleCommands_FirstPressed_Event;

	void RunEditorGameBatchConsoleCommands_FirstPressed();

	DECLARE_MULTICAST_DELEGATE(FOnRunEditorGameJavascriptFile_FirstPressed);

	FOnRunEditorGameJavascriptFile_FirstPressed OnRunEditorGameJavascriptFile_FirstPressed_Event;

	void RunEditorGameJavascriptFile_FirstPressed();

#pragma endregion Editor Game

#endif // #if WITH_EDITOR

// Actions
#pragma region
protected:

	//CS_DECLARE_INPUT_ACTION

	TArray<class UCsInput_Base*> Inputs;

	TArray<FCsInputInfo*> Infos;

	TArray<ECsInputEvent*> Actions;
	TArray<ECsInputEvent*> Last_Actions;

	template<typename T>
	void DefineInputValues(T*& Input, const FECsInputAction& Action, const int32& ActionMap)
	{
		Input = NewObject<T>(GetWorld(), T::StaticClass(), *(Action.Name), RF_Transient);
		Input->AddToRoot();
		Input->Manager_Input = this;
		Input->ActionMap = ActionMap;
		Input->Action = Action;
		Inputs[Action.Value] = Input;
		Infos[Action.Value] = &(Input->Info);
		Actions[Action.Value] = &(Input->Info.Event);
		Last_Actions[Action.Value] = &(Input->Info.Last_Event);
	}

	// Pressed Events
#pragma region
public:

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FCsManagerInput_Action Action_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAction, AActor*, const FECsInputAction&, const ECsInputEvent&);

	FOnAction Action_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FCsManagerInput_FirstPressed FirstPressed_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FFirstPressed, AActor*, const FECsInputAction&);

	FFirstPressed FirstPressed_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FCsManagerInput_Pressed Pressed_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FPressed, AActor*, const FECsInputAction&);

	FPressed Pressed_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FCsManagerInput_FirstReleased FirstReleased_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FFirstReleased, AActor*, const FECsInputAction&);

	FFirstReleased FirstReleased_Event;

#pragma endregion

	// Axis Events
#pragma region
public:

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FCsManagerInput_Axis Axis_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_FourParams(FAxis, AActor*, const FECsInputAction&, const ECsInputEvent&, const float&);

	FAxis Axis_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FCsManagerInput_Axis_FirstMoved Axis_FirstMoved_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FAxis_FirstMoved, AActor*, const FECsInputAction&, const float&);

	FAxis_FirstMoved Axis_FirstMoved_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FCsManagerInput_Axis_Moved Axis_Moved_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FAxis_Moved, AActor*, const FECsInputAction&, const float&);

	FAxis_Moved Axis_Moved_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FCsManagerInput_Axis_FirstStationary Axis_FirstStationary_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FAxis_FirstStationary, AActor*, const FECsInputAction&, const float&);

	FAxis_FirstStationary Axis_FirstStationary_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FCsManagerInput_Axis_Stationary Axis_Stationary_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FAxis_Stationary, AActor*, const FECsInputAction&, const float&);

	FAxis_Stationary Axis_Stationary_Event;

#pragma endregion Axis Events

	// Location Events
#pragma region
public:

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FCsManagerInput_Location Location_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_FourParams(FLocation, AActor*, const FECsInputAction&, const ECsInputEvent&, const FVector&);

	FLocation Location_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FCsManagerInput_Location_FirstMoved Location_FirstMoved_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FLocation_FirstMoved, AActor*, const FECsInputAction&, const FVector&);

	FLocation_FirstMoved Location_FirstMoved_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FCsManagerInput_Location_Moved Location_Moved_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FLocation_Moved, AActor*, const FECsInputAction&, const FVector&);

	FLocation_Moved Location_Moved_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FCsManagerInput_Location_FirstStationary Location_FirstStationary_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FLocation_FirstStationary, AActor*, const FECsInputAction&, const FVector&);

	FLocation_FirstStationary Location_FirstStationary_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FCsManagerInput_Location_Stationary Location_Stationary_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FLocation_Stationary, AActor*, const FECsInputAction&, const FVector&);

	FLocation_Stationary Location_Stationary_Event;

	// Mouse

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	FVector CurrentMousePosition;

	FBindableCall_CsManagerInput_Location_Raw Mouse_Location_Raw;

	// VR

	FBindableCall_CsManagerInput_Location_Raw HMD_Location_Raw;
	FBindableCall_CsManagerInput_Location_Raw LeftHand_Location_Raw;
	FBindableCall_CsManagerInput_Location_Raw RightHand_Location_Raw;

#pragma endregion Location Events

	// Rotation Events
#pragma region
public:

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FCsManagerInput_Rotation Rotation_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_FourParams(FCsManagerInput_Rotation, AActor*, const FECsInputAction&, const ECsInputEvent&, const FRotator&);

	FCsManagerInput_Rotation Rotation_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FCsManagerInput_Rotation_FirstMoved Rotation_FirstMoved_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FCsManagerInput_Rotation_FirstMoved, AActor*, const FECsInputAction&, const FRotator&);

	FCsManagerInput_Rotation_FirstMoved Rotation_FirstMoved_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FCsManagerInput_Rotation_Moved Rotation_Moved_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FCsManagerInput_Rotation_Moved, AActor*, const FECsInputAction&, const FRotator&);

	FCsManagerInput_Rotation_Moved Rotation_Moved_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FCsManagerInput_Rotation_FirstStationary Rotation_FirstStationary_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FCsManagerInput_Rotation_FirstStationary, AActor*, const FECsInputAction&, const FRotator&);

	FCsManagerInput_Rotation_FirstStationary Rotation_FirstStationary_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FCsManagerInput_Rotation_Stationary Rotation_Stationary_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FCsManagerInput_Rotation_Stationary, AActor*, const FECsInputAction&, const FRotator&);

	FCsManagerInput_Rotation_Stationary Rotation_Stationary_Event;

	// VR

	FBindableCall_CsManagerInput_Rotation_Raw HMD_Rotation_Raw;
	FBindableCall_CsManagerInput_Rotation_Raw LeftHand_Rotation_Raw;
	FBindableCall_CsManagerInput_Rotation_Raw RightHand_Rotation_Raw;

#pragma endregion Rotation Events

#pragma endregion Actions

// Game Events
#pragma region

	void CreateGameEventDefinitionSimple(TArray<FCsGameEventDefinition>& Definitions, const FECsGameEvent& GameEvent, const FECsInputAction& Action, const ECsInputEvent& Event);

#pragma endregion Game Events
};