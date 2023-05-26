// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
// Params
#include "Point/Data/Sound/Fire/CsParams_PointWeapon_SoundFire.h"

#include "CsData_PointWeapon_SoundFire.generated.h"

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NData
		{
			namespace NSound
			{
				namespace NFire
				{
					/**
					* Interface that describes any sound information associated to the Fire() call
					* from a Point Weapon.
					*  Weapon is an object that implements the interface: ICsWeapon.
					*  Point Weapon is an object that implements the interface: ICsPointWeapon.
					*/
					struct CSWP_API IFire : public ICsGetInterfaceMap
					{
					public:

						static const FName Name;

					#define FireSoundParamsType NCsWeapon::NPoint::NFire::NSound::FParams

					public:

						virtual ~IFire(){}

						/**
						* Get whether to use Fire Sound Params or not.
						* 
						* return
						*/
						virtual const bool& UseFireSoundParams() const = 0;

						/**
						* Get any Sound information related to the Fire action.
						*
						* return Fire Sound Params
						*/
						virtual const FireSoundParamsType& GetFireSoundParams() const = 0;

					#undef FireSoundParamsType
					};
				}
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_PointWeapon_SoundFire : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface that describes any sound information associated to the Fire() call
* from a Point Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Weapon is an object that implements the interface: ICsPointWeapon.
*/
class CSWP_API ICsData_PointWeapon_SoundFire : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

#define FireSoundParamsType NCsWeapon::NPoint::NFire::NSound::FParams

public:

	/**
	* Get whether to use Fire Sound Params or not.
	* 
	* return
	*/
	virtual const bool& UseFireSoundParams() const = 0;

	/**
	* Get any Sound information related to the Fire action.
	*
	* return Fire Sound Params
	*/
	virtual const FireSoundParamsType& GetFireSoundParams() const = 0;

#undef FireSoundParamsType
};