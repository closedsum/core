// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "CsData_Sound.generated.h"

UINTERFACE(BlueprintType)
class CSCORE_API UCsData_Sound : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSCORE_API ICsData_Sound : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;
};