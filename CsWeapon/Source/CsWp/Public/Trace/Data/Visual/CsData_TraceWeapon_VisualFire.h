// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Trace/Data/Visual/CsParams_TraceWeapon_VisualFire.h"

#include "CsData_TraceWeapon_VisualFire.generated.h"

// NCsWeapon::NProjectile::NData::NVisual::NFire::NParams::IParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_6(NCsWeapon, NTrace, NData, NVisual, NFire, NParams, IParams)

namespace NCsWeapon
{
	namespace NTrace
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

					#define ParamsType NCsWeapon::NTrace::NData::NVisual::NFire::NParams::IParams

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
class CSWP_API UCsData_TraceWeapon_VisualFire : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSWP_API ICsData_TraceWeapon_VisualFire : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

#define ParamsType NCsWeapon::NTrace::NData::NVisual::NFire::NParams::IParams

public:

	/**
	*
	*
	* return
	*/
	virtual const ParamsType* GetFireFXParams() const = 0;

#undef ParamsType
};