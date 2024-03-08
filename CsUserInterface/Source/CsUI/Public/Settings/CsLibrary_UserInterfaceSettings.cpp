// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsLibrary_UserInterfaceSettings.h"
#include "CsUI.h"

// Settings
#include "Settings/CsUserInterfaceSettings.h"

namespace NCsUI
{
	namespace NSettings
	{
		UCsUserInterfaceSettings* FLibrary::Get() { return GetMutableDefault<UCsUserInterfaceSettings>(); }
		
		// WidgetActor
		#pragma region

		const ECsPopulateEnumMapMethod& FLibrary::Get_ECsWidgetActor_PopulateEnumMapMethod() { return Get()->ECsWidgetActor_PopulateEnumMapMethod; }
		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_WidgetActor()				{ return Get()->GetSettingsEnum<FECsWidgetActor>(); }
		const FString& FLibrary::GetSettingsEnumPath_WidgetActor()							{ return NCsUserInterfaceSettings::NCached::Str::WidgetActor; }

		#pragma endregion WidgetActor

		// UserWidget
		#pragma region

		const ECsPopulateEnumMapMethod& FLibrary::Get_ECsUserWidget_PopulateEnumMapMethod() { return Get()->ECsUserWidget_PopulateEnumMapMethod; }
		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_UserWidget()				{ return Get()->GetSettingsEnum<FECsUserWidget>(); }
		const FString& FLibrary::GetSettingsEnumPath_UserWidget()							{ return NCsUserInterfaceSettings::NCached::Str::UserWidget; }

		const ECsPopulateEnumMapMethod& FLibrary::Get_ECsUserWidgetPooled_PopulateEnumMapMethod()	{ return Get()->ECsUserWidgetPooled_PopulateEnumMapMethod; }
		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_UserWidgetPooled()				{ return Get()->GetSettingsEnum<FECsUserWidgetPooled>(); }
		const FString& FLibrary::GetSettingsEnumPath_UserWidgetPooled()								{ return NCsUserInterfaceSettings::NCached::Str::UserWidgetPooled; }

		#pragma endregion UserWidget

		// MenuEvent
		#pragma region

		const ECsPopulateEnumMapMethod& FLibrary::Get_ECsMenuEvent_PopulateEnumMapMethod() { return Get()->ECsMenuEvent_PopulateEnumMapMethod; }
		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_MenuEvent()				{ return Get()->GetSettingsEnum<FECsMenuEvent>(); }
		const FString& FLibrary::GetSettingsEnumPath_MenuEvent()							{ return NCsUserInterfaceSettings::NCached::Str::MenuEvent; }

		#pragma endregion MenuEvent
	}
}