// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "UObject/Interface.h"
// Types
#include "Managers/Input/CsManager_Input_Delegates.h"

#include "CsManager_Input_Event.generated.h"

UINTERFACE(Blueprintable)
class CSINPUT_API UCsManager_Input_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSINPUT_API ICsManager_Input_Event
{
	GENERATED_IINTERFACE_BODY()

private:

	// Allow clearer names without name collisions
	struct _
	{
		using OnPostProcessInputEventType = NCsInput::NManager::FOnPostProcessInput;
		using OnGameEventInfoEventType = NCsInput::NManager::FOnGameEventInfo;
		using OnGameEventInfosEventType = NCsInput::NManager::FOnGameEventInfos;
		using OnAnyKeyPressedEventType = NCsInput::NManager::FOnAnyKey_Pressed;
		using OnAnyKeyReleasedEventType = NCsInput::NManager::FOnAnyKey_Released;
		using ModeOnChangeEventType = NCsInput::NManager::NMode::FOnChange;
	};
	
public:

	virtual _::OnPostProcessInputEventType& GetOnPostProcessInput_Event() = 0;
	virtual _::OnGameEventInfoEventType& GetOnGameEventInfo_Event() = 0;
	virtual _::OnGameEventInfosEventType& GetOnGameEventInfos_Event() = 0;
	virtual _::OnAnyKeyPressedEventType& GetOnAnyKey_Pressed_Event() = 0;
	virtual FCsManagerInput_OnAnyKey_Pressed& GetOnAnyKey_Pressed_ScriptEvent() = 0;
	virtual _::OnAnyKeyReleasedEventType& GetOnAnyKey_Released_Event() = 0;
	virtual FCsManagerInput_OnAnyKey_Released& GetOnAnyKey_Released_ScriptEvent() = 0;
	virtual _::ModeOnChangeEventType& GetActiveMode_OnChange_Event() = 0;
	virtual FCsManagerInput_OnActiveMode_Change& GetActiveMode_OnChange_ScriptEvent() = 0;
};