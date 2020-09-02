// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "CsData_Weapon.generated.h"

UINTERFACE(BlueprintType)
class CSWP_API UCsData_Weapon : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class CSWP_API ICsData_Weapon : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;
};