// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Beam/Data/Visual/CsParams_BeamWeapon_VisualFire.h"

#include "CsData_BeamWeapon_VisualFire.generated.h"

// NCsWeapon::NProjectile::NData::NVisual::NFire::NParams::IParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_6(NCsWeapon, NBeam, NData, NVisual, NFire, NParams, IParams)

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NData
		{
			namespace NVisual
			{
				namespace NFire
				{
					/**
					*
					*/
					struct CSWP_API IFire : public ICsGetInterfaceMap
					{
					public:

						static const FName Name;

					#define ParamsType NCsWeapon::NBeam::NData::NVisual::NFire::NParams::IParams

					public:

						virtual ~IFire(){}

						/**
						*
						*
						* return
						*/
						virtual const ParamsType* GetFireFXParams() const = 0;

					#undef ParamsType
					};
				}
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_BeamWeapon_VisualFire : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSWP_API ICsData_BeamWeapon_VisualFire : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

#define ParamsType NCsWeapon::NBeam::NData::NVisual::NFire::NParams::IParams

public:

	/**
	*
	*
	* return
	*/
	virtual const ParamsType* GetFireFXParams() const = 0;

#undef ParamsType
};