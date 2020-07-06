// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData.h"
#include "CsCore.h"

const FName ICsData::Name = FName("ICsData");

UCsData::UCsData(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FCsData FCsData::Empty;