// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Modifier/CsModifier.h"
#include "Managers/Damage/Modifier/CsDamageModifier.h"
#include "Managers/Damage/Modifier/Value/CsDamageModifier_Value.h"
#include "Managers/Damage/Modifier/Value/Point/CsDamageModifier_ValuePoint.h"
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
			namespace NPoint
			{
			#define ModifierType NCsModifier::IModifier
			#define DmgModifierType NCsDamage::NModifier::IModifier
			#define DmgValueModifierType NCsDamage::NModifier::NValue::IValue
			#define DmgValuePointModifierType NCsDamage::NModifier::NValue::NPoint::IPoint

				/**
				* 
				*/
				struct CSCORE_API FImpl : public ModifierType,
										  public DmgModifierType,
										  public DmgValueModifierType,
										  public DmgValuePointModifierType
				{
				public:

					static const FName Name;

				#define ValueType NCsDamage::NValue::IValue
				#define ApplicationType NCsModifier::NValue::NIntegral::EApplication

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

					// DmgModifierType (NCsDamage::NModifier::IModifier)
				
					// DmgValuePointModifierType (NCsDamage::NModifier::NValue::IValue)

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

				// DmgValuePointModifierType (NCsDamage::NModifier::NValue::IValue)
				#pragma region
				public:

					void Modify(ValueType* Value) const;

				#pragma endregion DmgValuePointModifierType (NCsDamage::NModifier::NValue::IValue)

				#undef ValueType
				#undef ApplicationType
				};

			#undef ModifierType
			#undef DmgModifierType
			#undef DmgValueModifierType
			#undef DmgValuePointModifierType
			}
		}
	}
}