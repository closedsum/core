// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Params
#include "Point/Sequence/Data/Sound/Fire/CsParams_PointSequenceWeapon_SoundFire.h"

#include "CsData_PointSequenceWeapon_SoundFire.generated.h"

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NData
			{
				namespace NSound
				{
					namespace NFire
					{
						/**
						* Interface that describes any sound information associated to the Fire() call
						* from a Point Seqeunce Weapon.
						*  Weapon is an object that implements the interface: ICsWeapon.
						*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
						*/
						struct CSWP_API IFire : public ICsGetInterfaceMap
						{
						public:

							static const FName Name;

						#define FireSoundParamsType NCsWeapon::NPoint::NSequence::NFire::NSound::FParams

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
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_PointSequenceWeapon_SoundFire : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface that describes any sound information associated to the Fire() call
* from a Point Sequence Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
*/
class CSWP_API ICsData_PointSequenceWeapon_SoundFire : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

#define FireSoundParamsType NCsWeapon::NPoint::NSequence::NFire::NSound::FParams

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