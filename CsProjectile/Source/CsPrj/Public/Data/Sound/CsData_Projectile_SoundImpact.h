// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/Sound/CsTypes_Sound.h"

#include "CsData_Projectile_SoundImpact.generated.h"

namespace NCsProjectile
{
	namespace NData
	{
		namespace NSound
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

					virtual const FCsSound& GetImpactSound(const EPhysicalSurface& SurfaceType) const = 0;
				};
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_Projectile_SoundImpact : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSPRJ_API ICsData_Projectile_SoundImpact : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:
	
	virtual const FCsSound& GetImpactSound(const EPhysicalSurface& SurfaceType) const = 0;
};