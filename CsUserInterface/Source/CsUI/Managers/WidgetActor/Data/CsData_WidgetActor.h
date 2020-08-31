// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

// Interfaces
#include "Containers/CsGetInterfaceMap.h"

#include "CsData_WidgetActor.generated.h"

UINTERFACE(BlueprintType)
class CSUI_API UCsData_WidgetActor : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class CSUI_API ICsData_WidgetActor : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:
};