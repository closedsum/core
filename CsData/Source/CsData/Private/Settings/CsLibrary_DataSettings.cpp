
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsLibrary_DataSettings.h"

// Settings
#include "Settings/CsDataSettings.h"

namespace NCsData
{
	namespace NSettings
	{
		UCsDataSettings* FLibrary::Get() { return GetMutableDefault<UCsDataSettings>(); }

		// Data
		#pragma region

		const TSoftClassPtr<UObject>& FLibrary::GetDataRootSetChecked(const FString& Context)
		{
		#if UE_BUILD_SHIPPING
			return Get()->DataRootSet;
		#else
			UCsDataSettings* Settings = Get();

			checkf(Settings, TEXT("%s: Failed to Get Developer Settings."), *Context);
			return Settings->DataRootSet;
		#endif // #if UE_BUILD_SHIPPING
		}

		const TSoftClassPtr<UObject>& FLibrary::GetDataRootSet()			{ return Get()->DataRootSet; }
		UObject* FLibrary::LoadDataRootSetChecked(const FString& Context)	{ return Get()->LoadDataRootSetChecked(Context); }
		UObject* FLibrary::SafeLoadDataRootSet(const FString& Context)		{ return Get()->SafeLoadDataRootSet(Context); }
		const TArray<FString>& FLibrary::GetIgnoreAssetPaths()				{ return Get()->IgnoreAssetPaths; }

		#pragma endregion Data
	}
}