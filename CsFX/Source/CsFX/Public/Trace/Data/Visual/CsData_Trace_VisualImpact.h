// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/FX/CsTypes_FX.h"
#include "Chaos/ChaosEngineInterface.h"

#include "CsData_Trace_VisualImpact.generated.h"

namespace NCsTrace
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NImpact
			{
				/**
				*/
				struct CSFX_API IImpact : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~IImpact() {}

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
class CSFX_API UCsData_Trace_VisualImpact : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSFX_API ICsData_Trace_VisualImpact : public ICsGetInterfaceMap
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