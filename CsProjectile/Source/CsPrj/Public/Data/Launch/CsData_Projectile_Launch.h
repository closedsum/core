// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Params/Launch/CsParams_Projectile_Launch.h"

#include "CsData_Projectile_Launch.generated.h"

namespace NCsProjectile
{
	namespace NData
	{
		namespace NLaunch
		{
			/**
			* Interface for describing any launch information associated with a Projectile.
			*  Projectile is an object that implements the interface: ICsProjectile.
			*/
			struct CSPRJ_API ILaunch : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~ILaunch() {}

			#define ParamsType NCsProjectile::NLaunch::FParams

				virtual const ParamsType& GetLaunchParams() const = 0;

			#undef ParamsType
			};
		}
	}
}

UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_Projectile_Launch : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface for describing any launch information associated with a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
class CSPRJ_API ICsData_Projectile_Launch : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

#define ParamsType NCsProjectile::NLaunch::FParams

	virtual const ParamsType& GetLaunchParams() const = 0;

#undef ParamsType
};