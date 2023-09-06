// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/Sound/CsTypes_Sound.h"

#include "CsData_Beam_SoundImpact.generated.h"

namespace NCsBeam
{
	namespace NData
	{
		namespace NSound
		{
			namespace NImpact
			{
				/**
				*/
				struct CSBEAM_API IImpact : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual const FCsSound& GetImpactSound(const EPhysicalSurface& SurfaceType) const = 0;
				};
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSBEAM_API UCsData_Beam_SoundImpact : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSBEAM_API ICsData_Beam_SoundImpact : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:
	
	virtual const FCsSound& GetImpactSound(const EPhysicalSurface& SurfaceType) const = 0;
};