// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsInterfaceMap.h"
#include "CsData_ProjectileWeapon.generated.h"

UINTERFACE(BlueprintType)
class CSWP_API UCsData_ProjectileWeapon : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class CSWP_API ICsData_ProjectileWeapon : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:
};