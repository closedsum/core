// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/Action/CsInputActionMap.h"
#include "CsCore.h"

// Library
	// Settings
#include "Settings/CsLibrary_DeveloperSettings.h"
// Utility
#include "Utility/CsLog.h"

namespace NCsInputActionMap
{
	namespace NCached
	{
		namespace Str
		{
			const FString InputActionMap = TEXT("InputActionMap");
		}
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		using namespace NCsInputActionMap::NCached;

		EMCsInputActionMap::Get().ClearUserDefinedEnums();

		typedef NCsCore::NSettings::FLibrary SettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary EnumSettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary::FPopulate::FPayload PayloadType;

		PayloadType Payload;
		Payload.Enums					 = SettingsLibrary::GetSettingsEnum_InputActionMap();
		Payload.EnumSettingsPath		 = SettingsLibrary::GetSettingsEnumPath_InputActionMap();
		Payload.EnumName				 = Str::InputActionMap;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &FCsLog::Warning;

		EnumSettingsLibrary::Populate(Context, Payload);
	}
}