// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Components/ActorComponent.h"
// Resource
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
// Types
#include "InputCoreTypes.h"
#include "Managers/Input/Profile/CsTypes_InputProfile.h"
// Input
#include "Managers/Input/CsInputFrame.h"
#include "Managers/Input/Action/CsInputActionMap.h"
// GameEvent
#include "Managers/Input/GameEvent/CsGameEventDefinition.h"

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

// Cached
#pragma region

namespace NCsManagerInput
{
	namespace NCached
	{
		namespace Str
		{
			extern CSCORE_API const FString SetCurrentInputActionMap;
			extern CSCORE_API const FString ClearCurrentInputActionMap;
		}
	}

	namespace NCurrentMode
	{
		namespace NCached
		{
			namespace Str
			{
				extern CSCORE_API const FString SetValue;
				extern CSCORE_API const FString ClearValue;
			}
		}
	}
}

#pragma endregion Cached

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerInput_OnAnyKey_Pressed, const FKey&, Key);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerInput_OnAnyKey_Released, const FKey&, Key);

#pragma endregion Delegates

class AActor;
class APlayerController;
class UCsInputListener;

UCLASS(Blueprintable)
class CSCORE_API UCsManager_Input : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:

	void Init();

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

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPostProcessInput, const float& /*DeltaTime*/, const bool /*bGamePaused*/);

	FOnPostProcessInput OnPostProcessInput_Event;

	void OnPostProcessInput_CaptureMouseInput(const float& DeltaTime, const bool bGamePaused);
	void OnPostProcessInput_LogCaptureMouseInput();

	void OnPostProcessInput_CaptureTouchInput(const float& DeltaTime, const bool bGamePaused);
	void OnPostProcessInput_LogCaptureTouchInput();

	void OnPostProcessInput_CaptureVRInput();

	void OnPostProcessInput_LogInputAction();
	void OnPostProcessInput_LogCurrentInputFrame();
	void OnPostProcessInput_LogGameEventInfo();

	void OnPostProcessInput_UpdateActiveInputMode(const float& DeltaTime, const bool bGamePaused);

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

public:

	FORCEINLINE const TArray<FCsInputInfo>& GetInputActionEventInfos() const { return InputActionEventInfos; }

private:

	void SetupInputActionEventInfos();

	/** */
	TMap<FECsInputAction, int32> InputActionMapping;

	void SetupInputActionMapping();

	/** Bit mask of current active InputActionMaps */
	int32 CurrentInputActionMap;

public:

	/**
	* Sets the bit (Map) in CurrentInputActionMap.
	*
	* @param Context	The calling context.
	* @param Map		A EnumStructFlag (contains a bit flag).
	*/
	FORCEINLINE void SetCurrentInputActionMap(const FString& Context, const FECsInputActionMap& Map) 
	{
		check(EMCsInputActionMap::Get().IsValidEnumChecked(Context, Map));

		CS_SET_BITFLAG(CurrentInputActionMap, Map.Mask); 
	}

	/**
	* Sets the bit (Map) in CurrentInputActionMap.
	*
	* @param Map	A EnumStructFlag (contains a bit flag).
	*/
	FORCEINLINE void SetCurrentInputActionMap(const FECsInputActionMap& Map) { SetCurrentInputActionMap(NCsManagerInput::NCached::Str::SetCurrentInputActionMap, Map); }
	
	/**
	* Sets the bit (Map) in CurrentInputActionMap.
	*
	* @param Context	The calling context.
	* @param Map		A bit flag.
	*/
	FORCEINLINE void SetCurrentInputActionMap(const FString& Context, const int32& Map) 
	{ 
		checkf(Map >= 0, TEXT("%s: Map: %s is NOT Valid."), *Context, Map);

		CS_SET_BITFLAG(CurrentInputActionMap, Map); 
	}

	/**
	* Sets the bit (Map) in CurrentInputActionMap.
	*
	* @param Map	A bit flag.
	*/
	FORCEINLINE void SetCurrentInputActionMap(const int32& Map) { SetCurrentInputActionMap(NCsManagerInput::NCached::Str::SetCurrentInputActionMap, Map); }

	/**
	* Clears the bit (Map) in CurrentInputActionMap.
	*
	* @param Context	The calling context.
	* @param Map		A EnumStructFlag (contains a bit flag).
	*/
	FORCEINLINE void ClearCurrentInputActionMap(const FString& Context, const FECsInputActionMap& Map)
	{
		checkf(EMCsInputActionMap::Get().IsValidEnum(Map), TEXT("%s: Map: %s is NOT Valid."), *Context, Map.ToChar());

		CS_CLEAR_BITFLAG(CurrentInputActionMap, Map.Mask);
	}

	/**
	* Clears the bit (Map) in CurrentInputActionMap.
	*
	* @param Map	A EnumStructFlag (contains a bit flag).
	*/
	FORCEINLINE void ClearCurrentInputActionMap(const FECsInputActionMap& Map) { ClearCurrentInputActionMap(NCsManagerInput::NCached::Str::ClearCurrentInputActionMap, Map); }

	/**
	* Clears the bit (Map) in CurrentInputActionMap.
	*
	* @param Context	The calling context.
	* @param Map		A bit flag.
	*/
	FORCEINLINE void ClearCurrentInputActionMap(const FString& Context, const int32& Map) 
	{
		checkf(Map >= 0, TEXT("%s: Map: %s is NOT Valid."), *Context, Map);

		CS_CLEAR_BITFLAG(CurrentInputActionMap, Map); 
	}

	/**
	* Clears the bit (Map) in CurrentInputActionMap.
	*
	* @param Map	A bit flag.
	*/
	FORCEINLINE void ClearCurrentInputActionMap(const int32& Map) { ClearCurrentInputActionMap(NCsManagerInput::NCached::Str::ClearCurrentInputActionMap, Map); }

	/**
	* Sets CurrentInputActionMap to 0.
	*/
	FORCEINLINE void ResetCurrentInputActionMap(){ CurrentInputActionMap = 0; }

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

