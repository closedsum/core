// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsLibrary_DamageModifier.h"
#include "CsDmg.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Damage
#include "Modifier/Value/CsDamageModifier_Value.h"
#include "Modifier/Value/Point/CsDamageModifier_ValuePoint.h"
#include "Modifier/Value/Range/CsDamageModifier_ValueRange.h"
#include "Modifier/CsDamageModifierRange.h"
#include "Modifier/CsResource_DamageModifier.h"

#define CS_TEMP_ECHECK NCsDamage::NModifier::FLibrary::FModify::ECheck

const int32 NCsDamage::NModifier::FLibrary::FModify::SafeModifierImplementsInterface = ((int32)(CS_TEMP_ECHECK::Modifier) | (int32)(CS_TEMP_ECHECK::Value));
const int32 NCsDamage::NModifier::FLibrary::FModify::SafeModifiersImplementsInterface = ((int32)(CS_TEMP_ECHECK::Modifier) | (int32)(CS_TEMP_ECHECK::Modifiers_AnyNull) | (int32)(CS_TEMP_ECHECK::Value));

#undef CS_TEMP_ECHECK

namespace NCsDamage
{
	namespace NModifier
	{
		#define ModifierType NCsDamage::NModifier::IModifier
		#define DataType NCsDamage::NData::IData
		#define ValueType NCsDamage::NValue::IValue
		#define RangeType NCsDamage::NRange::IRange

		const FECsDamageModifier& FLibrary::GetTypeChecked(const FString& Context, const ModifierType* Modifier)
		{
			CS_IS_PTR_NULL_CHECKED(Modifier)

			typedef NCsDamage::NModifier::NValue::NPoint::IPoint ModiferValuePointType;
			typedef NCsDamage::NModifier::NValue::NRange::IRange ModiferValueRangeType;
			typedef NCsDamage::NModifier::NRange::IRange ModifierRangeType;

			// ValuePoint
			if (GetSafeInterfaceChecked<ModiferValuePointType>(Context, Modifier))
				return NCsDamageModifier::ValuePoint;
			// ValueRange
			if (GetSafeInterfaceChecked<ModiferValueRangeType>(Context, Modifier))
				return NCsDamageModifier::ValueRange;
			// Range
			if (GetSafeInterfaceChecked<ModifierRangeType>(Context, Modifier))
				return NCsDamageModifier::Range;

			checkf(0, TEXT("%s: Failed to determine type (FECsDamageModifier) for Value."), *Context);
			return EMCsDamageModifier::Get().GetMAX();
		}

		bool FLibrary::CopyChecked(const FString& Context, const ModifierType* From, ModifierType* To)
		{
			CS_IS_PTR_NULL_CHECKED(From)

			CS_IS_PTR_NULL_CHECKED(To)
			return false;
		}

		bool FLibrary::ModifyChecked(const FString& Context, const ModifierType* Modifier, const DataType* Data, ValueType* Value)
		{
			CS_IS_PTR_NULL_CHECKED(Modifier)

			CS_IS_PTR_NULL_CHECKED(Data)

			CS_IS_PTR_NULL_CHECKED(Value)
			return false;
		}

		bool FLibrary::ModifyChecked(const FString& Context, const ModifierType* Modifier, const DataType* Data, RangeType* Range)
		{
			CS_IS_PTR_NULL_CHECKED(Modifier)

			CS_IS_PTR_NULL_CHECKED(Data)

			CS_IS_PTR_NULL_CHECKED(Range)
			return false;	 
		}

		#define ModifierResourceType NCsDamage::NModifier::FResource

		void FLibrary::ModifyChecked(const FString& Context, const TArray<ModifierResourceType*>& Modifiers, const DataType* Data, ValueType* Value, RangeType* Range)
		{
			for (const ModifierResourceType* Resource : Modifiers)
			{
				const ModifierType* Modifier = Resource->Get();

				ModifyChecked(Context, Modifier, Data, Value);
				ModifyChecked(Context, Modifier, Data, Range);
			}
		}

