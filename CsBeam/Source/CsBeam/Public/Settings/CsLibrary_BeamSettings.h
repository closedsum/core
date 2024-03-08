// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Settings/CsTypes_Settings_Enum.h"

class UCsBeamSettings;

namespace NCsBeam
{
	namespace NSettings
	{
		/**
		*/
		class CSBEAM_API FLibrary
		{
		public:

			static UCsBeamSettings* Get();

		// Enum
		#pragma region
		public:

			static const ECsPopulateEnumMapMethod& Get_ECsBeam_PopulateEnumMapMethod();
			static const TArray<FCsSettings_Enum>& GetSettingsEnum_Beam();
			static const FString& GetSettingsEnumPath_Beam();

			static const ECsPopulateEnumMapMethod& Get_ECsBeamClass_PopulateEnumMapMethod();
			static const TArray<FCsSettings_Enum>& GetSettingsEnum_BeamClass();
			static const FString& GetSettingsEnumPath_BeamClass();

		#pragma endregion Enum
		};
	}
}