// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.

#include "UObject/Interface.h"
#include "CsGetInterfaceMap.generated.h"
#pragma once

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