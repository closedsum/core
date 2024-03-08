// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Point/Sequence/Data/Visual/Impact/CsTypes_PointSequenceWeapon_VisualImpact.h"

#include "CsData_PointSequenceWeapon_VisualImpact.generated.h"

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NData
			{
				namespace NVisual
				{
					namespace NImpact
					{
						/**
						*/
						struct CSWP_API IImpact : public ICsGetInterfaceMap
						{
						public:

							static const FName Name;

						public:

						#define ImpactVisualInfoType NCsWeapon::NPoint::NSequence::NImpact::NVisual::FInfo

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
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_PointSequenceWeapon_VisualImpact : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSWP_API ICsData_PointSequenceWeapon_VisualImpact : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:
	
#define ImpactVisualInfoType NCsWeapon::NPoint::NSequence::NImpact::NVisual::FInfo

	/**
	* Get the Visual Impact information associated with the given SurfaceType.
	*
	* @param SurfaceType	Physics Surface type.
	* return				Visual Impact information associated with the given SurfaceType
	*/
	virtual const ImpactVisualInfoType& GetImpactVisualInfo(const EPhysicalSurface& SurfaceType) const = 0;

#undef ImpactVisualInfoType
};