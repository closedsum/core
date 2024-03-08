// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Projectile.h"

#include "CsData_GetProjectileType.generated.h"


UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_GetProjectileType : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class CSPRJ_API ICsData_GetProjectileType : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

	/**
	*
	*
	* return
	*/
	virtual const FECsProjectile& GetProjectileType() const = 0;
};