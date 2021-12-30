// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_DamageModifier.generated.h"

// DamageModifier
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsDamageModifier : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsDamageModifier)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsDamageModifier)

struct CSCORE_API EMCsDamageModifier : public TCsEnumStructMap<FECsDamageModifier, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsDamageModifier, FECsDamageModifier, uint8)
};

namespace NCsDamageModifier
{
	typedef FECsDamageModifier Type;
	typedef EMCsDamageModifier EnumMapType;

	extern CSCORE_API const Type ValuePoint;
	extern CSCORE_API const Type ValueRange;
	extern CSCORE_API const Type Range;
}

#pragma endregion DamageModifier

// DamageModifierApplication
#pragma region

namespace NCsDamage
{
	namespace NModifier
	{
		enum class EApplication : uint8
		{
			Multiply,
			Add,
			Replace,
			ReplaceOnlyIfGreater,
			EApplication_MAX
		};

		struct CSCORE_API EMApplication : public TCsEnumMap<EApplication>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMApplication, EApplication)
		};

		namespace NApplication
		{
			namespace Ref
			{
				typedef EApplication Type;

				extern CSCORE_API const Type Multiply;
				extern CSCORE_API const Type Add;
				extern CSCORE_API const Type Replace;
				extern CSCORE_API const Type ReplaceOnlyIfGreater;
				extern CSCORE_API const Type EApplication_MAX;
			}

			FORCEINLINE void Modify(float& ValueToModify, const float& Modifier, const EApplication& Type)
			{
				if (Type == EApplication::Multiply)
				{
					ValueToModify *= Modifier;
				}
				else
				if (Type == EApplication::Add)
				{
					ValueToModify += Modifier;
				}
				else
				if (Type == EApplication::Replace)
				{
					ValueToModify = Modifier;
				}
				else
				if (Type == EApplication::ReplaceOnlyIfGreater)
				{
					if (Modifier > ValueToModify)
						ValueToModify = Modifier;
				}
			}
		}
	}
}

#pragma endregion DamageModifierApplication

// TODO: DamageModifierOrder

// TODO: DamageModifierPriority