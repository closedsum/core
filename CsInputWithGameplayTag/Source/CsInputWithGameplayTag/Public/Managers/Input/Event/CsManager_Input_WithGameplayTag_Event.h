// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "UObject/Interface.h"
// Types
#include "Managers/Input/CsManager_Input_WithGameplayTag_Delegates.h"

#include "CsManager_Input_WithGameplayTag_Event.generated.h"

UINTERFACE(Blueprintable)
class CSINPUTWITHGAMEPLAYTAG_API UCsManager_Input_WithGameplayTag_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSINPUTWITHGAMEPLAYTAG_API ICsManager_Input_WithGameplayTag_Event
{
	GENERATED_IINTERFACE_BODY()

#define OnPressedRawEventType NCsInput::NWithGameplayTag::NManager::NRaw::FOnPressed
#define OnReleasedRawEventType NCsInput::NWithGameplayTag::NManager::NRaw::FOnReleased
#define OnActionRawEventType NCsInput::NWithGameplayTag::NManager::NRaw::FOnAction
#define OnActionEventType NCsInput::NWithGameplayTag::NManager::FOnAction

	virtual OnPressedRawEventType& GetOnPressed_Raw_Event() = 0;
	virtual FCsManagerInputWithGameplayTag_OnPressed_Raw& GetOnPressed_Raw_ScriptEvent() = 0;

	virtual OnReleasedRawEventType& GetOnReleased_Raw_Event() = 0;
	virtual FCsManagerInputWithGameplayTag_OnReleased_Raw& GetOnReleased_Raw_ScriptEvent() = 0;

	virtual OnActionRawEventType& GetOnAction_Raw_Event() = 0;
	virtual FCsManagerInputWithGameplayTag_OnAction_Raw& GetOnAction_Raw_ScriptEvent() = 0;

	virtual OnActionEventType& GetOnAction_Event() = 0;
	virtual FCsManagerInputWithGameplayTag_OnAction& GetOnAction_ScriptEvent() = 0;

#undef OnPressedRawEventType
#undef OnReleasedRawEventType
#undef OnActionRawEventType
#undef OnActionEventType
};