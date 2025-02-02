// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/ICsData.h"

// Types
#include "CsMacro_Interface.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ICsData)

CS_INTERFACE_DEFINE_STATIC_CONST_FNAME(NCsData::IData);
CS_INTERFACE_DEFINE_STATIC_CONST_FNAME(ICsData);

UCsData::UCsData(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FCsData FCsData::Empty;