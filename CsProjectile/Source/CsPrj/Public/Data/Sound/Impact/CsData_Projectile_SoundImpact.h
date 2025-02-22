// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/Sound/Impact/CsTypes_Projectile_Sound_Impact.h"

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

				private:

					// Allow clearer names without name collisions
					struct _
					{
						using ImpactSoundInfoType = NCsProjectile::NImpact::NSound::FInfo;
					};

				public:

					/**
					* Get the Visual Impact information associated with the given SurfaceType.
					*
					* @param SurfaceType	Physics Surface type.
					* return				Visual Impact information associated with the given SurfaceType
					*/
					virtual const _::ImpactSoundInfoType& GetImpactSoundInfo(const EPhysicalSurface& SurfaceType) const = 0;
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

private:

	// Allow clearer names without name collisions
	struct _
	{
		using ImpactSoundInfoType = NCsProjectile::NImpact::NSound::FInfo;
	};

public:

	/**
	* Get the Visual Impact information associated with the given SurfaceType.
	*
	* @param SurfaceType	Physics Surface type.
	* return				Visual Impact information associated with the given SurfaceType
	*/
	virtual const _::ImpactSoundInfoType& GetImpactSoundInfo(const EPhysicalSurface& SurfaceType) const = 0;
};