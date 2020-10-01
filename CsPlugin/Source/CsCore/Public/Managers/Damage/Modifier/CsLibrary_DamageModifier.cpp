// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Modifier/CsLibrary_DamageModifier.h"
#include "CsCore.h"


bool FCsLibrary_DamageModifier::CopyChecked(const FString& Context, const NCsDamage::NModifier::IModifier* From, NCsDamage::NModifier::IModifier* To)
{
	return false;
}

bool FCsLibrary_DamageModifier::ModifyChecked(const FString& Context, const NCsDamage::NModifier::IModifier* Modifier, const ICsData_Damage* Data, NCsDamage::NValue::IValue* Value)
{
	return false;
}

bool FCsLibrary_DamageModifier::ModifyChecked(const FString& Context, const NCsDamage::NModifier::IModifier* Modifier, const ICsData_Damage* Data, NCsDamage::NRange::IRange* Range)
{
	return false;	 
}