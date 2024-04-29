// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Components/ActorComponent.h"
// Interface
#include "Managers/Input/CsManager_Input.h"
#include "Managers/Input/Event/CsManager_Input_Event.h"
// Types
#include "Managers/Input/Action/CsInputActionMap.h"
#include "Managers/Input/GameEvent/CsGameEvent.h"
#include "Managers/Input/Profile/CsTypes_InputProfile.h"

#include "CsManager_Input_Enhanced.generated.h"

class AActor;
class APlayerController;
struct FCsGameEventDefinition;

UCLASS(BlueprintType, Blueprintable)
class CSCORE_API UCsManager_Input_Enhanced : public UActorComponent,
											 public ICsManager_Input,
											 public ICsManager_Input_Event
{
	GENERATED_BODY()

	UCsManager_Input_Enhanced();

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

// ICsManager_Input
#pragma region
public:

	// Owner

	FORCEINLINE APlayerController* GetOwnerAsController() const { return OwnerAsController; }
	FORCEINLINE int32 GetControllerId() const { return ControllerId; }
	
	void Init();

	// Process

	void PreProcessInput(const float DeltaTime, const bool bGamePaused);
	void PostProcessInput(const float DeltaTime, const bool bGamePaused);

	// Action Map

	/**
	* Sets the bit (Map) in CurrentInputActionMap.
	*
	* @param Context	The calling context.
	* @param Map		A EnumStructFlag (contains a bit flag).
	*/
	void SetCurrentInputActionMap(const FString& Context, const FECsInputActionMap& Map);

	/**
	* Sets the bit (Map) in CurrentInputActionMap.
	*
	* @param Map	A EnumStructFlag (contains a bit flag).
	*/
	void SetCurrentInputActionMap(const FECsInputActionMap& Map);
	
	/**
	* Sets the bit (Map) in CurrentInputActionMap.
	*
	* @param Context	The calling context.
	* @param Map		A bit flag.
	*/
	void SetCurrentInputActionMap(const FString& Context, const int32& Map);

	/**
	* Sets the bit (Map) in CurrentInputActionMap.
	*
	* @param Map	A bit flag.
	*/
	void SetCurrentInputActionMap(const int32& Map);

	/**
	* Clears the bit (Map) in CurrentInputActionMap.
	*
	* @param Context	The calling context.
	* @param Map		A EnumStructFlag (contains a bit flag).
	*/
	void ClearCurrentInputActionMap(const FString& Context, const FECsInputActionMap& Map);

	/**
	* Clears the bit (Map) in CurrentInputActionMap.
	*
	* @param Map	A EnumStructFlag (contains a bit flag).
	*/
	void ClearCurrentInputActionMap(const FECsInputActionMap& Map);

	/**
	* Clears the bit (Map) in CurrentInputActionMap.
	*
	* @param Context	The calling context.
	* @param Map		A bit flag.
	*/
	void ClearCurrentInputActionMap(const FString& Context, const int32& Map);

	/**
	* Clears the bit (Map) in CurrentInputActionMap.
	*
	* @param Map	A bit flag.
	*/
	void ClearCurrentInputActionMap(const int32& Map);

	/**
	* Sets CurrentInputActionMap to 0.
	*/
	void ResetCurrentInputActionMap();

	// Event
	
	FORCEINLINE const FCsGameEventDefinition* GetGameEventDefinition(const FECsGameEvent& GameEvent) const
	{
		/*for (const FCsGameEventDefinition& Def : GameEventDefinitions)
		{
			if (Def.Event == GameEvent)
				return &Def;
		}*/
		return nullptr;
	}


	// Profile
	
	FORCEINLINE const FCsInputProfile& GetDefaultInputProfile() const { return DefaultInputProfile; }

#pragma endregion ICsManager_Input

// Manager_Input
#pragma region
private:

	APlayerController* OwnerAsController;

	int32 ControllerId;

	uint32 CurrentInputActionMap;

	FCsInputProfile DefaultInputProfile;

#pragma endregion Manager_Input

// ICsManager_Input_Event
#pragma region
public:

#define OnPostProcessInputEventType NCsInput::NManager::FOnPostProcessInput
#define OnGameEventInfoEventType NCsInput::NManager::FOnGameEventInfo
#define OnGameEventInfosEventType NCsInput::NManager::FOnGameEventInfos
#define OnAnyKeyPressedEventType NCsInput::NManager::FOnAnyKey_Pressed
#define OnAnyKeyReleasedEventType NCsInput::NManager::FOnAnyKey_Released
#define ModeOnChangeEventType NCsInput::NManager::NMode::FOnChange

	FORCEINLINE OnPostProcessInputEventType& GetOnPostProcessInput_Event() { return OnPostProcessInput_Event; }
	FORCEINLINE OnGameEventInfoEventType& GetOnGameEventInfo_Event() { return OnGameEventInfo_Event; }
	FORCEINLINE OnGameEventInfosEventType& GetOnGameEventInfos_Event() { return OnGameEventInfos_Event; }
	FORCEINLINE OnAnyKeyPressedEventType& GetOnAnyKey_Pressed_Event() { return OnAnyKey_Pressed_Event; }
	FORCEINLINE FCsManagerInput_OnAnyKey_Pressed& GetOnAnyKey_Pressed_ScriptEvent() { return OnAnyKey_Pressed_ScriptEvent; }
	FORCEINLINE OnAnyKeyReleasedEventType& GetOnAnyKey_Released_Event() { return OnAnyKey_Released_Event; }
	FORCEINLINE FCsManagerInput_OnAnyKey_Released& GetOnAnyKey_Released_ScriptEvent() { return OnAnyKey_Released_ScriptEvent; }
	//FORCEINLINE ModeOnChangeEventType& GetActiveMode_OnChange_Event() { return ActiveMode.GetOnChange_Event();  }
	FORCEINLINE ModeOnChangeEventType& GetActiveMode_OnChange_Event() { return Mode_OnChange_Event;  }
	FORCEINLINE FCsManagerInput_OnActiveMode_Change& GetActiveMode_OnChange_ScriptEvent() { return OnActiveMode_Change_ScriptEvent; }

#undef OnPostProcessInputEventType
#undef OnGameEventInfoEventType
#undef OnGameEventInfosEventType
#undef OnAnyKeyPressedEventType
#undef OnAnyKeyReleasedEventType
#undef ModeOnChangeEventType

#pragma endregion ICsManager_Input_Event

// Manager_Input_Event
#pragma region
public:

#define OnPostProcessInputEventType NCsInput::NManager::FOnPostProcessInput
#define OnGameEventInfoEventType NCsInput::NManager::FOnGameEventInfo
#define OnGameEventInfosEventType NCsInput::NManager::FOnGameEventInfos
#define OnAnyKeyPressedEventType NCsInput::NManager::FOnAnyKey_Pressed
#define OnAnyKeyReleasedEventType NCsInput::NManager::FOnAnyKey_Released

	OnPostProcessInputEventType OnPostProcessInput_Event;

	OnGameEventInfoEventType OnGameEventInfo_Event;

	OnGameEventInfosEventType OnGameEventInfos_Event;

	OnAnyKeyPressedEventType OnAnyKey_Pressed_Event;

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Manager|Input")
	FCsManagerInput_OnAnyKey_Pressed OnAnyKey_Pressed_ScriptEvent;

	OnAnyKeyReleasedEventType OnAnyKey_Released_Event;

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Manager|Input")
	FCsManagerInput_OnAnyKey_Released OnAnyKey_Released_ScriptEvent;

	UPROPERTY(BlueprintAssignable)
	FCsManagerInput_OnActiveMode_Change OnActiveMode_Change_ScriptEvent;

#undef OnPostProcessInputEventType
#undef OnGameEventInfoEventType
#undef OnGameEventInfosEventType
#undef OnAnyKeyPressedEventType
#undef OnAnyKeyReleasedEventType

// TEMP
#define ModeOnChangeEventType NCsInput::NManager::NMode::FOnChange

	ModeOnChangeEventType Mode_OnChange_Event;

#undef ModeOnChangeEventType

#pragma endregion Manager_Input_Event
};