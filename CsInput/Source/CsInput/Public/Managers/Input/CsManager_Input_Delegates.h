// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Input/GameEvent/CsGameEvent.h"

#include "CsManager_Input_Delegates.generated.h"

USTRUCT()
struct CSINPUT_API FCsManager_Input_Delegates_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsManager_Input_Delegates_STUB()
	{
	}
};

// Script Passable
#pragma region

DECLARE_DYNAMIC_DELEGATE_OneParam(FCsManagerInput_ScriptPassable_OnAnyKey_Pressed, const FKey&, Key);

#pragma endregion Script Passable

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerInput_OnAnyKey_Pressed, const FKey&, Key);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerInput_OnAnyKey_Released, const FKey&, Key);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerInput_OnActiveMode_Change, const int32&, Previous, const int32&, Current);

namespace NCsInput
{
	namespace NManager
	{
		DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPostProcessInput, const float& /*DeltaTime*/, const bool /*bGamePaused*/);

		/**
		*/
		DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameEventInfo, const FCsGameEventInfo& /*Info*/);

		/**
		*/
		DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameEventInfos, const TArray<FCsGameEventInfo>& /*Infos*/);

		DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnyKey_Pressed, const FKey& /*Key*/);
		DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnyKey_Released, const FKey& /*Key*/);

		namespace NMode
		{
			DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChange, const int32& /*Previous*/, const int32& /*Current*/);
		}
	}
}