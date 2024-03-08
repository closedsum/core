// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/Sound/CsTypes_Sound.h"

#include "CsData_Trace_SoundImpact.generated.h"

namespace NCsTrace
{
	namespace NData
	{
		namespace NSound
		{
			namespace NImpact
			{
				/**
				*/
				struct CSCORE_API IImpact : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~IImpact() {}

					virtual const FCsSound& GetImpactSound(const EPhysicalSurface& SurfaceType) const = 0;
				};
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSCORE_API UCsData_Trace_SoundImpact : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSCORE_API ICsData_Trace_SoundImpact : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:
	
	virtual const FCsSound& GetImpactSound(const EPhysicalSurface& SurfaceType) const = 0;
};