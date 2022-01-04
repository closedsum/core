// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/Damage/CsProjectileModifier_DamageValuePointImpl.h"

// Library
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Managers/Damage/Value/Point/CsDamageValuePoint.h"

const FName NCsProjectile::NModifier::NDamage::NValue::NPoint::FImpl::Name = FName("NCsProjectile::NModifier::NDamage::NValue::NPoint::FImpl");

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
					namespace NCached
					{
						namespace Str
						{
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NModifier::NDamage::NValue::NPoint::FImpl, Modify);
						}
					}

					FImpl::FImpl() :
						// ICsGetInterfaceMap
						InterfaceMap(nullptr),
						Val(0.0f),
						Application(NCsDamage::NModifier::EApplication::Multiply)
					{
						InterfaceMap = new FCsInterfaceMap();

						InterfaceMap->SetRoot<FImpl>(this);

						typedef NCsModifier::IModifier ModifierType;
						typedef NCsDamage::NModifier::IModifier DmgModifierType;
						typedef NCsDamage::NModifier::NValue::IValue DmgModifierValueType;
						typedef NCsDamage::NModifier::NValue::NPoint::IPoint DmgModifierValuePointType;
						typedef NCsProjectile::NModifier::IModifier PrjModifierType;

						InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
						InterfaceMap->Add<DmgModifierType>(static_cast<DmgModifierType*>(this));
						InterfaceMap->Add<DmgModifierValueType>(static_cast<DmgModifierValueType*>(this));
						InterfaceMap->Add<DmgModifierValuePointType>(static_cast<DmgModifierValuePointType*>(this));
						InterfaceMap->Add<PrjModifierType>(static_cast<PrjModifierType*>(this));
						InterfaceMap->Add<ICsReset>(static_cast<ICsReset*>(this));
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
						using namespace NCsProjectile::NModifier::NDamage::NValue::NPoint::NCached;

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

					void FImpl::CopyTo(FImpl* To) const
					{
						To->Val = Val;
						To->Application = Application;
					}

					bool FImpl::IsValidChecked(const FString& Context) const
					{
						CS_IS_FLOAT_GREATER_THAN_CHECKED(Val, 0.0f)

						typedef NCsDamage::NModifier::EMApplication ApplicationMapType;

						CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, Application)
						return true;
					}

					bool FImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
					{
						CS_IS_FLOAT_GREATER_THAN(Val, 0.0f)

						typedef NCsDamage::NModifier::EMApplication ApplicationMapType;
						typedef NCsDamage::NModifier::EApplication ApplicationType;

						CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, Application)
						return true;
					}
				}
			}
		}
	}
}