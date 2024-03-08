// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Params/OnHit/Ricochet/CsParams_Projectile_OnHit_Ricochet.h"

#include "CsData_Projectile_OnHit_Ricochet.generated.h"

CS_FWD_DECLARE_STRUCT_NAMESPACE_1(NCsModifier, IModifier)

namespace NCsProjectile
{
	namespace NData
	{
		namespace NOnHit
		{
			namespace NRicochet
			{
				/**
				* Interface for describing any ricochet collision associated with a Projectile.
				*  Projectile is an object that implements the interface: ICsProjectile.
				*/
				struct CSPRJ_API IRicochet : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~IRicochet() {}

				#define ParamsType NCsProjectile::NOnHit::NRicochet::FParams

					virtual const bool& ShouldRicochetOnHit() const = 0;

					virtual const ParamsType& GetRicochetOnHitParams() const = 0;

				#undef ParamsType
				};
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_Projectile_OnHit_Ricochet : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface for describing any ricochet collision associated with a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
class CSPRJ_API ICsData_Projectile_OnHit_Ricochet : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

#define ParamsType NCsProjectile::NOnHit::NRicochet::FParams

	virtual const bool& ShouldRicochetOnHit() const = 0;

	virtual const ParamsType& GetRicochetOnHitParams() const = 0;

#undef ParamsType
};