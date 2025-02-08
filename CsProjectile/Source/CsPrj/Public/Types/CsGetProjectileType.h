// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
// Types
#include "Types/CsTypes_Projectile.h"

#include "CsGetProjectileType.generated.h"

UINTERFACE(BlueprintType)
class CSPRJ_API UCsGetProjectileType : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSPRJ_API ICsGetProjectileType
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*
	* return
	*/
	virtual const FECsProjectile& GetProjectileType() const = 0;
};