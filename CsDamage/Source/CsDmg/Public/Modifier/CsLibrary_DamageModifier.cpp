// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsLibrary_DamageModifier.h"
#include "CsDmg.h"

// Library
#include "Value/CsLibrary_DamageValue.h"
#include "Modifier/CsLibrary_Modifier.h"
#include "Library/CsLibrary_Valid.h"
// Damage
#include "Value/Point/CsDamageValuePoint.h"
#include "Value/Range/CsDamageValueRange.h"
	// Modifier
#include "Modifier/Types/CsGetDamageModifierType.h"
#include "Modifier/Value/CsDamageModifier_Value.h" // TODO: Remove
#include "Modifier/Value/Point/CsDamageModifier_ValuePoint.h" // TODO: Remove
#include "Modifier/Value/Range/CsDamageModifier_ValueRange.h" // TODO: Remove
#include "Modifier/CsDamageModifierRange.h"
#include "Modifier/CsResource_DamageModifier.h"
// Modifier
#include "Modifier/CsModifier_Int.h"
#include "Modifier/CsModifier_Int_Range.h"
#include "Modifier/CsModifier_Float.h"
#include "Modifier/CsModifier_Float_Range.h"

namespace NCsDamage
{
	namespace NModifier
	{
		#define ModifierType NCsDamage::NModifier::IModifier
		#define DataType NCsDamage::NData::IData
		#define ValueType NCsDamage::NValue::IValue
		#define RangeType NCsDamage::NRange::IRange
		#define ModifierResourceType NCsDamage::NModifier::FResource
		#define AllocatedModifierType NCsDamage::NModifier::FAllocated

		const FECsDamageModifier& FLibrary::GetTypeChecked(const FString& Context, const ModifierType* Modifier)
		{
			const ICsGetDamageModifierType* GetDamageModifierType = GetInterfaceChecked<ICsGetDamageModifierType>(Context, Modifier);
			
			return GetDamageModifierType->GetDamageModifierType();
		}

		bool FLibrary::CopyChecked(const FString& Context, const ModifierType* From, ModifierType* To)
		{
			CS_IS_PTR_NULL_CHECKED(From)

			CS_IS_PTR_NULL_CHECKED(To)
			return false;
		}

		void FLibrary::CopyChecked(const FString& Context, const TArray<AllocatedModifierType>& From, TArray<ModifierResourceType*>& To)
		{
			To.Reset(FMath::Max(To.Max(), From.Num()));

			for (const AllocatedModifierType& AllocatedModifier : From)
			{
				ModifierResourceType* Resource = AllocatedModifier.GetContainerChecked(Context);

				To.Add(Resource);
			}
		}

		void FLibrary::CopyChecked(const FString& Context, const TArray<AllocatedModifierType>& From, TArray<ModifierType*>& To)
		{
			To.Reset(FMath::Max(To.Max(), From.Num()));

			for (const AllocatedModifierType& AllocatedModifier : From)
			{
				ModifierResourceType* Resource = AllocatedModifier.GetContainerChecked(Context);
				ModifierType* Modifier		   = Resource->Get();

				To.Add(Modifier);
			}
		}

		void FLibrary::AddChecked(const FString& Context, UObject* WorldContext, const TArray<ModifierType*>& Modifiers, TArray<AllocatedModifierType>& AllocatedModifiers)
		{
			CS_IS_ARRAY_ANY_NULL_CHECKED(Modifiers, ModifierType)

			const int32 CountToAdd = Modifiers.Num();

			if (AllocatedModifiers.Num() + CountToAdd > AllocatedModifiers.Max())
			{
				const int32 Count = AllocatedModifiers.Num();

				static TArray<AllocatedModifierType> TempModifiers;
				TempModifiers.Reset(FMath::Max(TempModifiers.Max(), Count + CountToAdd));
				TempModifiers.AddDefaulted(Count + CountToAdd);

				for (int32 I = 0; I < Count; ++I)
				{
					AllocatedModifiers[I].Transfer(TempModifiers[I]);
				}
				AllocatedModifiers.Reset(Count + CountToAdd);
				AllocatedModifiers.AddDefaulted(Count);

				for (int32 I = 0; I < Count; ++I)
				{
					TempModifiers[I].Transfer(AllocatedModifiers[I]);
				}
			}

			for (ModifierType* Modifier : Modifiers)
			{
				AllocatedModifierType& AllocatedModifier = AllocatedModifiers.AddDefaulted_GetRef();
				AllocatedModifier.Copy(WorldContext, Modifier);
			}
		}

