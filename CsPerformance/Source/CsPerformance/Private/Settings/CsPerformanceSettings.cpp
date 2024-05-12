// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsPerformanceSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsPerformanceSettings)

UCsPerformanceSettings::UCsPerformanceSettings(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	Manager_Performance(),
	UI(),
	bShowFPS(false)
{
}