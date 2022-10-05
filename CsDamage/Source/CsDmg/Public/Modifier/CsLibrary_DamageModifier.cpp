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
		#define BaseModifierType NCsModifier::IModifier

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

		void FLibrary::CopyChecked(const FString& Context, const TArray<BaseModifierType*>& From, TArray<ModifierType*>& To)
		{
			typedef NCsModifier::FLibrary ModifierLibrary;

			To.Reset(FMath::Max(To.Max(), From.Num()));

			for (BaseModifierType* B : From)
			{
				if (ModifierType* Modifier = ModifierLibrary::GetSafeInterfaceChecked<ModifierType>(Context, B))
				{
					To.Add(Modifier);
				}
			}
		}

		void FLibrary::AddChecked(const FString& Context, UObject* WorldContext, const TArray<ModifierType*>& From, TArray<AllocatedModifierType>& To)
		{
			CS_IS_TARRAY_ANY_NULL_CHECKED(From, ModifierType)

			const int32 CountToAdd = From.Num();

			if (To.Num() + CountToAdd > To.Max())
			{
				const int32 Count = To.Num();

				static TArray<AllocatedModifierType> TempModifiers;
				TempModifiers.AddDefaulted(Count + CountToAdd);

				for (int32 I = 0; I < Count; ++I)
				{
					To[I].Transfer(TempModifiers[I]);
				}
				To.Reset(Count + CountToAdd);
				To.AddDefaulted(Count);

				for (int32 I = Count - 1; I >= 0; --I)
				{
					TempModifiers[I].Transfer(To[I]);
					TempModifiers.RemoveAt(I, 1, false);
				}
			}

			for (ModifierType* Modifier : From)
			{
				AllocatedModifierType& AllocatedModifier = To.AddDefaulted_GetRef();
				AllocatedModifier.Copy(WorldContext, Modifier);
			}
		}	

		void FLibrary::AddChecked(const FString& Context, const TArray<ModifierType*>& From, TArray<BaseModifierType*>& To)
		{
			CS_IS_TARRAY_ANY_NULL_CHECKED(From, ModifierType)

			const int32 ToSize = To.Num();
			const int32 FromSize = From.Num();

			To.AddDefaulted(From.Num());

			for (int32 I = 0; I < FromSize; ++I)
			{
				ModifierType* F		= From[I];				
				BaseModifierType* T = GetInterfaceChecked<BaseModifierType>(Context, F);

				To[ToSize + I] = T;
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
			uint32 Mask = 0;
			ModifyChecked(Context, Modifiers, Data, Value, Mask);
		}

		void FLibrary::ModifyChecked(const FString& Context, const TArray<ModifierType*>& Modifiers, const DataType* Data, ValueType* Value, uint32& OutMask)
		{
			if (Modifiers.Num() <= 64)
			{
				ModifyChecked_Size64(Context, Modifiers, Data, Value, OutMask);
			}
			else
			{
				CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, ModifierType)
				CS_IS_PTR_NULL_CHECKED(Data)
				CS_IS_PTR_NULL_CHECKED(Value)
				
				typedef NCsModifier::FLibrary ModifierLibrary;
				typedef NCsDamage::NValue::FLibrary ValueLibrary;
				typedef NCsModifier::NFloat::IFloat FloatModifierType;
				typedef NCsModifier::NFloat::NRange::IRange FloatRangeModifierType;

				// Value
			
					// Point
				typedef NCsDamage::NValue::NPoint::IPoint ValuePointType;

				ValuePointType* ValuePoint = ValueLibrary::GetSafeInterfaceChecked<ValuePointType>(Context, Value);
				static TArray<FloatModifierType*> ValuePoint_FloatModifiers;
				float* ValuePoint_Value = nullptr;

				if (ValuePoint)
				{
					ValuePoint_Value = const_cast<float*>(&(ValuePoint->GetValue()));
				}

					// Range
				typedef NCsDamage::NValue::NRange::IRange ValueRangeType;

				ValueRangeType* ValueRange = ValueLibrary::GetSafeInterfaceChecked<ValueRangeType>(Context, Value);
				static TArray<FloatModifierType*> ValueRange_FloatModifiers;
				static TArray<FloatRangeModifierType*> ValueRange_FloatRangeModifiers;
				float* ValueRange_ValueMin = nullptr;
				float* ValueRange_ValueMax = nullptr;

				if (ValueRange)
				{
					ValueRange_ValueMin = const_cast<float*>(&(ValueRange->GetMinValue()));
					ValueRange_ValueMax = const_cast<float*>(&(ValueRange->GetMaxValue()));
				}


				// Critical Chance
				static TArray<FloatModifierType*> CriticalChance_FloatModifiers;
				// Critical Strike
				static TArray<FloatModifierType*> CriticalStrike_FloatModifiers;

				for (ModifierType* Modifier : Modifiers)
				{
					const FECsDamageModifier& DmgModifierType = GetTypeChecked(Context, Modifier);

					// Value
				
						// Point
					if (ValuePoint)
					{
						if (DmgModifierType == NCsDamageModifier::ValuePoint)
						{
							FloatModifierType* FloatModifier = GetInterfaceChecked<FloatModifierType>(Context, Modifier);

							ValuePoint_FloatModifiers.Add(FloatModifier);
						}
					}

					// Range
					if (ValueRange)
					{
						if (DmgModifierType == NCsDamageModifier::ValueRange)
						{
							// Float
							if (FloatModifierType* FloatModifier = GetSafeInterfaceChecked<FloatModifierType>(Context, Modifier))
							{
								ValueRange_FloatModifiers.Add(FloatModifier);
							}

							// Float Range
							if (FloatRangeModifierType* FloatRangeModifier = GetSafeInterfaceChecked<FloatRangeModifierType>(Context, Modifier))
							{
								ValueRange_FloatRangeModifiers.Add(FloatRangeModifier);
							}	
						}
					}

					// TODO: Range
				}

				// Get Critical Chance
				//  Assume Default Chance starts at 0.0f
				//  Assume Chance is in the range [0.0f, 1.0f]
				float CriticalChance = 0.0f;
				CriticalChance		 = ModifierLibrary::ModifyFloatAndEmptyChecked(Context, CriticalChance_FloatModifiers, CriticalChance);

				// TODO: Need somewhere to take Random Seem
	
				// Check to Apply Critical Strike
				//	 Assume Default Strike multiplier is 1.0f
				float CriticalStrike = 1.0f;

				if (CriticalChance >= FMath::FRandRange(0.0f, 1.0f))
				{
					CriticalStrike = ModifierLibrary::ModifyFloatAndEmptyChecked(Context, CriticalStrike_FloatModifiers, CriticalStrike);
				}

				if (ValuePoint)
				{
					*ValuePoint_Value  = ModifierLibrary::ModifyFloatAndEmptyChecked(Context, ValuePoint_FloatModifiers, *ValuePoint_Value);
					*ValuePoint_Value *= CriticalStrike;

					if (ValuePoint_FloatModifiers.Num() > CS_EMPTY)
					{
						OutMask |= (1 << NCsDamageModifier::ValuePoint.GetValue());
					}

					if (CriticalChance > 0.0f)
					{
						OutMask |= (1 << NCsDamageModifier::CriticalChance.GetValue());
					}

					if (CriticalStrike > 0.0f)
					{
						OutMask |= (1 << NCsDamageModifier::CriticalStrike.GetValue());
					}
				}

				if (ValueRange)
				{
					const float A = ValueRange_FloatModifiers.Num();
					const float B = ValueRange_FloatRangeModifiers.Num();

					checkf((A == 0 && B == 0) || (A > 0 && B == 0) || (A == 0 && B > 0), TEXT("%s: Value currently can NOT be modified with a mix of Float and Float Range Modifiers."), *Context);

					*ValueRange_ValueMin = ModifierLibrary::ModifyFloatAndEmptyChecked(Context, ValueRange_FloatModifiers, *ValueRange_ValueMin);
					*ValueRange_ValueMax = ModifierLibrary::ModifyFloatAndEmptyChecked(Context, ValueRange_FloatModifiers, *ValueRange_ValueMax);

					*ValueRange_ValueMin = ModifierLibrary::ModifyFloatMinAndEmptyChecked(Context, ValueRange_FloatRangeModifiers, *ValueRange_ValueMin);
					*ValueRange_ValueMax = ModifierLibrary::ModifyFloatMaxAndEmptyChecked(Context, ValueRange_FloatRangeModifiers, *ValueRange_ValueMax);

					*ValueRange_ValueMin *= CriticalStrike;
					*ValueRange_ValueMax *= CriticalStrike;

					if (ValuePoint_FloatModifiers.Num() > CS_EMPTY)
					{
						OutMask |= (1 << NCsDamageModifier::ValuePoint.GetValue());
					}

					if (CriticalChance > 0.0f)
					{
						OutMask |= (1 << NCsDamageModifier::CriticalChance.GetValue());
					}

					if (CriticalStrike > 0.0f)
					{
						OutMask |= (1 << NCsDamageModifier::CriticalStrike.GetValue());
					}
				}
			}
		}

		void FLibrary::ModifyChecked(const FString& Context, const TArray<ModifierType*>& Modifiers, const DataType* Data, ValueType* Value, RangeType* Range)
		{
			CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, ModifierType)
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
			CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, ModifierResourceType)
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

		void FLibrary::ModifyChecked_Size64(const FString& Context, const TArray<ModifierType*>& Modifiers, const DataType* Data, ValueType* Value)
		{
			uint32 Mask = 0;
			ModifyChecked_Size64(Context, Modifiers, Data, Value, Mask);
		}

		void FLibrary::ModifyChecked_Size64(const FString& Context, const TArray<ModifierType*>& Modifiers, const DataType* Data, ValueType* Value, uint32& OutMask)
		{
			CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, ModifierType)
			CS_IS_TARRAY_LESS_THAN_OR_EQUAL_SIZE_CHECKED(Modifiers, ModifierType*, 64)
			CS_IS_PTR_NULL_CHECKED(Data)
			CS_IS_PTR_NULL_CHECKED(Value)

			typedef NCsModifier::FLibrary ModifierLibrary;
			typedef NCsDamage::NValue::FLibrary ValueLibrary;
			typedef NCsModifier::NFloat::IFloat FloatModifierType;
			typedef NCsModifier::NFloat::NRange::IRange FloatRangeModifierType;

			// Value
			
				// Point
			typedef NCsDamage::NValue::NPoint::IPoint ValuePointType;

			ValuePointType* ValuePoint = ValueLibrary::GetSafeInterfaceChecked<ValuePointType>(Context, Value);
			TArray<FloatModifierType*, TFixedAllocator<64>> ValuePoint_FloatModifiers;
			float* ValuePoint_Value = nullptr;

			if (ValuePoint)
			{
				ValuePoint_Value = const_cast<float*>(&(ValuePoint->GetValue()));
			}

				// Range
			typedef NCsDamage::NValue::NRange::IRange ValueRangeType;

			ValueRangeType* ValueRange = ValueLibrary::GetSafeInterfaceChecked<ValueRangeType>(Context, Value);
			TArray<FloatModifierType*, TFixedAllocator<64>> ValueRange_FloatModifiers;
			TArray<FloatRangeModifierType*, TFixedAllocator<64>> ValueRange_FloatRangeModifiers;
			float* ValueRange_ValueMin = nullptr;
			float* ValueRange_ValueMax = nullptr;

			if (ValueRange)
			{
				ValueRange_ValueMin = const_cast<float*>(&(ValueRange->GetMinValue()));
				ValueRange_ValueMax = const_cast<float*>(&(ValueRange->GetMaxValue()));
			}

			// Critical Chance
			TArray<FloatModifierType*, TFixedAllocator<64>> CriticalChance_FloatModifiers;
			// Critical Strike
			TArray<FloatModifierType*, TFixedAllocator<64>> CriticalStrike_FloatModifiers;

			for (ModifierType* Modifier : Modifiers)
			{
				const FECsDamageModifier& DmgModifierType = GetTypeChecked(Context, Modifier);

				// Value
				
					// Point
				if (ValuePoint)
				{

					if (DmgModifierType == NCsDamageModifier::ValuePoint)
					{
						FloatModifierType* FloatModifier = GetInterfaceChecked<FloatModifierType>(Context, Modifier);

						ValuePoint_FloatModifiers.Add(FloatModifier);
					}
				}

					// Range
				if (ValueRange)
				{
					if (DmgModifierType == NCsDamageModifier::ValueRange)
					{
						// Float
						if (FloatModifierType* FloatModifier = GetSafeInterfaceChecked<FloatModifierType>(Context, Modifier))
						{
							ValueRange_FloatModifiers.Add(FloatModifier);
						}

						// Float Range
						if (FloatRangeModifierType* FloatRangeModifier = GetSafeInterfaceChecked<FloatRangeModifierType>(Context, Modifier))
						{
							ValueRange_FloatRangeModifiers.Add(FloatRangeModifier);
						}	
					}
				}

				// TODO: Range

				// Critical Chance
				if (DmgModifierType == NCsDamageModifier::CriticalChance)
				{
					FloatModifierType* FloatModifier = GetInterfaceChecked<FloatModifierType>(Context, Modifier);

					CriticalChance_FloatModifiers.Add(FloatModifier);
				}
				// Critical Strike
				if (DmgModifierType == NCsDamageModifier::CriticalStrike)
				{
					FloatModifierType* FloatModifier = GetInterfaceChecked<FloatModifierType>(Context, Modifier);

					CriticalStrike_FloatModifiers.Add(FloatModifier);
				}
			}

			// Get Critical Chance
			//  Assume Default Chance starts at 0.0f
			//  Assume Chance is in the range [0.0f, 1.0f]
			float CriticalChance = 0.0f;
			CriticalChance		 = ModifierLibrary::ModifyFloatChecked(Context, CriticalChance_FloatModifiers, CriticalChance);

			// TODO: Need somewhere to take Random Seem
	
			// Check to Apply Critical Strike
			//	 Assume Default Strike multiplier is 1.0f
			float CriticalStrike = 1.0f;

			if (CriticalChance >= FMath::FRandRange(0.0f, 1.0f))
			{
				CriticalStrike = ModifierLibrary::ModifyFloatChecked(Context, CriticalStrike_FloatModifiers, CriticalStrike);
			}

			if (ValuePoint)
			{
				*ValuePoint_Value  = ModifierLibrary::ModifyFloatChecked(Context, ValuePoint_FloatModifiers, *ValuePoint_Value);
				*ValuePoint_Value *= CriticalStrike;

				if (ValuePoint_FloatModifiers.Num() > CS_EMPTY)
				{
					OutMask |= (1 << NCsDamageModifier::ValuePoint.GetValue());
				}

				if (CriticalChance > 0.0f)
				{
					OutMask |= (1 << NCsDamageModifier::CriticalChance.GetValue());
				}

				if (CriticalStrike > 0.0f)
				{
					OutMask |= (1 << NCsDamageModifier::CriticalStrike.GetValue());
				}
			}

			if (ValueRange)
			{
				const float A = ValueRange_FloatModifiers.Num();
				const float B = ValueRange_FloatRangeModifiers.Num();

				checkf((A == 0 && B == 0) || (A > 0 && B == 0) || (A == 0 && B > 0), TEXT("%s: Value currently can NOT be modified with a mix of Float and Float Range Modifiers."), *Context);

				*ValueRange_ValueMin = ModifierLibrary::ModifyFloatChecked(Context, ValueRange_FloatModifiers, *ValueRange_ValueMin);
				*ValueRange_ValueMax = ModifierLibrary::ModifyFloatChecked(Context, ValueRange_FloatModifiers, *ValueRange_ValueMax);

				*ValueRange_ValueMin = ModifierLibrary::ModifyFloatMinChecked(Context, ValueRange_FloatRangeModifiers, *ValueRange_ValueMin);
				*ValueRange_ValueMax = ModifierLibrary::ModifyFloatMaxChecked(Context, ValueRange_FloatRangeModifiers, *ValueRange_ValueMax);

				*ValueRange_ValueMin *= CriticalStrike;
				*ValueRange_ValueMax *= CriticalStrike;

				if (ValueRange_FloatModifiers.Num() > CS_EMPTY ||
					ValueRange_FloatRangeModifiers.Num() > CS_EMPTY)
				{
					OutMask |= (1 << NCsDamageModifier::ValueRange.GetValue());
				}

				if (CriticalChance > 0.0f)
				{
					OutMask |= (1 << NCsDamageModifier::CriticalChance.GetValue());
				}

				if (CriticalStrike > 0.0f)
				{
					OutMask |= (1 << NCsDamageModifier::CriticalStrike.GetValue());
				}
			}
		}

		#undef ModifierType
		#undef DataType
		#undef ValueType
		#undef RangeType
		#undef ModifierResourceType
		#undef AllocatedModifierType
		#undef BaseModifierType
	}
}