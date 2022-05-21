// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_Modifier.generated.h"

// NumericValueModifierApplication
#pragma region

UENUM(BlueprintType)
enum class ECsNumericValueModifierApplication : uint8
{
	Multiply								UMETA(DisplayName = "Multiply"),
	Add										UMETA(DisplayName = "Add"),
	Replace									UMETA(DisplayName = "Replace"),
	ReplaceOnlyIfGreater					UMETA(DisplayName = "Replace Only If Greater"),
	ECsNumericValueModifierApplication_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsNumericValueModifierApplication : public TCsEnumMap<ECsNumericValueModifierApplication>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsNumericValueModifierApplication, ECsNumericValueModifierApplication)
};

namespace NCsNumericValueModifierApplication
{
	typedef ECsNumericValueModifierApplication Type;

	namespace Ref
	{
		extern CSCORE_API const Type Multiply;
		extern CSCORE_API const Type Add;
		extern CSCORE_API const Type Replace;
		extern CSCORE_API const Type ReplaceOnlyIfGreater;
		extern CSCORE_API const Type ECsNumericValueModifierApplication_MAX;
	}
}

namespace NCsModifier
{
	namespace NValue
	{
		namespace NNumeric
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

				FORCEINLINE float Modify(const float& InValue, const float& Modifier, const EApplication& Type)
				{
					if (Type == EApplication::Multiply)
					{
						return InValue * Modifier;
					}
					else
					if (Type == EApplication::Add)
					{
						return InValue + Modifier;
					}
					else
					if (Type == EApplication::Replace)
					{
						return Modifier;
					}
					else
					if (Type == EApplication::ReplaceOnlyIfGreater)
					{
						if (Modifier > InValue)
							return Modifier;
					}
					return InValue;
				}

				FORCEINLINE int32 Modify(const int32& InValue, const int32& Modifier, const EApplication& Type)
				{
					if (Type == EApplication::Multiply)
					{
						return InValue * Modifier;
					}
					else
					if (Type == EApplication::Add)
					{
						return InValue + Modifier;
					}
					else
					if (Type == EApplication::Replace)
					{
						return Modifier;
					}
					else
					if (Type == EApplication::ReplaceOnlyIfGreater)
					{
						if (Modifier > InValue)
							return Modifier;
					}
					return InValue;
				}
			}
		}
	}
}

#pragma endregion NumericValueModifierApplication