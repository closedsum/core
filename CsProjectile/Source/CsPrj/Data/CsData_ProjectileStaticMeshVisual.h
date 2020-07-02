// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "Data/CsTypes_Data_Projectile.h"
#include "CsData_ProjectileStaticMeshVisual.generated.h"

UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_ProjectileStaticMeshVisual : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class UStaticMesh;

class CSPRJ_API ICsData_ProjectileStaticMeshVisual : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	virtual const FCsPrjStaticMesh& GetStaticMesh() const = 0;
};