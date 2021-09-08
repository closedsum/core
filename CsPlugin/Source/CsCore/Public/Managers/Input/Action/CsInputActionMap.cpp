// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/Action/CsInputActionMap.h"
#include "CsCore.h"

// Settings
#include "Settings/CsDeveloperSettings.h"
// Utility
#include "Utility/CsLog.h"
#include "Utility/CsPopulateEnumMapFromSettings.h"

namespace NCsInputActionMap
{
	namespace Str
	{
		const FString InputActionMap = TEXT("InputActionMap");
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		if (UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>())
		{
			EMCsInputActionMap::Get().ClearUserDefinedEnums();

			FCsPopulateEnumMapFromSettings::FromEnumSettings<UCsDeveloperSettings, EMCsInputActionMap, FECsInputActionMap>(Context, Str::InputActionMap, &FCsLog::Warning);
		}
	}
}