		void FLibrary::ModifyChecked(const FString& Context, const ModifierType* Modifier, const DataType* Data, ValueType* Value)
		{
			CS_IS_PTR_NULL_CHECKED(Modifier)
			CS_IS_PTR_NULL_CHECKED(Data)
			CS_IS_PTR_NULL_CHECKED(Value)

			typedef NCsModifier::FLibrary ModifierLibrary;
			typedef NCsDamage::NValue::FLibrary ValueLibrary;

			// Point
			typedef NCsDamage::NValue::NPoint::IPoint ValuePointType;

			if (ValuePointType* Point = ValueLibrary::GetSafeInterfaceChecked<ValuePointType>(Context, Value))
			{
				const FECsDamageModifier& DmgModifierType = GetTypeChecked(Context, Modifier);

				if (DmgModifierType == NCsDamageModifier::ValuePoint)
				{
					float& V = *(const_cast<float*>(&(Point->GetValue())));

					// Float
					typedef NCsModifier::NFloat::IFloat FloatModifierType;

					const FloatModifierType* FloatModifier = GetInterfaceChecked<FloatModifierType>(Context, Modifier);

					V = ModifierLibrary::ModifyFloatChecked(Context, FloatModifier, V);
				}
				return;
			}
			// Range
			typedef NCsDamage::NValue::NRange::IRange ValueRangeType;

			if (ValueRangeType* Range = ValueLibrary::GetSafeInterfaceChecked<ValueRangeType>(Context, Value))
			{
				const FECsDamageModifier& DmgModifierType = GetTypeChecked(Context, Modifier);

				if (DmgModifierType == NCsDamageModifier::ValueRange)
				{
					float& Min = *(const_cast<float*>(&(Range->GetMinValue())));
					float& Max = *(const_cast<float*>(&(Range->GetMaxValue())));

					// Float
					typedef NCsModifier::NFloat::IFloat FloatModifierType;

					if (const FloatModifierType* FloatModifier = GetSafeInterfaceChecked<FloatModifierType>(Context, Modifier))
					{
						Min = ModifierLibrary::ModifyFloatChecked(Context, FloatModifier, Min);
						Max = ModifierLibrary::ModifyFloatChecked(Context, FloatModifier, Max);
						return;
					}

					// Float Range
					typedef NCsModifier::NFloat::NRange::IRange FloatRangeModifierType;

					if (const FloatRangeModifierType* FloatRangeModifier = GetSafeInterfaceChecked<FloatRangeModifierType>(Context, Modifier))
					{
						Min = ModifierLibrary::ModifyFloatMinChecked(Context, FloatRangeModifier, Min);
						Max = ModifierLibrary::ModifyFloatMaxChecked(Context, FloatRangeModifier, Max);
						return;
					}
				}
				return;
			}
			
			checkf(0, TEXT("%s: Failed to Apply Modifiers to Value. No supported interfaces found for Value."), *Context);
		}

		bool FLibrary::ModifyChecked(const FString& Context, const ModifierType* Modifier, const DataType* Data, RangeType* Range)
		{
			CS_IS_PTR_NULL_CHECKED(Modifier)

			CS_IS_PTR_NULL_CHECKED(Data)

			CS_IS_PTR_NULL_CHECKED(Range)
			return false;	 
		}

		void FLibrary::ModifyChecked(const FString& Context, const TArray<ModifierType*>& Modifiers, const DataType* Data, ValueType* Value)
		{
			CS_IS_ARRAY_ANY_NULL_CHECKED(Modifiers, ModifierType)
			CS_IS_PTR_NULL_CHECKED(Data)
			CS_IS_PTR_NULL_CHECKED(Value)

			typedef NCsModifier::FLibrary ModifierLibrary;
			typedef NCsDamage::NValue::FLibrary ValueLibrary;
			typedef NCsModifier::NFloat::IFloat FloatModifierType;
			typedef NCsModifier::NFloat::NRange::IRange FloatRangeModifierType;

			for (const ModifierType* Modifier : Modifiers)
			{
				// Point
				typedef NCsDamage::NValue::NPoint::IPoint ValuePointType;

				if (ValuePointType* Point = ValueLibrary::GetSafeInterfaceChecked<ValuePointType>(Context, Value))
				{
					const FECsDamageModifier& DmgModifierType = GetTypeChecked(Context, Modifier);

					if (DmgModifierType == NCsDamageModifier::ValuePoint)
					{
						const FloatModifierType* FloatModifier = GetInterfaceChecked<FloatModifierType>(Context, Modifier);

						float& V = *(const_cast<float*>(&(Point->GetValue())));

						V = ModifierLibrary::ModifyFloatChecked(Context, FloatModifier, V);
					}
				}

				// Range
				typedef NCsDamage::NValue::NRange::IRange ValueRangeType;

				if (ValueRangeType* Range = ValueLibrary::GetSafeInterfaceChecked<ValueRangeType>(Context, Value))
				{
					const FECsDamageModifier& DmgModifierType = GetTypeChecked(Context, Modifier);

					if (DmgModifierType == NCsDamageModifier::ValueRange)
					{
						float& Min = *(const_cast<float*>(&(Range->GetMinValue())));
						float& Max = *(const_cast<float*>(&(Range->GetMaxValue())));

						// Float
						if (const FloatModifierType* FloatModifier = GetSafeInterfaceChecked<FloatModifierType>(Context, Modifier))
						{
							Min = ModifierLibrary::ModifyFloatChecked(Context, FloatModifier, Min);
							Max = ModifierLibrary::ModifyFloatChecked(Context, FloatModifier, Max);
						}

						// Float Range
						if (const FloatRangeModifierType* FloatRangeModifier = GetSafeInterfaceChecked<FloatRangeModifierType>(Context, Modifier))
						{
							Min = ModifierLibrary::ModifyFloatMinChecked(Context, FloatRangeModifier, Min);
							Max = ModifierLibrary::ModifyFloatMaxChecked(Context, FloatRangeModifier, Max);
						}	
					}
				}
			}
		}

