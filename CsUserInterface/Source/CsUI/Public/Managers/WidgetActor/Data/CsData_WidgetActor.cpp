// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/WidgetActor/Data/CsData_WidgetActor.h"
#include "CsUI.h"

const FName NCsWidgetActor::NData::IData::Name = FName("NCsWidgetActor::NData::IData");

const FName ICsData_WidgetActor::Name = FName("ICsData_WidgetActor");

UCsData_WidgetActor::UCsData_WidgetActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}