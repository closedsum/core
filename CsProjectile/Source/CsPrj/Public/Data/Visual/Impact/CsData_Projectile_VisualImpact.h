// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/FX/CsTypes_FX.h"

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

					/**
					* Get the FX information associated with the given SurfaceType.
					* 
					* @param SurfaceType	Physics Surface type.
					* return				FX associated with the given SurfaceType
					*/
					virtual const FCsFX& GetImpactFX(const EPhysicalSurface& SurfaceType) const = 0;
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
	
	/**
	* Get the FX information associated with the given SurfaceType.
	* 
	* @param SurfaceType	Physics Surface type.
	* return				FX associated with the given SurfaceType
	*/
	virtual const FCsFX& GetImpactFX(const EPhysicalSurface& SurfaceType) const = 0;
};