// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Containers/UnrealString.h"
#include "UObject/SoftObjectPtr.h"

class UObject;
class UCsDataSettings;

namespace NCsData
{
	namespace NSettings
	{
		/**
		*/
		class CSDATA_API FLibrary
		{
		public:
			
			static UCsDataSettings* Get();

		// Data
		#pragma region
		public:
			
			static const TSoftClassPtr<UObject>& GetDataRootSetChecked(const FString& Context);
			static const TSoftClassPtr<UObject>& GetDataRootSet();

			static UObject* LoadDataRootSetChecked(const FString& Context);
			static UObject* SafeLoadDataRootSet(const FString& Context);

			static const TArray<FString>& GetIgnoreAssetPaths();

		#pragma endregion Data
		};
	}
}

using CsDataSettingsLibrary = NCsData::NSettings::FLibrary;