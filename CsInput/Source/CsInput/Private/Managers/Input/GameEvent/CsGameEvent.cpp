// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/GameEvent/CsGameEvent.h"

// Library
	// Settings
#include "Settings/CsLibrary_InputSettings.h"
// Utility
#include "Utility/CsLibrary_EnumStruct.h"
#include "Utility/CsInputLog.h"
// Input
#include "Managers/Input/Definition/CsTypes_InputDefinition.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsGameEvent)

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

	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__MousePositionXY__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__MouseLeftButtonPressed__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__MouseLeftButtonReleased__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__MouseRightButtonPressed__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__MouseRightButtonReleased__);

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		using namespace NCsGameEvent::NCached;

		EMCsGameEvent::Get().ClearUserDefinedEnums();

		typedef NCsInput::NSettings::FLibrary SettingsLibrary;
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
		Payload.Log						 = &NCsInput::FLog::Warning;

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