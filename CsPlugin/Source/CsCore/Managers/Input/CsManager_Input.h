// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Classes/Components/ActorComponent.h"
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
#include "Managers/Input/CsInputFrame.h"
#include "CsManager_Input.generated.h"

#define CS_MAX_INPUT_FRAMES 32

// Struct
#pragma region

	// Input

struct CSCORE_API FCsResource_Input : public TCsResourceContainer<FCsInput>
{
};

struct CSCORE_API FCsManager_Input : public TCsManager_ResourceValueType_Fixed<FCsInput, FCsResource_Input, 0>
{
};

#pragma endregion Structs

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

#pragma endregion Input Delegates

// Game Action Delegates

class AActor;
class APlayerController;
struct FKeyState;

UCLASS(Blueprintable)
class CSCORE_API UCsManager_Input : public UActorComponent
{
	GENERATED_UCLASS_BODY()

	virtual void Init();

// UActorComponent Interface
#pragma region
protected:

	virtual void OnRegister() override;

#pragma endregion UActorComponent Interface

// Owner
#pragma region
public:

	APlayerController* OwnerAsController;

	int32 ControllerId;

#pragma endregion Owner

	virtual void PreProcessInput(const float DeltaTime, const bool bGamePaused);
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused);
	virtual void ProcessInput(AActor* ActionOwner, const FCsInput* PreviousInput, const FCsInput* CurrentInput, const float DeltaTime);

	float CurrentDeltaTime;

	FCsManager_Input Manager_Inputs;

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

	int32 CurrentInputFrameIndex;

	FCsInputFrame* CurrentInputFrame;

	TArray<FKey> AllKeys;
	TArray<FKeyState*> AllKeyStates;

// Action Map
#pragma region
public:

	TArray<FCsInputInfo> InputActionEventInfos;

	void SetupInputActionEventInfos();
	void SetupInputActionMapping();

	TMap<FECsInputAction, int32> InputActionMapping;

	int32 CurrentInputActionMap;

	void SetCurrentInputActionMap(const FECsInputActionMap& Map);
	void SetCurrentInputActionMap(const int32& Map);

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

	TSet<FCsGameEventDefinition> GameEventDefinitions;

	TMap<FECsGameEvent, FCsInputSentence> GameEventDefinitionMap;

	void SetupGameEventDefinitions();

	TArray<FECsGameEvent> GameEventPriorityList;

	TArray<int32> GameEventPriorityMap;

	TArray<FCsGameEventInfo> CurrentGameEventInfos;
	TArray<FCsGameEventInfo> CurrentValidGameEventInfos;
	TArray<FCsGameEventInfo> QueuedGameEventInfosForNextFrame;

	void LogProcessGameEventDefinition(const FString& Context, const FECsGameEvent& Event, const FCsInputSentence& Sentence);

	virtual void QueueGameEvent(const FECsGameEvent& Event);

	void ClearQueuedGameEvents();

	virtual void DetermineGameEvents(const TArray<FCsInput*>& InInputs);

	bool HasActionEventOccured(const FECsInputAction& Action, const ECsInputEvent& Event);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameEventInfo, const FCsGameEventInfo&);

	FOnGameEventInfo OnGameEventInfo_Event;

#pragma endregion Events

public:

	float GetInputValue(const FECsInputAction& Action);

	FVector GetInputLocation(const FECsInputAction& Action);

	ECsInputEvent GetInputEvent(const FECsInputAction& Action);

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

	const FKey& GetKey(const FString &KeyName);
	
	const FECsInputAction& GetActionFromKey(const ECsInputDevice& Device, const FKey& Key);
	const FKey& GetKeyFromAction(const ECsInputDevice& Device, const FECsInputAction& Action);
	const FKey& GetKeyFromAction(const FECsInputAction& Action);

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

	TArray<FCsInputInfo*> Infos;

	TArray<ECsInputEvent*> Actions;
	TArray<ECsInputEvent*> Last_Actions;

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