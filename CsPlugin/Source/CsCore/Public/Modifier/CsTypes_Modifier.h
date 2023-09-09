// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_Modifier.generated.h"

// NumericValueModifierApplication
#pragma region

/**
* Describes how a Numeric type Modifier is applied to a value.
*  Modifier is an object that implements the interface: NCsModifier::IModifier.
*/
UENUM(BlueprintType)
enum class ECsNumericValueModifierApplication : uint8
{
	/** Multiply the modifier by the current value being modified. */
	Multiply								UMETA(DisplayName = "Multiply"),
	/** Add to the modifier to the current value being modified. */
	Add										UMETA(DisplayName = "Add"),
	/** Replace the current value being modified with the modifier. */
	Replace									UMETA(DisplayName = "Replace"),
	/** Replace the current value being modified ONLY IF the modifier 
	    is GREATER THAN the current value. */
	ReplaceOnlyIfGreater					UMETA(DisplayName = "Replace Only If Greater"),
	/** All Percent Add First values are added first (i.e. 0.1 + 0.05 + 0.05 + ... etc = 0.2),
		then the result is added to 1.0f and multiplied by the current value being modified. 
		NOTE: Currently Percent Add First values are applied BEFORE any other modifiers have
			  been applied. */
	PercentAddFirst							UMETA(DisplayName = "Percent Add First"),
	/** All Percent Add Last values are added first (i.e. 0.1 + 0.05 + 0.05 + ... etc = 0.2),
		then the result is added to 1.0f and multiplied by the current value being modified.
		NOTE: Currently Percent Add Last values are applied LAST, AFTER all other modifiers have
			  been applied. */
	PercentAddLast							UMETA(DisplayName = "Percent Add Last"),
	/** All Percent Subtract First values are added first (i.e. 0.1 + 0.05 + 0.05 + ... etc = 0.2),
		then the result is subtracted from 1.0f (clamped to 0.0f) and multiplied by the current value being modified. 
		NOTE: Currently Percent Subtract First values are applied BEFORE any other modifiers have
			  been applied. */
	PercentSubtractFirst					UMETA(DisplayName = "Percent Subtract First"),
	/** All Percent Subtract Last values are added first (i.e. 0.1 + 0.05 + 0.05 + ... etc = 0.2),
		then the result is subtracted from 1.0f (clamped to 0.0f) and multiplied by the current value being modified.
		NOTE: Currently Percent Subtract Last values are applied LAST, AFTER all other modifiers have
			  been applied. */
	PercentSubtractLast						UMETA(DisplayName = "Percent Subtract Last"),
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
		extern CSCORE_API const Type PercentAddFirst;
		extern CSCORE_API const Type PercentAddLast;
		extern CSCORE_API const Type PercentSubtractFirst;
		extern CSCORE_API const Type PercentSubtractLast;
		extern CSCORE_API const Type ECsNumericValueModifierApplication_MAX;
	}
}

namespace NCsModifier
{
	namespace NValue
	{
		namespace NNumeric
		{
			/**
			* Describes how a Numeric type Modifier is applied to a value.
			*  Modifier is an object that implements the interface: NCsModifier::IModifier.
			*/
			enum class EApplication : uint8
			{
				/** Multiply the modifier by the current value being modified. */
				Multiply,
				/** Add to the modifier to the current value being modified. */
				Add,
				/** Replace the current value being modified with the modifier. */
				Replace,
				/** Replace the current value being modified ONLY IF the modifier
					is GREATER THAN the current value. */
				ReplaceOnlyIfGreater,
				/** All Percent Add First values are added first (i.e. 0.1 + 0.05 + 0.05 + ... etc = 0.2),
					then the result is added to 1.0f and multiplied by the current value being modified.
					NOTE: Currently Percent Add First values are applied BEFORE any other modifiers have
						  been applied. */
				PercentAddFirst,
				/** All Percent Add Last values are added first (i.e. 0.1 + 0.05 + 0.05 + ... etc = 0.2),
					then the result is added to 1.0f and multiplied by the current value being modified.
					NOTE: Currently Percent Add Last values are applied LAST, AFTER all other modifiers have
						  been applied. */
				PercentAddLast,
				/** All Percent Subtract First values are added first (i.e. 0.1 + 0.05 + 0.05 + ... etc = 0.2),
					then the result is subtracted from 1.0f (clamped to 0.0f) and multiplied by the current value being modified. 
					NOTE: Currently Percent Subtract First values are applied BEFORE any other modifiers have
						  been applied. */
				PercentSubtractFirst,
				/** All Percent Subtract Last values are added first (i.e. 0.1 + 0.05 + 0.05 + ... etc = 0.2),
					then the result is subtracted from 1.0f (clamped to 0.0f) and multiplied by the current value being modified.
					NOTE: Currently Percent Subtract Last values are applied LAST, AFTER all other modifiers have
						  been applied. */
				PercentSubtractLast,
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
					extern CSCORE_API const Type PercentAddFirst;
					extern CSCORE_API const Type PercentAddLast;
					extern CSCORE_API const Type PercentSubtractFirst;
					extern CSCORE_API const Type PercentSubtractLast;
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
					else
					if (Type == EApplication::PercentAddFirst)
					{
						return InValue + Modifier;
					}
					else
					if (Type == EApplication::PercentAddLast)
					{
						return InValue + Modifier;
					}
					else
					if (Type == EApplication::PercentSubtractFirst)
					{
						return InValue - Modifier;
					}
					else
					if (Type == EApplication::PercentSubtractLast)
					{
						return InValue - Modifier;
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

				FORCEINLINE int32 GetNewValue(const ECreate& Type, const int32& Current, const int32& Value)
				{
					if (Type == ECreate::Current)
						return Current;
					if (Type == ECreate::CurrentAndMultiplyBy)
						return Current * Value;
					if (Type == ECreate::CurrentAndAddTo)
						return Current + Value;
					checkf(0, TEXT("NCsModifier::NValue::NNumeric::NCreate:GetNewValue: Type: %s is NOT Valid."), EMCreate::Get().ToChar(Type));
					return Current;
				}

				FORCEINLINE float GetNewValue(const ECreate& Type, const float& Current, const float& Value)
				{
					if (Type == ECreate::Current)
						return Current;
					if (Type == ECreate::CurrentAndMultiplyBy)
						return Current * Value;
					if (Type == ECreate::CurrentAndAddTo)
						return Current + Value;
					checkf(0, TEXT("NCsModifier::NValue::NNumeric::NCreate:GetNewValue: Type: %s is NOT Valid."), EMCreate::Get().ToChar(Type));
					return Current;
				}
			}
		}
	}
}

#pragma endregion NumericValueCreateModifier