// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Managers/Damage/Modifier/CsDamageModifier.h"
#include "Managers/Damage/Modifier/Value/CsDamageModifier_Value.h"
#include "Managers/Damage/Modifier/Value/Range/CsDamageModifier_ValueRange.h"
// Types
#include "Managers/Damage/Modifier/CsTypes_DamageModifier.h"

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
				/**
				* 
				*/
				struct CSCORE_API FImpl : public IModifier,
										  public IValue,
										  public IRange
				{
				public:

					static const FName Name;

				#define ValueType NCsDamage::NValue::IValue
				#define ApplicationType NCsDamage::NModifier::EApplication

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

					// IModifier (NCsDamage::NModifier::IModifier)
				
					// IValue (NCsDamage::NModifier::NValue::IValue)

					// IRange (NCsDamage::NModifier::NValue::NRange::IRange)

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

				// IValue (NCsDamage::NModifier::NValue::IValue)
				#pragma region
				public:

					void Modify(ValueType* Value) const;

				#pragma endregion IValue (NCsDamage::NModifier::NValue::IValue)

				#undef ValueType
				#undef ApplicationType
				};
			}
		}
	}
}