// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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
							CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Sound),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(AttachType, EAttach::Component)
						{
							InterfaceMap = new FCsInterfaceMap();

							InterfaceMap->SetRoot<FImpl>(this);

							InterfaceMap->Add<IParams>(static_cast<IParams*>(this));
						}

						FImpl::~FImpl()
						{
							delete InterfaceMap;
						}

						bool FImpl::IsValidChecked(const FString& Context) const
						{
							check(GetSound().IsValidChecked(Context));
							return true;
						}

						bool FImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
						{
							if (!GetSound().IsValid(Context, Log))
								return false;
							return true;
						}
					}
				}
			}
		}
	}
}