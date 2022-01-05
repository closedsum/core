// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Modifier/CsModifier.h"
#include "Managers/Damage/Modifier/CsDamageModifier.h"
#include "Managers/Damage/Modifier/Value/CsDamageModifier_Value.h"
#include "Managers/Damage/Modifier/Value/Point/CsDamageModifier_ValuePoint.h"
#include "Modifier/CsProjectileModifier.h"
#include "Reset/CsReset.h"
// Types
#include "Modifier/CsTypes_Modifier.h"
// Log
#include "Utility/CsPrjLog.h"

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
				#define ModifierType NCsModifier::IModifier
				#define DmgModifierType NCsDamage::NModifier::IModifier
				#define DmgValueModifierType NCsDamage::NModifier::NValue::IValue
				#define DmgValuePointModifierType NCsDamage::NModifier::NValue::NPoint::IPoint
				#define PrjModifierType NCsProjectile::NModifier::IModifier

					struct CSPRJ_API FImpl : public ModifierType,
											 public DmgModifierType,
											 public DmgValueModifierType,
											 public DmgValuePointModifierType,
											 public PrjModifierType,
											 public ICsReset
					{
					public:

						static const FName Name;

					#define ValueType NCsDamage::NValue::IValue
					#define ApplicationType NCsModifier::NValue::NIntegral::EApplication

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

					// DmgValueModifierType (NCsDamage::NModifier::NValue::IValue)
					#pragma region
					public:

						void Modify(ValueType* Value) const;

					#pragma endregion DmgValueModifierType (NCsDamage::NModifier::NValue::IValue)

					// ICsReset
					#pragma region
					public:

						FORCEINLINE void Reset()
						{
							Val = 0.0f;
							Application = ApplicationType::EApplication_MAX;
						}

					#pragma endregion ICsReset

					public:

						void CopyTo(FImpl* To) const;

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

					#undef ValueType
					#undef ApplicationType
					};
				
				#undef ModifierType
				#undef DmgModifierType
				#undef DmgValueModifierType
				#undef DmgValuePointModifierType
				#undef PrjModifierType
				}
			}
		}
	}
}