public:

	FORCEINLINE const FCsGameEventDefinition* GetGameEventDefinition(const FECsGameEvent& GameEvent) const
	{
		for (const FCsGameEventDefinition& Def : GameEventDefinitions)
		{
			if (Def.Event == GameEvent)
				return &Def;
		}
		return nullptr;
	}

private:

	TMap<FECsGameEvent, FCsInputSentence> InputSentenceByGameEventMap;

	TArray<FECsGameEvent> GameEventPriorityList;

	TArray<int32> GameEventPriorityMap;

	void SetupGameEventDefinitions();

	/** */
	TArray<FCsGameEventInfo> QueuedGameEventInfosForNextFrame;

	/** */
	TArray<FCsGameEventInfo> CurrentGameEventInfos;

public:

	FORCEINLINE const TArray<FCsGameEventInfo>& GetCurrentGameEventInfos() const { return CurrentGameEventInfos; }

private:

	/** */
	TArray<FCsGameEventInfo> CurrentValidGameEventInfos;

public:

	FORCEINLINE const TArray<FCsGameEventInfo>& GetCurrentValidGameEventInfos() const { return CurrentValidGameEventInfos; }

private:

	void LogProcessGameEventDefinition(const FString& Context);

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

	void OnAnyKey_Pressed(FKey Key);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnyKey_Pressed, const FKey& /*Key*/);

	FOnAnyKey_Pressed OnAnyKey_Pressed_Event;

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Manager|Input")
	FCsManagerInput_OnAnyKey_Pressed OnAnyKey_Pressed_ScriptEvent;

	void OnAnyKey_Released(FKey Key);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnyKey_Released, const FKey& /*Key*/);

	FOnAnyKey_Released OnAnyKey_Released_Event;

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Manager|Input")
	FCsManagerInput_OnAnyKey_Released OnAnyKey_Released_ScriptEvent;

	void OnAction_Pressed(const FECsInputAction& Action, const FKey& Key);

	void OnAction_Released(const FECsInputAction& Action, const FKey& Key);

	void OnTouchAction_Pressed(ETouchIndex::Type Index, FVector Location);

	void OnTouchAction_Released(ETouchIndex::Type Index, FVector Location);

	void OnAxis(const FECsInputAction& Action, const float& Value);

#pragma endregion Listener

// Actions
#pragma region
protected:

	TArray<FCsInputInfo*> Infos;

	TArray<ECsInputEvent*> Actions;
	TArray<ECsInputEvent*> Last_Actions;

	// Mouse
