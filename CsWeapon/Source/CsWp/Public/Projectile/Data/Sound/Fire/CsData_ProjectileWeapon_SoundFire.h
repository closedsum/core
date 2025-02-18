// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
// Params
#include "Projectile/Data/Sound/Fire/CsParams_ProjectileWeapon_SoundFire.h"

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

					public:

						virtual ~IFire(){}

					private:

						// Allow clearer names without name collisions
						struct _
						{
							using FireSoundParamsType = NCsWeapon::NProjectile::NFire::NSound::FParams;
						};

					public:

						/**
						* Get any Sound information related to the Fire action.
						*
						* return Fire Sound Params
						*/
						virtual const _::FireSoundParamsType& GetFireSoundParams() const = 0;
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

private:

	// Allow clearer names without name collisions
	struct _
	{
		using FireSoundParamsType = NCsWeapon::NProjectile::NFire::NSound::FParams;
	};

public:

	/**
	* Get any Sound information related to the Fire action.
	*
	* return Fire Sound Params
	*/
	virtual const _::FireSoundParamsType& GetFireSoundParams() const = 0;
};