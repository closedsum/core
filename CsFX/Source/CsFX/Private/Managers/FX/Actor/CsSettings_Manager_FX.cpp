// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/FX/Actor/CsSettings_Manager_FX.h"

// Settings
#include "Settings/CsFXSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSettings_Manager_FX)

// FCsSettings_Manager_FX
#pragma region

const FCsSettings_Manager_FX& FCsSettings_Manager_FX::GetChecked(const FString& Context)
{
	UCsFXSettings* Settings = GetMutableDefault<UCsFXSettings>();

	checkf(Settings, TEXT("%s: Failed to get settings of type: UCsFXSettings."), *Context);
	return Settings->Manager_FX;
}

#pragma endregion FCsSettings_Manager_FX