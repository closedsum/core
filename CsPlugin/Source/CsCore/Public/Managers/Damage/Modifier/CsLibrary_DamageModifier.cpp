// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Modifier/CsLibrary_DamageModifier.h"
#include "CsCore.h"

#define ModifierType NCsDamage::NModifier::IModifier
bool FCsLibrary_DamageModifier::CopyChecked(const FString& Context, const ModifierType* From, ModifierType* To)
{
#undef ModifierType
	return false;
}

#define ModifierType NCsDamage::NModifier::IModifier
#define ValueType NCsDamage::NValue::IValue
bool FCsLibrary_DamageModifier::ModifyChecked(const FString& Context, const ModifierType* Modifier, const ICsData_Damage* Data, ValueType* Value)
{
#undef ModifierType
#undef ValueType
	return false;
}

#define ModifierType NCsDamage::NModifier::IModifier
#define RangeType NCsDamage::NRange::IRange
bool FCsLibrary_DamageModifier::ModifyChecked(const FString& Context, const ModifierType* Modifier, const ICsData_Damage* Data, RangeType* Range)
{
#undef ModifierType
#undef RangeType
	return false;	 
}