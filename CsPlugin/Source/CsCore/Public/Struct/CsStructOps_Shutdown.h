// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsStructOps_Shutdown.generated.h"

USTRUCT(BlueprintInternalUseOnly)
struct CSCORE_API FCsStructOps_Shutdown
{
	GENERATED_USTRUCT_BODY()

	FCsStructOps_Shutdown() { }
	virtual ~FCsStructOps_Shutdown() { }

	virtual void Shutdown() {}
};