// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
// Types
#include "Managers/Projectile/CsSettings_Manager_Projectile.h"

#include "CsGetSettingsManagerProjectilePoolParams.generated.h"

UINTERFACE(BlueprintType)
class CSPRJ_API UCsGetSettingsManagerProjectilePoolParams : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSPRJ_API ICsGetSettingsManagerProjectilePoolParams
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*
	* return
	*/
	virtual const TMap<FECsProjectile, FCsSettings_Manager_Projectile_PoolParams>& GetSettingsManagerProjectilePoolParams() const = 0;
};