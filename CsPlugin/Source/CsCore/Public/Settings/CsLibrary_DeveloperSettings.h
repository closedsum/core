// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Settings/CsTypes_Settings_Enum.h"
#include "Types/Enum/CsEnumStructLayoutHistory.h"

class UCsDeveloperSettings;
class UObject;

namespace NCsCore
{
	namespace NSettings
	{
		/**
		*/
		class CSCORE_API FLibrary
		{
		public:
			
			static UCsDeveloperSettings* Get();
			
			static bool TryUpdateDefaultConfigFile();

		// Enum
		#pragma region
		public:

			static TMap<FName, FCsEnumStructLayoutHistory>& GetEnumStructlayoutHistoryMap();

		#pragma endregion Enum

		// Data
		#pragma region
		public:
			
			static const TSoftClassPtr<UObject>& GetDataRootSetChecked(const FString& Context);
			static const TSoftClassPtr<UObject>& GetDataRootSet();

			static UObject* LoadDataRootSetChecked(const FString& Context);
			static UObject* SafeLoadDataRootSet(const FString& Context);

			static const TArray<FString>& GetIgnoreAssetPaths();

		#pragma endregion Data

		// Input
		#pragma region
		public:

			static const TArray<FCsSettings_Enum>& GetSettingsEnum_InputActionMap();
			static const FString& GetSettingsEnumPath_InputActionMap();
			static const TArray<FCsSettings_Enum>& GetSettingsEnum_GameEvent();
			static const FString& GetSettingsEnumPath_GameEvent();

		#pragma endregion Input

		// Anim
		#pragma region
		public:

			static const ECsPopulateEnumMapMethod& GetVertexAnimNotify_PopulateEnumMapMethod();
			static const TArray<FCsSettings_Enum>& GetSettingsEnum_VertexAnimNotify();
			static const FString& GetSettingsEnumPath_VertexAnimNotify();

		#pragma endregion Anim
		};
	}
}