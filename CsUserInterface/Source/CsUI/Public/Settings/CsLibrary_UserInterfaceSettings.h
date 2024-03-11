// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Settings/CsTypes_Settings_Enum.h"

class UCsUserInterfaceSettings;

namespace NCsUI
{
	namespace NSettings
	{
		/**
		*/
		class CSUI_API FLibrary
		{
		public:
			
			static UCsUserInterfaceSettings* Get();
		
		// WidgetActor
		#pragma region
		public:

			static const ECsPopulateEnumMapMethod& Get_ECsWidgetActor_PopulateEnumMapMethod();
			static const TArray<FCsSettings_Enum>& GetSettingsEnum_WidgetActor();
			static const FString& GetSettingsEnumPath_WidgetActor();

		#pragma endregion WidgetActor

		// UserWidget
		#pragma region
		public:

			static const ECsPopulateEnumMapMethod& Get_ECsUserWidget_PopulateEnumMapMethod();
			static const TArray<FCsSettings_Enum>& GetSettingsEnum_UserWidget();
			static const FString& GetSettingsEnumPath_UserWidget();

			static const ECsPopulateEnumMapMethod& Get_ECsUserWidgetPooled_PopulateEnumMapMethod();
			static const TArray<FCsSettings_Enum>& GetSettingsEnum_UserWidgetPooled();
			static const FString& GetSettingsEnumPath_UserWidgetPooled();

		#pragma endregion UserWidget
		};
	}
}