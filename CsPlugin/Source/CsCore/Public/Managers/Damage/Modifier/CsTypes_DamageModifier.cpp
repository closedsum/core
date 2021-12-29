// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Modifier/CsTypes_DamageModifier.h"

// DamageModifier
#pragma region

namespace NCsDamageModifier
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(ValuePoint, "NCsDamage::NModifier::NValue::NPoint::IPoint");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(ValueRange, "NCsDamage::NModifier::NValue::NRange::IRange");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(Range, "NCsDamage::NModifier::NRange::IRange");
}

#pragma endregion DamageModifier

// DamageModifierApplication
#pragma region

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NApplication
		{
			namespace Ref
			{
				typedef EMApplication EnumMapType;

				CSCORE_API CS_ADD_TO_ENUM_MAP(Multiply);
				CSCORE_API CS_ADD_TO_ENUM_MAP(Add);
				CSCORE_API CS_ADD_TO_ENUM_MAP(Replace);
				CSCORE_API CS_ADD_TO_ENUM_MAP(ReplaceOnlyIfGreater);
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EApplication_MAX, "MAX");
			}
		}
	}
}

#pragma endregion DamageModifierApplication