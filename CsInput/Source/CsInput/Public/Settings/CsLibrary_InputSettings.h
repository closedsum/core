// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Settings/CsTypes_Settings_Enum.h"

class UCsInputSettings;
class UObject;

namespace NCsInput
{
	namespace NSettings
	{
		/**
		*/
		class CSINPUT_API FLibrary
		{
		public:
			
			static UCsInputSettings* Get();

		// Input
		#pragma region
		public:

			static const TArray<FCsSettings_Enum>& GetSettingsEnum_InputActionMap();
			static const FString& GetSettingsEnumPath_InputActionMap();
			static const TArray<FCsSettings_Enum>& GetSettingsEnum_GameEvent();
			static const FString& GetSettingsEnumPath_GameEvent();

		#pragma endregion Input
		};
	}
}