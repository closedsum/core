// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/Sound/CsParams_ProjectileWeapon_SoundFire.h"

#include "Containers/CsInterfaceMap.h"

#define NCurrentNamespace NCsWeapon::NProjectile::NData::NSound::NFire::NParams

const FName NCurrentNamespace::IParams::Name = FName("NCsWeapon::NProjectile::NData::NSound::NFire::NParams::IParams::Name");

const FName NCurrentNamespace::FEmu::Name = FName("NCsWeapon::NProjectile::NData::NSound::NFire::NParams::FEmu::Name");

#undef NCurrentNamespace

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

							InterfaceMap->SetRootName(FEmu::Name);

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