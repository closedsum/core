// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Modifier/Value/Point/CsDamageModifier_ValuePointImpl.h"
#include "CsCore.h"

// Library
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
// Containers
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Managers/Damage/Value/Point/CsDamageValuePoint.h"

const FName NCsDamage::NModifier::NValue::NPoint::FImpl::Name = FName("NCsDamage::NModifier::NValue::NPoint::FImpl");

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NValue
		{
			namespace NPoint
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NModifier::NValue::NPoint::FImpl, Modify);
					}
				}

				FImpl::FImpl() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					Application(NCsDamage::NModifier::EApplication::Multiply)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FImpl>(this);

					typedef NCsModifier::IModifier ModifierType;
					typedef NCsDamage::NModifier::IModifier DmgModifierType;
					typedef NCsDamage::NModifier::NValue::IValue DmgModifierValueType;
					typedef NCsDamage::NModifier::NValue::NPoint::IPoint DmgModifierValuePointType;

					InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
					InterfaceMap->Add<DmgModifierType>(static_cast<DmgModifierType*>(this));
					InterfaceMap->Add<DmgModifierValueType>(static_cast<DmgModifierValueType*>(this));
					InterfaceMap->Add<DmgModifierValuePointType>(static_cast<DmgModifierValuePointType*>(this));
				}
				
				FImpl::~FImpl()
				{
					// ICsGetInterfaceMap
					delete InterfaceMap;
				}

				// DmgModifierValueType (NCsDamage::NModifier::NValue::IValue)
				#pragma region

				#define ValueType NCsDamage::NValue::IValue
				void FImpl::Modify(ValueType* Value) const
				{
					using namespace NCsDamage::NModifier::NValue::NPoint::NCached;

					const FString& Context = Str::Modify;

					// TODO: Perform Check

					typedef NCsDamage::NValue::FLibrary ValueLibrary;
					typedef NCsDamage::NValue::NPoint::IPoint ValuePointType;

					ValuePointType* ValuePoint = ValueLibrary::GetInterfaceChecked<ValuePointType>(Context, Value);

					const float& ValRef = ValuePoint->GetValue();
					float* ValPtr	    = const_cast<float*>((const float*)(&ValRef));

					NCsDamage::NModifier::NApplication::Modify(*ValPtr, Val, Application);
				}
				#undef ValueType

				#pragma endregion DmgModifierValueType (NCsDamage::NModifier::NValue::IValue)
			}
		}
	}
}