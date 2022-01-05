// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Modifier/CsModifier.h"
#include "Modifier/CsWeaponModifier.h"
#include "Modifier/Projectile/CsProjectileWeaponModifier.h"
#include "Reset/CsReset.h"
// Types
#include "Modifier/CsTypes_WeaponModifier.h"
// Log
#include "Utility/CsWpLog.h"

class ICsWeapon;
class ICsProjectileWeapon;

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)

namespace NCsWeapon
{
	namespace NModifier
	{
		namespace NProjectile
		{
			namespace NTimeBetweenShots
			{
			#define ModifierType NCsModifier::IModifier
			#define WeaponModifierType NCsWeapon::NModifier::IModifier
			#define PrjWeaponModifierType NCsWeapon::NModifier::NProjectile::IProjectile

				struct CSWP_API FImpl : public ModifierType,
										public WeaponModifierType,
										public PrjWeaponModifierType,
										public ICsReset
				{
				public:

					static const FName Name;

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

				public:

				public:
						
					FImpl();
					~FImpl();

					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

				// WeaponModifierType (NCsWeapon::NModifier::IModifier)
				#pragma region
				public:

					void Modify(ICsWeapon* Weapon){}

				#pragma endregion WeaponModifierType (NCsWeapon::NModifier::IModifier)

				// PrjWeaponModifierType (NCsWeapon::NModifier::NProjectile::IProjectile)
				#pragma region
				public:

					void Modify(ICsProjectileWeapon* ProjectileWeapon){}

				#pragma endregion PrjWeaponModifierType (NCsWeapon::NModifier::NProjectile::IProjectile)

				// ICsReset
				#pragma region
				public:

					FORCEINLINE void Reset()
					{
					}

				#pragma endregion ICsReset

				public:

					void CopyTo(FImpl* To) const;

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
				};
				
			#undef ModifierType
			#undef WeaponModifierType
			#undef PrjWeaponModifierType
			}
		}
	}
}