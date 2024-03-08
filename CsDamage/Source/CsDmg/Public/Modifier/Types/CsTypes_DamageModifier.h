// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_DamageModifier.generated.h"

// DamageModifier
#pragma region

USTRUCT(BlueprintType)
struct CSDMG_API FECsDamageModifier : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsDamageModifier)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsDamageModifier)

struct CSDMG_API EMCsDamageModifier : public TCsEnumStructMap<FECsDamageModifier, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsDamageModifier, FECsDamageModifier, uint8)
};

namespace NCsDamageModifier
{
	typedef FECsDamageModifier Type;
	typedef EMCsDamageModifier EnumMapType;

	extern CSDMG_API const Type ValuePoint;
	extern CSDMG_API const Type ValueRange_Uniform;
	extern CSDMG_API const Type ValueRange_Range;
	extern CSDMG_API const Type Range_Uniform;
	extern CSDMG_API const Type Range_Range;
	// Critical
	extern CSDMG_API const Type CriticalChance;
	extern CSDMG_API const Type CriticalStrike;
}

#pragma endregion DamageModifier

// DamageModifierImpl
#pragma region

namespace NCsDamage
{
	namespace NModifier
	{
		enum class EImpl : uint8
		{
			Int,
			Float,
			Toggle,
			EImpl_MAX
		};
	}
}

#pragma endregion DamageModifierImpl

// TODO: DamageModifierOrder

// TODO: DamageModifierPriority