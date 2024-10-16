// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "Managers/Input/CsTypes_Input_WithGameplayTag.h"

#include "CsCoordinator_GameplayTag_InputEvent.generated.h"

UINTERFACE(Blueprintable)
class CSINPUTWITHGAMEPLAYTAG_API UCsCoordinator_GameplayTag_InputEvent : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSINPUTWITHGAMEPLAYTAG_API ICsCoordinator_GameplayTag_InputEvent
{
	GENERATED_IINTERFACE_BODY()

private:

	// Allow clearer names without name collisions
	struct _
	{
		using EventType = NCsInput::NWithGameplayTag::FEvent;
		using ActionEventDelegateType = TDelegate<void(const EventType&)>;
	};

public:

	virtual _::ActionEventDelegateType GetOnAction_ManagerInput0_Delegate() = 0;

	virtual void OnAction_ManagerInput0(const _::EventType& Event) = 0;

	virtual _::ActionEventDelegateType GetOnAction_ManagerInput1_Delegate() = 0;

	virtual void OnAction_ManagerInput1(const _::EventType& Event) = 0;
};