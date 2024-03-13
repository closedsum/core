// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Settings/CsTypes_Settings_Enum.h"

class UCsSoundSettings;
class UObject;

struct FECsSound;

namespace NCsSound
{
	namespace NSettings
	{
		/**
		*/
		class CSSOUND_API FLibrary
		{
		public:
			
			static UCsSoundSettings* Get();
		
		// Sound
		#pragma region
		public:

			static const TArray<FCsSettings_Enum>& GetSettingsEnum_Sound();
			static const FString& GetSettingsEnumPath_Sound();
			static FECsSound* GetDefault_ECsSound();

		#pragma endregion SkeletaMesh
		};
	}
}