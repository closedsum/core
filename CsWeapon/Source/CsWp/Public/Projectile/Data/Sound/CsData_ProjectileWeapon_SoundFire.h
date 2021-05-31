// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
// Params
#include "Projectile/Data/Sound/CsParams_ProjectileWeapon_SoundFire.h"

#include "CsData_ProjectileWeapon_SoundFire.generated.h"

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NData
		{
			namespace NSound
			{
				namespace NFire
				{
					/**/
					struct CSWP_API IFire : public ICsGetInterfaceMap
					{
					public:

						static const FName Name;

					#define ParamsType NCsWeapon::NProjectile::NData::NSound::NFire::NParams::FImpl

					public:

						virtual ~IFire(){}

						/**
						*
						*
						* return
						*/
						virtual const ParamsType& GetFireSoundParams() const = 0;

					#undef ParamsType
					};
				}
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_ProjectileWeapon_SoundFire : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSWP_API ICsData_ProjectileWeapon_SoundFire : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

#define ParamsType NCsWeapon::NProjectile::NData::NSound::NFire::NParams::FImpl

public:

	/**
	*
	*
	* return
	*/
	virtual const ParamsType& GetFireSoundParams() const = 0;

#undef ParamsType
};