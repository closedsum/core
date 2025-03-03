// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Params/Tracking/CsParams_Projectile_Tracking.h"

#include "CsData_Projectile_Tracking.generated.h"

namespace NCsProjectile
{
	namespace NData
	{
		namespace NTracking
		{
			/**
			* Interface for describing any information related to a Projectile Tracking.
			*  Projectile is an object that implements the interface: ICsProjectile.
			*/
			struct CSPRJ_API ITracking : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~ITracking() {}

			private:

				// Allow clearer names without name collisions
				struct _
				{
					using ParamsType = NCsProjectile::NTracking::FParams;
				};

			public:

				virtual const bool& ShouldUseTracking() const = 0;

				virtual const _::ParamsType& GetTrackingParams() const = 0;
			};
		}
	}
}

UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_Projectile_Tracking : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface for describing any information related to a Projectile Tracking.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
class CSPRJ_API ICsData_Projectile_Tracking : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

private:

	// Allow clearer names without name collisions
	struct _
	{
		using ParamsType = NCsProjectile::NTracking::FParams;
	};

public:

	virtual const bool& ShouldUseTracking() const = 0;

	virtual const _::ParamsType& GetTrackingParams() const = 0;
};