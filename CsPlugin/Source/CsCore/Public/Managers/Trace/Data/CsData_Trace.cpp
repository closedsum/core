// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Trace/Data/CsData_Trace.h"
#include "CsCore.h"

const FName NCsTrace::NData::IData::Name = FName("NCsTrace::NData::IData");

const FName ICsData_Trace::Name = FName("ICsData_Trace");

UCsData_Trace::UCsData_Trace(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}