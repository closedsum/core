// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Settings/CsTypes_Settings_Enum.h"

class UCsFXSettings;
class UObject;

struct FECsFX;

namespace NCsFX
{
	namespace NSettings
	{
		/**
		*/
		class CSFX_API FLibrary
		{
		public:
			
			static UCsFXSettings* Get();
		
		// FX
		#pragma region
		public:

			static const TArray<FCsSettings_Enum>& GetSettingsEnum_FX();
			static const FString& GetSettingsEnumPath_FX();
			static FECsFX* GetDefault_ECsFX();

		#pragma endregion SkeletaMesh
		};
	}
}