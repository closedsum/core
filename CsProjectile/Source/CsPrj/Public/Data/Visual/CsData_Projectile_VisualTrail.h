// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interface
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/Visual/CsTypes_Projectile_Visual_Trail.h"

#include "CsData_Projectile_VisualTrail.generated.h"

namespace NCsProjectile
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NTrail
			{
				/**
				* Interface describes the Trail visual information for a Projectile.
				*  Projectile is an object that implements the interface: ICsProjectile.
				*/
				struct CSPRJ_API ITrail : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				private:

					// Allow clearer names without name collisions
					struct _
					{
						using TrailInfoType = NCsProjectile::NVisual::NTrail::FInfo;
					};

				public:

					/**
					* Get any information related to a Trail.
					* 
					* return Trail Info
					*/
					virtual const _::TrailInfoType& GetTrailInfo() const = 0;
				};
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_Projectile_VisualTrail : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface describes the Trail visual information for a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
class CSPRJ_API ICsData_Projectile_VisualTrail : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

private:

	// Allow clearer names without name collisions
	struct _
	{
		using TrailInfoType = NCsProjectile::NVisual::NTrail::FInfo;
	};

public:

	/**
	* Get any information related to a Trail.
	*
	* return Trail Info
	*/
	virtual const _::TrailInfoType& GetTrailInfo() const = 0;
};