// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/Visual/Impact/CsTypes_Projectile_Visual_Impact.h"

#include "CsData_Projectile_VisualImpact.generated.h"

namespace NCsProjectile
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NImpact
			{
				/**
				*/
				struct CSPRJ_API IImpact : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

				#define ImpactVisualInfoType NCsProjectile::NImpact::NVisual::FInfo

					/**
					* Get the Visual Impact information associated with the given SurfaceType.
					* 
					* @param SurfaceType	Physics Surface type.
					* return				Visual Impact information associated with the given SurfaceType
					*/
					virtual const ImpactVisualInfoType& GetImpactVisualInfo(const EPhysicalSurface& SurfaceType) const = 0;

				#undef ImpactVisualInfoType
				};
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_Projectile_VisualImpact : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSPRJ_API ICsData_Projectile_VisualImpact : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:
	
#define ImpactVisualInfoType NCsProjectile::NImpact::NVisual::FInfo

	/**
	* Get the Visual Impact information associated with the given SurfaceType.
	*
	* @param SurfaceType	Physics Surface type.
	* return				Visual Impact information associated with the given SurfaceType
	*/
	virtual const ImpactVisualInfoType& GetImpactVisualInfo(const EPhysicalSurface& SurfaceType) const = 0;

#undef ImpactVisualInfoType
};