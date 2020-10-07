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
#define DataType NCsDamage::NData::IData
#define ValueType NCsDamage::NValue::IValue
bool FCsLibrary_DamageModifier::ModifyChecked(const FString& Context, const ModifierType* Modifier, const DataType* Data, ValueType* Value)
{
#undef ModifierType
#undef DataType
#undef ValueType
	return false;
}

#define ModifierType NCsDamage::NModifier::IModifier
#define DataType NCsDamage::NData::IData
#define RangeType NCsDamage::NRange::IRange
bool FCsLibrary_DamageModifier::ModifyChecked(const FString& Context, const ModifierType* Modifier, const DataType* Data, RangeType* Range)
{
#undef ModifierType
#undef DataType
#undef RangeType
	return false;	 
}