		void FLibrary::ModifyChecked(const FString& Context, const TArray<ModifierResourceType*>& Modifiers, const DataType* Data, ValueType* Value)
		{
			for (const ModifierResourceType* Resource : Modifiers)
			{
				const ModifierType* Modifier = Resource->Get();

				ModifyChecked(Context, Modifier, Data, Value);
			}
		}

		#undef ModifierResourceType

		#define AllocatedModifierType NCsDamage::NModifier::FAllocated

		void FLibrary::ModifyChecked(const FString& Context, const TArray<AllocatedModifierType>& Modifiers, const DataType* Data, ValueType* Value, RangeType* Range)
		{
			for (const AllocatedModifierType& AllocatedModifier : Modifiers)
			{
				const ModifierType* Modifier = AllocatedModifier.GetModifier();

				ModifyChecked(Context, Modifier, Data, Value);
				ModifyChecked(Context, Modifier, Data, Range);
			}
		}

		void FLibrary::ModifyChecked(const FString& Context, const TArray<AllocatedModifierType>& Modifiers, const DataType* Data, ValueType* Value)
		{
			for (const AllocatedModifierType& AllocatedModifier : Modifiers)
			{
				const ModifierType* Modifier = AllocatedModifier.GetModifier();

				ModifyChecked(Context, Modifier, Data, Value);
			}
		}

		#undef AllocatedModifierType

		void FLibrary::ConditionalModifyChecked(const FString& Context, const ModifierType* Modifier, ValueType* Value, const int32& CheckMask /*=FModify::SafeModifierImplementsInterface*/)
		{
			typedef NCsDamage::NModifier::FLibrary::FModify::ECheck CheckType;

			void(*Log)(const FString&) = nullptr;

			if (CS_TEST_BITFLAG(CheckMask, CheckType::Modifier))
			{
				CS_IS_PTR_NULL_CHECKED(Modifier)
			}
			else
			{
				CS_IS_PTR_NULL_EXIT(Modifier)
			}

			if (CS_TEST_BITFLAG(CheckMask, CheckType::Value))
			{
				CS_IS_PTR_NULL_CHECKED(Value)
			}
			else
			{
				CS_IS_PTR_NULL_EXIT(Value)
			}

			typedef NCsDamage::NModifier::NValue::IValue ValueModifierType;

			if (CS_TEST_BLUEPRINT_BITFLAG(CheckMask, CheckType::Modifier_ImplementsInterface))
			{
				const ValueModifierType* ValueModifier = GetInterfaceChecked<ValueModifierType>(Context, Modifier);
				
				ValueModifier->Modify(Value);
			}
			else
			{
				if (const ValueModifierType* ValueModifier = GetSafeInterfaceChecked<ValueModifierType>(Context, Modifier))
				{
					ValueModifier->Modify(Value);
				}
			}
		}

		void FLibrary::ConditionalModifyChecked(const FString& Context, const TArray<ModifierType*>& Modifiers, ValueType* Value, const int32& CheckMask /*=FModify::SafeModifiersImplementsInterface*/)
		{
			typedef NCsDamage::NModifier::FLibrary::FModify::ECheck CheckType;

			if (CS_TEST_BITFLAG(CheckMask, CheckType::Modifiers_Empty))
			{
				CS_IS_ARRAY_EMPTY_CHECKED(Modifiers, ModifierType*)
			}

			void(*Log)(const FString&) = nullptr;

			if (CS_TEST_BITFLAG(CheckMask, CheckType::Modifiers_AnyNull))
			{
				CS_IS_ARRAY_ANY_NULL_CHECKED(Modifiers, ModifierType)
			}
			else
			{
				//CS_IS_ARRAY_ANY_NULL_EXIT(Modifiers, ModifierType)
			}

			for (const ModifierType* Modifier : Modifiers)
			{
				ConditionalModifyChecked(Context, Modifier, Value, CheckMask);
			}
		}

		#undef ModifierType
		#undef DataType
		#undef ValueType
		#undef RangeType
	}
}