// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/Projectile/TimeBetweenShots/CsProjectileWeaponModifier_TimeBetweenShotsImpl.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"

const FName NCsWeapon::NProjectile::NModifier::NTimeBetweenShots::FImpl::Name = FName("NCsWeapon::NProjectile::NModifier::NTimeBetweenShots::FImpl");

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NModifier
		{
			namespace NTimeBetweenShots
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NProjectile::NModifier::NTimeBetweenShots::FImpl, Modify);
					}
				}

				FImpl::FImpl() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Application, NCsModifier::NValue::NIntegral::EApplication::Multiply)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FImpl>(this);

					typedef NCsModifier::IModifier ModifierType;
					typedef NCsWeapon::NModifier::IModifier WeaponModifierType;
					typedef NCsWeapon::NProjectile::NModifier::IModifier PrjWeaponModifierType;

					InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
					InterfaceMap->Add<WeaponModifierType>(static_cast<WeaponModifierType*>(this));
					InterfaceMap->Add<PrjWeaponModifierType>(static_cast<PrjWeaponModifierType*>(this));
					InterfaceMap->Add<ICsReset>(static_cast<ICsReset*>(this));

					CS_CTOR_SET_MEMBER_PROXY(Value);
					CS_CTOR_SET_MEMBER_PROXY(Application);
				}
				
				FImpl::~FImpl()
				{
					// ICsGetInterfaceMap
					delete InterfaceMap;
				}

				void FImpl::CopyTo(FImpl* To) const
				{
					To->SetValue(GetValue());
					To->SetApplication(GetApplication());
				}

				bool FImpl::IsValidChecked(const FString& Context) const
				{
					CS_IS_FLOAT_GREATER_THAN_CHECKED(GetValue(), 0.0f)

					typedef NCsModifier::NValue::NIntegral::EMApplication ApplicationMapType;

					CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetApplication())
					return true;
				}

				bool FImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
				{
					CS_IS_FLOAT_GREATER_THAN(GetValue(), 0.0f)

					typedef NCsModifier::NValue::NIntegral::EMApplication ApplicationMapType;
					typedef NCsModifier::NValue::NIntegral::EApplication ApplicationType;

					CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetApplication())
					return true;
				}
			}
		}
	}
}