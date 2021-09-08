// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/FX/CsTypes_FX.h"

#include "CsData_Trace_VisualTrail.generated.h"

namespace NCsTrace
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NTrail
			{
				/**
				*/
				struct CSCORE_API ITrail : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~ITrail() {}

					/**
					*/
					virtual const FCsFX& GetTrailFX() const = 0;
				};
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSCORE_API UCsData_Trace_VisualTrail : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSCORE_API ICsData_Trace_VisualTrail : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*/
	virtual const FCsFX& GetTrailFX() const = 0;
};