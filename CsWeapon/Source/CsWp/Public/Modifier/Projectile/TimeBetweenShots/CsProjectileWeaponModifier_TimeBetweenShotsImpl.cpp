// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/Projectile/TimeBetweenShots/CsProjectileWeaponModifier_TimeBetweenShotsImpl.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"

const FName NCsWeapon::NModifier::NProjectile::NTimeBetweenShots::FImpl::Name = FName("NCsWeapon::NModifier::NProjectile::NTimeBetweenShots::FImpl");

namespace NCsWeapon
{
	namespace NModifier
	{
		namespace NProjectile
		{
			namespace NTimeBetweenShots
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NModifier::NProjectile::NTimeBetweenShots::FImpl, Modify);
					}
				}

				FImpl::FImpl() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FImpl>(this);

					typedef NCsModifier::IModifier ModifierType;
					typedef NCsWeapon::NModifier::IModifier WeaponModifierType;
					typedef NCsWeapon::NModifier::NProjectile::IProjectile PrjWeaponModifierType;

					InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
					InterfaceMap->Add<WeaponModifierType>(static_cast<WeaponModifierType*>(this));
					InterfaceMap->Add<PrjWeaponModifierType>(static_cast<PrjWeaponModifierType*>(this));
					InterfaceMap->Add<ICsReset>(static_cast<ICsReset*>(this));
				}
				
				FImpl::~FImpl()
				{
					// ICsGetInterfaceMap
					delete InterfaceMap;
				}

				void FImpl::CopyTo(FImpl* To) const
				{
				}

				bool FImpl::IsValidChecked(const FString& Context) const
				{
					return true;
				}

				bool FImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
				{
					return true;
				}
			}
		}
	}
}