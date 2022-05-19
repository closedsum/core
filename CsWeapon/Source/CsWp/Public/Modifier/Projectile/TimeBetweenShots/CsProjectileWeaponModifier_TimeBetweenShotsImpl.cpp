// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/Projectile/TimeBetweenShots/CsProjectileWeaponModifier_TimeBetweenShotsImpl.h"

// Library
#include "Modifier/CsLibrary_WeaponModifier.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"
// Weapon
#include "Projectile/CsProjectileWeaponActorPooled.h"

const FName NCsWeapon::NProjectile::NModifier::NTimeBetweenShots::FImpl::Name = FName("NCsWeapon::NProjectile::NModifier::NTimeBetweenShots::FImpl");

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NModifier
		{
			namespace NTimeBetweenShots
			{
				namespace NImpl
				{
					namespace NCached
					{
						namespace Str
						{
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NProjectile::NModifier::NTimeBetweenShots::FImpl, Modify);
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NProjectile::NModifier::NTimeBetweenShots::FImpl, Copy);
						}
					}
				}

				FImpl::FImpl() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Application, NCsModifier::NValue::NNumeric::EApplication::Multiply)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FImpl>(this);

					typedef NCsModifier::IModifier ModifierType;
					typedef NCsWeapon::NModifier::IModifier WeaponModifierType;
					typedef NCsWeapon::NProjectile::NModifier::IModifier PrjWeaponModifierType;
					typedef NCsWeapon::NModifier::NCopy::ICopy CopyType;

					InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
					InterfaceMap->Add<WeaponModifierType>(static_cast<WeaponModifierType*>(this));
					InterfaceMap->Add<PrjWeaponModifierType>(static_cast<PrjWeaponModifierType*>(this));
					InterfaceMap->Add<ICsGetWeaponModifierType>(static_cast<ICsGetWeaponModifierType*>(this));
					InterfaceMap->Add<CopyType>(static_cast<CopyType*>(this));
					InterfaceMap->Add<ICsReset>(static_cast<ICsReset*>(this));

					CS_CTOR_SET_MEMBER_PROXY(Value);
					CS_CTOR_SET_MEMBER_PROXY(Application);
				}
				
				FImpl::~FImpl()
				{
					// ICsGetInterfaceMap
					delete InterfaceMap;
				}

				// WeaponModifierType (NCsWeapon::NModifier::IModifier)
				#pragma region

				void FImpl::Modify(ICsWeapon* Weapon)
				{
					using namespace NCsWeapon::NProjectile::NModifier::NTimeBetweenShots::NImpl::NCached;

					const FString& Context = Str::Modify;

					check(IsValidChecked(Context));

					ACsProjectileWeaponActorPooled* Actor = CS_INTERFACE_TO_UOBJECT_CAST_CHECKED(Weapon, ICsWeapon, ACsProjectileWeaponActorPooled);

					NCsModifier::NValue::NNumeric::NApplication::Modify(Actor->TimeBetweenShotsImpl.Value, GetValue(), GetApplication());
				}

				#pragma endregion WeaponModifierType (NCsWeapon::NModifier::IModifier)

				// PrjWeaponModifierType (NCsWeapon::NProjectile::NModifier::IModifier)
				#pragma region

				void FImpl::Modify(ICsProjectileWeapon* ProjectileWeapon)
				{
					using namespace NCsWeapon::NProjectile::NModifier::NTimeBetweenShots::NImpl::NCached;

					const FString& Context = Str::Modify;

					check(IsValidChecked(Context));

					ACsProjectileWeaponActorPooled* Actor = CS_INTERFACE_TO_UOBJECT_CAST_CHECKED(ProjectileWeapon, ICsProjectileWeapon, ACsProjectileWeaponActorPooled);

					NCsModifier::NValue::NNumeric::NApplication::Modify(Actor->TimeBetweenShotsImpl.Value, GetValue(), GetApplication());
				}

				#pragma endregion PrjWeaponModifierType (NCsWeapon::NProjectile::NModifier::IModifier)

				// CopyType (NCsWeapon::NModifier::NCopy::ICopy)
				#pragma region

				#define WeaponModifierType NCsWeapon::NModifier::IModifier
				void FImpl::Copy(const WeaponModifierType* From)
				{
				#undef WeaponModifierType
						
					using namespace NCsWeapon::NProjectile::NModifier::NTimeBetweenShots::NImpl::NCached;

					const FString& Context = Str::Copy;
						
					typedef NCsWeapon::NModifier::FLibrary WeaponModifierLibrary;

					const FImpl* FromImpl = WeaponModifierLibrary::PureStaticCastChecked<FImpl>(Context, From);

					SetValue(FromImpl->GetValue());
					SetApplication(FromImpl->GetApplication());
				}

				#pragma endregion CopyType (NCsWeapon::NModifier::NCopy::ICopy)

				bool FImpl::IsValidChecked(const FString& Context) const
				{
					CS_IS_FLOAT_GREATER_THAN_CHECKED(GetValue(), 0.0f)

					typedef NCsModifier::NValue::NNumeric::EMApplication ApplicationMapType;

					CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetApplication())
					return true;
				}

				bool FImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
				{
					CS_IS_FLOAT_GREATER_THAN(GetValue(), 0.0f)

					typedef NCsModifier::NValue::NNumeric::EMApplication ApplicationMapType;
					typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

					CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetApplication())
					return true;
				}
			}
		}
	}
}