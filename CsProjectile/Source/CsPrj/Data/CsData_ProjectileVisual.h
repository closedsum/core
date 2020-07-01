// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/FX/CsTypes_FX.h"
#include "CsData_ProjectileVisual.generated.h"

UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_ProjectileVisual : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class UStaticMesh;
class USkeletalMesh;

class CSPRJ_API ICsData_ProjectileVisual : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	virtual UStaticMesh* GetStaticMesh() const = 0;

	virtual USkeletalMesh* GetSkeletalMesh() const = 0;
	
	virtual const FCsFX& GetTrailFX() const = 0;
};