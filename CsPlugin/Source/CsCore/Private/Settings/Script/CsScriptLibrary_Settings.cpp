// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/Script/CsScriptLibrary_Settings.h"

// Settings
#include "Settings/CsDeveloperSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Settings)

UCsScriptLibrary_Settings::UCsScriptLibrary_Settings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UCsDeveloperSettings* UCsScriptLibrary_Settings::Get()
{
	return GetMutableDefault<UCsDeveloperSettings>();
}