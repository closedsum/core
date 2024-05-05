// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Trace/CsSettings_Manager_Trace.h"

// Settings
#include "Settings/CsPhysicsSettings.h"

// FCsSettings_Manager_Trace_Debug
#pragma region

const FCsSettings_Manager_Trace_Debug& FCsSettings_Manager_Trace_Debug::Get()
{
	return FCsSettings_Manager_Trace::Get().Debug;
}

#pragma endregion FCsSettings_Manager_Trace_Debug

// FCsSettings_Manager_Trace
#pragma region

const FCsSettings_Manager_Trace& FCsSettings_Manager_Trace::Get()
{
	return GetMutableDefault<UCsPhysicsSettings>()->Manager_Trace;
}

#pragma endregion FCsSettings_Manager_Trace