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
class CSCORE_API UCsManager_Input_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsManager_Input_Event
{
	GENERATED_IINTERFACE_BODY()

public:

#define OnPostProcessInputEventType NCsInput::NManager::FOnPostProcessInput
#define OnGameEventInfoEventType NCsInput::NManager::FOnGameEventInfo
#define OnGameEventInfosEventType NCsInput::NManager::FOnGameEventInfos
#define OnAnyKeyPressedEventType NCsInput::NManager::FOnAnyKey_Pressed
#define OnAnyKeyReleasedEventType NCsInput::NManager::FOnAnyKey_Released
#define ModeOnChangeEventType NCsInput::NManager::NMode::FOnChange

	virtual OnPostProcessInputEventType& GetOnPostProcessInput_Event() = 0;
	virtual OnGameEventInfoEventType& GetOnGameEventInfo_Event() = 0;
	virtual OnGameEventInfosEventType& GetOnGameEventInfos_Event() = 0;
	virtual OnAnyKeyPressedEventType& GetOnAnyKey_Pressed_Event() = 0;
	virtual FCsManagerInput_OnAnyKey_Pressed& GetOnAnyKey_Pressed_ScriptEvent() = 0;
	virtual OnAnyKeyReleasedEventType& GetOnAnyKey_Released_Event() = 0;
	virtual FCsManagerInput_OnAnyKey_Released& GetOnAnyKey_Released_ScriptEvent() = 0;
	virtual ModeOnChangeEventType& GetActiveMode_OnChange_Event() = 0;
	virtual FCsManagerInput_OnActiveMode_Change& GetActiveMode_OnChange_ScriptEvent() = 0;

#undef OnGameEventInfoEventType
#undef OnGameEventInfosEventType
#undef OnAnyKeyPressedEventType
#undef OnAnyKeyReleasedEventType
#undef ModeOnChangeEventType
#undef OnPostProcessInputEventType
};