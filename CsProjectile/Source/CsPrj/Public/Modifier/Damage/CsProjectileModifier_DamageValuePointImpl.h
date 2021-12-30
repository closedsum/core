// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Managers/Damage/Modifier/CsDamageModifier.h"
#include "Managers/Damage/Modifier/Value/CsDamageModifier_Value.h"
#include "Managers/Damage/Modifier/Value/Point/CsDamageModifier_ValuePoint.h"
#include "Modifier/CsProjectileModifier.h"
// Types
#include "Managers/Damage/Modifier/CsTypes_DamageModifier.h"

class ICsProjectile;

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NDamage
		{
			namespace NValue
			{
				namespace NPoint
				{
				#define DmgModifierType NCsDamage::NModifier::IModifier
				#define DmgValueModifierType NCsDamage::NModifier::NValue::IValue
				#define DmgValuePointModifierType NCsDamage::NModifier::NValue::NPoint::IPoint
				#define PrjModifierType NCsProjectile::NModifier::IModifier

					struct CSPRJ_API FImpl : public DmgModifierType,
											 public DmgValueModifierType,
											 public DmgValuePointModifierType,
											 public PrjModifierType
					{
					public:

						static const FName Name;

					#define ValueType NCsDamage::NValue::IValue
					#define ApplicationType NCsDamage::NModifier::EApplication
					private:

						// ICsGetInterfaceMap

						FCsInterfaceMap* InterfaceMap;

					public:

						float Val;

						ApplicationType Application;

					public:
						
						FImpl();
						~FImpl();

						FORCEINLINE UObject* _getUObject() const { return nullptr; }

					// ICsGetInterfaceMap
					#pragma region
					public:

						FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

					#pragma endregion ICsGetInterfaceMap

					// PrjModifierType
					#pragma region
					public:

						void Modify(ICsProjectile* Projectile){}

					#pragma endregion PrjModifierType

					// IValue (NCsDamage::NModifier::NValue::IValue)
					#pragma region
					public:

						void Modify(ValueType* Value);

					#pragma endregion IValue (NCsDamage::NModifier::NValue::IValue)

					public:

						void CopyTo(FImpl* To) const;

					#undef ValueType
					#undef ApplicationType
					};

				#undef DmgModifierType
				#undef DmgValueModifierType
				#undef DmgValuePointModifierType
				#undef PrjModifierType
				}
			}
		}
	}
}