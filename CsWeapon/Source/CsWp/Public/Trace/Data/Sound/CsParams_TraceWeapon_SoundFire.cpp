// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Trace/Data/Sound/CsParams_TraceWeapon_SoundFire.h"

#include "Containers/CsInterfaceMap.h"

#define NCurrentNamespace NCsWeapon::NTrace::NData::NSound::NFire::NParams

const FName NCurrentNamespace::IParams::Name = FName("NCsWeapon::NTrace::NData::NSound::NFire::NParams::IParams::Name");

const FName NCurrentNamespace::FEmu::Name = FName("NCsWeapon::NTrace::NData::NSound::NFire::NParams::FEmu::Name");

#undef NCurrentNamespace

namespace NCsWeapon
{
	namespace NTrace
	{
		namespace NData
		{
			namespace NSound
			{
				namespace NFire
				{
					namespace NParams
					{
						FEmu::FEmu() :
							// ICsGetInterfaceMap
							InterfaceMap(nullptr),
							// IParams
							Sound(nullptr),
							Attach(nullptr)

						{
							InterfaceMap = new FCsInterfaceMap();

							InterfaceMap->SetRoot<FEmu>(this);

							InterfaceMap->Add<IParams>(static_cast<IParams*>(this));
						}

						FEmu::~FEmu()
						{
							delete InterfaceMap;
						}
					}
				}
			}
		}
	}
}