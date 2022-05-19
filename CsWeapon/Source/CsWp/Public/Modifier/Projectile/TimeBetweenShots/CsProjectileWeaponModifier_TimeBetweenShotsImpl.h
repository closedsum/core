// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Modifier/CsModifier.h"
#include "Modifier/CsWeaponModifier.h"
#include "Modifier/Projectile/CsProjectileWeaponModifier.h"
#include "Modifier/Types/CsGetWeaponModifierType.h"
#include "Modifier/Copy/CsWeaponModifier_Copy.h"
#include "Reset/CsReset.h"
// Types
#include "Modifier/CsTypes_Modifier.h"
#include "Modifier/Types/CsTypes_WeaponModifier.h"
// Log
#include "Utility/CsWpLog.h"

class ICsWeapon;
class ICsProjectileWeapon;

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NModifier
		{
			namespace NTimeBetweenShots
			{
			#define ModifierType NCsModifier::IModifier
			#define WeaponModifierType NCsWeapon::NModifier::IModifier
			#define PrjWeaponModifierType NCsWeapon::NProjectile::NModifier::IModifier
			#define CopyType NCsWeapon::NModifier::NCopy::ICopy

				struct CSWP_API FImpl : public ModifierType,
										public WeaponModifierType,
										public PrjWeaponModifierType,
										public ICsGetWeaponModifierType,
										public CopyType,
										public ICsReset
				{
				public:

					static const FName Name;

				#define ApplicationType NCsModifier::NValue::NNumeric::EApplication

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

					CS_DECLARE_MEMBER_WITH_PROXY(Value, float)
					CS_DECLARE_MEMBER_WITH_PROXY(Application, ApplicationType)

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

					void Modify(ICsWeapon* Weapon);

				#pragma endregion WeaponModifierType (NCsWeapon::NModifier::IModifier)

				// PrjWeaponModifierType (NCsWeapon::NProjectile::NModifier::IModifier)
				#pragma region
				public:

					void Modify(ICsProjectileWeapon* ProjectileWeapon);

				#pragma endregion PrjWeaponModifierType (NCsWeapon::NProjectile::NModifier::IModifier)

				// ICsGetWeaponModifierType
				#pragma region
				public:

					FORCEINLINE const FECsWeaponModifier& GetWeaponModifierType() const { return NCsWeaponModifier::PrjWp_TimeBetweenShots; }

				#pragma endregion ICsGetWeaponModifierType

				// CopyType (NCsWeapon::NModifier::NCopy::ICopy)
				#pragma region
				public:

					void Copy(const WeaponModifierType* From);

				#pragma endregion CopyType (NCsWeapon::NModifier::NCopy::ICopy)

				// ICsReset
				#pragma region
				public:

					FORCEINLINE void Reset()
					{
						CS_RESET_MEMBER_WITH_PROXY(Value, 0.0)
						CS_RESET_MEMBER_WITH_PROXY(Application, ApplicationType::EApplication_MAX)
					}

				#pragma endregion ICsReset

				public:

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Application, ApplicationType)

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

				#undef ApplicationType
				};
				
			#undef ModifierType
			#undef WeaponModifierType
			#undef PrjWeaponModifierType
			#undef CopyType
			}
		}
	}
}