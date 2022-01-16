// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Modifier/CsModifier.h"
#include "Managers/Damage/Modifier/CsDamageModifier.h"
#include "Managers/Damage/Modifier/Value/CsDamageModifier_Value.h"
#include "Managers/Damage/Modifier/Value/Range/CsDamageModifier_ValueRange.h"
#include "Managers/Damage/Modifier/Types/CsGetDamageModifierType.h"
#include "Reset/CsReset.h"
// Types
#include "Modifier/CsTypes_Modifier.h"

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NValue
		{
			namespace NRange
			{
			#define ModifierType NCsModifier::IModifier
			#define DmgModifierType NCsDamage::NModifier::IModifier
			#define DmgValueModifierType NCsDamage::NModifier::NValue::IValue
			#define DmgValueRangeModifierType NCsDamage::NModifier::NValue::NRange::IRange

				/**
				* 
				*/
				struct CSCORE_API FImpl : public ModifierType,
										  public DmgModifierType,
										  public DmgValueModifierType,
										  public DmgValueRangeModifierType,
										  public ICsGetDamageModifierType,
										  public ICsReset
				{
				public:

					static const FName Name;

				#define ValueType NCsDamage::NValue::IValue
				#define ApplicationType NCsModifier::NValue::NIntegral::EApplication

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

					// DmgModifierType (NCsDamage::NModifier::IModifier)
				
					// DmgValueModifierType (NCsDamage::NModifier::NValue::IValue)

					// DmgValueRangeModifierType (NCsDamage::NModifier::NValue::NRange::IRange)

					ApplicationType ApplicationMin;

					float MinValue;

					ApplicationType ApplicationMax;

					float MaxValue;

				public:

					FImpl();
					~FImpl();

					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

				// DmgValueModifierType (NCsDamage::NModifier::NValue::IValue)
				#pragma region
				public:

					void Modify(ValueType* Value) const;

				#pragma endregion DmgValueModifierType (NCsDamage::NModifier::NValue::IValue)

				// ICsGetDamageModifierType
				#pragma region
				public:

					FORCEINLINE const FECsDamageModifier& GetDamageModifierType() const { return NCsDamageModifier::ValueRange; }

				#pragma endregion ICsGetDamageModifierType

				// ICsReset
				#pragma region
				public:

					FORCEINLINE void Reset()
					{
						ApplicationMin = ApplicationType::EApplication_MAX;
						MinValue = 0.0f;
						ApplicationMax = ApplicationType::EApplication_MAX;
						MaxValue = 0.0f;
					}

				#pragma endregion ICsReset

				#undef ValueType
				#undef ApplicationType
				};

			#undef ModifierType
			#undef DmgModifierType
			#undef DmgValueModifierType
			#undef DmgValueRangeModifierType
			}
		}
	}
}