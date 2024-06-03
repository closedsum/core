// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/ICsData.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ICsData)

const FName NCsData::IData::Name = FName("NCsData::IData");

const FName ICsData::Name = FName("ICsData");

UCsData::UCsData(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FCsData FCsData::Empty;