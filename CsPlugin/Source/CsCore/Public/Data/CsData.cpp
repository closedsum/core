// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData.h"
#include "CsCore.h"

const FName NCsData::IData::Name = FName("NCsData::IData::Name");

const FName ICsData::Name = FName("ICsData");

UCsData::UCsData(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FCsData FCsData::Empty;