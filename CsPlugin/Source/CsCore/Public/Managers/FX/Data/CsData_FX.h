// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "CsData_FX.generated.h"

UINTERFACE(BlueprintType)
class CSCORE_API UCsData_FX : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsData_FX : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;
};