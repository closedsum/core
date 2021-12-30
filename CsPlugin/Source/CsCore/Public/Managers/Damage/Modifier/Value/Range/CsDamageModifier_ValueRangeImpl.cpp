// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Modifier/Value/Range/CsDamageModifier_ValueRangeImpl.h"
#include "CsCore.h"

// Library
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
// Containers
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Managers/Damage/Value/Range/CsDamageValueRange.h"

const FName NCsDamage::NModifier::NValue::NRange::FImpl::Name = FName("NCsDamage::NModifier::NValue::NRange::FImpl");

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NValue
		{
			namespace NRange
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NModifier::NValue::NRange::FImpl, Modify);
					}
				}

				FImpl::FImpl() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					ApplicationMin(NCsDamage::NModifier::EApplication::Multiply),
					MinValue(0.0f),
					ApplicationMax(NCsDamage::NModifier::EApplication::Multiply),
					MaxValue(0.0f)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FImpl>(this);

					typedef NCsDamage::NModifier::IModifier ModifierType;
					typedef NCsDamage::NModifier::NValue::IValue ModifierValueType;
					typedef NCsDamage::NModifier::NValue::NRange::IRange ModifierRangeType;

					InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
					InterfaceMap->Add<ModifierValueType>(static_cast<ModifierValueType*>(this));
					InterfaceMap->Add<ModifierRangeType>(static_cast<ModifierRangeType*>(this));
				}
				
				FImpl::~FImpl()
				{
					// ICsGetInterfaceMap
					delete InterfaceMap;
				}

				// IValue (NCsDamage::NModifier::NValue::IValue)
				#pragma region

				#define ValueType NCsDamage::NValue::IValue
				void FImpl::Modify(ValueType* Value) const
				{
					using namespace NCsDamage::NModifier::NValue::NRange::NCached;

					const FString& Context = Str::Modify;

					// TODO: Perform Check

					typedef NCsDamage::NValue::FLibrary ValueLibrary;
					typedef NCsDamage::NValue::NRange::IRange ValueRangeType;

					ValueRangeType* ValueRange = ValueLibrary::GetInterfaceChecked<ValueRangeType>(Context, Value);

					// Min
					const float& MinValueRef = ValueRange->GetMinValue();
					float* MinValuePtr	    = const_cast<float*>((const float*)(&MinValueRef));

					NCsDamage::NModifier::NApplication::Modify(*MinValuePtr, MinValue, ApplicationMin);

					// Max
					const float& MaxValueRef = ValueRange->GetMinValue();
					float* MaxValuePtr	    = const_cast<float*>((const float*)(&MaxValueRef));

					NCsDamage::NModifier::NApplication::Modify(*MaxValuePtr, MaxValue, ApplicationMax);
				}
				#undef ValueType

				#pragma endregion IValue (NCsDamage::NModifier::NValue::IValue)
			}
		}
	}
}