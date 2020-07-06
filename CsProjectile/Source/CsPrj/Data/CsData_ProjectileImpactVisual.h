// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/FX/CsTypes_FX.h"
#include "CsData_ProjectileImpactVisual.generated.h"

UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_ProjectileImpactVisual : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class CSPRJ_API ICsData_ProjectileImpactVisual : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:
	
	virtual const FCsFX& GetImpactFX(const EPhysicalSurface& SurfaceType) const = 0;
};