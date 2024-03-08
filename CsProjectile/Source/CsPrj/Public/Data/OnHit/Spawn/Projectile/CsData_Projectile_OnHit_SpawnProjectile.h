// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Params/OnHit/Spawn/Projectile/CsParams_Projectile_OnHit_SpawnProjectile.h"

#include "CsData_Projectile_OnHit_SpawnProjectile.generated.h"

namespace NCsProjectile
{
	namespace NData
	{
		namespace NOnHit
		{
			namespace NSpawn
			{
				namespace NProjectile
				{
					/**
					* Interface for describing spawning Projectiles after a Projectile collides with another object.
					*  Projectile is an object that implements the interface: ICsProjectile.
					*/
					struct CSPRJ_API IProjectile : public ICsGetInterfaceMap
					{
					public:

						static const FName Name;

					public:

						virtual ~IProjectile() {}

					#define ParamsType NCsProjectile::NOnHit::NSpawn::NProjectile::FParams

					virtual const bool& ShouldSpawnProjectileOnHit() const = 0;

					virtual const ParamsType& GetSpawnProjectileOnHitParams() const = 0;

					#undef ParamsType
					};
				}
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_Projectile_OnHit_SpawnProjectile : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface for describing spawning Projectiles after a Projectile collides with another object.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
class CSPRJ_API ICsData_Projectile_OnHit_SpawnProjectile : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

#define ParamsType NCsProjectile::NOnHit::NSpawn::NProjectile::FParams

	virtual const bool& ShouldSpawnProjectileOnHit() const = 0;

	virtual const ParamsType& GetSpawnProjectileOnHitParams() const = 0;

#undef ParamsType
};