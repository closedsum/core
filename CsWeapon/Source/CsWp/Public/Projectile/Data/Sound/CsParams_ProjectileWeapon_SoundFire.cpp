// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/Sound/CsParams_ProjectileWeapon_SoundFire.h"

// Containers
#include "Containers/CsInterfaceMap.h"

#define NCurrentNamespace NCsWeapon::NProjectile::NData::NSound::NFire::NParams

const FName NCurrentNamespace::IParams::Name = FName("NCsWeapon::NProjectile::NData::NSound::NFire::NParams::IParams::Name");

const FName NCurrentNamespace::FImpl::Name = FName("NCsWeapon::NProjectile::NData::NSound::NFire::NParams::FImpl::Name");

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
						FImpl::FImpl() :
							InterfaceMap(nullptr),
							// IParams
							Sound(),
							Sound_Emu(nullptr),
							AttachType(EAttach::Component),
							AttachType_Emu(nullptr)

						{
							InterfaceMap = new FCsInterfaceMap();

							InterfaceMap->SetRootName(FImpl::Name);

							InterfaceMap->Add<IParams>(static_cast<IParams*>(this));
						}

						FImpl::~FImpl()
						{
							delete InterfaceMap;
						}

						bool FImpl::IsValidChecked(const FString& Context) const
						{
							check(Sound.IsValidChecked(Context));
							return true;
						}

						bool FImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
						{
							if (!Sound.IsValid(Context, Log))
								return false;
							return true;
						}
					}
				}
			}
		}
	}
}