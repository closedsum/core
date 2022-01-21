// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/FX/CsTypes_FX.h"

#include "CsData_TraceWeapon_VisualTracer.generated.h"

namespace NCsWeapon
{
	namespace NTrace
	{
		namespace NData
		{
			namespace NVisual
			{
				namespace NTracer
				{
					/**
					*/
					struct CSWP_API ITracer : public ICsGetInterfaceMap
					{
					public:

						static const FName Name;

					public:

						/**
						*/
						virtual const FCsFX& GetTracerFX() const = 0;
					};
				}
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_TraceWeapon_VisualTracer : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSWP_API ICsData_TraceWeapon_VisualTracer : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*/
	virtual const FCsFX& GetTracerFX() const = 0;
};