		void FLibrary::ModifyChecked(const FString& Context, const TArray<ModifierType*>& Modifiers, const DataType* Data, ValueType* Value, RangeType* Range)
		{
			CS_IS_ARRAY_ANY_NULL_CHECKED(Modifiers, ModifierType)
			CS_IS_PTR_NULL_CHECKED(Data)
			CS_IS_PTR_NULL_CHECKED(Value)
			CS_IS_PTR_NULL_CHECKED(Range)
		}

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
			CS_IS_ARRAY_ANY_NULL_CHECKED(Modifiers, ModifierResourceType)
			CS_IS_PTR_NULL_CHECKED(Data)
			CS_IS_PTR_NULL_CHECKED(Value)

			typedef NCsModifier::FLibrary ModifierLibrary;
			typedef NCsDamage::NValue::FLibrary ValueLibrary;
			typedef NCsModifier::NFloat::IFloat FloatModifierType;
			typedef NCsModifier::NFloat::NRange::IRange FloatRangeModifierType;

			for (ModifierResourceType* M : Modifiers)
			{
				ModifierType* Modifier = M->Get();

				// Point
				typedef NCsDamage::NValue::NPoint::IPoint ValuePointType;

				if (ValuePointType* Point = ValueLibrary::GetSafeInterfaceChecked<ValuePointType>(Context, Value))
				{
					const FECsDamageModifier& DmgModifierType = GetTypeChecked(Context, Modifier);

					if (DmgModifierType == NCsDamageModifier::ValuePoint)
					{
						FloatModifierType* FloatModifier = GetInterfaceChecked<FloatModifierType>(Context, Modifier);

						float& V = *(const_cast<float*>(&(Point->GetValue())));

						V = ModifierLibrary::ModifyFloatChecked(Context, FloatModifier, V);
					}
				}

				// Range
				typedef NCsDamage::NValue::NRange::IRange ValueRangeType;

				if (ValueRangeType* Range = ValueLibrary::GetSafeInterfaceChecked<ValueRangeType>(Context, Value))
				{
					const FECsDamageModifier& DmgModifierType = GetTypeChecked(Context, Modifier);

					if (DmgModifierType == NCsDamageModifier::ValueRange)
					{
						float& Min = *(const_cast<float*>(&(Range->GetMinValue())));
						float& Max = *(const_cast<float*>(&(Range->GetMaxValue())));

						// Float
						if (FloatModifierType* FloatModifier = GetSafeInterfaceChecked<FloatModifierType>(Context, Modifier))
						{
							Min = ModifierLibrary::ModifyFloatChecked(Context, FloatModifier, Min);
							Max = ModifierLibrary::ModifyFloatChecked(Context, FloatModifier, Max);
						}

						// Float Range
						if (FloatRangeModifierType* FloatRangeModifier = GetSafeInterfaceChecked<FloatRangeModifierType>(Context, Modifier))
						{
							Min = ModifierLibrary::ModifyFloatMinChecked(Context, FloatRangeModifier, Min);
							Max = ModifierLibrary::ModifyFloatMaxChecked(Context, FloatRangeModifier, Max);
						}	
					}
				}
			}
		}

		void FLibrary::ModifyChecked(const FString& Context, const TArray<AllocatedModifierType>& Modifiers, const DataType* Data, ValueType* Value, RangeType* Range)
		{
			// TODO: FUTURE: Use a tiny / small array on the stack

			for (const AllocatedModifierType& AllocatedModifier : Modifiers)
			{
				const ModifierType* Modifier = AllocatedModifier.Get();

				ModifyChecked(Context, Modifier, Data, Value);
				ModifyChecked(Context, Modifier, Data, Range);
			}
		}

		void FLibrary::ModifyChecked(const FString& Context, const TArray<AllocatedModifierType>& Modifiers, const DataType* Data, ValueType* Value)
		{
			for (const AllocatedModifierType& AllocatedModifier : Modifiers)
			{
				const ModifierType* Modifier = AllocatedModifier.Get();

				ModifyChecked(Context, Modifier, Data, Value);
			}
		}

		#undef ModifierType
		#undef DataType
		#undef ValueType
		#undef RangeType
		#undef ModifierResourceType
		#undef AllocatedModifierType
	}
}