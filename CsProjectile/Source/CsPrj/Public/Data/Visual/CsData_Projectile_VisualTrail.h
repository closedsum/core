// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/FX/CsTypes_FX.h"
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

				public:

					/**
					* Get the Trail FX to play when Projectile is Launched.
					* If 
					*  The Projectile Data implements the interface: 
					*  StaticMeshVisualDataType (NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh) then
					*  the Trail with be attached to the Mesh associated with Projectile.
					* Else
					*  The Trail is attached to the Collision of the Projectile.
					* 
					* return Trail FX
					*/
					virtual const FCsFX& GetTrailFX() const = 0;
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

public:

	/**
	* Get the Trail FX to play when Projectile is Launched.
	* If
	*  The Projectile Data implements the interface:
	*  StaticMeshVisualDataType (NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh) then
	*  the Trail with be attached to the Mesh associated with Projectile.
	* Else
	*  The Trail is attached to the Collision of the Projectile.
	*
	* return Trail FX
	*/
	virtual const FCsFX& GetTrailFX() const = 0;
};