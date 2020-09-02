// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Modifier/CsLibrary_DamageModifier.h"
#include "CsCore.h"


bool FCsLibrary_DamageModifier::CopyChecked(const FString& Context, const ICsDamageModifier* From, ICsDamageModifier* To)
{
	return false;
}

bool FCsLibrary_DamageModifier::ModifyChecked(const FString& Context, const ICsDamageModifier* Modifier, const ICsData_Damage* Data, ICsDamageValue* Value)
{
	return false;
}

bool FCsLibrary_DamageModifier::ModifyChecked(const FString& Context, const ICsDamageModifier* Modifier, const ICsData_Damage* Data, ICsDamageRange* Range)
{
	return false;	 
}