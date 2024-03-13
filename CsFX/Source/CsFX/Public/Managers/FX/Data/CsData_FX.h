// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"

#include "CsData_FX.generated.h"

UINTERFACE(BlueprintType)
class CSFX_API UCsData_FX : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class CSFX_API ICsData_FX : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;
};