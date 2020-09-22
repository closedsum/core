// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Components/ActorComponent.h"
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

class AActor;
class APlayerController;
class UCsInputListener;

UCLASS(Blueprintable)
class CSCORE_API UCsManager_Input : public UActorComponent
{
	GENERATED_UCLASS_BODY()

	virtual void Init();

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

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

public:

	void PreProcessInput(const float DeltaTime, const bool bGamePaused);
	void PostProcessInput(const float DeltaTime, const bool bGamePaused);

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

	FCsInputFrame InputFrames[CS_MAX_INPUT_FRAMES];

	int32 CurrentInputFrameIndex;

	FCsInputFrame* CurrentInputFrame;

// Action Map
#pragma region
private:

	/** */
	TArray<FCsInputInfo> InputActionEventInfos;

	void SetupInputActionEventInfos();

	/** */
	TMap<FECsInputAction, int32> InputActionMapping;

	void SetupInputActionMapping();

public:

	/** Bit mask of current active InputActionMaps */
	int32 CurrentInputActionMap;

	/**
	* Sets the bit (Map) in CurrentInputActionMap.
	*
	* @param Map	A EnumStructFlag (contains a bit flag).
	*/
	void SetCurrentInputActionMap(const FECsInputActionMap& Map);
	
	/**
	* Sets the bit (Map) in CurrentInputActionMap.
	*
	* @param Map	A bit flag.
	*/
	void SetCurrentInputActionMap(const int32& Map);

	/**
	* Clears the bit (Map) in CurrentInputActionMap.
	*
	* @param Map	A EnumStructFlag (contains a bit flag).
	*/
	void ClearCurrentInputActionMap(const FECsInputActionMap& Map);

	/**
	* Clears the bit (Map) in CurrentInputActionMap.
	*
	* @param Map	A bit flag.
	*/
	void ClearCurrentInputActionMap(const int32& Map);

#pragma endregion Action Map

private:

	TArray<FKey> PressedKeys;

	FCsInput* GetPreviousInputAction(const FECsInputAction& Action);
	FCsInput* GetPreviousInputAction(const FECsInputAction& Action, const ECsInputEvent& Event);
	FCsInput* GetPreviousInputAction(const FECsInputAction& Action, const TArray<ECsInputEvent>& Events);
	FCsInput* GetPreviousPreviousInputAction(const FECsInputAction& Action);

// Events
#pragma region
private:

	TSet<FCsGameEventDefinition> GameEventDefinitions;

	TMap<FECsGameEvent, FCsInputSentence> GameEventDefinitionMap;

	TArray<FECsGameEvent> GameEventPriorityList;

	TArray<int32> GameEventPriorityMap;

	void SetupGameEventDefinitions();

	/** */
	TArray<FCsGameEventInfo> QueuedGameEventInfosForNextFrame;

	/** */
	TArray<FCsGameEventInfo> CurrentGameEventInfos;

public:

	FORCEINLINE const TArray<FCsGameEventInfo>& GetCurrentGameEventInfos() const
	{
		return CurrentGameEventInfos;
	}

private:

	/** */
	TArray<FCsGameEventInfo> CurrentValidGameEventInfos;

public:

	FORCEINLINE const TArray<FCsGameEventInfo>& GetCurrentValidGameEventInfos() const
	{
		return CurrentValidGameEventInfos;
	}

private:

	void LogProcessGameEventDefinition(const FString& Context, const FECsGameEvent& Event, const FCsInputSentence& Sentence);

public:

	void QueueGameEvent(const FECsGameEvent& Event);

	void ClearQueuedGameEvents();

	bool HasActionEventOccured(const FECsInputAction& Action, const ECsInputEvent& Event);

	/** Flag for whether OnGameEventInfo_Event and OnGameEventInfos_Event should be broadcasted. */
	bool bOnGameEventInfo;

	/**
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameEventInfo, const FCsGameEventInfo& /*Info*/);

	FOnGameEventInfo OnGameEventInfo_Event;

	/**
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameEventInfos, const TArray<FCsGameEventInfo>& /*Infos*/);

	FOnGameEventInfos OnGameEventInfos_Event;

#pragma endregion Events

public:

	float GetInputValue(const FECsInputAction& Action);

	FVector GetInputLocation(const FECsInputAction& Action);

	ECsInputEvent GetInputEvent(const FECsInputAction& Action);

	float GetInputDuration(const FECsInputAction& Action);

// Listener
#pragma region
private:

	UPROPERTY()
	TArray<UCsInputListener*> Listeners;

public:

	void OnAction_Pressed(const FECsInputAction& Action);

	void OnAction_Released(const FECsInputAction& Action);

	void OnAxis(const FECsInputAction& Action, const float& Value);

#pragma endregion Listener

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

	TArray<FKey> AllKeys;

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

	// Location Events
#pragma region
public:

	// Mouse

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	FVector CurrentMousePosition;

#pragma endregion Location Events

#pragma endregion Actions

// Game Events
#pragma region

	void CreateGameEventDefinitionSimple(TArray<FCsGameEventDefinition>& Definitions, const FECsGameEvent& GameEvent, const FECsInputAction& Action, const ECsInputEvent& Event);

#pragma endregion Game Events
};