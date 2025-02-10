// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
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

			private:

				// Allow clearer names without name collisions
				struct _
				{
					using ParamsType = NCsProjectile::NLaunch::FParams;
				};

			public:

				virtual const _::ParamsType& GetLaunchParams() const = 0;
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

private:

	// Allow clearer names without name collisions
	struct _
	{
		using ParamsType = NCsProjectile::NLaunch::FParams;
	};

	virtual const _::ParamsType& GetLaunchParams() const = 0;
};