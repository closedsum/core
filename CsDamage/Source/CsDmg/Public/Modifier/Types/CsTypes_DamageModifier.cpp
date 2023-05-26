// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/Types/CsTypes_DamageModifier.h"

// DamageModifier
#pragma region

namespace NCsDamageModifier
{
	CSDMG_API CS_CREATE_ENUM_STRUCT_CUSTOM(ValuePoint, "Value Point");
	CSDMG_API CS_CREATE_ENUM_STRUCT_CUSTOM(ValueRange_Uniform, "Value Range: Uniform");
	CSDMG_API CS_CREATE_ENUM_STRUCT_CUSTOM(ValueRange_Range, "Value Range: Range");
	CSDMG_API CS_CREATE_ENUM_STRUCT_CUSTOM(Range_Uniform, "Range: Uniform");
	CSDMG_API CS_CREATE_ENUM_STRUCT_CUSTOM(Range_Range, "Range: Range");
	// Critical
	CSDMG_API CS_CREATE_ENUM_STRUCT_CUSTOM(CriticalChance, "Critical Chance");
	CSDMG_API CS_CREATE_ENUM_STRUCT_CUSTOM(CriticalStrike, "Critical Strike");
}

#pragma endregion DamageModifier