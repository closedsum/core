// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Modifier/CsLibrary_DamageModifier.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Damage
#include "Managers/Damage/Modifier/Value/Point/CsDamageModifier_ValuePoint.h"
#include "Managers/Damage/Modifier/Value/Range/CsDamageModifier_ValueRange.h"
#include "Managers/Damage/Modifier/CsDamageModifierRange.h"
#include "Managers/Damage/Modifier/CsResource_DamageModifier.h"

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

		#undef ModifierType
		#undef DataType
		#undef ValueType
		#undef RangeType
	}
}