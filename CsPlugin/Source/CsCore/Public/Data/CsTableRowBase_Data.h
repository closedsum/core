// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Engine
#include "Engine/DataTable.h"

#include "CsTableRowBase_Data.generated.h"

USTRUCT(BlueprintInternalUseOnly)
struct CSCORE_API FCsTableRowBase_Data : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FCsTableRowBase_Data() { }
	virtual ~FCsTableRowBase_Data() { }

	virtual void Unload() {}
};