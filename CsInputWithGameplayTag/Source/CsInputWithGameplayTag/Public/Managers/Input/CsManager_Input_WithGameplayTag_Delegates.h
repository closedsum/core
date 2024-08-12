// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Input/CsTypes_Input_WithGameplayTag.h"

#include "CsManager_Input_WithGameplayTag_Delegates.generated.h"

USTRUCT()
struct CSINPUTWITHGAMEPLAYTAG_API FCsManager_Input_WithGameplayTag_Delegates_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsManager_Input_WithGameplayTag_Delegates_STUB()
	{
	}
};

// Raw
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerInputWithGameplayTag_OnPressed_Raw, const FCsInput_WithGameplayTag_Event&, Event);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerInputWithGameplayTag_OnReleased_Raw, const FCsInput_WithGameplayTag_Event&, Event);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerInputWithGameplayTag_OnAction_Raw, const FCsInput_WithGameplayTag_Event&, Event);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerInputWithGameplayTag_OnAction, const FCsInput_WithGameplayTag_Event&, Event);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerInputWithGameplayTag_OnAction2, FCsInput_WithGameplayTag_Event, Event);

namespace NCsInput
{
	namespace NWithGameplayTag
	{
		namespace NManager
		{
			namespace NRaw
			{
				#define EventType NCsInput::NWithGameplayTag::FEvent

				DECLARE_MULTICAST_DELEGATE_OneParam(FOnPressed, const EventType& /*Event*/);
				DECLARE_MULTICAST_DELEGATE_OneParam(FOnReleased, const EventType& /*Event*/);
				DECLARE_MULTICAST_DELEGATE_OneParam(FOnAction, const EventType& /*Event*/);

				#undef EventType
			}

			#define EventType NCsInput::NWithGameplayTag::FEvent

			DECLARE_MULTICAST_DELEGATE_OneParam(FOnAction, const EventType& /*Event*/);

			#undef EventType
		}
	}
}