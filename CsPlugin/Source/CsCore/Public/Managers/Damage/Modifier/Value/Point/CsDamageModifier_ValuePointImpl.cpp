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

					typedef NCsDamage::NModifier::IModifier ModifierType;
					typedef NCsDamage::NModifier::NValue::IValue ModifierValueType;
					typedef NCsDamage::NModifier::NValue::NPoint::IPoint ModifierValuePointType;

					InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
					InterfaceMap->Add<ModifierValueType>(static_cast<ModifierValueType*>(this));
					InterfaceMap->Add<ModifierValuePointType>(static_cast<ModifierValuePointType*>(this));
				}
				
				FImpl::~FImpl()
				{
					// ICsGetInterfaceMap
					delete InterfaceMap;
				}

				// IValue (NCsDamage::NModifier::NValue::IValue)
				#pragma region

				#define ValueType NCsDamage::NValue::IValue
				void FImpl::Modify(ValueType* Value)
				{
					using namespace NCsDamage::NModifier::NValue::NPoint::NCached;

					const FString& Context = Str::Modify;

					// TODO: Perform Check

					typedef NCsDamage::NValue::FLibrary ValueLibrary;
					typedef NCsDamage::NValue::NPoint::IPoint ValuePointType;

					ValuePointType* ValuePoint = ValueLibrary::GetInterfaceChecked<ValuePointType>(Context, Value);

					const float& ValRef = ValuePoint->GetValue();
					float* ValPtr	    = const_cast<float*>((const float*)(&ValRef));

					typedef NCsDamage::NModifier::EApplication ApplicationType;

					if (Application == ApplicationType::Multiply)
					{
						*ValPtr *= Val;
					}
					else
					if (Application == ApplicationType::Add)
					{
						*ValPtr += Val;
					}
					else
					if (Application == ApplicationType::Replace)
					{
						*ValPtr = Val;
					}
					else
					if (Application == ApplicationType::ReplaceOnlyIfGreater)
					{
						if (Val > *ValPtr)
							*ValPtr = Val;
					}
						
				}
				#undef ValueType

				#pragma endregion IValue (NCsDamage::NModifier::NValue::IValue)
			}
		}
	}
}