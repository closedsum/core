// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/GameEvent/CsGameEvent.h"
#include "CsCore.h"

// Settings
#include "Settings/CsDeveloperSettings.h"
// Utility
#include "Utility/CsPopulateEnumMapFromSettings.h"
#include "Utility/CsLog.h"
// Input
#include "Managers/Input/Definition/CsTypes_InputDefinition.h"

// GameEvent
#pragma region

namespace NCsGameEvent
{
	namespace Str
	{
		const FString GameEvent = TEXT("GameEvent");
	}

	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__MousePositionXY__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__MouseLeftButtonPressed__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__MouseLeftButtonReleased__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__MouseRightButtonPressed__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__MouseRightButtonReleased__);

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		if (UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>())
		{
			EMCsGameEvent::Get().ClearUserDefinedEnums();

			FCsPopulateEnumMapFromSettings::FromEnumSettings<UCsDeveloperSettings, EMCsGameEvent, FECsGameEvent>(Context, Str::GameEvent, &FCsLog::Warning);
		}
	}
}

#pragma endregion GameEvent

// FCsGameEventInfo
#pragma region

void FCsGameEventInfo::ApplyInputCompletedValue(const FCsInputCompletedValue* CompletedValue)
{
	// Value | Float
	if (CompletedValue->ValueType == ECsInputValue::Float)
		Value = CompletedValue.Value;
	// Location | Vector
	if (CompletedValue->ValueType == ECsInputValue::Vector)
		Location = CompletedValue.Location;
}

#pragma endregion FCsGameEventInfo