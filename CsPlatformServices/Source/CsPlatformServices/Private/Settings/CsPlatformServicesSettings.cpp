// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsPlatformServicesSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsPlatformServicesSettings)

UCsPlatformServicesSettings::UCsPlatformServicesSettings(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	Manager_Save(),
	Manager_PlayerProfile(),
	Manager_Achievement(),
	Achievements(nullptr)
{
}