// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Menu/CsTypes_Menu.h"

// Library
	// Settings
#include "Settings/CsLibrary_UserInterfaceSettings.h"
// Utility
#include "Utility/CsUIPopulateEnumMapFromSettings.h"
#include "Utility/CsUILog.h"

// MenuEvent
#pragma region

namespace NCsMenuEvent
{
	namespace NCached
	{
		namespace Str
		{
			const FString MenuEvent = TEXT("MenuEvent");
		}
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		using namespace NCsMenuEvent::NCached;

		EMCsMenuEvent::Get().ClearUserDefinedEnums();

		typedef NCsUI::NSettings::FLibrary SettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary EnumSettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary::FPopulate::FPayload PayloadType;

		PayloadType Payload;
		Payload.Enums					 = SettingsLibrary::GetSettingsEnum_MenuEvent();
		Payload.EnumSettingsPath		 = SettingsLibrary::GetSettingsEnumPath_MenuEvent();
		Payload.EnumName				 = Str::MenuEvent;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsUI::FLog::Warning;

		EnumSettingsLibrary::Populate(Context, Payload);
	}
}

#pragma endregion MenuEvent