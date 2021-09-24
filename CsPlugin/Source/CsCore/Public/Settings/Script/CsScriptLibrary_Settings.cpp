// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Settings/Script/CsScriptLibrary_Settings.h"

// Settings
#include "Settings/CsDeveloperSettings.h"

UCsScriptLibrary_Settings::UCsScriptLibrary_Settings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UCsDeveloperSettings* UCsScriptLibrary_Settings::Get()
{
	return GetMutableDefault<UCsDeveloperSettings>();
}