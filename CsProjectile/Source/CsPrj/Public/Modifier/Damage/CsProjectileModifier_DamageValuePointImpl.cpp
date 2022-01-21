// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/Damage/CsProjectileModifier_DamageValuePointImpl.h"

// Library
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
#include "Modifier/CsLibrary_ProjectileModifier.h"
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
					namespace NImpl
					{
						namespace NCached
						{
							namespace Str
							{
								CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NModifier::NDamage::NValue::NPoint::FImpl, Modify);
								CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NModifier::NDamage::NValue::NPoint::FImpl, Copy);
							}
						}
					}

					FImpl::FImpl() :
						// ICsGetInterfaceMap
						InterfaceMap(nullptr),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0.0f),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Application, NCsModifier::NValue::NIntegral::EApplication::Multiply)
					{
						InterfaceMap = new FCsInterfaceMap();

						InterfaceMap->SetRoot<FImpl>(this);

						typedef NCsModifier::IModifier ModifierType;
						typedef NCsDamage::NModifier::IModifier DmgModifierType;
						typedef NCsDamage::NModifier::NValue::IValue DmgModifierValueType;
						typedef NCsDamage::NModifier::NValue::NPoint::IPoint DmgModifierValuePointType;
						typedef NCsProjectile::NModifier::IModifier PrjModifierType;
						typedef NCsProjectile::NModifier::NCopy::ICopy CopyType;

						InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
						InterfaceMap->Add<DmgModifierType>(static_cast<DmgModifierType*>(this));
						InterfaceMap->Add<DmgModifierValueType>(static_cast<DmgModifierValueType*>(this));
						InterfaceMap->Add<DmgModifierValuePointType>(static_cast<DmgModifierValuePointType*>(this));
						InterfaceMap->Add<PrjModifierType>(static_cast<PrjModifierType*>(this));
						InterfaceMap->Add<ICsGetProjectileModifierType>(static_cast<ICsGetProjectileModifierType*>(this));
						InterfaceMap->Add<ICsIsValid>(static_cast<ICsIsValid*>(this));
						InterfaceMap->Add<CopyType>(static_cast<CopyType*>(this));
						InterfaceMap->Add<ICsReset>(static_cast<ICsReset*>(this));

						CS_CTOR_SET_MEMBER_PROXY(Value);
						CS_CTOR_SET_MEMBER_PROXY(Application);
					}
				
					FImpl::~FImpl()
					{
						// ICsGetInterfaceMap
						delete InterfaceMap;
					}

					// DmgModifierValueType (NCsDamage::NModifier::NValue::IValue)
					#pragma region

					#define ValueType NCsDamage::NValue::IValue
					void FImpl::Modify(ValueType* InValue) const
					{
						using namespace NCsProjectile::NModifier::NDamage::NValue::NPoint::NImpl::NCached;

						const FString& Context = Str::Modify;

						// TODO: Perform Check

						typedef NCsDamage::NValue::FLibrary ValueLibrary;
						typedef NCsDamage::NValue::NPoint::IPoint ValuePointType;

						ValuePointType* ValuePoint = ValueLibrary::GetInterfaceChecked<ValuePointType>(Context, InValue);

						const float& ValRef = ValuePoint->GetValue();
						float* ValPtr	    = const_cast<float*>((const float*)(&ValRef));

						NCsModifier::NValue::NIntegral::NApplication::Modify(*ValPtr, GetValue(), GetApplication());
					}
					#undef ValueType

					#pragma endregion DmgModifierValueType (NCsDamage::NModifier::NValue::IValue)

					// ICsIsValid
					#pragma region

					bool FImpl::IsValidChecked(const FString& Context) const
					{
						CS_IS_FLOAT_GREATER_THAN_CHECKED(GetValue(), 0.0f)

						typedef NCsModifier::NValue::NIntegral::EMApplication ApplicationMapType;

						CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetApplication())
						return true;
					}

					bool FImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
					{
						CS_IS_FLOAT_GREATER_THAN(GetValue(), 0.0f)

						typedef NCsModifier::NValue::NIntegral::EMApplication ApplicationMapType;
						typedef NCsModifier::NValue::NIntegral::EApplication ApplicationType;

						CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetApplication())
						return true;
					}

					#pragma endregion ICsIsValid

					// CopyType (NCsProjectile::NModifier::NCopy::ICopy)
					#pragma region

					#define PrjModifierType NCsProjectile::NModifier::IModifier
					void FImpl::Copy(const PrjModifierType* From)
					{
					#undef PrjModifierType
						
						using namespace NCsProjectile::NModifier::NDamage::NValue::NPoint::NImpl::NCached;

						const FString& Context = Str::Copy;
						
						typedef NCsProjectile::NModifier::FLibrary PrjModifierLibrary;

						const FImpl* FromImpl = PrjModifierLibrary::PureStaticCastChecked<FImpl>(Context, From);

						SetValue(FromImpl->GetValue());
						SetApplication(FromImpl->GetApplication());
					}

					#pragma endregion CopyType (NCsProjectile::NModifier::NCopy::ICopy)
				}
			}
		}
	}
}