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

// NumericValueCreateModifier
#pragma region

/** Describes the method to create a numeric value Modifier.
	Modifier is an object that implements the interface: NCsModifier::IModifier. */
UENUM(BlueprintType)
enum class ECsNumericValueCreateModifier : uint8
{
	/** Create the numeric value modifier from the current value on the object with
		the SAME numeric value modifier type it is associated with.
		(i.e. If a modifier changes the Health parameter on an object, then
			  Current will create a numeric value modifier associated with Health
			  and pass the Current value of Health to the modifier. ) */
	Current								UMETA(DisplayName = "Current"),
	/** Create the numeric value modifier from the current value on the object with
		the SAME numeric value modifier type it is associated with and Multiply it by
		a predefined Value.
		(i.e. If a modifier changes the Health parameter on an object, then
			  Current will create a numeric value modifier associated with Health
			  and pass the Current value of Health multiplied by a predefined Value to the modifier. ) */
	CurrentAndMultiplyBy				UMETA(DisplayName = "Current and Multiply By"),
	/** Create the numeric value modifier from the current value on the object with
		the SAME numeric value modifier type it is associated with and Add it by
		a predefined Value.
		(i.e. If a modifier changes the Health parameter on an object, then
			  Current will create a numeric value modifier associated with Health
			  and pass the Current value of Health added by a predefined Value to the modifier. ) */
	CurrentAndAddTo						UMETA(DisplayName = "Current and Add To"),
	ECsNumericValueCreateModifier_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsNumericValueCreateModifier : public TCsEnumMap<ECsNumericValueCreateModifier>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsNumericValueCreateModifier, ECsNumericValueCreateModifier)
};

namespace NCsNumericValueCreateModifier
{
	typedef ECsNumericValueCreateModifier Type;

	namespace Ref
	{
		extern CSCORE_API const Type Current;
		extern CSCORE_API const Type CurrentAndMultiplyBy;
		extern CSCORE_API const Type CurrentAndAddTo;
		extern CSCORE_API const Type ECsNumericValueCreateModifier_MAX;
	}
}

namespace NCsModifier
{
	namespace NValue
	{
		namespace NNumeric
		{
			/** Describes the method to create a numeric value Modifier.
				Modifier is an object that implements the interface: NCsModifier::IModifier. */
			enum class ECreate : uint8
			{
				/** Create the numeric value modifier from the current value on the object with
					the SAME numeric value modifier type it is associated with.
					(i.e. If a modifier changes the Health parameter on an object, then
						  Current will create a numeric value modifier associated with Health
						  and pass the Current value of Health to the modifier. ) */
				Current,
				/** Create the numeric value modifier from the current value on the object with
					the SAME numeric value modifier type it is associated with and Multiply it by
					a predefined Value.
					(i.e. If a modifier changes the Health parameter on an object, then
						  Current will create a numeric value modifier associated with Health
						  and pass the Current value of Health multiplied by a predefined Value to the modifier. ) */
				CurrentAndMultiplyBy,
				/** Create the numeric value modifier from the current value on the object with
					the SAME numeric value modifier type it is associated with and Add it by
					a predefined Value.
					(i.e. If a modifier changes the Health parameter on an object, then
						  Current will create a numeric value modifier associated with Health
						  and pass the Current value of Health added by a predefined Value to the modifier. ) */
				CurrentAndAddTo,
				ECreate_MAX
			};

			struct CSCORE_API EMCreate : public TCsEnumMap<ECreate>
			{
				CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCreate, ECreate)
			};

			namespace NCreate
			{
				namespace Ref
				{
					typedef ECreate Type;

					extern CSCORE_API const Type Current;
					extern CSCORE_API const Type CurrentAndMultiplyBy;
					extern CSCORE_API const Type CurrentAndAddTo;
					extern CSCORE_API const Type ECreate_MAX;
				}
			}
		}
	}
}

#pragma endregion NumericValueCreateModifier