// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/Sound/CsTypes_Sound.h"
#include "CsData_ProjectileWeapon_SoundFire.generated.h"

// NCsWeapon::NProjectile::NData::NSound::NFire::NParmas::IParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_6(NCsWeapon, NProjectile, NData, NSound, NFire, NParams, IParams)

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

#define ParamsType NCsWeapon::NProjectile::NData::NSound::NFire::NParams::IParams

					public:

						/**
						*
						*
						* return
						*/
						virtual ParamsType* GetFireSoundParams() const = 0;

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

// NCsWeapon::NProjectile::NData::NSound::NFire::NParmas::IParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_6(NCsWeapon, NProjectile, NData, NSound, NFire, NParams, IParams)

/**
*
*/
class CSWP_API ICsData_ProjectileWeapon_SoundFire : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

#define ParamsType NCsWeapon::NProjectile::NData::NSound::NFire::NParams::IParams

public:

	/**
	*
	*
	* return
	*/
	virtual ParamsType* GetFireSoundParams() const = 0;

#undef ParamsType
};