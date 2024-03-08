// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/Sound/CsTypes_Sound.h"

#include "CsData_BeamWeapon_SoundFire.generated.h"

// NCsWeapon::NBeam::NData::NSound::NFire::NParmas::IParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_6(NCsWeapon, NBeam, NData, NSound, NFire, NParams, IParams)

namespace NCsWeapon
{
	namespace NBeam
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

					#define ParamsType NCsWeapon::NBeam::NData::NSound::NFire::NParams::IParams

					public:

						virtual ~IFire(){}

						/**
						*
						*
						* return
						*/
						virtual const ParamsType* GetFireSoundParams() const = 0;

					#undef ParamsType
					};
				}
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_BeamWeapon_SoundFire : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

// NCsWeapon::NBeam::NData::NSound::NFire::NParmas::IParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_6(NCsWeapon, NBeam, NData, NSound, NFire, NParams, IParams)

/**
*
*/
class CSWP_API ICsData_BeamWeapon_SoundFire : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

#define ParamsType NCsWeapon::NBeam::NData::NSound::NFire::NParams::IParams

public:

	/**
	*
	*
	* return
	*/
	virtual const ParamsType* GetFireSoundParams() const = 0;

#undef ParamsType
};