// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsLibrary_DeveloperSettings.h"
#include "CsCore.h"

// Settings
#include "Settings/CsDeveloperSettings.h"

namespace NCsCore
{
	namespace NSettings
	{
		const TSoftClassPtr<UObject>& FLibrary::GetDataRootSetChecked(const FString& Context)
		{
		#if UE_BUILD_SHIPPING
			return GetMutableDefault<UCsDeveloperSettings>()->DataRootSet;
		#else
			UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

			checkf(Settings, TEXT("%s: Failed to Get Developer Settings."), *Context);

			return Settings->DataRootSet;
		#endif // #if UE_BUILD_SHIPPING
		}

		const TSoftClassPtr<UObject>& FLibrary::GetDataRootSet() 
		{ 
			return GetMutableDefault<UCsDeveloperSettings>()->DataRootSet;
		}
	}
}