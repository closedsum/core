// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Beam/Data/Sound/CsParams_BeamWeapon_SoundFire.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsWeapon::NBeam::NData::NSound::NFire::NParams::IParams::Name = FName("NCsWeapon::NBeam::NData::NSound::NFire::NParams::IParams::Name");

const FName NCsWeapon::NBeam::NData::NSound::NFire::NParams::FProxy::Name = FName("NCsWeapon::NBeam::NData::NSound::NFire::NParams::FProxy::Name");

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
					namespace NParams
					{
						FProxy::FProxy() :
							// ICsGetInterfaceMap
							InterfaceMap(nullptr),
							// IParams
							Sound(nullptr),
							Attach(nullptr)

						{
							InterfaceMap = new FCsInterfaceMap();

							InterfaceMap->SetRoot<FProxy>(this);

							InterfaceMap->Add<IParams>(static_cast<IParams*>(this));
						}

						FProxy::~FProxy()
						{
							delete InterfaceMap;
						}
					}
				}
			}
		}
	}
}