#pragma region
public:

	TArray<FECsInputAction> MouseActions;
	
	FVector CurrentMousePosition;

#pragma endregion Mouse

	// Touch
#pragma region
private:

	TArray<FECsInputAction> TouchActions;
	TArray<FECsInputAction> TouchAxisActions;

#pragma endregion Touch

#pragma endregion Actions

// Game Events
#pragma region

	void CreateGameEventDefinitionSimple(TArray<FCsGameEventDefinition>& Definitions, const FECsGameEvent& GameEvent, const FECsInputAction& Action, const ECsInputEvent& Event);

#pragma endregion Game Events

// Mode
#pragma region
public:

	struct FMode
	{
		friend class UCsManager_Input;

	protected:

		UCsManager_Input* Outer;

		int32 Value;

		int32 Last_Value;

	public:

		DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChange, const int32& /*Previous*/, const int32& /*Current*/);

		FOnChange OnChange_Event;

		FMode() :
			Outer(nullptr),
			Value(0),
			Last_Value(0),
			OnChange_Event()
		{
		}

		FORCEINLINE const int32& GetValue() const { return Value; }

		/**
		* Sets Value to 0.
		*/
		FORCEINLINE void ResetValue() { Value = 0; }
	};

	struct FCurrentMode : public FMode
	{
	private:

		typedef FMode _Super;

	public:

		FCurrentMode() :
			_Super()
		{
		}

		/**
		* Sets the bit in Value.
		*
		* @param Context	The calling context.
		* @param Mode		A BlueprintFlag (value will get bit shifted).
		*/
		void SetValue(const FString& Context, const ECsInputMode& Mode);

		/**
		* Sets the bit in Value.
		*
		* @param Mode	A BlueprintFlag (value will get bit shifted).
		*/
		FORCEINLINE void SetValue(const ECsInputMode& Mode) { SetValue(NCsManagerInput::NCurrentMode::NCached::Str::SetValue, Mode); }

		/**
		* Sets the bit in Value.
		*
		* @param Context	The calling context.
		* @param Mode		A bit flag.
		*/
		void SetValue(const FString& Context, const int32& Mode);

		/**
		* Sets the bit in Value.
		*
		* @param Mode	A bit flag.
		*/
		FORCEINLINE void SetValue(const int32& Mode) { SetValue(NCsManagerInput::NCurrentMode::NCached::Str::SetValue, Mode); }

		/**
		* Clears the bit in Value.
		*
		* @param Context	The calling context.
		* @param Mode		A BlueprintFlag (value will get bit shifted).
		*/
		void ClearValue(const FString& Context, const ECsInputMode& Mode);

		/**
		* Clears the bit in Value.
		*
		* @param Mode	A BlueprintFlag (value will get bit shifted).
		*/
		FORCEINLINE void ClearValue(const ECsInputMode& Mode) { ClearValue(NCsManagerInput::NCurrentMode::NCached::Str::ClearValue, Mode); }

		/**
		* Clears the bit in Value.
		*
		* @param Context	The calling context.
		* @param Mode		A bit flag.
		*/
		void ClearValue(const FString& Context, const int32& Mode);

		/**
		* Clears the bit in Value.
		*
		* @param Mode	A bit flag.
		*/
		FORCEINLINE void ClearValue(const int32& Mode) { ClearValue(NCsManagerInput::NCurrentMode::NCached::Str::ClearValue, Mode); }
	};

	/** Bit mask of current InputMode */
	FCurrentMode CurrentMode;

	struct FActiveMode : public FMode
	{
	private:

		typedef FMode _Super;

	public:

		FActiveMode() :
			_Super()
		{
		}

		void OnPostProcessInput(const float& DeltaTime, const bool bGamePaused);

		void PrintSet(const FString& Context, const FECsInputAction& Action, const FCsInputInfo& Info, const ECsInputMode& Mode);
		void PrintSummary(const FString& Context);
	};

	FActiveMode ActiveMode;

private:

	int32 ActiveInputMode;

	int32 Last_ActiveInputMode;

public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnActiveInputModeChange, const int32& /*PreviousMode*/, const int32& /*CurrentMode*/);

	FOnActiveInputModeChange OnActiveInputModeChange_Event;

#pragma endregion Mode

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
};