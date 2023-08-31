// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/GameEvent/CsGameEvent.h"
#include "CsCore.h"

// Library
	// Settings
#include "Settings/CsLibrary_DeveloperSettings.h"
// Utility
#include "Utility/CsPopulateEnumMapFromSettings.h"
#include "Utility/CsLog.h"
// Input
#include "Managers/Input/Definition/CsTypes_InputDefinition.h"

// GameEvent
#pragma region

namespace NCsGameEvent
{
	namespace NCached
	{
		namespace Str
		{
			const FString GameEvent = TEXT("GameEvent");
		}
	}

	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__MousePositionXY__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__MouseLeftButtonPressed__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__MouseLeftButtonReleased__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__MouseRightButtonPressed__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__MouseRightButtonReleased__);

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		using namespace NCsGameEvent::NCached;

		typedef NCsCore::NSettings::FLibrary SettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary EnumSettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary::FPopulate::FPayload PayloadType;

		PayloadType Payload;
		Payload.Enums					 = SettingsLibrary::GetSettingsEnum_GameEvent();
		Payload.EnumSettingsPath		 = SettingsLibrary::GetSettingsEnumPath_GameEvent();
		Payload.EnumName				 = Str::GameEvent;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &FCsLog::Warning;

		EnumSettingsLibrary::Populate(Context, Payload);
	}
}

#pragma endregion GameEvent

// FCsGameEventInfo
#pragma region

void FCsGameEventInfo::ApplyInputCompletedValue(const FCsInputCompletedValue* CompletedValue)
{
	// Value | Float
	if (CompletedValue->ValueType == ECsInputValue::Float)
		Value = CompletedValue->Value;
	// Location | Vector
	if (CompletedValue->ValueType == ECsInputValue::Vector)
		Location = CompletedValue->Location;
}

#pragma endregion FCsGameEventInfo