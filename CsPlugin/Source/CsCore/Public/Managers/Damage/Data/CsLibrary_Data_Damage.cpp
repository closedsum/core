// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"

// Data
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"

const NCsDamage::NRange::IRange* FCsLibrary_Data_Damage::GetRangeChecked(const FString& Context, const ICsData_Damage* Data)
{
	// ICsData_DamageShape
	if (const ICsData_DamageShape* Shape = GetSafeInterfaceChecked<ICsData_DamageShape>(Context, Data))
	{
		return Shape->GetRange();
	}
	return nullptr;
}