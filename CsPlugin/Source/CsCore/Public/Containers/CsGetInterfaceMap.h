// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetInterfaceMap.generated.h"

UINTERFACE()
class CSCORE_API UCsGetInterfaceMap : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

struct FCsInterfaceMap;

class CSCORE_API ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

	virtual FCsInterfaceMap* GetInterfaceMap() const = 0;
};